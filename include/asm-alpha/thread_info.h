macro_line|#ifndef _ALPHA_THREAD_INFO_H
DECL|macro|_ALPHA_THREAD_INFO_H
mdefine_line|#define _ALPHA_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|struct|thread_info
r_struct
id|thread_info
(brace
DECL|member|pcb
r_struct
id|pcb_struct
id|pcb
suffix:semicolon
multiline_comment|/* palcode state */
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
multiline_comment|/* main task structure */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* low level flags */
DECL|member|ieee_state
r_int
r_int
id|ieee_state
suffix:semicolon
multiline_comment|/* see fpu.h */
DECL|member|exec_domain
r_struct
id|exec_domain
op_star
id|exec_domain
suffix:semicolon
multiline_comment|/* execution domain */
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
multiline_comment|/* thread address space */
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
multiline_comment|/* current CPU */
DECL|member|preempt_count
r_int
id|preempt_count
suffix:semicolon
multiline_comment|/* 0 =&gt; preemptable, &lt;0 =&gt; BUG */
DECL|member|bpt_nsaved
r_int
id|bpt_nsaved
suffix:semicolon
DECL|member|bpt_addr
r_int
r_int
id|bpt_addr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* breakpoint handling  */
DECL|member|bpt_insn
r_int
r_int
id|bpt_insn
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Macros/functions for gaining access to the thread information structure.&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;task:&t;&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;exec_domain:&t;&amp;default_exec_domain,&t;&bslash;&n;&t;addr_limit:&t;KERNEL_DS,&t;&t;&bslash;&n;}
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
l_string|&quot;$8&quot;
)paren
suffix:semicolon
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()  __current_thread_info
multiline_comment|/* Thread information allocation.  */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info() &bslash;&n;  ((struct thread_info *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) free_pages((unsigned long) (ti), 1)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
multiline_comment|/*&n; * Thread information flags:&n; * - these are process state flags and used from assembly&n; * - pending work-to-be-done flags come first to fit in and immediate operand.&n; *&n; * TIF_SYSCALL_TRACE is known to be 0 via blbs.&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;4&t;/* poll_idle is polling NEED_RESCHED */
DECL|macro|TIF_DIE_IF_KERNEL
mdefine_line|#define TIF_DIE_IF_KERNEL&t;5&t;/* dik recursion lock */
DECL|macro|TIF_UAC_NOPRINT
mdefine_line|#define TIF_UAC_NOPRINT&t;&t;6&t;/* see sysinfo.h */
DECL|macro|TIF_UAC_NOFIX
mdefine_line|#define TIF_UAC_NOFIX&t;&t;7
DECL|macro|TIF_UAC_SIGBUS
mdefine_line|#define TIF_UAC_SIGBUS&t;&t;8
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
multiline_comment|/* Work to do on interrupt/exception return.  */
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK&t;&t;(_TIF_NOTIFY_RESUME&t;&bslash;&n;&t;&t;&t;&t; | _TIF_SIGPENDING&t;&bslash;&n;&t;&t;&t;&t; | _TIF_NEED_RESCHED)
multiline_comment|/* Work to do on any return to userspace.  */
DECL|macro|_TIF_ALLWORK_MASK
mdefine_line|#define _TIF_ALLWORK_MASK&t;(_TIF_WORK_MASK&t;&t;&bslash;&n;&t;&t;&t;&t; | _TIF_SYSCALL_TRACE)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ALPHA_THREAD_INFO_H */
eof
