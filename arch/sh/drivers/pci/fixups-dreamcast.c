multiline_comment|/*&n; * arch/sh/pci/fixups-dreamcast.c&n; *&n; * PCI fixups for the Sega Dreamcast&n; *&n; * Copyright (C) 2001, 2002  M. R. Brown&n; * Copyright (C) 2002, 2003  Paul Mundt&n; *&n; * This file originally bore the message (with enclosed-$):&n; *&t;Id: pci.c,v 1.3 2003/05/04 19:29:46 lethal Exp&n; *&t;Dreamcast PCI: Supports SEGA Broadband Adaptor only.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
DECL|function|gapspci_fixup_resources
r_static
r_void
id|__init
id|gapspci_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_channel
op_star
id|p
op_assign
id|board_pci_channels
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;PCI: Fixing up device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_SEGA_BBA
suffix:colon
multiline_comment|/*&n;&t;&t; * We also assume that dev-&gt;devfn == 0&n;&t;&t; */
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_assign
id|p-&gt;io_resource-&gt;start
op_plus
l_int|0x100
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|end
op_assign
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_plus
l_int|0x200
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PCI: Failed resource fixup&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|DECLARE_PCI_FIXUP_HEADER
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|gapspci_fixup_resources
)paren
suffix:semicolon
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
multiline_comment|/* &n;&t; * We don&squot;t have any sub bus to fix up, and this is a rather&n;&t; * stupid place to put general device fixups. Don&squot;t do it.&n;&t; * Use the pcibios_fixups table or suffer the consequences.&n;&t; */
)brace
DECL|function|pcibios_fixup_irqs
r_void
id|__init
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|0
suffix:semicolon
id|for_each_pci_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * The interrupt routing semantics here are quite trivial.&n;&t;&t; *&n;&t;&t; * We basically only support one interrupt, so we only bother&n;&t;&t; * updating a device&squot;s interrupt line with this single shared&n;&t;&t; * interrupt. Keeps routing quite simple, doesn&squot;t it?&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;PCI: Fixing up IRQ routing for device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|GAPSPCI_IRQ
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
)brace
eof
