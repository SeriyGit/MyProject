// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "ExplosionCPP.generated.h"

UCLASS()
class MYPROJECT_API AExplosionCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionCPP();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UParticleSystemComponent* Body;

	UFUNCTION()
		void SelfDestroy();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
