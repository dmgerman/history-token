multiline_comment|/*&n; * $Id: rpckbd.c,v 1.7 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;unknown author&n; */
multiline_comment|/*&n; * Acorn RiscPC PS/2 keyboard controller driver for Linux/ARM&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/iomd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Acorn RiscPC PS/2 keyboard controller driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|rpckbd_write
r_static
r_inline
r_void
id|rpckbd_write
c_func
(paren
r_int
r_char
id|val
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|IOMD_KCTRL
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
)paren
(brace
suffix:semicolon
)brace
id|outb
c_func
(paren
id|val
comma
id|IOMD_KARTTX
)paren
suffix:semicolon
)brace
DECL|variable|rpckbd_port
r_static
r_struct
id|serio
id|rpckbd_port
op_assign
(brace
id|type
suffix:colon
id|SERIO_8042
comma
id|write
suffix:colon
id|rpckbd_write
comma
id|name
suffix:colon
l_string|&quot;RiscPC PS/2 kbd port&quot;
comma
id|phys
suffix:colon
l_string|&quot;rpckbd/serio0&quot;
comma
)brace
suffix:semicolon
DECL|function|rpckbd_rx
r_static
r_void
id|rpckbd_rx
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
id|kbd_pt_regs
op_assign
id|regs
suffix:semicolon
r_while
c_loop
(paren
id|inb
c_func
(paren
id|IOMD_KCTRL
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
r_if
c_cond
(paren
id|rpckbd_port.dev
)paren
id|rpckbd_port.dev
op_member_access_from_pointer
id|interrupt
c_func
(paren
op_amp
id|rpckbd_port
comma
id|inb
c_func
(paren
id|IOMD_KARTRX
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|rpckbd_tx
r_static
r_void
id|rpckbd_tx
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
)brace
DECL|function|rpckbd_init
r_static
r_int
id|__init
id|rpckbd_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Reset the keyboard state machine. */
id|outb
c_func
(paren
l_int|0
comma
id|IOMD_KCTRL
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|8
comma
id|IOMD_KCTRL
)paren
suffix:semicolon
id|save_flags_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_KEYBOARDRX
comma
id|rpckbd_rx
comma
l_int|0
comma
l_string|&quot;rpckbd&quot;
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rpckbd.c: Could not allocate keyboard receive IRQ!&bslash;n&quot;
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_KEYBOARDTX
comma
id|rpckbd_tx
comma
l_int|0
comma
l_string|&quot;rpckbd&quot;
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rpckbd.c: Could not allocate keyboard transmit IRQ!&bslash;n&quot;
)paren
id|free_irq
c_func
(paren
id|IRQ_KEYBOARDRX
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|disable_irq
c_func
(paren
id|IRQ_KEYBOARDTX
)paren
suffix:semicolon
(paren
r_void
)paren
id|IOMD_KARTRX
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|register_serio_port
c_func
(paren
op_amp
id|rpckbd_port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: RiscPC PS/2 kbd port irq %d %d&bslash;n&quot;
comma
id|IRQ_KEYBOARDRX
comma
id|IRQ_KEYBOARDTX
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpckbd_exit
r_static
r_void
id|__exit
id|rpckbd_exit
c_func
(paren
r_void
)paren
(brace
id|free_irq
c_func
(paren
id|IRQ_KEYBOARDRX
comma
l_int|NULL
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_KEYBOARDTX
comma
l_int|NULL
)paren
suffix:semicolon
id|unregister_serio_port
c_func
(paren
op_amp
id|rpckbd_port
)paren
suffix:semicolon
)brace
DECL|variable|rpckbd_init
id|module_init
c_func
(paren
id|rpckbd_init
)paren
suffix:semicolon
DECL|variable|rpckbd_exit
id|module_exit
c_func
(paren
id|rpckbd_exit
)paren
suffix:semicolon
eof
