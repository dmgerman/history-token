multiline_comment|/*&n; * Copyright (C) 2002-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_THREAD_INFO_H
DECL|macro|_ASM_IA64_THREAD_INFO_H
mdefine_line|#define _ASM_IA64_THREAD_INFO_H
macro_line|#include &lt;asm/offsets.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|PREEMPT_ACTIVE_BIT
mdefine_line|#define PREEMPT_ACTIVE_BIT 30
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;(1 &lt;&lt; PREEMPT_ACTIVE_BIT)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * On IA-64, we want to keep the task structure and kernel stack together, so they can be&n; * mapped by a single TLB entry and so they can be addressed by the &quot;current&quot; pointer&n; * without having to do pointer masking.&n; */
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
multiline_comment|/* XXX not really needed, except for dup_task_struct() */
DECL|member|exec_domain
r_struct
id|exec_domain
op_star
id|exec_domain
suffix:semicolon
multiline_comment|/* execution domain */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* thread_info flags (see TIF_*) */
DECL|member|cpu
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* current CPU */
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
multiline_comment|/* user-level address space limit */
DECL|member|preempt_count
id|__s32
id|preempt_count
suffix:semicolon
multiline_comment|/* 0=premptable, &lt;0=BUG; will also serve as bh-counter */
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
r_struct
(brace
DECL|member|signo
r_int
id|signo
suffix:semicolon
DECL|member|code
r_int
id|code
suffix:semicolon
DECL|member|addr
r_void
id|__user
op_star
id|addr
suffix:semicolon
DECL|member|start_time
r_int
r_int
id|start_time
suffix:semicolon
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|sigdelayed
)brace
id|sigdelayed
suffix:semicolon
multiline_comment|/* Saved information for TIF_SIGDELAYED */
)brace
suffix:semicolon
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;&t;KERNEL_STACK_SIZE
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.addr_limit&t;= KERNEL_DS,&t;&t;&bslash;&n;&t;.preempt_count&t;= 0,&t;&t;&t;&bslash;&n;&t;.restart_block = {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/* how to get the thread information struct from C */
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()&t;((struct thread_info *) ((char *) current + IA64_TASK_SIZE))
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk)&t;((struct thread_info *) ((char *) (tsk) + IA64_TASK_SIZE))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)&t;/* nothing */
DECL|macro|__HAVE_ARCH_TASK_STRUCT_ALLOCATOR
mdefine_line|#define __HAVE_ARCH_TASK_STRUCT_ALLOCATOR
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()&t;((task_t *)__get_free_pages(GFP_KERNEL, KERNEL_STACK_SIZE_ORDER))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(tsk)&t;free_pages((unsigned long) (tsk), KERNEL_STACK_SIZE_ORDER)
macro_line|#endif /* !__ASSEMBLY */
multiline_comment|/*&n; * thread information flags&n; * - these are process state flags that various assembly files may need to access&n; * - pending work-to-be-done flags are in least-significant 16 bits, other flags&n; *   in top 16 bits&n; */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;0&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;1&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;2&t;/* rescheduling necessary */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;3&t;/* syscall trace active */
DECL|macro|TIF_SYSCALL_AUDIT
mdefine_line|#define TIF_SYSCALL_AUDIT&t;4&t;/* syscall auditing active */
DECL|macro|TIF_SIGDELAYED
mdefine_line|#define TIF_SIGDELAYED&t;&t;5&t;/* signal delayed from MCA/INIT/NMI/PMI context */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;16&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1 &lt;&lt; TIF_SYSCALL_TRACE)
DECL|macro|_TIF_SYSCALL_AUDIT
mdefine_line|#define _TIF_SYSCALL_AUDIT&t;(1 &lt;&lt; TIF_SYSCALL_AUDIT)
DECL|macro|_TIF_SYSCALL_TRACEAUDIT
mdefine_line|#define _TIF_SYSCALL_TRACEAUDIT&t;(_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1 &lt;&lt; TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1 &lt;&lt; TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1 &lt;&lt; TIF_NEED_RESCHED)
DECL|macro|_TIF_SIGDELAYED
mdefine_line|#define _TIF_SIGDELAYED&t;(1 &lt;&lt; TIF_SIGDELAYED)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1 &lt;&lt; TIF_POLLING_NRFLAG)
multiline_comment|/* &quot;work to do on user-return&quot; bits */
DECL|macro|TIF_ALLWORK_MASK
mdefine_line|#define TIF_ALLWORK_MASK&t;(_TIF_NOTIFY_RESUME|_TIF_SIGPENDING|_TIF_NEED_RESCHED|_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT|_TIF_SIGDELAYED)
multiline_comment|/* like TIF_ALLWORK_BITS but sans TIF_SYSCALL_TRACE or TIF_SYSCALL_AUDIT */
DECL|macro|TIF_WORK_MASK
mdefine_line|#define TIF_WORK_MASK&t;&t;(TIF_ALLWORK_MASK&amp;~(_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT))
macro_line|#endif /* _ASM_IA64_THREAD_INFO_H */
eof
