#ifndef GECKO_NODE_H
#define GECKO_NODE_H

#include <atomic>
#include <cstdint>
#include <string>

namespace GeckoEngine
{
    class Node
    {
    public:
        using id_t = uint32_t;

        std::string name;

        explicit Node() : id{generateId()} {}
        Node(const Node &) = delete;
        Node &operator=(const Node &) = delete;
        Node(Node &&) = default;
        Node &operator=(Node &&) = default;

        id_t getId() const { return id; }

    private:
        static id_t generateId()
        {
            static std::atomic<id_t> currentId{0};
            return currentId.fetch_add(1, std::memory_order_relaxed);
        }

        id_t id;
    };
} // namespace GeckoEngine

#endif // GECKO_NODE_H