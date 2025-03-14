// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::isDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	FString PawnName = GetPawn()->GetName();
	UE_LOG(LogTemp,Warning,TEXT("Name : %s"),*PawnName);
	return true;
}
