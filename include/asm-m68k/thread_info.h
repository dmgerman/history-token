macro_line|#ifndef _ASM_M68K_THREAD_INFO_H
DECL|macro|_ASM_M68K_THREAD_INFO_H
mdefine_line|#define _ASM_M68K_THREAD_INFO_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
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
DECL|member|preempt_count
id|__s32
id|preempt_count
suffix:semicolon
multiline_comment|/* 0 =&gt; preemptable, &lt;0 =&gt; BUG */
DECL|member|cpu
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* should always be 0 on m68k */
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
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&bslash;&n;&t;.restart_block = {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/* THREAD_SIZE should be 8k, so handle differently for 4k and 8k machines */
macro_line|#if PAGE_SHIFT == 13 /* 8k machines */
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk)   ((struct thread_info *)__get_free_pages(GFP_KERNEL,0))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)  free_pages((unsigned long)(ti),0)
macro_line|#else /* otherwise assume 4k pages */
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk)   ((struct thread_info *)__get_free_pages(GFP_KERNEL,1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)  free_pages((unsigned long)(ti),1)
macro_line|#endif /* PAGE_SHIFT == 13 */
singleline_comment|//#define init_thread_info&t;(init_task.thread.info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()&t;(current-&gt;thread_info)
DECL|macro|__HAVE_THREAD_FUNCTIONS
mdefine_line|#define __HAVE_THREAD_FUNCTIONS
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_DELAYED_TRACE
mdefine_line|#define TIF_DELAYED_TRACE&t;1&t;/* single step a syscall */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;2&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;3&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;4&t;/* rescheduling necessary */
DECL|macro|TIF_MEMDIE
mdefine_line|#define TIF_MEMDIE&t;&t;5
r_extern
r_int
id|thread_flag_fixme
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * flag set/clear/test wrappers&n; * - pass TIF_xxxx constants to these functions&n; */
DECL|macro|__set_tsk_thread_flag
mdefine_line|#define __set_tsk_thread_flag(tsk, flag, val) ({&t;&bslash;&n;&t;switch (flag) {&t;&t;&t;&t;&t;&bslash;&n;&t;case TIF_SIGPENDING:&t;&t;&t;&t;&bslash;&n;&t;&t;tsk-&gt;thread.work.sigpending = val;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;case TIF_NEED_RESCHED:&t;&t;&t;&t;&bslash;&n;&t;&t;tsk-&gt;thread.work.need_resched = val;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;case TIF_SYSCALL_TRACE:&t;&t;&t;&t;&bslash;&n;&t;&t;tsk-&gt;thread.work.syscall_trace = val;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;thread_flag_fixme();&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_tsk_thread_flag
mdefine_line|#define __get_tsk_thread_flag(tsk, flag) ({&t;&t;&bslash;&n;&t;int ___res;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (flag) {&t;&t;&t;&t;&t;&bslash;&n;&t;case TIF_SIGPENDING:&t;&t;&t;&t;&bslash;&n;&t;&t;___res = tsk-&gt;thread.work.sigpending;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;case TIF_NEED_RESCHED:&t;&t;&t;&t;&bslash;&n;&t;&t;___res = tsk-&gt;thread.work.need_resched;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;case TIF_SYSCALL_TRACE:&t;&t;&t;&t;&bslash;&n;&t;&t;___res = tsk-&gt;thread.work.syscall_trace;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;___res = thread_flag_fixme();&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;___res;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_set_tsk_thread_flag
mdefine_line|#define __get_set_tsk_thread_flag(tsk, flag, val) ({&t;&bslash;&n;&t;int __res = __get_tsk_thread_flag(tsk, flag);&t;&bslash;&n;&t;__set_tsk_thread_flag(tsk, flag, val);&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|set_tsk_thread_flag
mdefine_line|#define set_tsk_thread_flag(tsk, flag) __set_tsk_thread_flag(tsk, flag, ~0)
DECL|macro|clear_tsk_thread_flag
mdefine_line|#define clear_tsk_thread_flag(tsk, flag) __set_tsk_thread_flag(tsk, flag, 0)
DECL|macro|test_and_set_tsk_thread_flag
mdefine_line|#define test_and_set_tsk_thread_flag(tsk, flag) __get_set_tsk_thread_flag(tsk, flag, ~0)
DECL|macro|test_tsk_thread_flag
mdefine_line|#define test_tsk_thread_flag(tsk, flag) __get_tsk_thread_flag(tsk, flag)
DECL|macro|set_thread_flag
mdefine_line|#define set_thread_flag(flag) set_tsk_thread_flag(current, flag)
DECL|macro|clear_thread_flag
mdefine_line|#define clear_thread_flag(flag) clear_tsk_thread_flag(current, flag)
DECL|macro|test_thread_flag
mdefine_line|#define test_thread_flag(flag) test_tsk_thread_flag(current, flag)
DECL|macro|set_need_resched
mdefine_line|#define set_need_resched() set_thread_flag(TIF_NEED_RESCHED)
DECL|macro|clear_need_resched
mdefine_line|#define clear_need_resched() clear_thread_flag(TIF_NEED_RESCHED)
macro_line|#endif&t;/* _ASM_M68K_THREAD_INFO_H */
eof
