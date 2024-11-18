// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWIndowWidget.h"
#include "Components/Image.h"
#include <Camera/CameraComponent.h>
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void USubWIndowWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void USubWIndowWidget::InitializeCameraComponent()
{
    if (BP_SCCamActor)
    {
        CameraComponent = BP_SCCamActor->FindComponentByClass<USceneCaptureComponent2D>();

        if (!CameraComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("CameraComponent not found on BP_SCCamActor!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BP_SCCamActor is not set in the widget!"));
    }

}

FReply USubWIndowWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        bIsDragging = true; // �h���b�O�J�n
        StartDragLocation = InMouseEvent.GetScreenSpacePosition(); // �J�n�ʒu���L�^
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply USubWIndowWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsDragging && TargetActor && CameraComponent)
    {
        FVector2D CurrentLocation = InMouseEvent.GetScreenSpacePosition();
        FVector2D Delta = CurrentLocation - StartDragLocation;

        // ��]�������s���w���p�[�֐��̌Ăяo��
        RotateCameraAroundTarget(Delta);

        StartDragLocation = CurrentLocation; // ���݈ʒu���X�V
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply USubWIndowWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        bIsDragging = false; // �h���b�O�I��
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

void USubWIndowWidget::RotateCameraAroundTarget(const FVector2D& Delta)
{
    if (!TargetActor || !CameraComponent)
    {
        return;
    }

    // Yaw�i���E��]�j��Pitch�i�㉺��]�j�̌v�Z
    float DeltaYaw = Delta.X * RotationSpeed;
    float DeltaPitch = Delta.Y * RotationSpeed;

    // �J�����̐V������]�p�x���v�Z
    FRotator NewRotation = CameraComponent->GetComponentRotation();
    NewRotation.Yaw += DeltaYaw;
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + DeltaPitch, -80.0f, 80.0f); // �s�b�`�͈͂𐧌�

    // �J�������^�[�Q�b�g�̎���ŉ�]
    FVector TargetLocation = TargetActor->GetActorLocation();
    FVector NewLocation = TargetLocation - NewRotation.Vector() * DistanceFromTarget; // �������ێ����ăJ������z�u

    // �J�����̈ʒu�Ɖ�]��ݒ�
    CameraComponent->SetWorldLocationAndRotation(NewLocation, NewRotation);
}
