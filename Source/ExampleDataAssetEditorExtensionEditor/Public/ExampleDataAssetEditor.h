#pragma once
#include "ExampleDataAsset.h"

class ExampleDataAssetEditor : public FAssetEditorToolkit
{
public:
	virtual void InitExampleAssetDataEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost,UExampleDataAsset* ExampleDataAsset);
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	void ExtendToolbar(TSharedPtr<FExtender> Extender);
	void FillToolbar(FToolBarBuilder& ToolbarBuilder);

	//以下4つは今回の主旨と外れるが実装しないとハングするため実装する
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	/**	Spawns the tab with the data table inside */
	TSharedRef<SDockTab> SpawnTab_DataTableDetails(const FSpawnTabArgs& Args);
	virtual void CreateAndRegisterDataTableDetailsTab(const TSharedRef<class FTabManager>& InTabManager);

	/** Property viewing widget */
	TSharedPtr<class IDetailsView> PropertyView;

	/**	The tab id for the data table details tab */
	static const FName DetailsTabId;
	
	UExampleDataAsset* GetEditableExampleDataAsset() const;

	bool CanAddItem() const;
	void AddItem_Execute();
	
};
