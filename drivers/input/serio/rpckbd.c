multiline_comment|/*&n; * $Id: rpckbd.c,v 1.7 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *  Copyright (c) 2002 Russell King&n; */
multiline_comment|/*&n; * Acorn RiscPC PS/2 keyboard controller driver for Linux/ARM&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik, Russell King&quot;
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
DECL|variable|rpckbd_port
r_static
r_struct
id|serio
op_star
id|rpckbd_port
suffix:semicolon
DECL|variable|rpckbd_device
r_static
r_struct
id|platform_device
op_star
id|rpckbd_device
suffix:semicolon
DECL|function|rpckbd_write
r_static
r_int
id|rpckbd_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
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
id|iomd_readb
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
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
comma
id|IOMD_KARTTX
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpckbd_rx
r_static
id|irqreturn_t
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
r_struct
id|serio
op_star
id|port
op_assign
id|dev_id
suffix:semicolon
r_int
r_int
id|byte
suffix:semicolon
r_int
id|handled
op_assign
id|IRQ_NONE
suffix:semicolon
r_while
c_loop
(paren
id|iomd_readb
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
(brace
id|byte
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_KARTRX
)paren
suffix:semicolon
id|serio_interrupt
c_func
(paren
id|port
comma
id|byte
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
id|handled
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
r_return
id|handled
suffix:semicolon
)brace
DECL|function|rpckbd_tx
r_static
id|irqreturn_t
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
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|rpckbd_open
r_static
r_int
id|rpckbd_open
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
multiline_comment|/* Reset the keyboard state machine. */
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_KCTRL
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|8
comma
id|IOMD_KCTRL
)paren
suffix:semicolon
id|iomd_readb
c_func
(paren
id|IOMD_KARTRX
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
id|port
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rpckbd.c: Could not allocate keyboard receive IRQ&bslash;n&quot;
)paren
suffix:semicolon
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
id|port
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rpckbd.c: Could not allocate keyboard transmit IRQ&bslash;n&quot;
)paren
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpckbd_close
r_static
r_void
id|rpckbd_close
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
id|free_irq
c_func
(paren
id|IRQ_KEYBOARDRX
comma
id|port
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_KEYBOARDTX
comma
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate and initialize serio structure for subsequent registration&n; * with serio core.&n; */
DECL|function|rpckbd_allocate_port
r_static
r_struct
id|serio
op_star
id|__init
id|rpckbd_allocate_port
c_func
(paren
r_void
)paren
(brace
r_struct
id|serio
op_star
id|serio
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
id|serio
)paren
(brace
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
id|serio-&gt;type
op_assign
id|SERIO_8042
suffix:semicolon
id|serio-&gt;write
op_assign
id|rpckbd_write
suffix:semicolon
id|serio-&gt;open
op_assign
id|rpckbd_open
suffix:semicolon
id|serio-&gt;close
op_assign
id|rpckbd_close
suffix:semicolon
id|serio-&gt;dev.parent
op_assign
op_amp
id|rpckbd_device-&gt;dev
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;name
comma
l_string|&quot;RiscPC PS/2 kbd port&quot;
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
l_string|&quot;rpckbd/serio0&quot;
comma
r_sizeof
(paren
id|serio-&gt;phys
)paren
)paren
suffix:semicolon
)brace
r_return
id|serio
suffix:semicolon
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
id|rpckbd_device
op_assign
id|platform_device_register_simple
c_func
(paren
l_string|&quot;rpckbd&quot;
comma
op_minus
l_int|1
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|rpckbd_device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|rpckbd_device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rpckbd_port
op_assign
id|rpckbd_allocate_port
c_func
(paren
)paren
)paren
)paren
(brace
id|platform_device_unregister
c_func
(paren
id|rpckbd_device
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|serio_register_port
c_func
(paren
id|rpckbd_port
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
id|serio_unregister_port
c_func
(paren
id|rpckbd_port
)paren
suffix:semicolon
id|platform_device_unregister
c_func
(paren
id|rpckbd_device
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
