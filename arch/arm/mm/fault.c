multiline_comment|/*&n; *  linux/arch/arm/mm/fault.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995-2004 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;fault.h&quot;
multiline_comment|/*&n; * This is useful to dump out the page tables associated with&n; * &squot;addr&squot; in mm &squot;mm&squot;.&n; */
DECL|function|show_pte
r_void
id|show_pte
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
id|mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;pgd = %p&bslash;n&quot;
comma
id|mm-&gt;pgd
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;[%08lx] *pgd=%08lx&quot;
comma
id|addr
comma
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
)paren
suffix:semicolon
r_do
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
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
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;(bad)&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
macro_line|#if PTRS_PER_PMD != 1
id|printk
c_func
(paren
l_string|&quot;, *pmd=%08lx&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
macro_line|#endif
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
r_break
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
id|printk
c_func
(paren
l_string|&quot;(bad)&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_HIGHMEM
multiline_comment|/* We must not map this if we have highmem enabled */
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, *pte=%08lx&quot;
comma
id|pte_val
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|printk
c_func
(paren
l_string|&quot;, *ppte=%08lx&quot;
comma
id|pte_val
c_func
(paren
id|pte
(braket
op_minus
id|PTRS_PER_PTE
)braket
)paren
)paren
suffix:semicolon
macro_line|#endif
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
macro_line|#endif
)brace
r_while
c_loop
(paren
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Oops.  The kernel tried to access some page that wasn&squot;t present.&n; */
r_static
r_void
DECL|function|__do_kernel_fault
id|__do_kernel_fault
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * Are we prepared to handle this kernel fault?&n;&t; */
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
multiline_comment|/*&n;&t; * No handler, we&squot;ll have to terminate things with extreme prejudice.&n;&t; */
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
l_string|&quot;Unable to handle kernel %s at virtual address %08lx&bslash;n&quot;
comma
(paren
id|addr
OL
id|PAGE_SIZE
)paren
ques
c_cond
l_string|&quot;NULL pointer dereference&quot;
suffix:colon
l_string|&quot;paging request&quot;
comma
id|addr
)paren
suffix:semicolon
id|show_pte
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|fsr
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
)brace
multiline_comment|/*&n; * Something tried to access memory that isn&squot;t in our memory map..&n; * User mode accesses just cause a SIGSEGV&n; */
r_static
r_void
DECL|function|__do_user_fault
id|__do_user_fault
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_int
id|code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|siginfo
id|si
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
r_if
c_cond
(paren
id|user_debug
op_amp
id|UDBG_SEGV
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: unhandled page fault at 0x%08lx, code 0x%03x&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|addr
comma
id|fsr
)paren
suffix:semicolon
id|show_pte
c_func
(paren
id|tsk-&gt;mm
comma
id|addr
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
id|tsk-&gt;thread.address
op_assign
id|addr
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|fsr
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
l_int|14
suffix:semicolon
id|si.si_signo
op_assign
id|SIGSEGV
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
id|addr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|si
comma
id|tsk
)paren
suffix:semicolon
)brace
r_void
DECL|function|do_bad_area
id|do_bad_area
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * If we are in kernel mode at this point, we&n;&t; * have no context to handle this fault with.&n;&t; */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|__do_user_fault
c_func
(paren
id|tsk
comma
id|addr
comma
id|fsr
comma
id|SEGV_MAPERR
comma
id|regs
)paren
suffix:semicolon
r_else
id|__do_kernel_fault
c_func
(paren
id|mm
comma
id|addr
comma
id|fsr
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|macro|VM_FAULT_BADMAP
mdefine_line|#define VM_FAULT_BADMAP&t;&t;(-20)
DECL|macro|VM_FAULT_BADACCESS
mdefine_line|#define VM_FAULT_BADACCESS&t;(-21)
r_static
r_int
DECL|function|__do_page_fault
id|__do_page_fault
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|fault
comma
id|mask
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|fault
op_assign
id|VM_FAULT_BADMAP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
OG
id|addr
)paren
r_goto
id|check_stack
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, we have a good vm_area for this&n;&t; * memory access, so we can handle it.&n;&t; */
id|good_area
suffix:colon
r_if
c_cond
(paren
id|fsr
op_amp
(paren
l_int|1
op_lshift
l_int|11
)paren
)paren
multiline_comment|/* write? */
id|mask
op_assign
id|VM_WRITE
suffix:semicolon
r_else
id|mask
op_assign
id|VM_READ
op_or
id|VM_EXEC
suffix:semicolon
id|fault
op_assign
id|VM_FAULT_BADACCESS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|mask
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * If for any reason at all we couldn&squot;t handle&n;&t; * the fault, make sure we exit gracefully rather&n;&t; * than endlessly redo the fault.&n;&t; */
id|survive
suffix:colon
id|fault
op_assign
id|handle_mm_fault
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
op_amp
id|PAGE_MASK
comma
id|fsr
op_amp
(paren
l_int|1
op_lshift
l_int|11
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Handle the &quot;normal&quot; cases first - successful and sigbus&n;&t; */
r_switch
c_cond
(paren
id|fault
)paren
(brace
r_case
id|VM_FAULT_MAJOR
suffix:colon
id|tsk-&gt;maj_flt
op_increment
suffix:semicolon
r_return
id|fault
suffix:semicolon
r_case
id|VM_FAULT_MINOR
suffix:colon
id|tsk-&gt;min_flt
op_increment
suffix:semicolon
r_case
id|VM_FAULT_SIGBUS
suffix:colon
r_return
id|fault
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tsk-&gt;pid
op_ne
l_int|1
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * If we are out of memory for pid1,&n;&t; * sleep for a while and retry&n;&t; */
id|yield
c_func
(paren
)paren
suffix:semicolon
r_goto
id|survive
suffix:semicolon
id|check_stack
suffix:colon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
op_logical_and
op_logical_neg
id|expand_stack
c_func
(paren
id|vma
comma
id|addr
)paren
)paren
r_goto
id|good_area
suffix:semicolon
id|out
suffix:colon
r_return
id|fault
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_page_fault
id|do_page_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
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
r_int
id|fault
suffix:semicolon
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
id|fault
op_assign
id|__do_page_fault
c_func
(paren
id|mm
comma
id|addr
comma
id|fsr
comma
id|tsk
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Handle the &quot;normal&quot; case first&n;&t; */
r_if
c_cond
(paren
id|fault
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We had some memory, but were unable to&n;&t; * successfully fix up this page fault.&n;&t; */
r_if
c_cond
(paren
id|fault
op_eq
l_int|0
)paren
r_goto
id|do_sigbus
suffix:semicolon
multiline_comment|/*&n;&t; * If we are in kernel mode at this point, we&n;&t; * have no context to handle this fault with.&n;&t; */
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
r_if
c_cond
(paren
id|fault
op_eq
id|VM_FAULT_OOM
)paren
(brace
multiline_comment|/*&n;&t;&t; * We ran out of memory, or some other thing happened to&n;&t;&t; * us that made us unable to handle the page fault gracefully.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;VM: killing process %s&bslash;n&quot;
comma
id|tsk-&gt;comm
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
r_else
id|__do_user_fault
c_func
(paren
id|tsk
comma
id|addr
comma
id|fsr
comma
id|fault
op_eq
id|VM_FAULT_BADACCESS
ques
c_cond
id|SEGV_ACCERR
suffix:colon
id|SEGV_MAPERR
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n; * We ran out of memory, or some other thing happened to us that made&n; * us unable to handle the page fault gracefully.&n; */
id|do_sigbus
suffix:colon
multiline_comment|/*&n;&t; * Send a sigbus, regardless of whether we were in kernel&n;&t; * or user mode.&n;&t; */
id|tsk-&gt;thread.address
op_assign
id|addr
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|fsr
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
macro_line|#ifdef CONFIG_DEBUG_USER
r_if
c_cond
(paren
id|user_debug
op_amp
id|UDBG_BUS
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: sigbus at 0x%08lx, pc=0x%08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|addr
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Kernel mode? Handle exceptions or die */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|no_context
suffix:colon
id|__do_kernel_fault
c_func
(paren
id|mm
comma
id|addr
comma
id|fsr
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * First Level Translation Fault Handler&n; *&n; * We enter here because the first level page table doesn&squot;t contain&n; * a valid entry for the address.&n; *&n; * If the address is in kernel space (&gt;= TASK_SIZE), then we are&n; * probably faulting in the vmalloc() area.&n; *&n; * If the init_task&squot;s first level page tables contains the relevant&n; * entry, we copy the it to this task.  If not, we send the process&n; * a signal, fixup the exception, or oops the kernel.&n; *&n; * NOTE! We MUST NOT take any locks for this case. We may be in an&n; * interrupt or a critical region, and should only copy the information&n; * from the master page table, nothing more.&n; */
r_static
r_int
DECL|function|do_translation_fault
id|do_translation_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
r_int
id|index
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
r_if
c_cond
(paren
id|addr
OL
id|TASK_SIZE
)paren
r_return
id|do_page_fault
c_func
(paren
id|addr
comma
id|fsr
comma
id|regs
)paren
suffix:semicolon
id|index
op_assign
id|pgd_index
c_func
(paren
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: CP15 C1 is write only on ARMv3 architectures.&n;&t; */
id|pgd
op_assign
id|cpu_get_pgd
c_func
(paren
)paren
op_plus
id|index
suffix:semicolon
id|pgd_k
op_assign
id|init_mm.pgd
op_plus
id|index
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd_k
)paren
)paren
r_goto
id|bad_area
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
id|set_pgd
c_func
(paren
id|pgd
comma
op_star
id|pgd_k
)paren
suffix:semicolon
id|pmd_k
op_assign
id|pmd_offset
c_func
(paren
id|pgd_k
comma
id|addr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd_k
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
id|copy_pmd
c_func
(paren
id|pmd
comma
id|pmd_k
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad_area
suffix:colon
id|tsk
op_assign
id|current
suffix:semicolon
id|do_bad_area
c_func
(paren
id|tsk
comma
id|tsk-&gt;active_mm
comma
id|addr
comma
id|fsr
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Some section permission faults need to be handled gracefully.&n; * They can happen due to a __{get,put}_user during an oops.&n; */
r_static
r_int
DECL|function|do_sect_fault
id|do_sect_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|do_bad_area
c_func
(paren
id|tsk
comma
id|tsk-&gt;active_mm
comma
id|addr
comma
id|fsr
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This abort handler always returns &quot;fault&quot;.&n; */
r_static
r_int
DECL|function|do_bad
id|do_bad
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|struct|fsr_info
r_static
r_struct
id|fsr_info
(brace
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|variable|fsr_info
)brace
id|fsr_info
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&t; * The following are the standard ARMv3 and ARMv4 aborts.  ARMv5&n;&t; * defines these to be &quot;precise&quot; aborts.&n;&t; */
(brace
id|do_bad
comma
id|SIGSEGV
comma
l_string|&quot;vector exception&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGILL
comma
l_string|&quot;alignment exception&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGKILL
comma
l_string|&quot;terminal exception&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGILL
comma
l_string|&quot;alignment exception&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on linefetch&quot;
)brace
comma
(brace
id|do_translation_fault
comma
id|SIGSEGV
comma
l_string|&quot;section translation fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on linefetch&quot;
)brace
comma
(brace
id|do_page_fault
comma
id|SIGSEGV
comma
l_string|&quot;page translation fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on non-linefetch&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGSEGV
comma
l_string|&quot;section domain fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on non-linefetch&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGSEGV
comma
l_string|&quot;page domain fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on translation&quot;
)brace
comma
(brace
id|do_sect_fault
comma
id|SIGSEGV
comma
l_string|&quot;section permission fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on translation&quot;
)brace
comma
(brace
id|do_page_fault
comma
id|SIGSEGV
comma
l_string|&quot;page permission fault&quot;
)brace
comma
multiline_comment|/*&n;&t; * The following are &quot;imprecise&quot; aborts, which are signalled by bit&n;&t; * 10 of the FSR, and may not be recoverable.  These are only&n;&t; * supported if the CPU abort handler supports bit 10.&n;&t; */
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 16&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 17&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 18&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 19&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;lock abort&quot;
)brace
comma
multiline_comment|/* xscale */
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 21&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;imprecise external abort&quot;
)brace
comma
multiline_comment|/* xscale */
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 23&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;dcache parity error&quot;
)brace
comma
multiline_comment|/* xscale */
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 25&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 26&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 27&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 28&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 29&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 30&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;unknown 31&quot;
)brace
)brace
suffix:semicolon
r_void
id|__init
DECL|function|hook_fault_code
id|hook_fault_code
c_func
(paren
r_int
id|nr
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|sig
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|nr
op_ge
l_int|0
op_logical_and
id|nr
OL
id|ARRAY_SIZE
c_func
(paren
id|fsr_info
)paren
)paren
(brace
id|fsr_info
(braket
id|nr
)braket
dot
id|fn
op_assign
id|fn
suffix:semicolon
id|fsr_info
(braket
id|nr
)braket
dot
id|sig
op_assign
id|sig
suffix:semicolon
id|fsr_info
(braket
id|nr
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Dispatch a data abort to the relevant handler.&n; */
id|asmlinkage
r_void
DECL|function|do_DataAbort
id|do_DataAbort
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_const
r_struct
id|fsr_info
op_star
id|inf
op_assign
id|fsr_info
op_plus
(paren
id|fsr
op_amp
l_int|15
)paren
op_plus
(paren
(paren
id|fsr
op_amp
(paren
l_int|1
op_lshift
l_int|10
)paren
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inf
op_member_access_from_pointer
id|fn
c_func
(paren
id|addr
comma
id|fsr
comma
id|regs
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unhandled fault: %s (0x%03x) at 0x%08lx&bslash;n&quot;
comma
id|inf-&gt;name
comma
id|fsr
comma
id|addr
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|inf-&gt;sig
comma
id|current
)paren
suffix:semicolon
id|show_pte
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|do_PrefetchAbort
id|do_PrefetchAbort
c_func
(paren
r_int
r_int
id|addr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_translation_fault
c_func
(paren
id|addr
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
)brace
eof
