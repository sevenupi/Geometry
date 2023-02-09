// Fill out your copyright notice in the Description page of Project Settings.


#include "SanboxPlayerController.h"

#include "SandBoxPawn.h"
#include  "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandBoxPlayerController, All, All)
void ASanboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
if(InputComponent)
{
	InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASanboxPlayerController::ChangePawn);
}

}
void ASanboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandBoxPawn::StaticClass(), Pawns);
}


void ASanboxPlayerController::ChangePawn()
{
	if (Pawns.Num()<=1) return;

	ASandBoxPawn* CurrentPawn=Cast<ASandBoxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1 )% Pawns.Num();
	if(!CurrentPawn) return;
	
Possess(CurrentPawn);
	
	UE_LOG(LogSandBoxPlayerController, Warning, TEXT("Change player"));
}
