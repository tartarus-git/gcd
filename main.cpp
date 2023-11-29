#include <cstdlib>
#include <climits>
#include <iostream>

template <typename from_t, typename to_t>
concept implicitly_convertible_to = requires(from_t from_t_instance) {
	[](to_t){}(from_t_instance);
};

template <typename T>
concept gcd_able_t = requires(T instance) {
	{ instance == instance } -> implicitly_convertible_to<bool>;
	{ instance < instance } -> implicitly_convertible_to<bool>;
	{ instance % instance } -> implicitly_convertible_to<T>;
	{ instance = instance } -> implicitly_convertible_to<T>;
	T(instance);
	(T)0;
};

template <gcd_able_t T>
T gcd(T a, T b) noexcept {
	if (a < b) {
		T temp = b;
		b = a;
		a = temp;
	}
	T rest = a % b;
	if (rest == (T)0) { return b; }
	return gcd(b, rest);
}

int main(int argc, const char * const *argv) {
	if (argc != 3) { std::cerr << "[ERROR]: must supply exactly 2 arguments\n"; return 1; }

	long a = std::strtol(argv[1], nullptr, 10);
	switch (a) {
		case 0: std::cerr << "[ERROR]: input cannot be 0 or invalid\n"; return 1;
		case LONG_MAX: case LONG_MIN:
			std::cerr << "[ERROR]: input is out of range of long\n"; return 1;
	}

	long b = std::strtol(argv[2], nullptr, 10);
	switch (b) {
		case 0: std::cerr << "[ERROR]: input cannot be 0 or invalid\n"; return 1;
		case LONG_MAX: case LONG_MIN:
			std::cerr << "[ERROR]: input is out of range of long\n"; return 1;
	}

	std::cout << gcd(a, b) << '\n';
}
