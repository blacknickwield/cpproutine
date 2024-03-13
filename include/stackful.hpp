#ifndef CPPROUTINE_INCLUDE_STACKFUL_HPP
#define CPPROUTINE_INCLUDE_STACKFUL_HPP

#include "context.hpp"
#include "scheduler.hpp"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>
#include <set>

constexpr size_t DEFAULT_STACK_SIZE = 128 * 1024;
namespace cpproutine {
namespace stackful {

auto coroutine_entry(std::function<void()> *f) -> void;
auto coroutine_yield() -> void;
auto coroutine_resume(Coroutine *coroutine) -> void;

class Coroutine {
public:
    enum Status {
        SUSPEND,
        RUNNING,
        AWAITING,
        DESTROYED,
    };
public:
    explicit Coroutine();
    
    template<class F, class... Arg>
    explicit Coroutine(F &&f, Arg&&... args) : m_status(SUSPEND) {
        main_scheduler->register_coroutine(this);
        wrap<F, Arg...>(std::forward<F>(f), std::forward<Arg>(args)...);
        this->m_fp = &this->m_f;
        this->m_stack_end = new char[DEFAULT_STACK_SIZE];
        this->m_stack_start = this->m_stack_end + DEFAULT_STACK_SIZE;
        this->m_ctx.regs[Context::LR] = (int64_t)coroutine_entry;
        this->m_ctx.regs[Context::X0] = (int64_t)this->m_fp;
        this->m_ctx.regs[Context::SP] = (int64_t)this->m_stack_start;
    }
private:
    template<class F, class... Arg>
    explicit Coroutine(bool is_main_co, F &&f, Arg&&... args) : m_status(SUSPEND) {
        if (!is_main_co) {
            main_scheduler->register_coroutine(this);
        }
        wrap<F, Arg...>(std::forward<F>(f), std::forward<Arg>(args)...);
        this->m_fp = &this->m_f;
        this->m_stack_end = new char[DEFAULT_STACK_SIZE];
        this->m_stack_start = this->m_stack_end + DEFAULT_STACK_SIZE;
        this->m_ctx.regs[Context::LR] = (int64_t)coroutine_entry;
        this->m_ctx.regs[Context::X0] = (int64_t)this->m_fp;
        this->m_ctx.regs[Context::SP] = (int64_t)this->m_stack_start;
    }
public:
    auto make_context() -> void;
private:
    template<class F, class... Arg>
    void wrap(F &&f, Arg... args) {
        auto work = std::bind(std::forward<F>(f), std::forward<Arg>(args)...);
        m_f = [&] () {
            m_status = RUNNING;
            work();
            m_status = AWAITING;
        };
    }
public:
    friend auto coroutine_yield() -> void;
    friend auto coroutine_resume(Coroutine *coroutine) -> void;
    friend auto coroutine_entry(std::function<void()> *f) -> void;
    friend auto coroutine_exit() -> void;
public:
    friend class Scheduler;
private:
    Coroutine *m_parent;
    std::set<Coroutine*> m_children;
    Scheduler *m_scheduler;
    std::function<void()> m_f;
    std::function<void()> *m_fp;
    Context m_ctx;
    char *m_stack_start; // 高地址
    char *m_stack_end; // 低地址
    Status m_status;
};



} // namespace stackful
} // namespace cpproutine
#endif