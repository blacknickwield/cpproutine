#ifndef CPPROUTINE_INCLUDE_CONTEXT_HPP
#define CPPROUTINE_INCLUDE_CONTEXT_HPP
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ostream>
namespace cpproutine {

struct Context {
    constexpr static size_t REGISTER_SIZE = 32;
    enum {
        X0 = 0, X1, X2, X3, X4, X5, X6, X7, X8, X9,
        X10, X11, X12, X13, X14, X15, X16, X17, X18, X19,
        X20, X21, X22, X23, X24, X25, X26, X27, X28,
        LR, SP, CPSR
    };
    // LR记录当前协程的下一条指令
    Context(): sp(nullptr), size(0) {
        regs.fill(0);
    }
    Context(size_t stack_size) : sp(new char[stack_size]), size(stack_size) {}
    friend auto operator<<(std::ostream &os, const Context &context) -> std::ostream& {
        for (size_t i = 0; i <= 28; ++i) {
            os << "x" << i << ": " << context.regs[i] << std::endl;
        }
        os << "lr: " << context.regs[29] << std::endl;
        os << "sp: " << context.regs[30] << std::endl;
        return os;
    }
    std::array<int64_t, REGISTER_SIZE> regs;
    char *sp;
    size_t size;
};

extern "C" void context_save(Context*);
extern "C" void context_swap(Context*, Context*);
extern "C" void context_back(Context*);
extern "C" void context_swap2(Context*, Context*);
} // namespace cpproutine
#endif