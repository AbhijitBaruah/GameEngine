#pragma  once
#include "DefaultHash.h"

namespace GameEngine
{
	template <typename AbstractFactory>
	struct  DefaultHash
	{
		std::size_t operator()(const AbstractFactory& value)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(&value), sizeof(AbstractFactory));

		}

	};
	
	template<>
	struct DefaultHash<std::string>
	{
		std::size_t operator()(const std::string& value)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(value.c_str()), value.size());
		}
	};

	template<>
	struct DefaultHash<char*>
	{
		std::size_t operator()(const char* value)
		{
			std::size_t seed = 31;
			std::size_t index = 0;
			while (value[index] != '\0')
			{
				seed += value[index];
				++index;
			}
			return seed;
		}
	};

	template<>
	struct DefaultHash<const std::string>
	{
		std::size_t operator()(const std::string& value)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(value.c_str()), value.size());
		}
	};

}