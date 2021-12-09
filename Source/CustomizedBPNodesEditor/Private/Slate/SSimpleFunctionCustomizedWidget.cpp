// Fill out your copyright notice in the Description page of Project Settings.


#include "SSimpleFunctionCustomizedWidget.h"

#include "SimpleEnumExampleCustomizedNode.h"
#include "SimpleFunctionCustomizedNode.h"
#include "SlateOptMacros.h"
#include "SNameComboBox.h"

#include "Kismet2/BlueprintEditorUtils.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSimpleFunctionCustomizedWidget::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;
    
	UpdateGraphNode();
}

void SSimpleFunctionCustomizedWidget::CreatePinWidgets()
{
	SGraphNodeK2Base::CreatePinWidgets();

	auto* SimpleFunctionCustomizedNode = Cast<USimpleFunctionCustomizedNode>(GraphNode);

	LeftNodeBox->AddSlot()
	.AutoHeight()
	.Padding(FMargin { 32, 4, 4, 4})
	[
		SNew(STextBlock)
			.Text(NSLOCTEXT("CustomizedBPNodes", "Label.ExampleString", "Example String Value"))
			.TextStyle(FEditorStyle::Get(), "Graph.Node.PinName")
			.IsEnabled(this, &SGraphNodeK2Base::IsNodeEditable)
	];

	LeftNodeBox->AddSlot()
	.AutoHeight()
	.Padding(FMargin { 36, 4, 4, 4 })
	[
		SNew(SEditableText)
		.Text(FText::FromString(SimpleFunctionCustomizedNode->ExampleString))
		.HintText(NSLOCTEXT("CustomizedBPNodes", "Label.DialogPlaceholderText", "Enter example string..."))
		.OnTextChanged(this, &SSimpleFunctionCustomizedWidget::OnExampleStringChanged)
		.IsEnabled(this, &SGraphNodeK2Base::IsNodeEditable)
	];

}

void SSimpleFunctionCustomizedWidget::OnExampleStringChanged(const FText& DialogText)
{
	auto* SimpleFunctionCustomizedNode = Cast<USimpleFunctionCustomizedNode>(GraphNode);

	SimpleFunctionCustomizedNode->Modify();
	SimpleFunctionCustomizedNode->ExampleString = DialogText.ToString();
	FBlueprintEditorUtils::MarkBlueprintAsModified(SimpleFunctionCustomizedNode->GetBlueprint());
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
