// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoungeonGoal.generated.h"

UCLASS()
class CRAFTNDEFEND_API ADoungeonGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoungeonGoal();
	UFUNCTION(BlueprintCallable,CallInEditor)
		void ReloadDungeon();
protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		TObjectPtr<class ALevelGenerator> GeneratorRef;
	UPROPERTY(BlueprintReadWrite)
		bool HasBeenTaken;

};
