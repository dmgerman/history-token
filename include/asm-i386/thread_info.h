multiline_comment|/* thread_info.h: i386 low-level thread information&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#endif
multiline_comment|/*&n; * low level task data that entry.S needs immediate access to&n; * - this struct should fit entirely inside of one cache line&n; * - this struct shares the supervisor stack pages&n; * - if the contents of this structure are changed, the assembly constants must also be changed&n; */
macro_line|#ifndef __ASSEMBLY__
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
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* thread-synchronous flags */
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
DECL|member|previous_esp
r_int
r_int
id|previous_esp
suffix:semicolon
multiline_comment|/* ESP of the previous stack in case&n;&t;&t;&t;&t;&t;&t;   of nested (IRQ) stacks&n;&t;&t;&t;&t;&t;&t;*/
DECL|member|supervisor_stack
id|__u8
id|supervisor_stack
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else /* !__ASSEMBLY__ */
macro_line|#include &lt;asm/asm_offsets.h&gt;
macro_line|#endif
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x10000000
macro_line|#ifdef CONFIG_4KSTACKS
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE            (4096)
macro_line|#else
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;(8192)
macro_line|#endif
DECL|macro|STACK_WARN
mdefine_line|#define STACK_WARN             (THREAD_SIZE/8)
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; *&n; * preempt_count needs to be 1 initially, until the scheduler is functional.&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= &amp;tsk,&t;&t;&t;&bslash;&n;&t;.exec_domain&t;= &amp;default_exec_domain,&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.cpu&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.preempt_count&t;= 1,&t;&t;&t;&bslash;&n;&t;.addr_limit&t;= KERNEL_DS,&t;&t;&bslash;&n;&t;.restart_block = {&t;&t;&t;&bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&bslash;&n;}
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
c_func
(paren
l_string|&quot;andl %%esp,%0; &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_complement
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
multiline_comment|/* how to get the current stack pointer from C */
r_register
r_int
r_int
id|current_stack_pointer
id|asm
c_func
(paren
l_string|&quot;esp&quot;
)paren
suffix:semicolon
multiline_comment|/* thread information allocation */
macro_line|#ifdef CONFIG_DEBUG_STACK_USAGE
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct thread_info *ret;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = kmalloc(THREAD_SIZE, GFP_KERNEL);&t;&t;&bslash;&n;&t;&t;if (ret)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;memset(ret, 0, THREAD_SIZE);&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#else
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk) kmalloc(THREAD_SIZE, GFP_KERNEL)
macro_line|#endif
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(info)&t;kfree(info)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
macro_line|#else /* !__ASSEMBLY__ */
multiline_comment|/* how to get the thread information struct from ASM */
DECL|macro|GET_THREAD_INFO
mdefine_line|#define GET_THREAD_INFO(reg) &bslash;&n;&t;movl $-THREAD_SIZE, reg; &bslash;&n;&t;andl %esp, reg
multiline_comment|/* use this one if reg already contains %esp */
DECL|macro|GET_THREAD_INFO_WITH_ESP
mdefine_line|#define GET_THREAD_INFO_WITH_ESP(reg) &bslash;&n;&t;andl $-THREAD_SIZE, reg
macro_line|#endif
multiline_comment|/*&n; * thread information flags&n; * - these are process state flags that various assembly files may need to access&n; * - pending work-to-be-done flags are in LSW&n; * - other flags in MSW&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_SINGLESTEP
mdefine_line|#define TIF_SINGLESTEP&t;&t;4&t;/* restore singlestep on return to user mode */
DECL|macro|TIF_IRET
mdefine_line|#define TIF_IRET&t;&t;5&t;/* return with iret */
DECL|macro|TIF_SYSCALL_AUDIT
mdefine_line|#define TIF_SYSCALL_AUDIT&t;7&t;/* syscall auditing active */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;16&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1&lt;&lt;TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1&lt;&lt;TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1&lt;&lt;TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1&lt;&lt;TIF_NEED_RESCHED)
DECL|macro|_TIF_SINGLESTEP
mdefine_line|#define _TIF_SINGLESTEP&t;&t;(1&lt;&lt;TIF_SINGLESTEP)
DECL|macro|_TIF_IRET
mdefine_line|#define _TIF_IRET&t;&t;(1&lt;&lt;TIF_IRET)
DECL|macro|_TIF_SYSCALL_AUDIT
mdefine_line|#define _TIF_SYSCALL_AUDIT&t;(1&lt;&lt;TIF_SYSCALL_AUDIT)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
multiline_comment|/* work to do on interrupt/exception return */
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK &bslash;&n;  (0x0000FFFF &amp; ~(_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT|_TIF_SINGLESTEP))
DECL|macro|_TIF_ALLWORK_MASK
mdefine_line|#define _TIF_ALLWORK_MASK&t;0x0000FFFF&t;/* work to do on any return to u-space */
multiline_comment|/*&n; * Thread-synchronous status.&n; *&n; * This is different from the flags in that nobody else&n; * ever touches our thread-synchronous status, so we don&squot;t&n; * have to worry about atomic accesses.&n; */
DECL|macro|TS_USEDFPU
mdefine_line|#define TS_USEDFPU&t;&t;0x0001&t;/* FPU was used by this task this quantum (SMP) */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
