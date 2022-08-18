// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalProjectCharacter.generated.h"

UCLASS(config=Game)
class AFinalProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	//�@���ɃJ������z�u(CameraBoom)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//�@�J�������t�H���[(FollowCamera )
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AFinalProjectCharacter();

	//�@�J�����̐��񑬓x (�x/�b�P��)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	//�@�J�����̏㉺���x (�x/�b�P��)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// HP�f�t�H���g�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialHealth();

	// HP�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterHealth();

	// HP�X�V
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterHealth(float HealthChange);

	// �G�l���M�[�f�t�H���g�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialEnergy();

	// �G�l���M�[�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterEnergy();

	// �G�l���M�[�X�V
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterEnergy(float EnergyChange);

	// �X�^�~�i�f�t�H���g�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialMove();

	// �X�^�~�i�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterMove();

	// �X�^�~�i�X�V
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterMove(float MoveChange);

	// �A�C�e�������p�f�t�H���g�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialPower();

	// �A�C�e�������p�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterPower();

	// �A�C�e�������p�X�V
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterPower(float PowerChange);

	// �N���A�p�f�t�H���g�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialWinPower();

	// �N���A�p�l�擾
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCharacterWinPower();

	// �N���A�p�X�V
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCharacterWinPower(float WinPowerChange);

	/**
	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
		void PowerChangeEffect();
		*/

protected:

	//�@VR �� HMD �̌��������Z�b�g���܂��B
	void OnResetVR();

	//�@�O��/������͂ɌĂяo����܂� 
	void MoveForward(float Value);

	//�@side to side���͂ɌĂяo����܂�
	void MoveRight(float Value);

	/**
	* �^����ꂽ���x�ŉ�]���邽�߂ɓ��͂���ČĂяo����܂��B
	* @param ����͐��K�����ꂽ���[�g�A�܂�1.0�͊�]�̃^�[�����[�g��100%���Ӗ����܂��B
	*/
	void TurnAtRate(float Rate);

	/**
	 * ����̃��[�g�ŏ㉺��؂�ւ��邽�߂ɓ��͂���ČĂяo����܂��B
	 * @param ����͐��K�����ꂽ���[�g�A�܂�1.0�͊�]�̃^�[�����[�g��100%���Ӗ����܂��B
	 */
	void LookUpAtRate(float Rate);

	// �^�b�`���͂��J�n���ꂽ�Ƃ���Handler�B
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	// �^�b�`���͂���~�����Ƃ���Handler�B
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn �C���^�[�t�F�C�X
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// APawn �C���^�[�t�F�C�X�̏I��

	// Jump�֎~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		bool NotJump;
	// �ړ��֎~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		bool NotMove;

	// HP�f�t�H���g�l (�s��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialHealth;

	// Energy�f�t�H���g�l (�s��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialEnergy;

	// �X�^�~�i�f�t�H���g�l (�s��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialMove;

	// �L�����N�^�[�̃X�s�[�h�搔
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float SpeedFactor;

	// �L�����N�^�[�̃��x��0�̎��̃X�s�[�h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float BaseSpeed;

	// �A�C�e�������p�f�t�H���g�l (�s��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialPower;
	// �N���A�p�f�t�H���g�l (�s��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialWinPower;

private:

	// HP�̒l�i���A���^�C���ɕω������)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterHealth;

	// Energy�̒l�i���A���^�C���ɕω������)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterEnergy;

	// �X�^�~�i�̒l�i���A���^�C���ɕω������)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterMove;

	// �A�C�e�������p�̒l�i���A���^�C���ɕω������)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterPower;

	// �N���A�p�̒l�i���A���^�C���ɕω������)
	UPROPERTY(VisibleAnywhere, Category = "Power")
		float CharacterWinPower;

public:
	// CameraBoom �T�u�I�u�W�F�N�g��Ԃ��܂��B
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// FollowCamera  �T�u�I�u�W�F�N�g��Ԃ��܂��B
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

