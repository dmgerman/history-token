multiline_comment|/***********************************************************************&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/ddb5xxx/common/pci.c&n; *     Common PCI routines for DDB5xxx - as a matter of fact, meant for all &n; *&t;MIPS machines.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; ***********************************************************************&n; */
multiline_comment|/*&n; * This file contains common PCI routines meant to be shared for&n; * all MIPS machines.&n; *&n; * Strategies:&n; *&n; * . We rely on pci_auto.c file to assign PCI resources (MEM and IO)&n; *   TODO: this shold be optional for some machines where they do have&n; *   a real &quot;pcibios&quot; that does resource assignment.&n; *&n; * . We then use pci_scan_bus() to &quot;discover&quot; all the resources for&n; *   later use by Linux.&n; *&n; * . We finally reply on a board supplied function, pcibios_fixup_irq(), to &n; *   to assign the interrupts.  We may use setup-irq.c under drivers/pci&n; *   later.&n; *&n; * . Specifically, we will *NOT* use pci_assign_unassigned_resources(),&n; *   because we assume all PCI devices should have the resources correctly&n; *   assigned and recorded.&n; *&n; * Limitations:&n; *&n; * . We &quot;collapse&quot; all IO and MEM spaces in sub-buses under a top-level bus &n; *   into a contiguous range.  &n; * &n; * . In the case of Memory space, the rnage is 1:1 mapping with CPU physical&n; *   address space.&n; *&n; * . In the case of IO space, it starts from 0, and the beginning address&n; *   is mapped to KSEG0ADDR(mips_io_port) in the CPU physical address.&n; *&n; * . These are the current MIPS limitations (by ioremap, etc).  In the&n; *   future, we may remove them.&n; *&n; * Credits:&n; *&t;Most of the code are derived from the pci routines from PPC and Alpha,&n; *&t;which were mostly writtne by&n; *&t;&t;Cort Dougan, cort@fsmlabs.com&n; *&t;&t;Matt Porter, mporter@mvista.com&n; *&t;&t;Dave Rusling david.rusling@reo.mts.dec.com&n; *&t;&t;David Mosberger davidm@cs.arizona.edu&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/ddb5xxx/pci.h&gt;
macro_line|#include &lt;asm/ddb5xxx/debug.h&gt;
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_extern
r_int
id|pciauto_assign_resources
c_func
(paren
r_int
id|busno
comma
r_struct
id|pci_channel
op_star
id|hose
)paren
suffix:semicolon
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_channel
op_star
id|p
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_int
id|busno
suffix:semicolon
multiline_comment|/* assign resources */
id|busno
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|mips_pci_channels
suffix:semicolon
id|p-&gt;pci_ops
op_ne
l_int|NULL
suffix:semicolon
id|p
op_increment
)paren
(brace
id|busno
op_assign
id|pciauto_assign_resources
c_func
(paren
id|busno
comma
id|p
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* scan the buses */
id|busno
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|mips_pci_channels
suffix:semicolon
id|p-&gt;pci_ops
op_ne
l_int|NULL
suffix:semicolon
id|p
op_increment
)paren
(brace
id|bus
op_assign
id|pci_scan_bus
c_func
(paren
id|busno
comma
id|p-&gt;pci_ops
comma
id|p
)paren
suffix:semicolon
id|busno
op_assign
id|bus-&gt;subordinate
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* fixup irqs (board specific routines) */
id|pcibios_fixup_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * should we do a fixup of ioport_resource and iomem_resource&n;&t; * based on mips_pci_channels?  &n;&t; * Let us wait and see if this is a common need and whether there&n;&t; * are exceptions.  Until then, each board should adjust them&n;&t; * perhaps in their setup() function.&n;&t; */
)brace
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* pciauto_assign_resources() will enable all devices found */
r_return
l_int|0
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|pci_bridge_check_io
id|pci_bridge_check_io
c_func
(paren
r_struct
id|pci_dev
op_star
id|bridge
)paren
(brace
id|u16
id|io
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
op_amp
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io
)paren
(brace
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
l_int|0xf0f0
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
op_amp
id|io
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|io
)paren
r_return
id|IORESOURCE_IO
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: bridge %s does not support I/O forwarding!&bslash;n&quot;
comma
id|bridge-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
multiline_comment|/* Propogate hose info into the subordinate devices.  */
r_struct
id|pci_channel
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|bus-&gt;self
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
multiline_comment|/* Root bus */
id|bus-&gt;resource
(braket
l_int|0
)braket
op_assign
id|hose-&gt;io_resource
suffix:semicolon
id|bus-&gt;resource
(braket
l_int|1
)braket
op_assign
id|hose-&gt;mem_resource
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is a bridge. Do not care how it&squot;s initialized,&n;                   just link its resources to the bus ones */
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bus-&gt;resource
(braket
id|i
)braket
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_BRIDGE_RESOURCES
op_plus
id|i
)braket
suffix:semicolon
id|bus-&gt;resource
(braket
id|i
)braket
op_member_access_from_pointer
id|name
op_assign
id|bus-&gt;name
suffix:semicolon
)brace
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|flags
op_or_assign
id|pci_bridge_check_io
c_func
(paren
id|dev
)paren
suffix:semicolon
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|flags
op_or_assign
id|IORESOURCE_MEM
suffix:semicolon
multiline_comment|/* For now, propagate hose limits to the bus;&n;                   we&squot;ll adjust them later. */
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|end
op_assign
id|hose-&gt;io_resource-&gt;end
suffix:semicolon
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|end
op_assign
id|hose-&gt;mem_resource-&gt;end
suffix:semicolon
multiline_comment|/* Turn off downstream PF memory address range by default */
id|bus-&gt;resource
(braket
l_int|2
)braket
op_member_access_from_pointer
id|start
op_assign
l_int|1024
op_star
l_int|1024
suffix:semicolon
id|bus-&gt;resource
(braket
l_int|2
)braket
op_member_access_from_pointer
id|end
op_assign
id|bus-&gt;resource
(braket
l_int|2
)braket
op_member_access_from_pointer
id|start
op_minus
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|pcibios_setup
r_char
op_star
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|str
suffix:semicolon
)brace
r_void
DECL|function|pcibios_align_resource
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
multiline_comment|/* this should not be called */
id|MIPS_ASSERT
c_func
(paren
l_int|1
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|pcibios_update_resource
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
id|res
comma
r_int
id|resource
)paren
(brace
multiline_comment|/* this should not be called */
id|MIPS_ASSERT
c_func
(paren
l_int|1
op_eq
l_int|0
)paren
suffix:semicolon
)brace
eof
