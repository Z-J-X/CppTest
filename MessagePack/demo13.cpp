#if 0
#include <tuple>
#include <cassert>
#include <iostream>
#include <memory>

struct base {};
struct type_a : base {
	type_a(int i) {
		std::cout << "type_a " << i << std::endl;
	}
};

struct type_b : base {
	type_b(double d, int i) {
		std::cout << "type_b " << d << " " << i << std::endl;
	}
};

using base_sp = std::shared_ptr<base>;
using types = std::tuple<type_a, type_b>;

template <size_t I>
struct indexed_construct_impl {
	template <typename... Params>
	static base_sp indexed_construct(size_t idx, Params&&... params) {
		if (idx == I - 1) {
			if constexpr (
				std::is_constructible_v<
				typename std::tuple_element<I - 1, types>::type,
				Params...
				>
				) {
				auto derived =
					std::make_shared<
					typename std::tuple_element<I - 1, types>::type
					>(std::forward<Params>(params)...);
				return base_sp(std::move(derived));
			}
			std::cerr
				<< "no matching constructor at index " << idx << " params ";
			((std::cerr << params), ...);
			std::cerr << std::endl;
			// you can insert assert or throw here
			return nullptr;
		}
		else {
			return indexed_construct_impl<I - 1>::indexed_construct(idx, std::forward<Params>(params)...);
		}
	}
};

template <>
struct indexed_construct_impl<0> {
	template <typename... Params>
	static base_sp indexed_construct(size_t idx, Params&&... /*params*/) {
		std::cerr << "index " << idx << " out of range" << std::endl;
		// you can insert assert or throw here
		return nullptr;
	}
};

template <typename... Params>
base_sp indexed_construct(size_t idx, Params&&... params) {
	return
		indexed_construct_impl<
		std::tuple_size<types>::value
		>::indexed_construct(
			idx,
			std::forward<Params>(params)...
		);
}

int main() {
	base_sp v1 = indexed_construct(0, 1);         // type index:0 params:1
	base_sp v2 = indexed_construct(1, 1.23, 45);  // type index:1 params:1.23, 45
	base_sp v3 = indexed_construct(1, 12.34);     // type index:1 params 12.34 // too few
	assert(!v3); // construct error return nullptr
	base_sp v4 = indexed_construct(2);            // index out of range is compile error
}
#endif