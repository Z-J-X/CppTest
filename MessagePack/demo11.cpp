#if 0
#include <msgpack.hpp>
#include <vector>
#include <string>
#include <iostream>

class base
{
public:
    virtual void convert(msgpack::sbuffer& sbuf);
    virtual void deconvert(msgpack::sbuffer& sbuf);
public:
    std::string b_str;
    MSGPACK_DEFINE_MAP(b_str);
};
void base::convert(msgpack::sbuffer& sbuf)
{
    //std::string
    msgpack::packer<msgpack::sbuffer> pk(&sbuf);
    pk.pack_map(1);
    pk.pack("b_str");
    pk.pack(b_str);
}
void base::deconvert(msgpack::sbuffer& sbuf)
{
    msgpack::object_handle oh =
        msgpack::unpack(sbuf.data(), sbuf.size());

    msgpack::object obj = oh.get();


    if (obj.type != msgpack::type::ARRAY)throw msgpack::type_error();
    if (obj.via.array.size != 1)throw msgpack::type_error();

}



class myclass :public base {
public:
    void convert(msgpack::sbuffer& sbuf);
public:
    std::string m_str;
    std::vector<int> m_vec;
public:
    MSGPACK_DEFINE_MAP(MSGPACK_BASE_MAP(base), m_vec, m_str);//默认以array序列化:#define MSGPACK_DEFINE MSGPACK_DEFINE_ARRAY
    //MSGPACK_DEFINE_MAP(m_str, m_vec);
};

void myclass::convert(msgpack::sbuffer& sbuf)
{
    msgpack::packer<msgpack::sbuffer> pk(&sbuf);
    pk.pack_map(3);
    pk.pack("base");
    base::convert(sbuf);
    pk.pack("m_vec");
    pk.pack_array(m_vec.size());
    for (int i = 0; i < m_vec.size(); i++)
    {
        pk.pack(m_vec.at(i));
    }

    pk.pack("m_str");
    pk.pack(m_str);
}




int main()
{
    myclass test, test1;
    test.b_str = "base";
    test.m_str = "hello";
    test.m_vec.push_back(9);
    test.m_vec.push_back(4);

    test1.b_str = "base";
    test1.m_str = "hello";
    test1.m_vec.push_back(9);
    test1.m_vec.push_back(4);

    msgpack::sbuffer sbuf, sbuf1;
    msgpack::pack(sbuf, test);



    test1.convert(sbuf1);
    msgpack::object_handle oh =
        msgpack::unpack(sbuf1.data(), sbuf1.size());
    msgpack::object obj = oh.get();

    std::cout << obj << std::endl;


    std::cout << std::memcmp(sbuf.data(), sbuf1.data(), sbuf.size()) << std::endl;

    try
    {
        throw msgpack::type_error();
    }
    catch (std::exception& ec)
    {
        std::cout << ec.what();
    }

}
#endif