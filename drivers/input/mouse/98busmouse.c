multiline_comment|/*&n; *&n; *  Copyright (c) 2002 Osamu Tomita&n; *&n; *  Based on the work of:&n; *&t;James Banks&t;&t;Matthew Dillon&n; *&t;David Giller&t;&t;Nathan Laredo&n; *&t;Linus Torvalds&t;&t;Johan Myreen&n; *&t;Cliff Matthews&t;&t;Philip Blundell&n; *&t;Russell King&t;&t;Vojtech Pavlik&n; */
multiline_comment|/*&n; * NEC PC-9801 Bus Mouse Driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Osamu Tomita &lt;tomita@cinet.co.jp&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PC-9801 busmouse driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|PC98BM_BASE
mdefine_line|#define&t;PC98BM_BASE&t;&t;0x7fd9
DECL|macro|PC98BM_DATA_PORT
mdefine_line|#define&t;PC98BM_DATA_PORT&t;PC98BM_BASE + 0
multiline_comment|/*&t;PC98BM_SIGNATURE_PORT&t;does not exist */
DECL|macro|PC98BM_CONTROL_PORT
mdefine_line|#define&t;PC98BM_CONTROL_PORT&t;PC98BM_BASE + 4
multiline_comment|/*&t;PC98BM_INTERRUPT_PORT&t;does not exist */
DECL|macro|PC98BM_CONFIG_PORT
mdefine_line|#define&t;PC98BM_CONFIG_PORT&t;PC98BM_BASE + 6
DECL|macro|PC98BM_ENABLE_IRQ
mdefine_line|#define&t;PC98BM_ENABLE_IRQ&t;0x00
DECL|macro|PC98BM_DISABLE_IRQ
mdefine_line|#define&t;PC98BM_DISABLE_IRQ&t;0x10
DECL|macro|PC98BM_READ_X_LOW
mdefine_line|#define&t;PC98BM_READ_X_LOW&t;0x80
DECL|macro|PC98BM_READ_X_HIGH
mdefine_line|#define&t;PC98BM_READ_X_HIGH&t;0xa0
DECL|macro|PC98BM_READ_Y_LOW
mdefine_line|#define&t;PC98BM_READ_Y_LOW&t;0xc0
DECL|macro|PC98BM_READ_Y_HIGH
mdefine_line|#define&t;PC98BM_READ_Y_HIGH&t;0xe0
DECL|macro|PC98BM_DEFAULT_MODE
mdefine_line|#define PC98BM_DEFAULT_MODE&t;0x93
multiline_comment|/*&t;PC98BM_CONFIG_BYTE&t;is not used */
multiline_comment|/*&t;PC98BM_SIGNATURE_BYTE&t;is not used */
DECL|macro|PC98BM_TIMER_PORT
mdefine_line|#define PC98BM_TIMER_PORT&t;0xbfdb
DECL|macro|PC98BM_DEFAULT_TIMER_VAL
mdefine_line|#define PC98BM_DEFAULT_TIMER_VAL&t;0x00
DECL|macro|PC98BM_IRQ
mdefine_line|#define PC98BM_IRQ&t;&t;13
id|MODULE_PARM
c_func
(paren
id|pc98bm_irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|pc98bm_irq
r_static
r_int
id|pc98bm_irq
op_assign
id|PC98BM_IRQ
suffix:semicolon
DECL|variable|pc98bm_used
r_static
r_int
id|pc98bm_used
op_assign
l_int|0
suffix:semicolon
r_static
r_void
id|pc98bm_interrupt
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
DECL|function|pc98bm_open
r_static
r_int
id|pc98bm_open
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
id|pc98bm_used
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pc98bm_irq
comma
id|pc98bm_interrupt
comma
l_int|0
comma
l_string|&quot;98busmouse&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|pc98bm_used
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;98busmouse.c: Can&squot;t allocate irq %d&bslash;n&quot;
comma
id|pc98bm_irq
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
id|PC98BM_ENABLE_IRQ
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pc98bm_close
r_static
r_void
id|pc98bm_close
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
op_decrement
id|pc98bm_used
)paren
r_return
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_DISABLE_IRQ
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|pc98bm_irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|pc98bm_dev
r_static
r_struct
id|input_dev
id|pc98bm_dev
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
id|pc98bm_open
comma
dot
id|close
op_assign
id|pc98bm_close
comma
dot
id|name
op_assign
l_string|&quot;PC-9801 bus mouse&quot;
comma
dot
id|phys
op_assign
l_string|&quot;isa7fd9/input0&quot;
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
l_int|0x0004
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
DECL|function|pc98bm_interrupt
r_static
r_void
id|pc98bm_interrupt
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
r_char
id|dx
comma
id|dy
suffix:semicolon
r_int
r_char
id|buttons
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_READ_X_LOW
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
id|dx
op_assign
(paren
id|inb
c_func
(paren
id|PC98BM_DATA_PORT
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_READ_X_HIGH
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
id|dx
op_or_assign
(paren
id|inb
c_func
(paren
id|PC98BM_DATA_PORT
)paren
op_amp
l_int|0xf
)paren
op_lshift
l_int|4
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_READ_Y_LOW
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
id|dy
op_assign
(paren
id|inb
c_func
(paren
id|PC98BM_DATA_PORT
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_READ_Y_HIGH
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
id|buttons
op_assign
id|inb
c_func
(paren
id|PC98BM_DATA_PORT
)paren
suffix:semicolon
id|dy
op_or_assign
(paren
id|buttons
op_amp
l_int|0xf
)paren
op_lshift
l_int|4
suffix:semicolon
id|buttons
op_assign
op_complement
id|buttons
op_rshift
l_int|5
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|pc98bm_dev
comma
id|REL_X
comma
id|dx
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|pc98bm_dev
comma
id|REL_Y
comma
id|dy
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|pc98bm_dev
comma
id|BTN_RIGHT
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
id|pc98bm_dev
comma
id|BTN_MIDDLE
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
id|pc98bm_dev
comma
id|BTN_LEFT
comma
id|buttons
op_amp
l_int|4
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|pc98bm_dev
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_ENABLE_IRQ
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|pc98bm_setup
r_static
r_int
id|__init
id|pc98bm_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|ints
(braket
l_int|4
)braket
suffix:semicolon
id|str
op_assign
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|0
)paren
id|pc98bm_irq
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pc98bm_irq=&quot;
comma
id|pc98bm_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|function|pc98bm_init
r_static
r_int
id|__init
id|pc98bm_init
c_func
(paren
r_void
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
op_le
l_int|6
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|PC98BM_BASE
op_plus
id|i
comma
l_int|1
comma
l_string|&quot;98busmouse&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;98busmouse.c: Can&squot;t allocate ports at %#x&bslash;n&quot;
comma
id|PC98BM_BASE
op_plus
id|i
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
id|i
op_sub_assign
l_int|2
suffix:semicolon
id|release_region
c_func
(paren
id|PC98BM_BASE
op_plus
id|i
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|PC98BM_TIMER_PORT
comma
l_int|1
comma
l_string|&quot;98busmouse&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;98busmouse.c: Can&squot;t allocate ports at %#x&bslash;n&quot;
comma
id|PC98BM_TIMER_PORT
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
op_le
l_int|6
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|release_region
c_func
(paren
id|PC98BM_BASE
op_plus
id|i
comma
l_int|1
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
id|PC98BM_DEFAULT_MODE
comma
id|PC98BM_CONFIG_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_DISABLE_IRQ
comma
id|PC98BM_CONTROL_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|PC98BM_DEFAULT_TIMER_VAL
comma
id|PC98BM_TIMER_PORT
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|pc98bm_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: PC-9801 bus mouse at %#x irq %d&bslash;n&quot;
comma
id|PC98BM_BASE
comma
id|pc98bm_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pc98bm_exit
r_static
r_void
id|__exit
id|pc98bm_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|pc98bm_dev
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
op_le
l_int|6
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|release_region
c_func
(paren
id|PC98BM_BASE
op_plus
id|i
comma
l_int|1
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|PC98BM_TIMER_PORT
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|pc98bm_init
id|module_init
c_func
(paren
id|pc98bm_init
)paren
suffix:semicolon
DECL|variable|pc98bm_exit
id|module_exit
c_func
(paren
id|pc98bm_exit
)paren
suffix:semicolon
eof
