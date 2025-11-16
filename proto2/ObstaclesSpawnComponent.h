// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObstaclesSpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXTRAIL_API UObstaclesSpawnComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObstaclesSpawnComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<class UBoxComponent> ObstacleBound;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> ToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxNumberToSpawn;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
