multiline_comment|/*&n; * thread_info.h: sparc low-level thread information&n; * adapted from the ppc version by Pete Zaitcev, which was&n; * adapted from the i386 version by Paul Mackerras&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * Copyright (c) 2002  Pete Zaitcev (zaitcev@yahoo.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Low level task data.&n; *&n; * If you change this, change the TI_* offsets below to match.&n; */
DECL|macro|NSWINS
mdefine_line|#define NSWINS 8
DECL|struct|thread_info
r_struct
id|thread_info
(brace
DECL|member|uwinmask
r_int
r_int
id|uwinmask
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
multiline_comment|/* main task structure */
DECL|member|exec_domain
r_struct
id|exec_domain
op_star
id|exec_domain
suffix:semicolon
multiline_comment|/* execution domain */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* low level flags */
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu we&squot;re on */
DECL|member|preempt_count
r_int
id|preempt_count
suffix:semicolon
DECL|member|softirq_count
r_int
id|softirq_count
suffix:semicolon
DECL|member|hardirq_count
r_int
id|hardirq_count
suffix:semicolon
multiline_comment|/* Context switch saved kernel state. */
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* ... ksp __attribute__ ((aligned (8))); */
DECL|member|kpc
r_int
r_int
id|kpc
suffix:semicolon
DECL|member|kpsr
r_int
r_int
id|kpsr
suffix:semicolon
DECL|member|kwim
r_int
r_int
id|kwim
suffix:semicolon
multiline_comment|/* A place to store user windows and stack pointers&n;&t; * when the stack needs inspection.&n;&t; */
DECL|member|reg_window
r_struct
id|reg_window
id|reg_window
(braket
id|NSWINS
)braket
suffix:semicolon
multiline_comment|/* align for ldd! */
DECL|member|rwbuf_stkptrs
r_int
r_int
id|rwbuf_stkptrs
(braket
id|NSWINS
)braket
suffix:semicolon
DECL|member|w_saved
r_int
r_int
id|w_saved
suffix:semicolon
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; *&n; * preempt_count needs to be 1 initially, until the scheduler is functional.&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.uwinmask&t;=&t;0,&t;&t;&t;&bslash;&n;&t;.task&t;&t;=&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;=&t;&amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;=&t;0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;=&t;0,&t;&t;&t;&bslash;&n;&t;.preempt_count&t;=&t;1,&t;&t;&t;&bslash;&n;&t;.restart_block&t;= {&t;&t;&t;&t;&bslash;&n;&t;&t;.fn&t;=&t;do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/* how to get the thread information struct from C */
r_register
r_struct
id|thread_info
op_star
id|current_thread_info_reg
id|asm
c_func
(paren
l_string|&quot;g6&quot;
)paren
suffix:semicolon
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()   (current_thread_info_reg)
multiline_comment|/*&n; * thread information allocation&n; */
macro_line|#if PAGE_SHIFT == 13
DECL|macro|THREAD_INFO_ORDER
mdefine_line|#define THREAD_INFO_ORDER  0
macro_line|#else /* PAGE_SHIFT */
DECL|macro|THREAD_INFO_ORDER
mdefine_line|#define THREAD_INFO_ORDER  1
macro_line|#endif
id|BTFIXUPDEF_CALL
c_func
(paren
r_struct
id|thread_info
op_star
comma
id|alloc_thread_info
comma
r_void
)paren
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk) BTFIXUP_CALL(alloc_thread_info)()
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|free_thread_info
comma
r_struct
id|thread_info
op_star
)paren
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) BTFIXUP_CALL(free_thread_info)(ti)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti)&t;get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti)&t;put_task_struct((ti)-&gt;task)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Size of kernel stack for each process.&n; * Observe the order of get_free_pages() in alloc_thread_info().&n; * The sun4 has 8K stack too, because it&squot;s short on memory, and 16K is a waste.&n; */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;8192
multiline_comment|/*&n; * Offsets in thread_info structure, used in assembly code&n; * The &quot;#define REGWIN_SZ 0x40&quot; was abolished, so no multiplications.&n; */
DECL|macro|TI_UWINMASK
mdefine_line|#define TI_UWINMASK&t;0x00&t;/* uwinmask */
DECL|macro|TI_TASK
mdefine_line|#define TI_TASK&t;&t;0x04
DECL|macro|TI_EXECDOMAIN
mdefine_line|#define TI_EXECDOMAIN&t;0x08&t;/* exec_domain */
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;0x0c
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;0x10
DECL|macro|TI_PREEMPT
mdefine_line|#define TI_PREEMPT&t;0x14&t;/* preempt_count */
DECL|macro|TI_SOFTIRQ
mdefine_line|#define TI_SOFTIRQ&t;0x18&t;/* softirq_count */
DECL|macro|TI_HARDIRQ
mdefine_line|#define TI_HARDIRQ&t;0x1c&t;/* hardirq_count */
DECL|macro|TI_KSP
mdefine_line|#define TI_KSP&t;&t;0x20&t;/* ksp */
DECL|macro|TI_KPC
mdefine_line|#define TI_KPC&t;&t;0x24&t;/* kpc (ldd&squot;ed with kpc) */
DECL|macro|TI_KPSR
mdefine_line|#define TI_KPSR&t;&t;0x28&t;/* kpsr */
DECL|macro|TI_KWIM
mdefine_line|#define TI_KWIM&t;&t;0x2c&t;/* kwim (ldd&squot;ed with kpsr) */
DECL|macro|TI_REG_WINDOW
mdefine_line|#define TI_REG_WINDOW&t;0x30
DECL|macro|TI_RWIN_SPTRS
mdefine_line|#define TI_RWIN_SPTRS&t;0x230
DECL|macro|TI_W_SAVED
mdefine_line|#define TI_W_SAVED&t;0x250
multiline_comment|/* #define TI_RESTART_BLOCK 0x25n */
multiline_comment|/* Nobody cares */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
multiline_comment|/*&n; * thread information flag bit numbers&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_USEDFPU
mdefine_line|#define TIF_USEDFPU&t;&t;8&t;/* FPU was used by this task&n;&t;&t;&t;&t;&t; * this quantum (SMP) */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;9&t;/* true if poll_idle() is polling&n;&t;&t;&t;&t;&t; * TIF_NEED_RESCHED */
DECL|macro|TIF_MEMDIE
mdefine_line|#define TIF_MEMDIE&t;&t;10
multiline_comment|/* as above, but as bit values */
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1&lt;&lt;TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1&lt;&lt;TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1&lt;&lt;TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1&lt;&lt;TIF_NEED_RESCHED)
DECL|macro|_TIF_USEDFPU
mdefine_line|#define _TIF_USEDFPU&t;&t;(1&lt;&lt;TIF_USEDFPU)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
