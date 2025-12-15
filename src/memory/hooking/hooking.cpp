#include "hooking.hpp"

#include "common.hpp"
#include "renderer/gui/gui.hpp"
#include "util/logger/logger.hpp"
#include "memory/module.hpp"
#include "renderer/renderer.hpp"
#include "memory/pointers.hpp"
#include <MinHook.h>
#include <fibersapi.h>

namespace menu
{
	hooking::hooking()//game only crashes on reinjection if these hooks are uncommented. most likely not unloading them properly
	{
		try
		{
			for (auto& detour_hook_helper : m_detour_hook_helpers)
				detour_hook_helper->m_detour_hook->set_target_and_create_hook(detour_hook_helper->m_on_hooking_available());

			detour_hook_helper::add<hooks::network_getnetwork>("NGN", (void*)sdk::Network_Get_Network_ptr);
			detour_hook_helper::add<hooks::exitlevel_exit>("ELE", (void*)sdk::ExitLevel_Exit_ptr);
			detour_hook_helper::add<hooks::firstpersoncontroller_update>("FPCU", (void*)sdk::FirstPersonController_Update_ptr);
		}
		catch (std::exception& e)
		{
			LOG(WARNING) << "Exception while creating hooks in hooking constructor: " << e.what();
		}
		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		for (const auto& detour_hook_helper : m_detour_hook_helpers)
			detour_hook_helper->m_detour_hook->enable();

		MH_ApplyQueued();
		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
			detour_hook_helper->m_detour_hook->disable();

		MH_ApplyQueued();

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
			delete detour_hook_helper;
		m_detour_hook_helpers.clear();
	}

	hooking::detour_hook_helper::~detour_hook_helper()
	{
		delete m_detour_hook;
	}

	void hooking::detour_hook_helper::enable_hook_if_hooking_is_already_running()
	{
		if (g_hooking && g_hooking->m_enabled)
		{
			if (m_on_hooking_available)
				m_detour_hook->set_target_and_create_hook(m_on_hooking_available());

			m_detour_hook->enable();
			MH_ApplyQueued();
		}
	}
}
