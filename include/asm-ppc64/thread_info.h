multiline_comment|/* thread_info.h: PPC low-level thread information&n; * adapted from the i386 version by Paul Mackerras&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
multiline_comment|/*&n; * low level task data.&n; */
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
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu we&squot;re on */
DECL|member|preempt_count
r_int
id|preempt_count
suffix:semicolon
DECL|member|restart_block
r_struct
id|restart_block
id|restart_block
suffix:semicolon
multiline_comment|/* set by force_successful_syscall_return */
DECL|member|syscall_noerror
r_int
r_char
id|syscall_noerror
suffix:semicolon
multiline_comment|/* low level flags - has atomic operations done on it */
DECL|member|____cacheline_aligned_in_smp
r_int
r_int
id|flags
id|____cacheline_aligned_in_smp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; *&n; * preempt_count needs to be 1 initially, until the scheduler is functional.&n; */
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task =&t;&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain =&t;&amp;default_exec_domain,&t;&bslash;&n;&t;.cpu =&t;&t;0,&t;&t;&t;&bslash;&n;&t;.preempt_count = 1,&t;&t;&t;&bslash;&n;&t;.restart_block = {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;&t;.flags =&t;0,&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/* thread information allocation */
DECL|macro|THREAD_ORDER
mdefine_line|#define THREAD_ORDER&t;&t;2
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;(PAGE_SIZE &lt;&lt; THREAD_ORDER)
DECL|macro|THREAD_SHIFT
mdefine_line|#define THREAD_SHIFT&t;&t;(PAGE_SHIFT + THREAD_ORDER)
macro_line|#ifdef CONFIG_DEBUG_STACK_USAGE
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct thread_info *ret;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = kmalloc(THREAD_SIZE, GFP_KERNEL);&t;&t;&bslash;&n;&t;&t;if (ret)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;memset(ret, 0, THREAD_SIZE);&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#else
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk) kmalloc(THREAD_SIZE, GFP_KERNEL)
macro_line|#endif
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)&t;kfree(ti)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti)&t;get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti)&t;put_task_struct((ti)-&gt;task)
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
l_string|&quot;clrrdi %0,1,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|THREAD_SHIFT
)paren
)paren
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x10000000
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
DECL|macro|TIF_32BIT
mdefine_line|#define TIF_32BIT&t;&t;5&t;/* 32 bit binary */
DECL|macro|TIF_RUN_LIGHT
mdefine_line|#define TIF_RUN_LIGHT&t;&t;6&t;/* iSeries run light */
DECL|macro|TIF_ABI_PENDING
mdefine_line|#define TIF_ABI_PENDING&t;&t;7&t;/* 32/64 bit switch needed */
DECL|macro|TIF_SYSCALL_AUDIT
mdefine_line|#define TIF_SYSCALL_AUDIT&t;8&t;/* syscall auditing active */
DECL|macro|TIF_SINGLESTEP
mdefine_line|#define TIF_SINGLESTEP&t;&t;9&t;/* singlestepping active */
DECL|macro|TIF_MEMDIE
mdefine_line|#define TIF_MEMDIE&t;&t;10
DECL|macro|TIF_SECCOMP
mdefine_line|#define TIF_SECCOMP&t;&t;11&t;/* secure computing */
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
DECL|macro|_TIF_32BIT
mdefine_line|#define _TIF_32BIT&t;&t;(1&lt;&lt;TIF_32BIT)
DECL|macro|_TIF_RUN_LIGHT
mdefine_line|#define _TIF_RUN_LIGHT&t;&t;(1&lt;&lt;TIF_RUN_LIGHT)
DECL|macro|_TIF_ABI_PENDING
mdefine_line|#define _TIF_ABI_PENDING&t;(1&lt;&lt;TIF_ABI_PENDING)
DECL|macro|_TIF_SYSCALL_AUDIT
mdefine_line|#define _TIF_SYSCALL_AUDIT&t;(1&lt;&lt;TIF_SYSCALL_AUDIT)
DECL|macro|_TIF_SINGLESTEP
mdefine_line|#define _TIF_SINGLESTEP&t;&t;(1&lt;&lt;TIF_SINGLESTEP)
DECL|macro|_TIF_SECCOMP
mdefine_line|#define _TIF_SECCOMP&t;&t;(1&lt;&lt;TIF_SECCOMP)
DECL|macro|_TIF_SYSCALL_T_OR_A
mdefine_line|#define _TIF_SYSCALL_T_OR_A&t;(_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT|_TIF_SECCOMP)
DECL|macro|_TIF_USER_WORK_MASK
mdefine_line|#define _TIF_USER_WORK_MASK&t;(_TIF_NOTIFY_RESUME | _TIF_SIGPENDING | &bslash;&n;&t;&t;&t;&t; _TIF_NEED_RESCHED)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
