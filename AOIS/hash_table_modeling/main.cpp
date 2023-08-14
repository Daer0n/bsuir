#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>



class HashTable
{
public:
	int capacity = 50;
	std::unordered_map<std::string, std::vector<std::string>> data;
	int length = 0;

	std::string hash_key(std::string key);
	std::vector<std::string> get_item(std::string key);
	void add_item(std::string key, std::string value);
	void delete_item(std::string key);
	void rehash();
	void print();
};


std::string HashTable::hash_key(std::string key)
{
	int value = 0;

	for (int i = 0; i < 3; i++) 
		value += int(key[i]);

	value = value % this->capacity;
	std::stringstream ss;
	ss << value;
	std::string str_value = ss.str();

	return str_value;
}

std::vector<std::string> HashTable::get_item(std::string key)
{
	std::string h_key = hash_key(key);
	return this->data[h_key];
}

void HashTable::add_item(std::string key, std::string value)
{
	std::string h_key = hash_key(key);
	std::vector<std::string> hash_value;
	hash_value.push_back(key);
	hash_value.push_back(value);

	this->data[h_key] = hash_value;
	this->length++;
	
	if (this->length == this->capacity)
		rehash();
}

void HashTable::rehash()
{
	this->capacity += 50;

	std::unordered_map<std::string, std::vector<std::string>> new_data;

	for (auto it = this->data.begin(); it != this->data.end(); it++) {
		auto h_key = this->hash_key(it->first);
		new_data[h_key] = it->second;
	}
	this->data = new_data;
}

void HashTable::delete_item(std::string key)
{
	std::string h_key = hash_key(key);

	this->data.erase(this->data.find(h_key));
}

void HashTable::print()
{
	for (auto it = this->data.begin(); it != this->data.end(); it++) {
		std::cout << it->first << "\n";
		for (size_t i = 0; i < it->second.size(); i++) {
			std::cout << it->second[i] << " ";
		}
		std::cout << "\n";
	}
}


int main()
{
	HashTable ht;
	ht.add_item("Audi", "100");
	ht.add_item("Audi", "80");
	ht.add_item("Ford", "Mondeo 1");
	ht.add_item("Bmw", "M5");

	ht.print();

	ht.delete_item("Bmw");

	ht.print();


}