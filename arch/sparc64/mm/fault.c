multiline_comment|/* $Id: fault.c,v 1.59 2002/02/09 19:49:31 davem Exp $&n; * arch/sparc64/mm/fault.c: Page fault handlers for the 64-bit Sparc.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; */
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/lsu.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
DECL|macro|ELEMENTS
mdefine_line|#define ELEMENTS(arr) (sizeof (arr)/sizeof (arr[0]))
r_extern
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
)braket
suffix:semicolon
multiline_comment|/*&n; * To debug kernel during syscall entry.&n; */
DECL|function|syscall_trace_entry
r_void
id|syscall_trace_entry
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scall entry: %s[%d]/cpu%d: %d&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|smp_processor_id
c_func
(paren
)paren
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_G1
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * To debug kernel during syscall exit.&n; */
DECL|function|syscall_trace_exit
r_void
id|syscall_trace_exit
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scall exit: %s[%d]/cpu%d: %d&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|smp_processor_id
c_func
(paren
)paren
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_G1
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * To debug kernel to catch accesses to certain virtual/physical addresses.&n; * Mode = 0 selects physical watchpoints, mode = 1 selects virtual watchpoints.&n; * flags = VM_READ watches memread accesses, flags = VM_WRITE watches memwrite accesses.&n; * Caller passes in a 64bit aligned addr, with mask set to the bytes that need to be&n; * watched. This is only useful on a single cpu machine for now. After the watchpoint&n; * is detected, the process causing it will be killed, thus preventing an infinite loop.&n; */
DECL|function|set_brkpt
r_void
id|set_brkpt
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_char
id|mask
comma
r_int
id|flags
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|lsubits
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa [%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lsubits
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_LSU_CONTROL
)paren
)paren
suffix:semicolon
id|lsubits
op_and_assign
op_complement
(paren
id|LSU_CONTROL_PM
op_or
id|LSU_CONTROL_VM
op_or
id|LSU_CONTROL_PR
op_or
id|LSU_CONTROL_VR
op_or
id|LSU_CONTROL_PW
op_or
id|LSU_CONTROL_VW
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&t;%0, [%1] %2&bslash;n&bslash;t&quot;
l_string|&quot;membar&t;#Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|mode
ques
c_cond
id|VIRT_WATCHPOINT
suffix:colon
id|PHYS_WATCHPOINT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_DMMU
)paren
)paren
suffix:semicolon
id|lsubits
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|mask
op_lshift
(paren
id|mode
ques
c_cond
l_int|25
suffix:colon
l_int|33
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|VM_READ
)paren
id|lsubits
op_or_assign
(paren
id|mode
ques
c_cond
id|LSU_CONTROL_VR
suffix:colon
id|LSU_CONTROL_PR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|VM_WRITE
)paren
id|lsubits
op_or_assign
(paren
id|mode
ques
c_cond
id|LSU_CONTROL_VW
suffix:colon
id|LSU_CONTROL_PW
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa %0, [%%g0] %1&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|lsubits
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_LSU_CONTROL
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Nice, simple, prom library does all the sweating for us. ;) */
DECL|function|prom_probe_memory
r_int
r_int
id|__init
id|prom_probe_memory
(paren
r_void
)paren
(brace
r_register
r_struct
id|linux_mlist_p1275
op_star
id|mlist
suffix:semicolon
r_register
r_int
r_int
id|bytes
comma
id|base_paddr
comma
id|tally
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|mlist
op_assign
op_star
id|prom_meminfo
c_func
(paren
)paren
op_member_access_from_pointer
id|p1275_available
suffix:semicolon
id|bytes
op_assign
id|tally
op_assign
id|mlist-&gt;num_bytes
suffix:semicolon
id|base_paddr
op_assign
id|mlist-&gt;start_adr
suffix:semicolon
id|sp_banks
(braket
l_int|0
)braket
dot
id|base_addr
op_assign
id|base_paddr
suffix:semicolon
id|sp_banks
(braket
l_int|0
)braket
dot
id|num_bytes
op_assign
id|bytes
suffix:semicolon
r_while
c_loop
(paren
id|mlist-&gt;theres_more
op_ne
(paren
r_void
op_star
)paren
l_int|0
)paren
(brace
id|i
op_increment
suffix:semicolon
id|mlist
op_assign
id|mlist-&gt;theres_more
suffix:semicolon
id|bytes
op_assign
id|mlist-&gt;num_bytes
suffix:semicolon
id|tally
op_add_assign
id|bytes
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|SPARC_PHYS_BANKS
op_minus
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;The machine has more banks than &quot;
l_string|&quot;this kernel can support&bslash;n&quot;
l_string|&quot;Increase the SPARC_PHYS_BANKS &quot;
l_string|&quot;setting (currently %d)&bslash;n&quot;
comma
id|SPARC_PHYS_BANKS
)paren
suffix:semicolon
id|i
op_assign
id|SPARC_PHYS_BANKS
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_assign
id|mlist-&gt;start_adr
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_assign
id|mlist-&gt;num_bytes
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_assign
l_int|0xdeadbeefbeefdeadUL
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now mask all bank sizes on a page boundary, it is all we can&n;&t; * use anyways.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_return
id|tally
suffix:semicolon
)brace
DECL|function|unhandled_fault
r_static
r_void
id|unhandled_fault
c_func
(paren
r_int
r_int
id|address
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|address
OL
id|PAGE_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL &quot;
l_string|&quot;pointer dereference&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel paging request &quot;
l_string|&quot;at virtual address %016lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;tsk-&gt;{mm,active_mm}-&gt;context = %016lx&bslash;n&quot;
comma
(paren
id|tsk-&gt;mm
ques
c_cond
id|tsk-&gt;mm-&gt;context
suffix:colon
id|tsk-&gt;active_mm-&gt;context
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;tsk-&gt;{mm,active_mm}-&gt;pgd = %016lx&bslash;n&quot;
comma
(paren
id|tsk-&gt;mm
ques
c_cond
(paren
r_int
r_int
)paren
id|tsk-&gt;mm-&gt;pgd
suffix:colon
(paren
r_int
r_int
)paren
id|tsk-&gt;active_mm-&gt;pgd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notify_die
c_func
(paren
id|DIE_GPF
comma
l_string|&quot;general protection fault&quot;
comma
id|regs
comma
l_int|0
comma
l_int|0
comma
id|SIGSEGV
)paren
op_eq
id|NOTIFY_STOP
)paren
r_return
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|bad_kernel_pc
r_static
r_void
id|bad_kernel_pc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
op_star
id|ksp
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;OOPS: Bogus kernel PC [%016lx] in fault handler&bslash;n&quot;
comma
id|regs-&gt;tpc
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %%sp, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ksp
)paren
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
id|ksp
)paren
suffix:semicolon
id|unhandled_fault
c_func
(paren
id|regs-&gt;tpc
comma
id|current
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We now make sure that mmap_sem is held in all paths that call &n; * this. Additionally, to prevent kswapd from ripping ptes from&n; * under us, raise interrupts around the time that we look at the&n; * pte, kswapd will have to wait to get his smp ipi response from&n; * us. This saves us having to get page_table_lock.&n; */
DECL|function|get_user_insn
r_static
r_int
r_int
id|get_user_insn
c_func
(paren
r_int
r_int
id|tpc
)paren
(brace
id|pgd_t
op_star
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|tpc
)paren
suffix:semicolon
id|pud_t
op_star
id|pudp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
comma
id|pte
suffix:semicolon
r_int
r_int
id|pa
suffix:semicolon
id|u32
id|insn
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pstate
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgdp
)paren
)paren
r_goto
id|outret
suffix:semicolon
id|pudp
op_assign
id|pud_offset
c_func
(paren
id|pgdp
comma
id|tpc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pud_none
c_func
(paren
op_star
id|pudp
)paren
)paren
r_goto
id|outret
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pudp
comma
id|tpc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmdp
)paren
)paren
r_goto
id|outret
suffix:semicolon
multiline_comment|/* This disables preemption for us as well. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr %%pstate, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pstate
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wrpr %0, %1, %%pstate&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pstate
)paren
comma
l_string|&quot;i&quot;
(paren
id|PSTATE_IE
)paren
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_map
c_func
(paren
id|pmdp
comma
id|tpc
)paren
suffix:semicolon
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
r_goto
id|out
suffix:semicolon
id|pa
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_PADDR
)paren
suffix:semicolon
id|pa
op_add_assign
(paren
id|tpc
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
multiline_comment|/* Use phys bypass so we don&squot;t pollute dtlb/dcache. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduwa [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|insn
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|pa
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_USE_EC
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|pte_unmap
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wrpr %0, 0x0, %%pstate&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pstate
)paren
)paren
suffix:semicolon
id|outret
suffix:colon
r_return
id|insn
suffix:semicolon
)brace
r_extern
r_int
r_int
id|compute_effective_address
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|function|do_fault_siginfo
r_static
r_void
id|do_fault_siginfo
c_func
(paren
r_int
id|code
comma
r_int
id|sig
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
comma
r_int
id|fault_code
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|info.si_code
op_assign
id|code
suffix:semicolon
id|info.si_signo
op_assign
id|sig
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fault_code
op_amp
id|FAULT_CODE_ITLB
)paren
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|regs-&gt;tpc
suffix:semicolon
r_else
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|compute_effective_address
c_func
(paren
id|regs
comma
id|insn
comma
l_int|0
)paren
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|sig
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
r_extern
r_int
id|handle_ldf_stq
c_func
(paren
id|u32
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|handle_ld_nf
c_func
(paren
id|u32
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|function|get_fault_insn
r_static
r_int
r_int
id|get_fault_insn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|insn
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|regs-&gt;tpc
op_logical_or
(paren
id|regs-&gt;tpc
op_amp
l_int|0x3
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|insn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;tpc
suffix:semicolon
)brace
r_else
(brace
id|insn
op_assign
id|get_user_insn
c_func
(paren
id|regs-&gt;tpc
)paren
suffix:semicolon
)brace
)brace
r_return
id|insn
suffix:semicolon
)brace
DECL|function|do_kernel_fault
r_static
r_void
id|do_kernel_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|si_code
comma
r_int
id|fault_code
comma
r_int
r_int
id|insn
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|g2
suffix:semicolon
r_int
r_char
id|asi
op_assign
id|ASI_P
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|insn
)paren
op_logical_and
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
)paren
r_goto
id|cannot_handle
suffix:semicolon
multiline_comment|/* If user insn could be read (thus insn is zero), that&n;&t; * is fine.  We will just gun down the process with a signal&n;&t; * in that case.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|fault_code
op_amp
(paren
id|FAULT_CODE_WRITE
op_or
id|FAULT_CODE_ITLB
)paren
)paren
op_logical_and
(paren
id|insn
op_amp
l_int|0xc0800000
)paren
op_eq
l_int|0xc0800000
)paren
(brace
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x2000
)paren
id|asi
op_assign
(paren
id|regs-&gt;tstate
op_rshift
l_int|24
)paren
suffix:semicolon
r_else
id|asi
op_assign
(paren
id|insn
op_rshift
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|asi
op_amp
l_int|0xf2
)paren
op_eq
l_int|0x82
)paren
(brace
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x1000000
)paren
(brace
id|handle_ldf_stq
c_func
(paren
id|insn
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This was a non-faulting load. Just clear the&n;&t;&t;&t;&t; * destination register(s) and continue with the next&n;&t;&t;&t;&t; * instruction. -jj&n;&t;&t;&t;&t; */
id|handle_ld_nf
c_func
(paren
id|insn
comma
id|regs
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
id|g2
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
suffix:semicolon
multiline_comment|/* Is this in ex_table? */
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
r_int
r_int
id|fixup
suffix:semicolon
r_if
c_cond
(paren
id|asi
op_eq
id|ASI_P
op_logical_and
(paren
id|insn
op_amp
l_int|0xc0800000
)paren
op_eq
l_int|0xc0800000
)paren
(brace
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x2000
)paren
id|asi
op_assign
(paren
id|regs-&gt;tstate
op_rshift
l_int|24
)paren
suffix:semicolon
r_else
id|asi
op_assign
(paren
id|insn
op_rshift
l_int|5
)paren
suffix:semicolon
)brace
multiline_comment|/* Look in asi.h: All _S asis have LS bit set */
r_if
c_cond
(paren
(paren
id|asi
op_amp
l_int|0x1
)paren
op_logical_and
(paren
id|fixup
op_assign
id|search_extables_range
c_func
(paren
id|regs-&gt;tpc
comma
op_amp
id|g2
)paren
)paren
)paren
(brace
id|regs-&gt;tpc
op_assign
id|fixup
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|regs-&gt;tpc
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
op_assign
id|g2
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* The si_code was set to make clear whether&n;&t;&t; * this was a SEGV_MAPERR or SEGV_ACCERR fault.&n;&t;&t; */
id|do_fault_siginfo
c_func
(paren
id|si_code
comma
id|SIGSEGV
comma
id|regs
comma
id|insn
comma
id|fault_code
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cannot_handle
suffix:colon
id|unhandled_fault
(paren
id|address
comma
id|current
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_sparc64_fault
id|asmlinkage
r_void
id|do_sparc64_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
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
id|insn
op_assign
l_int|0
suffix:semicolon
r_int
id|si_code
comma
id|fault_code
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|fault_code
op_assign
id|get_thread_fault_code
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notify_die
c_func
(paren
id|DIE_PAGE_FAULT
comma
l_string|&quot;page_fault&quot;
comma
id|regs
comma
id|fault_code
comma
l_int|0
comma
id|SIGSEGV
)paren
op_eq
id|NOTIFY_STOP
)paren
r_return
suffix:semicolon
id|si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
id|address
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|fault_address
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fault_code
op_amp
id|FAULT_CODE_ITLB
)paren
op_logical_and
(paren
id|fault_code
op_amp
id|FAULT_CODE_DTLB
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
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
r_int
r_int
id|tpc
op_assign
id|regs-&gt;tpc
suffix:semicolon
multiline_comment|/* Sanity check the PC. */
r_if
c_cond
(paren
(paren
id|tpc
op_ge
id|KERNBASE
op_logical_and
id|tpc
OL
(paren
r_int
r_int
)paren
id|_etext
)paren
op_logical_or
(paren
id|tpc
op_ge
id|MODULES_VADDR
op_logical_and
id|tpc
OL
id|MODULES_END
)paren
)paren
(brace
multiline_comment|/* Valid, no problems... */
)brace
r_else
(brace
id|bad_kernel_pc
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
id|intr_or_no_mm
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
)paren
id|regs-&gt;tpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|address
op_and_assign
l_int|0xffffffff
suffix:semicolon
)brace
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
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
op_logical_and
op_logical_neg
id|search_exception_tables
c_func
(paren
id|regs-&gt;tpc
)paren
)paren
(brace
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
r_goto
id|handle_kernel_fault
suffix:semicolon
)brace
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
multiline_comment|/* Pure DTLB misses do not tell us whether the fault causing&n;&t; * load/store/atomic was a write or not, it only says that there&n;&t; * was no match.  So in such a case we (carefully) read the&n;&t; * instruction to try and figure this out.  It&squot;s an optimization&n;&t; * so it&squot;s ok if we can&squot;t do this.&n;&t; *&n;&t; * Special hack, window spill/fill knows the exact fault type.&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|fault_code
op_amp
(paren
id|FAULT_CODE_DTLB
op_or
id|FAULT_CODE_WRITE
op_or
id|FAULT_CODE_WINFIXUP
)paren
)paren
op_eq
id|FAULT_CODE_DTLB
)paren
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
op_ne
l_int|0
)paren
(brace
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|insn
)paren
r_goto
id|continue_fault
suffix:semicolon
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc0200000
)paren
op_eq
l_int|0xc0200000
op_logical_and
(paren
id|insn
op_amp
l_int|0x1780000
)paren
op_ne
l_int|0x1680000
)paren
(brace
multiline_comment|/* Don&squot;t bother updating thread struct value,&n;&t;&t;&t; * because update_mmu_cache only cares which tlb&n;&t;&t;&t; * the access came from.&n;&t;&t;&t; */
id|fault_code
op_or_assign
id|FAULT_CODE_WRITE
suffix:semicolon
)brace
)brace
id|continue_fault
suffix:colon
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
op_logical_neg
(paren
id|fault_code
op_amp
id|FAULT_CODE_WRITE
)paren
)paren
(brace
multiline_comment|/* Non-faulting loads shouldn&squot;t expand stack. */
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc0800000
)paren
op_eq
l_int|0xc0800000
)paren
(brace
r_int
r_char
id|asi
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x2000
)paren
id|asi
op_assign
(paren
id|regs-&gt;tstate
op_rshift
l_int|24
)paren
suffix:semicolon
r_else
id|asi
op_assign
(paren
id|insn
op_rshift
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|asi
op_amp
l_int|0xf2
)paren
op_eq
l_int|0x82
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * Ok, we have a good vm_area for this memory access, so&n;&t; * we can handle it..&n;&t; */
id|good_area
suffix:colon
id|si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
multiline_comment|/* If we took a ITLB miss on a non-executable page, catch&n;&t; * that here.&n;&t; */
r_if
c_cond
(paren
(paren
id|fault_code
op_amp
id|FAULT_CODE_ITLB
)paren
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
(brace
id|BUG_ON
c_func
(paren
id|address
op_ne
id|regs-&gt;tpc
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
suffix:semicolon
r_goto
id|bad_area
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fault_code
op_amp
id|FAULT_CODE_WRITE
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
multiline_comment|/* Spitfire has an icache which does not snoop&n;&t;&t; * processor stores.  Later processors do...&n;&t;&t; */
r_if
c_cond
(paren
id|tlb_type
op_eq
id|spitfire
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
op_ne
l_int|0
op_logical_and
id|vma-&gt;vm_file
op_ne
l_int|NULL
)paren
id|set_thread_fault_code
c_func
(paren
id|fault_code
op_or
id|FAULT_CODE_BLKCOMMIT
)paren
suffix:semicolon
)brace
r_else
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
id|VM_EXEC
)paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
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
(paren
id|fault_code
op_amp
id|FAULT_CODE_WRITE
)paren
)paren
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
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_goto
id|fault_done
suffix:semicolon
multiline_comment|/*&n;&t; * Something tried to access memory that isn&squot;t in our memory map..&n;&t; * Fix it, but check if it&squot;s kernel or user first..&n;&t; */
id|bad_area
suffix:colon
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|handle_kernel_fault
suffix:colon
id|do_kernel_fault
c_func
(paren
id|regs
comma
id|si_code
comma
id|fault_code
comma
id|insn
comma
id|address
)paren
suffix:semicolon
r_goto
id|fault_done
suffix:semicolon
multiline_comment|/*&n; * We ran out of memory, or some other thing happened to us that made&n; * us unable to handle the page fault gracefully.&n; */
id|out_of_memory
suffix:colon
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VM: killing process %s&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
)paren
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
r_goto
id|handle_kernel_fault
suffix:semicolon
id|intr_or_no_mm
suffix:colon
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|handle_kernel_fault
suffix:semicolon
id|do_sigbus
suffix:colon
id|insn
op_assign
id|get_fault_insn
c_func
(paren
id|regs
comma
id|insn
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Send a sigbus, regardless of whether we were in kernel&n;&t; * or user mode.&n;&t; */
id|do_fault_siginfo
c_func
(paren
id|BUS_ADRERR
comma
id|SIGBUS
comma
id|regs
comma
id|insn
comma
id|fault_code
)paren
suffix:semicolon
multiline_comment|/* Kernel mode? Handle exceptions or die */
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
r_goto
id|handle_kernel_fault
suffix:semicolon
id|fault_done
suffix:colon
multiline_comment|/* These values are no longer needed, clear them. */
id|set_thread_fault_code
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|fault_address
op_assign
l_int|0
suffix:semicolon
)brace
eof
