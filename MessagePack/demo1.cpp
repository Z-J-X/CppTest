#if 0
#include <msgpack.hpp>
#include <vector>
#include <string>
#include <iostream>

int main(void) {
    std::vector<std::string> vec;
    vec.push_back("Hello");
    vec.push_back("MessagePack");

    // serialize it into simple buffer.
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);
    std::string str(sbuf.data(), sbuf.size());
    for (int i = 0; i < str.length(); i++)
    {
        std::cout << std::setw(2) << str[i]<< std::ends;
    }
    std::cout << std::endl;
    for (int i = 0; i < str.length(); i++)
    {
        unsigned int tmp = 0xff & (unsigned int)str[i];
        std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(2) << std::setfill('0') << tmp << std::ends;
    }
    std::cout << std::endl;

    // deserialize it.
    msgpack::object_handle oh =
        msgpack::unpack(sbuf.data(), sbuf.size());

    // print the deserialized object.
    msgpack::object obj = oh.get();
    std::cout << obj << std::endl;  //=> ["Hello", "MessagePack"]

    // convert it into statically typed object.
    std::vector<std::string> rvec;
    std::vector<std::string>& ref = rvec;
    obj.convert(ref);
    std::cout << ref.size() << std::endl;
}
#endif