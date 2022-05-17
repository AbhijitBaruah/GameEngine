#pragma once
#include "RTTI.h"
#include "IJsonParseHelper.h"
#include <cstdint>
#include <string>
namespace GameEngine 
{
	class JsonIntegerParseHelper : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonIntegerParseHelper);

	public:
		class SharedData final : public GameEngine::JsonParseCoordinator::SharedData
		{
			friend JsonIntegerParseHelper;
			RTTI_DECLARATIONS(SharedData);
		public:
			virtual void Initialize() override;
			virtual SharedData* Create() const override;
			Vector<std::int32_t> Data;
			std::size_t _maxDepth{ 0 };

		};


		virtual void Initialize() override;
		virtual IJsonParseHelper* Create() const override;
		virtual bool StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) override;

		virtual bool EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key,const Json::Value&) override;
		std::size_t GetStartHandlerCount();
		std::size_t GetEndHandlerCount();
		//std::uint32_t GetArrayElementCount();
		bool isInitialized{ false };
	private:
		inline static const std::string _integerKey = "integer";
		bool _isParsingData{ false };
		
		 std::size_t _startHandlerCount{ 0 };
		 std::size_t _endHandlerCount{ 0 };
		// std::uint32_t _arrayElementCount{ 0 };
	};


}
