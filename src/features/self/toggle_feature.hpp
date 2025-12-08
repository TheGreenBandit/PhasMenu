#include "features/core/feature.hpp"

namespace menu
{
	class toggle_feature : public feature
	{
		bool m_enabled;
	public:
		bool& is_enabled();
		
		void toggle();

		virtual void on_enable() {};
		virtual void on_tick() {};
		virtual void on_disable() {};
	};
}