#pragma once
#include "RTTI.h"

namespace GameEngine
{
	inline bool RTTI::Is(IdType) const
	{
		return false;
	}

	inline std::string RTTI::ToString() const
	{
		return "RTTI";
	}

	inline bool RTTI::Equals(const RTTI* rhs) const
	{
		return this==rhs;
	}

	template <typename AbstractFactory>
	inline const AbstractFactory* RTTI::As() const
	{
		return (Is(AbstractFactory::TypeIdClass()) ? reinterpret_cast<const AbstractFactory*>(this) : nullptr);
	}

	template <typename AbstractFactory>
	inline AbstractFactory* RTTI::As()
	{
		return (Is(AbstractFactory::TypeIdClass()) ? reinterpret_cast<AbstractFactory*>(const_cast<RTTI*>(this)) : nullptr);
	}
}
