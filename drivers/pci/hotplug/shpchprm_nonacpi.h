multiline_comment|/*&n; * SHPCHPRM NONACPI: PHP Resource Manager for Non-ACPI/Legacy platform&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; * Copyright (C) 2003-2004 Intel Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;, &lt;dely.l.sy@intel.com&gt;&n; *&n; */
macro_line|#ifndef _SHPCHPRM_NONACPI_H_
DECL|macro|_SHPCHPRM_NONACPI_H_
mdefine_line|#define _SHPCHPRM_NONACPI_H_
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
macro_line|#endif&t;&t;&t;&t;/* _SHPCHPRM_NONACPI_H_ */
eof
