multiline_comment|/*&n; *&t;TLB shootdown specifics for PPC64&n; *&n; * Copyright (C) 2002 Anton Blanchard, IBM Corp.&n; * Copyright (C) 2002 Paul Mackerras, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_TLB_H
DECL|macro|_PPC64_TLB_H
mdefine_line|#define _PPC64_TLB_H
macro_line|#include &lt;asm/tlbflush.h&gt;
r_struct
id|mmu_gather
suffix:semicolon
r_extern
r_void
id|pte_free_finish
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|tlb_flush
r_static
r_inline
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
id|flush_tlb_pending
c_func
(paren
)paren
suffix:semicolon
id|pte_free_finish
c_func
(paren
)paren
suffix:semicolon
)brace
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
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, pte, address) do { } while (0)
macro_line|#endif /* _PPC64_TLB_H */
eof
