#pragma once

#include "common.hpp"

#define S(s)                                           \
    ([&]() -> std::string {                            \
        if (!(s)) return {};                           \
        const int32_t _len = (s)->Fields.StringLength; \
        const auto _first = &(s)->Fields.FirstChar;\
        std::wstring _wide(_first, _first + _len);     \
        return std::string(_wide.begin(), _wide.end());\
    })()

namespace menu
{
	class game_util
	{
	public:
		sdk::Network* get_network()
		{
			if (game::network) return game::network;

			sdk::Network* network = sdk::Network_Get_Network_ptr(nullptr);
			if (network == nullptr)
				return nullptr;

			game::network = network;
			return network;
		}

		ImVec2 world_to_screen(const sdk::Vector3 vWorldPosition) 
		{
			static ImVec2 ret = ImVec2(0, 0);
			RECT rect;
			const HWND hGame = FindWindowA(nullptr, "Phasmophobia");
			GetWindowRect(hGame, &rect);
			const auto screenHeight = rect.bottom - rect.top;
			const auto screenWidth = rect.right;
			const auto camera = get_network()->Fields.LocalPlayer->Fields.Camera;
			if (camera == nullptr) 
			return ImVec2(-1, -1);
			const auto cameraTransform = sdk::Component_Get_Transform_ptr(reinterpret_cast<sdk::Component*>(camera), nullptr);
			const auto cameraPos = sdk::Transform_Get_Position_ptr(cameraTransform, nullptr); 
			const auto cameraForward = sdk::Transform_Get_Forward_ptr(cameraTransform, nullptr);
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

			ret.x = (ndcX * 0.5f + 0.5f) * screenWidth; ret.y = (1.0f - (ndcY * 0.5f + 0.5f)) * screenHeight;

			return ret; 
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