macro_line|#ifndef __ASM_TLB_H
DECL|macro|__ASM_TLB_H
mdefine_line|#define __ASM_TLB_H
multiline_comment|/*&n; * MIPS doesn&squot;t need any special per-pte or per-vma handling, except&n; * we need to flush cache for area to be unmapped.&n; */
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) &t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!tlb-&gt;fullmm)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;flush_cache_range(vma, vma-&gt;vm_start, vma-&gt;vm_end); &bslash;&n;&t;}  while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma) do { } while (0)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, ptep, address) do { } while (0)
multiline_comment|/*&n; * .. because we flush the whole mm when it fills up.&n; */
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb) flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif /* __ASM_TLB_H */
eof
