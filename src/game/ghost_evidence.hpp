#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	enum class GhostEvidence : int32_t
	{
		None,
		EMF,
		SpiritBox,
		Ultraviolet,
		GhostOrb,
		GhostWritingBook,
		Temperature,
		DotsProjector
	};

	// GhostEvidence[]
	struct GhostEvidenceArray
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		Il2CppArrayBounds* Bounds; // Il2CppArrayBounds
		Il2CppArraySize* MaxLength; // Il2CppArraySizeT
		GhostEvidence Vector[65535];
	};

	struct __declspec(align(8)) ListGhostEvidenceFields
	{
		GhostEvidenceArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	// List<GhostEvidence>
	struct ListGhostEvidence
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		ListGhostEvidenceFields Fields;
	};
}
