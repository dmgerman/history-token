multiline_comment|/************************************************************************/
multiline_comment|/* Provides the Hypervisor PCI calls for iSeries Linux Parition.        */
multiline_comment|/* Copyright (C) 20yy  &lt;Wayne G Holm&gt; &lt;IBM Corporation&gt;                 */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is free software; you can redistribute it and/or modify */
multiline_comment|/* it under the terms of the GNU General Public License as published by */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or    */
multiline_comment|/* (at your option) any later version.                                  */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is distributed in the hope that it will be useful,      */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
multiline_comment|/* GNU General Public License for more details.                         */
multiline_comment|/*                                                                      */
multiline_comment|/* You should have received a copy of the GNU General Public License    */
multiline_comment|/* along with this program; if not, write to the:                       */
multiline_comment|/* Free Software Foundation, Inc.,                                      */
multiline_comment|/* 59 Temple Place, Suite 330,                                          */
multiline_comment|/* Boston, MA  02111-1307  USA                                          */
multiline_comment|/************************************************************************/
multiline_comment|/* Change Activity:                                                     */
multiline_comment|/*   Created, Jan 9, 2001                                               */
multiline_comment|/************************************************************************/
singleline_comment|//============================================================================
singleline_comment|//&t;&t;&t;&t;&t;&t;&t; Header File Id
singleline_comment|// Name______________:&t;HvCallPci.H
singleline_comment|//
singleline_comment|// Description_______:
singleline_comment|//
singleline_comment|//&t;This file contains the &quot;hypervisor call&quot; interface which is used to
singleline_comment|//&t;drive the hypervisor from SLIC.
singleline_comment|//
singleline_comment|//============================================================================
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Forward declarations 
singleline_comment|//-------------------------------------------------------------------
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef  _HVCALLSC_H
macro_line|#include &quot;HvCallSc.h&quot;
macro_line|#endif
macro_line|#ifndef  _HVTYPES_H
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#endif
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Other Includes
singleline_comment|//-------------------------------------------------------------------
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-----------------------------------------------------------------------------
macro_line|#ifndef _HVCALLPCI_H
DECL|macro|_HVCALLPCI_H
mdefine_line|#define _HVCALLPCI_H
DECL|struct|HvCallPci_DsaAddr
r_struct
id|HvCallPci_DsaAddr
(brace
singleline_comment|// make sure this struct size is 64-bits total
DECL|member|busNumber
id|u16
id|busNumber
suffix:semicolon
DECL|member|subBusNumber
id|u8
id|subBusNumber
suffix:semicolon
DECL|member|deviceId
id|u8
id|deviceId
suffix:semicolon
DECL|member|barNumber
id|u8
id|barNumber
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|union|HvDsaMap
r_union
id|HvDsaMap
(brace
DECL|member|DsaAddr
id|u64
id|DsaAddr
suffix:semicolon
DECL|member|Dsa
r_struct
id|HvCallPci_DsaAddr
id|Dsa
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|HvCallPci_LoadReturn
r_struct
id|HvCallPci_LoadReturn
(brace
DECL|member|rc
id|u64
id|rc
suffix:semicolon
DECL|member|value
id|u64
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|HvCallPci_DeviceType
DECL|enumerator|HvCallPci_NodeDevice
r_enum
id|HvCallPci_DeviceType
(brace
id|HvCallPci_NodeDevice
op_assign
l_int|1
comma
DECL|enumerator|HvCallPci_SpDevice
id|HvCallPci_SpDevice
op_assign
l_int|2
comma
DECL|enumerator|HvCallPci_IopDevice
id|HvCallPci_IopDevice
op_assign
l_int|3
comma
DECL|enumerator|HvCallPci_BridgeDevice
id|HvCallPci_BridgeDevice
op_assign
l_int|4
comma
DECL|enumerator|HvCallPci_MultiFunctionDevice
id|HvCallPci_MultiFunctionDevice
op_assign
l_int|5
comma
DECL|enumerator|HvCallPci_IoaDevice
id|HvCallPci_IoaDevice
op_assign
l_int|6
)brace
suffix:semicolon
DECL|struct|HvCallPci_DeviceInfo
r_struct
id|HvCallPci_DeviceInfo
(brace
DECL|member|deviceType
id|u32
id|deviceType
suffix:semicolon
singleline_comment|// See DeviceType enum for values
)brace
suffix:semicolon
DECL|struct|HvCallPci_BusUnitInfo
r_struct
id|HvCallPci_BusUnitInfo
(brace
DECL|member|sizeReturned
id|u32
id|sizeReturned
suffix:semicolon
singleline_comment|// length of data returned
DECL|member|deviceType
id|u32
id|deviceType
suffix:semicolon
singleline_comment|// see DeviceType enum for values
)brace
suffix:semicolon
DECL|struct|HvCallPci_BridgeInfo
r_struct
id|HvCallPci_BridgeInfo
(brace
DECL|member|busUnitInfo
r_struct
id|HvCallPci_BusUnitInfo
id|busUnitInfo
suffix:semicolon
singleline_comment|// Generic bus unit info
DECL|member|subBusNumber
id|u8
id|subBusNumber
suffix:semicolon
singleline_comment|// Bus number of secondary bus
DECL|member|maxAgents
id|u8
id|maxAgents
suffix:semicolon
singleline_comment|// Max idsels on secondary bus
)brace
suffix:semicolon
singleline_comment|//  Maximum BusUnitInfo buffer size.  Provided for clients so they can allocate
singleline_comment|//  a buffer big enough for any type of bus unit.  Increase as needed.
DECL|enumerator|HvCallPci_MaxBusUnitInfoSize
r_enum
(brace
id|HvCallPci_MaxBusUnitInfoSize
op_assign
l_int|128
)brace
suffix:semicolon
DECL|struct|HvCallPci_BarParms
r_struct
id|HvCallPci_BarParms
(brace
DECL|member|vaddr
id|u64
id|vaddr
suffix:semicolon
DECL|member|raddr
id|u64
id|raddr
suffix:semicolon
DECL|member|size
id|u64
id|size
suffix:semicolon
DECL|member|protectStart
id|u64
id|protectStart
suffix:semicolon
DECL|member|protectEnd
id|u64
id|protectEnd
suffix:semicolon
DECL|member|relocationOffset
id|u64
id|relocationOffset
suffix:semicolon
DECL|member|pciAddress
id|u64
id|pciAddress
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|HvCallPci_VpdType
r_enum
id|HvCallPci_VpdType
(brace
DECL|enumerator|HvCallPci_BusVpd
id|HvCallPci_BusVpd
op_assign
l_int|1
comma
DECL|enumerator|HvCallPci_BusAdapterVpd
id|HvCallPci_BusAdapterVpd
op_assign
l_int|2
)brace
suffix:semicolon
DECL|macro|HvCallPciConfigLoad8
mdefine_line|#define HvCallPciConfigLoad8&t;&t;HvCallPci + 0
DECL|macro|HvCallPciConfigLoad16
mdefine_line|#define HvCallPciConfigLoad16&t;&t;HvCallPci + 1
DECL|macro|HvCallPciConfigLoad32
mdefine_line|#define HvCallPciConfigLoad32&t;&t;HvCallPci + 2
DECL|macro|HvCallPciConfigStore8
mdefine_line|#define HvCallPciConfigStore8&t;&t;HvCallPci + 3
DECL|macro|HvCallPciConfigStore16
mdefine_line|#define HvCallPciConfigStore16&t;&t;HvCallPci + 4
DECL|macro|HvCallPciConfigStore32
mdefine_line|#define HvCallPciConfigStore32&t;&t;HvCallPci + 5
DECL|macro|HvCallPciEoi
mdefine_line|#define HvCallPciEoi&t;&t;&t;HvCallPci + 16
DECL|macro|HvCallPciGetBarParms
mdefine_line|#define HvCallPciGetBarParms&t;&t;HvCallPci + 18
DECL|macro|HvCallPciMaskFisr
mdefine_line|#define HvCallPciMaskFisr&t;&t;HvCallPci + 20
DECL|macro|HvCallPciUnmaskFisr
mdefine_line|#define HvCallPciUnmaskFisr&t;&t;HvCallPci + 21
DECL|macro|HvCallPciSetSlotReset
mdefine_line|#define HvCallPciSetSlotReset&t;&t;HvCallPci + 25
DECL|macro|HvCallPciGetDeviceInfo
mdefine_line|#define HvCallPciGetDeviceInfo&t;&t;HvCallPci + 27
DECL|macro|HvCallPciGetCardVpd
mdefine_line|#define HvCallPciGetCardVpd&t;&t;HvCallPci + 28
DECL|macro|HvCallPciBarLoad8
mdefine_line|#define HvCallPciBarLoad8&t;&t;HvCallPci + 40
DECL|macro|HvCallPciBarLoad16
mdefine_line|#define HvCallPciBarLoad16&t;&t;HvCallPci + 41
DECL|macro|HvCallPciBarLoad32
mdefine_line|#define HvCallPciBarLoad32&t;&t;HvCallPci + 42
DECL|macro|HvCallPciBarLoad64
mdefine_line|#define HvCallPciBarLoad64&t;&t;HvCallPci + 43
DECL|macro|HvCallPciBarStore8
mdefine_line|#define HvCallPciBarStore8&t;&t;HvCallPci + 44
DECL|macro|HvCallPciBarStore16
mdefine_line|#define HvCallPciBarStore16&t;&t;HvCallPci + 45
DECL|macro|HvCallPciBarStore32
mdefine_line|#define HvCallPciBarStore32&t;&t;HvCallPci + 46
DECL|macro|HvCallPciBarStore64
mdefine_line|#define HvCallPciBarStore64&t;&t;HvCallPci + 47
DECL|macro|HvCallPciMaskInterrupts
mdefine_line|#define HvCallPciMaskInterrupts&t;&t;HvCallPci + 48
DECL|macro|HvCallPciUnmaskInterrupts
mdefine_line|#define HvCallPciUnmaskInterrupts&t;HvCallPci + 49
DECL|macro|HvCallPciGetBusUnitInfo
mdefine_line|#define HvCallPciGetBusUnitInfo&t;&t;HvCallPci + 50
singleline_comment|//============================================================================
DECL|function|HvCallPci_configLoad8
r_static
r_inline
id|u64
id|HvCallPci_configLoad8
c_func
(paren
id|u16
id|busNumber
comma
id|u8
id|subBusNumber
comma
id|u8
id|deviceId
comma
id|u32
id|offset
comma
id|u8
op_star
id|value
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumber
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusNumber
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceId
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciConfigLoad8
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offset
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|value
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_configLoad16
r_static
r_inline
id|u64
id|HvCallPci_configLoad16
c_func
(paren
id|u16
id|busNumber
comma
id|u8
id|subBusNumber
comma
id|u8
id|deviceId
comma
id|u32
id|offset
comma
id|u16
op_star
id|value
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumber
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusNumber
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceId
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciConfigLoad16
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offset
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|value
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_configLoad32
r_static
r_inline
id|u64
id|HvCallPci_configLoad32
c_func
(paren
id|u16
id|busNumber
comma
id|u8
id|subBusNumber
comma
id|u8
id|deviceId
comma
id|u32
id|offset
comma
id|u32
op_star
id|value
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumber
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusNumber
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceId
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciConfigLoad32
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offset
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|value
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_configStore8
r_static
r_inline
id|u64
id|HvCallPci_configStore8
c_func
(paren
id|u16
id|busNumber
comma
id|u8
id|subBusNumber
comma
id|u8
id|deviceId
comma
id|u32
id|offset
comma
id|u8
id|value
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumber
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusNumber
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceId
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciConfigStore8
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offset
comma
id|value
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_configStore16
r_static
r_inline
id|u64
id|HvCallPci_configStore16
c_func
(paren
id|u16
id|busNumber
comma
id|u8
id|subBusNumber
comma
id|u8
id|deviceId
comma
id|u32
id|offset
comma
id|u16
id|value
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumber
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusNumber
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceId
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciConfigStore16
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offset
comma
id|value
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_configStore32
r_static
r_inline
id|u64
id|HvCallPci_configStore32
c_func
(paren
id|u16
id|busNumber
comma
id|u8
id|subBusNumber
comma
id|u8
id|deviceId
comma
id|u32
id|offset
comma
id|u32
id|value
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumber
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusNumber
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceId
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciConfigStore32
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offset
comma
id|value
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barLoad8
r_static
r_inline
id|u64
id|HvCallPci_barLoad8
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u8
op_star
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciBarLoad8
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|valueParm
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barLoad16
r_static
r_inline
id|u64
id|HvCallPci_barLoad16
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u16
op_star
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciBarLoad16
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|valueParm
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barLoad32
r_static
r_inline
id|u64
id|HvCallPci_barLoad32
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u32
op_star
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciBarLoad32
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|valueParm
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barLoad64
r_static
r_inline
id|u64
id|HvCallPci_barLoad64
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u64
op_star
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|HvCall3Ret16
c_func
(paren
id|HvCallPciBarLoad64
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
op_star
id|valueParm
op_assign
id|retVal.value
suffix:semicolon
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barStore8
r_static
r_inline
id|u64
id|HvCallPci_barStore8
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u8
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciBarStore8
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
id|valueParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barStore16
r_static
r_inline
id|u64
id|HvCallPci_barStore16
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u16
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciBarStore16
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
id|valueParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barStore32
r_static
r_inline
id|u64
id|HvCallPci_barStore32
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u32
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciBarStore32
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
id|valueParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_barStore64
r_static
r_inline
id|u64
id|HvCallPci_barStore64
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|offsetParm
comma
id|u64
id|valueParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|retVal
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciBarStore64
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|offsetParm
comma
id|valueParm
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_eoi
r_static
r_inline
id|u64
id|HvCallPci_eoi
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
r_struct
id|HvCallPci_LoadReturn
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|HvCall1Ret16
c_func
(paren
id|HvCallPciEoi
comma
op_amp
id|retVal
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal.rc
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_getBarParms
r_static
r_inline
id|u64
id|HvCallPci_getBarParms
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u8
id|barNumberParm
comma
id|u64
id|parms
comma
id|u32
id|sizeofParms
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|dsa.barNumber
op_assign
id|barNumberParm
suffix:semicolon
id|retVal
op_assign
id|HvCall3
c_func
(paren
id|HvCallPciGetBarParms
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|parms
comma
id|sizeofParms
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_maskFisr
r_static
r_inline
id|u64
id|HvCallPci_maskFisr
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u64
id|fisrMask
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallPciMaskFisr
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|fisrMask
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_unmaskFisr
r_static
r_inline
id|u64
id|HvCallPci_unmaskFisr
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u64
id|fisrMask
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallPciUnmaskFisr
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|fisrMask
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_setSlotReset
r_static
r_inline
id|u64
id|HvCallPci_setSlotReset
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u64
id|onNotOff
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallPciSetSlotReset
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|onNotOff
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_getDeviceInfo
r_static
r_inline
id|u64
id|HvCallPci_getDeviceInfo
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceNumberParm
comma
id|u64
id|parms
comma
id|u32
id|sizeofParms
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceNumberParm
op_lshift
l_int|4
suffix:semicolon
id|retVal
op_assign
id|HvCall3
c_func
(paren
id|HvCallPciGetDeviceInfo
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|parms
comma
id|sizeofParms
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_maskInterrupts
r_static
r_inline
id|u64
id|HvCallPci_maskInterrupts
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u64
id|interruptMask
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallPciMaskInterrupts
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|interruptMask
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_unmaskInterrupts
r_static
r_inline
id|u64
id|HvCallPci_unmaskInterrupts
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u64
id|interruptMask
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|retVal
op_assign
id|HvCall2
c_func
(paren
id|HvCallPciUnmaskInterrupts
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|interruptMask
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_getBusUnitInfo
r_static
r_inline
id|u64
id|HvCallPci_getBusUnitInfo
c_func
(paren
id|u16
id|busNumberParm
comma
id|u8
id|subBusParm
comma
id|u8
id|deviceIdParm
comma
id|u64
id|parms
comma
id|u32
id|sizeofParms
)paren
(brace
r_struct
id|HvCallPci_DsaAddr
id|dsa
suffix:semicolon
id|u64
id|retVal
suffix:semicolon
op_star
(paren
(paren
id|u64
op_star
)paren
op_amp
id|dsa
)paren
op_assign
l_int|0
suffix:semicolon
id|dsa.busNumber
op_assign
id|busNumberParm
suffix:semicolon
id|dsa.subBusNumber
op_assign
id|subBusParm
suffix:semicolon
id|dsa.deviceId
op_assign
id|deviceIdParm
suffix:semicolon
id|retVal
op_assign
id|HvCall3
c_func
(paren
id|HvCallPciGetBusUnitInfo
comma
op_star
(paren
id|u64
op_star
)paren
op_amp
id|dsa
comma
id|parms
comma
id|sizeofParms
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retVal
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_getBusVpd
r_static
r_inline
r_int
id|HvCallPci_getBusVpd
c_func
(paren
id|u16
id|busNumParm
comma
id|u64
id|destParm
comma
id|u16
id|sizeParm
)paren
(brace
r_int
id|xRetSize
suffix:semicolon
id|u64
id|xRc
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciGetCardVpd
comma
id|busNumParm
comma
id|destParm
comma
id|sizeParm
comma
id|HvCallPci_BusVpd
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_if
c_cond
(paren
id|xRc
op_eq
op_minus
l_int|1
)paren
id|xRetSize
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|xRetSize
op_assign
id|xRc
op_amp
l_int|0xFFFF
suffix:semicolon
r_return
id|xRetSize
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallPci_getBusAdapterVpd
r_static
r_inline
r_int
id|HvCallPci_getBusAdapterVpd
c_func
(paren
id|u16
id|busNumParm
comma
id|u64
id|destParm
comma
id|u16
id|sizeParm
)paren
(brace
r_int
id|xRetSize
suffix:semicolon
id|u64
id|xRc
op_assign
id|HvCall4
c_func
(paren
id|HvCallPciGetCardVpd
comma
id|busNumParm
comma
id|destParm
comma
id|sizeParm
comma
id|HvCallPci_BusAdapterVpd
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_if
c_cond
(paren
id|xRc
op_eq
op_minus
l_int|1
)paren
id|xRetSize
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|xRetSize
op_assign
id|xRc
op_amp
l_int|0xFFFF
suffix:semicolon
r_return
id|xRetSize
suffix:semicolon
)brace
singleline_comment|//============================================================================
macro_line|#endif 
singleline_comment|// _HVCALLPCI_H
eof
