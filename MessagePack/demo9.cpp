#if 0
#include <cassert>
#include <memory>
#include <iostream>
#include <msgpack.hpp>

struct my {
    my() = delete;

    // target class should be either copyable or movable (or both).
    my(my const&) = delete;
    my(my&&) = default;

    my(int a) :a(a) {}
    int a;
    MSGPACK_DEFINE(a);
};

namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {

            template<>
            struct as<my> {
                my operator()(msgpack::object const& o) const {
                    if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
                    if (o.via.array.size != 1) throw msgpack::type_error();
                    return my(o.via.array.ptr[0].as<int>());
                }
            };

        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack

int main() {
    my m1(42);
    msgpack::zone z;
    msgpack::object obj(m1, z);
    std::cout << obj << std::endl;// => [42]
    assert(m1.a == obj.as<my>().a);
}

#endif