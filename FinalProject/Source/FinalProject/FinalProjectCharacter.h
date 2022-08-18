// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalProjectCharacter.generated.h"

UCLASS(config=Game)
class AFinalProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	//　後ろにカメラを配置(CameraBoom)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//　カメラをフォロー(FollowCamera )
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AFinalProjectCharacter();

	//　カメラの旋回速度 (度/秒単位)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	//　カメラの上下速度 (度/秒単位)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// HPデフォルト値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialHealth();

	// HP値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterHealth();

	// HP更新
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterHealth(float HealthChange);

	// エネルギーデフォルト値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialEnergy();

	// エネルギー値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterEnergy();

	// エネルギー更新
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterEnergy(float EnergyChange);

	// スタミナデフォルト値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialMove();

	// スタミナ値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterMove();

	// スタミナ更新
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterMove(float MoveChange);

	// アイテム合成用デフォルト値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialPower();

	// アイテム合成用値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterPower();

	// アイテム合成用更新
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterPower(float PowerChange);

	// クリア用デフォルト値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialWinPower();

	// クリア用値取得
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterWinPower();

	// クリア用更新
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterWinPower(float WinPowerChange);

	/**
	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
		void PowerChangeEffect();
		*/

protected:

	//　VR で HMD の向きをリセットします。
	void OnResetVR();

	//　前方/後方入力に呼び出されます 
	void MoveForward(float Value);

	//　side to side入力に呼び出されます
	void MoveRight(float Value);

	/**
	* 与えられた速度で回転するために入力を介して呼び出されます。
	* @param これは正規化されたレート、つまり1.0は希望のターンレートの100%を意味します。
	*/
	void TurnAtRate(float Rate);

	/**
	 * 特定のレートで上下を切り替えるために入力を介して呼び出されます。
	 * @param これは正規化されたレート、つまり1.0は希望のターンレートの100%を意味します。
	 */
	void LookUpAtRate(float Rate);

	// タッチ入力が開始されたときのHandler。
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	// タッチ入力が停止したときのHandler。
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn インターフェイス
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// APawn インターフェイスの終了

	// Jump禁止
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		bool NotJump;
	// 移動禁止
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		bool NotMove;

	// HPデフォルト値 (不変)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialHealth;

	// Energyデフォルト値 (不変)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialEnergy;

	// スタミナデフォルト値 (不変)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialMove;

	// キャラクターのスピード乗数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float SpeedFactor;

	// キャラクターのレベル0の時のスピード
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float BaseSpeed;

	// アイテム合成用デフォルト値 (不変)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialPower;
	// クリア用デフォルト値 (不変)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialWinPower;

private:

	// HPの値（リアルタイムに変化する方)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterHealth;

	// Energyの値（リアルタイムに変化する方)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterEnergy;

	// スタミナの値（リアルタイムに変化する方)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterMove;

	// アイテム合成用の値（リアルタイムに変化する方)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterPower;

	// クリア用の値（リアルタイムに変化する方)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterWinPower;

public:
	// CameraBoom サブオブジェクトを返します。
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// FollowCamera  サブオブジェクトを返します。
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

