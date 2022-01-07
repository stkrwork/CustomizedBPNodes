// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SimpleEnumExampleCustomizedNode.h"

#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "SSimpleEnumExampleCustomizedWidget.h"
#include "CustomizedBPNodes/ExampleFunctionsLibrary.h"

void USimpleEnumExampleCustomizedNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    
	// Add exec pins
	check(Pins.Num() == 0);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Execute);    
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Then);
}

FText USimpleEnumExampleCustomizedNode::GetNodeTitle(ENodeTitleType::Type Title) const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleEnumExampleCustomizedNode.Title", "Simple Enum Example Customized Node");
}

FText USimpleEnumExampleCustomizedNode::GetTooltipText() const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleEnumExampleNode.Tooltip", "Simple Enum Example Customized Node to show the example customized");
}

TSharedPtr<SGraphNode> USimpleEnumExampleCustomizedNode::CreateVisualWidget()
{
    return SNew(SSimpleEnumExampleCustomizedWidget, this);

}

void USimpleEnumExampleCustomizedNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const FName FunctionName = GET_FUNCTION_NAME_CHECKED(UExampleFunctionsLibrary, SimpleEnumFunctionForNodeCustomized);
	UFunction* SimpleEnumFunctionForNodeCustomizedFunction = UExampleFunctionsLibrary::StaticClass()->FindFunctionByName(FunctionName);

	if (!SimpleEnumFunctionForNodeCustomizedFunction) {
		CompilerContext.MessageLog.Error(*NSLOCTEXT("CustomizedBPNodes", "InvalidFunctionName", "The function has not been found.").ToString(), this);
		return;
	}

	UK2Node_CallFunction* SimpleEnumFunctionForNodeCustomized = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	SimpleEnumFunctionForNodeCustomized->SetFromFunction(SimpleEnumFunctionForNodeCustomizedFunction);
	SimpleEnumFunctionForNodeCustomized->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(SimpleEnumFunctionForNodeCustomized, this);


	// The value is always the string version of the enum value
	SimpleEnumFunctionForNodeCustomized->FindPin(TEXT("ExampleEnum"))->DefaultValue = *ExampleEnumUtils::EnumToString(TEXT("EExampleEnum"), static_cast<int32>(EnumExample));

	//Exec pins
	UEdGraphPin* NodeExec = GetExecPin();
	UEdGraphPin* NodeThen = FindPin(UEdGraphSchema_K2::PN_Then);
	UEdGraphPin* SimpleEnumFunctionForNodeCustomizedExecPin = SimpleEnumFunctionForNodeCustomized->GetExecPin();
	UEdGraphPin* SimpleEnumFunctionForNodeCustomizedNodePin = SimpleEnumFunctionForNodeCustomized->GetThenPin();

	// Move Exec and Then links to internal node
	CompilerContext.MovePinLinksToIntermediate(*NodeExec, *SimpleEnumFunctionForNodeCustomizedExecPin);
	CompilerContext.MovePinLinksToIntermediate(*NodeThen, *SimpleEnumFunctionForNodeCustomizedNodePin);
	
	//After we are done we break all links to this node (not the internally created one)
	BreakAllNodeLinks();
}
