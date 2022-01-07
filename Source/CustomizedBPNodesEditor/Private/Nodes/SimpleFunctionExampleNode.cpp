// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SimpleFunctionExampleNode.h"

#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "CustomizedBPNodes/ExampleFunctionsLibrary.h"

void USimpleFunctionExampleNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL)
							 ? PropertyChangedEvent.Property->GetFName()
							 : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USimpleFunctionExampleNode, bUseExampleStringPin))
	{
		ReconstructNode();
		GetGraph()->NotifyGraphChanged();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void USimpleFunctionExampleNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    
	// Add exec pins
	check(Pins.Num() == 0);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Execute);

	if (bUseExampleStringPin)
	{
		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, {}, nullptr, TEXT("ExampleString"));
	}
    
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Then);
}

FText USimpleFunctionExampleNode::GetNodeTitle(ENodeTitleType::Type Title) const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleFunctionExampleNode.Title", "Simple Function Example Node");
}

FText USimpleFunctionExampleNode::GetTooltipText() const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleFunctionExampleNode.Tooltip", "Simple Function Example Node to show the example");
}

bool USimpleFunctionExampleNode::ShouldShowNodeProperties() const
{
	// if set to false, the details panel of the node will be empty
	return true;
}

void USimpleFunctionExampleNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	const FName FunctionName = GET_FUNCTION_NAME_CHECKED(UExampleFunctionsLibrary, SimpleFunctionForNode);
	UFunction* SimpleFunctionForNodeFunction = UExampleFunctionsLibrary::StaticClass()->FindFunctionByName(FunctionName);

	if (!SimpleFunctionForNodeFunction) {
		CompilerContext.MessageLog.Error(*NSLOCTEXT("CustomizedBPNodes", "InvalidFunctionName", "The function has not been found.").ToString(), this);
		return;
	}

	UK2Node_CallFunction* SimpleFunctionForNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	SimpleFunctionForNode->SetFromFunction(SimpleFunctionForNodeFunction);
	SimpleFunctionForNode->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(SimpleFunctionForNode, this);

	if (!bUseExampleStringPin)
	{
		SimpleFunctionForNode->FindPin(TEXT("ExampleString"))->DefaultValue = ExampleString;
	}
	else
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("ExampleString")), *SimpleFunctionForNode->FindPin(TEXT("ExampleString")));
	}

	//Exec pins
    UEdGraphPin* NodeExec = GetExecPin();
	UEdGraphPin* NodeThen = FindPin(UEdGraphSchema_K2::PN_Then);
	UEdGraphPin* SimpleFunctionForNodeExecPin = SimpleFunctionForNode->GetExecPin();
    UEdGraphPin* SimpleFunctionForNodePin = SimpleFunctionForNode->GetThenPin();

	// Move Exec and Then links to internal node
    CompilerContext.MovePinLinksToIntermediate(*NodeExec, *SimpleFunctionForNodeExecPin);
	CompilerContext.MovePinLinksToIntermediate(*NodeThen, *SimpleFunctionForNodePin);
	
	//After we are done we break all links to this node (not the internally created one)
	BreakAllNodeLinks();
}
