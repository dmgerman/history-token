macro_line|#ifndef __IBMPHP_H
DECL|macro|__IBMPHP_H
mdefine_line|#define __IBMPHP_H
multiline_comment|/*&n; * IBM Hot Plug Controller Driver&n; *&n; * Written By: Jyoti Shah, Tong Yu, Irene Zubarev, IBM Corporation&n; *&n; * Copyright (c) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (c) 2001,2002 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;gregkh@us.ibm.com&gt;&n; *&n; */
macro_line|#include &quot;pci_hotplug.h&quot;
r_extern
r_int
id|ibmphp_debug
suffix:semicolon
macro_line|#if !defined(CONFIG_HOTPLUG_PCI_IBM_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;ibmphpd&quot;
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME THIS_MODULE-&gt;name
macro_line|#endif
DECL|macro|debug
mdefine_line|#define debug(fmt, arg...) do { if (ibmphp_debug) printk(KERN_DEBUG &quot;%s: &quot; fmt , MY_NAME , ## arg); } while (0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format , MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format , MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format , MY_NAME , ## arg)
multiline_comment|/* EBDA stuff */
multiline_comment|/***********************************************************&n;* SLOT CAPABILITY                                          *&n;***********************************************************/
DECL|macro|EBDA_SLOT_133_MAX
mdefine_line|#define EBDA_SLOT_133_MAX&t;&t;0x20
DECL|macro|EBDA_SLOT_100_MAX
mdefine_line|#define EBDA_SLOT_100_MAX&t;&t;0x10
DECL|macro|EBDA_SLOT_66_MAX
mdefine_line|#define EBDA_SLOT_66_MAX&t;&t;0x02
DECL|macro|EBDA_SLOT_PCIX_CAP
mdefine_line|#define EBDA_SLOT_PCIX_CAP&t;&t;0x08
multiline_comment|/************************************************************&n;*  RESOURE TYPE                                             *&n;************************************************************/
DECL|macro|EBDA_RSRC_TYPE_MASK
mdefine_line|#define EBDA_RSRC_TYPE_MASK&t;&t;0x03
DECL|macro|EBDA_IO_RSRC_TYPE
mdefine_line|#define EBDA_IO_RSRC_TYPE&t;&t;0x00
DECL|macro|EBDA_MEM_RSRC_TYPE
mdefine_line|#define EBDA_MEM_RSRC_TYPE&t;&t;0x01
DECL|macro|EBDA_PFM_RSRC_TYPE
mdefine_line|#define EBDA_PFM_RSRC_TYPE&t;&t;0x03
DECL|macro|EBDA_RES_RSRC_TYPE
mdefine_line|#define EBDA_RES_RSRC_TYPE&t;&t;0x02
multiline_comment|/*************************************************************&n;*  IO RESTRICTION TYPE                                       *&n;*************************************************************/
DECL|macro|EBDA_IO_RESTRI_MASK
mdefine_line|#define EBDA_IO_RESTRI_MASK&t;&t;0x0c
DECL|macro|EBDA_NO_RESTRI
mdefine_line|#define EBDA_NO_RESTRI&t;&t;&t;0x00
DECL|macro|EBDA_AVO_VGA_ADDR
mdefine_line|#define EBDA_AVO_VGA_ADDR&t;&t;0x04
DECL|macro|EBDA_AVO_VGA_ADDR_AND_ALIA
mdefine_line|#define EBDA_AVO_VGA_ADDR_AND_ALIA&t;0x08
DECL|macro|EBDA_AVO_ISA_ADDR
mdefine_line|#define EBDA_AVO_ISA_ADDR&t;&t;0x0c
multiline_comment|/**************************************************************&n;*  DEVICE TYPE DEF                                            *&n;**************************************************************/
DECL|macro|EBDA_DEV_TYPE_MASK
mdefine_line|#define EBDA_DEV_TYPE_MASK&t;&t;0x10
DECL|macro|EBDA_PCI_DEV
mdefine_line|#define EBDA_PCI_DEV&t;&t;&t;0x10
DECL|macro|EBDA_NON_PCI_DEV
mdefine_line|#define EBDA_NON_PCI_DEV&t;&t;0x00
multiline_comment|/***************************************************************&n;*  PRIMARY DEF DEFINITION                                      *&n;***************************************************************/
DECL|macro|EBDA_PRI_DEF_MASK
mdefine_line|#define EBDA_PRI_DEF_MASK&t;&t;0x20
DECL|macro|EBDA_PRI_PCI_BUS_INFO
mdefine_line|#define EBDA_PRI_PCI_BUS_INFO&t;&t;0x20
DECL|macro|EBDA_NORM_DEV_RSRC_INFO
mdefine_line|#define EBDA_NORM_DEV_RSRC_INFO&t;&t;0x00
singleline_comment|//--------------------------------------------------------------
singleline_comment|// RIO TABLE DATA STRUCTURE
singleline_comment|//--------------------------------------------------------------
DECL|struct|rio_table_hdr
r_struct
id|rio_table_hdr
(brace
DECL|member|ver_num
id|u8
id|ver_num
suffix:semicolon
DECL|member|scal_count
id|u8
id|scal_count
suffix:semicolon
DECL|member|riodev_count
id|u8
id|riodev_count
suffix:semicolon
DECL|member|offset
id|u16
id|offset
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|//-------------------------------------------------------------
singleline_comment|// SCALABILITY DETAIL
singleline_comment|//-------------------------------------------------------------
DECL|struct|scal_detail
r_struct
id|scal_detail
(brace
DECL|member|node_id
id|u8
id|node_id
suffix:semicolon
DECL|member|cbar
id|u32
id|cbar
suffix:semicolon
DECL|member|port0_node_connect
id|u8
id|port0_node_connect
suffix:semicolon
DECL|member|port0_port_connect
id|u8
id|port0_port_connect
suffix:semicolon
DECL|member|port1_node_connect
id|u8
id|port1_node_connect
suffix:semicolon
DECL|member|port1_port_connect
id|u8
id|port1_port_connect
suffix:semicolon
DECL|member|port2_node_connect
id|u8
id|port2_node_connect
suffix:semicolon
DECL|member|port2_port_connect
id|u8
id|port2_port_connect
suffix:semicolon
singleline_comment|//&t;struct list_head scal_detail_list;
)brace
suffix:semicolon
singleline_comment|//--------------------------------------------------------------
singleline_comment|// RIO DETAIL 
singleline_comment|//--------------------------------------------------------------
DECL|struct|rio_detail
r_struct
id|rio_detail
(brace
DECL|member|rio_node_id
id|u8
id|rio_node_id
suffix:semicolon
DECL|member|bbar
id|u32
id|bbar
suffix:semicolon
DECL|member|rio_type
id|u8
id|rio_type
suffix:semicolon
DECL|member|owner_id
id|u8
id|owner_id
suffix:semicolon
DECL|member|port0_node_connect
id|u8
id|port0_node_connect
suffix:semicolon
DECL|member|port0_port_connect
id|u8
id|port0_port_connect
suffix:semicolon
DECL|member|port1_node_connect
id|u8
id|port1_node_connect
suffix:semicolon
DECL|member|port1_port_connect
id|u8
id|port1_port_connect
suffix:semicolon
DECL|member|first_slot_num
id|u8
id|first_slot_num
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
singleline_comment|//&t;struct list_head rio_detail_list;
)brace
suffix:semicolon
multiline_comment|/****************************************************************&n;*  HPC DESCRIPTOR NODE                                          *&n;****************************************************************/
DECL|struct|ebda_hpc_list
r_struct
id|ebda_hpc_list
(brace
DECL|member|format
id|u8
id|format
suffix:semicolon
DECL|member|num_ctlrs
id|u16
id|num_ctlrs
suffix:semicolon
DECL|member|phys_addr
r_int
id|phys_addr
suffix:semicolon
singleline_comment|//      struct list_head ebda_hpc_list;
)brace
suffix:semicolon
multiline_comment|/*****************************************************************&n;*   IN HPC DATA STRUCTURE, THE ASSOCIATED SLOT AND BUS           *&n;*   STRUCTURE                                                    *&n;*****************************************************************/
DECL|struct|ebda_hpc_slot
r_struct
id|ebda_hpc_slot
(brace
DECL|member|slot_num
id|u8
id|slot_num
suffix:semicolon
DECL|member|slot_bus_num
id|u32
id|slot_bus_num
suffix:semicolon
DECL|member|ctl_index
id|u8
id|ctl_index
suffix:semicolon
DECL|member|slot_cap
id|u8
id|slot_cap
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebda_hpc_bus
r_struct
id|ebda_hpc_bus
(brace
DECL|member|bus_num
id|u32
id|bus_num
suffix:semicolon
DECL|member|slots_at_33_conv
id|u8
id|slots_at_33_conv
suffix:semicolon
DECL|member|slots_at_66_conv
id|u8
id|slots_at_66_conv
suffix:semicolon
DECL|member|slots_at_66_pcix
id|u8
id|slots_at_66_pcix
suffix:semicolon
DECL|member|slots_at_100_pcix
id|u8
id|slots_at_100_pcix
suffix:semicolon
DECL|member|slots_at_133_pcix
id|u8
id|slots_at_133_pcix
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/********************************************************************&n;*   THREE TYPE OF HOT PLUG CONTROLER                                *&n;********************************************************************/
DECL|struct|isa_ctlr_access
r_struct
id|isa_ctlr_access
(brace
DECL|member|io_start
id|u16
id|io_start
suffix:semicolon
DECL|member|io_end
id|u16
id|io_end
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_ctlr_access
r_struct
id|pci_ctlr_access
(brace
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|dev_fun
id|u8
id|dev_fun
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wpeg_i2c_ctlr_access
r_struct
id|wpeg_i2c_ctlr_access
(brace
DECL|member|wpegbbar
id|ulong
id|wpegbbar
suffix:semicolon
DECL|member|i2c_addr
id|u8
id|i2c_addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*************************************************************************&n;*   RSTC DESCRIPTOR NODE                                                 *&n;*************************************************************************/
DECL|struct|ebda_rsrc_list
r_struct
id|ebda_rsrc_list
(brace
DECL|member|format
id|u8
id|format
suffix:semicolon
DECL|member|num_entries
id|u16
id|num_entries
suffix:semicolon
DECL|member|phys_addr
id|u16
id|phys_addr
suffix:semicolon
DECL|member|next
r_struct
id|ebda_rsrc_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/***************************************************************************&n;*   PCI RSRC NODE                                                          *&n;***************************************************************************/
DECL|struct|ebda_pci_rsrc
r_struct
id|ebda_pci_rsrc
(brace
DECL|member|rsrc_type
id|u8
id|rsrc_type
suffix:semicolon
DECL|member|bus_num
id|u8
id|bus_num
suffix:semicolon
DECL|member|dev_fun
id|u8
id|dev_fun
suffix:semicolon
DECL|member|start_addr
id|ulong
id|start_addr
suffix:semicolon
DECL|member|end_addr
id|ulong
id|end_addr
suffix:semicolon
DECL|member|ebda_pci_rsrc_list
r_struct
id|list_head
id|ebda_pci_rsrc_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/***********************************************************&n;* BUS_INFO DATE STRUCTURE                                  *&n;***********************************************************/
DECL|struct|bus_info
r_struct
id|bus_info
(brace
DECL|member|slot_min
id|u8
id|slot_min
suffix:semicolon
DECL|member|slot_max
id|u8
id|slot_max
suffix:semicolon
DECL|member|slot_count
id|u8
id|slot_count
suffix:semicolon
DECL|member|busno
id|u8
id|busno
suffix:semicolon
DECL|member|controller_id
id|u8
id|controller_id
suffix:semicolon
DECL|member|current_speed
id|u8
id|current_speed
suffix:semicolon
DECL|member|current_bus_mode
id|u8
id|current_bus_mode
suffix:semicolon
DECL|member|index
id|u8
id|index
suffix:semicolon
DECL|member|slots_at_33_conv
id|u8
id|slots_at_33_conv
suffix:semicolon
DECL|member|slots_at_66_conv
id|u8
id|slots_at_66_conv
suffix:semicolon
DECL|member|slots_at_66_pcix
id|u8
id|slots_at_66_pcix
suffix:semicolon
DECL|member|slots_at_100_pcix
id|u8
id|slots_at_100_pcix
suffix:semicolon
DECL|member|slots_at_133_pcix
id|u8
id|slots_at_133_pcix
suffix:semicolon
DECL|member|bus_info_list
r_struct
id|list_head
id|bus_info_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/***********************************************************&n;* GLOBAL VARIABLES                                         *&n;***********************************************************/
r_extern
r_struct
id|list_head
id|ibmphp_ebda_pci_rsrc_head
suffix:semicolon
r_extern
r_struct
id|list_head
id|ibmphp_slot_head
suffix:semicolon
multiline_comment|/***********************************************************&n;* FUNCTION PROTOTYPES                                      *&n;***********************************************************/
r_extern
r_void
id|ibmphp_free_ebda_hpc_queue
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_access_ebda
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|slot
op_star
id|ibmphp_get_slot_from_physical_num
(paren
id|u8
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_get_total_hp_slots
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_free_ibm_slot
(paren
r_struct
id|slot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_free_bus_info_queue
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_free_ebda_pci_rsrc_queue
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|bus_info
op_star
id|ibmphp_find_same_bus_num
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_get_bus_index
(paren
id|u8
)paren
suffix:semicolon
r_extern
id|u16
id|ibmphp_get_total_controllers
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* passed parameters */
DECL|macro|MEM
mdefine_line|#define MEM&t;&t;0
DECL|macro|IO
mdefine_line|#define IO&t;&t;1
DECL|macro|PFMEM
mdefine_line|#define PFMEM&t;&t;2
multiline_comment|/* bit masks */
DECL|macro|RESTYPE
mdefine_line|#define RESTYPE&t;&t;0x03
DECL|macro|IOMASK
mdefine_line|#define IOMASK&t;&t;0x00&t;/* will need to take its complement */
DECL|macro|MMASK
mdefine_line|#define MMASK&t;&t;0x01
DECL|macro|PFMASK
mdefine_line|#define PFMASK&t;&t;0x03
DECL|macro|PCIDEVMASK
mdefine_line|#define PCIDEVMASK&t;0x10&t;/* we should always have PCI devices */
DECL|macro|PRIMARYBUSMASK
mdefine_line|#define PRIMARYBUSMASK&t;0x20
multiline_comment|/* pci specific defines */
DECL|macro|PCI_VENDOR_ID_NOTVALID
mdefine_line|#define PCI_VENDOR_ID_NOTVALID&t;&t;0xFFFF
DECL|macro|PCI_HEADER_TYPE_MULTIDEVICE
mdefine_line|#define PCI_HEADER_TYPE_MULTIDEVICE&t;0x80
DECL|macro|PCI_HEADER_TYPE_MULTIBRIDGE
mdefine_line|#define PCI_HEADER_TYPE_MULTIBRIDGE&t;0x81
DECL|macro|LATENCY
mdefine_line|#define LATENCY&t;&t;0x64
DECL|macro|CACHE
mdefine_line|#define CACHE&t;&t;64
DECL|macro|DEVICEENABLE
mdefine_line|#define DEVICEENABLE&t;0x015F&t;&t;/* CPQ has 0x0157 */
DECL|macro|IOBRIDGE
mdefine_line|#define IOBRIDGE&t;0x1000&t;&t;/* 4k */
DECL|macro|MEMBRIDGE
mdefine_line|#define MEMBRIDGE&t;0x100000&t;/* 1M */
multiline_comment|/* irqs */
DECL|macro|SCSI_IRQ
mdefine_line|#define SCSI_IRQ&t;0x09
DECL|macro|LAN_IRQ
mdefine_line|#define LAN_IRQ&t;&t;0x0A
DECL|macro|OTHER_IRQ
mdefine_line|#define OTHER_IRQ&t;0x0B
multiline_comment|/* Data Structures */
multiline_comment|/* type is of the form x x xx xx&n; *                     | |  |  |_ 00 - I/O, 01 - Memory, 11 - PFMemory&n; *                     | |  - 00 - No Restrictions, 01 - Avoid VGA, 10 - Avoid&n; *                     | |    VGA and their aliases, 11 - Avoid ISA&n; *                     | - 1 - PCI device, 0 - non pci device&n; *                     - 1 - Primary PCI Bus Information (0 if Normal device)&n; * the IO restrictions [2:3] are only for primary buses&n; */
multiline_comment|/* we need this struct because there could be several resource blocks&n; * allocated per primary bus in the EBDA&n; */
DECL|struct|range_node
r_struct
id|range_node
(brace
DECL|member|rangeno
r_int
id|rangeno
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|end
id|u32
id|end
suffix:semicolon
DECL|member|next
r_struct
id|range_node
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bus_node
r_struct
id|bus_node
(brace
DECL|member|busno
id|u8
id|busno
suffix:semicolon
DECL|member|noIORanges
r_int
id|noIORanges
suffix:semicolon
DECL|member|rangeIO
r_struct
id|range_node
op_star
id|rangeIO
suffix:semicolon
DECL|member|noMemRanges
r_int
id|noMemRanges
suffix:semicolon
DECL|member|rangeMem
r_struct
id|range_node
op_star
id|rangeMem
suffix:semicolon
DECL|member|noPFMemRanges
r_int
id|noPFMemRanges
suffix:semicolon
DECL|member|rangePFMem
r_struct
id|range_node
op_star
id|rangePFMem
suffix:semicolon
DECL|member|needIOUpdate
r_int
id|needIOUpdate
suffix:semicolon
DECL|member|needMemUpdate
r_int
id|needMemUpdate
suffix:semicolon
DECL|member|needPFMemUpdate
r_int
id|needPFMemUpdate
suffix:semicolon
DECL|member|firstIO
r_struct
id|resource_node
op_star
id|firstIO
suffix:semicolon
multiline_comment|/* first IO resource on the Bus */
DECL|member|firstMem
r_struct
id|resource_node
op_star
id|firstMem
suffix:semicolon
multiline_comment|/* first memory resource on the Bus */
DECL|member|firstPFMem
r_struct
id|resource_node
op_star
id|firstPFMem
suffix:semicolon
multiline_comment|/* first prefetchable memory resource on the Bus */
DECL|member|firstPFMemFromMem
r_struct
id|resource_node
op_star
id|firstPFMemFromMem
suffix:semicolon
multiline_comment|/* when run out of pfmem available, taking from Mem */
DECL|member|bus_list
r_struct
id|list_head
id|bus_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|resource_node
r_struct
id|resource_node
(brace
DECL|member|rangeno
r_int
id|rangeno
suffix:semicolon
DECL|member|busno
id|u8
id|busno
suffix:semicolon
DECL|member|devfunc
id|u8
id|devfunc
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|end
id|u32
id|end
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* MEM, IO, PFMEM */
DECL|member|fromMem
id|u8
id|fromMem
suffix:semicolon
multiline_comment|/* this is to indicate that the range is from&n;&t;&t;&t;&t; * from the Memory bucket rather than from PFMem */
DECL|member|next
r_struct
id|resource_node
op_star
id|next
suffix:semicolon
DECL|member|nextRange
r_struct
id|resource_node
op_star
id|nextRange
suffix:semicolon
multiline_comment|/* for the other mem range on bus */
)brace
suffix:semicolon
DECL|struct|res_needed
r_struct
id|res_needed
(brace
DECL|member|mem
id|u32
id|mem
suffix:semicolon
DECL|member|pfmem
id|u32
id|pfmem
suffix:semicolon
DECL|member|io
id|u32
id|io
suffix:semicolon
DECL|member|not_correct
id|u8
id|not_correct
suffix:semicolon
multiline_comment|/* needed for return */
DECL|member|devices
r_int
id|devices
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* for device numbers behind this bridge */
)brace
suffix:semicolon
multiline_comment|/* functions */
r_extern
r_int
id|ibmphp_rsrc_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_add_resource
(paren
r_struct
id|resource_node
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_remove_resource
(paren
r_struct
id|resource_node
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_find_resource
(paren
r_struct
id|bus_node
op_star
comma
id|u32
comma
r_struct
id|resource_node
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_check_resource
(paren
r_struct
id|resource_node
op_star
comma
id|u8
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_remove_bus
(paren
r_struct
id|bus_node
op_star
comma
id|u8
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_free_resources
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_add_pfmem_from_mem
(paren
r_struct
id|resource_node
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|bus_node
op_star
id|ibmphp_find_res_bus
(paren
id|u8
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_print_test
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* for debugging purposes */
r_extern
r_void
id|ibmphp_hpc_initvars
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_hpc_readslot
(paren
r_struct
id|slot
op_star
comma
id|u8
comma
id|u8
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_hpc_writeslot
(paren
r_struct
id|slot
op_star
comma
id|u8
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_lock_operations
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_unlock_operations
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_hpc_fillhpslotinfo
(paren
r_struct
id|hotplug_slot
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_hpc_start_poll_thread
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ibmphp_hpc_stop_poll_thread
(paren
r_void
)paren
suffix:semicolon
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|FALSE
mdefine_line|#define FALSE&t;&t;&t;&t;0x00
DECL|macro|TRUE
mdefine_line|#define TRUE&t;&t;&t;&t;0x01
DECL|macro|HPC_ERROR
mdefine_line|#define HPC_ERROR&t;&t;&t;0xFF
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// BUS INFO
singleline_comment|//-----------------------------------------------------------------------------
DECL|macro|BUS_SPEED
mdefine_line|#define BUS_SPEED&t;&t;&t;0x30
DECL|macro|BUS_MODE
mdefine_line|#define BUS_MODE&t;&t;&t;0x40
DECL|macro|BUS_MODE_PCIX
mdefine_line|#define BUS_MODE_PCIX&t;&t;&t;0x01
DECL|macro|BUS_MODE_PCI
mdefine_line|#define BUS_MODE_PCI&t;&t;&t;0x00
DECL|macro|BUS_SPEED_2
mdefine_line|#define BUS_SPEED_2&t;&t;&t;0x20
DECL|macro|BUS_SPEED_1
mdefine_line|#define BUS_SPEED_1&t;&t;&t;0x10
DECL|macro|BUS_SPEED_33
mdefine_line|#define BUS_SPEED_33&t;&t;&t;0x00
DECL|macro|BUS_SPEED_66
mdefine_line|#define BUS_SPEED_66&t;&t;&t;0x01
DECL|macro|BUS_SPEED_100
mdefine_line|#define BUS_SPEED_100&t;&t;&t;0x02
DECL|macro|BUS_SPEED_133
mdefine_line|#define BUS_SPEED_133&t;&t;&t;0x03
DECL|macro|BUS_SPEED_66PCIX
mdefine_line|#define BUS_SPEED_66PCIX&t;&t;0x04
DECL|macro|BUS_SPEED_66UNKNOWN
mdefine_line|#define BUS_SPEED_66UNKNOWN&t;&t;0x05
DECL|macro|BUS_STATUS_AVAILABLE
mdefine_line|#define BUS_STATUS_AVAILABLE&t;&t;0x01
DECL|macro|BUS_CONTROL_AVAILABLE
mdefine_line|#define BUS_CONTROL_AVAILABLE&t;&t;0x02
DECL|macro|SLOT_LATCH_REGS_SUPPORTED
mdefine_line|#define SLOT_LATCH_REGS_SUPPORTED&t;0x10
DECL|macro|PRGM_MODEL_REV_LEVEL
mdefine_line|#define PRGM_MODEL_REV_LEVEL&t;&t;0xF0
DECL|macro|MAX_ADAPTER_NONE
mdefine_line|#define MAX_ADAPTER_NONE&t;&t;0x09
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC &squot;write&squot; operations/commands
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|//&t;Command&t;&t;&t;Code&t;State&t;Write to reg
singleline_comment|//&t;&t;&t;&t;&t;Machine&t;at index
singleline_comment|//-------------------------&t;----&t;-------&t;------------
DECL|macro|HPC_CTLR_ENABLEIRQ
mdefine_line|#define HPC_CTLR_ENABLEIRQ&t;0x00&t;
singleline_comment|// N&t;15
DECL|macro|HPC_CTLR_DISABLEIRQ
mdefine_line|#define HPC_CTLR_DISABLEIRQ&t;0x01&t;
singleline_comment|// N&t;15
DECL|macro|HPC_SLOT_OFF
mdefine_line|#define HPC_SLOT_OFF&t;&t;0x02&t;
singleline_comment|// Y&t;0-14
DECL|macro|HPC_SLOT_ON
mdefine_line|#define HPC_SLOT_ON&t;&t;0x03&t;
singleline_comment|// Y&t;0-14
DECL|macro|HPC_SLOT_ATTNOFF
mdefine_line|#define HPC_SLOT_ATTNOFF&t;0x04&t;
singleline_comment|// N&t;0-14
DECL|macro|HPC_SLOT_ATTNON
mdefine_line|#define HPC_SLOT_ATTNON&t;&t;0x05&t;
singleline_comment|// N&t;0-14
DECL|macro|HPC_CTLR_CLEARIRQ
mdefine_line|#define HPC_CTLR_CLEARIRQ&t;0x06&t;
singleline_comment|// N&t;15
DECL|macro|HPC_CTLR_RESET
mdefine_line|#define HPC_CTLR_RESET&t;&t;0x07&t;
singleline_comment|// Y&t;15
DECL|macro|HPC_CTLR_IRQSTEER
mdefine_line|#define HPC_CTLR_IRQSTEER&t;0x08&t;
singleline_comment|// N&t;15
DECL|macro|HPC_BUS_33CONVMODE
mdefine_line|#define HPC_BUS_33CONVMODE&t;0x09&t;
singleline_comment|// Y&t;31-34
DECL|macro|HPC_BUS_66CONVMODE
mdefine_line|#define HPC_BUS_66CONVMODE&t;0x0A&t;
singleline_comment|// Y&t;31-34
DECL|macro|HPC_BUS_66PCIXMODE
mdefine_line|#define HPC_BUS_66PCIXMODE&t;0x0B&t;
singleline_comment|// Y&t;31-34
DECL|macro|HPC_BUS_100PCIXMODE
mdefine_line|#define HPC_BUS_100PCIXMODE&t;0x0C&t;
singleline_comment|// Y&t;31-34
DECL|macro|HPC_BUS_133PCIXMODE
mdefine_line|#define HPC_BUS_133PCIXMODE&t;0x0D&t;
singleline_comment|// Y&t;31-34
DECL|macro|HPC_ALLSLOT_OFF
mdefine_line|#define HPC_ALLSLOT_OFF&t;&t;0x11&t;
singleline_comment|// Y&t;15
DECL|macro|HPC_ALLSLOT_ON
mdefine_line|#define HPC_ALLSLOT_ON&t;&t;0x12&t;
singleline_comment|// Y&t;15
DECL|macro|HPC_SLOT_BLINKLED
mdefine_line|#define HPC_SLOT_BLINKLED&t;0x13&t;
singleline_comment|// N&t;0-14
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// read commands
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|READ_SLOTSTATUS
mdefine_line|#define READ_SLOTSTATUS&t;&t;0x01
DECL|macro|READ_EXTSLOTSTATUS
mdefine_line|#define READ_EXTSLOTSTATUS&t;0x02
DECL|macro|READ_BUSSTATUS
mdefine_line|#define READ_BUSSTATUS&t;&t;0x03
DECL|macro|READ_CTLRSTATUS
mdefine_line|#define READ_CTLRSTATUS&t;&t;0x04
DECL|macro|READ_ALLSTAT
mdefine_line|#define READ_ALLSTAT&t;&t;0x05
DECL|macro|READ_ALLSLOT
mdefine_line|#define READ_ALLSLOT&t;&t;0x06
DECL|macro|READ_SLOTLATCHLOWREG
mdefine_line|#define READ_SLOTLATCHLOWREG&t;0x07
DECL|macro|READ_REVLEVEL
mdefine_line|#define READ_REVLEVEL&t;&t;0x08
DECL|macro|READ_HPCOPTIONS
mdefine_line|#define READ_HPCOPTIONS&t;&t;0x09
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// slot status
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_POWER
mdefine_line|#define HPC_SLOT_POWER&t;&t;0x01
DECL|macro|HPC_SLOT_CONNECT
mdefine_line|#define HPC_SLOT_CONNECT&t;0x02
DECL|macro|HPC_SLOT_ATTN
mdefine_line|#define HPC_SLOT_ATTN&t;&t;0x04
DECL|macro|HPC_SLOT_PRSNT2
mdefine_line|#define HPC_SLOT_PRSNT2&t;&t;0x08
DECL|macro|HPC_SLOT_PRSNT1
mdefine_line|#define HPC_SLOT_PRSNT1&t;&t;0x10
DECL|macro|HPC_SLOT_PWRGD
mdefine_line|#define HPC_SLOT_PWRGD&t;&t;0x20
DECL|macro|HPC_SLOT_BUS_SPEED
mdefine_line|#define HPC_SLOT_BUS_SPEED&t;0x40
DECL|macro|HPC_SLOT_LATCH
mdefine_line|#define HPC_SLOT_LATCH&t;&t;0x80
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_POWER status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_POWER_OFF
mdefine_line|#define HPC_SLOT_POWER_OFF&t;0x00
DECL|macro|HPC_SLOT_POWER_ON
mdefine_line|#define HPC_SLOT_POWER_ON&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_CONNECT status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_CONNECTED
mdefine_line|#define HPC_SLOT_CONNECTED&t;0x00
DECL|macro|HPC_SLOT_DISCONNECTED
mdefine_line|#define HPC_SLOT_DISCONNECTED&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_ATTN status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_ATTN_OFF
mdefine_line|#define HPC_SLOT_ATTN_OFF&t;0x00
DECL|macro|HPC_SLOT_ATTN_ON
mdefine_line|#define HPC_SLOT_ATTN_ON&t;0x01
DECL|macro|HPC_SLOT_ATTN_BLINK
mdefine_line|#define HPC_SLOT_ATTN_BLINK&t;0x02
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_PRSNT status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_EMPTY
mdefine_line|#define HPC_SLOT_EMPTY&t;&t;0x00
DECL|macro|HPC_SLOT_PRSNT_7
mdefine_line|#define HPC_SLOT_PRSNT_7&t;0x01
DECL|macro|HPC_SLOT_PRSNT_15
mdefine_line|#define HPC_SLOT_PRSNT_15&t;0x02
DECL|macro|HPC_SLOT_PRSNT_25
mdefine_line|#define HPC_SLOT_PRSNT_25&t;0x03
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_PWRGD status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_PWRGD_FAULT_NONE
mdefine_line|#define HPC_SLOT_PWRGD_FAULT_NONE&t;0x00
DECL|macro|HPC_SLOT_PWRGD_GOOD
mdefine_line|#define HPC_SLOT_PWRGD_GOOD&t;&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_BUS_SPEED status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_BUS_SPEED_OK
mdefine_line|#define HPC_SLOT_BUS_SPEED_OK&t;0x00
DECL|macro|HPC_SLOT_BUS_SPEED_MISM
mdefine_line|#define HPC_SLOT_BUS_SPEED_MISM&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_SLOT_LATCH status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_LATCH_OPEN
mdefine_line|#define HPC_SLOT_LATCH_OPEN&t;0x01&t;
singleline_comment|// NOTE : in PCI spec bit off = open
DECL|macro|HPC_SLOT_LATCH_CLOSED
mdefine_line|#define HPC_SLOT_LATCH_CLOSED&t;0x00&t;
singleline_comment|// NOTE : in PCI spec bit on  = closed
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// extended slot status
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_PCIX
mdefine_line|#define HPC_SLOT_PCIX&t;&t;0x01
DECL|macro|HPC_SLOT_SPEED1
mdefine_line|#define HPC_SLOT_SPEED1&t;&t;0x02
DECL|macro|HPC_SLOT_SPEED2
mdefine_line|#define HPC_SLOT_SPEED2&t;&t;0x04
DECL|macro|HPC_SLOT_BLINK_ATTN
mdefine_line|#define HPC_SLOT_BLINK_ATTN&t;0x08
DECL|macro|HPC_SLOT_RSRVD1
mdefine_line|#define HPC_SLOT_RSRVD1&t;&t;0x10
DECL|macro|HPC_SLOT_RSRVD2
mdefine_line|#define HPC_SLOT_RSRVD2&t;&t;0x20
DECL|macro|HPC_SLOT_BUS_MODE
mdefine_line|#define HPC_SLOT_BUS_MODE&t;0x40
DECL|macro|HPC_SLOT_RSRVD3
mdefine_line|#define HPC_SLOT_RSRVD3&t;&t;0x80
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_XSLOT_PCIX_CAP status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_PCIX_NO
mdefine_line|#define HPC_SLOT_PCIX_NO&t;0x00
DECL|macro|HPC_SLOT_PCIX_YES
mdefine_line|#define HPC_SLOT_PCIX_YES&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_XSLOT_SPEED status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_SPEED_33
mdefine_line|#define HPC_SLOT_SPEED_33&t;0x00
DECL|macro|HPC_SLOT_SPEED_66
mdefine_line|#define HPC_SLOT_SPEED_66&t;0x01
DECL|macro|HPC_SLOT_SPEED_133
mdefine_line|#define HPC_SLOT_SPEED_133&t;0x02
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_XSLOT_ATTN_BLINK status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_ATTN_BLINK_OFF
mdefine_line|#define HPC_SLOT_ATTN_BLINK_OFF&t;0x00
DECL|macro|HPC_SLOT_ATTN_BLINK_ON
mdefine_line|#define HPC_SLOT_ATTN_BLINK_ON&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_XSLOT_BUS_MODE status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_SLOT_BUS_MODE_OK
mdefine_line|#define HPC_SLOT_BUS_MODE_OK&t;0x00
DECL|macro|HPC_SLOT_BUS_MODE_MISM
mdefine_line|#define HPC_SLOT_BUS_MODE_MISM&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// Controller status
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_CTLR_WORKING
mdefine_line|#define HPC_CTLR_WORKING&t;0x01
DECL|macro|HPC_CTLR_FINISHED
mdefine_line|#define HPC_CTLR_FINISHED&t;0x02
DECL|macro|HPC_CTLR_RESULT0
mdefine_line|#define HPC_CTLR_RESULT0&t;0x04
DECL|macro|HPC_CTLR_RESULT1
mdefine_line|#define HPC_CTLR_RESULT1&t;0x08
DECL|macro|HPC_CTLR_RESULE2
mdefine_line|#define HPC_CTLR_RESULE2&t;0x10
DECL|macro|HPC_CTLR_RESULT3
mdefine_line|#define HPC_CTLR_RESULT3&t;0x20
DECL|macro|HPC_CTLR_IRQ_ROUTG
mdefine_line|#define HPC_CTLR_IRQ_ROUTG&t;0x40
DECL|macro|HPC_CTLR_IRQ_PENDG
mdefine_line|#define HPC_CTLR_IRQ_PENDG&t;0x80
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_CTLR_WROKING status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_CTLR_WORKING_NO
mdefine_line|#define HPC_CTLR_WORKING_NO&t;0x00
DECL|macro|HPC_CTLR_WORKING_YES
mdefine_line|#define HPC_CTLR_WORKING_YES&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_CTLR_FINISHED status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_CTLR_FINISHED_NO
mdefine_line|#define HPC_CTLR_FINISHED_NO&t;0x00
DECL|macro|HPC_CTLR_FINISHED_YES
mdefine_line|#define HPC_CTLR_FINISHED_YES&t;0x01
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// HPC_CTLR_RESULT status return codes
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|HPC_CTLR_RESULT_SUCCESS
mdefine_line|#define HPC_CTLR_RESULT_SUCCESS&t;0x00
DECL|macro|HPC_CTLR_RESULT_FAILED
mdefine_line|#define HPC_CTLR_RESULT_FAILED&t;0x01
DECL|macro|HPC_CTLR_RESULT_RSVD
mdefine_line|#define HPC_CTLR_RESULT_RSVD&t;0x02
DECL|macro|HPC_CTLR_RESULT_NORESP
mdefine_line|#define HPC_CTLR_RESULT_NORESP&t;0x03
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// macro for slot info
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|SLOT_POWER
mdefine_line|#define SLOT_POWER(s)&t;((u8) ((s &amp; HPC_SLOT_POWER) &bslash;&n;&t;? HPC_SLOT_POWER_ON : HPC_SLOT_POWER_OFF))
DECL|macro|SLOT_CONNECT
mdefine_line|#define SLOT_CONNECT(s)&t;((u8) ((s &amp; HPC_SLOT_CONNECT) &bslash;&n;&t;? HPC_SLOT_DISCONNECTED : HPC_SLOT_CONNECTED))
DECL|macro|SLOT_ATTN
mdefine_line|#define SLOT_ATTN(s,es)&t;((u8) ((es &amp; HPC_SLOT_BLINK_ATTN) &bslash;&n;&t;? HPC_SLOT_ATTN_BLINK &bslash;&n;&t;: ((s &amp; HPC_SLOT_ATTN) ? HPC_SLOT_ATTN_ON : HPC_SLOT_ATTN_OFF)))
DECL|macro|SLOT_PRESENT
mdefine_line|#define SLOT_PRESENT(s)&t;((u8) ((s &amp; HPC_SLOT_PRSNT1) &bslash;&n;&t;? ((s &amp; HPC_SLOT_PRSNT2) ? HPC_SLOT_EMPTY : HPC_SLOT_PRSNT_15) &bslash;&n;&t;: ((s &amp; HPC_SLOT_PRSNT2) ? HPC_SLOT_PRSNT_25 : HPC_SLOT_PRSNT_7)))
DECL|macro|SLOT_PWRGD
mdefine_line|#define SLOT_PWRGD(s)&t;((u8) ((s &amp; HPC_SLOT_PWRGD) &bslash;&n;&t;? HPC_SLOT_PWRGD_GOOD : HPC_SLOT_PWRGD_FAULT_NONE))
DECL|macro|SLOT_BUS_SPEED
mdefine_line|#define SLOT_BUS_SPEED(s)&t;((u8) ((s &amp; HPC_SLOT_BUS_SPEED) &bslash;&n;&t;? HPC_SLOT_BUS_SPEED_MISM : HPC_SLOT_BUS_SPEED_OK))
DECL|macro|SLOT_LATCH
mdefine_line|#define SLOT_LATCH(s)&t;((u8) ((s &amp; HPC_SLOT_LATCH) &bslash;&n;&t;? HPC_SLOT_LATCH_CLOSED : HPC_SLOT_LATCH_OPEN))
DECL|macro|SLOT_PCIX
mdefine_line|#define SLOT_PCIX(es)&t;((u8) ((es &amp; HPC_SLOT_PCIX) &bslash;&n;&t;? HPC_SLOT_PCIX_YES : HPC_SLOT_PCIX_NO))
DECL|macro|SLOT_SPEED
mdefine_line|#define SLOT_SPEED(es)&t;((u8) ((es &amp; HPC_SLOT_SPEED2) &bslash;&n;&t;? ((es &amp; HPC_SLOT_SPEED1) ? HPC_SLOT_SPEED_133   &bslash;&n;&t;&t;&t;&t;: HPC_SLOT_SPEED_66)   &bslash;&n;&t;: HPC_SLOT_SPEED_33))
DECL|macro|SLOT_BUS_MODE
mdefine_line|#define SLOT_BUS_MODE(es)&t;((u8) ((es &amp; HPC_SLOT_BUS_MODE) &bslash;&n;&t;? HPC_SLOT_BUS_MODE_MISM : HPC_SLOT_BUS_MODE_OK))
singleline_comment|//--------------------------------------------------------------------------
singleline_comment|// macro for bus info
singleline_comment|//---------------------------------------------------------------------------
DECL|macro|CURRENT_BUS_SPEED
mdefine_line|#define CURRENT_BUS_SPEED(s)&t;((u8) (s &amp; BUS_SPEED_2) &bslash;&n;&t;? ((s &amp; BUS_SPEED_1) ? BUS_SPEED_133 : BUS_SPEED_100) &bslash;&n;&t;: ((s &amp; BUS_SPEED_1) ? BUS_SPEED_66 : BUS_SPEED_33))
DECL|macro|CURRENT_BUS_MODE
mdefine_line|#define CURRENT_BUS_MODE(s)&t;((u8) (s &amp; BUS_MODE) ? BUS_MODE_PCIX : BUS_MODE_PCI)
DECL|macro|READ_BUS_STATUS
mdefine_line|#define READ_BUS_STATUS(s)&t;((u8) (s-&gt;options &amp; BUS_STATUS_AVAILABLE))
DECL|macro|READ_BUS_MODE
mdefine_line|#define READ_BUS_MODE(s)&t;((s-&gt;revision &amp; PRGM_MODEL_REV_LEVEL) &gt;= 0x20)
DECL|macro|SET_BUS_STATUS
mdefine_line|#define SET_BUS_STATUS(s)&t;((u8) (s-&gt;options &amp; BUS_CONTROL_AVAILABLE))
DECL|macro|READ_SLOT_LATCH
mdefine_line|#define READ_SLOT_LATCH(s)&t;((u8) (s-&gt;options &amp; SLOT_LATCH_REGS_SUPPORTED))
singleline_comment|//----------------------------------------------------------------------------
singleline_comment|// macro for controller info
singleline_comment|//----------------------------------------------------------------------------
DECL|macro|CTLR_WORKING
mdefine_line|#define CTLR_WORKING(c) ((u8) ((c &amp; HPC_CTLR_WORKING) &bslash;&n;&t;? HPC_CTLR_WORKING_YES : HPC_CTLR_WORKING_NO))
DECL|macro|CTLR_FINISHED
mdefine_line|#define CTLR_FINISHED(c) ((u8) ((c &amp; HPC_CTLR_FINISHED) &bslash;&n;&t;? HPC_CTLR_FINISHED_YES : HPC_CTLR_FINISHED_NO))
DECL|macro|CTLR_RESULT
mdefine_line|#define CTLR_RESULT(c) ((u8) ((c &amp; HPC_CTLR_RESULT1)  &bslash;&n;&t;? ((c &amp; HPC_CTLR_RESULT0) ? HPC_CTLR_RESULT_NORESP &bslash;&n;&t;&t;&t;&t;: HPC_CTLR_RESULT_RSVD)  &bslash;&n;&t;: ((c &amp; HPC_CTLR_RESULT0) ? HPC_CTLR_RESULT_FAILED &bslash;&n;&t;&t;&t;&t;: HPC_CTLR_RESULT_SUCCESS)))
singleline_comment|// command that affect the state machine of HPC
DECL|macro|NEEDTOCHECK_CMDSTATUS
mdefine_line|#define NEEDTOCHECK_CMDSTATUS(c) ((c == HPC_SLOT_OFF)        || &bslash;&n;&t;&t;&t;&t;  (c == HPC_SLOT_ON)         || &bslash;&n;&t;&t;&t;&t;  (c == HPC_CTLR_RESET)      || &bslash;&n;&t;&t;&t;&t;  (c == HPC_BUS_33CONVMODE)  || &bslash;&n;&t;&t;&t;&t;  (c == HPC_BUS_66CONVMODE)  || &bslash;&n;&t;&t;&t;&t;  (c == HPC_BUS_66PCIXMODE)  || &bslash;&n;&t;&t;&t;&t;  (c == HPC_BUS_100PCIXMODE) || &bslash;&n;&t;&t;&t;&t;  (c == HPC_BUS_133PCIXMODE) || &bslash;&n;&t;&t;&t;&t;  (c == HPC_ALLSLOT_OFF)     || &bslash;&n;&t;&t;&t;&t;  (c == HPC_ALLSLOT_ON))
multiline_comment|/* Core part of the driver */
DECL|macro|ENABLE
mdefine_line|#define ENABLE&t;&t;1
DECL|macro|DISABLE
mdefine_line|#define DISABLE&t;&t;0
DECL|macro|ADD
mdefine_line|#define ADD&t;&t;0
DECL|macro|REMOVE
mdefine_line|#define REMOVE&t;&t;1
DECL|macro|DETAIL
mdefine_line|#define DETAIL&t;&t;2
DECL|macro|MAX_OPS
mdefine_line|#define MAX_OPS&t;&t;3
DECL|macro|CARD_INFO
mdefine_line|#define CARD_INFO&t;0x07
DECL|macro|PCIX133
mdefine_line|#define PCIX133&t;&t;0x07
DECL|macro|PCIX66
mdefine_line|#define PCIX66&t;&t;0x05
DECL|macro|PCI66
mdefine_line|#define PCI66&t;&t;0x04
r_extern
r_struct
id|pci_ops
op_star
id|ibmphp_pci_root_ops
suffix:semicolon
multiline_comment|/* Variables */
DECL|struct|pci_func
r_struct
id|pci_func
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* from the OS */
DECL|member|busno
id|u8
id|busno
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|function
id|u8
id|function
suffix:semicolon
DECL|member|io
r_struct
id|resource_node
op_star
id|io
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|mem
r_struct
id|resource_node
op_star
id|mem
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|pfmem
r_struct
id|resource_node
op_star
id|pfmem
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|next
r_struct
id|pci_func
op_star
id|next
suffix:semicolon
DECL|member|devices
r_int
id|devices
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* for bridge config */
DECL|member|irq
id|u8
id|irq
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* for interrupt config */
DECL|member|bus
id|u8
id|bus
suffix:semicolon
multiline_comment|/* flag for unconfiguring, to say if PPB */
)brace
suffix:semicolon
DECL|struct|slot
r_struct
id|slot
(brace
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|number
id|u8
id|number
suffix:semicolon
DECL|member|real_physical_slot_num
id|u8
id|real_physical_slot_num
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|100
)braket
suffix:semicolon
DECL|member|capabilities
id|u32
id|capabilities
suffix:semicolon
DECL|member|supported_speed
id|u8
id|supported_speed
suffix:semicolon
DECL|member|supported_bus_mode
id|u8
id|supported_bus_mode
suffix:semicolon
DECL|member|hotplug_slot
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
suffix:semicolon
DECL|member|ctrl
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
DECL|member|func
r_struct
id|pci_func
op_star
id|func
suffix:semicolon
DECL|member|irq
id|u8
id|irq
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* this is for disable slot and polling */
DECL|member|bit_mode
r_int
id|bit_mode
suffix:semicolon
multiline_comment|/* 0 = 32, 1 = 64 */
DECL|member|ctlr_index
id|u8
id|ctlr_index
suffix:semicolon
DECL|member|bus_on
r_struct
id|bus_info
op_star
id|bus_on
suffix:semicolon
DECL|member|ibm_slot_list
r_struct
id|list_head
id|ibm_slot_list
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|member|ext_status
id|u8
id|ext_status
suffix:semicolon
DECL|member|busstatus
id|u8
id|busstatus
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|controller
r_struct
id|controller
(brace
DECL|member|slots
r_struct
id|ebda_hpc_slot
op_star
id|slots
suffix:semicolon
DECL|member|buses
r_struct
id|ebda_hpc_bus
op_star
id|buses
suffix:semicolon
DECL|member|starting_slot_num
id|u8
id|starting_slot_num
suffix:semicolon
multiline_comment|/* starting and ending slot #&squot;s this ctrl controls*/
DECL|member|ending_slot_num
id|u8
id|ending_slot_num
suffix:semicolon
DECL|member|revision
id|u8
id|revision
suffix:semicolon
DECL|member|options
id|u8
id|options
suffix:semicolon
multiline_comment|/* which options HPC supports */
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|member|ctlr_id
id|u8
id|ctlr_id
suffix:semicolon
DECL|member|slot_count
id|u8
id|slot_count
suffix:semicolon
DECL|member|bus_count
id|u8
id|bus_count
suffix:semicolon
DECL|member|ctlr_relative_id
id|u8
id|ctlr_relative_id
suffix:semicolon
DECL|member|irq
id|u32
id|irq
suffix:semicolon
r_union
(brace
DECL|member|isa_ctlr
r_struct
id|isa_ctlr_access
id|isa_ctlr
suffix:semicolon
DECL|member|pci_ctlr
r_struct
id|pci_ctlr_access
id|pci_ctlr
suffix:semicolon
DECL|member|wpeg_ctlr
r_struct
id|wpeg_i2c_ctlr_access
id|wpeg_ctlr
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|ctlr_type
id|u8
id|ctlr_type
suffix:semicolon
DECL|member|ebda_hpc_list
r_struct
id|list_head
id|ebda_hpc_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Functions */
r_extern
r_int
id|ibmphp_init_devno
(paren
r_struct
id|slot
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* This function is called from EBDA, so we need it not be static */
r_extern
r_int
id|ibmphp_disable_slot
(paren
r_struct
id|hotplug_slot
op_star
)paren
suffix:semicolon
multiline_comment|/* This function is called from HPC, so we need it to not be static */
r_extern
r_int
id|ibmphp_update_slot_info
(paren
r_struct
id|slot
op_star
)paren
suffix:semicolon
multiline_comment|/* This function is called from HPC, so we need it to not be be static */
r_extern
r_int
id|ibmphp_configure_card
(paren
r_struct
id|pci_func
op_star
comma
id|u8
)paren
suffix:semicolon
r_extern
r_int
id|ibmphp_unconfigure_card
(paren
r_struct
id|slot
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|hotplug_slot_ops
id|ibmphp_hotplug_slot_ops
suffix:semicolon
DECL|function|long_delay
r_static
r_inline
r_void
id|long_delay
(paren
r_int
id|delay
)paren
(brace
id|set_current_state
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
(paren
id|delay
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;
singleline_comment|//__IBMPHP_H
eof
