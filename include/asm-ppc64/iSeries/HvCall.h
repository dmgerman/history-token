multiline_comment|/*&n; * HvCall.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//===========================================================================
singleline_comment|//
singleline_comment|//&t;This file contains the &quot;hypervisor call&quot; interface which is used to
singleline_comment|//&t;drive the hypervisor from the OS.
singleline_comment|//
singleline_comment|//===========================================================================
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef  _HVCALLSC_H
macro_line|#include &quot;HvCallSc.h&quot;
macro_line|#endif
macro_line|#ifndef  _HVTYPES_H
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/paca.h&gt;
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef _HVCALL_H
DECL|macro|_HVCALL_H
mdefine_line|#define _HVCALL_H
multiline_comment|/*&n;enum HvCall_ReturnCode&n;{&n;&t;HvCall_Good&t;&t;= 0,&n;&t;HvCall_Partial&t;&t;= 1,&n;&t;HvCall_NotOwned&t;&t;= 2,&n;&t;HvCall_NotFreed&t;&t;= 3,&n;&t;HvCall_UnspecifiedError&t;= 4&n;};&n;&n;enum HvCall_TypeOfSIT&n;{&n;&t;HvCall_ReduceOnly&t;= 0,&n;&t;HvCall_Unconditional&t;= 1&n;};&n;&n;enum HvCall_TypeOfYield&n;{&n;&t;HvCall_YieldTimed&t;= 0,&t;// Yield until specified time&n;&t;HvCall_YieldToActive&t;= 1,&t;// Yield until all active procs have run&n;&t;HvCall_YieldToProc&t;= 2&t;// Yield until the specified processor has run&n;};&n;&n;enum HvCall_InterruptMasks&n;{&n;&t;HvCall_MaskIPI&t;&t;= 0x00000001,&n;&t;HvCall_MaskLpEvent&t;= 0x00000002,&n;&t;HvCall_MaskLpProd&t;= 0x00000004,&n;&t;HvCall_MaskTimeout&t;= 0x00000008&n;};&n;&n;enum HvCall_VaryOffChunkRc&n;{&n;&t;HvCall_VaryOffSucceeded&t;&t;= 0,&n;&t;HvCall_VaryOffWithdrawn&t;&t;= 1,&n;&t;HvCall_ChunkInLoadArea&t;&t;= 2,&n;&t;HvCall_ChunkInHPT&t;&t;= 3,&n;&t;HvCall_ChunkNotAccessible&t;= 4,&n;&t;HvCall_ChunkInUse&t;&t;= 5&n;};&n;*/
multiline_comment|/* Type of yield for HvCallBaseYieldProcessor */
DECL|macro|HvCall_YieldTimed
mdefine_line|#define HvCall_YieldTimed &t;0&t;
singleline_comment|// Yield until specified time (tb)
DECL|macro|HvCall_YieldToActive
mdefine_line|#define HvCall_YieldToActive&t;1&t;
singleline_comment|// Yield until all active procs have run
DECL|macro|HvCall_YieldToProc
mdefine_line|#define HvCall_YieldToProc&t;2&t;
singleline_comment|// Yield until the specified processor has run
multiline_comment|/* interrupt masks for setEnabledInterrupts */
DECL|macro|HvCall_MaskIPI
mdefine_line|#define HvCall_MaskIPI&t;&t;0x00000001
DECL|macro|HvCall_MaskLpEvent
mdefine_line|#define HvCall_MaskLpEvent&t;0x00000002
DECL|macro|HvCall_MaskLpProd
mdefine_line|#define HvCall_MaskLpProd&t;0x00000004
DECL|macro|HvCall_MaskTimeout
mdefine_line|#define HvCall_MaskTimeout&t;0x00000008
multiline_comment|/* Log buffer formats                       */
DECL|macro|HvCall_LogBuffer_ASCII
mdefine_line|#define HvCall_LogBuffer_ASCII          0
DECL|macro|HvCall_LogBuffer_EBCDIC
mdefine_line|#define HvCall_LogBuffer_EBCDIC         1
DECL|macro|HvCallBaseAckDeferredInts
mdefine_line|#define HvCallBaseAckDeferredInts&t;&t;&t;HvCallBase +  0
DECL|macro|HvCallBaseCpmPowerOff
mdefine_line|#define HvCallBaseCpmPowerOff&t;&t;&t;&t;HvCallBase +  1
DECL|macro|HvCallBaseGetHwPatch
mdefine_line|#define HvCallBaseGetHwPatch&t;&t;&t;&t;HvCallBase +  2
DECL|macro|HvCallBaseReIplSpAttn
mdefine_line|#define HvCallBaseReIplSpAttn&t;&t;&t;&t;HvCallBase +  3
DECL|macro|HvCallBaseSetASR
mdefine_line|#define HvCallBaseSetASR&t;&t;&t;&t;HvCallBase +  4
DECL|macro|HvCallBaseSetASRAndRfi
mdefine_line|#define HvCallBaseSetASRAndRfi&t;&t;&t;&t;HvCallBase +  5 
DECL|macro|HvCallBaseSetIMR
mdefine_line|#define HvCallBaseSetIMR&t;&t;&t;&t;HvCallBase +  6
DECL|macro|HvCallBaseSendIPI
mdefine_line|#define HvCallBaseSendIPI&t;&t;&t;&t;HvCallBase +  7
DECL|macro|HvCallBaseTerminateMachine
mdefine_line|#define HvCallBaseTerminateMachine&t;&t;&t;HvCallBase +  8
DECL|macro|HvCallBaseTerminateMachineSrc
mdefine_line|#define HvCallBaseTerminateMachineSrc&t;&t;&t;HvCallBase +  9
DECL|macro|HvCallBaseProcessPlicInterrupts
mdefine_line|#define HvCallBaseProcessPlicInterrupts&t;&t;&t;HvCallBase + 10
DECL|macro|HvCallBaseIsPrimaryCpmOrMsdIpl
mdefine_line|#define HvCallBaseIsPrimaryCpmOrMsdIpl&t;&t;&t;HvCallBase + 11
DECL|macro|HvCallBaseSetVirtualSIT
mdefine_line|#define HvCallBaseSetVirtualSIT&t;&t;&t;&t;HvCallBase + 12
DECL|macro|HvCallBaseVaryOffThisProcessor
mdefine_line|#define HvCallBaseVaryOffThisProcessor&t;&t;&t;HvCallBase + 13
DECL|macro|HvCallBaseVaryOffMemoryChunk
mdefine_line|#define HvCallBaseVaryOffMemoryChunk&t;&t;&t;HvCallBase + 14
DECL|macro|HvCallBaseVaryOffInteractivePercentage
mdefine_line|#define HvCallBaseVaryOffInteractivePercentage&t;&t;HvCallBase + 15
DECL|macro|HvCallBaseSendLpProd
mdefine_line|#define HvCallBaseSendLpProd&t;&t;&t;&t;HvCallBase + 16
DECL|macro|HvCallBaseSetEnabledInterrupts
mdefine_line|#define HvCallBaseSetEnabledInterrupts&t;&t;&t;HvCallBase + 17
DECL|macro|HvCallBaseYieldProcessor
mdefine_line|#define HvCallBaseYieldProcessor&t;&t;&t;HvCallBase + 18
DECL|macro|HvCallBaseVaryOffSharedProcUnits
mdefine_line|#define HvCallBaseVaryOffSharedProcUnits&t;&t;HvCallBase + 19
DECL|macro|HvCallBaseSetVirtualDecr
mdefine_line|#define HvCallBaseSetVirtualDecr&t;&t;&t;HvCallBase + 20
DECL|macro|HvCallBaseClearLogBuffer
mdefine_line|#define HvCallBaseClearLogBuffer&t;&t;&t;HvCallBase + 21
DECL|macro|HvCallBaseGetLogBufferCodePage
mdefine_line|#define HvCallBaseGetLogBufferCodePage&t;&t;&t;HvCallBase + 22
DECL|macro|HvCallBaseGetLogBufferFormat
mdefine_line|#define HvCallBaseGetLogBufferFormat&t;&t;&t;HvCallBase + 23
DECL|macro|HvCallBaseGetLogBufferLength
mdefine_line|#define HvCallBaseGetLogBufferLength&t;&t;&t;HvCallBase + 24
DECL|macro|HvCallBaseReadLogBuffer
mdefine_line|#define HvCallBaseReadLogBuffer &t;&t;&t;HvCallBase + 25
DECL|macro|HvCallBaseSetLogBufferFormatAndCodePage
mdefine_line|#define HvCallBaseSetLogBufferFormatAndCodePage&t;&t;HvCallBase + 26
DECL|macro|HvCallBaseWriteLogBuffer
mdefine_line|#define HvCallBaseWriteLogBuffer               &t;&t;HvCallBase + 27
DECL|macro|HvCallBaseRouter28
mdefine_line|#define HvCallBaseRouter28&t;&t;&t;&t;HvCallBase + 28
DECL|macro|HvCallBaseRouter29
mdefine_line|#define HvCallBaseRouter29&t;&t;&t;&t;HvCallBase + 29
DECL|macro|HvCallBaseRouter30
mdefine_line|#define HvCallBaseRouter30&t;&t;&t;&t;HvCallBase + 30
singleline_comment|//=====================================================================================
DECL|function|HvCall_setVirtualDecr
r_static
r_inline
r_void
id|HvCall_setVirtualDecr
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Ignore any error return codes - most likely means that the target value for the&n;&t; * LP has been increased and this vary off would bring us below the new target. */
id|HvCall0
c_func
(paren
id|HvCallBaseSetVirtualDecr
)paren
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_yieldProcessor
r_static
r_inline
r_void
id|HvCall_yieldProcessor
c_func
(paren
r_int
id|typeOfYield
comma
id|u64
id|yieldParm
)paren
(brace
id|HvCall2
c_func
(paren
id|HvCallBaseYieldProcessor
comma
id|typeOfYield
comma
id|yieldParm
)paren
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_setEnabledInterrupts
r_static
r_inline
r_void
id|HvCall_setEnabledInterrupts
c_func
(paren
id|u64
id|enabledInterrupts
)paren
(brace
id|HvCall1
c_func
(paren
id|HvCallBaseSetEnabledInterrupts
comma
id|enabledInterrupts
)paren
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_clearLogBuffer
r_static
r_inline
r_void
id|HvCall_clearLogBuffer
c_func
(paren
id|HvLpIndex
id|lpindex
)paren
(brace
id|HvCall1
c_func
(paren
id|HvCallBaseClearLogBuffer
comma
id|lpindex
)paren
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_getLogBufferCodePage
r_static
r_inline
id|u32
id|HvCall_getLogBufferCodePage
c_func
(paren
id|HvLpIndex
id|lpindex
)paren
(brace
id|u32
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallBaseGetLogBufferCodePage
comma
id|lpindex
)paren
suffix:semicolon
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_getLogBufferFormat
r_static
r_inline
r_int
id|HvCall_getLogBufferFormat
c_func
(paren
id|HvLpIndex
id|lpindex
)paren
(brace
r_int
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallBaseGetLogBufferFormat
comma
id|lpindex
)paren
suffix:semicolon
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_getLogBufferLength
r_static
r_inline
id|u32
id|HvCall_getLogBufferLength
c_func
(paren
id|HvLpIndex
id|lpindex
)paren
(brace
id|u32
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallBaseGetLogBufferLength
comma
id|lpindex
)paren
suffix:semicolon
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_setLogBufferFormatAndCodepage
r_static
r_inline
r_void
id|HvCall_setLogBufferFormatAndCodepage
c_func
(paren
r_int
id|format
comma
id|u32
id|codePage
)paren
(brace
id|HvCall2
c_func
(paren
id|HvCallBaseSetLogBufferFormatAndCodePage
comma
id|format
comma
id|codePage
)paren
suffix:semicolon
)brace
singleline_comment|//=====================================================================
r_int
id|HvCall_readLogBuffer
c_func
(paren
id|HvLpIndex
id|lpindex
comma
r_void
op_star
id|buffer
comma
id|u64
id|bufLen
)paren
suffix:semicolon
r_void
id|HvCall_writeLogBuffer
c_func
(paren
r_const
r_void
op_star
id|buffer
comma
id|u64
id|bufLen
)paren
suffix:semicolon
singleline_comment|//=====================================================================
DECL|function|HvCall_sendIPI
r_static
r_inline
r_void
id|HvCall_sendIPI
c_func
(paren
r_struct
id|paca_struct
op_star
id|targetPaca
)paren
(brace
id|HvCall1
c_func
(paren
id|HvCallBaseSendIPI
comma
id|targetPaca-&gt;xPacaIndex
)paren
suffix:semicolon
)brace
singleline_comment|//=====================================================================
DECL|function|HvCall_terminateMachineSrc
r_static
r_inline
r_void
id|HvCall_terminateMachineSrc
c_func
(paren
r_void
)paren
(brace
id|HvCall0
c_func
(paren
id|HvCallBaseTerminateMachineSrc
)paren
suffix:semicolon
)brace
macro_line|#endif 
singleline_comment|// _HVCALL_H
eof
