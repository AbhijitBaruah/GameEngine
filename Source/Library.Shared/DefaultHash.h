#pragma once
#include "pch.h"
#include <cstddef>
#include <cstdint>
#include <string>
namespace GameEngine
{	
	std::size_t AdditiveHash(const uint8_t* data, std::size_t size);


	
}
#include "DefaultHash.inl"
