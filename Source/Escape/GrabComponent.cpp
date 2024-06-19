// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerIC = GetOwner()->FindComponentByClass<UInputComponent>();

	if (OwnerIC)
	{
		UE_LOG(LogTemp, Error, TEXT("Trovato input"));

		OwnerIC->BindAction("Grab",IE_Pressed,this,&UGrabComponent::Afferra);

		OwnerIC->BindAction("Grab", IE_Released, this, &UGrabComponent::Rilascia);
	}


	// ...
	
}

void UGrabComponent::Afferra()
{
	UE_LOG(LogTemp, Error, TEXT("afferro"));

	AActor* Possessore = GetOwner();
	FVector Start = Possessore->GetActorLocation();
	//FVector End = Start + FVector(0,0,300);
	FVector End = Start + Possessore->GetActorForwardVector() * 300;
	//il draw debug line mi permette di vedere dove sto tracciando una linea tra due punti
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, -1, 0, 4.f);

	FHitResult Risultato;
	FCollisionQueryParams Extra;
	Extra.AddIgnoredActor(Possessore);

	auto trace = GetWorld()->LineTraceSingleByObjectType(Risultato, Start, End, ECC_PhysicsBody, Extra);

	if (trace)
	{
		Afferrato = Risultato.GetActor();
	}
}

void UGrabComponent::Rilascia()
{
	Afferrato = nullptr;
	UE_LOG(LogTemp, Error, TEXT("rilascio"));
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//prendo posizione del pawn a cui il componente è agganciato

	AActor* Possessore = GetOwner();
	FVector Start = Possessore->GetActorLocation();
	//FVector End = Start + FVector(0,0,300);
	FVector End = Start + Possessore->GetActorForwardVector() * 300;
	//il draw debug line mi permette di vedere dove sto tracciando una linea tra due punti
    DrawDebugLine(GetWorld(),Start,End,FColor::Blue,false,-1,0,4.f);
	
	if (Afferrato)
	{
		Afferrato->SetActorLocation(End);
	}

	/*if (trace)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ho trovato %s"), *Risultato.GetActor()->GetName());
	}
	*/

	// ...
}

