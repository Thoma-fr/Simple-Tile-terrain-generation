// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTile.generated.h"
UENUM(BlueprintType)
enum class LevelDirection : uint8 {
	Null=0,
	LeftCorner = 1 UMETA(DisplayName = "Turn LEft"),
	RightCorner = 2  UMETA(DisplayName = "Turn Right"),
	Straight =3     UMETA(DisplayName = "Straight"),
	
};
UCLASS()
class HEXTRAIL_API ALevelTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTile();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		LevelDirection Direction = LevelDirection::Straight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class USceneComponent>> NextTilePoints;//it's an array in case you need mutiple spawnpoint
	UPROPERTY(EditAnywhere)
	uint32 NumOfAdjacent = 1;// not used now
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> OverlapCheckBox;//not used for now
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	//UFUNCTION(BlueprintCallable)
	//void KillTile();//in case of overlap
};
