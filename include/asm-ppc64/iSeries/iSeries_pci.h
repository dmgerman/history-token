macro_line|#ifndef _ISERIES_64_PCI_H
DECL|macro|_ISERIES_64_PCI_H
mdefine_line|#define _ISERIES_64_PCI_H
multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_pci.h created by Allan Trautman on Tue Feb 20, 2001.    */
multiline_comment|/************************************************************************/
multiline_comment|/* Define some useful macros for the iSeries pci routines.              */
multiline_comment|/* Copyright (C) 2001  Allan H Trautman, IBM Corporation                */
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
multiline_comment|/*   Ported to ppc64, May 25, 2001                                      */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* For Forward Reference        */
r_struct
id|iSeries_Device_Node
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Gets iSeries Bus, SubBus, DevFn using iSeries_Device_Node structure */
multiline_comment|/************************************************************************/
DECL|macro|ISERIES_BUS
mdefine_line|#define ISERIES_BUS(DevPtr)&t;DevPtr-&gt;DsaAddr.Dsa.busNumber
DECL|macro|ISERIES_SUBBUS
mdefine_line|#define ISERIES_SUBBUS(DevPtr)&t;DevPtr-&gt;DsaAddr.Dsa.subBusNumber
DECL|macro|ISERIES_DEVICE
mdefine_line|#define ISERIES_DEVICE(DevPtr)&t;DevPtr-&gt;DsaAddr.Dsa.deviceId
DECL|macro|ISERIES_DSA
mdefine_line|#define ISERIES_DSA(DevPtr)&t;DevPtr-&gt;DsaAddr.DsaAddr
DECL|macro|ISERIES_DEVFUN
mdefine_line|#define ISERIES_DEVFUN(DevPtr)&t;DevPtr-&gt;DevFn
DECL|macro|ISERIES_DEVNODE
mdefine_line|#define ISERIES_DEVNODE(PciDev) ((struct iSeries_Device_Node*)PciDev-&gt;sysdata)
DECL|macro|EADsMaxAgents
mdefine_line|#define EADsMaxAgents 7
multiline_comment|/************************************************************************/
multiline_comment|/* Decodes Linux DevFn to iSeries DevFn, bridge device, or function.    */
multiline_comment|/* For Linux, see PCI_SLOT and PCI_FUNC in include/linux/pci.h          */
multiline_comment|/************************************************************************/
DECL|macro|ISERIES_PCI_AGENTID
mdefine_line|#define ISERIES_PCI_AGENTID(idsel,func)&t;((idsel &amp; 0x0F) &lt;&lt; 4) | (func  &amp; 0x07)
DECL|macro|ISERIES_ENCODE_DEVICE
mdefine_line|#define ISERIES_ENCODE_DEVICE(agentid)&t;((0x10) | ((agentid&amp;0x20)&gt;&gt;2) | (agentid&amp;07))
DECL|macro|ISERIES_GET_DEVICE_FROM_SUBBUS
mdefine_line|#define ISERIES_GET_DEVICE_FROM_SUBBUS(subbus)   ((subbus &gt;&gt; 5) &amp; 0x7)
DECL|macro|ISERIES_GET_FUNCTION_FROM_SUBBUS
mdefine_line|#define ISERIES_GET_FUNCTION_FROM_SUBBUS(subbus) ((subbus &gt;&gt; 2) &amp; 0x7)
multiline_comment|/*&n; * N.B. the ISERIES_DECODE_* macros are not used anywhere, and I think&n; * the 0x71 (at least) must be wrong - 0x78 maybe?  -- paulus.&n; */
DECL|macro|ISERIES_DECODE_DEVFN
mdefine_line|#define ISERIES_DECODE_DEVFN(linuxdevfn)  (((linuxdevfn &amp; 0x71) &lt;&lt; 1) | (linuxdevfn &amp; 0x07))
DECL|macro|ISERIES_DECODE_DEVICE
mdefine_line|#define ISERIES_DECODE_DEVICE(linuxdevfn) (((linuxdevfn &amp; 0x38) &gt;&gt; 3) |(((linuxdevfn &amp; 0x40) &gt;&gt; 2) + 0x10))
DECL|macro|ISERIES_DECODE_FUNCTION
mdefine_line|#define ISERIES_DECODE_FUNCTION(linuxdevfn) (linuxdevfn &amp; 0x07)
multiline_comment|/************************************************************************/
multiline_comment|/* Converts Virtual Address to Real Address for Hypervisor calls        */
multiline_comment|/************************************************************************/
DECL|macro|ISERIES_HV_ADDR
mdefine_line|#define ISERIES_HV_ADDR(virtaddr)  (0x8000000000000000 | virt_to_abs(virtaddr))
multiline_comment|/************************************************************************/
multiline_comment|/* iSeries Device Information                                           */
multiline_comment|/************************************************************************/
DECL|struct|iSeries_Device_Node
r_struct
id|iSeries_Device_Node
(brace
DECL|member|Device_List
r_struct
id|list_head
id|Device_List
suffix:semicolon
DECL|member|PciDev
r_struct
id|pci_dev
op_star
id|PciDev
suffix:semicolon
multiline_comment|/* Pointer to pci_dev structure*/
DECL|member|DsaAddr
r_union
id|HvDsaMap
id|DsaAddr
suffix:semicolon
multiline_comment|/* Direct Select Address       */
multiline_comment|/* busNumber,subBusNumber,     */
multiline_comment|/* deviceId, barNumber         */
DECL|member|AgentId
id|HvAgentId
id|AgentId
suffix:semicolon
multiline_comment|/* Hypervisor DevFn            */
DECL|member|DevFn
r_int
id|DevFn
suffix:semicolon
multiline_comment|/* Linux devfn                 */
DECL|member|BarOffset
r_int
id|BarOffset
suffix:semicolon
DECL|member|Irq
r_int
id|Irq
suffix:semicolon
multiline_comment|/* Assigned IRQ                */
DECL|member|ReturnCode
r_int
id|ReturnCode
suffix:semicolon
multiline_comment|/* Return Code Holder          */
DECL|member|IoRetry
r_int
id|IoRetry
suffix:semicolon
multiline_comment|/* Current Retry Count         */
DECL|member|Flags
r_int
id|Flags
suffix:semicolon
multiline_comment|/* Possible flags(disable/bist)*/
DECL|member|Vendor
id|u16
id|Vendor
suffix:semicolon
multiline_comment|/* Vendor ID                   */
DECL|member|LogicalSlot
id|u8
id|LogicalSlot
suffix:semicolon
multiline_comment|/* Hv Slot Index for Tces      */
DECL|member|iommu_table
r_struct
id|iommu_table
op_star
id|iommu_table
suffix:semicolon
multiline_comment|/* Device TCE Table            */
DECL|member|PhbId
id|u8
id|PhbId
suffix:semicolon
multiline_comment|/* Phb Card is on.             */
DECL|member|Board
id|u16
id|Board
suffix:semicolon
multiline_comment|/* Board Number                */
DECL|member|FrameId
id|u8
id|FrameId
suffix:semicolon
multiline_comment|/* iSeries spcn Frame Id       */
DECL|member|CardLocation
r_char
id|CardLocation
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Char format of planar vpd   */
DECL|member|Location
r_char
id|Location
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Frame  1, Card C10          */
)brace
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Functions                                                            */
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
r_extern
r_void
id|iSeries_Get_Location_Code
c_func
(paren
r_struct
id|iSeries_Device_Node
op_star
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
macro_line|#endif /* _ISERIES_64_PCI_H */
eof
