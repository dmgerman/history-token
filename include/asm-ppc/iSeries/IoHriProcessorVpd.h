multiline_comment|/*&n; * IoHriProcessorVpd.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//===================================================================
singleline_comment|//
singleline_comment|//&t;This struct maps Processor Vpd that is DMAd to SLIC by CSP 
singleline_comment|//
macro_line|#ifndef&t;_TYPES_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _IOHRIPROCESSORVPD_H
DECL|macro|_IOHRIPROCESSORVPD_H
mdefine_line|#define _IOHRIPROCESSORVPD_H
DECL|struct|IoHriProcessorVpd
r_struct
id|IoHriProcessorVpd
(brace
DECL|member|xFormat
id|u8
id|xFormat
suffix:semicolon
singleline_comment|// VPD format indicator&t;&t;x00-x00
DECL|member|xProcStatus
id|u8
id|xProcStatus
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Processor State&t;&t;x01-x01
DECL|member|xSecondaryThreadCount
id|u8
id|xSecondaryThreadCount
suffix:semicolon
singleline_comment|// Secondary thread cnt&t;&t;x02-x02
DECL|member|xSrcType
id|u8
id|xSrcType
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Src Type&t;&t;&t;x03-x03
DECL|member|xSrcSoft
id|u8
id|xSrcSoft
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Src stay soft&t;&t;...
DECL|member|xSrcParable
id|u8
id|xSrcParable
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Src parable&t;&t;&t;...
DECL|member|xRsvd1
id|u8
id|xRsvd1
suffix:colon
l_int|5
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;...
DECL|member|xHvPhysicalProcIndex
id|u16
id|xHvPhysicalProcIndex
suffix:semicolon
singleline_comment|// Hypervisor physical proc index04-x05
DECL|member|xRsvd2
id|u16
id|xRsvd2
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x06-x07
DECL|member|xHwNodeId
id|u32
id|xHwNodeId
suffix:semicolon
singleline_comment|// Hardware node id&t;&t;x08-x0B
DECL|member|xHwProcId
id|u32
id|xHwProcId
suffix:semicolon
singleline_comment|// Hardware processor id&t;x0C-x0F
DECL|member|xTypeNum
id|u32
id|xTypeNum
suffix:semicolon
singleline_comment|// Card Type/CCIN number&t;x10-x13
DECL|member|xModelNum
id|u32
id|xModelNum
suffix:semicolon
singleline_comment|// Model/Feature number&t;&t;x14-x17
DECL|member|xSerialNum
id|u64
id|xSerialNum
suffix:semicolon
singleline_comment|// Serial number&t;&t;x18-x1F
DECL|member|xPartNum
r_char
id|xPartNum
(braket
l_int|12
)braket
suffix:semicolon
singleline_comment|// Book Part or FPU number&t;x20-x2B
DECL|member|xMfgID
r_char
id|xMfgID
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// Manufacturing ID&t;&t;x2C-x2F
DECL|member|xProcFreq
id|u32
id|xProcFreq
suffix:semicolon
singleline_comment|// Processor Frequency&t;&t;x30-x33
DECL|member|xTimeBaseFreq
id|u32
id|xTimeBaseFreq
suffix:semicolon
singleline_comment|// Time Base Frequency&t;&t;x34-x37
DECL|member|xChipEcLevel
id|u32
id|xChipEcLevel
suffix:semicolon
singleline_comment|// Chip EC Levels&t;&t;x38-x3B
DECL|member|xProcIdReg
id|u32
id|xProcIdReg
suffix:semicolon
singleline_comment|// PIR SPR value&t;&t;x3C-x3F
DECL|member|xPVR
id|u32
id|xPVR
suffix:semicolon
singleline_comment|// PVR value&t;&t;&t;x40-x43
DECL|member|xRsvd3
id|u8
id|xRsvd3
(braket
l_int|12
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x44-x4F
DECL|member|xInstCacheSize
id|u32
id|xInstCacheSize
suffix:semicolon
singleline_comment|// Instruction cache size in KB&t;x50-x53
DECL|member|xInstBlockSize
id|u32
id|xInstBlockSize
suffix:semicolon
singleline_comment|// Instruction cache block size&t;x54-x57
DECL|member|xDataCacheOperandSize
id|u32
id|xDataCacheOperandSize
suffix:semicolon
singleline_comment|// Data cache operand size&t;x58-x5B
DECL|member|xInstCacheOperandSize
id|u32
id|xInstCacheOperandSize
suffix:semicolon
singleline_comment|// Inst cache operand size&t;x5C-x5F
DECL|member|xDataL1CacheSizeKB
id|u32
id|xDataL1CacheSizeKB
suffix:semicolon
singleline_comment|// L1 data cache size in KB&t;x60-x63
DECL|member|xDataL1CacheLineSize
id|u32
id|xDataL1CacheLineSize
suffix:semicolon
singleline_comment|// L1 data cache block size&t;x64-x67
DECL|member|xRsvd4
id|u64
id|xRsvd4
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x68-x6F
DECL|member|xDataL2CacheSizeKB
id|u32
id|xDataL2CacheSizeKB
suffix:semicolon
singleline_comment|// L2 data cache size in KB&t;x70-x73
DECL|member|xDataL2CacheLineSize
id|u32
id|xDataL2CacheLineSize
suffix:semicolon
singleline_comment|// L2 data cache block size&t;x74-x77
DECL|member|xRsvd5
id|u64
id|xRsvd5
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x78-x7F
DECL|member|xDataL3CacheSizeKB
id|u32
id|xDataL3CacheSizeKB
suffix:semicolon
singleline_comment|// L3 data cache size in KB&t;x80-x83
DECL|member|xDataL3CacheLineSize
id|u32
id|xDataL3CacheLineSize
suffix:semicolon
singleline_comment|// L3 data cache block size&t;x84-x87
DECL|member|xRsvd6
id|u64
id|xRsvd6
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x88-x8F
DECL|member|xFruLabel
id|u64
id|xFruLabel
suffix:semicolon
singleline_comment|// Card Location Label&t;&t;x90-x97
DECL|member|xSlotsOnCard
id|u8
id|xSlotsOnCard
suffix:semicolon
singleline_comment|// Slots on card (0=no slots)&t;x98-x98
DECL|member|xPartLocFlag
id|u8
id|xPartLocFlag
suffix:semicolon
singleline_comment|// Location flag (0-pluggable 1-imbedded) x99-x99
DECL|member|xSlotMapIndex
id|u16
id|xSlotMapIndex
suffix:semicolon
singleline_comment|// Index in slot map table&t;x9A-x9B
DECL|member|xSmartCardPortNo
id|u8
id|xSmartCardPortNo
suffix:semicolon
singleline_comment|// Smart card port number&t;x9C-x9C
DECL|member|xRsvd7
id|u8
id|xRsvd7
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x9D-x9D
DECL|member|xFrameIdAndRackUnit
id|u16
id|xFrameIdAndRackUnit
suffix:semicolon
singleline_comment|// Frame ID and rack unit adr&t;x9E-x9F
DECL|member|xRsvd8
id|u8
id|xRsvd8
(braket
l_int|24
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;xA0-xB7
DECL|member|xProcSrc
r_char
id|xProcSrc
(braket
l_int|72
)braket
suffix:semicolon
singleline_comment|// CSP format SRC&t;&t;xB8-xFF
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _IOHRIPROCESSORVPD_H
eof
