multiline_comment|/* thread_info.h: PPC low-level thread information&n; * adapted from the i386 version by Paul Mackerras&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * low level task data.&n; * If you change this, change the TI_* offsets below to match.&n; */
DECL|struct|thread_info
r_struct
id|thread_info
(brace
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
multiline_comment|/* not used at present */
DECL|member|softirq_count
r_int
id|softirq_count
suffix:semicolon
DECL|member|hardirq_count
r_int
id|hardirq_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;task:&t;&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;exec_domain:&t;&amp;default_exec_domain,&t;&bslash;&n;&t;flags:&t;&t;0,&t;&t;&t;&bslash;&n;&t;cpu:&t;&t;0,&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/* how to get the thread information struct from C */
DECL|function|current_thread_info
r_static
r_inline
r_struct
id|thread_info
op_star
id|current_thread_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_info
op_star
id|ti
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rlwinm %0,1,0,0,18&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti
)paren
)paren
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
multiline_comment|/* thread information allocation */
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info() ((struct thread_info *) &bslash;&n;&t;&t;&t;&t;__get_free_pages(GFP_KERNEL, 1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)&t;free_pages((unsigned long) (ti), 1)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti)&t;get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti)&t;put_task_struct((ti)-&gt;task)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Size of kernel stack for each process.&n; */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;8192&t;/* 2 pages */
multiline_comment|/*&n; * Offsets in thread_info structure, used in assembly code&n; */
DECL|macro|TI_TASK
mdefine_line|#define TI_TASK&t;&t;0
DECL|macro|TI_EXECDOMAIN
mdefine_line|#define TI_EXECDOMAIN&t;4
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;8
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;12
DECL|macro|TI_PREEMPT
mdefine_line|#define TI_PREEMPT&t;16
DECL|macro|TI_SOFTIRQ
mdefine_line|#define TI_SOFTIRQ&t;20
DECL|macro|TI_HARDIRQ
mdefine_line|#define TI_HARDIRQ&t;24
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
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;4&t;/* true if poll_idle() is polling&n;&t;&t;&t;&t;&t;   TIF_NEED_RESCHED */
multiline_comment|/* as above, but as bit values */
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1&lt;&lt;TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1&lt;&lt;TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1&lt;&lt;TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1&lt;&lt;TIF_NEED_RESCHED)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
