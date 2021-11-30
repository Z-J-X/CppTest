#include <msgpack.hpp>
#include <vector>
#include <string>
#include <iostream>

int main()
{
	msgpack::sbuffer sbuf;
	msgpack::packer<msgpack::sbuffer> pk(&sbuf);
	pk.pack_map(1);
	auto ptr = std::make_shared<std::vector<std::string>>();
	ptr->push_back("dasdas");
	ptr->push_back("aaa");
	pk.pack("map").pack(ptr);

	msgpack::object_handle oh = msgpack::unpack(sbuf.data(), sbuf.size());
	msgpack::object obj = oh.get();
	std::cout << obj << std::endl;;


	std::map<std::string, msgpack::object> mp;
	obj >> mp;
	auto ptr2 = std::make_shared<std::vector<std::string>>();
	mp["map"].convert(ptr2);
	std::cout << ptr2->at(0);
}