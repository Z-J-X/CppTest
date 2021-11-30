#if 0
#include <msgpack.hpp>
#include <iostream>
#include <string>

int main() {
    // serializes multiple objects into one message containing an array using msgpack::packer.
    msgpack::sbuffer buffer1;

    msgpack::packer<msgpack::sbuffer> pk1(&buffer1);
    pk1.pack_array(3);
    pk1.pack(std::string("Log message ... 1"));
    pk1.pack(std::string("Log message ... 2"));
    pk1.pack(std::string("Log message ... 3"));

    // serializes multiple objects into one message containing a map using msgpack::packer.
    msgpack::sbuffer buffer2;

    msgpack::packer<msgpack::sbuffer> pk2(&buffer2);
    pk2.pack_map(2);
    pk2.pack(std::string("x"));
    pk2.pack(3);
    pk2.pack(std::string("y"));
    pk2.pack(3.4321);

    msgpack::object_handle oh1 =
        msgpack::unpack(buffer1.data(), buffer1.size());
    msgpack::object_handle oh2 =
        msgpack::unpack(buffer2.data(), buffer2.size());

    msgpack::object obj1 = oh1.get();
    std::cout << obj1 << std::endl;
    msgpack::object obj2 = oh2.get();
    std::cout << obj2 << std::endl;

}
#endif