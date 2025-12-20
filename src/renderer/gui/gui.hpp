#include "common.hpp"

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


		etab m_selected_tab = SELF;

		bool test_bool = false;
		bool menu_open = false;
		ImFont* segoeui_font;
	};
	static inline gui g_gui;
}