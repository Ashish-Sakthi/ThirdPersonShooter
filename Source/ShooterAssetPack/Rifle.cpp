#include "Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARifle::ARifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void ARifle::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("Muzzle"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);//camera view for player and eye view for AI

	FHitResult OutHit;
	FVector EndLocation = Location + Rotation.Vector() * MaxRange;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OutHit, Location, EndLocation, ECC_GameTraceChannel1);
	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.ImpactPoint, Rotation);
		FPointDamageEvent DamageEvent(Damage, OutHit, ShotDirection, nullptr);
		AActor* HitActor = OutHit.GetActor();
		if (HitActor != nullptr)
		{
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}