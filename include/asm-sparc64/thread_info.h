multiline_comment|/* $Id: thread_info.h,v 1.1 2002/02/10 00:00:58 davem Exp $&n; * thread_info.h: sparc64 low-level thread information&n; *&n; * Copyright (C) 2002  David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _ASM_THREAD_INFO_H
DECL|macro|_ASM_THREAD_INFO_H
mdefine_line|#define _ASM_THREAD_INFO_H
macro_line|#ifdef __KERNEL__
DECL|macro|NSWINS
mdefine_line|#define NSWINS&t;&t;7
DECL|macro|TI_FLAG_BYTE_FAULT_CODE
mdefine_line|#define TI_FLAG_BYTE_FAULT_CODE&t;&t;0
DECL|macro|TI_FLAG_FAULT_CODE_SHIFT
mdefine_line|#define TI_FLAG_FAULT_CODE_SHIFT&t;56
DECL|macro|TI_FLAG_BYTE_WSTATE
mdefine_line|#define TI_FLAG_BYTE_WSTATE&t;&t;1
DECL|macro|TI_FLAG_WSTATE_SHIFT
mdefine_line|#define TI_FLAG_WSTATE_SHIFT&t;&t;48
DECL|macro|TI_FLAG_BYTE_CWP
mdefine_line|#define TI_FLAG_BYTE_CWP&t;&t;2
DECL|macro|TI_FLAG_CWP_SHIFT
mdefine_line|#define TI_FLAG_CWP_SHIFT&t;&t;40
DECL|macro|TI_FLAG_BYTE_CURRENT_DS
mdefine_line|#define TI_FLAG_BYTE_CURRENT_DS&t;&t;3
DECL|macro|TI_FLAG_CURRENT_DS_SHIFT
mdefine_line|#define TI_FLAG_CURRENT_DS_SHIFT&t;32
DECL|macro|TI_FLAG_BYTE_FPDEPTH
mdefine_line|#define TI_FLAG_BYTE_FPDEPTH&t;&t;4
DECL|macro|TI_FLAG_FPDEPTH_SHIFT
mdefine_line|#define TI_FLAG_FPDEPTH_SHIFT&t;&t;24
DECL|macro|TI_FLAG_BYTE_WSAVED
mdefine_line|#define TI_FLAG_BYTE_WSAVED&t;&t;5
DECL|macro|TI_FLAG_WSAVED_SHIFT
mdefine_line|#define TI_FLAG_WSAVED_SHIFT&t;&t;16
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
r_struct
id|task_struct
suffix:semicolon
r_struct
id|exec_domain
suffix:semicolon
DECL|struct|thread_info
r_struct
id|thread_info
(brace
multiline_comment|/* D$ line 1 */
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|cpu
id|__u8
id|cpu
suffix:semicolon
DECL|member|fpsaved
id|__u8
id|fpsaved
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* D$ line 2 */
DECL|member|fault_address
r_int
r_int
id|fault_address
suffix:semicolon
DECL|member|kregs
r_struct
id|pt_regs
op_star
id|kregs
suffix:semicolon
DECL|member|exec_domain
r_struct
id|exec_domain
op_star
id|exec_domain
suffix:semicolon
DECL|member|preempt_count
r_int
id|preempt_count
suffix:semicolon
DECL|member|utraps
r_int
r_int
op_star
id|utraps
suffix:semicolon
DECL|member|reg_window
r_struct
id|reg_window
id|reg_window
(braket
id|NSWINS
)braket
suffix:semicolon
DECL|member|rwbuf_stkptrs
r_int
r_int
id|rwbuf_stkptrs
(braket
id|NSWINS
)braket
suffix:semicolon
DECL|member|gsr
r_int
r_int
id|gsr
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|xfsr
r_int
r_int
id|xfsr
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|user_cntd0
DECL|member|user_cntd1
id|__u64
op_star
id|user_cntd0
comma
op_star
id|user_cntd1
suffix:semicolon
DECL|member|kernel_cntd0
DECL|member|kernel_cntd1
id|__u64
id|kernel_cntd0
comma
id|kernel_cntd1
suffix:semicolon
DECL|member|pcr_reg
id|__u64
id|pcr_reg
suffix:semicolon
DECL|member|cee_stuff
id|__u64
id|cee_stuff
suffix:semicolon
DECL|member|fpregs
r_int
r_int
id|fpregs
(braket
l_int|0
)braket
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* offsets into the thread_info struct for assembly code access */
DECL|macro|TI_TASK
mdefine_line|#define TI_TASK&t;&t;0x00000000
DECL|macro|TI_FLAGS
mdefine_line|#define TI_FLAGS&t;0x00000008
DECL|macro|TI_FAULT_CODE
mdefine_line|#define TI_FAULT_CODE&t;(TI_FLAGS + TI_FLAG_BYTE_FAULT_CODE)
DECL|macro|TI_WSTATE
mdefine_line|#define TI_WSTATE&t;(TI_FLAGS + TI_FLAG_BYTE_WSTATE)
DECL|macro|TI_CWP
mdefine_line|#define TI_CWP&t;&t;(TI_FLAGS + TI_FLAG_BYTE_CWP)
DECL|macro|TI_CURRENT_DS
mdefine_line|#define TI_CURRENT_DS&t;(TI_FLAGS + TI_FLAG_BYTE_CURRENT_DS)
DECL|macro|TI_FPDEPTH
mdefine_line|#define TI_FPDEPTH&t;(TI_FLAGS + TI_FLAG_BYTE_FPDEPTH)
DECL|macro|TI_WSAVED
mdefine_line|#define TI_WSAVED&t;(TI_FLAGS + TI_FLAG_BYTE_WSAVED)
DECL|macro|TI_CPU
mdefine_line|#define TI_CPU&t;&t;0x00000010
DECL|macro|TI_FPSAVED
mdefine_line|#define TI_FPSAVED&t;0x00000011
DECL|macro|TI_KSP
mdefine_line|#define TI_KSP&t;&t;0x00000018
DECL|macro|TI_FAULT_ADDR
mdefine_line|#define TI_FAULT_ADDR&t;0x00000020
DECL|macro|TI_KREGS
mdefine_line|#define TI_KREGS&t;0x00000028
DECL|macro|TI_EXEC_DOMAIN
mdefine_line|#define TI_EXEC_DOMAIN&t;0x00000030
DECL|macro|TI_PRE_COUNT
mdefine_line|#define TI_PRE_COUNT&t;0x00000038
DECL|macro|TI_UTRAPS
mdefine_line|#define TI_UTRAPS&t;0x00000040
DECL|macro|TI_REG_WINDOW
mdefine_line|#define TI_REG_WINDOW&t;0x00000048
DECL|macro|TI_RWIN_SPTRS
mdefine_line|#define TI_RWIN_SPTRS&t;0x000003c8&t;
DECL|macro|TI_GSR
mdefine_line|#define TI_GSR&t;&t;0x00000400
DECL|macro|TI_XFSR
mdefine_line|#define TI_XFSR&t;&t;0x00000438
DECL|macro|TI_USER_CNTD0
mdefine_line|#define TI_USER_CNTD0&t;0x00000470
DECL|macro|TI_USER_CNTD1
mdefine_line|#define TI_USER_CNTD1&t;0x00000478
DECL|macro|TI_KERN_CNTD0
mdefine_line|#define TI_KERN_CNTD0&t;0x00000480
DECL|macro|TI_KERN_CNTD1
mdefine_line|#define TI_KERN_CNTD1&t;0x00000488
DECL|macro|TI_PCR
mdefine_line|#define TI_PCR&t;&t;0x00000490
DECL|macro|TI_CEE_STUFF
mdefine_line|#define TI_CEE_STUFF&t;0x00000498
DECL|macro|TI_FPREGS
mdefine_line|#define TI_FPREGS&t;0x000004c0
multiline_comment|/* We embed this in the uppermost byte of thread_info-&gt;flags */
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE&t;0x01&t;/* Write access, implies D-TLB&t;&t;*/
DECL|macro|FAULT_CODE_DTLB
mdefine_line|#define FAULT_CODE_DTLB&t;&t;0x02&t;/* Miss happened in D-TLB&t;&t;*/
DECL|macro|FAULT_CODE_ITLB
mdefine_line|#define FAULT_CODE_ITLB&t;&t;0x04&t;/* Miss happened in I-TLB&t;&t;*/
DECL|macro|FAULT_CODE_WINFIXUP
mdefine_line|#define FAULT_CODE_WINFIXUP&t;0x08&t;/* Miss happened during spill/fill&t;*/
macro_line|#if PAGE_SHIFT == 13
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|THREAD_SHIFT
mdefine_line|#define THREAD_SHIFT (PAGE_SHIFT + 1)
macro_line|#else /* PAGE_SHIFT == 13 */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE PAGE_SIZE
DECL|macro|THREAD_SHIFT
mdefine_line|#define THREAD_SHIFT PAGE_SHIFT
macro_line|#endif /* PAGE_SHIFT == 13 */
DECL|macro|PREEMPT_ACTIVE
mdefine_line|#define PREEMPT_ACTIVE&t;&t;0x4000000
multiline_comment|/*&n; * macros/functions for gaining access to the thread information structure&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|INIT_THREAD_INFO
mdefine_line|#define INIT_THREAD_INFO(tsk)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;task:&t;&t;&amp;tsk,&t;&t;&t;&t;&bslash;&n;&t;flags:&t;&t;((unsigned long)ASI_P) &lt;&lt; TI_FLAG_CURRENT_DS_SHIFT,&t;&bslash;&n;&t;exec_domain:&t;&amp;default_exec_domain,&t;&t;&bslash;&n;}
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;(init_thread_union.thread_info)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;&t;(init_thread_union.stack)
multiline_comment|/* how to get the thread information struct from C */
r_register
r_struct
id|thread_info
op_star
id|current_thread_info_reg
id|asm
c_func
(paren
l_string|&quot;g6&quot;
)paren
suffix:semicolon
DECL|macro|current_thread_info
mdefine_line|#define current_thread_info()&t;(current_thread_info_reg)
multiline_comment|/* thread information allocation */
macro_line|#if PAGE_SHIFT == 13
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info()   ((struct thread_info *)__get_free_pages(GFP_KERNEL, 1))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)  free_pages((unsigned long)(ti),1)
macro_line|#else /* PAGE_SHIFT == 13 */
DECL|macro|alloc_thread_info
mdefine_line|#define alloc_thread_info()   ((struct thread_info *)__get_free_pages(GFP_KERNEL, 0))
DECL|macro|free_thread_info
mdefine_line|#define free_thread_info(ti)  free_pages((unsigned long)(ti),0)
macro_line|#endif /* PAGE_SHIFT == 13 */
DECL|macro|__thread_flag_byte_ptr
mdefine_line|#define __thread_flag_byte_ptr(ti)&t;&bslash;&n;&t;((unsigned char *)(&amp;((ti)-&gt;flags)))
DECL|macro|__cur_thread_flag_byte_ptr
mdefine_line|#define __cur_thread_flag_byte_ptr&t;__thread_flag_byte_ptr(current_thread_info())
DECL|macro|get_thread_fault_code
mdefine_line|#define get_thread_fault_code()&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_FAULT_CODE])
DECL|macro|set_thread_fault_code
mdefine_line|#define set_thread_fault_code(val)&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_FAULT_CODE] = (val))
DECL|macro|get_thread_wstate
mdefine_line|#define get_thread_wstate()&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_WSTATE])
DECL|macro|set_thread_wstate
mdefine_line|#define set_thread_wstate(val)&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_WSTATE] = (val))
DECL|macro|get_thread_cwp
mdefine_line|#define get_thread_cwp()&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_CWP])
DECL|macro|set_thread_cwp
mdefine_line|#define set_thread_cwp(val)&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_CWP] = (val))
DECL|macro|get_thread_current_ds
mdefine_line|#define get_thread_current_ds()&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_CURRENT_DS])
DECL|macro|set_thread_current_ds
mdefine_line|#define set_thread_current_ds(val)&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_CURRENT_DS] = (val))
DECL|macro|get_thread_fpdepth
mdefine_line|#define get_thread_fpdepth()&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_FPDEPTH])
DECL|macro|set_thread_fpdepth
mdefine_line|#define set_thread_fpdepth(val)&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_FPDEPTH] = (val))
DECL|macro|get_thread_wsaved
mdefine_line|#define get_thread_wsaved()&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_WSAVED])
DECL|macro|set_thread_wsaved
mdefine_line|#define set_thread_wsaved(val)&t;&t;(__cur_thread_flag_byte_ptr[TI_FLAG_BYTE_WSAVED] = (val))
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/*&n; * Thread information flags, only 16 bits are available as we encode&n; * other values into the upper 6 bytes.&n; *&n; * On trap return we need to test several values:&n; *&n; * user:&t;need_resched, notify_resume, sigpending, wsaved, perfctr&n; * kernel:&t;fpdepth&n; *&n; * So to check for work in the kernel case we simply load the fpdepth&n; * byte out of the flags and test it.  For the user case we encode the&n; * lower 3 bytes of flags as follows:&n; *&t;----------------------------------------&n; *&t;| wsaved | flags byte 1 | flags byte 2 |&n; *&t;----------------------------------------&n; * This optimizes the user test into:&n; *&t;ldx&t;&t;[%g6 + TI_FLAGS], REG1&n; *&t;sethi&t;&t;%hi(_TIF_USER_WORK_MASK), REG2&n; *&t;or&t;&t;REG2, %lo(_TIF_USER_WORK_MASK), REG2&n; *&t;andcc&t;&t;REG1, REG2, %g0&n; *&t;be,pt&t;&t;no_work_to_do&n; *&t; nop&n; */
DECL|macro|TIF_SYSCALL_TRACE
mdefine_line|#define TIF_SYSCALL_TRACE&t;0&t;/* syscall trace active */
DECL|macro|TIF_NOTIFY_RESUME
mdefine_line|#define TIF_NOTIFY_RESUME&t;1&t;/* resumption notification requested */
DECL|macro|TIF_SIGPENDING
mdefine_line|#define TIF_SIGPENDING&t;&t;2&t;/* signal pending */
DECL|macro|TIF_NEED_RESCHED
mdefine_line|#define TIF_NEED_RESCHED&t;3&t;/* rescheduling necessary */
DECL|macro|TIF_PERFCTR
mdefine_line|#define TIF_PERFCTR&t;&t;4&t;/* performance counters active */
DECL|macro|TIF_UNALIGNED
mdefine_line|#define TIF_UNALIGNED&t;&t;5&t;/* allowed to do unaligned accesses */
DECL|macro|TIF_NEWSIGNALS
mdefine_line|#define TIF_NEWSIGNALS&t;&t;6&t;/* wants new-style signals */
DECL|macro|TIF_32BIT
mdefine_line|#define TIF_32BIT&t;&t;7&t;/* 32-bit binary */
DECL|macro|TIF_NEWCHILD
mdefine_line|#define TIF_NEWCHILD&t;&t;8&t;/* just-spawned child process */
multiline_comment|/* XXX Make this one FAULT_CODE_BLKCOMMIT XXX */
DECL|macro|TIF_BLKCOMMIT
mdefine_line|#define TIF_BLKCOMMIT&t;&t;9&t;/* use ASI_BLK_COMMIT_* in copy_user_page */
DECL|macro|TIF_POLLING_NRFLAG
mdefine_line|#define TIF_POLLING_NRFLAG&t;10
DECL|macro|TIF_ABI_PENDING
mdefine_line|#define TIF_ABI_PENDING&t;&t;11
DECL|macro|_TIF_SYSCALL_TRACE
mdefine_line|#define _TIF_SYSCALL_TRACE&t;(1&lt;&lt;TIF_SYSCALL_TRACE)
DECL|macro|_TIF_NOTIFY_RESUME
mdefine_line|#define _TIF_NOTIFY_RESUME&t;(1&lt;&lt;TIF_NOTIFY_RESUME)
DECL|macro|_TIF_SIGPENDING
mdefine_line|#define _TIF_SIGPENDING&t;&t;(1&lt;&lt;TIF_SIGPENDING)
DECL|macro|_TIF_NEED_RESCHED
mdefine_line|#define _TIF_NEED_RESCHED&t;(1&lt;&lt;TIF_NEED_RESCHED)
DECL|macro|_TIF_PERFCTR
mdefine_line|#define _TIF_PERFCTR&t;&t;(1&lt;&lt;TIF_PERFCTR)
DECL|macro|_TIF_UNALIGNED
mdefine_line|#define _TIF_UNALIGNED&t;&t;(1&lt;&lt;TIF_UNALIGNED)
DECL|macro|_TIF_NEWSIGNALS
mdefine_line|#define _TIF_NEWSIGNALS&t;&t;(1&lt;&lt;TIF_NEWSIGNALS)
DECL|macro|_TIF_32BIT
mdefine_line|#define _TIF_32BIT&t;&t;(1&lt;&lt;TIF_32BIT)
DECL|macro|_TIF_NEWCHILD
mdefine_line|#define _TIF_NEWCHILD&t;&t;(1&lt;&lt;TIF_NEWCHILD)
DECL|macro|_TIF_BLKCOMMIT
mdefine_line|#define _TIF_BLKCOMMIT&t;&t;(1&lt;&lt;TIF_BLKCOMMIT)
DECL|macro|_TIF_POLLING_NRFLAG
mdefine_line|#define _TIF_POLLING_NRFLAG&t;(1&lt;&lt;TIF_POLLING_NRFLAG)
DECL|macro|_TIF_ABI_PENDING
mdefine_line|#define _TIF_ABI_PENDING&t;(1&lt;&lt;TIF_ABI_PENDING)
DECL|macro|_TIF_USER_WORK_MASK
mdefine_line|#define _TIF_USER_WORK_MASK&t;((0xff &lt;&lt; TI_FLAG_WSAVED_SHIFT) | &bslash;&n;&t;&t;&t;&t; (_TIF_NOTIFY_RESUME | _TIF_SIGPENDING | &bslash;&n;&t;&t;&t;&t;  _TIF_NEED_RESCHED | _TIF_PERFCTR))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_THREAD_INFO_H */
eof
