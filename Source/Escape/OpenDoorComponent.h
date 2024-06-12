// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorComponent();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="OpenDoor")
	UStaticMeshComponent* PortaAprire;

	UPROPERTY(EditAnywhere, Category = "OpenDoor")
	AActor* Attivatore; //memorizzerò il trigger volume

	UPROPERTY(EditAnywhere, Category = "OpenDoor")
	AActor* Chiave; //memorizzerò l'oggetto che entrato nel volume apre la porta

	bool bClose = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
