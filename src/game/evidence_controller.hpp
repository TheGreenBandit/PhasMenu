#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct EvidenceControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		/*ListEvidence**/ void* EvidenceInLevel;
		void* RoomsToSpawnDNAEvidenceInside; // LevelRoom[]
		PhotonView* View; // PhotonView
		void* Bone; // DNAEvidence
		/*Transform* */void* GhostOrb;//add esp for me
		void* GhostOrbRenderer; // ParticleSystemRenderer
		/*LevelController* */void* LevelController;
		bool IsFreezingTemperatureGhost;
		float DotsCheckTimer;
		void* ActiveFingerprints; // List<Fingerprint>
		void* FoggyOrbColor; // Color
	};

	struct EvidenceController
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		EvidenceControllerFields Fields;
	};

	DECLARE_POINTER(EvidenceController_Start, void(*)(EvidenceController* evidenceController, MethodInfo* methodInfo), "Assembly-CSharp", "", "EvidenceController", "Start",
	                       0);
}
