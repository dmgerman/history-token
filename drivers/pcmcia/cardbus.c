multiline_comment|/*&n; * cardbus.c -- 16-bit PCMCIA core support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * (C) 1999&t;&t;David A. Hinds&n; */
multiline_comment|/*&n; * Cardbus handling has been re-written to be more of a PCI bridge thing,&n; * and the PCI code basically does all the resource handling.&n; *&n; *&t;&t;Linus, Jan 2000&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|IN_CARD_SERVICES
mdefine_line|#define IN_CARD_SERVICES
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
multiline_comment|/*====================================================================*/
DECL|macro|FIND_FIRST_BIT
mdefine_line|#define FIND_FIRST_BIT(n)&t;((n) - ((n) &amp; ((n)-1)))
multiline_comment|/* Offsets in the Expansion ROM Image Header */
DECL|macro|ROM_SIGNATURE
mdefine_line|#define ROM_SIGNATURE&t;&t;0x0000&t;/* 2 bytes */
DECL|macro|ROM_DATA_PTR
mdefine_line|#define ROM_DATA_PTR&t;&t;0x0018&t;/* 2 bytes */
multiline_comment|/* Offsets in the CardBus PC Card Data Structure */
DECL|macro|PCDATA_SIGNATURE
mdefine_line|#define PCDATA_SIGNATURE&t;0x0000&t;/* 4 bytes */
DECL|macro|PCDATA_VPD_PTR
mdefine_line|#define PCDATA_VPD_PTR&t;&t;0x0008&t;/* 2 bytes */
DECL|macro|PCDATA_LENGTH
mdefine_line|#define PCDATA_LENGTH&t;&t;0x000a&t;/* 2 bytes */
DECL|macro|PCDATA_REVISION
mdefine_line|#define PCDATA_REVISION&t;&t;0x000c
DECL|macro|PCDATA_IMAGE_SZ
mdefine_line|#define PCDATA_IMAGE_SZ&t;&t;0x0010&t;/* 2 bytes */
DECL|macro|PCDATA_ROM_LEVEL
mdefine_line|#define PCDATA_ROM_LEVEL&t;0x0012&t;/* 2 bytes */
DECL|macro|PCDATA_CODE_TYPE
mdefine_line|#define PCDATA_CODE_TYPE&t;0x0014
DECL|macro|PCDATA_INDICATOR
mdefine_line|#define PCDATA_INDICATOR&t;0x0015
multiline_comment|/*=====================================================================&n;&n;    Expansion ROM&squot;s have a special layout, and pointers specify an&n;    image number and an offset within that image.  xlate_rom_addr()&n;    converts an image/offset address to an absolute offset from the&n;    ROM&squot;s base address.&n;    &n;=====================================================================*/
DECL|function|xlate_rom_addr
r_static
id|u_int
id|xlate_rom_addr
c_func
(paren
r_void
id|__iomem
op_star
id|b
comma
id|u_int
id|addr
)paren
(brace
id|u_int
id|img
op_assign
l_int|0
comma
id|ofs
op_assign
l_int|0
comma
id|sz
suffix:semicolon
id|u_short
id|data
suffix:semicolon
r_while
c_loop
(paren
(paren
id|readb
c_func
(paren
id|b
)paren
op_eq
l_int|0x55
)paren
op_logical_and
(paren
id|readb
c_func
(paren
id|b
op_plus
l_int|1
)paren
op_eq
l_int|0xaa
)paren
)paren
(brace
r_if
c_cond
(paren
id|img
op_eq
(paren
id|addr
op_rshift
l_int|28
)paren
)paren
r_return
(paren
id|addr
op_amp
l_int|0x0fffffff
)paren
op_plus
id|ofs
suffix:semicolon
id|data
op_assign
id|readb
c_func
(paren
id|b
op_plus
id|ROM_DATA_PTR
)paren
op_plus
(paren
id|readb
c_func
(paren
id|b
op_plus
id|ROM_DATA_PTR
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|sz
op_assign
l_int|512
op_star
(paren
id|readb
c_func
(paren
id|b
op_plus
id|data
op_plus
id|PCDATA_IMAGE_SZ
)paren
op_plus
(paren
id|readb
c_func
(paren
id|b
op_plus
id|data
op_plus
id|PCDATA_IMAGE_SZ
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sz
op_eq
l_int|0
)paren
op_logical_or
(paren
id|readb
c_func
(paren
id|b
op_plus
id|data
op_plus
id|PCDATA_INDICATOR
)paren
op_amp
l_int|0x80
)paren
)paren
r_break
suffix:semicolon
id|b
op_add_assign
id|sz
suffix:semicolon
id|ofs
op_add_assign
id|sz
suffix:semicolon
id|img
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    These are similar to setup_cis_mem and release_cis_mem for 16-bit&n;    cards.  The &quot;result&quot; that is used externally is the cb_cis_virt&n;    pointer in the struct pcmcia_socket structure.&n;    &n;=====================================================================*/
DECL|function|cb_release_cis_mem
r_static
r_void
id|cb_release_cis_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;cb_cis_virt
)paren
(brace
id|cs_dbg
c_func
(paren
id|s
comma
l_int|1
comma
l_string|&quot;cb_release_cis_mem()&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|s-&gt;cb_cis_virt
)paren
suffix:semicolon
id|s-&gt;cb_cis_virt
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;cb_cis_res
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|cb_setup_cis_mem
r_static
r_int
id|cb_setup_cis_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
r_int
r_int
id|start
comma
id|size
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
id|s-&gt;cb_cis_res
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;cb_cis_res
)paren
id|cb_release_cis_mem
c_func
(paren
id|s
)paren
suffix:semicolon
id|start
op_assign
id|res-&gt;start
suffix:semicolon
id|size
op_assign
id|res-&gt;end
op_minus
id|start
op_plus
l_int|1
suffix:semicolon
id|s-&gt;cb_cis_virt
op_assign
id|ioremap
c_func
(paren
id|start
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;cb_cis_virt
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|s-&gt;cb_cis_res
op_assign
id|res
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    This is used by the CIS processing code to read CIS information&n;    from a CardBus device.&n;    &n;=====================================================================*/
DECL|function|read_cb_mem
r_int
id|read_cb_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
id|space
comma
id|u_int
id|addr
comma
id|u_int
id|len
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|cs_dbg
c_func
(paren
id|s
comma
l_int|3
comma
l_string|&quot;read_cb_mem(%d, %#x, %u)&bslash;n&quot;
comma
id|space
comma
id|addr
comma
id|len
)paren
suffix:semicolon
id|dev
op_assign
id|pci_find_slot
c_func
(paren
id|s-&gt;cb_dev-&gt;subordinate-&gt;number
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* Config space? */
r_if
c_cond
(paren
id|space
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|addr
op_plus
id|len
OG
l_int|0x100
)paren
r_goto
id|fail
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
suffix:semicolon
id|addr
op_increment
comma
id|ptr
op_increment
comma
id|len
op_decrement
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|addr
comma
id|ptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|res
op_assign
id|dev-&gt;resource
op_plus
id|space
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res-&gt;flags
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|cb_setup_cis_mem
c_func
(paren
id|s
comma
id|res
)paren
op_ne
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|space
op_eq
l_int|7
)paren
(brace
id|addr
op_assign
id|xlate_rom_addr
c_func
(paren
id|s-&gt;cb_cis_virt
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_plus
id|len
OG
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
r_goto
id|fail
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|ptr
comma
id|s-&gt;cb_cis_virt
op_plus
id|addr
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|memset
c_func
(paren
id|ptr
comma
l_int|0xff
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*=====================================================================&n;&n;    cb_alloc() and cb_free() allocate and free the kernel data&n;    structures for a Cardbus device, and handle the lowest level PCI&n;    device setup issues.&n;    &n;=====================================================================*/
multiline_comment|/*&n; * Since there is only one interrupt available to CardBus&n; * devices, all devices downstream of this device must&n; * be using this IRQ.&n; */
DECL|function|cardbus_assign_irqs
r_static
r_void
id|cardbus_assign_irqs
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|irq
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
id|u8
id|irq_pin
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|irq_pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_pin
)paren
(brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;subordinate
)paren
id|cardbus_assign_irqs
c_func
(paren
id|dev-&gt;subordinate
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
DECL|function|cb_alloc
r_int
id|cb_alloc
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|s-&gt;cb_dev-&gt;subordinate
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
r_int
id|max
comma
id|pass
suffix:semicolon
id|s-&gt;functions
op_assign
id|pci_scan_slot
c_func
(paren
id|bus
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
suffix:semicolon
singleline_comment|//&t;pcibios_fixup_bus(bus);
id|max
op_assign
id|bus-&gt;secondary
suffix:semicolon
r_for
c_loop
(paren
id|pass
op_assign
l_int|0
suffix:semicolon
id|pass
OL
l_int|2
suffix:semicolon
id|pass
op_increment
)paren
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_BRIDGE
op_logical_or
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
id|max
op_assign
id|pci_scan_bridge
c_func
(paren
id|bus
comma
id|dev
comma
id|max
comma
id|pass
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Size all resources below the CardBus controller.&n;&t; */
id|pci_bus_size_bridges
c_func
(paren
id|bus
)paren
suffix:semicolon
id|pci_bus_assign_resources
c_func
(paren
id|bus
)paren
suffix:semicolon
id|cardbus_assign_irqs
c_func
(paren
id|bus
comma
id|s-&gt;pci_irq
)paren
suffix:semicolon
id|pci_enable_bridges
c_func
(paren
id|bus
)paren
suffix:semicolon
id|pci_bus_add_devices
c_func
(paren
id|bus
)paren
suffix:semicolon
id|s-&gt;irq.AssignedIRQ
op_assign
id|s-&gt;pci_irq
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
DECL|function|cb_free
r_void
id|cb_free
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|s-&gt;cb_dev
suffix:semicolon
id|cb_release_cis_mem
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge
)paren
id|pci_remove_behind_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
)brace
eof
