multiline_comment|/*&n; * MMU fault handling support.&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
r_extern
r_void
id|die
(paren
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
multiline_comment|/*&n; * This routine is analogous to expand_stack() but instead grows the&n; * register backing store (which grows towards higher addresses).&n; * Since the register backing store is access sequentially, we&n; * disallow growing the RBS by more than a page at a time.  Note that&n; * the VM_GROWSUP flag can be set on any VM area but that&squot;s fine&n; * because the total process size is still limited by RLIMIT_STACK and&n; * RLIMIT_AS.&n; */
r_static
r_inline
r_int
DECL|function|expand_backing_store
id|expand_backing_store
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|grow
suffix:semicolon
id|grow
op_assign
id|PAGE_SIZE
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|address
op_minus
id|vma-&gt;vm_start
OG
id|current-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_cur
op_logical_or
(paren
(paren
(paren
id|vma-&gt;vm_mm-&gt;total_vm
op_plus
id|grow
)paren
op_lshift
id|PAGE_SHIFT
)paren
OG
id|current-&gt;rlim
(braket
id|RLIMIT_AS
)braket
dot
id|rlim_cur
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|vma-&gt;vm_end
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|vma-&gt;vm_mm-&gt;total_vm
op_add_assign
id|grow
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
id|vma-&gt;vm_mm-&gt;locked_vm
op_add_assign
id|grow
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return TRUE if ADDRESS points at a page in the kernel&squot;s mapped segment&n; * (inside region 5, on ia64) and that page is present.&n; */
r_static
r_int
DECL|function|mapped_kernel_page_is_present
id|mapped_kernel_page_is_present
(paren
r_int
r_int
id|address
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|ptep
comma
id|pte
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
op_logical_or
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
r_return
l_int|0
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
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
op_logical_or
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|ptep
op_assign
id|pte_offset_kernel
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
id|ptep
)paren
r_return
l_int|0
suffix:semicolon
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_return
id|pte_present
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_do_page_fault
id|ia64_do_page_fault
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|isr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|signal
op_assign
id|SIGSEGV
comma
id|code
op_assign
id|SEGV_MAPERR
suffix:semicolon
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
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or have no user context, we must not take the fault..&n;&t; */
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
id|no_context
suffix:semicolon
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
multiline_comment|/*&n;&t; * If fault is in region 5 and we are in the kernel, we may already&n;&t; * have the mmap_sem (pfn_valid macro is called during mmap). There&n;&t; * is no vma for region 5 addr&squot;s anyway, so skip getting the semaphore&n;&t; * and go directly to the exception handling code.&n;&t; */
r_if
c_cond
(paren
(paren
id|REGION_NUMBER
c_func
(paren
id|address
)paren
op_eq
l_int|5
)paren
op_logical_and
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_goto
id|bad_area_no_up
suffix:semicolon
macro_line|#endif
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma_prev
c_func
(paren
id|mm
comma
id|address
comma
op_amp
id|prev_vma
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
multiline_comment|/* find_vma_prev() returns vma such that address &lt; vma-&gt;vm_end or NULL */
r_if
c_cond
(paren
id|address
OL
id|vma-&gt;vm_start
)paren
r_goto
id|check_expansion
suffix:semicolon
id|good_area
suffix:colon
id|code
op_assign
id|SEGV_ACCERR
suffix:semicolon
multiline_comment|/* OK, we&squot;ve got a good vm_area for this memory area.  Check the access permissions: */
DECL|macro|VM_READ_BIT
macro_line|#&t;define VM_READ_BIT&t;0
DECL|macro|VM_WRITE_BIT
macro_line|#&t;define VM_WRITE_BIT&t;1
DECL|macro|VM_EXEC_BIT
macro_line|#&t;define VM_EXEC_BIT&t;2
macro_line|#&t;if (((1 &lt;&lt; VM_READ_BIT) != VM_READ || (1 &lt;&lt; VM_WRITE_BIT) != VM_WRITE) &bslash;&n;&t;    || (1 &lt;&lt; VM_EXEC_BIT) != VM_EXEC)
macro_line|#&t;&t;error File is out of sync with &lt;linux/mm.h&gt;.  Please update.
macro_line|#&t;endif
id|mask
op_assign
(paren
(paren
(paren
(paren
id|isr
op_rshift
id|IA64_ISR_X_BIT
)paren
op_amp
l_int|1UL
)paren
op_lshift
id|VM_EXEC_BIT
)paren
op_or
(paren
(paren
(paren
id|isr
op_rshift
id|IA64_ISR_W_BIT
)paren
op_amp
l_int|1UL
)paren
op_lshift
id|VM_WRITE_BIT
)paren
op_or
(paren
(paren
(paren
id|isr
op_rshift
id|IA64_ISR_R_BIT
)paren
op_amp
l_int|1UL
)paren
op_lshift
id|VM_READ_BIT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|mask
)paren
op_ne
id|mask
)paren
r_goto
id|bad_area
suffix:semicolon
id|survive
suffix:colon
multiline_comment|/*&n;&t; * If for any reason at all we couldn&squot;t handle the fault, make&n;&t; * sure we exit gracefully rather than endlessly redo the&n;&t; * fault.&n;&t; */
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
(paren
id|mask
op_amp
id|VM_WRITE
)paren
op_ne
l_int|0
)paren
)paren
(brace
r_case
id|VM_FAULT_MINOR
suffix:colon
op_increment
id|current-&gt;min_flt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VM_FAULT_MAJOR
suffix:colon
op_increment
id|current-&gt;maj_flt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VM_FAULT_SIGBUS
suffix:colon
multiline_comment|/*&n;&t;&t; * We ran out of memory, or some other thing happened&n;&t;&t; * to us that made us unable to handle the page fault&n;&t;&t; * gracefully.&n;&t;&t; */
id|signal
op_assign
id|SIGBUS
suffix:semicolon
r_goto
id|bad_area
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
id|check_expansion
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|prev_vma
op_logical_and
(paren
id|prev_vma-&gt;vm_flags
op_amp
id|VM_GROWSUP
)paren
op_logical_and
(paren
id|address
op_eq
id|prev_vma-&gt;vm_end
)paren
)paren
)paren
(brace
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
id|REGION_NUMBER
c_func
(paren
id|address
)paren
op_ne
id|REGION_NUMBER
c_func
(paren
id|vma-&gt;vm_start
)paren
op_logical_or
id|REGION_OFFSET
c_func
(paren
id|address
)paren
op_ge
id|RGN_MAP_LIMIT
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
)brace
r_else
(brace
id|vma
op_assign
id|prev_vma
suffix:semicolon
r_if
c_cond
(paren
id|REGION_NUMBER
c_func
(paren
id|address
)paren
op_ne
id|REGION_NUMBER
c_func
(paren
id|vma-&gt;vm_start
)paren
op_logical_or
id|REGION_OFFSET
c_func
(paren
id|address
)paren
op_ge
id|RGN_MAP_LIMIT
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|expand_backing_store
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
)brace
r_goto
id|good_area
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
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
id|bad_area_no_up
suffix:colon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|isr
op_amp
id|IA64_ISR_SP
)paren
op_logical_or
(paren
(paren
id|isr
op_amp
id|IA64_ISR_NA
)paren
op_logical_and
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
multiline_comment|/*&n;&t;&t; * This fault was due to a speculative load or lfetch.fault, set the &quot;ed&quot;&n;&t;&t; * bit in the psr to ensure forward progress.  (Target register will get a&n;&t;&t; * NaT for ld.s, lfetch will be canceled.)&n;&t;&t; */
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
id|si.si_signo
op_assign
id|signal
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|code
suffix:semicolon
id|si.si_addr
op_assign
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
id|si.si_isr
op_assign
id|isr
suffix:semicolon
id|si.si_flags
op_assign
id|__ISR_VALID
suffix:semicolon
id|force_sig_info
c_func
(paren
id|signal
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|no_context
suffix:colon
r_if
c_cond
(paren
id|isr
op_amp
id|IA64_ISR_SP
)paren
(brace
multiline_comment|/*&n;&t;&t; * This fault was due to a speculative load set the &quot;ed&quot; bit in the psr to&n;&t;&t; * ensure forward progress (target register will get a NaT).&n;&t;&t; */
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
multiline_comment|/*&n;&t; * Since we have no vma&squot;s for region 5, we might get here even if the address is&n;&t; * valid, due to the VHPT walker inserting a non present translation that becomes&n;&t; * stale. If that happens, the non present fault handler already purged the stale&n;&t; * translation, which fixed the problem. So, we check to see if the translation is&n;&t; * valid, and return if it is.&n;&t; */
r_if
c_cond
(paren
id|REGION_NUMBER
c_func
(paren
id|address
)paren
op_eq
l_int|5
op_logical_and
id|mapped_kernel_page_is_present
c_func
(paren
id|address
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Oops. The kernel tried to access some bad page. We&squot;ll have to terminate things&n;&t; * with extreme prejudice.&n;&t; */
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
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
l_string|&quot;Unable to handle kernel paging request at &quot;
l_string|&quot;virtual address %016lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|isr
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
r_return
suffix:semicolon
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
id|KERN_CRIT
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
r_goto
id|no_context
suffix:semicolon
)brace
eof
