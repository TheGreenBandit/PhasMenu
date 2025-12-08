#include "hooking.hpp"

#include "common.hpp"
#include "renderer/gui/gui.hpp"
#include "util/logger/logger.hpp"
#include "memory/module.hpp"
#include "renderer/renderer.hpp"

#include <MinHook.h>
#include <fibersapi.h>

namespace menu
{
	hooking::hooking()
	{
		// The only instances in that vector at this point should only be the "lazy" hooks
		// aka the ones that still don't have their m_target assigned
		try
		{
			LOG(INFO) << "0";
			for (auto& detour_hook_helper : m_detour_hook_helpers)
				detour_hook_helper->m_detour_hook->set_target_and_create_hook(detour_hook_helper->m_on_hooking_available());
			LOG(INFO) << "1";
			LOG(INFO) << (void*)sdk::PlayerStamina_Update_ptr;
			LOG(INFO) << "1.5";
			detour_hook_helper::add<hooks::PlayerStamina_Update>("PSU", (void*)sdk::PlayerStamina_Update_ptr);
			LOG(INFO) << "2";
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
		LOG(INFO) << "4";
		for (const auto& detour_hook_helper : m_detour_hook_helpers)
			detour_hook_helper->m_detour_hook->enable();
		LOG(INFO) << "5";
		MH_ApplyQueued();
		LOG(INFO) << "6";
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
