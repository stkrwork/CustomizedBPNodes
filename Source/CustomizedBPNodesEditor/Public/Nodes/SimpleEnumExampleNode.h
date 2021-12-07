// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomizedBPNodes/ExampleEnum.h"
#include "Nodes/BaseNode.h"
#include "SimpleEnumExampleNode.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMIZEDBPNODESEDITOR_API USimpleEnumExampleNode : public UBaseNode
{
	GENERATED_BODY()
public:
	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UObject interface
	
	//UEdGraphNode implementation
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	//virtual FLinearColor GetNodeTitleColor() const override;
	//virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	//UEdGraphNode implementation

	//K2Node implementation
	virtual bool ShouldShowNodeProperties() const override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	//K2Node implementation

	protected:
	UPROPERTY(EditAnywhere)
	bool bUseEnumExamplePin;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bUseEnumExamplePin"))
	EExampleEnum EnumExample;
};
