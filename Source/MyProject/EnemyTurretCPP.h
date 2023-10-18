// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "EnemyTurretCPP.generated.h"

UCLASS()
class MYPROJECT_API AEnemyTurretCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyTurretCPP();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* RootScene;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* RotateGunScene;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* FireScene;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* Body;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* Gun;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UParticleSystemComponent* FireEmitter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class AMyPlayerCPP* Player;

	UPROPERTY()
		bool bCanFire = true;
	UPROPERTY()
		float Health = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FHitResult Hit;
	FCollisionQueryParams CollParam;
	FActorSpawnParameters SpawnInfo;

	UFUNCTION()
		void Fire();

	UFUNCTION()
		void OnBodyBeginOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
