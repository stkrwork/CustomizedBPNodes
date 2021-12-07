// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/SimpleEnumExampleNode.h"

#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "CustomizedBPNodes/ExampleFunctionsLibrary.h"

void USimpleEnumExampleNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL)
							 ? PropertyChangedEvent.Property->GetFName()
							 : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USimpleEnumExampleNode, bUseEnumExamplePin))
	{
		ReconstructNode();
		GetGraph()->NotifyGraphChanged();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void USimpleEnumExampleNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    
	// Add exec pins
	check(Pins.Num() == 0);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Execute);

	if (bUseEnumExamplePin)
	{
		static UEnum* ExampleEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("EExampleEnum"), /*ExactClass*/true);
		// Internally enum classes of type uint8 are handled as bytes, therefore the pin is of type byte
		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Byte, {}, ExampleEnum, TEXT("EnumExample"));
	}
    
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Then);
}

FText USimpleEnumExampleNode::GetNodeTitle(ENodeTitleType::Type Title) const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleEnumExampleNode.Title", "Simple Enum Example Node");
}

FText USimpleEnumExampleNode::GetTooltipText() const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.SimpleEnumExampleNode.Tooltip", "Simple Enum Example Node to show the example");
}

bool USimpleEnumExampleNode::ShouldShowNodeProperties() const
{
	// if set to false, the details panel of the node will be empty
	return true;
}

void USimpleEnumExampleNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const FName FunctionName = GET_FUNCTION_NAME_CHECKED(UExampleFunctionsLibrary, SimpleEnumFunctionForNode);
	UFunction* SimpleEnumFunctionForNodeFunction = UExampleFunctionsLibrary::StaticClass()->FindFunctionByName(FunctionName);

	if (!SimpleEnumFunctionForNodeFunction) {
		CompilerContext.MessageLog.Error(*NSLOCTEXT("CustomizedBPNodes", "InvalidFunctionName", "The function has not been found.").ToString(), this);
		return;
	}

	UK2Node_CallFunction* SimpleEnumFunctionForNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	SimpleEnumFunctionForNode->SetFromFunction(SimpleEnumFunctionForNodeFunction);
	SimpleEnumFunctionForNode->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(SimpleEnumFunctionForNode, this);

	if (!bUseEnumExamplePin)
	{
		// The value is always the string version of the enum value
		SimpleEnumFunctionForNode->FindPin(TEXT("ExampleEnum"))->DefaultValue = *ExampleEnumUtils::EnumToString(TEXT("EExampleEnum"), static_cast<int32>(EnumExample));
	}
	else
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(TEXT("EnumExample")), *SimpleEnumFunctionForNode->FindPin(TEXT("ExampleEnum")));
	}

	//Exec pins
	UEdGraphPin* NodeExec = GetExecPin();
	UEdGraphPin* NodeThen = FindPin(UEdGraphSchema_K2::PN_Then);
	UEdGraphPin* DisplayDialogTextFunctionNodeExecPin = SimpleEnumFunctionForNode->GetExecPin();
	UEdGraphPin* DisplayDialogTextFunctionNodePin = SimpleEnumFunctionForNode->GetThenPin();

	// Move Exec and Then links to internal node
	CompilerContext.MovePinLinksToIntermediate(*NodeExec, *DisplayDialogTextFunctionNodeExecPin);
	CompilerContext.MovePinLinksToIntermediate(*NodeThen, *DisplayDialogTextFunctionNodePin);
	
	//After we are done we break all links to this node (not the internally created one)
	BreakAllNodeLinks();
}
