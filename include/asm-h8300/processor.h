multiline_comment|/*&n; * include/asm-h8300/processor.h&n; *&n; * Copyright (C) 2002 Yoshinori Sato&n; *&n; * Based on: linux/asm-m68nommu/processor.h&n; *&n; * Copyright (C) 1995 Hamish Macdonald&n; */
macro_line|#ifndef __ASM_H8300_PROCESSOR_H
DECL|macro|__ASM_H8300_PROCESSOR_H
mdefine_line|#define __ASM_H8300_PROCESSOR_H
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/current.h&gt;
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
r_extern
r_int
r_int
id|sw_usp
suffix:semicolon
r_return
id|sw_usp
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
r_extern
r_int
r_int
id|sw_usp
suffix:semicolon
id|sw_usp
op_assign
id|usp
suffix:semicolon
)brace
multiline_comment|/*&n; * User space process size: 3.75GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xFFFFFFFFUL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s. We won&squot;t be using it&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;0
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
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
multiline_comment|/* saved status register */
DECL|member|esp0
r_int
r_int
id|esp0
suffix:semicolon
multiline_comment|/* points to SR of stack frame */
r_struct
(brace
DECL|member|addr
r_int
r_int
op_star
id|addr
suffix:semicolon
DECL|member|inst
r_int
r_int
id|inst
suffix:semicolon
DECL|member|breakinfo
)brace
id|breakinfo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.ksp  = sizeof(init_stack) + (unsigned long)init_stack, &bslash;&n;&t;.usp  = 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.ccr  = PS_S,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.esp0 = 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.breakinfo = {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.addr = (unsigned short *)-1,&t;&t;&t;&bslash;&n;&t;&t;.inst = 0&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; *&n; * pass the data segment into user programs if it exists,&n; * it can&squot;t hurt anything as far as I can tell&n; */
macro_line|#if defined(__H8300H__)
DECL|macro|start_thread
mdefine_line|#define start_thread(_regs, _pc, _usp)&t;&t;&t;        &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;        &bslash;&n;&t;set_fs(USER_DS);           /* reads from user space */  &bslash;&n;  &t;(_regs)-&gt;pc = (_pc);&t;&t;&t;&t;        &bslash;&n;&t;(_regs)-&gt;ccr &amp;= 0x00;&t;   /* clear kernel flag */      &bslash;&n;&t;(_regs)-&gt;er5 = current-&gt;mm-&gt;start_data;&t;/* GOT base */  &bslash;&n;&t;wrusp((unsigned long)(_usp) - sizeof(unsigned long)*3);&t;&bslash;&n;} while(0)
macro_line|#endif
macro_line|#if defined(__H8300S__)
DECL|macro|start_thread
mdefine_line|#define start_thread(_regs, _pc, _usp)&t;&t;&t;        &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;        &bslash;&n;&t;set_fs(USER_DS);           /* reads from user space */  &bslash;&n;&t;(_regs)-&gt;pc = (_pc);&t;&t;&t;&t;        &bslash;&n;&t;(_regs)-&gt;ccr = 0x00;&t;   /* clear kernel flag */      &bslash;&n;&t;(_regs)-&gt;exr = 0x78;       /* enable all interrupts */  &bslash;&n;&t;(_regs)-&gt;er5 = current-&gt;mm-&gt;start_data;&t;/* GOT base */  &bslash;&n;&t;/* 14 = space for retaddr(4), vector(4), er0(4) and ext(2) on stack */ &bslash;&n;&t;wrusp(((unsigned long)(_usp)) - 14);                    &bslash;&n;} while(0)
macro_line|#endif
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
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
mdefine_line|#define&t;KSTK_EIP(tsk)&t;&bslash;&n;    ({&t;&t;&t;&bslash;&n;&t;unsigned long eip = 0;&t; &bslash;&n;&t;if ((tsk)-&gt;thread.esp0 &gt; PAGE_SIZE &amp;&amp; &bslash;&n;&t;    MAP_NR((tsk)-&gt;thread.esp0) &lt; max_mapnr) &bslash;&n;&t;      eip = ((struct pt_regs *) (tsk)-&gt;thread.esp0)-&gt;pc; &bslash;&n;&t;eip; })
DECL|macro|KSTK_ESP
mdefine_line|#define&t;KSTK_ESP(tsk)&t;((tsk) == current ? rdusp() : (tsk)-&gt;thread.usp)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()    do { } while (0)
macro_line|#endif
eof
