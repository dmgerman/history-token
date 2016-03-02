multiline_comment|/*&n; * thread_info.h: sparc low-level thread information&n; * adapted from the ppc version by Pete Zaitcev, which was&n; * adapted from the i386 version by Paul Mackerras&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * Copyright (c) 2002  Pete Zaitcev (zaitcev@yahoo.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
singleline_comment|// XXX todo: comment thread_info components and see what breaks.
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/btfixup.h&gt;
multiline_comment|/*&n; * Low level task data.&n; *&n; * If you change this, change the TI_* offsets below to match. XXX check_asm.&n; *&n; * The uwinmask is a first class citizen among w_saved and friends.&n; * XXX Is this a good idea? wof.S/wuf.S have to use w_saved anyway,&n; *     so they waste a register on current, and an ld on fetching it.&n; */
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
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.uwinmask&t;=&t;0,&t;&t;&t;&bslash;&n;&t;.task&t;&t;=&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;=&t;&amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;=&t;0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;=&t;0,&t;&t;&t;&bslash;&n;&t;.restart_block&t;= {&t;&t;&t;&t;&bslash;&n;&t;&t;.fn&t;=&t;do_no_restart_syscall,&t;&bslash;&n;&t;},
)brace
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
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
mdefine_line|#define current_thread_info()   (current_thread_info_reg)
multiline_comment|/*&n; * thread information allocation&n; */
macro_line|#ifdef CONFIG_SUN4
mdefine_line|#define THREAD_INFO_ORDER  0
macro_line|#else
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
mdefine_line|#define alloc_thread_info() BTFIXUP_CALL(alloc_thread_info)()
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
mdefine_line|#define free_thread_info(ti) BTFIXUP_CALL(free_thread_info)(ti)
mdefine_line|#define get_thread_info(ti)&t;get_task_struct((ti)-&gt;task)
mdefine_line|#define put_thread_info(ti)&t;put_task_struct((ti)-&gt;task)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Size of kernel stack for each process.&n; * Observe the order of get_free_pages() in alloc_thread_info().&n; * The sun4 has 8K stack too, because it&squot;s short on memory, and 16K is a waste.&n; *&n; * XXX Watch how INIT_THREAD_SIZE evolves in linux/sched.h and elsewhere.&n; *     On 2.5.24 it happens to match 8192 magically.&n; */
mdefine_line|#define THREAD_SIZE&t;&t;8192
multiline_comment|/*&n; * Offsets in thread_info structure, used in assembly code&n; */
mdefine_line|#define TI_UWINMASK&t;0x00&t;/* uwinmask */
mdefine_line|#define TI_TASK&t;&t;0x04
mdefine_line|#define TI_EXECDOMAIN&t;0x08&t;/* exec_domain */
mdefine_line|#define TI_FLAGS&t;0x0c
mdefine_line|#define TI_CPU&t;&t;0x10
mdefine_line|#define TI_PREEMPT&t;0x14&t;/* preempt_count */
mdefine_line|#define TI_SOFTIRQ&t;0x18&t;/* softirq_count */
mdefine_line|#define TI_HARDIRQ&t;0x1c&t;/* hardirq_count */
mdefine_line|#define TI_KSP&t;&t;0x20&t;/* ksp */
mdefine_line|#define TI_KPC&t;&t;0x24&t;/* kpc (ldd&squot;ed with kpc) */
mdefine_line|#define TI_KPSR&t;&t;0x28&t;/* kpsr */
mdefine_line|#define TI_KWIM&t;&t;0x2c&t;/* kwim (ldd&squot;ed with kpsr) */
mdefine_line|#define TI_RESTART_BLOCK 0x30
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
multiline_comment|/*&n; * thread information flag bit numbers&n; */
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
mdefine_line|#define TIF_USEDFPU&t;&t;8&t;/* FPU was used by this task&n;&t;&t;&t;&t;&t; * this quantum (SMP) */
mdefine_line|#define TIF_POLLING_NRFLAG&t;9&t;/* true if poll_idle() is polling&n;&t;&t;&t;&t;&t; * TIF_NEED_RESCHED */
multiline_comment|/* as above, but as bit values */
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1&lt;&lt;TIF_SYSCALL_TRACE)
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1&lt;&lt;TIF_NOTIFY_RESUME)
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1&lt;&lt;TIF_SIGPENDING)
mdefine_line|#define _TIF_NEED_RESCHED&t;(1&lt;&lt;TIF_NEED_RESCHED)
mdefine_line|#define _TIF_USEDFPU&t;&t;(1&lt;&lt;TIF_USEDFPU)
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
