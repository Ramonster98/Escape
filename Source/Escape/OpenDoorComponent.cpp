// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

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

	StartRot= PortaAprire->GetComponentRotation(); // memorizzo la posizione iniziale in caso di successiva chiusura
	// ma anche per sapere quando ho raggiunto l'apertura desiderata

	//vado a catturare il pawn attuale del giocatore
	Chiave = GetWorld()->GetFirstPlayerController()->GetPawn();

	// ...
	
}

void UOpenDoorComponent::OpenDoor()
{
	auto ActualRot = PortaAprire->GetComponentRotation();

	auto DT = GetWorld()->GetDeltaSeconds();

//	if (ActualRot.Yaw < StartRot.Yaw + 90)
	if(OffsetDeg<OpenDeg)
	{
		ActualRot.Yaw += OpenDeg *DT;
		OffsetDeg += OpenDeg * DT;
		PortaAprire->SetWorldRotation(ActualRot);
	}
	
	//else bClose = false;

}

void UOpenDoorComponent::CloseDoor()
{
	auto ActualRot = PortaAprire->GetComponentRotation();

	auto DT = GetWorld()->GetDeltaSeconds();

	//if (ActualRot.Yaw > StartRot.Yaw)
	if (OffsetDeg > 0)
	{
		ActualRot.Yaw -= OpenDeg * DT;
		OffsetDeg -= OpenDeg * DT;
		PortaAprire->SetWorldRotation(ActualRot);
	}
	//else bClose = true;
}

void UOpenDoorComponent::ResetClose()
{
	bOpening = false;
}


// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (!Chiave || !Attivatore) return;

	if (Attivatore->IsOverlappingActor(Chiave))
	{
		bOpening = true;
		//if (bClose) OpenDoor();
	}
	else
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(CloseTimer)) 
		{
			GetWorld()->GetTimerManager().SetTimer(CloseTimer, this, &UOpenDoorComponent::ResetClose, DelayClose, false);
		}
	}

	if (bOpening)
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}

	// ...
}

