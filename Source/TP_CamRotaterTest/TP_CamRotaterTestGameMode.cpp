// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_CamRotaterTestGameMode.h"
#include "TP_CamRotaterTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Slate.h"
#include "SlateCore.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "Components/Widget.h"
#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"

ATP_CamRotaterTestGameMode::ATP_CamRotaterTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

ATP_CamRotaterTestGameMode::~ATP_CamRotaterTestGameMode()
{
	if (m_WindowOverlay) {

		m_WindowOverlay.Get()->ClearChildren();
		m_WindowOverlay.Reset();
	}

	if (m_CreateWindow) {
		FSlateApplication::Get().RequestDestroyWindow(m_CreateWindow.ToSharedRef());
	}
}

/*
*	ウィンドウの作成
*	param : windowSize	ウィンドウのサイズ
*	param : windowPos	ウィンドウの位置
*	param : tilte		ウィンドウのタイトル
*/
void ATP_CamRotaterTestGameMode::CreateWindow(const FVector2D& windowSize, const FVector2D& windowPos, const FText& tilte)
{
	if (GEngine && GEngine->GameViewport) {
		// ウィンドウ作成
		m_CreateWindow = SNew(SWindow)
			.Title(tilte/*LOCTEXT("CreateWindow", "Title")*/)
			.AutoCenter(EAutoCenter::None)
			.ScreenPosition(windowPos)
			.ClientSize(windowSize)
			.CreateTitleBar(true);

		m_WindowOverlay = SNew(SOverlay);


		//ウィンドウに設定する
		m_CreateWindow->SetContent(m_WindowOverlay.ToSharedRef());
		//m_CreateWindow->OnKeyDown(FOnKeyDown::CreateRaw(this, &AWindowCreateActor::HandleKeyDown));

		// 作成したウィンドウを親ウィンドウを設定して即座表示する
		//FSlateApplication::Get().AddWindowAsNativeChild(m_CreateWindow.ToSharedRef(), GEngine->GameViewport->GetWindow().ToSharedRef(), true);
		FSlateApplication::Get().AddWindow(m_CreateWindow.ToSharedRef(), true);
		FSlateApplication::Get().SetKeyboardFocus(m_CreateWindow.ToSharedRef());
		//FSlateApplication::Get().OnKeyDown
	}
}

/*
*	ウィジットの設定
*	param : setWidget 追加するウィジット
*/
void ATP_CamRotaterTestGameMode::SetWidget(UWidget* setWidget)
{
	if (m_WindowOverlay) {
		// ウィットを設定するためにオーバーレイに指定されたウィジェットを設定する
		auto OVerlaySlot = m_WindowOverlay.Get()->AddSlot();
		OVerlaySlot.AttachWidget(setWidget->TakeWidget());
	}
}