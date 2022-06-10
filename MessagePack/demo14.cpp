#include <msgpack.hpp>
#include <iostream>
#include <string>

int main() {
    // serializes multiple objects using msgpack::packer.
    msgpack::sbuffer buffer1,buffer2;

    std::vector<std::string> vec;
    vec.push_back("Hello");
    vec.push_back("MessagePack");

    msgpack::packer<msgpack::sbuffer> pk1(&buffer1);
    msgpack::packer<msgpack::sbuffer> pk2(&buffer2);
    pk1.pack(std::string("Log message ... 1"));
    pk1.pack(std::string("Log message ... 2"));
    pk1.pack(std::string("Log message ... 3"));


    pk2.pack(vec);
    pk2.pack(std::string("Log message ... 4"));

    // deserializes these objects using msgpack::unpacker.
    msgpack::unpacker pac;

    // feeds the buffer.
    pac.reserve_buffer(buffer1.size()+buffer2.size());
    memcpy(pac.buffer(), buffer1.data(), buffer1.size());
    memcpy(pac.buffer()+ buffer1.size(), buffer2.data(), buffer2.size());
    pac.buffer_consumed(buffer1.size()+ buffer2.size());

    // now starts streaming deserialization.
    msgpack::object_handle oh;
    while (pac.next(oh)) {
        std::cout << oh.get() << std::endl;
    }
}