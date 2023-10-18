// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AmmoKit.generated.h"

UCLASS()
class MYPROJECT_API AAmmoKit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoKit();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* RootScene;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* Body;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
