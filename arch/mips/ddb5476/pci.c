multiline_comment|/*&n; *  arch/mips/ddb5476/pci.c -- NEC DDB Vrc-5074 PCI access routines&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Albert Dorofeev &lt;albert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm-mips/nile4.h&gt;
DECL|function|nile4_pre_pci_access0
r_static
id|u32
id|nile4_pre_pci_access0
c_func
(paren
r_int
id|slot_num
)paren
(brace
id|u32
id|pci_addr
op_assign
l_int|0
suffix:semicolon
id|u32
id|virt_addr
op_assign
id|NILE4_PCI_CFG_BASE
suffix:semicolon
multiline_comment|/* work around the bug for Vrc5476 */
r_if
c_cond
(paren
id|slot_num
op_eq
l_int|13
)paren
r_return
id|NILE4_BASE
op_plus
id|NILE4_PCI_BASE
suffix:semicolon
multiline_comment|/* Set window 1 address 08000000 - 32 bit - 128 MB (PCI config space) */
id|nile4_set_pdar
c_func
(paren
id|NILE4_PCIW1
comma
id|PHYSADDR
c_func
(paren
id|virt_addr
)paren
comma
l_int|0x08000000
comma
l_int|32
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// [jsun] we start scanning from addr:10, 
singleline_comment|// with 128M we can go up to addr:26 (slot 16)
r_if
c_cond
(paren
id|slot_num
op_le
l_int|16
)paren
(brace
id|virt_addr
op_add_assign
l_int|0x00000400
op_lshift
id|slot_num
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* for high slot, we have to set higher PCI base addr */
id|pci_addr
op_assign
l_int|0x00000400
op_lshift
id|slot_num
suffix:semicolon
)brace
id|nile4_set_pmr
c_func
(paren
id|NILE4_PCIINIT1
comma
id|NILE4_PCICMD_CFG
comma
id|pci_addr
)paren
suffix:semicolon
r_return
id|virt_addr
suffix:semicolon
)brace
DECL|function|nile4_post_pci_access0
r_static
r_void
id|nile4_post_pci_access0
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Set window 1 back to address 08000000 - 32 bit - 128 MB&n;&t; * (PCI IO space)&n;&t; */
id|nile4_set_pdar
c_func
(paren
id|NILE4_PCIW1
comma
id|PHYSADDR
c_func
(paren
id|NILE4_PCI_MEM_BASE
)paren
comma
l_int|0x08000000
comma
l_int|32
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|// nile4_set_pmr(NILE4_PCIINIT1, NILE4_PCICMD_MEM, 0);
id|nile4_set_pmr
c_func
(paren
id|NILE4_PCIINIT1
comma
id|NILE4_PCICMD_MEM
comma
l_int|0x08000000
)paren
suffix:semicolon
)brace
DECL|function|nile4_pci_read
r_static
r_int
id|nile4_pci_read
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
id|val
)paren
(brace
r_int
id|status
comma
id|slot_num
comma
id|func_num
suffix:semicolon
id|u32
id|result
comma
id|base
comma
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Do we need to generate type 1 configure transaction? */
r_if
c_cond
(paren
id|bus-&gt;number
)paren
(brace
multiline_comment|/* FIXME - not working yet */
r_return
id|PCIBIOS_FUNC_NOT_SUPPORTED
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * the largest type 1 configuration addr is 16M, &n;&t;&t;&t; * &lt; 256M config space &n;&t;&t;&t; */
id|slot_num
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
(paren
id|bus-&gt;number
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
OL
l_int|8
)paren
op_or
id|where
op_or
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|func_num
op_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|func_num
op_lshift
l_int|8
)paren
op_plus
id|where
suffix:semicolon
)brace
id|base
op_assign
id|nile4_pre_pci_access0
c_func
(paren
id|slot_num
)paren
suffix:semicolon
op_star
id|val
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|base
op_plus
id|addr
)paren
suffix:semicolon
id|nile4_post_pci_access0
c_func
(paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|status
op_assign
id|nile4_pci_read
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
op_amp
op_complement
l_int|3
comma
l_int|4
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|status
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
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
id|result
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|result
op_rshift_assign
l_int|16
suffix:semicolon
op_star
id|val
op_assign
(paren
id|u8
)paren
(paren
id|result
op_amp
l_int|0xff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|result
op_rshift_assign
l_int|16
suffix:semicolon
op_star
id|val
op_assign
(paren
id|u16
)paren
(paren
id|result
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|nile4_pci_write
r_static
r_int
id|nile4_pci_write
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
id|val
)paren
(brace
r_int
id|status
comma
id|slot_num
comma
id|func_num
comma
id|shift
op_assign
l_int|0
suffix:semicolon
id|u32
id|result
comma
id|base
comma
id|addr
suffix:semicolon
id|status
op_assign
id|nile4_pci_read
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
op_amp
op_complement
l_int|3
comma
l_int|4
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
r_return
id|status
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
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|shift
op_add_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
id|shift
op_add_assign
l_int|8
suffix:semicolon
id|result
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|shift
)paren
suffix:semicolon
id|result
op_or_assign
id|val
op_lshift
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|shift
op_add_assign
l_int|16
suffix:semicolon
id|result
op_and_assign
op_complement
(paren
l_int|0xffff
op_lshift
id|shift
)paren
suffix:semicolon
id|result
op_or_assign
id|val
op_lshift
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* Do we need to generate type 1 configure transaction? */
r_if
c_cond
(paren
id|bus-&gt;number
)paren
(brace
multiline_comment|/* FIXME - not working yet */
r_return
id|PCIBIOS_FUNC_NOT_SUPPORTED
suffix:semicolon
multiline_comment|/* the largest type 1 configuration addr is 16M, &n;&t;&t;&t;&t; * &lt; 256M config space */
id|slot_num
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
(paren
id|bus-&gt;number
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
OL
l_int|8
)paren
op_or
id|where
op_or
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|func_num
op_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|func_num
op_lshift
l_int|8
)paren
op_plus
id|where
suffix:semicolon
)brace
id|base
op_assign
id|nile4_pre_pci_access0
c_func
(paren
id|slot_num
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|base
op_plus
id|addr
)paren
op_assign
id|val
suffix:semicolon
id|nile4_post_pci_access0
c_func
(paren
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_return
id|nile4_pci_write
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
op_amp
op_complement
l_int|3
comma
l_int|4
comma
id|result
)paren
suffix:semicolon
)brace
DECL|variable|nile4_pci_ops
r_struct
id|pci_ops
id|nile4_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|nile4_pci_read
comma
dot
id|write
op_assign
id|nile4_pci_write
comma
)brace
suffix:semicolon
r_struct
(brace
DECL|member|ram
r_struct
id|resource
id|ram
suffix:semicolon
DECL|member|flash
r_struct
id|resource
id|flash
suffix:semicolon
DECL|member|isa_io
r_struct
id|resource
id|isa_io
suffix:semicolon
DECL|member|pci_io
r_struct
id|resource
id|pci_io
suffix:semicolon
DECL|member|isa_mem
r_struct
id|resource
id|isa_mem
suffix:semicolon
DECL|member|pci_mem
r_struct
id|resource
id|pci_mem
suffix:semicolon
DECL|member|nile4
r_struct
id|resource
id|nile4
suffix:semicolon
DECL|member|boot
r_struct
id|resource
id|boot
suffix:semicolon
DECL|variable|ddb5476_resources
)brace
id|ddb5476_resources
op_assign
(brace
singleline_comment|// { &quot;RAM&quot;, 0x00000000, 0x03ffffff, IORESOURCE_MEM | PCI_BASE_ADDRESS_MEM_TYPE_64 },
(brace
l_string|&quot;RAM&quot;
comma
l_int|0x00000000
comma
l_int|0x03ffffff
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Flash ROM&quot;
comma
l_int|0x04000000
comma
l_int|0x043fffff
)brace
comma
(brace
l_string|&quot;Nile4 ISA I/O&quot;
comma
l_int|0x06000000
comma
l_int|0x060fffff
)brace
comma
(brace
l_string|&quot;Nile4 PCI I/O&quot;
comma
l_int|0x06100000
comma
l_int|0x07ffffff
)brace
comma
(brace
l_string|&quot;Nile4 ISA mem&quot;
comma
l_int|0x08000000
comma
l_int|0x08ffffff
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Nile4 PCI mem&quot;
comma
l_int|0x09000000
comma
l_int|0x0fffffff
comma
id|IORESOURCE_MEM
)brace
comma
singleline_comment|// { &quot;Nile4 ctrl&quot;, 0x1fa00000, 0x1fbfffff, IORESOURCE_MEM | PCI_BASE_ADDRESS_MEM_TYPE_64 },
(brace
l_string|&quot;Nile4 ctrl&quot;
comma
l_int|0x1fa00000
comma
l_int|0x1fbfffff
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Boot ROM&quot;
comma
l_int|0x1fc00000
comma
l_int|0x1fffffff
)brace
)brace
suffix:semicolon
DECL|variable|M5229_resources
r_struct
id|resource
id|M5229_resources
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_string|&quot;M5229 BAR0&quot;
comma
l_int|0x1f0
comma
l_int|0x1f3
comma
id|IORESOURCE_IO
)brace
comma
(brace
l_string|&quot;M5229 BAR1&quot;
comma
l_int|0x3f4
comma
l_int|0x3f7
comma
id|IORESOURCE_IO
)brace
comma
(brace
l_string|&quot;M5229 BAR2&quot;
comma
l_int|0x170
comma
l_int|0x173
comma
id|IORESOURCE_IO
)brace
comma
(brace
l_string|&quot;M5229 BAR3&quot;
comma
l_int|0x374
comma
l_int|0x377
comma
id|IORESOURCE_IO
)brace
comma
(brace
l_string|&quot;M5229 BAR4&quot;
comma
l_int|0xf000
comma
l_int|0xf00f
comma
id|IORESOURCE_IO
)brace
)brace
suffix:semicolon
DECL|function|ddb5476_pci_fixup
r_static
r_void
id|__init
id|ddb5476_pci_fixup
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
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NEC
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_NEC_VRC5476
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The first 64-bit PCI base register should point to&n;&t;&t;&t; * the Nile4 control registers. Unfortunately this&n;&t;&t;&t; * isn&squot;t the case, so we fix it ourselves. This allows&n;&t;&t;&t; * the serial driver to find the UART.&n;&t;&t;&t; */
id|dev-&gt;resource
(braket
l_int|0
)braket
op_assign
id|ddb5476_resources.nile4
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|dev-&gt;resource
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The second 64-bit PCI base register points to the&n;&t;&t;&t; * first memory bank. Unfortunately the address is&n;&t;&t;&t; * wrong, so we fix it (again).&n;&t;&t;&t; */
multiline_comment|/* [jsun] We cannot request the resource anymore,&n;&t;&t;&t; * because kernel/setup.c has already reserved &quot;System &n;&t;&t;&t; * RAM&quot; resource at the same spot.  &n;&t;&t;&t; * The fundamental problem here is that PCI host &n;&t;&t;&t; * controller should not put system RAM mapping in BAR&n;&t;&t;&t; * and make subject to PCI resource assignement.&n;&t;&t;&t; * Current fix is a total hack.  We set parent to 1 so&n;                         * so that PCI resource assignement code is fooled to &n;                         * think the resource is assigned, and will not attempt&n;                         * to mess with it.&n;&t;&t;&t; */
id|dev-&gt;resource
(braket
l_int|2
)braket
op_assign
id|ddb5476_resources.ram
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|dev-&gt;resource
(braket
l_int|2
)braket
)paren
)paren
(brace
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|parent
op_assign
l_int|0x1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AL
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AL_M7101
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * It&squot;s nice to have the LEDs on the GPIO pins&n;&t;&t;&t; * available for debugging&n;&t;&t;&t; */
r_extern
r_struct
id|pci_dev
op_star
id|pci_pmu
suffix:semicolon
id|u8
id|t8
suffix:semicolon
id|pci_pmu
op_assign
id|dev
suffix:semicolon
multiline_comment|/* for LEDs D2 and D3 */
multiline_comment|/* Program the lines for LEDs D2 and D3 to output */
id|nile4_pci_read
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
l_int|0x7d
comma
l_int|1
comma
op_amp
id|t8
)paren
suffix:semicolon
id|t8
op_or_assign
l_int|0xc0
suffix:semicolon
id|nile4_pci_write
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
l_int|0x7d
comma
l_int|1
comma
id|t8
)paren
suffix:semicolon
multiline_comment|/* Turn LEDs D2 and D3 off */
id|nile4_pci_read
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
l_int|0x7e
comma
l_int|1
comma
op_amp
id|t8
)paren
suffix:semicolon
id|t8
op_or_assign
l_int|0xc0
suffix:semicolon
id|nile4_pci_write
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;devfn
comma
l_int|0x7e
comma
l_int|1
comma
id|t8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AL
op_logical_and
id|dev-&gt;device
op_eq
l_int|0x5229
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;resource
(braket
id|i
)braket
op_assign
id|M5229_resources
(braket
id|i
)braket
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pcibios_fixup_irqs
r_static
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
suffix:semicolon
r_int
id|slot_num
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
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
r_switch
c_cond
(paren
id|slot_num
)paren
(brace
r_case
l_int|3
suffix:colon
multiline_comment|/* re-programmed to USB */
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* hard-coded; see irq.c */
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* re-programmed to PMU */
id|dev-&gt;irq
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* hard-coded; see irq.c */
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* on-board pci-pci bridge */
id|dev-&gt;irq
op_assign
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* on-board ether */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTB
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* ISA-PCI bridge  */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTC
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
multiline_comment|/* ext slot #3 */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTD
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
multiline_comment|/* ext slot #4 */
id|dev-&gt;irq
op_assign
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_INTA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
multiline_comment|/* Vrc5476 */
id|dev-&gt;irq
op_assign
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
multiline_comment|/* HD controller, M5229 */
id|dev-&gt;irq
op_assign
l_int|14
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;JSUN : in pcibios_fixup_irqs - unkown slot %d&bslash;n&quot;
comma
id|slot_num
)paren
suffix:semicolon
id|panic
(paren
l_string|&quot;JSUN : in pcibios_fixup_irqs - unkown slot.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Emulate bios initialization &bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* [jsun] we need to set BAR0 so that SDRAM 0 appears at 0x0 in PCI */
op_star
(paren
r_int
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|NILE4_BAR0
)paren
op_assign
l_int|0x8
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
)paren
suffix:semicolon
id|ioport_resource.end
op_assign
l_int|0x1ffffff
suffix:semicolon
multiline_comment|/*  32 MB */
id|iomem_resource.end
op_assign
l_int|0x1fffffff
suffix:semicolon
multiline_comment|/* 512 MB */
multiline_comment|/* `ram&squot; and `nile4&squot; are requested through the Nile4 pci_dev */
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5476_resources.flash
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5476_resources.isa_io
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5476_resources.pci_io
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5476_resources.isa_mem
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5476_resources.pci_mem
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|ddb5476_resources.boot
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|nile4_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
id|ddb5476_pci_fixup
c_func
(paren
)paren
suffix:semicolon
id|pci_assign_unassigned_resources
c_func
(paren
)paren
suffix:semicolon
id|pcibios_fixup_irqs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
multiline_comment|/* [jsun] we don&squot;t know how to fix sub-buses yet */
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
l_int|0
)paren
(brace
id|bus-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|ddb5476_resources.pci_mem
suffix:semicolon
)brace
)brace
DECL|function|pcibios_setup
r_char
op_star
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
multiline_comment|/*&n;&t; * our caller figure out range by going through the dev structures.  &n;&t; * I guess this is the place to fix things up if the bus is using a &n;&t; * different view of the addressing space.&n;&t; */
macro_line|#if 0&t;/*  original DDB5074 code */
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
l_int|0
)paren
(brace
id|ranges-&gt;io_start
op_sub_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;io_end
op_sub_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;mem_start
op_sub_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|ranges-&gt;mem_end
op_sub_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|pcibios_enable_resources
r_int
id|pcibios_enable_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
multiline_comment|/*&n;&t; *  Don&squot;t touch the Nile 4&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NEC
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_NEC_VRC5476
)paren
r_return
l_int|0
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
id|dev-&gt;slot_name
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
id|cmd
op_ne
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
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
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
id|pcibios_enable_resources
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|pcibios_update_resource
r_void
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
id|reg
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Somebody might have asked allocation of a non-standard&n;&t;&t; * resource&n;&t;&t; */
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
id|dev-&gt;slot_name
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
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
multiline_comment|/* We need to avoid collisions with `mirrored&squot; VGA ports&n;&t;&t;   and other strange ISA hardware, so we always want the&n;&t;&t;   addresses kilobyte aligned.  */
r_if
c_cond
(paren
id|size
OG
l_int|0x100
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: I/O Region %s/%d too large&quot;
l_string|&quot; (%ld bytes)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;resource
op_minus
id|res
comma
id|size
)paren
suffix:semicolon
)brace
id|start
op_assign
(paren
id|start
op_plus
l_int|1024
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
l_int|1024
op_minus
l_int|1
)paren
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
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
r_return
l_int|1
suffix:semicolon
)brace
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
eof
