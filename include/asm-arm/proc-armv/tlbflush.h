multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/tlbflush.h&n; *&n; *  Copyright (C) 1999-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/glue.h&gt;
DECL|macro|TLB_V3_PAGE
mdefine_line|#define TLB_V3_PAGE&t;(1 &lt;&lt; 0)
DECL|macro|TLB_V4_U_PAGE
mdefine_line|#define TLB_V4_U_PAGE&t;(1 &lt;&lt; 1)
DECL|macro|TLB_V4_D_PAGE
mdefine_line|#define TLB_V4_D_PAGE&t;(1 &lt;&lt; 2)
DECL|macro|TLB_V4_I_PAGE
mdefine_line|#define TLB_V4_I_PAGE&t;(1 &lt;&lt; 3)
DECL|macro|TLB_V3_FULL
mdefine_line|#define TLB_V3_FULL&t;(1 &lt;&lt; 8)
DECL|macro|TLB_V4_U_FULL
mdefine_line|#define TLB_V4_U_FULL&t;(1 &lt;&lt; 9)
DECL|macro|TLB_V4_D_FULL
mdefine_line|#define TLB_V4_D_FULL&t;(1 &lt;&lt; 10)
DECL|macro|TLB_V4_I_FULL
mdefine_line|#define TLB_V4_I_FULL&t;(1 &lt;&lt; 11)
DECL|macro|TLB_WB
mdefine_line|#define TLB_WB&t;&t;(1 &lt;&lt; 31)
multiline_comment|/*&n; *&t;MMU TLB Model&n; *&t;=============&n; *&n; *&t;We have the following to choose from:&n; *&t;  v3    - ARMv3&n; *&t;  v4    - ARMv4 without write buffer&n; *&t;  v4wb  - ARMv4 with write buffer without I TLB flush entry instruction&n; *&t;  v4wbi - ARMv4 with write buffer with I TLB flush entry instruction&n; */
DECL|macro|_TLB
macro_line|#undef _TLB
DECL|macro|MULTI_TLB
macro_line|#undef MULTI_TLB
DECL|macro|v3_tlb_flags
mdefine_line|#define v3_tlb_flags&t;(TLB_V3_FULL | TLB_V3_PAGE)
macro_line|#if defined(CONFIG_CPU_ARM610) || defined(CONFIG_CPU_ARM710)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v3
macro_line|# endif
macro_line|#endif
DECL|macro|v4_tlb_flags
mdefine_line|#define v4_tlb_flags&t;(TLB_V4_U_FULL | TLB_V4_U_PAGE)
macro_line|#if defined(CONFIG_CPU_ARM720T)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4
macro_line|# endif
macro_line|#endif
DECL|macro|v4wbi_tlb_flags
mdefine_line|#define v4wbi_tlb_flags&t;(TLB_WB | &bslash;&n;&t;&t;&t; TLB_V4_I_FULL | TLB_V4_D_FULL | &bslash;&n;&t;&t;&t; TLB_V4_I_PAGE | TLB_V4_D_PAGE)
macro_line|#if defined(CONFIG_CPU_ARM920T) || defined(CONFIG_CPU_ARM922T) || &bslash;&n;    defined(CONFIG_CPU_ARM926T) || defined(CONFIG_CPU_ARM1020) || &bslash;&n;    defined(CONFIG_CPU_XSCALE)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wbi
macro_line|# endif
macro_line|#endif
DECL|macro|v4wb_tlb_flags
mdefine_line|#define v4wb_tlb_flags&t;(TLB_WB | &bslash;&n;&t;&t;&t; TLB_V4_I_FULL | TLB_V4_D_FULL | &bslash;&n;&t;&t;&t; TLB_V4_D_PAGE)
macro_line|#if defined(CONFIG_CPU_SA110) || defined(CONFIG_CPU_SA1100)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wb
macro_line|# endif
macro_line|#endif
macro_line|#ifndef _TLB
macro_line|#error Unknown TLB model
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|struct|cpu_tlb_fns
r_struct
id|cpu_tlb_fns
(brace
DECL|member|flush_user_range
r_void
(paren
op_star
id|flush_user_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
DECL|member|flush_kern_range
r_void
(paren
op_star
id|flush_kern_range
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|tlb_flags
r_int
r_int
id|tlb_flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Select the calling method&n; */
macro_line|#ifdef MULTI_TLB
r_extern
r_struct
id|cpu_tlb_fns
id|cpu_tlb
suffix:semicolon
DECL|macro|__cpu_flush_user_tlb_range
mdefine_line|#define __cpu_flush_user_tlb_range&t;cpu_tlb.flush_user_range
DECL|macro|__cpu_flush_kern_tlb_range
mdefine_line|#define __cpu_flush_kern_tlb_range&t;cpu_tlb.flush_kern_range
DECL|macro|__cpu_tlb_flags
mdefine_line|#define __cpu_tlb_flags&t;&t;&t;cpu_tlb.tlb_flags
macro_line|#else
DECL|macro|__cpu_flush_user_tlb_range
mdefine_line|#define __cpu_flush_user_tlb_range&t;__glue(_TLB,_flush_user_tlb_range)
DECL|macro|__cpu_flush_kern_tlb_range
mdefine_line|#define __cpu_flush_kern_tlb_range&t;__glue(_TLB,_flush_kern_tlb_range)
DECL|macro|__cpu_tlb_flags
mdefine_line|#define __cpu_tlb_flags&t;&t;&t;__glue(_TLB,_tlb_flags)
r_extern
r_void
id|__cpu_flush_user_tlb_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__cpu_flush_kern_tlb_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;TLB Management&n; *&t;==============&n; *&n; *&t;The arch/arm/mm/tlb-*.S files implement these methods.&n; *&n; *&t;The TLB specific code is expected to perform whatever tests it&n; *&t;needs to determine if it should invalidate the TLB for each&n; *&t;call.  Start addresses are inclusive and end addresses are&n; *&t;exclusive; it is safe to round these addresses down.&n; *&n; *&t;flush_tlb_all()&n; *&n; *&t;&t;Invalidate the entire TLB.&n; *&n; *&t;flush_tlb_mm(mm)&n; *&n; *&t;&t;Invalidate all TLB entries in a particular address&n; *&t;&t;space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&n; *&t;flush_tlb_range(mm,start,end)&n; *&n; *&t;&t;Invalidate a range of TLB entries in the specified&n; *&t;&t;address space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&t;&t;- start - start address (may not be aligned)&n; *&t;&t;- end&t;- end address (exclusive, may not be aligned)&n; *&n; *&t;flush_tlb_page(vaddr,vma)&n; *&n; *&t;&t;Invalidate the specified page in the specified address range.&n; *&t;&t;- vaddr - virtual address (may not be aligned)&n; *&t;&t;- vma&t;- vma_struct describing address range&n; *&n; *&t;flush_kern_tlb_page(kaddr)&n; *&n; *&t;&t;Invalidate the TLB entry for the specified page.  The address&n; *&t;&t;will be in the kernels virtual memory space.  Current uses&n; *&t;&t;only require the D-TLB to be invalidated.&n; *&t;&t;- kaddr - Kernel virtual memory address&n; */
DECL|macro|tlb_flag
mdefine_line|#define tlb_flag(f)&t;(__cpu_tlb_flags &amp; (f))
DECL|function|flush_tlb_all
r_static
r_inline
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_const
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_WB
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c7, c10, 4&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V3_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c6, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_U_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c7, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_D_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c6, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_I_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_const
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_WB
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c7, c10, 4&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
(brace
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V3_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c6, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_U_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c7, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_D_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c6, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_I_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|flush_tlb_page
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|uaddr
)paren
(brace
r_const
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
id|uaddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_WB
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c7, c10, 4&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
(brace
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V3_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c6, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|uaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_U_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c7, 1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|uaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_D_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c6, 1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|uaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_I_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|uaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tlb_flag
c_func
(paren
id|TLB_V4_I_PAGE
)paren
op_logical_and
id|tlb_flag
c_func
(paren
id|TLB_V4_I_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_kernel_page
r_static
r_inline
r_void
id|flush_tlb_kernel_page
c_func
(paren
r_int
r_int
id|kaddr
)paren
(brace
r_const
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
id|kaddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_WB
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c7, c10, 4&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V3_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c6, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|kaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_U_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c7, 1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|kaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_D_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c6, 1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|kaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V4_I_PAGE
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|kaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tlb_flag
c_func
(paren
id|TLB_V4_I_PAGE
)paren
op_logical_and
id|tlb_flag
c_func
(paren
id|TLB_V4_I_FULL
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert calls to our calling convention.&n; */
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(vma,start,end)&t;__cpu_flush_user_tlb_range(start,end,vma)
DECL|macro|flush_tlb_kernel_range
mdefine_line|#define flush_tlb_kernel_range(s,e)&t;__cpu_flush_kern_tlb_range(s,e)
multiline_comment|/*&n; * if PG_dcache_dirty is set for the page, we need to ensure that any&n; * cache entries for the kernels virtual memory range are written&n; * back to the page.&n; */
r_extern
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
id|pte_t
id|pte
)paren
suffix:semicolon
multiline_comment|/*&n; * ARM processors do not cache TLB tables in RAM.&n; */
DECL|macro|flush_tlb_pgtables
mdefine_line|#define flush_tlb_pgtables(mm,start,end)&t;do { } while (0)
multiline_comment|/*&n; * Old ARM MEMC stuff.  This supports the reversed mapping handling that&n; * we have on the older 26-bit machines.  We don&squot;t have a MEMC chip, so...&n; */
DECL|macro|memc_update_all
mdefine_line|#define memc_update_all()&t;&t;do { } while (0)
DECL|macro|memc_update_mm
mdefine_line|#define memc_update_mm(mm)&t;&t;do { } while (0)
DECL|macro|memc_update_addr
mdefine_line|#define memc_update_addr(mm,pte,log)&t;do { } while (0)
DECL|macro|memc_clear
mdefine_line|#define memc_clear(mm,physaddr)&t;&t;do { } while (0)
macro_line|#endif
eof
