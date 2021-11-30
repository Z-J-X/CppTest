#if 0
#include <iostream>

#include <msgpack.hpp>

struct foo {
    foo(int i, std::string s, double d)
        :i{ i }, s{ std::move(s) }, d{ d } {}

    int i;
    std::string s;
    double d;
};

namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {

            template<>
            struct pack<foo> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, foo const& v) const {
                    // packing member variables as an array.
                    o.pack_map(3);
                    o.pack("i");
                    o.pack(v.i);
                    o.pack("s");
                    o.pack(v.s);
                    o.pack("d");
                    o.pack(v.d);
                    return o;
                }
            };

            template <>
            struct as<foo> {
                foo operator()(msgpack::object const& o) const {
                    if (o.type != msgpack::type::MAP) throw msgpack::type_error();
                    if (o.via.map.size != 3) throw msgpack::type_error();
                    std::map<std::string, msgpack::object> m;
                    o >> m;
                    return foo(
                        m["i"].as<int>(),
                        m["s"].as<std::string>(),
                        m["d"].as<double>()
                    );
                }
            };

        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack

int main() {
    foo f1(123, "ABC", 45.67);
    msgpack::sbuffer b;
    msgpack::pack(b, f1);
    auto oh = msgpack::unpack(b.data(), b.size());
    std::cout << *oh << std::endl;

    auto f2 = oh->as<foo>();
    std::cout << f2.i << " " << f2.s << " " << f2.d << std::endl;
}
#endif