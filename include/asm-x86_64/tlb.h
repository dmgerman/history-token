macro_line|#ifndef TLB_H
DECL|macro|TLB_H
mdefine_line|#define TLB_H 1
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma) do { } while (0)
DECL|macro|tlb_remove_tlb_entry
mdefine_line|#define tlb_remove_tlb_entry(tlb, pte, address) do { } while (0)
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb) flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif
eof
