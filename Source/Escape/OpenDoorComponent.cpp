// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorComponent.h"

// Sets default values for this component's properties
UOpenDoorComponent::UOpenDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	//vado a catturare il pawn attuale del giocatore
	Chiave = GetWorld()->GetFirstPlayerController()->GetPawn();

	//OpenDoor();

	// ...
	
}

void UOpenDoorComponent::OpenDoor()
{
	auto Rotazione = PortaAprire->GetComponentRotation();
	Rotazione.Yaw += 90;
	PortaAprire->SetWorldRotation(Rotazione);
}


// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Chiave || !Attivatore) return;

	if (Attivatore->IsOverlappingActor(Chiave) && bClose)
	{
		OpenDoor();
		bClose = false;
	}

	// ...
}

