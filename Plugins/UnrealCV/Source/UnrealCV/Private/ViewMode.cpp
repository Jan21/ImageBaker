#include "UnrealCVPrivate.h"
#include "ViewMode.h"
#include "BufferVisualizationData.h"

/**
FViewMode is a helper class to tweak render options. Important options are
	Tonemapper
	EyeAdaptation
	TemporalAA
	MotionBlur
	Lighting
	Bloom
	ColorGrading
	GammaCorrection
	DepthOfField
	LensFlare
	Vignette
*/


void BasicSetting(FEngineShowFlags& ShowFlags)
{
	ShowFlags = FEngineShowFlags(EShowFlagInitMode::ESFIM_All0);
	ShowFlags.SetRendering(true);
	ShowFlags.SetStaticMeshes(true);
}

void FViewMode::Lit(FEngineShowFlags& ShowFlags)
{
	BasicSetting(ShowFlags);
	ShowFlags = FEngineShowFlags(EShowFlagInitMode::ESFIM_Game);
	ApplyViewMode(VMI_Lit, true, ShowFlags);
	ShowFlags.SetMaterials(true);
	ShowFlags.SetLighting(true);
	ShowFlags.SetPostProcessing(true);
	// ToneMapper needs to be enabled, otherwise the screen will be very dark
	ShowFlags.SetTonemapper(true);
	// TemporalAA needs to be disabled, otherwise the previous frame might contaminate current frame.
	// Check: https://answers.unrealengine.com/questions/436060/low-quality-screenshot-after-setting-the-actor-pos.html for detail

	// ShowFlags.SetTemporalAA(true);
	ShowFlags.SetTemporalAA(false);
	ShowFlags.SetAntiAliasing(true);
	ShowFlags.SetEyeAdaptation(false); // Eye adaption is a slow temporal procedure, not useful for image capture
}

void FViewMode::BufferVisualization(FEngineShowFlags& ShowFlags)
{
	ApplyViewMode(EViewModeIndex::VMI_VisualizeBuffer, true, ShowFlags); // This did more than just SetVisualizeBuffer(true);
	// EngineShowFlagOverride()

	// From ShowFlags.cpp
	ShowFlags.SetPostProcessing(true);
	ShowFlags.SetMaterials(true);
	ShowFlags.SetVisualizeBuffer(true);

	// ToneMapper needs to be disabled
	ShowFlags.SetTonemapper(false);
	// TemporalAA needs to be disabled, or it will contaminate the following frame
	ShowFlags.SetTemporalAA(false);
}


/** ViewMode showing post process */
void FViewMode::PostProcess(FEngineShowFlags& ShowFlags)
{
	BasicSetting(ShowFlags);
	// These are minimal setting
	ShowFlags.SetPostProcessing(true);
	ShowFlags.SetPostProcessMaterial(true);
	// ShowFlags.SetVertexColors(true); // This option will change object material to vertex color material, which don't produce surface normal

	GVertexColorViewMode = EVertexColorViewMode::Color;
}

void FViewMode::Wireframe(FEngineShowFlags& ShowFlags)
{
	// ApplyViewMode(VMI_Wireframe, true, ShowFlags);
	ShowFlags.SetPostProcessing(true);
	ShowFlags.SetWireframe(true);
}


void FViewMode::VertexColor(FEngineShowFlags& ShowFlags)
{
	ApplyViewMode(VMI_Lit, true, ShowFlags);

	// From MeshPaintEdMode.cpp:2942
	ShowFlags.SetMaterials(false);
	ShowFlags.SetLighting(false);
	ShowFlags.SetBSPTriangles(true);
	ShowFlags.SetVertexColors(true);
	ShowFlags.SetPostProcessing(false);
	ShowFlags.SetHMDDistortion(false);
	ShowFlags.SetTonemapper(false); // This won't take effect here

	GVertexColorViewMode = EVertexColorViewMode::Color;
}

void FViewMode::Unlit(FEngineShowFlags& ShowFlags)
{
	ApplyViewMode(VMI_Unlit, true, ShowFlags);
	ShowFlags.SetMaterials(false);
	ShowFlags.SetVertexColors(false);
	ShowFlags.SetLightFunctions(false);
	ShowFlags.SetLighting(false);
	ShowFlags.SetAtmosphericFog(false);
}
