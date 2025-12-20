#pragma once

#include <Windows.h>
#include <chrono>
#include <atomic>
#include <thread>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <consoleapi.h>
#include <filesystem>
#include <stack>
#include <d3d11.h>

#include <wrl/client.h>
#include <nlohmann/json.hpp>s
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include "core/settings.hpp"
#include "core/file_manager/file_manager.hpp"
#include "features/feature_manager.hpp"
#include "util/logger/logger.hpp"
#include "util/il2cpp/il2cpp.hpp"
#include "renderer/fonts/font_awesome_5.h"
#include "game/sdk.hpp"
#include "services/notification_service/notification_service.hpp"

namespace menu
{
	using namespace std::chrono_literals;

	template<typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	static HMODULE g_hmodule;
	static HANDLE g_main_thread;
	static DWORD g_main_thread_id;
	static std::atomic_bool g_running = true;

	namespace game
	{
		inline sdk::Network* network;
	}
}