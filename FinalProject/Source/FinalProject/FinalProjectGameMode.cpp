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

	// �X�^�~�i���񕜂��Ă����X�s�[�h
	DecayRate = 0.1f;

	// Tick�֐���L���ɂ���
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

	// �X�e�[�g��Playing��
	SetCurrentState(EFinalPlayState::EPlaying);

	AFinalProjectCharacter* MyCharacter = Cast<AFinalProjectCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	// HP�̏����ݒ�
		UpperLimitOfHealth = 3000.0f;
	// �G�l���M�[�̏����ݒ�
		UpperLimitOfEnergy = 3000.0f;
	// �X�^�~�i�̏����ݒ�
		UpperLimitOfMove = 3000.0f;

	
	// �N���A���邽�߂̐ݒ�
		PowerToWin = 1.0f;

	// HUD�̒ǉ�
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
			// �v���C���[�̓��͂��I�t��
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
				PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		break;
		case EFinalPlayState::EGameOver:
		{
			

			// �v���C���[�̓��͂��I�t��
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
				PlayerController->SetCinematicMode(true, false, false, true, true);

			// �L�����N�^�[�����O�h�[����
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
