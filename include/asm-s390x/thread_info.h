multiline_comment|/*&n; *  include/asm-s390/thread_info.h&n; *&n; *  S390 version&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * low level task data that entry.S needs immediate access to&n; * - this struct should fit entirely inside of one cache line&n; * - this struct shares the supervisor stack pages&n; * - if the contents of this structure are changed, the assembly constants must also be changed&n; */
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
r_int
id|cpu
suffix:semicolon
multiline_comment|/* current CPU */
DECL|member|preempt_count
r_int
id|preempt_count
suffix:semicolon
multiline_comment|/* 0 =&gt; preemptable, &lt;0 =&gt; BUG */
)brace
suffix:semicolon
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
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
r_return
(paren
r_struct
id|thread_info
op_star
)paren
(paren
(paren
op_star
(paren
r_int
r_int
op_star
)paren
l_int|0xd40
)paren
op_minus
l_int|16384
)paren
suffix:semicolon
)brace
multiline_comment|/* thread information allocation */
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info() ((struct thread_info *) &bslash;&n;&t;__get_free_pages(GFP_KERNEL,2))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) free_pages((unsigned long) (ti), 2)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
macro_line|#endif
multiline_comment|/*&n; * Size of kernel stack for each process&n; */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (4*PAGE_SIZE)
multiline_comment|/*&n; * thread information flags bit numbers&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_USEDFPU
mdefine_line|#define TIF_USEDFPU&t;&t;16&t;/* FPU was used by this task this quantum (SMP) */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;17&t;/* true if poll_idle() is polling &n;&t;&t;&t;&t;&t;   TIF_NEED_RESCHED */
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
