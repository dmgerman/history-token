macro_line|#ifndef _SPARC_TLB_H
DECL|macro|_SPARC_TLB_H
mdefine_line|#define _SPARC_TLB_H
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flush_cache_range(vma, vma-&gt;vm_start, vma-&gt;vm_end);&t;&bslash;&n;} while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma) &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flush_tlb_range(vma, vma-&gt;vm_start, vma-&gt;vm_end);&t;&bslash;&n;} while (0)
DECL|macro|tlb_remove_tlb_entry
mdefine_line|#define tlb_remove_tlb_entry(tlb, pte, address) &bslash;&n;&t;do { } while (0)
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb) &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flush_tlb_mm((tlb)-&gt;mm);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif /* _SPARC_TLB_H */
eof
