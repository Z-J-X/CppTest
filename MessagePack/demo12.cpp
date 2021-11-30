#if 0
#include <msgpack.hpp>
#include <vector>
#include <string>
#include <iostream>

using SeqPdu = ::std::vector<unsigned char>;

class Base
{
public:
	virtual void toMasgpack(msgpack::sbuffer& buf) {}
	void fromMasgpackObj(msgpack::object& obj) {}
	virtual void fromMasgpack(msgpack::sbuffer& buf) 
	{
		msgpack::object_handle oh = msgpack::unpack(buf.data(), buf.size());
		msgpack::object obj = oh.get();
		fromMasgpackObj(obj);
	}
	
	
public:
	MSGPACK_DEFINE();
};

class Int :public Base
{
public:
	void toMasgpack(msgpack::sbuffer& buf)
	{
		msgpack::packer<msgpack::sbuffer> pk(&buf);
		pk.pack_array(2);
		pk.pack(0);
		pk.pack_map(1);
		pk.pack("value");
		pk.pack(value);
	}
	void fromMasgpackObj(msgpack::object& obj) 
	{
		if (obj.type != msgpack::type::ARRAY)throw msgpack::type_error();
		if (obj.via.array.size != 2) throw msgpack::type_error();
		msgpack::object obj1 = obj.via.array.ptr[1];

		if (obj1.type != msgpack::type::MAP)throw msgpack::type_error();
		if (obj1.via.map.size != 1) throw msgpack::type_error();
		std::map<std::string, msgpack::object> mp;
		obj1 >> mp;
		mp["value"].convert(value);
	}
public:
	int value;
	MSGPACK_DEFINE(value);
};

class String :public Base
{
public:
	void toMasgpack(msgpack::sbuffer& buf)
	{
		msgpack::packer<msgpack::sbuffer> pk(&buf);
		pk.pack_array(2);
		pk.pack(1);
		pk.pack_map(1);
		pk.pack("value");
		pk.pack(value);
	}
	void fromMasgpackObj(msgpack::object& obj)
	{
		if (obj.type != msgpack::type::ARRAY)throw msgpack::type_error();
		if (obj.via.array.size != 2) throw msgpack::type_error();
		msgpack::object obj1 = obj.via.array.ptr[1];

		if (obj1.type != msgpack::type::MAP)throw msgpack::type_error();
		if (obj1.via.map.size != 1) throw msgpack::type_error();
		std::map<std::string, msgpack::object> mp;
		obj1 >> mp;
		mp["value"].convert(value);
	}
public:
	std::string value;
	MSGPACK_DEFINE(value);
};

class Data
{
public:
	virtual void toMasgpack(msgpack::sbuffer& buf)
	{
		msgpack::packer<msgpack::sbuffer> pk(&buf);
		pk.pack_map(1);
		pk.pack("dataList");
		pk.pack_array(dataList.size());
		for (int i = 0; i < dataList.size(); i++)
		{
			dataList.at(i)->toMasgpack(buf);
		}
	}
	void fromMasgpack(msgpack::sbuffer& buf)
	{
		msgpack::object_handle oh = msgpack::unpack(buf.data(), buf.size());
		msgpack::object obj = oh.get();
		if (obj.type != msgpack::type::MAP)throw msgpack::type_error();
		if (obj.via.map.size != 1) throw msgpack::type_error();
		std::map<std::string, msgpack::object> mp;
		obj >> mp;
		for (int i = 0; i < mp["dataList"].via.array.size; i++)
		{
			msgpack::object tmp = mp["dataList"].via.array.ptr[i];
			switch (tmp.via.array.ptr[0].as<int>())
			{
			case 0:
			{
				std::shared_ptr<Int> val(new Int);
				val->fromMasgpackObj(tmp);
				dataList.push_back(val);
			}break;
			case 1:
			{
				std::shared_ptr<String> val(new String);
				val->fromMasgpackObj(tmp);
				dataList.push_back(val);
			}break;
			default:
				break;
			}
		}
	}
public:
	std::vector<std::shared_ptr<Base>> dataList;
	MSGPACK_DEFINE(dataList);
};


int main()
{
	std::shared_ptr<Data> val(new Data);
	std::shared_ptr<Int> a(new Int);
	a->value = 1;
	std::shared_ptr<String> b(new String);
	b->value = "msgpack";

	val->dataList.push_back(a);
	val->dataList.push_back(b);

	msgpack::sbuffer sbuf;
	val->toMasgpack(sbuf);

	std::shared_ptr<Data> des(new Data);
	des->fromMasgpack(sbuf);
	sbuf.clear();
	des->toMasgpack(sbuf);

	msgpack::object_handle oh =
		msgpack::unpack(sbuf.data(), sbuf.size());
	msgpack::object obj = oh.get();
	std::cout << obj << std::endl;
}
#endif