multiline_comment|/*&n; * HvCallCfg.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//=====================================================================================
singleline_comment|//
singleline_comment|//&t;This file contains the &quot;hypervisor call&quot; interface which is used to
singleline_comment|//&t;drive the hypervisor from the OS.
singleline_comment|//
singleline_comment|//=====================================================================================
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef  _HVCALLSC_H
macro_line|#include &quot;HvCallSc.h&quot;
macro_line|#endif
macro_line|#ifndef  _HVTYPES_H
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#endif
singleline_comment|//-------------------------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-------------------------------------------------------------------------------------
macro_line|#ifndef _HVCALLCFG_H
DECL|macro|_HVCALLCFG_H
mdefine_line|#define _HVCALLCFG_H
DECL|enum|HvCallCfg_ReqQual
r_enum
id|HvCallCfg_ReqQual
(brace
DECL|enumerator|HvCallCfg_Cur
id|HvCallCfg_Cur
op_assign
l_int|0
comma
DECL|enumerator|HvCallCfg_Init
id|HvCallCfg_Init
op_assign
l_int|1
comma
DECL|enumerator|HvCallCfg_Max
id|HvCallCfg_Max
op_assign
l_int|2
comma
DECL|enumerator|HvCallCfg_Min
id|HvCallCfg_Min
op_assign
l_int|3
)brace
suffix:semicolon
DECL|macro|HvCallCfgGetLps
mdefine_line|#define HvCallCfgGetLps&t;&t;&t;&t;&t;HvCallCfg +  0
DECL|macro|HvCallCfgGetActiveLpMap
mdefine_line|#define HvCallCfgGetActiveLpMap&t;&t;&t;&t;HvCallCfg +  1
DECL|macro|HvCallCfgGetLpVrmIndex
mdefine_line|#define HvCallCfgGetLpVrmIndex&t;&t;&t;&t;HvCallCfg +  2
DECL|macro|HvCallCfgGetLpMinSupportedPlicVrmIndex
mdefine_line|#define HvCallCfgGetLpMinSupportedPlicVrmIndex&t;&t;HvCallCfg +  3
DECL|macro|HvCallCfgGetLpMinCompatablePlicVrmIndex
mdefine_line|#define HvCallCfgGetLpMinCompatablePlicVrmIndex&t;&t;HvCallCfg +  4
DECL|macro|HvCallCfgGetLpVrmName
mdefine_line|#define HvCallCfgGetLpVrmName&t;&t;&t;&t;HvCallCfg +  5 
DECL|macro|HvCallCfgGetSystemPhysicalProcessors
mdefine_line|#define HvCallCfgGetSystemPhysicalProcessors&t;&t;HvCallCfg +  6
DECL|macro|HvCallCfgGetPhysicalProcessors
mdefine_line|#define HvCallCfgGetPhysicalProcessors&t;&t;&t;HvCallCfg +  7
DECL|macro|HvCallCfgGetSystemMsChunks
mdefine_line|#define HvCallCfgGetSystemMsChunks&t;&t;&t;HvCallCfg +  8
DECL|macro|HvCallCfgGetMsChunks
mdefine_line|#define HvCallCfgGetMsChunks&t;&t;&t;&t;HvCallCfg +  9
DECL|macro|HvCallCfgGetInteractivePercentage
mdefine_line|#define HvCallCfgGetInteractivePercentage&t;&t;HvCallCfg + 10
DECL|macro|HvCallCfgIsBusDedicated
mdefine_line|#define HvCallCfgIsBusDedicated&t;&t;&t;&t;HvCallCfg + 11
DECL|macro|HvCallCfgGetBusOwner
mdefine_line|#define HvCallCfgGetBusOwner&t;&t;&t;&t;HvCallCfg + 12
DECL|macro|HvCallCfgGetBusAllocation
mdefine_line|#define HvCallCfgGetBusAllocation&t;&t;&t;HvCallCfg + 13
DECL|macro|HvCallCfgGetBusUnitOwner
mdefine_line|#define HvCallCfgGetBusUnitOwner&t;&t;&t;HvCallCfg + 14
DECL|macro|HvCallCfgGetBusUnitAllocation
mdefine_line|#define HvCallCfgGetBusUnitAllocation&t;&t;&t;HvCallCfg + 15
DECL|macro|HvCallCfgGetVirtualBusPool
mdefine_line|#define HvCallCfgGetVirtualBusPool&t;&t;&t;HvCallCfg + 16
DECL|macro|HvCallCfgGetBusUnitInterruptProc
mdefine_line|#define HvCallCfgGetBusUnitInterruptProc&t;&t;HvCallCfg + 17
DECL|macro|HvCallCfgGetConfiguredBusUnitsForIntProc
mdefine_line|#define HvCallCfgGetConfiguredBusUnitsForIntProc&t;HvCallCfg + 18
DECL|macro|HvCallCfgGetRioSanBusPool
mdefine_line|#define HvCallCfgGetRioSanBusPool&t;&t;&t;HvCallCfg + 19
DECL|macro|HvCallCfgGetSharedPoolIndex
mdefine_line|#define HvCallCfgGetSharedPoolIndex&t;&t;&t;HvCallCfg + 20
DECL|macro|HvCallCfgGetSharedProcUnits
mdefine_line|#define HvCallCfgGetSharedProcUnits&t;&t;&t;HvCallCfg + 21
DECL|macro|HvCallCfgGetNumProcsInSharedPool
mdefine_line|#define HvCallCfgGetNumProcsInSharedPool&t;&t;HvCallCfg + 22
DECL|macro|HvCallCfgRouter23
mdefine_line|#define HvCallCfgRouter23&t;&t;&t;&t;HvCallCfg + 23
DECL|macro|HvCallCfgRouter24
mdefine_line|#define HvCallCfgRouter24&t;&t;&t;&t;HvCallCfg + 24
DECL|macro|HvCallCfgRouter25
mdefine_line|#define HvCallCfgRouter25&t;&t;&t;&t;HvCallCfg + 25
DECL|macro|HvCallCfgRouter26
mdefine_line|#define HvCallCfgRouter26&t;&t;&t;&t;HvCallCfg + 26
DECL|macro|HvCallCfgRouter27
mdefine_line|#define HvCallCfgRouter27&t;&t;&t;&t;HvCallCfg + 27
DECL|macro|HvCallCfgGetMinRuntimeMsChunks
mdefine_line|#define HvCallCfgGetMinRuntimeMsChunks&t;&t;&t;HvCallCfg + 28
DECL|macro|HvCallCfgSetMinRuntimeMsChunks
mdefine_line|#define HvCallCfgSetMinRuntimeMsChunks&t;&t;&t;HvCallCfg + 29
DECL|macro|HvCallCfgGetVirtualLanIndexMap
mdefine_line|#define HvCallCfgGetVirtualLanIndexMap&t;&t;&t;HvCallCfg + 30
DECL|macro|HvCallCfgGetLpExecutionMode
mdefine_line|#define HvCallCfgGetLpExecutionMode&t;&t;&t;HvCallCfg + 31
DECL|macro|HvCallCfgGetHostingLpIndex
mdefine_line|#define HvCallCfgGetHostingLpIndex &t;&t;&t;HvCallCfg + 32
singleline_comment|//====================================================================
DECL|function|HvCallCfg_getLps
r_static
r_inline
id|HvLpIndex
id|HvCallCfg_getLps
c_func
(paren
r_void
)paren
(brace
id|HvLpIndex
id|retVal
op_assign
id|HvCall0
c_func
(paren
id|HvCallCfgGetLps
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallCfg_isBusDedicated
r_static
r_inline
r_int
id|HvCallCfg_isBusDedicated
c_func
(paren
id|u64
id|busIndex
)paren
(brace
r_int
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgIsBusDedicated
comma
id|busIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallCfg_getBusOwner
r_static
r_inline
id|HvLpIndex
id|HvCallCfg_getBusOwner
c_func
(paren
id|u64
id|busIndex
)paren
(brace
id|HvLpIndex
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetBusOwner
comma
id|busIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallCfg_getBusAllocation
r_static
r_inline
id|HvLpIndexMap
id|HvCallCfg_getBusAllocation
c_func
(paren
id|u64
id|busIndex
)paren
(brace
id|HvLpIndexMap
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetBusAllocation
comma
id|busIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallCfg_getActiveLpMap
r_static
r_inline
id|HvLpIndexMap
id|HvCallCfg_getActiveLpMap
c_func
(paren
r_void
)paren
(brace
id|HvLpIndexMap
id|retVal
op_assign
id|HvCall0
c_func
(paren
id|HvCallCfgGetActiveLpMap
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//====================================================================
DECL|function|HvCallCfg_getVirtualLanIndexMap
r_static
r_inline
id|HvLpVirtualLanIndexMap
id|HvCallCfg_getVirtualLanIndexMap
c_func
(paren
id|HvLpIndex
id|lp
)paren
(brace
singleline_comment|// This is a new function in V5R1 so calls to this on older 
singleline_comment|// hypervisors will return -1
id|u64
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetVirtualLanIndexMap
comma
id|lp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retVal
op_eq
op_minus
l_int|1
)paren
(brace
id|retVal
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_getSystemMsChunks
r_static
r_inline
id|u64
id|HvCallCfg_getSystemMsChunks
c_func
(paren
r_void
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall0
c_func
(paren
id|HvCallCfgGetSystemMsChunks
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_getMsChunks
r_static
r_inline
id|u64
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpIndex
id|lp
comma
r_enum
id|HvCallCfg_ReqQual
id|qual
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallCfgGetMsChunks
comma
id|lp
comma
id|qual
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_getMinRuntimeMsChunks
r_static
r_inline
id|u64
id|HvCallCfg_getMinRuntimeMsChunks
c_func
(paren
id|HvLpIndex
id|lp
)paren
(brace
singleline_comment|// NOTE: This function was added in v5r1 so older hypervisors will return a -1 value
id|u64
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetMinRuntimeMsChunks
comma
id|lp
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_setMinRuntimeMsChunks
r_static
r_inline
id|u64
id|HvCallCfg_setMinRuntimeMsChunks
c_func
(paren
id|u64
id|chunks
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgSetMinRuntimeMsChunks
comma
id|chunks
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_getSystemPhysicalProcessors
r_static
r_inline
id|u64
id|HvCallCfg_getSystemPhysicalProcessors
c_func
(paren
r_void
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall0
c_func
(paren
id|HvCallCfgGetSystemPhysicalProcessors
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_getPhysicalProcessors
r_static
r_inline
id|u64
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpIndex
id|lp
comma
r_enum
id|HvCallCfg_ReqQual
id|qual
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallCfgGetPhysicalProcessors
comma
id|lp
comma
id|qual
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvCallCfg_getConfiguredBusUnitsForInterruptProc
r_static
r_inline
id|u64
id|HvCallCfg_getConfiguredBusUnitsForInterruptProc
c_func
(paren
id|HvLpIndex
id|lp
comma
id|u16
id|hvLogicalProcIndex
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallCfgGetConfiguredBusUnitsForIntProc
comma
id|lp
comma
id|hvLogicalProcIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//==================================================================
DECL|function|HvCallCfg_getSharedPoolIndex
r_static
r_inline
id|HvLpSharedPoolIndex
id|HvCallCfg_getSharedPoolIndex
c_func
(paren
id|HvLpIndex
id|lp
)paren
(brace
id|HvLpSharedPoolIndex
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetSharedPoolIndex
comma
id|lp
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//==================================================================
DECL|function|HvCallCfg_getSharedProcUnits
r_static
r_inline
id|u64
id|HvCallCfg_getSharedProcUnits
c_func
(paren
id|HvLpIndex
id|lp
comma
r_enum
id|HvCallCfg_ReqQual
id|qual
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallCfgGetSharedProcUnits
comma
id|lp
comma
id|qual
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//==================================================================
DECL|function|HvCallCfg_getNumProcsInSharedPool
r_static
r_inline
id|u64
id|HvCallCfg_getNumProcsInSharedPool
c_func
(paren
id|HvLpSharedPoolIndex
id|sPI
)paren
(brace
id|u16
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetNumProcsInSharedPool
comma
id|sPI
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//==================================================================
DECL|function|HvCallCfg_getHostingLpIndex
r_static
r_inline
id|HvLpIndex
id|HvCallCfg_getHostingLpIndex
c_func
(paren
id|HvLpIndex
id|lp
)paren
(brace
id|u64
id|retVal
op_assign
id|HvCall1
c_func
(paren
id|HvCallCfgGetHostingLpIndex
comma
id|lp
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
macro_line|#endif 
singleline_comment|// _HVCALLCFG_H
eof
