multiline_comment|/*&n; * PowerPC64 SLB support.&n; *&n; * Copyright (C) 2004 David Gibson &lt;dwg@au.ibm.com&gt;, IBM&n; * Based on earlier code writteh by:&n; * Dave Engebretsen and Mike Corrigan {engebret|mikejc}@us.ibm.com&n; *    Copyright (c) 2001 Dave Engebretsen&n; * Copyright (C) 2002 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
r_extern
r_void
id|slb_allocate
c_func
(paren
r_int
r_int
id|ea
)paren
suffix:semicolon
DECL|function|mk_esid_data
r_static
r_inline
r_int
r_int
id|mk_esid_data
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|slot
)paren
(brace
r_return
(paren
id|ea
op_amp
id|ESID_MASK
)paren
op_or
id|SLB_ESID_V
op_or
id|slot
suffix:semicolon
)brace
DECL|function|mk_vsid_data
r_static
r_inline
r_int
r_int
id|mk_vsid_data
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|flags
)paren
(brace
r_return
(paren
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
op_lshift
id|SLB_VSID_SHIFT
)paren
op_or
id|flags
suffix:semicolon
)brace
DECL|function|create_slbe
r_static
r_inline
r_void
id|create_slbe
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|vsid
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|entry
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;slbmte  %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mk_vsid_data
c_func
(paren
id|ea
comma
id|flags
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|mk_esid_data
c_func
(paren
id|ea
comma
id|entry
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|slb_flush_and_rebolt
r_static
r_void
id|slb_flush_and_rebolt
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* If you change this make sure you change SLB_NUM_BOLTED&n;&t; * appropriately too. */
r_int
r_int
id|ksp_flags
op_assign
id|SLB_VSID_KERNEL
suffix:semicolon
r_int
r_int
id|ksp_esid_data
suffix:semicolon
id|WARN_ON
c_func
(paren
op_logical_neg
id|irqs_disabled
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_16M_PAGE
)paren
id|ksp_flags
op_or_assign
id|SLB_VSID_L
suffix:semicolon
id|ksp_esid_data
op_assign
id|mk_esid_data
c_func
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|kstack
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ksp_esid_data
op_amp
id|ESID_MASK
)paren
op_eq
id|KERNELBASE
)paren
id|ksp_esid_data
op_and_assign
op_complement
id|SLB_ESID_V
suffix:semicolon
multiline_comment|/* We need to do this all in asm, so we&squot;re sure we don&squot;t touch&n;&t; * the stack between the slbia and rebolting it. */
id|asm
r_volatile
(paren
l_string|&quot;isync&bslash;n&quot;
l_string|&quot;slbia&bslash;n&quot;
multiline_comment|/* Slot 1 - first VMALLOC segment */
l_string|&quot;slbmte&t;%0,%1&bslash;n&quot;
multiline_comment|/* Slot 2 - kernel stack */
l_string|&quot;slbmte&t;%2,%3&bslash;n&quot;
l_string|&quot;isync&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|mk_vsid_data
c_func
(paren
id|VMALLOCBASE
comma
id|SLB_VSID_KERNEL
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|mk_esid_data
c_func
(paren
id|VMALLOCBASE
comma
l_int|1
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|mk_vsid_data
c_func
(paren
id|ksp_esid_data
comma
id|ksp_flags
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|ksp_esid_data
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Flush all user entries from the segment table of the current processor. */
DECL|function|switch_slb
r_void
id|switch_slb
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
r_int
r_int
id|offset
op_assign
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|slb_cache_ptr
suffix:semicolon
r_int
r_int
id|esid_data
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pc
op_assign
id|KSTK_EIP
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_int
r_int
id|stack
op_assign
id|KSTK_ESP
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_int
r_int
id|unmapped_base
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_le
id|SLB_CACHE_ENTRIES
)paren
(brace
r_int
id|i
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|offset
suffix:semicolon
id|i
op_increment
)paren
(brace
id|esid_data
op_assign
(paren
r_int
r_int
)paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|slb_cache
(braket
id|i
)braket
op_lshift
id|SID_SHIFT
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;slbie %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|esid_data
)paren
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|slb_flush_and_rebolt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Workaround POWER5 &lt; DD2.1 issue */
r_if
c_cond
(paren
id|offset
op_eq
l_int|1
op_logical_or
id|offset
OG
id|SLB_CACHE_ENTRIES
)paren
id|asm
r_volatile
(paren
l_string|&quot;slbie %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|esid_data
)paren
)paren
suffix:semicolon
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|slb_cache_ptr
op_assign
l_int|0
suffix:semicolon
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|context
op_assign
id|mm-&gt;context
suffix:semicolon
multiline_comment|/*&n;&t; * preload some userspace segments into the SLB.&n;&t; */
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|tsk
comma
id|TIF_32BIT
)paren
)paren
id|unmapped_base
op_assign
id|TASK_UNMAPPED_BASE_USER32
suffix:semicolon
r_else
id|unmapped_base
op_assign
id|TASK_UNMAPPED_BASE_USER64
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
id|KERNELBASE
)paren
r_return
suffix:semicolon
id|slb_allocate
c_func
(paren
id|pc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|GET_ESID
c_func
(paren
id|pc
)paren
op_eq
id|GET_ESID
c_func
(paren
id|stack
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|stack
op_ge
id|KERNELBASE
)paren
r_return
suffix:semicolon
id|slb_allocate
c_func
(paren
id|stack
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|GET_ESID
c_func
(paren
id|pc
)paren
op_eq
id|GET_ESID
c_func
(paren
id|unmapped_base
)paren
)paren
op_logical_or
(paren
id|GET_ESID
c_func
(paren
id|stack
)paren
op_eq
id|GET_ESID
c_func
(paren
id|unmapped_base
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|unmapped_base
op_ge
id|KERNELBASE
)paren
r_return
suffix:semicolon
id|slb_allocate
c_func
(paren
id|unmapped_base
)paren
suffix:semicolon
)brace
DECL|function|slb_initialize
r_void
id|slb_initialize
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* On iSeries the bolted entries have already been set up by&n;&t; * the hypervisor from the lparMap data in head.S */
macro_line|#ifndef CONFIG_PPC_ISERIES
r_int
r_int
id|flags
op_assign
id|SLB_VSID_KERNEL
suffix:semicolon
multiline_comment|/* Invalidate the entire SLB (even slot 0) &amp; all the ERATS */
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_16M_PAGE
)paren
id|flags
op_or_assign
id|SLB_VSID_L
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;slbmte  %0,%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;isync; slbia; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|create_slbe
c_func
(paren
id|KERNELBASE
comma
id|get_kernel_vsid
c_func
(paren
id|KERNELBASE
)paren
comma
id|flags
comma
l_int|0
)paren
suffix:semicolon
id|create_slbe
c_func
(paren
id|VMALLOCBASE
comma
id|get_kernel_vsid
c_func
(paren
id|KERNELBASE
)paren
comma
id|SLB_VSID_KERNEL
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t bolt the stack for the time being - we&squot;re in boot,&n;&t; * so the stack is in the bolted segment.  By the time it goes&n;&t; * elsewhere, we&squot;ll call _switch() which will bolt in the new&n;&t; * one. */
id|asm
r_volatile
(paren
l_string|&quot;isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|stab_rr
op_assign
id|SLB_NUM_BOLTED
suffix:semicolon
)brace
eof
