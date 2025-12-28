#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct EvidenceFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		/*MediaValues* */void* MediaValues;
		bool Field1;
		bool ResetTakenPhotoOnEnable;
	};

	struct Evidence
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		EvidenceFields Fields;
	};

	// Evidence[]
	struct EvidenceArray
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		Il2CppArrayBounds* Bounds; // Il2CppArrayBounds
		il2cpp_array_size_t* MaxLength; // Il2CppArraySizeT
		Evidence* Vector[65535];
	};

	struct __declspec(align(8)) ListEvidenceFields
	{
		EvidenceArray* Items;
		int32_t Size;
		int32_t Version;
		Object* SyncRoot; // Object
	};

	// List<Evidence>
	struct ListEvidence
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		ListEvidenceFields Fields;
	};

	enum class EvidenceType : int32_t
	{
		EMFSpot,
		OuijaBoard,
		Fingerprint,
		Footstep,
		DNA,
		Ghost,
		DeadBody,
		DirtyWater,
		MusicBox,
		TarotCards,
		SummoningCircle,
		HauntedMirror,
		VoodooDoll,
		GhostWriting,
		UsedCrucifix,
		DotsGhost,
		MonkeyPaw,
		MoonAlter,
		None
	};
}
