multiline_comment|/*&n; * arch/ppc/platforms/prpmc750_setup.c&n; *&n; * Board setup routines for Motorola PrPMC750&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
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
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/hawk.h&gt;
macro_line|#include &quot;prpmc750.h&quot;
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
DECL|variable|__initdata
r_static
id|u_char
id|prpmc750_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_HOSTINT0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_UART */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_DEBUGINT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_HAWK_WDT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_ABORT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_HOSTINT1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_HOSTINT2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_HOSTINT3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_PMC_INTA */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_PMC_INTB */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_PMC_INTC */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_PMC_INTD */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC750_INT_UNUSED */
)brace
suffix:semicolon
multiline_comment|/*&n; * Motorola PrPMC750/PrPMC800 in PrPMCBASE or PrPMC-Carrier&n; * Combined irq tables.  Only Base has IDSEL 14, only Carrier has 21 and 22.&n; */
r_static
r_inline
r_int
DECL|function|prpmc_map_irq
id|prpmc_map_irq
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
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; *      A       B       C       D&n;&t; */
(brace
(brace
l_int|12
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 14 - Ethernet, base */
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
multiline_comment|/* IDSEL 15 - unused */
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
multiline_comment|/* IDSEL 16 - PMC A1, PMC1 */
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
multiline_comment|/* IDSEL 17 - PrPMC-A-B, PMC2-B */
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
multiline_comment|/* IDSEL 18 - PMC A1-B, PMC1-B */
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
multiline_comment|/* IDSEL 19 - unused */
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
multiline_comment|/* IDSEL 20 - P2P Bridge */
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
multiline_comment|/* IDSEL 21 - PMC A2, carrier */
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
multiline_comment|/* IDSEL 22 - PMC A2-B, carrier */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|14
comma
id|max_idsel
op_assign
l_int|22
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
suffix:semicolon
DECL|function|prpmc750_pcibios_fixup
r_static
r_void
id|__init
id|prpmc750_pcibios_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
r_int
id|wtmp
suffix:semicolon
multiline_comment|/*&n;&t; * Kludge to clean up after PPC6BUG which doesn&squot;t&n;&t; * configure the CL5446 VGA card.  Also the&n;&t; * resource subsystem doesn&squot;t fixup the&n;&t; * PCI mem resources on the CL5446.&n;&t; */
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_VENDOR_ID_CIRRUS
comma
id|PCI_DEVICE_ID_CIRRUS_5446
comma
l_int|0
)paren
)paren
)paren
(brace
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_add_assign
id|PRPMC750_PCI_PHY_MEM_OFFSET
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_add_assign
id|PRPMC750_PCI_PHY_MEM_OFFSET
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|wtmp
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|wtmp
op_or
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Enable Color mode in MISC reg */
id|outb
c_func
(paren
l_int|0x03
comma
l_int|0x3c2
)paren
suffix:semicolon
multiline_comment|/* Select DRAM config reg */
id|outb
c_func
(paren
l_int|0x0f
comma
l_int|0x3c4
)paren
suffix:semicolon
multiline_comment|/* Set proper DRAM config */
id|outb
c_func
(paren
l_int|0xdf
comma
l_int|0x3c5
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|prpmc750_find_bridges
r_void
id|__init
id|prpmc750_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|hose
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
id|hose
)paren
r_return
suffix:semicolon
id|hose-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|hose-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|PRPMC750_ISA_IO_BASE
suffix:semicolon
id|hose-&gt;pci_mem_offset
op_assign
id|PRPMC750_PCI_PHY_MEM_OFFSET
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
id|PRPMC750_PCI_IO_START
comma
id|PRPMC750_PCI_IO_END
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
comma
id|PRPMC750_PROC_PCI_MEM_START
comma
id|PRPMC750_PROC_PCI_MEM_END
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|hose-&gt;io_space.start
op_assign
id|PRPMC750_PCI_IO_START
suffix:semicolon
id|hose-&gt;io_space.end
op_assign
id|PRPMC750_PCI_IO_END
suffix:semicolon
id|hose-&gt;mem_space.start
op_assign
id|PRPMC750_PCI_MEM_START
suffix:semicolon
id|hose-&gt;mem_space.end
op_assign
id|PRPMC750_PCI_MEM_END
op_minus
id|HAWK_MPIC_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|hawk_init
c_func
(paren
id|hose
comma
id|PRPMC750_HAWK_PPC_REG_BASE
comma
id|PRPMC750_PROC_PCI_MEM_START
comma
id|PRPMC750_PROC_PCI_MEM_END
op_minus
id|HAWK_MPIC_SIZE
comma
id|PRPMC750_PROC_PCI_IO_START
comma
id|PRPMC750_PROC_PCI_IO_END
comma
id|PRPMC750_PROC_PCI_MEM_END
op_minus
id|HAWK_MPIC_SIZE
op_plus
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Could not initialize host bridge&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|hose-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
)paren
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
id|prpmc750_pcibios_fixup
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|prpmc_map_irq
suffix:semicolon
)brace
DECL|function|prpmc750_show_cpuinfo
r_static
r_int
id|prpmc750_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: PrPMC750&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prpmc750_setup_arch
r_static
r_void
id|__init
id|prpmc750_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* Lookup PCI host bridges */
id|prpmc750_find_bridges
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
id|Root_SDA2
suffix:semicolon
macro_line|#endif
id|OpenPIC_InitSenses
op_assign
id|prpmc750_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|prpmc750_openpic_initsenses
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
)brace
multiline_comment|/*&n; * Compute the PrPMC750&squot;s bus speed using the baud clock as a&n; * reference.&n; */
DECL|function|prpmc750_get_bus_speed
r_static
r_int
r_int
id|__init
id|prpmc750_get_bus_speed
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tbl_start
comma
id|tbl_end
suffix:semicolon
r_int
r_int
id|current_state
comma
id|old_state
comma
id|bus_speed
suffix:semicolon
r_int
r_char
id|lcr
comma
id|dll
comma
id|dlm
suffix:semicolon
r_int
id|baud_divisor
comma
id|count
suffix:semicolon
multiline_comment|/* Read the UART&squot;s baud clock divisor */
id|lcr
op_assign
id|readb
c_func
(paren
id|PRPMC750_SERIAL_0_LCR
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|lcr
op_or
id|UART_LCR_DLAB
comma
id|PRPMC750_SERIAL_0_LCR
)paren
suffix:semicolon
id|dll
op_assign
id|readb
c_func
(paren
id|PRPMC750_SERIAL_0_DLL
)paren
suffix:semicolon
id|dlm
op_assign
id|readb
c_func
(paren
id|PRPMC750_SERIAL_0_DLM
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|lcr
op_amp
op_complement
id|UART_LCR_DLAB
comma
id|PRPMC750_SERIAL_0_LCR
)paren
suffix:semicolon
id|baud_divisor
op_assign
(paren
id|dlm
op_lshift
l_int|8
)paren
op_or
id|dll
suffix:semicolon
multiline_comment|/*&n;&t; * Use the baud clock divisor and base baud clock&n;&t; * to determine the baud rate and use that as&n;&t; * the number of baud clock edges we use for&n;&t; * the time base sample.  Make it half the baud&n;&t; * rate.&n;&t; */
id|count
op_assign
id|PRPMC750_BASE_BAUD
op_div
(paren
id|baud_divisor
op_star
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Find the first edge of the baud clock */
id|old_state
op_assign
id|readb
c_func
(paren
id|PRPMC750_STATUS_REG
)paren
op_amp
id|PRPMC750_BAUDOUT_MASK
suffix:semicolon
r_do
(brace
id|current_state
op_assign
id|readb
c_func
(paren
id|PRPMC750_STATUS_REG
)paren
op_amp
id|PRPMC750_BAUDOUT_MASK
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old_state
op_eq
id|current_state
)paren
suffix:semicolon
id|old_state
op_assign
id|current_state
suffix:semicolon
multiline_comment|/* Get the starting time base value */
id|tbl_start
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Loop until we have found a number of edges equal&n;&t; * to half the count (half the baud rate)&n;&t; */
r_do
(brace
r_do
(brace
id|current_state
op_assign
id|readb
c_func
(paren
id|PRPMC750_STATUS_REG
)paren
op_amp
id|PRPMC750_BAUDOUT_MASK
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old_state
op_eq
id|current_state
)paren
suffix:semicolon
id|old_state
op_assign
id|current_state
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|count
)paren
suffix:semicolon
multiline_comment|/* Get the ending time base value */
id|tbl_end
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Compute bus speed */
id|bus_speed
op_assign
(paren
id|tbl_end
op_minus
id|tbl_start
)paren
op_star
l_int|128
suffix:semicolon
r_return
id|bus_speed
suffix:semicolon
)brace
DECL|function|prpmc750_calibrate_decr
r_static
r_void
id|__init
id|prpmc750_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
r_int
id|divisor
op_assign
l_int|4
suffix:semicolon
id|freq
op_assign
id|prpmc750_get_bus_speed
c_func
(paren
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
(paren
id|HZ
op_star
id|divisor
)paren
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
DECL|function|prpmc750_restart
r_static
r_void
id|prpmc750_restart
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
id|writeb
c_func
(paren
id|PRPMC750_MODRST_MASK
comma
id|PRPMC750_MODRST_REG
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|prpmc750_halt
r_static
r_void
id|prpmc750_halt
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|prpmc750_power_off
r_static
r_void
id|prpmc750_power_off
c_func
(paren
r_void
)paren
(brace
id|prpmc750_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prpmc750_init_IRQ
r_static
r_void
id|__init
id|prpmc750_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|openpic_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space.&n; */
DECL|function|prpmc750_set_bat
r_static
id|__inline__
r_void
id|prpmc750_set_bat
c_func
(paren
r_void
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT1U
comma
l_int|0xf0001ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT1L
comma
l_int|0xf000002a
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to read the Falcon/Hawk memory controller&n; * to properly determine this value&n; */
DECL|function|prpmc750_find_end_of_memory
r_static
r_int
r_int
id|__init
id|prpmc750_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Read the memory size from the Hawk SMC */
r_return
id|hawk_get_mem_size
c_func
(paren
id|PRPMC750_HAWK_SMC_BASE
)paren
suffix:semicolon
)brace
DECL|function|prpmc750_map_io
r_static
r_void
id|__init
id|prpmc750_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|PRPMC750_ISA_IO_BASE
comma
id|PRPMC750_ISA_IO_BASE
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#if 0
id|io_block_mapping
c_func
(paren
l_int|0xf0000000
comma
l_int|0xc0000000
comma
l_int|0x08000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
macro_line|#endif
id|io_block_mapping
c_func
(paren
l_int|0xf8000000
comma
l_int|0xf8000000
comma
l_int|0x08000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|platform_init
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
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Cover the Hawk registers with a BAT */
id|prpmc750_set_bat
c_func
(paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|PRPMC750_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|PRPMC750_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|PRPMC750_PCI_DRAM_OFFSET
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|prpmc750_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|prpmc750_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|prpmc750_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|prpmc750_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|prpmc750_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|prpmc750_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|prpmc750_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|prpmc750_halt
suffix:semicolon
multiline_comment|/* PrPMC750 has no timekeeper part */
id|ppc_md.time_init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|prpmc750_calibrate_decr
suffix:semicolon
macro_line|#ifdef  CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_SERIAL_TEXT_DEBUG */
)brace
eof
