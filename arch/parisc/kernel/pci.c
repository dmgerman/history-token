multiline_comment|/* $Id: pci.c,v 1.6 2000/01/29 00:12:05 grundler Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998 Ralf Baechle&n; * Copyright (C) 1999 SuSE GmbH&n; * Copyright (C) 1999-2001 Hewlett-Packard Company&n; * Copyright (C) 1999-2001 Grant Grundler&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* for __init and __devinit */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cache.h&gt;&t;&t;/* for L1_CACHE_BYTES */
DECL|macro|DEBUG_RESOURCES
mdefine_line|#define DEBUG_RESOURCES 0
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBGC
macro_line|# define DBGC(x...)     printk(KERN_DEBUG x)
macro_line|#else
DECL|macro|DBGC
macro_line|# define DBGC(x...)
macro_line|#endif
macro_line|#if DEBUG_RESOURCES
DECL|macro|DBG_RES
mdefine_line|#define DBG_RES(x...)&t;printk(KERN_DEBUG x)
macro_line|#else
DECL|macro|DBG_RES
mdefine_line|#define DBG_RES(x...)
macro_line|#endif
multiline_comment|/* To be used as: mdelay(pci_post_reset_delay);&n;**&n;** post_reset is the time the kernel should stall to prevent anyone from&n;** accessing the PCI bus once #RESET is de-asserted. &n;** PCI spec somewhere says 1 second but with multi-PCI bus systems,&n;** this makes the boot time much longer than necessary.&n;** 20ms seems to work for all the HP PCI implementations to date.&n;*/
DECL|variable|pci_post_reset_delay
r_int
id|pci_post_reset_delay
op_assign
l_int|50
suffix:semicolon
DECL|variable|pci_port
r_struct
id|pci_port_ops
op_star
id|pci_port
suffix:semicolon
DECL|variable|pci_bios
r_struct
id|pci_bios_ops
op_star
id|pci_bios
suffix:semicolon
DECL|variable|pci_hba_count
r_int
id|pci_hba_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;** parisc_pci_hba used by pci_port-&gt;in/out() ops to lookup bus data.&n;*/
DECL|macro|PCI_HBA_MAX
mdefine_line|#define PCI_HBA_MAX 32
DECL|variable|parisc_pci_hba
r_struct
id|pci_hba_data
op_star
id|parisc_pci_hba
(braket
id|PCI_HBA_MAX
)braket
suffix:semicolon
multiline_comment|/********************************************************************&n;**&n;** I/O port space support&n;**&n;*********************************************************************/
multiline_comment|/* EISA port numbers and PCI port numbers share the same interface.  Some&n; * machines have both EISA and PCI adapters installed.  Rather than turn&n; * pci_port into an array, we reserve bus 0 for EISA and call the EISA&n; * routines if the access is to a port on bus 0.  We don&squot;t want to fix&n; * EISA and ISA drivers which assume port space is &lt;= 0xffff.&n; */
macro_line|#ifdef CONFIG_EISA
DECL|macro|EISA_IN
mdefine_line|#define EISA_IN(size) if (EISA_bus &amp;&amp; (b == 0)) return eisa_in##size(addr)
DECL|macro|EISA_OUT
mdefine_line|#define EISA_OUT(size) if (EISA_bus &amp;&amp; (b == 0)) return eisa_out##size(d, addr)
macro_line|#else
DECL|macro|EISA_IN
mdefine_line|#define EISA_IN(size)
DECL|macro|EISA_OUT
mdefine_line|#define EISA_OUT(size)
macro_line|#endif
DECL|macro|PCI_PORT_IN
mdefine_line|#define PCI_PORT_IN(type, size) &bslash;&n;u##size in##type (int addr) &bslash;&n;{ &bslash;&n;&t;int b = PCI_PORT_HBA(addr); &bslash;&n;&t;u##size d = (u##size) -1; &bslash;&n;&t;EISA_IN(size); &bslash;&n;&t;ASSERT(pci_port); /* make sure services are defined */ &bslash;&n;&t;ASSERT(parisc_pci_hba[b]); /* make sure ioaddr are &quot;fixed up&quot; */ &bslash;&n;&t;if (parisc_pci_hba[b] == NULL) { &bslash;&n;&t;&t;printk(KERN_WARNING &quot;&bslash;nPCI or EISA Host Bus Adapter %d not registered. in&quot; #size &quot;(0x%x) returning -1&bslash;n&quot;, b, addr); &bslash;&n;&t;} else { &bslash;&n;&t;&t;d = pci_port-&gt;in##type(parisc_pci_hba[b], PCI_PORT_ADDR(addr)); &bslash;&n;&t;} &bslash;&n;&t;return d; &bslash;&n;}
id|PCI_PORT_IN
c_func
(paren
id|b
comma
l_int|8
)paren
id|PCI_PORT_IN
c_func
(paren
id|w
comma
l_int|16
)paren
id|PCI_PORT_IN
c_func
(paren
id|l
comma
l_int|32
)paren
DECL|macro|PCI_PORT_OUT
mdefine_line|#define PCI_PORT_OUT(type, size) &bslash;&n;void out##type (u##size d, int addr) &bslash;&n;{ &bslash;&n;&t;int b = PCI_PORT_HBA(addr); &bslash;&n;&t;EISA_OUT(size); &bslash;&n;&t;ASSERT(pci_port); &bslash;&n;&t;pci_port-&gt;out##type(parisc_pci_hba[b], PCI_PORT_ADDR(addr), d); &bslash;&n;}
id|PCI_PORT_OUT
c_func
(paren
id|b
comma
l_int|8
)paren
id|PCI_PORT_OUT
c_func
(paren
id|w
comma
l_int|16
)paren
id|PCI_PORT_OUT
c_func
(paren
id|l
comma
l_int|32
)paren
multiline_comment|/*&n; * BIOS32 replacement.&n; */
DECL|function|pcibios_init
r_static
r_int
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_bios
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pci_bios-&gt;init
)paren
(brace
id|pci_bios
op_member_access_from_pointer
id|init
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pci_bios != NULL but init() is!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called from pci_do_scan_bus() *after* walking a bus but before walking PPBs. */
DECL|function|pcibios_fixup_bus
r_void
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
id|ASSERT
c_func
(paren
id|pci_bios
op_ne
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_bios-&gt;fixup_bus
)paren
(brace
id|pci_bios
op_member_access_from_pointer
id|fixup_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;pci_bios != NULL but fixup_bus() is!&bslash;n&quot;
)paren
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
multiline_comment|/*&n;** Used in drivers/pci/quirks.c&n;*/
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
multiline_comment|/*&n;** called by drivers/pci/setup.c:pdev_fixup_irq()&n;*/
DECL|function|pcibios_update_irq
r_void
id|__devinit
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
multiline_comment|/*&n;** updates IRQ_LINE cfg register to reflect PCI-PCI bridge skewing.&n;**&n;** Calling path for Alpha is:&n;**  alpha/kernel/pci.c:common_init_pci(swizzle_func, pci_map_irq_func )&n;**&t;drivers/pci/setup.c:pci_fixup_irqs()&n;**&t;    drivers/pci/setup.c:pci_fixup_irq()&t;(for each PCI device)&n;**&t;&t;invoke swizzle and map functions&n;**&t;        alpha/kernel/pci.c:pcibios_update_irq()&n;**&n;** Don&squot;t need this for PA legacy PDC systems.&n;**&n;** On PAT PDC systems, We only support one &quot;swizzle&quot; for any number&n;** of PCI-PCI bridges deep. That&squot;s how bit3 PCI expansion chassis&n;** are implemented. The IRQ lines are &quot;skewed&quot; for all devices but&n;** *NOT* routed through the PCI-PCI bridge. Ie any device &quot;0&quot; will&n;** share an IRQ line. Legacy PDC is expecting this IRQ line routing&n;** as well.&n;**&n;** Unfortunately, PCI spec allows the IRQ lines to be routed&n;** around the PCI bridge as long as the IRQ lines are skewed&n;** based on the device number...&lt;sigh&gt;...&n;**&n;** Lastly, dino.c might be able to use pci_fixup_irq() to&n;** support RS-232 and PS/2 children. Not sure how but it&squot;s&n;** something to think about.&n;*/
)brace
multiline_comment|/* ------------------------------------&n;**&n;** Program one BAR in PCI config space.&n;**&n;** ------------------------------------&n;** PAT PDC systems need this routine. PA legacy PDC does not.&n;**&n;** When BAR&squot;s are configured by linux, this routine will update&n;** configuration space with the &quot;normalized&quot; address. &quot;root&quot; indicates&n;** where the range starts and res is some portion of that range.&n;**&n;** VCLASS: For all PA-RISC systems except V-class, root-&gt;start would be zero.&n;**&n;** PAT PDC can tell us which MMIO ranges are available or already in use.&n;** I/O port space and such are not memory mapped anyway for PA-Risc.&n;*/
r_void
id|__devinit
DECL|function|pcibios_update_resource
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
id|barnum
)paren
(brace
r_int
id|where
suffix:semicolon
id|u32
id|barval
op_assign
l_int|0
suffix:semicolon
id|DBG_RES
c_func
(paren
l_string|&quot;pcibios_update_resource(%s, ..., %d) [%lx,%lx]/%x&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|barnum
comma
id|res-&gt;start
comma
id|res-&gt;end
comma
(paren
r_int
)paren
id|res-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|barnum
op_ge
id|PCI_BRIDGE_RESOURCES
)paren
(brace
multiline_comment|/* handled in PCI-PCI bridge specific support */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|barnum
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
id|where
op_assign
id|PCI_ROM_ADDRESS
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 0-5  standard PCI &quot;regions&quot; */
id|where
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|barnum
op_star
l_int|4
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|barval
op_assign
id|PCI_PORT_ADDR
c_func
(paren
id|res-&gt;start
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
id|barval
op_assign
id|PCI_BUS_ADDR
c_func
(paren
id|HBA_DATA
c_func
(paren
id|dev-&gt;bus-&gt;sysdata
)paren
comma
id|res-&gt;start
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;pcibios_update_resource() WTF? flags not IO or MEM&quot;
)paren
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
comma
id|barval
)paren
suffix:semicolon
multiline_comment|/* XXX FIXME - Elroy does support 64-bit (dual cycle) addressing.&n;** But at least one device (Symbios 53c896) which has 64-bit BAR&n;** doesn&squot;t actually work right with dual cycle addresses.&n;** So ignore the whole mess for now.&n;*/
r_if
c_cond
(paren
(paren
id|res-&gt;flags
op_amp
(paren
id|PCI_BASE_ADDRESS_SPACE
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
)paren
op_eq
(paren
id|PCI_BASE_ADDRESS_SPACE_MEMORY
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
op_plus
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|DBGC
c_func
(paren
l_string|&quot;PCIBIOS: dev %s type 64-bit&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** Called by pci_set_master() - a driver interface.&n;**&n;** Legacy PDC guarantees to set:&n;**      Map Memory BAR&squot;s into PA IO space.&n;**      Map Expansion ROM BAR into one common PA IO space per bus.&n;**      Map IO BAR&squot;s into PCI IO space.&n;**      Command (see below)&n;**      Cache Line Size&n;**      Latency Timer&n;**      Interrupt Line&n;**&t;PPB: secondary latency timer, io/mmio base/limit,&n;**&t;&t;bus numbers, bridge control&n;**&n;*/
r_void
DECL|function|pcibios_set_master
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|lat
suffix:semicolon
multiline_comment|/* If someone already mucked with this, don&squot;t touch it. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lat
op_ge
l_int|16
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t;** HP generally has fewer devices on the bus than other architectures.&n;&t;** upper byte is PCI_LATENCY_TIMER.&n;&t;*/
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
(paren
l_int|0x80
op_lshift
l_int|8
)paren
op_or
(paren
id|L1_CACHE_BYTES
op_div
r_sizeof
(paren
id|u32
)paren
)paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_init_bus
id|pcibios_init_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|bus-&gt;self
suffix:semicolon
multiline_comment|/* We deal only with pci controllers and pci-pci bridges. */
r_if
c_cond
(paren
id|dev
op_logical_and
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_BRIDGE_PCI
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_int
r_int
id|bridge_ctl
suffix:semicolon
multiline_comment|/* PCI-PCI bridge - set the cache line and default latency&n;&t;&t;   (32) for primary and secondary buses. */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_SEC_LATENCY_TIMER
comma
l_int|32
)paren
suffix:semicolon
multiline_comment|/* Read bridge control */
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_BRIDGE_CONTROL
comma
op_amp
id|bridge_ctl
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_BRIDGE_CONTROL
comma
id|bridge_ctl
op_or
id|PCI_BRIDGE_CTL_PARITY
op_or
id|PCI_BRIDGE_CTL_SERR
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** KLUGE: Link the child and parent resources - generic PCI didn&squot;t&n;*/
r_static
r_void
DECL|function|pcibios_link_hba_resources
id|pcibios_link_hba_resources
c_func
(paren
r_struct
id|resource
op_star
id|hba_res
comma
r_struct
id|resource
op_star
id|r
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;parent
)paren
(brace
id|r-&gt;parent
op_assign
id|hba_res
suffix:semicolon
multiline_comment|/* reverse link is harder *sigh*  */
r_if
c_cond
(paren
id|r-&gt;parent-&gt;child
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;parent-&gt;sibling
)paren
(brace
r_struct
id|resource
op_star
id|next
op_assign
id|r-&gt;parent-&gt;sibling
suffix:semicolon
r_while
c_loop
(paren
id|next-&gt;sibling
)paren
id|next
op_assign
id|next-&gt;sibling
suffix:semicolon
id|next-&gt;sibling
op_assign
id|r
suffix:semicolon
)brace
r_else
(brace
id|r-&gt;parent-&gt;sibling
op_assign
id|r
suffix:semicolon
)brace
)brace
r_else
id|r-&gt;parent-&gt;child
op_assign
id|r
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** called by drivers/pci/setup-res.c:pci_setup_bridge().&n;*/
DECL|function|pcibios_fixup_pbus_ranges
r_void
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
r_struct
id|pci_hba_data
op_star
id|hba
op_assign
id|HBA_DATA
c_func
(paren
id|bus-&gt;sysdata
)paren
suffix:semicolon
multiline_comment|/*&n;&t;** I/O space may see busnumbers here. Something&n;&t;** in the form of 0xbbxxxx where bb is the bus num&n;&t;** and xxxx is the I/O port space address.&n;&t;** Remaining address translation are done in the&n;&t;** PCI Host adapter specific code - ie dino_out8.&n;&t;*/
id|ranges-&gt;io_start
op_assign
id|PCI_PORT_ADDR
c_func
(paren
id|ranges-&gt;io_start
)paren
suffix:semicolon
id|ranges-&gt;io_end
op_assign
id|PCI_PORT_ADDR
c_func
(paren
id|ranges-&gt;io_end
)paren
suffix:semicolon
multiline_comment|/* Convert MMIO addr to PCI addr (undo global virtualization) */
id|ranges-&gt;mem_start
op_assign
id|PCI_BUS_ADDR
c_func
(paren
id|hba
comma
id|ranges-&gt;mem_start
)paren
suffix:semicolon
id|ranges-&gt;mem_end
op_assign
id|PCI_BUS_ADDR
c_func
(paren
id|hba
comma
id|ranges-&gt;mem_end
)paren
suffix:semicolon
id|DBG_RES
c_func
(paren
l_string|&quot;pcibios_fixup_pbus_ranges(%02x, [%lx,%lx %lx,%lx])&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|ranges-&gt;io_start
comma
id|ranges-&gt;io_end
comma
id|ranges-&gt;mem_start
comma
id|ranges-&gt;mem_end
)paren
suffix:semicolon
multiline_comment|/* KLUGE ALERT&n;&t;** if this resource isn&squot;t linked to a &quot;parent&quot;, then it seems&n;&t;** to be a child of the HBA - lets link it in.&n;&t;*/
id|pcibios_link_hba_resources
c_func
(paren
op_amp
id|hba-&gt;io_space
comma
id|bus-&gt;resource
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pcibios_link_hba_resources
c_func
(paren
op_amp
id|hba-&gt;lmmio_space
comma
id|bus-&gt;resource
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|macro|MAX
mdefine_line|#define MAX(val1, val2)   ((val1) &gt; (val2) ? (val1) : (val2))
multiline_comment|/*&n;** pcibios align resources() is called everytime generic PCI code&n;** wants to generate a new address. The process of looking for&n;** an available address, each candidate is first &quot;aligned&quot; and&n;** then checked if the resource is available until a match is found.&n;**&n;** Since we are just checking candidates, don&squot;t use any fields other&n;** than res-&gt;start.&n;*/
r_void
id|__devinit
DECL|function|pcibios_align_resource
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
id|alignment
)paren
(brace
r_int
r_int
id|mask
comma
id|align
suffix:semicolon
id|DBG_RES
c_func
(paren
l_string|&quot;pcibios_align_resource(%s, (%p) [%lx,%lx]/%x, 0x%lx, 0x%lx)&bslash;n&quot;
comma
(paren
(paren
r_struct
id|pci_dev
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|slot_name
comma
id|res-&gt;parent
comma
id|res-&gt;start
comma
id|res-&gt;end
comma
(paren
r_int
)paren
id|res-&gt;flags
comma
id|size
comma
id|alignment
)paren
suffix:semicolon
multiline_comment|/* has resource already been aligned/assigned? */
r_if
c_cond
(paren
id|res-&gt;parent
)paren
r_return
suffix:semicolon
multiline_comment|/* If it&squot;s not IO, then it&squot;s gotta be MEM */
id|align
op_assign
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
ques
c_cond
id|PCIBIOS_MIN_IO
suffix:colon
id|PCIBIOS_MIN_MEM
suffix:semicolon
multiline_comment|/* Align to largest of MIN or input size */
id|mask
op_assign
id|MAX
c_func
(paren
id|alignment
comma
id|align
)paren
op_minus
l_int|1
suffix:semicolon
id|res-&gt;start
op_add_assign
id|mask
suffix:semicolon
id|res-&gt;start
op_and_assign
op_complement
id|mask
suffix:semicolon
multiline_comment|/*&n;&t;** WARNING : caller is expected to update &quot;end&quot; field.&n;&t;** We can&squot;t since it might really represent the *size*.&n;&t;** The difference is &quot;end = start + size&quot; vs &quot;end += start&quot;.&n;&t;*/
)brace
r_int
id|__devinit
DECL|function|pcibios_enable_device
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
id|u16
id|cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
multiline_comment|/*&n;&t;** The various platform PDC&squot;s (aka &quot;BIOS&quot; for PCs) don&squot;t&n;&t;** enable all the same bits. We just make sure they are here.&n;&t;*/
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
multiline_comment|/*&n;&t;** See if any resources have been allocated&n;&t;** While &quot;regular&quot; PCI devices only use 0-5, Bridges use a few&n;&t;** beyond that for window registers.&n;&t;*/
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|DEVICE_COUNT_RESOURCE
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
multiline_comment|/* only setup requested resources */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|idx
)paren
)paren
)paren
r_continue
suffix:semicolon
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
multiline_comment|/*&n;&t;** Enable System error and Parity Error reporting by default.&n;&t;** Devices that do NOT want those behaviors should clear them&n;&t;** (eg PCI graphics, possibly networking).&n;&t;** Interfaces like SCSI certainly should not. We want the&n;&t;** system to crash if a system or parity error is detected.&n;&t;** At least until the device driver can recover from such an error.&n;&t;*/
id|cmd
op_or_assign
(paren
id|PCI_COMMAND_SERR
op_or
id|PCI_COMMAND_PARITY
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* If bridge/bus controller has FBB enabled, child must too. */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;bridge_ctl
op_amp
id|PCI_BRIDGE_CTL_FAST_BACK
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_FAST_BACK
suffix:semicolon
macro_line|#endif
id|DBGC
c_func
(paren
l_string|&quot;PCIBIOS: Enabling device %s cmd 0x%04x&bslash;n&quot;
comma
id|dev-&gt;slot_name
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
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_setup_host_bridge
id|pcibios_setup_host_bridge
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
id|ASSERT
c_func
(paren
id|pci_bios
op_ne
l_int|NULL
)paren
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|pci_bios
)paren
(brace
r_if
c_cond
(paren
id|pci_bios-&gt;setup_host_bridge
)paren
(brace
(paren
op_star
id|pci_bios-&gt;setup_host_bridge
)paren
(paren
id|bus
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
multiline_comment|/*&n;** Mostly copied from drivers/pci/setup-bus.c:pci_assign_unassigned_resources()&n;*/
r_void
id|__devinit
DECL|function|pcibios_assign_unassigned_resources
id|pcibios_assign_unassigned_resources
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
multiline_comment|/* from drivers/pci/setup-bus.c */
r_extern
r_void
id|pbus_assign_resources
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
suffix:semicolon
r_struct
id|pbus_set_ranges_data
id|ranges
suffix:semicolon
id|ranges.io_end
op_assign
id|ranges.io_start
op_assign
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
op_plus
id|PCIBIOS_MIN_IO
suffix:semicolon
id|ranges.mem_end
op_assign
id|ranges.mem_start
op_assign
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|start
op_plus
id|PCIBIOS_MIN_MEM
suffix:semicolon
id|pbus_assign_resources
c_func
(paren
id|bus
comma
op_amp
id|ranges
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** PARISC specific (unfortunately)&n;*/
DECL|function|pcibios_register_hba
r_void
id|pcibios_register_hba
c_func
(paren
r_struct
id|pci_hba_data
op_star
id|hba
)paren
(brace
id|ASSERT
c_func
(paren
id|pci_hba_count
OL
id|PCI_HBA_MAX
)paren
suffix:semicolon
multiline_comment|/* pci_port-&gt;in/out() uses parisc_pci_hba to lookup parameter. */
id|parisc_pci_hba
(braket
id|pci_hba_count
)braket
op_assign
id|hba
suffix:semicolon
id|hba-&gt;hba_num
op_assign
id|pci_hba_count
op_increment
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
eof
