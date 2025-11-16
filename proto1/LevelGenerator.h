// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS(Blueprintable)
class CRAFTNDEFEND_API ALevelGenerator : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALevelGenerator();
	UFUNCTION(CallInEditor)
		void ReloadGen();
	UFUNCTION(CallInEditor, BlueprintCallable)
		void GenerateLevel();
	UFUNCTION(CallInEditor, BlueprintCallable)
		void GenerateGoal();
	UFUNCTION(CallInEditor, BlueprintCallable)
	void SpawnObjects();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<class USceneComponent> BaseNextTileSpawn;//stocke le prochain points de spawn des tiles
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADoungeonGoal> EndGoalObject;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<class UStaticMeshComponent> TileMesh;
	UPROPERTY(EditAnywhere)
		uint32 NumberToSpawn;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<class USceneComponent> NextTilePoint;//stocke le prochain points de spawn des tiles
	UPROPERTY(VisibleAnywhere)
		class ATile* CurrentTile = nullptr;
	UPROPERTY(EditAnywhere)//tableau de BP contenant les Tiles que l'on veux spawn
		TArray<TSubclassOf<class ATile>> TileSpawnable;
	UPROPERTY(EditAnywhere)//tableau de BP contenant les Tiles que l'on veux spawn
		TSubclassOf<ALevelGenerator> SubLevelGen;
	UPROPERTY(EditAnywhere)//Tiles de fin que l'on veux
		TArray<TSubclassOf<class ATile>> EndTiles;

	UPROPERTY(EditAnywhere)//keep an eye on the spwanedTiles
		TArray<TObjectPtr<class ATile>> SpawnedTile;
	UPROPERTY(EditAnywhere)//keep an eye on the spawned End Tiles
		TArray<TObjectPtr<class ATile>> SpawnedEndTile;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)//move this in a subclass later
		TObjectPtr<ALevelGenerator> ParentGen;//use to give tiles refs to the first gen 
	UPROPERTY(EditAnywhere)
		bool IsSub;//define is has been spawned by another gen
	UPROPERTY(EditAnywhere)//listes des object que l'on peut Spawner
		TArray<TSubclassOf<AActor>> ObjectSpawnable;
	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<class ADoungeonGoal> SpawnedGoal;
	UPROPERTY(EditAnywhere)
		uint32 MaxNumberOfObjectToSpawnPerTile=1;
};
