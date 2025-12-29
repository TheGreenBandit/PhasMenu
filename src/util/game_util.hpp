#pragma once

#include "common.hpp"
#include "gui_util.hpp"

#define S(s)                                           \
    ([&]() -> std::string {                            \
        if (!(s)) return {};                           \
        const int32_t _len = (s)->Fields.StringLength; \
        const auto _first = &(s)->Fields.FirstChar;\
        std::wstring _wide(_first, _first + _len);     \
        return std::string(_wide.begin(), _wide.end());\
    })()

#define S_(s)\
    ([&]() -> sdk::String* {                            \
        return sdk::Marshal_PtrToStringAnsi_ptr((void*)s, nullptr);\
    })()

namespace menu
{
	class game_util
	{
	public:
		std::vector<sdk::NetworkPlayerSpot*> playerlist;
		sdk::Player* selected_player = nullptr;
		template<typename T>
		sdk::PhotonView* get_photon_view(T* base)
		{
			reinterpret_cast<sdk::PhotonView*>(sdk::GameObject_GetComponentByName_ptr(sdk::Component_Get_GameObject_ptr(reinterpret_cast<sdk::Component*>(base), nullptr), S_("PhotonView"), nullptr));
		}

		//add args!
		template <typename... args>
		void send_rpc(sdk::PhotonView* view, std::string name, sdk::RpcTarget target, args ...)//add param support
		{
			//add param support todo 

			//sdk::PhotonView_RPC_ptr(view, S_(name.c_str()), target, ..., nullptr);
		}

		sdk::Network* get_network()
		{
			if (game::network) return game::network;

			sdk::Network* network = sdk::Network_Get_Network_ptr(nullptr);
			if (network == nullptr)
				return nullptr;

			game::network = network;
			return network;
		}

		bool is_game_started()
		{
			return game::network->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController != nullptr;
		}

		ImVec2 world_to_screen(const sdk::Vector3 vWorldPosition) 
		{
			static ImVec2 ret = ImVec2(-1, -1);
			ImVec2 screen = g_gui_util->get_screen_size();
			auto camera = get_network()->Fields.LocalPlayer->Fields.Camera;
			if (camera == nullptr) 
				return ImVec2(-1, -1);
			sdk::Transform* cameraTransform = sdk::Component_Get_Transform_ptr(reinterpret_cast<sdk::Component*>(camera), nullptr);
			sdk::Vector3 cameraPos = sdk::Transform_Get_Position_ptr(cameraTransform, nullptr);
			sdk::Vector3 cameraForward = sdk::Transform_Get_Forward_ptr(cameraTransform, nullptr);
			sdk::Vector3 direction;
			direction.X = vWorldPosition.X - cameraPos.X;
			direction.Y = vWorldPosition.Y - cameraPos.Y;
			direction.Z = vWorldPosition.Z - cameraPos.Z;
			const float dot = direction.X * cameraForward.X + direction.Y * cameraForward.Y + direction.Z * cameraForward.Z;
			if (dot <= 0) 
				return ImVec2(-1, -1);
			sdk::Matrix4x4 viewMatrix = sdk::Camera_Get_WorldToCameraMatrix_ptr(camera, nullptr); 
			sdk::Matrix4x4 projMatrix = sdk::Camera_Get_ProjectionMatrix_ptr(camera, nullptr); 
			float camX = viewMatrix.m00 * vWorldPosition.X + viewMatrix.m01 * vWorldPosition.Y + viewMatrix.m02 * vWorldPosition.Z + viewMatrix.m03; float camY = viewMatrix.m10 * vWorldPosition.X + viewMatrix.m11 * vWorldPosition.Y + viewMatrix.m12 * vWorldPosition.Z + viewMatrix.m13; 
			float camZ = viewMatrix.m20 * vWorldPosition.X + viewMatrix.m21 * vWorldPosition.Y + viewMatrix.m22 * vWorldPosition.Z + viewMatrix.m23; float camW = viewMatrix.m30 * vWorldPosition.X + viewMatrix.m31 * vWorldPosition.Y + viewMatrix.m32 * vWorldPosition.Z + viewMatrix.m33; 
			// Then apply the projection matrix to convert from camera to clip space 
			float clipX = projMatrix.m00 * camX + projMatrix.m01 * camY + projMatrix.m02 * camZ + projMatrix.m03 * camW; 
			float clipY = projMatrix.m10 * camX + projMatrix.m11 * camY + projMatrix.m12 * camZ + projMatrix.m13 * camW;
			float clipZ = projMatrix.m20 * camX + projMatrix.m21 * camY + projMatrix.m22 * camZ + projMatrix.m23 * camW; 
			float clipW = projMatrix.m30 * camX + projMatrix.m31 * camY + projMatrix.m32 * camZ + projMatrix.m33 * camW; 
			// Check if the point is behind the camera after projection 
			if (clipW < 0.1f)
				return ImVec2(-1, -1);
			// Perspective divide to get normalized device coordinates 
			float ndcX = clipX / clipW; 
			float ndcY = clipY / clipW; 
			float ndcZ = clipZ / clipW; 

			ret.x = (ndcX * 0.5f + 0.5f) * screen.x; ret.y = (1.0f - (ndcY * 0.5f + 0.5f)) * screen.y;

			return ret; 
		}

		std::string get_ghost_state(sdk::GhostState gs)
		{
			std::string state = "Unknown";

			switch (gs)
			{
				case sdk::GhostState::Idle:
					state = "Idle";
					break;
				case sdk::GhostState::Wander:
					state = "Wandering";
					break;
				case sdk::GhostState::Hunting:
					state = "Hunting";
					break;
				case sdk::GhostState::FavoriteRoom:
					state = "FavoriteRoom";
					break;
				case sdk::GhostState::Light:
					state = "Interacting With A Light";
					break;
				case sdk::GhostState::Door:
					state = "Interacting With A Door";
					break;
				case sdk::GhostState::Throwing:
					state = "Throwing A Prop";
					break;
				case sdk::GhostState::FuseBox:
					state = "Interacting With Fusebox";
					break;
				case sdk::GhostState::Appear:
					state = "Appearing";
					break;
				case sdk::GhostState::DoorKnock:
					state = "Knocking On Door";
					break;
				case sdk::GhostState::WindowKnock:
					state = "Knocking On Window";
					break;
				case sdk::GhostState::CarAlarm:
					state = "Setting of Alarm";
					break;
				case sdk::GhostState::Flicker:
					state = "Flashing";
					break;
				case sdk::GhostState::CCTV:
					state = "Camera stuff";
					break;
				case sdk::GhostState::RandomEvent:
					state = "Doing Something Random";
					break;
				case sdk::GhostState::GhostAbility:
					state = "Doing Ability";
					break;
				case sdk::GhostState::Mannequin:
					state = "Interacting With Mannequin";
					break;
				case sdk::GhostState::TeleportObject:
					state = "Teleporting Object";
					break;
				case sdk::GhostState::Interact:
					state = "Interacting With Something";
					break;
				case sdk::GhostState::SummoningCircle:
					state = "Being Summoned";
					break;
				case sdk::GhostState::MusicBox:
					state = "Music Box";
					break;
				case sdk::GhostState::Dots:
					state = "Appearing in Dots";
					break;
				case sdk::GhostState::Salt:
					state = "Interacting With Salt";
					break;
				default: state = "Unknown";
			}

			return state;
		}

		std::string get_ghost_name(sdk::GhostType gt)//make this better
		{
			std::string type = "Unknown";

			switch (gt)
			{
			case sdk::GhostType::Spirit:
				type = "Spirit";
				break;
			case sdk::GhostType::Wraith:
				type = "Wraith";
				break;
			case sdk::GhostType::Phantom:
				type = "Phantom";
				break;
			case sdk::GhostType::Poltergeist:
				type = "Poltergeist";
				break;
			case sdk::GhostType::Banshee:
				type = "Banshee";
				break;
			case sdk::GhostType::Jinn:
				type = "Jinn";
				break;
			case sdk::GhostType::Mare:
				type = "Mare";
				break;
			case sdk::GhostType::Revenant:
				type = "Revenant";
				break;
			case sdk::GhostType::Shade:
				type = "Shade";
				break;
			case sdk::GhostType::Demon:
				type = "Demon";
				break;
			case sdk::GhostType::Yurei:
				type = "Yurei";
				break;
			case sdk::GhostType::Oni:
				type = "Oni";
				break;
			case sdk::GhostType::Yokai:
				type = "Yokai";
				break;
			case sdk::GhostType::Hantu:
				type = "Hantu";
				break;
			case sdk::GhostType::Goryo:
				type = "Goryo";
				break;
			case sdk::GhostType::Myling:
				type = "Myling";
				break;
			case sdk::GhostType::Onryo:
				type = "Onryo";
				break;
			case sdk::GhostType::TheTwins:
				type = "The Twins";
				break;
			case sdk::GhostType::Raiju:
				type = "Raiju";
				break;
			case sdk::GhostType::Obake:
				type = "Obake";
				break;
			case sdk::GhostType::Mimic:
				type = "Mimic";
				break;
			case sdk::GhostType::Moroi:
				type = "Moroi";
				break;
			case sdk::GhostType::Deogen:
				type = "Deogen";
				break;
			case sdk::GhostType::Thaye:
				type = "Thaye";
				break;
			case sdk::GhostType::None:
				type = "None";
				break;
			case sdk::GhostType::Gallu:
				type = "Gallu";
				break;
			case sdk::GhostType::Dayan:
				type = "Dayan";
				break;
			case sdk::GhostType::Obambo:
				type = "Obambo";
				break;
			}

			return type;
		}

		float get_distance_between_coords(sdk::Vector3 a, sdk::Vector3 b)
		{
			const float dx = a.X - b.X;
			const float dy = a.Y - b.Y;
			const float dz = a.Z - b.Z;
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
	};
	inline auto g_game_util = new game_util();
}