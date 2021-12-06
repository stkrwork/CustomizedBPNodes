// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleFunctionsLibrary.h"

void UExampleFunctionsLibrary::SimpleFunction(FString ExampleString)
{
	UE_LOG(LogTemp, Display, TEXT("UExampleFunctionsLibrary::SimpleFunction: Example String passed: %s"), *ExampleString);
}

void UExampleFunctionsLibrary::SimpleFunctionForNode(FString ExampleString)
{
	UE_LOG(LogTemp, Display, TEXT("UExampleFunctionsLibrary::SimpleFunctionForNode: Example String passed: %s"), *ExampleString);
}

void UExampleFunctionsLibrary::SimpleFunctionForNodeCustomized(FString ExampleString)
{
	UE_LOG(LogTemp, Display, TEXT("UExampleFunctionsLibrary::SimpleFunctionForNodeCustomized: Example String passed: %s"), *ExampleString);
}

void UExampleFunctionsLibrary::SimpleEnumFunction(EExampleEnum ExampleEnum)
{
	UE_LOG(LogTemp, Display, TEXT("UExampleFunctionsLibrary::SimpleEnumFunction: Example Enum passed: %s"), *ExampleEnumUtils::EnumToString(TEXT("EExampleEnum"), static_cast<int32>(ExampleEnum)));
}

void UExampleFunctionsLibrary::SimpleEnumFunctionForNode(EExampleEnum ExampleEnum)
{
	UE_LOG(LogTemp, Display, TEXT("UExampleFunctionsLibrary::SimpleEnumFunctionForNode: Example Enum passed: %s"), *ExampleEnumUtils::EnumToString(TEXT("EExampleEnum"), static_cast<int32>(ExampleEnum)));
}

void UExampleFunctionsLibrary::SimpleEnumFunctionForNodeCustomized(EExampleEnum ExampleEnum)
{
	UE_LOG(LogTemp, Display, TEXT("UExampleFunctionsLibrary::SimpleEnumFunctionForNodeCustomized: Example Enum passed: %s"), *ExampleEnumUtils::EnumToString(TEXT("EExampleEnum"), static_cast<int32>(ExampleEnum)));
}
