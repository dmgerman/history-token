multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: pci.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:12&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)pci.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_pci_h__
DECL|macro|__rio_pci_h__
mdefine_line|#define&t;__rio_pci_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_pci_h_sccs_
r_static
r_char
op_star
id|_pci_h_sccs_
op_assign
l_string|&quot;@(#)pci.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** PCI stuff&n;*/
DECL|macro|PCITpFastClock
mdefine_line|#define&t;PCITpFastClock&t;&t;0x80
DECL|macro|PCITpSlowClock
mdefine_line|#define&t;PCITpSlowClock&t;&t;0x00
DECL|macro|PCITpFastLinks
mdefine_line|#define&t;PCITpFastLinks&t;        0x40
DECL|macro|PCITpSlowLinks
mdefine_line|#define&t;PCITpSlowLinks&t;        0x00
DECL|macro|PCITpIntEnable
mdefine_line|#define&t;PCITpIntEnable&t;&t;0x04
DECL|macro|PCITpIntDisable
mdefine_line|#define&t;PCITpIntDisable&t;&t;0x00
DECL|macro|PCITpBusEnable
mdefine_line|#define&t;PCITpBusEnable&t;&t;0x02
DECL|macro|PCITpBusDisable
mdefine_line|#define&t;PCITpBusDisable&t;&t;0x00
DECL|macro|PCITpBootFromRam
mdefine_line|#define&t;PCITpBootFromRam&t;0x01
DECL|macro|PCITpBootFromLink
mdefine_line|#define&t;PCITpBootFromLink&t;0x00
DECL|macro|RIO_PCI_VENDOR
mdefine_line|#define&t;RIO_PCI_VENDOR&t;&t;0x11CB
DECL|macro|RIO_PCI_DEVICE
mdefine_line|#define&t;RIO_PCI_DEVICE&t;&t;0x8000
DECL|macro|RIO_PCI_BASE_CLASS
mdefine_line|#define&t;RIO_PCI_BASE_CLASS&t;0x02
DECL|macro|RIO_PCI_SUB_CLASS
mdefine_line|#define&t;RIO_PCI_SUB_CLASS&t;0x80
DECL|macro|RIO_PCI_PROG_IFACE
mdefine_line|#define&t;RIO_PCI_PROG_IFACE&t;0x00
DECL|macro|RIO_PCI_RID
mdefine_line|#define RIO_PCI_RID&t;&t;0x0008
DECL|macro|RIO_PCI_BADR0
mdefine_line|#define RIO_PCI_BADR0&t;&t;0x0010
DECL|macro|RIO_PCI_INTLN
mdefine_line|#define RIO_PCI_INTLN&t;&t;0x003C
DECL|macro|RIO_PCI_INTPIN
mdefine_line|#define RIO_PCI_INTPIN&t;&t;0x003D
DECL|macro|RIO_PCI_MEM_SIZE
mdefine_line|#define&t;RIO_PCI_MEM_SIZE&t;65536
DECL|macro|RIO_PCI_TURBO_TP
mdefine_line|#define&t;RIO_PCI_TURBO_TP&t;0x80
DECL|macro|RIO_PCI_FAST_LINKS
mdefine_line|#define&t;RIO_PCI_FAST_LINKS&t;0x40
DECL|macro|RIO_PCI_INT_ENABLE
mdefine_line|#define&t;RIO_PCI_INT_ENABLE&t;0x04
DECL|macro|RIO_PCI_TP_BUS_ENABLE
mdefine_line|#define&t;RIO_PCI_TP_BUS_ENABLE&t;0x02
DECL|macro|RIO_PCI_BOOT_FROM_RAM
mdefine_line|#define&t;RIO_PCI_BOOT_FROM_RAM&t;0x01
DECL|macro|RIO_PCI_DEFAULT_MODE
mdefine_line|#define&t;RIO_PCI_DEFAULT_MODE&t;0x05
macro_line|#endif&t;/* __rio_pci_h__ */
eof
