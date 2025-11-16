// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
#include "DoungeonGoal.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Tile.h"
// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseNextTileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Point"));

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	
	Super::BeginPlay();

	
	GenerateLevel();
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ALevelGenerator::GenerateLevel()
{
	NextTilePoint = BaseNextTileSpawn;
	uint32 TileArrayIndex;
	uint32 previousTileArrayIndex = 100;//cette valeur est pour forcer le fail de la première condition
	//si un des tableau est vide il ne passe pas par le for pour pas crash
	if (TileSpawnable.Num() > 0 /* && EndTiles.Num() > 0 */)
	{
		for (size_t i = 0; i < NumberToSpawn; i++)
		{

			TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
			while (previousTileArrayIndex == TileArrayIndex)//pour eviter de spawn la même tile a la suite
			{
				TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);

			}previousTileArrayIndex = TileArrayIndex;
			//on fais juste spawn une tile, creé en BP et renseigner dans le tableau en editeur
			CurrentTile = GetWorld()->SpawnActor<ATile>(TileSpawnable[TileArrayIndex], NextTilePoint->GetComponentLocation(), NextTilePoint->GetComponentRotation());
			CurrentTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			if (!IsSub)
				SpawnedTile.Add(CurrentTile);
			else
				ParentGen->SpawnedTile.Add(CurrentTile);
			//on récupère le scene component qui sers de repère pour la position de la prochaine tile
			class ATile* SubTile = nullptr;
			class ATile* previousTile = CurrentTile;
			NextTilePoint = CurrentTile->NextTilePoints[0];
			for (int j = 0; j <= previousTile->NextTilePoints.Num()-1; j++)
			{
				if (j == 0)
				{
					TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
					while (previousTileArrayIndex == TileArrayIndex)//pour eviter de spawn la même tile a la suite
					{
						TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);

					}previousTileArrayIndex = TileArrayIndex;
					CurrentTile = GetWorld()->SpawnActor<ATile>(TileSpawnable[TileArrayIndex], NextTilePoint->GetComponentLocation(), NextTilePoint->GetComponentRotation());
					CurrentTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					if (!IsSub)
						SpawnedTile.Add(CurrentTile);
					else
						ParentGen->SpawnedTile.Add(CurrentTile);
				}
				else
				{
					/*ALevelGenerator* subgen = GetWorld()->SpawnActorDeferred<ALevelGenerator>(SubLevelGen, previousTile->NextTilePoints[j]->GetComponentTransform());

					subgen->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					subgen->ParentGen = *this;
					subgen->FinishSpawning(previousTile->NextTilePoints[j]->GetComponentTransform(), true);
					NextTilePoint = previousTile->NextTilePoints[j];
					 
					previousTile->NextTilePoints[j]->GetChildComponent(0)->DestroyComponent();
					if (!IsSub)
						SpawnedTile.Add(CurrentTile);
					else
						ParentGen->SpawnedTile.Add(CurrentTile);*/
				}


			}

			NextTilePoint = CurrentTile->NextTilePoints[0];

			//définis si on fait spawn un element en plus sur la tile ou non
			//can be use to add rendom or spawn objects
			/*if (FMath::RandRange(0, 10) > 5)
			{
				if(CurrentTile->TrapPoint!=nullptr&& TrapSpawnable.Num()>0)
					GetWorld()->SpawnActor<AActor>(TrapSpawnable[0], CurrentTile->TrapPoint->GetComponentToWorld().GetLocation(), CurrentTile->TrapPoint->GetComponentRotation());
			}*/
			/*switch (RandomNumber)
			{
			case 1: GetWorld()->SpawnActor<AActor>(ObjectSpawnable[FMath::RandRange(0, ObjectSpawnable.Num() - 1)], CurrentTile->ObjectSpawnPos->GetComponentLocation(), CurrentTile->ObjectSpawnPos->GetComponentRotation());
				break;
			}*/

		}
		//a la fin on fait spawn une tile déclenchant la fin du parcours 
		TileArrayIndex = FMath::RandRange(0, EndTiles.Num() - 1);
		if (EndTiles.Num() > 0)
		{
			CurrentTile = GetWorld()->SpawnActor<ATile>(EndTiles[TileArrayIndex], NextTilePoint->GetComponentLocation(), NextTilePoint->GetComponentRotation());
			if (!IsSub)
				SpawnedEndTile.Add(CurrentTile);
			else
				ParentGen->SpawnedEndTile.Add(CurrentTile);
		}
	}
}
void ALevelGenerator::GenerateGoal()
{
	uint32 IndexToSpawnGoal = FMath::RandRange(0, SpawnedEndTile.Num() - 1);
	NextTilePoint = SpawnedEndTile[IndexToSpawnGoal]->NextTilePoints[0];
	//AActor newEnd;
	if (EndGoalObject == nullptr)
		return;
	SpawnedGoal=GetWorld()->SpawnActorDeferred<ADoungeonGoal>(EndGoalObject, NextTilePoint->GetComponentTransform());
	SpawnedGoal->GeneratorRef = this;
	SpawnedGoal->FinishSpawning(NextTilePoint->GetComponentTransform(), true);
}
void ALevelGenerator::SpawnObjects()
{
	if (ObjectSpawnable.Num() < 0)
		return;

	for (size_t i = 0; i < SpawnedTile.Num(); i++)
	{
		uint32 numberToSpawn =FMath::RandRange(0, MaxNumberOfObjectToSpawnPerTile);
		for (size_t j = 0; j < MaxNumberOfObjectToSpawnPerTile; j++)
		{
			GetWorld()->SpawnActor<AActor>(ObjectSpawnable[FMath::RandRange(0, (ObjectSpawnable.Num() - 1))], SpawnedTile[i]->GetObjectSpawnPoint(), NextTilePoint->GetComponentRotation());

		}
	}
}
void ALevelGenerator::ReloadGen()//Regenerate all dungeon, and destroyall old tile
{
	if (SpawnedTile.Num() == 0)
	{
		return;
	}
	for (size_t i = 0; i < SpawnedTile.Num(); i++)
	{
		SpawnedTile[i]->KillTile();
	}
	for (size_t i = 0; i < SpawnedEndTile.Num(); i++)
	{
		SpawnedEndTile[i]->KillTile();
	}
	GenerateLevel();
}

