multiline_comment|/*&n; * HvLpConfig.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//===========================================================================
singleline_comment|//
singleline_comment|//      This file contains the interface to the LPAR configuration data
singleline_comment|//  to determine which resources should be allocated to each partition.
singleline_comment|//
singleline_comment|//===========================================================================
macro_line|#ifndef  _HVCALLCFG_H
macro_line|#include &quot;HvCallCfg.h&quot;
macro_line|#endif
macro_line|#ifndef  _HVTYPES_H
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#endif
macro_line|#ifndef  _ITLPNACA_H
macro_line|#include &lt;asm/iSeries/ItLpNaca.h&gt;
macro_line|#endif
macro_line|#ifndef  _LPARDATA_H
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#endif
macro_line|#ifndef _HVLPCONFIG_H
DECL|macro|_HVLPCONFIG_H
mdefine_line|#define _HVLPCONFIG_H
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-------------------------------------------------------------------
r_extern
id|HvLpIndex
id|HvLpConfig_getLpIndex_outline
c_func
(paren
r_void
)paren
suffix:semicolon
singleline_comment|//===================================================================
DECL|function|HvLpConfig_getLpIndex
r_static
r_inline
id|HvLpIndex
id|HvLpConfig_getLpIndex
c_func
(paren
r_void
)paren
(brace
r_return
id|itLpNaca.xLpIndex
suffix:semicolon
)brace
singleline_comment|//===================================================================
DECL|function|HvLpConfig_getPrimaryLpIndex
r_static
r_inline
id|HvLpIndex
id|HvLpConfig_getPrimaryLpIndex
c_func
(paren
r_void
)paren
(brace
r_return
id|itLpNaca.xPrimaryLpIndex
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvLpConfig_getLps
r_static
r_inline
id|HvLpIndex
id|HvLpConfig_getLps
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getLps
c_func
(paren
)paren
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvLpConfig_getActiveLpMap
r_static
r_inline
id|HvLpIndexMap
id|HvLpConfig_getActiveLpMap
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getActiveLpMap
c_func
(paren
)paren
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvLpConfig_getSystemMsMegs
r_static
r_inline
id|u64
id|HvLpConfig_getSystemMsMegs
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSystemMsChunks
c_func
(paren
)paren
op_div
id|HVCHUNKSPERMEG
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvLpConfig_getSystemMsChunks
r_static
r_inline
id|u64
id|HvLpConfig_getSystemMsChunks
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSystemMsChunks
c_func
(paren
)paren
suffix:semicolon
)brace
singleline_comment|//=================================================================
DECL|function|HvLpConfig_getSystemMsPages
r_static
r_inline
id|u64
id|HvLpConfig_getSystemMsPages
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSystemMsChunks
c_func
(paren
)paren
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMsMegs
r_static
r_inline
id|u64
id|HvLpConfig_getMsMegs
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Cur
)paren
op_div
id|HVCHUNKSPERMEG
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMsChunks
r_static
r_inline
id|u64
id|HvLpConfig_getMsChunks
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Cur
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMsPages
r_static
r_inline
id|u64
id|HvLpConfig_getMsPages
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Cur
)paren
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMinMsMegs
r_static
r_inline
id|u64
id|HvLpConfig_getMinMsMegs
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Min
)paren
op_div
id|HVCHUNKSPERMEG
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMinMsChunks
r_static
r_inline
id|u64
id|HvLpConfig_getMinMsChunks
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Min
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMinMsPages
r_static
r_inline
id|u64
id|HvLpConfig_getMinMsPages
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Min
)paren
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getMinRuntimeMsMegs
r_static
r_inline
id|u64
id|HvLpConfig_getMinRuntimeMsMegs
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMinRuntimeMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
)paren
op_div
id|HVCHUNKSPERMEG
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMinRuntimeMsChunks
r_static
r_inline
id|u64
id|HvLpConfig_getMinRuntimeMsChunks
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMinRuntimeMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMinRuntimeMsPages
r_static
r_inline
id|u64
id|HvLpConfig_getMinRuntimeMsPages
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMinRuntimeMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
)paren
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMaxMsMegs
r_static
r_inline
id|u64
id|HvLpConfig_getMaxMsMegs
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Max
)paren
op_div
id|HVCHUNKSPERMEG
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMaxMsChunks
r_static
r_inline
id|u64
id|HvLpConfig_getMaxMsChunks
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Max
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMaxMsPages
r_static
r_inline
id|u64
id|HvLpConfig_getMaxMsPages
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Max
)paren
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getInitMsMegs
r_static
r_inline
id|u64
id|HvLpConfig_getInitMsMegs
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Init
)paren
op_div
id|HVCHUNKSPERMEG
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getInitMsChunks
r_static
r_inline
id|u64
id|HvLpConfig_getInitMsChunks
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Init
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getInitMsPages
r_static
r_inline
id|u64
id|HvLpConfig_getInitMsPages
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getMsChunks
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Init
)paren
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getSystemPhysicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getSystemPhysicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSystemPhysicalProcessors
c_func
(paren
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getSystemLogicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getSystemLogicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSystemPhysicalProcessors
c_func
(paren
)paren
op_star
(paren
multiline_comment|/*getPaca()-&gt;getSecondaryThreadCount() +*/
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getNumProcsInSharedPool
r_static
r_inline
id|u64
id|HvLpConfig_getNumProcsInSharedPool
c_func
(paren
id|HvLpSharedPoolIndex
id|sPI
)paren
(brace
r_return
id|HvCallCfg_getNumProcsInSharedPool
c_func
(paren
id|sPI
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getPhysicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getPhysicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Cur
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getLogicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getLogicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Cur
)paren
op_star
(paren
multiline_comment|/*getPaca()-&gt;getSecondaryThreadCount() +*/
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getSharedPoolIndex
r_static
r_inline
id|HvLpSharedPoolIndex
id|HvLpConfig_getSharedPoolIndex
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSharedPoolIndex
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getSharedProcUnits
r_static
r_inline
id|u64
id|HvLpConfig_getSharedProcUnits
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSharedProcUnits
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Cur
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMinSharedProcUnits
r_static
r_inline
id|u64
id|HvLpConfig_getMinSharedProcUnits
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSharedProcUnits
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Min
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMaxSharedProcUnits
r_static
r_inline
id|u64
id|HvLpConfig_getMaxSharedProcUnits
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getSharedProcUnits
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Max
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMinPhysicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getMinPhysicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Min
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMinLogicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getMinLogicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Min
)paren
op_star
(paren
multiline_comment|/*getPaca()-&gt;getSecondaryThreadCount() +*/
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMaxPhysicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getMaxPhysicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Max
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getMaxLogicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getMaxLogicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Max
)paren
op_star
(paren
multiline_comment|/*getPaca()-&gt;getSecondaryThreadCount() +*/
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getInitPhysicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getInitPhysicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Init
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getInitLogicalProcessors
r_static
r_inline
id|u64
id|HvLpConfig_getInitLogicalProcessors
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getPhysicalProcessors
c_func
(paren
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
comma
id|HvCallCfg_Init
)paren
op_star
(paren
multiline_comment|/*getPaca()-&gt;getSecondaryThreadCount() +*/
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getVirtualLanIndexMap
r_static
r_inline
id|HvLpVirtualLanIndexMap
id|HvLpConfig_getVirtualLanIndexMap
c_func
(paren
r_void
)paren
(brace
r_return
id|HvCallCfg_getVirtualLanIndexMap
c_func
(paren
id|HvLpConfig_getLpIndex_outline
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_getVirtualLanIndexMapForLp
r_static
r_inline
id|HvLpVirtualLanIndexMap
id|HvLpConfig_getVirtualLanIndexMapForLp
c_func
(paren
id|HvLpIndex
id|lp
)paren
(brace
r_return
id|HvCallCfg_getVirtualLanIndexMap
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getBusOwner
r_static
r_inline
id|HvLpIndex
id|HvLpConfig_getBusOwner
c_func
(paren
id|HvBusNumber
id|busNumber
)paren
(brace
r_return
id|HvCallCfg_getBusOwner
c_func
(paren
id|busNumber
)paren
suffix:semicolon
)brace
singleline_comment|//===============================================================
DECL|function|HvLpConfig_isBusDedicated
r_static
r_inline
r_int
id|HvLpConfig_isBusDedicated
c_func
(paren
id|HvBusNumber
id|busNumber
)paren
(brace
r_return
id|HvCallCfg_isBusDedicated
c_func
(paren
id|busNumber
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getBusAllocation
r_static
r_inline
id|HvLpIndexMap
id|HvLpConfig_getBusAllocation
c_func
(paren
id|HvBusNumber
id|busNumber
)paren
(brace
r_return
id|HvCallCfg_getBusAllocation
c_func
(paren
id|busNumber
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
singleline_comment|// returns the absolute real address of the load area
DECL|function|HvLpConfig_getLoadAddress
r_static
r_inline
id|u64
id|HvLpConfig_getLoadAddress
c_func
(paren
r_void
)paren
(brace
r_return
id|itLpNaca.xLoadAreaAddr
op_amp
l_int|0x7fffffffffffffff
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getLoadPages
r_static
r_inline
id|u64
id|HvLpConfig_getLoadPages
c_func
(paren
r_void
)paren
(brace
r_return
id|itLpNaca.xLoadAreaChunks
op_star
id|HVPAGESPERCHUNK
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_isBusOwnedByThisLp
r_static
r_inline
r_int
id|HvLpConfig_isBusOwnedByThisLp
c_func
(paren
id|HvBusNumber
id|busNumber
)paren
(brace
id|HvLpIndex
id|busOwner
op_assign
id|HvLpConfig_getBusOwner
c_func
(paren
id|busNumber
)paren
suffix:semicolon
r_return
(paren
id|busOwner
op_eq
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_doLpsCommunicateOnVirtualLan
r_static
r_inline
r_int
id|HvLpConfig_doLpsCommunicateOnVirtualLan
c_func
(paren
id|HvLpIndex
id|lp1
comma
id|HvLpIndex
id|lp2
)paren
(brace
id|HvLpVirtualLanIndexMap
id|virtualLanIndexMap1
op_assign
id|HvCallCfg_getVirtualLanIndexMap
c_func
(paren
id|lp1
)paren
suffix:semicolon
id|HvLpVirtualLanIndexMap
id|virtualLanIndexMap2
op_assign
id|HvCallCfg_getVirtualLanIndexMap
c_func
(paren
id|lp2
)paren
suffix:semicolon
r_return
(paren
(paren
id|virtualLanIndexMap1
op_amp
id|virtualLanIndexMap2
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
DECL|function|HvLpConfig_getHostingLpIndex
r_static
r_inline
id|HvLpIndex
id|HvLpConfig_getHostingLpIndex
c_func
(paren
id|HvLpIndex
id|lp
)paren
(brace
r_return
id|HvCallCfg_getHostingLpIndex
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
singleline_comment|//================================================================
macro_line|#endif 
singleline_comment|// _HVLPCONFIG_H
eof
