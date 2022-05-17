#include "pch.h"
#include "Scope.h"
#include <stdexcept>
#include "RTTI.h"
using namespace std;
namespace GameEngine
{
	RTTI_DEFINITIONS(Scope, RTTI)

		Scope::Scope(std::size_t size) : _map(size)
	{
	}

	Scope::~Scope()
	{
		Clear();

	}
	Scope::Scope(const Scope& rhs) : _map(rhs._map.Size()), _orderedVector(rhs._orderedVector.Capacity())
	{
		for (const HashMap<std::string, Datum>::PairType* p : rhs._orderedVector)
		{
			Datum newDatum;
			if (p->second.Type() == DatumTypes::Table)
			{
				newDatum.SetType(DatumTypes::Table);
				newDatum.Reserve(p->second.Size());
				for (std::size_t i = 0; i < p->second.Size(); ++i)
				{
					Scope& nestedScope = *(p->second.Get<Scope*>(i));
					Scope* childCopy = nestedScope.Clone();
					childCopy->_parent = this;
					newDatum.PushBack(childCopy);

				}

			}
			else
			{
				newDatum = p->second;
			}

			auto pair = _map.Insert(std::make_pair(p->first, newDatum));
			_orderedVector.PushBack(&(*(pair.first)));
		}
	}

	Scope::Scope(Scope&& rhs) noexcept :_map{ std::move(rhs._map) }, _orderedVector{ std::move(rhs._orderedVector) }, _parent{ rhs._parent }
	{
		if (rhs._parent != nullptr)
		{
			auto returnPair = rhs._parent->FindContainedScope(&rhs);
			(returnPair.first)->Set(this, returnPair.second);
		}

		Vector<typename HashMap<const std::string, Datum>::PairType*>::Iterator it;
		for (it = _orderedVector.begin(); it != _orderedVector.end(); ++it)
		{
			if ((*it)->second.Type() == DatumTypes::Table)
			{
				for (std::size_t i = 0; i < (*it)->second.Size(); ++i)
				{
					(*it)->second[i]._parent = this;
				}
			}
		}
		rhs._parent = nullptr;
	}

	Scope& Scope::operator=(Scope&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			_map.Clear();
			_orderedVector.Clear();
			_map = std::move(rhs._map);
			_orderedVector = std::move(rhs._orderedVector);
			_parent = rhs._parent;

			if (_parent != nullptr)
			{
				auto returnPair = _parent->FindContainedScope(&rhs);
				(returnPair.first)->Set(this, returnPair.second);
			}

			Vector<typename HashMap<const std::string, Datum>::PairType*>::Iterator it;
			for (it = _orderedVector.begin(); it != _orderedVector.end(); ++it)
			{
				if ((*it)->second.Type() == DatumTypes::Table)
				{
					for (std::size_t i = 0; i < (*it)->second.Size(); ++i)
					{
						(*it)->second[i]._parent = this;
					}
				}
			}
			rhs._parent = nullptr;

		}

		return *this;
	}


	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			_map.Clear();
			_orderedVector.Clear();
			_parent = rhs._parent;
			_map.ReHash(rhs._map.Capacity());
			for (const HashMap<std::string, Datum>::PairType* p : rhs._orderedVector)
			{
				Datum newDatum;
				if (p->second.Type() == DatumTypes::Table)
				{
					newDatum.SetType(DatumTypes::Table);
					newDatum.Reserve(p->second.Size());
					for (std::size_t i = 0; i < p->second.Size(); ++i)
					{
						Scope& nestedScope = *(p->second.Get<Scope*>(i));
						Scope* childCopy = nestedScope.Clone();
						childCopy->_parent = this;
						newDatum.PushBack(childCopy);

					}

				}
				else
				{
					newDatum = p->second;
				}

				auto pair = _map.Insert(std::make_pair(p->first, newDatum));
				_orderedVector.PushBack(&(*(pair.first)));
			}
		}

		return *this;

	}


	bool Scope::operator==(const Scope& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		if (_orderedVector.Size() != rhs._orderedVector.Size())
		{
			return false;
		}

		for (std::size_t i = 0; i < _orderedVector.Size(); ++i)
		{
			auto rhsFindres = rhs._map.Find(_orderedVector[i]->first);
			if (rhsFindres.second)
			{
				if (_orderedVector[i]->second == rhsFindres.first.operator*().second)
				{
					continue;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}

		}
		return true;

	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(*this == rhs);
	}
	Datum& Scope::Append(const std::string& key)
	{
		Datum* result = Find(key);
		std::pair<typename HashMap<std::string, Datum>::Iterator, bool> insertReturnVal;
		if (result == nullptr)
		{
			insertReturnVal = _map.Insert(std::make_pair(key, Datum()));
			result = &(insertReturnVal.first.operator*().second);
			_orderedVector.PushBack(&(insertReturnVal.first.operator*()));
		}

		return *result;
	}

	Datum& Scope::operator[](const std::string& key)
	{
		return(Append(key));
	}

	Datum& Scope::operator[](std::int32_t key)
	{
		return(_orderedVector[key]->second);
	}

	Scope& Scope::AppendScope(const std::string& key)
	{
		Datum& appendResult = Append(key);
		Scope* newScope = nullptr;
		if (appendResult.Type() != DatumTypes::Unknown && appendResult.Type() != DatumTypes::Table)
		{
			throw std::runtime_error("Invalid datum type already exists for this key");
		}
		newScope = new Scope();
		appendResult.PushBack(newScope);
		newScope->_parent = this;
		return *newScope;
	}
	Datum* Scope::Search(const std::string& key, Scope*& outScope)
	{
		Datum* result = Find(key);
		if (result == nullptr && _parent != nullptr)
		{
			return (_parent->Search(key, outScope));
		}
		outScope = this;
		return result;
	}
	const Datum* Scope::Search(const std::string& key, const Scope*& outScope) const
	{
		const Datum* result = Find(key);
		if (result == nullptr && _parent != nullptr)
		{
			return (_parent->Search(key, outScope));
		}
		outScope = this;
		return result;
	}
	Datum* Scope::Search(const std::string& key)
	{
		Scope* s = nullptr;
		return Search(key, s);
	}

	const Datum* Scope::Search(const std::string& key) const
	{
		const Scope* s = nullptr;
		return Search(key, s);
	}

	const Datum* Scope::Find(const std::string& key) const
	{
		auto findReturnVal = _map.Find(key);
		if (!findReturnVal.second)
			return nullptr;
		return &(findReturnVal.first.operator*().second);
	}

	Datum* Scope::Find(const std::string& key)
	{
		auto findReturnVal = _map.Find(key);
		if (!findReturnVal.second)
			return nullptr;
		return &(findReturnVal.first.operator*().second);
	}

	void Scope::Adopt(Scope& scopeToAdopt, const std::string& key)
	{

		if (scopeToAdopt._parent == this || &scopeToAdopt == this || scopeToAdopt.IsAncestorOf(*this))
			return;


		Datum* result = Find(key);

		if (result == nullptr)
		{
			auto insertReturnVal = _map.Insert(std::make_pair(key, Datum(&scopeToAdopt)));

			_orderedVector.PushBack(&(*(insertReturnVal.first)));

		}

		else
		{
			if (result->Type() != DatumTypes::Unknown && result->Type() != DatumTypes::Table)
			{
				throw std::runtime_error("Invalid datum type already exists for this key");
			}
			result->PushBack(&scopeToAdopt);

		}
		if (scopeToAdopt._parent != nullptr)
		{
			scopeToAdopt.Orphan();
		}
		scopeToAdopt._parent = this;
	}


	std::pair<Datum*, std::size_t> Scope::FindContainedScope(Scope* const scopeToFindIn)
	{
		for (std::size_t i = 0; i < _orderedVector.Size(); ++i)
		{
			if (_orderedVector[i]->second.Type() == DatumTypes::Table)
			{
				for (std::size_t j = 0; j < _orderedVector[i]->second.Size(); ++j)
				{
					if (_orderedVector[i]->second.Get<Scope*>(j) == (scopeToFindIn))
					{
						return (std::make_pair(&(_orderedVector[i]->second), j));
					}
				}
			}
		}

		return (std::make_pair(nullptr, 0));
	}

	const std::pair<Datum*, std::size_t> Scope::FindContainedScope(Scope* const scopeToFindIn) const
	{
		for (std::size_t i = 0; i < _orderedVector.Size(); ++i)
		{
			if (_orderedVector[i]->second.Type() == DatumTypes::Table)
			{
				for (std::size_t j = 0; j < _orderedVector[i]->second.Size(); ++j)
				{
					if (_orderedVector[i]->second.Get<Scope*>(j) == (scopeToFindIn))
					{
						return (std::make_pair(&(_orderedVector[i]->second), j));
					}
				}
			}
		}

		return (std::make_pair(nullptr, 0));
	}
	Scope* Scope::Clone() const
	{
		return new Scope(*this);
	}

	void Scope::Orphan()
	{
		if (_parent == nullptr)
			return;
		auto result = _parent->FindContainedScope(this);
		if (result.first != nullptr)
		{
			result.first->RemoveAt(result.second);
		}
		_parent = nullptr;
	}

	void Scope::Clear()
	{
		if (_parent != nullptr)
		{
			Orphan();
		}
		for (std::size_t i = 0; i < _orderedVector.Size(); ++i)
		{
			if (_orderedVector[i]->second.Type() == DatumTypes::Table)
			{
				for (std::size_t j = _orderedVector[i]->second.Size(); j > 0; --j)
				{

					delete (&(_orderedVector[i]->second[j - 1]));
				}

			}
		}
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		if (rhs->Is(Scope::TypeIdClass()))
		{
			const Scope* myScope = reinterpret_cast<const Scope*>(rhs);
			return (*this == *myScope);
		}

		return false;
	}

	Scope* Scope::GetParent()
	{
		return _parent;
	}
	const Scope* Scope::GetParent() const
	{
		return _parent;
	}

	bool Scope::IsEmpty() const
	{
		return _orderedVector.Size() == 0;
	}

	bool Scope::IsAncestorOf(const Scope& scope) const
	{
		bool result = false;
		Scope* parent = scope._parent;
		while (parent != nullptr)
		{
			if (parent == this)
			{
				result = true;
				break;
			}
			parent = parent->_parent;
		}
		return result;
	}

	bool Scope::IsDescendentOf(const Scope& scope) const
	{
		return scope.IsAncestorOf(*this);
	}

	Datum& Scope::At(const std::string string)
	{
		Datum* datum = Find(string);
		if (datum == nullptr)
		{
			throw std::runtime_error("Expected entry.");
		}

		return *datum;
	}

	const Datum& Scope::At(const std::string string) const
	{
		const Datum* datum = (Find(string));
		if (datum == nullptr)
		{
			throw std::runtime_error("Expected entry.");
		}

		return *datum;
	}

}
