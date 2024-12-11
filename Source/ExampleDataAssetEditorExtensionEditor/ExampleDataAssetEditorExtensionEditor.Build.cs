using UnrealBuildTool;

public class ExampleDataAssetEditorExtensionEditor : ModuleRules
{
    public ExampleDataAssetEditorExtensionEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "ExampleDataAssetEditorExtension",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "AssetDefinition",
                "UnrealEd",
                "ExampleDataAssetEditorExtension"
            }
        );
    }
}