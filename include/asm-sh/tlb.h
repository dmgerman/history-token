macro_line|#ifndef __ASM_SH_TLB_H
DECL|macro|__ASM_SH_TLB_H
mdefine_line|#define __ASM_SH_TLB_H
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) &bslash;&n;&t;flush_cache_range(vma, vma-&gt;vm_start, vma-&gt;vm_end)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&bslash;&n;&t;flush_tlb_range(vma, vma-&gt;vm_start, vma-&gt;vm_end)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, pte, address)&t;do { } while (0)
multiline_comment|/*&n; * Flush whole TLBs for MM&n; */
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;&t;&t;&t;flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif
eof
