multiline_comment|/*&n; * HvCallEvent.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//==================================================================
singleline_comment|//
singleline_comment|//&t;This file contains the &quot;hypervisor call&quot; interface which is used to
singleline_comment|//&t;drive the hypervisor from the OS.
singleline_comment|//
singleline_comment|//==================================================================
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef  _HVCALLSC_H
macro_line|#include &lt;asm/iSeries/HvCallSc.h&gt;
macro_line|#endif
macro_line|#ifndef  _HVTYPES_H
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef _HVCALLEVENT_H
DECL|macro|_HVCALLEVENT_H
mdefine_line|#define _HVCALLEVENT_H
r_struct
id|HvLpEvent
suffix:semicolon
DECL|typedef|HvLpEvent_Type
r_typedef
id|u8
id|HvLpEvent_Type
suffix:semicolon
DECL|typedef|HvLpEvent_AckInd
r_typedef
id|u8
id|HvLpEvent_AckInd
suffix:semicolon
DECL|typedef|HvLpEvent_AckType
r_typedef
id|u8
id|HvLpEvent_AckType
suffix:semicolon
DECL|struct|HvCallEvent_PackedParms
r_struct
id|HvCallEvent_PackedParms
(brace
DECL|member|xAckType
id|u8
id|xAckType
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xAckInd
id|u8
id|xAckInd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xRsvd
id|u8
id|xRsvd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xTargetLp
id|u8
id|xTargetLp
suffix:colon
l_int|5
suffix:semicolon
DECL|member|xType
id|u8
id|xType
suffix:semicolon
DECL|member|xSubtype
id|u16
id|xSubtype
suffix:semicolon
DECL|member|xSourceInstId
id|HvLpInstanceId
id|xSourceInstId
suffix:semicolon
DECL|member|xTargetInstId
id|HvLpInstanceId
id|xTargetInstId
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|HvLpDma_Direction
r_typedef
id|u8
id|HvLpDma_Direction
suffix:semicolon
DECL|typedef|HvLpDma_AddressType
r_typedef
id|u8
id|HvLpDma_AddressType
suffix:semicolon
DECL|struct|HvCallEvent_PackedDmaParms
r_struct
id|HvCallEvent_PackedDmaParms
(brace
DECL|member|xDirection
id|u8
id|xDirection
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xLocalAddrType
id|u8
id|xLocalAddrType
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xRemoteAddrType
id|u8
id|xRemoteAddrType
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xRsvd1
id|u8
id|xRsvd1
suffix:colon
l_int|5
suffix:semicolon
DECL|member|xRemoteLp
id|HvLpIndex
id|xRemoteLp
suffix:semicolon
DECL|member|xType
id|u8
id|xType
suffix:semicolon
DECL|member|xRsvd2
id|u8
id|xRsvd2
suffix:semicolon
DECL|member|xLocalInstId
id|HvLpInstanceId
id|xLocalInstId
suffix:semicolon
DECL|member|xRemoteInstId
id|HvLpInstanceId
id|xRemoteInstId
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|HvLpEvent_Rc
r_typedef
id|u64
id|HvLpEvent_Rc
suffix:semicolon
DECL|typedef|HvLpDma_Rc
r_typedef
id|u64
id|HvLpDma_Rc
suffix:semicolon
DECL|macro|HvCallEventAckLpEvent
mdefine_line|#define HvCallEventAckLpEvent&t;&t;&t;&t;HvCallEvent +  0
DECL|macro|HvCallEventCancelLpEvent
mdefine_line|#define HvCallEventCancelLpEvent&t;&t;&t;HvCallEvent +  1
DECL|macro|HvCallEventCloseLpEventPath
mdefine_line|#define HvCallEventCloseLpEventPath&t;&t;&t;HvCallEvent +  2
DECL|macro|HvCallEventDmaBufList
mdefine_line|#define HvCallEventDmaBufList&t;&t;&t;&t;HvCallEvent +  3
DECL|macro|HvCallEventDmaSingle
mdefine_line|#define HvCallEventDmaSingle&t;&t;&t;&t;HvCallEvent +  4
DECL|macro|HvCallEventDmaToSp
mdefine_line|#define HvCallEventDmaToSp&t;&t;&t;&t;HvCallEvent +  5 
DECL|macro|HvCallEventGetOverflowLpEvents
mdefine_line|#define HvCallEventGetOverflowLpEvents&t;&t;&t;HvCallEvent +  6
DECL|macro|HvCallEventGetSourceLpInstanceId
mdefine_line|#define HvCallEventGetSourceLpInstanceId&t;&t;HvCallEvent +  7
DECL|macro|HvCallEventGetTargetLpInstanceId
mdefine_line|#define HvCallEventGetTargetLpInstanceId&t;&t;HvCallEvent +  8
DECL|macro|HvCallEventOpenLpEventPath
mdefine_line|#define HvCallEventOpenLpEventPath&t;&t;&t;HvCallEvent +  9
DECL|macro|HvCallEventSetLpEventStack
mdefine_line|#define HvCallEventSetLpEventStack&t;&t;&t;HvCallEvent + 10
DECL|macro|HvCallEventSignalLpEvent
mdefine_line|#define HvCallEventSignalLpEvent&t;&t;&t;HvCallEvent + 11
DECL|macro|HvCallEventSignalLpEventParms
mdefine_line|#define HvCallEventSignalLpEventParms&t;&t;&t;HvCallEvent + 12
DECL|macro|HvCallEventSetInterLpQueueIndex
mdefine_line|#define HvCallEventSetInterLpQueueIndex&t;&t;&t;HvCallEvent + 13
DECL|macro|HvCallEventSetLpEventQueueInterruptProc
mdefine_line|#define HvCallEventSetLpEventQueueInterruptProc&t;&t;HvCallEvent + 14
DECL|macro|HvCallEventRouter15
mdefine_line|#define HvCallEventRouter15&t;&t;&t;&t;HvCallEvent + 15
singleline_comment|//======================================================================
DECL|function|HvCallEvent_getOverflowLpEvents
r_static
r_inline
r_void
id|HvCallEvent_getOverflowLpEvents
c_func
(paren
id|u8
id|queueIndex
)paren
(brace
id|HvCall1
c_func
(paren
id|HvCallEventGetOverflowLpEvents
comma
id|queueIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//======================================================================
DECL|function|HvCallEvent_setInterLpQueueIndex
r_static
r_inline
r_void
id|HvCallEvent_setInterLpQueueIndex
c_func
(paren
id|u8
id|queueIndex
)paren
(brace
id|HvCall1
c_func
(paren
id|HvCallEventSetInterLpQueueIndex
comma
id|queueIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//======================================================================
DECL|function|HvCallEvent_setLpEventStack
r_static
r_inline
r_void
id|HvCallEvent_setLpEventStack
c_func
(paren
id|u8
id|queueIndex
comma
r_char
op_star
id|eventStackAddr
comma
id|u32
id|eventStackSize
)paren
(brace
id|u64
id|abs_addr
suffix:semicolon
id|abs_addr
op_assign
id|virt_to_absolute_outline
c_func
(paren
(paren
r_int
r_int
)paren
id|eventStackAddr
)paren
suffix:semicolon
id|HvCall3
c_func
(paren
id|HvCallEventSetLpEventStack
comma
id|queueIndex
comma
id|abs_addr
comma
id|eventStackSize
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//======================================================================
DECL|function|HvCallEvent_setLpEventQueueInterruptProc
r_static
r_inline
r_void
id|HvCallEvent_setLpEventQueueInterruptProc
c_func
(paren
id|u8
id|queueIndex
comma
id|u16
id|lpLogicalProcIndex
)paren
(brace
id|HvCall2
c_func
(paren
id|HvCallEventSetLpEventQueueInterruptProc
comma
id|queueIndex
comma
id|lpLogicalProcIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//=====================================================================
DECL|function|HvCallEvent_signalLpEvent
r_static
r_inline
id|HvLpEvent_Rc
id|HvCallEvent_signalLpEvent
c_func
(paren
r_struct
id|HvLpEvent
op_star
id|event
)paren
(brace
id|u64
id|abs_addr
suffix:semicolon
id|HvLpEvent_Rc
id|retVal
suffix:semicolon
id|abs_addr
op_assign
id|virt_to_absolute_outline
c_func
(paren
(paren
r_int
r_int
)paren
id|event
)paren
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpEvent_Rc
)paren
id|HvCall1
c_func
(paren
id|HvCallEventSignalLpEvent
comma
id|abs_addr
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCallEvent_signalLpEventFast
r_static
r_inline
id|HvLpEvent_Rc
id|HvCallEvent_signalLpEventFast
c_func
(paren
id|HvLpIndex
id|targetLp
comma
id|HvLpEvent_Type
id|type
comma
id|u16
id|subtype
comma
id|HvLpEvent_AckInd
id|ackInd
comma
id|HvLpEvent_AckType
id|ackType
comma
id|HvLpInstanceId
id|sourceInstanceId
comma
id|HvLpInstanceId
id|targetInstanceId
comma
id|u64
id|correlationToken
comma
id|u64
id|eventData1
comma
id|u64
id|eventData2
comma
id|u64
id|eventData3
comma
id|u64
id|eventData4
comma
id|u64
id|eventData5
)paren
(brace
id|HvLpEvent_Rc
id|retVal
suffix:semicolon
singleline_comment|// Pack the misc bits into a single Dword to pass to PLIC
r_union
(brace
r_struct
id|HvCallEvent_PackedParms
id|parms
suffix:semicolon
id|u64
id|dword
suffix:semicolon
)brace
id|packed
suffix:semicolon
id|packed.parms.xAckType
op_assign
id|ackType
suffix:semicolon
id|packed.parms.xAckInd
op_assign
id|ackInd
suffix:semicolon
id|packed.parms.xRsvd
op_assign
l_int|0
suffix:semicolon
id|packed.parms.xTargetLp
op_assign
id|targetLp
suffix:semicolon
id|packed.parms.xType
op_assign
id|type
suffix:semicolon
id|packed.parms.xSubtype
op_assign
id|subtype
suffix:semicolon
id|packed.parms.xSourceInstId
op_assign
id|sourceInstanceId
suffix:semicolon
id|packed.parms.xTargetInstId
op_assign
id|targetInstanceId
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpEvent_Rc
)paren
id|HvCall7
c_func
(paren
id|HvCallEventSignalLpEventParms
comma
id|packed.dword
comma
id|correlationToken
comma
id|eventData1
comma
id|eventData2
comma
id|eventData3
comma
id|eventData4
comma
id|eventData5
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallEvent_ackLpEvent
r_static
r_inline
id|HvLpEvent_Rc
id|HvCallEvent_ackLpEvent
c_func
(paren
r_struct
id|HvLpEvent
op_star
id|event
)paren
(brace
id|u64
id|abs_addr
suffix:semicolon
id|HvLpEvent_Rc
id|retVal
suffix:semicolon
id|abs_addr
op_assign
id|virt_to_absolute_outline
c_func
(paren
(paren
r_int
r_int
)paren
id|event
)paren
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpEvent_Rc
)paren
id|HvCall1
c_func
(paren
id|HvCallEventAckLpEvent
comma
id|abs_addr
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallEvent_cancelLpEvent
r_static
r_inline
id|HvLpEvent_Rc
id|HvCallEvent_cancelLpEvent
c_func
(paren
r_struct
id|HvLpEvent
op_star
id|event
)paren
(brace
id|u64
id|abs_addr
suffix:semicolon
id|HvLpEvent_Rc
id|retVal
suffix:semicolon
id|abs_addr
op_assign
id|virt_to_absolute_outline
c_func
(paren
(paren
r_int
r_int
)paren
id|event
)paren
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpEvent_Rc
)paren
id|HvCall1
c_func
(paren
id|HvCallEventCancelLpEvent
comma
id|abs_addr
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallEvent_getSourceLpInstanceId
r_static
r_inline
id|HvLpInstanceId
id|HvCallEvent_getSourceLpInstanceId
c_func
(paren
id|HvLpIndex
id|targetLp
comma
id|HvLpEvent_Type
id|type
)paren
(brace
id|HvLpInstanceId
id|retVal
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallEventGetSourceLpInstanceId
comma
id|targetLp
comma
id|type
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallEvent_getTargetLpInstanceId
r_static
r_inline
id|HvLpInstanceId
id|HvCallEvent_getTargetLpInstanceId
c_func
(paren
id|HvLpIndex
id|targetLp
comma
id|HvLpEvent_Type
id|type
)paren
(brace
id|HvLpInstanceId
id|retVal
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallEventGetTargetLpInstanceId
comma
id|targetLp
comma
id|type
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallEvent_openLpEventPath
r_static
r_inline
r_void
id|HvCallEvent_openLpEventPath
c_func
(paren
id|HvLpIndex
id|targetLp
comma
id|HvLpEvent_Type
id|type
)paren
(brace
id|HvCall2
c_func
(paren
id|HvCallEventOpenLpEventPath
comma
id|targetLp
comma
id|type
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//===================================================================
DECL|function|HvCallEvent_closeLpEventPath
r_static
r_inline
r_void
id|HvCallEvent_closeLpEventPath
c_func
(paren
id|HvLpIndex
id|targetLp
comma
id|HvLpEvent_Type
id|type
)paren
(brace
id|HvCall2
c_func
(paren
id|HvCallEventCloseLpEventPath
comma
id|targetLp
comma
id|type
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//===================================================================
DECL|function|HvCallEvent_dmaBufList
r_static
r_inline
id|HvLpDma_Rc
id|HvCallEvent_dmaBufList
c_func
(paren
id|HvLpEvent_Type
id|type
comma
id|HvLpIndex
id|remoteLp
comma
id|HvLpDma_Direction
id|direction
comma
id|HvLpInstanceId
id|localInstanceId
comma
id|HvLpInstanceId
id|remoteInstanceId
comma
id|HvLpDma_AddressType
id|localAddressType
comma
id|HvLpDma_AddressType
id|remoteAddressType
comma
singleline_comment|// Do these need to be converted to
singleline_comment|// absolute addresses?
id|u64
id|localBufList
comma
id|u64
id|remoteBufList
comma
id|u32
id|transferLength
)paren
(brace
id|HvLpDma_Rc
id|retVal
suffix:semicolon
singleline_comment|// Pack the misc bits into a single Dword to pass to PLIC
r_union
(brace
r_struct
id|HvCallEvent_PackedDmaParms
id|parms
suffix:semicolon
id|u64
id|dword
suffix:semicolon
)brace
id|packed
suffix:semicolon
id|packed.parms.xDirection
op_assign
id|direction
suffix:semicolon
id|packed.parms.xLocalAddrType
op_assign
id|localAddressType
suffix:semicolon
id|packed.parms.xRemoteAddrType
op_assign
id|remoteAddressType
suffix:semicolon
id|packed.parms.xRsvd1
op_assign
l_int|0
suffix:semicolon
id|packed.parms.xRemoteLp
op_assign
id|remoteLp
suffix:semicolon
id|packed.parms.xType
op_assign
id|type
suffix:semicolon
id|packed.parms.xRsvd2
op_assign
l_int|0
suffix:semicolon
id|packed.parms.xLocalInstId
op_assign
id|localInstanceId
suffix:semicolon
id|packed.parms.xRemoteInstId
op_assign
id|remoteInstanceId
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpDma_Rc
)paren
id|HvCall4
c_func
(paren
id|HvCallEventDmaBufList
comma
id|packed.dword
comma
id|localBufList
comma
id|remoteBufList
comma
id|transferLength
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvCallEvent_dmaSingle
r_static
r_inline
id|HvLpDma_Rc
id|HvCallEvent_dmaSingle
c_func
(paren
id|HvLpEvent_Type
id|type
comma
id|HvLpIndex
id|remoteLp
comma
id|HvLpDma_Direction
id|direction
comma
id|HvLpInstanceId
id|localInstanceId
comma
id|HvLpInstanceId
id|remoteInstanceId
comma
id|HvLpDma_AddressType
id|localAddressType
comma
id|HvLpDma_AddressType
id|remoteAddressType
comma
id|u64
id|localAddrOrTce
comma
id|u64
id|remoteAddrOrTce
comma
id|u32
id|transferLength
)paren
(brace
id|HvLpDma_Rc
id|retVal
suffix:semicolon
singleline_comment|// Pack the misc bits into a single Dword to pass to PLIC
r_union
(brace
r_struct
id|HvCallEvent_PackedDmaParms
id|parms
suffix:semicolon
id|u64
id|dword
suffix:semicolon
)brace
id|packed
suffix:semicolon
id|packed.parms.xDirection
op_assign
id|direction
suffix:semicolon
id|packed.parms.xLocalAddrType
op_assign
id|localAddressType
suffix:semicolon
id|packed.parms.xRemoteAddrType
op_assign
id|remoteAddressType
suffix:semicolon
id|packed.parms.xRsvd1
op_assign
l_int|0
suffix:semicolon
id|packed.parms.xRemoteLp
op_assign
id|remoteLp
suffix:semicolon
id|packed.parms.xType
op_assign
id|type
suffix:semicolon
id|packed.parms.xRsvd2
op_assign
l_int|0
suffix:semicolon
id|packed.parms.xLocalInstId
op_assign
id|localInstanceId
suffix:semicolon
id|packed.parms.xRemoteInstId
op_assign
id|remoteInstanceId
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpDma_Rc
)paren
id|HvCall4
c_func
(paren
id|HvCallEventDmaSingle
comma
id|packed.dword
comma
id|localAddrOrTce
comma
id|remoteAddrOrTce
comma
id|transferLength
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvCallEvent_dmaToSp
r_static
r_inline
id|HvLpDma_Rc
id|HvCallEvent_dmaToSp
c_func
(paren
r_void
op_star
id|local
comma
id|u32
id|remote
comma
id|u32
id|length
comma
id|HvLpDma_Direction
id|dir
)paren
(brace
id|u64
id|abs_addr
suffix:semicolon
id|HvLpDma_Rc
id|retVal
suffix:semicolon
id|abs_addr
op_assign
id|virt_to_absolute_outline
c_func
(paren
(paren
r_int
r_int
)paren
id|local
)paren
suffix:semicolon
id|retVal
op_assign
(paren
id|HvLpDma_Rc
)paren
id|HvCall4
c_func
(paren
id|HvCallEventDmaToSp
comma
id|abs_addr
comma
id|remote
comma
id|length
comma
id|dir
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//================================================================
macro_line|#endif 
singleline_comment|// _HVCALLEVENT_H
eof
