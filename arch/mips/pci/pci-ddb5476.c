macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/pci_channel.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
DECL|variable|extpci_io_resource
r_static
r_struct
id|resource
id|extpci_io_resource
op_assign
(brace
l_string|&quot;pci IO space&quot;
comma
l_int|0x1000
comma
multiline_comment|/* leave some room for ISA bus */
id|DDB_PCI_IO_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|extpci_mem_resource
r_static
r_struct
id|resource
id|extpci_mem_resource
op_assign
(brace
l_string|&quot;pci memory space&quot;
comma
id|DDB_PCI_MEM_BASE
op_plus
l_int|0x00100000
comma
multiline_comment|/* leave 1 MB for RTC */
id|DDB_PCI_MEM_BASE
op_plus
id|DDB_PCI_MEM_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_MEM
)brace
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|ddb5476_ext_pci_ops
suffix:semicolon
DECL|variable|mips_pci_channels
r_struct
id|pci_channel
id|mips_pci_channels
(braket
)braket
op_assign
(brace
(brace
op_amp
id|ddb5476_ext_pci_ops
comma
op_amp
id|extpci_io_resource
comma
op_amp
id|extpci_mem_resource
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * we fix up irqs based on the slot number.&n; * The first entry is at AD:11.&n; *&n; * This does not work for devices on sub-buses yet.&n; */
multiline_comment|/*&n; * temporary&n; */
DECL|macro|PCI_EXT_INTA
mdefine_line|#define&t;&t;PCI_EXT_INTA&t;&t;8
DECL|macro|PCI_EXT_INTB
mdefine_line|#define&t;&t;PCI_EXT_INTB&t;&t;9
DECL|macro|PCI_EXT_INTC
mdefine_line|#define&t;&t;PCI_EXT_INTC&t;&t;10
DECL|macro|PCI_EXT_INTD
mdefine_line|#define&t;&t;PCI_EXT_INTD&t;&t;11
DECL|macro|PCI_EXT_INTE
mdefine_line|#define&t;&t;PCI_EXT_INTE&t;&t;12
multiline_comment|/*&n; * based on ddb5477 manual page 11&n; */
DECL|macro|MAX_SLOT_NUM
mdefine_line|#define&t;&t;MAX_SLOT_NUM&t;&t;21
DECL|variable|irq_map
r_static
r_int
r_char
id|irq_map
(braket
id|MAX_SLOT_NUM
)braket
op_assign
(brace
multiline_comment|/* SLOT:  0, AD:11 */
l_int|0xff
comma
multiline_comment|/* SLOT:  1, AD:12 */
l_int|0xff
comma
multiline_comment|/* SLOT:  2, AD:13 */
l_int|9
comma
multiline_comment|/* USB */
multiline_comment|/* SLOT:  3, AD:14 */
l_int|10
comma
multiline_comment|/* PMU */
multiline_comment|/* SLOT:  4, AD:15 */
l_int|0xff
comma
multiline_comment|/* SLOT:  5, AD:16 */
l_int|0x0
comma
multiline_comment|/* P2P bridge */
multiline_comment|/* SLOT:  6, AD:17 */
id|nile4_to_irq
c_func
(paren
id|PCI_EXT_INTB
)paren
comma
multiline_comment|/* SLOT:  7, AD:18 */
id|nile4_to_irq
c_func
(paren
id|PCI_EXT_INTC
)paren
comma
multiline_comment|/* SLOT:  8, AD:19 */
id|nile4_to_irq
c_func
(paren
id|PCI_EXT_INTD
)paren
comma
multiline_comment|/* SLOT:  9, AD:20 */
id|nile4_to_irq
c_func
(paren
id|PCI_EXT_INTA
)paren
comma
multiline_comment|/* SLOT: 10, AD:21 */
l_int|0xff
comma
multiline_comment|/* SLOT: 11, AD:22 */
l_int|0xff
comma
multiline_comment|/* SLOT: 12, AD:23 */
l_int|0xff
comma
multiline_comment|/* SLOT: 13, AD:24 */
l_int|14
comma
multiline_comment|/* HD controller, M5229 */
multiline_comment|/* SLOT: 14, AD:25 */
l_int|0xff
comma
multiline_comment|/* SLOT: 15, AD:26 */
l_int|0xff
comma
multiline_comment|/* SLOT: 16, AD:27 */
l_int|0xff
comma
multiline_comment|/* SLOT: 17, AD:28 */
l_int|0xff
comma
multiline_comment|/* SLOT: 18, AD:29 */
l_int|0xff
comma
multiline_comment|/* SLOT: 19, AD:30 */
l_int|0xff
comma
multiline_comment|/* SLOT: 20, AD:31 */
l_int|0xff
)brace
suffix:semicolon
r_extern
r_int
id|vrc5477_irq_to_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
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
l_int|NULL
suffix:semicolon
r_int
id|slot_num
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
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t do IRQ fixup for sub-bus yet */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;parent
op_ne
l_int|NULL
)paren
(brace
id|db_run
c_func
(paren
id|printk
(paren
l_string|&quot;Don&squot;t know how to fixup irq for PCI device %d on sub-bus %d&bslash;n&quot;
comma
id|slot_num
comma
id|dev-&gt;bus-&gt;number
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|db_assert
c_func
(paren
id|slot_num
OL
id|MAX_SLOT_NUM
)paren
suffix:semicolon
id|db_assert
c_func
(paren
id|irq_map
(braket
id|slot_num
)braket
op_ne
l_int|0xff
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq_map
(braket
id|slot_num
)braket
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq_map
(braket
id|slot_num
)braket
suffix:semicolon
)brace
)brace
macro_line|#if defined(CONFIG_RUNTIME_DEBUG)
r_extern
r_void
id|jsun_scan_pci_bus
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|ddb_pci_reset_bus
r_void
id|__init
id|ddb_pci_reset_bus
c_func
(paren
r_void
)paren
(brace
id|u32
id|temp
suffix:semicolon
multiline_comment|/*&n;&t; * I am not sure about the &quot;official&quot; procedure, the following&n;&t; * steps work as far as I know:&n;&t; * We first set PCI cold reset bit (bit 31) in PCICTRL-H.&n;&t; * Then we clear the PCI warm reset bit (bit 30) to 0 in PCICTRL-H.&n;&t; * The same is true for both PCI channels.&n;&t; */
id|temp
op_assign
id|ddb_in32
c_func
(paren
id|DDB_PCICTRL
op_plus
l_int|4
)paren
suffix:semicolon
id|temp
op_or_assign
l_int|0x80000000
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_PCICTRL
op_plus
l_int|4
comma
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
l_int|0xc0000000
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_PCICTRL
op_plus
l_int|4
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|pcibios_assign_all_busses
r_int
id|__init
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we hope pci_auto has assigned the bus numbers to all buses */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pcibios_fixup_resources
r_void
id|__init
id|pcibios_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pcibios_fixup
r_void
id|__init
id|pcibios_fixup
c_func
(paren
r_void
)paren
(brace
)brace
eof
