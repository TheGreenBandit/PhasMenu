#include "common.hpp"
#include "memory/hooking/hooking.hpp"
#include "thread_pool.hpp"
#include "renderer/renderer.hpp"
#include "util/game_util.hpp"
#include "services/notification_service/notification_service.hpp"

using namespace menu;

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);
		
		g_hmodule = hmod;
		g_main_thread = CreateThread(
			nullptr,
			0,
			[](PVOID) -> DWORD 
			{
				std::filesystem::path base_dir = std::getenv("appdata");
				base_dir /= "PhasMenu";
				g_file_manager.init(base_dir);

				//g_file_manager.get_project_folder("./Resources/").get_file("./rainbow_border.gif");
				auto logger_instance = std::make_unique<logger>("PhasMenu", g_file_manager.get_project_file("./PhasMenu.log"));
				//init
				LOG(INFO) << "Initializing...";
				auto thread_pool_instance = std::make_unique<thread_pool>();
				LOG(INFO) << "Thread pool initialized.";

				g.init(g_file_manager.get_project_file("./settings.json"));
				LOG(INFO) << "Settings Loaded.";
				g_feature_manager.init();
				LOG(INFO) << "Features Loaded.";
				auto notification_service_instance = std::make_unique<notification_service>();

				g_renderer.init();
				LOG(INFO) << "Renderer Loaded.";
				g_il2cpp.init();
				LOG(INFO) << "Il2cpp helper Loaded.";
				auto hooking_instance = std::make_unique<hooking>();
				LOG(INFO) << "Hooking initialized.";

				g_hooking->enable();
				LOG(INFO) << "Hooking enabled.";

				while (!GetAsyncKeyState(VK_DELETE))
				{
					std::this_thread::sleep_for(10ms);
				}
				g_running = false;
				g_hooking->disable();

				g.destroy();
				g_renderer.destroy();
				notification_service_instance.reset();
				hooking_instance.reset();
				LOG(INFO) << "Hooking uninitialized.";
				g_feature_manager.destroy();
				LOG(INFO) << "Destroyed feature manager.";
				thread_pool_instance->destroy();
				LOG(INFO) << "Destroyed thread pool.";

				LOG(INFO) << "Shutting down...";
				logger_instance.reset();

				CloseHandle(g_main_thread);
				FreeLibraryAndExitThread(g_hmodule, 0);
			}, nullptr, 0, &g_main_thread_id);
	}
	return true;
}