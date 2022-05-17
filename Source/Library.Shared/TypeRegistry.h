#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include "Datum.h"
#include "HashMap.h"
#include "Vector.h"

namespace GameEngine
{
	class Attributed;
	struct Signature
	{
		std::string name;
		DatumTypes type;
		std::size_t size;
		std::size_t offset;

	};
	class TypeRegistry
	{

	public:
		TypeRegistry(const TypeRegistry& rhs) = delete;
		TypeRegistry& operator=(const TypeRegistry& rhs) = delete;

		static TypeRegistry* getInstance();
		

		template<typename Child, typename Parent>
		void RegisterClass();

		template<typename Child>
		void RegisterClass();
		HashMap<std::size_t, Vector<Signature>> _hashMap;


	private:
		TypeRegistry() {};

		static TypeRegistry* _instance;

	};

}
#include "TypeRegistry.inl"
