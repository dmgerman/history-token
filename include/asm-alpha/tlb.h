macro_line|#ifndef _ALPHA_TLB_H
DECL|macro|_ALPHA_TLB_H
mdefine_line|#define _ALPHA_TLB_H
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma)&t;&t;&t;do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&t;&t;do { } while (0)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, pte, addr)&t;do { } while (0)
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;&t;&t;&t;flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
DECL|macro|__pte_free_tlb
mdefine_line|#define __pte_free_tlb(tlb,pte)&t;&t;&t;pte_free(pte)
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb,pmd)&t;&t;&t;pmd_free(pmd)
macro_line|#endif
eof
