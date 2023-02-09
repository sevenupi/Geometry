// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"

#include "Spatial/GeometrySet3.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHUB, All, All)
// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	DoActorSpawn3();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for(int32 i=0; i<10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f *i, 300.0f));
			ABaseGeometryActor* Geometry =  World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			if(Geometry)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Data.Amplitude = 4;
				Data.Frequency = 2;
				Geometry->SetGeometryData(Data);
			}
	
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for(int32 i=0; i<10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f *i, 700.0f));
			ABaseGeometryActor* Geometry =  World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			if(Geometry)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Data.Amplitude = 4;
				Data.Frequency = 2;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}
	void AGeometryHubActor::DoActorSpawn3()
	{
		UWorld* World = GetWorld();
		if(World)
		{
			for (const FGeometryPayLoad PayLoad : GeometryPayLoads)
			{
				ABaseGeometryActor* Geometry =  World->SpawnActorDeferred<ABaseGeometryActor>(PayLoad.GeometryClass,PayLoad.InititialTransform);
				if(Geometry)
				{
					Geometry->SetGeometryData(PayLoad.Data);
					Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
					Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
					Geometry->FinishSpawning(PayLoad.InititialTransform);
				}
			}
		}
	}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHUB, Warning, TEXT("Actor name: %s Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if(!Actor) return;
	UE_LOG(LogGeometryHUB, Error, TEXT("Timer Finished: %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry  = Cast<ABaseGeometryActor>(Actor);
	if(!Geometry) return;
	UE_LOG(LogGeometryHUB, Display, TEXT("Cast is succsed, amplitude %f"), Geometry->GetGeometryData().Amplitude)
	Geometry->Destroy();
	//Geometry->SetLifeSpan(2.0f);
}




