multiline_comment|/*&n; * arch/ppc/platforms/prpmc800.c&n; *&n; * Author: Dale Farnsworth &lt;dale.farnsworth@mvista.com&gt;&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
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
macro_line|#include &lt;linux/harrier_defs.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/harrier.h&gt;
macro_line|#include &quot;prpmc800.h&quot;
DECL|macro|HARRIER_REVI_REG
mdefine_line|#define HARRIER_REVI_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_REVI_OFF)
DECL|macro|HARRIER_UCTL_REG
mdefine_line|#define HARRIER_UCTL_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_UCTL_OFF)
DECL|macro|HARRIER_MISC_CSR_REG
mdefine_line|#define HARRIER_MISC_CSR_REG   (PRPMC800_HARRIER_XCSR_BASE+HARRIER_MISC_CSR_OFF)
DECL|macro|HARRIER_IFEVP_REG
mdefine_line|#define HARRIER_IFEVP_REG    (PRPMC800_HARRIER_MPIC_BASE+HARRIER_MPIC_IFEVP_OFF)
DECL|macro|HARRIER_IFEDE_REG
mdefine_line|#define HARRIER_IFEDE_REG    (PRPMC800_HARRIER_MPIC_BASE+HARRIER_MPIC_IFEDE_OFF)
DECL|macro|HARRIER_FEEN_REG
mdefine_line|#define HARRIER_FEEN_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_FEEN_OFF)
DECL|macro|HARRIER_FEMA_REG
mdefine_line|#define HARRIER_FEMA_REG&t;(PRPMC800_HARRIER_XCSR_BASE+HARRIER_FEMA_OFF)
DECL|macro|HARRIER_VENI_REG
mdefine_line|#define HARRIER_VENI_REG&t;(PRPMC800_HARRIER_XCSR_BASE + HARRIER_VENI_OFF)
DECL|macro|HARRIER_MISC_CSR
mdefine_line|#define HARRIER_MISC_CSR&t;(PRPMC800_HARRIER_XCSR_BASE + &bslash;&n;&t;&t;&t;&t; HARRIER_MISC_CSR_OFF)
DECL|macro|MONARCH
mdefine_line|#define MONARCH&t;(monarch != 0)
DECL|macro|NON_MONARCH
mdefine_line|#define NON_MONARCH (monarch == 0)
r_extern
r_int
id|mpic_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
DECL|variable|monarch
r_static
r_int
id|monarch
op_assign
l_int|0
suffix:semicolon
DECL|variable|found_self
r_static
r_int
id|found_self
op_assign
l_int|0
suffix:semicolon
DECL|variable|self
r_static
r_int
id|self
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|prpmc800_openpic_initsenses
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
multiline_comment|/* PRPMC800_INT_HOSTINT0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_DEBUGINT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_HARRIER_WDT */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_HOSTINT1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_HOSTINT2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_HOSTINT3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_PMC_INTA */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_PMC_INTB */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_PMC_INTC */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_PMC_INTD */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_UNUSED */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* PRPMC800_INT_HARRIER_INT (UARTS, ABORT, DMA) */
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
r_static
r_int
DECL|function|prpmc_read_config_dword
id|prpmc_read_config_dword
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|u8
id|bus
comma
id|u8
id|devfn
comma
r_int
id|offset
comma
id|u32
op_star
id|val
)paren
(brace
multiline_comment|/* paranoia */
r_if
c_cond
(paren
(paren
id|hose
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|hose-&gt;cfg_addr
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|hose-&gt;cfg_data
op_eq
l_int|NULL
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|out_be32
c_func
(paren
id|hose-&gt;cfg_addr
comma
(paren
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_lshift
l_int|24
)paren
op_or
(paren
id|devfn
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|bus
op_minus
id|hose-&gt;bus_offset
)paren
op_lshift
l_int|8
)paren
op_or
l_int|0x80
)paren
suffix:semicolon
op_star
id|val
op_assign
id|in_le32
c_func
(paren
(paren
id|u32
op_star
)paren
(paren
id|hose-&gt;cfg_data
op_plus
(paren
id|offset
op_amp
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|macro|HARRIER_PCI_VEND_DEV_ID
mdefine_line|#define HARRIER_PCI_VEND_DEV_ID&t;(PCI_VENDOR_ID_MOTOROLA | &bslash;&n;&t;&t;&t;&t; (PCI_DEVICE_ID_MOTOROLA_HARRIER &lt;&lt; 16))
DECL|function|prpmc_self
r_static
r_int
id|prpmc_self
c_func
(paren
id|u8
id|bus
comma
id|u8
id|devfn
)paren
(brace
multiline_comment|/*&n;&t; * Harriers always view themselves as being on bus 0. If we&squot;re not&n;&t; * looking at bus 0, we&squot;re not going to find ourselves.&n;&t; */
r_if
c_cond
(paren
id|bus
op_ne
l_int|0
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_else
(brace
r_int
id|result
suffix:semicolon
r_int
id|val
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|hose
op_assign
id|pci_bus_to_hose
c_func
(paren
id|bus
)paren
suffix:semicolon
multiline_comment|/* See if target device is a Harrier */
id|result
op_assign
id|prpmc_read_config_dword
c_func
(paren
id|hose
comma
id|bus
comma
id|devfn
comma
id|PCI_VENDOR_ID
comma
op_amp
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
op_logical_or
(paren
id|val
op_ne
id|HARRIER_PCI_VEND_DEV_ID
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t;&t; * LBA bit is set if target Harrier == initiating Harrier&n;&t;&t; * (i.e. if we are reading our own PCI header).&n;&t;&t; */
id|result
op_assign
id|prpmc_read_config_dword
c_func
(paren
id|hose
comma
id|bus
comma
id|devfn
comma
id|HARRIER_LBA_OFF
comma
op_amp
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
op_logical_or
(paren
(paren
id|val
op_amp
id|HARRIER_LBA_MSK
)paren
op_ne
id|HARRIER_LBA_MSK
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/* It&squot;s us, save our location for later */
id|self
op_assign
id|devfn
suffix:semicolon
id|found_self
op_assign
l_int|1
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
)brace
DECL|function|prpmc_exclude_device
r_static
r_int
id|prpmc_exclude_device
c_func
(paren
id|u8
id|bus
comma
id|u8
id|devfn
)paren
(brace
multiline_comment|/*&n;&t; * Monarch is allowed to access all PCI devices. Non-monarch is&n;&t; * only allowed to access its own Harrier.&n;&t; */
r_if
c_cond
(paren
id|MONARCH
)paren
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
r_if
c_cond
(paren
id|found_self
)paren
r_if
c_cond
(paren
(paren
id|bus
op_eq
l_int|0
)paren
op_logical_and
(paren
id|devfn
op_eq
id|self
)paren
)paren
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
r_else
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_else
r_return
id|prpmc_self
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
)brace
DECL|function|prpmc800_find_bridges
r_void
id|__init
id|prpmc800_find_bridges
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
r_int
id|host_bridge
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
id|ppc_md.pci_exclude_device
op_assign
id|prpmc_exclude_device
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.pcibios_fixup_bus
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|prpmc_map_irq
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|PRPMC800_PCI_CONFIG_ADDR
comma
id|PRPMC800_PCI_CONFIG_DATA
)paren
suffix:semicolon
multiline_comment|/* Get host bridge vendor/dev id */
id|host_bridge
op_assign
id|in_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|HARRIER_VENI_REG
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host_bridge
op_ne
id|HARRIER_VEND_DEV_ID
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Host bridge 0x%x not supported&bslash;n&quot;
comma
id|host_bridge
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|monarch
op_assign
id|in_be32
c_func
(paren
(paren
id|uint
op_star
)paren
id|HARRIER_MISC_CSR
)paren
op_amp
id|HARRIER_SYSCON
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Running as %s.&bslash;n&quot;
comma
id|MONARCH
ques
c_cond
l_string|&quot;Monarch&quot;
suffix:colon
l_string|&quot;Non-Monarch&quot;
)paren
suffix:semicolon
id|hose-&gt;io_space.start
op_assign
id|PRPMC800_PCI_IO_START
suffix:semicolon
id|hose-&gt;io_space.end
op_assign
id|PRPMC800_PCI_IO_END
suffix:semicolon
id|hose-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|PRPMC800_ISA_IO_BASE
suffix:semicolon
id|hose-&gt;pci_mem_offset
op_assign
id|PRPMC800_PCI_PHY_MEM_OFFSET
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
id|PRPMC800_PCI_IO_START
comma
id|PRPMC800_PCI_IO_END
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MONARCH
)paren
(brace
id|hose-&gt;mem_space.start
op_assign
id|PRPMC800_PCI_MEM_START
suffix:semicolon
id|hose-&gt;mem_space.end
op_assign
id|PRPMC800_PCI_MEM_END
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
id|PRPMC800_PCI_MEM_START
comma
id|PRPMC800_PCI_MEM_END
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|harrier_init
c_func
(paren
id|hose
comma
id|PRPMC800_HARRIER_XCSR_BASE
comma
id|PRPMC800_PROC_PCI_MEM_START
comma
id|PRPMC800_PROC_PCI_MEM_END
comma
id|PRPMC800_PROC_PCI_IO_START
comma
id|PRPMC800_PROC_PCI_IO_END
comma
id|PRPMC800_HARRIER_MPIC_BASE
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Could not initialize HARRIER &quot;
l_string|&quot;bridge&bslash;n&quot;
)paren
suffix:semicolon
id|harrier_release_eready
c_func
(paren
id|PRPMC800_HARRIER_XCSR_BASE
)paren
suffix:semicolon
id|harrier_wait_eready
c_func
(paren
id|PRPMC800_HARRIER_XCSR_BASE
)paren
suffix:semicolon
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
)brace
r_else
(brace
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
comma
id|PRPMC800_NM_PCI_MEM_START
comma
id|PRPMC800_NM_PCI_MEM_END
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|hose-&gt;mem_space.start
op_assign
id|PRPMC800_NM_PCI_MEM_START
suffix:semicolon
id|hose-&gt;mem_space.end
op_assign
id|PRPMC800_NM_PCI_MEM_END
suffix:semicolon
r_if
c_cond
(paren
id|harrier_init
c_func
(paren
id|hose
comma
id|PRPMC800_HARRIER_XCSR_BASE
comma
id|PRPMC800_NM_PROC_PCI_MEM_START
comma
id|PRPMC800_NM_PROC_PCI_MEM_END
comma
id|PRPMC800_PROC_PCI_IO_START
comma
id|PRPMC800_PROC_PCI_IO_END
comma
id|PRPMC800_HARRIER_MPIC_BASE
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Could not initialize HARRIER &quot;
l_string|&quot;bridge&bslash;n&quot;
)paren
suffix:semicolon
id|harrier_setup_nonmonarch
c_func
(paren
id|PRPMC800_HARRIER_XCSR_BASE
comma
id|HARRIER_ITSZ_1MB
)paren
suffix:semicolon
id|harrier_release_eready
c_func
(paren
id|PRPMC800_HARRIER_XCSR_BASE
)paren
suffix:semicolon
)brace
)brace
DECL|function|prpmc800_show_cpuinfo
r_static
r_int
id|prpmc800_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: PrPMC800&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prpmc800_setup_arch
r_static
r_void
id|__init
id|prpmc800_setup_arch
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
id|prpmc800_find_bridges
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Port by MontaVista Software, Inc. &quot;
l_string|&quot;(source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Compute the PrPMC800&squot;s tbl frequency using the baud clock as a reference.&n; */
DECL|function|prpmc800_calibrate_decr
r_static
r_void
id|__init
id|prpmc800_calibrate_decr
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
id|tb_ticks_per_second
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|harrier_revision
suffix:semicolon
id|harrier_revision
op_assign
id|readb
c_func
(paren
id|HARRIER_REVI_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|harrier_revision
OL
l_int|2
)paren
(brace
multiline_comment|/* XTAL64 was broken in harrier revision 1 */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time_init: Harrier revision %d, assuming &quot;
l_string|&quot;100 Mhz bus&bslash;n&quot;
comma
id|harrier_revision
)paren
suffix:semicolon
id|tb_ticks_per_second
op_assign
l_int|100000000
op_div
l_int|4
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|tb_ticks_per_second
op_div
id|HZ
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|tb_ticks_per_second
comma
l_int|1000000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The XTAL64 bit oscillates at the 1/64 the base baud clock&n;&t; * Set count to XTAL64 cycles per second.  Since we&squot;ll count&n;&t; * half-cycles, we&squot;ll reach the count in half a second.&n;&t; */
id|count
op_assign
id|PRPMC800_BASE_BAUD
op_div
l_int|64
suffix:semicolon
multiline_comment|/* Find the first edge of the baud clock */
id|old_state
op_assign
id|readb
c_func
(paren
id|HARRIER_UCTL_REG
)paren
op_amp
id|HARRIER_XTAL64_MASK
suffix:semicolon
r_do
(brace
id|current_state
op_assign
id|readb
c_func
(paren
id|HARRIER_UCTL_REG
)paren
op_amp
id|HARRIER_XTAL64_MASK
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
multiline_comment|/*&n;&t; * Loop until we have found a number of edges (half-cycles)&n;&t; * equal to the count (half a second)&n;&t; */
r_do
(brace
r_do
(brace
id|current_state
op_assign
id|readb
c_func
(paren
id|HARRIER_UCTL_REG
)paren
op_amp
id|HARRIER_XTAL64_MASK
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
multiline_comment|/* We only counted for half a second, so double to get ticks/second */
id|tb_ticks_per_second
op_assign
(paren
id|tbl_end
op_minus
id|tbl_start
)paren
op_star
l_int|2
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|tb_ticks_per_second
op_div
id|HZ
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|tb_ticks_per_second
comma
l_int|1000000
)paren
suffix:semicolon
)brace
DECL|function|prpmc800_restart
r_static
r_void
id|prpmc800_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|ulong
id|temp
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|temp
op_assign
id|in_be32
c_func
(paren
(paren
id|uint
op_star
)paren
id|HARRIER_MISC_CSR_REG
)paren
suffix:semicolon
id|temp
op_or_assign
id|HARRIER_RSTOUT
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
id|HARRIER_MISC_CSR_REG
comma
id|temp
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|prpmc800_halt
r_static
r_void
id|prpmc800_halt
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
DECL|function|prpmc800_power_off
r_static
r_void
id|prpmc800_power_off
c_func
(paren
r_void
)paren
(brace
id|prpmc800_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prpmc800_init_IRQ
r_static
r_void
id|__init
id|prpmc800_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|OpenPIC_InitSenses
op_assign
id|prpmc800_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|prpmc800_openpic_initsenses
)paren
suffix:semicolon
multiline_comment|/* Setup external interrupt sources. */
id|openpic_set_sources
c_func
(paren
l_int|0
comma
l_int|16
comma
id|OpenPIC_Addr
op_plus
l_int|0x10000
)paren
suffix:semicolon
multiline_comment|/* Setup internal UART interrupt source. */
id|openpic_set_sources
c_func
(paren
l_int|16
comma
l_int|1
comma
id|OpenPIC_Addr
op_plus
l_int|0x10200
)paren
suffix:semicolon
multiline_comment|/* Do the MPIC initialization based on the above settings. */
id|openpic_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* enable functional exceptions for uarts and abort */
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|HARRIER_FEEN_REG
comma
(paren
id|HARRIER_FE_UA0
op_or
id|HARRIER_FE_UA1
)paren
)paren
suffix:semicolon
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|HARRIER_FEMA_REG
comma
op_complement
(paren
id|HARRIER_FE_UA0
op_or
id|HARRIER_FE_UA1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space.&n; */
DECL|function|prpmc800_set_bat
r_static
id|__inline__
r_void
id|prpmc800_set_bat
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
multiline_comment|/*&n; * We need to read the Harrier memory controller&n; * to properly determine this value&n; */
DECL|function|prpmc800_find_end_of_memory
r_static
r_int
r_int
id|__init
id|prpmc800_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Read the memory size from the Harrier XCSR */
r_return
id|harrier_get_mem_size
c_func
(paren
id|PRPMC800_HARRIER_XCSR_BASE
)paren
suffix:semicolon
)brace
DECL|function|prpmc800_map_io
r_static
r_void
id|__init
id|prpmc800_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0x80000000
comma
l_int|0x80000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
l_int|0xf0000000
comma
l_int|0xf0000000
comma
l_int|0x10000000
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
id|prpmc800_set_bat
c_func
(paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|PRPMC800_ISA_IO_BASE
suffix:semicolon
id|isa_mem_base
op_assign
id|PRPMC800_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|PRPMC800_PCI_DRAM_OFFSET
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|prpmc800_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|prpmc800_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|prpmc800_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|prpmc800_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|prpmc800_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|prpmc800_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|prpmc800_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|prpmc800_halt
suffix:semicolon
multiline_comment|/* PrPMC800 has no timekeeper part */
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
id|prpmc800_calibrate_decr
suffix:semicolon
macro_line|#ifdef  CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#else&t;&t;&t;&t;/* !CONFIG_SERIAL_TEXT_DEBUG */
id|ppc_md.progress
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_SERIAL_TEXT_DEBUG */
)brace
eof
