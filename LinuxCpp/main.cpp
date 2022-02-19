#include <iostream>
#include <unordered_set>
#include <sw/redis++/redis++.h>

using namespace sw::redis;
int main()
{
	try
	{
		auto redis = Redis("tcp://kaifa123@192.168.10.144:6379");
		//redis.auth("kaifa123");

// ***** STRING commands *****
		redis.set("key", "val");
		auto val = redis.get("key");    // val is of type OptionalString. See 'API Reference' section for details.
		if (val) {
			// Dereference val to get the returned value of std::string type.
			std::cout << *val << std::endl;
		} // else key doesn't exist.
		
// ***** LIST commands *****

		// std::vector<std::string> to Redis LIST.
		std::vector<std::string> vec = { "a", "b", "c" };
		redis.rpush("list", vec.begin(), vec.end());

		// std::initializer_list to Redis LIST.
		redis.rpush("list", { "a", "b", "c" });

		// Redis LIST to std::vector<std::string>.
		vec.clear();
		redis.lrange("list", 0, -1, std::back_inserter(vec));
		for (auto i : vec)
		{
			std::cout << i <<" " << std::flush;
		}
		std::cout << std::endl;

// ***** HASH commands *****
		redis.hset("hash", "field", "val");

		// Another way to do the same job.
		redis.hset("hash", std::make_pair("field", "val"));
		
		// std::unordered_map<std::string, std::string> to Redis HASH.
		std::unordered_map<std::string, std::string> m = {
			{"field1", "val1"},
			{"field2", "val2"}
		};
		redis.hmset("hash", m.begin(), m.end());

		// Redis HASH to std::unordered_map<std::string, std::string>.
		m.clear();
		redis.hgetall("hash", std::inserter(m, m.begin()));

		// Get value only.
		// NOTE: since field might NOT exist, so we need to parse it to OptionalString.
		std::vector<OptionalString> vals;
		redis.hmget("hash", { "field1", "field2" }, std::back_inserter(vals));

		std::cout << vals[0].value() <<"  " << vals[1].has_value() << std::endl;

// ***** SET commands *****

		redis.sadd("set", "m1");

		// std::unordered_set<std::string> to Redis SET.
		std::unordered_set<std::string> set = { "m2", "m3" };
		redis.sadd("set", set.begin(), set.end());

		// std::initializer_list to Redis SET.
		redis.sadd("set", { "m2", "m3" });

		// Redis SET to std::unordered_set<std::string>.
		set.clear();
		redis.smembers("set", std::inserter(set, set.begin()));

		if (redis.sismember("set", "m1")) {
			std::cout << "m1 exists" << std::endl;
		}   // else NOT exist.


		redis.del("key");
		redis.del("list");
		redis.del("hash");
		redis.del("set");

	}
	catch (std::exception& ec)
	{
		std::cout << "Error:" << ec.what() << std::endl;
	}

	return 0;
}