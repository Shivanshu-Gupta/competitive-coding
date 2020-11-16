//
// Created by Shivanshu Gupta on 02/03/20.
//

/**
Hashing for User Defined Types
- Two options:
 - specialize std::hash
 - define hash type to pass as template argument (could be a functor or a std::function or function pointer)
References:
1. https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x: How to combine hash functions
2. https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine - Boost hash_combine explanation
*/

#include <cstddef>
#include <string>

//using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// hash_combiner functions used to create Hash Functions for User Defined Types
////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Simple hash_combine inspired by boost::hash_combine
 * - https://stackoverflow.com/a/2595226/4953139
 */
template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

/**
 * Variadic version of hash_combine
 * - https://stackoverflow.com/a/38140932/4953139
 * - https://en.cppreference.com/w/cpp/language/parameter_pack
 */
inline void hash_combiner_recursive(std::size_t& seed) { } // base function

template <typename T, typename... Rest>
inline void hash_combiner_recursive(std::size_t& seed, const T& v, const Rest&... rest) {     // recursive variadic function
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    hash_combine(seed, rest...);    // recursive call
}

/**
 * Variadic version of hash_combine using Fold Expression (C++17 only)
 * - https://stackoverflow.com/a/57595105/4953139
 * - https://en.cppreference.com/w/cpp/language/fold
 */
template <typename T, typename... Rest>
void hash_combiner_fold(std::size_t& seed, const T& v, const Rest&... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hash_combine(seed, rest), ...);        // if rest is empty, this will evaluate to void()
}

/**
 * Variadic version of hash_combine (C++11 as well)
 * - https://stackoverflow.com/a/59388432/4953139
 * - uses "Expander Trick" to emulate fold expression
 * - uses perfect forwarding (using && and std::forward) for the variadic template arguments
 *      - https://en.cppreference.com/w/cpp/utility/forward
 * TODO: understand "Expander Trick" and std::forward
 */
template <typename T, typename... Rest>
inline void hash_combiner_cpp11(std::size_t &seed, T const &v, Rest &&... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (int[]){0, (hashCombine(seed, std::forward<Rest>(rest)), 0)...};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Usage and Creation of Hash functions for User Defined Types
////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Variadic macro to create hashes for custom types using std::hash
 * B - type to extend std::hash for
 * hash_combiner - variadic hash_combine function to use
*/
#define MAKE_HASHABLE(K, hash_combiner, ...) \
namespace std {\
    template<> struct hash<K> {\
        std::size_t operator()(const K &k) const noexcept {\
            std::size_t ret = 0;\
            hash_combiner(ret, __VA_ARGS__);\
            return ret;\
        }\
    };\
}

struct Key {
    std::string key1;
    std::string key2;
    bool key3;
};

// Inject hash for Key into std::
namespace std
{
    template<>
    struct hash<Key> {
        std::size_t operator()(Key const& k) const noexcept {
            std::size_t h = 0;
            hash_combiner_fold(h, k.key1, k.key2, k.key3);
            return h;
        }
    };
}

// Or using the macro
//MAKE_HASHABLE(Key, hash_combiner_fold, b.key1, b.key2, b.key3)


int testHashing() {
    Key key = {"asd", "as", true};
    std::size_t h=0;
    hash_combiner_fold(h, key.key1, key.key2, key.key3); // compute hash of key
    return 0;
}
