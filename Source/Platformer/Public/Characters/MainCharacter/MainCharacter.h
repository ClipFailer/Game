// Copyright 2026 Aleksey Nikolaychik. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "Interfaces/CharacterInterface/CharacterInferface.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

enum class EInteractionType : uint8;
class UInteractionComponent;
class UCameraComponent;
class UCharacterInputComponent;
class UInventoryComponent;

#define CharacterChannel ECC_GameTraceChannel3

/**
 * @brief Класс главного персонажа
 */
UCLASS()
class PLATFORMER_API AMainCharacter : public ACharacter, public ICharacterInferface
{
	GENERATED_BODY()

public:
	/**
	 * @brief Инициализирует персонажа
	 */
	AMainCharacter();

	/**
	 * @brief Подключает Enhanced Input к персонажу
	 * @param PlayerInputComponent Стандартная система ввода, получаемая автоматически
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	//===============================================================
	//			                METHODS
	//===============================================================

	//---------------------------------------------------------------
	//					Movement & Interaction
	//---------------------------------------------------------------

	/// @brief Выполняется в начале игры
	virtual void BeginPlay() override;

	/**
	 * @brief Обрабатывает действие по его типу.
	 *
	 * Отвечает соответствующим методом на входящий тип события и тип тригера
	 *
	 * @param TriggerEvent TriggerEvent, запустивший событие Action
	 * @param ActionType Тип события для обработки
	 *
	 * @see EInteractionType
	 */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HandleAction(ETriggerEvent TriggerEvent, EInteractionType ActionType);

	/**
	 * Выполняет взаимодействие с интерактивным эктором
	 */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnInteractActionStarted();

	/**
	 * Обрабатывает окончание второстепенного действия
	 */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnPrimaryActionStarted();

	/**
	 * Обрабатывает окончание второстепенного действия
	 */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnPrimaryActionCompleted();

	/**
	 * @brief Обрабатывает начало второстепенного действия
	 */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnSecondaryActionStarted();

	/**
	 * @brief Обрабатывает окончание второстепенного действия
	 */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnSecondaryActionCompleted();

	//===============================================================
	//			                PROPERTIES
	//===============================================================

	// Компонент камеры
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	// Компонент обработки ввода персонажа
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	UCharacterInputComponent* CharacterInputComponent;

	// Компонент, отвечающий за взаимодействие персонажа с миром
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	UInteractionComponent* InteractionComponent;

	// Компонент, отвечающий за взаимодействие персонажа с миром
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;
};