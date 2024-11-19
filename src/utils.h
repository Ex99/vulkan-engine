#ifndef UTILS_H
#define UTILS_H

#include <functional>

namespace GeckoEngine
{
    template <typename T, typename... Rest>
    void hashCombine(std::size_t &seed, const T &v, const Rest &...rest)
    {
        seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    };
} // namespace GeckoEngine

#endif // UTILS_H