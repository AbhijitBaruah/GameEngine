
#include "pch.h"
#include "Datum.h"
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <glm/glm.hpp>
using namespace std;
namespace GameEngine
{
	const std::size_t Datum::DatumTypeSizes[] =
	{
		0,
		sizeof(std::int32_t),
		sizeof(float),
		sizeof(glm::vec4),
		sizeof(glm::mat4),
		sizeof(std::string),
		sizeof(RTTI*),
		sizeof(Scope*)

	};

	Datum::~Datum()
	{
		if (!_isExternal)
		{
			Clear();
			free(_data.vp);
		}

	}
	void Datum::Clear()
	{
		if (!_isExternal)
		{

			for (std::size_t i = _size; i > 0; --i)
			{
				PopBack();
			}

		}
	}
	Datum::Datum(std::int32_t value)
	{

		SetType(DatumTypes::Integer);
		Reserve(1);
		PushBack(value);

	}

	Datum::Datum(Scope* value)
	{
		SetType(DatumTypes::Table);
		Reserve(1);
		PushBack(value);

	}

	void Datum::PushBack(Scope* value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::Table);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 1);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::Table)
			{
				throw std::runtime_error("Cannot change datum type");
			}

			new(_data.t + _size++)Scope* (value);
		}
	}

	Scope& Datum::operator[](std::size_t index)
	{
		return *Get<Scope*>(index);
	}
	void Datum::Set(Scope* value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Table);

			if (!_isExternal && index>= _size)
			{
				Reserve(10);
			}

		}
		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::Table)
		{
			throw std::runtime_error("Invalid datum type");
		}
		/*if (!_isExternal)
		{
			++_size;
		}*/

		*(_data.t + index) = value;
	}
	Datum::Datum(float value)
	{

		SetType(DatumTypes::Float);
		Reserve(1);
		PushBack(value);

	}
	Datum::Datum(const std::string& value)
	{

		SetType(DatumTypes::String);
		Reserve(1);
		PushBack(value);

	}
	Datum::Datum(const glm::vec4& value)
	{

		SetType(DatumTypes::Vector);
		Reserve(1);
		PushBack(value);

	}

	Datum::Datum(const glm::mat4& value)
	{

		SetType(DatumTypes::Matrix);
		Reserve(1);
		PushBack(value);

	}
	Datum::Datum(RTTI* value)
	{

		SetType(DatumTypes::Pointer);
		Reserve(1);
		PushBack(value);

	}

	Datum::Datum(const Datum& rhs)
	{
		if (rhs._isExternal)
		{
			_data = rhs._data;
			_size = rhs._size;
			_capacity = rhs._capacity;
			_type = rhs._type;
			_isExternal = true;
		}
		if (!rhs._isExternal)
		{
			_type = rhs._type;
			Reserve(rhs._capacity);

			if (Type() != DatumTypes::String)
			{
				std::size_t size = Datum::DatumTypeSizes[static_cast<std::size_t>(_type)];
				std::memcpy(_data.vp, rhs._data.vp, rhs._size * size);
				_size = rhs._size;
			}
			else
			{
				for (std::size_t i = 0; i < rhs._size; ++i)
				{
					PushBack(rhs.Get<std::string>(i));
				}
			}
		}
	}

	Datum::Datum(Datum&& rhs) noexcept : _data{ rhs._data }, _size{ rhs._size }, _capacity{ rhs._capacity }, _type{ rhs._type }, _isExternal{ rhs._isExternal }
	{
		rhs._data.vp = nullptr;
		rhs._size = 0;
		rhs._capacity = 0;
		rhs._type = DatumTypes::Unknown;
	}

	Datum& Datum::operator=(Datum&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			free(_data.vp);
			_data = rhs._data;
			_size = rhs._size;
			_capacity = rhs._capacity;
			_type = rhs._type;
			_isExternal = rhs._isExternal;

			rhs._data.vp = nullptr;
			rhs._size = 0;
			rhs._capacity = 0;
			rhs._type = DatumTypes::Unknown;
		}
		return *this;
	}

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{

			if (!_isExternal)
			{
				Clear();
				free(_data.vp);
			}
			if (rhs._isExternal)
			{
				_data = rhs._data;
				_size = rhs._size;
				_capacity = rhs._capacity;
				_type = rhs._type;
				_isExternal = true;
			}
			if (!rhs._isExternal)
			{
				_type = rhs._type;
				Reserve(rhs._capacity);

				if (Type() != DatumTypes::String)
				{
					std::size_t size = Datum::DatumTypeSizes[static_cast<std::size_t>(_type)];
					std::memcpy(_data.vp, rhs._data.vp, rhs._size * size);
					_size = rhs._size;
				}
				else
				{
					for (std::size_t i = 0; i < rhs._size; ++i)
					{
						PushBack(rhs.Get<std::string>(i));
					}
				}

			}
		}

		return *this;
	}
	Datum& Datum::operator=(std::int32_t integer)
	{
		if (_isExternal)
		{
			throw std::runtime_error("cant reserve memory for external object");
		}
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Integer);
		}
		Clear();
		if (Type() == DatumTypes::Integer)
		{
			Reserve(1);
			PushBack(integer);
		}
		return *this;
	}
	Datum& Datum::operator=(float f)
	{
		if (_isExternal)
		{
			throw std::runtime_error("cant reserve memory for external object");
		}
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Float);
		}
		Clear();
		if (Type() == DatumTypes::Float)
		{
			Reserve(1);
			PushBack(f);
		}
		return *this;
	}
	Datum& Datum::operator=(const glm::vec4& v)
	{
		if (_isExternal)
		{
			throw std::runtime_error("cant reserve memory for external object");
		}
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Vector);
		}
		Clear();
		if (Type() == DatumTypes::Vector)
		{
			Reserve(1);
			PushBack(v);
		}
		return *this;
	}
	Datum& Datum::operator=(const glm::mat4& m)
	{
		if (_isExternal)
		{
			throw std::runtime_error("cant reserve memory for external object");
		}
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Matrix);
		}
		Clear();
		if (Type() == DatumTypes::Matrix)
		{
			Reserve(1);
			PushBack(m);
		}
		return *this;
	}
	Datum& Datum::operator=(const std::string& s)
	{
		if (_isExternal)
		{
			throw std::runtime_error("cant reserve memory for external object");
		}
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::String);
		}
		Clear();
		if (Type() == DatumTypes::String)
		{
			Reserve(1);
			PushBack(s);
		}
		return *this;
	}
	Datum& Datum::operator=(RTTI* p)
	{
		if (_isExternal)
		{
			throw std::runtime_error("cant reserve memory for external object");
		}
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Pointer);
		}
		Clear();
		if (Type() == DatumTypes::Pointer)
		{
			Reserve(1);
			PushBack(p);
		}
		return *this;
	}


	bool Datum::operator==(const Datum& rhs) const
	{
		if (_size != rhs._size || _capacity != rhs._capacity || _type != rhs._type || _isExternal != rhs._isExternal)
		{
			return false;
		}

		if (_type != DatumTypes::String && _type != DatumTypes::Pointer && _type != DatumTypes::Table)
		{
			std::size_t size = Datum::DatumTypeSizes[static_cast<std::size_t>(_type)];

			int a = std::memcmp(_data.vp, rhs._data.vp, _size * size);
			return(a == 0);


		}

		if (_type == DatumTypes::String)
		{
			for (std::size_t i = 0; i < _size; ++i)
			{
				if (*(_data.s + i) != *(rhs._data.s + i))
				{
					return false;
				}
			}
			return true;
		}
		if (_type == DatumTypes::Pointer || _type == DatumTypes::Table)
		{
			for (std::size_t i = 0; i < _size; ++i)
			{
				if ((_data.r[i]->Equals(rhs._data.r[i])) == false)
				{
					return false;
				}
			}
		}


		return true;


	}

	bool Datum::operator==(std::int32_t value) const
	{
		if (_size == 1)
		{
			return ((Front<std::int32_t>() == value));
		}
		return false;

	}

	bool Datum::operator==(float value) const
	{
		if (_size == 1)
		{
			return ((Front<float>() == value));
		}
		return false;

	}
	bool Datum::operator==(const glm::vec4& value) const
	{
		if (_size == 1)
		{
			return ((Front<glm::vec4>() == value));
		}
		return false;

	}
	bool Datum::operator==(const glm::mat4& value) const
	{
		if (_size == 1)
		{
			return ((Front<glm::mat4>() == value));
		}
		return false;

	}

	bool Datum::operator==(const std::string& value) const
	{
		if (_size == 1)
		{
			return ((Front<std::string>() == value));
		}
		return false;

	}

	bool Datum::operator==(RTTI* value) const
	{
		if (_size == 1)
		{
			return ((Front<RTTI*>()->Equals(value)));
		}
		return false;

	}


	bool Datum::operator!=(const Datum& rhs)
	{
		return !(*this == rhs);
	}
	bool Datum::operator!=(std::int32_t value)
	{
		return!(*this == value);

	}
	bool Datum::operator!=(float value)
	{
		return!(*this == value);

	}
	bool Datum::operator!=(const glm::vec4& value)
	{
		return!(*this == value);

	}
	bool Datum::operator!=(const glm::mat4& value)
	{
		return!(*this == value);

	}

	bool Datum::operator!=(const std::string& value)
	{
		return!(*this == value);

	}

	bool Datum::operator!=(RTTI* value)
	{
		return!(*this == value);
	}


	void Datum::SetStorage(std::int32_t* array, std::size_t size)
	{
		if ((Type() != DatumTypes::Integer && Type() != DatumTypes::Unknown && !_isExternal) || (!_isExternal && _size > 0))
		{
			throw std::runtime_error("Cant change Datum type");

		}
		SetStorage(array, size, DatumTypes::Integer);

	}
	void Datum::SetStorage(float* array, std::size_t size)
	{
		if ((Type() != DatumTypes::Float && Type() != DatumTypes::Unknown && !_isExternal) || (!_isExternal && _size > 0))
		{
			throw std::runtime_error("Cant change Datum type");

		}

		SetStorage(array, size, DatumTypes::Float);
	}
	void Datum::SetStorage(std::string* array, std::size_t size)
	{
		if ((Type() != DatumTypes::String && Type() != DatumTypes::Unknown && !_isExternal) || (!_isExternal && _size > 0))
		{
			throw std::runtime_error("Cant change Datum type");

		}

		SetStorage(array, size, DatumTypes::String);

	}

	void Datum::SetStorage(glm::vec4* array, std::size_t size)
	{
		if ((Type() != DatumTypes::Vector && Type() != DatumTypes::Unknown && !_isExternal) || (!_isExternal && _size > 0))
		{
			throw std::runtime_error("Cant change Datum type");

		}
		SetStorage(array, size, DatumTypes::Vector);

	}
	void Datum::SetStorage(glm::mat4* array, std::size_t size)
	{
		if ((Type() != DatumTypes::Matrix && Type() != DatumTypes::Unknown && !_isExternal) || (!_isExternal && _size > 0))
		{
			throw std::runtime_error("Cant change Datum type");

		}
		SetStorage(array, size, DatumTypes::Matrix);

	}

	void Datum::SetStorage(RTTI** array, std::size_t size)
	{
		if ((Type() != DatumTypes::Pointer && Type() != DatumTypes::Unknown && !_isExternal) || (!_isExternal && _size > 0))
		{
			throw std::runtime_error("Cant change Datum type");

		}
		SetStorage(array, size, DatumTypes::Pointer);


	}

	void Datum::SetFromString(const std::string& string, std::size_t index)
	{

		switch (auto r = Type())
		{
		case GameEngine::DatumTypes::Integer:
			Set(std::stoi(string), index);
			break;
		case GameEngine::DatumTypes::Float:
			Set(std::stof(string), index);
			break;
		case GameEngine::DatumTypes::Vector:
			float vector[4];
			sscanf_s(string.c_str(), "vec4(%f,%f,%f,%f)", &vector[0], &vector[1], &vector[2], &vector[3]);
			glm::vec4 v{ vector[0],vector[1],vector[2],vector[3] };
			Set(v, index);
			break;
		case GameEngine::DatumTypes::Matrix:
			float matrix[16];
			sscanf_s(string.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &matrix[0], &matrix[1], &matrix[2], &matrix[3], &matrix[4], &matrix[5], &matrix[6], &matrix[7],
				&matrix[8], &matrix[9], &matrix[10], &matrix[11], &matrix[12], &matrix[13], &matrix[14], &matrix[15]);
			glm::mat4 m{ matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7],
				matrix[8], matrix[9], matrix[10], matrix[11], matrix[12], matrix[13], matrix[14], matrix[15] };
			Set(m, index);
			break;
		case GameEngine::DatumTypes::String:
			Set(string, index);
			break;
		default:
			throw std::runtime_error("Not valid type");
		}

	}

	std::string Datum::ToString(std::size_t index)
	{
		switch (auto r = Type())
		{
		case GameEngine::DatumTypes::Integer:
			return std::to_string(Get<std::int32_t>(index));
			break;
		case GameEngine::DatumTypes::Float:
			return std::to_string(Get<float>(index));
			break;
		case GameEngine::DatumTypes::Vector:
			return glm::to_string(Get<glm::vec4>(index));
			break;
		case GameEngine::DatumTypes::Matrix:
			return glm::to_string(Get<glm::mat4>(index));
			break;
		case GameEngine::DatumTypes::String:
			return Get<std::string>(index);
			break;
		default:
			throw std::runtime_error("Not valid type");
		}

	}

	void Datum::Resize(std::size_t newSize)
	{
		if (!_isExternal)
		{

			if (Type() != DatumTypes::Unknown)
			{
				if (newSize > _capacity)
				{
					Reserve(newSize);
					if (Type() == DatumTypes::String)
					{
						for (std::size_t i = _size; i < newSize; ++i)
						{
							new(_data.s + i)std::string("");
						}
					}
					_size = newSize;
					_capacity = newSize;
				}
				else
				{

					ShrinkToFit(newSize);
					_size = newSize;
				}
			}
		}
	}

	void Datum::ShrinkToFit(std::size_t newSize)
	{
		if (!_isExternal)
		{
			if (_size > newSize)
			{
				for (std::size_t i = _size; i > newSize; --i)
				{
					PopBack();
				}

			}
			_capacity = newSize;
		}
	}
	void Datum::SetType(DatumTypes d)
	{
		if (_type == DatumTypes::Unknown || _isExternal)
		{
			_type = d;
		}
	}

	void Datum::Reserve(std::size_t capacity)
	{
		if (!_isExternal)
		{
			if (Type() != DatumTypes::Unknown)
			{
				if (_capacity < capacity)
				{
					std::size_t size = Datum::DatumTypeSizes[static_cast<std::size_t>(_type)];
					assert(size != 0);
					void* data = realloc(_data.vp, capacity * size);

					assert(data != nullptr);
					_data.vp = data;
					_capacity = capacity;
				}
			}
		}
	}

	void Datum::RemoveAt(std::size_t index)
	{
		if (index > _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		std::size_t size = Datum::DatumTypeSizes[static_cast<std::size_t>(_type)];

		if (Type() == DatumTypes::String)
		{
			(_data.s + index)->~basic_string();
		}
		uint8_t* Onesize = reinterpret_cast<uint8_t*>(_data.vp);
		memmove(Onesize + (size * index), (Onesize +  ((index+1)*size)), (size*(_size-index-1)));
		--_size;


	}
	void Datum::Set(std::int32_t value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Integer);
			if (!_isExternal)
			{
				Reserve(10);
			}
		}

		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::Integer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		if (!_isExternal)
		{
			++_size;
		}
		*(_data.i + index) = value;

	}
	void Datum::Set(float value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Float);
			if (!_isExternal)
			{
				Reserve(10);
			}
		}

		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::Float)
		{
			throw std::runtime_error("Invalid datum type");
		}
		if (!_isExternal)
		{
			++_size;
		}
		*(_data.f + index) = value;
	}
	void Datum::Set(const glm::vec4& value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Vector);
			if (!_isExternal)
			{
				Reserve(10);
			}
		}
		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::Vector)
		{
			throw std::runtime_error("Invalid datum type");
		}
		if (!_isExternal)
		{
			++_size;
		}
		*(_data.v + index) = value;
	}
	void Datum::Set(const glm::mat4& value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Matrix);
			if (!_isExternal)
			{
				Reserve(10);
			}
		}

		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::Matrix)
		{
			throw std::runtime_error("Invalid datum type");
		}
		if (!_isExternal)
		{
			++_size;
		}
		*(_data.m + index) = value;
	}

	void Datum::Set(const std::string& value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::String);
			if (!_isExternal)
			{
				Reserve(10);
			}
		}

		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::String)
		{
			throw std::runtime_error("Invalid datum type");
		}
		if (!_isExternal)
		{
			new(_data.s + _size++)std::string(value);
		}
		else
		{

			*(_data.s + index) = value;
		}
	}

	void Datum::Set(RTTI* value, std::size_t index)
	{
		if (Type() == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Pointer);

			if (!_isExternal)
			{
				Reserve(10);
			}

		}
		if (index >= _capacity)
		{
			throw std::out_of_range("Index passed is greater than size");
		}

		if (Type() != DatumTypes::Pointer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		if (!_isExternal)
		{
			++_size;
		}

		*(_data.r + index) = value;
	}

	void Datum::PushBack(std::int32_t value)
	{

		if (!_isExternal)
		{

			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::Integer);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::Integer)
			{
				throw std::runtime_error("Cannot change datum type");
			}


			new(_data.i + _size++)std::int32_t(value);
		}
	}

	void Datum::PushBack(float value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::Float);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}

			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::Float)
			{
				throw std::runtime_error("Cannot change datum type");
			}

			new(_data.f + _size++)float(value);
		}
	}

	void Datum::PushBack(const glm::vec4& value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::Vector);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::Vector)
			{
				throw std::runtime_error("Cannot change datum type");
			}
			new(_data.v + _size++)glm::vec4(value);
		}
	}

	void Datum::PushBack(const glm::mat4& value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::Matrix);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::Matrix)
			{
				throw std::runtime_error("Cannot change datum type");
			}


			new(_data.m + _size++)glm::mat4(value);
		}
	}

	void Datum::PushBack(const std::string& value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::String);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::String)
			{
				throw std::runtime_error("Cannot change datum type");
			}
			new(_data.s + _size++)std::string(value);
		}
	}

	void Datum::PushBack(RTTI* value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::Pointer);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::Pointer)
			{
				throw std::runtime_error("Cannot change datum type");
			}


			new(_data.r + _size++)RTTI* (value);
		}
	}

	void Datum::PushBack(const std::string&& value)
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::Unknown)
			{
				SetType(DatumTypes::String);
			}
			if (_size == _capacity)
			{
				Reserve(_capacity + 10);
			}
			if (Type() != DatumTypes::Unknown && Type() != DatumTypes::String)
			{
				throw std::runtime_error("Cannot change datum type");
			}
			new(_data.s + _size++)std::string(std::move(value));
		}

	}

	void Datum::PopBack()
	{
		if (!_isExternal)
		{
			if (Type() == DatumTypes::String)
			{
				(_data.s + _size - 1)->~basic_string();

			}
			--_size;
		}

	}




	bool Datum::Remove(std::int32_t obj)
	{
		std::pair<bool, std::size_t> s1 = Find(obj);
		if (s1.first)
		{
			RemoveAt(s1.second);
			return true;

		}

		return false;
	}

	bool Datum::Remove(float obj)
	{
		std::pair<bool, std::size_t> s1 = Find(obj);
		if (s1.first)
		{
			RemoveAt(s1.second);
			return true;
		}
		return false;
	}

	bool Datum::Remove(const glm::vec4& obj)
	{
		std::pair<bool, std::size_t> s1 = Find(obj);
		if (s1.first)
		{
			RemoveAt(s1.second);
			return true;
		}
		return false;
	}
	bool Datum::Remove(const glm::mat4& obj)
	{
		std::pair<bool, std::size_t> s1 = Find(obj);
		if (s1.first)
		{
			RemoveAt(s1.second);
			return true;
		}
		return false;
	}
	bool Datum::Remove(const std::string& obj)
	{
		std::pair<bool, std::size_t> s1 = Find(obj);
		if (s1.first)
		{
			RemoveAt(s1.second);
			return true;
		}
		return false;
	}
	bool Datum::Remove(RTTI* obj)
	{
		std::pair<bool, std::size_t> s1 = Find(obj);
		if (s1.first)
		{
			RemoveAt(s1.second);
			return true;
		}
		return false;
	}

	std::pair<bool, std::size_t> Datum::Find(std::int32_t obj)
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			if (*(_data.i + i) == obj)
			{
				return std::make_pair(true, i);
			}
		}

		return std::make_pair(false, 0);
	}
	std::pair<bool, std::size_t> Datum::Find(float obj)
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			if (*(_data.f + i) == obj)
			{
				return std::make_pair(true, i);
			}
		}

		return std::make_pair(false, 0);
	}
	std::pair<bool, std::size_t> Datum::Find(const glm::vec4& obj)
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			if (*(_data.v + i) == obj)
			{
				return std::make_pair(true, i);
			}
		}

		return std::make_pair(false, 0);
	}
	std::pair<bool, std::size_t> Datum::Find(const glm::mat4& obj)
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			if (*(_data.m + i) == obj)
			{
				return std::make_pair(true, i);
			}
		}

		return std::make_pair(false, 0);
	}
	std::pair<bool, std::size_t> Datum::Find(const std::string& obj)
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			if (*(_data.s + i) == obj)
			{
				return std::make_pair(true, i);
			}
		}

		return std::make_pair(false, 0);
	}
	std::pair<bool, std::size_t> Datum::Find(RTTI* obj)
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			if (*(_data.r + i) == obj)
			{
				return std::make_pair(true, i);
			}
		}

		return std::make_pair(false, 0);
	}


	void Datum::SetStorage(void* vp, std::size_t size, DatumTypes type)
	{
		if (Type() == DatumTypes::Unknown || _isExternal)
		{
			SetType(type);
		}
		if (!_isExternal)
		{
			free(_data.vp);
			_isExternal = true;
		}
		_data.vp = vp;
		_size = _capacity = size;

	}
}