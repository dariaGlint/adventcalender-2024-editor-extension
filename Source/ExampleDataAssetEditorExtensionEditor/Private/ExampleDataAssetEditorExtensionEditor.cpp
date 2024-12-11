#include "ExampleDataAssetEditorExtensionEditor.h"

#include "ExampleDataAssetEditor.h"

#define LOCTEXT_NAMESPACE "FExampleDataAssetEditorExtensionEditorModule"

void FExampleDataAssetEditorExtensionEditorModule::StartupModule()
{
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
}

void FExampleDataAssetEditorExtensionEditorModule::ShutdownModule()
{
	MenuExtensibilityManager.Reset();
	ToolBarExtensibilityManager.Reset();
}

void FExampleDataAssetEditorExtensionEditorModule::CreateExampleDataAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UExampleDataAsset* DataAsset)
{
	TSharedRef<ExampleDataAssetEditor> NewDataTableEditor(new ExampleDataAssetEditor());
	NewDataTableEditor->InitExampleAssetDataEditor(Mode, InitToolkitHost, DataAsset);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FExampleDataAssetEditorExtensionEditorModule, ExampleDataAssetEditorExtensionEditor)