#if 0
#include <msgpack.hpp>
#include <iostream>
#include <string>

int main() {
    // serializes multiple objects using msgpack::packer.
    msgpack::sbuffer buffer;

    std::vector<std::string> vec;
    vec.push_back("Hello");
    vec.push_back("MessagePack");

    msgpack::packer<msgpack::sbuffer> pk(&buffer);
    pk.pack(std::string("Log message ... 1"));
    pk.pack(std::string("Log message ... 2"));
    pk.pack(std::string("Log message ... 3"));
    pk.pack(vec);

    // deserializes these objects using msgpack::unpacker.
    msgpack::unpacker pac;

    // feeds the buffer.
    pac.reserve_buffer(buffer.size());
    memcpy(pac.buffer(), buffer.data(), buffer.size());
    pac.buffer_consumed(buffer.size());

    // now starts streaming deserialization.
    msgpack::object_handle oh;
    while (pac.next(oh)) {
        std::cout << oh.get() << std::endl;
    }
}
#endif