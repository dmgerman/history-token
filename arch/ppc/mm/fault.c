multiline_comment|/*&n; *  arch/ppc/mm/fault.c&n; *&n; *  PowerPC version&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/i386/mm/fault.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Modified by Cort Dougan and Paul Mackerras.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
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
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_extern
r_void
(paren
op_star
id|debugger
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|debugger_kernel_faults
r_int
id|debugger_kernel_faults
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
DECL|variable|htab_reloads
r_int
r_int
id|htab_reloads
suffix:semicolon
multiline_comment|/* updated by hashtable.S:hash_page() */
DECL|variable|htab_evicts
r_int
r_int
id|htab_evicts
suffix:semicolon
multiline_comment|/* updated by hashtable.S:hash_page() */
DECL|variable|htab_preloads
r_int
r_int
id|htab_preloads
suffix:semicolon
multiline_comment|/* updated by hashtable.S:add_hash_page() */
DECL|variable|pte_misses
r_int
r_int
id|pte_misses
suffix:semicolon
multiline_comment|/* updated by do_page_fault() */
DECL|variable|pte_errors
r_int
r_int
id|pte_errors
suffix:semicolon
multiline_comment|/* updated by do_page_fault() */
DECL|variable|probingmem
r_int
r_int
id|probingmem
suffix:semicolon
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
)paren
suffix:semicolon
r_void
id|bad_page_fault
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
id|sig
)paren
suffix:semicolon
r_void
id|do_page_fault
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
r_extern
r_int
id|get_pteptr
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
id|pte_t
op_star
op_star
id|ptep
)paren
suffix:semicolon
multiline_comment|/*&n; * Check whether the instruction at regs-&gt;nip is a store using&n; * an update addressing form which will update r1.&n; */
DECL|function|store_updates_sp
r_static
r_int
id|store_updates_sp
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
id|inst
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|inst
comma
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;nip
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check for 1 in the rA field */
r_if
c_cond
(paren
(paren
(paren
id|inst
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
op_ne
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check major opcode */
r_switch
c_cond
(paren
id|inst
op_rshift
l_int|26
)paren
(brace
r_case
l_int|37
suffix:colon
multiline_comment|/* stwu */
r_case
l_int|39
suffix:colon
multiline_comment|/* stbu */
r_case
l_int|45
suffix:colon
multiline_comment|/* sthu */
r_case
l_int|53
suffix:colon
multiline_comment|/* stfsu */
r_case
l_int|55
suffix:colon
multiline_comment|/* stfdu */
r_return
l_int|1
suffix:semicolon
r_case
l_int|31
suffix:colon
multiline_comment|/* check minor opcode */
r_switch
c_cond
(paren
(paren
id|inst
op_rshift
l_int|1
)paren
op_amp
l_int|0x3ff
)paren
(brace
r_case
l_int|183
suffix:colon
multiline_comment|/* stwux */
r_case
l_int|247
suffix:colon
multiline_comment|/* stbux */
r_case
l_int|439
suffix:colon
multiline_comment|/* sthux */
r_case
l_int|695
suffix:colon
multiline_comment|/* stfsux */
r_case
l_int|759
suffix:colon
multiline_comment|/* stfdux */
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * For 600- and 800-family processors, the error_code parameter is DSISR&n; * for a data fault, SRR1 for an instruction fault. For 400-family processors&n; * the error_code parameter is ESR for a data fault, 0 for an instruction&n; * fault.&n; */
DECL|function|do_page_fault
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
id|address
comma
r_int
r_int
id|error_code
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
id|siginfo_t
id|info
suffix:semicolon
r_int
id|code
op_assign
id|SEGV_MAPERR
suffix:semicolon
macro_line|#if defined(CONFIG_4xx)
r_int
id|is_write
op_assign
id|error_code
op_amp
id|ESR_DST
suffix:semicolon
macro_line|#else
r_int
id|is_write
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Fortunately the bit assignments in SRR1 for an instruction&n;&t; * fault and DSISR for a data fault are mostly the same for the&n;&t; * bits we are interested in.  But there are some bits which&n;&t; * indicate errors in DSISR but can validly be set in SRR1.&n;&t; */
r_if
c_cond
(paren
id|TRAP
c_func
(paren
id|regs
)paren
op_eq
l_int|0x400
)paren
id|error_code
op_and_assign
l_int|0x48200000
suffix:semicolon
r_else
id|is_write
op_assign
id|error_code
op_amp
l_int|0x02000000
suffix:semicolon
macro_line|#endif /* CONFIG_4xx */
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_if
c_cond
(paren
id|debugger_fault_handler
op_logical_and
id|TRAP
c_func
(paren
id|regs
)paren
op_eq
l_int|0x300
)paren
(brace
id|debugger_fault_handler
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#if !defined(CONFIG_4xx)
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x00400000
)paren
(brace
multiline_comment|/* DABR match */
r_if
c_cond
(paren
id|debugger_dabr_match
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_4xx */
macro_line|#endif /* CONFIG_XMON || CONFIG_KGDB */
r_if
c_cond
(paren
id|in_atomic
c_func
(paren
)paren
op_logical_or
id|mm
op_eq
l_int|NULL
)paren
(brace
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGSEGV
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
op_logical_neg
id|is_write
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/*&n;&t; * N.B. The rs6000/xcoff ABI allows programs to access up to&n;&t; * a few hundred bytes below the stack pointer.&n;&t; * The kernel signal delivery code writes up to about 1.5kB&n;&t; * below the stack pointer (r1) before decrementing it.&n;&t; * The exec code can write slightly over 640kB to the stack&n;&t; * before setting the user r1.  Thus we allow the stack to&n;&t; * expand to 1MB without further checks.&n;&t; */
r_if
c_cond
(paren
id|address
op_plus
l_int|0x100000
OL
id|vma-&gt;vm_end
)paren
(brace
multiline_comment|/* get user regs even if this fault is in kernel mode */
r_struct
id|pt_regs
op_star
id|uregs
op_assign
id|current-&gt;thread.regs
suffix:semicolon
r_if
c_cond
(paren
id|uregs
op_eq
l_int|NULL
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/*&n;&t;&t; * A user-mode access to an address a long way below&n;&t;&t; * the stack pointer is only valid if the instruction&n;&t;&t; * is one which would update the stack pointer to the&n;&t;&t; * address accessed if the instruction completed,&n;&t;&t; * i.e. either stwu rs,n(r1) or stwux rs,r1,rb&n;&t;&t; * (or the byte, halfword, float or double forms).&n;&t;&t; *&n;&t;&t; * If we don&squot;t check this then any write to the area&n;&t;&t; * between the last mapped region and the stack will&n;&t;&t; * expand the stack rather than segfaulting.&n;&t;&t; */
r_if
c_cond
(paren
id|address
op_plus
l_int|2048
OL
id|uregs-&gt;gpr
(braket
l_int|1
)braket
op_logical_and
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_or
op_logical_neg
id|store_updates_sp
c_func
(paren
id|regs
)paren
)paren
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
id|good_area
suffix:colon
id|code
op_assign
id|SEGV_ACCERR
suffix:semicolon
macro_line|#if defined(CONFIG_6xx)
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x95700000
)paren
multiline_comment|/* an error such as lwarx to I/O controller space,&n;&t;&t;   address matching DABR, eciwx, etc. */
r_goto
id|bad_area
suffix:semicolon
macro_line|#endif /* CONFIG_6xx */
macro_line|#if defined(CONFIG_8xx)
multiline_comment|/* The MPC8xx seems to always set 0x80000000, which is&n;         * &quot;undefined&quot;.  Of those that can be set, this is the only&n;         * one which seems bad.&n;         */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x10000000
)paren
multiline_comment|/* Guarded storage error. */
r_goto
id|bad_area
suffix:semicolon
macro_line|#endif /* CONFIG_8xx */
multiline_comment|/* a write */
r_if
c_cond
(paren
id|is_write
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
macro_line|#if defined(CONFIG_4xx)
multiline_comment|/* an exec  - 4xx allows for per-page execute permission */
)brace
r_else
r_if
c_cond
(paren
id|TRAP
c_func
(paren
id|regs
)paren
op_eq
l_int|0x400
)paren
(brace
id|pte_t
op_star
id|ptep
suffix:semicolon
macro_line|#if 0
multiline_comment|/* It would be nice to actually enforce the VM execute&n;&t;&t;   permission on CPUs which can do so, but far too&n;&t;&t;   much stuff in userspace doesn&squot;t get the permissions&n;&t;&t;   right, so we let any page be executed for now. */
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
macro_line|#endif
multiline_comment|/* Since 4xx supports per-page execute permission,&n;&t;&t; * we lazily flush dcache to icache. */
id|ptep
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|get_pteptr
c_func
(paren
id|mm
comma
id|address
comma
op_amp
id|ptep
)paren
op_logical_and
id|pte_present
c_func
(paren
op_star
id|ptep
)paren
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
)paren
(brace
r_int
r_int
id|phys
op_assign
id|page_to_pfn
c_func
(paren
id|page
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|__flush_dcache_icache_phys
c_func
(paren
id|phys
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
id|pte_update
c_func
(paren
id|ptep
comma
l_int|0
comma
id|_PAGE_HWEXEC
)paren
suffix:semicolon
id|_tlbie
c_func
(paren
id|address
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|ptep
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
)brace
r_if
c_cond
(paren
id|ptep
op_ne
l_int|NULL
)paren
id|pte_unmap
c_func
(paren
id|ptep
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* a read */
)brace
r_else
(brace
multiline_comment|/* protection fault */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|0x08000000
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
id|survive
suffix:colon
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
id|is_write
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
multiline_comment|/*&n;&t; * keep track of tlb+htab misses that are good addrs but&n;&t; * just need pte&squot;s created via handle_mm_fault()&n;&t; * -- Cort&n;&t; */
id|pte_misses
op_increment
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
id|pte_errors
op_increment
suffix:semicolon
multiline_comment|/* User mode accesses cause a SIGSEGV */
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
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
id|code
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
)brace
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGSEGV
)paren
suffix:semicolon
r_return
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
l_string|&quot;VM: killing process %s&bslash;n&quot;
comma
id|current-&gt;comm
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
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGKILL
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
id|force_sig_info
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
id|bad_page_fault
c_func
(paren
id|regs
comma
id|address
comma
id|SIGBUS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * bad_page_fault is called when we have a bad access from the kernel.&n; * It is called from do_page_fault above and from some of the procedures&n; * in traps.c.&n; */
r_void
DECL|function|bad_page_fault
id|bad_page_fault
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
comma
r_int
id|sig
)paren
(brace
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
r_const
r_struct
id|exception_table_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* Are we prepared to handle this fault?  */
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;nip
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|regs-&gt;nip
op_assign
id|entry-&gt;fixup
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* kernel has accessed a bad area */
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_if
c_cond
(paren
id|debugger_kernel_faults
)paren
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|die
c_func
(paren
l_string|&quot;kernel access of bad area&quot;
comma
id|regs
comma
id|sig
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_8xx
multiline_comment|/* The pgtable.h claims some functions generically exist, but I&n; * can&squot;t find them......&n; */
DECL|function|va_to_pte
id|pte_t
op_star
id|va_to_pte
c_func
(paren
r_int
r_int
id|address
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_if
c_cond
(paren
id|address
OL
id|TASK_SIZE
)paren
r_return
l_int|NULL
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|address
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_logical_and
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
op_logical_and
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
r_return
id|pte
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|va_to_phys
r_int
r_int
id|va_to_phys
c_func
(paren
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte
op_assign
id|va_to_pte
c_func
(paren
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
r_return
(paren
(paren
r_int
r_int
)paren
(paren
id|pte_val
c_func
(paren
op_star
id|pte
)paren
)paren
op_amp
id|PAGE_MASK
)paren
op_or
(paren
id|address
op_amp
op_complement
(paren
id|PAGE_MASK
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|print_8xx_pte
id|print_8xx_pte
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
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pte @ 0x%8lx: &quot;
comma
id|addr
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
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_logical_and
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; (0x%08lx)-&gt;(0x%08lx)-&gt;0x%08lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|pgd
comma
(paren
r_int
)paren
id|pte
comma
(paren
r_int
)paren
id|pte_val
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
DECL|macro|pp
mdefine_line|#define pp ((long)pte_val(*pte))&t;&t;&t;
id|printk
c_func
(paren
l_string|&quot; RPN: %05lx PP: %lx SPS: %lx SH: %lx &quot;
l_string|&quot;CI: %lx v: %lx&bslash;n&quot;
comma
id|pp
op_rshift
l_int|12
comma
multiline_comment|/* rpn */
(paren
id|pp
op_rshift
l_int|10
)paren
op_amp
l_int|3
comma
multiline_comment|/* pp */
(paren
id|pp
op_rshift
l_int|3
)paren
op_amp
l_int|1
comma
multiline_comment|/* small */
(paren
id|pp
op_rshift
l_int|2
)paren
op_amp
l_int|1
comma
multiline_comment|/* shared */
(paren
id|pp
op_rshift
l_int|1
)paren
op_amp
l_int|1
comma
multiline_comment|/* cache inhibit */
id|pp
op_amp
l_int|1
multiline_comment|/* valid */
)paren
suffix:semicolon
DECL|macro|pp
macro_line|#undef pp&t;&t;&t;
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;no pte&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;no pmd&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;no pgd&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|get_8xx_pte
id|get_8xx_pte
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
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_logical_and
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
id|retval
op_assign
(paren
r_int
)paren
id|pte_val
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_8xx */
eof
