macro_line|#ifndef _ASM_PARISC_THREAD_INFO_H
DECL|macro|_ASM_PARISC_THREAD_INFO_H
mdefine_line|#define _ASM_PARISC_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
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
multiline_comment|/* thread_info flags (see TIF_*) */
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
multiline_comment|/* user-level address space limit */
DECL|member|cpu
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* current CPU */
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
)brace
suffix:semicolon
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.addr_limit&t;= KERNEL_DS,&t;&t;&bslash;&n;&t;.preempt_count&t;= 0,&t;&t;&t;&bslash;&n;  &t;.restart_block&t;= {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info        (init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack              (init_thread_union.stack)
multiline_comment|/* thread information allocation */
DECL|macro|THREAD_ORDER
mdefine_line|#define THREAD_ORDER            2
multiline_comment|/* Be sure to hunt all references to this down when you change the size of&n; * the kernel stack */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE             (PAGE_SIZE &lt;&lt; THREAD_ORDER)
DECL|macro|THREAD_SHIFT
mdefine_line|#define THREAD_SHIFT            (PAGE_SHIFT + THREAD_ORDER)
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk) ((struct thread_info *) &bslash;&n;&t;&t;&t;__get_free_pages(GFP_KERNEL, THREAD_ORDER))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)    free_pages((unsigned long) (ti), THREAD_ORDER)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti)     get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti)     put_task_struct((ti)-&gt;task)
multiline_comment|/* how to get the thread information struct from C */
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()&t;((struct thread_info *)mfctl(30))
macro_line|#endif /* !__ASSEMBLY */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE          0x4000000
multiline_comment|/*&n; * thread information flags&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;4&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
DECL|macro|TIF_32BIT
mdefine_line|#define TIF_32BIT               5       /* 32 bit binary */
DECL|macro|TIF_MEMDIE
mdefine_line|#define TIF_MEMDIE&t;&t;6
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1 &lt;&lt; TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1 &lt;&lt; TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1 &lt;&lt; TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1 &lt;&lt; TIF_NEED_RESCHED)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1 &lt;&lt; TIF_POLLING_NRFLAG)
DECL|macro|_TIF_32BIT
mdefine_line|#define _TIF_32BIT&t;&t;(1 &lt;&lt; TIF_32BIT)
DECL|macro|_TIF_USER_WORK_MASK
mdefine_line|#define _TIF_USER_WORK_MASK     (_TIF_NOTIFY_RESUME | _TIF_SIGPENDING | &bslash;&n;                                 _TIF_NEED_RESCHED)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_PARISC_THREAD_INFO_H */
eof
