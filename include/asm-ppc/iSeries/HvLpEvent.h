multiline_comment|/*&n; * HvLpEvent.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//======================================================================
singleline_comment|//
singleline_comment|//&t;This file contains the class for HV events in the system.
singleline_comment|//
singleline_comment|//=====================================================================
macro_line|#ifndef _HVLPEVENT_H
DECL|macro|_HVLPEVENT_H
mdefine_line|#define _HVLPEVENT_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#ifndef _HVCALLEVENT_H
macro_line|#include &lt;asm/iSeries/HvCallEvent.h&gt;
macro_line|#endif
singleline_comment|//=====================================================================
singleline_comment|//
singleline_comment|// HvLpEvent is the structure for Lp Event messages passed between
singleline_comment|// partitions through PLIC. 
singleline_comment|//
singleline_comment|//=====================================================================
DECL|struct|HvEventFlags
r_struct
id|HvEventFlags
(brace
DECL|member|xValid
id|u8
id|xValid
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Indicates a valid request&t;x00-x00
DECL|member|xRsvd1
id|u8
id|xRsvd1
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;...
DECL|member|xAckType
id|u8
id|xAckType
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Immediate or deferred&t;...
DECL|member|xAckInd
id|u8
id|xAckInd
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Indicates if ACK required&t;...
DECL|member|xFunction
id|u8
id|xFunction
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Interrupt or Acknowledge&t;...
)brace
suffix:semicolon
DECL|struct|HvLpEvent
r_struct
id|HvLpEvent
(brace
DECL|member|xFlags
r_struct
id|HvEventFlags
id|xFlags
suffix:semicolon
singleline_comment|// Event flags&t;&t;&t;x00-x00
DECL|member|xType
id|u8
id|xType
suffix:semicolon
singleline_comment|// Type of message&t;&t;x01-x01
DECL|member|xSubtype
id|u16
id|xSubtype
suffix:semicolon
singleline_comment|// Subtype for event&t;&t;x02-x03
DECL|member|xSourceLp
id|u8
id|xSourceLp
suffix:semicolon
singleline_comment|// Source LP&t;&t;&t;x04-x04
DECL|member|xTargetLp
id|u8
id|xTargetLp
suffix:semicolon
singleline_comment|// Target LP&t;&t;&t;x05-x05
DECL|member|xSizeMinus1
id|u8
id|xSizeMinus1
suffix:semicolon
singleline_comment|// Size of Derived class - 1&t;x06-x06
DECL|member|xRc
id|u8
id|xRc
suffix:semicolon
singleline_comment|// RC for Ack flows&t;&t;x07-x07
DECL|member|xSourceInstanceId
id|u16
id|xSourceInstanceId
suffix:semicolon
singleline_comment|// Source sides instance id&t;x08-x09
DECL|member|xTargetInstanceId
id|u16
id|xTargetInstanceId
suffix:semicolon
singleline_comment|// Target sides instance id&t;x0A-x0B
r_union
(brace
DECL|member|xSubtypeData
id|u32
id|xSubtypeData
suffix:semicolon
singleline_comment|// Data usable by the subtype&t;x0C-x0F
DECL|member|xSubtypeDataShort
id|u16
id|xSubtypeDataShort
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|// Data as 2 shorts
DECL|member|xSubtypeDataChar
id|u8
id|xSubtypeDataChar
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// Data as 4 chars
DECL|member|x
)brace
id|x
suffix:semicolon
DECL|member|xCorrelationToken
id|u64
id|xCorrelationToken
suffix:semicolon
singleline_comment|// Unique value for source/type x10-x17
)brace
suffix:semicolon
singleline_comment|// Lp Event handler function
DECL|typedef|LpEventHandler
r_typedef
r_void
(paren
op_star
id|LpEventHandler
)paren
(paren
r_struct
id|HvLpEvent
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
singleline_comment|// Register a handler for an event type
singleline_comment|//  returns 0 on success
r_extern
r_int
id|HvLpEvent_registerHandler
c_func
(paren
id|HvLpEvent_Type
id|eventType
comma
id|LpEventHandler
id|hdlr
)paren
suffix:semicolon
singleline_comment|// Unregister a handler for an event type
singleline_comment|//  returns 0 on success
singleline_comment|//  Unregister will fail if there are any paths open for the type
r_extern
r_int
id|HvLpEvent_unregisterHandler
c_func
(paren
id|HvLpEvent_Type
id|eventType
)paren
suffix:semicolon
singleline_comment|// Open an Lp Event Path for an event type
singleline_comment|//  returns 0 on success
singleline_comment|//  openPath will fail if there is no handler registered for the event type.
singleline_comment|//  The lpIndex specified is the partition index for the target partition
singleline_comment|//  (for VirtualIo, VirtualLan and SessionMgr) other types specify zero) 
r_extern
r_int
id|HvLpEvent_openPath
c_func
(paren
id|HvLpEvent_Type
id|eventType
comma
id|HvLpIndex
id|lpIndex
)paren
suffix:semicolon
singleline_comment|// Close an Lp Event Path for a type and partition
singleline_comment|//  returns 0 on sucess
r_extern
r_int
id|HvLpEvent_closePath
c_func
(paren
id|HvLpEvent_Type
id|eventType
comma
id|HvLpIndex
id|lpIndex
)paren
suffix:semicolon
DECL|macro|HvLpEvent_Type_Hypervisor
mdefine_line|#define HvLpEvent_Type_Hypervisor 0
DECL|macro|HvLpEvent_Type_MachineFac
mdefine_line|#define HvLpEvent_Type_MachineFac 1
DECL|macro|HvLpEvent_Type_SessionMgr
mdefine_line|#define HvLpEvent_Type_SessionMgr 2
DECL|macro|HvLpEvent_Type_SpdIo
mdefine_line|#define HvLpEvent_Type_SpdIo      3
DECL|macro|HvLpEvent_Type_VirtualBus
mdefine_line|#define HvLpEvent_Type_VirtualBus 4
DECL|macro|HvLpEvent_Type_PciIo
mdefine_line|#define HvLpEvent_Type_PciIo      5
DECL|macro|HvLpEvent_Type_RioIo
mdefine_line|#define HvLpEvent_Type_RioIo      6
DECL|macro|HvLpEvent_Type_VirtualLan
mdefine_line|#define HvLpEvent_Type_VirtualLan 7
DECL|macro|HvLpEvent_Type_VirtualIo
mdefine_line|#define HvLpEvent_Type_VirtualIo  8
DECL|macro|HvLpEvent_Type_NumTypes
mdefine_line|#define HvLpEvent_Type_NumTypes   9
DECL|macro|HvLpEvent_Rc_Good
mdefine_line|#define HvLpEvent_Rc_Good 0
DECL|macro|HvLpEvent_Rc_BufferNotAvailable
mdefine_line|#define HvLpEvent_Rc_BufferNotAvailable 1
DECL|macro|HvLpEvent_Rc_Cancelled
mdefine_line|#define HvLpEvent_Rc_Cancelled 2
DECL|macro|HvLpEvent_Rc_GenericError
mdefine_line|#define HvLpEvent_Rc_GenericError 3
DECL|macro|HvLpEvent_Rc_InvalidAddress
mdefine_line|#define HvLpEvent_Rc_InvalidAddress 4
DECL|macro|HvLpEvent_Rc_InvalidPartition
mdefine_line|#define HvLpEvent_Rc_InvalidPartition 5
DECL|macro|HvLpEvent_Rc_InvalidSize
mdefine_line|#define HvLpEvent_Rc_InvalidSize 6
DECL|macro|HvLpEvent_Rc_InvalidSubtype
mdefine_line|#define HvLpEvent_Rc_InvalidSubtype 7
DECL|macro|HvLpEvent_Rc_InvalidSubtypeData
mdefine_line|#define HvLpEvent_Rc_InvalidSubtypeData 8
DECL|macro|HvLpEvent_Rc_InvalidType
mdefine_line|#define HvLpEvent_Rc_InvalidType 9
DECL|macro|HvLpEvent_Rc_PartitionDead
mdefine_line|#define HvLpEvent_Rc_PartitionDead 10
DECL|macro|HvLpEvent_Rc_PathClosed
mdefine_line|#define HvLpEvent_Rc_PathClosed 11
DECL|macro|HvLpEvent_Rc_SubtypeError
mdefine_line|#define HvLpEvent_Rc_SubtypeError 12
DECL|macro|HvLpEvent_Function_Ack
mdefine_line|#define HvLpEvent_Function_Ack 0
DECL|macro|HvLpEvent_Function_Int
mdefine_line|#define HvLpEvent_Function_Int 1
DECL|macro|HvLpEvent_AckInd_NoAck
mdefine_line|#define HvLpEvent_AckInd_NoAck 0
DECL|macro|HvLpEvent_AckInd_DoAck
mdefine_line|#define HvLpEvent_AckInd_DoAck 1
DECL|macro|HvLpEvent_AckType_ImmediateAck
mdefine_line|#define HvLpEvent_AckType_ImmediateAck 0
DECL|macro|HvLpEvent_AckType_DeferredAck
mdefine_line|#define HvLpEvent_AckType_DeferredAck 1
DECL|macro|HvLpDma_Direction_LocalToRemote
mdefine_line|#define HvLpDma_Direction_LocalToRemote 0
DECL|macro|HvLpDma_Direction_RemoteToLocal
mdefine_line|#define HvLpDma_Direction_RemoteToLocal 1
DECL|macro|HvLpDma_AddressType_TceIndex
mdefine_line|#define HvLpDma_AddressType_TceIndex 0
DECL|macro|HvLpDma_AddressType_RealAddress
mdefine_line|#define HvLpDma_AddressType_RealAddress 1
DECL|macro|HvLpDma_Rc_Good
mdefine_line|#define HvLpDma_Rc_Good 0
DECL|macro|HvLpDma_Rc_Error
mdefine_line|#define HvLpDma_Rc_Error 1
DECL|macro|HvLpDma_Rc_PartitionDead
mdefine_line|#define HvLpDma_Rc_PartitionDead 2
DECL|macro|HvLpDma_Rc_PathClosed
mdefine_line|#define HvLpDma_Rc_PathClosed 3
DECL|macro|HvLpDma_Rc_InvalidAddress
mdefine_line|#define HvLpDma_Rc_InvalidAddress 4
DECL|macro|HvLpDma_Rc_InvalidLength
mdefine_line|#define HvLpDma_Rc_InvalidLength 5
macro_line|#endif 
singleline_comment|// _HVLPEVENT_H
eof
