#include "pch.h"
#include "JsonIntegerParseHelper.h"


namespace GameEngine
{
	RTTI_DEFINITIONS(JsonIntegerParseHelper, IJsonParseHelper)
		RTTI_DEFINITIONS(JsonIntegerParseHelper::SharedData, JsonParseCoordinator::SharedData)


#pragma  region SharedData
		JsonIntegerParseHelper::SharedData* JsonIntegerParseHelper::SharedData::Create() const { return new JsonIntegerParseHelper::SharedData(); }
	void JsonIntegerParseHelper::SharedData::Initialize()
	{
		JsonParseCoordinator::SharedData::Initialize();
		Data.Clear();

	}
#pragma endregion

#pragma region IntegerParseHelper		

	void JsonIntegerParseHelper::Initialize()
	{ 
		isInitialized = true;
		_isParsingData = false; 
		_startHandlerCount = 0;
		_endHandlerCount = 0;
		//_arrayElementCount = 0;
	}

	IJsonParseHelper* JsonIntegerParseHelper::Create() const { return new JsonIntegerParseHelper(); }

	bool JsonIntegerParseHelper::StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value)
	{
		if (value.isObject()) { return true; }
		JsonIntegerParseHelper::SharedData* customSharedData = sharedData.As<JsonIntegerParseHelper::SharedData>();
		if (customSharedData == nullptr) { return false; }
		if (key != _integerKey) { return false; }
		if (_isParsingData) { throw std::runtime_error("Received another element while parsing data"); }
		_isParsingData = true;
		++_startHandlerCount;
		customSharedData->Data.PushBack(value.asInt());
		return true;
	}

	bool JsonIntegerParseHelper::EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value&)
	{
		JsonIntegerParseHelper::SharedData* customSharedData = sharedData.As<JsonIntegerParseHelper::SharedData>();
		if (customSharedData == nullptr || !_isParsingData || key != _integerKey) { return false; }
		_isParsingData = false;
		++_endHandlerCount;
		return true;
	}

	std::size_t JsonIntegerParseHelper::GetStartHandlerCount() { return _startHandlerCount; }

	std::size_t JsonIntegerParseHelper::GetEndHandlerCount() { return _endHandlerCount; }

	//std::uint32_t JsonIntegerParseHelper::GetArrayElementCount() { return _arrayElementCount; }

#pragma  endregion
}