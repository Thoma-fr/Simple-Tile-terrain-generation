// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"

#include "GISSLevelGenerationInformation.h"
#include "LevelTile.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseNextTileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Point"));
}

void ALevelGenerator::GenerateLevel()
{
	NextTilePoint = BaseNextTileSpawn;
	uint32 TileArrayIndex;
	uint32 previousTileArrayIndex = 100;//cette valeur est pour forcer le fail de la première condition
	SpawnedPosition.Add(GetTransform().GetLocation());
	
	//si un des tableau est vide il ne passe pas par le for pour pas crash
	if (TileSpawnable.Num() > 0)
	{
		for (size_t i = 0; i < NumberToSpawn; i++)
		{
			TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
			

			while (Cast<ALevelTile>(TileSpawnable[TileArrayIndex]->GetDefaultObject())->Direction == previousCorner ||
				SpawnedPosition.Contains(Cast<ALevelTile>(TileSpawnable[0]->GetDefaultObject())->GetTransform().GetLocation()))//pour eviter de spawn la même tile a la suite
			{
				TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
			}
			if (SpawnedTile.Num()<2)
			{
				while (Cast<ALevelTile>(TileSpawnable[TileArrayIndex]->GetDefaultObject())->Direction != LevelDirection::Straight)
				{
					TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
				}
			}
			previousTileArrayIndex = TileArrayIndex;
			//on fais juste spawn une tile, creé en BP et renseigner dans le tableau en editeur
			
			SpawnNextTile(TileArrayIndex);
			SpawnedTile.Add(CurrentTile);
			// if (!IsSub)
			// 	SpawnedTile.Add(CurrentTile);
			// else
			// 	ParentGen->SpawnedTile.Add(CurrentTile);
			//on récupère le scene component qui sers de repère pour la position de la prochaine tile
			class ALevelTile* previousTile = CurrentTile;
			NextTilePoint = CurrentTile->NextTilePoints[0];
			
			// for (int j = 0; j <= previousTile->NextTilePoints.Num()-1; j++)
			// {
			// 	if (j == 0)
			// 	{
			// 		TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
			// 		while (previousTileArrayIndex == TileArrayIndex)//pour eviter de spawn la même tile a la suite
			// 		{
			// 			TileArrayIndex = FMath::RandRange(0, TileSpawnable.Num() - 1);
			//
			// 		}previousTileArrayIndex = TileArrayIndex;
			// 		CurrentTile = GetWorld()->SpawnActor<ALevelTile>(TileSpawnable[TileArrayIndex], NextTilePoint->GetComponentLocation(), NextTilePoint->GetComponentRotation());
			// 		CurrentTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			// 		if (!IsSub)
			// 			SpawnedTile.Add(CurrentTile);
			// 		else
			// 			ParentGen->SpawnedTile.Add(CurrentTile);
			// 	}
			// }
			//
			// NextTilePoint = CurrentTile->NextTilePoints[0];
		}
		//a la fin on fait spawn une tile déclenchant la fin du parcours 
		TileArrayIndex = FMath::RandRange(0, EndTiles.Num() - 1);
		NextTilePoint = CurrentTile->NextTilePoints[0];
		
		if (SubLevelGen)
		{
			GetWorld()->SpawnActor<AActor>(SubLevelGen, NextTilePoint->GetComponentLocation(), NextTilePoint->GetComponentRotation());

		}
	}
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

void ALevelGenerator::SpawnNextTile(int indexToSpawn)
{
	CurrentTile = GetWorld()->SpawnActor<ALevelTile>(TileSpawnable[indexToSpawn], NextTilePoint->GetComponentLocation(), NextTilePoint->GetComponentRotation());
	CurrentTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	if (SpawnedPosition.Contains(CurrentTile->GetTransform().GetLocation()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *FString::Printf(TEXT("Position déjà présente")));
	}
	if (CurrentTile->Direction == LevelDirection::RightCorner || CurrentTile->Direction == LevelDirection::LeftCorner)
	{
		previousCorner =CurrentTile->Direction;
	}
	SpawnedPosition.Add(CurrentTile->GetTransform().GetLocation());
	UKismetMathLibrary::RandomPointInBoundingBox(CurrentTile->OverlapCheckBox->GetComponentLocation(), CurrentTile->OverlapCheckBox->GetScaledBoxExtent());
	
	GetGameInstance()->GetSubsystem<UGISSLevelGenerationInformation>()->TileNavigationTarget.Add(CurrentTile->GetTransform().GetLocation());
}

