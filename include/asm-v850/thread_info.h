multiline_comment|/*&n; * include/asm-v850/thread_info.h -- v850 low-level thread information&n; *&n; *  Copyright (C) 2002  NEC Corporation&n; *  Copyright (C) 2002  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 2002  David Howells (dhowells@redhat.com)&n; *    - Incorporating suggestions made by Linus Torvalds and Dave Miller&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * This file was derived from the PPC version, include/asm-ppc/thread_info.h&n; * which was adapted from the i386 version by Paul Mackerras&n; */
macro_line|#ifndef __V850_THREAD_INFO_H__
DECL|macro|__V850_THREAD_INFO_H__
mdefine_line|#define __V850_THREAD_INFO_H__
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * low level task data.&n; * If you change this, change the TI_* offsets below to match.&n; */
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
)brace
suffix:semicolon
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&t;&t;&t;      &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;.task =&t;&t;&amp;tsk,&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;.exec_domain =&t;&amp;default_exec_domain,&t;&t;&t;&t;      &bslash;&n;&t;.flags =&t;0,&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;.cpu =&t;&t;0,&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;.preempt_count = 1,&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;.restart_block = {&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;.fn = do_no_restart_syscall,&t;&t;&t;&t;      &bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; */
multiline_comment|/* thread information allocation */
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info(tsk) ((struct thread_info *) &bslash;&n;&t;&t;&t;&t;__get_free_pages(GFP_KERNEL, 1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)&t;free_pages((unsigned long) (ti), 1)
DECL|macro|get_thread_info
mdefine_line|#define get_thread_info(ti)&t;get_task_struct((ti)-&gt;task)
DECL|macro|put_thread_info
mdefine_line|#define put_thread_info(ti)&t;put_task_struct((ti)-&gt;task)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Offsets in thread_info structure, used in assembly code&n; */
DECL|macro|TI_TASK
mdefine_line|#define TI_TASK&t;&t;0
DECL|macro|TI_EXECDOMAIN
mdefine_line|#define TI_EXECDOMAIN&t;4
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;8
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;12
DECL|macro|TI_PREEMPT
mdefine_line|#define TI_PREEMPT&t;16
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
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
DECL|macro|TIF_MEMDIE
mdefine_line|#define TIF_MEMDIE&t;&t;5
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
multiline_comment|/* Size of kernel stack for each process.  */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;&t;0x2000
multiline_comment|/* The alignment of kernel threads, with thread_info structures at their&n;   base.  Thus, a pointer for a task&squot;s task structure can be derived from&n;   its kernel stack pointer.  */
DECL|macro|THREAD_ALIGNMENT
mdefine_line|#define THREAD_ALIGNMENT&t;THREAD_SIZE
DECL|macro|THREAD_MASK
mdefine_line|#define THREAD_MASK&t;&t;(-THREAD_ALIGNMENT)
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/* Put a pointer to the current thread_info structure into REG.  Note that&n;   this definition requires THREAD_MASK to be representable as a signed&n;   16-bit value.  */
DECL|macro|GET_CURRENT_THREAD
mdefine_line|#define GET_CURRENT_THREAD(reg)&t;&t;&t;&t;&t;&t;&bslash;&n;        /* Use `addi&squot; and then `and&squot; instead of just `andi&squot;, because&t;&bslash;&n;&t;   `addi&squot; sign-extends the immediate value, whereas `andi&squot;&t;&bslash;&n;&t;   zero-extends it.  */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;addi&t;THREAD_MASK, r0, reg;&t;&t;&t;&t;&t;&bslash;&n;&t;and&t;sp, reg
macro_line|#else
multiline_comment|/* Return a pointer to the current thread_info structure.  */
DECL|function|current_thread_info
r_static
r_inline
r_struct
id|thread_info
op_star
id|current_thread_info
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|sp
id|__asm__
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
id|THREAD_MASK
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __V850_THREAD_INFO_H__ */
eof
