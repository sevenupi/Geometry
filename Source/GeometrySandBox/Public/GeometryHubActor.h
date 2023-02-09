// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGeometryActor.h"
#include "GameFramework/Actor.h"
#include "Spatial/GeometrySet3.h"
#include "GeometryHubActor.generated.h"


USTRUCT(BlueprintType)
struct FGeometryPayLoad
{
	GENERATED_USTRUCT_BODY() 

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	

	
	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InititialTransform;
};



UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

/*	UPROPERTY(EditAnywhere)
	UClass* Class;
	
	UPROPERTY(EditAnywhere)
	ABaseGeometryActor* GeometryObject;
*/
	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayLoad> GeometryPayLoads;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);

	void OnTimerFinished(AActor* Actor);
	
};
