#include "sdk.hpp"

namespace menu::sdk
{
	struct LevelController;

	struct GhostActivityFields
	{
		void* rangesensor; //RangeSensor*
		GhostAI* ghostAI;
		void* electronicsSensor; //RangeSensor*
		bool unk;
		LevelController* levelController;
		Vector3 unk2;
		Vector3 unk3;
		Vector3 unk4;
		Vector3 unk5;
		bool unk6;
	};

	struct GhostActivity
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		GhostActivityFields Fields;
	};

	DECLARE_POINTER(GhostActivity_InteractWithARandomDoor, bool*(*)(GhostActivity* this_, MethodInfo* mi), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomDoor", 0)
	DECLARE_POINTER(GhostActivity_InteractWithARandomProp, void*(*)(GhostActivity* this_, bool a1, MethodInfo* mi), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomDoor", 0)
	DECLARE_POINTER(GhostActivity_InteractWithARandomLightSwitch, bool*(*)(GhostActivity* this_, bool a1, MethodInfo* mi), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomDoor", 0)

}