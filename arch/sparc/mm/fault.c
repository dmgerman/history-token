multiline_comment|/* $Id: fault.c,v 1.122 2001/11/17 07:19:26 davem Exp $&n; * fault.c:  Page fault handlers for the Sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/memreg.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
r_extern
r_int
id|prom_node_root
suffix:semicolon
multiline_comment|/* At boot time we determine these two values necessary for setting&n; * up the segment maps and page table entries (pte&squot;s).&n; */
DECL|variable|num_segmaps
DECL|variable|num_contexts
r_int
id|num_segmaps
comma
id|num_contexts
suffix:semicolon
DECL|variable|invalid_segment
r_int
id|invalid_segment
suffix:semicolon
multiline_comment|/* various Virtual Address Cache parameters we find at boot time... */
DECL|variable|vac_size
DECL|variable|vac_linesize
DECL|variable|vac_do_hw_vac_flushes
r_int
id|vac_size
comma
id|vac_linesize
comma
id|vac_do_hw_vac_flushes
suffix:semicolon
DECL|variable|vac_entries_per_context
DECL|variable|vac_entries_per_segment
r_int
id|vac_entries_per_context
comma
id|vac_entries_per_segment
suffix:semicolon
DECL|variable|vac_entries_per_page
r_int
id|vac_entries_per_page
suffix:semicolon
multiline_comment|/* Nice, simple, prom library does all the sweating for us. ;) */
DECL|function|prom_probe_memory
r_int
id|prom_probe_memory
(paren
r_void
)paren
(brace
r_register
r_struct
id|linux_mlist_v0
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
id|v0_available
suffix:semicolon
id|bytes
op_assign
id|tally
op_assign
id|mlist-&gt;num_bytes
suffix:semicolon
id|base_paddr
op_assign
(paren
r_int
r_int
)paren
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
(paren
r_int
r_int
)paren
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
l_int|0xdeadbeef
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
(brace
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_and_assign
id|PAGE_MASK
suffix:semicolon
)brace
r_return
id|tally
suffix:semicolon
)brace
multiline_comment|/* Traverse the memory lists in the prom to see how much physical we&n; * have.&n; */
r_int
r_int
DECL|function|probe_memory
id|probe_memory
c_func
(paren
r_void
)paren
(brace
r_int
id|total
suffix:semicolon
id|total
op_assign
id|prom_probe_memory
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Oh man, much nicer, keep the dirt in promlib. */
r_return
id|total
suffix:semicolon
)brace
r_extern
r_void
id|sun4c_complete_all_stores
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Whee, a level 15 NMI interrupt memory error.  Let&squot;s have fun... */
DECL|function|sparc_lvl15_nmi
id|asmlinkage
r_void
id|sparc_lvl15_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|serr
comma
r_int
r_int
id|svaddr
comma
r_int
r_int
id|aerr
comma
r_int
r_int
id|avaddr
)paren
(brace
id|sun4c_complete_all_stores
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FAULT: NMI received&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SREGS: Synchronous Error %08lx&bslash;n&quot;
comma
id|serr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;       Synchronous Vaddr %08lx&bslash;n&quot;
comma
id|svaddr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      Asynchronous Error %08lx&bslash;n&quot;
comma
id|aerr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      Asynchronous Vaddr %08lx&bslash;n&quot;
comma
id|avaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sun4c_memerr_reg
)paren
id|printk
c_func
(paren
l_string|&quot;     Memory Parity Error %08lx&bslash;n&quot;
comma
op_star
id|sun4c_memerr_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;REGISTER DUMP:&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|unhandled_fault
c_func
(paren
r_int
r_int
comma
r_struct
id|task_struct
op_star
comma
r_struct
id|pt_regs
op_star
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
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
l_string|&quot;Unable to handle kernel NULL pointer dereference&bslash;n&quot;
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
l_string|&quot;at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;tsk-&gt;{mm,active_mm}-&gt;context = %08lx&bslash;n&quot;
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
l_string|&quot;tsk-&gt;{mm,active_mm}-&gt;pgd = %08lx&bslash;n&quot;
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
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|lookup_fault
id|asmlinkage
r_int
id|lookup_fault
c_func
(paren
r_int
r_int
id|pc
comma
r_int
r_int
id|ret_pc
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|pt_regs
id|regs
suffix:semicolon
r_int
r_int
id|g2
suffix:semicolon
r_int
r_int
id|insn
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
id|search_exception_table
c_func
(paren
id|ret_pc
comma
op_amp
id|g2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|3
suffix:colon
multiline_comment|/* load &amp; store will be handled by fixup */
r_return
l_int|3
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* store will be handled by fixup, load will bump out */
multiline_comment|/* for _to_ macros */
id|insn
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|pc
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|insn
op_rshift
l_int|21
)paren
op_amp
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* load will be handled by fixup, store will bump out */
multiline_comment|/* for _from_ macros */
id|insn
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|pc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|insn
op_rshift
l_int|21
)paren
op_amp
l_int|1
)paren
op_logical_or
(paren
(paren
id|insn
op_rshift
l_int|19
)paren
op_amp
l_int|0x3f
)paren
op_eq
l_int|15
)paren
r_return
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|regs
comma
l_int|0
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
id|regs.pc
op_assign
id|pc
suffix:semicolon
id|regs.npc
op_assign
id|pc
op_plus
l_int|4
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %0&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|regs.psr
)paren
)paren
suffix:semicolon
id|unhandled_fault
c_func
(paren
id|address
comma
id|current
comma
op_amp
id|regs
)paren
suffix:semicolon
multiline_comment|/* Not reached */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_sparc_fault
id|asmlinkage
r_void
id|do_sparc_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|text_fault
comma
r_int
id|write
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_int
r_int
id|fixup
suffix:semicolon
r_int
r_int
id|g2
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
id|from_user
op_assign
op_logical_neg
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|text_fault
)paren
(brace
id|address
op_assign
id|regs-&gt;pc
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We fault-in kernel-space virtual memory on-demand. The&n;&t; * &squot;reference&squot; page table is init_mm.pgd.&n;&t; *&n;&t; * NOTE! We MUST NOT take any locks for this case. We may&n;&t; * be in an interrupt or a critical region, and should&n;&t; * only copy the information from the master page table,&n;&t; * nothing more.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ARCH_SUN4C_SUN4
op_logical_and
id|address
op_ge
id|TASK_SIZE
)paren
r_goto
id|vmalloc_fault
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
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
multiline_comment|/*&n;&t; * The kernel referencing a bad kernel pointer can lock up&n;&t; * a sun4c machine completely, so we must attempt recovery.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|from_user
op_logical_and
id|address
op_ge
id|PAGE_OFFSET
)paren
(brace
r_goto
id|bad_area
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_start
op_le
id|address
)paren
(brace
r_goto
id|good_area
suffix:semicolon
)brace
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
(brace
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ok, we have a good vm_area for this memory access, so&n;&t; * we can handle it..&n;&t; */
id|good_area
suffix:colon
id|info.si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
r_if
c_cond
(paren
id|write
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
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
id|current-&gt;min_flt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|current-&gt;maj_flt
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
multiline_comment|/*&n;&t; * Something tried to access memory that isn&squot;t in our memory map..&n;&t; * Fix it, but check if it&squot;s kernel or user first..&n;&t; */
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
id|from_user
)paren
(brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Fault whee %s [%d]: segfaults at %08lx pc=%08lx&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|address
comma
id|regs-&gt;pc
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* info.si_code set above to make clear whether&n;&t;&t;   this was a SEGV_MAPERR or SEGV_ACCERR fault.  */
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
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
multiline_comment|/* Is this in ex_table? */
id|no_context
suffix:colon
id|g2
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|from_user
op_logical_and
(paren
id|fixup
op_assign
id|search_exception_table
(paren
id|regs-&gt;pc
comma
op_amp
id|g2
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|fixup
OG
l_int|10
)paren
(brace
multiline_comment|/* Values below are reserved for other things */
r_extern
r_const
r_int
id|__memset_start
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|__memset_end
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|__csum_partial_copy_start
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|__csum_partial_copy_end
(braket
)braket
suffix:semicolon
macro_line|#ifdef DEBUG_EXCEPTIONS
id|printk
c_func
(paren
l_string|&quot;Exception: PC&lt;%08lx&gt; faddr&lt;%08lx&gt;&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EX_TABLE: insn&lt;%08lx&gt; fixup&lt;%08x&gt; g2&lt;%08lx&gt;&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|fixup
comma
id|g2
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|regs-&gt;pc
op_ge
(paren
r_int
r_int
)paren
id|__memset_start
op_logical_and
id|regs-&gt;pc
OL
(paren
r_int
r_int
)paren
id|__memset_end
)paren
op_logical_or
(paren
id|regs-&gt;pc
op_ge
(paren
r_int
r_int
)paren
id|__csum_partial_copy_start
op_logical_and
id|regs-&gt;pc
OL
(paren
r_int
r_int
)paren
id|__csum_partial_copy_end
)paren
)paren
(brace
id|regs-&gt;u_regs
(braket
id|UREG_I4
)braket
op_assign
id|address
suffix:semicolon
id|regs-&gt;u_regs
(braket
id|UREG_I5
)braket
op_assign
id|regs-&gt;pc
suffix:semicolon
)brace
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
op_assign
id|g2
suffix:semicolon
id|regs-&gt;pc
op_assign
id|fixup
suffix:semicolon
id|regs-&gt;npc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|unhandled_fault
(paren
id|address
comma
id|tsk
comma
id|regs
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
id|from_user
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
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|from_user
)paren
r_goto
id|no_context
suffix:semicolon
id|vmalloc_fault
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * Synchronize this task&squot;s top level page-table&n;&t;&t; * with the &squot;reference&squot; page table.&n;&t;&t; */
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
id|pgd
op_assign
id|tsk-&gt;active_mm-&gt;pgd
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
op_logical_neg
id|pgd_present
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
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
id|bad_area_nosemaphore
suffix:semicolon
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
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
op_logical_or
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd_k
)paren
)paren
r_goto
id|bad_area_nosemaphore
suffix:semicolon
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|pmd_val
c_func
(paren
op_star
id|pmd_k
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|do_sun4c_fault
id|asmlinkage
r_void
id|do_sun4c_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|text_fault
comma
r_int
id|write
comma
r_int
r_int
id|address
)paren
(brace
r_extern
r_void
id|sun4c_update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|sun4c_pte_offset_kernel
c_func
(paren
id|pmd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
id|text_fault
)paren
(brace
id|address
op_assign
id|regs-&gt;pc
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|write
op_logical_and
op_logical_neg
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
)paren
(brace
r_int
r_int
id|insn
comma
op_star
id|ip
suffix:semicolon
id|ip
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;pc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_user
c_func
(paren
id|insn
comma
id|ip
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1680000
)paren
op_eq
l_int|0xc0680000
)paren
id|write
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
id|ptep
op_assign
id|sun4c_pte_offset_kernel
c_func
(paren
(paren
id|pmd_t
op_star
)paren
id|pgdp
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
)paren
(brace
r_if
c_cond
(paren
id|write
)paren
(brace
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
(paren
id|_SUN4C_PAGE_WRITE
op_or
id|_SUN4C_PAGE_PRESENT
)paren
)paren
op_eq
(paren
id|_SUN4C_PAGE_WRITE
op_or
id|_SUN4C_PAGE_PRESENT
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
op_star
id|ptep
op_assign
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_or
id|_SUN4C_PAGE_ACCESSED
op_or
id|_SUN4C_PAGE_MODIFIED
op_or
id|_SUN4C_PAGE_VALID
op_or
id|_SUN4C_PAGE_DIRTY
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sun4c_get_segmap
c_func
(paren
id|address
)paren
op_ne
id|invalid_segment
)paren
(brace
id|sun4c_put_pte
c_func
(paren
id|address
comma
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
(paren
id|_SUN4C_PAGE_READ
op_or
id|_SUN4C_PAGE_PRESENT
)paren
)paren
op_eq
(paren
id|_SUN4C_PAGE_READ
op_or
id|_SUN4C_PAGE_PRESENT
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
op_star
id|ptep
op_assign
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_or
id|_SUN4C_PAGE_ACCESSED
op_or
id|_SUN4C_PAGE_VALID
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sun4c_get_segmap
c_func
(paren
id|address
)paren
op_ne
id|invalid_segment
)paren
(brace
id|sun4c_put_pte
c_func
(paren
id|address
comma
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* This conditional is &squot;interesting&squot;. */
r_if
c_cond
(paren
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_logical_and
op_logical_neg
(paren
id|write
op_logical_and
op_logical_neg
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_SUN4C_PAGE_WRITE
)paren
)paren
op_logical_and
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_SUN4C_PAGE_VALID
)paren
)paren
multiline_comment|/* Note: It is safe to not grab the MMAP semaphore here because&n;&t;&t; *       we know that update_mmu_cache() will not sleep for&n;&t;&t; *       any reason (at least not in the current implementation)&n;&t;&t; *       and therefore there is no danger of another thread getting&n;&t;&t; *       on the CPU and doing a shrink_mmap() on this vma.&n;&t;&t; */
id|sun4c_update_mmu_cache
(paren
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|address
)paren
comma
id|address
comma
op_star
id|ptep
)paren
suffix:semicolon
r_else
id|do_sparc_fault
c_func
(paren
id|regs
comma
id|text_fault
comma
id|write
comma
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/* This always deals with user addresses. */
DECL|function|force_user_fault
r_inline
r_void
id|force_user_fault
c_func
(paren
r_int
r_int
id|address
comma
r_int
id|write
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;wf&lt;pid=%d,wr=%d,addr=%08lx&gt;&bslash;n&quot;
comma
id|tsk-&gt;pid
comma
id|write
comma
id|address
)paren
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_start
op_le
id|address
)paren
(brace
r_goto
id|good_area
suffix:semicolon
)brace
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
(brace
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
id|good_area
suffix:colon
id|info.si_code
op_assign
id|SEGV_ACCERR
suffix:semicolon
r_if
c_cond
(paren
id|write
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
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
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
(paren
id|VM_READ
op_or
id|VM_EXEC
)paren
)paren
)paren
(brace
r_goto
id|bad_area
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
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
r_goto
id|do_sigbus
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
id|bad_area
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Window whee %s [%d]: segfaults at %08lx&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|address
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* info.si_code set above to make clear whether&n;&t;   this was a SEGV_MAPERR or SEGV_ACCERR fault.  */
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
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
id|do_sigbus
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
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
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|window_overflow_fault
r_void
id|window_overflow_fault
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sp
suffix:semicolon
id|sp
op_assign
id|current-&gt;thread.rwbuf_stkptrs
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|sp
op_plus
l_int|0x38
)paren
op_amp
id|PAGE_MASK
)paren
op_ne
(paren
id|sp
op_amp
id|PAGE_MASK
)paren
)paren
(brace
id|force_user_fault
c_func
(paren
id|sp
op_plus
l_int|0x38
comma
l_int|1
)paren
suffix:semicolon
)brace
id|force_user_fault
c_func
(paren
id|sp
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|window_underflow_fault
r_void
id|window_underflow_fault
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|sp
op_plus
l_int|0x38
)paren
op_amp
id|PAGE_MASK
)paren
op_ne
(paren
id|sp
op_amp
id|PAGE_MASK
)paren
)paren
(brace
id|force_user_fault
c_func
(paren
id|sp
op_plus
l_int|0x38
comma
l_int|0
)paren
suffix:semicolon
)brace
id|force_user_fault
c_func
(paren
id|sp
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|window_ret_fault
r_void
id|window_ret_fault
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
id|sp
suffix:semicolon
id|sp
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|sp
op_plus
l_int|0x38
)paren
op_amp
id|PAGE_MASK
)paren
op_ne
(paren
id|sp
op_amp
id|PAGE_MASK
)paren
)paren
(brace
id|force_user_fault
c_func
(paren
id|sp
op_plus
l_int|0x38
comma
l_int|0
)paren
suffix:semicolon
)brace
id|force_user_fault
c_func
(paren
id|sp
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
