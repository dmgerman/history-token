multiline_comment|/*&n; * Copyright (C) 1999 Niibe Yutaka&n; * Copyright (C) 2003 Paul Mundt&n; *&n; * ASID handling idea taken from MIPS implementation.&n; */
macro_line|#ifndef __ASM_SH_MMU_CONTEXT_H
DECL|macro|__ASM_SH_MMU_CONTEXT_H
mdefine_line|#define __ASM_SH_MMU_CONTEXT_H
macro_line|#include &lt;asm/cpu/mmu_context.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * The MMU &quot;context&quot; consists of two things:&n; *    (a) TLB cache version (or round, cycle whatever expression you like)&n; *    (b) ASID (Address Space IDentifier)&n; */
multiline_comment|/*&n; * Cache of MMU context last used.&n; */
r_extern
r_int
r_int
id|mmu_context_cache
suffix:semicolon
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
macro_line|#ifdef CONFIG_MMU
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
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|mc
op_assign
id|mmu_context_cache
suffix:semicolon
multiline_comment|/* Check if we have old version of context. */
r_if
c_cond
(paren
(paren
(paren
id|mm-&gt;context
op_xor
id|mc
)paren
op_amp
id|MMU_CONTEXT_VERSION_MASK
)paren
op_eq
l_int|0
)paren
multiline_comment|/* It&squot;s up to date, do nothing */
r_return
suffix:semicolon
multiline_comment|/* It&squot;s old, we need to get new context with new version. */
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
multiline_comment|/*&n;&t;&t; * We exhaust ASID of this version.&n;&t;&t; * Flush all TLB and start new cycle.&n;&t;&t; */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Fix version; Note that we avoid version #0&n;&t;&t; * to distingush NO_CONTEXT.&n;&t;&t; */
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
multiline_comment|/*&n; * Initialize the context related info for a new mm_struct&n; * instance.&n; */
DECL|function|init_new_context
r_static
id|__inline__
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
id|__inline__
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
multiline_comment|/* Do nothing */
)brace
DECL|function|set_asid
r_static
id|__inline__
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
id|__dummy
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov.l&t;%2, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%3, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;%0, %2&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|asid
)paren
comma
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_PTEH
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0xffffff00
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_asid
r_static
id|__inline__
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
id|asid
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov.l&t;%1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|asid
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_PTEH
)paren
)paren
)paren
suffix:semicolon
id|asid
op_and_assign
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
r_return
id|asid
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
multiline_comment|/* MMU_TTB can be used for optimizing the fault handling.&n;   (Currently not used) */
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
id|likely
c_func
(paren
id|prev
op_ne
id|next
)paren
)paren
(brace
r_int
r_int
id|__pgdir
op_assign
(paren
r_int
r_int
)paren
id|next-&gt;pgd
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov.l&t;%0, %1&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|__pgdir
)paren
comma
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_TTB
)paren
)paren
)paren
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
id|__inline__
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
macro_line|#else /* !CONFIG_MMU */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(mm)&t;&t;do { } while (0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;(0)
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while (0)
DECL|macro|set_asid
mdefine_line|#define set_asid(asid)&t;&t;&t;do { } while (0)
DECL|macro|get_asid
mdefine_line|#define get_asid()&t;&t;&t;(0)
DECL|macro|activate_context
mdefine_line|#define activate_context(mm)&t;&t;do { } while (0)
DECL|macro|switch_mm
mdefine_line|#define switch_mm(prev,next,tsk)&t;do { } while (0)
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;&t;do { } while (0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev,next)&t;&t;do { } while (0)
DECL|macro|enter_lazy_tlb
mdefine_line|#define enter_lazy_tlb(mm,tsk)&t;&t;do { } while (0)
macro_line|#endif /* CONFIG_MMU */
macro_line|#if defined(CONFIG_CPU_SH3) || defined(CONFIG_CPU_SH4)
multiline_comment|/*&n; * If this processor has an MMU, we need methods to turn it off/on ..&n; * paging_init() will also have to be updated for the processor in&n; * question.&n; */
DECL|function|enable_mmu
r_static
r_inline
r_void
id|enable_mmu
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Enable MMU */
id|ctrl_outl
c_func
(paren
id|MMU_CONTROL_INIT
comma
id|MMUCR
)paren
suffix:semicolon
multiline_comment|/* The manual suggests doing some nops after turning on the MMU */
id|__asm__
id|__volatile__
(paren
l_string|&quot;nop;nop;nop;nop;nop;nop;nop;nop&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmu_context_cache
op_eq
id|NO_CONTEXT
)paren
id|mmu_context_cache
op_assign
id|MMU_CONTEXT_FIRST_VERSION
suffix:semicolon
id|set_asid
c_func
(paren
id|mmu_context_cache
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
)brace
DECL|function|disable_mmu
r_static
r_inline
r_void
id|disable_mmu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cr
suffix:semicolon
id|cr
op_assign
id|ctrl_inl
c_func
(paren
id|MMUCR
)paren
suffix:semicolon
id|cr
op_and_assign
op_complement
id|MMU_CONTROL_INIT
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|cr
comma
id|MMUCR
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;nop;nop;nop;nop;nop;nop;nop;nop&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * MMU control handlers for processors lacking memory&n; * management hardware.&n; */
DECL|macro|enable_mmu
mdefine_line|#define enable_mmu()&t;do { BUG(); } while (0)
DECL|macro|disable_mmu
mdefine_line|#define disable_mmu()&t;do { BUG(); } while (0)
macro_line|#endif
macro_line|#endif /* __ASM_SH_MMU_CONTEXT_H */
eof
