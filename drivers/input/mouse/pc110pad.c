multiline_comment|/*&n; * $Id: pc110pad.c,v 1.12 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Alan Cox&t;Robin O&squot;Leary&t;&n; */
multiline_comment|/*&n; * IBM PC110 touchpad driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IBM PC110 touchpad driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|PC110PAD_OFF
mdefine_line|#define PC110PAD_OFF&t;0x30
DECL|macro|PC110PAD_ON
mdefine_line|#define PC110PAD_ON&t;0x38
DECL|variable|pc110pad_irq
r_static
r_int
id|pc110pad_irq
op_assign
l_int|10
suffix:semicolon
DECL|variable|pc110pad_io
r_static
r_int
id|pc110pad_io
op_assign
l_int|0x15e0
suffix:semicolon
DECL|variable|pc110pad_dev
r_static
r_struct
id|input_dev
id|pc110pad_dev
suffix:semicolon
DECL|variable|pc110pad_data
r_static
r_int
id|pc110pad_data
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|pc110pad_count
r_static
r_int
id|pc110pad_count
suffix:semicolon
DECL|variable|pc110pad_used
r_static
r_int
id|pc110pad_used
suffix:semicolon
DECL|variable|pc110pad_name
r_static
r_char
op_star
id|pc110pad_name
op_assign
l_string|&quot;IBM PC110 TouchPad&quot;
suffix:semicolon
DECL|variable|pc110pad_phys
r_static
r_char
op_star
id|pc110pad_phys
op_assign
l_string|&quot;isa15e0/input0&quot;
suffix:semicolon
DECL|function|pc110pad_interrupt
r_static
id|irqreturn_t
id|pc110pad_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|value
op_assign
id|inb_p
c_func
(paren
id|pc110pad_io
)paren
suffix:semicolon
r_int
id|handshake
op_assign
id|inb_p
c_func
(paren
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|handshake
op_or
l_int|1
comma
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|handshake
op_amp
op_complement
l_int|1
comma
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
id|inb_p
c_func
(paren
l_int|0x64
)paren
suffix:semicolon
id|pc110pad_data
(braket
id|pc110pad_count
op_increment
)braket
op_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|pc110pad_count
OL
l_int|3
)paren
r_return
id|IRQ_HANDLED
suffix:semicolon
id|input_regs
c_func
(paren
op_amp
id|pc110pad_dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|pc110pad_dev
comma
id|BTN_TOUCH
comma
id|pc110pad_data
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|pc110pad_dev
comma
id|ABS_X
comma
id|pc110pad_data
(braket
l_int|1
)braket
op_or
(paren
(paren
id|pc110pad_data
(braket
l_int|0
)braket
op_lshift
l_int|3
)paren
op_amp
l_int|0x80
)paren
op_or
(paren
(paren
id|pc110pad_data
(braket
l_int|0
)braket
op_lshift
l_int|1
)paren
op_amp
l_int|0x100
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|pc110pad_dev
comma
id|ABS_Y
comma
id|pc110pad_data
(braket
l_int|2
)braket
op_or
(paren
(paren
id|pc110pad_data
(braket
l_int|0
)braket
op_lshift
l_int|4
)paren
op_amp
l_int|0x80
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|pc110pad_dev
)paren
suffix:semicolon
id|pc110pad_count
op_assign
l_int|0
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|pc110pad_close
r_static
r_void
id|pc110pad_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|pc110pad_used
)paren
id|outb
c_func
(paren
id|PC110PAD_OFF
comma
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|pc110pad_open
r_static
r_int
id|pc110pad_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|pc110pad_used
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|pc110pad_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|pc110pad_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|pc110pad_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC110PAD_ON
comma
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
id|pc110pad_count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We try to avoid enabling the hardware if it&squot;s not&n; * there, but we don&squot;t know how to test. But we do know&n; * that the PC110 is not a PCI system. So if we find any&n; * PCI devices in the machine, we don&squot;t have a PC110.&n; */
DECL|function|pc110pad_init
r_static
r_int
id|__init
id|pc110pad_init
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
id|dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|pc110pad_io
comma
l_int|4
comma
l_string|&quot;pc110pad&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pc110pad: I/O area %#x-%#x in use.&bslash;n&quot;
comma
id|pc110pad_io
comma
id|pc110pad_io
op_plus
l_int|4
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|outb
c_func
(paren
id|PC110PAD_OFF
comma
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pc110pad_irq
comma
id|pc110pad_interrupt
comma
l_int|0
comma
l_string|&quot;pc110pad&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|release_region
c_func
(paren
id|pc110pad_io
comma
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pc110pad: Unable to get irq %d.&bslash;n&quot;
comma
id|pc110pad_irq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pc110pad_dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
suffix:semicolon
id|pc110pad_dev.absbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
suffix:semicolon
id|pc110pad_dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
suffix:semicolon
id|pc110pad_dev.absmax
(braket
id|ABS_X
)braket
op_assign
l_int|0x1ff
suffix:semicolon
id|pc110pad_dev.absmax
(braket
id|ABS_Y
)braket
op_assign
l_int|0x0ff
suffix:semicolon
id|pc110pad_dev.open
op_assign
id|pc110pad_open
suffix:semicolon
id|pc110pad_dev.close
op_assign
id|pc110pad_close
suffix:semicolon
id|pc110pad_dev.name
op_assign
id|pc110pad_name
suffix:semicolon
id|pc110pad_dev.phys
op_assign
id|pc110pad_phys
suffix:semicolon
id|pc110pad_dev.id.bustype
op_assign
id|BUS_ISA
suffix:semicolon
id|pc110pad_dev.id.vendor
op_assign
l_int|0x0003
suffix:semicolon
id|pc110pad_dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|pc110pad_dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|pc110pad_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s at %#x irq %d&bslash;n&quot;
comma
id|pc110pad_name
comma
id|pc110pad_io
comma
id|pc110pad_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pc110pad_exit
r_static
r_void
id|__exit
id|pc110pad_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|pc110pad_dev
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC110PAD_OFF
comma
id|pc110pad_io
op_plus
l_int|2
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|pc110pad_irq
comma
l_int|NULL
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|pc110pad_io
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|variable|pc110pad_init
id|module_init
c_func
(paren
id|pc110pad_init
)paren
suffix:semicolon
DECL|variable|pc110pad_exit
id|module_exit
c_func
(paren
id|pc110pad_exit
)paren
suffix:semicolon
eof
