multiline_comment|/*&n; * ItLpNaca.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//=============================================================================
singleline_comment|//
singleline_comment|//&t;This control block contains the data that is shared between the
singleline_comment|//&t;hypervisor (PLIC) and the OS.
singleline_comment|//
singleline_comment|//=============================================================================
macro_line|#ifndef _ITLPNACA_H
DECL|macro|_ITLPNACA_H
mdefine_line|#define _ITLPNACA_H
DECL|struct|ItLpNaca
r_struct
id|ItLpNaca
(brace
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_1 0x0000 - 0x007F Contains read-only data
singleline_comment|//=============================================================================
DECL|member|xDesc
id|u32
id|xDesc
suffix:semicolon
singleline_comment|// Eye catcher&t;&t;&t;x00-x03
DECL|member|xSize
id|u16
id|xSize
suffix:semicolon
singleline_comment|// Size of this class&t;&t;x04-x05
DECL|member|xIntHdlrOffset
id|u16
id|xIntHdlrOffset
suffix:semicolon
singleline_comment|// Offset to IntHdlr array&t;x06-x07
DECL|member|xMaxIntHdlrEntries
id|u8
id|xMaxIntHdlrEntries
suffix:semicolon
singleline_comment|// Number of entries in array&t;x08-x08
DECL|member|xPrimaryLpIndex
id|u8
id|xPrimaryLpIndex
suffix:semicolon
singleline_comment|// LP Index of Primary&t;&t;x09-x09
DECL|member|xServiceLpIndex
id|u8
id|xServiceLpIndex
suffix:semicolon
singleline_comment|// LP Ind of Service Focal Pointx0A-x0A
DECL|member|xLpIndex
id|u8
id|xLpIndex
suffix:semicolon
singleline_comment|// LP Index&t;&t;&t;x0B-x0B
DECL|member|xMaxLpQueues
id|u16
id|xMaxLpQueues
suffix:semicolon
singleline_comment|// Number of allocated queues&t;x0C-x0D
DECL|member|xLpQueueOffset
id|u16
id|xLpQueueOffset
suffix:semicolon
singleline_comment|// Offset to start of LP queues&t;x0E-x0F
DECL|member|xPirEnvironMode
id|u8
id|xPirEnvironMode
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Piranha or hardware&t;&t;x10-x10
DECL|member|xPirConsoleMode
id|u8
id|xPirConsoleMode
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Piranha console indicator&t;x11-x11
DECL|member|xPirDasdMode
id|u8
id|xPirDasdMode
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Piranha dasd indicator&t;x12-x12
DECL|member|xRsvd1_0
id|u8
id|xRsvd1_0
(braket
l_int|5
)braket
suffix:semicolon
singleline_comment|// Reserved for Piranha related&t;x13-x17
DECL|member|xLparInstalled
id|u8
id|xLparInstalled
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Is LPAR installed on system&t;x18-x1F
DECL|member|xSysPartitioned
id|u8
id|xSysPartitioned
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Is the system partitioned&t;...
DECL|member|xHwSyncedTBs
id|u8
id|xHwSyncedTBs
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Hardware synced TBs&t;&t;...
DECL|member|xIntProcUtilHmt
id|u8
id|xIntProcUtilHmt
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Utilize HMT for interrupts&t;...
DECL|member|xRsvd1_1
id|u8
id|xRsvd1_1
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;...
DECL|member|xSpVpdFormat
id|u8
id|xSpVpdFormat
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// VPD areas are in CSP format&t;...
DECL|member|xIntProcRatio
id|u8
id|xIntProcRatio
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Ratio of int procs to procs&t;...
DECL|member|xRsvd1_2
id|u8
id|xRsvd1_2
(braket
l_int|5
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;...
DECL|member|xRsvd1_3
id|u16
id|xRsvd1_3
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x20-x21
DECL|member|xPlicVrmIndex
id|u16
id|xPlicVrmIndex
suffix:semicolon
singleline_comment|// VRM index of PLIC&t;&t;x22-x23
DECL|member|xMinSupportedSlicVrmInd
id|u16
id|xMinSupportedSlicVrmInd
suffix:semicolon
singleline_comment|// Min supported OS VRM index&t;x24-x25
DECL|member|xMinCompatableSlicVrmInd
id|u16
id|xMinCompatableSlicVrmInd
suffix:semicolon
singleline_comment|// Min compatable OS VRM index x26-x27
DECL|member|xLoadAreaAddr
id|u64
id|xLoadAreaAddr
suffix:semicolon
singleline_comment|// ER address of load area&t;x28-x2F
DECL|member|xLoadAreaChunks
id|u32
id|xLoadAreaChunks
suffix:semicolon
singleline_comment|// Chunks for the load area&t;x30-x33
DECL|member|xPaseSysCallCRMask
id|u32
id|xPaseSysCallCRMask
suffix:semicolon
singleline_comment|// Mask used to test CR before  x34-x37
singleline_comment|// doing an ASR switch on PASE
singleline_comment|// system call.
DECL|member|xSlicSegmentTablePtr
id|u64
id|xSlicSegmentTablePtr
suffix:semicolon
singleline_comment|// Pointer to Slic seg table.   x38-x3f
DECL|member|xRsvd1_4
id|u8
id|xRsvd1_4
(braket
l_int|64
)braket
suffix:semicolon
singleline_comment|//         &t;&t;&t;x40-x7F 
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_2 0x0080 - 0x00FF Contains local read-write data
singleline_comment|//=============================================================================
DECL|member|xRsvd2_0
id|u8
id|xRsvd2_0
(braket
l_int|128
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x00-x7F
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_3-6 0x0100 - 0x02FF Contains LP Queue indicators
singleline_comment|// NB: Padding required to keep xInterrruptHdlr at x300 which is required 
singleline_comment|// for v4r4 PLIC.
singleline_comment|//=============================================================================
DECL|member|xOldLpQueue
id|u8
id|xOldLpQueue
(braket
l_int|128
)braket
suffix:semicolon
singleline_comment|// LP Queue needed for v4r4&t;100-17F
DECL|member|xRsvd3_0
id|u8
id|xRsvd3_0
(braket
l_int|384
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;180-2FF
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_7-8 0x0300 - 0x03FF Contains the address of the OS interrupt
singleline_comment|//  handlers
singleline_comment|//=============================================================================
DECL|member|xInterruptHdlr
id|u64
id|xInterruptHdlr
(braket
l_int|32
)braket
suffix:semicolon
singleline_comment|// Interrupt handlers&t;&t;300-x3FF
)brace
suffix:semicolon
singleline_comment|//=============================================================================
macro_line|#endif 
singleline_comment|// _ITLPNACA_H
eof
