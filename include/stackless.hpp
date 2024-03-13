#ifndef CPPROUTINE_INCLUDE_STACKLESS_HPP
#define CPPROUTINE_INCLUDE_STACKLESS_HPP

#include <cstddef>
#include <functional>
#include <cstdlib>
#include <type_traits>

#define STACKLESS_CO(name) \
class name \
    : public cpproutine::stackless::Coroutine { \
    template<class... Arg> \
    name(Arg... args) \
        : cpproutine::stackless::Coroutine() { \
        this->m_f = std::bind(&name::f, this, args...); \
        this->m_fp = &this->m_f; \
    } \


#define STACKLESS_END \
}; \

#define CO_BEGIN(RET_TYPE) \
void f() { \
    switch(m_state) { \
    case 0: \
    if (!std::is_void<RET_TYPE>::value) { \
        m_ret = (RET_TYPE*)malloc(sizeof(RET_TYPE)); \
    } \

#define CO_YIELD \
m_state = __LINE__; \
m_status = SUSPEND; \
return; \
case __LINE__: ;\

#define CO_RETURN \
m_state = 0; \
m_status = DESTROYED \
return \

#define CO_END \
default: ;\
    } \
} \

namespace cpproutine {
namespace stackless {

class Coroutine {
public:
    Coroutine();
public:
    enum Status {
        SUSPEND,
        RUNNING,
        AWAITING,
        DESTROYED,
    };
public:
    Coroutine *m_parent;
    Status m_status;
    size_t m_state;
    std::function<void()> m_f;
    std::function<void()> *m_fp;
    void *m_ret;
};

}
}

STACKLESS_CO(Hello)
int a, b, c;
CO_BEGIN(int)
CO_END
STACKLESS_END

#endif