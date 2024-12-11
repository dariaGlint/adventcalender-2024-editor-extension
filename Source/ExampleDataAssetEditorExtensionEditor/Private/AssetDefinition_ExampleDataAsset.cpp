// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetDefinition_ExampleDataAsset.h"

#include "ExampleDataAssetEditorExtensionEditor.h"

EAssetCommandResult UAssetDefinition_ExampleDataAsset::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	TArray<UExampleDataAsset*> ExampleAssetToOpen;

	for (UExampleDataAsset* ExampleDataAsset : OpenArgs.LoadObjects<UExampleDataAsset>())
	{
		ExampleAssetToOpen.Add(ExampleDataAsset);
	}
	
	FExampleDataAssetEditorExtensionEditorModule& ExampleDataAssetEditorExtensionEditorModule = FModuleManager::LoadModuleChecked<FExampleDataAssetEditorExtensionEditorModule>("ExampleMessageTalkEditor");
	for (UExampleDataAsset* ExampleAsset : ExampleAssetToOpen)
	{
		ExampleDataAssetEditorExtensionEditorModule.CreateExampleDataAssetEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, ExampleAsset);
	}

	return EAssetCommandResult::Handled;
}
