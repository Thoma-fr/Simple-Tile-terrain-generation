// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GISSLevelGenerationInformation.generated.h"

/**
 * 
 */
UCLASS()
class HEXTRAIL_API UGISSLevelGenerationInformation : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	public:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		TArray<FVector> TileNavigationTarget;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		int CurrentTileIndex;
	
	UPROPERTY()
		int LevelIndex;
	UFUNCTION(BlueprintCallable)
	void Clearinstance();
};
