multiline_comment|/*&n; * SHPCHPRM Legacy: PHP Resource Manager for Non-ACPI/Legacy platform using HRT&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; * Copyright (C) 2003-2004 Intel Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;, &lt;dely.l.sy@intel.com&gt;&n; *&n; */
macro_line|#ifndef _SHPCHPRM_LEGACY_H_
DECL|macro|_SHPCHPRM_LEGACY_H_
mdefine_line|#define _SHPCHPRM_LEGACY_H_
DECL|macro|ROM_PHY_ADDR
mdefine_line|#define ROM_PHY_ADDR&t;0x0F0000
DECL|macro|ROM_PHY_LEN
mdefine_line|#define ROM_PHY_LEN&t;0x00FFFF
DECL|struct|slot_rt
r_struct
id|slot_rt
(brace
DECL|member|dev_func
id|u8
id|dev_func
suffix:semicolon
DECL|member|primary_bus
id|u8
id|primary_bus
suffix:semicolon
DECL|member|secondary_bus
id|u8
id|secondary_bus
suffix:semicolon
DECL|member|max_bus
id|u8
id|max_bus
suffix:semicolon
DECL|member|io_base
id|u16
id|io_base
suffix:semicolon
DECL|member|io_length
id|u16
id|io_length
suffix:semicolon
DECL|member|mem_base
id|u16
id|mem_base
suffix:semicolon
DECL|member|mem_length
id|u16
id|mem_length
suffix:semicolon
DECL|member|pre_mem_base
id|u16
id|pre_mem_base
suffix:semicolon
DECL|member|pre_mem_length
id|u16
id|pre_mem_length
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets to the hotplug slot resource table registers based on the above structure layout */
DECL|enum|slot_rt_offsets
r_enum
id|slot_rt_offsets
(brace
DECL|enumerator|DEV_FUNC
id|DEV_FUNC
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|dev_func
)paren
comma
DECL|enumerator|PRIMARY_BUS
id|PRIMARY_BUS
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|primary_bus
)paren
comma
DECL|enumerator|SECONDARY_BUS
id|SECONDARY_BUS
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|secondary_bus
)paren
comma
DECL|enumerator|MAX_BUS
id|MAX_BUS
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|max_bus
)paren
comma
DECL|enumerator|IO_BASE
id|IO_BASE
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|io_base
)paren
comma
DECL|enumerator|IO_LENGTH
id|IO_LENGTH
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|io_length
)paren
comma
DECL|enumerator|MEM_BASE
id|MEM_BASE
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|mem_base
)paren
comma
DECL|enumerator|MEM_LENGTH
id|MEM_LENGTH
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|mem_length
)paren
comma
DECL|enumerator|PRE_MEM_BASE
id|PRE_MEM_BASE
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|pre_mem_base
)paren
comma
DECL|enumerator|PRE_MEM_LENGTH
id|PRE_MEM_LENGTH
op_assign
m_offsetof
(paren
r_struct
id|slot_rt
comma
id|pre_mem_length
)paren
comma
)brace
suffix:semicolon
DECL|struct|hrt
r_struct
id|hrt
(brace
DECL|member|sig0
r_char
id|sig0
suffix:semicolon
DECL|member|sig1
r_char
id|sig1
suffix:semicolon
DECL|member|sig2
r_char
id|sig2
suffix:semicolon
DECL|member|sig3
r_char
id|sig3
suffix:semicolon
DECL|member|unused_IRQ
id|u16
id|unused_IRQ
suffix:semicolon
DECL|member|PCIIRQ
id|u16
id|PCIIRQ
suffix:semicolon
DECL|member|number_of_entries
id|u8
id|number_of_entries
suffix:semicolon
DECL|member|revision
id|u8
id|revision
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* offsets to the hotplug resource table registers based on the above structure layout */
DECL|enum|hrt_offsets
r_enum
id|hrt_offsets
(brace
DECL|enumerator|SIG0
id|SIG0
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|sig0
)paren
comma
DECL|enumerator|SIG1
id|SIG1
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|sig1
)paren
comma
DECL|enumerator|SIG2
id|SIG2
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|sig2
)paren
comma
DECL|enumerator|SIG3
id|SIG3
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|sig3
)paren
comma
DECL|enumerator|UNUSED_IRQ
id|UNUSED_IRQ
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|unused_IRQ
)paren
comma
DECL|enumerator|PCIIRQ
id|PCIIRQ
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|PCIIRQ
)paren
comma
DECL|enumerator|NUMBER_OF_ENTRIES
id|NUMBER_OF_ENTRIES
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|number_of_entries
)paren
comma
DECL|enumerator|REVISION
id|REVISION
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|revision
)paren
comma
DECL|enumerator|HRT_RESERVED1
id|HRT_RESERVED1
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|reserved1
)paren
comma
DECL|enumerator|HRT_RESERVED2
id|HRT_RESERVED2
op_assign
m_offsetof
(paren
r_struct
id|hrt
comma
id|reserved2
)paren
comma
)brace
suffix:semicolon
DECL|struct|irq_info
r_struct
id|irq_info
(brace
DECL|member|bus
DECL|member|devfn
id|u8
id|bus
comma
id|devfn
suffix:semicolon
multiline_comment|/* bus, device and function */
r_struct
(brace
DECL|member|link
id|u8
id|link
suffix:semicolon
multiline_comment|/* IRQ line ID, chipset dependent, 0=not routed */
DECL|member|bitmap
id|u16
id|bitmap
suffix:semicolon
multiline_comment|/* Available IRQs */
DECL|member|irq
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|irq
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|slot
id|u8
id|slot
suffix:semicolon
multiline_comment|/* slot number, 0=onboard */
DECL|member|rfu
id|u8
id|rfu
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|irq_routing_table
r_struct
id|irq_routing_table
(brace
DECL|member|signature
id|u32
id|signature
suffix:semicolon
multiline_comment|/* PIRQ_SIGNATURE should be here */
DECL|member|version
id|u16
id|version
suffix:semicolon
multiline_comment|/* PIRQ_VERSION */
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* Table size in bytes */
DECL|member|rtr_bus
DECL|member|rtr_devfn
id|u8
id|rtr_bus
comma
id|rtr_devfn
suffix:semicolon
multiline_comment|/* Where the interrupt router lies */
DECL|member|exclusive_irqs
id|u16
id|exclusive_irqs
suffix:semicolon
multiline_comment|/* IRQs devoted exclusively to PCI usage */
DECL|member|rtr_vendor
DECL|member|rtr_device
id|u16
id|rtr_vendor
comma
id|rtr_device
suffix:semicolon
multiline_comment|/* Vendor and device ID of interrupt router */
DECL|member|miniport_data
id|u32
id|miniport_data
suffix:semicolon
multiline_comment|/* Crap */
DECL|member|rfu
id|u8
id|rfu
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
multiline_comment|/* Modulo 256 checksum must give zero */
DECL|member|slots
r_struct
id|irq_info
id|slots
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _SHPCHPRM_LEGACY_H_ */
eof
