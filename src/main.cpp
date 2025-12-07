#include "common.hpp"
#include "memory/hooking/hooking.hpp"
#include "thread_pool.hpp"

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
				auto logger_instance = std::make_unique<logger>("PhasMenu", g_file_manager.get_project_file("./PhasMenu.log"));
				//init
				LOG(INFO) << "Initializing...";
				auto thread_pool_instance = std::make_unique<thread_pool>();
				LOG(INFO) << "Thread pool initialized.";

				g.init(g_file_manager.get_project_file("./settings.json"));
				g_feature_manager.init();

				LOG(INFO) << "Settings Loaded.";


				//g_hooking->enable();
				LOG(INFO) << "Hooking enabled.";
				while (!GetAsyncKeyState(VK_DELETE))
				{
					LOG(INFO) << "Running...";
					std::this_thread::sleep_for(10ms);
				}
				g_running = false;
				//g_hooking->disable();

				g.destroy();

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