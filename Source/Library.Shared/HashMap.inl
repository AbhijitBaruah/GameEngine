#include "HashMap.h"

namespace GameEngine
{
	template<typename TKey, typename TData>
	HashMap<TKey, TData>::HashMap(size_t Size, std::function<size_t(const TKey&)>defaultHash, std::function<bool(const TKey&, const TKey&)> equalityFunctor) : _size(0), _hash(defaultHash), _equality(equalityFunctor)
	{
		_hashMap.Reserve(Size);
		_hashMap.Resize(Size);
	}

	template<typename TKey, typename TData>
	std::pair<typename HashMap<TKey, TData>::Iterator, bool> HashMap<TKey, TData>::Insert(const PairType& pair)
	{

		size_t value = _hash(pair.first);
		value = (value % _hashMap.Capacity());
		ChainType& list = _hashMap.At(value);
		typename ChainType::Iterator it1;
		for (it1 = list.begin(); it1 != list.end(); ++it1)
		{
			if (it1.operator*().first == pair.first)
			{
				Iterator it2(*this, value, it1);
				return std::make_pair(it2, false);
			}
		}
		it1 = list.PushBack(pair);
		++_size;
		return std::make_pair(Iterator(*this, value, it1), true);


	}

	template<typename TKey, typename TData>
	TData& HashMap<TKey, TData>::operator[](const TKey& key)
	{
		std::pair< Iterator, bool> it = Insert(std::make_pair(key, TData()));
		return it.first._node.operator*().second;
	}

	template<typename TKey, typename TData>
	TData& HashMap<TKey, TData>::At(const TKey& key)
	{
		size_t value = _hash(key);
		value = (value % _hashMap.Capacity());
		ChainType& list = _hashMap.At(value);
		typename ChainType::Iterator it1;
		for (it1 = list.begin(); it1 != list.end(); ++it1)
		{
			if (it1.operator*().first == key)
			{
				return (it1.operator*().second);
			}
		}
		throw std::runtime_error("Invalid key passed in");
	}

	template<typename TKey, typename TData>
	const TData& HashMap<TKey, TData>::At(const TKey& key) const
	{
		size_t value = _hash(key);
		value = (value % _hashMap.Capacity());
		const ChainType& list = _hashMap.At(value);
		typename ChainType::ConstIterator it1;
		for (it1 = list.begin(); it1 != list.end(); ++it1)
		{
			if (it1.operator*().first == key)
			{
				return (it1.operator*().second);
			}
		}
		throw std::runtime_error("Invalid key passed in");
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::begin()
	{
		size_t index = 0;
		if (_size != 0)
		{
			while (_hashMap.At(index).Size() == 0 && (index < _hashMap.Capacity()))
			{
				++index;
			}
			return Iterator(*this, index, _hashMap.At(index).begin());
		}
		return Iterator(*this, _hashMap.Capacity());

	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::begin() const
	{
		size_t index = 0;
		if (_size != 0)
		{
			while (_hashMap.At(index).Size() == 0 && (index < _hashMap.Capacity()))
			{
				++index;
			}
			return ConstIterator(*this, index, _hashMap.At(index).begin());
		}

		return ConstIterator(*this, _hashMap.Capacity());
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cbegin() const
	{
		size_t index = 0;
		if (_size != 0)
		{
			while (_hashMap.At(index).Size() == 0 && (index < _hashMap.Capacity()))
			{
				++index;
			}
			return ConstIterator(*this, index, _hashMap.At(index).begin());
		}

		return ConstIterator(*this, _hashMap.Capacity());
	}

	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::end() const
	{
		return ConstIterator(*this, _hashMap.Capacity());
	}
	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cend() const
	{
		return ConstIterator(*this, _hashMap.Capacity());
	}
	template<typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::end()
	{
		return Iterator(*this, _hashMap.Capacity());
	}



	template<typename TKey, typename TData>
	HashMap<TKey, TData>::Iterator::Iterator(HashMap& owner, size_t index, typename ChainType::Iterator node) : _owner(&owner), _index(index), _node(node)
	{
	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const HashMap& owner, size_t index, typename ChainType::ConstIterator node) : _owner(&owner), _index(index), _node(node)
	{
	}

	template<typename TKey, typename TData>
	inline size_t HashMap<TKey, TData>::Size() const
	{
		return _size;
	}
	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ContainsKey(const TKey& key) const
	{
		return (Find(key).second);
	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ContainsKey(const TKey& key, TData*& outData)
	{
		std::pair<Iterator, bool> returnVal = Find(key);
		outData = &returnVal.first.operator *().second;
		return (returnVal.second);
	}

	template<typename TKey, typename TData>
	std::pair<typename HashMap<TKey, TData>::Iterator, bool> HashMap<TKey, TData>::Find(const TKey& key)
	{
		size_t value = _hash(key);
		value = (value % _hashMap.Capacity());
		ChainType& list = _hashMap.At(value);
		typename ChainType::Iterator it1;
		for (it1 = list.begin(); it1 != list.end(); ++it1)
		{
			if (it1.operator*().first == key)
			{
				return std::make_pair(Iterator(*this, value, it1), true);
			}
		}
		return std::make_pair(Iterator(*this, value, it1), false);
	}

	template<typename TKey, typename TData>
	std::pair<typename HashMap<TKey, TData>::ConstIterator, bool> HashMap<TKey, TData>::Find(const TKey& key) const
	{
		size_t value = _hash(key);
		value = (value % _hashMap.Capacity());
		const ChainType& list = _hashMap.At(value);
		typename ChainType::ConstIterator it1;
		for (it1 = list.begin(); it1 != list.end(); ++it1)
		{
			if (it1.operator*().first == key)
			{
				return std::make_pair(ConstIterator(*this, value, it1), true);
			}
		}
		return std::make_pair(ConstIterator(*this, value, it1), false);
	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::Iterator::operator!=(const Iterator& other)const
	{
		return (_node.operator !=(other._node) || _index != other._index || _owner != other._owner);
	}
	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ConstIterator::operator!=(const ConstIterator& other)const
	{
		return (_node.operator !=(other._node) || _index != other._index || _owner != other._owner);
	}
	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::Iterator::operator==(const Iterator& other)const
	{
		return !operator!=(other);
	}

	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::ConstIterator::operator==(const ConstIterator& other)const
	{
		return !operator!=(other);
	}

	template<typename TKey, typename TData>
	typename inline HashMap<TKey, TData>::Iterator& HashMap<TKey, TData>::Iterator::operator++()
	{

		if (_node.operator *() != _owner->_hashMap.At(_index).Back())
		{
			_node.operator++();
		}
		else
		{
			while (_owner->_hashMap.At(++_index).IsEmpty() && _index < _owner->_hashMap.Capacity())
			{
				continue;
			}
			if (_index < _owner->_hashMap.Capacity())
			{
				_node = _owner->_hashMap.At(_index).begin();
			}
			else
			{
				_node = typename ChainType::Iterator::Iterator();
			}
		}

		return *this;

	}
	template<typename TKey, typename TData>
	typename inline HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Iterator::operator++(int)
	{
		Iterator copy = *this;
		operator++();
		return copy;
	}

	template<typename TKey, typename TData>
	typename inline HashMap<TKey, TData>::ConstIterator& HashMap<TKey, TData>::ConstIterator::operator++()
	{

		if (_node.operator *() != _owner->_hashMap.At(_index).Back())
		{
			_node.operator++();
		}
		else
		{
			while (_owner->_hashMap.At(++_index).IsEmpty() && _index < _owner->_hashMap.Capacity() - 1)
			{
				continue;
			}

			_node = _owner->_hashMap.At(_index).begin();

		}

		return *this;

	}
	template<typename TKey, typename TData>
	typename inline HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::ConstIterator::operator++(int)
	{
		ConstIterator copy = *this;
		operator++();
		return copy;
	}

	template<typename TKey, typename TData>
	std::pair<const TKey, TData>& HashMap<TKey, TData>::Iterator::operator*()
	{
		return _node.operator *();
	}
	template<typename TKey, typename TData>
	std::pair<const TKey, TData>* HashMap<TKey, TData>::Iterator::operator->()
	{
		return &(_node.operator *());
	}
	template<typename TKey, typename TData>
	const std::pair<const TKey, TData>& HashMap<TKey, TData>::ConstIterator::operator*() const
	{
		return _node.operator *();
	}
	template<typename TKey, typename TData>
	const std::pair<const TKey, TData>* HashMap<TKey, TData>::ConstIterator::operator->() const
	{
		return &(_node.operator *());
	}
	template<typename TKey, typename TData>
	inline void HashMap<TKey, TData>::Clear()
	{
		_hashMap.Clear();
		_size = 0;
	}
	template<typename TKey, typename TData>
	bool HashMap<TKey, TData>::Remove(const TKey& value)
	{
		std::pair<Iterator, bool>returnVal = Find(value);
		if (returnVal.second == false)
		{
			return false;
		}

		ChainType& list = _hashMap.At(returnVal.first._index);
		list.Remove(returnVal.first._node.operator *());
		--_size;
		return true;

	}

	template<typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const Iterator& other) : _owner(other._owner), _index(other._index), _node(other._node)
	{
	}
	template<typename TKey, typename TData>
	inline size_t HashMap<TKey, TData>::LoadFactor()
	{
		return  (_size / _hashMap.Capacity());
	}
	

	template<typename TKey, typename TData>
	inline void GameEngine::HashMap<TKey, TData>::ReHash(size_t newCapacity)
	{
		Vector<PairType>v(_size);
		for (Iterator it = begin(); it != end(); ++it)
		{
			v.PushBack(*it);
		}
		for (size_t i = 0; i < _hashMap.Size(); ++i)
		{
			_hashMap.At(i).Clear();


		}
		if (newCapacity > _hashMap.Capacity())
		{
			_hashMap.Reserve(newCapacity);
		}
		_hashMap.Resize(newCapacity);
		_size = 0;
		for (size_t i = 0; i < v.Size(); ++i)
		{
			Insert(v.At(i));
		}
	}
	template<typename TKey, typename TData>
	inline std::size_t HashMap<TKey, TData>::Capacity() const
	{
		return _hashMap.Capacity();
	}


}
