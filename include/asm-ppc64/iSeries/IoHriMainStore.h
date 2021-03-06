multiline_comment|/*&n; * IoHriMainStore.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _IOHRIMAINSTORE_H
DECL|macro|_IOHRIMAINSTORE_H
mdefine_line|#define _IOHRIMAINSTORE_H
multiline_comment|/* Main Store Vpd for Condor,iStar,sStar */
DECL|struct|IoHriMainStoreSegment4
r_struct
id|IoHriMainStoreSegment4
(brace
DECL|member|msArea0Exists
id|u8
id|msArea0Exists
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea1Exists
id|u8
id|msArea1Exists
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea2Exists
id|u8
id|msArea2Exists
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea3Exists
id|u8
id|msArea3Exists
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|msArea0Functional
id|u8
id|msArea0Functional
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea1Functional
id|u8
id|msArea1Functional
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea2Functional
id|u8
id|msArea2Functional
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea3Functional
id|u8
id|msArea3Functional
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
id|u8
id|reserved3
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved4
id|u8
id|reserved4
suffix:semicolon
DECL|member|totalMainStore
id|u32
id|totalMainStore
suffix:semicolon
DECL|member|msArea0Ptr
id|u64
id|msArea0Ptr
suffix:semicolon
DECL|member|msArea1Ptr
id|u64
id|msArea1Ptr
suffix:semicolon
DECL|member|msArea2Ptr
id|u64
id|msArea2Ptr
suffix:semicolon
DECL|member|msArea3Ptr
id|u64
id|msArea3Ptr
suffix:semicolon
DECL|member|cardProductionLevel
id|u32
id|cardProductionLevel
suffix:semicolon
DECL|member|msAdrHole
id|u32
id|msAdrHole
suffix:semicolon
DECL|member|msArea0HasRiserVpd
id|u8
id|msArea0HasRiserVpd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea1HasRiserVpd
id|u8
id|msArea1HasRiserVpd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea2HasRiserVpd
id|u8
id|msArea2HasRiserVpd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msArea3HasRiserVpd
id|u8
id|msArea3HasRiserVpd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved5
id|u8
id|reserved5
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved6
id|u8
id|reserved6
suffix:semicolon
DECL|member|reserved7
id|u16
id|reserved7
suffix:semicolon
DECL|member|reserved8
id|u8
id|reserved8
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|nonInterleavedBlocksStartAdr
id|u64
id|nonInterleavedBlocksStartAdr
suffix:semicolon
DECL|member|nonInterleavedBlocksEndAdr
id|u64
id|nonInterleavedBlocksEndAdr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Main Store VPD for Power4 */
DECL|struct|IoHriMainStoreChipInfo1
r_struct
id|IoHriMainStoreChipInfo1
(brace
id|u32
id|chipMfgID
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_char
id|chipECLevel
(braket
l_int|4
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|IoHriMainStoreVpdIdData
r_struct
id|IoHriMainStoreVpdIdData
(brace
DECL|member|typeNumber
r_char
id|typeNumber
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|modelNumber
r_char
id|modelNumber
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|partNumber
r_char
id|partNumber
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|serialNumber
r_char
id|serialNumber
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|IoHriMainStoreVpdFruData
r_struct
id|IoHriMainStoreVpdFruData
(brace
r_char
id|fruLabel
(braket
l_int|8
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|numberOfSlots
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|pluggingType
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u16
id|slotMapIndex
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|IoHriMainStoreAdrRangeBlock
r_struct
id|IoHriMainStoreAdrRangeBlock
(brace
r_void
op_star
id|blockStart
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_void
op_star
id|blockEnd
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|blockProcChipId
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MaxAreaAdrRangeBlocks
mdefine_line|#define MaxAreaAdrRangeBlocks 4
DECL|struct|IoHriMainStoreArea4
r_struct
id|IoHriMainStoreArea4
(brace
id|u32
id|msVpdFormat
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|containedVpdType
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|reserved1
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u16
id|reserved2
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u64
id|msExists
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u64
id|msFunctional
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|memorySize
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|procNodeId
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|numAdrRangeBlocks
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreAdrRangeBlock
id|xAdrRangeBlock
(braket
id|MaxAreaAdrRangeBlocks
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo0
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo1
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo2
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo3
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo4
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo5
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo6
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreChipInfo1
id|chipInfo7
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_void
op_star
id|msRamAreaArray
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|msRamAreaArrayNumEntries
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|msRamAreaArrayEntrySize
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|numaDimmExists
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|numaDimmFunctional
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_void
op_star
id|numaDimmArray
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|numaDimmArrayNumEntries
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|numaDimmArrayEntrySize
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreVpdIdData
id|idData
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u64
id|powerData
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u64
id|cardAssemblyPartNum
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u64
id|chipSerialNum
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u64
id|reserved3
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_char
id|reserved4
(braket
l_int|16
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_struct
id|IoHriMainStoreVpdFruData
id|fruData
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|vpdPortNum
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|reserved5
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|frameId
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|rackUnit
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_char
id|asciiKeywordVpd
(braket
l_int|256
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|reserved6
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|IoHriMainStoreSegment5
r_struct
id|IoHriMainStoreSegment5
(brace
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|msVpdFormat
id|u8
id|msVpdFormat
suffix:semicolon
DECL|member|totalMainStore
id|u32
id|totalMainStore
suffix:semicolon
DECL|member|maxConfiguredMsAdr
id|u64
id|maxConfiguredMsAdr
suffix:semicolon
DECL|member|msAreaArray
r_struct
id|IoHriMainStoreArea4
op_star
id|msAreaArray
suffix:semicolon
DECL|member|msAreaArrayNumEntries
id|u32
id|msAreaArrayNumEntries
suffix:semicolon
DECL|member|msAreaArrayEntrySize
id|u32
id|msAreaArrayEntrySize
suffix:semicolon
DECL|member|msAreaExists
id|u32
id|msAreaExists
suffix:semicolon
DECL|member|msAreaFunctional
id|u32
id|msAreaFunctional
suffix:semicolon
DECL|member|reserved3
id|u64
id|reserved3
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _IOHRIMAINSTORE_H
eof
