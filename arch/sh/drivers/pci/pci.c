multiline_comment|/* arch/sh/kernel/pci.c&n; * $Id: pci.c,v 1.1 2003/08/24 19:15:45 lethal Exp $&n; *&n; * Copyright (c) 2002 M. R. Brown  &lt;mrbrown@linux-sh.org&gt;&n; * &n; * &n; * These functions are collected here to reduce duplication of common&n; * code amongst the many platform-specific PCI support code files.&n; * &n; * These routines require the following board-specific routines:&n; * void pcibios_fixup_irqs();&n; *&n; * See include/asm-sh/pci.h for more information.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|pcibios_init
r_static
r_int
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
macro_line|#ifdef CONFIG_PCI_AUTO
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
id|board_pci_channels
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
macro_line|#endif
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
id|board_pci_channels
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
multiline_comment|/* board-specific fixups */
id|pcibios_fixup_irqs
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
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
id|u32
r_new
comma
id|check
suffix:semicolon
r_int
id|reg
suffix:semicolon
r_new
op_assign
id|res-&gt;start
op_or
(paren
id|res-&gt;flags
op_amp
id|PCI_REGION_FLAG_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource
OL
l_int|6
)paren
(brace
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
l_int|4
op_star
id|resource
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resource
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
id|res-&gt;flags
op_or_assign
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
r_new
op_or_assign
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
id|reg
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Somebody might have asked allocation of a non-standard resource */
r_return
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
r_new
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_new
op_xor
id|check
)paren
op_amp
(paren
(paren
r_new
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
ques
c_cond
id|PCI_BASE_ADDRESS_IO_MASK
suffix:colon
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error while updating region &quot;
l_string|&quot;%s/%d (%08x != %08x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|resource
comma
r_new
comma
id|check
)paren
suffix:semicolon
)brace
)brace
r_void
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
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * We need to avoid collisions with `mirrored&squot; VGA ports&n; * and other strange ISA hardware, so we always want the&n; * addresses to be allocated in the 0x000-0x0ff region&n; * modulo 0x400.&n; */
DECL|function|pcibios_align_resource
r_void
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
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
r_int
r_int
id|start
op_assign
id|res-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|start
op_amp
l_int|0x300
)paren
(brace
id|start
op_assign
(paren
id|start
op_plus
l_int|0x3ff
)paren
op_amp
op_complement
l_int|0x3ff
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
)brace
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
comma
r_int
id|mask
)paren
(brace
id|u16
id|cmd
comma
id|old_cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|old_cmd
op_assign
id|cmd
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|idx
)paren
)paren
)paren
r_continue
suffix:semicolon
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Device %s not available because &quot;
l_string|&quot;of resource collisions&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|old_cmd
comma
id|cmd
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  If we set up a device for bus mastering, we need to check and set&n; *  the latency timer as it may not be properly set.&n; */
DECL|variable|pcibios_max_latency
r_int
r_int
id|pcibios_max_latency
op_assign
l_int|255
suffix:semicolon
DECL|function|pcibios_set_master
r_void
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|lat
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lat
OL
l_int|16
)paren
id|lat
op_assign
(paren
l_int|64
op_le
id|pcibios_max_latency
)paren
ques
c_cond
l_int|64
suffix:colon
id|pcibios_max_latency
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lat
OG
id|pcibios_max_latency
)paren
id|lat
op_assign
id|pcibios_max_latency
suffix:semicolon
r_else
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Setting latency timer of device %s to %d&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|lat
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
id|lat
)paren
suffix:semicolon
)brace
DECL|function|pcibios_update_irq
r_void
id|__init
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
)brace
eof
