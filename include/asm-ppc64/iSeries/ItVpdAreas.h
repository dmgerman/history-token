multiline_comment|/*&n; * ItVpdAreas.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//=====================================================================================
singleline_comment|//
singleline_comment|//      This file defines the address and length of all of the VPD area passed to
singleline_comment|//&t;the OS from PLIC (most of which start from the SP).
singleline_comment|//
macro_line|#ifndef _PPC_TYPES_H
macro_line|#include        &lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _ITVPDAREAS_H
DECL|macro|_ITVPDAREAS_H
mdefine_line|#define _ITVPDAREAS_H
singleline_comment|// VPD Entry index is carved in stone - cannot be changed (easily).
DECL|macro|ItVpdCecVpd
mdefine_line|#define ItVpdCecVpd&t;&t;&t;&t;   0
DECL|macro|ItVpdDynamicSpace
mdefine_line|#define ItVpdDynamicSpace&t;&t;&t;   1
DECL|macro|ItVpdExtVpd
mdefine_line|#define ItVpdExtVpd&t;&t;&t;&t;   2
DECL|macro|ItVpdExtVpdOnPanel
mdefine_line|#define ItVpdExtVpdOnPanel&t;&t;&t;   3
DECL|macro|ItVpdFirstPaca
mdefine_line|#define ItVpdFirstPaca&t;&t;&t;&t;   4
DECL|macro|ItVpdIoVpd
mdefine_line|#define ItVpdIoVpd&t;&t;&t;&t;   5
DECL|macro|ItVpdIplParms
mdefine_line|#define ItVpdIplParms&t;&t;&t;&t;   6
DECL|macro|ItVpdMsVpd
mdefine_line|#define ItVpdMsVpd&t;&t;&t;&t;   7
DECL|macro|ItVpdPanelVpd
mdefine_line|#define ItVpdPanelVpd&t;&t;&t;&t;   8
DECL|macro|ItVpdLpNaca
mdefine_line|#define ItVpdLpNaca&t;&t;&t;&t;   9
DECL|macro|ItVpdBackplaneAndMaybeClockCardVpd
mdefine_line|#define ItVpdBackplaneAndMaybeClockCardVpd        10 
DECL|macro|ItVpdRecoveryLogBuffer
mdefine_line|#define ItVpdRecoveryLogBuffer&t;&t;          11
DECL|macro|ItVpdSpCommArea
mdefine_line|#define ItVpdSpCommArea&t;&t;&t;&t;  12
DECL|macro|ItVpdSpLogBuffer
mdefine_line|#define ItVpdSpLogBuffer&t;&t;&t;  13
DECL|macro|ItVpdSpLogBufferSave
mdefine_line|#define ItVpdSpLogBufferSave&t;&t;&t;  14
DECL|macro|ItVpdSpCardVpd
mdefine_line|#define ItVpdSpCardVpd&t;&t;&t;&t;  15
DECL|macro|ItVpdFirstProcVpd
mdefine_line|#define ItVpdFirstProcVpd&t;&t;&t;  16&t;
DECL|macro|ItVpdApModelVpd
mdefine_line|#define ItVpdApModelVpd&t;&t;&t;&t;  17
DECL|macro|ItVpdClockCardVpd
mdefine_line|#define ItVpdClockCardVpd&t;&t;&t;  18
DECL|macro|ItVpdBusExtCardVpd
mdefine_line|#define ItVpdBusExtCardVpd&t;&t;&t;  19
DECL|macro|ItVpdProcCapacityVpd
mdefine_line|#define ItVpdProcCapacityVpd&t;&t;&t;  20
DECL|macro|ItVpdInteractiveCapacityVpd
mdefine_line|#define ItVpdInteractiveCapacityVpd&t;&t;  21
DECL|macro|ItVpdFirstSlotLabel
mdefine_line|#define ItVpdFirstSlotLabel&t;&t;&t;  22
DECL|macro|ItVpdFirstLpQueue
mdefine_line|#define ItVpdFirstLpQueue&t;&t;&t;  23
DECL|macro|ItVpdFirstL3CacheVpd
mdefine_line|#define ItVpdFirstL3CacheVpd&t;&t;&t;  24&t;
DECL|macro|ItVpdFirstProcFruVpd
mdefine_line|#define ItVpdFirstProcFruVpd&t;&t;&t;  25
DECL|macro|ItVpdMaxEntries
mdefine_line|#define ItVpdMaxEntries&t;&t;&t;&t;  26
DECL|macro|ItDmaMaxEntries
mdefine_line|#define ItDmaMaxEntries&t;&t;&t;&t;  10
DECL|macro|ItVpdAreasMaxSlotLabels
mdefine_line|#define ItVpdAreasMaxSlotLabels&t;&t; 192 
DECL|struct|SlicVpdAdrs
r_struct
id|SlicVpdAdrs
(brace
DECL|member|pad1
id|u32
id|pad1
suffix:semicolon
DECL|member|vpdAddr
r_void
op_star
id|vpdAddr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ItVpdAreas
r_struct
id|ItVpdAreas
(brace
DECL|member|xSlicDesc
id|u32
id|xSlicDesc
suffix:semicolon
singleline_comment|// Descriptor&t;&t;&t;&t;000-003
DECL|member|xSlicSize
id|u16
id|xSlicSize
suffix:semicolon
singleline_comment|// Size of this control block&t;&t;004-005
DECL|member|xPlicAdjustVpdLens
id|u16
id|xPlicAdjustVpdLens
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Flag to indicate new interface &t;006-007
DECL|member|xRsvd1
id|u16
id|xRsvd1
suffix:colon
l_int|15
suffix:semicolon
singleline_comment|// Reserved bits&t;&t;&t;...
DECL|member|xSlicVpdEntries
id|u16
id|xSlicVpdEntries
suffix:semicolon
singleline_comment|// Number of VPD entries&t;&t;008-009
DECL|member|xSlicDmaEntries
id|u16
id|xSlicDmaEntries
suffix:semicolon
singleline_comment|// Number of DMA entries&t;&t;00A-00B
DECL|member|xSlicMaxLogicalProcs
id|u16
id|xSlicMaxLogicalProcs
suffix:semicolon
singleline_comment|// Maximum logical processors&t;&t;00C-00D
DECL|member|xSlicMaxPhysicalProcs
id|u16
id|xSlicMaxPhysicalProcs
suffix:semicolon
singleline_comment|// Maximum physical processors&t;&t;00E-00F
DECL|member|xSlicDmaToksOffset
id|u16
id|xSlicDmaToksOffset
suffix:semicolon
singleline_comment|// Offset into this of array&t;&t;010-011
DECL|member|xSlicVpdAdrsOffset
id|u16
id|xSlicVpdAdrsOffset
suffix:semicolon
singleline_comment|// Offset into this of array&t;&t;012-013
DECL|member|xSlicDmaLensOffset
id|u16
id|xSlicDmaLensOffset
suffix:semicolon
singleline_comment|// Offset into this of array&t;&t;014-015
DECL|member|xSlicVpdLensOffset
id|u16
id|xSlicVpdLensOffset
suffix:semicolon
singleline_comment|// Offset into this of array&t;&t;016-017
DECL|member|xSlicMaxSlotLabels
id|u16
id|xSlicMaxSlotLabels
suffix:semicolon
singleline_comment|// Maximum number of slot labels&t;018-019
DECL|member|xSlicMaxLpQueues
id|u16
id|xSlicMaxLpQueues
suffix:semicolon
singleline_comment|// Maximum number of LP Queues&t;&t;01A-01B
DECL|member|xRsvd2
id|u8
id|xRsvd2
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;01C-01F
DECL|member|xRsvd3
id|u64
id|xRsvd3
(braket
l_int|12
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;020-07F
DECL|member|xPlicDmaLens
id|u32
id|xPlicDmaLens
(braket
id|ItDmaMaxEntries
)braket
suffix:semicolon
singleline_comment|// Array of DMA lengths&t;&t;080-0A7
DECL|member|xPlicDmaToks
id|u32
id|xPlicDmaToks
(braket
id|ItDmaMaxEntries
)braket
suffix:semicolon
singleline_comment|// Array of DMA tokens&t;&t;0A8-0CF
DECL|member|xSlicVpdLens
id|u32
id|xSlicVpdLens
(braket
id|ItVpdMaxEntries
)braket
suffix:semicolon
singleline_comment|// Array of VPD lengths&t;&t;0D0-12F
DECL|member|xSlicVpdAdrs
r_void
op_star
id|xSlicVpdAdrs
(braket
id|ItVpdMaxEntries
)braket
suffix:semicolon
singleline_comment|// Array of VPD buffers&t;130-1EF
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _ITVPDAREAS_H
eof
