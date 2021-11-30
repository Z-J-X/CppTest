#if 0
#include <msgpack.hpp>
#include <vector>
#include <string>
#include <iostream>

class myclass {
public:
    std::string m_str;
    std::vector<int> m_vec;
public:
    MSGPACK_DEFINE(m_str, m_vec);//默认以array序列化:#define MSGPACK_DEFINE MSGPACK_DEFINE_ARRAY
    //MSGPACK_DEFINE_MAP(m_str, m_vec);
};

int main() {
    std::vector<myclass> vec;

    myclass test1, test2;
    test1.m_str = "hello ";
    test1.m_vec.push_back(1);
    test1.m_vec.push_back(2);
    test2.m_str = "world";
    test2.m_vec.push_back(99);
    test2.m_vec.push_back(100);
    vec.push_back(test1);
    vec.push_back(test2);

    // 序列化
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);

    // 将序列化后得字符串转换(反序列化)为 msgpack::object对象
    msgpack::object_handle oh =
        msgpack::unpack(sbuf.data(), sbuf.size());
    msgpack::object obj = oh.get();
    std::cout << obj << std::endl;

    // 反序列化，将对象从object中反序列化回来
    std::vector<myclass> rvec;
    obj.convert(rvec);
    return 0;
}

#endif