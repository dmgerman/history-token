multiline_comment|/* thread_info.h: x86_64 low-level thread information&n; *&n; * Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; * - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#endif
multiline_comment|/*&n; * low level task data that entry.S needs immediate access to&n; * - this struct should fit entirely inside of one cache line&n; * - this struct shares the supervisor stack pages&n; */
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
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* low level flags */
DECL|member|cpu
id|__u32
id|cpu
suffix:semicolon
multiline_comment|/* current CPU */
DECL|member|preempt_count
r_int
id|preempt_count
suffix:semicolon
DECL|member|addr_limit
id|mm_segment_t
id|addr_limit
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;task:&t;&t;&amp;tsk,&t;&t;&t;&bslash;&n;&t;exec_domain:&t;&amp;default_exec_domain,&t;&bslash;&n;&t;flags:&t;&t;0,&t;&t;&t;&bslash;&n;&t;cpu:&t;&t;0,&t;&t;&t;&bslash;&n;&t;addr_limit:&t;KERNEL_DS,&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/* how to get the thread information struct from C */
macro_line|#ifdef CONFIG_PREEMPT 
multiline_comment|/* Preemptive kernels need to access this from interrupt context too. */
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
id|ti
op_assign
(paren
r_void
op_star
)paren
id|read_pda
c_func
(paren
id|kernelstack
)paren
op_plus
id|PDA_STACKOFFSET
op_minus
id|THREAD_SIZE
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* On others go for a minimally cheaper way. */
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
l_string|&quot;andq %%rsp,%0; &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_complement
l_int|8191UL
)paren
)paren
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* thread information allocation */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info() ((struct thread_info *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti) free_pages((unsigned long) (ti), 1)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti) get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti) put_task_struct((ti)-&gt;task)
macro_line|#else /* !__ASSEMBLY__ */
multiline_comment|/* how to get the thread information struct from ASM */
DECL|macro|GET_THREAD_INFO
mdefine_line|#define GET_THREAD_INFO(reg) &bslash;&n;&t;movq $-8192, reg; &bslash;&n;&t;andq %rsp, reg
macro_line|#endif
multiline_comment|/*&n; * thread information flags&n; * - these are process state flags that various assembly files may need to access&n; * - pending work-to-be-done flags are in LSW&n; * - other flags in MSW&n; * Warning: layout of LSW is hardcoded in entry.S&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_USEDFPU
mdefine_line|#define TIF_USEDFPU&t;&t;16&t;/* FPU was used by this task this quantum (SMP) */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;17&t;/* true if poll_idle() is polling TIF_NEED_RESCHED */
DECL|macro|TIF_IA32
mdefine_line|#define TIF_IA32&t;&t;18&t;/* 32bit process */ 
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1&lt;&lt;TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1&lt;&lt;TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1&lt;&lt;TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1&lt;&lt;TIF_NEED_RESCHED)
DECL|macro|_TIF_USEDFPU
mdefine_line|#define _TIF_USEDFPU&t;&t;(1&lt;&lt;TIF_USEDFPU)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
DECL|macro|_TIF_IA32
mdefine_line|#define _TIF_IA32&t;&t;(1&lt;&lt;TIF_IA32)
DECL|macro|_TIF_WORK_MASK
mdefine_line|#define _TIF_WORK_MASK&t;&t;0x0000FFFE&t;/* work to do on interrupt/exception return */
DECL|macro|_TIF_ALLWORK_MASK
mdefine_line|#define _TIF_ALLWORK_MASK&t;0x0000FFFF&t;/* work to do on any return to u-space */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof