multiline_comment|/*&n; *  linux/include/asm-arm/thread_info.h&n; *&n; *  Copyright (C) 2002 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_THREAD_INFO_H
DECL|macro|__ASM_ARM_THREAD_INFO_H
mdefine_line|#define __ASM_ARM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/fpstate.h&gt;
macro_line|#ifndef __ASSEMBLY__
r_struct
id|task_struct
suffix:semicolon
r_struct
id|exec_domain
suffix:semicolon
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/domain.h&gt;
DECL|typedef|mm_segment_t
r_typedef
r_int
r_int
id|mm_segment_t
suffix:semicolon
DECL|struct|cpu_context_save
r_struct
id|cpu_context_save
(brace
DECL|member|r4
id|__u32
id|r4
suffix:semicolon
DECL|member|r5
id|__u32
id|r5
suffix:semicolon
DECL|member|r6
id|__u32
id|r6
suffix:semicolon
DECL|member|r7
id|__u32
id|r7
suffix:semicolon
DECL|member|r8
id|__u32
id|r8
suffix:semicolon
DECL|member|r9
id|__u32
id|r9
suffix:semicolon
DECL|member|sl
id|__u32
id|sl
suffix:semicolon
DECL|member|fp
id|__u32
id|fp
suffix:semicolon
DECL|member|sp
id|__u32
id|sp
suffix:semicolon
DECL|member|pc
id|__u32
id|pc
suffix:semicolon
DECL|member|extra
id|__u32
id|extra
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Xscale &squot;acc&squot; register, etc */
)brace
suffix:semicolon
multiline_comment|/*&n; * low level task data that entry.S needs immediate access to.&n; * __switch_to() assumes cpu_context follows immediately after cpu_domain.&n; */
DECL|struct|thread_info
r_struct
id|thread_info
(brace
DECL|member|flags
r_int
r_int
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
DECL|member|cpu
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* cpu */
DECL|member|cpu_domain
id|__u32
id|cpu_domain
suffix:semicolon
multiline_comment|/* cpu domain */
DECL|member|cpu_context
r_struct
id|cpu_context_save
id|cpu_context
suffix:semicolon
multiline_comment|/* cpu context */
DECL|member|used_cp
id|__u8
id|used_cp
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* thread used copro */
DECL|member|tp_value
r_int
r_int
id|tp_value
suffix:semicolon
DECL|member|fpstate
r_union
id|fp_state
id|fpstate
suffix:semicolon
DECL|member|vfpstate
r_union
id|vfp_state
id|vfpstate
suffix:semicolon
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&t;&t;&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.preempt_count&t;= 1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.addr_limit&t;= KERNEL_DS,&t;&t;&t;&t;&t;&bslash;&n;&t;.cpu_domain&t;= domain_val(DOMAIN_USER, DOMAIN_MANAGER) |&t;&bslash;&n;&t;&t;&t;  domain_val(DOMAIN_KERNEL, DOMAIN_MANAGER) |&t;&bslash;&n;&t;&t;&t;  domain_val(DOMAIN_IO, DOMAIN_CLIENT),&t;&t;&bslash;&n;&t;.restart_block&t;= {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.fn&t;= do_no_restart_syscall,&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;8192
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
id|__attribute_const__
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
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|thread_info
op_star
id|alloc_thread_info
c_func
(paren
r_struct
id|task_struct
op_star
id|task
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
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(tsk)&t;&bslash;&n;&t;((unsigned long)(pc_pointer((tsk)-&gt;thread_info-&gt;cpu_context.pc)))
DECL|macro|thread_saved_fp
mdefine_line|#define thread_saved_fp(tsk)&t;&bslash;&n;&t;((unsigned long)((tsk)-&gt;thread_info-&gt;cpu_context.fp))
r_extern
r_void
id|iwmmxt_task_disable
c_func
(paren
r_struct
id|thread_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|iwmmxt_task_copy
c_func
(paren
r_struct
id|thread_info
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|iwmmxt_task_restore
c_func
(paren
r_struct
id|thread_info
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|iwmmxt_task_release
c_func
(paren
r_struct
id|thread_info
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * We use bit 30 of the preempt_count to indicate that kernel&n; * preemption is occuring.  See include/asm-arm/hardirq.h.&n; */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;0x40000000
multiline_comment|/*&n; * thread information flags:&n; *  TIF_SYSCALL_TRACE&t;- syscall trace active&n; *  TIF_NOTIFY_RESUME&t;- resumption notification requested&n; *  TIF_SIGPENDING&t;- signal pending&n; *  TIF_NEED_RESCHED&t;- rescheduling necessary&n; *  TIF_USEDFPU&t;&t;- FPU was used by this task this quantum (SMP)&n; *  TIF_POLLING_NRFLAG&t;- true if poll_idle() is polling TIF_NEED_RESCHED&n; */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;0
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;1
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;2
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;8
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;16
DECL|macro|TIF_USING_IWMMXT
mdefine_line|#define TIF_USING_IWMMXT&t;17
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1 &lt;&lt; TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1 &lt;&lt; TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1 &lt;&lt; TIF_NEED_RESCHED)
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1 &lt;&lt; TIF_SYSCALL_TRACE)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1 &lt;&lt; TIF_POLLING_NRFLAG)
DECL|macro|_TIF_USING_IWMMXT
mdefine_line|#define _TIF_USING_IWMMXT&t;(1 &lt;&lt; TIF_USING_IWMMXT)
multiline_comment|/*&n; * Change these and you break ASM code in entry-common.S&n; */
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK&t;&t;0x000000ff
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_ARM_THREAD_INFO_H */
eof
