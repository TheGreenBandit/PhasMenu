#include "../gui.hpp"

namespace menu
{
	void gui::self_tab()
	{
		g_gui_util->checkbox("Infinite Sprint");
		g_gui_util->checkbox("Always Sane");
		g_gui_util->checkboxslider("Movement Speed", "", 0, 10);

	}
}