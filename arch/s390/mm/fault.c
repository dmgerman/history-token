multiline_comment|/*&n; *  arch/s390/mm/fault.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *               Ulrich Weigand (uweigand@de.ibm.com)&n; *&n; *  Derived from &quot;arch/i386/mm/fault.c&quot;&n; *    Copyright (C) 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#ifndef CONFIG_ARCH_S390X
DECL|macro|__FAIL_ADDR_MASK
mdefine_line|#define __FAIL_ADDR_MASK 0x7ffff000
DECL|macro|__FIXUP_MASK
mdefine_line|#define __FIXUP_MASK 0x7fffffff
DECL|macro|__SUBCODE_MASK
mdefine_line|#define __SUBCODE_MASK 0x0200
DECL|macro|__PF_RES_FIELD
mdefine_line|#define __PF_RES_FIELD 0ULL
macro_line|#else /* CONFIG_ARCH_S390X */
DECL|macro|__FAIL_ADDR_MASK
mdefine_line|#define __FAIL_ADDR_MASK -4096L
DECL|macro|__FIXUP_MASK
mdefine_line|#define __FIXUP_MASK ~0L
DECL|macro|__SUBCODE_MASK
mdefine_line|#define __SUBCODE_MASK 0x0600
DECL|macro|__PF_RES_FIELD
mdefine_line|#define __PF_RES_FIELD 0x8000000000000000ULL
macro_line|#endif /* CONFIG_ARCH_S390X */
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_int
id|sysctl_userprocess_debug
suffix:semicolon
macro_line|#endif
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
r_extern
id|spinlock_t
id|timerlist_lock
suffix:semicolon
multiline_comment|/*&n; * Unlock any spinlocks which will prevent us from getting the&n; * message out (timerlist_lock is acquired through the&n; * console unblank code)&n; */
DECL|function|bust_spinlocks
r_void
id|bust_spinlocks
c_func
(paren
r_int
id|yes
)paren
(brace
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
)brace
r_else
(brace
r_int
id|loglevel_save
op_assign
id|console_loglevel
suffix:semicolon
id|oops_in_progress
op_assign
l_int|0
suffix:semicolon
id|console_unblank
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * OK, the message is on the console.  Now we call printk()&n;&t;&t; * without oops_in_progress set so that printk will give klogd&n;&t;&t; * a poke.  Hold onto your hats...&n;&t;&t; */
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
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
)brace
multiline_comment|/*&n; * Check which address space is addressed by the access&n; * register in S390_lowcore.exc_access_id.&n; * Returns 1 for user space and 0 for kernel space.&n; */
DECL|function|__check_access_register
r_static
r_int
id|__check_access_register
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_int
id|areg
op_assign
id|S390_lowcore.exc_access_id
suffix:semicolon
r_if
c_cond
(paren
id|areg
op_eq
l_int|0
)paren
multiline_comment|/* Access via access register 0 -&gt; kernel address */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|regs
op_logical_and
id|areg
OL
id|NUM_ACRS
op_logical_and
id|regs-&gt;acrs
(braket
id|areg
)braket
op_le
l_int|1
)paren
multiline_comment|/*&n;&t;&t; * access register contains 0 -&gt; kernel address,&n;&t;&t; * access register contains 1 -&gt; user space address&n;&t;&t; */
r_return
id|regs-&gt;acrs
(braket
id|areg
)braket
suffix:semicolon
multiline_comment|/* Something unhealthy was done with the access registers... */
id|die
c_func
(paren
l_string|&quot;page fault via unknown access register&quot;
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check which address space the address belongs to.&n; * Returns 1 for user space and 0 for kernel space.&n; */
DECL|function|check_user_space
r_static
r_inline
r_int
id|check_user_space
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
multiline_comment|/*&n;&t; * The lowest two bits of S390_lowcore.trans_exc_code indicate&n;&t; * which paging table was used:&n;&t; *   0: Primary Segment Table Descriptor&n;&t; *   1: STD determined via access register&n;&t; *   2: Secondary Segment Table Descriptor&n;&t; *   3: Home Segment Table Descriptor&n;&t; */
r_int
id|descriptor
op_assign
id|S390_lowcore.trans_exc_code
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|descriptor
op_eq
l_int|1
)paren
r_return
id|__check_access_register
c_func
(paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
r_return
id|descriptor
op_rshift
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Send SIGSEGV to task.  This is an external routine&n; * to keep the stack usage of do_page_fault small.&n; */
DECL|function|force_sigsegv
r_static
r_void
id|force_sigsegv
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
id|si_code
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|siginfo
id|si
suffix:semicolon
macro_line|#if defined(CONFIG_SYSCTL) || defined(CONFIG_PROCESS_DEBUG)
macro_line|#if defined(CONFIG_SYSCTL)
r_if
c_cond
(paren
id|sysctl_userprocess_debug
)paren
macro_line|#endif
(brace
id|printk
c_func
(paren
l_string|&quot;User process fault: interruption code 0x%lX&bslash;n&quot;
comma
id|error_code
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;failing address: %lX&bslash;n&quot;
comma
id|address
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
id|si.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|si.si_code
op_assign
id|si_code
suffix:semicolon
id|si.si_addr
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
id|si
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; *&n; * error_code:&n; *   04       Protection           -&gt;  Write-Protection  (suprression)&n; *   10       Segment translation  -&gt;  Not present       (nullification)&n; *   11       Page translation     -&gt;  Not present       (nullification)&n; *   3b       Region third trans.  -&gt;  Not present       (nullification)&n; */
DECL|function|do_exception
r_extern
r_inline
r_void
id|do_exception
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
id|address
suffix:semicolon
r_int
id|user_address
suffix:semicolon
r_const
r_struct
id|exception_table_entry
op_star
id|fixup
suffix:semicolon
r_int
id|si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
multiline_comment|/* &n;         * Check for low-address protection.  This needs to be treated&n;&t; * as a special case because the translation exception code &n;&t; * field is not guaranteed to contain valid data in this case.&n;&t; */
r_if
c_cond
(paren
id|error_code
op_eq
l_int|4
op_logical_and
op_logical_neg
(paren
id|S390_lowcore.trans_exc_code
op_amp
l_int|4
)paren
)paren
(brace
multiline_comment|/* Low-address protection hit in kernel mode means &n;&t;&t;   NULL pointer write access in kernel mode.  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
)paren
(brace
id|address
op_assign
l_int|0
suffix:semicolon
id|user_address
op_assign
l_int|0
suffix:semicolon
r_goto
id|no_context
suffix:semicolon
)brace
multiline_comment|/* Low-address protection hit in user mode &squot;cannot happen&squot;.  */
id|die
(paren
l_string|&quot;Low-address protection&quot;
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
multiline_comment|/* &n;         * get the failing address &n;         * more specific the segment and page table portion of &n;         * the address &n;         */
id|address
op_assign
id|S390_lowcore.trans_exc_code
op_amp
id|__FAIL_ADDR_MASK
suffix:semicolon
id|user_address
op_assign
id|check_user_space
c_func
(paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Verify that the fault happened in user space, that&n;&t; * we are not in an interrupt and that there is a &n;&t; * user context.&n;&t; */
r_if
c_cond
(paren
id|user_address
op_eq
l_int|0
op_logical_or
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
multiline_comment|/*&n;&t; * When we get here, the fault happened in the current&n;&t; * task&squot;s user address space, so we can switch on the&n;&t; * interrupts again and then search the VMAs&n;&t; */
id|local_irq_enable
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
id|si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
r_if
c_cond
(paren
id|error_code
op_ne
l_int|4
)paren
(brace
multiline_comment|/* page not present, check vm flags */
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
op_or
id|VM_WRITE
)paren
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
id|VM_WRITE
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
id|error_code
op_eq
l_int|4
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
multiline_comment|/* User mode accesses just cause a SIGSEGV */
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
(brace
id|tsk-&gt;thread.prot_addr
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
id|error_code
suffix:semicolon
id|force_sigsegv
c_func
(paren
id|regs
comma
id|error_code
comma
id|si_code
comma
id|address
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|no_context
suffix:colon
multiline_comment|/* Are we prepared to handle this kernel fault?  */
id|fixup
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;psw.addr
op_amp
id|__FIXUP_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixup
)paren
(brace
id|regs-&gt;psw.addr
op_assign
id|fixup-&gt;fixup
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n; * terminate things with extreme prejudice.&n; */
r_if
c_cond
(paren
id|user_address
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel pointer dereference&quot;
l_string|&quot; at virtual kernel address %p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|address
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel paging request&quot;
l_string|&quot; at virtual user address %p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
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
id|error_code
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
multiline_comment|/*&n; * We ran out of memory, or some other thing happened to us that made&n; * us unable to handle the page fault gracefully.&n;*/
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
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
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
id|tsk-&gt;thread.prot_addr
op_assign
id|address
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
id|error_code
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
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
)paren
r_goto
id|no_context
suffix:semicolon
)brace
DECL|function|do_protection_exception
r_void
id|do_protection_exception
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
)paren
(brace
id|regs-&gt;psw.addr
op_sub_assign
(paren
id|error_code
op_rshift
l_int|16
)paren
suffix:semicolon
id|do_exception
c_func
(paren
id|regs
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|do_segment_exception
r_void
id|do_segment_exception
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
)paren
(brace
id|do_exception
c_func
(paren
id|regs
comma
l_int|0x10
)paren
suffix:semicolon
)brace
DECL|function|do_page_exception
r_void
id|do_page_exception
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
)paren
(brace
id|do_exception
c_func
(paren
id|regs
comma
l_int|0x11
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_S390X
r_void
DECL|function|do_region_exception
id|do_region_exception
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
)paren
(brace
id|do_exception
c_func
(paren
id|regs
comma
l_int|0x3b
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_ARCH_S390X */
DECL|struct|_pseudo_wait_t
r_typedef
r_struct
id|_pseudo_wait_t
(brace
DECL|member|next
r_struct
id|_pseudo_wait_t
op_star
id|next
suffix:semicolon
DECL|member|queue
id|wait_queue_head_t
id|queue
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|resolved
r_int
id|resolved
suffix:semicolon
DECL|typedef|pseudo_wait_t
)brace
id|pseudo_wait_t
suffix:semicolon
DECL|variable|pseudo_lock_queue
r_static
id|pseudo_wait_t
op_star
id|pseudo_lock_queue
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pseudo_wait_spinlock
r_static
id|spinlock_t
id|pseudo_wait_spinlock
suffix:semicolon
multiline_comment|/* spinlock to protect lock queue */
multiline_comment|/*&n; * This routine handles &squot;pagex&squot; pseudo page faults.&n; */
id|asmlinkage
r_void
DECL|function|do_pseudo_page_fault
id|do_pseudo_page_fault
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
)paren
(brace
id|pseudo_wait_t
id|wait_struct
suffix:semicolon
id|pseudo_wait_t
op_star
id|ptr
comma
op_star
id|last
comma
op_star
id|next
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/*&n;         * get the failing address&n;         * more specific the segment and page table portion of&n;         * the address&n;         */
id|address
op_assign
id|S390_lowcore.trans_exc_code
op_amp
l_int|0xfffff000
suffix:semicolon
r_if
c_cond
(paren
id|address
op_amp
l_int|0x80000000
)paren
(brace
multiline_comment|/* high bit set -&gt; a page has been swapped in by VM */
id|address
op_and_assign
l_int|0x7fffffff
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pseudo_wait_spinlock
)paren
suffix:semicolon
id|last
op_assign
l_int|NULL
suffix:semicolon
id|ptr
op_assign
id|pseudo_lock_queue
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_ne
l_int|NULL
)paren
(brace
id|next
op_assign
id|ptr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|address
op_eq
id|ptr-&gt;address
)paren
(brace
multiline_comment|/*&n;                                 * This is one of the processes waiting&n;                                 * for the page. Unchain from the queue.&n;                                 * There can be more than one process&n;                                 * waiting for the same page. VM presents&n;                                 * an initial and a completion interrupt for&n;                                 * every process that tries to access a &n;                                 * page swapped out by VM. &n;                                 */
r_if
c_cond
(paren
id|last
op_eq
l_int|NULL
)paren
id|pseudo_lock_queue
op_assign
id|next
suffix:semicolon
r_else
id|last-&gt;next
op_assign
id|next
suffix:semicolon
multiline_comment|/* now wake up the process */
id|ptr-&gt;resolved
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ptr-&gt;queue
)paren
suffix:semicolon
)brace
r_else
id|last
op_assign
id|ptr
suffix:semicolon
id|ptr
op_assign
id|next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|pseudo_wait_spinlock
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Pseudo page faults in kernel mode is a bad idea */
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * VM presents pseudo page faults if the interrupted&n;&t;&t;&t; * state was not disabled for interrupts. So we can&n;&t;&t;&t; * get pseudo page fault interrupts while running&n;&t;&t;&t; * in kernel mode. We simply access the page here&n;&t;&t;&t; * while we are running disabled. VM will then swap&n;&t;&t;&t; * in the page synchronously.&n;                         */
r_if
c_cond
(paren
id|check_user_space
c_func
(paren
id|regs
comma
id|error_code
)paren
op_eq
l_int|0
)paren
multiline_comment|/* dereference a virtual kernel address */
id|__asm__
id|__volatile__
(paren
l_string|&quot;  ic 0,0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|address
)paren
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_else
multiline_comment|/* dereference a virtual user address */
id|__asm__
id|__volatile__
(paren
l_string|&quot;  la   2,0(%0)&bslash;n&quot;
l_string|&quot;  sacf 512&bslash;n&quot;
l_string|&quot;  ic   2,0(2)&bslash;n&quot;
l_string|&quot;0:sacf 0&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;  .align 4&bslash;n&quot;
l_string|&quot;  .long  0b,0b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|address
)paren
suffix:colon
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* initialize and add element to pseudo_lock_queue */
id|init_waitqueue_head
(paren
op_amp
id|wait_struct.queue
)paren
suffix:semicolon
id|wait_struct.address
op_assign
id|address
suffix:semicolon
id|wait_struct.resolved
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pseudo_wait_spinlock
)paren
suffix:semicolon
id|wait_struct.next
op_assign
id|pseudo_lock_queue
suffix:semicolon
id|pseudo_lock_queue
op_assign
op_amp
id|wait_struct
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pseudo_wait_spinlock
)paren
suffix:semicolon
multiline_comment|/* go to sleep */
id|wait_event
c_func
(paren
id|wait_struct.queue
comma
id|wait_struct.resolved
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
macro_line|#ifdef CONFIG_PFAULT 
multiline_comment|/*&n; * &squot;pfault&squot; pseudo page faults routines.&n; */
DECL|variable|pfault_disable
r_static
r_int
id|pfault_disable
op_assign
l_int|0
suffix:semicolon
DECL|function|nopfault
r_static
r_int
id|__init
id|nopfault
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|pfault_disable
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nopfault&quot;
comma
id|nopfault
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|refdiagc
id|__u16
id|refdiagc
suffix:semicolon
DECL|member|reffcode
id|__u16
id|reffcode
suffix:semicolon
DECL|member|refdwlen
id|__u16
id|refdwlen
suffix:semicolon
DECL|member|refversn
id|__u16
id|refversn
suffix:semicolon
DECL|member|refgaddr
id|__u64
id|refgaddr
suffix:semicolon
DECL|member|refselmk
id|__u64
id|refselmk
suffix:semicolon
DECL|member|refcmpmk
id|__u64
id|refcmpmk
suffix:semicolon
DECL|member|reserved
id|__u64
id|reserved
suffix:semicolon
DECL|typedef|pfault_refbk_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|pfault_refbk_t
suffix:semicolon
DECL|function|pfault_init
r_int
id|pfault_init
c_func
(paren
r_void
)paren
(brace
id|pfault_refbk_t
id|refbk
op_assign
(brace
l_int|0x258
comma
l_int|0
comma
l_int|5
comma
l_int|2
comma
id|__LC_CURRENT
comma
l_int|1ULL
op_lshift
l_int|48
comma
l_int|1ULL
op_lshift
l_int|48
comma
id|__PF_RES_FIELD
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|pfault_disable
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    diag  %1,%0,0x258&bslash;n&quot;
l_string|&quot;0:  j     2f&bslash;n&quot;
l_string|&quot;1:  la    %0,8&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
macro_line|#ifndef CONFIG_ARCH_S390X
l_string|&quot;   .long  0b,1b&bslash;n&quot;
macro_line|#else /* CONFIG_ARCH_S390X */
l_string|&quot;   .quad  0b,1b&bslash;n&quot;
macro_line|#endif /* CONFIG_ARCH_S390X */
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|rc
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|refbk
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|__ctl_set_bit
c_func
(paren
l_int|0
comma
l_int|9
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|pfault_fini
r_void
id|pfault_fini
c_func
(paren
r_void
)paren
(brace
id|pfault_refbk_t
id|refbk
op_assign
(brace
l_int|0x258
comma
l_int|1
comma
l_int|5
comma
l_int|2
comma
l_int|0ULL
comma
l_int|0ULL
comma
l_int|0ULL
comma
l_int|0ULL
)brace
suffix:semicolon
r_if
c_cond
(paren
id|pfault_disable
)paren
r_return
suffix:semicolon
id|__ctl_clear_bit
c_func
(paren
l_int|0
comma
l_int|9
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    diag  %0,0,0x258&bslash;n&quot;
l_string|&quot;0:&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
macro_line|#ifndef CONFIG_ARCH_S390X
l_string|&quot;   .long  0b,0b&bslash;n&quot;
macro_line|#else /* CONFIG_ARCH_S390X */
l_string|&quot;   .quad  0b,0b&bslash;n&quot;
macro_line|#endif /* CONFIG_ARCH_S390X */
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|refbk
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|pfault_interrupt
id|pfault_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u16
id|error_code
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
id|__u16
id|subcode
suffix:semicolon
multiline_comment|/*&n;&t; * Get the external interruption subcode &amp; pfault&n;&t; * initial/completion signal bit. VM stores this &n;&t; * in the &squot;cpu address&squot; field associated with the&n;         * external interrupt. &n;&t; */
id|subcode
op_assign
id|S390_lowcore.cpu_addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|subcode
op_amp
l_int|0xff00
)paren
op_ne
id|__SUBCODE_MASK
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Get the token (= address of the task structure of the affected task).&n;&t; */
id|tsk
op_assign
op_star
(paren
r_struct
id|task_struct
op_star
op_star
)paren
id|__LC_PFAULT_INTPARM
suffix:semicolon
r_if
c_cond
(paren
id|subcode
op_amp
l_int|0x0080
)paren
(brace
multiline_comment|/* signal bit is set -&gt; a page has been swapped in by VM */
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|tsk-&gt;thread.pfault_wait
comma
op_minus
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Initial interrupt was faster than the completion&n;&t;&t;&t; * interrupt. pfault_wait is valid. Set pfault_wait&n;&t;&t;&t; * back to zero and wake up the process. This can&n;&t;&t;&t; * safely be done because the task is still sleeping&n;&t;&t;&t; * and can&squot;t procude new pfaults. */
id|tsk-&gt;thread.pfault_wait
op_assign
l_int|0
suffix:semicolon
id|wake_up_process
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* signal bit not set -&gt; a real page is missing. */
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|tsk-&gt;thread.pfault_wait
comma
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Completion interrupt was faster than the initial&n;&t;&t;&t; * interrupt (swapped in a -1 for pfault_wait). Set&n;&t;&t;&t; * pfault_wait back to zero and exit. This can be&n;&t;&t;&t; * done safely because tsk is running in kernel &n;&t;&t;&t; * mode and can&squot;t produce new pfaults. */
id|tsk-&gt;thread.pfault_wait
op_assign
l_int|0
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_RUNNING
)paren
suffix:semicolon
)brace
r_else
id|set_tsk_need_resched
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
