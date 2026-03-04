// Copyright © 2026 Aleksey Nikolaychik. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/BaseObject/BaseObject.h"
#include "Interfaces/Interactable/Interactable.h"
#include "InteractableActor.generated.h"

#define InteractiveChannel ECC_GameTraceChannel1

class UWidgetComponent;
class UInteractivePopup;


/**
 * Базовый класс интерактивного эктора.
 *
 * Отвечает за экторы, расположенные на сцене, с которыми
 * может взаимодействовать персонаж
 */
UCLASS()
class PLATFORMER_API AInteractableActor : public ABaseObject, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableActor();

	//=====================================================
	//					PUBLIC INTERFACE
	//=====================================================

	UFUNCTION(BlueprintCallable)
	void SetShouldPopup(const bool bNewShouldPopup);

protected:
	//=====================================================
	//						METHODS
	//=====================================================

	virtual void BeginPlay() override;

	/// Реализация взаимодействия эктора
	virtual void Interact_Implementation(ACharacter* InteractedCharacter) override;

	/// Реализация подсветки эктора
	virtual void SetHighlighted_Implementation(const bool bIsHighlighted) override;

	//=====================================================
	//						PROPERTIES
	//=====================================================

	/**
	 * Отвечает за возможность взаимодействия с данным эктором
	 *
	 * - true = c эктором можно взаимодействовать
	 * - false = с эктором нельзя взаимодействовать
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bInteracting = true;

	/// Отвечает за симуляцию физики при появлении на сцене
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	bool bSimulatesPhysics = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bShouldHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bShouldPopup = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInstance* HighlightMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* InteractiveWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInteractivePopup> InteractiveWidgetClass;
};