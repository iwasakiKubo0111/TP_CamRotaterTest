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
        bIsDragging = true; // ドラッグ開始
        StartDragLocation = InMouseEvent.GetScreenSpacePosition(); // 開始位置を記録
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

        // 回転処理を行うヘルパー関数の呼び出し
        RotateCameraAroundTarget(Delta);

        StartDragLocation = CurrentLocation; // 現在位置を更新
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply USubWIndowWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        bIsDragging = false; // ドラッグ終了
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

    // Yaw（左右回転）とPitch（上下回転）の計算
    float DeltaYaw = Delta.X * RotationSpeed;
    float DeltaPitch = Delta.Y * RotationSpeed;

    // カメラの新しい回転角度を計算
    FRotator NewRotation = CameraComponent->GetComponentRotation();
    NewRotation.Yaw += DeltaYaw;
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + DeltaPitch, -80.0f, 80.0f); // ピッチ範囲を制限

    // カメラをターゲットの周りで回転
    FVector TargetLocation = TargetActor->GetActorLocation();
    FVector NewLocation = TargetLocation - NewRotation.Vector() * DistanceFromTarget; // 距離を維持してカメラを配置

    // カメラの位置と回転を設定
    CameraComponent->SetWorldLocationAndRotation(NewLocation, NewRotation);
}
