multiline_comment|/*&n; *  arch/ppc/mm/fault.c&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/i386/mm/fault.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Modified by Cort Dougan and Paul Mackerras.&n; *&n; *  Modified for PPC64 by Dave Engebretsen (engebret@ibm.com)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#ifdef CONFIG_DEBUG_KERNEL
DECL|variable|debugger_kernel_faults
r_int
id|debugger_kernel_faults
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
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
multiline_comment|/*&n; * For 600- and 800-family processors, the error_code parameter is DSISR&n; * for a data fault, SRR1 for an instruction fault.&n; */
DECL|function|do_page_fault
r_void
id|do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|address
comma
r_int
r_int
id|error_code
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
r_int
id|code
op_assign
id|SEGV_MAPERR
suffix:semicolon
r_int
r_int
id|is_write
op_assign
id|error_code
op_amp
l_int|0x02000000
suffix:semicolon
multiline_comment|/*&n;&t; * Fortunately the bit assignments in SRR1 for an instruction&n;&t; * fault and DSISR for a data fault are mostly the same for the&n;&t; * bits we are interested in.  But there are some bits which&n;&t; * indicate errors in DSISR but can validly be set in SRR1.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
l_int|0x400
)paren
id|error_code
op_and_assign
l_int|0x48200000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regs-&gt;trap
op_ne
l_int|0x300
)paren
multiline_comment|/* ensure error_code is 0 on SLB miss */
id|error_code
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger_fault_handler
op_logical_and
(paren
id|regs-&gt;trap
op_eq
l_int|0x300
op_logical_or
id|regs-&gt;trap
op_eq
l_int|0x380
)paren
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
macro_line|#endif
multiline_comment|/* On a kernel SLB miss we can only check for a valid exception entry */
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
(paren
id|regs-&gt;trap
op_eq
l_int|0x380
)paren
)paren
(brace
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGSEGV
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x00400000
)paren
(brace
multiline_comment|/* DABR match */
r_if
c_cond
(paren
id|debugger_dabr_match
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|in_atomic
c_func
(paren
)paren
op_logical_or
id|mm
op_eq
l_int|NULL
)paren
(brace
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGSEGV
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
op_le
id|address
)paren
(brace
r_goto
id|good_area
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|expand_stack
c_func
(paren
id|vma
comma
id|address
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
id|good_area
suffix:colon
id|code
op_assign
id|SEGV_ACCERR
suffix:semicolon
multiline_comment|/* a write */
r_if
c_cond
(paren
id|is_write
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/* a read */
)brace
r_else
(brace
multiline_comment|/* protection fault */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x08000000
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_READ
op_or
id|VM_EXEC
)paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
id|survive
suffix:colon
multiline_comment|/*&n;&t; * If for any reason at all we couldn&squot;t handle the fault,&n;&t; * make sure we exit gracefully rather than endlessly redo&n;&t; * the fault.&n;&t; */
r_switch
c_cond
(paren
id|handle_mm_fault
c_func
(paren
id|mm
comma
id|vma
comma
id|address
comma
id|is_write
)paren
)paren
(brace
r_case
id|VM_FAULT_MINOR
suffix:colon
id|current-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VM_FAULT_MAJOR
suffix:colon
id|current-&gt;maj_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VM_FAULT_SIGBUS
suffix:colon
r_goto
id|do_sigbus
suffix:semicolon
r_case
id|VM_FAULT_OOM
suffix:colon
r_goto
id|out_of_memory
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bad_area
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* User mode accesses cause a SIGSEGV */
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
id|code
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|ifppcdebug
c_func
(paren
id|PPCDBG_SIGNALXMON
)paren
id|PPCDBG_ENTER_DEBUGGER_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
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
r_return
suffix:semicolon
)brace
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGSEGV
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/*&n; * We ran out of memory, or some other thing happened to us that made&n; * us unable to handle the page fault gracefully.&n; */
id|out_of_memory
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
l_int|1
)paren
(brace
id|yield
c_func
(paren
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_goto
id|survive
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;VM: killing process %s&bslash;n&quot;
comma
id|current-&gt;comm
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
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGKILL
)paren
suffix:semicolon
r_return
suffix:semicolon
id|do_sigbus
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
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
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|current
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
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGBUS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * bad_page_fault is called when we have a bad access from the kernel.&n; * It is called from do_page_fault above and from some of the procedures&n; * in traps.c.&n; */
r_void
DECL|function|bad_page_fault
id|bad_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|address
comma
r_int
id|sig
)paren
(brace
r_extern
r_void
id|die
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_const
r_struct
id|exception_table_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* Are we prepared to handle this fault?  */
r_if
c_cond
(paren
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
id|regs-&gt;nip
op_assign
id|entry-&gt;fixup
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* kernel has accessed a bad area */
macro_line|#ifdef CONFIG_DEBUG_KERNEL
r_if
c_cond
(paren
id|debugger_kernel_faults
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
l_string|&quot;Kernel access of bad area&quot;
comma
id|regs
comma
id|sig
)paren
suffix:semicolon
)brace
eof
