multiline_comment|/*&n; *  linux/arch/frv/mm/fault.c&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * - Written by David Howells (dhowells@redhat.com)&n; * - Derived from arch/m68knommu/mm/fault.c&n; *   - Copyright (C) 1998  D. Jeff Dionne &lt;jeff@lineo.ca&gt;,&n; *   - Copyright (C) 2000  Lineo, Inc.  (www.lineo.com)&n; *&n; *  Based on:&n; *&n; *  linux/arch/m68k/mm/fault.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/hardirq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * This routine handles page faults.  It determines the problem, and&n; * then passes it off to one of the appropriate routines.&n; */
DECL|function|do_page_fault
id|asmlinkage
r_void
id|do_page_fault
c_func
(paren
r_int
id|datammu
comma
r_int
r_int
id|esr0
comma
r_int
r_int
id|ear0
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
comma
op_star
id|prev_vma
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_int
r_int
id|_pme
comma
id|lrai
comma
id|lrad
comma
id|fixup
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
id|pgd_t
op_star
id|pge
suffix:semicolon
id|pud_t
op_star
id|pue
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|write
suffix:semicolon
macro_line|#if 0
r_const
r_char
op_star
id|atxc
(braket
l_int|16
)braket
op_assign
(brace
(braket
l_int|0x0
)braket
op_assign
l_string|&quot;mmu-miss&quot;
comma
(braket
l_int|0x8
)braket
op_assign
l_string|&quot;multi-dat&quot;
comma
(braket
l_int|0x9
)braket
op_assign
l_string|&quot;multi-sat&quot;
comma
(braket
l_int|0xa
)braket
op_assign
l_string|&quot;tlb-miss&quot;
comma
(braket
l_int|0xc
)braket
op_assign
l_string|&quot;privilege&quot;
comma
(braket
l_int|0xd
)braket
op_assign
l_string|&quot;write-prot&quot;
comma
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;do_page_fault(%d,%lx [%s],%lx)&bslash;n&quot;
comma
id|datammu
comma
id|esr0
comma
id|atxc
(braket
id|esr0
op_rshift
l_int|20
op_amp
l_int|0xf
)braket
comma
id|ear0
)paren
suffix:semicolon
macro_line|#endif
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
multiline_comment|/*&n;&t; * We fault-in kernel-space virtual memory on-demand. The&n;&t; * &squot;reference&squot; page table is init_mm.pgd.&n;&t; *&n;&t; * NOTE! We MUST NOT take any locks for this case. We may&n;&t; * be in an interrupt or a critical region, and should&n;&t; * only copy the information from the master page table,&n;&t; * nothing more.&n;&t; *&n;&t; * This verifies that the fault happens in kernel space&n;&t; * and that the fault was a page not present (invalid) error&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|__frame
)paren
op_logical_and
(paren
id|esr0
op_amp
id|ESR0_ATXC
)paren
op_eq
id|ESR0_ATXC_AMRTLB_MISS
)paren
(brace
r_if
c_cond
(paren
id|ear0
op_ge
id|VMALLOC_START
op_logical_and
id|ear0
OL
id|VMALLOC_END
)paren
r_goto
id|kernel_pte_fault
suffix:semicolon
r_if
c_cond
(paren
id|ear0
op_ge
id|PKMAP_BASE
op_logical_and
id|ear0
OL
id|PKMAP_END
)paren
r_goto
id|kernel_pte_fault
suffix:semicolon
)brace
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
id|ear0
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
id|ear0
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
id|__frame
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * accessing the stack below %esp is always a bug.&n;&t;&t; * The &quot;+ 32&quot; is there due to some instructions (like&n;&t;&t; * pusha) doing post-decrement on the stack and that&n;&t;&t; * doesn&squot;t show up until later..&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|ear0
op_amp
id|PAGE_MASK
)paren
op_plus
l_int|2
op_star
id|PAGE_SIZE
OL
id|__frame-&gt;sp
)paren
(brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;[%d] ### Access below stack @%lx (sp=%lx)&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|ear0
comma
id|__frame-&gt;sp
)paren
suffix:semicolon
id|show_registers
c_func
(paren
id|__frame
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[%d] ### Code: [%08lx] %02x %02x %02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|__frame-&gt;pc
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|1
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|2
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|3
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|4
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|5
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|6
)braket
comma
(paren
(paren
id|u8
op_star
)paren
id|__frame-&gt;pc
)paren
(braket
l_int|7
)braket
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|bad_area
suffix:semicolon
)brace
)brace
multiline_comment|/* find_vma_prev is just a bit slower, because it cannot use&n;&t; * the mmap_cache, so we run it only in the growsdown slow&n;&t; * path and we leave find_vma in the fast path.&n;&t; */
id|find_vma_prev
c_func
(paren
id|current-&gt;mm
comma
id|ear0
comma
op_amp
id|prev_vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expand_stack
c_func
(paren
id|vma
comma
id|ear0
comma
id|prev_vma
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
id|write
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|esr0
op_amp
id|ESR0_ATXC
)paren
(brace
r_default
suffix:colon
(brace
)brace
multiline_comment|/* handle write to write protected page */
r_case
id|ESR0_ATXC_WP_EXCEP
suffix:colon
macro_line|#ifdef TEST_VERIFY_AREA
r_if
c_cond
(paren
op_logical_neg
(paren
id|user_mode
c_func
(paren
id|__frame
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;WP fault at %08lx&bslash;n&quot;
comma
id|__frame-&gt;pc
)paren
suffix:semicolon
macro_line|#endif
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
id|write
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* handle read from protected page */
r_case
id|ESR0_ATXC_PRIV_EXCEP
suffix:colon
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/* handle read, write or exec on absent page&n;&t;&t;  * - can&squot;t support write without permitting read&n;&t;&t;  * - don&squot;t support execute without permitting read and vice-versa&n;&t;&t;  */
r_case
id|ESR0_ATXC_AMRTLB_MISS
suffix:colon
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
id|VM_WRITE
op_or
id|VM_EXEC
)paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
r_break
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
id|ear0
comma
id|write
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|current-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|current-&gt;maj_flt
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
multiline_comment|/* User mode accesses just cause a SIGSEGV */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|__frame
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
id|ear0
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
suffix:semicolon
)brace
id|no_context
suffix:colon
multiline_comment|/* are we prepared to handle this kernel fault? */
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|__frame-&gt;pc
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|__frame-&gt;pc
op_assign
id|fixup
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n; * terminate things with extreme prejudice.&n; */
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ear0
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
l_string|&quot;Unable to handle kernel paging request&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at virtual addr %08lx&bslash;n&quot;
comma
id|ear0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  PC  : %08lx&bslash;n&quot;
comma
id|__frame-&gt;pc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  EXC : esr0=%08lx ear0=%08lx&bslash;n&quot;
comma
id|esr0
comma
id|ear0
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;lrai %1,%0,#1,#0,#0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|lrai
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ear0
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;lrad %1,%0,#1,#0,#0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|lrad
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ear0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;  LRAI: %08lx&bslash;n&quot;
comma
id|lrai
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;  LRAD: %08lx&bslash;n&quot;
comma
id|lrad
)paren
suffix:semicolon
id|__break_hijack_kernel_event
c_func
(paren
)paren
suffix:semicolon
id|pge
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|ear0
)paren
suffix:semicolon
id|pue
op_assign
id|pud_offset
c_func
(paren
id|pge
comma
id|ear0
)paren
suffix:semicolon
id|_pme
op_assign
id|pue-&gt;pue
(braket
l_int|0
)braket
dot
id|ste
(braket
l_int|0
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;  PGE : %8p { PME %08lx }&bslash;n&quot;
comma
id|pge
comma
id|_pme
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_pme
op_amp
id|xAMPRx_V
)paren
(brace
r_int
r_int
id|dampr
comma
id|damlr
comma
id|val
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movsg dampr2,%0 ! movgs %2,dampr2 ! movsg damlr2,%1&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|dampr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|damlr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|_pme
op_or
id|xAMPRx_L
op_or
id|xAMPRx_SS_16Kb
op_or
id|xAMPRx_S
op_or
id|xAMPRx_C
op_or
id|xAMPRx_V
)paren
)paren
suffix:semicolon
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|damlr
op_plus
id|__pte_index
c_func
(paren
id|ear0
)paren
suffix:semicolon
id|val
op_assign
id|pte_val
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movgs %0,dampr2&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|dampr
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;  PTE : %8p { %08lx }&bslash;n&quot;
comma
id|pte
comma
id|val
)paren
suffix:semicolon
)brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
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
id|__frame
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
multiline_comment|/*&n;&t; * Send a sigbus, regardless of whether we were in kernel&n;&t; * or user mode.&n;&t; */
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
id|ear0
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
multiline_comment|/* Kernel mode? Handle exceptions or die */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|__frame
)paren
)paren
r_goto
id|no_context
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/*&n; * The fault was caused by a kernel PTE (such as installed by vmalloc or kmap)&n; */
id|kernel_pte_fault
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * Synchronize this task&squot;s top level page-table&n;&t;&t; * with the &squot;reference&squot; page table.&n;&t;&t; *&n;&t;&t; * Do _not_ use &quot;tsk&quot; here. We might be inside&n;&t;&t; * an interrupt in the middle of a task switch..&n;&t;&t; */
r_int
id|index
op_assign
id|pgd_index
c_func
(paren
id|ear0
)paren
suffix:semicolon
id|pgd_t
op_star
id|pgd
comma
op_star
id|pgd_k
suffix:semicolon
id|pud_t
op_star
id|pud
comma
op_star
id|pud_k
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
id|__get_TTBR
c_func
(paren
)paren
suffix:semicolon
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|__va
c_func
(paren
id|pgd
)paren
op_plus
id|index
suffix:semicolon
id|pgd_k
op_assign
(paren
(paren
id|pgd_t
op_star
)paren
(paren
id|init_mm.pgd
)paren
)paren
op_plus
id|index
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
singleline_comment|//set_pgd(pgd, *pgd_k); /////// gcc ICE&squot;s on this line
id|pud_k
op_assign
id|pud_offset
c_func
(paren
id|pgd_k
comma
id|ear0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pud_present
c_func
(paren
op_star
id|pud_k
)paren
)paren
r_goto
id|no_context
suffix:semicolon
id|pmd_k
op_assign
id|pmd_offset
c_func
(paren
id|pud_k
comma
id|ear0
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
id|pud
op_assign
id|pud_offset
c_func
(paren
id|pgd
comma
id|ear0
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pud
comma
id|ear0
)paren
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
id|ear0
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
multiline_comment|/* end do_page_fault() */
eof
