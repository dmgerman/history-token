multiline_comment|/*&n; *  arch/s390/kernel/traps.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *&n; *  Derived from &quot;arch/i386/kernel/traps.c&quot;&n; *    Copyright (C) 1991, 1992 Linus Torvalds&n; */
multiline_comment|/*&n; * &squot;Traps.c&squot; handles hardware traps and faults after we have saved some&n; * state in &squot;asm.s&squot;.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/mathemu.h&gt;
macro_line|#if CONFIG_REMOTE_DEBUG
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
multiline_comment|/* Called from entry.S only */
r_extern
r_void
id|handle_per_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|typedef|pgm_check_handler_t
r_typedef
r_void
id|pgm_check_handler_t
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|pgm_check_table
id|pgm_check_handler_t
op_star
id|pgm_check_table
(braket
l_int|128
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
macro_line|#ifdef CONFIG_PROCESS_DEBUG
DECL|variable|sysctl_userprocess_debug
r_int
id|sysctl_userprocess_debug
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|sysctl_userprocess_debug
r_int
id|sysctl_userprocess_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_extern
id|pgm_check_handler_t
id|do_page_fault
suffix:semicolon
r_extern
id|pgm_check_handler_t
id|do_pseudo_page_fault
suffix:semicolon
macro_line|#ifdef CONFIG_PFAULT
r_extern
r_int
id|pfault_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pfault_fini
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pfault_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u16
id|error_code
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|die_lock
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
l_string|&quot;%s: %04lx&bslash;n&quot;
comma
id|str
comma
id|err
op_amp
l_int|0xffff
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
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|macro|DO_ERROR
mdefine_line|#define DO_ERROR(signr, str, name) &bslash;&n;asmlinkage void name(struct pt_regs * regs, long interruption_code) &bslash;&n;{ &bslash;&n;&t;do_trap(interruption_code, signr, str, regs, NULL); &bslash;&n;}
DECL|macro|DO_ERROR_INFO
mdefine_line|#define DO_ERROR_INFO(signr, str, name, sicode, siaddr) &bslash;&n;asmlinkage void name(struct pt_regs * regs, long interruption_code) &bslash;&n;{ &bslash;&n;        siginfo_t info; &bslash;&n;        info.si_signo = signr; &bslash;&n;        info.si_errno = 0; &bslash;&n;        info.si_code = sicode; &bslash;&n;        info.si_addr = (void *)siaddr; &bslash;&n;        do_trap(interruption_code, signr, str, regs, &amp;info); &bslash;&n;}
DECL|function|do_trap
r_static
r_void
r_inline
id|do_trap
c_func
(paren
r_int
id|interruption_code
comma
r_int
id|signr
comma
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|siginfo_t
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
id|interruption_code
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
id|force_sig_info
c_func
(paren
id|signr
comma
id|info
comma
id|tsk
)paren
suffix:semicolon
r_else
id|force_sig
c_func
(paren
id|signr
comma
id|tsk
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SYSCTL
macro_line|#ifdef CONFIG_PROCESS_DEBUG
id|printk
c_func
(paren
l_string|&quot;User process fault: interruption code 0x%lX&bslash;n&quot;
comma
id|interruption_code
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
r_if
c_cond
(paren
id|sysctl_userprocess_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;User process fault: interruption code 0x%lX&bslash;n&quot;
comma
id|interruption_code
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
r_int
r_int
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|regs-&gt;psw.addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixup
)paren
id|regs-&gt;psw.addr
op_assign
id|fixup
suffix:semicolon
r_else
id|die
c_func
(paren
id|str
comma
id|regs
comma
id|interruption_code
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_debugger_trap
r_int
id|do_debugger_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|signal
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
(brace
id|force_sig
c_func
(paren
id|signal
comma
id|current
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
macro_line|#if CONFIG_REMOTE_DEBUG
r_if
c_cond
(paren
id|gdb_stub_initialised
)paren
(brace
id|gdb_stub_handle_exception
c_func
(paren
(paren
r_struct
id|gdb_pt_regs
op_star
)paren
id|regs
comma
id|signal
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|DO_ERROR
c_func
(paren
id|SIGSEGV
comma
l_string|&quot;Unknown program exception&quot;
comma
id|default_trap_handler
)paren
id|DO_ERROR
c_func
(paren
id|SIGILL
comma
l_string|&quot;privileged operation&quot;
comma
id|privileged_op
)paren
id|DO_ERROR
c_func
(paren
id|SIGILL
comma
l_string|&quot;execute exception&quot;
comma
id|execute_exception
)paren
id|DO_ERROR
c_func
(paren
id|SIGSEGV
comma
l_string|&quot;addressing exception&quot;
comma
id|addressing_exception
)paren
id|DO_ERROR
c_func
(paren
id|SIGFPE
comma
l_string|&quot;fixpoint divide exception&quot;
comma
id|divide_exception
)paren
id|DO_ERROR
c_func
(paren
id|SIGILL
comma
l_string|&quot;translation exception&quot;
comma
id|translation_exception
)paren
id|DO_ERROR
c_func
(paren
id|SIGILL
comma
l_string|&quot;special operand exception&quot;
comma
id|special_op_exception
)paren
id|DO_ERROR
c_func
(paren
id|SIGILL
comma
l_string|&quot;operand exception&quot;
comma
id|operand_exception
)paren
DECL|function|illegal_op
id|asmlinkage
r_void
id|illegal_op
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|interruption_code
)paren
(brace
id|__u8
id|opcode
(braket
l_int|6
)braket
suffix:semicolon
id|__u16
op_star
id|location
suffix:semicolon
r_int
id|signal
op_assign
l_int|0
suffix:semicolon
r_int
id|problem_state
op_assign
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
suffix:semicolon
id|location
op_assign
(paren
id|__u16
op_star
)paren
(paren
id|regs-&gt;psw.addr
op_minus
id|S390_lowcore.pgm_ilc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|problem_state
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
comma
id|location
)paren
suffix:semicolon
)brace
r_else
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_assign
op_star
(paren
(paren
id|__u16
op_star
)paren
id|location
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_eq
id|S390_BREAKPOINT_U16
)paren
(brace
r_if
c_cond
(paren
id|do_debugger_trap
c_func
(paren
id|regs
comma
id|SIGTRAP
)paren
)paren
(brace
id|signal
op_assign
id|SIGILL
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_MATHEMU
r_else
r_if
c_cond
(paren
id|problem_state
)paren
(brace
r_if
c_cond
(paren
id|opcode
(braket
l_int|0
)braket
op_eq
l_int|0xb3
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_b3
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|opcode
(braket
l_int|0
)braket
op_eq
l_int|0xed
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u32
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
(paren
id|__u32
op_star
)paren
(paren
id|location
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_ed
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_eq
l_int|0xb299
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_srnm
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_eq
l_int|0xb29c
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_stfpc
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_eq
l_int|0xb29d
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_lfpc
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
id|signal
op_assign
id|SIGILL
suffix:semicolon
)brace
macro_line|#endif 
r_else
id|signal
op_assign
id|SIGILL
suffix:semicolon
r_if
c_cond
(paren
id|signal
op_eq
id|SIGFPE
)paren
(brace
id|current-&gt;thread.ieee_instruction_pointer
op_assign
(paren
id|addr_t
)paren
id|location
suffix:semicolon
id|do_trap
c_func
(paren
id|interruption_code
comma
id|signal
comma
l_string|&quot;floating point exception&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|signal
)paren
id|do_trap
c_func
(paren
id|interruption_code
comma
id|signal
comma
l_string|&quot;illegal operation&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MATHEMU
id|asmlinkage
r_void
DECL|function|specification_exception
id|specification_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|interruption_code
)paren
(brace
id|__u8
id|opcode
(braket
l_int|6
)braket
suffix:semicolon
id|__u16
op_star
id|location
op_assign
l_int|NULL
suffix:semicolon
r_int
id|signal
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
(brace
id|location
op_assign
(paren
id|__u16
op_star
)paren
(paren
id|regs-&gt;psw.addr
op_minus
id|S390_lowcore.pgm_ilc
)paren
suffix:semicolon
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
comma
id|location
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0x28
suffix:colon
multiline_comment|/* LDR Rx,Ry   */
id|signal
op_assign
id|math_emu_ldr
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x38
suffix:colon
multiline_comment|/* LER Rx,Ry   */
id|signal
op_assign
id|math_emu_ler
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x60
suffix:colon
multiline_comment|/* STD R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_std
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x68
suffix:colon
multiline_comment|/* LD R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_ld
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x70
suffix:colon
multiline_comment|/* STE R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_ste
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x78
suffix:colon
multiline_comment|/* LE R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_le
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|signal
op_assign
id|SIGILL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|signal
op_assign
id|SIGILL
suffix:semicolon
r_if
c_cond
(paren
id|signal
op_eq
id|SIGFPE
)paren
(brace
id|current-&gt;thread.ieee_instruction_pointer
op_assign
(paren
id|addr_t
)paren
id|location
suffix:semicolon
id|do_trap
c_func
(paren
id|interruption_code
comma
id|signal
comma
l_string|&quot;floating point exception&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|signal
)paren
id|do_trap
c_func
(paren
id|interruption_code
comma
id|signal
comma
l_string|&quot;specification exception&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#else
id|DO_ERROR
c_func
(paren
id|SIGILL
comma
l_string|&quot;specification exception&quot;
comma
id|specification_exception
)paren
macro_line|#endif
DECL|function|data_exception
id|asmlinkage
r_void
id|data_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|interruption_code
)paren
(brace
id|__u8
id|opcode
(braket
l_int|6
)braket
suffix:semicolon
id|__u16
op_star
id|location
suffix:semicolon
r_int
id|signal
op_assign
l_int|0
suffix:semicolon
id|location
op_assign
(paren
id|__u16
op_star
)paren
(paren
id|regs-&gt;psw.addr
op_minus
id|S390_lowcore.pgm_ilc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MACHINE_HAS_IEEE
)paren
id|__asm__
r_volatile
(paren
l_string|&quot;stfpc %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|current-&gt;thread.fp_regs.fpc
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MATHEMU
r_else
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
comma
id|location
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0x28
suffix:colon
multiline_comment|/* LDR Rx,Ry   */
id|signal
op_assign
id|math_emu_ldr
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x38
suffix:colon
multiline_comment|/* LER Rx,Ry   */
id|signal
op_assign
id|math_emu_ler
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x60
suffix:colon
multiline_comment|/* STD R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_std
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x68
suffix:colon
multiline_comment|/* LD R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_ld
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x70
suffix:colon
multiline_comment|/* STE R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_ste
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x78
suffix:colon
multiline_comment|/* LE R,D(X,B) */
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_le
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xb3
suffix:colon
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_b3
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xed
suffix:colon
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u32
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
(paren
id|__u32
op_star
)paren
(paren
id|location
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_ed
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xb2
suffix:colon
r_if
c_cond
(paren
id|opcode
(braket
l_int|1
)braket
op_eq
l_int|0x99
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_srnm
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|opcode
(braket
l_int|1
)braket
op_eq
l_int|0x9c
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_stfpc
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|opcode
(braket
l_int|1
)braket
op_eq
l_int|0x9d
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|opcode
op_plus
l_int|2
)paren
)paren
comma
id|location
op_plus
l_int|1
)paren
suffix:semicolon
id|signal
op_assign
id|math_emu_lfpc
c_func
(paren
id|opcode
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
id|signal
op_assign
id|SIGILL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|signal
op_assign
id|SIGILL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif 
r_if
c_cond
(paren
id|current-&gt;thread.fp_regs.fpc
op_amp
id|FPC_DXC_MASK
)paren
id|signal
op_assign
id|SIGFPE
suffix:semicolon
r_else
id|signal
op_assign
id|SIGILL
suffix:semicolon
r_if
c_cond
(paren
id|signal
op_eq
id|SIGFPE
)paren
(brace
id|current-&gt;thread.ieee_instruction_pointer
op_assign
(paren
id|addr_t
)paren
id|location
suffix:semicolon
id|do_trap
c_func
(paren
id|interruption_code
comma
id|signal
comma
l_string|&quot;floating point exception&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|signal
)paren
id|do_trap
c_func
(paren
id|interruption_code
comma
id|signal
comma
l_string|&quot;data exception&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* init is done in lowcore.S and head.S */
DECL|function|trap_init
r_void
id|__init
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|pgm_check_table
(braket
id|i
)braket
op_assign
op_amp
id|default_trap_handler
suffix:semicolon
id|pgm_check_table
(braket
l_int|1
)braket
op_assign
op_amp
id|illegal_op
suffix:semicolon
id|pgm_check_table
(braket
l_int|2
)braket
op_assign
op_amp
id|privileged_op
suffix:semicolon
id|pgm_check_table
(braket
l_int|3
)braket
op_assign
op_amp
id|execute_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|4
)braket
op_assign
op_amp
id|do_page_fault
suffix:semicolon
id|pgm_check_table
(braket
l_int|5
)braket
op_assign
op_amp
id|addressing_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|6
)braket
op_assign
op_amp
id|specification_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|7
)braket
op_assign
op_amp
id|data_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|9
)braket
op_assign
op_amp
id|divide_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x10
)braket
op_assign
op_amp
id|do_page_fault
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x11
)braket
op_assign
op_amp
id|do_page_fault
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x12
)braket
op_assign
op_amp
id|translation_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x13
)braket
op_assign
op_amp
id|special_op_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x14
)braket
op_assign
op_amp
id|do_pseudo_page_fault
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x15
)braket
op_assign
op_amp
id|operand_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x1C
)braket
op_assign
op_amp
id|privileged_op
suffix:semicolon
macro_line|#ifdef CONFIG_PFAULT
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
(brace
multiline_comment|/* request the 0x2603 external interrupt */
r_if
c_cond
(paren
id|register_external_interrupt
c_func
(paren
l_int|0x2603
comma
id|pfault_interrupt
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t request external interrupt 0x2603&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * First try to get pfault pseudo page faults going.&n;&t;&t; * If this isn&squot;t available turn on pagex page faults.&n;&t;&t; */
r_if
c_cond
(paren
id|pfault_init
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Tough luck, no pfault. */
id|unregister_external_interrupt
c_func
(paren
l_int|0x2603
comma
id|pfault_interrupt
)paren
suffix:semicolon
id|cpcmd
c_func
(paren
l_string|&quot;SET PAGEX ON&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
id|cpcmd
c_func
(paren
l_string|&quot;SET PAGEX ON&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|handle_per_exception
r_void
id|handle_per_exception
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
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
(brace
id|per_struct
op_star
id|per_info
op_assign
op_amp
id|current-&gt;thread.per_info
suffix:semicolon
id|per_info-&gt;lowcore.words.perc_atmid
op_assign
id|S390_lowcore.per_perc_atmid
suffix:semicolon
id|per_info-&gt;lowcore.words.address
op_assign
id|S390_lowcore.per_address
suffix:semicolon
id|per_info-&gt;lowcore.words.access_id
op_assign
id|S390_lowcore.per_access_id
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_debugger_trap
c_func
(paren
id|regs
comma
id|SIGTRAP
)paren
)paren
(brace
multiline_comment|/* I&squot;ve seen this possibly a task structure being reused ? */
id|printk
c_func
(paren
l_string|&quot;Spurious per exception detected&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;switching off per tracing for this task.&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* Hopefully switching off per tracing will help us survive */
id|regs-&gt;psw.mask
op_and_assign
op_complement
id|PSW_PER_MASK
suffix:semicolon
)brace
)brace
eof
