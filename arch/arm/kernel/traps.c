multiline_comment|/*&n; *  linux/arch/arm/kernel/traps.c&n; *&n; *  Copyright (C) 1995, 1996 Russell King&n; *  Fragments that appear the same as linux/arch/i386/kernel/traps.c (C) Linus Torvalds&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  &squot;traps.c&squot; handles hardware exceptions after we have saved some state in&n; *  &squot;linux/arch/arm/lib/traps.S&squot;.  Mostly a debugging aid, but will probably&n; *  kill the offending process.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ptrace.h&quot;
r_extern
r_void
id|c_backtrace
(paren
r_int
r_int
id|fp
comma
r_int
id|pmode
)paren
suffix:semicolon
r_extern
r_void
id|show_pte
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|variable|processor_modes
r_const
r_char
op_star
id|processor_modes
(braket
)braket
op_assign
(brace
l_string|&quot;USER_26&quot;
comma
l_string|&quot;FIQ_26&quot;
comma
l_string|&quot;IRQ_26&quot;
comma
l_string|&quot;SVC_26&quot;
comma
l_string|&quot;UK4_26&quot;
comma
l_string|&quot;UK5_26&quot;
comma
l_string|&quot;UK6_26&quot;
comma
l_string|&quot;UK7_26&quot;
comma
l_string|&quot;UK8_26&quot;
comma
l_string|&quot;UK9_26&quot;
comma
l_string|&quot;UK10_26&quot;
comma
l_string|&quot;UK11_26&quot;
comma
l_string|&quot;UK12_26&quot;
comma
l_string|&quot;UK13_26&quot;
comma
l_string|&quot;UK14_26&quot;
comma
l_string|&quot;UK15_26&quot;
comma
l_string|&quot;USER_32&quot;
comma
l_string|&quot;FIQ_32&quot;
comma
l_string|&quot;IRQ_32&quot;
comma
l_string|&quot;SVC_32&quot;
comma
l_string|&quot;UK4_32&quot;
comma
l_string|&quot;UK5_32&quot;
comma
l_string|&quot;UK6_32&quot;
comma
l_string|&quot;ABT_32&quot;
comma
l_string|&quot;UK8_32&quot;
comma
l_string|&quot;UK9_32&quot;
comma
l_string|&quot;UK10_32&quot;
comma
l_string|&quot;UND_32&quot;
comma
l_string|&quot;UK12_32&quot;
comma
l_string|&quot;UK13_32&quot;
comma
l_string|&quot;UK14_32&quot;
comma
l_string|&quot;SYS_32&quot;
)brace
suffix:semicolon
DECL|variable|handler
r_static
r_const
r_char
op_star
id|handler
(braket
)braket
op_assign
(brace
l_string|&quot;prefetch abort&quot;
comma
l_string|&quot;data abort&quot;
comma
l_string|&quot;address exception&quot;
comma
l_string|&quot;interrupt&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * Stack pointers should always be within the kernels view of&n; * physical memory.  If it is not there, then we can&squot;t dump&n; * out any information relating to the stack.&n; */
DECL|function|verify_stack
r_static
r_int
id|verify_stack
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_if
c_cond
(paren
id|sp
template_param
(paren
r_int
r_int
)paren
id|high_memory
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Dump out the contents of some memory nicely...&n; */
DECL|function|dump_mem
r_void
id|dump_mem
c_func
(paren
r_int
r_int
id|bottom
comma
r_int
r_int
id|top
)paren
(brace
r_int
r_int
id|p
op_assign
id|bottom
op_amp
op_complement
l_int|31
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|bottom
op_amp
op_complement
l_int|31
suffix:semicolon
id|p
OL
id|top
suffix:semicolon
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%08lx: &quot;
comma
id|p
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
id|i
op_increment
comma
id|p
op_add_assign
l_int|4
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
id|bottom
op_logical_or
id|p
op_ge
id|top
)paren
id|printk
c_func
(paren
l_string|&quot;         &quot;
)paren
suffix:semicolon
r_else
(brace
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|p
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * These constants are for searching for possible module text&n; * segments.  VMALLOC_OFFSET comes from mm/vmalloc.c; MODULE_RANGE is&n; * a guess of how much space is likely to be vmalloced.&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET (8*1024*1024)
DECL|macro|MODULE_RANGE
mdefine_line|#define MODULE_RANGE (8*1024*1024)
DECL|function|dump_instr
r_static
r_void
id|dump_instr
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|addr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_const
r_int
id|thumb
op_assign
id|thumb_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
r_const
r_int
id|width
op_assign
id|thumb
ques
c_cond
l_int|4
suffix:colon
l_int|8
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Code: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|2
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|val
comma
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|thumb
)paren
id|bad
op_assign
id|__get_user
c_func
(paren
id|val
comma
op_amp
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|bad
op_assign
id|__get_user
c_func
(paren
id|val
comma
op_amp
(paren
(paren
id|u32
op_star
)paren
id|addr
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bad
)paren
id|printk
c_func
(paren
id|i
op_eq
l_int|0
ques
c_cond
l_string|&quot;(%0*x) &quot;
suffix:colon
l_string|&quot;%0*x &quot;
comma
id|width
comma
id|val
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;bad PC value.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|dump_stack
r_static
r_void
id|dump_stack
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|sp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Stack:&bslash;n&quot;
)paren
suffix:semicolon
id|dump_mem
c_func
(paren
id|sp
op_minus
l_int|16
comma
l_int|8192
op_plus
(paren
r_int
r_int
)paren
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|dump_backtrace
r_static
r_void
id|dump_backtrace
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|fp
suffix:semicolon
r_int
id|ok
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Backtrace: &quot;
)paren
suffix:semicolon
id|fp
op_assign
id|regs-&gt;ARM_fp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;no frame pointer&quot;
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|verify_stack
c_func
(paren
id|fp
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;invalid frame pointer 0x%08x&quot;
comma
id|fp
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fp
OL
l_int|4096
op_plus
(paren
r_int
r_int
)paren
id|tsk
)paren
id|printk
c_func
(paren
l_string|&quot;frame pointer underflow&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ok
)paren
id|c_backtrace
c_func
(paren
id|fp
comma
id|processor_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
)brace
DECL|variable|die_lock
id|spinlock_t
id|die_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * This function is protected against re-entrancy.&n; */
DECL|function|die
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Internal error: %s: %x&bslash;n&quot;
comma
id|str
comma
id|err
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU: %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, stackpage=%08lx)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
l_int|4096
op_plus
(paren
r_int
r_int
)paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|mm_segment_t
id|fs
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We need to switch to kernel mode so that we can&n;&t;&t; * use __get_user to safely read from kernel space.&n;&t;&t; * Note that we now dump the code first, just in case&n;&t;&t; * the backtrace kills us.&n;&t;&t; */
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
id|tsk
comma
(paren
r_int
r_int
)paren
(paren
id|regs
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|dump_backtrace
c_func
(paren
id|regs
comma
id|tsk
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
id|str
comma
id|regs
comma
id|err
)paren
suffix:semicolon
)brace
DECL|function|do_undefinstr
id|asmlinkage
r_void
id|do_undefinstr
c_func
(paren
r_int
id|address
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|addr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s (%d): undefined instruction: pc=%08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|addr
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|current-&gt;thread.error_code
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.trap_no
op_assign
l_int|6
suffix:semicolon
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLOPC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops - undefined instruction&quot;
comma
id|regs
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|do_excpt
id|asmlinkage
r_void
id|do_excpt
c_func
(paren
r_int
id|address
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|mode
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s (%d): address exception: pc=%08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|current-&gt;thread.error_code
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.trap_no
op_assign
l_int|11
suffix:semicolon
id|info.si_signo
op_assign
id|SIGBUS
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|BUS_ADRERR
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops - address exception&quot;
comma
id|regs
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|do_unexp_fiq
id|asmlinkage
r_void
id|do_unexp_fiq
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifndef CONFIG_IGNORE_FIQ
id|printk
c_func
(paren
l_string|&quot;Hmm.  Unexpected FIQ received, but trying to continue&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;You may have a hardware problem...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * bad_mode handles the impossible case in the vectors.  If you see one of&n; * these, then it&squot;s extremely serious, and could mean you have buggy hardware.&n; * It never returns, and never tries to sync.  We hope that we can at least&n; * dump out some state information...&n; */
DECL|function|bad_mode
id|asmlinkage
r_void
id|bad_mode
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|reason
comma
r_int
id|proc_mode
)paren
(brace
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Bad mode in %s handler detected: mode %s&bslash;n&quot;
comma
id|handler
(braket
id|reason
)braket
comma
id|processor_modes
(braket
id|proc_mode
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dump out the vectors and stub routines.  Maybe a better solution&n;&t; * would be to dump them out only if we detect that they are corrupted.&n;&t; */
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Vectors:&bslash;n&quot;
)paren
suffix:semicolon
id|dump_mem
c_func
(paren
l_int|0
comma
l_int|0x40
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Stubs:&bslash;n&quot;
)paren
suffix:semicolon
id|dump_mem
c_func
(paren
l_int|0x200
comma
l_int|0x4b8
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;bad mode&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle some more esoteric system calls&n; */
DECL|function|arm_syscall
id|asmlinkage
r_int
id|arm_syscall
c_func
(paren
r_int
id|no
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_switch
c_cond
(paren
id|no
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* branch through 0 */
id|info.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
id|info.si_addr
op_assign
l_int|NULL
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;branch through zero&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* SWI BREAK_POINT */
multiline_comment|/*&n;&t;&t; * The PC is always left pointing at the next&n;&t;&t; * instruction.  Fix this.&n;&t;&t; */
id|regs-&gt;ARM_pc
op_sub_assign
l_int|4
suffix:semicolon
id|__ptrace_cancel_bpt
c_func
(paren
id|current
)paren
suffix:semicolon
id|info.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|TRAP_BRKPT
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* sys_cacheflush */
macro_line|#ifdef CONFIG_CPU_32
multiline_comment|/* r0 = start, r1 = end, r2 = flags */
id|cpu_cache_clean_invalidate_range
c_func
(paren
id|regs-&gt;ARM_r0
comma
id|regs-&gt;ARM_r1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Calls 9f00xx..9f07ff are defined to return -ENOSYS&n;&t;&t;   if not implemented, rather than raising SIGILL.  This&n;&t;&t;   way the calling program can gracefully determine whether&n;&t;&t;   a feature is supported.  */
r_if
c_cond
(paren
id|no
op_le
l_int|0x7ff
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
multiline_comment|/* experience shows that these seem to indicate that&n;&t;&t; * something catastrophic has happened&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;[%d] %s: arm syscall %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|no
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
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
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|c_backtrace
c_func
(paren
id|regs-&gt;ARM_fp
comma
id|processor_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|no
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|deferred
id|asmlinkage
r_void
id|deferred
c_func
(paren
r_int
id|n
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* You might think just testing `handler&squot; would be enough, but PER_LINUX&n;&t; * points it to no_lcall7 to catch undercover SVr4 binaries.  Gutted.&n;&t; */
r_if
c_cond
(paren
id|current-&gt;personality
op_ne
id|PER_LINUX
op_logical_and
id|current-&gt;exec_domain-&gt;handler
)paren
(brace
multiline_comment|/* Hand it off to iBCS.  The extra parameter and consequent type &n;&t;&t; * forcing is necessary because of the weird ARM calling convention.&n;&t;&t; */
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
id|nr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
(paren
r_void
op_star
)paren
id|current-&gt;exec_domain-&gt;handler
suffix:semicolon
(paren
op_star
id|handler
)paren
(paren
id|n
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_USER
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;[%d] %s: obsolete system call %08x.&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|n
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|__bad_xchg
r_void
id|__bad_xchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;xchg: bad data size: pc 0x%p, ptr 0x%p, size %d&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A data abort trap was taken, but we did not handle the instruction.&n; * Try to abort the user program, or panic if it was the kernel.&n; */
id|asmlinkage
r_void
DECL|function|baddataabort
id|baddataabort
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|addr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;[%d] %s: bad data abort: code %d instr 0x%08lx&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|code
comma
id|instr
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
id|show_pte
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLOPC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;unknown data abort code&quot;
comma
id|regs
comma
id|instr
)paren
suffix:semicolon
)brace
DECL|function|__bug
r_void
id|__bug
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;kernel BUG at %s:%d!&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot; - extra data = %p&quot;
comma
id|data
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
l_int|0
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|__readwrite_bug
r_void
id|__readwrite_bug
c_func
(paren
r_const
r_char
op_star
id|fn
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s called, but not implemented&quot;
comma
id|fn
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__pte_error
r_void
id|__pte_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d: bad pte %08lx.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|__pmd_error
r_void
id|__pmd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|__pgd_error
r_void
id|__pgd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|__div0
id|asmlinkage
r_void
id|__div0
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Division by zero in kernel.&bslash;n&quot;
)paren
suffix:semicolon
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|abort
r_void
m_abort
(paren
r_void
)paren
(brace
r_void
op_star
id|lr
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;abort() called from %p!  (Please &quot;
l_string|&quot;report to rmk@arm.linux.org.uk)&bslash;n&quot;
comma
id|lr
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if that doesn&squot;t kill us, halt */
id|panic
c_func
(paren
l_string|&quot;Oops failed to kill thread&quot;
)paren
suffix:semicolon
)brace
DECL|function|trap_init
r_void
id|__init
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|__trap_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|__trap_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|modify_domain
c_func
(paren
id|DOMAIN_USER
comma
id|DOMAIN_CLIENT
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
