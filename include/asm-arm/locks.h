multiline_comment|/*&n; *  linux/include/asm-arm/locks.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Interrupt safe locking assembler. &n; */
macro_line|#ifndef __ASM_PROC_LOCKS_H
DECL|macro|__ASM_PROC_LOCKS_H
mdefine_line|#define __ASM_PROC_LOCKS_H
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 6
DECL|macro|__down_op
mdefine_line|#define __down_op(ptr,fail)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ down_op&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&t;ldrex&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;sub&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;strex&t;ip, lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne&t;1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;lr, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movmi&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blmi&t;&quot; #fail&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
DECL|macro|__down_op_ret
mdefine_line|#define __down_op_ret(ptr,fail)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ down_op_ret&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;1:&t;ldrex&t;lr, [%1]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;sub&t;lr, lr, %2&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;strex&t;ip, lr, [%1]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne&t;1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;lr, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movmi&t;ip, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movpl&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blmi&t;&quot; #fail &quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;mov&t;%0, ip&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (ret)&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|__up_op
mdefine_line|#define __up_op(ptr,wake)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ up_op&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;1:&t;ldrex&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;add&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;strex&t;ip, lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne&t;1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;lr, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movle&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blle&t;&quot; #wake&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * The value 0x01000000 supports up to 128 processors and&n; * lots of processes.  BIAS must be chosen such that sub&squot;ing&n; * BIAS once per CPU will result in the long remaining&n; * negative.&n; */
DECL|macro|RW_LOCK_BIAS
mdefine_line|#define RW_LOCK_BIAS      0x01000000
DECL|macro|RW_LOCK_BIAS_STR
mdefine_line|#define RW_LOCK_BIAS_STR &quot;0x01000000&quot;
DECL|macro|__down_op_write
mdefine_line|#define __down_op_write(ptr,fail)&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ down_op_write&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;1:&t;ldrex&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;sub&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;strex&t;ip, lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne&t;1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;lr, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movne&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blne&t;&quot; #fail&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (RW_LOCK_BIAS)&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
DECL|macro|__up_op_write
mdefine_line|#define __up_op_write(ptr,wake)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ up_op_read&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;1:&t;ldrex&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;add&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;strex&t;ip, lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne&t;1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;movcs&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blcs&t;&quot; #wake&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (RW_LOCK_BIAS)&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
DECL|macro|__down_op_read
mdefine_line|#define __down_op_read(ptr,fail)&t;&t;&bslash;&n;&t;__down_op(ptr, fail)
DECL|macro|__up_op_read
mdefine_line|#define __up_op_read(ptr,wake)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ up_op_read&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;1:&t;ldrex&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;add&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;strex&t;ip, lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bne&t;1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;teq&t;lr, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;moveq&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bleq&t;&quot; #wake&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
macro_line|#else
DECL|macro|__down_op
mdefine_line|#define __down_op(ptr,fail)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ down_op&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;mrs&t;ip, cpsr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;lr, ip, #128&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, lr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;ldr&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;subs&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;str&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, ip&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movmi&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blmi&t;&quot; #fail&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
DECL|macro|__down_op_ret
mdefine_line|#define __down_op_ret(ptr,fail)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int ret;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ down_op_ret&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;mrs&t;ip, cpsr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;lr, ip, #128&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, lr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;ldr&t;lr, [%1]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;subs&t;lr, lr, %2&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;str&t;lr, [%1]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, ip&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movmi&t;ip, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movpl&t;ip, #0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blmi&t;&quot; #fail &quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;mov&t;%0, ip&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (ret)&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|__up_op
mdefine_line|#define __up_op(ptr,wake)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ up_op&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;mrs&t;ip, cpsr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;lr, ip, #128&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, lr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;ldr&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;adds&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;str&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, ip&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movle&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blle&t;&quot; #wake&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * The value 0x01000000 supports up to 128 processors and&n; * lots of processes.  BIAS must be chosen such that sub&squot;ing&n; * BIAS once per CPU will result in the long remaining&n; * negative.&n; */
DECL|macro|RW_LOCK_BIAS
mdefine_line|#define RW_LOCK_BIAS      0x01000000
DECL|macro|RW_LOCK_BIAS_STR
mdefine_line|#define RW_LOCK_BIAS_STR &quot;0x01000000&quot;
DECL|macro|__down_op_write
mdefine_line|#define __down_op_write(ptr,fail)&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ down_op_write&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;mrs&t;ip, cpsr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;lr, ip, #128&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, lr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;ldr&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;subs&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;str&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, ip&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movne&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blne&t;&quot; #fail&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (RW_LOCK_BIAS)&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
DECL|macro|__up_op_write
mdefine_line|#define __up_op_write(ptr,wake)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ up_op_read&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;mrs&t;ip, cpsr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;lr, ip, #128&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, lr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;ldr&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;adds&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;str&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, ip&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;movcs&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;blcs&t;&quot; #wake&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (RW_LOCK_BIAS)&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
DECL|macro|__down_op_read
mdefine_line|#define __down_op_read(ptr,fail)&t;&t;&bslash;&n;&t;__down_op(ptr, fail)
DECL|macro|__up_op_read
mdefine_line|#define __up_op_read(ptr,wake)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&quot;@ up_op_read&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;mrs&t;ip, cpsr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;lr, ip, #128&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, lr&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;ldr&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;adds&t;lr, lr, %1&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;str&t;lr, [%0]&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, ip&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;moveq&t;ip, %0&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;bleq&t;&quot; #wake&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (ptr), &quot;I&quot; (1)&t;&t;&t;&bslash;&n;&t;: &quot;ip&quot;, &quot;lr&quot;, &quot;cc&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
macro_line|#endif
macro_line|#endif
eof
