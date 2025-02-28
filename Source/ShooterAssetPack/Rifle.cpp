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

	FHitResult OutHit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(OutHit,ShotDirection);
	if (bSuccess)
	{
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.ImpactPoint, ShotDirection.Rotation());
		FPointDamageEvent DamageEvent(Damage, OutHit, ShotDirection, nullptr);
		AActor* HitActor = OutHit.GetActor();
		if (HitActor != nullptr)
		{
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
		}
	}
}

bool ARifle::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);//camera view for player and eye view for AI
	ShotDirection = -Rotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	FVector EndLocation = Location + Rotation.Vector() * MaxRange;
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, EndLocation, ECC_GameTraceChannel1, Params);
}

AController* ARifle::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) 
		return nullptr;
	
	return OwnerPawn->GetController();
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