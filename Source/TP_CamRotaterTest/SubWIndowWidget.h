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
    // BP_SCCamアクターへの参照
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    AActor* BP_SCCamActor;

    // ターゲットアクター（カメラが回転する中心）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    AActor* TargetActor;

    // カメラコンポーネント
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    USceneCaptureComponent2D* CameraComponent;

    // 回転速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float RotationSpeed = 0.1f;

    // カメラのターゲットからの距離
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float DistanceFromTarget = 300.0f;

private:
    // ドラッグ中かどうかのフラグ
    bool bIsDragging = false;

    // ドラッグ開始時の位置
    FVector2D StartDragLocation;

    // カメラの回転を行うヘルパー関数
    void RotateCameraAroundTarget(const FVector2D& Delta);

    //std::shared_ptr<ADummy> StdSharedPtr;

};
