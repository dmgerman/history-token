multiline_comment|/*&n; *  arch/mips/ddb5476/nile4.c --&n; *  &t;low-level PIC code for NEC Vrc-5476 (Nile 4)&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; *&n; *  Copyright 2001 MontaVista Software Inc.&n; *  Author: jsun@mvista.com or jsun@junsun.net&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
DECL|variable|irq_base
r_static
r_int
id|irq_base
suffix:semicolon
multiline_comment|/*&n; *  Interrupt Programming&n; */
DECL|function|nile4_map_irq
r_void
id|nile4_map_irq
c_func
(paren
r_int
id|nile4_irq
comma
r_int
id|cpu_irq
)paren
(brace
id|u32
id|offset
comma
id|t
suffix:semicolon
id|offset
op_assign
id|DDB_INTCTRL
suffix:semicolon
r_if
c_cond
(paren
id|nile4_irq
op_ge
l_int|8
)paren
(brace
id|offset
op_add_assign
l_int|4
suffix:semicolon
id|nile4_irq
op_sub_assign
l_int|8
suffix:semicolon
)brace
id|t
op_assign
id|ddb_in32
c_func
(paren
id|offset
)paren
suffix:semicolon
id|t
op_and_assign
op_complement
(paren
l_int|7
op_lshift
(paren
id|nile4_irq
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|t
op_or_assign
id|cpu_irq
op_lshift
(paren
id|nile4_irq
op_star
l_int|4
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|offset
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_map_irq_all
r_void
id|nile4_map_irq_all
c_func
(paren
r_int
id|cpu_irq
)paren
(brace
id|u32
id|all
comma
id|t
suffix:semicolon
id|all
op_assign
id|cpu_irq
suffix:semicolon
id|all
op_or_assign
id|all
op_lshift
l_int|4
suffix:semicolon
id|all
op_or_assign
id|all
op_lshift
l_int|8
suffix:semicolon
id|all
op_or_assign
id|all
op_lshift
l_int|16
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|DDB_INTCTRL
)paren
suffix:semicolon
id|t
op_and_assign
l_int|0x88888888
suffix:semicolon
id|t
op_or_assign
id|all
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTCTRL
comma
id|t
)paren
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|DDB_INTCTRL
op_plus
l_int|4
)paren
suffix:semicolon
id|t
op_and_assign
l_int|0x88888888
suffix:semicolon
id|t
op_or_assign
id|all
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTCTRL
op_plus
l_int|4
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_enable_irq
r_void
id|nile4_enable_irq
c_func
(paren
r_int
r_int
id|nile4_irq
)paren
(brace
id|u32
id|offset
comma
id|t
suffix:semicolon
id|nile4_irq
op_sub_assign
id|irq_base
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|offset
op_assign
id|DDB_INTCTRL
suffix:semicolon
r_if
c_cond
(paren
id|nile4_irq
op_ge
l_int|8
)paren
(brace
id|offset
op_add_assign
l_int|4
suffix:semicolon
id|nile4_irq
op_sub_assign
l_int|8
suffix:semicolon
)brace
id|ddb5074_led_hex
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|offset
)paren
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|t
op_or_assign
l_int|8
op_lshift
(paren
id|nile4_irq
op_star
l_int|4
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|offset
comma
id|t
)paren
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
)brace
DECL|function|nile4_disable_irq
r_void
id|nile4_disable_irq
c_func
(paren
r_int
r_int
id|nile4_irq
)paren
(brace
id|u32
id|offset
comma
id|t
suffix:semicolon
id|nile4_irq
op_sub_assign
id|irq_base
suffix:semicolon
id|offset
op_assign
id|DDB_INTCTRL
suffix:semicolon
r_if
c_cond
(paren
id|nile4_irq
op_ge
l_int|8
)paren
(brace
id|offset
op_add_assign
l_int|4
suffix:semicolon
id|nile4_irq
op_sub_assign
l_int|8
suffix:semicolon
)brace
id|t
op_assign
id|ddb_in32
c_func
(paren
id|offset
)paren
suffix:semicolon
id|t
op_and_assign
op_complement
(paren
l_int|8
op_lshift
(paren
id|nile4_irq
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|offset
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_disable_irq_all
r_void
id|nile4_disable_irq_all
c_func
(paren
r_void
)paren
(brace
id|ddb_out32
c_func
(paren
id|DDB_INTCTRL
comma
l_int|0
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTCTRL
op_plus
l_int|4
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|nile4_get_irq_stat
id|u16
id|nile4_get_irq_stat
c_func
(paren
r_int
id|cpu_irq
)paren
(brace
r_return
id|ddb_in16
c_func
(paren
id|DDB_INTSTAT0
op_plus
id|cpu_irq
op_star
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|nile4_enable_irq_output
r_void
id|nile4_enable_irq_output
c_func
(paren
r_int
id|cpu_irq
)paren
(brace
id|u32
id|t
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|DDB_INTSTAT1
op_plus
l_int|4
)paren
suffix:semicolon
id|t
op_or_assign
l_int|1
op_lshift
(paren
l_int|16
op_plus
id|cpu_irq
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTSTAT1
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_disable_irq_output
r_void
id|nile4_disable_irq_output
c_func
(paren
r_int
id|cpu_irq
)paren
(brace
id|u32
id|t
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|DDB_INTSTAT1
op_plus
l_int|4
)paren
suffix:semicolon
id|t
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|16
op_plus
id|cpu_irq
)paren
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTSTAT1
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_set_pci_irq_polarity
r_void
id|nile4_set_pci_irq_polarity
c_func
(paren
r_int
id|pci_irq
comma
r_int
id|high
)paren
(brace
id|u32
id|t
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|DDB_INTPPES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
)paren
id|t
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|pci_irq
op_star
l_int|2
)paren
)paren
suffix:semicolon
r_else
id|t
op_or_assign
l_int|1
op_lshift
(paren
id|pci_irq
op_star
l_int|2
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTPPES
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_set_pci_irq_level_or_edge
r_void
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
r_int
id|pci_irq
comma
r_int
id|level
)paren
(brace
id|u32
id|t
suffix:semicolon
id|t
op_assign
id|ddb_in32
c_func
(paren
id|DDB_INTPPES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
)paren
id|t
op_or_assign
l_int|2
op_lshift
(paren
id|pci_irq
op_star
l_int|2
)paren
suffix:semicolon
r_else
id|t
op_and_assign
op_complement
(paren
l_int|2
op_lshift
(paren
id|pci_irq
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTPPES
comma
id|t
)paren
suffix:semicolon
)brace
DECL|function|nile4_clear_irq
r_void
id|nile4_clear_irq
c_func
(paren
r_int
id|nile4_irq
)paren
(brace
id|nile4_irq
op_sub_assign
id|irq_base
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_INTCLR
comma
l_int|1
op_lshift
id|nile4_irq
)paren
suffix:semicolon
)brace
DECL|function|nile4_clear_irq_mask
r_void
id|nile4_clear_irq_mask
c_func
(paren
id|u32
id|mask
)paren
(brace
id|ddb_out32
c_func
(paren
id|DDB_INTCLR
comma
id|mask
)paren
suffix:semicolon
)brace
DECL|function|nile4_i8259_iack
id|u8
id|nile4_i8259_iack
c_func
(paren
r_void
)paren
(brace
id|u8
id|irq
suffix:semicolon
id|u32
id|reg
suffix:semicolon
multiline_comment|/* Set window 0 for interrupt acknowledge */
id|reg
op_assign
id|ddb_in32
c_func
(paren
id|DDB_PCIINIT0
)paren
suffix:semicolon
id|ddb_set_pmr
c_func
(paren
id|DDB_PCIINIT0
comma
id|DDB_PCICMD_IACK
comma
l_int|0
comma
id|DDB_PCI_ACCESS_32
)paren
suffix:semicolon
id|irq
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|DDB_PCI_IACK_BASE
)paren
suffix:semicolon
multiline_comment|/* restore window 0 for PCI I/O space */
singleline_comment|// ddb_set_pmr(DDB_PCIINIT0, DDB_PCICMD_IO, 0, DDB_PCI_ACCESS_32);
id|ddb_out32
c_func
(paren
id|DDB_PCIINIT0
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* i8269.c set the base vector to be 0x0 */
r_return
id|irq
suffix:semicolon
)brace
DECL|function|nile4_irq_startup
r_static
r_int
r_int
id|nile4_irq_startup
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|nile4_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nile4_ack_irq
r_static
r_void
id|nile4_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ddb5074_led_hex
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|nile4_clear_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|nile4_disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|nile4_irq_end
r_static
r_void
id|nile4_irq_end
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ddb5074_led_hex
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
(brace
id|ddb5074_led_hex
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|nile4_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|7
)paren
suffix:semicolon
)brace
id|ddb5074_led_hex
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|nile4_irq_shutdown
mdefine_line|#define nile4_irq_shutdown nile4_disable_irq
DECL|variable|nile4_irq_controller
r_static
id|hw_irq_controller
id|nile4_irq_controller
op_assign
(brace
l_string|&quot;nile4&quot;
comma
id|nile4_irq_startup
comma
id|nile4_irq_shutdown
comma
id|nile4_enable_irq
comma
id|nile4_disable_irq
comma
id|nile4_ack_irq
comma
id|nile4_irq_end
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|nile4_irq_setup
r_void
id|nile4_irq_setup
c_func
(paren
id|u32
id|base
)paren
(brace
r_int
id|i
suffix:semicolon
id|irq_base
op_assign
id|base
suffix:semicolon
multiline_comment|/* Map all interrupts to CPU int #0 */
id|nile4_map_irq_all
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* PCI INTA#-E# must be level triggered */
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
l_int|2
comma
l_int|1
)paren
suffix:semicolon
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
l_int|3
comma
l_int|1
)paren
suffix:semicolon
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
l_int|4
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* PCI INTA#-D# must be active low, INTE# must be active high */
id|nile4_set_pci_irq_polarity
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|nile4_set_pci_irq_polarity
c_func
(paren
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|nile4_set_pci_irq_polarity
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
id|nile4_set_pci_irq_polarity
c_func
(paren
l_int|3
comma
l_int|0
)paren
suffix:semicolon
id|nile4_set_pci_irq_polarity
c_func
(paren
l_int|4
comma
l_int|1
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nile4_clear_irq
c_func
(paren
id|i
)paren
suffix:semicolon
id|nile4_disable_irq
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable CPU int #0 */
id|nile4_enable_irq_output
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|base
suffix:semicolon
id|i
OL
id|base
op_plus
id|NUM_NILE4_INTERRUPTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|nile4_irq_controller
suffix:semicolon
)brace
)brace
macro_line|#if defined(CONFIG_RUNTIME_DEBUG)
DECL|function|nile4_dump_irq_status
r_void
id|nile4_dump_irq_status
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
"&quot;"
id|CPUSTAT
op_assign
op_mod
id|p
suffix:colon
op_mod
id|p
"&bslash;"
id|n
"&quot;"
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_CPUSTAT
op_plus
l_int|4
)paren
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_CPUSTAT
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
"&quot;"
id|INTCTRL
op_assign
op_mod
id|p
suffix:colon
op_mod
id|p
"&bslash;"
id|n
"&quot;"
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTCTRL
op_plus
l_int|4
)paren
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTCTRL
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;INTSTAT0 = %p:%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTSTAT0
op_plus
l_int|4
)paren
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTSTAT0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;INTSTAT1 = %p:%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTSTAT1
op_plus
l_int|4
)paren
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTSTAT1
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;INTCLR = %p:%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTCLR
op_plus
l_int|4
)paren
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTCLR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;INTPPES = %p:%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTPPES
op_plus
l_int|4
)paren
comma
(paren
r_void
op_star
)paren
id|ddb_in32
c_func
(paren
id|DDB_INTPPES
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
