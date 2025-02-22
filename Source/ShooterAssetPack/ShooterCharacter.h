// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class ARifle;

UCLASS()
class SHOOTERASSETPACK_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttachGun();

	void SetupEnhancedIMC();

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MovementContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;


	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Fire();
	void StartSprint();
	void StopSprint();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARifle> GunClass;

	UPROPERTY()
	ARifle* Gun;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 350.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float Health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
