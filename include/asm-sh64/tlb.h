multiline_comment|/*&n; * include/asm-sh64/tlb.h&n; *&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#ifndef __ASM_SH64_TLB_H
DECL|macro|__ASM_SH64_TLB_H
mdefine_line|#define __ASM_SH64_TLB_H
multiline_comment|/*&n; * Note! These are mostly unused, we just need the xTLB_LAST_VAR_UNRESTRICTED&n; * for head.S! Once this limitation is gone, we can clean the rest of this up.&n; */
multiline_comment|/* ITLB defines */
DECL|macro|ITLB_FIXED
mdefine_line|#define ITLB_FIXED&t;0x00000000&t;/* First fixed ITLB, see head.S */
DECL|macro|ITLB_LAST_VAR_UNRESTRICTED
mdefine_line|#define ITLB_LAST_VAR_UNRESTRICTED&t;0x000003F0&t;/* Last ITLB */
multiline_comment|/* DTLB defines */
DECL|macro|DTLB_FIXED
mdefine_line|#define DTLB_FIXED&t;0x00800000&t;/* First fixed DTLB, see head.S */
DECL|macro|DTLB_LAST_VAR_UNRESTRICTED
mdefine_line|#define DTLB_LAST_VAR_UNRESTRICTED&t;0x008003F0&t;/* Last DTLB */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/**&n; * for_each_dtlb_entry&n; *&n; * @tlb:&t;TLB entry&n; *&n; * Iterate over free (non-wired) DTLB entries&n; */
DECL|macro|for_each_dtlb_entry
mdefine_line|#define for_each_dtlb_entry(tlb)&t;&t;&bslash;&n;&t;for (tlb  = cpu_data-&gt;dtlb.first;&t;&bslash;&n;&t;     tlb &lt;= cpu_data-&gt;dtlb.last;&t;&bslash;&n;&t;     tlb += cpu_data-&gt;dtlb.step)
multiline_comment|/**&n; * for_each_itlb_entry&n; *&n; * @tlb:&t;TLB entry&n; *&n; * Iterate over free (non-wired) ITLB entries&n; */
DECL|macro|for_each_itlb_entry
mdefine_line|#define for_each_itlb_entry(tlb)&t;&t;&bslash;&n;&t;for (tlb  = cpu_data-&gt;itlb.first;&t;&bslash;&n;&t;     tlb &lt;= cpu_data-&gt;itlb.last;&t;&bslash;&n;&t;     tlb += cpu_data-&gt;itlb.step)
multiline_comment|/**&n; * __flush_tlb_slot&n; *&n; * @slot:&t;Address of TLB slot.&n; *&n; * Flushes TLB slot @slot.&n; */
DECL|function|__flush_tlb_slot
r_static
r_inline
r_void
id|__flush_tlb_slot
c_func
(paren
r_int
r_int
r_int
id|slot
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;putcfg %0, 0, r63&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|slot
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* arch/sh64/mm/tlb.c */
r_extern
r_int
id|sh64_tlb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|sh64_next_free_dtlb_entry
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|sh64_get_wired_dtlb_entry
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sh64_put_wired_dtlb_entry
c_func
(paren
r_int
r_int
r_int
id|entry
)paren
suffix:semicolon
r_extern
r_void
id|sh64_setup_tlb_slot
c_func
(paren
r_int
r_int
r_int
id|config_addr
comma
r_int
r_int
id|eaddr
comma
r_int
r_int
id|asid
comma
r_int
r_int
id|paddr
)paren
suffix:semicolon
r_extern
r_void
id|sh64_teardown_tlb_slot
c_func
(paren
r_int
r_int
r_int
id|config_addr
)paren
suffix:semicolon
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) &bslash;&n;&t;flush_cache_range(vma, vma-&gt;vm_start, vma-&gt;vm_end)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&bslash;&n;&t;flush_tlb_range(vma, vma-&gt;vm_start, vma-&gt;vm_end)
DECL|macro|__tlb_remove_tlb_entry
mdefine_line|#define __tlb_remove_tlb_entry(tlb, pte, address)&t;do { } while (0)
multiline_comment|/*&n; * Flush whole TLBs for MM&n; */
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;&t;flush_tlb_mm((tlb)-&gt;mm)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_SH64_TLB_H */
eof
