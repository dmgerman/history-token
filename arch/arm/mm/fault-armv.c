multiline_comment|/*&n; *  linux/arch/arm/mm/fault-armv.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
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
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|do_page_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|do_translation_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|do_bad_area
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
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
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALIGNMENT_TRAP
r_extern
r_int
id|do_alignment
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
DECL|macro|do_alignment
mdefine_line|#define do_alignment do_bad
macro_line|#endif
multiline_comment|/*&n; * Some section permission faults need to be handled gracefully.&n; * They can happen due to a __{get,put}_user during an oops.&n; */
r_static
r_int
DECL|function|do_sect_fault
id|do_sect_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
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
op_assign
id|current
suffix:semicolon
id|do_bad_area
c_func
(paren
id|tsk
comma
id|tsk-&gt;active_mm
comma
id|addr
comma
id|error_code
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Hook for things that need to trap external faults.  Note that&n; * we don&squot;t guarantee that this will be the final version of the&n; * interface.&n; */
DECL|variable|external_fault
r_int
(paren
op_star
id|external_fault
)paren
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
suffix:semicolon
r_static
r_int
DECL|function|do_external_fault
id|do_external_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
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
id|external_fault
)paren
r_return
id|external_fault
c_func
(paren
id|addr
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This abort handler always returns &quot;fault&quot;.&n; */
r_static
r_int
DECL|function|do_bad
id|do_bad
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|struct|fsr_info
r_static
r_const
r_struct
id|fsr_info
(brace
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
id|addr
comma
r_int
id|error_code
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|variable|fsr_info
)brace
id|fsr_info
(braket
)braket
op_assign
(brace
(brace
id|do_bad
comma
id|SIGSEGV
comma
l_string|&quot;vector exception&quot;
)brace
comma
(brace
id|do_alignment
comma
id|SIGILL
comma
l_string|&quot;alignment exception&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGKILL
comma
l_string|&quot;terminal exception&quot;
)brace
comma
(brace
id|do_alignment
comma
id|SIGILL
comma
l_string|&quot;alignment exception&quot;
)brace
comma
(brace
id|do_external_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on linefetch&quot;
)brace
comma
(brace
id|do_translation_fault
comma
id|SIGSEGV
comma
l_string|&quot;section translation fault&quot;
)brace
comma
(brace
id|do_external_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on linefetch&quot;
)brace
comma
(brace
id|do_page_fault
comma
id|SIGSEGV
comma
l_string|&quot;page translation fault&quot;
)brace
comma
(brace
id|do_external_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on non-linefetch&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGSEGV
comma
l_string|&quot;section domain fault&quot;
)brace
comma
(brace
id|do_external_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on non-linefetch&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGSEGV
comma
l_string|&quot;page domain fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on translation&quot;
)brace
comma
(brace
id|do_sect_fault
comma
id|SIGSEGV
comma
l_string|&quot;section permission fault&quot;
)brace
comma
(brace
id|do_bad
comma
id|SIGBUS
comma
l_string|&quot;external abort on translation&quot;
)brace
comma
(brace
id|do_page_fault
comma
id|SIGSEGV
comma
l_string|&quot;page permission fault&quot;
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Dispatch a data abort to the relevant handler.&n; */
id|asmlinkage
r_void
DECL|function|do_DataAbort
id|do_DataAbort
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
r_const
r_struct
id|fsr_info
op_star
id|inf
op_assign
id|fsr_info
op_plus
(paren
id|fsr
op_amp
l_int|15
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inf
op_member_access_from_pointer
id|fn
c_func
(paren
id|addr
comma
id|fsr
comma
id|regs
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unhandled fault: %s (0x%03x) at 0x%08lx&bslash;n&quot;
comma
id|inf-&gt;name
comma
id|fsr
comma
id|addr
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|inf-&gt;sig
comma
id|current
)paren
suffix:semicolon
id|show_pte
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
id|asmlinkage
r_void
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
id|do_translation_fault
c_func
(paren
id|addr
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We take the easy way out of this problem - we make the&n; * PTE uncacheable.  However, we leave the write buffer on.&n; */
DECL|function|adjust_pte
r_static
r_void
id|adjust_pte
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
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
comma
id|entry
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|bad_pgd
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
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
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
r_goto
id|bad_pmd
suffix:semicolon
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|entry
op_assign
op_star
id|pte
suffix:semicolon
multiline_comment|/*&n;&t; * If this page isn&squot;t present, or is already setup to&n;&t; * fault (ie, is old), we can safely ignore any issues.&n;&t; */
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|entry
)paren
op_logical_and
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
id|L_PTE_CACHEABLE
)paren
(brace
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|entry
)paren
op_and_assign
op_complement
id|L_PTE_CACHEABLE
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|entry
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
)brace
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bad_pgd
suffix:colon
id|pgd_ERROR
c_func
(paren
op_star
id|pgd
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bad_pmd
suffix:colon
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|make_coherent
id|make_coherent
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
r_int
id|pgoff
op_assign
(paren
id|addr
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|aliases
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If we have any shared mappings that are in the same mm&n;&t; * space, then we need to handle them specially to maintain&n;&t; * cache coherency.&n;&t; */
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|page-&gt;mapping-&gt;i_mmap_shared
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
r_int
r_int
id|off
suffix:semicolon
id|mpnt
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|vm_area_struct
comma
id|shared
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this VMA is not in our MM, we can ignore it.&n;&t;&t; * Note that we intentionally don&squot;t mask out the VMA&n;&t;&t; * that we are fixing up.&n;&t;&t; */
r_if
c_cond
(paren
id|mpnt-&gt;vm_mm
op_ne
id|mm
op_logical_or
id|mpnt
op_eq
id|vma
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the page isn&squot;t in this VMA, we can also ignore it.&n;&t;&t; */
r_if
c_cond
(paren
id|pgoff
OL
id|mpnt-&gt;vm_pgoff
)paren
r_continue
suffix:semicolon
id|off
op_assign
id|pgoff
op_minus
id|mpnt-&gt;vm_pgoff
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
(paren
id|mpnt-&gt;vm_end
op_minus
id|mpnt-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ok, it is within mpnt.  Fix it up.&n;&t;&t; */
id|adjust_pte
c_func
(paren
id|mpnt
comma
id|mpnt-&gt;vm_start
op_plus
(paren
id|off
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|aliases
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aliases
)paren
id|adjust_pte
c_func
(paren
id|vma
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Take care of architecture specific things when placing a new PTE into&n; * a page table, or changing an existing PTE.  Basically, there are two&n; * things that we need to take care of:&n; *&n; *  1. If PG_dcache_dirty is set for the page, we need to ensure&n; *     that any cache entries for the kernels virtual memory&n; *     range are written back to the page.&n; *  2. If we have multiple shared mappings of the same space in&n; *     an object, we need to deal with the cache aliasing issues.&n; *&n; * Note that the page_table_lock will be held.&n; */
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
id|addr
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
id|pfn
op_assign
id|pte_pfn
c_func
(paren
id|pte
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pfn_valid
c_func
(paren
id|pfn
)paren
)paren
r_return
suffix:semicolon
id|page
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
(brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|PG_dcache_dirty
comma
op_amp
id|page-&gt;flags
)paren
)paren
id|__flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|make_coherent
c_func
(paren
id|vma
comma
id|addr
comma
id|page
)paren
suffix:semicolon
)brace
)brace
eof
