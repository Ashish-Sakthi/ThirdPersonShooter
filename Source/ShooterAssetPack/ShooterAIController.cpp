// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	
	bool bCanSeePlayer = LineOfSightTo(PlayerPawn);

	if (bCanSeePlayer)
	{
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, AcceptanceRadius);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}*/
}
