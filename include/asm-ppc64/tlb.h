multiline_comment|/*&n; *&t;TLB shootdown specifics for PPC64&n; *&n; * Copyright (C) 2002 Anton Blanchard, IBM Corp.&n; * Copyright (C) 2002 Paul Mackerras, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_TLB_H
DECL|macro|_PPC64_TLB_H
mdefine_line|#define _PPC64_TLB_H
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
r_struct
id|free_pte_ctx
suffix:semicolon
r_static
r_inline
r_void
id|tlb_flush
c_func
(paren
r_struct
id|free_pte_ctx
op_star
id|tlb
)paren
suffix:semicolon
multiline_comment|/* Avoid pulling in another include just for this */
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
multiline_comment|/* Get the generic bits... */
macro_line|#include &lt;asm-generic/tlb.h&gt;
multiline_comment|/* Nothing needed here in fact... */
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma)&t;do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;do { } while (0)
multiline_comment|/* Should make this at least as large as the generic batch size, but it&n; * takes up too much space */
DECL|macro|PPC64_TLB_BATCH_NR
mdefine_line|#define PPC64_TLB_BATCH_NR 192
DECL|struct|ppc64_tlb_batch
r_struct
id|ppc64_tlb_batch
(brace
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|pte
id|pte_t
id|pte
(braket
id|PPC64_TLB_BATCH_NR
)braket
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
(braket
id|PPC64_TLB_BATCH_NR
)braket
suffix:semicolon
DECL|member|vaddr
r_int
r_int
id|vaddr
(braket
id|PPC64_TLB_BATCH_NR
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ppc64_tlb_batch
id|ppc64_tlb_batch
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|__tlb_remove_tlb_entry
r_static
r_inline
r_void
id|__tlb_remove_tlb_entry
c_func
(paren
id|mmu_gather_t
op_star
id|tlb
comma
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|address
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|ppc64_tlb_batch
op_star
id|batch
op_assign
op_amp
id|ppc64_tlb_batch
(braket
id|cpu
)braket
suffix:semicolon
r_int
r_int
id|i
op_assign
id|batch-&gt;index
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_HASHPTE
)paren
(brace
id|pte
op_assign
id|__pte
c_func
(paren
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_HPTEFLAGS
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_HASHPTE
)paren
(brace
id|batch-&gt;pte
(braket
id|i
)braket
op_assign
id|pte
suffix:semicolon
id|batch-&gt;addr
(braket
id|i
)braket
op_assign
id|address
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|PPC64_TLB_BATCH_NR
)paren
(brace
r_int
id|local
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tlb-&gt;mm-&gt;cpu_vm_mask
op_eq
(paren
l_int|1
op_lshift
id|cpu
)paren
)paren
id|local
op_assign
l_int|1
suffix:semicolon
id|flush_hash_range
c_func
(paren
id|tlb-&gt;mm-&gt;context
comma
id|i
comma
id|local
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|batch-&gt;index
op_assign
id|i
suffix:semicolon
)brace
DECL|function|tlb_flush
r_static
r_inline
r_void
id|tlb_flush
c_func
(paren
r_struct
id|free_pte_ctx
op_star
id|tlb
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|ppc64_tlb_batch
op_star
id|batch
op_assign
op_amp
id|ppc64_tlb_batch
(braket
id|cpu
)braket
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tlb-&gt;mm-&gt;cpu_vm_mask
op_eq
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
id|local
op_assign
l_int|1
suffix:semicolon
id|flush_hash_range
c_func
(paren
id|tlb-&gt;mm-&gt;context
comma
id|batch-&gt;index
comma
id|local
)paren
suffix:semicolon
id|batch-&gt;index
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* _PPC64_TLB_H */
eof
