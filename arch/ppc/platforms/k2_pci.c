multiline_comment|/*&n; * arch/ppc/platforms/k2_pci.c&n; * &n; * PCI support for SBS K2&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;syslib/cpc710.h&gt;
macro_line|#include &quot;k2.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif /* DEBUG */
r_static
r_inline
r_int
id|__init
DECL|function|k2_map_irq
id|k2_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|pci_bus_to_hose
c_func
(paren
id|dev-&gt;bus-&gt;number
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check our hose index.  If we are zero then we are on the&n;&t; * local PCI hose, otherwise we are on the cPCI hose.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|hose-&gt;index
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;&t;&t; * &t;PCI IDSEL/INTPIN-&gt;INTLINE &n;&t;&t;&t; * &t;A&t;B&t;C&t;D&n;&t;&t;&t; */
(brace
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Ethernet */
(brace
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
)brace
comma
multiline_comment|/* PMC Site 1 */
(brace
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
)brace
comma
multiline_comment|/* PMC Site 2 */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PCI-ISA Bridge */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
(brace
l_int|15
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* M5229 IDE */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|3
comma
id|max_idsel
op_assign
l_int|17
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_else
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;&t; * &t;PCI IDSEL/INTPIN-&gt;INTLINE &n;&t;&t; * &t;A&t;B&t;C&t;D&n;&t;&t; */
(brace
(brace
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|9
)brace
comma
multiline_comment|/* cPCI slot 8 */
(brace
l_int|11
comma
l_int|12
comma
l_int|9
comma
l_int|10
)brace
comma
multiline_comment|/* cPCI slot 7 */
(brace
l_int|12
comma
l_int|9
comma
l_int|10
comma
l_int|11
)brace
comma
multiline_comment|/* cPCI slot 6 */
(brace
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
)brace
comma
multiline_comment|/* cPCI slot 5 */
(brace
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|9
)brace
comma
multiline_comment|/* cPCI slot 4 */
(brace
l_int|11
comma
l_int|12
comma
l_int|9
comma
l_int|10
)brace
comma
multiline_comment|/* cPCI slot 3 */
(brace
l_int|12
comma
l_int|9
comma
l_int|10
comma
l_int|11
)brace
comma
multiline_comment|/* cPCI slot 2 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|15
comma
id|max_idsel
op_assign
l_int|21
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
)brace
DECL|function|k2_pcibios_fixup
r_void
id|k2_pcibios_fixup
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
r_struct
id|pci_dev
op_star
id|ide_dev
suffix:semicolon
multiline_comment|/*&n;&t; * Enable DMA support on hdc&n;&t; */
id|ide_dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M5229
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_dev
)paren
(brace
r_int
r_int
id|ide_dma_base
suffix:semicolon
id|ide_dma_base
op_assign
id|pci_resource_start
c_func
(paren
id|ide_dev
comma
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|ide_dma_base
op_plus
l_int|0x2
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x20
comma
id|ide_dma_base
op_plus
l_int|0xa
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|k2_pcibios_fixup_resources
r_void
id|k2_pcibios_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_IBM
)paren
op_logical_and
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_IBM_CPC710_PCI64
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Fixup CPC710 resources&bslash;n&quot;
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
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|k2_setup_hoses
r_void
id|k2_setup_hoses
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose_a
comma
op_star
id|hose_b
suffix:semicolon
multiline_comment|/*&n;&t; * Reconfigure CPC710 memory map so&n;&t; * we have some more PCI memory space.&n;&t; */
multiline_comment|/* Set FPHB mode */
id|__raw_writel
c_func
(paren
l_int|0x808000e0
comma
id|PGCHP
)paren
suffix:semicolon
multiline_comment|/* Set FPHB mode */
multiline_comment|/* PCI32 mappings */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI32_BAR
op_plus
id|PIBAR
)paren
suffix:semicolon
multiline_comment|/* PCI I/O base */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI32_BAR
op_plus
id|PMBAR
)paren
suffix:semicolon
multiline_comment|/* PCI Mem base */
id|__raw_writel
c_func
(paren
l_int|0xf0000000
comma
id|K2_PCI32_BAR
op_plus
id|MSIZE
)paren
suffix:semicolon
multiline_comment|/* 256MB */
id|__raw_writel
c_func
(paren
l_int|0xfff00000
comma
id|K2_PCI32_BAR
op_plus
id|IOSIZE
)paren
suffix:semicolon
multiline_comment|/* 1MB */
id|__raw_writel
c_func
(paren
l_int|0xc0000000
comma
id|K2_PCI32_BAR
op_plus
id|SMBAR
)paren
suffix:semicolon
multiline_comment|/* Base@0xc0000000 */
id|__raw_writel
c_func
(paren
l_int|0x80000000
comma
id|K2_PCI32_BAR
op_plus
id|SIBAR
)paren
suffix:semicolon
multiline_comment|/* Base@0x80000000 */
id|__raw_writel
c_func
(paren
l_int|0x000000c0
comma
id|K2_PCI32_BAR
op_plus
id|PSSIZE
)paren
suffix:semicolon
multiline_comment|/* 1GB space */
id|__raw_writel
c_func
(paren
l_int|0x000000c0
comma
id|K2_PCI32_BAR
op_plus
id|PPSIZE
)paren
suffix:semicolon
multiline_comment|/* 1GB space */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI32_BAR
op_plus
id|BARPS
)paren
suffix:semicolon
multiline_comment|/* Base@0x00000000 */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI32_BAR
op_plus
id|BARPP
)paren
suffix:semicolon
multiline_comment|/* Base@0x00000000 */
id|__raw_writel
c_func
(paren
l_int|0x00000080
comma
id|K2_PCI32_BAR
op_plus
id|PSBAR
)paren
suffix:semicolon
multiline_comment|/* Base@0x80 */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI32_BAR
op_plus
id|PPBAR
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0xc0000000
comma
id|K2_PCI32_BAR
op_plus
id|BPMDLK
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0xd0000000
comma
id|K2_PCI32_BAR
op_plus
id|TPMDLK
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0x80000000
comma
id|K2_PCI32_BAR
op_plus
id|BIODLK
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0x80100000
comma
id|K2_PCI32_BAR
op_plus
id|TIODLK
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0xe0008000
comma
id|K2_PCI32_BAR
op_plus
id|DLKCTRL
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0xffffffff
comma
id|K2_PCI32_BAR
op_plus
id|DLKDEV
)paren
suffix:semicolon
multiline_comment|/* PCI64 mappings */
id|__raw_writel
c_func
(paren
l_int|0x00100000
comma
id|K2_PCI64_BAR
op_plus
id|PIBAR
)paren
suffix:semicolon
multiline_comment|/* PCI I/O base */
id|__raw_writel
c_func
(paren
l_int|0x10000000
comma
id|K2_PCI64_BAR
op_plus
id|PMBAR
)paren
suffix:semicolon
multiline_comment|/* PCI Mem base */
id|__raw_writel
c_func
(paren
l_int|0xf0000000
comma
id|K2_PCI64_BAR
op_plus
id|MSIZE
)paren
suffix:semicolon
multiline_comment|/* 256MB */
id|__raw_writel
c_func
(paren
l_int|0xfff00000
comma
id|K2_PCI64_BAR
op_plus
id|IOSIZE
)paren
suffix:semicolon
multiline_comment|/* 1MB */
id|__raw_writel
c_func
(paren
l_int|0xd0000000
comma
id|K2_PCI64_BAR
op_plus
id|SMBAR
)paren
suffix:semicolon
multiline_comment|/* Base@0xd0000000 */
id|__raw_writel
c_func
(paren
l_int|0x80100000
comma
id|K2_PCI64_BAR
op_plus
id|SIBAR
)paren
suffix:semicolon
multiline_comment|/* Base@0x80100000 */
id|__raw_writel
c_func
(paren
l_int|0x000000c0
comma
id|K2_PCI64_BAR
op_plus
id|PSSIZE
)paren
suffix:semicolon
multiline_comment|/* 1GB space */
id|__raw_writel
c_func
(paren
l_int|0x000000c0
comma
id|K2_PCI64_BAR
op_plus
id|PPSIZE
)paren
suffix:semicolon
multiline_comment|/* 1GB space */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI64_BAR
op_plus
id|BARPS
)paren
suffix:semicolon
multiline_comment|/* Base@0x00000000 */
id|__raw_writel
c_func
(paren
l_int|0x00000000
comma
id|K2_PCI64_BAR
op_plus
id|BARPP
)paren
suffix:semicolon
multiline_comment|/* Base@0x00000000 */
multiline_comment|/* Setup PCI32 hose */
id|hose_a
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose_a
)paren
r_return
suffix:semicolon
id|hose_a-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose_a-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|hose_a-&gt;pci_mem_offset
op_assign
id|K2_PCI32_MEM_BASE
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose_a-&gt;io_resource
comma
id|K2_PCI32_LOWER_IO
comma
id|K2_PCI32_UPPER_IO
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI32 host bridge&quot;
)paren
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
comma
id|K2_PCI32_LOWER_MEM
op_plus
id|K2_PCI32_MEM_BASE
comma
id|K2_PCI32_UPPER_MEM
op_plus
id|K2_PCI32_MEM_BASE
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI32 host bridge&quot;
)paren
suffix:semicolon
id|hose_a-&gt;io_space.start
op_assign
id|K2_PCI32_LOWER_IO
suffix:semicolon
id|hose_a-&gt;io_space.end
op_assign
id|K2_PCI32_UPPER_IO
suffix:semicolon
id|hose_a-&gt;mem_space.start
op_assign
id|K2_PCI32_LOWER_MEM
suffix:semicolon
id|hose_a-&gt;mem_space.end
op_assign
id|K2_PCI32_UPPER_MEM
suffix:semicolon
id|hose_a-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|K2_ISA_IO_BASE
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose_a
comma
id|K2_PCI32_CONFIG_ADDR
comma
id|K2_PCI32_CONFIG_DATA
)paren
suffix:semicolon
multiline_comment|/* Initialize PCI32 bus registers */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|CPC710_BUS_NUMBER
comma
id|hose_a-&gt;first_busno
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|CPC710_SUB_BUS_NUMBER
comma
id|hose_a-&gt;last_busno
)paren
suffix:semicolon
multiline_comment|/* Enable PCI interrupt polling */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x45
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Route polled PCI interrupts */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x48
comma
l_int|0x58
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x49
comma
l_int|0x07
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x4a
comma
l_int|0x31
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x4b
comma
l_int|0xb9
)paren
suffix:semicolon
multiline_comment|/* route secondary IDE channel interrupt to IRQ 15 */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x75
comma
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* enable IDE controller IDSEL */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|8
comma
l_int|0
)paren
comma
l_int|0x58
comma
l_int|0x48
)paren
suffix:semicolon
multiline_comment|/* Enable IDE function */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|17
comma
l_int|0
)paren
comma
l_int|0x50
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Set M5229 IDE controller to native mode */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|17
comma
l_int|0
)paren
comma
id|PCI_CLASS_PROG
comma
l_int|0xdf
)paren
suffix:semicolon
id|hose_a-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
)paren
suffix:semicolon
multiline_comment|/* Write out correct max subordinate bus number for hose A */
id|early_write_config_byte
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|CPC710_SUB_BUS_NUMBER
comma
id|hose_a-&gt;last_busno
)paren
suffix:semicolon
multiline_comment|/* Only setup PCI64 hose if we are in the system slot */
r_if
c_cond
(paren
op_logical_neg
(paren
id|readb
c_func
(paren
id|K2_MISC_REG
)paren
op_amp
id|K2_SYS_SLOT_MASK
)paren
)paren
(brace
multiline_comment|/* Setup PCI64 hose */
id|hose_b
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose_b
)paren
r_return
suffix:semicolon
id|hose_b-&gt;first_busno
op_assign
id|hose_a-&gt;last_busno
op_plus
l_int|1
suffix:semicolon
id|hose_b-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Reminder: quit changing the following, it is correct. */
id|hose_b-&gt;pci_mem_offset
op_assign
id|K2_PCI32_MEM_BASE
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose_b-&gt;io_resource
comma
id|K2_PCI64_LOWER_IO
comma
id|K2_PCI64_UPPER_IO
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI64 host bridge&quot;
)paren
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose_b-&gt;mem_resources
(braket
l_int|0
)braket
comma
id|K2_PCI64_LOWER_MEM
op_plus
id|K2_PCI32_MEM_BASE
comma
id|K2_PCI64_UPPER_MEM
op_plus
id|K2_PCI32_MEM_BASE
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI64 host bridge&quot;
)paren
suffix:semicolon
id|hose_b-&gt;io_space.start
op_assign
id|K2_PCI64_LOWER_IO
suffix:semicolon
id|hose_b-&gt;io_space.end
op_assign
id|K2_PCI64_UPPER_IO
suffix:semicolon
id|hose_b-&gt;mem_space.start
op_assign
id|K2_PCI64_LOWER_MEM
suffix:semicolon
id|hose_b-&gt;mem_space.end
op_assign
id|K2_PCI64_UPPER_MEM
suffix:semicolon
id|hose_b-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|K2_ISA_IO_BASE
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose_b
comma
id|K2_PCI64_CONFIG_ADDR
comma
id|K2_PCI64_CONFIG_DATA
)paren
suffix:semicolon
multiline_comment|/* Initialize PCI64 bus registers */
id|early_write_config_byte
c_func
(paren
id|hose_b
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|CPC710_SUB_BUS_NUMBER
comma
l_int|0xff
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose_b
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|CPC710_BUS_NUMBER
comma
id|hose_b-&gt;first_busno
)paren
suffix:semicolon
id|hose_b-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose_b
comma
id|hose_b-&gt;first_busno
)paren
suffix:semicolon
multiline_comment|/* Write out correct max subordinate bus number for hose B */
id|early_write_config_byte
c_func
(paren
id|hose_b
comma
id|hose_b-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|CPC710_SUB_BUS_NUMBER
comma
id|hose_b-&gt;last_busno
)paren
suffix:semicolon
multiline_comment|/* Configure PCI64 PSBAR */
id|early_write_config_dword
c_func
(paren
id|hose_b
comma
id|hose_b-&gt;first_busno
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|PCI_BASE_ADDRESS_0
comma
id|K2_PCI64_SYS_MEM_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/* Configure i8259 level/edge settings */
id|outb
c_func
(paren
l_int|0x62
comma
l_int|0x4d0
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xde
comma
l_int|0x4d1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPC710_DATA_GATHERING
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|__raw_readl
c_func
(paren
id|ABCNTL
)paren
suffix:semicolon
multiline_comment|/* Enable data gathering on both PCI interfaces */
id|__raw_writel
c_func
(paren
id|tmp
op_or
l_int|0x05000000
comma
id|ABCNTL
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ppc_md.pcibios_fixup
op_assign
id|k2_pcibios_fixup
suffix:semicolon
id|ppc_md.pcibios_fixup_resources
op_assign
id|k2_pcibios_fixup_resources
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|k2_map_irq
suffix:semicolon
)brace
eof
