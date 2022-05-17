#include "Datum.h"
namespace GameEngine
{
	inline size_t Datum::Size()const
	{
		return _size;
	}
	inline DatumTypes Datum::Type() const
	{
		return _type;
	}

	inline bool Datum::IsExternal() const
	{
		return _isExternal;
	}

	inline size_t Datum::Capacity() const
	{
		return _capacity;
	}

	template<>
	inline  const std::string& Datum::Get<std::string>(std::size_t index)const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::String)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.s + index);
	}
	template<>
	inline std::int32_t& Datum::Get<std::int32_t>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Integer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.i + index);

	}
	template<>
	inline Scope*& Datum::Get<Scope*>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Table)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.t + index);

	}
	template<>
	inline float& Datum::Get<float>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Float)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.f + index);

	}

	template<>
	inline std::string& Datum::Get<std::string>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::String)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.s + index);

	}
	

	template<>
	inline glm::vec4& Datum::Get<glm::vec4>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Vector)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.v + index);

	}

	template<>
	inline  glm::mat4& Datum::Get<glm::mat4>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Matrix)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.m + index);

	}

	template<>
	inline RTTI*& Datum::Get<RTTI*>(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Pointer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.r + index);

	}
	template<>
	inline RTTI* const& Datum::Get<RTTI*>(std::size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Pointer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.r + index);

	}
	template<>
	inline Scope* const& Datum::Get<Scope*>(std::size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Table)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.t + index);

	}

	template<>
	inline  const std::int32_t& Datum::Get<std::int32_t>(std::size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Integer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.i + index);

	}

	template<>
	inline  const float& Datum::Get<float>(std::size_t index)const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Float)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.f + index);

	}



	template<>
	inline const glm::vec4& Datum::Get<glm::vec4>(std::size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Vector)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.v + index);

	}

	template<>
	inline const glm::mat4& Datum::Get<glm::mat4>(std::size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index passed is greater than size");
		}
		if (Type() != DatumTypes::Matrix)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return *(_data.m + index);
	}

	inline void Datum::PushBackFromString(const std::string& string)
	{
		switch (auto r = Type())
		{
		case GameEngine::DatumTypes::Integer:
			PushBack(std::stoi(string));
			break;
		case GameEngine::DatumTypes::Float:
			PushBack(std::stof(string));
			break;
		case GameEngine::DatumTypes::Vector:
			float vector[4];
			sscanf_s(string.c_str(), "vec4(%f,%f,%f,%f)", &vector[0], &vector[1], &vector[2], &vector[3]);
			glm::vec4 v{ vector[0],vector[1],vector[2],vector[3] };
			PushBack(v);
			break;
		case GameEngine::DatumTypes::Matrix:
			float matrix[16];
			sscanf_s(string.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &matrix[0], &matrix[1], &matrix[2], &matrix[3], &matrix[4], &matrix[5], &matrix[6], &matrix[7],
				&matrix[8], &matrix[9], &matrix[10], &matrix[11], &matrix[12], &matrix[13], &matrix[14], &matrix[15]);
			glm::mat4 m{ matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7],
				matrix[8], matrix[9], matrix[10], matrix[11], matrix[12], matrix[13], matrix[14], matrix[15] };
			PushBack(m);
			break;
		case GameEngine::DatumTypes::String:
			PushBack(string);
			break;
		default:
			throw std::runtime_error("Not valid type");
		}
	}


	template<>
	inline std::int32_t& Datum::Front<std::int32_t>()
	{
		if ( _type != DatumTypes::Integer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		
			return (*_data.i);
		
		
	}

	template<>
	inline float& Datum::Front<float>()
	{
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.f);
	}

	template<>
	inline glm::vec4& Datum::Front<glm::vec4>()
	{
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.v);
	}


	template<>
	inline glm::mat4& Datum::Front<glm::mat4>()
	{
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.m);
	}

	template<>
	inline std::string& Datum::Front<std::string>()
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.s);
	}

	template<>
	inline RTTI*& Datum::Front<RTTI*>()
	{
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.r);
	}

	template<>
	inline  RTTI* const & Datum::Front<RTTI*>() const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.r);
	}

	template<>
	inline const std::int32_t& Datum::Front<std::int32_t>() const
	{
		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.i);
	}

	template<>
	inline const float& Datum::Front<float>() const
	{
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.f);
	}

	template<>
	inline const glm::vec4& Datum::Front<glm::vec4>() const
	{
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.v);
	}

	template<>
	inline const glm::mat4& Datum::Front<glm::mat4>() const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.m);
	}
	
	template<>
	inline const std::string& Datum::Front<std::string>() const
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Invalid datum type");
		}
		return (*_data.s);
	}


}