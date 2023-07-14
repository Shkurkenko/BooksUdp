#pragma once

#include <string>
#include <json/json.h>

namespace Serialization {

	class IJsonSerializable
	{
	public:
		virtual void Serialize(Json::Value& root) = 0;
		virtual void Deserialize(Json::Value& root) = 0;
	};

	class CJsonSerializer
	{
	public:
		static bool Serialize(IJsonSerializable* pObj, std::string& output);
		static bool Deserialize(IJsonSerializable* pObj, std::string& input);
	private:
		CJsonSerializer() {};
	};
}
