multiline_comment|/* include/asm-x86_64/rwlock.h&n; *&n; *&t;Helpers used by both rw spinlocks and rw semaphores.&n; *&n; *&t;Based in part on code from semaphore.h and&n; *&t;spinlock.h Copyright 1996 Linus Torvalds.&n; *&n; *&t;Copyright 1999 Red Hat, Inc.&n; *&t;Copyright 2001 SuSE labs &n; *&n; *&t;Written by Benjamin LaHaise.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_X86_64_RWLOCK_H
DECL|macro|_ASM_X86_64_RWLOCK_H
mdefine_line|#define _ASM_X86_64_RWLOCK_H
DECL|macro|RW_LOCK_BIAS
mdefine_line|#define RW_LOCK_BIAS&t;&t; 0x01000000
DECL|macro|RW_LOCK_BIAS_STR
mdefine_line|#define RW_LOCK_BIAS_STR&t;&quot;0x01000000&quot;
DECL|macro|__build_read_lock_ptr
mdefine_line|#define __build_read_lock_ptr(rw, helper)   &bslash;&n;&t;asm volatile(LOCK &quot;subl $1,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;js 2f&bslash;n&quot; &bslash;&n;&t;&t;     &quot;1:&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;     &quot;2:&bslash;tcall &quot; helper &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.previous&quot; &bslash;&n;&t;&t;     ::&quot;d&quot; (rw) : &quot;memory&quot;)
DECL|macro|__build_read_lock_const
mdefine_line|#define __build_read_lock_const(rw, helper)   &bslash;&n;&t;asm volatile(LOCK &quot;subl $1,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;js 2f&bslash;n&quot; &bslash;&n;&t;&t;     &quot;1:&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;     &quot;2:&bslash;tpushq %%rax&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;leal %0,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;call &quot; helper &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;popq %%rax&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.previous&quot; &bslash;&n;&t;&t;     :&quot;=m&quot; (*((volatile int *)rw))::&quot;memory&quot;)
DECL|macro|__build_read_lock
mdefine_line|#define __build_read_lock(rw, helper)&t;do { &bslash;&n;&t;&t;&t;&t;&t;&t;if (__builtin_constant_p(rw)) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;__build_read_lock_const(rw, helper); &bslash;&n;&t;&t;&t;&t;&t;&t;else &bslash;&n;&t;&t;&t;&t;&t;&t;&t;__build_read_lock_ptr(rw, helper); &bslash;&n;&t;&t;&t;&t;&t;} while (0)
DECL|macro|__build_write_lock_ptr
mdefine_line|#define __build_write_lock_ptr(rw, helper) &bslash;&n;&t;asm volatile(LOCK &quot;subl $&quot; RW_LOCK_BIAS_STR &quot;,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jnz 2f&bslash;n&quot; &bslash;&n;&t;&t;     &quot;1:&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;     &quot;2:&bslash;tcall &quot; helper &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.previous&quot; &bslash;&n;&t;&t;     ::&quot;d&quot; (rw) : &quot;memory&quot;)
DECL|macro|__build_write_lock_const
mdefine_line|#define __build_write_lock_const(rw, helper) &bslash;&n;&t;asm volatile(LOCK &quot;subl $&quot; RW_LOCK_BIAS_STR &quot;,(%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jnz 2f&bslash;n&quot; &bslash;&n;&t;&t;     &quot;1:&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;     &quot;2:&bslash;tpushq %%rax&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;leaq %0,%%rax&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;call &quot; helper &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;popq %%rax&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.previous&quot; &bslash;&n;&t;&t;     :&quot;=m&quot; (*((volatile long *)rw))::&quot;memory&quot;)
DECL|macro|__build_write_lock
mdefine_line|#define __build_write_lock(rw, helper)&t;do { &bslash;&n;&t;&t;&t;&t;&t;&t;if (__builtin_constant_p(rw)) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;__build_write_lock_const(rw, helper); &bslash;&n;&t;&t;&t;&t;&t;&t;else &bslash;&n;&t;&t;&t;&t;&t;&t;&t;__build_write_lock_ptr(rw, helper); &bslash;&n;&t;&t;&t;&t;&t;} while (0)
macro_line|#endif
eof
