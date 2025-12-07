#include "common.hpp"

namespace menu
{
	class renderer
	{
	public:
		void loop();
	};
	static inline renderer* g_renderer;
}