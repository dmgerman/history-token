multiline_comment|/*&n; *  linux/arch/m32r/mm/fault.c&n; *&n; *  Copyright (c) 2001, 2002  Hitoshi Yamamoto, and H. Kondo&n; *  Copyright (c) 2004  Naoto Sugai, NIIBE Yutaka&n; *&n; *  Some code taken from i386 version.&n; *    Copyright (C) 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;&t;&t;/* For unblank_screen() */
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
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
macro_line|#ifndef CONFIG_SMP
DECL|variable|tlb_entry_i_dat
id|asmlinkage
r_int
r_int
id|tlb_entry_i_dat
suffix:semicolon
DECL|variable|tlb_entry_d_dat
id|asmlinkage
r_int
r_int
id|tlb_entry_d_dat
suffix:semicolon
DECL|macro|tlb_entry_i
mdefine_line|#define tlb_entry_i tlb_entry_i_dat
DECL|macro|tlb_entry_d
mdefine_line|#define tlb_entry_d tlb_entry_d_dat
macro_line|#else
DECL|variable|tlb_entry_i_dat
r_int
r_int
id|tlb_entry_i_dat
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|tlb_entry_d_dat
r_int
r_int
id|tlb_entry_d_dat
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|tlb_entry_i
mdefine_line|#define tlb_entry_i tlb_entry_i_dat[smp_processor_id()]
DECL|macro|tlb_entry_d
mdefine_line|#define tlb_entry_d tlb_entry_d_dat[smp_processor_id()]
macro_line|#endif
r_extern
r_void
id|init_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Unlock any spinlocks which will prevent us from getting the&n; * message out&n; */
DECL|function|bust_spinlocks
r_void
id|bust_spinlocks
c_func
(paren
r_int
id|yes
)paren
(brace
r_int
id|loglevel_save
op_assign
id|console_loglevel
suffix:semicolon
r_if
c_cond
(paren
id|yes
)paren
(brace
id|oops_in_progress
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VT
id|unblank_screen
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|oops_in_progress
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * OK, the message is on the console.  Now we call printk()&n;&t; * without oops_in_progress set so that printk will give klogd&n;&t; * a poke.  Hold onto your hats...&n;&t; */
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* NMI oopser may have shut the console up */
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|loglevel_save
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * do_page_fault()&n; *======================================================================*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; *&n; * ARGUMENT:&n; *  regs       : M32R SP reg.&n; *  error_code : See below&n; *  address    : M32R MMU MDEVA reg. (Operand ACE)&n; *             : M32R BPC reg. (Instruction ACE)&n; *&n; * error_code :&n; *  bit 0 == 0 means no page found, 1 means protection fault&n; *  bit 1 == 0 means read, 1 means write&n; *  bit 2 == 0 means kernel, 1 means user-mode&n; *  bit 3 == 0 means data, 1 means instruction&n; *======================================================================*/
DECL|macro|ACE_PROTECTION
mdefine_line|#define ACE_PROTECTION&t;&t;1
DECL|macro|ACE_WRITE
mdefine_line|#define ACE_WRITE&t;&t;2
DECL|macro|ACE_USERMODE
mdefine_line|#define ACE_USERMODE&t;&t;4
DECL|macro|ACE_INSTRUCTION
mdefine_line|#define ACE_INSTRUCTION&t;&t;8
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
id|error_code
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
comma
id|addr
suffix:semicolon
r_int
id|write
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
multiline_comment|/*&n;&t; * If BPSW IE bit enable --&gt; set PSW IE bit&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;psw
op_amp
id|M32R_PSW_BIE
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
multiline_comment|/*&n;&t; * We fault-in kernel-space virtual memory on-demand. The&n;&t; * &squot;reference&squot; page table is init_mm.pgd.&n;&t; *&n;&t; * NOTE! We MUST NOT take any locks for this case. We may&n;&t; * be in an interrupt or a critical region, and should&n;&t; * only copy the information from the master page table,&n;&t; * nothing more.&n;&t; *&n;&t; * This verifies that the fault happens in kernel space&n;&t; * (error_code &amp; ACE_USERMODE) == 0, and that the fault was not a&n;&t; * protection error (error_code &amp; ACE_PROTECTION) == 0.&n;&t; */
r_if
c_cond
(paren
id|address
op_ge
id|TASK_SIZE
op_logical_and
op_logical_neg
(paren
id|error_code
op_amp
id|ACE_USERMODE
)paren
)paren
r_goto
id|vmalloc_fault
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or have no user context or are running in an&n;&t; * atomic region then we must not take the fault..&n;&t; */
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
(paren
id|error_code
op_amp
id|ACE_USERMODE
)paren
op_eq
l_int|0
op_logical_and
op_logical_neg
id|search_exception_tables
c_func
(paren
id|regs-&gt;psw
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
macro_line|#if 0
r_if
c_cond
(paren
id|error_code
op_amp
id|ACE_USERMODE
)paren
(brace
multiline_comment|/*&n;&t;&t; * accessing the stack below &quot;spu&quot; is always a bug.&n;&t;&t; * The &quot;+ 4&quot; is there due to the push instruction&n;&t;&t; * doing pre-decrement on the stack and that&n;&t;&t; * doesn&squot;t show up until later..&n;&t;&t; */
r_if
c_cond
(paren
id|address
op_plus
l_int|4
OL
id|regs-&gt;spu
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
macro_line|#endif
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
id|write
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|error_code
op_amp
(paren
id|ACE_WRITE
op_or
id|ACE_PROTECTION
)paren
)paren
(brace
r_default
suffix:colon
(brace
)brace
multiline_comment|/* 3: write, present */
multiline_comment|/* fall through */
r_case
id|ACE_WRITE
suffix:colon
multiline_comment|/* write, not present */
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
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACE_PROTECTION
suffix:colon
multiline_comment|/* read, present */
r_case
l_int|0
suffix:colon
multiline_comment|/* read, not present */
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
multiline_comment|/*&n;&t; * For instruction access exception, check if the area is executable&n;&t; */
r_if
c_cond
(paren
(paren
id|error_code
op_amp
id|ACE_INSTRUCTION
)paren
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
id|survive
suffix:colon
multiline_comment|/*&n;&t; * If for any reason at all we couldn&squot;t handle the fault,&n;&t; * make sure we exit gracefully rather than endlessly redo&n;&t; * the fault.&n;&t; */
id|addr
op_assign
(paren
id|address
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|set_thread_fault_code
c_func
(paren
id|error_code
)paren
suffix:semicolon
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
id|addr
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
id|set_thread_fault_code
c_func
(paren
l_int|0
)paren
suffix:semicolon
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
id|error_code
op_amp
id|ACE_USERMODE
)paren
(brace
id|tsk-&gt;thread.address
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|error_code
op_or
(paren
id|address
op_ge
id|TASK_SIZE
)paren
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
l_int|14
suffix:semicolon
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
l_string|&quot; printing bpc:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08lx&bslash;n&quot;
comma
id|regs-&gt;bpc
)paren
suffix:semicolon
id|page
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|MPTB
suffix:semicolon
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
id|PGDIR_SHIFT
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
id|error_code
op_amp
id|ACE_USERMODE
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
multiline_comment|/* Kernel mode? Handle exception or die */
r_if
c_cond
(paren
op_logical_neg
(paren
id|error_code
op_amp
id|ACE_USERMODE
)paren
)paren
r_goto
id|no_context
suffix:semicolon
id|tsk-&gt;thread.address
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
id|error_code
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
l_int|14
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
op_star
(paren
r_int
r_int
op_star
)paren
id|MPTB
suffix:semicolon
id|pgd
op_assign
id|offset
op_plus
(paren
id|pgd_t
op_star
)paren
id|pgd
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
multiline_comment|/*&n;&t;&t; * set_pgd(pgd, *pgd_k); here would be useless on PAE&n;&t;&t; * and redundant with the set_pmd() on non-PAE.&n;&t;&t; */
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
id|addr
op_assign
(paren
id|address
op_amp
id|PAGE_MASK
)paren
op_or
(paren
id|error_code
op_amp
id|ACE_INSTRUCTION
)paren
suffix:semicolon
id|update_mmu_cache
c_func
(paren
l_int|NULL
comma
id|addr
comma
op_star
id|pte_k
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*======================================================================*&n; * update_mmu_cache()&n; *======================================================================*/
DECL|macro|TLB_MASK
mdefine_line|#define TLB_MASK&t;(NR_TLB_ENTRIES - 1)
DECL|macro|ITLB_END
mdefine_line|#define ITLB_END&t;(unsigned long *)(ITLB_BASE + (NR_TLB_ENTRIES * 8))
DECL|macro|DTLB_END
mdefine_line|#define DTLB_END&t;(unsigned long *)(DTLB_BASE + (NR_TLB_ENTRIES * 8))
DECL|function|update_mmu_cache
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
op_star
id|entry1
comma
op_star
id|entry2
suffix:semicolon
r_int
r_int
id|pte_data
comma
id|flags
suffix:semicolon
r_int
r_int
op_star
id|entry_dat
suffix:semicolon
r_int
id|inst
op_assign
id|get_thread_fault_code
c_func
(paren
)paren
op_amp
id|ACE_INSTRUCTION
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Ptrace may call this routine. */
r_if
c_cond
(paren
id|vma
op_logical_and
id|current-&gt;active_mm
op_ne
id|vma-&gt;vm_mm
)paren
r_return
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
id|vaddr
op_amp
id|PAGE_MASK
)paren
op_or
id|get_asid
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CHIP_OPSP
id|entry1
op_assign
(paren
r_int
r_int
op_star
)paren
id|ITLB_BASE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_TLB_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|entry1
op_increment
op_eq
id|vaddr
)paren
(brace
id|pte_data
op_assign
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
id|set_tlb_data
c_func
(paren
id|entry1
comma
id|pte_data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|entry1
op_increment
suffix:semicolon
)brace
id|entry2
op_assign
(paren
r_int
r_int
op_star
)paren
id|DTLB_BASE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_TLB_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|entry2
op_increment
op_eq
id|vaddr
)paren
(brace
id|pte_data
op_assign
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
id|set_tlb_data
c_func
(paren
id|entry2
comma
id|pte_data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|entry2
op_increment
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#else
id|pte_data
op_assign
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Update TLB entries&n;&t; *  entry1: ITLB entry address&n;&t; *  entry2: DTLB entry address&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;seth&t;%0, #high(%4)&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%2, @(%5, %0)&t;&bslash;n&bslash;t&quot;
l_string|&quot;ldi&t;%1, #1&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%1, @(%6, %0)&t;&bslash;n&bslash;t&quot;
l_string|&quot;add3&t;r4, %0, %7&t;&bslash;n&bslash;t&quot;
l_string|&quot;.fillinsn&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%1, @(%6, %0)&t;&bslash;n&bslash;t&quot;
l_string|&quot;bnez&t;%1, 1b&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%0, @r4+&t;&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%1, @r4&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%3, @+%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;st&t;%3, @+%1&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|entry1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|entry2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|pte_data
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMU_REG_BASE
)paren
comma
l_string|&quot;i&quot;
(paren
id|MSVA_offset
)paren
comma
l_string|&quot;i&quot;
(paren
id|MTOP_offset
)paren
comma
l_string|&quot;i&quot;
(paren
id|MIDXI_offset
)paren
suffix:colon
l_string|&quot;r4&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|inst
op_logical_and
id|entry2
op_ge
id|DTLB_END
)paren
op_logical_or
(paren
id|inst
op_logical_and
id|entry1
op_ge
id|ITLB_END
)paren
)paren
r_goto
id|notfound
suffix:semicolon
id|found
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* Valid entry not found */
id|notfound
suffix:colon
multiline_comment|/*&n;&t; * Update ITLB or DTLB entry&n;&t; *  entry1: TLB entry address&n;&t; *  entry2: TLB base address&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|inst
)paren
(brace
id|entry2
op_assign
(paren
r_int
r_int
op_star
)paren
id|DTLB_BASE
suffix:semicolon
id|entry_dat
op_assign
op_amp
id|tlb_entry_d
suffix:semicolon
)brace
r_else
(brace
id|entry2
op_assign
(paren
r_int
r_int
op_star
)paren
id|ITLB_BASE
suffix:semicolon
id|entry_dat
op_assign
op_amp
id|tlb_entry_i
suffix:semicolon
)brace
id|entry1
op_assign
id|entry2
op_plus
(paren
(paren
(paren
op_star
id|entry_dat
op_minus
l_int|1
)paren
op_amp
id|TLB_MASK
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_TLB_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry1
(braket
l_int|1
)braket
op_amp
l_int|2
)paren
)paren
multiline_comment|/* Valid bit check */
r_break
suffix:semicolon
r_if
c_cond
(paren
id|entry1
op_ne
id|entry2
)paren
id|entry1
op_sub_assign
l_int|2
suffix:semicolon
r_else
id|entry1
op_add_assign
id|TLB_MASK
op_lshift
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|NR_TLB_ENTRIES
)paren
(brace
multiline_comment|/* Empty entry not found */
id|entry1
op_assign
id|entry2
op_plus
(paren
op_star
id|entry_dat
op_lshift
l_int|1
)paren
suffix:semicolon
op_star
id|entry_dat
op_assign
(paren
op_star
id|entry_dat
op_plus
l_int|1
)paren
op_amp
id|TLB_MASK
suffix:semicolon
)brace
op_star
id|entry1
op_increment
op_assign
id|vaddr
suffix:semicolon
multiline_comment|/* Set TLB tag */
id|set_tlb_data
c_func
(paren
id|entry1
comma
id|pte_data
)paren
suffix:semicolon
r_goto
id|found
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*======================================================================*&n; * flush_tlb_page() : flushes one page&n; *======================================================================*/
DECL|function|local_flush_tlb_page
r_void
id|local_flush_tlb_page
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
id|mm_context
c_func
(paren
id|vma-&gt;vm_mm
)paren
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
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|page
op_or_assign
(paren
id|mm_context
c_func
(paren
id|vma-&gt;vm_mm
)paren
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
id|__flush_tlb_page
c_func
(paren
id|page
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
multiline_comment|/*======================================================================*&n; * flush_tlb_range() : flushes a range of pages&n; *======================================================================*/
DECL|function|local_flush_tlb_range
r_void
id|local_flush_tlb_range
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
suffix:semicolon
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm_context
c_func
(paren
id|mm
)paren
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
id|NR_TLB_ENTRIES
op_div
l_int|4
)paren
)paren
(brace
multiline_comment|/* Too many TLB to flush */
id|mm_context
c_func
(paren
id|mm
)paren
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
suffix:semicolon
id|asid
op_assign
id|mm_context
c_func
(paren
id|mm
)paren
op_amp
id|MMU_CONTEXT_ASID_MASK
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
id|start
op_or_assign
id|asid
suffix:semicolon
id|end
op_or_assign
id|asid
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
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*======================================================================*&n; * flush_tlb_mm() : flushes the specified mm context TLB&squot;s&n; *======================================================================*/
DECL|function|local_flush_tlb_mm
r_void
id|local_flush_tlb_mm
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
id|mm_context
c_func
(paren
id|mm
)paren
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
id|mm_context
c_func
(paren
id|mm
)paren
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
multiline_comment|/*======================================================================*&n; * flush_tlb_all() : flushes all processes TLBs&n; *======================================================================*/
DECL|function|local_flush_tlb_all
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
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
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * init_mmu()&n; *======================================================================*/
DECL|function|init_mmu
r_void
id|__init
id|init_mmu
c_func
(paren
r_void
)paren
(brace
id|tlb_entry_i
op_assign
l_int|0
suffix:semicolon
id|tlb_entry_d
op_assign
l_int|0
suffix:semicolon
id|mmu_context_cache
op_assign
id|MMU_CONTEXT_FIRST_VERSION
suffix:semicolon
id|set_asid
c_func
(paren
id|mmu_context_cache
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|MPTB
op_assign
(paren
r_int
r_int
)paren
id|swapper_pg_dir
suffix:semicolon
)brace
eof
