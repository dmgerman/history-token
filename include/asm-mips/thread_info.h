multiline_comment|/* thread_info.h: i386 low-level thread information&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * low level task data that entry.S needs immediate access to&n; * - this struct should fit entirely inside of one cache line&n; * - this struct shares the supervisor stack pages&n; * - if the contents of this structure are changed, the assembly constants&n; *   must also be changed&n; */
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
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* current CPU */
DECL|member|preempt_count
id|__s32
id|preempt_count
suffix:semicolon
multiline_comment|/* 0 =&gt; preemptable, &lt;0 =&gt; BUG */
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
multiline_comment|/* thread address space:&n;&t;&t;&t;&t;&t; &t;   0-0xBFFFFFFF for user-thead&n;&t;&t;&t;&t;&t;&t;   0-0xFFFFFFFF for kernel-thread&n;&t;&t;&t;&t;&t;&t;*/
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; *&n; * preempt_count needs to be 1 initially, until the scheduler is functional.&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.preempt_count&t;= 1,&t;&t;&t;&bslash;&n;&t;.addr_limit&t;= KERNEL_DS,&t;&t;&bslash;&n;&t;.restart_block&t;= {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/* How to get the thread information struct from C.  */
r_register
r_struct
id|thread_info
op_star
id|__current_thread_info
id|__asm__
c_func
(paren
l_string|&quot;$28&quot;
)paren
suffix:semicolon
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()  __current_thread_info
multiline_comment|/* thread information allocation */
DECL|macro|THREAD_SIZE_ORDER
mdefine_line|#define THREAD_SIZE_ORDER (1)
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (PAGE_SIZE &lt;&lt; THREAD_SIZE_ORDER)
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk) ((struct thread_info *) &bslash;&n;&t;__get_free_pages(GFP_KERNEL,THREAD_SIZE_ORDER))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) free_pages((unsigned long) (ti), THREAD_SIZE_ORDER)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * thread information flags&n; * - these are process state flags that various assembly files may need to&n; *   access&n; * - pending work-to-be-done flags are in LSW&n; * - other flags in MSW&n; */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_USEDFPU
mdefine_line|#define TIF_USEDFPU&t;&t;16&t;/* FPU was used by this task this quantum (SMP) */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;17&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;31&t;/* syscall trace active */
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
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK&t;&t;0x0000fffe&t;/* work to do on&n;                                                   interrupt/exception return */
DECL|macro|_TIF_ALLWORK_MASK
mdefine_line|#define _TIF_ALLWORK_MASK&t;0x8000fffe&t;/* work to do on any return to&n;                                                   u-space */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
