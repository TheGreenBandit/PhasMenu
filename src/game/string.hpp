#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct __declspec(align(8)) StringFields
	{
		int32_t StringLength;
		uint16_t FirstChar;
	};

	struct String
	{
		void* Clazz;
		void* Monitor;
		StringFields Fields;
	};
}
