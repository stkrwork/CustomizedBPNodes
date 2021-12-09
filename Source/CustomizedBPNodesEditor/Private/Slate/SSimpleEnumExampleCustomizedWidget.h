// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetNodes/SGraphNodeK2Base.h"

/**
 * 
 */
class CUSTOMIZEDBPNODESEDITOR_API SSimpleEnumExampleCustomizedWidget : public SGraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SSimpleEnumExampleCustomizedWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UK2Node* InNode);
    
    virtual void CreatePinWidgets() override;
protected:
	void OnExampleEnumValueChanged(TSharedPtr<FName> Item, ESelectInfo::Type);
	
	TArray<TSharedPtr<FName>> ExampleEnumValues;
};
