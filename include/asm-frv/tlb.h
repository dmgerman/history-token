macro_line|#ifndef _ASM_TLB_H
DECL|macro|_ASM_TLB_H
mdefine_line|#define _ASM_TLB_H
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache() do {} while(0)
multiline_comment|/*&n; * we don&squot;t need any special per-pte or per-vma handling...&n; */
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma)&t;&t;&t;&t;do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&t;&t;&t;do { } while (0)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, ptep, address)&t;do { } while (0)
multiline_comment|/*&n; * .. because we flush the whole mm when it fills up&n; */
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;&t;flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif /* _ASM_TLB_H */
eof
