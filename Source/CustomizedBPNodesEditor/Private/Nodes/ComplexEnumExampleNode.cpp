// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/ComplexEnumExampleNode.h"

#include "K2Node_CallFunction.h"
#include "K2Node_SwitchEnum.h"
#include "KismetCompiler.h"
#include "CustomizedBPNodes/ExampleFunctionsLibrary.h"

void UComplexEnumExampleNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    
	// Add exec pins
	check(Pins.Num() == 0);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, {}, nullptr, UEdGraphSchema_K2::PN_Execute);    

	static UEnum* ExampleEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("EExampleEnum"), /*ExactClass*/true);
	if (ExampleEnum)
	{
		PreloadObject(ExampleEnum);
		ExampleEnum->ConditionalPostLoad();

		EnumEntries.Empty();
		EnumFriendlyNames.Empty();

		for (int32 EnumIndex = 0; EnumIndex < ExampleEnum->NumEnums() - 1; ++EnumIndex)
		{
			bool const bShouldBeHidden = ExampleEnum->HasMetaData(TEXT("Hidden"), EnumIndex ) || ExampleEnum->HasMetaData(TEXT("Spacer"), EnumIndex );
			if (!bShouldBeHidden)
			{
				FString const EnumValueName = ExampleEnum->GetNameStringByIndex(EnumIndex);
				FText EnumFriendlyName = ExampleEnum->GetDisplayNameTextByIndex(EnumIndex);
				
				UEdGraphPin* NewPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, FName(*EnumValueName));
				NewPin->PinFriendlyName = EnumFriendlyName;
				
				EnumEntries.Add(FName(*EnumValueName));
				EnumFriendlyNames.Add( EnumFriendlyName );
			}
		}
	}
}

FText UComplexEnumExampleNode::GetNodeTitle(ENodeTitleType::Type Title) const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.ComplexEnumExampleNode.Title", "Complex Enum Example Node");
}

FText UComplexEnumExampleNode::GetTooltipText() const
{
    return NSLOCTEXT("CustomizedBPNodes", "Nodes.ComplexEnumExampleNode.Tooltip", "Complex Enum Example Node to show the example");
}

bool UComplexEnumExampleNode::ShouldShowNodeProperties() const
{
	// if set to false, the details panel of the node will be empty
	return true;
}

void UComplexEnumExampleNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const FName FunctionName = GET_FUNCTION_NAME_CHECKED(UExampleFunctionsLibrary, ComplexEnumFunctionForNode);
	UFunction* ComplexEnumFunctionForNodeFunction = UExampleFunctionsLibrary::StaticClass()->FindFunctionByName(FunctionName);

	if (!ComplexEnumFunctionForNodeFunction) {
		CompilerContext.MessageLog.Error(*NSLOCTEXT("CustomizedBPNodes", "InvalidFunctionName", "The function has not been found.").ToString(), this);
		return;
	}

	UK2Node_CallFunction* ComplexEnumFunctionForNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	ComplexEnumFunctionForNode->SetFromFunction(ComplexEnumFunctionForNodeFunction);
	ComplexEnumFunctionForNode->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ComplexEnumFunctionForNode, this);
	
	//Exec pins
	UEdGraphPin* NodeExec = GetExecPin();
	UEdGraphPin* ComplexEnumFunctionForNodeExecPin = ComplexEnumFunctionForNode->GetExecPin();
	UEdGraphPin* ComplexEnumFunctionForNodeThenPin = ComplexEnumFunctionForNode->GetThenPin();
	UEdGraphPin* ComplexEnumFunctionForNodeReturnPin = ComplexEnumFunctionForNode->GetReturnValuePin();
	
	// Move Exec and Then links to internal node
	CompilerContext.MovePinLinksToIntermediate(*NodeExec, *ComplexEnumFunctionForNodeExecPin);

	UK2Node_SwitchEnum* SwitchEnumNode = CompilerContext.SpawnIntermediateNode<UK2Node_SwitchEnum>(this, SourceGraph);

	static UEnum* ExampleEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("EExampleEnum"), /*ExactClass*/true);
	SwitchEnumNode->Enum = ExampleEnum;
	SwitchEnumNode->AllocateDefaultPins();

	ComplexEnumFunctionForNodeReturnPin->MakeLinkTo(SwitchEnumNode->GetSelectionPin());

	for (const FName EnumEntry: EnumEntries)
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(EnumEntry), *SwitchEnumNode->FindPin(EnumEntry));
	}
	
	ComplexEnumFunctionForNodeThenPin->MakeLinkTo(SwitchEnumNode->GetExecPin());

	
	//After we are done we break all links to this node (not the internally created one)
	BreakAllNodeLinks();
}
