multiline_comment|/*&n; * include/asm-cris/processor.h&n; *&n; * Copyright (C) 2000, 2001 Axis Communications AB&n; *&n; * Authors:         Bjorn Wesen        Initial version&n; *&n; */
macro_line|#ifndef __ASM_CRIS_PROCESSOR_H
DECL|macro|__ASM_CRIS_PROCESSOR_H
mdefine_line|#define __ASM_CRIS_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/arch/processor.h&gt;
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE      (PAGE_ALIGN(TASK_SIZE / 3))
multiline_comment|/* THREAD_SIZE is the size of the task_struct/kernel_stack combo.&n; * normally, the stack is found by doing something like p + THREAD_SIZE&n; * in CRIS, a page is 8192 bytes, which seems like a sane size&n; */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE       PAGE_SIZE
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE PAGE_SIZE
multiline_comment|/*&n; * At user-&gt;kernel entry, the pt_regs struct is stacked on the top of the kernel-stack.&n; * This macro allows us to find those regs for a task.&n; * Notice that subsequent pt_regs stackings, like recursive interrupts occurring while&n; * we&squot;re in the kernel, won&squot;t affect this - only the first user-&gt;kernel transition&n; * registers are reached by this.&n; */
DECL|macro|user_regs
mdefine_line|#define user_regs(thread_info) (((struct pt_regs *)((unsigned long)(thread_info) + THREAD_SIZE)) - 1)
multiline_comment|/*&n; * Dito but for the currently running task&n; */
DECL|macro|current_regs
mdefine_line|#define current_regs() user_regs(current-&gt;thread_info)
DECL|function|prepare_to_copy
r_extern
r_inline
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
)brace
r_extern
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
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)   ((tsk) == current ? rdusp() : (tsk)-&gt;thread.usp)
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_extern
r_inline
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing needs to be done.  */
)brace
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
multiline_comment|/* Free all resources held by a thread. */
DECL|function|release_thread
r_extern
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
multiline_comment|/* Nothing needs to be done.  */
)brace
DECL|macro|init_stack
mdefine_line|#define init_stack      (init_thread_union.stack)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()     barrier()
macro_line|#endif /* __ASM_CRIS_PROCESSOR_H */
eof
