// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FinalProjectGameMode.h"
#include "FinalProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
// #include "SpawnVolume.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"

AFinalProjectGameMode::AFinalProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// スタミナが回復していくスピード
	DecayRate = 0.1f;

	// Tick関数を有効にする
	PrimaryActorTick.bCanEverTick = true;
}

void AFinalProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFinalProjectCharacter* MyCharacter = Cast<AFinalProjectCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		
		if (MyCharacter->GetCharacterWinPower() >= PowerToWin)
			SetCurrentState(EFinalPlayState::EWon);
		else  if (MyCharacter->GetCharacterHealth() <= 0.0f)
			SetCurrentState(EFinalPlayState::EGameOver);
		else if (MyCharacter->GetCharacterMove() < UpperLimitOfMove)
			{MyCharacter->UpdateCharacterMove(DeltaTime * DecayRate * (MyCharacter->GetInitialMove()));/**MyCharacter->UpdateCharacterHealth(-50.0f);*/}

	}

	
}

float AFinalProjectGameMode::GetUpperLimitOfHealth() const
{
	return UpperLimitOfHealth;
}

float AFinalProjectGameMode::GetUpperLimitOfEnergy() const
{
	return UpperLimitOfEnergy;
}

float AFinalProjectGameMode::GetUpperLimitOfMove() const
{
	return UpperLimitOfMove;
}

float AFinalProjectGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

void AFinalProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	/** TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
	}
	*/

	// ステートをPlayingに
	SetCurrentState(EFinalPlayState::EPlaying);

	AFinalProjectCharacter* MyCharacter = Cast<AFinalProjectCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	// HPの上限を設定
		UpperLimitOfHealth = 3000.0f;
	// エネルギーの上限を設定
		UpperLimitOfEnergy = 3000.0f;
	// スタミナの上限を設定
		UpperLimitOfMove = 3000.0f;

	
	// クリアするための設定
		PowerToWin = 1.0f;

	// HUDの追加
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
			CurrentWidget->AddToViewport();
	}


}



EFinalPlayState AFinalProjectGameMode::GetCurrentState() const
{
	return CurrentState;
}


void AFinalProjectGameMode::SetCurrentState(EFinalPlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);
}


void AFinalProjectGameMode::HandleNewState(EFinalPlayState NewState)
{

	switch (NewState)
	{
		case EFinalPlayState::EPlaying:
		{
			
		}
		break;
		case EFinalPlayState::EWon:
		{
			// プレイヤーの入力をオフに
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
				PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		break;
		case EFinalPlayState::EGameOver:
		{
			

			// プレイヤーの入力をオフに
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
				PlayerController->SetCinematicMode(true, false, false, true, true);

			// キャラクターをラグドールに
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter)
			{
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}

		}
		break;
		case EFinalPlayState::EUnknown:
		{}
		break;
	}
}
