#include "pch.h"
#include "TableParserHelper.h"
#include "GameObject.h"
namespace GameEngine
{
	RTTI_DEFINITIONS(TableParserHelper, IJsonParseHelper)
		RTTI_DEFINITIONS(TableParserHelper::SharedData, JsonParseCoordinator::SharedData)


#pragma  region SharedData

		TableParserHelper::SharedData* TableParserHelper::SharedData::Create()const { return new TableParserHelper::SharedData(); }
	TableParserHelper::SharedData::SharedData(Scope* rootScope)
	{
		if (_root == nullptr)
		{
			if (rootScope == nullptr)
			{
				_root = new Scope;
			}
			else
			{
				_root = rootScope;
			}
		}
		Initialize();
	}

	TableParserHelper::SharedData::~SharedData()
	{
		Cleanup();
	}
	void TableParserHelper::SharedData::Initialize()
	{
		JsonParseCoordinator::SharedData::Initialize();

	}
	void TableParserHelper::SharedData::Cleanup()
	{
		delete _root;
	}
#pragma endregion

#pragma  region TableParseHelper

	TableParserHelper::TableParserHelper()
	{

		Initialize();
	}

	TableParserHelper::~TableParserHelper()
	{
		Cleanup();
	}

	void TableParserHelper::Initialize()
	{
		if (!isInitialized)
		{
			IJsonParseHelper::Initialize();
			_isParsingData = false;
			_stringDatumMap.Insert(std::make_pair("integer", DatumTypes::Integer));
			_stringDatumMap.Insert(std::make_pair("float", DatumTypes::Float));
			_stringDatumMap.Insert(std::make_pair("vector", DatumTypes::Vector));
			_stringDatumMap.Insert(std::make_pair("matrix", DatumTypes::Matrix));
			_stringDatumMap.Insert(std::make_pair("string", DatumTypes::String));
			_stringDatumMap.Insert(std::make_pair("table", DatumTypes::Table));
			_stringDatumMap.Insert(std::make_pair("pointer", DatumTypes::Pointer));
			isInitialized = true;
		}
	}

	IJsonParseHelper* TableParserHelper::Create() const { return new TableParserHelper(); }

	bool TableParserHelper::StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value)
	{
		TableParserHelper::SharedData* customSharedData = sharedData.As<TableParserHelper::SharedData>();
		if (customSharedData == nullptr) { return false; }

		Scope* currentScopeContext;
		if (!_contextStack.isEmpty()) { currentScopeContext = _contextStack.Back().currentScope; }
		else { currentScopeContext = customSharedData->_root; }
		if (value.isObject())
		{
			_arrayIndex = 0;
			if (key != _valueKey && key != _classKey)
			{
				_contextStack.PushBack(ContextFrame{ key, currentScopeContext });
				currentScopeContext->Append(key);
			}
			else
			{
				Scope* derivedScope = Factory<Scope>::Create(value["class"].asString());
				assert(derivedScope != nullptr);
				assert((_contextStack.Back().key == _childrenKey && derivedScope->As<GameObject>() != nullptr) || (_contextStack.Back().key != _childrenKey));
				_contextStack.Back().currentScope->Adopt(*derivedScope, _contextStack.Back().key);
				_contextStack.PushBack(ContextFrame{ _contextStack.Back().key,derivedScope });
			}

		}
		else
		{
			if ((key != _valueKey) && (key != _typeKey) && (key != _classKey)) { return false; }
			auto& parentScope = *currentScopeContext;
			auto& datumName = _contextStack.Back().key;
			auto& datum = *parentScope.Find(datumName);
			if (key == _typeKey)
			{
				auto [mapIterator, wasFound] = _stringDatumMap.Find(value.asString());
				auto [datumKey, datumType] = *mapIterator;
				datum.SetType(datumType);
				_arrayIndex = 0;
			}

			if (key == _valueKey)
			{
				if (!datum.IsExternal())
				{

					datum.PushBackFromString(value.asString());

				}
				else
				{
					if (datum.Type() != DatumTypes::Pointer)
					{
						datum.SetFromString(value.asString(), _arrayIndex);
					}
					++_arrayIndex;
				}
			}
		}
		_isParsingData = true;
		return true;

	}
	bool TableParserHelper::EndHandler(JsonParseCoordinator::SharedData&, const std::string& key, const Json::Value& value)
	{
		if (key != _typeKey && key != _classKey)
		{
			if (key == _valueKey && (!value.isObject()))
			{
				return true;
			}
			else
			{
				_contextStack.PopBack();
			}
		}
		return true;
	}

	//What does cleanup do?
	void TableParserHelper::Cleanup()
	{
	}



#pragma endregion

}