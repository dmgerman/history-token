multiline_comment|/*&n; *&t;Low-Level PCI Support for the MPC-1211(CTP/PCI/MPC-SH02)&n; *&n; *  (c) 2002-2003 Saito.K &amp; Jeanne&n; *&n; *  Dustin McIntire (dustin@sensoria.com)&n; *&t;Derived from arch/i386/kernel/pci-*.c which bore the message:&n; *&t;(c) 1999--2000 Martin Mares &lt;mj@ucw.cz&gt;&n; *&t;&n; *  May be copied or modified under the terms of the GNU General Public&n; *  License.  See linux/COPYING for more information.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mpc1211/pci.h&gt;
DECL|variable|mpcpci_io_resource
r_static
r_struct
id|resource
id|mpcpci_io_resource
op_assign
(brace
l_string|&quot;MPCPCI IO&quot;
comma
l_int|0x00000000
comma
l_int|0xffffffff
comma
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|mpcpci_mem_resource
r_static
r_struct
id|resource
id|mpcpci_mem_resource
op_assign
(brace
l_string|&quot;MPCPCI mem&quot;
comma
l_int|0x00000000
comma
l_int|0xffffffff
comma
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|pci_direct_conf1
r_static
r_struct
id|pci_ops
id|pci_direct_conf1
suffix:semicolon
DECL|variable|board_pci_channels
r_struct
id|pci_channel
id|board_pci_channels
(braket
)braket
op_assign
(brace
(brace
op_amp
id|pci_direct_conf1
comma
op_amp
id|mpcpci_io_resource
comma
op_amp
id|mpcpci_mem_resource
comma
l_int|0
comma
l_int|256
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Direct access to PCI hardware...&n; */
DECL|macro|CONFIG_CMD
mdefine_line|#define CONFIG_CMD(bus, devfn, where) (0x80000000 | (bus-&gt;number &lt;&lt; 16) | (devfn &lt;&lt; 8) | (where &amp; ~3))
multiline_comment|/*&n; * Functions for accessing PCI configuration space with type 1 accesses&n; */
DECL|function|pci_conf1_read
r_static
r_int
id|pci_conf1_read
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
id|u32
id|word
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* &n;&t; * PCIPDR may only be accessed as 32 bit words, &n;&t; * so we must do byte alignment by hand &n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|writel
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
id|PCIPAR
)paren
suffix:semicolon
id|word
op_assign
id|readl
c_func
(paren
id|PCIPDR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
r_switch
c_cond
(paren
id|where
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|3
suffix:colon
op_star
id|value
op_assign
(paren
id|u8
)paren
(paren
id|word
op_rshift
l_int|24
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|value
op_assign
(paren
id|u8
)paren
(paren
id|word
op_rshift
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
op_star
id|value
op_assign
(paren
id|u8
)paren
(paren
id|word
op_rshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|value
op_assign
(paren
id|u8
)paren
id|word
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_switch
c_cond
(paren
id|where
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|3
suffix:colon
op_star
id|value
op_assign
(paren
id|u16
)paren
(paren
id|word
op_rshift
l_int|24
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|writel
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
(paren
id|where
op_plus
l_int|1
)paren
)paren
comma
id|PCIPAR
)paren
suffix:semicolon
id|word
op_assign
id|readl
c_func
(paren
id|PCIPDR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|value
op_or_assign
(paren
(paren
id|word
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|value
op_assign
(paren
id|u16
)paren
(paren
id|word
op_rshift
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
op_star
id|value
op_assign
(paren
id|u16
)paren
(paren
id|word
op_rshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|value
op_assign
(paren
id|u16
)paren
id|word
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|value
op_assign
id|word
suffix:semicolon
r_break
suffix:semicolon
)brace
id|PCIDBG
c_func
(paren
l_int|4
comma
l_string|&quot;pci_conf1_read@0x%08x=0x%x&bslash;n&quot;
comma
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
op_star
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
multiline_comment|/* &n; * Since MPC-1211 only does 32bit access we&squot;ll have to do a read,mask,write operation.  &n; * We&squot;ll allow an odd byte offset, though it should be illegal.&n; */
DECL|function|pci_conf1_write
r_static
r_int
id|pci_conf1_write
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
id|u32
id|word
comma
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|shift
op_assign
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
(brace
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
l_int|8
)paren
op_minus
l_int|1
)paren
op_lshift
id|shift
suffix:semicolon
singleline_comment|// create the byte mask
)brace
r_else
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|shift
op_eq
l_int|24
)paren
(brace
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
)brace
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
l_int|16
)paren
op_minus
l_int|1
)paren
op_lshift
id|shift
suffix:semicolon
singleline_comment|// create the word mask
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|writel
c_func
(paren
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
id|PCIPAR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|4
)paren
(brace
id|writel
c_func
(paren
id|value
comma
id|PCIPDR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|4
comma
l_string|&quot;pci_conf1_write@0x%08x=0x%x&bslash;n&quot;
comma
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|word
op_assign
id|readl
c_func
(paren
id|PCIPDR
)paren
suffix:semicolon
id|word
op_and_assign
op_complement
id|mask
suffix:semicolon
id|word
op_or_assign
(paren
(paren
id|value
op_lshift
id|shift
)paren
op_amp
id|mask
)paren
suffix:semicolon
id|writel
c_func
(paren
id|word
comma
id|PCIPDR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|4
comma
l_string|&quot;pci_conf1_write@0x%08x=0x%x&bslash;n&quot;
comma
id|CONFIG_CMD
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
comma
id|word
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|macro|CONFIG_CMD
macro_line|#undef CONFIG_CMD
DECL|variable|pci_direct_conf1
r_static
r_struct
id|pci_ops
id|pci_direct_conf1
op_assign
(brace
dot
id|read
op_assign
id|pci_conf1_read
comma
dot
id|write
op_assign
id|pci_conf1_write
comma
)brace
suffix:semicolon
DECL|function|quirk_ali_ide_ports
r_static
r_void
id|__devinit
id|quirk_ali_ide_ports
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0x1f0
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
l_int|0x1f7
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_assign
l_int|0x3f6
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|end
op_assign
l_int|0x3f6
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
op_assign
l_int|0x170
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|end
op_assign
l_int|0x177
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|start
op_assign
l_int|0x376
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|end
op_assign
l_int|0x376
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|start
op_assign
l_int|0xf000
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|end
op_assign
l_int|0xf00f
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
)brace
multiline_comment|/* Add future fixups here... */
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M5229
comma
id|quirk_ali_ide_ports
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|pcibios_setup
r_char
op_star
id|__devinit
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
multiline_comment|/*&n; *  Called after each bus is probed, but before its children&n; *  are examined.&n; */
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
id|pci_read_bridge_bases
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * &t;IRQ functions &n; */
DECL|function|bridge_swizzle
r_static
r_inline
id|u8
id|bridge_swizzle
c_func
(paren
id|u8
id|pin
comma
id|u8
id|slot
)paren
(brace
r_return
(paren
(paren
(paren
id|pin
op_minus
l_int|1
)paren
op_plus
id|slot
)paren
op_mod
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|bridge_swizzle_pci_1
r_static
r_inline
id|u8
id|bridge_swizzle_pci_1
c_func
(paren
id|u8
id|pin
comma
id|u8
id|slot
)paren
(brace
r_return
(paren
(paren
(paren
id|pin
op_minus
l_int|1
)paren
op_minus
id|slot
)paren
op_amp
l_int|3
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|mpc1211_swizzle
r_static
id|u8
id|__init
id|mpc1211_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pinp
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
id|u32
id|word
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|dev-&gt;bus-&gt;self
suffix:semicolon
id|dev
op_assign
id|dev-&gt;bus-&gt;self
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pin
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|1
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x80000000
op_or
l_int|0x2c
comma
id|PCIPAR
)paren
suffix:semicolon
id|word
op_assign
id|readl
c_func
(paren
id|PCIPDR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|word
op_rshift_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|word
op_eq
l_int|0x0001
)paren
id|pin
op_assign
id|bridge_swizzle_pci_1
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_else
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
)brace
r_else
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
)brace
op_star
id|pinp
op_assign
id|pin
suffix:semicolon
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
DECL|function|map_mpc1211_irq
r_static
r_int
id|__init
id|map_mpc1211_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_int
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* now lookup the actual IRQ on a platform specific basis (pci-&squot;platform&squot;.c) */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|13
suffix:colon
id|irq
op_assign
l_int|9
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* USB */
r_case
l_int|22
suffix:colon
id|irq
op_assign
l_int|10
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* LAN */
r_default
suffix:colon
id|irq
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|0
suffix:colon
id|irq
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|irq
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|irq
op_assign
l_int|9
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irq
op_assign
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|irq
op_assign
l_int|11
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
(brace
id|PCIDBG
c_func
(paren
l_int|3
comma
l_string|&quot;PCI: Error mapping IRQ on device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting IRQ for slot %s to %d&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
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
id|pci_fixup_irqs
c_func
(paren
id|mpc1211_swizzle
comma
id|map_mpc1211_irq
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|start
op_assign
id|res-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
r_if
c_cond
(paren
id|start
op_ge
l_int|0x10000UL
)paren
(brace
r_if
c_cond
(paren
(paren
id|start
op_amp
l_int|0xffffUL
)paren
OL
l_int|0x4000UL
)paren
(brace
id|start
op_assign
(paren
id|start
op_amp
l_int|0xffff0000UL
)paren
op_plus
l_int|0x4000UL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|start
op_amp
l_int|0xffffUL
)paren
op_ge
l_int|0xf000UL
)paren
(brace
id|start
op_assign
(paren
id|start
op_amp
l_int|0xffff0000UL
)paren
op_plus
l_int|0x10000UL
suffix:semicolon
)brace
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
r_else
(brace
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
)brace
eof
