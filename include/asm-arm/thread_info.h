multiline_comment|/*&n; *  linux/include/asm-arm/thread_info.h&n; *&n; *  Copyright (C) 2002 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_THREAD_INFO_H
DECL|macro|__ASM_ARM_THREAD_INFO_H
mdefine_line|#define __ASM_ARM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_struct
id|task_struct
suffix:semicolon
r_struct
id|exec_domain
suffix:semicolon
macro_line|#include &lt;asm/fpstate.h&gt;
macro_line|#include &lt;asm/proc/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|typedef|mm_segment_t
r_typedef
r_int
r_int
id|mm_segment_t
suffix:semicolon
multiline_comment|/* domain register&t;*/
multiline_comment|/*&n; * low level task data that entry.S needs immediate access to.&n; */
DECL|struct|thread_info
r_struct
id|thread_info
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* low level flags */
DECL|member|preempt_count
id|__s32
id|preempt_count
suffix:semicolon
multiline_comment|/* 0 =&gt; preemptable, &lt;0 =&gt; bug */
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
multiline_comment|/* address limit */
DECL|member|cpu
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* cpu */
DECL|member|cpu_context
r_struct
id|cpu_context_save
op_star
id|cpu_context
suffix:semicolon
multiline_comment|/* cpu context */
DECL|member|cpu_domain
id|__u32
id|cpu_domain
suffix:semicolon
multiline_comment|/* cpu domain */
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
DECL|member|fpstate
r_union
id|fp_state
id|fpstate
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;task:&t;&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;exec_domain:&t;&amp;default_exec_domain,&t;&bslash;&n;&t;flags:&t;&t;0,&t;&t;&t;&bslash;&n;&t;preempt_count:&t;0,&t;&t;&t;&bslash;&n;&t;addr_limit:&t;KERNEL_DS,&t;&t;&bslash;&n;&t;INIT_EXTRA_THREAD_INFO,&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/*&n; * how to get the thread information struct from C&n; */
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
id|__attribute__
(paren
(paren
id|__const__
)paren
)paren
suffix:semicolon
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
r_register
r_int
r_int
id|sp
id|asm
(paren
l_string|&quot;sp&quot;
)paren
suffix:semicolon
r_return
(paren
r_struct
id|thread_info
op_star
)paren
(paren
id|sp
op_amp
op_complement
l_int|0x1fff
)paren
suffix:semicolon
)brace
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;(8192)
r_extern
r_struct
id|thread_info
op_star
id|alloc_thread_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_thread_info
c_func
(paren
r_struct
id|thread_info
op_star
)paren
suffix:semicolon
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti)&t;get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti)&t;put_task_struct((ti)-&gt;task)
DECL|function|__thread_saved_pc
r_static
r_inline
r_int
r_int
id|__thread_saved_pc
c_func
(paren
r_struct
id|thread_info
op_star
id|thread
)paren
(brace
r_struct
id|cpu_context_save
op_star
id|context
op_assign
id|thread-&gt;cpu_context
suffix:semicolon
r_return
id|context
ques
c_cond
id|pc_pointer
c_func
(paren
id|context-&gt;pc
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|__thread_saved_fp
r_static
r_inline
r_int
r_int
id|__thread_saved_fp
c_func
(paren
r_struct
id|thread_info
op_star
id|thread
)paren
(brace
r_struct
id|cpu_context_save
op_star
id|context
op_assign
id|thread-&gt;cpu_context
suffix:semicolon
r_return
id|context
ques
c_cond
id|context-&gt;fp
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(tsk)&t;__thread_saved_pc((tsk)-&gt;thread_info)
DECL|macro|thread_saved_fp
mdefine_line|#define thread_saved_fp(tsk)&t;__thread_saved_fp((tsk)-&gt;thread_info)
macro_line|#else /* !__ASSEMBLY__ */
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;0
DECL|macro|TI_PREEMPT
mdefine_line|#define TI_PREEMPT&t;4
DECL|macro|TI_ADDR_LIMIT
mdefine_line|#define TI_ADDR_LIMIT&t;8
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;12
DECL|macro|TI_CPU_SAVE
mdefine_line|#define TI_CPU_SAVE&t;16
DECL|macro|TI_CPU_DOMAIN
mdefine_line|#define TI_CPU_DOMAIN&t;20
DECL|macro|TI_TASK
mdefine_line|#define TI_TASK&t;&t;24
DECL|macro|TI_EXEC_DOMAIN
mdefine_line|#define TI_EXEC_DOMAIN&t;28
DECL|macro|TI_FPSTATE
mdefine_line|#define TI_FPSTATE&t;32
macro_line|#endif
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;0x04000000
multiline_comment|/*&n; * thread information flags:&n; *  TIF_SYSCALL_TRACE&t;- syscall trace active&n; *  TIF_NOTIFY_RESUME&t;- resumption notification requested&n; *  TIF_SIGPENDING&t;- signal pending&n; *  TIF_NEED_RESCHED&t;- rescheduling necessary&n; *  TIF_USEDFPU&t;&t;- FPU was used by this task this quantum (SMP)&n; *  TIF_POLLING_NRFLAG&t;- true if poll_idle() is polling TIF_NEED_RESCHED&n; */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;0
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;1
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;2
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;8
DECL|macro|TIF_USED_FPU
mdefine_line|#define TIF_USED_FPU&t;&t;16
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;17
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1 &lt;&lt; TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1 &lt;&lt; TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1 &lt;&lt; TIF_NEED_RESCHED)
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1 &lt;&lt; TIF_SYSCALL_TRACE)
DECL|macro|_TIF_USED_FPU
mdefine_line|#define _TIF_USED_FPU&t;&t;(1 &lt;&lt; TIF_USED_FPU)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1 &lt;&lt; TIF_POLLING_NRFLAG)
multiline_comment|/*&n; * Change these and you break ASM code in entry-common.S&n; */
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK&t;&t;0x000000ff
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_ARM_THREAD_INFO_H */
eof
