multiline_comment|/*&n; *  linux/arch/i386/mm/fault.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
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
macro_line|#ifndef CONFIG_X86_WP_WORKS_OK
multiline_comment|/*&n; * Ugly, ugly, but the goto&squot;s result in better assembly..&n; */
DECL|function|__verify_write
r_int
id|__verify_write
c_func
(paren
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|start
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|segment_eq
c_func
(paren
id|get_fs
c_func
(paren
)paren
comma
id|KERNEL_DS
)paren
)paren
r_return
l_int|1
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
id|current-&gt;mm
comma
id|start
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
OG
id|start
)paren
r_goto
id|check_stack
suffix:semicolon
id|good_area
suffix:colon
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
id|size
op_decrement
suffix:semicolon
id|size
op_add_assign
id|start
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|size
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|survive
suffix:colon
r_switch
c_cond
(paren
id|handle_mm_fault
c_func
(paren
id|current-&gt;mm
comma
id|vma
comma
id|start
comma
l_int|1
)paren
)paren
(brace
r_case
id|VM_FAULT_SIGBUS
suffix:colon
r_goto
id|bad_area
suffix:semicolon
r_case
id|VM_FAULT_OOM
suffix:colon
r_goto
id|out_of_memory
suffix:semicolon
r_case
id|VM_FAULT_MINOR
suffix:colon
r_case
id|VM_FAULT_MAJOR
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_break
suffix:semicolon
id|size
op_decrement
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|vma-&gt;vm_end
)paren
r_continue
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|vma-&gt;vm_start
op_ne
id|start
)paren
r_goto
id|bad_area
suffix:semicolon
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
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We really need to hold mmap_sem over the whole access to&n;&t; * userspace, else another thread could change permissions.&n;&t; * This is unfixable, so don&squot;t use i386-class machines for&n;&t; * critical servers.&n;&t; */
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|check_stack
suffix:colon
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
id|start
)paren
op_eq
l_int|0
)paren
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
r_return
l_int|0
suffix:semicolon
id|out_of_memory
suffix:colon
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
r_goto
id|survive
suffix:semicolon
)brace
r_goto
id|bad_area
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Unlock any spinlocks which will prevent us from getting the&n; * message out &n; */
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
id|asmlinkage
r_void
id|do_invalid_op
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; *&n; * error_code:&n; *&t;bit 0 == 0 means no page found, 1 means protection fault&n; *&t;bit 1 == 0 means read, 1 means write&n; *&t;bit 2 == 0 means kernel, 1 means user-mode&n; */
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
r_int
id|page
suffix:semicolon
r_int
id|write
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
multiline_comment|/* get the address */
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr2,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|address
)paren
)paren
suffix:semicolon
multiline_comment|/* It&squot;s safe to allow irq&squot;s after cr2 has been saved */
r_if
c_cond
(paren
id|regs-&gt;eflags
op_amp
id|X86_EFLAGS_IF
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
multiline_comment|/*&n;&t; * We fault-in kernel-space virtual memory on-demand. The&n;&t; * &squot;reference&squot; page table is init_mm.pgd.&n;&t; *&n;&t; * NOTE! We MUST NOT take any locks for this case. We may&n;&t; * be in an interrupt or a critical region, and should&n;&t; * only copy the information from the master page table,&n;&t; * nothing more.&n;&t; *&n;&t; * This verifies that the fault happens in kernel space&n;&t; * (error_code &amp; 4) == 0, and that the fault was not a&n;&t; * protection error (error_code &amp; 1) == 0.&n;&t; */
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
l_int|5
)paren
)paren
r_goto
id|vmalloc_fault
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt, have no user context or are running in an&n;&t; * atomic region then we must not take the fault..&n;&t; */
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
id|error_code
op_amp
l_int|4
)paren
(brace
multiline_comment|/*&n;&t;&t; * accessing the stack below %esp is always a bug.&n;&t;&t; * The &quot;+ 32&quot; is there due to some instructions (like&n;&t;&t; * pusha) doing post-decrement on the stack and that&n;&t;&t; * doesn&squot;t show up until later..&n;&t;&t; */
r_if
c_cond
(paren
id|address
op_plus
l_int|32
OL
id|regs-&gt;esp
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
l_int|3
)paren
(brace
r_default
suffix:colon
(brace
)brace
multiline_comment|/* 3: write, present */
macro_line|#ifdef TEST_VERIFY_AREA
r_if
c_cond
(paren
id|regs-&gt;cs
op_eq
id|KERNEL_CS
)paren
id|printk
c_func
(paren
l_string|&quot;WP fault at %08lx&bslash;n&quot;
comma
id|regs-&gt;eip
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* fall through */
r_case
l_int|2
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
l_int|1
suffix:colon
multiline_comment|/* read, present */
r_goto
id|bad_area
suffix:semicolon
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
multiline_comment|/*&n;&t; * Did it hit the DOS screen memory VA from vm86 mode?&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;eflags
op_amp
id|VM_MASK
)paren
(brace
r_int
r_int
id|bit
op_assign
(paren
id|address
op_minus
l_int|0xA0000
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
l_int|32
)paren
id|tsk-&gt;thread.screen_bitmap
op_or_assign
l_int|1
op_lshift
id|bit
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
id|error_code
op_amp
l_int|4
)paren
(brace
id|tsk-&gt;thread.cr2
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
macro_line|#ifdef CONFIG_X86_F00F_BUG
multiline_comment|/*&n;&t; * Pentium F0 0F C7 C8 bug workaround.&n;&t; */
r_if
c_cond
(paren
id|boot_cpu_data.f00f_bug
)paren
(brace
r_int
r_int
id|nr
suffix:semicolon
id|nr
op_assign
(paren
id|address
op_minus
id|idt_descr.address
)paren
op_rshift
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_eq
l_int|6
)paren
(brace
id|do_invalid_op
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
macro_line|#endif
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
l_string|&quot; printing eip:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08lx&bslash;n&quot;
comma
id|regs-&gt;eip
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%cr3,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|page
)paren
)paren
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
multiline_comment|/*&n;&t; * We must not directly access the pte in the highpte&n;&t; * case, the page table might be allocated in highmem.&n;&t; * And lets rather not kmap-atomic the pte, just in case&n;&t; * it&squot;s allocated already.&n;&t; */
macro_line|#ifndef CONFIG_HIGHPTE
r_if
c_cond
(paren
id|page
op_amp
l_int|1
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
macro_line|#endif
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
l_int|4
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
id|tsk-&gt;thread.cr2
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
(paren
id|error_code
op_amp
l_int|4
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
id|asm
c_func
(paren
l_string|&quot;movl %%cr3,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pgd
)paren
)paren
suffix:semicolon
id|pgd
op_assign
id|offset
op_plus
(paren
id|pgd_t
op_star
)paren
id|__va
c_func
(paren
id|pgd
)paren
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
