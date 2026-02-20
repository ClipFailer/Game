// Copyright 2026 Aleksey Nikolaychik. All rights reserved.


#include "Characters/MainCharacter/MainCharacter.h"

#include "Components/CharacterInputComponent/CharacterInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InteractionComponent/InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/Interactable/Interactable.h"
#include "Enums/InteractionType.h"
#include "Components/InventoryComponent/InventoryComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
	
	CharacterInputComponent = CreateDefaultSubobject<UCharacterInputComponent>(TEXT("InputComponent"));
	CharacterInputComponent->ActionDlg.AddDynamic(this, &ThisClass::HandleAction);
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = CharacterInputComponent->GetWalkSpeed();
}



void AMainCharacter::HandleAction(ETriggerEvent TriggerEvent, EInteractionType ActionType)
{
	switch (ActionType)
	{
	case EInteractionType::Interact:
		switch (TriggerEvent)
		{
			case ETriggerEvent::Started:
				OnInteractActionStarted();
				break;
		}
		break;
		
	case EInteractionType::Primary:
		switch (TriggerEvent)
		{
			case ETriggerEvent::Started:
			case ETriggerEvent::Triggered:
				OnPrimaryActionStarted();
				break;
			case ETriggerEvent::Completed:
			case ETriggerEvent::Canceled:
				OnPrimaryActionCompleted();
				break;
		}
		break;
		
	case EInteractionType::Secondary:
		switch (TriggerEvent)
		{
			case ETriggerEvent::Started:
			case ETriggerEvent::Triggered:
				OnSecondaryActionStarted();
				break;
			case ETriggerEvent::Completed:
			case ETriggerEvent::Canceled:
				OnSecondaryActionCompleted();
				break;
		}
		break;
	}
}

void AMainCharacter::OnInteractActionStarted()
{
	if (ABaseObject* obj = InteractionComponent->GetCurrentTracedActor())
	{
		if (InteractionComponent->IsActorPickupable(obj))
		{
			InventoryComponent->AddItem(obj->GetInfo());

			auto Items = InventoryComponent->GetAllItems();

			for (auto Item : Items) 
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					2.f,
					FColor::Blue,
					*Item.Name.ToString()
				);
			}
		}

		IInteractable::Execute_Interact(obj, this);
	}
}

void AMainCharacter::OnSecondaryActionStarted()
{
	InteractionComponent->GrabCurrentTracedActor();
}

void AMainCharacter::OnSecondaryActionCompleted()
{
	InteractionComponent->ReleaseCurrentGrabbedActor();
}

void AMainCharacter::OnPrimaryActionStarted()
{
	InteractionComponent->StartThrowChargeTimer();
}

void AMainCharacter::OnPrimaryActionCompleted()
{
	InteractionComponent->StopThrowChargeTimer();
	InteractionComponent->ThrowCurrentGrabbedActor();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	CharacterInputComponent->Init(this);
}

