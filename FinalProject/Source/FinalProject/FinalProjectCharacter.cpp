// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FinalProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AFinalProjectCharacter

AFinalProjectCharacter::AFinalProjectCharacter()
{
	// �����蔻��̃T�C�Y��ݒ肷��
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// ���͂̉�]����ݒ肷��
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// bool�̐ݒ�
	NotJump = false;
	NotMove = false;

	// HP�f�t�H���g�l�ݒ�
	InitialHealth = 3000.0f;
	CharacterHealth = InitialHealth;

	// �G�l���M�[�f�t�H���g�l�ݒ�
	InitialEnergy = 3000.0f;
	CharacterEnergy = InitialEnergy;

	// �X�^�~�i�f�t�H���g�l�ݒ�
	InitialMove = 3000.0f;
	CharacterMove = InitialMove;

	// �A�C�e�������p�f�t�H���g�l�ݒ�
	InitialPower = 0.0f;
	CharacterPower = InitialPower;

	// �N���A�p�f�t�H���g�l�ݒ�
	InitialWinPower = 0.0f;
	CharacterWinPower = InitialWinPower;

	// �L�����N�^�[�̃X�s�[�h
	SpeedFactor = 0.75f;
	BaseSpeed = 10.0f;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

float AFinalProjectCharacter::GetInitialHealth()
{
	return InitialHealth;
}

float AFinalProjectCharacter::GetCharacterHealth()
{
	return CharacterHealth;
}

void AFinalProjectCharacter::UpdateCharacterHealth(float HealthChange)
{
	// HP�l�̍X�V
	CharacterHealth = CharacterHealth + HealthChange;
}

float AFinalProjectCharacter::GetInitialEnergy()
{
	return InitialEnergy;
}

float AFinalProjectCharacter::GetCharacterEnergy()
{
	return CharacterEnergy;
}

void AFinalProjectCharacter::UpdateCharacterEnergy(float EnergyChange)
{
	// �G�l���M�[�l�̍X�V
	CharacterEnergy = CharacterEnergy + EnergyChange;
}


float AFinalProjectCharacter::GetInitialMove()
{
	return InitialMove;
}

float AFinalProjectCharacter::GetCharacterMove()
{
	return CharacterMove;
}

void AFinalProjectCharacter::UpdateCharacterMove(float MoveChange)
{
	// �X�^�~�i�l�̍X�V
	CharacterMove = CharacterMove + MoveChange;
	/**
	//�@�L�����̃X�s�[�h�̍X�V
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed + (SpeedFactor * CharacterPower);
	*/
}

float AFinalProjectCharacter::GetInitialPower()
{
	return InitialPower;
}

float AFinalProjectCharacter::GetCharacterPower()
{
	return CharacterPower;
}

void AFinalProjectCharacter::UpdateCharacterPower(float PowerChange)
{
	// �A�C�e�������pno�l�̍X�V
	CharacterPower = CharacterPower + PowerChange;
}

float AFinalProjectCharacter::GetInitialWinPower()
{
	return InitialWinPower;
}

float AFinalProjectCharacter::GetCharacterWinPower()
{
	return CharacterWinPower;
}

void AFinalProjectCharacter::UpdateCharacterWinPower(float WinPowerChange)
{
	// HP�l�̍X�V
	CharacterWinPower = CharacterWinPower + WinPowerChange;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFinalProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	/**

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	if (NotJump == false) {
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	}

	*/

	/**

	PlayerInputComponent->BindAxis("MoveForward", this, &AFinalProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFinalProjectCharacter::MoveRight);

	*/

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFinalProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFinalProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFinalProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFinalProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFinalProjectCharacter::OnResetVR);
}


void AFinalProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFinalProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AFinalProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AFinalProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFinalProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFinalProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFinalProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
