multiline_comment|/*&n; *  linux/arch/ppc64/kernel/traps.c&n; *&n; *  Copyright (C) 1995-1996  Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  and Paul Mackerras (paulus@cs.anu.edu.au)&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of hardware exceptions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
r_extern
r_int
id|fix_alignment
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bad_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* This is true if we are using the firmware NMI handler (typically LPAR) */
r_extern
r_int
id|fwnmi_active
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_KERNEL
DECL|variable|debugger
r_void
(paren
op_star
id|debugger
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_bpt
r_int
(paren
op_star
id|debugger_bpt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_sstep
r_int
(paren
op_star
id|debugger_sstep
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_iabr_match
r_int
(paren
op_star
id|debugger_iabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_dabr_match
r_int
(paren
op_star
id|debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_fault_handler
r_void
(paren
op_star
id|debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Trap &amp; Exception support&n; */
multiline_comment|/* Should we panic on bad kernel exceptions or try to recover */
DECL|macro|PANIC_ON_ERROR
macro_line|#undef PANIC_ON_ERROR
DECL|variable|die_lock
r_static
id|spinlock_t
id|die_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
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
r_static
r_int
id|die_counter
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
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Oops: %s, sig: %ld [#%d]&bslash;n&quot;
comma
id|str
comma
id|err
comma
op_increment
id|die_counter
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
macro_line|#ifdef PANIC_ON_ERROR
id|panic
c_func
(paren
id|str
)paren
suffix:semicolon
macro_line|#else
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
DECL|function|_exception
id|_exception
c_func
(paren
r_int
id|signr
comma
id|siginfo_t
op_star
id|info
comma
r_struct
id|pt_regs
op_star
id|regs
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
(brace
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger
)paren
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|die
c_func
(paren
l_string|&quot;Exception in kernel mode&bslash;n&quot;
comma
id|regs
comma
id|signr
)paren
suffix:semicolon
)brace
id|force_sig_info
c_func
(paren
id|signr
comma
id|info
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the error information for errors coming through the&n; * FWNMI vectors.  The pt_regs&squot; r3 will be updated to reflect&n; * the actual r3 if possible, and a ptr to the error log entry&n; * will be returned if found.&n; */
DECL|function|FWNMI_get_errinfo
r_static
r_struct
id|rtas_error_log
op_star
id|FWNMI_get_errinfo
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
id|errdata
op_assign
id|regs-&gt;gpr
(braket
l_int|3
)braket
suffix:semicolon
r_struct
id|rtas_error_log
op_star
id|errhdr
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|savep
suffix:semicolon
r_if
c_cond
(paren
(paren
id|errdata
op_ge
l_int|0x7000
op_logical_and
id|errdata
OL
l_int|0x7fff0
)paren
op_logical_or
(paren
id|errdata
op_ge
id|rtas.base
op_logical_and
id|errdata
OL
id|rtas.base
op_plus
id|rtas.size
op_minus
l_int|16
)paren
)paren
(brace
id|savep
op_assign
id|__va
c_func
(paren
id|errdata
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|savep
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* restore original r3 */
id|errhdr
op_assign
(paren
r_struct
id|rtas_error_log
op_star
)paren
(paren
id|savep
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;FWNMI: corrupt r3&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|errhdr
suffix:semicolon
)brace
multiline_comment|/* Call this when done with the data returned by FWNMI_get_errinfo.&n; * It will release the saved data area for other CPUs in the&n; * partition to receive FWNMI errors.&n; */
DECL|function|FWNMI_release_errinfo
r_static
r_void
id|FWNMI_release_errinfo
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ret
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,nmi-interlock&quot;
)paren
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;FWNMI: nmi-interlock failed: %ld&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
r_void
DECL|function|SystemResetException
id|SystemResetException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|fwnmi_active
)paren
(brace
r_struct
id|rtas_error_log
op_star
id|errhdr
op_assign
id|FWNMI_get_errinfo
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errhdr
)paren
(brace
multiline_comment|/* XXX Should look at FWNMI information */
)brace
id|FWNMI_release_errinfo
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger
)paren
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef PANIC_ON_ERROR
id|panic
c_func
(paren
l_string|&quot;System Reset&quot;
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Must die if the interrupt is not recoverable */
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;msr
op_amp
id|MSR_RI
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Unrecoverable System Reset&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* What should we do here? We could issue a shutdown or hard reset. */
)brace
multiline_comment|/* &n; * See if we can recover from a machine check exception.&n; * This is only called on power4 (or above) and only via&n; * the Firmware Non-Maskable Interrupts (fwnmi) handler&n; * which provides the error analysis for us.&n; *&n; * Return 1 if corrected (or delivered a signal).&n; * Return 0 if there is nothing we can do.&n; */
DECL|function|recover_mce
r_static
r_int
id|recover_mce
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|rtas_error_log
id|err
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|err.disposition
op_eq
id|DISP_FULLY_RECOVERED
)paren
(brace
multiline_comment|/* Platform corrected itself */
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|regs-&gt;msr
op_amp
id|MSR_RI
)paren
op_logical_and
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
id|err.severity
op_eq
id|SEVERITY_ERROR_SYNC
op_logical_and
id|err.disposition
op_eq
id|DISP_NOT_RECOVERED
op_logical_and
id|err.target
op_eq
id|TARGET_MEMORY
op_logical_and
id|err.type
op_eq
id|TYPE_ECC_UNCORR
op_logical_and
op_logical_neg
(paren
id|current-&gt;pid
op_eq
l_int|0
op_logical_or
id|current-&gt;pid
op_eq
l_int|1
)paren
)paren
(brace
multiline_comment|/* Kill off a user process with an ECC error */
id|info.si_signo
op_assign
id|SIGBUS
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX something better for ECC error? */
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
id|regs-&gt;nip
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;MCE: uncorrectable ecc error for pid %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|_exception
c_func
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a machine check.&n; *&n; * Note that on Power 4 and beyond Firmware Non-Maskable Interrupts (fwnmi)&n; * should be present.  If so the handler which called us tells us if the&n; * error was recovered (never true if RI=0).&n; *&n; * On hardware prior to Power 4 these exceptions were asynchronous which&n; * means we can&squot;t tell exactly where it occurred and so we can&squot;t recover.&n; *&n; * Note that the debugger should test RI=0 and warn the user that system&n; * state has been corrupted.&n; */
r_void
DECL|function|MachineCheckException
id|MachineCheckException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|rtas_error_log
id|err
comma
op_star
id|errp
suffix:semicolon
r_if
c_cond
(paren
id|fwnmi_active
)paren
(brace
id|errp
op_assign
id|FWNMI_get_errinfo
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errp
)paren
id|err
op_assign
op_star
id|errp
suffix:semicolon
id|FWNMI_release_errinfo
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* frees errp */
r_if
c_cond
(paren
id|errp
op_logical_and
id|recover_mce
c_func
(paren
id|regs
comma
id|err
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger_fault_handler
)paren
(brace
id|debugger_fault_handler
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debugger
)paren
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
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
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Machine check in kernel mode.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Caused by (from SRR1=%lx): &quot;
comma
id|regs-&gt;msr
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Unrecoverable Machine Check&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|UnknownException
id|UnknownException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bad trap at PC: %lx, SR: %lx, vector=%lx&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
comma
id|regs-&gt;trap
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
l_int|0
suffix:semicolon
id|info.si_addr
op_assign
l_int|0
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|InstructionBreakpointException
id|InstructionBreakpointException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger_iabr_match
op_logical_and
id|debugger_iabr_match
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
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
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|parse_fpe
r_static
r_void
id|parse_fpe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_int
r_int
id|fpscr
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
id|fpscr
op_assign
id|current-&gt;thread.fpscr
suffix:semicolon
multiline_comment|/* Invalid operation */
r_if
c_cond
(paren
(paren
id|fpscr
op_amp
id|FPSCR_VE
)paren
op_logical_and
(paren
id|fpscr
op_amp
id|FPSCR_VX
)paren
)paren
id|info.si_code
op_assign
id|FPE_FLTINV
suffix:semicolon
multiline_comment|/* Overflow */
r_else
r_if
c_cond
(paren
(paren
id|fpscr
op_amp
id|FPSCR_OE
)paren
op_logical_and
(paren
id|fpscr
op_amp
id|FPSCR_OX
)paren
)paren
id|info.si_code
op_assign
id|FPE_FLTOVF
suffix:semicolon
multiline_comment|/* Underflow */
r_else
r_if
c_cond
(paren
(paren
id|fpscr
op_amp
id|FPSCR_UE
)paren
op_logical_and
(paren
id|fpscr
op_amp
id|FPSCR_UX
)paren
)paren
id|info.si_code
op_assign
id|FPE_FLTUND
suffix:semicolon
multiline_comment|/* Divide by zero */
r_else
r_if
c_cond
(paren
(paren
id|fpscr
op_amp
id|FPSCR_ZE
)paren
op_logical_and
(paren
id|fpscr
op_amp
id|FPSCR_ZX
)paren
)paren
id|info.si_code
op_assign
id|FPE_FLTDIV
suffix:semicolon
multiline_comment|/* Inexact result */
r_else
r_if
c_cond
(paren
(paren
id|fpscr
op_amp
id|FPSCR_XE
)paren
op_logical_and
(paren
id|fpscr
op_amp
id|FPSCR_XX
)paren
)paren
id|info.si_code
op_assign
id|FPE_FLTRES
suffix:semicolon
r_else
id|info.si_code
op_assign
l_int|0
suffix:semicolon
id|info.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGFPE
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|ProgramCheckException
id|ProgramCheckException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
l_int|0x100000
)paren
(brace
multiline_comment|/* IEEE FP exception */
id|parse_fpe
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
id|regs-&gt;msr
op_amp
l_int|0x40000
)paren
(brace
multiline_comment|/* Privileged instruction */
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
id|ILL_PRVOPC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
l_int|0x20000
)paren
(brace
multiline_comment|/* trap exception */
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger_bpt
op_logical_and
id|debugger_bpt
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
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
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Illegal instruction */
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
id|ILL_ILLTRP
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|SingleStepException
id|SingleStepException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_SE
suffix:semicolon
multiline_comment|/* Turn off &squot;trace&squot; bit */
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger_sstep
op_logical_and
id|debugger_sstep
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
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
id|TRAP_TRACE
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|PerformanceMonitorException
id|PerformanceMonitorException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
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
l_int|0
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|AlignmentException
id|AlignmentException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|fixed
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
id|fixed
op_assign
id|fix_alignment
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixed
op_eq
l_int|1
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
id|PPCDBG
c_func
(paren
id|PPCDBG_ALIGNFIXUP
comma
l_string|&quot;fix alignment at %lx&bslash;n&quot;
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* skip over emulated instruction */
r_return
suffix:semicolon
)brace
multiline_comment|/* Operand address was bad */
r_if
c_cond
(paren
id|fixed
op_eq
op_minus
id|EFAULT
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
(brace
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
(paren
r_void
op_star
)paren
id|regs-&gt;dar
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
)brace
r_else
(brace
multiline_comment|/* Search exception table */
id|bad_page_fault
c_func
(paren
id|regs
comma
id|regs-&gt;dar
comma
id|SIGSEGV
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
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
id|BUS_ADRALN
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
id|_exception
c_func
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|regs
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
)brace
eof
