#include "scheduler.hpp"
#include "context.hpp"
#include "stackful.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>

namespace cpproutine {
namespace stackful {
Scheduler::Scheduler() 
    : m_capicity(DEFAULT_COROUTINE_SIZE), m_size(0), m_stack_size(DEFAULT_STACK_SIZE) {
    this->m_coroutines.fill(nullptr);
    this->m_coroutines[MAIN_COROUTINE_ID] = new Coroutine(true, [] () {
        exit(0);
    });
    this->m_ids[this->m_coroutines[MAIN_COROUTINE_ID]] = MAIN_COROUTINE_ID;
    this->m_running = MAIN_COROUTINE_ID;
    ++this->m_size;
}

Scheduler::Scheduler(const size_t stack_size) 
    : m_capicity(DEFAULT_COROUTINE_SIZE), m_size(0), m_stack_size(stack_size) {
    if (this->m_stack_size == 0) {
        this->m_stack_size = DEFAULT_STACK_SIZE;
    }
    this->m_coroutines.fill(nullptr);
    this->m_coroutines[MAIN_COROUTINE_ID] = new Coroutine([] () {
        exit(0);
    });
    this->m_ids[this->m_coroutines[MAIN_COROUTINE_ID]] = MAIN_COROUTINE_ID;
    this->m_running = MAIN_COROUTINE_ID;
    ++this->m_size;
}

auto Scheduler::running_coroutine() const -> Coroutine* {
    if (this->m_running >= this->m_size) {
        return nullptr;
    } else {
        return this->m_coroutines[this->m_running];
    }
}

auto Scheduler::resume(Coroutine *coroutine) -> void {
    this->m_running = this->m_ids[coroutine];
}

auto Scheduler::yield(Coroutine *coroutine) -> void {
    Coroutine *parent = coroutine->m_parent;
    if (parent == nullptr) return;
    this->m_running = this->m_ids[parent];
}

auto Scheduler::destroy(Coroutine *coroutine) -> void {
    Coroutine *parent = coroutine->m_parent;
    this->m_running = this->m_ids[parent];
}

auto Scheduler::register_coroutine(Coroutine *coroutine) -> size_t {
    coroutine->m_scheduler = this;
    Coroutine *parent = this->running_coroutine();
    assert(parent != nullptr);
    coroutine->m_parent = parent;
    coroutine->m_ctx = Context(this->m_stack_size);
    size_t id = 0;
    for (id = 0; id < this->m_capicity; ++id) {
        if (this->m_coroutines[id] == nullptr) {
            this->m_coroutines[id] = coroutine;
            this->m_ids[coroutine] = id;
            break;
        }
    }
    ++this->m_size;
    return id;
}

Scheduler *main_scheduler = new Scheduler();
}
}