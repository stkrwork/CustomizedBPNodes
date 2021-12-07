// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExampleEnum.generated.h"

UENUM(BlueprintType)
enum class EExampleEnum : uint8
{
	INVALID,
	OPTION_ONE,
	OPTION_TWO
};

namespace ExampleEnumUtils
{
	inline FString EnumToString(const TCHAR* Enum, int32 EnumValue)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
		if (!EnumPtr)
			return TEXT("INVALID_ENUM");

		return EnumPtr->GetNameByIndex(EnumValue).ToString();

	}
	inline FString EnumToDisplayString(const TCHAR* Enum, int32 EnumValue)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
		if (!EnumPtr)
			return TEXT("INVALID_ENUM");

		return EnumPtr->GetDisplayNameTextByIndex(EnumValue).ToString();

	}
}
