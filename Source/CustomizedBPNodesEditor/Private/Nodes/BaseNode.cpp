// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/BaseNode.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

FText UBaseNode::GetMenuCategory() const
{
	return NSLOCTEXT("CustomizedBPNodes", "NodeCategoryName", "Customized BP Nodes Example");
}

void UBaseNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* Action = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action)) {
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}

}
