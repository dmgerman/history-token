multiline_comment|/*&n; *&t;TLB shootdown specifics for PPC&n; *&n; * Copyright (C) 2002 Paul Mackerras, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC_TLB_H
DECL|macro|_PPC_TLB_H
mdefine_line|#define _PPC_TLB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#ifdef CONFIG_PPC_STD_MMU
multiline_comment|/* Classic PPC with hash-table based MMU... */
r_struct
id|free_pte_ctx
suffix:semicolon
r_extern
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
multiline_comment|/* Get the generic bits... */
macro_line|#include &lt;asm-generic/tlb.h&gt;
multiline_comment|/* Nothing needed here in fact... */
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma)&t;do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;do { } while (0)
r_extern
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
id|address
)paren
suffix:semicolon
DECL|function|__tlb_remove_tlb_entry
r_static
r_inline
r_void
id|__tlb_remove_tlb_entry
c_func
(paren
r_struct
id|mmu_gather
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
id|flush_hash_entry
c_func
(paren
id|tlb-&gt;mm
comma
id|ptep
comma
id|address
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Embedded PPC with software-loaded TLB, very simple... */
DECL|struct|flush_tlb_arch
r_struct
id|flush_tlb_arch
(brace
)brace
suffix:semicolon
DECL|macro|tlb_init_arch
mdefine_line|#define tlb_init_arch(tlb, full_flush)&t;do { } while (0)
DECL|macro|tlb_finish_arch
mdefine_line|#define tlb_finish_arch(tlb)&t;&t;do { } while (0)
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma)&t;&t;do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&t;do { } while (0)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, pte, address) do { } while (0)
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;&t;&t;flush_tlb_mm((tlb)-&gt;mm)
multiline_comment|/* Get the generic bits... */
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif /* CONFIG_PPC_STD_MMU */
macro_line|#endif /* __PPC_TLB_H */
eof
