#include "../gui.hpp"

namespace menu
{
	void gui::visual_tab()
	{
		g_gui_util->checkbox("Fusebox ESP");
		g_gui_util->checkbox("Ghost ESP");
	}
}