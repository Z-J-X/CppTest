#if 0
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>

#include <msgpack.hpp>

class base
{
public:
    std::string bstr;
    MSGPACK_DEFINE(bstr);
};


class my_class :public base {
public:
    std::string name_;
    int age_;
};

// User defined class template specialization
namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {

            template<>
            struct convert<my_class> {
                msgpack::object const& operator()(msgpack::object const& o, my_class& v) const {
                    
                    if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();//判断序列化的格式 array/map
                    if (o.via.array.size != 3) throw msgpack::type_error();
                    base& bv = v;//浅拷贝
                    bv = o.via.array.ptr[0].as<base>();
                    v.name_ = o.via.array.ptr[1].as<std::string>();
                    v.age_ = o.via.array.ptr[2].as<int>();
                    return o;
                }
            };

            template<>
            struct pack<my_class> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, my_class const& v) const {
                    // packing member variables as an array.             
                    o.pack_array(3);
                    o.pack((base&)v);
                    o.pack(v.name_);
                    o.pack(v.age_);                    
                    
                    return o;
                }
            };

            template <>
            struct object_with_zone<my_class> {
                void operator()(msgpack::object::with_zone& o, my_class const& v) const {
                    o.type = type::ARRAY;
                    o.via.array.size = 3;
                    o.via.array.ptr = static_cast<msgpack::object*>(
                        o.zone.allocate_align(sizeof(msgpack::object) * o.via.array.size, MSGPACK_ZONE_ALIGNOF(msgpack::object)));
                    o.via.array.ptr[0] = msgpack::object((base&)v, o.zone);
                    o.via.array.ptr[1] = msgpack::object(v.name_, o.zone);
                    o.via.array.ptr[2] = msgpack::object(v.age_, o.zone);
                }
            };

        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack


class son :public my_class {
public:
    void print()
    {
        std::cout << "bstr: " << bstr << "\n"
            << "name_: " << name_ << "\n"
            << "age_: " << age_ << "\n"
            << "str_:" << str_ << "\n";
    }
public:
    std::string str_;
    MSGPACK_DEFINE(MSGPACK_BASE(my_class), str_);
};


void print(std::string const& buf) {
    for (std::string::const_iterator it = buf.begin(), end = buf.end();
        it != end;
        ++it) {
        std::cout
            << std::setw(2)
            << std::hex
            << std::setfill('0')
            << (static_cast<int>(*it) & 0xff)
            << ' ';
    }
    std::cout << std::dec << std::endl;
}

int main() {
    {   // pack, unpack
        son my;
        my.bstr = "base";
        my.age_ = 18;
        my.name_ = "myclass";
        my.str_ = "son";
        std::stringstream ss;
        msgpack::pack(ss, my);

        std::string const& str = ss.str();
        print(str);

        msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());
        msgpack::object obj = oh.get();
        std::cout << obj << std::endl;

        obj.as<son>().print();
        std::cout << std::endl;
    }
    {   // create object with zone
        son my;
        my.bstr = "base";
        my.age_ = 18;
        my.name_ = "myclass";
        my.str_ = "son";
        msgpack::zone z;
        msgpack::object obj(my, z);
        std::cout << obj << std::endl;
        obj.as<son>().print();
        std::cout << std::endl;
    }
}

#endif