#pragma  once
#include "pch.h"
#include "Attribute.h"
#include <stdexcept>
#include "HashMap.h"
#include "RTTI.h"
namespace GameEngine
{
	RTTI_DEFINITIONS(Attributed, Scope)

		Attributed::Attributed(std::size_t type)
		{
		Populate(type);
		}



	Attributed::Attributed(const Attributed& rhs) : Scope(rhs)
	{
		(*this)["this"] = this;
		Vector<Signature>& signatures = TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).first.operator*().second;
		assert(TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).second != false);
		for (std::size_t i = 1; i < rhs._orderedVector.Size(); ++i)
		{
			if (_orderedVector[i]->second._isExternal && _orderedVector[i]->second.Type() != DatumTypes::Table)
			{
				FixExternalPointers(signatures, i);
			}
		}

	}

	Attributed::Attributed(Attributed&& rhs) noexcept : Scope(std::move(rhs))
	{
		(*this)["this"] = this;
		Vector<Signature>& signatures = TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).first.operator*().second;
		assert(TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).second != false);
		for (std::size_t i = 1; i < signatures.Size(); ++i)
		{
			if (_orderedVector[i]->second._isExternal && _orderedVector[i]->second.Type() != DatumTypes::Table)
			{
				FixExternalPointers(signatures, i);
			}
		}
	}

	Attributed& Attributed::operator=(Attributed&& rhs) noexcept
	{

		if (this != &rhs)
		{
			Scope::operator=(std::move(rhs));
			(*this)["this"] = this;
			Vector<Signature>& signatures = TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).first.operator*().second;
			assert(TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).second != false);
			for (std::size_t i = 1; i < signatures.Size(); ++i)
			{
				if (_orderedVector[i]->second._isExternal && _orderedVector[i]->second.Type() != DatumTypes::Table)
				{
					FixExternalPointers(signatures, i);
				}
			}
		}

		return *this;
	}
	void Attributed::FixExternalPointers(const Vector<Signature>& vector, const std::size_t index)
	{

		uint8_t* byte = reinterpret_cast<uint8_t*>(this);
		_orderedVector[index]->second.SetStorage(byte + vector[index - 1].offset, vector[index - 1].size, vector[index - 1].type);
	}
	Attributed& Attributed::operator=(const Attributed& rhs)
	{

		if (this != &rhs)
		{
			Scope::operator =(rhs);
			(*this)["this"] = this;
			Vector<Signature>& signatures = TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).first.operator*().second;
			assert(TypeRegistry::getInstance()->_hashMap.Find(rhs.TypeIdInstance()).second != false);
			for (std::size_t i = 1; i < rhs._orderedVector.Size(); ++i)
			{
				if (_orderedVector[i]->second._isExternal && _orderedVector[i]->second.Type() != DatumTypes::Table)
				{
					FixExternalPointers(signatures, i);
				}
			}
		}

		return *this;
	}

	void Attributed::Populate(std::size_t key)
	{

		(*this)["this"] = this;
		uint8_t* byte = reinterpret_cast<uint8_t*>(this);
		if (TypeRegistry::getInstance()->_hashMap.Find(key).second)
		{
			Vector<Signature>& signatures = TypeRegistry::getInstance()->_hashMap.Find(key).first.operator*().second;
			for (std::size_t i = 0; i < signatures.Size(); ++i)
			{
				Datum& datumCreated = Append(signatures[i].name);
				if (datumCreated.Type() != DatumTypes::Unknown && datumCreated.Type() != signatures[i].type)
				{
					throw std::runtime_error("Cannot change parent datum type");
				}
				datumCreated.SetType(signatures[i].type);

				if (signatures[i].type != DatumTypes::Table)
				{
					datumCreated.SetStorage(byte + signatures[i].offset, signatures[i].size, signatures[i].type);
				}
			}
		}
		else
		{
			throw std::runtime_error("No such entry in type registry");
		}
	}

	Datum& Attributed::AppendAuxillary(const std::string& key)
	{
		if (Find(key) != nullptr)
		{
			throw std::runtime_error("Cannot append auxiliary attribute as prescribed attribute");
		}
		return(Append(key));

	}

	bool Attributed::IsAttribute(const std::string& key)
	{
		return (_map.Find(key).second);

	}
	bool Attributed::IsPrescribedAttribute(const std::string& key)
	{
		if (IsAttribute(key))
		{
			for (std::size_t i = 0; i < TypeRegistry::getInstance()->_hashMap.Find(TypeIdInstance()).first.operator *().second.Size(); ++i)
			{
				if (_orderedVector[i + 1]->first == key)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool Attributed::IsAuxillaryAttribute(const std::string& key)
	{
		return ((IsAttribute(key)) && (!IsPrescribedAttribute(key)));
	}


}