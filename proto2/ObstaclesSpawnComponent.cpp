// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclesSpawnComponent.h"

#include "GISSLevelGenerationInformation.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

class UGISSLevelGenerationInformation;
// Sets default values for this component's properties
UObstaclesSpawnComponent::UObstaclesSpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ObstacleBound= CreateDefaultSubobject<UBoxComponent>(TEXT("Obstacle Bound"));
	ObstacleBound->SetupAttachment(this);
	
}
	// ...


// Called when the game starts
void UObstaclesSpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->GetGameInstance()->GetSubsystem<UGISSLevelGenerationInformation>()->TileNavigationTarget.IsEmpty())
		return;
	if (ToSpawn.Num()==0)
		return;
	
	for (int i =0; i<MaxNumberToSpawn; i++)
	{
		int indexToSpawn = FMath::RandRange(0, ToSpawn.Num() - 1);
		FVector location = UKismetMathLibrary::RandomPointInBoundingBox(ObstacleBound->GetComponentLocation(), ObstacleBound->GetScaledBoxExtent());
		GetWorld()->SpawnActor<AActor>(static_cast<UClass*>(ToSpawn[indexToSpawn]), location, GetOwner()->GetTransform().GetRotation().Rotator());
	}
	

	
}


// Called every frame
void UObstaclesSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

