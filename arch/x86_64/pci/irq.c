multiline_comment|/*&n; *&t;Low-Level PCI Support for PC -- Routing of Interrupts&n; *&n; *&t;(c) 1999--2000 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|PIRQ_SIGNATURE
mdefine_line|#define PIRQ_SIGNATURE&t;((&squot;$&squot; &lt;&lt; 0) + (&squot;P&squot; &lt;&lt; 8) + (&squot;I&squot; &lt;&lt; 16) + (&squot;R&squot; &lt;&lt; 24))
DECL|macro|PIRQ_VERSION
mdefine_line|#define PIRQ_VERSION 0x0100
DECL|variable|broken_hp_bios_irq9
r_int
id|broken_hp_bios_irq9
suffix:semicolon
DECL|variable|pirq_table
r_static
r_struct
id|irq_routing_table
op_star
id|pirq_table
suffix:semicolon
multiline_comment|/*&n; * Never use: 0, 1, 2 (timer, keyboard, and cascade)&n; * Avoid using: 13, 14 and 15 (FP error and IDE).&n; * Penalize: 3, 4, 6, 7, 12 (known ISA uses: serial, floppy, parallel and mouse)&n; */
DECL|variable|pcibios_irq_mask
r_int
r_int
id|pcibios_irq_mask
op_assign
l_int|0xfff8
suffix:semicolon
DECL|variable|pirq_penalty
r_static
r_int
id|pirq_penalty
(braket
l_int|16
)braket
op_assign
(brace
l_int|1000000
comma
l_int|1000000
comma
l_int|1000000
comma
l_int|1000
comma
l_int|1000
comma
l_int|0
comma
l_int|1000
comma
l_int|1000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1000
comma
l_int|100000
comma
l_int|100000
comma
l_int|100000
)brace
suffix:semicolon
DECL|struct|irq_router
r_struct
id|irq_router
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|vendor
DECL|member|device
id|u16
id|vendor
comma
id|device
suffix:semicolon
DECL|member|get
r_int
(paren
op_star
id|get
)paren
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
suffix:semicolon
DECL|member|set
r_int
(paren
op_star
id|set
)paren
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
r_new
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|pcibios_enable_irq
r_int
(paren
op_star
id|pcibios_enable_irq
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; *  Search 0xf0000 -- 0xfffff for the PCI IRQ Routing Table.&n; */
DECL|function|pirq_find_routing_table
r_static
r_struct
id|irq_routing_table
op_star
id|__init
id|pirq_find_routing_table
c_func
(paren
r_void
)paren
(brace
id|u8
op_star
id|addr
suffix:semicolon
r_struct
id|irq_routing_table
op_star
id|rt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|sum
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
(paren
id|u8
op_star
)paren
id|__va
c_func
(paren
l_int|0xf0000
)paren
suffix:semicolon
id|addr
OL
(paren
id|u8
op_star
)paren
id|__va
c_func
(paren
l_int|0x100000
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|16
)paren
(brace
id|rt
op_assign
(paren
r_struct
id|irq_routing_table
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;signature
op_ne
id|PIRQ_SIGNATURE
op_logical_or
id|rt-&gt;version
op_ne
id|PIRQ_VERSION
op_logical_or
id|rt-&gt;size
op_mod
l_int|16
op_logical_or
id|rt-&gt;size
OL
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
r_continue
suffix:semicolon
id|sum
op_assign
l_int|0
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
id|rt-&gt;size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sum
op_add_assign
id|addr
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sum
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Interrupt Routing Table found at 0x%p&bslash;n&quot;
comma
id|rt
)paren
suffix:semicolon
r_return
id|rt
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *  If we have a IRQ routing table, use it to search for peer host&n; *  bridges.  It&squot;s a gross hack, but since there are no other known&n; *  ways how to get a list of buses, we have to go this way.&n; */
DECL|function|pirq_peer_trick
r_static
r_void
id|__init
id|pirq_peer_trick
c_func
(paren
r_void
)paren
(brace
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
id|pirq_table
suffix:semicolon
id|u8
id|busmap
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|irq_info
op_star
id|e
suffix:semicolon
id|memset
c_func
(paren
id|busmap
comma
l_int|0
comma
r_sizeof
(paren
id|busmap
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
(paren
id|rt-&gt;size
op_minus
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
op_div
r_sizeof
(paren
r_struct
id|irq_info
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e
op_assign
op_amp
id|rt-&gt;slots
(braket
id|i
)braket
suffix:semicolon
macro_line|#ifdef DEBUG
(brace
r_int
id|j
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%02x:%02x slot=%02x&quot;
comma
id|e-&gt;bus
comma
id|e-&gt;devfn
op_div
l_int|8
comma
id|e-&gt;slot
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
suffix:semicolon
id|j
op_increment
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; %d:%02x/%04x&quot;
comma
id|j
comma
id|e-&gt;irq
(braket
id|j
)braket
dot
id|link
comma
id|e-&gt;irq
(braket
id|j
)braket
dot
id|bitmap
)paren
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|busmap
(braket
id|e-&gt;bus
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/*&n;&t;&t; *  It might be a secondary bus, but in this case its parent is already&n;&t;&t; *  known (ascending bus order) and therefore pci_scan_bus returns immediately.&n;&t;&t; */
r_if
c_cond
(paren
id|busmap
(braket
id|i
)braket
op_logical_and
id|pci_scan_bus
c_func
(paren
id|i
comma
id|pci_root_bus-&gt;ops
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Discovered primary peer bus %02x [IRQ]&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
singleline_comment|//pcibios_last_bus = -1;
)brace
multiline_comment|/*&n; *  Code for querying and setting of IRQ routes on various interrupt routers.&n; */
DECL|function|eisa_set_level_irq
r_void
id|eisa_set_level_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_char
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
r_int
r_int
id|port
op_assign
l_int|0x4d0
op_plus
(paren
id|irq
op_rshift
l_int|3
)paren
suffix:semicolon
r_int
r_char
id|val
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|val
op_amp
id|mask
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; edge&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
op_or
id|mask
comma
id|port
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Common IRQ routing practice: nybbles in config space,&n; * offset by some magic constant.&n; */
DECL|function|read_config_nybble
r_static
r_int
r_int
id|read_config_nybble
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_int
id|offset
comma
r_int
id|nr
)paren
(brace
id|u8
id|x
suffix:semicolon
r_int
id|reg
op_assign
id|offset
op_plus
(paren
id|nr
op_rshift
l_int|1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|reg
comma
op_amp
id|x
)paren
suffix:semicolon
r_return
(paren
id|nr
op_amp
l_int|1
)paren
ques
c_cond
(paren
id|x
op_rshift
l_int|4
)paren
suffix:colon
(paren
id|x
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
DECL|function|write_config_nybble
r_static
r_void
id|write_config_nybble
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_int
id|offset
comma
r_int
id|nr
comma
r_int
r_int
id|val
)paren
(brace
id|u8
id|x
suffix:semicolon
r_int
id|reg
op_assign
id|offset
op_plus
(paren
id|nr
op_rshift
l_int|1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|reg
comma
op_amp
id|x
)paren
suffix:semicolon
id|x
op_assign
(paren
id|nr
op_amp
l_int|1
)paren
ques
c_cond
(paren
(paren
id|x
op_amp
l_int|0x0f
)paren
op_or
(paren
id|val
op_lshift
l_int|4
)paren
)paren
suffix:colon
(paren
(paren
id|x
op_amp
l_int|0xf0
)paren
op_or
id|val
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|router
comma
id|reg
comma
id|x
)paren
suffix:semicolon
)brace
macro_line|#if 0 /* enable when pci ids ae known */
multiline_comment|/*&n; * The VIA pirq rules are nibble-based, like ALI,&n; * but without the ugly irq number munging.&n; */
r_static
r_int
id|pirq_via_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
r_return
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0x55
comma
id|pirq
)paren
suffix:semicolon
)brace
r_static
r_int
id|pirq_via_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
id|write_config_nybble
c_func
(paren
id|router
comma
l_int|0x55
comma
id|pirq
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;PIRQ routing for SiS 85C503 router used in several SiS chipsets&n; *&t;According to the SiS 5595 datasheet (preliminary V1.0, 12/24/1997)&n; *&t;the related registers work as follows:&n; *&t;&n; *&t;general: one byte per re-routable IRQ,&n; *&t;&t; bit 7      IRQ mapping enabled (0) or disabled (1)&n; *&t;&t; bits [6:4] reserved&n; *&t;&t; bits [3:0] IRQ to map to&n; *&t;&t;     allowed: 3-7, 9-12, 14-15&n; *&t;&t;     reserved: 0, 1, 2, 8, 13&n; *&n; *&t;individual registers in device config space:&n; *&n; *&t;0x41/0x42/0x43/0x44:&t;PCI INT A/B/C/D - bits as in general case&n; *&n; *&t;0x61:&t;&t;&t;IDEIRQ: bits as in general case - but:&n; *&t;&t;&t;&t;bits [6:5] must be written 01&n; *&t;&t;&t;&t;bit 4 channel-select primary (0), secondary (1)&n; *&n; *&t;0x62:&t;&t;&t;USBIRQ: bits as in general case - but:&n; *&t;&t;&t;&t;bit 4 OHCI function disabled (0), enabled (1)&n; *&t;&n; *&t;0x6a:&t;&t;&t;ACPI/SCI IRQ - bits as in general case&n; *&n; *&t;0x7e:&t;&t;&t;Data Acq. Module IRQ - bits as in general case&n; *&n; *&t;Apparently there are systems implementing PCI routing table using both&n; *&t;link values 0x01-0x04 and 0x41-0x44 for PCI INTA..D, but register offsets&n; *&t;like 0x62 as link values for USBIRQ e.g. So there is no simple&n; *&t;&quot;register = offset + pirq&quot; relation.&n; *&t;Currently we support PCI INTA..D and USBIRQ and try our best to handle&n; *&t;both link mappings.&n; *&t;IDE/ACPI/DAQ mapping is currently unsupported (left untouched as set by BIOS).&n; */
r_static
r_int
id|pirq_sis_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
id|u8
id|x
suffix:semicolon
r_int
id|reg
op_assign
id|pirq
suffix:semicolon
r_switch
c_cond
(paren
id|pirq
)paren
(brace
r_case
l_int|0x01
suffix:colon
r_case
l_int|0x02
suffix:colon
r_case
l_int|0x03
suffix:colon
r_case
l_int|0x04
suffix:colon
id|reg
op_add_assign
l_int|0x40
suffix:semicolon
r_case
l_int|0x41
suffix:colon
r_case
l_int|0x42
suffix:colon
r_case
l_int|0x43
suffix:colon
r_case
l_int|0x44
suffix:colon
r_case
l_int|0x62
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|router
comma
id|reg
comma
op_amp
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ne
l_int|0x62
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0x40
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x61
suffix:colon
r_case
l_int|0x6a
suffix:colon
r_case
l_int|0x7e
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SiS pirq: advanced IDE/ACPI/DAQ mapping not yet implemented&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SiS router pirq escape (%d)&bslash;n&quot;
comma
id|pirq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|x
op_amp
l_int|0x80
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|x
op_amp
l_int|0x0f
)paren
suffix:semicolon
)brace
r_static
r_int
id|pirq_sis_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
id|u8
id|x
suffix:semicolon
r_int
id|reg
op_assign
id|pirq
suffix:semicolon
r_switch
c_cond
(paren
id|pirq
)paren
(brace
r_case
l_int|0x01
suffix:colon
r_case
l_int|0x02
suffix:colon
r_case
l_int|0x03
suffix:colon
r_case
l_int|0x04
suffix:colon
id|reg
op_add_assign
l_int|0x40
suffix:semicolon
r_case
l_int|0x41
suffix:colon
r_case
l_int|0x42
suffix:colon
r_case
l_int|0x43
suffix:colon
r_case
l_int|0x44
suffix:colon
r_case
l_int|0x62
suffix:colon
id|x
op_assign
(paren
id|irq
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|irq
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ne
l_int|0x62
)paren
r_break
suffix:semicolon
multiline_comment|/* always mark OHCI enabled, as nothing else knows about this */
id|x
op_or_assign
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x61
suffix:colon
r_case
l_int|0x6a
suffix:colon
r_case
l_int|0x7e
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;advanced SiS pirq mapping not yet implemented&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SiS router pirq escape (%d)&bslash;n&quot;
comma
id|pirq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|router
comma
id|reg
comma
id|x
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Support for AMD756 PCI IRQ Routing&n; * Jhon H. Caicedo &lt;jhcaiced@osso.org.co&gt;&n; * Jun/21/2001 0.2.0 Release, fixed to use &quot;nybble&quot; functions... (jhcaiced)&n; * Jun/19/2001 Alpha Release 0.1.0 (jhcaiced)&n; * The AMD756 pirq rules are nibble-based&n; * offset 0x56 0-3 PIRQA  4-7  PIRQB&n; * offset 0x57 0-3 PIRQC  4-7  PIRQD&n; */
DECL|function|pirq_amd756_get
r_static
r_int
id|pirq_amd756_get
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
)paren
(brace
id|u8
id|irq
suffix:semicolon
id|irq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pirq
op_le
l_int|4
)paren
(brace
id|irq
op_assign
id|read_config_nybble
c_func
(paren
id|router
comma
l_int|0x56
comma
id|pirq
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AMD756: dev %04x:%04x, router pirq : %d get irq : %2d&bslash;n&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|pirq
comma
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
DECL|function|pirq_amd756_set
r_static
r_int
id|pirq_amd756_set
c_func
(paren
r_struct
id|pci_dev
op_star
id|router
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pirq
comma
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AMD756: dev %04x:%04x, router pirq : %d SET irq : %2d&bslash;n&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|pirq
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pirq
op_le
l_int|4
)paren
(brace
id|write_config_nybble
c_func
(paren
id|router
comma
l_int|0x56
comma
id|pirq
op_minus
l_int|1
comma
id|irq
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pirq_routers
r_static
r_struct
id|irq_router
id|pirq_routers
(braket
)braket
op_assign
(brace
macro_line|#if 0 /* all these do not exist on Hammer currently, but keep one example&n;&t; for each. All these vendors have announced K8 chipsets, so we&squot;ll&n;&t; eventually need a router for them. Luckily they tend to use the&n;&t; same ones, so with luck just enabling the existing ones will work&n;&t; when you know the final PCI ids.  */ 
(brace
l_string|&quot;ALI&quot;
comma
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M1533
comma
id|pirq_ali_get
comma
id|pirq_ali_set
)brace
comma
(brace
l_string|&quot;VIA&quot;
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
id|pirq_via_get
comma
id|pirq_via_set
)brace
comma
(brace
l_string|&quot;SIS&quot;
comma
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_503
comma
id|pirq_sis_get
comma
id|pirq_sis_set
)brace
comma
macro_line|#endif
(brace
l_string|&quot;AMD756 VIPER&quot;
comma
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_VIPER_740B
comma
id|pirq_amd756_get
comma
id|pirq_amd756_set
)brace
comma
(brace
l_string|&quot;default&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|pirq_router
r_static
r_struct
id|irq_router
op_star
id|pirq_router
suffix:semicolon
DECL|variable|pirq_router_dev
r_static
r_struct
id|pci_dev
op_star
id|pirq_router_dev
suffix:semicolon
DECL|function|pirq_find_router
r_static
r_void
id|__init
id|pirq_find_router
c_func
(paren
r_void
)paren
(brace
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
id|pirq_table
suffix:semicolon
r_struct
id|irq_router
op_star
id|r
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Attempting to find IRQ router for %04x:%04x&bslash;n&quot;
comma
id|rt-&gt;rtr_vendor
comma
id|rt-&gt;rtr_device
)paren
suffix:semicolon
multiline_comment|/* fall back to default router if nothing else found */
id|pirq_router
op_assign
op_amp
id|pirq_routers
(braket
id|ARRAY_SIZE
c_func
(paren
id|pirq_routers
)paren
op_minus
l_int|1
)braket
suffix:semicolon
id|pirq_router_dev
op_assign
id|pci_find_slot
c_func
(paren
id|rt-&gt;rtr_bus
comma
id|rt-&gt;rtr_devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pirq_router_dev
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Interrupt router not found at %02x:%02x&bslash;n&quot;
comma
id|rt-&gt;rtr_bus
comma
id|rt-&gt;rtr_devfn
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|r
op_assign
id|pirq_routers
suffix:semicolon
id|r-&gt;vendor
suffix:semicolon
id|r
op_increment
)paren
(brace
multiline_comment|/* Exact match against router table entry? Use it! */
r_if
c_cond
(paren
id|r-&gt;vendor
op_eq
id|rt-&gt;rtr_vendor
op_logical_and
id|r-&gt;device
op_eq
id|rt-&gt;rtr_device
)paren
(brace
id|pirq_router
op_assign
id|r
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Match against router device entry? Use it as a fallback */
r_if
c_cond
(paren
id|r-&gt;vendor
op_eq
id|pirq_router_dev-&gt;vendor
op_logical_and
id|r-&gt;device
op_eq
id|pirq_router_dev-&gt;device
)paren
(brace
id|pirq_router
op_assign
id|r
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using IRQ router %s [%04x/%04x] at %s&bslash;n&quot;
comma
id|pirq_router-&gt;name
comma
id|pirq_router_dev-&gt;vendor
comma
id|pirq_router_dev-&gt;device
comma
id|pirq_router_dev-&gt;slot_name
)paren
suffix:semicolon
)brace
DECL|function|pirq_get_info
r_static
r_struct
id|irq_info
op_star
id|pirq_get_info
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
id|pirq_table
suffix:semicolon
r_int
id|entries
op_assign
(paren
id|rt-&gt;size
op_minus
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
op_div
r_sizeof
(paren
r_struct
id|irq_info
)paren
suffix:semicolon
r_struct
id|irq_info
op_star
id|info
suffix:semicolon
r_for
c_loop
(paren
id|info
op_assign
id|rt-&gt;slots
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
id|info
op_increment
)paren
r_if
c_cond
(paren
id|info-&gt;bus
op_eq
id|dev-&gt;bus-&gt;number
op_logical_and
id|PCI_SLOT
c_func
(paren
id|info-&gt;devfn
)paren
op_eq
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
r_return
id|info
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pcibios_test_irq_handler
r_static
id|irqreturn_t
id|pcibios_test_irq_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|IRQ_NONE
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
r_int
id|assign
)paren
(brace
id|u8
id|pin
suffix:semicolon
r_struct
id|irq_info
op_star
id|info
suffix:semicolon
r_int
id|i
comma
id|pirq
comma
id|newirq
suffix:semicolon
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
id|u32
id|mask
suffix:semicolon
r_struct
id|irq_router
op_star
id|r
op_assign
id|pirq_router
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev2
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Find IRQ pin */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pin
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; no interrupt pin&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pin
op_assign
id|pin
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Find IRQ routing entry */
r_if
c_cond
(paren
op_logical_neg
id|pirq_table
)paren
r_return
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;IRQ for %s:%d&quot;
comma
id|dev-&gt;slot_name
comma
id|pin
)paren
suffix:semicolon
id|info
op_assign
id|pirq_get_info
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; not found in routing table&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pirq
op_assign
id|info-&gt;irq
(braket
id|pin
)braket
dot
id|link
suffix:semicolon
id|mask
op_assign
id|info-&gt;irq
(braket
id|pin
)braket
dot
id|bitmap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pirq
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; not routed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; PIRQ %02x, mask %04x, excl %04x&quot;
comma
id|pirq
comma
id|mask
comma
id|pirq_table-&gt;exclusive_irqs
)paren
suffix:semicolon
id|mask
op_and_assign
id|pcibios_irq_mask
suffix:semicolon
multiline_comment|/* Work around broken HP Pavilion Notebooks which assign USB to&n;&t;   IRQ 9 even though it is actually wired to IRQ 11 */
r_if
c_cond
(paren
id|broken_hp_bios_irq9
op_logical_and
id|pirq
op_eq
l_int|0x59
op_logical_and
id|dev-&gt;irq
op_eq
l_int|9
)paren
(brace
id|dev-&gt;irq
op_assign
l_int|11
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
l_int|11
)paren
suffix:semicolon
id|r
op_member_access_from_pointer
id|set
c_func
(paren
id|pirq_router_dev
comma
id|dev
comma
id|pirq
comma
l_int|11
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Find the best IRQ to assign: use the one&n;&t; * reported by the device if possible.&n;&t; */
id|newirq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|newirq
)paren
op_amp
id|mask
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_USE_PIRQ_MASK
)paren
id|newirq
op_assign
l_int|0
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: IRQ %i for device %s doesn&squot;t match PIRQ mask - try pci=usepirqmask&bslash;n&quot;
comma
id|newirq
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|newirq
op_logical_and
id|assign
)paren
(brace
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
(brace
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
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pirq_penalty
(braket
id|i
)braket
OL
id|pirq_penalty
(braket
id|newirq
)braket
op_logical_and
op_logical_neg
id|request_irq
c_func
(paren
id|i
comma
id|pcibios_test_irq_handler
comma
id|SA_SHIRQ
comma
l_string|&quot;pci-test&quot;
comma
id|dev
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|i
comma
id|dev
)paren
suffix:semicolon
id|newirq
op_assign
id|i
suffix:semicolon
)brace
)brace
)brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; newirq=%d&quot;
comma
id|newirq
)paren
suffix:semicolon
multiline_comment|/* Check if it is hardcoded */
r_if
c_cond
(paren
(paren
id|pirq
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xf0
)paren
(brace
id|irq
op_assign
id|pirq
op_amp
l_int|0xf
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; -&gt; hardcoded IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|msg
op_assign
l_string|&quot;Hardcoded&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r-&gt;get
op_logical_and
(paren
id|irq
op_assign
id|r
op_member_access_from_pointer
id|get
c_func
(paren
id|pirq_router_dev
comma
id|dev
comma
id|pirq
)paren
)paren
op_logical_and
"&bslash;"
(paren
(paren
op_logical_neg
(paren
id|pci_probe
op_amp
id|PCI_USE_PIRQ_MASK
)paren
)paren
op_logical_or
(paren
(paren
l_int|1
op_lshift
id|irq
)paren
op_amp
id|mask
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; got IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|msg
op_assign
l_string|&quot;Found&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|newirq
op_logical_and
id|r-&gt;set
op_logical_and
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_DISPLAY_VGA
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; -&gt; assigning IRQ %d&quot;
comma
id|newirq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_member_access_from_pointer
id|set
c_func
(paren
id|pirq_router_dev
comma
id|dev
comma
id|pirq
comma
id|newirq
)paren
)paren
(brace
id|eisa_set_level_irq
c_func
(paren
id|newirq
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; ... OK&bslash;n&quot;
)paren
suffix:semicolon
id|msg
op_assign
l_string|&quot;Assigned&quot;
suffix:semicolon
id|irq
op_assign
id|newirq
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|irq
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot; ... failed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newirq
op_logical_and
id|mask
op_eq
(paren
l_int|1
op_lshift
id|newirq
)paren
)paren
(brace
id|msg
op_assign
l_string|&quot;Guessed&quot;
suffix:semicolon
id|irq
op_assign
id|newirq
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: %s IRQ %d for device %s&bslash;n&quot;
comma
id|msg
comma
id|irq
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* Update IRQ for all devices with the same pirq value */
r_while
c_loop
(paren
(paren
id|dev2
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev2
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev2
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pin
)paren
r_continue
suffix:semicolon
id|pin
op_decrement
suffix:semicolon
id|info
op_assign
id|pirq_get_info
c_func
(paren
id|dev2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;irq
(braket
id|pin
)braket
dot
id|link
op_eq
id|pirq
)paren
(brace
multiline_comment|/* We refuse to override the dev-&gt;irq information. Give a warning! */
r_if
c_cond
(paren
id|dev2-&gt;irq
op_logical_and
id|dev2-&gt;irq
op_ne
id|irq
op_logical_and
"&bslash;"
(paren
op_logical_neg
(paren
id|pci_probe
op_amp
id|PCI_USE_PIRQ_MASK
)paren
op_logical_or
"&bslash;"
(paren
(paren
l_int|1
op_lshift
id|dev2-&gt;irq
)paren
op_amp
id|mask
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IRQ routing conflict for %s, have irq %d, want irq %d&bslash;n&quot;
comma
id|dev2-&gt;slot_name
comma
id|dev2-&gt;irq
comma
id|irq
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dev2-&gt;irq
op_assign
id|irq
suffix:semicolon
id|pirq_penalty
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ne
id|dev2
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Sharing IRQ %d with %s&bslash;n&quot;
comma
id|irq
comma
id|dev2-&gt;slot_name
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
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
id|u8
id|pin
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: IRQ fixup&bslash;n&quot;
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
multiline_comment|/*&n;&t;&t; * If the BIOS has set an out of range IRQ number, just ignore it.&n;&t;&t; * Also keep track of which IRQ&squot;s are already in use.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|16
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%s: ignoring bogus IRQ %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If the IRQ is already assigned to a PCI device, ignore its ISA use penalty */
r_if
c_cond
(paren
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
op_ge
l_int|100
op_logical_and
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
OL
l_int|100000
)paren
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
id|pirq_penalty
(braket
id|dev-&gt;irq
)braket
op_increment
suffix:semicolon
)brace
id|dev
op_assign
l_int|NULL
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
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_IO_APIC
multiline_comment|/*&n;&t;&t; * Recalculate IRQ numbers if we use the I/O APIC.&n;&t;&t; */
r_if
c_cond
(paren
id|io_apic_assign_pci_irqs
)paren
(brace
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|pin
)paren
(brace
id|pin
op_decrement
suffix:semicolon
multiline_comment|/* interrupt pins are numbered starting from 1 */
id|irq
op_assign
id|IO_APIC_get_PCI_irq_vector
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|pin
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Busses behind bridges are typically not listed in the MP-table.&n;&t; * In this case we have to look up the IRQ based on the parent bus,&n;&t; * parent slot, and pin number. The SMP code detects such bridged&n;&t; * busses itself so we should get into this branch reliably.&n;&t; */
r_if
c_cond
(paren
id|irq
OL
l_int|0
op_logical_and
id|dev-&gt;bus-&gt;parent
)paren
(brace
multiline_comment|/* go back to the bridge */
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
id|pin
op_assign
(paren
id|pin
op_plus
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
op_mod
l_int|4
suffix:semicolon
id|irq
op_assign
id|IO_APIC_get_PCI_irq_vector
c_func
(paren
id|bridge-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|bridge-&gt;devfn
)paren
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: using PPB(B%d,I%d,P%d) to get irq %d&bslash;n&quot;
comma
id|bridge-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|bridge-&gt;devfn
)paren
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI-&gt;APIC IRQ transform: (B%d,I%d,P%d) -&gt; %d&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Still no IRQ? Try to lookup one...&n;&t;&t; */
r_if
c_cond
(paren
id|pin
op_logical_and
op_logical_neg
id|dev-&gt;irq
)paren
id|pcibios_lookup_irq
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_irq_init
r_static
r_int
id|__init
id|pcibios_irq_init
c_func
(paren
r_void
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: IRQ init&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_enable_irq
)paren
r_return
l_int|0
suffix:semicolon
id|pirq_table
op_assign
id|pirq_find_routing_table
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pirq_table
)paren
(brace
id|pirq_peer_trick
c_func
(paren
)paren
suffix:semicolon
id|pirq_find_router
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pirq_table-&gt;exclusive_irqs
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|pirq_table-&gt;exclusive_irqs
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|pirq_penalty
(braket
id|i
)braket
op_add_assign
l_int|100
suffix:semicolon
)brace
multiline_comment|/* If we&squot;re using the I/O APIC, avoid using the PCI IRQ routing table */
r_if
c_cond
(paren
id|io_apic_assign_pci_irqs
)paren
id|pirq_table
op_assign
l_int|NULL
suffix:semicolon
)brace
id|pcibios_enable_irq
op_assign
id|pirq_enable_irq
suffix:semicolon
id|pcibios_fixup_irqs
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_irq_init
id|subsys_initcall
c_func
(paren
id|pcibios_irq_init
)paren
suffix:semicolon
DECL|function|pcibios_penalize_isa_irq
r_void
id|pcibios_penalize_isa_irq
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; *  If any ISAPnP device reports an IRQ in its list of possible&n;&t; *  IRQ&squot;s, we try to avoid assigning it to PCI devices.&n;&t; */
id|pirq_penalty
(braket
id|irq
)braket
op_add_assign
l_int|100
suffix:semicolon
)brace
DECL|function|pirq_enable_irq
r_int
id|pirq_enable_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|pin
suffix:semicolon
r_extern
r_int
id|interrupt_line_quirk
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pin
op_logical_and
op_logical_neg
id|pcibios_lookup_irq
c_func
(paren
id|dev
comma
l_int|1
)paren
op_logical_and
op_logical_neg
id|dev-&gt;irq
)paren
(brace
multiline_comment|/* With IDE legacy devices the IRQ lookup failure is not a problem.. */
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_STORAGE_IDE
op_logical_and
op_logical_neg
(paren
id|dev
op_member_access_from_pointer
r_class
op_amp
l_int|0x5
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: No IRQ known for interrupt pin %c of device %s.&bslash;n&quot;
comma
l_char|&squot;A&squot;
op_plus
id|pin
op_minus
l_int|1
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
)brace
multiline_comment|/* VIA bridges use interrupt line for apic/pci steering across&n;&t;   the V-Link */
r_else
r_if
c_cond
(paren
id|interrupt_line_quirk
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
