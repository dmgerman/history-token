multiline_comment|/*&n; *  linux/arch/arm/mm/fault-common.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#ifdef CONFIG_CPU_26
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE&t;0x02
DECL|macro|FAULT_CODE_FORCECOW
mdefine_line|#define FAULT_CODE_FORCECOW&t;0x01
DECL|macro|DO_COW
mdefine_line|#define DO_COW(m)&t;&t;((m) &amp; (FAULT_CODE_WRITE|FAULT_CODE_FORCECOW))
DECL|macro|READ_FAULT
mdefine_line|#define READ_FAULT(m)&t;&t;(!((m) &amp; FAULT_CODE_WRITE))
macro_line|#else
multiline_comment|/*&n; * On 32-bit processors, we define &quot;mode&quot; to be zero when reading,&n; * non-zero when writing.  This now ties up nicely with the polarity&n; * of the 26-bit machines, and also means that we avoid the horrible&n; * gcc code for &quot;int val = !other_val;&quot;.&n; */
DECL|macro|DO_COW
mdefine_line|#define DO_COW(code)&t;&t;((code) &amp; (1 &lt;&lt; 8))
DECL|macro|READ_FAULT
mdefine_line|#define READ_FAULT(code)&t;(!DO_COW(code))
macro_line|#endif
id|NORET_TYPE
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|msg
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
id|ATTRIB_NORET
suffix:semicolon
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
l_string|&quot;*pgd = %08lx&quot;
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
id|printk
c_func
(paren
l_string|&quot;, *pmd = %08lx&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
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
l_string|&quot;, *pte = %08lx&quot;
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
l_string|&quot;, *ppte = %08lx&quot;
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
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|fixup
suffix:semicolon
multiline_comment|/*&n;&t; * Are we prepared to handle this kernel fault?&n;&t; */
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Exception at [&lt;%lx&gt;] addr=%lx (fixup: %lx)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|regs-&gt;ARM_pc
comma
id|addr
comma
id|fixup
)paren
suffix:semicolon
macro_line|#endif
id|regs-&gt;ARM_pc
op_assign
id|fixup
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No handler, we&squot;ll have to terminate things with extreme prejudice.&n;&t; */
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
id|error_code
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
id|error_code
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
id|error_code
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
macro_line|#endif
id|tsk-&gt;thread.address
op_assign
id|addr
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|error_code
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
id|error_code
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
id|error_code
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
id|error_code
comma
id|regs
)paren
suffix:semicolon
)brace
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
id|error_code
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
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* bad map area */
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
id|READ_FAULT
c_func
(paren
id|error_code
)paren
)paren
multiline_comment|/* read? */
id|mask
op_assign
id|VM_READ
op_or
id|VM_EXEC
suffix:semicolon
r_else
id|mask
op_assign
id|VM_WRITE
suffix:semicolon
id|fault
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* bad access type */
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
id|DO_COW
c_func
(paren
id|error_code
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
l_int|2
suffix:colon
id|tsk-&gt;maj_flt
op_increment
suffix:semicolon
r_return
id|fault
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tsk-&gt;min_flt
op_increment
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
id|fault
suffix:semicolon
)brace
id|fault
op_assign
op_minus
l_int|3
suffix:semicolon
multiline_comment|/* out of memory */
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
DECL|function|do_page_fault
r_int
id|do_page_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
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
id|error_code
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
op_minus
l_int|3
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
id|error_code
comma
id|fault
op_eq
op_minus
l_int|1
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
id|error_code
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
id|error_code
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * First Level Translation Fault Handler&n; *&n; * We enter here because the first level page table doesn&squot;t contain&n; * a valid entry for the address.&n; *&n; * If the address is in kernel space (&gt;= TASK_SIZE), then we are&n; * probably faulting in the vmalloc() area.&n; *&n; * If the init_task&squot;s first level page tables contains the relevant&n; * entry, we copy the it to this task.  If not, we send the process&n; * a signal, fixup the exception, or oops the kernel.&n; *&n; * NOTE! We MUST NOT take any locks for this case. We may be in an&n; * interrupt or a critical region, and should only copy the information&n; * from the master page table, nothing more.&n; */
DECL|function|do_translation_fault
r_int
id|do_translation_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
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
id|offset
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
id|error_code
comma
id|regs
)paren
suffix:semicolon
id|offset
op_assign
id|__pgd_offset
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
id|error_code
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
