multiline_comment|/*&n; * PowerPC64 Segment Translation Support.&n; *&n; * Dave Engebretsen and Mike Corrigan {engebret|mikejc}@us.ibm.com&n; *    Copyright (c) 2001 Dave Engebretsen&n; * &n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/pmc.h&gt;
r_int
id|make_ste
c_func
(paren
r_int
r_int
id|stab
comma
r_int
r_int
id|esid
comma
r_int
r_int
id|vsid
)paren
suffix:semicolon
r_void
id|make_slbe
c_func
(paren
r_int
r_int
id|esid
comma
r_int
r_int
id|vsid
comma
r_int
id|large
)paren
suffix:semicolon
r_extern
r_struct
id|Naca
op_star
id|naca
suffix:semicolon
multiline_comment|/*&n; * Build an entry for the base kernel segment and put it into&n; * the segment table or SLB.  All other segment table or SLB&n; * entries are faulted in.&n; */
DECL|function|stab_initialize
r_void
id|stab_initialize
c_func
(paren
r_int
r_int
id|stab
)paren
(brace
r_int
r_int
id|esid
comma
id|vsid
suffix:semicolon
id|esid
op_assign
id|GET_ESID
c_func
(paren
id|KERNELBASE
)paren
suffix:semicolon
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|esid
op_lshift
id|SID_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|__is_processor
c_func
(paren
id|PV_POWER4
)paren
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;isync; slbia; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|make_ste
c_func
(paren
id|stab
comma
id|esid
comma
id|vsid
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Invalidate the entire SLB &amp; all the ERATS */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PPC_ISERIES
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;slbmte  %0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;isync; slbia; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|make_slbe
c_func
(paren
id|esid
comma
id|vsid
comma
l_int|0
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;isync; slbia; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n; * Create a segment table entry for the given esid/vsid pair.&n; */
DECL|function|make_ste
r_int
id|make_ste
c_func
(paren
r_int
r_int
id|stab
comma
r_int
r_int
id|esid
comma
r_int
r_int
id|vsid
)paren
(brace
r_int
r_int
id|entry
comma
id|group
comma
id|old_esid
comma
id|castout_entry
comma
id|i
suffix:semicolon
r_int
r_int
id|global_entry
suffix:semicolon
id|STE
op_star
id|ste
comma
op_star
id|castout_ste
suffix:semicolon
multiline_comment|/* Search the primary group first. */
id|global_entry
op_assign
(paren
id|esid
op_amp
l_int|0x1f
)paren
op_lshift
l_int|3
suffix:semicolon
id|ste
op_assign
(paren
id|STE
op_star
)paren
(paren
id|stab
op_or
(paren
(paren
id|esid
op_amp
l_int|0x1f
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find an empty entry, if one exists.&n;&t; */
r_for
c_loop
(paren
id|group
op_assign
l_int|0
suffix:semicolon
id|group
OL
l_int|2
suffix:semicolon
id|group
op_increment
)paren
(brace
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
l_int|8
suffix:semicolon
id|entry
op_increment
comma
id|ste
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ste-&gt;dw0.dw0.v
)paren
)paren
(brace
id|ste-&gt;dw1.dw1.vsid
op_assign
id|vsid
suffix:semicolon
multiline_comment|/* Order VSID updte */
id|__asm__
id|__volatile__
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ste-&gt;dw0.dw0.esid
op_assign
id|esid
suffix:semicolon
id|ste-&gt;dw0.dw0.v
op_assign
l_int|1
suffix:semicolon
id|ste-&gt;dw0.dw0.kp
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Order update     */
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|global_entry
op_or
id|entry
suffix:semicolon
)brace
)brace
multiline_comment|/* Now search the secondary group. */
id|global_entry
op_assign
(paren
(paren
op_complement
id|esid
)paren
op_amp
l_int|0x1f
)paren
op_lshift
l_int|3
suffix:semicolon
id|ste
op_assign
(paren
id|STE
op_star
)paren
(paren
id|stab
op_or
(paren
(paren
(paren
op_complement
id|esid
)paren
op_amp
l_int|0x1f
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Could not find empty entry, pick one with a round robin selection.&n;&t; * Search all entries in the two groups.  Note that the first time&n;&t; * we get here, we start with entry 1 so the initializer&n;&t; * can be common with the SLB castout code.&n;&t; */
multiline_comment|/* This assumes we never castout when initializing the stab. */
id|PMC_SW_PROCESSOR
c_func
(paren
id|stab_capacity_castouts
)paren
suffix:semicolon
id|castout_entry
op_assign
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xStab_data.next_round_robin
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|castout_entry
OL
l_int|8
)paren
(brace
id|global_entry
op_assign
(paren
id|esid
op_amp
l_int|0x1f
)paren
op_lshift
l_int|3
suffix:semicolon
id|ste
op_assign
(paren
id|STE
op_star
)paren
(paren
id|stab
op_or
(paren
(paren
id|esid
op_amp
l_int|0x1f
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|castout_ste
op_assign
id|ste
op_plus
id|castout_entry
suffix:semicolon
)brace
r_else
(brace
id|global_entry
op_assign
(paren
(paren
op_complement
id|esid
)paren
op_amp
l_int|0x1f
)paren
op_lshift
l_int|3
suffix:semicolon
id|ste
op_assign
(paren
id|STE
op_star
)paren
(paren
id|stab
op_or
(paren
(paren
(paren
op_complement
id|esid
)paren
op_amp
l_int|0x1f
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|castout_ste
op_assign
id|ste
op_plus
(paren
id|castout_entry
op_minus
l_int|8
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
(paren
id|castout_ste-&gt;dw0.dw0.esid
)paren
op_rshift
l_int|32
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
(paren
id|castout_ste-&gt;dw0.dw0.esid
)paren
op_amp
l_int|0xffffffff
)paren
OG
l_int|0
)paren
)paren
(brace
multiline_comment|/* Found an entry to castout.  It is either a user */
multiline_comment|/* region, or a secondary kernel segment.          */
r_break
suffix:semicolon
)brace
id|castout_entry
op_assign
(paren
id|castout_entry
op_plus
l_int|1
)paren
op_amp
l_int|0xf
suffix:semicolon
)brace
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xStab_data.next_round_robin
op_assign
(paren
id|castout_entry
op_plus
l_int|1
)paren
op_amp
l_int|0xf
suffix:semicolon
multiline_comment|/* Modify the old entry to the new value. */
multiline_comment|/* Force previous translations to complete. DRENG */
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|castout_ste-&gt;dw0.dw0.v
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Order update */
id|castout_ste-&gt;dw1.dw1.vsid
op_assign
id|vsid
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Order update */
id|old_esid
op_assign
id|castout_ste-&gt;dw0.dw0.esid
suffix:semicolon
id|castout_ste-&gt;dw0.dw0.esid
op_assign
id|esid
suffix:semicolon
id|castout_ste-&gt;dw0.dw0.v
op_assign
l_int|1
suffix:semicolon
id|castout_ste-&gt;dw0.dw0.kp
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;slbie  %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|old_esid
op_lshift
id|SID_SHIFT
)paren
)paren
suffix:semicolon
multiline_comment|/* Ensure completion of slbie */
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|global_entry
op_or
(paren
id|castout_entry
op_amp
l_int|0x7
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a segment buffer entry for the given esid/vsid pair.&n; */
DECL|function|make_slbe
r_void
id|make_slbe
c_func
(paren
r_int
r_int
id|esid
comma
r_int
r_int
id|vsid
comma
r_int
id|large
)paren
(brace
r_int
id|kernel_segment
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|entry
comma
id|castout_entry
suffix:semicolon
r_union
(brace
r_int
r_int
id|word0
suffix:semicolon
id|slb_dword0
id|data
suffix:semicolon
)brace
id|esid_data
suffix:semicolon
r_union
(brace
r_int
r_int
id|word0
suffix:semicolon
id|slb_dword1
id|data
suffix:semicolon
)brace
id|vsid_data
suffix:semicolon
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|esid
op_lshift
id|SID_SHIFT
)paren
op_ge
id|KERNEL_REGION_ID
)paren
id|kernel_segment
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Find an empty entry, if one exists.&n;&t; */
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|naca-&gt;slb_size
suffix:semicolon
id|entry
op_increment
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;slbmfee  %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|esid_data
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|esid_data.data.v
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * Write the new SLB entry.&n;&t;&t;&t; */
id|vsid_data.word0
op_assign
l_int|0
suffix:semicolon
id|vsid_data.data.vsid
op_assign
id|vsid
suffix:semicolon
id|vsid_data.data.kp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|vsid_data.data.l
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|kernel_segment
)paren
id|vsid_data.data.c
op_assign
l_int|1
suffix:semicolon
id|esid_data.word0
op_assign
l_int|0
suffix:semicolon
id|esid_data.data.esid
op_assign
id|esid
suffix:semicolon
id|esid_data.data.v
op_assign
l_int|1
suffix:semicolon
id|esid_data.data.index
op_assign
id|entry
suffix:semicolon
multiline_comment|/* slbie not needed as no previous mapping existed. */
multiline_comment|/* Order update  */
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;slbmte  %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|vsid_data
)paren
comma
l_string|&quot;r&quot;
(paren
id|esid_data
)paren
)paren
suffix:semicolon
multiline_comment|/* Order update  */
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Could not find empty entry, pick one with a round robin selection.&n;&t; */
id|PMC_SW_PROCESSOR
c_func
(paren
id|stab_capacity_castouts
)paren
suffix:semicolon
id|castout_entry
op_assign
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xStab_data.next_round_robin
suffix:semicolon
id|entry
op_assign
id|castout_entry
suffix:semicolon
id|castout_entry
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|castout_entry
op_ge
id|naca-&gt;slb_size
)paren
id|castout_entry
op_assign
l_int|1
suffix:semicolon
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xStab_data.next_round_robin
op_assign
id|castout_entry
suffix:semicolon
multiline_comment|/* slbie not needed as the previous mapping is still valid. */
multiline_comment|/* &n;&t; * Write the new SLB entry.&n;&t; */
id|vsid_data.word0
op_assign
l_int|0
suffix:semicolon
id|vsid_data.data.vsid
op_assign
id|vsid
suffix:semicolon
id|vsid_data.data.kp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|vsid_data.data.l
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|kernel_segment
)paren
id|vsid_data.data.c
op_assign
l_int|1
suffix:semicolon
id|esid_data.word0
op_assign
l_int|0
suffix:semicolon
id|esid_data.data.esid
op_assign
id|esid
suffix:semicolon
id|esid_data.data.v
op_assign
l_int|1
suffix:semicolon
id|esid_data.data.index
op_assign
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Order update */
id|__asm__
id|__volatile__
(paren
l_string|&quot;slbmte  %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|vsid_data
)paren
comma
l_string|&quot;r&quot;
(paren
id|esid_data
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Order update */
)brace
multiline_comment|/*&n; * Allocate a segment table entry for the given ea.&n; */
DECL|function|ste_allocate
r_int
id|ste_allocate
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|trap
)paren
(brace
r_int
r_int
id|vsid
comma
id|esid
suffix:semicolon
r_int
id|kernel_segment
op_assign
l_int|0
suffix:semicolon
id|PMC_SW_PROCESSOR
c_func
(paren
id|stab_faults
)paren
suffix:semicolon
multiline_comment|/* Check for invalid effective addresses. */
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_EA
c_func
(paren
id|ea
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Kernel or user address? */
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|ea
)paren
op_ge
id|KERNEL_REGION_ID
)paren
(brace
id|kernel_segment
op_assign
l_int|1
suffix:semicolon
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|mm-&gt;context
comma
id|ea
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|esid
op_assign
id|GET_ESID
c_func
(paren
id|ea
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trap
op_eq
l_int|0x380
op_logical_or
id|trap
op_eq
l_int|0x480
)paren
(brace
macro_line|#ifndef CONFIG_PPC_ISERIES
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|ea
)paren
op_eq
id|KERNEL_REGION_ID
)paren
id|make_slbe
c_func
(paren
id|esid
comma
id|vsid
comma
l_int|1
)paren
suffix:semicolon
r_else
macro_line|#endif
id|make_slbe
c_func
(paren
id|esid
comma
id|vsid
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_char
id|top_entry
comma
id|stab_entry
comma
op_star
id|segments
suffix:semicolon
id|stab_entry
op_assign
id|make_ste
c_func
(paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xStab_data.virt
comma
id|esid
comma
id|vsid
)paren
suffix:semicolon
id|PMC_SW_PROCESSOR_A
c_func
(paren
id|stab_entry_use
comma
id|stab_entry
op_amp
l_int|0xf
)paren
suffix:semicolon
id|segments
op_assign
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xSegments
suffix:semicolon
id|top_entry
op_assign
id|segments
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kernel_segment
op_logical_and
id|top_entry
OL
(paren
id|STAB_CACHE_SIZE
op_minus
l_int|1
)paren
)paren
(brace
id|top_entry
op_increment
suffix:semicolon
id|segments
(braket
id|top_entry
)braket
op_assign
id|stab_entry
suffix:semicolon
r_if
c_cond
(paren
id|top_entry
op_eq
id|STAB_CACHE_SIZE
op_minus
l_int|1
)paren
(brace
id|top_entry
op_assign
l_int|0xff
suffix:semicolon
)brace
id|segments
(braket
l_int|0
)braket
op_assign
id|top_entry
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Flush all entries from the segment table of the current processor.&n; * Kernel and Bolted entries are not removed as we cannot tolerate &n; * faults on those addresses.&n; */
DECL|macro|STAB_PRESSURE
mdefine_line|#define STAB_PRESSURE 0
DECL|function|flush_stab
r_void
id|flush_stab
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
id|STE
op_star
id|stab
op_assign
(paren
id|STE
op_star
)paren
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xStab_data.virt
suffix:semicolon
r_int
r_char
op_star
id|segments
op_assign
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|xSegments
suffix:semicolon
r_int
r_int
id|flags
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|__is_processor
c_func
(paren
id|PV_POWER4
)paren
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
id|STE
op_star
id|ste
suffix:semicolon
multiline_comment|/* Force previous translations to complete. DRENG */
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|segments
(braket
l_int|0
)braket
op_ne
l_int|0xff
op_logical_and
op_logical_neg
id|STAB_PRESSURE
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|segments
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ste
op_assign
id|stab
op_plus
id|segments
(braket
id|i
)braket
suffix:semicolon
id|ste-&gt;dw0.dw0.v
op_assign
l_int|0
suffix:semicolon
id|PMC_SW_PROCESSOR
c_func
(paren
id|stab_invalidations
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Invalidate all entries. */
id|ste
op_assign
id|stab
suffix:semicolon
multiline_comment|/* Never flush the first entry. */
id|ste
op_add_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|1
suffix:semicolon
id|entry
OL
(paren
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|STE
)paren
)paren
suffix:semicolon
id|entry
op_increment
comma
id|ste
op_increment
)paren
(brace
r_int
r_int
id|ea
suffix:semicolon
id|ea
op_assign
id|ste-&gt;dw0.dw0.esid
op_lshift
id|SID_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|STAB_PRESSURE
op_logical_or
id|ea
OL
id|KERNELBASE
)paren
(brace
id|ste-&gt;dw0.dw0.v
op_assign
l_int|0
suffix:semicolon
id|PMC_SW_PROCESSOR
c_func
(paren
id|stab_invalidations
)paren
suffix:semicolon
)brace
)brace
)brace
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|segments
)paren
op_assign
l_int|0
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Invalidate the SLB. */
multiline_comment|/* Force invals to complete. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Flush the SLB.            */
id|__asm__
id|__volatile__
(paren
l_string|&quot;slbia&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Force flush to complete.  */
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* XXX The commented out code will only work for 32 bit tasks */
macro_line|#if 1
r_int
r_int
id|flags
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;isync; slbia; isync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#else
r_union
(brace
r_int
r_int
id|word0
suffix:semicolon
id|slb_dword0
id|data
suffix:semicolon
)brace
id|esid_data
suffix:semicolon
r_int
r_int
id|esid
suffix:semicolon
id|__asm__
id|__volatile__
c_func
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
id|esid
op_assign
l_int|0
suffix:semicolon
id|esid
OL
l_int|16
suffix:semicolon
id|esid
op_increment
)paren
(brace
id|esid_data.word0
op_assign
l_int|0
suffix:semicolon
id|esid_data.data.esid
op_assign
id|esid
suffix:semicolon
id|__asm__
id|__volatile__
c_func
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
id|PMC_SW_PROCESSOR
c_func
(paren
id|stab_invalidations
)paren
suffix:semicolon
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
(brace
r_int
r_int
id|esid
comma
id|vsid
suffix:semicolon
r_for
c_loop
(paren
id|esid
op_assign
l_int|0
suffix:semicolon
id|esid
OL
l_int|16
suffix:semicolon
id|esid
op_increment
)paren
(brace
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|mm-&gt;context
comma
id|esid
op_lshift
id|SID_SHIFT
)paren
suffix:semicolon
id|make_slbe
c_func
(paren
id|esid
comma
id|vsid
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
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
id|pc_segment
op_assign
id|pc
op_amp
op_complement
id|SID_MASK
suffix:semicolon
r_int
r_int
id|stack_segment
op_assign
id|stack
op_amp
op_complement
id|SID_MASK
suffix:semicolon
r_int
r_int
id|vsid
suffix:semicolon
r_if
c_cond
(paren
id|pc
)paren
(brace
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|pc
)paren
op_ge
id|KERNEL_REGION_ID
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|mm-&gt;context
comma
id|pc
)paren
suffix:semicolon
id|make_slbe
c_func
(paren
id|GET_ESID
c_func
(paren
id|pc
)paren
comma
id|vsid
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stack
op_logical_and
(paren
id|pc_segment
op_ne
id|stack_segment
)paren
)paren
(brace
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|stack
)paren
op_ge
id|KERNEL_REGION_ID
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|mm-&gt;context
comma
id|stack
)paren
suffix:semicolon
id|make_slbe
c_func
(paren
id|GET_ESID
c_func
(paren
id|stack
)paren
comma
id|vsid
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
eof
