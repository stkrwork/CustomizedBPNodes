// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BaseNode.h"
#include "SimpleFunctionCustomizedNode.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZEDBPNODESEDITOR_API USimpleFunctionCustomizedNode : public UBaseNode
{
	GENERATED_BODY()
public:
	//UEdGraphNode implementation
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	//virtual FLinearColor GetNodeTitleColor() const override;
	//virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	//UEdGraphNode implementation

	//K2Node implementation
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	//K2Node implementation

	UPROPERTY()
	FString ExampleString;
	
};
