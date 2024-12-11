#include "ExampleDataAssetEditor.h"

#include "ExampleDataAssetEditorExtensionEditor.h"
#define LOCTEXT_NAMESPACE "ExampleDataAssetEditor"

const FName ExampleDataAssetEditor::DetailsTabId("ExampleDataAssetToolKit_ExampleDataAssetDetails");

void ExampleDataAssetEditor::InitExampleAssetDataEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<class IToolkitHost>& InitToolkitHost, UExampleDataAsset* ExampleDataAsset)
{
	TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout( "ExampleDataAssetLayout2" )
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->AddTab(DetailsTabId, ETabState::OpenedTab)
			->SetForegroundTab(DetailsTabId)
		)
	);
	//ツールバーを作るかどうか。これがfalseだと作られないのでツールバーが要らない方はfalseにしてもいいが保存ボタンなども消えてしまうのでおすすめしない
	const bool bCreateDefaultToolbar = true;

	//todo これはfalseにしてもなにか表示が出たり消えたりしなかったので知ってる方がいれば教えてくれると助かります…
	const bool bCreateDefaultStandaloneMenu = true;

	InitAssetEditor( Mode, InitToolkitHost,  TEXT( "ExampleDataAssetEditorApp" ), StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, ExampleDataAsset );

	FExampleDataAssetEditorExtensionEditorModule& DataTableEditorModule = FModuleManager::LoadModuleChecked<FExampleDataAssetEditorExtensionEditorModule>( "ExampleDataAssetEditorExtensionEditor" );
	AddMenuExtender(DataTableEditorModule.GetMenuExtensibilityManager()->GetAllExtenders(GetToolkitCommands(), GetEditingObjects()));

	TSharedPtr<FExtender> ToolbarExtender = DataTableEditorModule.GetToolBarExtensibilityManager()->GetAllExtenders(GetToolkitCommands(), GetEditingObjects());
	ExtendToolbar(ToolbarExtender);

	AddToolbarExtender(ToolbarExtender);

	//これを呼ばないと表示されない
	RegenerateMenusAndToolbars();
}


void ExampleDataAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_ExampleDataAsset Editor", "Example DataAsset Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	CreateAndRegisterDataTableDetailsTab(InTabManager);
}

void ExampleDataAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}


void ExampleDataAssetEditor::ExtendToolbar(TSharedPtr<FExtender> Extender)
{
	Extender->AddToolBarExtension(
	"Asset",
	EExtensionHook::After,
	GetToolkitCommands(),
	FToolBarExtensionDelegate::CreateSP(this, &ExampleDataAssetEditor::FillToolbar)
);

}

void ExampleDataAssetEditor::FillToolbar(FToolBarBuilder& ToolbarBuilder)
{
		ToolbarBuilder.BeginSection("ExampleDataAssetCommands");
	{
		ToolbarBuilder.AddToolBarButton(
			FUIAction(
				FExecuteAction::CreateSP(this, &ExampleDataAssetEditor::AddItem_Execute),
				FCanExecuteAction::CreateSP(this, &ExampleDataAssetEditor::CanAddItem)),
			NAME_None,
			LOCTEXT("AddValueText", "Add Value One"),
			LOCTEXT("AddValueOneTooltip", "Add Value this ExampleDataAsset"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Import"));
	}
	ToolbarBuilder.EndSection();

}

FName ExampleDataAssetEditor::GetToolkitFName() const
{
	return FName("ExampleDataAssetToolKit");
}

FText ExampleDataAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "AppLabel", "ExampleDataAsset Toolkit" );
}

FString ExampleDataAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "ExampleDataAsset ").ToString();
}

FLinearColor ExampleDataAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor( 0.0f, 0.0f, 0.2f, 0.5f );
}

TSharedRef<SDockTab> ExampleDataAssetEditor::SpawnTab_DataTableDetails(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId().TabType == DetailsTabId);

	PropertyView->SetObject(GetEditableExampleDataAsset());

	return SNew(SDockTab)
		.Label(LOCTEXT("ExampleDataAssetTabDetails", "ExampleDataAsset Details"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(SBorder)
			.Padding(2)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				PropertyView.ToSharedRef()
			]
		];
}

void ExampleDataAssetEditor::CreateAndRegisterDataTableDetailsTab(const TSharedRef<class FTabManager>& InTabManager)
{
	FPropertyEditorModule & EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;
	PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

	InTabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &ExampleDataAssetEditor::SpawnTab_DataTableDetails))
		.SetDisplayName(LOCTEXT("ExampleDataAssetTab", "Example DataAsset Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

UExampleDataAsset* ExampleDataAssetEditor::GetEditableExampleDataAsset() const
{
	return Cast<UExampleDataAsset>(GetEditingObject());
}

bool ExampleDataAssetEditor::CanAddItem() const
{
	return true;
}

void ExampleDataAssetEditor::AddItem_Execute()
{
	UExampleDataAsset* ExampleDataAsset = GetEditableExampleDataAsset();
	ExampleDataAsset->Values.Add(1);
}


