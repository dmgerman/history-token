multiline_comment|/* thread_info.h: i386 low-level thread information&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
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
multiline_comment|/* offsets into the thread_info struct for assembly code access */
DECL|macro|TI_TASK
mdefine_line|#define TI_TASK&t;&t;0x00000000
DECL|macro|TI_EXEC_DOMAIN
mdefine_line|#define TI_EXEC_DOMAIN&t;0x00000004
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;0x00000008
DECL|macro|TI_STATUS
mdefine_line|#define TI_STATUS&t;0x0000000C
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;0x00000010
DECL|macro|TI_PRE_COUNT
mdefine_line|#define TI_PRE_COUNT&t;0x00000014
DECL|macro|TI_ADDR_LIMIT
mdefine_line|#define TI_ADDR_LIMIT&t;0x00000018
DECL|macro|TI_RESTART_BLOCK
mdefine_line|#define TI_RESTART_BLOCK 0x000001C
macro_line|#endif
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
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
id|__volatile__
(paren
l_string|&quot;ldi&t;%0, #0xffffe000;&t;&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%0, sp;&t;&t;&t;&bslash;n&bslash;t&quot;
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
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(task) &bslash;&n;&t;((struct thread_info *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) free_pages((unsigned long) (ti), 1)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
DECL|macro|TI_FLAG_FAULT_CODE_SHIFT
mdefine_line|#define TI_FLAG_FAULT_CODE_SHIFT&t;28
DECL|function|set_thread_fault_code
r_static
r_inline
r_void
id|set_thread_fault_code
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_struct
id|thread_info
op_star
id|ti
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
id|ti-&gt;flags
op_assign
(paren
id|ti-&gt;flags
op_amp
(paren
op_complement
l_int|0
op_rshift
(paren
l_int|32
op_minus
id|TI_FLAG_FAULT_CODE_SHIFT
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
id|TI_FLAG_FAULT_CODE_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|get_thread_fault_code
r_static
r_inline
r_int
r_int
id|get_thread_fault_code
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_info
op_star
id|ti
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
r_return
id|ti-&gt;flags
op_rshift
id|TI_FLAG_FAULT_CODE_SHIFT
suffix:semicolon
)brace
macro_line|#else /* !__ASSEMBLY__ */
multiline_comment|/* how to get the thread information struct from ASM */
DECL|macro|GET_THREAD_INFO
mdefine_line|#define GET_THREAD_INFO(reg)&t;GET_THREAD_INFO reg
dot
id|macro
id|GET_THREAD_INFO
id|reg
id|ldi
"&bslash;"
id|reg
comma
macro_line|#0xffffe000
DECL|variable|reg
op_logical_and
"&bslash;"
id|reg
comma
id|sp
dot
id|endm
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
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;16&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
multiline_comment|/* 31..28 fault code */
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
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK&t;&t;0x0000FFFE&t;/* work to do on interrupt/exception return */
DECL|macro|_TIF_ALLWORK_MASK
mdefine_line|#define _TIF_ALLWORK_MASK&t;0x0000FFFF&t;/* work to do on any return to u-space */
multiline_comment|/*&n; * Thread-synchronous status.&n; *&n; * This is different from the flags in that nobody else&n; * ever touches our thread-synchronous status, so we don&squot;t&n; * have to worry about atomic accesses.&n; */
DECL|macro|TS_USEDFPU
mdefine_line|#define TS_USEDFPU&t;&t;0x0001&t;/* FPU was used by this task this quantum (SMP) */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
