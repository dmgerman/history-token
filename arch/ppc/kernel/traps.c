multiline_comment|/*&n; *  arch/ppc/kernel/traps.c&n; *&n; *  Copyright (C) 1995-1996  Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  and Paul Mackerras (paulus@cs.anu.edu.au)&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of hardware exceptions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
macro_line|#ifdef CONFIG_PMAC_BACKLIGHT
macro_line|#include &lt;asm/backlight.h&gt;
macro_line|#endif
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
id|sig
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
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
op_assign
id|xmon
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
op_assign
id|xmon_bpt
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
op_assign
id|xmon_sstep
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
op_assign
id|xmon_iabr_match
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
op_assign
id|xmon_dabr_match
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
macro_line|#else
macro_line|#ifdef CONFIG_KGDB
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
macro_line|#else
DECL|macro|debugger
mdefine_line|#define debugger(regs)&t;&t;&t;do { } while (0)
DECL|macro|debugger_bpt
mdefine_line|#define debugger_bpt(regs)&t;&t;0
DECL|macro|debugger_sstep
mdefine_line|#define debugger_sstep(regs)&t;&t;0
DECL|macro|debugger_iabr_match
mdefine_line|#define debugger_iabr_match(regs)&t;0
DECL|macro|debugger_dabr_match
mdefine_line|#define debugger_dabr_match(regs)&t;0
DECL|macro|debugger_fault_handler
mdefine_line|#define debugger_fault_handler&t;&t;((void (*)(struct pt_regs *))0)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Trap &amp; Exception support&n; */
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
id|fp
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
macro_line|#ifdef CONFIG_PMAC_BACKLIGHT
id|set_backlight_enable
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|set_backlight_level
c_func
(paren
id|BACKLIGHT_MAX
)paren
suffix:semicolon
macro_line|#endif
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
id|fp
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
multiline_comment|/* do_exit() should take care of panic&squot;ing from an interrupt&n;&t; * context so we don&squot;t handle it here&n;&t; */
id|do_exit
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
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
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Exception in kernel mode&quot;
comma
id|regs
comma
id|signr
)paren
suffix:semicolon
)brace
id|force_sig
c_func
(paren
id|signr
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O accesses can cause machine checks on powermacs.&n; * Check if the NIP corresponds to the address of a sync&n; * instruction for which there is an entry in the exception&n; * table.&n; * Note that the 601 only takes a machine check on TEA&n; * (transfer error ack) signal assertion, and does not&n; * set any of the top 16 bits of SRR1.&n; *  -- paulus.&n; */
DECL|function|check_io_access
r_static
r_inline
r_int
id|check_io_access
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef CONFIG_PPC_PMAC
r_int
r_int
id|msr
op_assign
id|regs-&gt;msr
suffix:semicolon
r_const
r_struct
id|exception_table_entry
op_star
id|entry
suffix:semicolon
r_int
r_int
op_star
id|nip
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|msr
op_amp
l_int|0xffff0000
)paren
op_eq
l_int|0
op_logical_or
(paren
id|msr
op_amp
(paren
l_int|0x80000
op_or
l_int|0x40000
)paren
)paren
)paren
op_logical_and
(paren
id|entry
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;nip
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check that it&squot;s a sync instruction, or somewhere&n;&t;&t; * in the twi; isync; nop sequence that inb/inw/inl uses.&n;&t;&t; * As the address is in the exception table&n;&t;&t; * we should be able to read the instr there.&n;&t;&t; * For the debug message, we look at the preceding&n;&t;&t; * load or store.&n;&t;&t; */
r_if
c_cond
(paren
op_star
id|nip
op_eq
l_int|0x60000000
)paren
multiline_comment|/* nop */
id|nip
op_sub_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|nip
op_eq
l_int|0x4c00012c
)paren
multiline_comment|/* isync */
op_decrement
id|nip
suffix:semicolon
r_if
c_cond
(paren
op_star
id|nip
op_eq
l_int|0x7c0004ac
op_logical_or
(paren
op_star
id|nip
op_rshift
l_int|26
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/* sync or twi */
r_int
r_int
id|rb
suffix:semicolon
op_decrement
id|nip
suffix:semicolon
id|rb
op_assign
(paren
op_star
id|nip
op_rshift
l_int|11
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s bad port %lx at %p&bslash;n&quot;
comma
(paren
op_star
id|nip
op_amp
l_int|0x100
)paren
ques
c_cond
l_string|&quot;OUT to&quot;
suffix:colon
l_string|&quot;IN from&quot;
comma
id|regs-&gt;gpr
(braket
id|rb
)braket
op_minus
id|_IO_BASE
comma
id|nip
)paren
suffix:semicolon
id|regs-&gt;msr
op_or_assign
id|MSR_RI
suffix:semicolon
id|regs-&gt;nip
op_assign
id|entry-&gt;fixup
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
r_return
l_int|0
suffix:semicolon
)brace
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
id|regs-&gt;msr
op_or_assign
id|MSR_RI
suffix:semicolon
id|_exception
c_func
(paren
id|SIGSEGV
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_8xx) &amp;&amp; defined(CONFIG_PCI)
multiline_comment|/* the qspan pci read routines can cause machine checks -- Cort */
id|bad_page_fault
c_func
(paren
id|regs
comma
id|regs-&gt;dar
comma
id|SIGBUS
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif
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
id|regs-&gt;msr
op_or_assign
id|MSR_RI
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_io_access
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#ifndef CONFIG_4xx
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Machine check in kernel mode.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Caused by (from SRR1=%lx): &quot;
comma
id|regs-&gt;msr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|regs-&gt;msr
op_amp
l_int|0x601F0000
)paren
(brace
r_case
l_int|0x80000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Machine check signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* for 601 */
r_case
l_int|0x40000
suffix:colon
r_case
l_int|0x140000
suffix:colon
multiline_comment|/* 7450 MSS error and TEA */
id|printk
c_func
(paren
l_string|&quot;Transfer error ack signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Data parity error signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Address parity error signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20000000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;L1 Data Cache error&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40000000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;L1 Instruction Cache error&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00100000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;L2 data cache parity error&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown values in msr&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_4xx */
multiline_comment|/* Note that the ESR gets stored in regs-&gt;dsisr on 4xx. */
r_if
c_cond
(paren
id|regs-&gt;dsisr
op_amp
id|ESR_MCI
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Instruction&quot;
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_ESR
comma
id|regs-&gt;dsisr
op_amp
op_complement
id|ESR_MCI
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Data&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; machine check in kernel mode.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_4xx */
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;machine check&quot;
comma
id|regs
comma
id|SIGBUS
)paren
suffix:semicolon
)brace
r_void
DECL|function|SMIException
id|SMIException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#if !(defined(CONFIG_XMON) || defined(CONFIG_KGDB))
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;System Management Interrupt&quot;
)paren
suffix:semicolon
macro_line|#endif
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
l_string|&quot;Bad trap at PC: %lx, MSR: %lx, vector=%lx    %s&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
comma
id|regs-&gt;trap
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|InstructionBreakpoint
id|InstructionBreakpoint
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
)paren
suffix:semicolon
)brace
r_void
DECL|function|RunModeException
id|RunModeException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/* Illegal instruction emulation support.  Originally written to&n; * provide the PVR to user applications using the mfspr rd, PVR.&n; * Return non-zero if we can&squot;t emulate, or EFAULT if the associated&n; * memory access caused an access fault.  Return zero on success.&n; *&n; * There are a couple of ways to do this, either &quot;decode&quot; the instruction&n; * or directly match lots of bits.  In this case, matching lots of&n; * bits is faster and easier.&n; *&n; */
DECL|macro|INST_MFSPR_PVR
mdefine_line|#define INST_MFSPR_PVR&t;&t;0x7c1f42a6
DECL|macro|INST_MFSPR_PVR_MASK
mdefine_line|#define INST_MFSPR_PVR_MASK&t;0xfc1fffff
r_static
r_int
DECL|function|emulate_instruction
id|emulate_instruction
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|uint
id|instword
suffix:semicolon
id|uint
id|rd
suffix:semicolon
id|uint
id|retval
suffix:semicolon
id|retval
op_assign
id|EINVAL
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
id|retval
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
id|uint
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
multiline_comment|/* Emulate the mfspr rD, PVR.&n;&t; */
r_if
c_cond
(paren
(paren
id|instword
op_amp
id|INST_MFSPR_PVR_MASK
)paren
op_eq
id|INST_MFSPR_PVR
)paren
(brace
id|rd
op_assign
(paren
id|instword
op_rshift
l_int|21
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|regs-&gt;gpr
(braket
id|rd
)braket
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
r_return
id|retval
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
id|bug-&gt;line
op_amp
op_complement
id|BUG_WARNING_TRAP
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
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
r_int
id|errcode
suffix:semicolon
macro_line|#if defined(CONFIG_4xx)
r_int
r_int
id|esr
op_assign
id|regs-&gt;dsisr
suffix:semicolon
r_int
id|isbpt
op_assign
id|esr
op_amp
id|ESR_PTR
suffix:semicolon
r_extern
r_int
id|do_mathemu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MATH_EMULATION
r_if
c_cond
(paren
op_logical_neg
id|isbpt
op_logical_and
id|do_mathemu
c_func
(paren
id|regs
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#endif /* CONFIG_MATH_EMULATION */
macro_line|#else /* ! CONFIG_4xx */
r_int
id|isbpt
op_assign
id|regs-&gt;msr
op_amp
l_int|0x20000
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
id|_exception
c_func
(paren
id|SIGFPE
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* ! CONFIG_4xx */
r_if
c_cond
(paren
id|isbpt
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
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Try to emulate it if we should. */
r_if
c_cond
(paren
(paren
id|errcode
op_assign
id|emulate_instruction
c_func
(paren
id|regs
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|errcode
op_eq
op_minus
id|EFAULT
)paren
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
)paren
suffix:semicolon
r_else
id|_exception
c_func
(paren
id|SIGILL
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
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fixed
op_eq
op_minus
id|EFAULT
)paren
(brace
multiline_comment|/* fixed == -EFAULT means the operand address was bad */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_else
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
r_return
suffix:semicolon
)brace
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|StackOverflow
id|StackOverflow
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
id|KERN_CRIT
l_string|&quot;Kernel stack overflow in process %p, r1=%lx&bslash;n&quot;
comma
id|current
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;kernel stack overflow&quot;
)paren
suffix:semicolon
)brace
DECL|function|nonrecoverable_exception
r_void
id|nonrecoverable_exception
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
id|KERN_ERR
l_string|&quot;Non-recoverable exception at PC=%lx MSR=%lx&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
)paren
suffix:semicolon
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;nonrecoverable exception&quot;
comma
id|regs
comma
id|SIGKILL
)paren
suffix:semicolon
)brace
r_void
DECL|function|trace_syscall
id|trace_syscall
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
l_string|&quot;Task: %p(%d), PC: %08lX/%08lX, Syscall: %3ld, Result: %s%ld    %s&bslash;n&quot;
comma
id|current
comma
id|current-&gt;pid
comma
id|regs-&gt;nip
comma
id|regs-&gt;link
comma
id|regs-&gt;gpr
(braket
l_int|0
)braket
comma
id|regs-&gt;ccr
op_amp
l_int|0x10000000
ques
c_cond
l_string|&quot;Error=&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|regs-&gt;gpr
(braket
l_int|3
)braket
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_8xx
r_void
DECL|function|SoftwareEmulation
id|SoftwareEmulation
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_extern
r_int
id|do_mathemu
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|Soft_emulate_8xx
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_int
id|errcode
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
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Kernel Mode Software FPU Emulation&quot;
comma
id|regs
comma
id|SIGFPE
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MATH_EMULATION
id|errcode
op_assign
id|do_mathemu
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#else
id|errcode
op_assign
id|Soft_emulate_8xx
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|errcode
)paren
(brace
r_if
c_cond
(paren
id|errcode
OG
l_int|0
)paren
id|_exception
c_func
(paren
id|SIGFPE
comma
id|regs
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|errcode
op_eq
op_minus
id|EFAULT
)paren
id|_exception
c_func
(paren
id|SIGSEGV
comma
id|regs
)paren
suffix:semicolon
r_else
id|_exception
c_func
(paren
id|SIGILL
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_8xx */
macro_line|#if defined(CONFIG_4xx)
DECL|function|DebugException
r_void
id|DebugException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|debug_status
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|debug_status
op_amp
id|DBSR_TIE
)paren
(brace
multiline_comment|/* trap instruction*/
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
id|debugger_bpt
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
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|debug_status
op_amp
id|DBSR_IC
)paren
(brace
multiline_comment|/* instruction completion */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
id|debugger_sstep
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|current-&gt;thread.dbcr0
op_and_assign
op_complement
id|DBCR0_IC
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_4xx */
macro_line|#if !defined(CONFIG_TAU_INT)
r_void
DECL|function|TAUException
id|TAUException
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
l_string|&quot;TAU trap at PC: %lx, MSR: %lx, vector=%lx    %s&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
comma
id|regs-&gt;trap
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_INT_TAU */
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
