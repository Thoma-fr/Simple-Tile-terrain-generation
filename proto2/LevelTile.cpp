// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTile.h"
#include "Components/BoxComponent.h"
// Sets default values
ALevelTile::ALevelTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("StartPoint"));
	NextTilePoints.Add(CreateDefaultSubobject<USceneComponent>(TEXT("NextTile")));
	NextTilePoints[0]->SetupAttachment(RootComponent);
	
	OverlapCheckBox= CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapp Check")); //to check if inside a map
	OverlapCheckBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

