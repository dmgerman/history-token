multiline_comment|/*&n; *  linux/include/asm-arm/tlbflush.h&n; *&n; *  Copyright (C) 1999-2003 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_TLBFLUSH_H
DECL|macro|_ASMARM_TLBFLUSH_H
mdefine_line|#define _ASMARM_TLBFLUSH_H
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
DECL|macro|TLB_V6_U_PAGE
mdefine_line|#define TLB_V6_U_PAGE&t;(1 &lt;&lt; 4)
DECL|macro|TLB_V6_D_PAGE
mdefine_line|#define TLB_V6_D_PAGE&t;(1 &lt;&lt; 5)
DECL|macro|TLB_V6_I_PAGE
mdefine_line|#define TLB_V6_I_PAGE&t;(1 &lt;&lt; 6)
DECL|macro|TLB_V3_FULL
mdefine_line|#define TLB_V3_FULL&t;(1 &lt;&lt; 8)
DECL|macro|TLB_V4_U_FULL
mdefine_line|#define TLB_V4_U_FULL&t;(1 &lt;&lt; 9)
DECL|macro|TLB_V4_D_FULL
mdefine_line|#define TLB_V4_D_FULL&t;(1 &lt;&lt; 10)
DECL|macro|TLB_V4_I_FULL
mdefine_line|#define TLB_V4_I_FULL&t;(1 &lt;&lt; 11)
DECL|macro|TLB_V6_U_FULL
mdefine_line|#define TLB_V6_U_FULL&t;(1 &lt;&lt; 12)
DECL|macro|TLB_V6_D_FULL
mdefine_line|#define TLB_V6_D_FULL&t;(1 &lt;&lt; 13)
DECL|macro|TLB_V6_I_FULL
mdefine_line|#define TLB_V6_I_FULL&t;(1 &lt;&lt; 14)
DECL|macro|TLB_V6_U_ASID
mdefine_line|#define TLB_V6_U_ASID&t;(1 &lt;&lt; 16)
DECL|macro|TLB_V6_D_ASID
mdefine_line|#define TLB_V6_D_ASID&t;(1 &lt;&lt; 17)
DECL|macro|TLB_V6_I_ASID
mdefine_line|#define TLB_V6_I_ASID&t;(1 &lt;&lt; 18)
DECL|macro|TLB_DCLEAN
mdefine_line|#define TLB_DCLEAN&t;(1 &lt;&lt; 30)
DECL|macro|TLB_WB
mdefine_line|#define TLB_WB&t;&t;(1 &lt;&lt; 31)
multiline_comment|/*&n; *&t;MMU TLB Model&n; *&t;=============&n; *&n; *&t;We have the following to choose from:&n; *&t;  v3    - ARMv3&n; *&t;  v4    - ARMv4 without write buffer&n; *&t;  v4wb  - ARMv4 with write buffer without I TLB flush entry instruction&n; *&t;  v4wbi - ARMv4 with write buffer with I TLB flush entry instruction&n; *&t;  v6wbi - ARMv6 with write buffer with I TLB flush entry instruction&n; */
DECL|macro|_TLB
macro_line|#undef _TLB
DECL|macro|MULTI_TLB
macro_line|#undef MULTI_TLB
DECL|macro|v3_tlb_flags
mdefine_line|#define v3_tlb_flags&t;(TLB_V3_FULL | TLB_V3_PAGE)
macro_line|#ifdef CONFIG_CPU_TLB_V3
DECL|macro|v3_possible_flags
macro_line|# define v3_possible_flags&t;v3_tlb_flags
DECL|macro|v3_always_flags
macro_line|# define v3_always_flags&t;v3_tlb_flags
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v3
macro_line|# endif
macro_line|#else
DECL|macro|v3_possible_flags
macro_line|# define v3_possible_flags&t;0
DECL|macro|v3_always_flags
macro_line|# define v3_always_flags&t;(-1UL)
macro_line|#endif
DECL|macro|v4_tlb_flags
mdefine_line|#define v4_tlb_flags&t;(TLB_V4_U_FULL | TLB_V4_U_PAGE)
macro_line|#ifdef CONFIG_CPU_TLB_V4WT
DECL|macro|v4_possible_flags
macro_line|# define v4_possible_flags&t;v4_tlb_flags
DECL|macro|v4_always_flags
macro_line|# define v4_always_flags&t;v4_tlb_flags
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4
macro_line|# endif
macro_line|#else
DECL|macro|v4_possible_flags
macro_line|# define v4_possible_flags&t;0
DECL|macro|v4_always_flags
macro_line|# define v4_always_flags&t;(-1UL)
macro_line|#endif
DECL|macro|v4wbi_tlb_flags
mdefine_line|#define v4wbi_tlb_flags&t;(TLB_WB | TLB_DCLEAN | &bslash;&n;&t;&t;&t; TLB_V4_I_FULL | TLB_V4_D_FULL | &bslash;&n;&t;&t;&t; TLB_V4_I_PAGE | TLB_V4_D_PAGE)
macro_line|#ifdef CONFIG_CPU_TLB_V4WBI
DECL|macro|v4wbi_possible_flags
macro_line|# define v4wbi_possible_flags&t;v4wbi_tlb_flags
DECL|macro|v4wbi_always_flags
macro_line|# define v4wbi_always_flags&t;v4wbi_tlb_flags
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wbi
macro_line|# endif
macro_line|#else
DECL|macro|v4wbi_possible_flags
macro_line|# define v4wbi_possible_flags&t;0
DECL|macro|v4wbi_always_flags
macro_line|# define v4wbi_always_flags&t;(-1UL)
macro_line|#endif
DECL|macro|v4wb_tlb_flags
mdefine_line|#define v4wb_tlb_flags&t;(TLB_WB | TLB_DCLEAN | &bslash;&n;&t;&t;&t; TLB_V4_I_FULL | TLB_V4_D_FULL | &bslash;&n;&t;&t;&t; TLB_V4_D_PAGE)
macro_line|#ifdef CONFIG_CPU_TLB_V4WB
DECL|macro|v4wb_possible_flags
macro_line|# define v4wb_possible_flags&t;v4wb_tlb_flags
DECL|macro|v4wb_always_flags
macro_line|# define v4wb_always_flags&t;v4wb_tlb_flags
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wb
macro_line|# endif
macro_line|#else
DECL|macro|v4wb_possible_flags
macro_line|# define v4wb_possible_flags&t;0
DECL|macro|v4wb_always_flags
macro_line|# define v4wb_always_flags&t;(-1UL)
macro_line|#endif
DECL|macro|v6wbi_tlb_flags
mdefine_line|#define v6wbi_tlb_flags (TLB_WB | TLB_DCLEAN | &bslash;&n;&t;&t;&t; TLB_V6_I_FULL | TLB_V6_D_FULL | &bslash;&n;&t;&t;&t; TLB_V6_I_PAGE | TLB_V6_D_PAGE | &bslash;&n;&t;&t;&t; TLB_V6_I_ASID | TLB_V6_D_ASID)
macro_line|#ifdef CONFIG_CPU_TLB_V6
DECL|macro|v6wbi_possible_flags
macro_line|# define v6wbi_possible_flags&t;v6wbi_tlb_flags
DECL|macro|v6wbi_always_flags
macro_line|# define v6wbi_always_flags&t;v6wbi_tlb_flags
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v6wbi
macro_line|# endif
macro_line|#else
DECL|macro|v6wbi_possible_flags
macro_line|# define v6wbi_possible_flags&t;0
DECL|macro|v6wbi_always_flags
macro_line|# define v6wbi_always_flags&t;(-1UL)
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
DECL|macro|__cpu_flush_user_tlb_range
mdefine_line|#define __cpu_flush_user_tlb_range&t;cpu_tlb.flush_user_range
DECL|macro|__cpu_flush_kern_tlb_range
mdefine_line|#define __cpu_flush_kern_tlb_range&t;cpu_tlb.flush_kern_range
macro_line|#else
DECL|macro|__cpu_flush_user_tlb_range
mdefine_line|#define __cpu_flush_user_tlb_range&t;__glue(_TLB,_flush_user_tlb_range)
DECL|macro|__cpu_flush_kern_tlb_range
mdefine_line|#define __cpu_flush_kern_tlb_range&t;__glue(_TLB,_flush_kern_tlb_range)
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
r_extern
r_struct
id|cpu_tlb_fns
id|cpu_tlb
suffix:semicolon
DECL|macro|__cpu_tlb_flags
mdefine_line|#define __cpu_tlb_flags&t;&t;&t;cpu_tlb.tlb_flags
multiline_comment|/*&n; *&t;TLB Management&n; *&t;==============&n; *&n; *&t;The arch/arm/mm/tlb-*.S files implement these methods.&n; *&n; *&t;The TLB specific code is expected to perform whatever tests it&n; *&t;needs to determine if it should invalidate the TLB for each&n; *&t;call.  Start addresses are inclusive and end addresses are&n; *&t;exclusive; it is safe to round these addresses down.&n; *&n; *&t;flush_tlb_all()&n; *&n; *&t;&t;Invalidate the entire TLB.&n; *&n; *&t;flush_tlb_mm(mm)&n; *&n; *&t;&t;Invalidate all TLB entries in a particular address&n; *&t;&t;space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&n; *&t;flush_tlb_range(mm,start,end)&n; *&n; *&t;&t;Invalidate a range of TLB entries in the specified&n; *&t;&t;address space.&n; *&t;&t;- mm&t;- mm_struct describing address space&n; *&t;&t;- start - start address (may not be aligned)&n; *&t;&t;- end&t;- end address (exclusive, may not be aligned)&n; *&n; *&t;flush_tlb_page(vaddr,vma)&n; *&n; *&t;&t;Invalidate the specified page in the specified address range.&n; *&t;&t;- vaddr - virtual address (may not be aligned)&n; *&t;&t;- vma&t;- vma_struct describing address range&n; *&n; *&t;flush_kern_tlb_page(kaddr)&n; *&n; *&t;&t;Invalidate the TLB entry for the specified page.  The address&n; *&t;&t;will be in the kernels virtual memory space.  Current uses&n; *&t;&t;only require the D-TLB to be invalidated.&n; *&t;&t;- kaddr - Kernel virtual memory address&n; */
multiline_comment|/*&n; * We optimise the code below by:&n; *  - building a set of TLB flags that might be set in __cpu_tlb_flags&n; *  - building a set of TLB flags that will always be set in __cpu_tlb_flags&n; *  - if we&squot;re going to need __cpu_tlb_flags, access it once and only once&n; *&n; * This allows us to build optimal assembly for the single-CPU type case,&n; * and as close to optimal given the compiler constrants for multi-CPU&n; * case.  We could do better for the multi-CPU case if the compiler&n; * implemented the &quot;%?&quot; method, but this has been discontinued due to too&n; * many people getting it wrong.&n; */
DECL|macro|possible_tlb_flags
mdefine_line|#define possible_tlb_flags&t;(v3_possible_flags | &bslash;&n;&t;&t;&t;&t; v4_possible_flags | &bslash;&n;&t;&t;&t;&t; v4wbi_possible_flags | &bslash;&n;&t;&t;&t;&t; v4wb_possible_flags | &bslash;&n;&t;&t;&t;&t; v6wbi_possible_flags)
DECL|macro|always_tlb_flags
mdefine_line|#define always_tlb_flags&t;(v3_always_flags &amp; &bslash;&n;&t;&t;&t;&t; v4_always_flags &amp; &bslash;&n;&t;&t;&t;&t; v4wbi_always_flags &amp; &bslash;&n;&t;&t;&t;&t; v4wb_always_flags &amp; &bslash;&n;&t;&t;&t;&t; v6wbi_always_flags)
DECL|macro|tlb_flag
mdefine_line|#define tlb_flag(f)&t;((always_tlb_flags &amp; (f)) || (__tlb_flag &amp; possible_tlb_flags &amp; (f)))
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
r_const
r_int
r_int
id|__tlb_flag
op_assign
id|__cpu_tlb_flags
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
op_or
id|TLB_V6_U_FULL
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
op_or
id|TLB_V6_D_FULL
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
op_or
id|TLB_V6_I_FULL
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
r_const
r_int
id|asid
op_assign
id|ASID
c_func
(paren
id|mm
)paren
suffix:semicolon
r_const
r_int
r_int
id|__tlb_flag
op_assign
id|__cpu_tlb_flags
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
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm-&gt;cpu_vm_mask
)paren
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
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V6_U_ASID
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c7, 2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|asid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V6_D_ASID
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c6, 2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|asid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V6_I_ASID
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%? p15, 0, %0, c8, c5, 2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|asid
)paren
)paren
suffix:semicolon
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
r_const
r_int
r_int
id|__tlb_flag
op_assign
id|__cpu_tlb_flags
suffix:semicolon
id|uaddr
op_assign
(paren
id|uaddr
op_amp
id|PAGE_MASK
)paren
op_or
id|ASID
c_func
(paren
id|vma-&gt;vm_mm
)paren
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
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm-&gt;cpu_vm_mask
)paren
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
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V6_U_PAGE
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
id|TLB_V6_D_PAGE
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
id|TLB_V6_I_PAGE
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
r_const
r_int
r_int
id|__tlb_flag
op_assign
id|__cpu_tlb_flags
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
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_V6_U_PAGE
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
id|TLB_V6_D_PAGE
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
id|TLB_V6_I_PAGE
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
)brace
multiline_comment|/*&n; *&t;flush_pmd_entry&n; *&n; *&t;Flush a PMD entry (word aligned, or double-word aligned) to&n; *&t;RAM if the TLB for the CPU we are running on requires this.&n; *&t;This is typically used when we are creating PMD entries.&n; *&n; *&t;clean_pmd_entry&n; *&n; *&t;Clean (but don&squot;t drain the write buffer) if the CPU requires&n; *&t;these operations.  This is typically used when we are removing&n; *&t;PMD entries.&n; */
DECL|function|flush_pmd_entry
r_static
r_inline
r_void
id|flush_pmd_entry
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_const
r_int
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
r_const
r_int
r_int
id|__tlb_flag
op_assign
id|__cpu_tlb_flags
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_DCLEAN
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%?&t;p15, 0, %0, c7, c10, 1&t;@ flush_pmd&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pmd
)paren
)paren
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
l_string|&quot;mcr%?&t;p15, 0, %0, c7, c10, 4&t;@ flush_pmd&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
)brace
DECL|function|clean_pmd_entry
r_static
r_inline
r_void
id|clean_pmd_entry
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_const
r_int
r_int
id|__tlb_flag
op_assign
id|__cpu_tlb_flags
suffix:semicolon
r_if
c_cond
(paren
id|tlb_flag
c_func
(paren
id|TLB_DCLEAN
)paren
)paren
id|asm
c_func
(paren
l_string|&quot;mcr%?&t;p15, 0, %0, c7, c10, 1&t;@ flush_pmd&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pmd
)paren
)paren
suffix:semicolon
)brace
DECL|macro|tlb_flag
macro_line|#undef tlb_flag
DECL|macro|always_tlb_flags
macro_line|#undef always_tlb_flags
DECL|macro|possible_tlb_flags
macro_line|#undef possible_tlb_flags
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
macro_line|#endif
macro_line|#endif
eof
