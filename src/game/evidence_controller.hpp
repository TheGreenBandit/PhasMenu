#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct EvidenceControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		/*ListEvidence**/ void* EvidenceInLevel;
		void* RoomsToSpawnDNAEvidenceInside; // LevelRoom[]
		void* View; // PhotonView
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
		void* Clazz;
		void* Monitor;
		EvidenceControllerFields Fields;
	};

	DECLARE_POINTER(EvidenceController_Start, void(*)(EvidenceController* evidenceController, method_info* methodInfo), "Assembly-CSharp", "", "EvidenceController", "Start",
	                       0);
}
