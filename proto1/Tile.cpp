// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/BoxComponent.h"
#include"Kismet/KismetMathLibrary.h"
// Sets default values
ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("StartPoint"));
	NextTilePoints.Add(CreateDefaultSubobject<USceneComponent>(TEXT("NextTile")));
	NextTilePoints[0]->SetupAttachment(RootComponent); 
	OverlapCheckBox= CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapp Check"));
	OverlapCheckBox->SetupAttachment(RootComponent);
	//TrapPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TrappSpawnPoint"));
	//TrapPoint->SetupAttachment(RootComponent);
}
FVector ATile::GetObjectSpawnPoint()
{
	return UKismetMathLibrary::RandomPointInBoundingBox(OverlapCheckBox->GetComponentLocation(), OverlapCheckBox->GetScaledBoxExtent());
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::KillTile()
{
	Destroy();
}

