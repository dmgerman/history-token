multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000, 2001 Keith M Wesolowski&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/ip32/mace.h&gt;
macro_line|#include &lt;asm/ip32/crime.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|DEBUG_MACE_PCI
macro_line|#undef DEBUG_MACE_PCI
multiline_comment|/*&n; * O2 has up to 5 PCI devices connected into the MACE bridge.  The device&n; * map looks like this:&n; *&n; * 0  aic7xxx 0&n; * 1  aic7xxx 1&n; * 2  expansion slot&n; * 3  N/C&n; * 4  N/C&n; */
DECL|macro|chkslot
mdefine_line|#define chkslot(dev)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((dev)-&gt;bus-&gt;number &gt; 0 || PCI_SLOT ((dev)-&gt;devfn) &lt; 1&t;&bslash;&n;&t;    || PCI_SLOT ((dev)-&gt;devfn) &gt; 3)&t;&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_DEVICE_NOT_FOUND;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|mkaddr
mdefine_line|#define mkaddr(dev, where) &bslash;&n;((((dev)-&gt;devfn &amp; 0xffUL) &lt;&lt; 8) | ((where) &amp; 0xfcUL))
r_void
id|macepci_error
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|macepci_read_config_byte
r_static
r_int
id|macepci_read_config_byte
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|val
)paren
(brace
op_star
id|val
op_assign
l_int|0xff
suffix:semicolon
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_ADDR
comma
id|mkaddr
(paren
id|dev
comma
id|where
)paren
)paren
suffix:semicolon
op_star
id|val
op_assign
id|mace_read_8
(paren
id|MACEPCI_CONFIG_DATA
op_plus
(paren
(paren
id|where
op_amp
l_int|3UL
)paren
op_xor
l_int|3UL
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|macepci_read_config_word
r_static
r_int
id|macepci_read_config_word
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|val
)paren
(brace
op_star
id|val
op_assign
l_int|0xffff
suffix:semicolon
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_ADDR
comma
id|mkaddr
(paren
id|dev
comma
id|where
)paren
)paren
suffix:semicolon
op_star
id|val
op_assign
id|mace_read_16
(paren
id|MACEPCI_CONFIG_DATA
op_plus
(paren
(paren
id|where
op_amp
l_int|2UL
)paren
op_xor
l_int|2UL
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|macepci_read_config_dword
r_static
r_int
id|macepci_read_config_dword
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
(brace
op_star
id|val
op_assign
l_int|0xffffffff
suffix:semicolon
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_ADDR
comma
id|mkaddr
(paren
id|dev
comma
id|where
)paren
)paren
suffix:semicolon
op_star
id|val
op_assign
id|mace_read_32
(paren
id|MACEPCI_CONFIG_DATA
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|macepci_write_config_byte
r_static
r_int
id|macepci_write_config_byte
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|val
)paren
(brace
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_ADDR
comma
id|mkaddr
(paren
id|dev
comma
id|where
)paren
)paren
suffix:semicolon
id|mace_write_8
(paren
id|MACEPCI_CONFIG_DATA
op_plus
(paren
(paren
id|where
op_amp
l_int|3UL
)paren
op_xor
l_int|3UL
)paren
comma
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|macepci_write_config_word
r_static
r_int
id|macepci_write_config_word
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|val
)paren
(brace
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_ADDR
comma
id|mkaddr
(paren
id|dev
comma
id|where
)paren
)paren
suffix:semicolon
id|mace_write_16
(paren
id|MACEPCI_CONFIG_DATA
op_plus
(paren
(paren
id|where
op_amp
l_int|2UL
)paren
op_xor
l_int|2UL
)paren
comma
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|macepci_write_config_dword
r_static
r_int
id|macepci_write_config_dword
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|val
)paren
(brace
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_ADDR
comma
id|mkaddr
(paren
id|dev
comma
id|where
)paren
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONFIG_DATA
comma
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|macepci_ops
r_static
r_struct
id|pci_ops
id|macepci_ops
op_assign
(brace
id|macepci_read_config_byte
comma
id|macepci_read_config_word
comma
id|macepci_read_config_dword
comma
id|macepci_write_config_byte
comma
id|macepci_write_config_word
comma
id|macepci_write_config_dword
)brace
suffix:semicolon
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
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|u32
id|start
comma
id|size
suffix:semicolon
id|u16
id|cmd
suffix:semicolon
id|u32
id|base_io
op_assign
l_int|0x3000
suffix:semicolon
multiline_comment|/* The first i/o address to assign after SCSI */
id|u32
id|base_mem
op_assign
l_int|0x80100000
suffix:semicolon
multiline_comment|/* Likewise */
id|u32
id|rev
op_assign
id|mace_read_32
(paren
id|MACEPCI_REV
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
(paren
l_string|&quot;MACE: PCI rev %d detected at %016lx&bslash;n&quot;
comma
id|rev
comma
(paren
id|u64
)paren
id|MACE_BASE
op_plus
id|MACE_PCI
)paren
suffix:semicolon
multiline_comment|/* These are *bus* addresses */
id|ioport_resource.start
op_assign
l_int|0
suffix:semicolon
id|ioport_resource.end
op_assign
l_int|0xffffffffUL
suffix:semicolon
id|iomem_resource.start
op_assign
l_int|0x80000000UL
suffix:semicolon
id|iomem_resource.end
op_assign
l_int|0xffffffffUL
suffix:semicolon
multiline_comment|/* Clear any outstanding errors and enable interrupts */
id|mace_write_32
(paren
id|MACEPCI_ERROR_ADDR
comma
l_int|0
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
l_int|0
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_CONTROL
comma
l_int|0xff008500
)paren
suffix:semicolon
id|crime_write_64
(paren
id|CRIME_HARD_INT
comma
l_int|0UL
)paren
suffix:semicolon
id|crime_write_64
(paren
id|CRIME_SOFT_INT
comma
l_int|0UL
)paren
suffix:semicolon
id|crime_write_64
(paren
id|CRIME_INT_STAT
comma
l_int|0x000000000000ff00UL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
(paren
id|MACE_PCI_BRIDGE_IRQ
comma
id|macepci_error
comma
l_int|0
comma
l_string|&quot;MACE PCI error&quot;
comma
l_int|NULL
)paren
)paren
id|panic
(paren
l_string|&quot;PCI bridge can&squot;t get interrupt; can&squot;t happen.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_scan_bus
(paren
l_int|0
comma
op_amp
id|macepci_ops
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_MACE_PCI
id|pci_for_each_dev
(paren
id|dev
)paren
(brace
id|printk
(paren
l_string|&quot;Device: %d/%d/%d ARCS-assigned bus resource map&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
(paren
id|dev-&gt;devfn
)paren
)paren
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
id|DEVICE_COUNT_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|printk
(paren
l_string|&quot;%d: %016lx - %016lx (flags %04lx)&bslash;n&quot;
comma
id|i
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Assign sane resources to and enable all devices.  The requirement&n;&t; * for the SCSI controllers is well-known: a 256-byte I/O region&n;&t; * which we must assign, and a 1-page memory region which is&n;&t; * assigned by the system firmware.&n;&t; */
id|pci_for_each_dev
(paren
id|dev
)paren
(brace
r_switch
c_cond
(paren
id|PCI_SLOT
(paren
id|dev-&gt;devfn
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* SCSI bus 0 */
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0x1000UL
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
l_int|0x10ffUL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* SCSI bus 1 */
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0x2000UL
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
l_int|0x20ffUL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Slots - I guess we have only 1 */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|size
op_assign
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_minus
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
op_logical_neg
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
(paren
id|IORESOURCE_IO
op_or
id|IORESOURCE_MEM
)paren
)paren
)paren
(brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
l_int|0UL
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|base_io
suffix:semicolon
id|base_io
op_add_assign
id|PAGE_ALIGN
(paren
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|base_mem
suffix:semicolon
id|base_mem
op_add_assign
l_int|0x100000UL
suffix:semicolon
)brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_plus
id|size
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
id|start
op_or_assign
l_int|1
suffix:semicolon
id|pci_write_config_dword
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|i
op_lshift
l_int|2
)paren
comma
(paren
id|u32
)paren
id|start
)paren
suffix:semicolon
)brace
id|pci_write_config_byte
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0x20
)paren
suffix:semicolon
id|pci_write_config_byte
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x30
)paren
suffix:semicolon
id|pci_read_config_word
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|cmd
op_or_assign
(paren
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_PARITY
)paren
suffix:semicolon
id|pci_write_config_word
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
id|pci_set_master
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_MACE_PCI
id|printk
(paren
l_string|&quot;Triggering PCI bridge interrupt...&bslash;n&quot;
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|MACEPCI_ERROR_INTERRUPT_TEST
)paren
suffix:semicolon
id|pci_for_each_dev
(paren
id|dev
)paren
(brace
id|printk
(paren
l_string|&quot;Device: %d/%d/%d final bus resource map&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
(paren
id|dev-&gt;devfn
)paren
)paren
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
id|DEVICE_COUNT_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|printk
(paren
l_string|&quot;%d: %016lx - %016lx (flags %04lx)&bslash;n&quot;
comma
id|i
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * Given a PCI slot number (a la PCI_SLOT(...)) and the interrupt pin of&n; * the device (1-4 =&gt; A-D), tell what irq to use.  Note that we don&squot;t&n; * in theory have slots 4 and 5, and we never normally use the shared&n; * irqs.  I suppose a device without a pin A will thank us for doing it&n; * right if there exists such a broken piece of crap.&n; */
DECL|function|macepci_map_irq
r_static
r_int
id|__init
id|macepci_map_irq
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
id|chkslot
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pin
op_eq
l_int|0
)paren
id|pin
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|MACEPCI_SCSI0_IRQ
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
id|MACEPCI_SCSI1_IRQ
suffix:semicolon
r_case
l_int|3
suffix:colon
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|2
suffix:colon
r_return
id|MACEPCI_SHARED0_IRQ
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
id|MACEPCI_SHARED1_IRQ
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
id|MACEPCI_SHARED2_IRQ
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
r_return
id|MACEPCI_SLOT0_IRQ
suffix:semicolon
)brace
r_case
l_int|4
suffix:colon
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|2
suffix:colon
r_return
id|MACEPCI_SHARED2_IRQ
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
id|MACEPCI_SHARED0_IRQ
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
id|MACEPCI_SHARED1_IRQ
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
r_return
id|MACEPCI_SLOT1_IRQ
suffix:semicolon
)brace
r_return
id|MACEPCI_SLOT1_IRQ
suffix:semicolon
r_case
l_int|5
suffix:colon
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|2
suffix:colon
r_return
id|MACEPCI_SHARED1_IRQ
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
id|MACEPCI_SHARED2_IRQ
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
id|MACEPCI_SHARED0_IRQ
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
r_return
id|MACEPCI_SLOT2_IRQ
suffix:semicolon
)brace
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * It&squot;s not entirely clear what this does in a system with no bridges.&n; * In any case, bridges are not supported by Linux in O2.&n; */
DECL|function|macepci_swizzle
r_static
id|u8
id|__init
id|macepci_swizzle
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
r_if
c_cond
(paren
id|PCI_SLOT
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|2
)paren
op_star
id|pinp
op_assign
l_int|2
suffix:semicolon
r_else
op_star
id|pinp
op_assign
l_int|1
suffix:semicolon
r_return
id|PCI_SLOT
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
multiline_comment|/* All devices are enabled during initialization. */
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
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
DECL|function|pcibios_align_resource
r_void
id|__init
id|pcibios_align_resource
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
)brace
DECL|function|pcibios_update_resource
r_void
id|__init
id|pcibios_update_resource
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
)brace
DECL|function|pcibios_update_irq
r_void
id|__init
id|pcibios_update_irq
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
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
id|pci_fixup_irqs
(paren
id|macepci_swizzle
comma
id|macepci_map_irq
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX anybody know what this is supposed to do? */
DECL|function|pcibios_fixup_pbus_ranges
r_void
id|__init
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|ranges
)paren
(brace
)brace
multiline_comment|/*&n; * Handle errors from the bridge.  This includes master and target aborts,&n; * various command and address errors, and the interrupt test.  This gets&n; * registered on the bridge error irq.  It&squot;s conceivable that some of these&n; * conditions warrant a panic.  Anybody care to say which ones?&n; */
DECL|function|macepci_error
r_void
id|macepci_error
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|flags
comma
id|error_addr
suffix:semicolon
r_char
id|space
suffix:semicolon
id|flags
op_assign
id|mace_read_32
(paren
id|MACEPCI_ERROR_FLAGS
)paren
suffix:semicolon
id|error_addr
op_assign
id|mace_read_32
(paren
id|MACEPCI_ERROR_ADDR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_MEMORY_ADDR
)paren
id|space
op_assign
l_char|&squot;M&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_CONFIG_ADDR
)paren
id|space
op_assign
l_char|&squot;C&squot;
suffix:semicolon
r_else
id|space
op_assign
l_char|&squot;X&squot;
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_MASTER_ABORT
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Master abort at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_MASTER_ABORT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_TARGET_ABORT
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Target abort at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_TARGET_ABORT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_DATA_PARITY_ERR
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Data parity error at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_DATA_PARITY_ERR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_RETRY_ERR
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Retry error at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_RETRY_ERR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_ILLEGAL_CMD
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Illegal command at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_ILLEGAL_CMD
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_SYSTEM_ERR
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: System error at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_SYSTEM_ERR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_PARITY_ERR
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Parity error at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_PARITY_ERR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_OVERRUN
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Overrun error at 0x%08x (%c)&bslash;n&quot;
comma
id|error_addr
comma
id|space
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_OVERRUN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_SIG_TABORT
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Signaled target abort (clearing)&bslash;n&quot;
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_SIG_TABORT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MACEPCI_ERROR_INTERRUPT_TEST
)paren
(brace
id|printk
(paren
l_string|&quot;MACEPCI: Interrupt test triggered (clearing)&bslash;n&quot;
)paren
suffix:semicolon
id|mace_write_32
(paren
id|MACEPCI_ERROR_FLAGS
comma
id|flags
op_amp
op_complement
id|MACEPCI_ERROR_INTERRUPT_TEST
)paren
suffix:semicolon
)brace
)brace
eof
