macro_line|#ifndef _SPARC64_TLB_H
DECL|macro|_SPARC64_TLB_H
mdefine_line|#define _SPARC64_TLB_H
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;&t;&t;&bslash;&n;do {&t;if ((tlb)-&gt;fullmm)&t;&t;&bslash;&n;&t;&t;flush_tlb_mm((tlb)-&gt;mm);&bslash;&n;} while (0)
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) &bslash;&n;do {&t;if (!(tlb)-&gt;fullmm)&t;&bslash;&n;&t;&t;flush_cache_range(vma, vma-&gt;vm_start, vma-&gt;vm_end); &bslash;&n;} while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&bslash;&n;do {&t;if (!(tlb)-&gt;fullmm)&t;&bslash;&n;&t;&t;flush_tlb_range(vma, vma-&gt;vm_start, vma-&gt;vm_end); &bslash;&n;} while (0)
DECL|macro|tlb_remove_tlb_entry
mdefine_line|#define tlb_remove_tlb_entry(tlb, pte, address) &bslash;&n;&t;do { } while (0)
macro_line|#include &lt;asm-generic/tlb.h&gt;
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(tlb, pmd)&t;pmd_free(pmd)
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(tlb, pte)&t;pte_free(pte)
macro_line|#endif /* _SPARC64_TLB_H */
eof
