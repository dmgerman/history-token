multiline_comment|/* $Id: ebus.c,v 1.20 2002/01/05 01:13:43 davem Exp $&n; * ebus.c: PCI to EBus bridge device.&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; *&n; * Adopted for sparc by V. Roganov and G. Raiko.&n; * Fixes for different platforms by Pete Zaitcev.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/bpp.h&gt;
DECL|variable|ebus_chain
r_struct
id|linux_ebus
op_star
id|ebus_chain
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
id|rs_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* We are together with pcic.c under CONFIG_PCI. */
r_extern
r_int
r_int
id|pcic_pin_to_irq
c_func
(paren
r_int
r_int
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/*&n; * IRQ Blacklist&n; * Here we list PROMs and systems that are known to supply crap as IRQ numbers.&n; */
DECL|struct|ebus_device_irq
r_struct
id|ebus_device_irq
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|pin
r_int
r_int
id|pin
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebus_system_entry
r_struct
id|ebus_system_entry
(brace
DECL|member|esname
r_char
op_star
id|esname
suffix:semicolon
DECL|member|ipt
r_struct
id|ebus_device_irq
op_star
id|ipt
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|je1_1
r_static
r_struct
id|ebus_device_irq
id|je1_1
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;8042&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;SUNW,CS4231&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;parallel&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;se&quot;
comma
l_int|2
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Gleb&squot;s JE1 supplied reasonable pin numbers, but mine did not (OBP 2.32).&n; * Blacklist the sucker... Note that Gleb&squot;s system will work.&n; */
DECL|variable|ebus_blacklist
r_static
r_struct
id|ebus_system_entry
id|ebus_blacklist
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SUNW,JavaEngine1&quot;
comma
id|je1_1
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ebus_blackp
r_static
r_struct
id|ebus_device_irq
op_star
id|ebus_blackp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; */
DECL|function|ebus_alloc
r_static
r_inline
r_int
r_int
id|ebus_alloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|ebus_blacklist_irq
r_int
id|__init
id|ebus_blacklist_irq
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|ebus_device_irq
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp
op_assign
id|ebus_blackp
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|dp-&gt;name
op_ne
l_int|NULL
suffix:semicolon
id|dp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
id|dp-&gt;name
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|pcic_pin_to_irq
c_func
(paren
id|dp-&gt;pin
comma
id|name
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fill_ebus_child
r_void
id|__init
id|fill_ebus_child
c_func
(paren
r_int
id|node
comma
r_struct
id|linux_prom_registers
op_star
id|preg
comma
r_struct
id|linux_ebus_child
op_star
id|dev
)paren
(brace
r_int
id|regs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_int
id|irqs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_char
id|lbuf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
id|dev-&gt;prom_node
op_assign
id|node
suffix:semicolon
id|prom_getstring
c_func
(paren
id|node
comma
l_string|&quot;name&quot;
comma
id|lbuf
comma
r_sizeof
(paren
id|lbuf
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;prom_name
comma
id|lbuf
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
id|len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;num_addrs
op_assign
id|len
op_div
r_sizeof
(paren
id|regs
(braket
l_int|0
)braket
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
id|dev-&gt;num_addrs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|regs
(braket
id|i
)braket
op_ge
id|dev-&gt;parent-&gt;num_addrs
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;UGH: property for %s was %d, need &lt; %d&bslash;n&quot;
comma
id|dev-&gt;prom_name
comma
id|len
comma
id|dev-&gt;parent-&gt;num_addrs
)paren
suffix:semicolon
id|panic
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
)brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|dev-&gt;parent-&gt;resource
(braket
id|regs
(braket
id|i
)braket
)braket
dot
id|start
suffix:semicolon
multiline_comment|/* XXX resource */
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PROMINTR_MAX
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;irqs
(braket
id|i
)braket
op_assign
id|PCI_IRQ_NONE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|ebus_blacklist_irq
c_func
(paren
id|dev-&gt;prom_name
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|dev-&gt;num_irqs
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;interrupts&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|irqs
comma
r_sizeof
(paren
id|irqs
)paren
)paren
)paren
op_eq
op_minus
l_int|1
op_logical_or
id|len
op_eq
l_int|0
)paren
(brace
id|dev-&gt;num_irqs
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;parent-&gt;num_irqs
op_ne
l_int|0
)paren
(brace
id|dev-&gt;num_irqs
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|dev-&gt;parent-&gt;irqs
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* P3 */
multiline_comment|/* printk(&quot;EBUS: dev %s irq %d from parent&bslash;n&quot;, dev-&gt;prom_name, dev-&gt;irqs[0]); */
)brace
)brace
r_else
(brace
id|dev-&gt;num_irqs
op_assign
id|len
op_div
r_sizeof
(paren
id|irqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqs
(braket
l_int|0
)braket
op_eq
l_int|0
op_logical_or
id|irqs
(braket
l_int|0
)braket
op_ge
l_int|8
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * XXX Zero is a valid pin number...&n;&t;&t;&t; * This works as long as Ebus is not wired to INTA#.&n;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;EBUS: %s got bad irq %d from PROM&bslash;n&quot;
comma
id|dev-&gt;prom_name
comma
id|irqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|dev-&gt;num_irqs
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|pcic_pin_to_irq
c_func
(paren
id|irqs
(braket
l_int|0
)braket
comma
id|dev-&gt;prom_name
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fill_ebus_device
r_void
id|__init
id|fill_ebus_device
c_func
(paren
r_int
id|node
comma
r_struct
id|linux_ebus_device
op_star
id|dev
)paren
(brace
r_struct
id|linux_prom_registers
id|regs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_struct
id|linux_ebus_child
op_star
id|child
suffix:semicolon
r_int
id|irqs
(braket
id|PROMINTR_MAX
)braket
suffix:semicolon
r_char
id|lbuf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|i
comma
id|n
comma
id|len
suffix:semicolon
r_int
r_int
id|baseaddr
suffix:semicolon
id|dev-&gt;prom_node
op_assign
id|node
suffix:semicolon
id|prom_getstring
c_func
(paren
id|node
comma
l_string|&quot;name&quot;
comma
id|lbuf
comma
r_sizeof
(paren
id|lbuf
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;prom_name
comma
id|lbuf
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_mod
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;UGH: proplen for %s was %d, need multiple of %d&bslash;n&quot;
comma
id|dev-&gt;prom_name
comma
id|len
comma
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
)brace
id|dev-&gt;num_addrs
op_assign
id|len
op_div
r_sizeof
(paren
r_struct
id|linux_prom_registers
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
id|dev-&gt;num_addrs
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * XXX Collect JE-1 PROM&n;&t;&t; * &n;&t;&t; * Example - JS-E with 3.11:&n;&t;&t; *  /ebus&n;&t;&t; *      regs &n;&t;&t; *        0x00000000, 0x0, 0x00000000, 0x0, 0x00000000,&n;&t;&t; *        0x82000010, 0x0, 0xf0000000, 0x0, 0x01000000,&n;&t;&t; *        0x82000014, 0x0, 0x38800000, 0x0, 0x00800000,&n;&t;&t; *      ranges&n;&t;&t; *        0x00, 0x00000000, 0x02000010, 0x0, 0x0, 0x01000000,&n;&t;&t; *        0x01, 0x01000000, 0x02000014, 0x0, 0x0, 0x00800000,&n;&t;&t; *  /ebus/8042&n;&t;&t; *      regs&n;&t;&t; *        0x00000001, 0x00300060, 0x00000008,&n;&t;&t; *        0x00000001, 0x00300060, 0x00000008,&n;&t;&t; */
id|n
op_assign
id|regs
(braket
id|i
)braket
dot
id|which_io
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
l_int|4
)paren
(brace
multiline_comment|/* XXX This is copied from old JE-1 by Gleb. */
id|n
op_assign
(paren
id|regs
(braket
id|i
)braket
dot
id|which_io
op_minus
l_int|0x10
)paren
op_rshift
l_int|2
suffix:semicolon
)brace
r_else
(brace
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX Now as we have regions, why don&squot;t we make an on-demand allocation...&n; */
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|baseaddr
op_assign
id|dev-&gt;bus-&gt;self-&gt;resource
(braket
id|n
)braket
dot
id|start
op_plus
id|regs
(braket
id|i
)braket
dot
id|phys_addr
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* dev-&gt;resource[i].name = dev-&gt;prom_name; */
r_if
c_cond
(paren
(paren
id|baseaddr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|baseaddr
comma
id|regs
(braket
id|i
)braket
dot
id|reg_size
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;ebus: unable to remap dev %s&quot;
comma
id|dev-&gt;prom_name
)paren
suffix:semicolon
)brace
)brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|baseaddr
suffix:semicolon
multiline_comment|/* XXX Unaligned */
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PROMINTR_MAX
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;irqs
(braket
id|i
)braket
op_assign
id|PCI_IRQ_NONE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|ebus_blacklist_irq
c_func
(paren
id|dev-&gt;prom_name
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|dev-&gt;num_irqs
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;interrupts&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|irqs
comma
r_sizeof
(paren
id|irqs
)paren
)paren
)paren
op_eq
op_minus
l_int|1
op_logical_or
id|len
op_eq
l_int|0
)paren
(brace
id|dev-&gt;num_irqs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|dev-&gt;bus-&gt;self-&gt;irq
)paren
op_ne
l_int|0
)paren
(brace
id|dev-&gt;num_irqs
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* P3 */
multiline_comment|/* printk(&quot;EBUS: child %s irq %d from parent&bslash;n&quot;, dev-&gt;prom_name, dev-&gt;irqs[0]); */
)brace
)brace
r_else
(brace
id|dev-&gt;num_irqs
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* dev-&gt;num_irqs = len / sizeof(irqs[0]); */
r_if
c_cond
(paren
id|irqs
(braket
l_int|0
)braket
op_eq
l_int|0
op_logical_or
id|irqs
(braket
l_int|0
)braket
op_ge
l_int|8
)paren
(brace
multiline_comment|/* See above for the parent. XXX */
id|printk
c_func
(paren
l_string|&quot;EBUS: %s got bad irq %d from PROM&bslash;n&quot;
comma
id|dev-&gt;prom_name
comma
id|irqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|dev-&gt;num_irqs
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;irqs
(braket
l_int|0
)braket
op_assign
id|pcic_pin_to_irq
c_func
(paren
id|irqs
(braket
l_int|0
)braket
comma
id|dev-&gt;prom_name
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|node
op_assign
id|prom_getchild
c_func
(paren
id|node
)paren
)paren
)paren
(brace
id|dev-&gt;children
op_assign
(paren
r_struct
id|linux_ebus_child
op_star
)paren
id|ebus_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|linux_ebus_child
)paren
)paren
suffix:semicolon
id|child
op_assign
id|dev-&gt;children
suffix:semicolon
id|child-&gt;next
op_assign
l_int|0
suffix:semicolon
id|child-&gt;parent
op_assign
id|dev
suffix:semicolon
id|child-&gt;bus
op_assign
id|dev-&gt;bus
suffix:semicolon
id|fill_ebus_child
c_func
(paren
id|node
comma
op_amp
id|regs
(braket
l_int|0
)braket
comma
id|child
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|node
op_assign
id|prom_getsibling
c_func
(paren
id|node
)paren
)paren
)paren
(brace
id|child-&gt;next
op_assign
(paren
r_struct
id|linux_ebus_child
op_star
)paren
id|ebus_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|linux_ebus_child
)paren
)paren
suffix:semicolon
id|child
op_assign
id|child-&gt;next
suffix:semicolon
id|child-&gt;next
op_assign
l_int|0
suffix:semicolon
id|child-&gt;parent
op_assign
id|dev
suffix:semicolon
id|child-&gt;bus
op_assign
id|dev-&gt;bus
suffix:semicolon
id|fill_ebus_child
c_func
(paren
id|node
comma
op_amp
id|regs
(braket
l_int|0
)braket
comma
id|child
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|ebus_init
r_void
id|__init
id|ebus_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_prom_pci_registers
id|regs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_struct
id|linux_pbm_info
op_star
id|pbm
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|dev
suffix:semicolon
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|ebus_system_entry
op_star
id|sp
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|pcidev_cookie
op_star
id|cookie
suffix:semicolon
r_char
id|lbuf
(braket
l_int|128
)braket
suffix:semicolon
r_int
r_int
id|addr
comma
op_star
id|base
suffix:semicolon
r_int
r_int
id|pci_command
suffix:semicolon
r_int
id|nd
comma
id|len
comma
id|ebusnd
suffix:semicolon
r_int
id|reg
comma
id|nreg
suffix:semicolon
r_int
id|num_ebus
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_root_node
comma
l_string|&quot;name&quot;
comma
id|lbuf
comma
r_sizeof
(paren
id|lbuf
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sp
op_assign
id|ebus_blacklist
suffix:semicolon
id|sp-&gt;esname
op_ne
l_int|NULL
suffix:semicolon
id|sp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|lbuf
comma
id|sp-&gt;esname
)paren
op_eq
l_int|0
)paren
(brace
id|ebus_blackp
op_assign
id|sp-&gt;ipt
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_SUN
comma
id|PCI_DEVICE_ID_SUN_EBUS
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
(brace
r_return
suffix:semicolon
)brace
id|cookie
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
id|ebusnd
op_assign
id|cookie-&gt;prom_node
suffix:semicolon
id|ebus_chain
op_assign
id|ebus
op_assign
(paren
r_struct
id|linux_ebus
op_star
)paren
id|ebus_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|linux_ebus
)paren
)paren
suffix:semicolon
id|ebus-&gt;next
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ebusnd
)paren
(brace
id|prom_getstring
c_func
(paren
id|ebusnd
comma
l_string|&quot;name&quot;
comma
id|lbuf
comma
r_sizeof
(paren
id|lbuf
)paren
)paren
suffix:semicolon
id|ebus-&gt;prom_node
op_assign
id|ebusnd
suffix:semicolon
id|strcpy
c_func
(paren
id|ebus-&gt;prom_name
comma
id|lbuf
)paren
suffix:semicolon
id|ebus-&gt;self
op_assign
id|pdev
suffix:semicolon
id|ebus-&gt;parent
op_assign
id|pbm
op_assign
id|cookie-&gt;pbm
suffix:semicolon
multiline_comment|/* Enable BUS Master. */
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|PCI_COMMAND
comma
op_amp
id|pci_command
)paren
suffix:semicolon
id|pci_command
op_or_assign
id|PCI_COMMAND_MASTER
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pdev
comma
id|PCI_COMMAND
comma
id|pci_command
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|ebusnd
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
op_logical_or
id|len
op_eq
op_minus
l_int|1
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;%s: can&squot;t find reg property&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|nreg
op_assign
id|len
op_div
r_sizeof
(paren
r_struct
id|linux_prom_pci_registers
)paren
suffix:semicolon
id|base
op_assign
op_amp
id|ebus-&gt;self-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
r_for
c_loop
(paren
id|reg
op_assign
l_int|0
suffix:semicolon
id|reg
OL
id|nreg
suffix:semicolon
id|reg
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs
(braket
id|reg
)braket
dot
id|which_io
op_amp
l_int|0x03000000
)paren
)paren
r_continue
suffix:semicolon
id|addr
op_assign
id|regs
(braket
id|reg
)braket
dot
id|phys_lo
suffix:semicolon
op_star
id|base
op_increment
op_assign
id|addr
suffix:semicolon
)brace
id|nd
op_assign
id|prom_getchild
c_func
(paren
id|ebusnd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nd
)paren
r_goto
id|next_ebus
suffix:semicolon
id|ebus-&gt;devices
op_assign
(paren
r_struct
id|linux_ebus_device
op_star
)paren
id|ebus_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|linux_ebus_device
)paren
)paren
suffix:semicolon
id|dev
op_assign
id|ebus-&gt;devices
suffix:semicolon
id|dev-&gt;next
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;children
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;bus
op_assign
id|ebus
suffix:semicolon
id|fill_ebus_device
c_func
(paren
id|nd
comma
id|dev
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|nd
op_assign
id|prom_getsibling
c_func
(paren
id|nd
)paren
)paren
)paren
(brace
id|dev-&gt;next
op_assign
(paren
r_struct
id|linux_ebus_device
op_star
)paren
id|ebus_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|linux_ebus_device
)paren
)paren
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
id|dev-&gt;next
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;children
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;bus
op_assign
id|ebus
suffix:semicolon
id|fill_ebus_device
c_func
(paren
id|nd
comma
id|dev
)paren
suffix:semicolon
)brace
id|next_ebus
suffix:colon
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_SUN
comma
id|PCI_DEVICE_ID_SUN_EBUS
comma
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
r_break
suffix:semicolon
id|cookie
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
id|ebusnd
op_assign
id|cookie-&gt;prom_node
suffix:semicolon
id|ebus-&gt;next
op_assign
(paren
r_struct
id|linux_ebus
op_star
)paren
id|ebus_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|linux_ebus
)paren
)paren
suffix:semicolon
id|ebus
op_assign
id|ebus-&gt;next
suffix:semicolon
id|ebus-&gt;next
op_assign
l_int|0
suffix:semicolon
op_increment
id|num_ebus
suffix:semicolon
)brace
id|rs_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
