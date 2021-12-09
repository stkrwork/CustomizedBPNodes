// Fill out your copyright notice in the Description page of Project Settings.


#include "SSimpleEnumExampleCustomizedWidget.h"

#include "SimpleEnumExampleCustomizedNode.h"
#include "SlateOptMacros.h"
#include "SNameComboBox.h"

#include "Kismet2/BlueprintEditorUtils.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSimpleEnumExampleCustomizedWidget::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;
	
	for (uint8 i = 0; i < static_cast<uint8>(EExampleEnum::MAX); i++)
	{
		ExampleEnumValues.Add(MakeShared<FName>(*ExampleEnumUtils::EnumToDisplayString(TEXT("EExampleEnum"), i)));
	}
    
	UpdateGraphNode();
}

void SSimpleEnumExampleCustomizedWidget::CreatePinWidgets()
{
	SGraphNodeK2Base::CreatePinWidgets();

	auto* SimpleEnumExampleCustomizedNode = Cast<USimpleEnumExampleCustomizedNode>(GraphNode);

	LeftNodeBox->AddSlot()
	.AutoHeight()
	.Padding(FMargin { 32, 4, 4, 4})
	[
		SNew(STextBlock)
			.Text(NSLOCTEXT("CustomizedBPNodes", "Label.ExampleEnumName", "Example Enum Value"))
			.TextStyle(FEditorStyle::Get(), "Graph.Node.PinName")
			.IsEnabled(this, &SGraphNodeK2Base::IsNodeEditable)
	];

	LeftNodeBox->AddSlot()
		.AutoHeight()
		.Padding(FMargin { 36, 4, 4, 4 })
	[
		SNew(SNameComboBox)
		.ContentPadding(FMargin { 6.0f, 2.0f })
		.OptionsSource(&ExampleEnumValues)
		.InitiallySelectedItem(ExampleEnumValues[static_cast<uint8>(SimpleEnumExampleCustomizedNode->EnumExample)])
		.OnSelectionChanged(this, &SSimpleEnumExampleCustomizedWidget::OnExampleEnumValueChanged)
		.IsEnabled(this, &SGraphNodeK2Base::IsNodeEditable)
	];

}

void SSimpleEnumExampleCustomizedWidget::OnExampleEnumValueChanged(TSharedPtr<FName> Item, ESelectInfo::Type)
{
	auto* SimpleEnumExampleCustomizedNode = Cast<USimpleEnumExampleCustomizedNode>(GraphNode);

	SimpleEnumExampleCustomizedNode->Modify();
	const FString SanitizedEnumValueString = Item->ToString().Replace(TEXT(" "), TEXT("_"));
	SimpleEnumExampleCustomizedNode->EnumExample = ExampleEnumUtils::StringToEnumValue<EExampleEnum>(TEXT("EExampleEnum"), SanitizedEnumValueString);
	FBlueprintEditorUtils::MarkBlueprintAsModified(SimpleEnumExampleCustomizedNode->GetBlueprint());
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
