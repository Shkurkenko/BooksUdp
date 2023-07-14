#pragma once

#include <string>

#include "Serialize.h";

using namespace Serialization;

class Book : public IJsonSerializable {
private:
	std::string name;
	std::string author;
	int number_of_copies;
	int price;

public:
	Book() : Book("Not found", "Not found", 0, 0) {}
	Book(std::string name, std::string author, int number_of_copies, int price) 
		: name(name), author(author), number_of_copies(number_of_copies), price(price) {}
	virtual void Serialize(Json::Value& root);
	virtual void Deserialize(Json::Value& root);
};
