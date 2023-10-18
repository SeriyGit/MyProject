// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCPP.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"
#include "ExplosionCPP.h"

// Sets default values
ABulletCPP::ABulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootScene->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootScene);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAssets
	(TEXT("StaticMesh'/Game/BasicMeshes/Sphere.Sphere'"));
	if (BodyAssets.Succeeded()) {
		Body->SetStaticMesh(BodyAssets.Object);
		Body->SetRelativeScale3D(FVector(0.45, 0.05, 0.05));
		Body->SetCollisionProfileName(TEXT("Trigger"));
		Body->OnComponentBeginOverlap.AddDynamic(this, &ABulletCPP::OnBodyBeginOverlap);
	}

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->InitialSpeed = 5000;
	ProjectileComponent->MaxSpeed = 5000;
	ProjectileComponent->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void ABulletCPP::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABulletCPP::SelfDestroy, 2, false);
	
}

// Called every frame
void ABulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletCPP::SelfDestroy() {
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AExplosionCPP>(GetActorLocation(),
		GetActorRotation(), SpawnInfo);
	Destroy();
}

void ABulletCPP::OnBodyBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AExplosionCPP>(GetActorLocation(),
		GetActorRotation(), SpawnInfo);
	Destroy();
}

