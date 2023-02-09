// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);


UENUM(BlueprintType)
enum class EMovementType: uint8 
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData {
	GENERATED_USTRUCT_BODY() 
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Movement")
	float Amplitude = 50.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Movement")
	float Frequency = 2.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Movement")
	EMovementType MoveType = EMovementType::Static;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Design")
	FLinearColor Color = FLinearColor::Black;
	UPROPERTY(EditAnywhere, Category = "Design")
	float TimerRate = 3.0f;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	void SetGeometryData(const FGeometryData& Data){GeometryData = Data;}

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const{ return  GeometryData;}

	UPROPERTY(BlueprintAssignable);
	FOnColorChanged OnColorChanged;
	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category="Geometry Data")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WaeponsNum = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;
	UPROPERTY(EditInstanceOnly, Category ="Health")
	float Health = 34.754f;
	UPROPERTY(EditAnywhere, Category ="Health")
	bool IsDead = false;
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;
 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitialLocation;
	FTimerHandle TimerHandle;
	const int32 MaxTimeCount = 5;
	int32 TimeCount = 0;
	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();
	void SetCollor(const FLinearColor& Color);
	void HandleMovement();

	void OnTimerFired();
};
