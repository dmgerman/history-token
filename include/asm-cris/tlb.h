macro_line|#ifndef _CRIS_TLB_H
DECL|macro|_CRIS_TLB_H
mdefine_line|#define _CRIS_TLB_H
macro_line|#include &lt;asm/arch/tlb.h&gt;
multiline_comment|/*&n; * cris doesn&squot;t need any special per-pte or&n; * per-vma handling..&n; */
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma) do { } while (0)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, ptep, address) do { } while (0)
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb) flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif
eof
