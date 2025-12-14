#pragma once

#include "features/feature_manager.hpp"

namespace menu::feature
{
	inline toggle_feature* get_togglefeature_from_label(std::string_view label)
	{
		for (int i = 0; i <= g_toggle_features.size(); i++)
		{
			toggle_feature* feature = g_toggle_features[i];
			if (feature->label().compare(label.data()) == 0)
				return feature;

			if (i == g_toggle_features.size()) //return if no find any
				return g_default_toggle;
		}
		return g_default_toggle;
	}

	inline execute_feature* get_executefeature_from_label(std::string_view label)
	{
		for (int i = 0; i <= g_execute_features.size(); i++)
		{
			execute_feature* feature = g_execute_features[i];
			if (feature->label().compare(label.data()) == 0)
				return feature;

			if (i == g_toggle_features.size()) //return if no find any
				return g_default_execute;
		}
	}

	template<typename T>
	inline T* get_feature_from_label_type_specific(std::string_view label)
	{
		for (toggle_feature* feature : g_toggle_features)
		{
			if (feature->label().compare(label.data()) == 0)
				return reinterpret_cast<T*>(feature);
			else continue;
		}
	}

	template<typename T>
	inline T* get_feature_from_type()
	{
		static_assert(std::is_base_of<toggle_feature, T>::value, "T must be derived from toggle_feature");
		if (!std::is_base_of<toggle_feature, T>::value)
		{
			LOG(INFO) << "INVALID";
			return nullptr;
		}

		for (toggle_feature* feature : g_toggle_features)
		{
			if (typeid(*feature) == typeid(T))
				return static_cast<T*>(feature);
			else continue;
		}
	}
}