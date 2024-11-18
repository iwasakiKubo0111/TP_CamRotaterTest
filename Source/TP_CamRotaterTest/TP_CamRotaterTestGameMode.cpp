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
*	�E�B���h�E�̍쐬
*	param : windowSize	�E�B���h�E�̃T�C�Y
*	param : windowPos	�E�B���h�E�̈ʒu
*	param : tilte		�E�B���h�E�̃^�C�g��
*/
void ATP_CamRotaterTestGameMode::CreateWindow(const FVector2D& windowSize, const FVector2D& windowPos, const FText& tilte)
{
	if (GEngine && GEngine->GameViewport) {
		// �E�B���h�E�쐬
		m_CreateWindow = SNew(SWindow)
			.Title(tilte/*LOCTEXT("CreateWindow", "Title")*/)
			.AutoCenter(EAutoCenter::None)
			.ScreenPosition(windowPos)
			.ClientSize(windowSize)
			.CreateTitleBar(true);

		m_WindowOverlay = SNew(SOverlay);


		//�E�B���h�E�ɐݒ肷��
		m_CreateWindow->SetContent(m_WindowOverlay.ToSharedRef());
		//m_CreateWindow->OnKeyDown(FOnKeyDown::CreateRaw(this, &AWindowCreateActor::HandleKeyDown));

		// �쐬�����E�B���h�E��e�E�B���h�E��ݒ肵�đ����\������
		//FSlateApplication::Get().AddWindowAsNativeChild(m_CreateWindow.ToSharedRef(), GEngine->GameViewport->GetWindow().ToSharedRef(), true);
		FSlateApplication::Get().AddWindow(m_CreateWindow.ToSharedRef(), true);
		FSlateApplication::Get().SetKeyboardFocus(m_CreateWindow.ToSharedRef());
		//FSlateApplication::Get().OnKeyDown
	}
}

/*
*	�E�B�W�b�g�̐ݒ�
*	param : setWidget �ǉ�����E�B�W�b�g
*/
void ATP_CamRotaterTestGameMode::SetWidget(UWidget* setWidget)
{
	if (m_WindowOverlay) {
		// �E�B�b�g��ݒ肷�邽�߂ɃI�[�o�[���C�Ɏw�肳�ꂽ�E�B�W�F�b�g��ݒ肷��
		auto OVerlaySlot = m_WindowOverlay.Get()->AddSlot();
		OVerlaySlot.AttachWidget(setWidget->TakeWidget());
	}
}