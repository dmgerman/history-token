multiline_comment|/*&n; * arch/ppc/platforms/adir_pci.c&n; *&n; * PCI support for SBS Adirondack&n; *&n; * By Michael Sokolov &lt;msokolov@ivan.Harhan.ORG&gt;&n; * based on the K2 version by Matt Porter &lt;mporter@mvista.com&gt;&n; */
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
macro_line|#include &quot;adir.h&quot;
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
DECL|function|adir_map_irq
id|adir_map_irq
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
DECL|macro|PCIIRQ
mdefine_line|#define&t;PCIIRQ(a,b,c,d)&t;{ADIR_IRQ_##a,ADIR_IRQ_##b,ADIR_IRQ_##c,ADIR_IRQ_##d},
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
multiline_comment|/*&n;&t; * The three PCI devices on the motherboard have dedicated lines to the&n;&t; * CPLD interrupt controller, bypassing the standard PCI INTA-D and the&n;&t; * PC interrupt controller. All other PCI devices (slots) have usual&n;&t; * staggered INTA-D lines, resulting in 8 lines total (PCI0 INTA-D and&n;&t; * PCI1 INTA-D). All 8 go to the CPLD interrupt controller. PCI0 INTA-D&n;&t; * also go to the south bridge, so we have the option of taking them&n;&t; * via the CPLD interrupt controller or via the south bridge 8259&n;&t; * 8258 thingy. PCI1 INTA-D can only be taken via the CPLD interrupt&n;&t; * controller. We take all PCI interrupts via the CPLD interrupt&n;&t; * controller as recommended by SBS.&n;&t; *&n;&t; * We also have some monkey business with the PCI devices within the&n;&t; * VT82C686B south bridge itself. This chip actually has 7 functions on&n;&t; * its IDSEL. Function 0 is the actual south bridge, function 1 is IDE,&n;&t; * and function 4 is some special stuff. The other 4 functions are just&n;&t; * regular PCI devices bundled in the chip. 2 and 3 are USB UHCIs and 5&n;&t; * and 6 are audio (not supported on the Adirondack).&n;&t; *&n;&t; * This is where the monkey business begins. PCI devices are supposed&n;&t; * to signal normal PCI interrupts. But the 4 functions in question are&n;&t; * located in the south bridge chip, which is designed with the&n;&t; * assumption that it will be fielding PCI INTA-D interrupts rather&n;&t; * than generating them. Here&squot;s what it does. Each of the functions in&n;&t; * question routes its interrupt to one of the IRQs on the 8259 thingy.&n;&t; * Which one? It looks at the Interrupt Line register in the PCI config&n;&t; * space, even though the PCI spec says it&squot;s for BIOS/OS interaction&n;&t; * only.&n;&t; *&n;&t; * How do we deal with this? We take these interrupts via 8259 IRQs as&n;&t; * we have to. We return the desired IRQ numbers from this routine when&n;&t; * called for the functions in question. The PCI scan code will then&n;&t; * stick our return value into the Interrupt Line register in the PCI&n;&t; * config space, and the interrupt will actually go there. We identify&n;&t; * these functions within the south bridge IDSEL by their interrupt pin&n;&t; * numbers, as the VT82C686B has 04 in the Interrupt Pin register for&n;&t; * USB and 03 for audio.&n;&t; */
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
multiline_comment|/*&n;&t;&t; *             PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; *             A          B          C          D&n;&t;&t; */
(brace
multiline_comment|/* south bridge */
id|PCIIRQ
c_func
(paren
id|IDE0
comma
id|NONE
comma
id|VIA_AUDIO
comma
id|VIA_USB
)paren
multiline_comment|/* Ethernet 0 */
id|PCIIRQ
c_func
(paren
id|MBETH0
comma
id|MBETH0
comma
id|MBETH0
comma
id|MBETH0
)paren
multiline_comment|/* PCI0 slot 1 */
id|PCIIRQ
c_func
(paren
id|PCI0_INTB
comma
id|PCI0_INTC
comma
id|PCI0_INTD
comma
id|PCI0_INTA
)paren
multiline_comment|/* PCI0 slot 2 */
id|PCIIRQ
c_func
(paren
id|PCI0_INTC
comma
id|PCI0_INTD
comma
id|PCI0_INTA
comma
id|PCI0_INTB
)paren
multiline_comment|/* PCI0 slot 3 */
id|PCIIRQ
c_func
(paren
id|PCI0_INTD
comma
id|PCI0_INTA
comma
id|PCI0_INTB
comma
id|PCI0_INTC
)paren
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
l_int|7
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
multiline_comment|/*&n;&t;&t; *             PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; *             A          B          C          D&n;&t;&t; */
(brace
multiline_comment|/* Ethernet 1 */
id|PCIIRQ
c_func
(paren
id|MBETH1
comma
id|MBETH1
comma
id|MBETH1
comma
id|MBETH1
)paren
multiline_comment|/* SCSI */
id|PCIIRQ
c_func
(paren
id|MBSCSI
comma
id|MBSCSI
comma
id|MBSCSI
comma
id|MBSCSI
)paren
multiline_comment|/* PCI1 slot 1 */
id|PCIIRQ
c_func
(paren
id|PCI1_INTB
comma
id|PCI1_INTC
comma
id|PCI1_INTD
comma
id|PCI1_INTA
)paren
multiline_comment|/* PCI1 slot 2 */
id|PCIIRQ
c_func
(paren
id|PCI1_INTC
comma
id|PCI1_INTD
comma
id|PCI1_INTA
comma
id|PCI1_INTB
)paren
multiline_comment|/* PCI1 slot 3 */
id|PCIIRQ
c_func
(paren
id|PCI1_INTD
comma
id|PCI1_INTA
comma
id|PCI1_INTB
comma
id|PCI1_INTC
)paren
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
l_int|7
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
DECL|macro|PCIIRQ
macro_line|#undef PCIIRQ
)brace
r_static
r_void
DECL|function|adir_pcibios_fixup_resources
id|adir_pcibios_fixup_resources
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
multiline_comment|/*&n; * CPC710 DD3 has an errata causing it to hang the system if a type 0 config&n; * cycle is attempted on its PCI32 interface with a device number &gt; 21.&n; * CPC710&squot;s PCI bridges map device numbers 1 through 21 to AD11 through AD31.&n; * Per the PCI spec it MUST accept all other device numbers and do nothing, and&n; * software MUST scan all device numbers without assuming how IDSELs are&n; * mapped. However, as the CPC710 DD3&squot;s errata causes such correct scanning&n; * procedure to hang the system, we have no choice but to introduce this hack&n; * of knowingly avoiding device numbers &gt; 21 on PCI0,&n; */
r_static
r_int
DECL|function|adir_exclude_device
id|adir_exclude_device
c_func
(paren
id|u_char
id|bus
comma
id|u_char
id|devfn
)paren
(brace
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
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
OG
l_int|21
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_else
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|adir_find_bridges
r_void
id|adir_find_bridges
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
id|ADIR_PCI32_MEM_BASE
suffix:semicolon
id|hose_a-&gt;io_space.start
op_assign
l_int|0
suffix:semicolon
id|hose_a-&gt;io_space.end
op_assign
id|ADIR_PCI32_VIRT_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_a-&gt;mem_space.start
op_assign
l_int|0
suffix:semicolon
id|hose_a-&gt;mem_space.end
op_assign
id|ADIR_PCI32_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_a-&gt;io_resource.start
op_assign
l_int|0
suffix:semicolon
id|hose_a-&gt;io_resource.end
op_assign
id|ADIR_PCI32_VIRT_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_a-&gt;io_resource.flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|start
op_assign
id|ADIR_PCI32_MEM_BASE
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|end
op_assign
id|ADIR_PCI32_MEM_BASE
op_plus
id|ADIR_PCI32_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|hose_a-&gt;io_base_phys
op_assign
id|ADIR_PCI32_IO_BASE
suffix:semicolon
id|hose_a-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|ADIR_PCI32_VIRT_IO_BASE
suffix:semicolon
id|ppc_md.pci_exclude_device
op_assign
id|adir_exclude_device
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose_a
comma
id|ADIR_PCI32_CONFIG_ADDR
comma
id|ADIR_PCI32_CONFIG_DATA
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
id|hose_b-&gt;pci_mem_offset
op_assign
id|ADIR_PCI64_MEM_BASE
suffix:semicolon
id|hose_b-&gt;io_space.start
op_assign
l_int|0
suffix:semicolon
id|hose_b-&gt;io_space.end
op_assign
id|ADIR_PCI64_VIRT_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_b-&gt;mem_space.start
op_assign
l_int|0
suffix:semicolon
id|hose_b-&gt;mem_space.end
op_assign
id|ADIR_PCI64_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_b-&gt;io_resource.start
op_assign
l_int|0
suffix:semicolon
id|hose_b-&gt;io_resource.end
op_assign
id|ADIR_PCI64_VIRT_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_b-&gt;io_resource.flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|hose_b-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|start
op_assign
id|ADIR_PCI64_MEM_BASE
suffix:semicolon
id|hose_b-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|end
op_assign
id|ADIR_PCI64_MEM_BASE
op_plus
id|ADIR_PCI64_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|hose_b-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|hose_b-&gt;io_base_phys
op_assign
id|ADIR_PCI64_IO_BASE
suffix:semicolon
id|hose_b-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|ADIR_PCI64_VIRT_IO_BASE
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose_b
comma
id|ADIR_PCI64_CONFIG_ADDR
comma
id|ADIR_PCI64_CONFIG_DATA
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
id|ppc_md.pcibios_fixup
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.pcibios_fixup_resources
op_assign
id|adir_pcibios_fixup_resources
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|adir_map_irq
suffix:semicolon
)brace
eof
