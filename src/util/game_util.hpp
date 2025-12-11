#pragma once

#include "common.hpp"

namespace menu
{
	class game_util
	{
	public:
		sdk::Network* get_network()
		{
			if (game::network) return game::network;

			sdk::Network* network = sdk::Network_Get_Network_ptr(nullptr);
			if (network == nullptr)
				return nullptr;

			game::network = network;
			return network;
		}
	};
	inline auto g_game_util = new game_util();
}