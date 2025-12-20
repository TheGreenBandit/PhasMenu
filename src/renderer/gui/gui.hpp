#pragma once

#include "common.hpp"
#include "util/gui_util.hpp"

namespace menu
{
	enum etab : uint32_t
	{
		SELF,
		GHOST,
		VISUAL,
		SETTINGS
	};

	class gui
	{
	public:
		void init();
		void render();
		void handle_input();

		void self_tab();
		void ghost_tab();
		void visual_tab();
		void settings_tab();

		const char* tab_to_icon(etab tab)
		{
			switch (tab)
			{
				case SELF: return ICON_FA_USER;
				case GHOST: return ICON_FA_SKULL_CROSSBONES;
				case VISUAL: return ICON_FA_EYE;
				case SETTINGS: return ICON_FA_COG;
				default: return"NULL ICON";
			}
		}

		etab m_selected_tab = SELF;

		float test_floats[255];
		bool test_bools[255];

		bool m_menu_open = false;

		ImFont* segoeui_font;
	};
	static inline gui g_gui;
}