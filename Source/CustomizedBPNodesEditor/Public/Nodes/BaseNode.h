// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "BaseNode.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZEDBPNODESEDITOR_API UBaseNode : public UK2Node
{
	GENERATED_BODY()
public:
	//K2Node implementation
	virtual FText GetMenuCategory() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	//K2Node implementation

};
