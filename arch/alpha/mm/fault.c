multiline_comment|/*&n; *  linux/arch/alpha/mm/fault.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef  __EXTERN_INLINE
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Force a new ASN for a task.&n; */
macro_line|#ifndef CONFIG_SMP
DECL|variable|last_asn
r_int
r_int
id|last_asn
op_assign
id|ASN_FIRST_VERSION
suffix:semicolon
macro_line|#endif
r_void
DECL|function|__load_new_mm_context
id|__load_new_mm_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|next_mm
)paren
(brace
r_int
r_int
id|mmc
suffix:semicolon
r_struct
id|pcb_struct
op_star
id|pcb
suffix:semicolon
id|mmc
op_assign
id|__get_new_mm_context
c_func
(paren
id|next_mm
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|next_mm-&gt;context
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_assign
id|mmc
suffix:semicolon
id|pcb
op_assign
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|pcb
suffix:semicolon
id|pcb-&gt;asn
op_assign
id|mmc
op_amp
id|HARDWARE_ASN_MASK
suffix:semicolon
id|pcb-&gt;ptbr
op_assign
(paren
(paren
r_int
r_int
)paren
id|next_mm-&gt;pgd
op_minus
id|IDENT_ADDR
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|__reload_thread
c_func
(paren
id|pcb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to handle_mm_fault().&n; *&n; * mmcsr:&n; *&t;0 = translation not valid&n; *&t;1 = access violation&n; *&t;2 = fault-on-read&n; *&t;3 = fault-on-execute&n; *&t;4 = fault-on-write&n; *&n; * cause:&n; *&t;-1 = instruction fetch&n; *&t;0 = load&n; *&t;1 = store&n; *&n; * Registers $9 through $15 are saved in a block just prior to `regs&squot; and&n; * are saved and restored around the call to allow exception code to&n; * modify them.&n; */
multiline_comment|/* Macro for exception fixup code to access integer registers.  */
DECL|macro|dpf_reg
mdefine_line|#define dpf_reg(r)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((unsigned long *)regs)[(r) &lt;= 8 ? (r) : (r) &lt;= 15 ? (r)-16 :&t;&bslash;&n;&t;&t;&t;&t; (r) &lt;= 18 ? (r)+8 : (r)-10])
id|asmlinkage
r_void
DECL|function|do_page_fault
id|do_page_fault
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|mmcsr
comma
r_int
id|cause
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_const
r_struct
id|exception_table_entry
op_star
id|fixup
suffix:semicolon
r_int
id|fault
comma
id|si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
multiline_comment|/* As of EV6, a load into $31/$f31 is a prefetch, and never faults&n;&t;   (or is suppressed by the PALcode).  Support that for older CPUs&n;&t;   by ignoring such an instruction.  */
r_if
c_cond
(paren
id|cause
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|insn
suffix:semicolon
id|__get_user
c_func
(paren
id|insn
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|regs-&gt;pc
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|insn
op_rshift
l_int|21
op_amp
l_int|0x1f
)paren
op_eq
l_int|0x1f
op_logical_and
multiline_comment|/* ldq ldl ldt lds ldg ldf ldwu ldbu */
(paren
l_int|1ul
op_lshift
(paren
id|insn
op_rshift
l_int|26
)paren
op_amp
l_int|0x30f00001400ul
)paren
)paren
(brace
id|regs-&gt;pc
op_add_assign
l_int|4
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* If we&squot;re in an interrupt context, or have no user context,&n;&t;   we must not take the fault.  */
r_if
c_cond
(paren
op_logical_neg
id|mm
op_logical_or
id|in_interrupt
c_func
(paren
)paren
)paren
r_goto
id|no_context
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_LARGE_VMALLOC
r_if
c_cond
(paren
id|address
op_ge
id|TASK_SIZE
)paren
r_goto
id|vmalloc_fault
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
multiline_comment|/* Ok, we have a good vm_area for this memory access, so&n;&t;   we can handle it.  */
id|good_area
suffix:colon
id|si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
r_if
c_cond
(paren
id|cause
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
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
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|cause
)paren
(brace
multiline_comment|/* Allow reads even for write-only mappings */
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
multiline_comment|/* If for any reason at all we couldn&squot;t handle the fault,&n;&t;   make sure we exit gracefully rather than endlessly redo&n;&t;   the fault.  */
id|fault
op_assign
id|handle_mm_fault
c_func
(paren
id|mm
comma
id|vma
comma
id|address
comma
id|cause
OG
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
r_switch
c_cond
(paren
id|fault
)paren
(brace
r_case
id|VM_FAULT_MINOR
suffix:colon
id|current-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VM_FAULT_MAJOR
suffix:colon
id|current-&gt;maj_flt
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
r_return
suffix:semicolon
multiline_comment|/* Something tried to access memory that isn&squot;t in our memory map.&n;&t;   Fix it, but check if it&squot;s kernel or user first.  */
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
r_goto
id|do_sigsegv
suffix:semicolon
id|no_context
suffix:colon
multiline_comment|/* Are we prepared to handle this fault as an exception?  */
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;pc
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|newpc
suffix:semicolon
id|newpc
op_assign
id|fixup_exception
c_func
(paren
id|dpf_reg
comma
id|fixup
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|newpc
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Oops. The kernel tried to access some bad page. We&squot;ll have to&n;&t;   terminate things with extreme prejudice.  */
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
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|cause
comma
(paren
r_int
r_int
op_star
)paren
id|regs
op_minus
l_int|16
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
multiline_comment|/* We ran out of memory, or some other thing happened to us that&n;&t;   made us unable to handle the page fault gracefully.  */
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
id|KERN_ALERT
l_string|&quot;VM: killing process %s(%d)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
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
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
id|do_sigbus
suffix:colon
multiline_comment|/* Send a sigbus, regardless of whether we were in kernel&n;&t;   or user mode.  */
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
id|current
)paren
suffix:semicolon
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
r_return
suffix:semicolon
id|do_sigsegv
suffix:colon
id|info.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|si_code
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
id|SIGSEGV
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_LARGE_VMALLOC
id|vmalloc_fault
suffix:colon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_goto
id|do_sigsegv
suffix:semicolon
r_else
(brace
multiline_comment|/* Synchronize this task&squot;s top level page-table&n;&t;&t;   with the &quot;reference&quot; page table from init.  */
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
id|pgd
op_assign
id|current-&gt;active_mm-&gt;pgd
op_plus
id|index
suffix:semicolon
id|pgd_k
op_assign
id|swapper_pg_dir
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
id|pgd
)paren
op_logical_and
id|pgd_present
c_func
(paren
op_star
id|pgd_k
)paren
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
op_assign
id|pgd_val
c_func
(paren
op_star
id|pgd_k
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_goto
id|no_context
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
