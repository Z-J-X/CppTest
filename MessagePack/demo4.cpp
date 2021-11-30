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
    MSGPACK_DEFINE(m_str, m_vec);//Ĭ����array���л�:#define MSGPACK_DEFINE MSGPACK_DEFINE_ARRAY
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

    // ���л�
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);

    // �����л�����ַ���ת��(�����л�)Ϊ msgpack::object����
    msgpack::object_handle oh =
        msgpack::unpack(sbuf.data(), sbuf.size());
    msgpack::object obj = oh.get();
    std::cout << obj << std::endl;

    // �����л����������object�з����л�����
    std::vector<myclass> rvec;
    obj.convert(rvec);
    return 0;
}

#endif