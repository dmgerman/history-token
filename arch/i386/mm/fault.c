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
macro_line|#include &lt;linux/highmem.h&gt;
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
multiline_comment|/*&n; * Return EIP plus the CS segment base.  The segment limit is also&n; * adjusted, clamped to the kernel/user address space (whichever is&n; * appropriate), and returned in *eip_limit.&n; *&n; * The segment is checked, because it might have been changed by another&n; * task between the original faulting instruction and here.&n; *&n; * If CS is no longer a valid code segment, or if EIP is beyond the&n; * limit, or if it is a kernel address when CS is not a kernel segment,&n; * then the returned value will be greater than *eip_limit.&n; * &n; * This is slow, but is very rarely executed.&n; */
DECL|function|get_segment_eip
r_static
r_inline
r_int
r_int
id|get_segment_eip
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
op_star
id|eip_limit
)paren
(brace
r_int
r_int
id|eip
op_assign
id|regs-&gt;eip
suffix:semicolon
r_int
id|seg
op_assign
id|regs-&gt;xcs
op_amp
l_int|0xffff
suffix:semicolon
id|u32
id|seg_ar
comma
id|seg_limit
comma
id|base
comma
op_star
id|desc
suffix:semicolon
multiline_comment|/* The standard kernel/user address space limit. */
op_star
id|eip_limit
op_assign
(paren
id|seg
op_amp
l_int|3
)paren
ques
c_cond
id|USER_DS.seg
suffix:colon
id|KERNEL_DS.seg
suffix:semicolon
multiline_comment|/* Unlikely, but must come before segment checks. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|regs-&gt;eflags
op_amp
id|VM_MASK
)paren
op_ne
l_int|0
)paren
)paren
r_return
id|eip
op_plus
(paren
id|seg
op_lshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* By far the most common cases. */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|seg
op_eq
id|__USER_CS
op_logical_or
id|seg
op_eq
id|__KERNEL_CS
)paren
)paren
r_return
id|eip
suffix:semicolon
multiline_comment|/* Check the segment exists, is within the current LDT/GDT size,&n;&t;   that kernel/user (ring 0..3) has the appropriate privilege,&n;&t;   that it&squot;s a code segment, and get the limit. */
id|__asm__
(paren
l_string|&quot;larl %3,%0; lsll %3,%1&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|seg_ar
)paren
comma
l_string|&quot;=r&quot;
(paren
id|seg_limit
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;rm&quot;
(paren
id|seg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_complement
id|seg_ar
op_amp
l_int|0x9800
)paren
op_logical_or
id|eip
OG
id|seg_limit
)paren
(brace
op_star
id|eip_limit
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* So that returned eip &gt; *eip_limit. */
)brace
multiline_comment|/* Get the GDT/LDT descriptor base. &n;&t;   When you look for races in this code remember that&n;&t;   LDT and other horrors are only used in user space. */
r_if
c_cond
(paren
id|seg
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
(brace
multiline_comment|/* Must lock the LDT while reading it. */
id|down
c_func
(paren
op_amp
id|current-&gt;mm-&gt;context.sem
)paren
suffix:semicolon
id|desc
op_assign
id|current-&gt;mm-&gt;context.ldt
suffix:semicolon
id|desc
op_assign
(paren
r_void
op_star
)paren
id|desc
op_plus
(paren
id|seg
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Must disable preemption while reading the GDT. */
id|desc
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|cpu_gdt_table
(braket
id|get_cpu
c_func
(paren
)paren
)braket
suffix:semicolon
id|desc
op_assign
(paren
r_void
op_star
)paren
id|desc
op_plus
(paren
id|seg
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
)brace
multiline_comment|/* Decode the code segment base from the descriptor */
id|base
op_assign
(paren
id|desc
(braket
l_int|0
)braket
op_rshift
l_int|16
)paren
op_or
(paren
(paren
id|desc
(braket
l_int|1
)braket
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|desc
(braket
l_int|1
)braket
op_amp
l_int|0xff000000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;context.sem
)paren
suffix:semicolon
)brace
r_else
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Adjust EIP and segment limit, and clamp at the kernel limit.&n;&t;   It&squot;s legitimate for segments to wrap at 0xffffffff. */
id|seg_limit
op_add_assign
id|base
suffix:semicolon
r_if
c_cond
(paren
id|seg_limit
OL
op_star
id|eip_limit
op_logical_and
id|seg_limit
op_ge
id|base
)paren
op_star
id|eip_limit
op_assign
id|seg_limit
suffix:semicolon
r_return
id|eip
op_plus
id|base
suffix:semicolon
)brace
multiline_comment|/* &n; * Sometimes AMD Athlon/Opteron CPUs report invalid exceptions on prefetch.&n; * Check that here and ignore it.&n; */
DECL|function|__is_prefetch
r_static
r_int
id|__is_prefetch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|limit
suffix:semicolon
r_int
r_int
id|instr
op_assign
id|get_segment_eip
(paren
id|regs
comma
op_amp
id|limit
)paren
suffix:semicolon
r_int
id|scan_more
op_assign
l_int|1
suffix:semicolon
r_int
id|prefetch
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|scan_more
op_logical_and
id|i
OL
l_int|15
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|opcode
suffix:semicolon
r_int
r_char
id|instr_hi
suffix:semicolon
r_int
r_char
id|instr_lo
suffix:semicolon
r_if
c_cond
(paren
id|instr
OG
id|limit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|opcode
comma
(paren
r_int
r_char
op_star
)paren
id|instr
)paren
)paren
r_break
suffix:semicolon
id|instr_hi
op_assign
id|opcode
op_amp
l_int|0xf0
suffix:semicolon
id|instr_lo
op_assign
id|opcode
op_amp
l_int|0x0f
suffix:semicolon
id|instr
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|instr_hi
)paren
(brace
r_case
l_int|0x20
suffix:colon
r_case
l_int|0x30
suffix:colon
multiline_comment|/* Values 0x26,0x2E,0x36,0x3E are valid x86 prefixes. */
id|scan_more
op_assign
(paren
(paren
id|instr_lo
op_amp
l_int|7
)paren
op_eq
l_int|0x6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x60
suffix:colon
multiline_comment|/* 0x64 thru 0x67 are valid prefixes in all modes. */
id|scan_more
op_assign
(paren
id|instr_lo
op_amp
l_int|0xC
)paren
op_eq
l_int|0x4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xF0
suffix:colon
multiline_comment|/* 0xF0, 0xF2, and 0xF3 are valid prefixes */
id|scan_more
op_assign
op_logical_neg
id|instr_lo
op_logical_or
(paren
id|instr_lo
op_rshift
l_int|1
)paren
op_eq
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00
suffix:colon
multiline_comment|/* Prefetch instruction is 0x0F0D or 0x0F18 */
id|scan_more
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|instr
OG
id|limit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|opcode
comma
(paren
r_int
r_char
op_star
)paren
id|instr
)paren
)paren
r_break
suffix:semicolon
id|prefetch
op_assign
(paren
id|instr_lo
op_eq
l_int|0xF
)paren
op_logical_and
(paren
id|opcode
op_eq
l_int|0x0D
op_logical_or
id|opcode
op_eq
l_int|0x18
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|scan_more
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|prefetch
suffix:semicolon
)brace
DECL|function|is_prefetch
r_static
r_inline
r_int
id|is_prefetch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_AMD
op_logical_and
id|boot_cpu_data.x86
op_ge
l_int|6
)paren
)paren
r_return
id|__is_prefetch
c_func
(paren
id|regs
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|0
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
(paren
id|X86_EFLAGS_IF
op_or
id|VM_MASK
)paren
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
multiline_comment|/*&n;&t; * We fault-in kernel-space virtual memory on-demand. The&n;&t; * &squot;reference&squot; page table is init_mm.pgd.&n;&t; *&n;&t; * NOTE! We MUST NOT take any locks for this case. We may&n;&t; * be in an interrupt or a critical region, and should&n;&t; * only copy the information from the master page table,&n;&t; * nothing more.&n;&t; *&n;&t; * This verifies that the fault happens in kernel space&n;&t; * (error_code &amp; 4) == 0, and that the fault was not a&n;&t; * protection error (error_code &amp; 1) == 0.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|address
op_ge
id|TASK_SIZE
)paren
)paren
(brace
r_if
c_cond
(paren
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
multiline_comment|/* &n;&t;&t; * Don&squot;t take the mm semaphore here. If we fixup a prefetch&n;&t;&t; * fault we could otherwise deadlock.&n;&t;&t; */
r_goto
id|bad_area_nosemaphore
suffix:semicolon
)brace
id|mm
op_assign
id|tsk-&gt;mm
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
id|bad_area_nosemaphore
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
id|bad_area_nosemaphore
suffix:colon
multiline_comment|/* User mode accesses just cause a SIGSEGV */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|4
)paren
(brace
multiline_comment|/* &n;&t;&t; * Valid to do another page fault here because this one came &n;&t;&t; * from user space.&n;&t;&t; */
r_if
c_cond
(paren
id|is_prefetch
c_func
(paren
id|regs
comma
id|address
)paren
)paren
r_return
suffix:semicolon
id|tsk-&gt;thread.cr2
op_assign
id|address
suffix:semicolon
multiline_comment|/* Kernel addresses are always protection faults */
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
multiline_comment|/* &n;&t; * Valid to do another page fault here, because if this fault&n;&t; * had been triggered by is_prefetch fixup_exception would have &n;&t; * handled it.&n;&t; */
r_if
c_cond
(paren
id|is_prefetch
c_func
(paren
id|regs
comma
id|address
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
multiline_comment|/* User space =&gt; ok to do another page fault */
r_if
c_cond
(paren
id|is_prefetch
c_func
(paren
id|regs
comma
id|address
)paren
)paren
r_return
suffix:semicolon
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
r_return
suffix:semicolon
id|vmalloc_fault
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * Synchronize this task&squot;s top level page-table&n;&t;&t; * with the &squot;reference&squot; page table.&n;&t;&t; *&n;&t;&t; * Do _not_ use &quot;tsk&quot; here. We might be inside&n;&t;&t; * an interrupt in the middle of a task switch..&n;&t;&t; */
r_int
id|index
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
id|index
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
r_return
suffix:semicolon
)brace
)brace
eof
