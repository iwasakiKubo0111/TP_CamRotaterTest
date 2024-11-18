// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/SceneCaptureComponent2D.h>
#include "Dummy.h"
#include "SubWIndowWidget.generated.h"

class AActor;

/**
 * 
 */
UCLASS()
class TP_CAMROTATERTEST_API USubWIndowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    UFUNCTION(BlueprintCallable)
    void InitializeCameraComponent();
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
    // BP_SCCam�A�N�^�[�ւ̎Q��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    AActor* BP_SCCamActor;

    // �^�[�Q�b�g�A�N�^�[�i�J��������]���钆�S�j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    AActor* TargetActor;

    // �J�����R���|�[�l���g
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    USceneCaptureComponent2D* CameraComponent;

    // ��]���x
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float RotationSpeed = 0.1f;

    // �J�����̃^�[�Q�b�g����̋���
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float DistanceFromTarget = 300.0f;

private:
    // �h���b�O�����ǂ����̃t���O
    bool bIsDragging = false;

    // �h���b�O�J�n���̈ʒu
    FVector2D StartDragLocation;

    // �J�����̉�]���s���w���p�[�֐�
    void RotateCameraAroundTarget(const FVector2D& Delta);

    //std::shared_ptr<ADummy> StdSharedPtr;

};
