#include "stackful.hpp"
#include "context.hpp"
#include "scheduler.hpp"

namespace cpproutine {
namespace stackful {

Coroutine::Coroutine() 
    : m_status(SUSPEND), m_fp(nullptr) {
    main_scheduler->register_coroutine(this);
}

auto Coroutine::make_context() -> void {

}

auto coroutine_yield() -> void {
    // int64_t lr;
    // asm volatile("mov %x0, lr" : "=r" (lr));
    Coroutine *cur_coroutine = main_scheduler->running_coroutine();
    main_scheduler->yield(cur_coroutine);
    // 上条语句改变了lr
    // 所以要先保存lr
    Coroutine *par_coroutine = cur_coroutine->m_parent;
    //cur_coroutine->m_ctx.regs[Context::LR] = lr;
    //context_swap2(&cur_coroutine->m_ctx, &par_coroutine->m_ctx);

    context_swap(&cur_coroutine->m_ctx, &par_coroutine->m_ctx);
    // 此时上下文是当前coroutine_yield执行的上下文
}

auto coroutine_resume(Coroutine *coroutine) -> void {
    // 这里coroutine和cur_coroutine是一样的？
    Coroutine *cur_coroutine = main_scheduler->running_coroutine();
    main_scheduler->resume(coroutine);
    if (cur_coroutine == nullptr) context_back(&coroutine->m_ctx);
    context_swap(&cur_coroutine->m_ctx, &coroutine->m_ctx);
}


auto coroutine_entry(std::function<void()> *f) -> void {
    // 在执行函数前修改LR

    (*f)();
    Coroutine *running = main_scheduler->running_coroutine();
    Coroutine *parent = running->m_parent;
    main_scheduler->destroy(running);
    context_back(&parent->m_ctx);
    // context_back(&running->m_ctx);
    // context_swap(&running->m_ctx, &parent->m_ctx);
}

auto coroutine_exit() -> void {
    Coroutine *running = main_scheduler->running_coroutine();
    Coroutine *parent = running->m_parent;
    context_back(&parent->m_ctx);
}

}
}