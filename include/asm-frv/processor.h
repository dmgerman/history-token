multiline_comment|/* processor.h: FRV processor definitions&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_PROCESSOR_H
DECL|macro|_ASM_PROCESSOR_H
mdefine_line|#define _ASM_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mem-layout.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/registers.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; */
DECL|struct|cpuinfo_frv
r_struct
id|cpuinfo_frv
(brace
macro_line|#ifdef CONFIG_MMU
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
macro_line|#endif
DECL|variable|__cacheline_aligned
)brace
id|__cacheline_aligned
suffix:semicolon
r_extern
r_struct
id|cpuinfo_frv
id|__nongprelbss
id|boot_cpu_data
suffix:semicolon
DECL|macro|cpu_data
mdefine_line|#define cpu_data&t;&t;(&amp;boot_cpu_data)
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data&t;boot_cpu_data
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|frame
r_struct
id|pt_regs
op_star
id|frame
suffix:semicolon
multiline_comment|/* [GR28] exception frame ptr for this thread */
DECL|member|curr
r_struct
id|task_struct
op_star
id|curr
suffix:semicolon
multiline_comment|/* [GR29] current pointer for this thread */
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* [GR1 ] kernel stack pointer */
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
multiline_comment|/* [GR2 ] kernel frame pointer */
DECL|member|lr
r_int
r_int
id|lr
suffix:semicolon
multiline_comment|/* link register */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|gr
r_int
r_int
id|gr
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* [GR16-GR27] */
DECL|member|sched_lr
r_int
r_int
id|sched_lr
suffix:semicolon
multiline_comment|/* LR from schedule() */
r_union
(brace
DECL|member|frame0
r_struct
id|pt_regs
op_star
id|frame0
suffix:semicolon
multiline_comment|/* top (user) stack frame */
DECL|member|user
r_struct
id|user_context
op_star
id|user
suffix:semicolon
multiline_comment|/* userspace context */
)brace
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|pt_regs
op_star
id|__kernel_frame0_ptr
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|__kernel_current_task
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|INIT_THREAD_FRAME0
mdefine_line|#define INIT_THREAD_FRAME0 &bslash;&n;&t;((struct pt_regs *) &bslash;&n;&t;(sizeof(init_stack) + (unsigned long) init_stack - sizeof(struct user_context)))
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD {&t;&t;&t;&t;&bslash;&n;&t;NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;(struct task_struct *) init_stack,&t;&bslash;&n;&t;0, 0, 0, 0,&t;&t;&t;&t;&bslash;&n;&t;{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;{ INIT_THREAD_FRAME0 },&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * do necessary setup to start up a newly executed thread.&n; * - need to discard the frame stacked by init() invoking the execve syscall&n; */
DECL|macro|start_thread
mdefine_line|#define start_thread(_regs, _pc, _usp)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS); /* reads from user space */&t;&bslash;&n;&t;__frame = __kernel_frame0_ptr;&t;&t;&t;&bslash;&n;&t;__frame-&gt;pc&t;= (_pc);&t;&t;&t;&bslash;&n;&t;__frame-&gt;psr&t;&amp;= ~PSR_S;&t;&t;&t;&bslash;&n;&t;__frame-&gt;sp&t;= (_usp);&t;&t;&t;&bslash;&n;} while(0)
r_extern
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/* Free all resources held by a thread. */
DECL|function|release_thread
r_static
r_inline
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
)brace
r_extern
id|asmlinkage
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|save_user_regs
c_func
(paren
r_struct
id|user_context
op_star
id|target
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|restore_user_regs
c_func
(paren
r_const
r_struct
id|user_context
op_star
id|target
)paren
suffix:semicolon
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)&t;&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
DECL|macro|forget_segments
mdefine_line|#define forget_segments()&t;&t;do { } while (0)
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_static
r_inline
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|KSTK_EIP
mdefine_line|#define&t;KSTK_EIP(tsk)&t;((tsk)-&gt;thread.frame0-&gt;pc)
DECL|macro|KSTK_ESP
mdefine_line|#define&t;KSTK_ESP(tsk)&t;((tsk)-&gt;thread.frame0-&gt;sp)
multiline_comment|/* Allocation and freeing of basic task resources. */
r_extern
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()    do { } while (0)
multiline_comment|/* data cache prefetch */
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|function|prefetch
r_static
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;dcpl %0,gr0,#0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_PROCESSOR_H */
eof
