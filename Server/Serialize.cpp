#include "Serialize.h"

bool Serialization::CJsonSerializer::Serialize(IJsonSerializable* pObj, std::string& output)
{
	if (pObj == NULL) return false;

	Json::Value serializeRoot;
	pObj->Serialize(serializeRoot);

	Json::StyledWriter writer;
	output = writer.write(serializeRoot);

	return false;
}

bool Serialization::CJsonSerializer::Deserialize(IJsonSerializable* pObj, std::string& input)
{
	if (pObj == NULL) return false;

	Json::Value deserializeRoot;
	Json::Reader reader;

	if (!reader.parse(input, deserializeRoot)) return false;

	pObj->Deserialize(deserializeRoot);

	return true;
}
