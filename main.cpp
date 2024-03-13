#include <cstdio>
#include "stackful.hpp"

using namespace cpproutine;

int main(int argc, char *argv[]) {
    stackful::Coroutine *co = new stackful::Coroutine([] () {
        stackful::Coroutine *child_co = new stackful::Coroutine([] () {
            printf("child1\n");
            // std::cout << "child1" << std::endl;
            stackful::coroutine_yield(); // 此时yield保存的不是当前上下文？
            // std::cout << "child2" << std::endl;
            printf("child2\n");
        });

        printf("father1\n");
        // std::cout << "father1" << std::endl;
        stackful::coroutine_resume(child_co);
        printf("father2\n");
        //std::cout << "father2" << std::endl;
        stackful::coroutine_resume(child_co);
    });
    stackful::coroutine_resume(co);
    return 0;
}