macro_line|#ifdef CONFIG_PPC_ISERIES 
macro_line|#ifndef _ISERIES_PCI_H
DECL|macro|_ISERIES_PCI_H
mdefine_line|#define _ISERIES_PCI_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_pci.h created by Allan Trautman on Tue Jan  9 2001.     */
multiline_comment|/************************************************************************/
multiline_comment|/* Define some useful macros for the iseries pci routines.              */
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
multiline_comment|/*   Created December 28, 2000                                          */
multiline_comment|/*   Converted to iseries_pci.h Jan 25, 2001                            */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_FlightRecorder.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
multiline_comment|/************************************************************************************/
multiline_comment|/* Define some useful macros.                                                       */
multiline_comment|/* These macros started with Wayne, Al renamed and refined.                         */
multiline_comment|/************************************************************************************/
multiline_comment|/* Encodes SubBus address(seddddfff), Works only for bridges under EADS 1 and 2.    */
multiline_comment|/************************************************************************************/
multiline_comment|/* #define ISERIES_ENCODE_SUBBUS(eads, bridge, device) &bslash;&n;             (0x80 | ((eads-1 &amp; 0x01) &lt;&lt; 6) | ((bridge &amp; 0x0F) &lt;&lt; 3) | (device &amp; 0x07)) */
DECL|macro|ISERIES_ENCODE_SUBBUS
mdefine_line|#define ISERIES_ENCODE_SUBBUS(e, ef, df) (((0x80 | ((e&amp;0x02)&lt;&lt;5) | ((ef &amp; 0x07)&lt;&lt;3)) &amp; 0xF8) | (df &amp; 0x03))  
singleline_comment|// Al - Please Review
multiline_comment|/************************************************************************************/
multiline_comment|/* Combines IdSel and Function into Iseries 4.4 format                              */
multiline_comment|/* For Linux, see PCI_DEVFN(slot,func) in include/linux/pci.h                       */
multiline_comment|/************************************************************************************/
singleline_comment|// #define ISERIES_PCI_AGENTID(idsel,func)&t;((idsel &amp; 0x0F) &lt;&lt; 4) | (func  &amp; 0x07)
DECL|macro|ISERIES_PCI_AGENTID
mdefine_line|#define ISERIES_PCI_AGENTID(idsel,func)&t;(((idsel &amp; 0x0F) &lt;&lt; 4) | (func &amp; 0x0F))  
singleline_comment|// Al - Please Review
multiline_comment|/************************************************************************************/
multiline_comment|/* Converts DeviceFunction from Linux   5.3(dddddfff) to Iseries 4.4(dddd0fff)      */
multiline_comment|/* Converts DeviceFunction from Iseries 4.4(dddd0fff) to Linux   5.3(dddddfff)      */
multiline_comment|/************************************************************************************/
DECL|macro|ISERIES_44_FORMAT
mdefine_line|#define ISERIES_44_FORMAT(devfn53)          (((devfn53 &amp; 0xF8) &lt;&lt; 1) | (devfn53 &amp; 0x07))
DECL|macro|ISERIES_53_FORMAT
mdefine_line|#define ISERIES_53_FORMAT(devfn44)          (((devfn44 &amp; 0xF0) &gt;&gt; 1) | (devfn44 &amp; 0x07))
multiline_comment|/************************************************************************************/
multiline_comment|/* Tests for encoded subbus.                                                        */
multiline_comment|/************************************************************************************/
DECL|macro|ISERIES_IS_SUBBUS_ENCODED_IN_DEVFN
mdefine_line|#define ISERIES_IS_SUBBUS_ENCODED_IN_DEVFN(devfn)   ((devfn &amp; 0x80) == 0x80)
multiline_comment|/************************************************************************************/
multiline_comment|/* Decodes the Iseries subbus to devfn, ONLY Works for bus 0!! Use Table lookup.    */
multiline_comment|/************************************************************************************/
multiline_comment|/* #define ISERIES_DEVFN_DECODE_SUBBUS(devfn) &bslash;&n;                             ((((devfn &amp; 0x40) &gt;&gt; 1) + 0x20)  | ((devfn &gt;&gt; 1) &amp; 0x1C)) */
DECL|macro|ISERIES_DEVFN_DECODE_SUBBUS
mdefine_line|#define ISERIES_DEVFN_DECODE_SUBBUS(devfn) (((((devfn &gt;&gt; 6 ) &amp; 0x1) + 1) &lt;&lt; 5) | (((devfn &gt;&gt; 3) &amp; 0x7) &lt;&lt; 2))  
singleline_comment|// Al - Please Review
multiline_comment|/************************************************************************************/
multiline_comment|/* Decodes Linux DevFn to Iseries DevFn, bridge device, or function.                */
multiline_comment|/* For Linux, see PCI_SLOT and PCI_FUNC in include/linux/pci.h                      */
multiline_comment|/************************************************************************************/
DECL|macro|ISERIES_DECODE_DEVFN
mdefine_line|#define ISERIES_DECODE_DEVFN(linuxdevfn)  (((linuxdevfn &amp; 0x71) &lt;&lt; 1) | (linuxdevfn &amp; 0x07))
DECL|macro|ISERIES_DECODE_DEVICE
mdefine_line|#define ISERIES_DECODE_DEVICE(linuxdevfn) (((linuxdevfn &amp; 0x38) &gt;&gt; 3) |(((linuxdevfn &amp; 0x40) &gt;&gt; 2) + 0x10))
DECL|macro|ISERIES_DECODE_FUNCTION
mdefine_line|#define ISERIES_DECODE_FUNCTION(linuxdevfn) (linuxdevfn &amp; 0x07)
DECL|macro|ISERIES_GET_DEVICE_FROM_SUBBUS
mdefine_line|#define ISERIES_GET_DEVICE_FROM_SUBBUS(subbus) ((subbus &gt;&gt; 5) &amp; 0x7)
DECL|macro|ISERIES_GET_FUNCTION_FROM_SUBBUS
mdefine_line|#define ISERIES_GET_FUNCTION_FROM_SUBBUS(subbus) ((subbus &gt;&gt; 2) &amp; 0x7)
DECL|macro|ISERIES_GET_HOSE_HV_BUSNUM
mdefine_line|#define ISERIES_GET_HOSE_HV_BUSNUM(hose) (((struct iSeries_hose_arch_data *)(hose-&gt;arch_data))-&gt;hvBusNumber)
multiline_comment|/************************************************************************************/
multiline_comment|/* Retreives Iseries Bus and SubBus from GlobalBusMap                               */
multiline_comment|/************************************************************************************/
DECL|macro|ISERIES_GET_LPAR_BUS
mdefine_line|#define ISERIES_GET_LPAR_BUS(linux_bus)    iSeries_GlobalBusMap[linux_bus][_HVBUSNUMBER_]
DECL|macro|ISERIES_GET_LPAR_SUBBUS
mdefine_line|#define ISERIES_GET_LPAR_SUBBUS(linux_bus) iSeries_GlobalBusMap[linux_bus][_HVSUBBUSNUMBER_]
DECL|macro|ISERIES_ADD_BUS_GLOBALBUSMAP
mdefine_line|#define ISERIES_ADD_BUS_GLOBALBUSMAP(linuxbus, iseriesbus, iseriessubbus) &bslash;&n;    iSeries_GlobalBusMap[linuxbus][_HVBUSNUMBER_]    = iseriesbus;      &bslash;&n;    iSeries_GlobalBusMap[linuxbus][_HVSUBBUSNUMBER_] = iseriessubbus;       
multiline_comment|/************************************************************************************/
multiline_comment|/* Global Bus map                                                                   */
multiline_comment|/* Bus and Subbus index values into the global bus number map array.                */
multiline_comment|/************************************************************************************/
DECL|macro|ISERIES_GLOBALBUSMAP_SIZE
mdefine_line|#define ISERIES_GLOBALBUSMAP_SIZE 256
DECL|macro|_HVBUSNUMBER_
mdefine_line|#define _HVBUSNUMBER_    0
DECL|macro|_HVSUBBUSNUMBER_
mdefine_line|#define _HVSUBBUSNUMBER_ 1
r_extern
id|u8
id|iSeries_GlobalBusMap
(braket
id|ISERIES_GLOBALBUSMAP_SIZE
)braket
(braket
l_int|2
)braket
suffix:semicolon
r_void
id|iSeries_Initialize_GlobalBusMap
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|pci_assign_all_buses
mdefine_line|#define pci_assign_all_buses() 1  
singleline_comment|// Al - NEW
multiline_comment|/************************************************************************************/
multiline_comment|/* Converts Virtual Address to Real Address for Hypervisor calls                    */
multiline_comment|/************************************************************************************/
DECL|macro|REALADDR
mdefine_line|#define REALADDR(virtaddr)  (0x8000000000000000 | (virt_to_absolute((u32)virtaddr) ))
multiline_comment|/************************************************************************************/
multiline_comment|/* Define TRUE and FALSE Values for Al                                              */
multiline_comment|/************************************************************************************/
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|typedef|pciDev
r_typedef
r_struct
id|pci_dev
id|pciDev
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Routines to build the iSeries_Device for the pci device.             */
multiline_comment|/************************************************************************/
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
r_extern
r_int
id|build_iSeries_Device_From_IoAddress
c_func
(paren
id|iSeries_Device
op_star
id|Device
comma
id|u32
op_star
id|IoAddress
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_pci_Initialize
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Flight Recorder Debug Support                                        */
multiline_comment|/************************************************************************/
r_extern
r_int
id|PciTraceFlag
suffix:semicolon
multiline_comment|/* Conditional Trace    */
r_void
id|iSeries_Initialize_FlightRecorder
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|iSeries_Set_PciTraceFlag
c_func
(paren
r_int
id|Flag
)paren
suffix:semicolon
multiline_comment|/* Sets flag, return old*/
r_int
id|iSeries_Get_PciTraceFlag
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Gets Flag.           */
r_void
id|iSeries_DumpDevice
c_func
(paren
r_char
op_star
id|Text
comma
id|iSeries_Device
op_star
)paren
suffix:semicolon
macro_line|#endif  /* _ISERIES_PCI_H */
macro_line|#endif  /*CONFIG_PPC_ISERIES  */
eof
