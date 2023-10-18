// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionCPP.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AExplosionCPP::AExplosionCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ParticleSystemClass(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	Body->SetTemplate(ParticleSystemClass.Object);

}

// Called when the game starts or when spawned
void AExplosionCPP::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AExplosionCPP::SelfDestroy, 2, false);
}

// Called every frame
void AExplosionCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosionCPP::SelfDestroy() {
	Destroy();
}

