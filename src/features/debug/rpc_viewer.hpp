#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"
#include "game/photon_view.hpp"

namespace menu
{
	struct rpc_viewer : toggle_feature
	{
		using toggle_feature::toggle_feature;
	public:
		std::string rpc_plain;
		std::vector<std::string> rpc_list_plain;
		bool test = false;

		//https://katyscode.wordpress.com/2021/01/14/il2cppinspector-tutorial-working-with-code-in-il2cpp-dll-injection-projects/#:~:text=Creating%20an%20object,%3C%3C%20std%3A%3Aendl%3B
		virtual void on_tick() override
		{
			if (!test)
				return;

			sdk::PhotonView* view = game::network->Fields.LocalPlayer->Fields.View;
			if (!view)
				return;

			sdk::Object__Array* args = (sdk::Object__Array*)g_il2cpp.il2cpp_array_new(get_type_from_class("mscorlib", "System", "Object")->klass, 1);

			bool value = true;
			auto bool_class = get_type_from_class("mscorlib", "System", "Boolean")->klass;
			//args->vector[0] = (sdk::Object*)g_il2cpp.il2cpp_value_box(bool_class, &value);
			sdk::Boolean__Boxed* boxed_bool = (sdk::Boolean__Boxed*)g_il2cpp.il2cpp_object_new(bool_class);
			boxed_bool->fields = false;


			//ghostcontroller - make ghost appear, hunt etc
			args->vector[0] = (sdk::Object*)boxed_bool;
			game::network->Fields.LocalPlayer->Fields.PlayerSanity->Fields.Insanity = 0;
			sdk::PhotonView_RPC_ptr(view, S_("NetworkedCrouch"), sdk::RpcTarget::All, args, nullptr);

			test = false;
		}

		virtual void on_overlay() override
		{
			if (!(std::find(rpc_list_plain.begin(), rpc_list_plain.end(), rpc_plain) != rpc_list_plain.end()))
				rpc_list_plain.push_back(rpc_plain);

			ImGui::Begin("RPC Viewer");
			if (ImGui::Button("Log Recieved To File"))
			{
				test = true;
			}
			if (ImGui::Button("Log Recieved To Log"))
			{
				for (auto rpc : rpc_list_plain)
					LOG(INFO) << rpc;
			}
			//add blocking rpcs
			ImGui::BeginChild("RPC_LIST");
			auto inverse_list = rpc_list_plain;

			for (std::string rpc : rpc_list_plain)
			{
				ImGui::TextWrapped(rpc.c_str());
			}
			ImGui::EndChild();
			ImGui::End();

		}
	};
	static inline rpc_viewer* g_rpc_viewer = new rpc_viewer("RPC Viewer", "Look at RPCs being sent and log them to a file.");
}

//logged rpcs
//[19:54 : 45][INFO][rpc_viewer.hpp:55]
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME: CompleteObjectiveRPC, PARAMS : Unsupported, TARGET : AllBuffered, FROM : View 1056 on Truck Corkboard(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : SyncWalk, PARAMS : Unsupported, TARGET : All, FROM : View 10026 on PCPlayer(Clone)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : GrabbedKey, PARAMS : Unsupported, TARGET : All, FROM : View 476 on MainKey(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PhysicsDelayNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 395 on Bone(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedActivelyViewingCCTVMonitor, PARAMS : Unsupported, TARGET : All, FROM : View 480 on CCTV Controller(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayOutOfBreathSound, PARAMS : Unsupported, TARGET : All, FROM : View 10026 on PCPlayer(Clone)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedPlayUnlockSound, PARAMS : Unsupported, TARGET : All, FROM : View 101 on DoorMain_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 101 on DoorMain_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 101 on DoorMain_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayOrStopAppearSourceSync, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUpdatePlayerSanity, PARAMS : Unsupported, TARGET : Others, FROM : View 10026 on PCPlayer(Clone)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayThrowingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 119 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 119 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 308 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 308 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Use, PARAMS : Unsupported, TARGET : All, FROM : View 110 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : SyncSprint, PARAMS : Unsupported, TARGET : All, FROM : View 10026 on PCPlayer(Clone)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : SpawnGhostWhisperNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 341 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 341 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 136 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 136 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 121 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 121 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedCrouch, PARAMS : Unsupported, TARGET : AllBuffered, FROM : View 10026 on PCPlayer(Clone)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Use, PARAMS : Unsupported, TARGET : All, FROM : View 273 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 25 on Locker_Door_Left(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 25 on Locker_Door_Left(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 25 on Locker_Door_Left(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Use, PARAMS : Unsupported, TARGET : All, FROM : View 177 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Use, PARAMS : Unsupported, TARGET : All, FROM : View 70 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 1049 on Fuse_box_Door(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 1049 on Fuse_box_Door(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 1049 on Fuse_box_Door(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Use, PARAMS : Unsupported, TARGET : All, FROM : View 279 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FlickerNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 110 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : SpawnEMFNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 308 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Use, PARAMS : Unsupported, TARGET : All, FROM : View 226 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 22 on Locker_Door_Right(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorSlamNoise, PARAMS : Unsupported, TARGET : All, FROM : View 22 on Locker_Door_Right(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 22 on Locker_Door_Right(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1390 on Toy item 8 Rocks(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : UseNetworked, PARAMS : Unsupported, TARGET : AllBuffered, FROM : View 1050 on House fuse box(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 78 on Clipper_Plier_Closed(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : Hunting, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedPlayLockSound, PARAMS : Unsupported, TARGET : All, FROM : View 101 on DoorMain_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : MakeGhostAppear, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : SpawnFootstepNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 497 on Ghost_Main(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 73 on Fork(6) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1373 on Toy item 11 Sticks.2 (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 366 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1443 on Toy item 3 Coal.5 (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 614 on ClosetsDoor01_L(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 366 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 178 on Handsaw(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 614 on ClosetsDoor01_L(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 545 on ClosetsDoor01_R(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 1039 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1405 on Toy item 5 Gingerbread(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 614 on ClosetsDoor01_L(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 545 on ClosetsDoor01_R(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 1039 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : DisableOrEnableColliderNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 101 on DoorMain_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : TurnOffNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 273 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : TurnOffNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 177 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : TurnOffNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 226 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : TurnOffNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 279 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : TurnOffNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 70 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : TurnOffNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 110 on LightSwitch(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrab, PARAMS : Unsupported, TARGET : All, FROM : View 32 on DrawerB(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedUngrabbedDoor, PARAMS : Unsupported, TARGET : All, FROM : View 1039 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 161 on Paint_Spray_Brown(2) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrab, PARAMS : Unsupported, TARGET : All, FROM : View 33 on DrawerA(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 308 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 137 on Caulk_01(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1387 on Toy item 8 Rocks.3 (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 212 on Paint_Spray_Brown(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1386 on Toy item 8 Rocks.4 (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 123 on Hammer(2) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1435 on Toy item 8 Rocks.5 (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorRattlingNoise, PARAMS : Unsupported, TARGET : All, FROM : View 341 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : CheckOcclusionPortal, PARAMS : Unsupported, TARGET : All, FROM : View 341 on DoorWide_joint(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 268 on Caulk_02(1) (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : FreezeRigidbodyNetworked, PARAMS : Unsupported, TARGET : All, FROM : View 1388 on Toy item 8 Rocks.2 (scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : NetworkedGrab, PARAMS : Unsupported, TARGET : All, FROM : View 184 on Drawer_C(scene)
//[19:54 : 45][INFO][rpc_viewer.hpp:55]       NAME : PlayDoorSlamNoise, PARAMS : Unsupported, TARGET : All, FROM : View 308 on DoorWide_joint(scene)
