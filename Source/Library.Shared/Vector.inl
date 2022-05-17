#include "Vector.h"
#include <assert.h>

namespace GameEngine
{
	template<typename T>
	Vector<T>::Vector(size_t Capacity) : _capacity{ Capacity }
	{
		Reserve(Capacity);
	}
	template<typename T>
	Vector<T>::Vector(std::initializer_list<T> list)
	{
		for (const auto& value : list)
		{
			PushBack(value);
		}
	}
	template<typename T>
	Vector<T>::~Vector()
	{
		Clear();
		free(_data);

	}
	template<typename T>
	Vector<T>::Vector(const Vector& other)
	{
		_capacity = other._capacity;
		Reserve(other._capacity);
		for (size_t i = 0; i < other._size; ++i)
		{
			PushBack(other._data[i]);
		}
	}
	template<typename T>
	Vector<T>::Vector(Vector&& other) noexcept :
		_data{ other._data },
		_size{ other._size },
		_capacity{ other._capacity }
	{
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			_capacity = rhs._capacity;
			Reserve(rhs._capacity);
			for (size_t i = 0; i < rhs._size; ++i)
			{
				PushBack(rhs._data[i]);
			}
		}
		return *this;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			free(_data);

			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;

			other._data = nullptr;
			other._size = other._capacity = 0u;
		}

		return *this;
	}
	template<typename T>
	T& Vector<T>::operator[](size_t index)
	{
		if (index > _size)
		{
			throw std::runtime_error("Invalid index, Index is greater than size of Vector");
		}
		return _data[index];
	}

	template<typename T>
	const T& Vector<T>::operator[](size_t index) const
	{
		if (index > _size)
		{
			throw std::runtime_error("Invalid index, Index is greater than size of Vector");
		}
		return _data[index];
	}

	template<typename T>
	T& Vector<T>::At(size_t index)
	{
		if (index > _size)
		{
			throw std::runtime_error("Invalid index, Index is greater than size of Vector");
		}
		return _data[index];
	}

	template<typename T>
	const T& Vector<T>::At(size_t index) const
	{
		if (index > _size)
		{
			throw std::runtime_error("Invalid index, Index is greater than size of Vector");
		}
		return _data[index];
	}

	template<typename T>
	void Vector<T>::PopBack()
	{
		--_size;
		(_data + _size)-> ~T();

	}

	template<typename T>
	bool Vector<T>::isEmpty() const
	{
		return _size == 0;
	}

	template<typename T>
	T& Vector<T>::Front()
	{
		return _data[0];
	}

	template<typename T>
	const T& Vector<T>::Front() const
	{
		return _data[0];
	}
	template<typename T>
	T& Vector<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Vector is empty");
		}
		return _data[_size - 1];
	}

	template<typename T>
	const T& Vector<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Vector is empty");
		}
		return _data[_size - 1];
	}
	template<typename T>
	inline void Vector<T>::Resize(size_t size)
	{

		if (size < _size)
		{
			for (size_t i = size; i < _size;++i)
			{
				(_data + i)->~T();
			}
			_size = size;
			ShrinkToFit();
		}

		else if(size<_capacity)
		{
			
			for (size_t i = _size; i < size; ++i)
			{
				new (_data + i)T();
			}
			_size = size;
		}
		else
		{
			_capacity = size;
			
			for (size_t i = _size; i < _capacity; ++i)
			{
				new (_data + i)T();
			}
			
			_size = _capacity;
		}

	}
	template<typename T>
	size_t Vector<T>::Size() const
	{
		return _size;
	}
	template<typename T>
	size_t Vector<T>::Capacity() const
	{
		return _capacity;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& value)
	{
		if (_size >= _capacity)
		{
			if (_capacity > 0)_capacity = _capacity * 2;
			else _capacity = 10;
			Reserve(_capacity);
		}

		new(_data + _size++)T(value);

		return Iterator{ *this, (_size - 1) };
	}
	template<typename T>
	void Vector<T>::Clear()
	{
		while (_size > 0)
		{
			PopBack();
		}


	}

	template<typename T>
	void Vector<T>::Reserve(size_t capacity)
	{
		if (capacity <= 0)return;
		if (capacity < _capacity)
		{
			throw std::runtime_error("Cannot shrink the vector");
		}
		_capacity = capacity;

		_data = reinterpret_cast <T*>(std::realloc(_data, sizeof(T) * capacity));


	}

	template<typename T>
	void Vector<T>::Remove(const T& value)
	{
		Iterator it = Find(value);
		(_data + it._index)->~T();
		std::memmove(_data + it._index, (_data + it._index + 1), sizeof(T) * (_size - it._index));
		--_size;
	}

	template<typename T>
	void Vector<T>::Remove(const Iterator& it1, const Iterator& it2)
	{
		if (it1._owner != this || it2._owner != this)
		{
			return;
		}

		else if (it1._index > it2._index)
		{
			return;
		}
		size_t loopTimes = it2._index - it1._index;


		for (size_t i = it1._index; i < it2._index; ++i)
		{
			(_data + i)-> ~T();
		}



		std::memmove(_data + it1._index, (_data + (it2._index)), sizeof(T) * (_size - it2._index));
		_size = _size - loopTimes;
	}
	template <typename T>
	Vector<T>::Iterator::Iterator(const Vector& vector, size_t index) : _owner(&vector), _index(index)
	{
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return (_owner != other._owner || _index != other._index);
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return !operator!=(other);
	}


	template<typename T>
	inline T& Vector<T>::Iterator::operator*()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("De referencing invalid index");
		}
		return (_owner->_data[_index]);
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
	{
		Iterator copy = *this;
		operator--();
		return copy;
	}

	template<typename T>
	typename inline Vector<T>::Iterator& Vector<T>::Iterator::operator--()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		else if(_index>0)
		{
			--_index;

		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		else
		{
			++_index;

		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator copy = *this;
		operator++();
		return copy;
	}


	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value, std::function<bool(const T&, const T&)> equalityFunctor)
	{
		Iterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
			{
				break;
			}
		}
		return it;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::begin()
	{
		return  Iterator{ *this, 0 };
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator{ *this, _size };
	}
	template <typename T>
	Vector<T>::ConstIterator::ConstIterator(const Vector& vector, size_t index) : _owner(&vector), _index(index)
	{
	}

	template<typename T>
	Vector<T>::ConstIterator::ConstIterator(const Iterator& other) : _owner(other._owner), _index(other._index)
	{
	}
	
	template<typename T>
	inline void Vector<T>::RemoveAt(std::size_t index)
	{
		(_data + index)->~T();
		std::memmove(_data + index, (_data + index+ 1), sizeof(T) * (_size - index));
		--_size;
	}
	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return   ConstIterator{ *this,0 };
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return   ConstIterator{ *this,0 };
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::cend() const
	{
		return   ConstIterator{ *this,_size };
	}


	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		return ConstIterator{ *this,_size };
	}
	template <typename T>
	bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		if (_owner != other._owner)
		{
			return true;
		}
		else
		{
			return !(_index == other._index);
		}
	}

	template <typename T>
	bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !operator!=(other);
	}

	template<typename T>
	inline const T& Vector<T>::ConstIterator::operator*() const
	{
		if (_owner == nullptr || _index == _owner->_size)
		{
			throw std::runtime_error("De referencing invalid index");
		}
		return (_owner->_data[_index]);
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		else if (_index > 0)
		{
			--_index;

		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int)
	{
		ConstIterator copy = *this;
		operator--();
		return copy;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot access empty list");
		}
		else
		{
			++_index;

		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator copy = *this;
		operator++();
		return copy;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::Find(const T& value, std::function<bool(const T&, const T&)> equalityFunctor) const
	{
		ConstIterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
			{
				break;
			}
		}
		return it;
	}

	template<typename T>
	void Vector<T>::ShrinkToFit()
	{
		if (_size == 0)
		{
			_data = reinterpret_cast<T*>( realloc(_data, 0));
			_capacity = _size;
			return;
		}
		if (_capacity > _size)
		{
			T* data = reinterpret_cast<T*>(realloc(_data, sizeof(T) *_size));
			assert(data != nullptr);
			_data = data;
			_capacity =_size;
		}
		
	}

}