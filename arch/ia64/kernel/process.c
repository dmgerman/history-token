multiline_comment|/*&n; * Architecture-specific setup.&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__&t;/* see &lt;asm/unistd.h&gt; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/perfmon.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/unwind.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN
macro_line|#include &lt;asm/sn/idle.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_PERFMON
macro_line|# include &lt;asm/perfmon.h&gt;
macro_line|#endif
macro_line|#include &quot;sigframe.h&quot;
r_static
r_void
DECL|function|do_show_stack
id|do_show_stack
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|ip
comma
id|sp
comma
id|bsp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nCall Trace: &quot;
)paren
suffix:semicolon
r_do
(brace
id|unw_get_ip
c_func
(paren
id|info
comma
op_amp
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|unw_get_sp
c_func
(paren
id|info
comma
op_amp
id|sp
)paren
suffix:semicolon
id|unw_get_bsp
c_func
(paren
id|info
comma
op_amp
id|bsp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[&lt;%016lx&gt;] sp=0x%016lx bsp=0x%016lx&bslash;n&quot;
comma
id|ip
comma
id|sp
comma
id|bsp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|unw_unwind
c_func
(paren
id|info
)paren
op_ge
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|show_trace_task
id|show_trace_task
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_struct
id|unw_frame_info
id|info
suffix:semicolon
id|unw_init_from_blocked_task
c_func
(paren
op_amp
id|info
comma
id|task
)paren
suffix:semicolon
id|do_show_stack
c_func
(paren
op_amp
id|info
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|show_stack
id|show_stack
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|task
)paren
id|unw_init_running
c_func
(paren
id|do_show_stack
comma
l_int|0
)paren
suffix:semicolon
r_else
(brace
r_struct
id|unw_frame_info
id|info
suffix:semicolon
id|unw_init_from_blocked_task
c_func
(paren
op_amp
id|info
comma
id|task
)paren
suffix:semicolon
id|do_show_stack
c_func
(paren
op_amp
id|info
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|show_regs
id|show_regs
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|ip
op_assign
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nPid: %d, comm: %20s&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;psr : %016lx ifs : %016lx ip  : [&lt;%016lx&gt;]    %s&bslash;n&quot;
comma
id|regs-&gt;cr_ipsr
comma
id|regs-&gt;cr_ifs
comma
id|ip
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;unat: %016lx pfs : %016lx rsc : %016lx&bslash;n&quot;
comma
id|regs-&gt;ar_unat
comma
id|regs-&gt;ar_pfs
comma
id|regs-&gt;ar_rsc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;rnat: %016lx bsps: %016lx pr  : %016lx&bslash;n&quot;
comma
id|regs-&gt;ar_rnat
comma
id|regs-&gt;ar_bspstore
comma
id|regs-&gt;pr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ldrs: %016lx ccv : %016lx fpsr: %016lx&bslash;n&quot;
comma
id|regs-&gt;loadrs
comma
id|regs-&gt;ar_ccv
comma
id|regs-&gt;ar_fpsr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;b0  : %016lx b6  : %016lx b7  : %016lx&bslash;n&quot;
comma
id|regs-&gt;b0
comma
id|regs-&gt;b6
comma
id|regs-&gt;b7
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;f6  : %05lx%016lx f7  : %05lx%016lx&bslash;n&quot;
comma
id|regs-&gt;f6.u.bits
(braket
l_int|1
)braket
comma
id|regs-&gt;f6.u.bits
(braket
l_int|0
)braket
comma
id|regs-&gt;f7.u.bits
(braket
l_int|1
)braket
comma
id|regs-&gt;f7.u.bits
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;f8  : %05lx%016lx f9  : %05lx%016lx&bslash;n&quot;
comma
id|regs-&gt;f8.u.bits
(braket
l_int|1
)braket
comma
id|regs-&gt;f8.u.bits
(braket
l_int|0
)braket
comma
id|regs-&gt;f9.u.bits
(braket
l_int|1
)braket
comma
id|regs-&gt;f9.u.bits
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r1  : %016lx r2  : %016lx r3  : %016lx&bslash;n&quot;
comma
id|regs-&gt;r1
comma
id|regs-&gt;r2
comma
id|regs-&gt;r3
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r8  : %016lx r9  : %016lx r10 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r8
comma
id|regs-&gt;r9
comma
id|regs-&gt;r10
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r11 : %016lx r12 : %016lx r13 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r11
comma
id|regs-&gt;r12
comma
id|regs-&gt;r13
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r14 : %016lx r15 : %016lx r16 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r14
comma
id|regs-&gt;r15
comma
id|regs-&gt;r16
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r17 : %016lx r18 : %016lx r19 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r17
comma
id|regs-&gt;r18
comma
id|regs-&gt;r19
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r20 : %016lx r21 : %016lx r22 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r20
comma
id|regs-&gt;r21
comma
id|regs-&gt;r22
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r23 : %016lx r24 : %016lx r25 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r23
comma
id|regs-&gt;r24
comma
id|regs-&gt;r25
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r26 : %016lx r27 : %016lx r28 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r26
comma
id|regs-&gt;r27
comma
id|regs-&gt;r28
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r29 : %016lx r30 : %016lx r31 : %016lx&bslash;n&quot;
comma
id|regs-&gt;r29
comma
id|regs-&gt;r30
comma
id|regs-&gt;r31
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
multiline_comment|/* print the stacked registers */
r_int
r_int
id|val
comma
id|sof
comma
op_star
id|bsp
comma
id|ndirty
suffix:semicolon
r_int
id|i
comma
id|is_nat
op_assign
l_int|0
suffix:semicolon
id|sof
op_assign
id|regs-&gt;cr_ifs
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/* size of frame */
id|ndirty
op_assign
(paren
id|regs-&gt;loadrs
op_rshift
l_int|19
)paren
suffix:semicolon
id|bsp
op_assign
id|ia64_rse_skip_regs
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;ar_bspstore
comma
id|ndirty
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sof
suffix:semicolon
op_increment
id|i
)paren
(brace
id|get_user
c_func
(paren
id|val
comma
id|ia64_rse_skip_regs
c_func
(paren
id|bsp
comma
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r%-3u:%c%016lx%s&quot;
comma
l_int|32
op_plus
id|i
comma
id|is_nat
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|val
comma
(paren
(paren
id|i
op_eq
id|sof
op_minus
l_int|1
)paren
op_logical_or
(paren
id|i
op_mod
l_int|3
)paren
op_eq
l_int|2
)paren
ques
c_cond
l_string|&quot;&bslash;n&quot;
suffix:colon
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
)brace
r_else
id|show_stack
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|do_notify_resume_user
id|do_notify_resume_user
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|sigscratch
op_star
id|scr
comma
r_int
id|in_syscall
)paren
(brace
macro_line|#ifdef CONFIG_PERFMON
r_if
c_cond
(paren
id|current-&gt;thread.pfm_ovfl_block_reset
)paren
id|pfm_ovfl_block_reset
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* deal with pending signal delivery */
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_SIGPENDING
)paren
)paren
id|ia64_do_signal
c_func
(paren
id|oldset
comma
id|scr
comma
id|in_syscall
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We use this if we don&squot;t have any better idle routine..&n; */
r_static
r_void
DECL|function|default_idle
id|default_idle
(paren
r_void
)paren
(brace
multiline_comment|/* may want to do PAL_LIGHT_HALT here... */
)brace
r_void
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
DECL|function|cpu_idle
id|cpu_idle
(paren
r_void
op_star
id|unused
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
r_while
c_loop
(paren
l_int|1
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|min_xtp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
macro_line|#ifdef CONFIG_IA64_SGI_SN
id|snidle
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|pm_idle
)paren
(paren
op_star
id|pm_idle
)paren
(paren
)paren
suffix:semicolon
r_else
id|default_idle
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IA64_SGI_SN
id|snidleoff
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|normal_xtp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|ia64_save_extra
id|ia64_save_extra
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_if
c_cond
(paren
(paren
id|task-&gt;thread.flags
op_amp
id|IA64_THREAD_DBG_VALID
)paren
op_ne
l_int|0
)paren
id|ia64_save_debug_regs
c_func
(paren
op_amp
id|task-&gt;thread.dbr
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PERFMON
r_if
c_cond
(paren
(paren
id|task-&gt;thread.flags
op_amp
id|IA64_THREAD_PM_VALID
)paren
op_ne
l_int|0
)paren
id|pfm_save_regs
c_func
(paren
id|task
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_SMP
r_if
c_cond
(paren
id|local_cpu_data-&gt;pfm_syst_wide
)paren
id|pfm_syst_wide_update_task
c_func
(paren
id|task
comma
l_int|0
)paren
suffix:semicolon
macro_line|# endif
macro_line|#endif
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
id|ia64_task_regs
c_func
(paren
id|task
)paren
)paren
)paren
id|ia32_save_state
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_load_extra
id|ia64_load_extra
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_if
c_cond
(paren
(paren
id|task-&gt;thread.flags
op_amp
id|IA64_THREAD_DBG_VALID
)paren
op_ne
l_int|0
)paren
id|ia64_load_debug_regs
c_func
(paren
op_amp
id|task-&gt;thread.dbr
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PERFMON
r_if
c_cond
(paren
(paren
id|task-&gt;thread.flags
op_amp
id|IA64_THREAD_PM_VALID
)paren
op_ne
l_int|0
)paren
id|pfm_load_regs
c_func
(paren
id|task
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_SMP
r_if
c_cond
(paren
id|local_cpu_data-&gt;pfm_syst_wide
)paren
id|pfm_syst_wide_update_task
c_func
(paren
id|task
comma
l_int|1
)paren
suffix:semicolon
macro_line|# endif
macro_line|#endif
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
id|ia64_task_regs
c_func
(paren
id|task
)paren
)paren
)paren
id|ia32_load_state
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy the state of an ia-64 thread.&n; *&n; * We get here through the following  call chain:&n; *&n; *&t;&lt;clone syscall&gt;&n; *&t;sys_clone&n; *&t;do_fork&n; *&t;copy_thread&n; *&n; * This means that the stack layout is as follows:&n; *&n; *&t;+---------------------+ (highest addr)&n; *&t;|   struct pt_regs    |&n; *&t;+---------------------+&n; *&t;| struct switch_stack |&n; *&t;+---------------------+&n; *&t;|                     |&n; *&t;|    memory stack     |&n; *&t;|                     | &lt;-- sp (lowest addr)&n; *&t;+---------------------+&n; *&n; * Note: if we get called through kernel_thread() then the memory&n; * above &quot;(highest addr)&quot; is valid kernel stack memory that needs to&n; * be copied as well.&n; *&n; * Observe that we copy the unat values that are in pt_regs and&n; * switch_stack.  Spilling an integer to address X causes bit N in&n; * ar.unat to be set to the NaT bit of the register, with N=(X &amp;&n; * 0x1ff)/8.  Thus, copying the unat value preserves the NaT bits ONLY&n; * if the pt_regs structure in the parent is congruent to that of the&n; * child, modulo 512.  Since the stack is page aligned and the page&n; * size is at least 4KB, this is always the case, so there is nothing&n; * to worry about.&n; */
r_int
DECL|function|copy_thread
id|copy_thread
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|user_stack_base
comma
r_int
r_int
id|user_stack_size
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|rbs
comma
id|child_rbs
comma
id|rbs_size
comma
id|stack_offset
comma
id|stack_top
comma
id|stack_used
suffix:semicolon
r_struct
id|switch_stack
op_star
id|child_stack
comma
op_star
id|stack
suffix:semicolon
r_extern
r_char
id|ia64_ret_from_clone
comma
id|ia32_ret_from_clone
suffix:semicolon
r_struct
id|pt_regs
op_star
id|child_ptregs
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t; * For SMP idle threads, fork_by_hand() calls do_fork with&n;&t; * NULL regs.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|regs
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|stack_top
op_assign
(paren
r_int
r_int
)paren
id|current
op_plus
id|IA64_STK_OFFSET
suffix:semicolon
id|stack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|regs
)paren
op_minus
l_int|1
suffix:semicolon
id|stack_used
op_assign
id|stack_top
op_minus
(paren
r_int
r_int
)paren
id|stack
suffix:semicolon
id|stack_offset
op_assign
id|IA64_STK_OFFSET
op_minus
id|stack_used
suffix:semicolon
id|child_stack
op_assign
(paren
r_struct
id|switch_stack
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|p
op_plus
id|stack_offset
)paren
suffix:semicolon
id|child_ptregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|child_stack
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* copy parent&squot;s switch_stack &amp; pt_regs to child: */
id|memcpy
c_func
(paren
id|child_stack
comma
id|stack
comma
id|stack_used
)paren
suffix:semicolon
id|rbs
op_assign
(paren
r_int
r_int
)paren
id|current
op_plus
id|IA64_RBS_OFFSET
suffix:semicolon
id|child_rbs
op_assign
(paren
r_int
r_int
)paren
id|p
op_plus
id|IA64_RBS_OFFSET
suffix:semicolon
id|rbs_size
op_assign
id|stack-&gt;ar_bspstore
op_minus
id|rbs
suffix:semicolon
multiline_comment|/* copy the parent&squot;s register backing store to the child: */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|child_rbs
comma
(paren
r_void
op_star
)paren
id|rbs
comma
id|rbs_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|child_ptregs
)paren
)paren
(brace
r_if
c_cond
(paren
id|user_stack_base
)paren
(brace
id|child_ptregs-&gt;r12
op_assign
id|user_stack_base
op_plus
id|user_stack_size
op_minus
l_int|16
suffix:semicolon
id|child_ptregs-&gt;ar_bspstore
op_assign
id|user_stack_base
suffix:semicolon
id|child_ptregs-&gt;ar_rnat
op_assign
l_int|0
suffix:semicolon
id|child_ptregs-&gt;loadrs
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Note: we simply preserve the relative position of&n;&t;&t; * the stack pointer here.  There is no need to&n;&t;&t; * allocate a scratch area here, since that will have&n;&t;&t; * been taken care of by the caller of sys_clone()&n;&t;&t; * already.&n;&t;&t; */
id|child_ptregs-&gt;r12
op_assign
(paren
r_int
r_int
)paren
(paren
id|child_ptregs
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* kernel sp */
id|child_ptregs-&gt;r13
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
multiline_comment|/* set `current&squot; pointer */
)brace
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
id|regs
)paren
)paren
id|child_stack-&gt;b0
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia32_ret_from_clone
suffix:semicolon
r_else
id|child_stack-&gt;b0
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia64_ret_from_clone
suffix:semicolon
id|child_stack-&gt;ar_bspstore
op_assign
id|child_rbs
op_plus
id|rbs_size
suffix:semicolon
multiline_comment|/* copy parts of thread_struct: */
id|p-&gt;thread.ksp
op_assign
(paren
r_int
r_int
)paren
id|child_stack
op_minus
l_int|16
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE: The calling convention considers all floating point&n;&t; * registers in the high partition (fph) to be scratch.  Since&n;&t; * the only way to get to this point is through a system call,&n;&t; * we know that the values in fph are all dead.  Hence, there&n;&t; * is no need to inherit the fph state from the parent to the&n;&t; * child and all we have to do is to make sure that&n;&t; * IA64_THREAD_FPH_VALID is cleared in the child.&n;&t; *&n;&t; * XXX We could push this optimization a bit further by&n;&t; * clearing IA64_THREAD_FPH_VALID on ANY system call.&n;&t; * However, it&squot;s not clear this is worth doing.  Also, it&n;&t; * would be a slight deviation from the normal Linux system&n;&t; * call behavior where scratch registers are preserved across&n;&t; * system calls (unless used by the system call itself).&n;&t; */
DECL|macro|THREAD_FLAGS_TO_CLEAR
macro_line|#&t;define THREAD_FLAGS_TO_CLEAR&t;(IA64_THREAD_FPH_VALID | IA64_THREAD_DBG_VALID &bslash;&n;&t;&t;&t;&t;&t; | IA64_THREAD_PM_VALID)
DECL|macro|THREAD_FLAGS_TO_SET
macro_line|#&t;define THREAD_FLAGS_TO_SET&t;0
id|p-&gt;thread.flags
op_assign
(paren
(paren
id|current-&gt;thread.flags
op_amp
op_complement
id|THREAD_FLAGS_TO_CLEAR
)paren
op_or
id|THREAD_FLAGS_TO_SET
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_SUPPORT
multiline_comment|/*&n;&t; * If we&squot;re cloning an IA32 task then save the IA32 extra&n;&t; * state from the current task to the new task&n;&t; */
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
id|ia64_task_regs
c_func
(paren
id|current
)paren
)paren
)paren
id|ia32_save_state
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PERFMON
multiline_comment|/*&n;&t; * reset notifiers and owner check (may not have a perfmon context)&n;&t; */
id|atomic_set
c_func
(paren
op_amp
id|p-&gt;thread.pfm_notifiers_check
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|p-&gt;thread.pfm_owners_check
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;thread.pfm_context
)paren
id|retval
op_assign
id|pfm_inherit
c_func
(paren
id|p
comma
id|child_ptregs
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
r_void
DECL|function|do_copy_regs
id|do_copy_regs
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|mask
comma
id|sp
comma
id|nat_bits
op_assign
l_int|0
comma
id|ip
comma
id|ar_rnat
comma
id|urbs_end
comma
id|cfm
suffix:semicolon
id|elf_greg_t
op_star
id|dst
op_assign
id|arg
suffix:semicolon
r_struct
id|pt_regs
op_star
id|pt
suffix:semicolon
r_char
id|nat
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|dst
comma
l_int|0
comma
r_sizeof
(paren
id|elf_gregset_t
)paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t leak any kernel bits to user-level */
r_if
c_cond
(paren
id|unw_unwind_to_user
c_func
(paren
id|info
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|unw_get_sp
c_func
(paren
id|info
comma
op_amp
id|sp
)paren
suffix:semicolon
id|pt
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|sp
op_plus
l_int|16
)paren
suffix:semicolon
id|urbs_end
op_assign
id|ia64_get_user_rbs_end
c_func
(paren
id|current
comma
id|pt
comma
op_amp
id|cfm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ia64_sync_user_rbs
c_func
(paren
id|current
comma
id|info-&gt;sw
comma
id|pt-&gt;ar_bspstore
comma
id|urbs_end
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|ia64_peek
c_func
(paren
id|current
comma
id|info-&gt;sw
comma
id|urbs_end
comma
(paren
r_int
)paren
id|ia64_rse_rnat_addr
c_func
(paren
(paren
r_int
op_star
)paren
id|urbs_end
)paren
comma
op_amp
id|ar_rnat
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * coredump format:&n;&t; *&t;r0-r31&n;&t; *&t;NaT bits (for r0-r31; bit N == 1 iff rN is a NaT)&n;&t; *&t;predicate registers (p0-p63)&n;&t; *&t;b0-b7&n;&t; *&t;ip cfm user-mask&n;&t; *&t;ar.rsc ar.bsp ar.bspstore ar.rnat&n;&t; *&t;ar.ccv ar.unat ar.fpsr ar.pfs ar.lc ar.ec&n;&t; */
multiline_comment|/* r0 is zero */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
comma
id|mask
op_assign
(paren
l_int|1UL
op_lshift
id|i
)paren
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
op_increment
id|i
)paren
(brace
id|unw_get_gr
c_func
(paren
id|info
comma
id|i
comma
op_amp
id|dst
(braket
id|i
)braket
comma
op_amp
id|nat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nat
)paren
id|nat_bits
op_or_assign
id|mask
suffix:semicolon
id|mask
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|dst
(braket
l_int|32
)braket
op_assign
id|nat_bits
suffix:semicolon
id|unw_get_pr
c_func
(paren
id|info
comma
op_amp
id|dst
(braket
l_int|33
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
op_increment
id|i
)paren
id|unw_get_br
c_func
(paren
id|info
comma
id|i
comma
op_amp
id|dst
(braket
l_int|34
op_plus
id|i
)braket
)paren
suffix:semicolon
id|unw_get_rp
c_func
(paren
id|info
comma
op_amp
id|ip
)paren
suffix:semicolon
id|dst
(braket
l_int|42
)braket
op_assign
id|ip
op_plus
id|ia64_psr
c_func
(paren
id|pt
)paren
op_member_access_from_pointer
id|ri
suffix:semicolon
id|dst
(braket
l_int|43
)braket
op_assign
id|cfm
suffix:semicolon
id|dst
(braket
l_int|44
)braket
op_assign
id|pt-&gt;cr_ipsr
op_amp
id|IA64_PSR_UM
suffix:semicolon
id|unw_get_ar
c_func
(paren
id|info
comma
id|UNW_AR_RSC
comma
op_amp
id|dst
(braket
l_int|45
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For bsp and bspstore, unw_get_ar() would return the kernel&n;&t; * addresses, but we need the user-level addresses instead:&n;&t; */
id|dst
(braket
l_int|46
)braket
op_assign
id|urbs_end
suffix:semicolon
multiline_comment|/* note: by convention PT_AR_BSP points to the end of the urbs! */
id|dst
(braket
l_int|47
)braket
op_assign
id|pt-&gt;ar_bspstore
suffix:semicolon
id|dst
(braket
l_int|48
)braket
op_assign
id|ar_rnat
suffix:semicolon
id|unw_get_ar
c_func
(paren
id|info
comma
id|UNW_AR_CCV
comma
op_amp
id|dst
(braket
l_int|49
)braket
)paren
suffix:semicolon
id|unw_get_ar
c_func
(paren
id|info
comma
id|UNW_AR_UNAT
comma
op_amp
id|dst
(braket
l_int|50
)braket
)paren
suffix:semicolon
id|unw_get_ar
c_func
(paren
id|info
comma
id|UNW_AR_FPSR
comma
op_amp
id|dst
(braket
l_int|51
)braket
)paren
suffix:semicolon
id|dst
(braket
l_int|52
)braket
op_assign
id|pt-&gt;ar_pfs
suffix:semicolon
multiline_comment|/* UNW_AR_PFS is == to pt-&gt;cr_ifs for interrupt frames */
id|unw_get_ar
c_func
(paren
id|info
comma
id|UNW_AR_LC
comma
op_amp
id|dst
(braket
l_int|53
)braket
)paren
suffix:semicolon
id|unw_get_ar
c_func
(paren
id|info
comma
id|UNW_AR_EC
comma
op_amp
id|dst
(braket
l_int|54
)braket
)paren
suffix:semicolon
)brace
r_void
DECL|function|do_dump_fpu
id|do_dump_fpu
(paren
r_struct
id|unw_frame_info
op_star
id|info
comma
r_void
op_star
id|arg
)paren
(brace
id|elf_fpreg_t
op_star
id|dst
op_assign
id|arg
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|dst
comma
l_int|0
comma
r_sizeof
(paren
id|elf_fpregset_t
)paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t leak any &quot;random&quot; bits */
r_if
c_cond
(paren
id|unw_unwind_to_user
c_func
(paren
id|info
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* f0 is 0.0, f1 is 1.0 */
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
op_increment
id|i
)paren
id|unw_get_fr
c_func
(paren
id|info
comma
id|i
comma
id|dst
op_plus
id|i
)paren
suffix:semicolon
id|ia64_flush_fph
c_func
(paren
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;thread.flags
op_amp
id|IA64_THREAD_FPH_VALID
)paren
op_ne
l_int|0
)paren
id|memcpy
c_func
(paren
id|dst
op_plus
l_int|32
comma
id|current-&gt;thread.fph
comma
l_int|96
op_star
l_int|16
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_elf_core_copy_regs
id|ia64_elf_core_copy_regs
(paren
r_struct
id|pt_regs
op_star
id|pt
comma
id|elf_gregset_t
id|dst
)paren
(brace
id|unw_init_running
c_func
(paren
id|do_copy_regs
comma
id|dst
)paren
suffix:semicolon
)brace
r_int
DECL|function|dump_fpu
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|pt
comma
id|elf_fpregset_t
id|dst
)paren
(brace
id|unw_init_running
c_func
(paren
id|do_dump_fpu
comma
id|dst
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* f0-f31 are always valid so we always return 1 */
)brace
id|asmlinkage
r_int
DECL|function|sys_execve
id|sys_execve
(paren
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
id|argv
comma
id|envp
comma
id|regs
)paren
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_void
DECL|function|ia64_set_personality
id|ia64_set_personality
(paren
r_struct
id|elf64_hdr
op_star
id|elf_ex
comma
r_int
id|ibcs2_interpreter
)paren
(brace
id|set_personality
c_func
(paren
id|PER_LINUX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|elf_ex-&gt;e_flags
op_amp
id|EF_IA_64_LINUX_EXECUTABLE_STACK
)paren
id|current-&gt;thread.flags
op_or_assign
id|IA64_THREAD_XSTACK
suffix:semicolon
r_else
id|current-&gt;thread.flags
op_and_assign
op_complement
id|IA64_THREAD_XSTACK
suffix:semicolon
)brace
id|pid_t
DECL|function|kernel_thread
id|kernel_thread
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|task_struct
op_star
id|parent
op_assign
id|current
suffix:semicolon
r_int
id|result
comma
id|tid
suffix:semicolon
id|tid
op_assign
id|clone
c_func
(paren
id|flags
op_or
id|CLONE_VM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
op_ne
id|current
)paren
(brace
id|result
op_assign
(paren
op_star
id|fn
)paren
(paren
id|arg
)paren
suffix:semicolon
id|_exit
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_return
id|tid
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush thread state.  This is called when a thread does an execve().&n; */
r_void
DECL|function|flush_thread
id|flush_thread
(paren
r_void
)paren
(brace
multiline_comment|/* drop floating-point and debug-register state if it exists: */
id|current-&gt;thread.flags
op_and_assign
op_complement
(paren
id|IA64_THREAD_FPH_VALID
op_or
id|IA64_THREAD_DBG_VALID
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|ia64_get_fpu_owner
c_func
(paren
)paren
op_eq
id|current
)paren
id|ia64_set_fpu_owner
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_PERFMON
multiline_comment|/*&n; * by the time we get here, the task is detached from the tasklist. This is important&n; * because it means that no other tasks can ever find it as a notified task, therfore there&n; * is no race condition between this code and let&squot;s say a pfm_context_create().&n; * Conversely, the pfm_cleanup_notifiers() cannot try to access a task&squot;s pfm context if this&n; * other task is in the middle of its own pfm_context_exit() because it would already be out of&n; * the task list. Note that this case is very unlikely between a direct child and its parents&n; * (if it is the notified process) because of the way the exit is notified via SIGCHLD.&n; */
r_void
DECL|function|release_thread
id|release_thread
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_if
c_cond
(paren
id|task-&gt;thread.pfm_context
)paren
id|pfm_context_exit
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|task-&gt;thread.pfm_notifiers_check
)paren
OG
l_int|0
)paren
id|pfm_cleanup_notifiers
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|task-&gt;thread.pfm_owners_check
)paren
OG
l_int|0
)paren
id|pfm_cleanup_owners
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.pfm_smpl_buf_list
)paren
id|pfm_cleanup_smpl_buf
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Clean up state associated with current thread.  This is called when&n; * the thread calls exit().&n; */
r_void
DECL|function|exit_thread
id|exit_thread
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|ia64_get_fpu_owner
c_func
(paren
)paren
op_eq
id|current
)paren
id|ia64_set_fpu_owner
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PERFMON
multiline_comment|/* if needed, stop monitoring and flush state to perfmon context */
r_if
c_cond
(paren
id|current-&gt;thread.pfm_context
)paren
id|pfm_flush_regs
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/* free debug register resources */
r_if
c_cond
(paren
(paren
id|current-&gt;thread.flags
op_amp
id|IA64_THREAD_DBG_VALID
)paren
op_ne
l_int|0
)paren
(brace
id|pfm_release_debug_registers
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_int
r_int
DECL|function|get_wchan
id|get_wchan
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_struct
id|unw_frame_info
id|info
suffix:semicolon
r_int
r_int
id|ip
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * These bracket the sleeping functions..&n;&t; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
macro_line|#&t;define first_sched&t;((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
macro_line|#&t;define last_sched&t;((unsigned long) scheduling_functions_end_here)
multiline_comment|/*&n;&t; * Note: p may not be a blocked task (it could be current or&n;&t; * another process running on some other CPU.  Rather than&n;&t; * trying to determine if p is really blocked, we just assume&n;&t; * it&squot;s blocked and rely on the unwind routines to fail&n;&t; * gracefully if the process wasn&squot;t really blocked after all.&n;&t; * --davidm 99/12/15&n;&t; */
id|unw_init_from_blocked_task
c_func
(paren
op_amp
id|info
comma
id|p
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|unw_unwind
c_func
(paren
op_amp
id|info
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|unw_get_ip
c_func
(paren
op_amp
id|info
comma
op_amp
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
OL
id|first_sched
op_logical_or
id|ip
op_ge
id|last_sched
)paren
r_return
id|ip
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
DECL|macro|first_sched
macro_line|#&t;undef first_sched
DECL|macro|last_sched
macro_line|#&t;undef last_sched
)brace
r_void
DECL|function|cpu_halt
id|cpu_halt
(paren
r_void
)paren
(brace
id|pal_power_mgmt_info_u_t
id|power_info
(braket
l_int|8
)braket
suffix:semicolon
r_int
r_int
id|min_power
suffix:semicolon
r_int
id|i
comma
id|min_power_state
suffix:semicolon
r_if
c_cond
(paren
id|ia64_pal_halt_info
c_func
(paren
id|power_info
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|min_power_state
op_assign
l_int|0
suffix:semicolon
id|min_power
op_assign
id|power_info
(braket
l_int|0
)braket
dot
id|pal_power_mgmt_info_s.power_consumption
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|power_info
(braket
id|i
)braket
dot
id|pal_power_mgmt_info_s.im
op_logical_and
id|power_info
(braket
id|i
)braket
dot
id|pal_power_mgmt_info_s.power_consumption
OL
id|min_power
)paren
(brace
id|min_power
op_assign
id|power_info
(braket
id|i
)braket
dot
id|pal_power_mgmt_info_s.power_consumption
suffix:semicolon
id|min_power_state
op_assign
id|i
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
id|ia64_pal_halt
c_func
(paren
id|min_power_state
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_restart
id|machine_restart
(paren
r_char
op_star
id|restart_cmd
)paren
(brace
(paren
op_star
id|efi.reset_system
)paren
(paren
id|EFI_RESET_WARM
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_halt
id|machine_halt
(paren
r_void
)paren
(brace
id|cpu_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_power_off
id|machine_power_off
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pm_power_off
)paren
id|pm_power_off
c_func
(paren
)paren
suffix:semicolon
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|init_task_struct_cache
id|init_task_struct_cache
(paren
r_void
)paren
(brace
)brace
r_struct
id|task_struct
op_star
DECL|function|dup_task_struct
id|dup_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
id|orig
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
id|tsk
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|KERNEL_STACK_SIZE_ORDER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|tsk
comma
id|orig
comma
r_sizeof
(paren
r_struct
id|task_struct
)paren
op_plus
r_sizeof
(paren
r_struct
id|thread_info
)paren
)paren
suffix:semicolon
id|tsk-&gt;thread_info
op_assign
(paren
r_struct
id|thread_info
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|tsk
op_plus
id|IA64_TASK_SIZE
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|tsk-&gt;usage
comma
l_int|1
)paren
suffix:semicolon
r_return
id|tsk
suffix:semicolon
)brace
r_void
DECL|function|__put_task_struct
id|__put_task_struct
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|tsk
comma
id|KERNEL_STACK_SIZE_ORDER
)paren
suffix:semicolon
)brace
eof
