#include "book.h"

void Book::Serialize(Json::Value& root)
{
	root["name"] = name;
	root["author"] = author;
	root["number_of_copies"] = number_of_copies;
	root["price"] = price;
}

void Book::Deserialize(Json::Value& root)
{
	name = root.get("name", "").asString();
	author = root.get("author", "").asString();
	number_of_copies = root.get("number_of_copies", 0).asInt();
	price = root.get("price", 0).asInt();
}
