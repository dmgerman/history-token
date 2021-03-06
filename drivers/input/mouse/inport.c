multiline_comment|/*&n; * $Id: inport.c,v 1.11 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Teemu Rantanen&t;&t;Derrick Cole&n; *&t;Peter Cervasio&t;&t;Christoph Niemann&n; *&t;Philip Blundell&t;&t;Russell King&n; *&t;Bob Harris&n; */
multiline_comment|/*&n; * Inport (ATI XL and Microsoft) busmouse driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
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
l_string|&quot;Inport (ATI XL and Microsoft) busmouse driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|INPORT_BASE
mdefine_line|#define INPORT_BASE&t;&t;0x23c
DECL|macro|INPORT_EXTENT
mdefine_line|#define INPORT_EXTENT&t;&t;4
DECL|macro|INPORT_CONTROL_PORT
mdefine_line|#define INPORT_CONTROL_PORT&t;INPORT_BASE + 0
DECL|macro|INPORT_DATA_PORT
mdefine_line|#define INPORT_DATA_PORT&t;INPORT_BASE + 1
DECL|macro|INPORT_SIGNATURE_PORT
mdefine_line|#define INPORT_SIGNATURE_PORT&t;INPORT_BASE + 2
DECL|macro|INPORT_REG_BTNS
mdefine_line|#define INPORT_REG_BTNS&t;0x00
DECL|macro|INPORT_REG_X
mdefine_line|#define INPORT_REG_X&t;&t;0x01
DECL|macro|INPORT_REG_Y
mdefine_line|#define INPORT_REG_Y&t;&t;0x02
DECL|macro|INPORT_REG_MODE
mdefine_line|#define INPORT_REG_MODE&t;&t;0x07
DECL|macro|INPORT_RESET
mdefine_line|#define INPORT_RESET&t;&t;0x80
macro_line|#ifdef CONFIG_INPUT_ATIXL
DECL|macro|INPORT_NAME
mdefine_line|#define INPORT_NAME&t;&t;&quot;ATI XL Mouse&quot;
DECL|macro|INPORT_VENDOR
mdefine_line|#define INPORT_VENDOR&t;&t;0x0002
DECL|macro|INPORT_SPEED_30HZ
mdefine_line|#define INPORT_SPEED_30HZ&t;0x01
DECL|macro|INPORT_SPEED_50HZ
mdefine_line|#define INPORT_SPEED_50HZ&t;0x02
DECL|macro|INPORT_SPEED_100HZ
mdefine_line|#define INPORT_SPEED_100HZ&t;0x03
DECL|macro|INPORT_SPEED_200HZ
mdefine_line|#define INPORT_SPEED_200HZ&t;0x04
DECL|macro|INPORT_MODE_BASE
mdefine_line|#define INPORT_MODE_BASE&t;INPORT_SPEED_100HZ
DECL|macro|INPORT_MODE_IRQ
mdefine_line|#define INPORT_MODE_IRQ&t;&t;0x08
macro_line|#else
DECL|macro|INPORT_NAME
mdefine_line|#define INPORT_NAME&t;&t;&quot;Microsoft InPort Mouse&quot;
DECL|macro|INPORT_VENDOR
mdefine_line|#define INPORT_VENDOR&t;&t;0x0001
DECL|macro|INPORT_MODE_BASE
mdefine_line|#define INPORT_MODE_BASE&t;0x10
DECL|macro|INPORT_MODE_IRQ
mdefine_line|#define INPORT_MODE_IRQ&t;&t;0x01
macro_line|#endif
DECL|macro|INPORT_MODE_HOLD
mdefine_line|#define INPORT_MODE_HOLD&t;0x20
DECL|macro|INPORT_IRQ
mdefine_line|#define INPORT_IRQ&t;&t;5
DECL|variable|inport_irq
r_static
r_int
id|inport_irq
op_assign
id|INPORT_IRQ
suffix:semicolon
id|module_param_named
c_func
(paren
id|irq
comma
id|inport_irq
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ number (5=default)&quot;
)paren
suffix:semicolon
id|__obsolete_setup
c_func
(paren
l_string|&quot;inport_irq=&quot;
)paren
suffix:semicolon
DECL|variable|inport_used
r_static
r_int
id|inport_used
suffix:semicolon
r_static
id|irqreturn_t
id|inport_interrupt
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
suffix:semicolon
DECL|function|inport_open
r_static
r_int
id|inport_open
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
id|inport_used
op_increment
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|inport_irq
comma
id|inport_interrupt
comma
l_int|0
comma
l_string|&quot;inport&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_MODE
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_MODE_IRQ
op_or
id|INPORT_MODE_BASE
comma
id|INPORT_DATA_PORT
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inport_close
r_static
r_void
id|inport_close
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
id|inport_used
)paren
(brace
id|outb
c_func
(paren
id|INPORT_REG_MODE
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_MODE_BASE
comma
id|INPORT_DATA_PORT
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|inport_irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
DECL|variable|inport_dev
r_static
r_struct
id|input_dev
id|inport_dev
op_assign
(brace
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REL
)paren
)brace
comma
dot
id|keybit
op_assign
(brace
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
)brace
comma
dot
id|relbit
op_assign
(brace
id|BIT
c_func
(paren
id|REL_X
)paren
op_or
id|BIT
c_func
(paren
id|REL_Y
)paren
)brace
comma
dot
id|open
op_assign
id|inport_open
comma
dot
id|close
op_assign
id|inport_close
comma
dot
id|name
op_assign
id|INPORT_NAME
comma
dot
id|phys
op_assign
l_string|&quot;isa023c/input0&quot;
comma
dot
id|id
op_assign
(brace
dot
id|bustype
op_assign
id|BUS_ISA
comma
dot
id|vendor
op_assign
id|INPORT_VENDOR
comma
dot
id|product
op_assign
l_int|0x0001
comma
dot
id|version
op_assign
l_int|0x0100
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|inport_interrupt
r_static
id|irqreturn_t
id|inport_interrupt
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
r_int
r_char
id|buttons
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_MODE
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_MODE_HOLD
op_or
id|INPORT_MODE_IRQ
op_or
id|INPORT_MODE_BASE
comma
id|INPORT_DATA_PORT
)paren
suffix:semicolon
id|input_regs
c_func
(paren
op_amp
id|inport_dev
comma
id|regs
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_X
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|inport_dev
comma
id|REL_X
comma
id|inb
c_func
(paren
id|INPORT_DATA_PORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_Y
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|inport_dev
comma
id|REL_Y
comma
id|inb
c_func
(paren
id|INPORT_DATA_PORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_BTNS
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|buttons
op_assign
id|inb
c_func
(paren
id|INPORT_DATA_PORT
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|inport_dev
comma
id|BTN_MIDDLE
comma
id|buttons
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|inport_dev
comma
id|BTN_LEFT
comma
id|buttons
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|inport_dev
comma
id|BTN_RIGHT
comma
id|buttons
op_amp
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_MODE
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_MODE_IRQ
op_or
id|INPORT_MODE_BASE
comma
id|INPORT_DATA_PORT
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|inport_dev
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|inport_init
r_static
r_int
id|__init
id|inport_init
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|a
comma
id|b
comma
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|INPORT_BASE
comma
id|INPORT_EXTENT
comma
l_string|&quot;inport&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;inport.c: Can&squot;t allocate ports at %#x&bslash;n&quot;
comma
id|INPORT_BASE
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|a
op_assign
id|inb
c_func
(paren
id|INPORT_SIGNATURE_PORT
)paren
suffix:semicolon
id|b
op_assign
id|inb
c_func
(paren
id|INPORT_SIGNATURE_PORT
)paren
suffix:semicolon
id|c
op_assign
id|inb
c_func
(paren
id|INPORT_SIGNATURE_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a
op_eq
id|b
)paren
op_logical_or
(paren
id|a
op_ne
id|c
)paren
)paren
(brace
id|release_region
c_func
(paren
id|INPORT_BASE
comma
id|INPORT_EXTENT
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;inport.c: Didn&squot;t find InPort mouse at %#x&bslash;n&quot;
comma
id|INPORT_BASE
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|outb
c_func
(paren
id|INPORT_RESET
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_REG_MODE
comma
id|INPORT_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INPORT_MODE_BASE
comma
id|INPORT_DATA_PORT
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|inport_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: &quot;
id|INPORT_NAME
l_string|&quot; at %#x irq %d&bslash;n&quot;
comma
id|INPORT_BASE
comma
id|inport_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inport_exit
r_static
r_void
id|__exit
id|inport_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|inport_dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|INPORT_BASE
comma
id|INPORT_EXTENT
)paren
suffix:semicolon
)brace
DECL|variable|inport_init
id|module_init
c_func
(paren
id|inport_init
)paren
suffix:semicolon
DECL|variable|inport_exit
id|module_exit
c_func
(paren
id|inport_exit
)paren
suffix:semicolon
eof
