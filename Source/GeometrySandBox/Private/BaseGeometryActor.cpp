// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)
// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	//PrintTransform();
//PrintTypes();
//PrintStringTypes();
	SetCollor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);

}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor is dead %s"), *GetName());
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ABaseGeometryActor::PrintTypes()
{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d , kills num: %i"), WaeponsNum, KillsNum);

	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
	}

void ABaseGeometryActor::PrintStringTypes()
{	
	FString Name = "Jogn Connor";
	FString WeaponsNumStr = TEXT(" Weapons num - ") + FString::FromInt(WaeponsNum);
	FString HealthStr = TEXT("Health -  ") + FString::SanitizeFloat(Health, 2);
	FString IsDeadStr = TEXT("Is Dead - ") + FString(IsDead ? "True" : "False");
	FString HasWeaponStr = TEXT("Has Weapon - ") + FString(HasWeapon ? "True" : "False");
	FString Stats = FString::Printf(TEXT(" \n --------STATS--------- \n %s \n %s \n %s \n %s"),
											*WeaponsNumStr,  *HealthStr, *IsDeadStr, *HasWeaponStr); 
		GEngine ->AddOnScreenDebugMessage(-1, 3.0f , FColor::Red, Name );
		GEngine ->AddOnScreenDebugMessage(-1, 5.0f , FColor::Green, Stats, true, FVector2D(1.5f, 1.5f));
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor transform %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor location %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor rotator %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor scale %s"), *Scale.ToString());
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor humantransfrom %s"), *Transform.ToHumanReadableString());

}

void ABaseGeometryActor::SetCollor(const FLinearColor& Color)
{
	UMaterialInstanceDynamic* DynMaterial =    BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}


void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			float Time = GetWorld()->GetTimeSeconds();
			FVector CurrentLocationa = GetActorLocation();
			CurrentLocationa.Z = InitialLocation.Z * GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
			SetActorLocation(CurrentLocationa);

		}
		break;
	case EMovementType::Static:
		{

		}
		break;
	default:
		break;
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimeCount<=MaxTimeCount)
	{
		const FLinearColor NewColor= FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer count %i, Color to set up %s"),TimeCount, *NewColor.ToString());
		SetCollor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stoped"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}

}
