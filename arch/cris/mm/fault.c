multiline_comment|/*&n; *  linux/arch/cris/mm/fault.c&n; *&n; *  Copyright (C) 2000  Axis Communications AB&n; *&n; *  Authors:  Bjorn Wesen &n; * &n; *  $Log: fault.c,v $&n; *  Revision 1.8  2000/11/22 14:45:31  bjornw&n; *  * 2.4.0-test10 removed the set_pgdir instantaneous kernel global mapping&n; *    into all processes. Instead we fill in the missing PTE entries on demand.&n; *&n; *  Revision 1.7  2000/11/21 16:39:09  bjornw&n; *  fixup switches frametype&n; *&n; *  Revision 1.6  2000/11/17 16:54:08  bjornw&n; *  More detailed siginfo reporting&n; *&n; *&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/svinto.h&gt;
r_extern
r_void
id|die_if_kernel
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
id|asmlinkage
r_void
id|do_invalid_op
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|asmlinkage
r_void
id|do_page_fault
c_func
(paren
r_int
r_int
id|address
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
suffix:semicolon
multiline_comment|/* debug of low-level TLB reload */
DECL|macro|D
mdefine_line|#define D(x)
multiline_comment|/* debug of higher-level faults */
DECL|macro|DPG
mdefine_line|#define DPG(x)
multiline_comment|/* fast TLB-fill fault handler */
r_void
DECL|function|handle_mmu_bus_fault
id|handle_mmu_bus_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cause
comma
id|select
suffix:semicolon
r_int
id|index
suffix:semicolon
r_int
id|page_id
suffix:semicolon
r_int
id|miss
comma
id|we
comma
id|acc
comma
id|inv
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;active_mm
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_int
id|errcode
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|cause
op_assign
op_star
id|R_MMU_CAUSE
suffix:semicolon
id|select
op_assign
op_star
id|R_TLB_SELECT
suffix:semicolon
id|address
op_assign
id|cause
op_amp
id|PAGE_MASK
suffix:semicolon
multiline_comment|/* get faulting address */
id|page_id
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_MMU_CAUSE
comma
id|page_id
comma
id|cause
)paren
suffix:semicolon
id|miss
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_MMU_CAUSE
comma
id|miss_excp
comma
id|cause
)paren
suffix:semicolon
id|we
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_MMU_CAUSE
comma
id|we_excp
comma
id|cause
)paren
suffix:semicolon
id|acc
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_MMU_CAUSE
comma
id|acc_excp
comma
id|cause
)paren
suffix:semicolon
id|inv
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_MMU_CAUSE
comma
id|inv_excp
comma
id|cause
)paren
suffix:semicolon
id|index
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_TLB_SELECT
comma
id|index
comma
id|select
)paren
suffix:semicolon
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;bus_fault from IRP 0x%x: addr 0x%x, miss %d, inv %d, we %d, acc %d, &quot;
l_string|&quot;idx %d pid %d&bslash;n&quot;
comma
id|regs-&gt;irp
comma
id|address
comma
id|miss
comma
id|inv
comma
id|we
comma
id|acc
comma
id|index
comma
id|page_id
)paren
)paren
suffix:semicolon
multiline_comment|/* for a miss, we need to reload the TLB entry */
r_if
c_cond
(paren
id|miss
)paren
(brace
multiline_comment|/* see if the pte exists at all */
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd_offset
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
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
r_goto
id|dofault
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad pgdir entry 0x%x at 0x%x&bslash;n&quot;
comma
op_star
id|pmd
comma
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte
op_assign
op_star
id|pte_offset
c_func
(paren
id|pmd
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
id|pte
)paren
)paren
(brace
r_goto
id|dofault
suffix:semicolon
)brace
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; found pte %x pg %x &quot;
comma
id|pte_val
c_func
(paren
id|pte
)paren
comma
id|pte_page
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
id|D
c_func
(paren
(brace
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_SILENT_WRITE
)paren
id|printk
c_func
(paren
l_string|&quot;Silent-W &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_KERNEL
)paren
id|printk
c_func
(paren
l_string|&quot;Kernel &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_SILENT_READ
)paren
id|printk
c_func
(paren
l_string|&quot;Silent-R &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_GLOBAL
)paren
id|printk
c_func
(paren
l_string|&quot;Global &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_PRESENT
)paren
id|printk
c_func
(paren
l_string|&quot;Present &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
)paren
id|printk
c_func
(paren
l_string|&quot;Accessed &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_MODIFIED
)paren
id|printk
c_func
(paren
l_string|&quot;Modified &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
)paren
id|printk
c_func
(paren
l_string|&quot;Readable &quot;
)paren
suffix:semicolon
r_if
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_WRITE
)paren
id|printk
c_func
(paren
l_string|&quot;Writeable &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)paren
suffix:semicolon
multiline_comment|/* load up the chosen TLB entry&n;&t;&t; * this assumes the pte format is the same as the TLB_LO layout.&n;&t;&t; *&n;&t;&t; * the write to R_TLB_LO also writes the vpn and page_id fields from&n;&t;&t; * R_MMU_CAUSE, which we in this case obviously want to keep&n;&t;&t; */
op_star
id|R_TLB_LO
op_assign
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|errcode
op_assign
l_int|0x01
op_or
(paren
id|we
op_lshift
l_int|1
)paren
suffix:semicolon
id|dofault
suffix:colon
multiline_comment|/* leave it to the MM system fault handler below */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;do_page_fault %p errcode %d&bslash;n&quot;
comma
id|address
comma
id|errcode
)paren
)paren
suffix:semicolon
id|do_page_fault
c_func
(paren
id|address
comma
id|regs
comma
id|errcode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; *&n; * Notice that the address we&squot;re given is aligned to the page the fault&n; * occured in, since we only get the PFN in R_MMU_CAUSE not the complete&n; * address.&n; *&n; * error_code:&n; *&t;bit 0 == 0 means no page found, 1 means protection fault&n; *&t;bit 1 == 0 means read, 1 means write&n; *&n; * If this routine detects a bad access, it returns 1, otherwise it&n; * returns 0.&n; */
id|asmlinkage
r_void
DECL|function|do_page_fault
id|do_page_fault
c_func
(paren
r_int
r_int
id|address
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|writeaccess
suffix:semicolon
r_int
id|fault
suffix:semicolon
r_int
r_int
id|fixup
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
multiline_comment|/*&n;         * We fault-in kernel-space virtual memory on-demand. The&n;         * &squot;reference&squot; page table is init_mm.pgd.&n;         *&n;         * NOTE! We MUST NOT take any locks for this case. We may&n;         * be in an interrupt or a critical region, and should&n;         * only copy the information from the master page table,&n;         * nothing more.&n;&t; *&n;&t; * NOTE2: This is done so that, when updating the vmalloc&n;&t; * mappings we don&squot;t have to walk all processes pgdirs and&n;&t; * add the high mappings all at once. Instead we do it as they&n;&t; * are used.&n;&t; *&n;&t; * TODO: On CRIS, we have a PTE Global bit which should be set in&n;&t; * all the PTE&squot;s related to vmalloc in all processes - that means if&n;&t; * we switch process and a vmalloc PTE is still in the TLB, it won&squot;t&n;&t; * need to be reloaded. It&squot;s an optimization.&n;&t; *&n;&t; * Linux/CRIS&squot;s kernel is not page-mapped, so the comparision below&n;&t; * should really be &gt;= VMALLOC_START, however, kernel fixup errors&n;&t; * will be handled more quickly by going through vmalloc_fault and then&n;&t; * into bad_area_nosemaphore than falling through the find_vma user-mode&n;&t; * tests.&n;         */
r_if
c_cond
(paren
id|address
op_ge
id|TASK_SIZE
)paren
r_goto
id|vmalloc_fault
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|writeaccess
op_assign
id|error_code
op_amp
l_int|2
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or have no user&n;&t; * context, we must not take the fault..&n;&t; */
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
op_logical_or
op_logical_neg
id|mm
)paren
r_goto
id|no_context
suffix:semicolon
id|down
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
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * accessing the stack below usp is always a bug.&n;&t;&t; * we get page-aligned addresses so we can only check&n;&t;&t; * if we&squot;re within a page from usp, but that might be&n;&t;&t; * enough to catch brutal errors at least.&n;&t;&t; */
r_if
c_cond
(paren
id|address
op_plus
id|PAGE_SIZE
OL
id|rdusp
c_func
(paren
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
multiline_comment|/*&n;&t; * Ok, we have a good vm_area for this memory access, so&n;&t; * we can handle it..&n;&t; */
id|good_area
suffix:colon
id|info.si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
multiline_comment|/* first do some preliminary protection checks */
r_if
c_cond
(paren
id|writeaccess
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
id|writeaccess
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|tsk-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tsk-&gt;maj_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_goto
id|do_sigbus
suffix:semicolon
r_default
suffix:colon
r_goto
id|out_of_memory
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Something tried to access memory that isn&squot;t in our memory map..&n;&t; * Fix it, but check if it&squot;s kernel or user first..&n;&t; */
id|bad_area
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|bad_area_nosemaphore
suffix:colon
id|DPG
c_func
(paren
id|show_registers
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
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
multiline_comment|/* Are we prepared to handle this kernel fault?&n;&t; *&n;&t; * (The kernel has valid exception-points in the source &n;&t; *  when it acesses user-memory. When it fails in one&n;&t; *  of those points, we find it in a table and do a jump&n;&t; *  to some fixup code that loads an appropriate error&n;&t; *  code)&n;&t; */
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|regs-&gt;irp
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|regs-&gt;irp
op_assign
id|fixup
suffix:semicolon
id|regs-&gt;frametype
op_assign
id|CRIS_FRAME_FIXUP
suffix:semicolon
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;doing fixup to 0x%x&bslash;n&quot;
comma
id|fixup
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n; * terminate things with extreme prejudice.&n; */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
(paren
id|address
)paren
OL
id|PAGE_SIZE
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL pointer dereference&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel access&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We ran out of memory, or some other thing happened to us that made&n;&t; * us unable to handle the page fault gracefully.&n;&t; */
id|out_of_memory
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
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
(brace
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
r_goto
id|no_context
suffix:semicolon
id|do_sigbus
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/*&n;         * Send a sigbus, regardless of whether we were in kernel&n;         * or user mode.&n;         */
id|info.si_code
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
r_return
suffix:semicolon
id|vmalloc_fault
suffix:colon
(brace
multiline_comment|/*&n;                 * Synchronize this task&squot;s top level page-table&n;                 * with the &squot;reference&squot; page table.&n;                 */
r_int
id|offset
op_assign
id|pgd_index
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
id|pgd
op_assign
id|tsk-&gt;active_mm-&gt;pgd
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
id|pgd
)paren
)paren
(brace
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
id|bad_area_nosemaphore
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
r_return
suffix:semicolon
)brace
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
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
op_logical_or
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd_k
)paren
)paren
r_goto
id|bad_area_nosemaphore
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
r_return
suffix:semicolon
)brace
)brace
eof
