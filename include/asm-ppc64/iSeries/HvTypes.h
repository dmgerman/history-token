multiline_comment|/*&n; * HvTypes.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _HVTYPES_H
DECL|macro|_HVTYPES_H
mdefine_line|#define _HVTYPES_H
singleline_comment|//===========================================================================
singleline_comment|//                                                             Header File Id
singleline_comment|// Name______________:  HvTypes.H
singleline_comment|//
singleline_comment|// Description_______:
singleline_comment|//
singleline_comment|//&t;General typedefs for the hypervisor.
singleline_comment|//
singleline_comment|// Declared Class(es):
singleline_comment|//
singleline_comment|//===========================================================================
macro_line|#include &lt;asm/types.h&gt;
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Typedefs
singleline_comment|//-------------------------------------------------------------------
DECL|typedef|HvLpIndex
r_typedef
id|u8
id|HvLpIndex
suffix:semicolon
DECL|typedef|HvLpInstanceId
r_typedef
id|u16
id|HvLpInstanceId
suffix:semicolon
DECL|typedef|HvLpTOD
r_typedef
id|u64
id|HvLpTOD
suffix:semicolon
DECL|typedef|HvLpSystemSerialNum
r_typedef
id|u64
id|HvLpSystemSerialNum
suffix:semicolon
DECL|typedef|HvLpDeviceSerialNum
r_typedef
id|u8
id|HvLpDeviceSerialNum
(braket
l_int|12
)braket
suffix:semicolon
DECL|typedef|HvLpSanHwSet
r_typedef
id|u16
id|HvLpSanHwSet
suffix:semicolon
DECL|typedef|HvLpBus
r_typedef
id|u16
id|HvLpBus
suffix:semicolon
DECL|typedef|HvLpBoard
r_typedef
id|u16
id|HvLpBoard
suffix:semicolon
DECL|typedef|HvLpCard
r_typedef
id|u16
id|HvLpCard
suffix:semicolon
DECL|typedef|HvLpDeviceType
r_typedef
id|u8
id|HvLpDeviceType
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|HvLpDeviceModel
r_typedef
id|u8
id|HvLpDeviceModel
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|HvIoToken
r_typedef
id|u64
id|HvIoToken
suffix:semicolon
DECL|typedef|HvLpName
r_typedef
id|u8
id|HvLpName
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|HvIoId
r_typedef
id|u32
id|HvIoId
suffix:semicolon
DECL|typedef|HvRealMemoryIndex
r_typedef
id|u64
id|HvRealMemoryIndex
suffix:semicolon
DECL|typedef|HvLpIndexMap
r_typedef
id|u32
id|HvLpIndexMap
suffix:semicolon
singleline_comment|// Must hold HvMaxArchitectedLps bits!!!
DECL|typedef|HvLpVrmIndex
r_typedef
id|u16
id|HvLpVrmIndex
suffix:semicolon
DECL|typedef|HvXmGenerationId
r_typedef
id|u32
id|HvXmGenerationId
suffix:semicolon
DECL|typedef|HvLpBusPool
r_typedef
id|u8
id|HvLpBusPool
suffix:semicolon
DECL|typedef|HvLpSharedPoolIndex
r_typedef
id|u8
id|HvLpSharedPoolIndex
suffix:semicolon
DECL|typedef|HvLpSharedProcUnitsX100
r_typedef
id|u16
id|HvLpSharedProcUnitsX100
suffix:semicolon
DECL|typedef|HvLpVirtualLanIndex
r_typedef
id|u8
id|HvLpVirtualLanIndex
suffix:semicolon
DECL|typedef|HvLpVirtualLanIndexMap
r_typedef
id|u16
id|HvLpVirtualLanIndexMap
suffix:semicolon
singleline_comment|// Must hold HvMaxArchitectedVirtualLans bits!!!
DECL|typedef|HvBusNumber
r_typedef
id|u16
id|HvBusNumber
suffix:semicolon
singleline_comment|// Hypervisor Bus Number
DECL|typedef|HvSubBusNumber
r_typedef
id|u8
id|HvSubBusNumber
suffix:semicolon
singleline_comment|// Hypervisor SubBus Number
DECL|typedef|HvAgentId
r_typedef
id|u8
id|HvAgentId
suffix:semicolon
singleline_comment|// Hypervisor DevFn
DECL|macro|HVMAXARCHITECTEDLPS
mdefine_line|#define HVMAXARCHITECTEDLPS 32
DECL|macro|HVMAXARCHITECTEDVIRTUALLANS
mdefine_line|#define HVMAXARCHITECTEDVIRTUALLANS 16
DECL|macro|HVMAXARCHITECTEDVIRTUALDISKS
mdefine_line|#define HVMAXARCHITECTEDVIRTUALDISKS 32
DECL|macro|HVMAXARCHITECTEDVIRTUALCDROMS
mdefine_line|#define HVMAXARCHITECTEDVIRTUALCDROMS 8
DECL|macro|HVMAXARCHITECTEDVIRTUALTAPES
mdefine_line|#define HVMAXARCHITECTEDVIRTUALTAPES 8
DECL|macro|HVCHUNKSIZE
mdefine_line|#define HVCHUNKSIZE 256 * 1024
DECL|macro|HVPAGESIZE
mdefine_line|#define HVPAGESIZE 4 * 1024
DECL|macro|HVLPMINMEGSPRIMARY
mdefine_line|#define HVLPMINMEGSPRIMARY 256
DECL|macro|HVLPMINMEGSSECONDARY
mdefine_line|#define HVLPMINMEGSSECONDARY 64
DECL|macro|HVCHUNKSPERMEG
mdefine_line|#define HVCHUNKSPERMEG 4
DECL|macro|HVPAGESPERMEG
mdefine_line|#define HVPAGESPERMEG 256
DECL|macro|HVPAGESPERCHUNK
mdefine_line|#define HVPAGESPERCHUNK 64
DECL|macro|HvMaxArchitectedLps
mdefine_line|#define HvMaxArchitectedLps &t;&t;((HvLpIndex)HVMAXARCHITECTEDLPS)
DECL|macro|HvMaxArchitectedVirtualLans
mdefine_line|#define HvMaxArchitectedVirtualLans&t;((HvLpVirtualLanIndex)16)
DECL|macro|HvLpIndexInvalid
mdefine_line|#define HvLpIndexInvalid&t;&t;((HvLpIndex)0xff)
singleline_comment|//--------------------------------------------------------------------
singleline_comment|// Enums for the sub-components under PLIC
singleline_comment|// Used in HvCall  and HvPrimaryCall
singleline_comment|//--------------------------------------------------------------------
DECL|enum|HvCallCompIds
r_enum
id|HvCallCompIds
(brace
DECL|enumerator|HvCallCompId
id|HvCallCompId
op_assign
l_int|0
comma
DECL|enumerator|HvCallCpuCtlsCompId
id|HvCallCpuCtlsCompId
op_assign
l_int|1
comma
DECL|enumerator|HvCallCfgCompId
id|HvCallCfgCompId
op_assign
l_int|2
comma
DECL|enumerator|HvCallEventCompId
id|HvCallEventCompId
op_assign
l_int|3
comma
DECL|enumerator|HvCallHptCompId
id|HvCallHptCompId
op_assign
l_int|4
comma
DECL|enumerator|HvCallPciCompId
id|HvCallPciCompId
op_assign
l_int|5
comma
DECL|enumerator|HvCallSlmCompId
id|HvCallSlmCompId
op_assign
l_int|6
comma
DECL|enumerator|HvCallSmCompId
id|HvCallSmCompId
op_assign
l_int|7
comma
DECL|enumerator|HvCallSpdCompId
id|HvCallSpdCompId
op_assign
l_int|8
comma
DECL|enumerator|HvCallXmCompId
id|HvCallXmCompId
op_assign
l_int|9
comma
DECL|enumerator|HvCallRioCompId
id|HvCallRioCompId
op_assign
l_int|10
comma
DECL|enumerator|HvCallRsvd3CompId
id|HvCallRsvd3CompId
op_assign
l_int|11
comma
DECL|enumerator|HvCallRsvd2CompId
id|HvCallRsvd2CompId
op_assign
l_int|12
comma
DECL|enumerator|HvCallRsvd1CompId
id|HvCallRsvd1CompId
op_assign
l_int|13
comma
DECL|enumerator|HvCallMaxCompId
id|HvCallMaxCompId
op_assign
l_int|14
comma
DECL|enumerator|HvPrimaryCallCompId
id|HvPrimaryCallCompId
op_assign
l_int|0
comma
DECL|enumerator|HvPrimaryCallCfgCompId
id|HvPrimaryCallCfgCompId
op_assign
l_int|1
comma
DECL|enumerator|HvPrimaryCallPciCompId
id|HvPrimaryCallPciCompId
op_assign
l_int|2
comma
DECL|enumerator|HvPrimaryCallSmCompId
id|HvPrimaryCallSmCompId
op_assign
l_int|3
comma
DECL|enumerator|HvPrimaryCallSpdCompId
id|HvPrimaryCallSpdCompId
op_assign
l_int|4
comma
DECL|enumerator|HvPrimaryCallXmCompId
id|HvPrimaryCallXmCompId
op_assign
l_int|5
comma
DECL|enumerator|HvPrimaryCallRioCompId
id|HvPrimaryCallRioCompId
op_assign
l_int|6
comma
DECL|enumerator|HvPrimaryCallRsvd7CompId
id|HvPrimaryCallRsvd7CompId
op_assign
l_int|7
comma
DECL|enumerator|HvPrimaryCallRsvd6CompId
id|HvPrimaryCallRsvd6CompId
op_assign
l_int|8
comma
DECL|enumerator|HvPrimaryCallRsvd5CompId
id|HvPrimaryCallRsvd5CompId
op_assign
l_int|9
comma
DECL|enumerator|HvPrimaryCallRsvd4CompId
id|HvPrimaryCallRsvd4CompId
op_assign
l_int|10
comma
DECL|enumerator|HvPrimaryCallRsvd3CompId
id|HvPrimaryCallRsvd3CompId
op_assign
l_int|11
comma
DECL|enumerator|HvPrimaryCallRsvd2CompId
id|HvPrimaryCallRsvd2CompId
op_assign
l_int|12
comma
DECL|enumerator|HvPrimaryCallRsvd1CompId
id|HvPrimaryCallRsvd1CompId
op_assign
l_int|13
comma
DECL|enumerator|HvPrimaryCallMaxCompId
id|HvPrimaryCallMaxCompId
op_assign
id|HvCallMaxCompId
)brace
suffix:semicolon
DECL|struct|HvLpBufferList
r_struct
id|HvLpBufferList
(brace
DECL|member|addr
id|u64
id|addr
suffix:semicolon
DECL|member|len
id|u64
id|len
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _HVTYPES_H */
eof
