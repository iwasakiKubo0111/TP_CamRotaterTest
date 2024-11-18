// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_CamRotaterTestGameMode.generated.h"

UCLASS(minimalapi)
class ATP_CamRotaterTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_CamRotaterTestGameMode();
	virtual ~ATP_CamRotaterTestGameMode();

	UFUNCTION(BlueprintCallable, Category = "CreateWindowActor")
	void CreateWindow(const FVector2D& windowSize, const FVector2D& windowPos, const FText& tilte);

	UFUNCTION(BlueprintCallable, Category = "CreateWindowActor")
	void SetWidget(class UWidget* setWidget);

private:
	// ウィンドウ情報
	TSharedPtr<class SWindow> m_CreateWindow;
	// 別で作成されれたウィジェット配置用
	TSharedPtr<class SOverlay> m_WindowOverlay;
};



