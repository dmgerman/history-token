macro_line|#ifndef _ISERIES_32_PCI_H
DECL|macro|_ISERIES_32_PCI_H
mdefine_line|#define _ISERIES_32_PCI_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_pci.h created by Allan Trautman on Tue Feb 20, 2001.    */
multiline_comment|/************************************************************************/
multiline_comment|/* Define some useful macros for the iSeries pci routines.              */
multiline_comment|/* Copyright (C) 20yy  Allan H Trautman, IBM Corporation                */
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
multiline_comment|/*   Created Feb 20, 2001                                               */
multiline_comment|/*   Added device reset, March 22, 2001                                 */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* For Reference                */
multiline_comment|/************************************************************************/
multiline_comment|/* Gets iSeries Bus, SubBus, of DevFn using pci_dev* structure          */
multiline_comment|/************************************************************************/
DECL|macro|ISERIES_GET_BUS
mdefine_line|#define ISERIES_GET_BUS(DevPtr)    iSeries_Get_Bus(DevPtr)
DECL|macro|ISERIES_GET_SUBBUS
mdefine_line|#define ISERIES_GET_SUBBUS(DevPtr) iSeries_Get_SubBus(DevPtr)
DECL|macro|ISERIES_GET_DEVFUN
mdefine_line|#define ISERIES_GET_DEVFUN(DevPtr) iSeries_Get_DevFn(DevPtr)
multiline_comment|/************************************************************************/
multiline_comment|/* Functions                                                            */
multiline_comment|/************************************************************************/
r_extern
id|u8
id|iSeries_Get_Bus
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_extern
id|u8
id|iSeries_Get_SubBus
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_extern
id|u8
id|iSeries_Get_DevFn
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Global Bus map                                                       */
multiline_comment|/************************************************************************/
r_extern
id|u8
id|iSeries_GlobalBusMap
(braket
l_int|256
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Global iSeries Bus Map */
multiline_comment|/************************************************************************/
multiline_comment|/* iSeries Device Information                                           */
multiline_comment|/************************************************************************/
DECL|struct|iSeries_Device_Struct
r_struct
id|iSeries_Device_Struct
(brace
DECL|member|PciDevPtr
r_struct
id|pci_dev
op_star
id|PciDevPtr
suffix:semicolon
multiline_comment|/* Pointer to pci_dev structure */
DECL|member|BusNumber
id|HvBusNumber
id|BusNumber
suffix:semicolon
multiline_comment|/* Hypervisor Bus Number        */
DECL|member|SubBus
id|HvSubBusNumber
id|SubBus
suffix:semicolon
multiline_comment|/* Hypervisor SubBus Number     */
DECL|member|DevFn
id|HvAgentId
id|DevFn
suffix:semicolon
multiline_comment|/* Hypervisor DevFn             */
DECL|member|BarNumber
id|u8
id|BarNumber
suffix:semicolon
multiline_comment|/* Bar number on Xlates         */
DECL|member|BarOffset
id|u32
id|BarOffset
suffix:semicolon
multiline_comment|/* Offset within Bar on Xlates  */
DECL|member|RCode
r_int
id|RCode
suffix:semicolon
multiline_comment|/* Return Code Holder           */
)brace
suffix:semicolon
DECL|typedef|iSeries_Device
r_typedef
r_struct
id|iSeries_Device_Struct
id|iSeries_Device
suffix:semicolon
r_extern
r_void
id|build_iSeries_Device
c_func
(paren
id|iSeries_Device
op_star
id|Device
comma
r_struct
id|pci_dev
op_star
id|DevPtr
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Formatting device information.                                       */
multiline_comment|/************************************************************************/
r_extern
r_int
id|iSeries_Device_Information
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Flight Recorder tracing                                              */
multiline_comment|/************************************************************************/
r_extern
r_void
id|iSeries_Set_PciFilter
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Set_PciTraceFlag
c_func
(paren
r_int
id|TraceFlag
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Get_PciTraceFlag
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Set_PciErpFlag
c_func
(paren
r_int
id|ErpFlag
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Structure to hold the data for PCI Register Save/Restore functions.  */
multiline_comment|/************************************************************************/
DECL|struct|pci_config_reg_save_area
r_struct
id|pci_config_reg_save_area
(brace
multiline_comment|/*                              */
DECL|member|Flags
id|u16
id|Flags
suffix:semicolon
multiline_comment|/* Control &amp; Info Flags         */
DECL|member|ByteCount
id|u16
id|ByteCount
suffix:semicolon
multiline_comment|/* Number of Register Bytes to S*/
DECL|member|PciDev
r_struct
id|pci_dev
op_star
id|PciDev
suffix:semicolon
multiline_comment|/* Pointer to device            */
DECL|member|RCode
id|u32
id|RCode
suffix:semicolon
multiline_comment|/* Holder for possible errors   */
DECL|member|FailReg
id|u32
id|FailReg
suffix:semicolon
multiline_comment|/* Failing Register on error    */
DECL|member|Regs
id|u8
id|Regs
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Save Area                    */
)brace
suffix:semicolon
DECL|typedef|PciReqsSaveArea
r_typedef
r_struct
id|pci_config_reg_save_area
id|PciReqsSaveArea
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Various flavors of reset device functions.                           */
multiline_comment|/************************************************************************/
multiline_comment|/*                                                                      */
multiline_comment|/* iSeries_Device_Reset_NoIrq                                           */
multiline_comment|/*&t;IRQ is not disabled and default timings are used.               */
multiline_comment|/* iSeries_Device_Reset_Generic                                         */
multiline_comment|/*&t;A generic reset, IRQ is disable and re-enabled.  The assert and */
multiline_comment|/*&t;wait timings will be the pci defaults.                          */
multiline_comment|/* iSeries_Device_Reset                                                 */
multiline_comment|/*&t;A device Reset interface that client can control the timing of  */
multiline_comment|/*&t;the reset and wait delays.                                      */
multiline_comment|/*                                                                      */
multiline_comment|/* Parameters:                                                          */
multiline_comment|/*    pci_dev    = Device to reset.                                     */
multiline_comment|/*    AssertTime = Time in .1 seconds to hold the reset down.  The      */
multiline_comment|/*                 default (and minimum) is .5 seconds.                 */
multiline_comment|/*    DelayTime = Time in .1 seconds to wait for device to come ready   */
multiline_comment|/*                after the reset.  The default is 3 seconds.           */
multiline_comment|/*    IrgDisable = A non-zero will skip irq disable &amp; enable.           */
multiline_comment|/*                                                                      */
multiline_comment|/* Return:                                                              */
multiline_comment|/*    Zero return, reset is successful.                                 */
multiline_comment|/*    Non-zero return code indicates failure.                           */
multiline_comment|/************************************************************************/
r_extern
r_int
id|iSeries_Device_Reset_NoIrq
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Device_Reset_Generic
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Device_Reset
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_int
id|AssertTime
comma
r_int
id|DelayTime
comma
r_int
id|IrqDisable
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Device_ToggleReset
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_int
id|AssertTime
comma
r_int
id|DelayTime
)paren
suffix:semicolon
r_extern
r_int
id|iSeries_Device_RestoreConfigRegs
c_func
(paren
id|PciReqsSaveArea
op_star
id|SaveArea
)paren
suffix:semicolon
r_extern
id|PciReqsSaveArea
op_star
id|iSeries_Device_SaveConfigRegs
c_func
(paren
r_struct
id|pci_dev
op_star
id|DevPtr
)paren
suffix:semicolon
macro_line|#endif /* _ISERIES_32_PCI_H */
eof
