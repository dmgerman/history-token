multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_THREAD_INFO_H
DECL|macro|_ASM_IA64_THREAD_INFO_H
mdefine_line|#define _ASM_IA64_THREAD_INFO_H
macro_line|#include &lt;asm/offsets.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|TI_EXEC_DOMAIN
mdefine_line|#define TI_EXEC_DOMAIN&t;0x00
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;0x08
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;0x0c
DECL|macro|TI_ADDR_LIMIT
mdefine_line|#define TI_ADDR_LIMIT&t;0x10
DECL|macro|TI_PRE_COUNT
mdefine_line|#define TI_PRE_COUNT&t;0x18
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;0x4000000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * On IA-64, we want to keep the task structure and kernel stack together, so they can be&n; * mapped by a single TLB entry and so they can be addressed by the &quot;current&quot; pointer&n; * without having to do pointer masking.&n; */
DECL|struct|thread_info
r_struct
id|thread_info
(brace
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
)brace
suffix:semicolon
DECL|macro|INIT_THREAD_SIZE
mdefine_line|#define INIT_THREAD_SIZE&t;&t;/* tell sched.h not to declare the thread_union */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;&t;KERNEL_STACK_SIZE
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(ti)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;exec_domain:&t;&amp;default_exec_domain,&t;&bslash;&n;&t;flags:&t;&t;0,&t;&t;&t;&bslash;&n;&t;cpu:&t;&t;0,&t;&t;&t;&bslash;&n;&t;addr_limit:&t;KERNEL_DS,&t;&t;&bslash;&n;&t;preempt_count:&t;0,&t;&t;&t;&bslash;&n;}
multiline_comment|/* how to get the thread information struct from C */
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info() ((struct thread_info *) ((char *) current + IA64_TASK_SIZE))
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
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;16&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
DECL|macro|TIF_WORK_MASK
mdefine_line|#define TIF_WORK_MASK&t;&t;0x7&t;/* like TIF_ALLWORK_BITS but sans TIF_SYSCALL_TRACE */
DECL|macro|TIF_ALLWORK_MASK
mdefine_line|#define TIF_ALLWORK_MASK&t;0xf&t;/* bits 0..3 are &quot;work to do on user-return&quot; bits */
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1 &lt;&lt; TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1 &lt;&lt; TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1 &lt;&lt; TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1 &lt;&lt; TIF_NEED_RESCHED)
DECL|macro|_TIF_USEDFPU
mdefine_line|#define _TIF_USEDFPU&t;&t;(1 &lt;&lt; TIF_USEDFPU)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1 &lt;&lt; TIF_POLLING_NRFLAG)
macro_line|#endif /* _ASM_IA64_THREAD_INFO_H */
eof
