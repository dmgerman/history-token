multiline_comment|/*&n; * LparMap.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _LPARMAP_H
DECL|macro|_LPARMAP_H
mdefine_line|#define _LPARMAP_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* The iSeries hypervisor will set up mapping for one or more &n; * ESID/VSID pairs (in SLB/segment registers) and will set up&n; * mappings of one or more ranges of pages to VAs.&n; * We will have the hypervisor set up the ESID-&gt;VSID mapping&n; * for the four kernel segments (C-F).  With shared processors,&n; * the hypervisor will clear all segment registers and reload&n; * these four whenever the processor is switched from one &n; * partition to another.&n; */
multiline_comment|/* The Vsid and Esid identified below will be used by the hypervisor&n; * to set up a memory mapping for part of the load area before giving&n; * control to the Linux kernel.  The load area is 64 MB, but this must&n; * not attempt to map the whole load area.  The Hashed Page Table may&n; * need to be located within the load area (if the total partition size&n; * is 64 MB), but cannot be mapped.  Typically, this should specify&n; * to map half (32 MB) of the load area.&n; * &n; * The hypervisor will set up page table entries for the number of &n; * pages specified.&n; *&n; * In 32-bit mode, the hypervisor will load all four of the&n; * segment registers (identified by the low-order four bits of the &n; * Esid field.  In 64-bit mode, the hypervisor will load one SLB&n; * entry to map the Esid to the Vsid.&n;*/
singleline_comment|// Hypervisor initially maps 32MB of the load area 
DECL|macro|HvPagesToMap
mdefine_line|#define HvPagesToMap 8192
DECL|struct|LparMap
r_struct
id|LparMap
(brace
DECL|member|xNumberEsids
id|u64
id|xNumberEsids
suffix:semicolon
singleline_comment|// Number of ESID/VSID pairs (1)
DECL|member|xNumberRanges
id|u64
id|xNumberRanges
suffix:semicolon
singleline_comment|// Number of VA ranges to map (1)
DECL|member|xSegmentTableOffs
id|u64
id|xSegmentTableOffs
suffix:semicolon
singleline_comment|// Page number within load area of seg table (0)
DECL|member|xRsvd
id|u64
id|xRsvd
(braket
l_int|5
)braket
suffix:semicolon
singleline_comment|// Reserved (0)
DECL|member|xKernelEsid
id|u64
id|xKernelEsid
suffix:semicolon
singleline_comment|// Esid used to map kernel load (0x0C00000000)&t;
DECL|member|xKernelVsid
id|u64
id|xKernelVsid
suffix:semicolon
singleline_comment|// Vsid used to map kernel load (0x0C00000000)
DECL|member|xPages
id|u64
id|xPages
suffix:semicolon
singleline_comment|// Number of pages to be mapped&t;(8192)
DECL|member|xOffset
id|u64
id|xOffset
suffix:semicolon
singleline_comment|// Offset from start of load area (0)
DECL|member|xVPN
id|u64
id|xVPN
suffix:semicolon
singleline_comment|// Virtual Page Number (0x000C000000000000)
)brace
suffix:semicolon
macro_line|#endif /* _LPARMAP_H */
eof
