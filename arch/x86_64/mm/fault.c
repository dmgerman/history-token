multiline_comment|/*&n; *  linux/arch/x86-64/mm/fault.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 2001,2002 Andi Kleen, SuSE Labs.&n; */
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
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm-generic/sections.h&gt;
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
)brace
r_else
(brace
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
multiline_comment|/*&n;&t;&t; * OK, the message is on the console.  Now we call printk()&n;&t;&t; * without oops_in_progress set so that printk will give klogd&n;&t;&t; * a poke.  Hold onto your hats...&n;&t;&t; */
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
)brace
multiline_comment|/* Sometimes the CPU reports invalid exceptions on prefetch.&n;   Check that here and ignore.&n;   Opcode checker based on code by Richard Brunner */
DECL|function|is_prefetch
r_static
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
r_int
r_char
op_star
id|instr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|regs-&gt;rip
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
r_char
op_star
id|max_instr
op_assign
id|instr
op_plus
l_int|15
suffix:semicolon
multiline_comment|/* Avoid recursive faults for this common case */
r_if
c_cond
(paren
id|regs-&gt;rip
op_eq
id|addr
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Code segments in LDT could have a non zero base. Don&squot;t check&n;&t;   when that&squot;s possible */
r_if
c_cond
(paren
id|regs-&gt;cs
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|regs-&gt;cs
op_amp
l_int|3
)paren
op_ne
l_int|0
op_logical_and
id|regs-&gt;rip
op_ge
id|TASK_SIZE
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|scan_more
op_logical_and
id|instr
OL
id|max_instr
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
id|__get_user
c_func
(paren
id|opcode
comma
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
multiline_comment|/* Values 0x26,0x2E,0x36,0x3E are valid x86&n;&t;&t;&t;   prefixes.  In long mode, the CPU will signal&n;&t;&t;&t;   invalid opcode if some of these prefixes are&n;&t;&t;&t;   present so we will never get here anyway */
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
l_int|0x40
suffix:colon
multiline_comment|/* In AMD64 long mode, 0x40 to 0x4F are valid REX prefixes&n;&t;&t;&t;   Need to figure out under what instruction mode the&n;&t;&t;&t;   instruction was issued ... */
multiline_comment|/* Could check the LDT for lm, but for now it&squot;s good&n;&t;&t;&t;   enough to assume that long mode only uses well known&n;&t;&t;&t;   segments or kernel. */
id|scan_more
op_assign
(paren
(paren
id|regs-&gt;cs
op_amp
l_int|3
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|regs-&gt;cs
op_eq
id|__USER_CS
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
multiline_comment|/* 0xF0, 0xF2, and 0xF3 are valid prefixes in all modes. */
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
id|__get_user
c_func
(paren
id|opcode
comma
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
DECL|function|bad_address
r_static
r_int
id|bad_address
c_func
(paren
r_void
op_star
id|p
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_return
id|__get_user
c_func
(paren
id|dummy
comma
(paren
r_int
r_int
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|dump_pagetable
r_void
id|dump_pagetable
c_func
(paren
r_int
r_int
id|address
)paren
(brace
id|pml4_t
op_star
id|pml4
suffix:semicolon
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
id|pte
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr3,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pml4
)paren
)paren
suffix:semicolon
id|pml4
op_assign
id|__va
c_func
(paren
(paren
r_int
r_int
)paren
id|pml4
op_amp
id|PHYSICAL_PAGE_MASK
)paren
suffix:semicolon
id|pml4
op_add_assign
id|pml4_index
c_func
(paren
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PML4 %lx &quot;
comma
id|pml4_val
c_func
(paren
op_star
id|pml4
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_address
c_func
(paren
id|pml4
)paren
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pml4_present
c_func
(paren
op_star
id|pml4
)paren
)paren
r_goto
id|ret
suffix:semicolon
id|pgd
op_assign
id|__pgd_offset_k
c_func
(paren
(paren
id|pgd_t
op_star
)paren
id|pml4_page
c_func
(paren
op_star
id|pml4
)paren
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_address
c_func
(paren
id|pgd
)paren
)paren
r_goto
id|bad
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PGD %lx &quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
)paren
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
r_goto
id|ret
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
id|bad_address
c_func
(paren
id|pmd
)paren
)paren
r_goto
id|bad
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PMD %lx &quot;
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
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|ret
suffix:semicolon
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
r_if
c_cond
(paren
id|bad_address
c_func
(paren
id|pte
)paren
)paren
r_goto
id|bad
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PTE %lx&quot;
comma
id|pte_val
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
id|ret
suffix:colon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bad
suffix:colon
id|printk
c_func
(paren
l_string|&quot;BAD&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|errata93_warning
r_static
r_const
r_char
id|errata93_warning
(braket
)braket
op_assign
id|KERN_ERR
l_string|&quot;******* Your BIOS seems to not contain a fix for K8 errata #93&bslash;n&quot;
id|KERN_ERR
l_string|&quot;******* Working around it, but it may cause SEGVs or burn power.&bslash;n&quot;
id|KERN_ERR
l_string|&quot;******* Please consider a BIOS update.&bslash;n&quot;
id|KERN_ERR
l_string|&quot;******* Disabling USB legacy in the BIOS may also help.&bslash;n&quot;
suffix:semicolon
multiline_comment|/* Workaround for K8 erratum #93 &amp; buggy BIOS.&n;   BIOS SMM functions are required to use a specific workaround&n;   to avoid corruption of the 64bit RIP register on C stepping K8. &n;   A lot of BIOS that didn&squot;t get tested properly miss this. &n;   The OS sees this as a page fault with the upper 32bits of RIP cleared.&n;   Try to work around it here.&n;   Note we only handle faults in kernel here. */
DECL|function|is_errata93
r_static
r_int
id|is_errata93
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|address
)paren
(brace
r_static
r_int
id|warned
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ne
id|regs-&gt;rip
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|address
op_rshift
l_int|32
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|address
op_or_assign
l_int|0xffffffffUL
op_lshift
l_int|32
suffix:semicolon
r_if
c_cond
(paren
(paren
id|address
op_ge
(paren
id|u64
)paren
id|_stext
op_logical_and
id|address
op_le
(paren
id|u64
)paren
id|_etext
)paren
op_logical_or
(paren
id|address
op_ge
id|MODULES_VADDR
op_logical_and
id|address
op_le
id|MODULES_END
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|warned
)paren
(brace
id|printk
c_func
(paren
id|errata93_warning
)paren
suffix:semicolon
id|warned
op_assign
l_int|1
suffix:semicolon
)brace
id|regs-&gt;rip
op_assign
id|address
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unhandled_signal
r_int
id|unhandled_signal
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|sig
)paren
(brace
multiline_comment|/* Warn for strace, but not for gdb */
r_if
c_cond
(paren
op_logical_neg
id|test_ti_thread_flag
c_func
(paren
id|tsk-&gt;thread_info
comma
id|TIF_SYSCALL_TRACE
)paren
op_logical_and
(paren
id|tsk-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|tsk-&gt;sighand-&gt;action
(braket
id|sig
op_minus
l_int|1
)braket
dot
id|sa.sa_handler
op_eq
id|SIG_IGN
)paren
op_logical_or
(paren
id|tsk-&gt;sighand-&gt;action
(braket
id|sig
op_minus
l_int|1
)braket
dot
id|sa.sa_handler
op_eq
id|SIG_DFL
)paren
suffix:semicolon
)brace
DECL|variable|page_fault_trace
r_int
id|page_fault_trace
suffix:semicolon
DECL|variable|exception_trace
r_int
id|exception_trace
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; *&n; * error_code:&n; *&t;bit 0 == 0 means no page found, 1 means protection fault&n; *&t;bit 1 == 0 means read, 1 means write&n; *&t;bit 2 == 0 means kernel, 1 means user-mode&n; *      bit 3 == 1 means fault was an instruction fetch&n; */
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
r_const
r_struct
id|exception_table_entry
op_star
id|fixup
suffix:semicolon
r_int
id|write
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_CHECKING
(brace
r_int
r_int
id|gs
suffix:semicolon
r_struct
id|x8664_pda
op_star
id|pda
op_assign
id|cpu_pda
op_plus
id|stack_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_GS_BASE
comma
id|gs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gs
op_ne
(paren
r_int
r_int
)paren
id|pda
)paren
(brace
id|wrmsrl
c_func
(paren
id|MSR_GS_BASE
comma
id|pda
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;page_fault: wrong gs %lx expected %p&bslash;n&quot;
comma
id|gs
comma
id|pda
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* get the address */
id|__asm__
c_func
(paren
l_string|&quot;movq %%cr2,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|address
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|regs-&gt;eflags
op_amp
id|X86_EFLAGS_IF
)paren
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|page_fault_trace
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;pagefault rip:%lx rsp:%lx cs:%lu ss:%lu address %lx error %lx&bslash;n&quot;
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|regs-&gt;cs
comma
id|regs-&gt;ss
comma
id|address
comma
id|error_code
)paren
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
multiline_comment|/* 5 =&gt; page not present and from supervisor mode */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
(paren
id|error_code
op_amp
l_int|5
)paren
op_logical_and
(paren
(paren
id|address
op_ge
id|VMALLOC_START
op_logical_and
id|address
op_le
id|VMALLOC_END
)paren
op_logical_or
(paren
id|address
op_ge
id|MODULES_VADDR
op_logical_and
id|address
op_le
id|MODULES_END
)paren
)paren
)paren
)paren
r_goto
id|vmalloc_fault
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in an interrupt or have no user&n;&t; * context, we must not take the fault..&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_atomic
c_func
(paren
)paren
op_logical_or
op_logical_neg
id|mm
)paren
)paren
r_goto
id|bad_area_nosemaphore
suffix:semicolon
id|again
suffix:colon
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
id|likely
c_func
(paren
id|vma-&gt;vm_start
op_le
id|address
)paren
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
singleline_comment|// XXX: align red zone size with ABI 
r_if
c_cond
(paren
id|address
op_plus
l_int|128
OL
id|regs-&gt;rsp
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
l_int|1
suffix:colon
id|tsk-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tsk-&gt;maj_flt
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
id|bad_area_nosemaphore
suffix:colon
macro_line|#ifdef CONFIG_IA32_EMULATION
multiline_comment|/* 32bit vsyscall. map on demand. */
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_IA32
)paren
op_logical_and
id|address
op_ge
l_int|0xffffe000
op_logical_and
id|address
OL
l_int|0xffffe000
op_plus
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|map_syscall32
c_func
(paren
id|mm
comma
id|address
)paren
OL
l_int|0
)paren
r_goto
id|out_of_memory2
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* User mode accesses just cause a SIGSEGV */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|4
)paren
(brace
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
multiline_comment|/* Work around K8 erratum #100 K8 in compat mode&n;&t;&t;   occasionally jumps to illegal addresses &gt;4GB.  We&n;&t;&t;   catch this here in the page fault handler because&n;&t;&t;   these addresses are not reachable. Just detect this&n;&t;&t;   case and return.  Any code segment in LDT is&n;&t;&t;   compatibility mode. */
r_if
c_cond
(paren
(paren
id|regs-&gt;cs
op_eq
id|__USER32_CS
op_logical_or
(paren
id|regs-&gt;cs
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
)paren
op_logical_and
(paren
id|address
op_rshift
l_int|32
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|exception_trace
op_logical_and
id|unhandled_signal
c_func
(paren
id|tsk
comma
id|SIGSEGV
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s[%d]: segfault at %016lx rip %016lx rsp %016lx error %lx&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|address
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|error_code
)paren
suffix:semicolon
)brace
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
id|fixup
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;rip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixup
)paren
(brace
id|regs-&gt;rip
op_assign
id|fixup-&gt;fixup
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Hall of shame of CPU/BIOS bugs.&n;&t; */
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
r_if
c_cond
(paren
id|is_errata93
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
id|oops_begin
c_func
(paren
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
l_string|&quot; at %016lx RIP: &bslash;n&quot;
id|KERN_ALERT
comma
id|address
)paren
suffix:semicolon
id|printk_address
c_func
(paren
id|regs-&gt;rip
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|dump_pagetable
c_func
(paren
id|address
)paren
suffix:semicolon
id|__die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
multiline_comment|/* Executive summary in case the body of the oops scrolled away */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CR2: %016lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|oops_end
c_func
(paren
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
id|out_of_memory2
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
id|again
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
id|pte
suffix:semicolon
multiline_comment|/*&n;&t;&t; * x86-64 has the same kernel 3rd level pages for all CPUs.&n;&t;&t; * But for vmalloc/modules the TLB synchronization works lazily,&n;&t;&t; * so it can happen that we get a page fault for something&n;&t;&t; * that is really already in the page table. Just check if it&n;&t;&t; * is really there and when yes flush the local TLB. &n;&t;&t; */
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
id|pgd
op_ne
id|current_pgd_offset_k
c_func
(paren
id|address
)paren
)paren
id|BUG
c_func
(paren
)paren
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
r_goto
id|bad_area_nosemaphore
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
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|bad_area_nosemaphore
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
r_goto
id|bad_area_nosemaphore
suffix:semicolon
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
