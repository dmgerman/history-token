multiline_comment|/*&n; *&t;Low-Level PCI Support for the SH7751&n; *&n; *  Dustin McIntire (dustin@sensoria.com)&n; *&t;Derived from arch/i386/kernel/pci-*.c which bore the message:&n; *&t;(c) 1999--2000 Martin Mares &lt;mj@ucw.cz&gt;&n; *&t;&n; *  May be copied or modified under the terms of the GNU General Public&n; *  License.  See linux/COPYING for more information.&n; *&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci-sh7751.h&gt;
r_struct
id|pci_ops
op_star
id|pci_check_direct
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pcibios_resource_survey
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|u8
id|pcibios_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
suffix:semicolon
r_static
r_int
id|pcibios_lookup_irq
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
suffix:semicolon
DECL|variable|pci_probe
r_int
r_int
id|pci_probe
op_assign
id|PCI_PROBE_BIOS
op_or
id|PCI_PROBE_CONF1
suffix:semicolon
DECL|variable|pcibios_last_bus
r_int
id|pcibios_last_bus
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|pci_root_bus
r_struct
id|pci_bus
op_star
id|pci_root_bus
suffix:semicolon
DECL|variable|pci_root_ops
r_struct
id|pci_ops
op_star
id|pci_root_ops
suffix:semicolon
multiline_comment|/*&n; * Direct access to PCI hardware...&n; */
macro_line|#ifdef CONFIG_PCI_DIRECT
DECL|macro|CONFIG_CMD
mdefine_line|#define CONFIG_CMD(bus, devfn, where) (0x80000000 | (bus-&gt;number &lt;&lt; 16) | (devfn &lt;&lt; 8) | (where &amp; ~3))
DECL|macro|PCI_REG
mdefine_line|#define PCI_REG(reg) (SH7751_PCIREG_BASE+reg)
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
multiline_comment|/* PCIPDR may only be accessed as 32 bit words, &n;     * so we must do byte alignment by hand &n;     */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outl
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
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
)paren
suffix:semicolon
id|word
op_assign
id|inl
c_func
(paren
id|PCI_REG
c_func
(paren
id|SH7751_PCIPDR
)paren
)paren
suffix:semicolon
id|restore_flags
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
multiline_comment|/*This should never happen.*/
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI BIOS: read_config: Illegal u16 alignment&quot;
)paren
suffix:semicolon
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
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
multiline_comment|/* &n; * Since SH7751 only does 32bit access we&squot;ll have to do a read,mask,write operation.  &n; * We&squot;ll allow an odd byte offset, though it should be illegal.&n; */
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outl
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
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
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
id|outl
c_func
(paren
id|value
comma
id|PCI_REG
c_func
(paren
id|SH7751_PCIPDR
)paren
)paren
suffix:semicolon
id|restore_flags
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
id|inl
c_func
(paren
id|PCI_REG
c_func
(paren
id|SH7751_PCIPDR
)paren
)paren
suffix:semicolon
id|word
op_and_assign
op_complement
id|mask
suffix:semicolon
id|word
op_or_assign
id|value
op_lshift
id|shift
suffix:semicolon
id|outl
c_func
(paren
id|word
comma
id|PCI_REG
c_func
(paren
id|SH7751_PCIPDR
)paren
)paren
suffix:semicolon
id|restore_flags
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
DECL|function|pci_check_direct
r_struct
id|pci_ops
op_star
id|__init
id|pci_check_direct
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
comma
id|id
suffix:semicolon
multiline_comment|/* check for SH7751 hardware */
id|id
op_assign
(paren
id|SH7751_DEVICE_ID
op_lshift
l_int|16
)paren
op_or
id|SH7751_VENDOR_ID
suffix:semicolon
r_if
c_cond
(paren
id|inl
c_func
(paren
id|SH7751_PCIREG_BASE
op_plus
id|SH7751_PCICONF0
)paren
op_ne
id|id
)paren
(brace
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;PCI: This is not an SH7751&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check if configuration works.&n;&t; */
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_PROBE_CONF1
)paren
(brace
id|tmp
op_assign
id|inl
(paren
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
)paren
suffix:semicolon
id|outl
(paren
l_int|0x80000000
comma
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inl
(paren
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
)paren
op_eq
l_int|0x80000000
)paren
(brace
id|outl
(paren
id|tmp
comma
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using configuration type 1&bslash;n&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
comma
l_int|8
comma
l_string|&quot;PCI conf1&quot;
)paren
suffix:semicolon
r_return
op_amp
id|pci_direct_conf1
suffix:semicolon
)brace
id|outl
(paren
id|tmp
comma
id|PCI_REG
c_func
(paren
id|SH7751_PCIPAR
)paren
)paren
suffix:semicolon
)brace
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;PCI: pci_check_direct failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * BIOS32 and PCI BIOS handling.&n; * &n; * The BIOS version of the pci functions is not yet implemented but it is left&n; * in for completeness.  Currently an error will be generated at compile time. &n; */
macro_line|#ifdef CONFIG_PCI_BIOS
macro_line|#error PCI BIOS is not yet supported on SH7751
macro_line|#endif /* CONFIG_PCI_BIOS */
multiline_comment|/***************************************************************************************/
multiline_comment|/*&n; *  Handle bus scanning and fixups ....&n; */
multiline_comment|/*&n; * Discover remaining PCI buses in case there are peer host bridges.&n; * We use the number of last PCI bus provided by the PCI BIOS.&n; */
DECL|function|pcibios_fixup_peer_bridges
r_static
r_void
id|__init
id|pcibios_fixup_peer_bridges
c_func
(paren
r_void
)paren
(brace
r_int
id|n
suffix:semicolon
r_struct
id|pci_bus
id|bus
suffix:semicolon
r_struct
id|pci_dev
id|dev
suffix:semicolon
id|u16
id|l
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_last_bus
op_le
l_int|0
op_logical_or
id|pcibios_last_bus
op_ge
l_int|0xff
)paren
r_return
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;PCI: Peer bridge fixup&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
op_le
id|pcibios_last_bus
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pci_bus_exists
c_func
(paren
op_amp
id|pci_root_buses
comma
id|n
)paren
)paren
r_continue
suffix:semicolon
id|bus.number
op_assign
id|n
suffix:semicolon
id|bus.ops
op_assign
id|pci_root_ops
suffix:semicolon
id|dev.bus
op_assign
op_amp
id|bus
suffix:semicolon
r_for
c_loop
(paren
id|dev.devfn
op_assign
l_int|0
suffix:semicolon
id|dev.devfn
OL
l_int|256
suffix:semicolon
id|dev.devfn
op_add_assign
l_int|8
)paren
r_if
c_cond
(paren
op_logical_neg
id|pci_read_config_word
c_func
(paren
op_amp
id|dev
comma
id|PCI_VENDOR_ID
comma
op_amp
id|l
)paren
op_logical_and
id|l
op_ne
l_int|0x0000
op_logical_and
id|l
op_ne
l_int|0xffff
)paren
(brace
id|PCIDBG
c_func
(paren
l_int|3
comma
l_string|&quot;Found device at %02x:%02x [%04x]&bslash;n&quot;
comma
id|n
comma
id|dev.devfn
comma
id|l
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Discovered peer bus %02x&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|n
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|pci_fixup_ide_bases
r_static
r_void
id|__init
id|pci_fixup_ide_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * PCI IDE controllers use non-standard I/O port decoding, respect it.&n;&t; */
r_if
c_cond
(paren
(paren
id|d
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_STORAGE_IDE
)paren
r_return
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|3
comma
l_string|&quot;PCI: IDE base address fixup for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|d-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
op_complement
l_int|0x80
)paren
op_eq
l_int|0x374
)paren
(brace
id|r-&gt;start
op_or_assign
l_int|2
suffix:semicolon
id|r-&gt;end
op_assign
id|r-&gt;start
suffix:semicolon
)brace
)brace
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
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pci_fixup_ide_bases
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
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
multiline_comment|/*&n; * Initialization. Try all known PCI access methods. Note that we support&n; * using both PCI BIOS and direct access: in such cases, we use I/O ports&n; * to access config space.&n; * &n; * Note that the platform specific initialization (BSC registers, and memory&n; * space mapping) will be called via the machine vectors (sh_mv.mv_pci_init()) if it&n; * exitst and via the platform defined function pcibios_init_platform().  &n; * See pci_bigsur.c for implementation;&n; * &n; * The BIOS version of the pci functions is not yet implemented but it is left&n; * in for completeness.  Currently an error will be genereated at compile time. &n; */
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
id|pci_ops
op_star
id|bios
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pci_ops
op_star
id|dir
op_assign
l_int|NULL
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|1
comma
l_string|&quot;PCI: Starting initialization.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_BIOS
r_if
c_cond
(paren
(paren
id|pci_probe
op_amp
id|PCI_PROBE_BIOS
)paren
op_logical_and
(paren
(paren
id|bios
op_assign
id|pci_find_bios
c_func
(paren
)paren
)paren
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_BIOS_SORT
suffix:semicolon
id|pci_bios_present
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PCI_DIRECT
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_PROBE_CONF1
)paren
id|dir
op_assign
id|pci_check_direct
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dir
)paren
(brace
id|pci_root_ops
op_assign
id|dir
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pcibios_init_platform
c_func
(paren
)paren
)paren
(brace
id|PCIDBG
c_func
(paren
l_int|1
comma
l_string|&quot;PCI: Initialization failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sh_mv.mv_init_pci
op_ne
l_int|NULL
)paren
id|sh_mv
dot
id|mv_init_pci
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bios
)paren
id|pci_root_ops
op_assign
id|bios
suffix:semicolon
r_else
(brace
id|PCIDBG
c_func
(paren
l_int|1
comma
l_string|&quot;PCI: No PCI bus detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|PCIDBG
c_func
(paren
l_int|1
comma
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
)paren
suffix:semicolon
id|pci_root_bus
op_assign
id|pci_scan_bus
c_func
(paren
l_int|0
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
singleline_comment|//pci_assign_unassigned_resources();
id|pci_fixup_irqs
c_func
(paren
id|pcibios_swizzle
comma
id|pcibios_lookup_irq
)paren
suffix:semicolon
id|pcibios_fixup_peer_bridges
c_func
(paren
)paren
suffix:semicolon
id|pcibios_resource_survey
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_BIOS
r_if
c_cond
(paren
(paren
id|pci_probe
op_amp
id|PCI_BIOS_SORT
)paren
op_logical_and
op_logical_neg
(paren
id|pci_probe
op_amp
id|PCI_NO_SORT
)paren
)paren
id|pcibios_sort
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI_BIOS
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;bios&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
id|PCI_PROBE_BIOS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;nobios&quot;
)paren
)paren
(brace
id|pci_probe
op_and_assign
op_complement
id|PCI_PROBE_BIOS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;nosort&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_NO_SORT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;biosirq&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_BIOS_IRQ_SCAN
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PCI_DIRECT
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;conf1&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
id|PCI_PROBE_CONF1
op_or
id|PCI_NO_CHECKS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;rom&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_ASSIGN_ROMS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;lastbus=&quot;
comma
l_int|8
)paren
)paren
(brace
id|pcibios_last_bus
op_assign
id|simple_strtol
c_func
(paren
id|str
op_plus
l_int|8
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|str
suffix:semicolon
)brace
multiline_comment|/*&n; *    Allocate the bridge and device resources&n; */
DECL|function|pcibios_allocate_bus_resources
r_static
r_void
id|__init
id|pcibios_allocate_bus_resources
c_func
(paren
r_struct
id|list_head
op_star
id|bus_list
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
comma
op_star
id|pr
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;PCI: pcibios_allocate_bus_reasources called&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Depth-First Search on bus tree */
r_for
c_loop
(paren
id|ln
op_assign
id|bus_list-&gt;next
suffix:semicolon
id|ln
op_ne
id|bus_list
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|bus-&gt;self
)paren
)paren
(brace
r_for
c_loop
(paren
id|idx
op_assign
id|PCI_BRIDGE_RESOURCES
suffix:semicolon
id|idx
OL
id|PCI_NUM_RESOURCES
suffix:semicolon
id|idx
op_increment
)paren
(brace
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
)paren
r_continue
suffix:semicolon
id|pr
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
id|request_resource
c_func
(paren
id|pr
comma
id|r
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Cannot allocate resource region %d of bridge %s&bslash;n&quot;
comma
id|idx
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
)brace
)brace
id|pcibios_allocate_bus_resources
c_func
(paren
op_amp
id|bus-&gt;children
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_allocate_resources
r_static
r_void
id|__init
id|pcibios_allocate_resources
c_func
(paren
r_int
id|pass
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|idx
comma
id|disabled
suffix:semicolon
id|u16
id|command
suffix:semicolon
r_struct
id|resource
op_star
id|r
comma
op_star
id|pr
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;PCI: pcibios_allocate_resources pass %d called&bslash;n&quot;
comma
id|pass
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
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
id|r-&gt;parent
)paren
multiline_comment|/* Already allocated */
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
)paren
multiline_comment|/* Address not assigned at all */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|disabled
op_assign
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_IO
)paren
suffix:semicolon
r_else
id|disabled
op_assign
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_MEMORY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pass
op_eq
id|disabled
)paren
(brace
id|PCIDBG
c_func
(paren
l_int|3
comma
l_string|&quot;PCI: Resource %08lx-%08lx (f=%lx, d=%d, p=%d)&bslash;n&quot;
comma
id|r-&gt;start
comma
id|r-&gt;end
comma
id|r-&gt;flags
comma
id|disabled
comma
id|pass
)paren
suffix:semicolon
id|pr
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
id|request_resource
c_func
(paren
id|pr
comma
id|r
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Cannot allocate resource region %d of device %s&bslash;n&quot;
comma
id|idx
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll assign a new address later */
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|pass
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|PCI_ROM_ADDRESS_ENABLE
)paren
(brace
multiline_comment|/* Turn the ROM off, leave the resource region, but keep it unregistered. */
id|u32
id|reg
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|3
comma
l_string|&quot;PCI: Switching off ROM of %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|r-&gt;flags
op_and_assign
op_complement
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|dev-&gt;rom_base_reg
comma
op_amp
id|reg
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|dev-&gt;rom_base_reg
comma
id|reg
op_amp
op_complement
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pcibios_assign_resources
r_static
r_void
id|__init
id|pcibios_assign_resources
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|devn
op_assign
l_int|NULL
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
id|PCIDBG
c_func
(paren
l_int|2
comma
l_string|&quot;PCI: pcibios_assign_resources called&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_class
op_assign
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
suffix:semicolon
multiline_comment|/* Don&squot;t touch classless devices and host bridges */
r_if
c_cond
(paren
op_logical_neg
r_class
op_logical_or
r_class
op_eq
id|PCI_CLASS_BRIDGE_HOST
)paren
r_continue
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
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  Don&squot;t touch IDE controllers and I/O ports of video cards!&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
r_class
op_eq
id|PCI_CLASS_STORAGE_IDE
op_logical_and
id|idx
OL
l_int|4
)paren
op_logical_or
(paren
r_class
op_eq
id|PCI_CLASS_DISPLAY_VGA
op_logical_and
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  We shall assign a new address to this resource, either because&n;&t;&t;&t; *  the BIOS forgot to do so or because we have decided the old&n;&t;&t;&t; *  address was unusable for some reason.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|idx
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_ASSIGN_ROMS
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;end
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|PCI_ROM_RESOURCE
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|pcibios_resource_survey
r_void
id|__init
id|pcibios_resource_survey
c_func
(paren
r_void
)paren
(brace
id|PCIDBG
c_func
(paren
l_int|1
comma
l_string|&quot;PCI: Allocating resources&bslash;n&quot;
)paren
suffix:semicolon
id|pcibios_allocate_bus_resources
c_func
(paren
op_amp
id|pci_root_buses
)paren
suffix:semicolon
id|pcibios_allocate_resources
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pcibios_allocate_resources
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|pcibios_assign_resources
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/***************************************************************************************/
multiline_comment|/* &n; * &t;IRQ functions &n; */
DECL|function|pcibios_swizzle
r_static
id|u8
id|__init
id|pcibios_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
(brace
multiline_comment|/* no swizzling */
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
DECL|function|pcibios_lookup_irq
r_static
r_int
id|pcibios_lookup_irq
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
id|irq
op_assign
id|pcibios_map_platform_irq
c_func
(paren
id|slot
comma
id|pin
)paren
suffix:semicolon
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
id|dev-&gt;name
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
id|dev-&gt;slot_name
comma
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
eof
