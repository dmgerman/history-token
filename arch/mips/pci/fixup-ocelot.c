multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/gt64120/momenco_ocelot/pci.c&n; *     Board-specific PCI routines for gt64120 controller.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
DECL|function|pcibios_fixup_bus
r_void
id|__devinit
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_bus
op_star
id|current_bus
op_assign
id|bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|devices
suffix:semicolon
r_struct
id|list_head
op_star
id|devices_link
suffix:semicolon
id|u16
id|cmd
suffix:semicolon
id|list_for_each
c_func
(paren
id|devices_link
comma
op_amp
(paren
id|current_bus-&gt;devices
)paren
)paren
(brace
id|devices
op_assign
id|pci_dev_b
c_func
(paren
id|devices_link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devices
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|devices-&gt;devfn
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Slot 1 is primary ether port, i82559&n;&t;&t;&t; * we double-check against that assumption&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|devices-&gt;vendor
op_ne
l_int|0x8086
)paren
op_logical_or
(paren
id|devices-&gt;device
op_ne
l_int|0x1209
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;pcibios_fixup_bus: found &quot;
l_string|&quot;unexpected PCI device in slot 1.&quot;
)paren
suffix:semicolon
)brace
id|devices-&gt;irq
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* irq_nr is 2 for INT0 */
)brace
r_else
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|devices-&gt;devfn
)paren
op_eq
l_int|2
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Slot 2 is secondary ether port, i21143&n;&t;&t;&t; * we double-check against that assumption&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|devices-&gt;vendor
op_ne
l_int|0x1011
)paren
op_logical_or
(paren
id|devices-&gt;device
op_ne
l_int|0x19
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;galileo_pcibios_fixup_bus: &quot;
l_string|&quot;found unexpected PCI device in slot 2.&quot;
)paren
suffix:semicolon
)brace
id|devices-&gt;irq
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* irq_nr is 3 for INT1 */
)brace
r_else
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|devices-&gt;devfn
)paren
op_eq
l_int|4
)paren
(brace
multiline_comment|/* PMC Slot 1 */
id|devices-&gt;irq
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* irq_nr is 8 for INT6 */
)brace
r_else
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|devices-&gt;devfn
)paren
op_eq
l_int|5
)paren
(brace
multiline_comment|/* PMC Slot 1 */
id|devices-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* irq_nr is 9 for INT7 */
)brace
r_else
(brace
multiline_comment|/* We don&squot;t have assign interrupts for other devices. */
id|devices-&gt;irq
op_assign
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* Assign an interrupt number for the device */
id|bus-&gt;ops
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|devices
comma
id|PCI_INTERRUPT_LINE
comma
id|devices-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* enable master */
id|bus-&gt;ops
op_member_access_from_pointer
id|read_word
c_func
(paren
id|devices
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|cmd
op_or_assign
id|PCI_COMMAND_MASTER
suffix:semicolon
id|bus-&gt;ops
op_member_access_from_pointer
id|write_word
c_func
(paren
id|devices
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
)brace
eof
