multiline_comment|/*&n; * Architecture-specific trap handling.&n; *&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * 05/12/00 grao &lt;goutham.rao@intel.com&gt; : added isr in siginfo for SIGFPE&n; */
multiline_comment|/*&n; * fp_emulate() needs to be able to access and update all floating point registers.  Those&n; * saved in pt_regs can be accessed through that structure, but those not saved, will be&n; * accessed directly.  To make this work, we need to ensure that the compiler does not end&n; * up using a preserved floating point register on its own.  The following achieves this&n; * by declaring preserved registers that are not marked as &quot;fixed&quot; as global register&n; * variables.&n; */
r_register
r_float
id|f2
id|asm
(paren
l_string|&quot;f2&quot;
)paren
suffix:semicolon
r_register
r_float
id|f3
id|asm
(paren
l_string|&quot;f3&quot;
)paren
suffix:semicolon
r_register
r_float
id|f4
id|asm
(paren
l_string|&quot;f4&quot;
)paren
suffix:semicolon
r_register
r_float
id|f5
id|asm
(paren
l_string|&quot;f5&quot;
)paren
suffix:semicolon
r_register
r_int
id|f16
id|asm
(paren
l_string|&quot;f16&quot;
)paren
suffix:semicolon
r_register
r_int
id|f17
id|asm
(paren
l_string|&quot;f17&quot;
)paren
suffix:semicolon
r_register
r_int
id|f18
id|asm
(paren
l_string|&quot;f18&quot;
)paren
suffix:semicolon
r_register
r_int
id|f19
id|asm
(paren
l_string|&quot;f19&quot;
)paren
suffix:semicolon
r_register
r_int
id|f20
id|asm
(paren
l_string|&quot;f20&quot;
)paren
suffix:semicolon
r_register
r_int
id|f21
id|asm
(paren
l_string|&quot;f21&quot;
)paren
suffix:semicolon
r_register
r_int
id|f22
id|asm
(paren
l_string|&quot;f22&quot;
)paren
suffix:semicolon
r_register
r_int
id|f23
id|asm
(paren
l_string|&quot;f23&quot;
)paren
suffix:semicolon
r_register
r_float
id|f24
id|asm
(paren
l_string|&quot;f24&quot;
)paren
suffix:semicolon
r_register
r_float
id|f25
id|asm
(paren
l_string|&quot;f25&quot;
)paren
suffix:semicolon
r_register
r_float
id|f26
id|asm
(paren
l_string|&quot;f26&quot;
)paren
suffix:semicolon
r_register
r_float
id|f27
id|asm
(paren
l_string|&quot;f27&quot;
)paren
suffix:semicolon
r_register
r_float
id|f28
id|asm
(paren
l_string|&quot;f28&quot;
)paren
suffix:semicolon
r_register
r_float
id|f29
id|asm
(paren
l_string|&quot;f29&quot;
)paren
suffix:semicolon
r_register
r_float
id|f30
id|asm
(paren
l_string|&quot;f30&quot;
)paren
suffix:semicolon
r_register
r_float
id|f31
id|asm
(paren
l_string|&quot;f31&quot;
)paren
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;&t;&t;/* For unblank_screen() */
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/fpswa.h&gt;
r_extern
id|spinlock_t
id|timerlist_lock
suffix:semicolon
DECL|variable|fpswa_interface
r_static
id|fpswa_interface_t
op_star
id|fpswa_interface
suffix:semicolon
r_void
id|__init
DECL|function|trap_init
id|trap_init
(paren
r_void
)paren
(brace
r_int
id|major
op_assign
l_int|0
comma
id|minor
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ia64_boot_param-&gt;fpswa
)paren
(brace
multiline_comment|/* FPSWA fixup: make the interface pointer a kernel virtual address: */
id|fpswa_interface
op_assign
id|__va
c_func
(paren
id|ia64_boot_param-&gt;fpswa
)paren
suffix:semicolon
id|major
op_assign
id|fpswa_interface-&gt;revision
op_rshift
l_int|16
suffix:semicolon
id|minor
op_assign
id|fpswa_interface-&gt;revision
op_amp
l_int|0xffff
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fpswa interface at %lx (rev %d.%d)&bslash;n&quot;
comma
id|ia64_boot_param-&gt;fpswa
comma
id|major
comma
id|minor
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unlock any spinlocks which will prevent us from getting the message out (timerlist_lock&n; * is acquired through the console unblank code)&n; */
r_void
DECL|function|bust_spinlocks
id|bust_spinlocks
(paren
r_int
id|yes
)paren
(brace
r_int
id|loglevel_save
op_assign
id|console_loglevel
suffix:semicolon
r_if
c_cond
(paren
id|yes
)paren
(brace
id|oops_in_progress
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VT
id|unblank_screen
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|oops_in_progress
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * OK, the message is on the console.  Now we call printk() without&n;&t; * oops_in_progress set so that printk will give klogd a poke.  Hold onto&n;&t; * your hats...&n;&t; */
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* NMI oopser may have shut the console up */
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|loglevel_save
suffix:semicolon
)brace
r_void
DECL|function|die
id|die
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
r_static
r_struct
(brace
id|spinlock_t
id|lock
suffix:semicolon
r_int
id|lock_owner
suffix:semicolon
r_int
id|lock_owner_depth
suffix:semicolon
)brace
id|die
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
dot
id|lock_owner
op_assign
op_minus
l_int|1
comma
dot
id|lock_owner_depth
op_assign
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
id|die.lock_owner
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|die.lock
)paren
suffix:semicolon
id|die.lock_owner
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|die.lock_owner_depth
op_assign
l_int|0
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|die.lock_owner_depth
OL
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s[%d]: %s %ld&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|str
comma
id|err
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Recursive die() failure, output suppressed&bslash;n&quot;
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|die.lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die.lock
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
r_void
DECL|function|die_if_kernel
id|die_if_kernel
(paren
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
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
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
r_void
DECL|function|ia64_bad_break
id|ia64_bad_break
(paren
r_int
r_int
id|break_num
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|siginfo
suffix:semicolon
r_int
id|sig
comma
id|code
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, and SIGBUS want these field initialized: */
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
id|siginfo.si_imm
op_assign
id|break_num
suffix:semicolon
id|siginfo.si_flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear __ISR_VALID */
id|siginfo.si_isr
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|break_num
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* unknown error (used by GCC for __builtin_abort()) */
id|die_if_kernel
c_func
(paren
l_string|&quot;bugcheck!&quot;
comma
id|regs
comma
id|break_num
)paren
suffix:semicolon
id|sig
op_assign
id|SIGILL
suffix:semicolon
id|code
op_assign
id|ILL_ILLOPC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* integer divide by zero */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|FPE_INTDIV
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* integer overflow */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|FPE_INTOVF
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* range check/bounds check */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|FPE_FLTSUB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* null pointer dereference */
id|sig
op_assign
id|SIGSEGV
suffix:semicolon
id|code
op_assign
id|SEGV_MAPERR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* misaligned data */
id|sig
op_assign
id|SIGSEGV
suffix:semicolon
id|code
op_assign
id|BUS_ADRALN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* decimal overflow */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|__FPE_DECOVF
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* decimal divide by zero */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|__FPE_DECDIV
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* packed decimal error */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|__FPE_DECERR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
multiline_comment|/* invalid ASCII digit */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|__FPE_INVASC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
multiline_comment|/* invalid decimal digit */
id|sig
op_assign
id|SIGFPE
suffix:semicolon
id|code
op_assign
id|__FPE_INVDEC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
multiline_comment|/* paragraph stack overflow */
id|sig
op_assign
id|SIGSEGV
suffix:semicolon
id|code
op_assign
id|__SEGV_PSTKOVF
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3f000
dot
dot
dot
l_int|0x3ffff
suffix:colon
multiline_comment|/* bundle-update in progress */
id|sig
op_assign
id|SIGILL
suffix:semicolon
id|code
op_assign
id|__ILL_BNDMOD
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|break_num
template_param
l_int|0x100000
)paren
id|die_if_kernel
c_func
(paren
l_string|&quot;Bad break&quot;
comma
id|regs
comma
id|break_num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|break_num
OL
l_int|0x80000
)paren
(brace
id|sig
op_assign
id|SIGILL
suffix:semicolon
id|code
op_assign
id|__ILL_BREAK
suffix:semicolon
)brace
r_else
(brace
id|sig
op_assign
id|SIGTRAP
suffix:semicolon
id|code
op_assign
id|TRAP_BRKPT
suffix:semicolon
)brace
)brace
id|siginfo.si_signo
op_assign
id|sig
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|code
suffix:semicolon
id|force_sig_info
c_func
(paren
id|sig
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unimplemented system calls.  This is called only for stuff that&n; * we&squot;re supposed to implement but haven&squot;t done so yet.  Everything&n; * else goes to sys_ni_syscall.&n; */
id|asmlinkage
r_int
DECL|function|ia64_ni_syscall
id|ia64_ni_syscall
(paren
r_int
r_int
id|arg0
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
comma
r_int
r_int
id|arg5
comma
r_int
r_int
id|arg6
comma
r_int
r_int
id|arg7
comma
r_int
r_int
id|stack
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|stack
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(%d): &lt;sc%ld(%lx,%lx,%lx,%lx)&gt;&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;r15
comma
id|arg0
comma
id|arg1
comma
id|arg2
comma
id|arg3
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/*&n; * disabled_fph_fault() is called when a user-level process attempts to access f32..f127&n; * and it doesn&squot;t own the fp-high register partition.  When this happens, we save the&n; * current fph partition in the task_struct of the fpu-owner (if necessary) and then load&n; * the fp-high partition of the current task (if necessary).  Note that the kernel has&n; * access to fph by the time we get here, as the IVT&squot;s &quot;Disabled FP-Register&quot; handler takes&n; * care of clearing psr.dfh.&n; */
r_static
r_inline
r_void
DECL|function|disabled_fph_fault
id|disabled_fph_fault
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|ia64_psr
op_star
id|psr
op_assign
id|ia64_psr
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* first, grant user-level access to fph partition: */
id|psr-&gt;dfh
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
(brace
r_struct
id|task_struct
op_star
id|fpu_owner
op_assign
id|ia64_get_fpu_owner
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpu_owner
op_eq
id|current
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|fpu_owner
)paren
id|ia64_flush_fph
c_func
(paren
id|fpu_owner
)paren
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_SMP */
id|ia64_set_fpu_owner
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
(brace
id|__ia64_load_fpu
c_func
(paren
id|current-&gt;thread.fph
)paren
suffix:semicolon
id|psr-&gt;mfh
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|__ia64_init_fpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set mfh because the state in thread.fph does not match the state in&n;&t;&t; * the fph partition.&n;&t;&t; */
id|psr-&gt;mfh
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_static
r_inline
r_int
DECL|function|fp_emulate
id|fp_emulate
(paren
r_int
id|fp_fault
comma
r_void
op_star
id|bundle
comma
r_int
op_star
id|ipsr
comma
r_int
op_star
id|fpsr
comma
r_int
op_star
id|isr
comma
r_int
op_star
id|pr
comma
r_int
op_star
id|ifs
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|ia64_fpreg
id|f6_11
(braket
l_int|6
)braket
suffix:semicolon
id|fp_state_t
id|fp_state
suffix:semicolon
id|fpswa_ret_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpswa_interface
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|fp_state
comma
l_int|0
comma
r_sizeof
(paren
id|fp_state_t
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * compute fp_state.  only FP registers f6 - f11 are used by the&n;&t; * kernel, so set those bits in the mask and set the low volatile&n;&t; * pointer to point to these registers.&n;&t; */
id|fp_state.bitmask_low64
op_assign
l_int|0xfc0
suffix:semicolon
multiline_comment|/* bit6..bit11 */
id|f6_11
(braket
l_int|0
)braket
op_assign
id|regs-&gt;f6
suffix:semicolon
id|f6_11
(braket
l_int|1
)braket
op_assign
id|regs-&gt;f7
suffix:semicolon
id|f6_11
(braket
l_int|2
)braket
op_assign
id|regs-&gt;f8
suffix:semicolon
id|f6_11
(braket
l_int|3
)braket
op_assign
id|regs-&gt;f9
suffix:semicolon
id|__asm__
(paren
l_string|&quot;stf.spill %0=f10%P0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|f6_11
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;stf.spill %0=f11%P0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|f6_11
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|fp_state.fp_state_low_volatile
op_assign
(paren
id|fp_state_low_volatile_t
op_star
)paren
id|f6_11
suffix:semicolon
multiline_comment|/*&n;&t; * unsigned long (*EFI_FPSWA) (&n;&t; *      unsigned long    trap_type,&n;&t; *&t;void             *Bundle,&n;&t; *&t;unsigned long    *pipsr,&n;&t; *&t;unsigned long    *pfsr,&n;&t; *&t;unsigned long    *pisr,&n;&t; *&t;unsigned long    *ppreds,&n;&t; *&t;unsigned long    *pifs,&n;&t; *&t;void             *fp_state);&n;&t; */
id|ret
op_assign
(paren
op_star
id|fpswa_interface-&gt;fpswa
)paren
(paren
(paren
r_int
r_int
)paren
id|fp_fault
comma
id|bundle
comma
(paren
r_int
r_int
op_star
)paren
id|ipsr
comma
(paren
r_int
r_int
op_star
)paren
id|fpsr
comma
(paren
r_int
r_int
op_star
)paren
id|isr
comma
(paren
r_int
r_int
op_star
)paren
id|pr
comma
(paren
r_int
r_int
op_star
)paren
id|ifs
comma
op_amp
id|fp_state
)paren
suffix:semicolon
id|regs-&gt;f6
op_assign
id|f6_11
(braket
l_int|0
)braket
suffix:semicolon
id|regs-&gt;f7
op_assign
id|f6_11
(braket
l_int|1
)braket
suffix:semicolon
id|regs-&gt;f8
op_assign
id|f6_11
(braket
l_int|2
)braket
suffix:semicolon
id|regs-&gt;f9
op_assign
id|f6_11
(braket
l_int|3
)braket
suffix:semicolon
id|__asm__
(paren
l_string|&quot;ldf.fill f10=%0%P0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|f6_11
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;ldf.fill f11=%0%P0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|f6_11
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
r_return
id|ret.status
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle floating-point assist faults and traps.&n; */
r_static
r_int
DECL|function|handle_fpu_swa
id|handle_fpu_swa
(paren
r_int
id|fp_fault
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|isr
)paren
(brace
r_int
id|exception
comma
id|bundle
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|fault_ip
suffix:semicolon
r_struct
id|siginfo
id|siginfo
suffix:semicolon
r_static
r_int
id|fpu_swa_count
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|last_time
suffix:semicolon
id|fault_ip
op_assign
id|regs-&gt;cr_iip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp_fault
op_logical_and
(paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_eq
l_int|0
)paren
)paren
id|fault_ip
op_sub_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|bundle
comma
(paren
r_void
op_star
)paren
id|fault_ip
comma
r_sizeof
(paren
id|bundle
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_minus
id|last_time
OG
l_int|5
op_star
id|HZ
)paren
id|fpu_swa_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_increment
id|fpu_swa_count
OL
l_int|5
)paren
op_logical_and
op_logical_neg
(paren
id|current-&gt;thread.flags
op_amp
id|IA64_THREAD_FPEMU_NOPRINT
)paren
)paren
(brace
id|last_time
op_assign
id|jiffies
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s(%d): floating-point assist fault at ip %016lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
)brace
id|exception
op_assign
id|fp_emulate
c_func
(paren
id|fp_fault
comma
id|bundle
comma
op_amp
id|regs-&gt;cr_ipsr
comma
op_amp
id|regs-&gt;ar_fpsr
comma
op_amp
id|isr
comma
op_amp
id|regs-&gt;pr
comma
op_amp
id|regs-&gt;cr_ifs
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp_fault
)paren
(brace
r_if
c_cond
(paren
id|exception
op_eq
l_int|0
)paren
(brace
multiline_comment|/* emulation was successful */
id|ia64_increment_ip
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|exception
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;handle_fpu_swa: fp_emulate() returned -1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* is next instruction a trap? */
r_if
c_cond
(paren
id|exception
op_amp
l_int|2
)paren
(brace
id|ia64_increment_ip
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
id|siginfo.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|__SI_FAULT
suffix:semicolon
multiline_comment|/* default code */
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x11
)paren
(brace
id|siginfo.si_code
op_assign
id|FPE_FLTINV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x44
)paren
(brace
id|siginfo.si_code
op_assign
id|FPE_FLTDIV
suffix:semicolon
)brace
id|siginfo.si_isr
op_assign
id|isr
suffix:semicolon
id|siginfo.si_flags
op_assign
id|__ISR_VALID
suffix:semicolon
id|siginfo.si_imm
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|exception
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;handle_fpu_swa: fp_emulate() returned -1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|exception
op_ne
l_int|0
)paren
(brace
multiline_comment|/* raise exception */
id|siginfo.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|__SI_FAULT
suffix:semicolon
multiline_comment|/* default code */
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x880
)paren
(brace
id|siginfo.si_code
op_assign
id|FPE_FLTOVF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x1100
)paren
(brace
id|siginfo.si_code
op_assign
id|FPE_FLTUND
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x2200
)paren
(brace
id|siginfo.si_code
op_assign
id|FPE_FLTRES
suffix:semicolon
)brace
id|siginfo.si_isr
op_assign
id|isr
suffix:semicolon
id|siginfo.si_flags
op_assign
id|__ISR_VALID
suffix:semicolon
id|siginfo.si_imm
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|illegal_op_return
r_struct
id|illegal_op_return
(brace
DECL|member|fkt
DECL|member|arg1
DECL|member|arg2
DECL|member|arg3
r_int
r_int
id|fkt
comma
id|arg1
comma
id|arg2
comma
id|arg3
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|illegal_op_return
DECL|function|ia64_illegal_op_fault
id|ia64_illegal_op_fault
(paren
r_int
r_int
id|ec
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
comma
r_int
r_int
id|arg5
comma
r_int
r_int
id|arg6
comma
r_int
r_int
id|arg7
comma
r_int
r_int
id|stack
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|stack
suffix:semicolon
r_struct
id|illegal_op_return
id|rv
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_BRL_EMU
(brace
r_extern
r_struct
id|illegal_op_return
id|ia64_emulate_brl
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|rv
op_assign
id|ia64_emulate_brl
c_func
(paren
id|regs
comma
id|ec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv.fkt
op_ne
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
r_return
id|rv
suffix:semicolon
)brace
macro_line|#endif
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;IA-64 Illegal operation fault&quot;
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
id|buf
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|si
comma
l_int|0
comma
r_sizeof
(paren
id|si
)paren
)paren
suffix:semicolon
id|si.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|si.si_code
op_assign
id|ILL_ILLOPC
suffix:semicolon
id|si.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
id|rv.fkt
op_assign
l_int|0
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
r_void
DECL|function|ia64_fault
id|ia64_fault
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|isr
comma
r_int
r_int
id|ifa
comma
r_int
r_int
id|iim
comma
r_int
r_int
id|itir
comma
r_int
r_int
id|arg5
comma
r_int
r_int
id|arg6
comma
r_int
r_int
id|arg7
comma
r_int
r_int
id|stack
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|stack
suffix:semicolon
r_int
r_int
id|code
comma
id|error
op_assign
id|isr
suffix:semicolon
r_struct
id|siginfo
id|siginfo
suffix:semicolon
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|result
comma
id|sig
suffix:semicolon
r_static
r_const
r_char
op_star
id|reason
(braket
)braket
op_assign
(brace
l_string|&quot;IA-64 Illegal Operation fault&quot;
comma
l_string|&quot;IA-64 Privileged Operation fault&quot;
comma
l_string|&quot;IA-64 Privileged Register fault&quot;
comma
l_string|&quot;IA-64 Reserved Register/Field fault&quot;
comma
l_string|&quot;Disabled Instruction Set Transition fault&quot;
comma
l_string|&quot;Unknown fault 5&quot;
comma
l_string|&quot;Unknown fault 6&quot;
comma
l_string|&quot;Unknown fault 7&quot;
comma
l_string|&quot;Illegal Hazard fault&quot;
comma
l_string|&quot;Unknown fault 9&quot;
comma
l_string|&quot;Unknown fault 10&quot;
comma
l_string|&quot;Unknown fault 11&quot;
comma
l_string|&quot;Unknown fault 12&quot;
comma
l_string|&quot;Unknown fault 13&quot;
comma
l_string|&quot;Unknown fault 14&quot;
comma
l_string|&quot;Unknown fault 15&quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|isr
op_amp
id|IA64_ISR_NA
)paren
op_logical_and
(paren
(paren
id|isr
op_amp
id|IA64_ISR_CODE_MASK
)paren
op_eq
id|IA64_ISR_CODE_LFETCH
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This fault was due to lfetch.fault, set &quot;ed&quot; bit in the psr to cancel&n;&t;&t; * the lfetch.&n;&t;&t; */
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ed
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|vector
)paren
(brace
r_case
l_int|24
suffix:colon
multiline_comment|/* General Exception */
id|code
op_assign
(paren
id|isr
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;General Exception: %s%s&quot;
comma
id|reason
(braket
id|code
)braket
comma
(paren
id|code
op_eq
l_int|3
)paren
ques
c_cond
(paren
(paren
id|isr
op_amp
(paren
l_int|1UL
op_lshift
l_int|37
)paren
)paren
ques
c_cond
l_string|&quot; (RSE access)&quot;
suffix:colon
l_string|&quot; (data access)&quot;
)paren
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
l_int|8
)paren
(brace
macro_line|# ifdef CONFIG_IA64_PRINT_HAZARDS
id|printk
c_func
(paren
l_string|&quot;%s[%d]: possible hazard @ ip=%016lx (pr = %016lx)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
comma
id|regs-&gt;pr
)paren
suffix:semicolon
macro_line|# endif
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
multiline_comment|/* Disabled FP-Register */
r_if
c_cond
(paren
id|isr
op_amp
l_int|2
)paren
(brace
id|disabled_fph_fault
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Disabled FPL fault---not supposed to happen!&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|26
suffix:colon
multiline_comment|/* NaT Consumption */
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
r_void
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|isr
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
op_eq
l_int|2
)paren
(brace
multiline_comment|/* NaT page consumption */
id|sig
op_assign
id|SIGSEGV
suffix:semicolon
id|code
op_assign
id|SEGV_ACCERR
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
id|ifa
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* register NaT consumption */
id|sig
op_assign
id|SIGILL
suffix:semicolon
id|code
op_assign
id|ILL_ILLOPN
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
)brace
id|siginfo.si_signo
op_assign
id|sig
suffix:semicolon
id|siginfo.si_code
op_assign
id|code
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_addr
op_assign
id|addr
suffix:semicolon
id|siginfo.si_imm
op_assign
id|vector
suffix:semicolon
id|siginfo.si_flags
op_assign
id|__ISR_VALID
suffix:semicolon
id|siginfo.si_isr
op_assign
id|isr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|sig
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|done_with_exception
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;NaT consumption&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|31
suffix:colon
multiline_comment|/* Unsupported Data Reference */
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
id|siginfo.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|siginfo.si_code
op_assign
id|ILL_ILLOPN
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
id|siginfo.si_imm
op_assign
id|vector
suffix:semicolon
id|siginfo.si_flags
op_assign
id|__ISR_VALID
suffix:semicolon
id|siginfo.si_isr
op_assign
id|isr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Unsupported data reference&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|29
suffix:colon
multiline_comment|/* Debug */
r_case
l_int|35
suffix:colon
multiline_comment|/* Taken Branch Trap */
r_case
l_int|36
suffix:colon
multiline_comment|/* Single Step Trap */
macro_line|#ifdef CONFIG_FSYS
r_if
c_cond
(paren
id|fsys_mode
c_func
(paren
id|current
comma
id|regs
)paren
)paren
(brace
r_extern
r_char
id|syscall_via_break
(braket
)braket
comma
id|__start_gate_section
(braket
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Got a trap in fsys-mode: Taken Branch Trap and Single Step trap&n;&t;&t;&t; * need special handling; Debug trap is not supposed to happen.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|vector
op_eq
l_int|29
)paren
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Got debug trap in fsys-mode---not supposed to happen!&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* re-do the system call via break 0x100000: */
id|regs-&gt;cr_iip
op_assign
id|GATE_ADDR
op_plus
(paren
id|syscall_via_break
op_minus
id|__start_gate_section
)paren
suffix:semicolon
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_assign
l_int|0
suffix:semicolon
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|cpl
op_assign
l_int|3
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
r_switch
c_cond
(paren
id|vector
)paren
(brace
r_case
l_int|29
suffix:colon
id|siginfo.si_code
op_assign
id|TRAP_HWBKPT
suffix:semicolon
macro_line|#ifdef CONFIG_ITANIUM
multiline_comment|/*&n;&t;&t;&t; * Erratum 10 (IFA may contain incorrect address) now has&n;&t;&t;&t; * &quot;NoFix&quot; status.  There are no plans for fixing this.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|is
op_eq
l_int|0
)paren
id|ifa
op_assign
id|regs-&gt;cr_iip
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|35
suffix:colon
id|siginfo.si_code
op_assign
id|TRAP_BRANCH
suffix:semicolon
id|ifa
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|36
suffix:colon
id|siginfo.si_code
op_assign
id|TRAP_TRACE
suffix:semicolon
id|ifa
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|siginfo.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_flags
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_isr
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
id|ifa
suffix:semicolon
id|siginfo.si_imm
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|32
suffix:colon
multiline_comment|/* fp fault */
r_case
l_int|33
suffix:colon
multiline_comment|/* fp trap */
id|result
op_assign
id|handle_fpu_swa
c_func
(paren
(paren
id|vector
op_eq
l_int|32
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|regs
comma
id|isr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
OL
l_int|0
)paren
op_logical_or
(paren
id|current-&gt;thread.flags
op_amp
id|IA64_THREAD_FPEMU_SIGFPE
)paren
)paren
(brace
id|siginfo.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|FPE_FLTINV
suffix:semicolon
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
id|siginfo.si_flags
op_assign
id|__ISR_VALID
suffix:semicolon
id|siginfo.si_isr
op_assign
id|isr
suffix:semicolon
id|siginfo.si_imm
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
r_case
l_int|34
suffix:colon
r_if
c_cond
(paren
id|isr
op_amp
l_int|0x2
)paren
(brace
multiline_comment|/* Lower-Privilege Transfer Trap */
multiline_comment|/*&n;&t;&t;&t; * Just clear PSR.lp and then return immediately: all the&n;&t;&t;&t; * interesting work (e.g., signal delivery is done in the kernel&n;&t;&t;&t; * exit path).&n;&t;&t;&t; */
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|lp
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Unimplemented Instr. Address Trap */
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
id|siginfo.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|siginfo.si_code
op_assign
id|ILL_BADIADDR
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_flags
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_isr
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_imm
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
op_plus
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Unimplemented Instruction Address fault&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|45
suffix:colon
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|ia32_exception
c_func
(paren
id|regs
comma
id|isr
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unexpected IA-32 exception (Trap 45)&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;  iip - 0x%lx, ifa - 0x%lx, isr - 0x%lx&bslash;n&quot;
comma
id|regs-&gt;cr_iip
comma
id|ifa
comma
id|isr
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|46
suffix:colon
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|ia32_intercept
c_func
(paren
id|regs
comma
id|isr
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unexpected IA-32 intercept trap (Trap 46)&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;  iip - 0x%lx, ifa - 0x%lx, isr - 0x%lx, iim - 0x%lx&bslash;n&quot;
comma
id|regs-&gt;cr_iip
comma
id|ifa
comma
id|isr
comma
id|iim
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|47
suffix:colon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;IA-32 Interruption Fault (int 0x%lx)&quot;
comma
id|isr
op_rshift
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Fault %lu&quot;
comma
id|vector
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|die_if_kernel
c_func
(paren
id|buf
comma
id|regs
comma
id|error
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
)brace
eof
