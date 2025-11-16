// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class CRAFTNDEFEND_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATile();

	UFUNCTION(BlueprintCallable)
	FVector GetObjectSpawnPoint();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void KillTile();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TObjectPtr<class USceneComponent>> NextTilePoints;
	UPROPERTY(EditAnywhere)
		uint32 NumOfAdjacent = 1;// not used now
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<class UBoxComponent> OverlapCheckBox;//not used for now
};
