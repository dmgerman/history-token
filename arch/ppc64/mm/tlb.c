multiline_comment|/*&n; * This file contains the routines for flushing entries from the&n; * TLB and MMU hash table.&n; *&n; *  Derived from arch/ppc64/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Dave Engebretsen &lt;engebret@us.ibm.com&gt;&n; *      Rework for PPC64 port.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|ppc64_tlb_batch
comma
id|ppc64_tlb_batch
)paren
suffix:semicolon
multiline_comment|/* This is declared as we are using the more or less generic&n; * include/asm-ppc64/tlb.h file -- tgall&n; */
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|pte_freelist_batch
op_star
comma
id|pte_freelist_cur
)paren
suffix:semicolon
DECL|variable|pte_freelist_forced_free
r_int
r_int
id|pte_freelist_forced_free
suffix:semicolon
multiline_comment|/*&n; * Update the MMU hash table to correspond with a change to&n; * a Linux PTE.  If wrprot is true, it is permissible to&n; * change the existing HPTE to read-only rather than removing it&n; * (if we remove it we should clear the _PTE_HPTEFLAGS bits).&n; */
DECL|function|hpte_update
r_void
id|hpte_update
c_func
(paren
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|pte
comma
r_int
id|wrprot
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
id|addr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|context
op_assign
l_int|0
suffix:semicolon
r_struct
id|ppc64_tlb_batch
op_star
id|batch
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|ppc64_tlb_batch
)paren
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
op_star
id|PTRS_PER_PTE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|addr
)paren
op_eq
id|USER_REGION_ID
)paren
id|context
op_assign
id|mm-&gt;context.id
suffix:semicolon
id|i
op_assign
id|batch-&gt;index
suffix:semicolon
multiline_comment|/*&n;&t; * This can happen when we are in the middle of a TLB batch and&n;&t; * we encounter memory pressure (eg copy_page_range when it tries&n;&t; * to allocate a new pte). If we have to reclaim memory and end&n;&t; * up scanning and resetting referenced bits then our batch context&n;&t; * will change mid stream.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|i
op_ne
l_int|0
op_logical_and
id|context
op_ne
id|batch-&gt;context
)paren
)paren
(brace
id|flush_tlb_pending
c_func
(paren
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|batch-&gt;context
op_assign
id|context
suffix:semicolon
id|batch-&gt;mm
op_assign
id|mm
suffix:semicolon
)brace
id|batch-&gt;pte
(braket
id|i
)braket
op_assign
id|__pte
c_func
(paren
id|pte
)paren
suffix:semicolon
id|batch-&gt;addr
(braket
id|i
)braket
op_assign
id|addr
suffix:semicolon
id|batch-&gt;index
op_assign
op_increment
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|PPC64_TLB_BATCH_NR
)paren
id|flush_tlb_pending
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb_pending
r_void
id|__flush_tlb_pending
c_func
(paren
r_struct
id|ppc64_tlb_batch
op_star
id|batch
)paren
(brace
r_int
id|i
suffix:semicolon
id|cpumask_t
id|tmp
op_assign
id|cpumask_of_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|i
op_assign
id|batch-&gt;index
suffix:semicolon
r_if
c_cond
(paren
id|cpus_equal
c_func
(paren
id|batch-&gt;mm-&gt;cpu_vm_mask
comma
id|tmp
)paren
)paren
id|local
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
id|flush_hash_page
c_func
(paren
id|batch-&gt;context
comma
id|batch-&gt;addr
(braket
l_int|0
)braket
comma
id|batch-&gt;pte
(braket
l_int|0
)braket
comma
id|local
)paren
suffix:semicolon
r_else
id|flush_hash_range
c_func
(paren
id|batch-&gt;context
comma
id|i
comma
id|local
)paren
suffix:semicolon
id|batch-&gt;index
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|pte_free_smp_sync
r_static
r_void
id|pte_free_smp_sync
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
multiline_comment|/* Do nothing, just ensure we sync with all CPUs */
)brace
macro_line|#endif
multiline_comment|/* This is only called when we are critically out of memory&n; * (and fail to get a page in pte_free_tlb).&n; */
DECL|function|pte_free_now
r_void
id|pte_free_now
c_func
(paren
r_struct
id|page
op_star
id|ptepage
)paren
(brace
id|pte_freelist_forced_free
op_increment
suffix:semicolon
id|smp_call_function
c_func
(paren
id|pte_free_smp_sync
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|pte_free
c_func
(paren
id|ptepage
)paren
suffix:semicolon
)brace
DECL|function|pte_free_rcu_callback
r_static
r_void
id|pte_free_rcu_callback
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|pte_freelist_batch
op_star
id|batch
op_assign
id|arg
suffix:semicolon
r_int
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
id|i
OL
id|batch-&gt;index
suffix:semicolon
id|i
op_increment
)paren
id|pte_free
c_func
(paren
id|batch-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|batch
)paren
suffix:semicolon
)brace
DECL|function|pte_free_submit
r_void
id|pte_free_submit
c_func
(paren
r_struct
id|pte_freelist_batch
op_star
id|batch
)paren
(brace
id|INIT_RCU_HEAD
c_func
(paren
op_amp
id|batch-&gt;rcu
)paren
suffix:semicolon
id|call_rcu
c_func
(paren
op_amp
id|batch-&gt;rcu
comma
id|pte_free_rcu_callback
comma
id|batch
)paren
suffix:semicolon
)brace
DECL|function|pte_free_finish
r_void
id|pte_free_finish
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This is safe as we are holding page_table_lock */
r_struct
id|pte_freelist_batch
op_star
op_star
id|batchp
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|pte_freelist_cur
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|batchp
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|pte_free_submit
c_func
(paren
op_star
id|batchp
)paren
suffix:semicolon
op_star
id|batchp
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
