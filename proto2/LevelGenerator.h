// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTile.h"
#include "LevelGenerator.generated.h"

UCLASS()
class HEXTRAIL_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();
	
	// UFUNCTION(CallInEditor)
	// void ReloadGen();//reload the generation
	UFUNCTION(CallInEditor, BlueprintCallable)
	void GenerateLevel();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)//keep an eye on the spwanedTiles
	TArray<TObjectPtr<class ALevelTile>> SpawnedTile;
	
	//UFUNCTION(CallInEditor, BlueprintCallable)
	//void SpawnObjects(); //for powerup or other
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> BaseNextTileSpawn;//stocke le prochain points de spawn des tiles
	UPROPERTY(VisibleAnywhere)
		LevelDirection previousCorner= LevelDirection::Null;
	UPROPERTY()
		uint8 StraightCount=0;
	UPROPERTY(EditAnywhere)
		uint8 StraightBeforeCorner=3;
	UPROPERTY()
	bool CanSpawnCorner=false;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> TileMesh;
	UPROPERTY(EditAnywhere)
	uint32 NumberToSpawn;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> NextTilePoint;//stocke le prochain points de spawn des tiles
	UPROPERTY(VisibleAnywhere)
	class ALevelTile* CurrentTile = nullptr;
	UPROPERTY(EditAnywhere)//tableau de BP contenant les Tiles que l'on veux spawn
	TArray<TSubclassOf<class ALevelTile>> TileSpawnable;
	UPROPERTY(EditAnywhere)//tableau de BP contenant les Tiles que l'on veux spawn
	TSubclassOf<ALevelGenerator> SubLevelGen;//voir pour passer par des datatable
	UPROPERTY(EditAnywhere)//Tiles de fin que l'on veux
	TArray<TSubclassOf<class ALevelTile>> EndTiles;

	
	UPROPERTY(VisibleAnywhere)
		TArray<FVector> SpawnedPosition;
	UPROPERTY(EditAnywhere)//keep an eye on the spawned End Tiles
	TArray<TObjectPtr<class ALevelTile>> SpawnedEndTile;
protected:
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//======= In case of Mutilple spawn case like corridor in T or multiple ways
	UPROPERTY(VisibleAnywhere)//move this in a subclass later
		TObjectPtr<ALevelGenerator> ParentGen;//use to give tiles refs to the first gen
	UPROPERTY(EditAnywhere)
		bool IsSub;//define is has been spawned by another gen
	// UPROPERTY(EditAnywhere)//listes des object que l'on peut Spawner
	// TArray<TSubclassOf<AActor>> ObjectSpawnable;
	
	//UPROPERTY(EditAnywhere)
	//uint32 MaxNumberOfObjectToSpawnPerTile=1;
	private:
	UFUNCTION()
	void SpawnNextTile(int indexToSpawn);
};
