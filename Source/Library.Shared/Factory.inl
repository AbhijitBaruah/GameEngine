#pragma once
#include "pch.h"
#include "Factory.h"
#include "gsl/gsl"
#include "gsl/pointers"
namespace GameEngine
{
	template<typename AbstractFactory>
	inline Factory<AbstractFactory>* Factory<AbstractFactory>::Find(const std::string& className)
	{
		auto [mapIterator, wasFound] = _factoryList.Find(className);
		return(wasFound ? (*mapIterator).second : nullptr);
	}
	template <typename AbstractFactory>
	inline  gsl::owner<AbstractFactory*> Factory<AbstractFactory>::Create(const std::string& className)
	{
		auto [mapIterator, wasFound] = _factoryList.Find(className);
		return(wasFound ? (*mapIterator).second->Create() : nullptr);
	}
	template<typename AbstractFactory>
	inline  void  Factory<AbstractFactory>::Add(Factory<AbstractFactory>& concreteFactory)
	{
		auto [mapIterator, wasInserted] = _factoryList.Insert(std::make_pair(concreteFactory.ClassName(), &concreteFactory));
		if (!wasInserted) { throw std::runtime_error("Cannot add another class with same name"); }

	}
	template<typename AbstractFactory>
	inline  void  Factory<AbstractFactory>::Remove(Factory<AbstractFactory>& concreteFactory)
	{
		_factoryList.Remove(concreteFactory.ClassName());
	}

}