macro_line|#ifndef __ASM_SH64_THREAD_INFO_H
DECL|macro|__ASM_SH64_THREAD_INFO_H
mdefine_line|#define __ASM_SH64_THREAD_INFO_H
multiline_comment|/*&n; * SuperH 5 version&n; * Copyright (C) 2003  Paul Mundt&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/registers.h&gt;
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
multiline_comment|/* Put the 4 32-bit fields together to make asm offsetting easier. */
DECL|member|preempt_count
id|__s32
id|preempt_count
suffix:semicolon
multiline_comment|/* 0 =&gt; preemptable, &lt;0 =&gt; BUG */
DECL|member|cpu
id|__u16
id|cpu
suffix:semicolon
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
DECL|member|supervisor_stack
id|__u8
id|supervisor_stack
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.preempt_count&t;= 1,&t;&t;&t;&bslash;&n;&t;.addr_limit     = KERNEL_DS,            &bslash;&n;&t;.restart_block&t;= {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;}
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
id|__volatile__
(paren
l_string|&quot;getcon &quot;
id|__KCR0
l_string|&quot;, %0&bslash;n&bslash;t&quot;
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
mdefine_line|#define alloc_thread_info(ti) ((struct thread_info *) __get_free_pages(GFP_KERNEL,2))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) free_pages((unsigned long) (ti), 1)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
multiline_comment|/* thread information flags */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_MEMDIE
mdefine_line|#define TIF_MEMDIE&t;&t;4
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;16384
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH64_THREAD_INFO_H */
eof
