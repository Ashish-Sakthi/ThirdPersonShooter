// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputComponent.h"
#include "Rifle.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MovementContext, 0);
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	Gun = GetWorld()->SpawnActor<ARifle>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		const FRotator Rotation = GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y) * MoveAxisValue.X + FRotationMatrix(Rotation).GetUnitAxis(EAxis::X) * MoveAxisValue.Y;
		AddMovementInput(Direction);
	}
}

void AShooterCharacter::Turn(const FInputActionValue& Value)
{
	const FVector2D TurnAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(TurnAxisValue.X);
		AddControllerPitchInput(TurnAxisValue.Y);
	}
}

void AShooterCharacter::Fire()
{
	if (Gun)
	{
		Gun->PullTrigger();
	}
}

void AShooterCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AShooterCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}




// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedPlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedPlayerInput->BindAction(TurnAction,ETriggerEvent::Triggered,this,&AShooterCharacter::Turn);
		EnhancedPlayerInput->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);
		EnhancedPlayerInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedPlayerInput->BindAction(FireAction, ETriggerEvent::Started, this, &AShooterCharacter::Fire);
		EnhancedPlayerInput->BindAction(SprintAction, ETriggerEvent::Started, this, &AShooterCharacter::StartSprint);
		EnhancedPlayerInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AShooterCharacter::StopSprint);
	}

}

