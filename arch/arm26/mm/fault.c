multiline_comment|/*&n; *  linux/arch/arm26/mm/fault.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
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
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt; 
singleline_comment|//FIXME this header may be bogusly included
macro_line|#include &quot;fault.h&quot;
DECL|macro|FAULT_CODE_LDRSTRPOST
mdefine_line|#define FAULT_CODE_LDRSTRPOST   0x80
DECL|macro|FAULT_CODE_LDRSTRPRE
mdefine_line|#define FAULT_CODE_LDRSTRPRE    0x40
DECL|macro|FAULT_CODE_LDRSTRREG
mdefine_line|#define FAULT_CODE_LDRSTRREG    0x20
DECL|macro|FAULT_CODE_LDMSTM
mdefine_line|#define FAULT_CODE_LDMSTM       0x10
DECL|macro|FAULT_CODE_LDCSTC
mdefine_line|#define FAULT_CODE_LDCSTC       0x08
DECL|macro|FAULT_CODE_PREFETCH
mdefine_line|#define FAULT_CODE_PREFETCH     0x04
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE        0x02
DECL|macro|FAULT_CODE_FORCECOW
mdefine_line|#define FAULT_CODE_FORCECOW     0x01
DECL|macro|DO_COW
mdefine_line|#define DO_COW(m)               ((m) &amp; (FAULT_CODE_WRITE|FAULT_CODE_FORCECOW))
DECL|macro|READ_FAULT
mdefine_line|#define READ_FAULT(m)           (!((m) &amp; FAULT_CODE_WRITE))
DECL|macro|DEBUG
mdefine_line|#define DEBUG
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
multiline_comment|/* We must not map this if we have highmem enabled */
multiline_comment|/* FIXME */
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
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
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
multiline_comment|/*&n;         * Are we prepared to handle this kernel fault?&n;         */
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
id|printk
c_func
(paren
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
singleline_comment|//dump_backtrace(regs, tsk); // FIXME ARM32 dropped this - why?
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
singleline_comment|//FIXME - hack to stop debug going nutso
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
id|fsr
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
id|fsr
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
(brace
r_goto
id|do_sigbus
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we are in kernel mode at this point, we&n;&t; * have no context to handle this fault with.&n;         * FIXME - is this test right?&n;&t; */
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
r_goto
id|no_context
suffix:semicolon
)brace
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
(brace
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
)brace
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
singleline_comment|//FIXME - need other bits setting?
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
id|fsr
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a data abort.  Note that we have to handle a range of addresses&n; * on ARM2/3 for ldm.  If both pages are zero-mapped, then we have to force&n; * a copy-on-write.  However, on the second page, we always force COW.&n; */
id|asmlinkage
r_void
DECL|function|do_DataAbort
id|do_DataAbort
c_func
(paren
r_int
r_int
id|min_addr
comma
r_int
r_int
id|max_addr
comma
r_int
id|mode
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_page_fault
c_func
(paren
id|min_addr
comma
id|mode
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|min_addr
op_xor
id|max_addr
)paren
op_rshift
id|PAGE_SHIFT
)paren
(brace
id|do_page_fault
c_func
(paren
id|max_addr
comma
id|mode
op_or
id|FAULT_CODE_FORCECOW
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
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
macro_line|#if 0
r_if
c_cond
(paren
id|the
id|memc
id|mapping
r_for
id|this
id|page
id|exists
)paren
(brace
id|printk
(paren
l_string|&quot;Page in, but got abort (undefined instruction?)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|do_page_fault
c_func
(paren
id|addr
comma
id|FAULT_CODE_PREFETCH
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
