multiline_comment|/*&n; *  linux/arch/ppc64/kernel/traps.c&n; *&n; *  Copyright (C) 1995-1996  Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  and Paul Mackerras (paulus@cs.anu.edu.au)&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of hardware exceptions&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* This is true if we are using the firmware NMI handler (typically LPAR) */
r_extern
r_int
id|fwnmi_active
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUGGER
DECL|variable|__debugger
r_int
(paren
op_star
id|__debugger
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger_ipi
r_int
(paren
op_star
id|__debugger_ipi
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger_bpt
r_int
(paren
op_star
id|__debugger_bpt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger_sstep
r_int
(paren
op_star
id|__debugger_sstep
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger_iabr_match
r_int
(paren
op_star
id|__debugger_iabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger_dabr_match
r_int
(paren
op_star
id|__debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger_fault_handler
r_int
(paren
op_star
id|__debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|__debugger
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger
)paren
suffix:semicolon
DECL|variable|__debugger_ipi
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger_ipi
)paren
suffix:semicolon
DECL|variable|__debugger_bpt
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger_bpt
)paren
suffix:semicolon
DECL|variable|__debugger_sstep
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger_sstep
)paren
suffix:semicolon
DECL|variable|__debugger_iabr_match
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger_iabr_match
)paren
suffix:semicolon
DECL|variable|__debugger_dabr_match
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger_dabr_match
)paren
suffix:semicolon
DECL|variable|__debugger_fault_handler
id|EXPORT_SYMBOL
c_func
(paren
id|__debugger_fault_handler
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Trap &amp; Exception support&n; */
DECL|variable|die_lock
r_static
id|spinlock_t
id|die_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|die
r_int
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
r_int
id|nl
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|debugger
c_func
(paren
id|regs
)paren
)paren
r_return
l_int|1
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
macro_line|#ifdef CONFIG_PREEMPT
id|printk
c_func
(paren
l_string|&quot;PREEMPT &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|printk
c_func
(paren
l_string|&quot;SMP NR_CPUS=%d &quot;
comma
id|NR_CPUS
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_PAGEALLOC
id|printk
c_func
(paren
l_string|&quot;DEBUG_PAGEALLOC &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NUMA
id|printk
c_func
(paren
l_string|&quot;NUMA &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|systemcfg-&gt;platform
)paren
(brace
r_case
id|PLATFORM_PSERIES
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PSERIES &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PLATFORM_PSERIES_LPAR
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PSERIES LPAR &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PLATFORM_ISERIES_LPAR
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ISERIES LPAR &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PLATFORM_POWERMAC
suffix:colon
id|printk
c_func
(paren
l_string|&quot;POWERMAC &quot;
)paren
suffix:semicolon
id|nl
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nl
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Fatal exception in interrupt&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|panic_on_oops
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Fatal exception: panic in 5 seconds&bslash;n&quot;
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Fatal exception&quot;
)paren
suffix:semicolon
)brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
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
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|code
comma
r_int
r_int
id|addr
)paren
(brace
id|siginfo_t
id|info
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
r_if
c_cond
(paren
id|die
c_func
(paren
l_string|&quot;Exception in kernel mode&quot;
comma
id|regs
comma
id|signr
)paren
)paren
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.si_signo
op_assign
id|signr
suffix:semicolon
id|info.si_code
op_assign
id|code
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|addr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|signr
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
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
l_string|&quot;FWNMI: nmi-interlock failed: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#ifdef CONFIG_PPC_PSERIES
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
macro_line|#endif
id|die
c_func
(paren
l_string|&quot;System Reset&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
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
multiline_comment|/* What should we do here? We could issue a shutdown or hard reset. */
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
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
r_if
c_cond
(paren
id|err.disposition
op_eq
id|RTAS_DISP_FULLY_RECOVERED
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
id|RTAS_SEVERITY_ERROR_SYNC
op_logical_and
id|err.disposition
op_eq
id|RTAS_DISP_NOT_RECOVERED
op_logical_and
id|err.target
op_eq
id|RTAS_TARGET_MEMORY
op_logical_and
id|err.type
op_eq
id|RTAS_TYPE_ECC_UNCORR
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;MCE: uncorrectable ecc error for pid %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
multiline_comment|/* XXX something better for ECC error? */
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
comma
id|BUS_ADRERR
comma
id|regs-&gt;nip
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
macro_line|#endif
multiline_comment|/*&n; * Handle a machine check.&n; *&n; * Note that on Power 4 and beyond Firmware Non-Maskable Interrupts (fwnmi)&n; * should be present.  If so the handler which called us tells us if the&n; * error was recovered (never true if RI=0).&n; *&n; * On hardware prior to Power 4 these exceptions were asynchronous which&n; * means we can&squot;t tell exactly where it occurred and so we can&squot;t recover.&n; */
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
macro_line|#ifdef CONFIG_PPC_PSERIES
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
macro_line|#endif
r_if
c_cond
(paren
id|debugger_fault_handler
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
l_string|&quot;Machine check&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
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
l_string|&quot;Unrecoverable Machine check&quot;
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
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
comma
l_int|0
comma
l_int|0
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
r_if
c_cond
(paren
id|debugger_iabr_match
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
comma
id|TRAP_BRKPT
comma
id|regs-&gt;nip
)paren
suffix:semicolon
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
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_SE
suffix:semicolon
multiline_comment|/* Turn off &squot;trace&squot; bit */
r_if
c_cond
(paren
id|debugger_sstep
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
comma
id|TRAP_TRACE
comma
id|regs-&gt;nip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * After we have successfully emulated an instruction, we have to&n; * check if the instruction was being single-stepped, and if so,&n; * pretend we got a single-step exception.  This was pointed out&n; * by Kumar Gala.  -- paulus&n; */
DECL|function|emulate_single_step
r_static
r_inline
r_void
id|emulate_single_step
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
id|regs-&gt;msr
op_amp
id|MSR_SE
)paren
id|SingleStepException
c_func
(paren
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
r_int
id|code
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|fpscr
suffix:semicolon
id|flush_fp_to_thread
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
id|code
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
id|code
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
id|code
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
id|code
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
id|code
op_assign
id|FPE_FLTRES
suffix:semicolon
id|_exception
c_func
(paren
id|SIGFPE
comma
id|regs
comma
id|code
comma
id|regs-&gt;nip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Illegal instruction emulation support.  Return non-zero if we can&squot;t&n; * emulate, or -EFAULT if the associated memory access caused an access&n; * fault.  Return zero on success.&n; */
DECL|macro|INST_DCBA
mdefine_line|#define INST_DCBA&t;&t;0x7c0005ec
DECL|macro|INST_DCBA_MASK
mdefine_line|#define INST_DCBA_MASK&t;&t;0x7c0007fe
DECL|macro|INST_MCRXR
mdefine_line|#define INST_MCRXR&t;&t;0x7c000400
DECL|macro|INST_MCRXR_MASK
mdefine_line|#define INST_MCRXR_MASK&t;&t;0x7c0007fe
DECL|function|emulate_instruction
r_static
r_int
id|emulate_instruction
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
id|instword
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
r_return
op_minus
id|EINVAL
suffix:semicolon
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|instword
comma
(paren
r_int
r_int
id|__user
op_star
)paren
(paren
id|regs-&gt;nip
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Emulating the dcba insn is just a no-op.  */
r_if
c_cond
(paren
(paren
id|instword
op_amp
id|INST_DCBA_MASK
)paren
op_eq
id|INST_DCBA
)paren
(brace
r_static
r_int
id|warned
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|warned
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;process %d (%s) uses obsolete &squot;dcba&squot; insn&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|warned
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Emulate the mcrxr insn.  */
r_if
c_cond
(paren
(paren
id|instword
op_amp
id|INST_MCRXR_MASK
)paren
op_eq
id|INST_MCRXR
)paren
(brace
r_static
r_int
id|warned
suffix:semicolon
r_int
r_int
id|shift
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|warned
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;process %d (%s) uses obsolete &squot;mcrxr&squot; insn&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|warned
op_assign
l_int|1
suffix:semicolon
)brace
id|shift
op_assign
(paren
id|instword
op_rshift
l_int|21
)paren
op_amp
l_int|0x1c
suffix:semicolon
id|regs-&gt;ccr
op_and_assign
op_complement
(paren
l_int|0xf0000000
op_rshift
id|shift
)paren
suffix:semicolon
id|regs-&gt;ccr
op_or_assign
(paren
id|regs-&gt;xer
op_amp
l_int|0xf0000000
)paren
op_rshift
id|shift
suffix:semicolon
id|regs-&gt;xer
op_and_assign
op_complement
l_int|0xf0000000
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * Look through the list of trap instructions that are used for BUG(),&n; * BUG_ON() and WARN_ON() and see if we hit one.  At this point we know&n; * that the exception was caused by a trap instruction of some kind.&n; * Returns 1 if we should continue (i.e. it was a WARN_ON) or 0&n; * otherwise.&n; */
r_extern
r_struct
id|bug_entry
id|__start___bug_table
(braket
)braket
comma
id|__stop___bug_table
(braket
)braket
suffix:semicolon
macro_line|#ifndef CONFIG_MODULES
DECL|macro|module_find_bug
mdefine_line|#define module_find_bug(x)&t;NULL
macro_line|#endif
DECL|function|find_bug
r_static
r_struct
id|bug_entry
op_star
id|find_bug
c_func
(paren
r_int
r_int
id|bugaddr
)paren
(brace
r_struct
id|bug_entry
op_star
id|bug
suffix:semicolon
r_for
c_loop
(paren
id|bug
op_assign
id|__start___bug_table
suffix:semicolon
id|bug
OL
id|__stop___bug_table
suffix:semicolon
op_increment
id|bug
)paren
r_if
c_cond
(paren
id|bugaddr
op_eq
id|bug-&gt;bug_addr
)paren
r_return
id|bug
suffix:semicolon
r_return
id|module_find_bug
c_func
(paren
id|bugaddr
)paren
suffix:semicolon
)brace
r_int
DECL|function|check_bug_trap
id|check_bug_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|bug_entry
op_star
id|bug
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_PR
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not in kernel */
id|addr
op_assign
id|regs-&gt;nip
suffix:semicolon
multiline_comment|/* address of trap instruction */
r_if
c_cond
(paren
id|addr
OL
id|PAGE_OFFSET
)paren
r_return
l_int|0
suffix:semicolon
id|bug
op_assign
id|find_bug
c_func
(paren
id|regs-&gt;nip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bug
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bug-&gt;line
op_amp
id|BUG_WARNING_TRAP
)paren
(brace
multiline_comment|/* this is a WARN_ON rather than BUG/BUG_ON */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Badness in %s at %s:%d&bslash;n&quot;
comma
id|bug-&gt;function
comma
id|bug-&gt;file
comma
(paren
r_int
r_int
)paren
id|bug-&gt;line
op_amp
op_complement
id|BUG_WARNING_TRAP
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_void
op_star
)paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;kernel BUG in %s at %s:%d!&bslash;n&quot;
comma
id|bug-&gt;function
comma
id|bug-&gt;file
comma
(paren
r_int
r_int
)paren
id|bug-&gt;line
)paren
suffix:semicolon
r_return
l_int|0
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
id|_exception
c_func
(paren
id|SIGILL
comma
id|regs
comma
id|ILL_PRVOPC
comma
id|regs-&gt;nip
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
r_if
c_cond
(paren
id|debugger_bpt
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|check_bug_trap
c_func
(paren
id|regs
)paren
)paren
(brace
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
r_return
suffix:semicolon
)brace
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
comma
id|TRAP_BRKPT
comma
id|regs-&gt;nip
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Illegal instruction; try to emulate it.  */
r_switch
c_cond
(paren
id|emulate_instruction
c_func
(paren
id|regs
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
id|emulate_single_step
c_func
(paren
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EFAULT
suffix:colon
id|_exception
c_func
(paren
id|SIGSEGV
comma
id|regs
comma
id|SEGV_MAPERR
comma
id|regs-&gt;nip
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|_exception
c_func
(paren
id|SIGILL
comma
id|regs
comma
id|ILL_ILLOPC
comma
id|regs-&gt;nip
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|KernelFPUnavailableException
r_void
id|KernelFPUnavailableException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Unrecoverable FP Unavailable Exception &quot;
l_string|&quot;%lx at %lx&bslash;n&quot;
comma
id|regs-&gt;trap
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Unrecoverable FP Unavailable Exception&quot;
comma
id|regs
comma
id|SIGABRT
)paren
suffix:semicolon
)brace
DECL|function|AltivecUnavailableException
r_void
id|AltivecUnavailableException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifndef CONFIG_ALTIVEC
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
multiline_comment|/* A user program has executed an altivec instruction,&n;&t;&t;   but this kernel doesn&squot;t support altivec. */
id|_exception
c_func
(paren
id|SIGILL
comma
id|regs
comma
id|ILL_ILLOPC
comma
id|regs-&gt;nip
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Unrecoverable VMX/Altivec Unavailable Exception &quot;
l_string|&quot;%lx at %lx&bslash;n&quot;
comma
id|regs-&gt;trap
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Unrecoverable VMX/Altivec Unavailable Exception&quot;
comma
id|regs
comma
id|SIGABRT
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure exceptions are disabled */
DECL|macro|MMCR0_PMXE
mdefine_line|#define MMCR0_PMXE      (1UL &lt;&lt; (31 - 5))
DECL|macro|MMCR0_PMAO
mdefine_line|#define MMCR0_PMAO      (1UL &lt;&lt; (31 - 24))
DECL|function|dummy_perf
r_static
r_void
id|dummy_perf
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
id|mmcr0
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCR0
)paren
suffix:semicolon
id|mmcr0
op_and_assign
op_complement
(paren
id|MMCR0_PMXE
op_or
id|MMCR0_PMAO
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
)brace
DECL|variable|perf_irq
r_void
(paren
op_star
id|perf_irq
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
op_assign
id|dummy_perf
suffix:semicolon
DECL|variable|perf_irq
id|EXPORT_SYMBOL
c_func
(paren
id|perf_irq
)paren
suffix:semicolon
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
id|perf_irq
c_func
(paren
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
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* skip over emulated instruction */
id|emulate_single_step
c_func
(paren
id|regs
)paren
suffix:semicolon
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
id|_exception
c_func
(paren
id|SIGSEGV
comma
id|regs
comma
id|SEGV_MAPERR
comma
id|regs-&gt;dar
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
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
comma
id|BUS_ADRALN
comma
id|regs-&gt;nip
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ALTIVEC
r_void
DECL|function|AltivecAssistException
id|AltivecAssistException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|err
suffix:semicolon
id|siginfo_t
id|info
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
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;VMX/Altivec assist exception in kernel mode&quot;
l_string|&quot; at %lx&bslash;n&quot;
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Kernel VMX/Altivec assist exception&quot;
comma
id|regs
comma
id|SIGILL
)paren
suffix:semicolon
)brace
id|flush_altivec_to_thread
c_func
(paren
id|current
)paren
suffix:semicolon
id|err
op_assign
id|emulate_altivec
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* skip emulated instruction */
id|emulate_single_step
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
id|err
op_eq
op_minus
id|EFAULT
)paren
(brace
multiline_comment|/* got an error reading the instruction */
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
id|__user
op_star
)paren
id|regs-&gt;nip
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
multiline_comment|/* didn&squot;t recognize the instruction */
multiline_comment|/* XXX quick hack for now: set the non-Java bit in the VSCR */
r_if
c_cond
(paren
id|printk_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unrecognized altivec instruction &quot;
l_string|&quot;in %s at %lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|current-&gt;thread.vscr.u
(braket
l_int|3
)braket
op_or_assign
l_int|0x10000
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_ALTIVEC */
multiline_comment|/*&n; * We enter here if we get an unrecoverable exception, that is, one&n; * that happened at a point where the RI (recoverable interrupt) bit&n; * in the MSR is 0.  This indicates that SRR0/1 are live, and that&n; * we therefore lost state by taking this exception.&n; */
DECL|function|unrecoverable_exception
r_void
id|unrecoverable_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Unrecoverable exception %lx at %lx&bslash;n&quot;
comma
id|regs-&gt;trap
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Unrecoverable exception&quot;
comma
id|regs
comma
id|SIGABRT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We enter here if we discover during exception entry that we are&n; * running in supervisor mode with a userspace value in the stack pointer.&n; */
DECL|function|kernel_bad_stack
r_void
id|kernel_bad_stack
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Bad kernel stack pointer %lx at %lx&bslash;n&quot;
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Bad kernel stack pointer&quot;
comma
id|regs
comma
id|SIGABRT
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
