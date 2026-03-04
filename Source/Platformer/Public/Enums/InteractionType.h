#pragma once

/**
 * @brief Определяет доступные типы взаимодействия персонажа
 * 
 * Используется системой взаимодействия для определения поведения в ответ
 */
UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Interact			UMETA(DisplayName = "Interact Action"),
	Primary				UMETA(DisplayName = "Primary Action"),
	Secondary			UMETA(DisplayName = "Secondary Action"),
};
