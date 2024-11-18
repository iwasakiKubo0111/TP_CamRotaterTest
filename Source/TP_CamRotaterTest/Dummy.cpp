// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"

// Sets default values
//ADummy::ADummy()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}

ADummy::ADummy()
{
	UE_LOG(LogTemp, Warning, TEXT("Called ADummy::ADummy()"));
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Called first ADummy::Tick() 1"));

	if (!flg)
	{
		flg = true;
		UE_LOG(LogTemp, Warning, TEXT("Called first ADummy::Tick() 2"));
		StdSharedPtr = std::make_shared<ADummy2>();
		//TSharedPtr<ADummy2> UnrealSharedPtr(StdSharedPtr.get());
		TSharedPtr<ADummy2> UnrealSharedPtr = MakeShareable(StdSharedPtr.get());
	}
}

