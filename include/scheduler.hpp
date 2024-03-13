#ifndef CPPROUTINE_INCLUDE_SCHEDULER_HPP
#define CPPROUTINE_INCLUDE_SCHEDULER_HPP
#include <array>
#include <cstddef>
#include <unordered_map>

namespace cpproutine {
namespace stackful {
class  Coroutine;
class Scheduler;

extern Scheduler *main_scheduler;

class Scheduler {
public:
    explicit Scheduler();
    explicit Scheduler(const size_t stack_size);
public:
    constexpr static size_t MAIN_COROUTINE_ID = 0;
    constexpr static size_t DEFAULT_COROUTINE_SIZE = 128;
    constexpr static size_t DEFAULT_STACK_SIZE = 128 * 1024;
public:
    auto running_coroutine() const -> Coroutine*;
public:
    auto resume(Coroutine*) -> void;
    auto yield(Coroutine*) -> void;
    auto destroy(Coroutine*) -> void;
    auto register_coroutine(Coroutine*) -> size_t;
private:
    std::array<Coroutine*, DEFAULT_COROUTINE_SIZE> m_coroutines;
    std::unordered_map<Coroutine*, size_t> m_ids;
    size_t m_capicity;
    size_t m_size;
    size_t m_stack_size;
    size_t m_running;
};
}
}
#endif