// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExampleEnum.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExampleFunctionsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZEDBPNODES_API UExampleFunctionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Customized BP Nodes Example")
	static void SimpleFunction(FString ExampleString);
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), Category="Customized BP Nodes Example")
	static void SimpleFunctionForNode(FString ExampleString);
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), Category="Customized BP Nodes Example")
	static void SimpleFunctionForNodeCustomized(FString ExampleString);

	UFUNCTION(BlueprintCallable, Category="Customized BP Nodes Example")
	static void SimpleEnumFunction(EExampleEnum ExampleEnum);
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), Category="Customized BP Nodes Example")
	static void SimpleEnumFunctionForNode(EExampleEnum ExampleEnum);
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), Category="Customized BP Nodes Example")
	static void SimpleEnumFunctionForNodeCustomized(EExampleEnum ExampleEnum);
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), Category="Customized BP Nodes Example")
	static EExampleEnum ComplexEnumFunctionForNode();
	
};
