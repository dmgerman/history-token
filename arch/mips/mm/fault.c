multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 - 2000 by Ralf Baechle&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;&t;&t;/* For unblank_screen() */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; */
DECL|function|do_page_fault
id|asmlinkage
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
id|write
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_const
r_int
id|field
op_assign
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|2
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Cpu%d[%s:%d:%0*lx:%ld:%0*lx]&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|field
comma
id|address
comma
id|write
comma
id|field
comma
id|regs-&gt;cp0_epc
)paren
suffix:semicolon
macro_line|#endif
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
multiline_comment|/*&n;&t; * We fault-in kernel-space virtual memory on-demand. The&n;&t; * &squot;reference&squot; page table is init_mm.pgd.&n;&t; *&n;&t; * NOTE! We MUST NOT take any locks for this case. We may&n;&t; * be in an interrupt or a critical region, and should&n;&t; * only copy the information from the master page table,&n;&t; * nothing more.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|address
op_ge
id|VMALLOC_START
)paren
)paren
r_goto
id|vmalloc_fault
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or have no user&n;&t; * context, we must not take the fault..&n;&t; */
r_if
c_cond
(paren
id|in_atomic
c_func
(paren
)paren
op_logical_or
op_logical_neg
id|mm
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
r_goto
id|good_area
suffix:semicolon
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
multiline_comment|/*&n; * Ok, we have a good vm_area for this memory access, so&n; * we can handle it..&n; */
id|good_area
suffix:colon
id|info.si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
r_if
c_cond
(paren
id|write
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
)brace
r_else
(brace
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
id|write
)paren
)paren
(brace
r_case
id|VM_FAULT_MINOR
suffix:colon
id|tsk-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VM_FAULT_MAJOR
suffix:colon
id|tsk-&gt;maj_flt
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
multiline_comment|/*&n; * Something tried to access memory that isn&squot;t in our memory map..&n; * Fix it, but check if it&squot;s kernel or user first..&n; */
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
multiline_comment|/* User mode accesses just cause a SIGSEGV */
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
id|tsk-&gt;thread.cp0_badvaddr
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|write
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;do_page_fault() #2: sending SIGSEGV to %s for &quot;
l_string|&quot;invalid %s&bslash;n%0*lx (epc == %0*lx, ra == %0*lx)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|write
ques
c_cond
l_string|&quot;write access to&quot;
suffix:colon
l_string|&quot;read access from&quot;
comma
id|field
comma
id|address
comma
id|field
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_epc
comma
id|field
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* info.si_code has been set above */
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
id|SIGSEGV
comma
op_amp
id|info
comma
id|tsk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|no_context
suffix:colon
multiline_comment|/* Are we prepared to handle this kernel fault?  */
r_if
c_cond
(paren
id|fixup_exception
c_func
(paren
id|regs
)paren
)paren
(brace
id|current-&gt;thread.cp0_baduaddr
op_assign
id|address
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n;&t; * terminate things with extreme prejudice.&n;&t; */
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;CPU %d Unable to handle kernel paging request at &quot;
l_string|&quot;virtual address %0*lx, epc == %0*lx, ra == %0*lx&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|field
comma
id|address
comma
id|field
comma
id|regs-&gt;cp0_epc
comma
id|field
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
)paren
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
id|tsk-&gt;pid
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
id|tsk-&gt;comm
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
r_goto
id|no_context
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
multiline_comment|/* Kernel mode? Handle exceptions or die */
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
r_goto
id|no_context
suffix:semicolon
multiline_comment|/*&n;&t; * Send a sigbus, regardless of whether we were in kernel&n;&t; * or user mode.&n;&t; */
id|tsk-&gt;thread.cp0_badvaddr
op_assign
id|address
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
id|tsk
)paren
suffix:semicolon
r_return
suffix:semicolon
id|vmalloc_fault
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * Synchronize this task&squot;s top level page-table&n;&t;&t; * with the &squot;reference&squot; page table.&n;&t;&t; *&n;&t;&t; * Do _not_ use &quot;tsk&quot; here. We might be inside&n;&t;&t; * an interrupt in the middle of a task switch..&n;&t;&t; */
r_int
id|offset
op_assign
id|__pgd_offset
c_func
(paren
id|address
)paren
suffix:semicolon
id|pgd_t
op_star
id|pgd
comma
op_star
id|pgd_k
suffix:semicolon
id|pmd_t
op_star
id|pmd
comma
op_star
id|pmd_k
suffix:semicolon
id|pte_t
op_star
id|pte_k
suffix:semicolon
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|pgd_current
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_plus
id|offset
suffix:semicolon
id|pgd_k
op_assign
id|init_mm.pgd
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_present
c_func
(paren
op_star
id|pgd_k
)paren
)paren
r_goto
id|no_context
suffix:semicolon
id|set_pgd
c_func
(paren
id|pgd
comma
op_star
id|pgd_k
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
id|pmd_k
op_assign
id|pmd_offset
c_func
(paren
id|pgd_k
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd_k
)paren
)paren
r_goto
id|no_context
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
op_star
id|pmd_k
)paren
suffix:semicolon
id|pte_k
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd_k
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte_k
)paren
)paren
r_goto
id|no_context
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
