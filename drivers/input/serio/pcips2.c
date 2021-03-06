multiline_comment|/*&n; * linux/drivers/input/serio/pcips2.c&n; *&n; *  Copyright (C) 2003 Russell King, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License.&n; *&n; *  I&squot;m not sure if this is a generic PS/2 PCI interface or specific to&n; *  the Mobility Electronics docking station.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|PS2_CTRL
mdefine_line|#define PS2_CTRL&t;&t;(0)
DECL|macro|PS2_STATUS
mdefine_line|#define PS2_STATUS&t;&t;(1)
DECL|macro|PS2_DATA
mdefine_line|#define PS2_DATA&t;&t;(2)
DECL|macro|PS2_CTRL_CLK
mdefine_line|#define PS2_CTRL_CLK&t;&t;(1&lt;&lt;0)
DECL|macro|PS2_CTRL_DAT
mdefine_line|#define PS2_CTRL_DAT&t;&t;(1&lt;&lt;1)
DECL|macro|PS2_CTRL_TXIRQ
mdefine_line|#define PS2_CTRL_TXIRQ&t;&t;(1&lt;&lt;2)
DECL|macro|PS2_CTRL_ENABLE
mdefine_line|#define PS2_CTRL_ENABLE&t;&t;(1&lt;&lt;3)
DECL|macro|PS2_CTRL_RXIRQ
mdefine_line|#define PS2_CTRL_RXIRQ&t;&t;(1&lt;&lt;4)
DECL|macro|PS2_STAT_CLK
mdefine_line|#define PS2_STAT_CLK&t;&t;(1&lt;&lt;0)
DECL|macro|PS2_STAT_DAT
mdefine_line|#define PS2_STAT_DAT&t;&t;(1&lt;&lt;1)
DECL|macro|PS2_STAT_PARITY
mdefine_line|#define PS2_STAT_PARITY&t;&t;(1&lt;&lt;2)
DECL|macro|PS2_STAT_RXFULL
mdefine_line|#define PS2_STAT_RXFULL&t;&t;(1&lt;&lt;5)
DECL|macro|PS2_STAT_TXBUSY
mdefine_line|#define PS2_STAT_TXBUSY&t;&t;(1&lt;&lt;6)
DECL|macro|PS2_STAT_TXEMPTY
mdefine_line|#define PS2_STAT_TXEMPTY&t;(1&lt;&lt;7)
DECL|struct|pcips2_data
r_struct
id|pcips2_data
(brace
DECL|member|io
r_struct
id|serio
op_star
id|io
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|function|pcips2_write
r_static
r_int
id|pcips2_write
c_func
(paren
r_struct
id|serio
op_star
id|io
comma
r_int
r_char
id|val
)paren
(brace
r_struct
id|pcips2_data
op_star
id|ps2if
op_assign
id|io-&gt;port_data
suffix:semicolon
r_int
r_int
id|stat
suffix:semicolon
r_do
(brace
id|stat
op_assign
id|inb
c_func
(paren
id|ps2if-&gt;base
op_plus
id|PS2_STATUS
)paren
suffix:semicolon
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|stat
op_amp
id|PS2_STAT_TXEMPTY
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|ps2if-&gt;base
op_plus
id|PS2_DATA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcips2_interrupt
r_static
id|irqreturn_t
id|pcips2_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|devid
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pcips2_data
op_star
id|ps2if
op_assign
id|devid
suffix:semicolon
r_int
r_char
id|status
comma
id|scancode
suffix:semicolon
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_int
r_int
id|flag
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|ps2if-&gt;base
op_plus
id|PS2_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|PS2_STAT_RXFULL
)paren
)paren
r_break
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
id|scancode
op_assign
id|inb
c_func
(paren
id|ps2if-&gt;base
op_plus
id|PS2_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0xff
op_logical_and
id|scancode
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
id|flag
op_assign
(paren
id|status
op_amp
id|PS2_STAT_PARITY
)paren
ques
c_cond
l_int|0
suffix:colon
id|SERIO_PARITY
suffix:semicolon
r_if
c_cond
(paren
id|hweight8
c_func
(paren
id|scancode
)paren
op_amp
l_int|1
)paren
id|flag
op_xor_assign
id|SERIO_PARITY
suffix:semicolon
id|serio_interrupt
c_func
(paren
id|ps2if-&gt;io
comma
id|scancode
comma
id|flag
comma
id|regs
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
)brace
DECL|function|pcips2_flush_input
r_static
r_void
id|pcips2_flush_input
c_func
(paren
r_struct
id|pcips2_data
op_star
id|ps2if
)paren
(brace
r_int
r_char
id|status
comma
id|scancode
suffix:semicolon
r_do
(brace
id|status
op_assign
id|inb
c_func
(paren
id|ps2if-&gt;base
op_plus
id|PS2_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|PS2_STAT_RXFULL
)paren
)paren
r_break
suffix:semicolon
id|scancode
op_assign
id|inb
c_func
(paren
id|ps2if-&gt;base
op_plus
id|PS2_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0xff
op_logical_and
id|scancode
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|pcips2_open
r_static
r_int
id|pcips2_open
c_func
(paren
r_struct
id|serio
op_star
id|io
)paren
(brace
r_struct
id|pcips2_data
op_star
id|ps2if
op_assign
id|io-&gt;port_data
suffix:semicolon
r_int
id|ret
comma
id|val
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|PS2_CTRL_ENABLE
comma
id|ps2if-&gt;base
)paren
suffix:semicolon
id|pcips2_flush_input
c_func
(paren
id|ps2if
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
comma
id|pcips2_interrupt
comma
id|SA_SHIRQ
comma
l_string|&quot;pcips2&quot;
comma
id|ps2if
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|val
op_assign
id|PS2_CTRL_ENABLE
op_or
id|PS2_CTRL_RXIRQ
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|ps2if-&gt;base
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcips2_close
r_static
r_void
id|pcips2_close
c_func
(paren
r_struct
id|serio
op_star
id|io
)paren
(brace
r_struct
id|pcips2_data
op_star
id|ps2if
op_assign
id|io-&gt;port_data
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ps2if-&gt;base
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
comma
id|ps2if
)paren
suffix:semicolon
)brace
DECL|function|pcips2_probe
r_static
r_int
id|__devinit
id|pcips2_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|pcips2_data
op_star
id|ps2if
suffix:semicolon
r_struct
id|serio
op_star
id|serio
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|pci_enable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|pci_request_regions
c_func
(paren
id|dev
comma
l_string|&quot;pcips2&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|disable
suffix:semicolon
id|ps2if
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pcips2_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|serio
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serio
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ps2if
op_logical_or
op_logical_neg
id|serio
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ps2if
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pcips2_data
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|serio
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serio
)paren
)paren
suffix:semicolon
id|serio-&gt;id.type
op_assign
id|SERIO_8042
suffix:semicolon
id|serio-&gt;write
op_assign
id|pcips2_write
suffix:semicolon
id|serio-&gt;open
op_assign
id|pcips2_open
suffix:semicolon
id|serio-&gt;close
op_assign
id|pcips2_close
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;name
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
r_sizeof
(paren
id|serio-&gt;name
)paren
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;phys
comma
id|dev-&gt;dev.bus_id
comma
r_sizeof
(paren
id|serio-&gt;phys
)paren
)paren
suffix:semicolon
id|serio-&gt;port_data
op_assign
id|ps2if
suffix:semicolon
id|serio-&gt;dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|ps2if-&gt;io
op_assign
id|serio
suffix:semicolon
id|ps2if-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ps2if-&gt;base
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|ps2if
)paren
suffix:semicolon
id|serio_register_port
c_func
(paren
id|ps2if-&gt;io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|release
suffix:colon
id|kfree
c_func
(paren
id|ps2if
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|serio
)paren
suffix:semicolon
id|pci_release_regions
c_func
(paren
id|dev
)paren
suffix:semicolon
id|disable
suffix:colon
id|pci_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcips2_remove
r_static
r_void
id|__devexit
id|pcips2_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pcips2_data
op_star
id|ps2if
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|serio_unregister_port
c_func
(paren
id|ps2if-&gt;io
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ps2if
)paren
suffix:semicolon
id|pci_release_regions
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|pcips2_ids
r_static
r_struct
id|pci_device_id
id|pcips2_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
l_int|0x14f2
comma
multiline_comment|/* MOBILITY */
dot
id|device
op_assign
l_int|0x0123
comma
multiline_comment|/* Keyboard */
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
dot
r_class
op_assign
id|PCI_CLASS_INPUT_KEYBOARD
op_lshift
l_int|8
comma
dot
id|class_mask
op_assign
l_int|0xffff00
comma
)brace
comma
(brace
dot
id|vendor
op_assign
l_int|0x14f2
comma
multiline_comment|/* MOBILITY */
dot
id|device
op_assign
l_int|0x0124
comma
multiline_comment|/* Mouse */
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
dot
r_class
op_assign
id|PCI_CLASS_INPUT_MOUSE
op_lshift
l_int|8
comma
dot
id|class_mask
op_assign
l_int|0xffff00
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|pcips2_driver
r_static
r_struct
id|pci_driver
id|pcips2_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pcips2&quot;
comma
dot
id|id_table
op_assign
id|pcips2_ids
comma
dot
id|probe
op_assign
id|pcips2_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|pcips2_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|pcips2_init
r_static
r_int
id|__init
id|pcips2_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|pcips2_driver
)paren
suffix:semicolon
)brace
DECL|function|pcips2_exit
r_static
r_void
id|__exit
id|pcips2_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|pcips2_driver
)paren
suffix:semicolon
)brace
DECL|variable|pcips2_init
id|module_init
c_func
(paren
id|pcips2_init
)paren
suffix:semicolon
DECL|variable|pcips2_exit
id|module_exit
c_func
(paren
id|pcips2_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King &lt;rmk@arm.linux.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI PS/2 keyboard/mouse driver&quot;
)paren
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|pcips2_ids
)paren
suffix:semicolon
eof
