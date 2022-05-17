#pragma once
#include "RTTI.h"
#include "IJsonParseHelper.h"
#include <cstdint>
#include <string>
#include "Scope.h"
#include "Stack.h"
#include "HashMap.h"
#include "Datum.h"
#include "GameObject.h"
namespace GameEngine
{
	/// <summary>
	/// A class that helps parse a JSON file and store them in a Scope hierarchy , the grammer needed is type and value where type indicates the type of data, and value holds the values of that object
	/// </summary>
	class TableParserHelper : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(TableParserHelper);

	public:
		/// <summary>
		/// A struct to hold the context of the value being passed in the JSON hierarchy
		/// </summary>
		struct ContextFrame final
		{
			 const std::string& key;
			 Scope* currentScope;
		
		};
		/// <summary>
		/// A wrapper class that holds a root scope that will store the the data at the beginning of the JSON hierarchy 
		/// </summary>
		class SharedData final : public GameEngine::JsonParseCoordinator::SharedData
		{
			friend TableParserHelper;
			RTTI_DECLARATIONS(SharedData);
		public:
			SharedData(Scope* rootScope=nullptr);
			
			~SharedData();
			virtual void Initialize() override;
			void Cleanup();
			virtual SharedData* Create() const override;
			Scope* _root{ nullptr };
			std::size_t _maxDepth{ 0 };
		};
		/// <summary>
		/// Default constructor for Table Parse Helper, Calls initialize which sets up the hashmap for converting the string type to the Datum type 
		/// </summary>
		TableParserHelper();
		~TableParserHelper();
		/// <summary>
		/// A method that helps set up all member variables and populates the hashmap with string keys to Datum types
		/// </summary>
		virtual void Initialize() override;
		/// <summary>
		/// Virtual constructor that creates new instances of this class
		/// </summary>
		/// <returns></returns>
		virtual IJsonParseHelper* Create() const override;
		/// <summary>
		/// Start handler method that indicates that this handler can parse the data its passed inn, this method is responsoble for appending new scope's or datums
		/// </summary>
		/// <param name="sharedData">A referebce to the shared data that holds the root scope for parsing</param>
		/// <param name="key">The JSON key</param>
		/// <param name="value">The JSON value corresponding to the key passed in</param>
		/// <returns>If this handler can parse the data or no</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) override;
		/// <summary>
		/// End handler call checks if parsing was successful 
		/// </summary>
		/// <param name="sharedData">A referebce to the shared data that holds the root scope for parsing</param>
		/// <param name="key">The JSON key</param>
		/// <param name="value">The JSON value corresponding to the key passed in</param>
		/// <returns>Bool indicating if the value was parsed succesfully</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key,const Json::Value& value) override;
		/*std::size_t GetStartHandlerCount();
		std::size_t GetEndHandlerCount();*/
		//std::uint32_t GetArrayElementCount();
		bool isInitialized{ false };
		/// <summary>
		/// Cleanup method for any memory that might have been allocated
		/// </summary>
		void Cleanup();
	private:
		inline static const std::string _typeKey = "type";
		inline static const std::string _valueKey= "value";
		inline static const std::string _classKey = "class";
		inline static const std::string _childrenKey = "Children";
		bool _isParsingData{ false };
		Vector <ContextFrame> _contextStack;
		 HashMap<std::string, DatumTypes> _stringDatumMap;
		 std::size_t _arrayIndex = 0;
		/*std::size_t _startHandlerCount{ 0 };
		std::size_t _endHandlerCount{ 0 };
		 std::uint32_t _arrayElementCount{ 0 };*/
	};


}
