multiline_comment|/*&n; * This file contains the routines for TLB flushing.&n; * On machines where the MMU uses a hash table to store virtual to&n; * physical translations, these routines flush entries from the&n; * hash table also.&n; *  -- paulus&n; *&n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &quot;mmu_decl.h&quot;
multiline_comment|/*&n; * Called when unmapping pages to flush entries from the TLB/hash table.&n; */
DECL|function|flush_hash_entry
r_void
id|flush_hash_entry
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|ptephys
suffix:semicolon
r_if
c_cond
(paren
id|Hash
op_ne
l_int|0
)paren
(brace
id|ptephys
op_assign
id|__pa
c_func
(paren
id|ptep
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|flush_hash_pages
c_func
(paren
id|mm-&gt;context
comma
id|addr
comma
id|ptephys
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called by ptep_test_and_clear_young()&n; */
DECL|function|flush_hash_one_pte
r_void
id|flush_hash_one_pte
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_struct
id|page
op_star
id|ptepage
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_int
r_int
id|ptephys
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|Hash
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|ptepage
op_assign
id|virt_to_page
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|mm
op_assign
(paren
r_struct
id|mm_struct
op_star
)paren
id|ptepage-&gt;mapping
suffix:semicolon
id|ptephys
op_assign
id|__pa
c_func
(paren
id|ptep
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|addr
op_assign
id|ptepage-&gt;index
op_plus
(paren
(paren
(paren
r_int
r_int
)paren
id|ptep
op_amp
op_complement
id|PAGE_MASK
)paren
op_lshift
l_int|10
)paren
suffix:semicolon
id|flush_hash_pages
c_func
(paren
id|mm-&gt;context
comma
id|addr
comma
id|ptephys
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by ptep_set_access_flags, must flush on CPUs for which the&n; * DSI handler can&squot;t just &quot;fixup&quot; the TLB on a write fault&n; */
DECL|function|flush_tlb_page_nohash
r_void
id|flush_tlb_page_nohash
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
)paren
(brace
r_if
c_cond
(paren
id|Hash
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|_tlbie
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called at the end of a mmu_gather operation to make sure the&n; * TLB flush is completely done.&n; */
DECL|function|tlb_flush
r_void
id|tlb_flush
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
)paren
(brace
r_if
c_cond
(paren
id|Hash
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * 603 needs to flush the whole TLB here since&n;&t;&t; * it doesn&squot;t use a hash table.&n;&t;&t; */
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *  - flush_tlb_kernel_range(start, end) flushes kernel pages&n; *&n; * since the hardware hash table functions as an extension of the&n; * tlb as far as the linux tables are concerned, flush it too.&n; *    -- Cort&n; */
multiline_comment|/*&n; * 750 SMP is a Bad Idea because the 750 doesn&squot;t broadcast all&n; * the cache operations on the bus.  Hence we need to use an IPI&n; * to get the other CPU(s) to invalidate their TLBs.&n; */
macro_line|#ifdef CONFIG_SMP_750
DECL|macro|FINISH_FLUSH
mdefine_line|#define FINISH_FLUSH&t;smp_send_tlb_invalidate(0)
macro_line|#else
DECL|macro|FINISH_FLUSH
mdefine_line|#define FINISH_FLUSH&t;do { } while (0)
macro_line|#endif
DECL|function|flush_range
r_static
r_void
id|flush_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|pmd_end
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
r_int
id|ctx
op_assign
id|mm-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|Hash
op_eq
l_int|0
)paren
(brace
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
suffix:semicolon
id|end
op_assign
(paren
id|end
op_minus
l_int|1
)paren
op_or
op_complement
id|PAGE_MASK
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|mm
comma
id|start
)paren
comma
id|start
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|pmd_end
op_assign
(paren
(paren
id|start
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pmd_end
OG
id|end
)paren
id|pmd_end
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|count
op_assign
(paren
(paren
id|pmd_end
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_plus
l_int|1
suffix:semicolon
id|flush_hash_pages
c_func
(paren
id|ctx
comma
id|start
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
comma
id|count
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_end
op_eq
id|end
)paren
r_break
suffix:semicolon
id|start
op_assign
id|pmd_end
op_plus
l_int|1
suffix:semicolon
op_increment
id|pmd
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Flush kernel TLB entries in the given range&n; */
DECL|function|flush_tlb_kernel_range
r_void
id|flush_tlb_kernel_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|flush_range
c_func
(paren
op_amp
id|init_mm
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|FINISH_FLUSH
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush all the (user) entries for the address space described by mm.&n; */
DECL|function|flush_tlb_mm
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|mp
suffix:semicolon
r_if
c_cond
(paren
id|Hash
op_eq
l_int|0
)paren
(brace
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|mp
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|mp
op_ne
l_int|NULL
suffix:semicolon
id|mp
op_assign
id|mp-&gt;vm_next
)paren
id|flush_range
c_func
(paren
id|mp-&gt;vm_mm
comma
id|mp-&gt;vm_start
comma
id|mp-&gt;vm_end
)paren
suffix:semicolon
id|FINISH_FLUSH
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_if
c_cond
(paren
id|Hash
op_eq
l_int|0
)paren
(brace
id|_tlbie
c_func
(paren
id|vmaddr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mm
op_assign
(paren
id|vmaddr
OL
id|TASK_SIZE
)paren
ques
c_cond
id|vma-&gt;vm_mm
suffix:colon
op_amp
id|init_mm
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|mm
comma
id|vmaddr
)paren
comma
id|vmaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
id|flush_hash_pages
c_func
(paren
id|mm-&gt;context
comma
id|vmaddr
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
comma
l_int|1
)paren
suffix:semicolon
id|FINISH_FLUSH
suffix:semicolon
)brace
multiline_comment|/*&n; * For each address in the range, find the pte for the address&n; * and check _PAGE_HASHPTE bit; if it is set, find and destroy&n; * the corresponding HPTE.&n; */
DECL|function|flush_tlb_range
r_void
id|flush_tlb_range
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
id|flush_range
c_func
(paren
id|vma-&gt;vm_mm
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|FINISH_FLUSH
suffix:semicolon
)brace
eof
