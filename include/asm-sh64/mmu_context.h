macro_line|#ifndef __ASM_SH64_MMU_CONTEXT_H
DECL|macro|__ASM_SH64_MMU_CONTEXT_H
mdefine_line|#define __ASM_SH64_MMU_CONTEXT_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/mmu_context.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * ASID handling idea taken from MIPS implementation.&n; *&n; */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Cache of MMU context last used.&n; *&n; * The MMU &quot;context&quot; consists of two things:&n; *   (a) TLB cache version (or cycle, top 24 bits of mmu_context_cache)&n; *   (b) ASID (Address Space IDentifier, bottom 8 bits of mmu_context_cache)&n; */
r_extern
r_int
r_int
id|mmu_context_cache
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* Current mm&squot;s pgd */
r_extern
id|pgd_t
op_star
id|mmu_pdtp_cache
suffix:semicolon
DECL|macro|SR_ASID_MASK
mdefine_line|#define SR_ASID_MASK&t;&t;0xffffffffff00ffffULL
DECL|macro|SR_ASID_SHIFT
mdefine_line|#define SR_ASID_SHIFT&t;&t;16
DECL|macro|MMU_CONTEXT_ASID_MASK
mdefine_line|#define MMU_CONTEXT_ASID_MASK&t;&t;0x000000ff
DECL|macro|MMU_CONTEXT_VERSION_MASK
mdefine_line|#define MMU_CONTEXT_VERSION_MASK&t;0xffffff00
DECL|macro|MMU_CONTEXT_FIRST_VERSION
mdefine_line|#define MMU_CONTEXT_FIRST_VERSION&t;0x00000100
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT&t;&t;&t;0
multiline_comment|/* ASID is 8-bit value, so it can&squot;t be 0x100 */
DECL|macro|MMU_NO_ASID
mdefine_line|#define MMU_NO_ASID&t;&t;&t;0x100
multiline_comment|/*&n; * Virtual Page Number mask&n; */
DECL|macro|MMU_VPN_MASK
mdefine_line|#define MMU_VPN_MASK&t;0xfffff000
r_extern
id|__inline__
r_void
DECL|function|get_new_mmu_context
id|get_new_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|mc
op_assign
op_increment
id|mmu_context_cache
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mc
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
)paren
(brace
multiline_comment|/* We exhaust ASID of this version.&n;&t;&t;   Flush all TLB and start new cycle. */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We have to flush all caches as ASIDs are&n;                   used in cache */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fix version if needed.&n;&t;&t;   Note that we avoid version #0/asid #0 to distingush NO_CONTEXT. */
r_if
c_cond
(paren
op_logical_neg
id|mc
)paren
id|mmu_context_cache
op_assign
id|mc
op_assign
id|MMU_CONTEXT_FIRST_VERSION
suffix:semicolon
)brace
id|mm-&gt;context
op_assign
id|mc
suffix:semicolon
)brace
multiline_comment|/*&n; * Get MMU context if needed.&n; */
r_static
id|__inline__
r_void
DECL|function|get_mmu_context
id|get_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
)paren
(brace
r_int
r_int
id|mc
op_assign
id|mmu_context_cache
suffix:semicolon
multiline_comment|/* Check if we have old version of context.&n;&t;&t;   If it&squot;s old, we need to get new context with new version. */
r_if
c_cond
(paren
(paren
id|mm-&gt;context
op_xor
id|mc
)paren
op_amp
id|MMU_CONTEXT_VERSION_MASK
)paren
id|get_new_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize the context related info for a new mm_struct&n; * instance.&n; */
DECL|function|init_new_context
r_static
r_inline
r_int
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy context related info for an mm_struct that is about&n; * to be put to rest.&n; */
DECL|function|destroy_context
r_static
r_inline
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_extern
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/* Well, at least free TLB entries */
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* __ASSEMBLY__ */
multiline_comment|/* Common defines */
DECL|macro|TLB_STEP
mdefine_line|#define TLB_STEP&t;0x00000010
DECL|macro|TLB_PTEH
mdefine_line|#define TLB_PTEH&t;0x00000000
DECL|macro|TLB_PTEL
mdefine_line|#define TLB_PTEL&t;0x00000008
multiline_comment|/* PTEH defines */
DECL|macro|PTEH_ASID_SHIFT
mdefine_line|#define PTEH_ASID_SHIFT&t;2
DECL|macro|PTEH_VALID
mdefine_line|#define PTEH_VALID&t;0x0000000000000001
DECL|macro|PTEH_SHARED
mdefine_line|#define PTEH_SHARED&t;0x0000000000000002
DECL|macro|PTEH_MATCH_ASID
mdefine_line|#define PTEH_MATCH_ASID&t;0x00000000000003ff
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* This has to be a common function because the next location to fill&n; * information is shared. */
r_extern
r_void
id|__do_tlb_refill
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
r_int
id|is_text_not_data
comma
id|pte_t
op_star
id|pte
)paren
suffix:semicolon
multiline_comment|/* Profiling counter. */
macro_line|#ifdef CONFIG_SH64_PROC_TLB
r_extern
r_int
r_int
r_int
id|calls_to_do_fast_page_fault
suffix:semicolon
macro_line|#endif
DECL|function|get_asid
r_static
r_inline
r_int
r_int
id|get_asid
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|sr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;getcon   &quot;
id|__SR
l_string|&quot;, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sr
)paren
)paren
suffix:semicolon
id|sr
op_assign
(paren
id|sr
op_rshift
id|SR_ASID_SHIFT
)paren
op_amp
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|sr
suffix:semicolon
)brace
multiline_comment|/* Set ASID into SR */
DECL|function|set_asid
r_static
r_inline
r_void
id|set_asid
c_func
(paren
r_int
r_int
id|asid
)paren
(brace
r_int
r_int
r_int
id|sr
comma
id|pc
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;getcon&t;&quot;
id|__SR
l_string|&quot;, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sr
)paren
)paren
suffix:semicolon
id|sr
op_assign
(paren
id|sr
op_amp
id|SR_ASID_MASK
)paren
op_or
(paren
id|asid
op_lshift
id|SR_ASID_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * It is possible that this function may be inlined and so to avoid&n;&t; * the assembler reporting duplicate symbols we make use of the gas trick&n;&t; * of generating symbols using numerics and forward reference.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movi&t;1, %1&bslash;n&bslash;t&quot;
l_string|&quot;shlli&t;%1, 28, %1&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%0, %1, %1&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%1, &quot;
id|__SR
l_string|&quot;&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%0, &quot;
id|__SSR
l_string|&quot;&bslash;n&bslash;t&quot;
l_string|&quot;movi&t;1f, %1&bslash;n&bslash;t&quot;
l_string|&quot;ori&t;%1, 1 , %1&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%1, &quot;
id|__SPC
l_string|&quot;&bslash;n&bslash;t&quot;
l_string|&quot;rte&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pc
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|function|activate_context
r_static
id|__inline__
r_void
id|activate_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|get_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|set_asid
c_func
(paren
id|mm-&gt;context
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
)brace
DECL|function|switch_mm
r_static
id|__inline__
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
(brace
id|mmu_pdtp_cache
op_assign
id|next-&gt;pgd
suffix:semicolon
id|activate_context
c_func
(paren
id|next
)paren
suffix:semicolon
)brace
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;do { } while (0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev, next) &bslash;&n;&t;switch_mm((prev),(next),NULL)
r_static
r_inline
r_void
DECL|function|enter_lazy_tlb
id|enter_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
)brace
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif /* __ASM_SH64_MMU_CONTEXT_H */
eof
