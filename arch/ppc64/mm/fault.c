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
multiline_comment|/*&n; * Check whether the instruction at regs-&gt;nip is a store using&n; * an update addressing form which will update r1.&n; */
DECL|function|store_updates_sp
r_static
r_int
id|store_updates_sp
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
id|inst
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|inst
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|regs-&gt;nip
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check for 1 in the rA field */
r_if
c_cond
(paren
(paren
(paren
id|inst
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
op_ne
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check major opcode */
r_switch
c_cond
(paren
id|inst
op_rshift
l_int|26
)paren
(brace
r_case
l_int|37
suffix:colon
multiline_comment|/* stwu */
r_case
l_int|39
suffix:colon
multiline_comment|/* stbu */
r_case
l_int|45
suffix:colon
multiline_comment|/* sthu */
r_case
l_int|53
suffix:colon
multiline_comment|/* stfsu */
r_case
l_int|55
suffix:colon
multiline_comment|/* stfdu */
r_return
l_int|1
suffix:semicolon
r_case
l_int|62
suffix:colon
multiline_comment|/* std or stdu */
r_return
(paren
id|inst
op_amp
l_int|3
)paren
op_eq
l_int|1
suffix:semicolon
r_case
l_int|31
suffix:colon
multiline_comment|/* check minor opcode */
r_switch
c_cond
(paren
(paren
id|inst
op_rshift
l_int|1
)paren
op_amp
l_int|0x3ff
)paren
(brace
r_case
l_int|181
suffix:colon
multiline_comment|/* stdux */
r_case
l_int|183
suffix:colon
multiline_comment|/* stwux */
r_case
l_int|247
suffix:colon
multiline_comment|/* stbux */
r_case
l_int|439
suffix:colon
multiline_comment|/* sthux */
r_case
l_int|695
suffix:colon
multiline_comment|/* stfsux */
r_case
l_int|759
suffix:colon
multiline_comment|/* stfdux */
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The error_code parameter is&n; *  - DSISR for a non-SLB data access fault,&n; *  - SRR1 &amp; 0x08000000 for a non-SLB instruction access fault&n; *  - 0 any SLB fault.&n; * The return value is 0 if the fault was handled, or the signal&n; * number if this is a kernel fault that can&squot;t be handled here.&n; */
DECL|function|do_page_fault
r_int
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
r_int
r_int
id|trap
op_assign
id|TRAP
c_func
(paren
id|regs
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|trap
op_eq
l_int|0x380
)paren
op_logical_or
(paren
id|trap
op_eq
l_int|0x480
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trap
op_eq
l_int|0x300
)paren
(brace
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
l_int|0
suffix:semicolon
)brace
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
id|address
op_ge
id|TASK_SIZE
)paren
)paren
r_return
id|SIGSEGV
suffix:semicolon
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x00400000
)paren
(brace
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
l_int|0
suffix:semicolon
)brace
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
id|SIGSEGV
suffix:semicolon
multiline_comment|/* in_atomic() in user mode is really bad,&n;&t;&t;   as is current-&gt;mm == NULL. */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Page fault in user mode with&quot;
l_string|&quot;in_atomic() = %d mm = %p&bslash;n&quot;
comma
id|in_atomic
c_func
(paren
)paren
comma
id|mm
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;NIP = %lx  MSR = %lx&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Weird page fault&quot;
comma
id|regs
comma
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/* When running in the kernel we expect faults to occur only to&n;&t; * addresses in user space.  All other faults represent errors in the&n;&t; * kernel and should generate an OOPS.  Unfortunatly, in the case of an&n;&t; * erroneous fault occuring in a code path which already holds mmap_sem&n;&t; * we will deadlock attempting to validate the fault against the&n;&t; * address space.  Luckily the kernel only validly references user&n;&t; * space from well defined areas of code, which are listed in the&n;&t; * exceptions table.&n;&t; *&n;&t; * As the vast majority of faults will be valid we will only perform&n;&t; * the source reference check when there is a possibilty of a deadlock.&n;&t; * Attempt to lock the address space, if we cannot we then validate the&n;&t; * source.  If this is invalid we can skip the address space check,&n;&t; * thus avoiding the deadlock.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|down_read_trylock
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
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
op_logical_and
op_logical_neg
id|search_exception_tables
c_func
(paren
id|regs-&gt;nip
)paren
)paren
r_goto
id|bad_area_nosemaphore
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * N.B. The POWER/Open ABI allows programs to access up to&n;&t; * 288 bytes below the stack pointer.&n;&t; * The kernel signal delivery code writes up to about 1.5kB&n;&t; * below the stack pointer (r1) before decrementing it.&n;&t; * The exec code can write slightly over 640kB to the stack&n;&t; * before setting the user r1.  Thus we allow the stack to&n;&t; * expand to 1MB without further checks.&n;&t; */
r_if
c_cond
(paren
id|address
op_plus
l_int|0x100000
OL
id|vma-&gt;vm_end
)paren
(brace
multiline_comment|/* get user regs even if this fault is in kernel mode */
r_struct
id|pt_regs
op_star
id|uregs
op_assign
id|current-&gt;thread.regs
suffix:semicolon
r_if
c_cond
(paren
id|uregs
op_eq
l_int|NULL
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/*&n;&t;&t; * A user-mode access to an address a long way below&n;&t;&t; * the stack pointer is only valid if the instruction&n;&t;&t; * is one which would update the stack pointer to the&n;&t;&t; * address accessed if the instruction completed,&n;&t;&t; * i.e. either stwu rs,n(r1) or stwux rs,r1,rb&n;&t;&t; * (or the byte, halfword, float or double forms).&n;&t;&t; *&n;&t;&t; * If we don&squot;t check this then any write to the area&n;&t;&t; * between the last mapped region and the stack will&n;&t;&t; * expand the stack rather than segfaulting.&n;&t;&t; */
r_if
c_cond
(paren
id|address
op_plus
l_int|2048
OL
id|uregs-&gt;gpr
(braket
l_int|1
)braket
op_logical_and
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_or
op_logical_neg
id|store_updates_sp
c_func
(paren
id|regs
)paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
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
l_int|0
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
id|bad_area_nosemaphore
suffix:colon
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
id|__user
op_star
)paren
id|address
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
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|SIGSEGV
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
r_return
id|SIGKILL
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
id|__user
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
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|SIGBUS
suffix:semicolon
)brace
multiline_comment|/*&n; * bad_page_fault is called when we have a bad access from the kernel.&n; * It is called from do_page_fault above and from some of the procedures&n; * in traps.c.&n; */
DECL|function|bad_page_fault
r_void
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
