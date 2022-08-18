// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FinalProjectGameMode.generated.h"


// ゲームステート
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

	//　スタミナ()が回復していくスピード
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float DecayRate;

	// HPの上限
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float UpperLimitOfHealth;

	// エネルギーの上限
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float UpperLimitOfEnergy;

	// スタミナの上限(PowerToWinの変わり)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float UpperLimitOfMove;

	// 勝利するために必要な量
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float PowerToWin;

	// HUD画面に必要なWidgetクラス
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// HUDのインスタンス
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	// 現在ゲームのステート
	EFinalPlayState CurrentState;

	// TArray<class ASpawnVolume*> SpawnVolumeActors;

	// ステートに応じて処理を変えるためのハンドラ
	void HandleNewState(EFinalPlayState NewState);
};



