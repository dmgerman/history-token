multiline_comment|/* $Id: fault.c,v 1.13 2003/08/11 11:44:50 lethal Exp $&n; *&n; *  linux/arch/sh/mm/fault.c&n; *  Copyright (C) 1999  Niibe Yutaka&n; *  Copyright (C) 2003  Paul Mundt&n; *&n; *  Based on linux/arch/i386/mm/fault.c:&n; *   Copyright (C) 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
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
id|writeaccess
comma
r_int
r_int
id|address
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
r_int
id|page
suffix:semicolon
macro_line|#ifdef CONFIG_SH_KGDB
r_if
c_cond
(paren
id|kgdb_nofault
op_logical_and
id|kgdb_bus_err_hook
)paren
id|kgdb_bus_err_hook
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|tsk
op_assign
id|current
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
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
id|survive
suffix:colon
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
id|tsk-&gt;thread.address
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|writeaccess
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
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
r_return
suffix:semicolon
multiline_comment|/*&n; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n; * terminate things with extreme prejudice.&n; *&n; */
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
l_string|&quot;Unable to handle kernel paging request&quot;
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
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;pc = %08lx&bslash;n&quot;
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov.l&t;%1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_TTB
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|page
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|page
)paren
(braket
id|address
op_rshift
l_int|22
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;*pde = %08lx&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_amp
id|_PAGE_PRESENT
)paren
(brace
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|address
op_and_assign
l_int|0x003ff000
suffix:semicolon
id|page
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|__va
c_func
(paren
id|page
)paren
)paren
(braket
id|address
op_rshift
id|PAGE_SHIFT
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;*pte = %08lx&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
)brace
)brace
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|writeaccess
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
multiline_comment|/*&n;&t; * Send a sigbus, regardless of whether we were in kernel&n;&t; * or user mode.&n;&t; */
id|tsk-&gt;thread.address
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|writeaccess
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
l_int|14
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGBUS
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
)brace
multiline_comment|/*&n; * Called with interrupt disabled.&n; */
DECL|function|__do_page_fault
id|asmlinkage
r_int
id|__do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|writeaccess
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|addrmax
op_assign
id|P4SEG
suffix:semicolon
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte_t
id|entry
suffix:semicolon
macro_line|#ifdef CONFIG_SH_KGDB
r_if
c_cond
(paren
id|kgdb_nofault
op_logical_and
id|kgdb_bus_err_hook
)paren
id|kgdb_bus_err_hook
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SH_STORE_QUEUES
id|addrmax
op_assign
id|P4SEG_STORE_QUE
op_plus
l_int|0x04000000
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|address
op_ge
id|P3SEG
op_logical_and
id|address
OL
id|addrmax
)paren
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|address
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|address
op_ge
id|TASK_SIZE
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;mm
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
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
r_return
l_int|1
suffix:semicolon
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
id|pmd_ERROR
c_func
(paren
op_star
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
l_int|1
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|entry
op_assign
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|entry
)paren
op_logical_or
id|pte_not_present
c_func
(paren
id|entry
)paren
op_logical_or
(paren
id|writeaccess
op_logical_and
op_logical_neg
id|pte_write
c_func
(paren
id|entry
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|writeaccess
)paren
id|entry
op_assign
id|pte_mkdirty
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
id|pte_mkyoung
c_func
(paren
id|entry
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_SH4
multiline_comment|/*&n;&t; * ITLB is not affected by &quot;ldtlb&quot; instruction.&n;&t; * So, we need to flush the entry by ourselves.&n;&t; */
id|__flush_tlb_page
c_func
(paren
id|get_asid
c_func
(paren
)paren
comma
id|address
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
macro_line|#endif
id|set_pte
c_func
(paren
id|pte
comma
id|entry
)paren
suffix:semicolon
id|update_mmu_cache
c_func
(paren
l_int|NULL
comma
id|address
comma
id|entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_logical_and
id|vma-&gt;vm_mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|asid
suffix:semicolon
r_int
r_int
id|saved_asid
op_assign
id|MMU_NO_ASID
suffix:semicolon
id|asid
op_assign
id|vma-&gt;vm_mm-&gt;context
op_amp
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_ne
id|current-&gt;mm
)paren
(brace
id|saved_asid
op_assign
id|get_asid
c_func
(paren
)paren
suffix:semicolon
id|set_asid
c_func
(paren
id|asid
)paren
suffix:semicolon
)brace
id|__flush_tlb_page
c_func
(paren
id|asid
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_asid
op_ne
id|MMU_NO_ASID
)paren
id|set_asid
c_func
(paren
id|saved_asid
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_range
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|size
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|size
op_assign
(paren
id|end
op_minus
id|start
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|MMU_NTLB_ENTRIES
op_div
l_int|4
)paren
)paren
(brace
multiline_comment|/* Too many TLB to flush */
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
id|activate_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|asid
op_assign
id|mm-&gt;context
op_amp
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
r_int
r_int
id|saved_asid
op_assign
id|MMU_NO_ASID
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|end
op_add_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|current-&gt;mm
)paren
(brace
id|saved_asid
op_assign
id|get_asid
c_func
(paren
)paren
suffix:semicolon
id|set_asid
c_func
(paren
id|asid
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|__flush_tlb_page
c_func
(paren
id|asid
comma
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|saved_asid
op_ne
id|MMU_NO_ASID
)paren
id|set_asid
c_func
(paren
id|saved_asid
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_kernel_range
r_void
id|flush_tlb_kernel_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|size
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|size
op_assign
(paren
id|end
op_minus
id|start
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|MMU_NTLB_ENTRIES
op_div
l_int|4
)paren
)paren
(brace
multiline_comment|/* Too many TLB to flush */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|asid
op_assign
id|init_mm.context
op_amp
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
r_int
r_int
id|saved_asid
op_assign
id|get_asid
c_func
(paren
)paren
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|end
op_add_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|set_asid
c_func
(paren
id|asid
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|__flush_tlb_page
c_func
(paren
id|asid
comma
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|set_asid
c_func
(paren
id|saved_asid
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* Invalidate all TLB of this process. */
multiline_comment|/* Instead of invalidating each TLB, we get new MMU context. */
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
id|activate_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_all
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
comma
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Flush all the TLB.&n;&t; *&n;&t; * Write to the MMU control register&squot;s bit:&n;&t; * &t;TF-bit for SH-3, TI-bit for SH-4.&n;&t; *      It&squot;s same position, bit #2.&n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|ctrl_inl
c_func
(paren
id|MMUCR
)paren
suffix:semicolon
id|status
op_or_assign
l_int|0x04
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|status
comma
id|MMUCR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
