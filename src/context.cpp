//#include "context.hpp"

namespace cpproutine {
__asm__(
".globl _context_save\n\t"
".p2align	2\n\t"
"_context_save:\n\t"
"str x0, [x0, #0]\n\t"
"str x1, [x0, #8]\n\t"
"str x2, [x0, #16]\n\t"
"str x3, [x0, #24]\n\t"
"str x4, [x0, #32]\n\t"
"str x5, [x0, #40]\n\t"
"str x6, [x0, #48]\n\t"
"str x7, [x0, #56]\n\t"
"str x8, [x0, #64]\n\t"
"str x9, [x0, #72]\n\t"
"str x10, [x0, #80]\n\t"
"str x11, [x0, #88]\n\t"
"str x12, [x0, #96]\n\t"
"str x13, [x0, #104]\n\t"
"str x14, [x0, #112]\n\t"
"str x15, [x0, #120]\n\t"
"str x16, [x0, #128]\n\t"
"str x17, [x0, #136]\n\t"
"str x18, [x0, #144]\n\t"
"str x19, [x0, #152]\n\t"
"str x20, [x0, #160]\n\t"
"str x21, [x0, #168]\n\t"
"str x22, [x0, #176]\n\t"
"str x23, [x0, #184]\n\t"
"str x24, [x0, #192]\n\t"
"str x25, [x0, #200]\n\t"
"str x26, [x0, #208]\n\t"
"str x27, [x0, #216]\n\t"
"str x28, [x0, #224]\n\t"
"str lr, [x0, #232]\n\t"
"mov x1, sp\n\t"
"str x1, [x0, #240]\n\t"
"ldr x1, [x0, #8]\n\t"
"ret\n\t"
);

// X0~X3是调用者保存
__asm__(
".global _context_swap\n\t"
".p2align	2\n\t"
"_context_swap:\n\t"
// 保存当前环境
"str x0, [x0, #0]\n\t"
"str x1, [x0, #8]\n\t"
"str x2, [x0, #16]\n\t"
"str x3, [x0, #24]\n\t"
"str x4, [x0, #32]\n\t"
"str x5, [x0, #40]\n\t"
"str x6, [x0, #48]\n\t"
"str x7, [x0, #56]\n\t"
"str x8, [x0, #64]\n\t"
"str x9, [x0, #72]\n\t"
"str x10, [x0, #80]\n\t"
"str x11, [x0, #88]\n\t"
"str x12, [x0, #96]\n\t"
"str x13, [x0, #104]\n\t"
"str x14, [x0, #112]\n\t"
"str x15, [x0, #120]\n\t"
"str x16, [x0, #128]\n\t"
"str x17, [x0, #136]\n\t"
"str x18, [x0, #144]\n\t"
"str x19, [x0, #152]\n\t"
"str x20, [x0, #160]\n\t"
"str x21, [x0, #168]\n\t"
"str x22, [x0, #176]\n\t"
"str x23, [x0, #184]\n\t"
"str x24, [x0, #192]\n\t"
"str x25, [x0, #200]\n\t"
"str x26, [x0, #208]\n\t"
"str x27, [x0, #216]\n\t"
"str x28, [x0, #224]\n\t"
"str lr, [x0, #232]\n\t"
"mov x2, sp\n\t"
"str x2, [x0, #240]\n\t"
//"ldr x2, [x0, #8]\n\t"

// 恢复环境
//"ldr x0, [x1, #0]\n\t"
"ldr x2, [x1, #16]\n\t"
"ldr x3, [x1, #24]\n\t"
"ldr x4, [x1, #32]\n\t"
"ldr x5, [x1, #40]\n\t"
"ldr x6, [x1, #48]\n\t"
"ldr x7, [x1, #56]\n\t"
"ldr x8, [x1, #64]\n\t"
"ldr x9, [x1, #72]\n\t"
"ldr x10, [x1, #80]\n\t"
"ldr x11, [x1, #88]\n\t"
"ldr x12, [x1, #96]\n\t"
"ldr x13, [x1, #104]\n\t"
"ldr x14, [x1, #112]\n\t"
"ldr x15, [x1, #120]\n\t"
"ldr x16, [x1, #128]\n\t"
"ldr x17, [x1, #136]\n\t"
"ldr x18, [x1, #144]\n\t"
"ldr x19, [x1, #152]\n\t"
"ldr x20, [x1, #160]\n\t"
"ldr x21, [x1, #168]\n\t"
"ldr x22, [x1, #176]\n\t"
"ldr x23, [x1, #184]\n\t"
"ldr x24, [x1, #192]\n\t"
"ldr x25, [x1, #200]\n\t"
"ldr x26, [x1, #208]\n\t"
"ldr x27, [x1, #216]\n\t"
"ldr x28, [x1, #224]\n\t"
"ldr lr, [x1, #232]\n\t"
"ldr x0, [x1, #240]\n\t"
"mov sp, x0\n\t"
"ldr x0, [x1, #0]\n\t"
// 最后恢复X1
"ldr x1, [x1, #8]\n\t"
"ret\n\t"
);

__asm__(
".globl _context_back\n\t"
".p2align	2\n\t"
"_context_back:\n\t"
"ldr x2, [x0, #16]\n\t"
"ldr x3, [x0, #24]\n\t"
"ldr x4, [x0, #32]\n\t"
"ldr x5, [x0, #40]\n\t"
"ldr x6, [x0, #48]\n\t"
"ldr x7, [x0, #56]\n\t"
"ldr x8, [x0, #64]\n\t"
"ldr x9, [x0, #72]\n\t"
"ldr x10, [x0, #80]\n\t"
"ldr x11, [x0, #88]\n\t"
"ldr x12, [x0, #96]\n\t"
"ldr x13, [x0, #104]\n\t"
"ldr x14, [x0, #112]\n\t"
"ldr x15, [x0, #120]\n\t"
"ldr x16, [x0, #128]\n\t"
"ldr x17, [x0, #136]\n\t"
"ldr x18, [x0, #144]\n\t"
"ldr x19, [x0, #152]\n\t"
"ldr x20, [x0, #160]\n\t"
"ldr x21, [x0, #168]\n\t"
"ldr x22, [x0, #176]\n\t"
"ldr x23, [x0, #184]\n\t"
"ldr x24, [x0, #192]\n\t"
"ldr x25, [x0, #200]\n\t"
"ldr x26, [x0, #208]\n\t"
"ldr x27, [x0, #216]\n\t"
"ldr x28, [x0, #224]\n\t"
"ldr lr, [x0, #232]\n\t"
"ldr x1, [x0, #240]\n\t"
"mov sp, x1\n\t"
"ldr x1, [x0, #8]\n\t"
"ldr x0, [x0, #0]\n\t"
"ret\n\t"
);


// X0~X3是调用者保存
__asm__(
".global _context_swap2\n\t"
".p2align	2\n\t"
"_context_swap2:\n\t"
// 保存当前环境
"str x0, [x0, #0]\n\t"
"str x1, [x0, #8]\n\t"
"str x2, [x0, #16]\n\t"
"str x3, [x0, #24]\n\t"
"str x4, [x0, #32]\n\t"
"str x5, [x0, #40]\n\t"
"str x6, [x0, #48]\n\t"
"str x7, [x0, #56]\n\t"
"str x8, [x0, #64]\n\t"
"str x9, [x0, #72]\n\t"
"str x10, [x0, #80]\n\t"
"str x11, [x0, #88]\n\t"
"str x12, [x0, #96]\n\t"
"str x13, [x0, #104]\n\t"
"str x14, [x0, #112]\n\t"
"str x15, [x0, #120]\n\t"
"str x16, [x0, #128]\n\t"
"str x17, [x0, #136]\n\t"
"str x18, [x0, #144]\n\t"
"str x19, [x0, #152]\n\t"
"str x20, [x0, #160]\n\t"
"str x21, [x0, #168]\n\t"
"str x22, [x0, #176]\n\t"
"str x23, [x0, #184]\n\t"
"str x24, [x0, #192]\n\t"
"str x25, [x0, #200]\n\t"
"str x26, [x0, #208]\n\t"
"str x27, [x0, #216]\n\t"
"str x28, [x0, #224]\n\t"
// 不保存lr
// "str lr, [x0, #232]\n\t"
"mov x2, sp\n\t"
"str x2, [x0, #240]\n\t"
//"ldr x2, [x0, #8]\n\t"

// 恢复环境
//"ldr x0, [x1, #0]\n\t"
"ldr x2, [x1, #16]\n\t"
"ldr x3, [x1, #24]\n\t"
"ldr x4, [x1, #32]\n\t"
"ldr x5, [x1, #40]\n\t"
"ldr x6, [x1, #48]\n\t"
"ldr x7, [x1, #56]\n\t"
"ldr x8, [x1, #64]\n\t"
"ldr x9, [x1, #72]\n\t"
"ldr x10, [x1, #80]\n\t"
"ldr x11, [x1, #88]\n\t"
"ldr x12, [x1, #96]\n\t"
"ldr x13, [x1, #104]\n\t"
"ldr x14, [x1, #112]\n\t"
"ldr x15, [x1, #120]\n\t"
"ldr x16, [x1, #128]\n\t"
"ldr x17, [x1, #136]\n\t"
"ldr x18, [x1, #144]\n\t"
"ldr x19, [x1, #152]\n\t"
"ldr x20, [x1, #160]\n\t"
"ldr x21, [x1, #168]\n\t"
"ldr x22, [x1, #176]\n\t"
"ldr x23, [x1, #184]\n\t"
"ldr x24, [x1, #192]\n\t"
"ldr x25, [x1, #200]\n\t"
"ldr x26, [x1, #208]\n\t"
"ldr x27, [x1, #216]\n\t"
"ldr x28, [x1, #224]\n\t"
"ldr lr, [x1, #232]\n\t"
"ldr x0, [x1, #240]\n\t"
"mov sp, x0\n\t"
"ldr x0, [x1, #0]\n\t"
// 最后恢复X1
"ldr x1, [x1, #8]\n\t"
"ret\n\t"
);
}