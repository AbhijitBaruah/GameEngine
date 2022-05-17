#include "pch.h"
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"
#include <fstream>

namespace GameEngine
{
#pragma region SharedData
	RTTI_DEFINITIONS(JsonParseCoordinator::SharedData, RTTI)

		inline void JsonParseCoordinator::SharedData::IncrementDepth() { ++_depth; }
	inline void JsonParseCoordinator::SharedData::DecrementDepth() { --_depth; }
	inline void JsonParseCoordinator::SharedData::SetJsonParseCoordinator(JsonParseCoordinator* coordinator) { _owner = coordinator; }
	void JsonParseCoordinator::SharedData::Initialize() { _depth = 0; }
	std::size_t JsonParseCoordinator::SharedData::Depth() { return _depth; }
	std::size_t JsonParseCoordinator::SharedData::MaxDepth() { return _maxDepth; }
	JsonParseCoordinator* JsonParseCoordinator::SharedData::GetJsonParseCoordinator() { return _owner; }


#pragma  endregion
#pragma  region JsonCoordinator
	JsonParseCoordinator::~JsonParseCoordinator()
	{
		if (_isClone)
		{
			Cleanup();
		}
	}
	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& rhs) noexcept : _sharedData{ std::move(rhs._sharedData) }, _parseHelpers{ std::move(rhs._parseHelpers) }, _isClone{ rhs._isClone }
	{
		_sharedData->_owner = this;
	}
	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& rhs) noexcept
	{
		if (this != &rhs)
		{
			if (_isClone)
			{
				Cleanup();
			}
			else
			{
				_parseHelpers.Clear();
			}
			_sharedData = std::move(rhs._sharedData);
			_parseHelpers = std::move(rhs._parseHelpers);
			_sharedData->_owner = this;
			_isClone = rhs._isClone;

		}
		return *this;
	}
	JsonParseCoordinator::JsonParseCoordinator(SharedData& sharedData)
	{
		SetSharedData(&sharedData);
	}

	JsonParseCoordinator::SharedData* JsonParseCoordinator::GetSharedData() { return _sharedData; }

	inline void JsonParseCoordinator::SetSharedData(SharedData* sharedData)
	{
		if (sharedData != nullptr)
		{
			_sharedData = sharedData;
			_sharedData->Initialize();
			_sharedData->SetJsonParseCoordinator(this);
		}
	}

	void JsonParseCoordinator::AddHelper(IJsonParseHelper& helperToAdd)
	{
		if (_isClone) { throw std::runtime_error("Cannot add helpers to a cloned coordinator"); }
		{
			_parseHelpers.PushBack(&helperToAdd);
		}
	}

	bool JsonParseCoordinator::RemoveHelper(IJsonParseHelper& helperToRemove)
	{
		if (_isClone) { throw std::runtime_error("Cannot add helpers to a cloned coordinator"); }
		auto vectorIterator = _parseHelpers.Find(&helperToRemove);
		if (vectorIterator != _parseHelpers.end()) { _parseHelpers.Remove(&helperToRemove); }
		return (vectorIterator == _parseHelpers.end());
	}

	void JsonParseCoordinator::Parse(Json::String& parseString)
	{
		std::stringstream inputStream;
		inputStream << parseString;
		Parse(inputStream);
	}

	void JsonParseCoordinator::ParseFromFile(std::string& fileName)
	{
		std::ifstream fileStream(fileName, std::ifstream::binary);
		Parse(fileStream);
	}
	void JsonParseCoordinator::Parse(std::istream& data)
	{
		Json::Value _root;
		data >> _root;
		_sharedData->IncrementDepth();
		ParseMembers(_root);
		_sharedData->DecrementDepth();
	}
	void JsonParseCoordinator::Parse(std::pair<const std::string&, Json::Value> members)
	{
		auto [memberName, memberValue] = members;
		if (memberValue.isArray())
		{
			for (Json::Value::ArrayIndex i = 0; i < memberValue.size(); ++i)
			{
				for (const auto& helper : _parseHelpers)
				{
					if (helper->StartHandler(*_sharedData, memberName, memberValue[i]))
					{
						if (memberValue[i].isObject())
						{
							_sharedData->IncrementDepth();
							ParseMembers(memberValue[i]);
							_sharedData->DecrementDepth();
						}

						helper->EndHandler(*_sharedData, memberName, memberValue[i]);
						break;
					}
				}

			}
		}
		else
		{
			for (const auto& helper : _parseHelpers)
			{
				if (helper->StartHandler(*_sharedData, memberName, memberValue))
				{
					if (memberValue.isObject())
					{
						_sharedData->IncrementDepth();
						ParseMembers(memberValue);
						_sharedData->DecrementDepth();
					}

					helper->EndHandler(*_sharedData, memberName, memberValue);
					break;
				}
			}
		}
	}
	void JsonParseCoordinator::ParseMembers(Json::Value& value)
	{
		const auto memberNames = value.getMemberNames();

		_sharedData->_maxDepth++;
		for (const auto& memberName : memberNames)
		{
			auto& valueToParse = value[memberName];
			Parse(std::make_pair(memberName, valueToParse));
		}
	}
	JsonParseCoordinator* JsonParseCoordinator::Clone()
	{
		auto clone = new JsonParseCoordinator(*_sharedData->Create());
		clone->_isClone = true;
		for (auto& helper : _parseHelpers)
		{
			clone->_parseHelpers.PushBack(helper->Create());
		}
		return clone;
	}
	const Vector<IJsonParseHelper*>& JsonParseCoordinator::GetParseHelpers() const { return _parseHelpers; }

	void JsonParseCoordinator::Cleanup()
	{
		for (auto& helper : _parseHelpers)
		{
			delete helper;
		}
		delete _sharedData;
	}

	bool JsonParseCoordinator::IsClone()
	{
		return _isClone;
	}

#pragma endregion
}