#if 0
#include<iostream>
#include<vector>
#include<msgpack.hpp>

int main()
{
	std::vector<std::string> vec;
	vec.push_back("Hello");
	vec.push_back("MessagePack");

	msgpack::zone z;
	msgpack::object obj(vec, z);
	std::cout << obj << std::endl;
	assert(obj.as<std::vector<std::string>>() == vec);
	return 0;
}
#endif