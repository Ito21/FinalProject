// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FinalProjectGameMode.generated.h"


// �Q�[���X�e�[�g
UENUM(BlueprintType)
enum class EFinalPlayState : uint8
{
	EPlaying
	, EGameOver
	, EWon
	, EUnknown
};

UCLASS(minimalapi)
class AFinalProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFinalProjectGameMode();

	virtual void Tick(float DeltaTime) override;

	// UpperLimitOfHealth
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetUpperLimitOfHealth() const;

	// UpperLimitOfEnergy
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetUpperLimitOfEnergy() const;

	// UpperLimitOfMove
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetUpperLimitOfMove() const;

	UFUNCTION(BlueprintPure, Category = "Power")
		float GetPowerToWin() const;


	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Power")
		EFinalPlayState GetCurrentState() const;

	void SetCurrentState(EFinalPlayState NewState);


protected:

	//�@�X�^�~�i()���񕜂��Ă����X�s�[�h
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float DecayRate;

	// HP�̏��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float UpperLimitOfHealth;

	// �G�l���M�[�̏��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float UpperLimitOfEnergy;

	// �X�^�~�i�̏��(PowerToWin�̕ς��)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float UpperLimitOfMove;

	// �������邽�߂ɕK�v�ȗ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float PowerToWin;

	// HUD��ʂɕK�v��Widget�N���X
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// HUD�̃C���X�^���X
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	// ���݃Q�[���̃X�e�[�g
	EFinalPlayState CurrentState;

	// TArray<class ASpawnVolume*> SpawnVolumeActors;

	// �X�e�[�g�ɉ����ď�����ς��邽�߂̃n���h��
	void HandleNewState(EFinalPlayState NewState);
};



