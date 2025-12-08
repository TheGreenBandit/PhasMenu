#include "common.hpp"

namespace menu
{
	class gui
	{
	public:
		void render();
		void handle_input();


		bool menu_open = true;
		ImFont* segoeui_font;
	};
	static inline gui g_gui;
}