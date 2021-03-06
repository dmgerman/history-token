multiline_comment|/*&n; * arch/ppc/platforms/k2.c&n; *&n; * Board setup routines for SBS K2&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Updated by: Randy Vinson &lt;rvinson@mvista.com.&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;syslib/cpc710.h&gt;
macro_line|#include &quot;k2.h&quot;
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
r_extern
r_void
id|gen550_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|cpu_7xx
r_static
r_int
r_int
id|cpu_7xx
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|15
comma
l_int|14
comma
l_int|0
comma
l_int|0
comma
l_int|13
comma
l_int|5
comma
l_int|9
comma
l_int|6
comma
l_int|11
comma
l_int|8
comma
l_int|10
comma
l_int|16
comma
l_int|12
comma
l_int|7
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|cpu_6xx
r_static
r_int
r_int
id|cpu_6xx
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|0
comma
l_int|13
comma
l_int|5
comma
l_int|9
comma
l_int|6
comma
l_int|11
comma
l_int|8
comma
l_int|10
comma
l_int|0
comma
l_int|12
comma
l_int|7
comma
l_int|0
)brace
suffix:semicolon
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
multiline_comment|/*&n;&t;&t;&t; * &t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t;&t; * &t;A&t;B&t;C&t;D&n;&t;&t;&t; */
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
multiline_comment|/*&n;&t;&t; * &t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; * &t;A&t;B&t;C&t;D&n;&t;&t; */
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
id|pci_get_device
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
id|pci_dev_put
c_func
(paren
id|ide_dev
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
id|pr_debug
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
DECL|function|k2_get_bus_speed
r_static
r_int
id|k2_get_bus_speed
c_func
(paren
r_void
)paren
(brace
r_int
id|bus_speed
suffix:semicolon
r_int
r_char
id|board_id
suffix:semicolon
id|board_id
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|K2_BOARD_ID_REG
suffix:semicolon
r_switch
c_cond
(paren
id|K2_BUS_SPD
c_func
(paren
id|board_id
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_default
suffix:colon
id|bus_speed
op_assign
l_int|100000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|bus_speed
op_assign
l_int|83333333
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|bus_speed
op_assign
l_int|75000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|bus_speed
op_assign
l_int|66666666
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|bus_speed
suffix:semicolon
)brace
DECL|function|k2_get_cpu_speed
r_static
r_int
id|k2_get_cpu_speed
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid1
suffix:semicolon
r_int
id|cpu_speed
suffix:semicolon
id|hid1
op_assign
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
op_rshift
l_int|28
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
op_rshift
l_int|16
)paren
op_eq
l_int|8
)paren
id|hid1
op_assign
id|cpu_7xx
(braket
id|hid1
)braket
suffix:semicolon
r_else
id|hid1
op_assign
id|cpu_6xx
(braket
id|hid1
)braket
suffix:semicolon
id|cpu_speed
op_assign
id|k2_get_bus_speed
c_func
(paren
)paren
op_star
id|hid1
op_div
l_int|2
suffix:semicolon
r_return
id|cpu_speed
suffix:semicolon
)brace
DECL|function|k2_calibrate_decr
r_static
r_void
id|__init
id|k2_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
id|freq
comma
id|divisor
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* determine processor bus speed */
id|freq
op_assign
id|k2_get_bus_speed
c_func
(paren
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
op_div
id|divisor
comma
l_int|1000000
)paren
suffix:semicolon
)brace
DECL|function|k2_show_cpuinfo
r_static
r_int
id|k2_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_int
r_char
id|k2_geo_bits
comma
id|k2_system_slot
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: SBS&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: K2&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu speed&bslash;t: %dMhz&bslash;n&quot;
comma
id|k2_get_cpu_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bus speed&bslash;t: %dMhz&bslash;n&quot;
comma
id|k2_get_bus_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;memory type&bslash;t: SDRAM&bslash;n&quot;
)paren
suffix:semicolon
id|k2_geo_bits
op_assign
id|readb
c_func
(paren
id|K2_MSIZ_GEO_REG
)paren
op_amp
id|K2_GEO_ADR_MASK
suffix:semicolon
id|k2_system_slot
op_assign
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
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;backplane&bslash;t: %s slot board&quot;
comma
id|k2_system_slot
ques
c_cond
l_string|&quot;System&quot;
suffix:colon
l_string|&quot;Non system&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;with geographical address %x&bslash;n&quot;
comma
id|k2_geo_bits
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
DECL|function|k2_setup_arch
r_static
r_void
id|__init
id|k2_setup_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* Setup TODC access */
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T37
comma
l_int|0
comma
l_int|0
comma
id|ioremap
c_func
(paren
id|K2_RTC_BASE_ADDRESS
comma
id|K2_RTC_SIZE
)paren
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* make FLASH transactions higher priority than PCI to avoid deadlock */
id|__raw_writel
c_func
(paren
id|__raw_readl
c_func
(paren
id|SIOC1
)paren
op_or
l_int|0x80000000
comma
id|SIOC1
)paren
suffix:semicolon
multiline_comment|/* Set hardware to access FLASH page 2 */
id|__raw_writel
c_func
(paren
l_int|1
op_lshift
l_int|29
comma
id|GPOUT
)paren
suffix:semicolon
multiline_comment|/* Setup PCI host bridges */
id|k2_setup_hoses
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
macro_line|#ifdef CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_HDC1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;System Identification: SBS K2 - PowerPC 750 @ &quot;
l_string|&quot;%d Mhz&bslash;n&quot;
comma
id|k2_get_cpu_speed
c_func
(paren
)paren
op_div
l_int|1000000
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Port by MontaVista Software, Inc. &quot;
l_string|&quot;(source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Identify the CPU manufacturer */
id|cpu
op_assign
id|PVR_REV
c_func
(paren
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU manufacturer: %s [rev=%04x]&bslash;n&quot;
comma
(paren
id|cpu
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
ques
c_cond
l_string|&quot;IBM&quot;
suffix:colon
l_string|&quot;Motorola&quot;
comma
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|k2_restart
r_static
r_void
id|k2_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flip FLASH back to page 1 to access firmware image */
id|__raw_writel
c_func
(paren
l_int|0
comma
id|GPOUT
)paren
suffix:semicolon
multiline_comment|/* SRR0 has system reset vector, SRR1 has default MSR value */
multiline_comment|/* rfi restores MSR from SRR1 and sets the PC to the SRR0 value */
id|mtspr
c_func
(paren
id|SPRN_SRR0
comma
l_int|0xfff00100
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_SRR1
comma
l_int|0
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rfi&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
multiline_comment|/* not reached */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|k2_power_off
r_static
r_void
id|k2_power_off
c_func
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|k2_halt
r_static
r_void
id|k2_halt
c_func
(paren
r_void
)paren
(brace
id|k2_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map PCI32 I/O space.&n; */
DECL|function|k2_set_bat
r_static
id|__inline__
r_void
id|k2_set_bat
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* wait for all outstanding memory accesses to complete */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup DBATs */
id|mtspr
c_func
(paren
id|SPRN_DBAT2U
comma
l_int|0x80001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT2L
comma
l_int|0x8000002a
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT3U
comma
l_int|0xf0001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT3L
comma
l_int|0xf000002a
)paren
suffix:semicolon
multiline_comment|/* wait for updates */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|k2_find_end_of_memory
r_static
r_int
r_int
id|__init
id|k2_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|total
suffix:semicolon
r_int
r_char
id|msize
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* Default to 128MB */
id|msize
op_assign
id|K2_MEM_SIZE
c_func
(paren
id|readb
c_func
(paren
id|K2_MSIZ_GEO_REG
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|msize
)paren
(brace
r_case
l_int|2
suffix:colon
multiline_comment|/*&n;&t;&t; * This will break without a lowered&n;&t;&t; * KERNELBASE or CONFIG_HIGHMEM on.&n;&t;&t; * It seems non 1GB builds exist yet,&n;&t;&t; * though.&n;&t;&t; */
id|total
op_assign
id|K2_MEM_SIZE_1GB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
id|total
op_assign
id|K2_MEM_SIZE_512MB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
id|total
op_assign
id|K2_MEM_SIZE_256MB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|total
op_assign
id|K2_MEM_SIZE_128MB
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;K2: Invalid memory size detected, defaulting to 128MB&bslash;n&quot;
)paren
suffix:semicolon
id|total
op_assign
id|K2_MEM_SIZE_128MB
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|total
suffix:semicolon
)brace
DECL|function|k2_map_io
r_static
r_void
id|__init
id|k2_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|K2_PCI32_IO_BASE
comma
id|K2_PCI32_IO_BASE
comma
l_int|0x00200000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
l_int|0xff000000
comma
l_int|0xff000000
comma
l_int|0x01000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
DECL|function|k2_init_irq
r_static
r_void
id|__init
id|k2_init_irq
c_func
(paren
r_void
)paren
(brace
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
id|i8259_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|platform_init
r_void
id|__init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|parse_bootinfo
c_func
(paren
(paren
r_struct
id|bi_record
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
id|k2_set_bat
c_func
(paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|K2_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|K2_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|K2_PCI32_SYS_MEM_BASE
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|k2_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|k2_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|k2_init_irq
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|i8259_irq
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|k2_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|k2_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|k2_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|k2_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|k2_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|k2_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#endif
)brace
eof
