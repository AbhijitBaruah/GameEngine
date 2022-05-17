#pragma once
#include "TypeRegistry.h"

namespace GameEngine
{
	template<typename  Child, typename  Parent>
	void TypeRegistry::RegisterClass()
	{

		Vector<Signature> concatenatedVector;
		if (Parent::TypeIdClass() != Attributed::TypeIdClass())
		{
			if (_hashMap.Find(Parent::TypeIdClass()).second)
			{
				auto& a = _hashMap.Find(Parent::TypeIdClass()).first.operator*().second;
				for (const auto& value : a)
				{
					concatenatedVector.PushBack(value);
				}
			}

			else
			{
				throw std::runtime_error("Parent class is not in registry");
			}

		}
		Vector<Signature> childVector = Child::Signatures();
		for (auto& value : childVector )
		{
			concatenatedVector.PushBack(value);
		}

		_hashMap.Insert(std::make_pair(Child::TypeIdClass(), concatenatedVector));


	}
}