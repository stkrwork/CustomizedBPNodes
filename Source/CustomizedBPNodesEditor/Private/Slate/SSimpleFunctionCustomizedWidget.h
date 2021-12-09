// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetNodes/SGraphNodeK2Base.h"

/**
 * 
 */
class CUSTOMIZEDBPNODESEDITOR_API SSimpleFunctionCustomizedWidget : public SGraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SSimpleFunctionCustomizedWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UK2Node* InNode);
    
    virtual void CreatePinWidgets() override;
protected:
	void OnExampleStringChanged(const FText& DialogText);
};
