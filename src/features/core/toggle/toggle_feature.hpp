//#pragma once
//
//#include "../feature.hpp"
//#include "features/feature_manager.hpp"
//
//namespace menu
//{
//	class toggle_feature : public feature
//	{
//		bool m_enabled;
//
//		virtual void on_enable();
//		virtual void on_tick();
//		virtual void on_disable();
//	public:
//		bool& is_enabled();
//		void toggle();
//
//		toggle_feature(std::string name, std::string desc, int keybind = -255) : feature(name, desc, feature_type::toggle, keybind)
//		{
//		}
//	};
//}