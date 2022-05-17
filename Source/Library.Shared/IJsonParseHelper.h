#pragma once

#include "RTTI.h"
#include "JsonParseCoordinator.h"
#pragma warning (push)
#pragma warning (disable:4635)
#pragma warning (disable:26812)
#include <json/json.h>
#pragma warning (pop)
namespace GameEngine
{
	class IJsonParseHelper : public RTTI
	{

		RTTI_DECLARATIONS(IJsonParseHelper);
	public:
		/// <summary>
		/// Helps initialize the helpers by setting all private members to a default value
		/// </summary>
		virtual void Initialize() {};
		/// <summary>
		/// Starts the parsing process 
		/// </summary>
		/// <param name="sharedData">A reference to the coordinators shared data</param>
		/// <param name="key">The JSON key corresponding to this value</param>
		/// <param name="value">The actual JSON value</param>
		/// <returns>If this handler could parse the data or no</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key, const Json::Value& value) = 0;
		/// <summary>
		/// Ends the parsing process 
		/// </summary>
		/// <param name="sharedData">A reference to the coordinators shared data</param>
		/// <param name="key">The JSON key corresponding to this value</param>
		/// <param name="value">The actual JSON value</param>
		/// <returns>If this handler could parse the data or no</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedData& sharedData, const std::string& key,const Json::Value& value) = 0;
		/// <summary>
		/// A virtual constructor 
		/// </summary>
		/// <returns>A pointer to the helper created</returns>
		virtual IJsonParseHelper* Create() const = 0;

		virtual ~IJsonParseHelper() = default;

		



	};
}


