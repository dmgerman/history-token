multiline_comment|/*&n; * include/asm-m68k/processor.h&n; *&n; * Copyright (C) 1995 Hamish Macdonald&n; */
macro_line|#ifndef __ASM_M68K_PROCESSOR_H
DECL|macro|__ASM_M68K_PROCESSOR_H
mdefine_line|#define __ASM_M68K_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|function|rdusp
r_static
r_inline
r_int
r_int
id|rdusp
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|usp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move %/usp,%0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|usp
)paren
)paren
suffix:semicolon
r_return
id|usp
suffix:semicolon
)brace
DECL|function|wrusp
r_static
r_inline
r_void
id|wrusp
c_func
(paren
r_int
r_int
id|usp
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move %0,%/usp&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|usp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * User space process size: 3.75GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
macro_line|#ifndef CONFIG_SUN3
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xF0000000UL)
macro_line|#else
macro_line|#ifdef __ASSEMBLY__
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x0E000000)
macro_line|#else
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x0E000000UL)
macro_line|#endif
macro_line|#endif
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
macro_line|#ifndef CONFIG_SUN3
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;0xC0000000UL
macro_line|#else
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;0x0A000000UL
macro_line|#endif
DECL|macro|TASK_UNMAPPED_ALIGN
mdefine_line|#define TASK_UNMAPPED_ALIGN(addr, off)&t;PAGE_ALIGN(addr)
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|struct|task_work
r_struct
id|task_work
(brace
DECL|member|sigpending
r_int
r_char
id|sigpending
suffix:semicolon
DECL|member|notify_resume
r_int
r_char
id|notify_resume
suffix:semicolon
multiline_comment|/* request for notification on&n;&t;&t;&t;&t;&t;   userspace execution resumption */
DECL|member|need_resched
r_char
id|need_resched
suffix:semicolon
DECL|member|delayed_trace
r_int
r_char
id|delayed_trace
suffix:semicolon
multiline_comment|/* single step a syscall */
DECL|member|syscall_trace
r_int
r_char
id|syscall_trace
suffix:semicolon
multiline_comment|/* count of syscall interceptors */
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* user stack pointer */
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
multiline_comment|/* saved status register */
DECL|member|fs
r_int
r_int
id|fs
suffix:semicolon
multiline_comment|/* saved fs (sfc, dfc) */
DECL|member|crp
r_int
r_int
id|crp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* cpu root pointer */
DECL|member|esp0
r_int
r_int
id|esp0
suffix:semicolon
multiline_comment|/* points to SR of stack frame */
DECL|member|faddr
r_int
r_int
id|faddr
suffix:semicolon
multiline_comment|/* info about last fault */
DECL|member|signo
DECL|member|code
r_int
id|signo
comma
id|code
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
(braket
l_int|8
op_star
l_int|3
)braket
suffix:semicolon
DECL|member|fpcntl
r_int
r_int
id|fpcntl
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fp control regs */
DECL|member|fpstate
r_int
r_char
id|fpstate
(braket
id|FPSTATESIZE
)braket
suffix:semicolon
multiline_comment|/* floating point state */
DECL|member|work
r_struct
id|task_work
id|work
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ksp:&t;sizeof(init_stack) + (unsigned long) init_stack,&t;&bslash;&n;&t;sr:&t;PS_S,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;fs:&t;__KERNEL_DS,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;info:&t;INIT_THREAD_INFO(init_task)&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|function|start_thread
r_static
r_inline
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|usp
)paren
(brace
multiline_comment|/* reads from user space */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|pc
suffix:semicolon
id|regs-&gt;sr
op_and_assign
op_complement
l_int|0x2000
suffix:semicolon
id|wrusp
c_func
(paren
id|usp
)paren
suffix:semicolon
)brace
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|task_struct
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
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
mdefine_line|#define&t;KSTK_EIP(tsk)&t;&bslash;&n;    ({&t;&t;&t;&bslash;&n;&t;unsigned long eip = 0;&t; &bslash;&n;&t;if ((tsk)-&gt;thread.esp0 &gt; PAGE_SIZE &amp;&amp; &bslash;&n;&t;    (virt_addr_valid((tsk)-&gt;thread.esp0))) &bslash;&n;&t;      eip = ((struct pt_regs *) (tsk)-&gt;thread.esp0)-&gt;pc; &bslash;&n;&t;eip; })
DECL|macro|KSTK_ESP
mdefine_line|#define&t;KSTK_ESP(tsk)&t;((tsk) == current ? rdusp() : (tsk)-&gt;thread.usp)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
macro_line|#endif
eof
