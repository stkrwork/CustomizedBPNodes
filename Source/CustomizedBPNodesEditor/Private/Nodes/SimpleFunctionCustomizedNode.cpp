// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SimpleFunctionCustomizedNode.h"

#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "CustomizedBPNodes/ExampleFunctionsLibrary.h"
#include "SSimpleFunctionCustomizedWidget.h"

void USimpleFunctionCustomizedNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    
	// Add exec pins
	check(Pins.Num() == 0);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Execute);    
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Then);
}

FText USimpleFunctionCustomizedNode::GetNodeTitle(ENodeTitleType::Type Title) const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleFunctionCustomizedNode.Title", "Simple Function Customized Node");
}

FText USimpleFunctionCustomizedNode::GetTooltipText() const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleFunctionCustomizedNode.Tooltip", "Simple Function Customized Node to show the example customized");
}

TSharedPtr<SGraphNode> USimpleFunctionCustomizedNode::CreateVisualWidget()
{
    return SNew(SSimpleFunctionCustomizedWidget, this);
}

void USimpleFunctionCustomizedNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	const FName FunctionName = GET_FUNCTION_NAME_CHECKED(UExampleFunctionsLibrary, SimpleFunctionForNodeCustomized);
	UFunction* SimpleFunctionForNodeCustomizedFunction = UExampleFunctionsLibrary::StaticClass()->FindFunctionByName(FunctionName);

	if (!SimpleFunctionForNodeCustomizedFunction) {
		CompilerContext.MessageLog.Error(*NSLOCTEXT("CustomizedBPNodes", "InvalidFunctionName", "The function has not been found.").ToString(), this);
		return;
	}

	UK2Node_CallFunction* SimpleFunctionForNodeCustomized = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	SimpleFunctionForNodeCustomized->SetFromFunction(SimpleFunctionForNodeCustomizedFunction);
	SimpleFunctionForNodeCustomized->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(SimpleFunctionForNodeCustomized, this);

	SimpleFunctionForNodeCustomized->FindPin(TEXT("ExampleString"))->DefaultValue = ExampleString;

	//Exec pins
	UEdGraphPin* NodeExec = GetExecPin();
	UEdGraphPin* NodeThen = FindPin(UEdGraphSchema_K2::PN_Then);
	UEdGraphPin* DisplayDialogTextFunctionNodeExecPin = SimpleFunctionForNodeCustomized->GetExecPin();
	UEdGraphPin* DisplayDialogTextFunctionNodePin = SimpleFunctionForNodeCustomized->GetThenPin();

	// Move Exec and Then links to internal node
	CompilerContext.MovePinLinksToIntermediate(*NodeExec, *DisplayDialogTextFunctionNodeExecPin);
	CompilerContext.MovePinLinksToIntermediate(*NodeThen, *DisplayDialogTextFunctionNodePin);
	
	//After we are done we break all links to this node (not the internally created one)
	BreakAllNodeLinks();
}
