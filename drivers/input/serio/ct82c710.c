multiline_comment|/*&n; * $Id: ct82c710.c,v 1.11 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; *  82C710 C&amp;T mouse port chip driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;82C710 C&amp;T mouse port chip driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * ct82c710 interface&n; */
DECL|macro|CT82C710_DEV_IDLE
mdefine_line|#define CT82C710_DEV_IDLE     0x01&t;&t;/* Device Idle */
DECL|macro|CT82C710_RX_FULL
mdefine_line|#define CT82C710_RX_FULL      0x02&t;&t;/* Device Char received */
DECL|macro|CT82C710_TX_IDLE
mdefine_line|#define CT82C710_TX_IDLE      0x04&t;&t;/* Device XMIT Idle */
DECL|macro|CT82C710_RESET
mdefine_line|#define CT82C710_RESET        0x08&t;&t;/* Device Reset */
DECL|macro|CT82C710_INTS_ON
mdefine_line|#define CT82C710_INTS_ON      0x10&t;&t;/* Device Interrupt On */
DECL|macro|CT82C710_ERROR_FLAG
mdefine_line|#define CT82C710_ERROR_FLAG   0x20&t;&t;/* Device Error */
DECL|macro|CT82C710_CLEAR
mdefine_line|#define CT82C710_CLEAR        0x40&t;&t;/* Device Clear */
DECL|macro|CT82C710_ENABLE
mdefine_line|#define CT82C710_ENABLE       0x80&t;&t;/* Device Enable */
DECL|macro|CT82C710_IRQ
mdefine_line|#define CT82C710_IRQ          12
DECL|macro|CT82C710_DATA
mdefine_line|#define CT82C710_DATA         ct82c710_iores.start
DECL|macro|CT82C710_STATUS
mdefine_line|#define CT82C710_STATUS       (ct82c710_iores.start + 1)
DECL|variable|ct82c710_port
r_static
r_struct
id|serio
op_star
id|ct82c710_port
suffix:semicolon
DECL|variable|ct82c710_device
r_static
r_struct
id|platform_device
op_star
id|ct82c710_device
suffix:semicolon
DECL|variable|ct82c710_iores
r_static
r_struct
id|resource
id|ct82c710_iores
suffix:semicolon
multiline_comment|/*&n; * Interrupt handler for the 82C710 mouse port. A character&n; * is waiting in the 82C710.&n; */
DECL|function|ct82c710_interrupt
r_static
id|irqreturn_t
id|ct82c710_interrupt
c_func
(paren
r_int
id|cpl
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
id|serio_interrupt
c_func
(paren
id|ct82c710_port
comma
id|inb
c_func
(paren
id|CT82C710_DATA
)paren
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait for device to send output char and flush any input char.&n; */
DECL|function|ct82c170_wait
r_static
r_int
id|ct82c170_wait
c_func
(paren
r_void
)paren
(brace
r_int
id|timeout
op_assign
l_int|60000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|CT82C710_STATUS
)paren
op_amp
(paren
id|CT82C710_RX_FULL
op_or
id|CT82C710_TX_IDLE
op_or
id|CT82C710_DEV_IDLE
)paren
)paren
op_ne
(paren
id|CT82C710_DEV_IDLE
op_or
id|CT82C710_TX_IDLE
)paren
op_logical_and
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|CT82C710_STATUS
)paren
op_amp
id|CT82C710_RX_FULL
)paren
id|inb_p
c_func
(paren
id|CT82C710_DATA
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|timeout
op_decrement
suffix:semicolon
)brace
r_return
op_logical_neg
id|timeout
suffix:semicolon
)brace
DECL|function|ct82c710_close
r_static
r_void
id|ct82c710_close
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_if
c_cond
(paren
id|ct82c170_wait
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ct82c710.c: Device busy in close()&bslash;n&quot;
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|CT82C710_STATUS
)paren
op_amp
op_complement
(paren
id|CT82C710_ENABLE
op_or
id|CT82C710_INTS_ON
)paren
comma
id|CT82C710_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ct82c170_wait
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ct82c710.c: Device busy in close()&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|CT82C710_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|ct82c710_open
r_static
r_int
id|ct82c710_open
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|CT82C710_IRQ
comma
id|ct82c710_interrupt
comma
l_int|0
comma
l_string|&quot;ct82c710&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|status
op_assign
id|inb_p
c_func
(paren
id|CT82C710_STATUS
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|CT82C710_ENABLE
op_or
id|CT82C710_RESET
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|CT82C710_STATUS
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|CT82C710_RESET
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|CT82C710_STATUS
)paren
suffix:semicolon
id|status
op_or_assign
id|CT82C710_INTS_ON
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|CT82C710_STATUS
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts */
r_while
c_loop
(paren
id|ct82c170_wait
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ct82c710: Device busy in open()&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|CT82C710_ENABLE
op_or
id|CT82C710_INTS_ON
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|CT82C710_STATUS
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|CT82C710_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to the 82C710 mouse device.&n; */
DECL|function|ct82c710_write
r_static
r_int
id|ct82c710_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|ct82c170_wait
c_func
(paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb_p
c_func
(paren
id|c
comma
id|CT82C710_DATA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * See if we can find a 82C710 device. Read mouse address.&n; */
DECL|function|ct82c710_probe
r_static
r_int
id|__init
id|ct82c710_probe
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x55
comma
l_int|0x2fa
)paren
suffix:semicolon
multiline_comment|/* Any value except 9, ff or 36 */
id|outb_p
c_func
(paren
l_int|0xaa
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* Inverse of 55 */
id|outb_p
c_func
(paren
l_int|0x36
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* Address the chip */
id|outb_p
c_func
(paren
l_int|0xe4
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* 390/4; 390 = config address */
id|outb_p
c_func
(paren
l_int|0x1b
comma
l_int|0x2fa
)paren
suffix:semicolon
multiline_comment|/* Inverse of e4 */
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* Write index */
r_if
c_cond
(paren
id|inb_p
c_func
(paren
l_int|0x391
)paren
op_ne
l_int|0xe4
)paren
multiline_comment|/* Config address found? */
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* No: no 82C710 here */
id|outb_p
c_func
(paren
l_int|0x0d
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* Write index */
id|ct82c710_iores.start
op_assign
id|inb_p
c_func
(paren
l_int|0x391
)paren
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* Get mouse I/O address */
id|ct82c710_iores.end
op_assign
id|ct82c710_iores.start
op_plus
l_int|1
suffix:semicolon
id|ct82c710_iores.flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x390
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* Close config mode */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ct82c710_allocate_port
r_static
r_struct
id|serio
op_star
id|__init
id|ct82c710_allocate_port
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
id|serio-&gt;id.type
op_assign
id|SERIO_8042
suffix:semicolon
id|serio-&gt;open
op_assign
id|ct82c710_open
suffix:semicolon
id|serio-&gt;close
op_assign
id|ct82c710_close
suffix:semicolon
id|serio-&gt;write
op_assign
id|ct82c710_write
suffix:semicolon
id|serio-&gt;dev.parent
op_assign
op_amp
id|ct82c710_device-&gt;dev
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;name
comma
l_string|&quot;C&amp;T 82c710 mouse port&quot;
comma
r_sizeof
(paren
id|serio-&gt;name
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|serio-&gt;phys
comma
r_sizeof
(paren
id|serio-&gt;phys
)paren
comma
l_string|&quot;isa%04lx/serio0&quot;
comma
id|CT82C710_DATA
)paren
suffix:semicolon
)brace
r_return
id|serio
suffix:semicolon
)brace
DECL|function|ct82c710_init
r_static
r_int
id|__init
id|ct82c710_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ct82c710_probe
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ct82c710_device
op_assign
id|platform_device_register_simple
c_func
(paren
l_string|&quot;ct82c710&quot;
comma
op_minus
l_int|1
comma
op_amp
id|ct82c710_iores
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|ct82c710_device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|ct82c710_device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ct82c710_port
op_assign
id|ct82c710_allocate_port
c_func
(paren
)paren
)paren
)paren
(brace
id|platform_device_unregister
c_func
(paren
id|ct82c710_device
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
id|ct82c710_port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: C&amp;T 82c710 mouse port at %#lx irq %d&bslash;n&quot;
comma
id|CT82C710_DATA
comma
id|CT82C710_IRQ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ct82c710_exit
r_static
r_void
id|__exit
id|ct82c710_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_port
c_func
(paren
id|ct82c710_port
)paren
suffix:semicolon
id|platform_device_unregister
c_func
(paren
id|ct82c710_device
)paren
suffix:semicolon
)brace
DECL|variable|ct82c710_init
id|module_init
c_func
(paren
id|ct82c710_init
)paren
suffix:semicolon
DECL|variable|ct82c710_exit
id|module_exit
c_func
(paren
id|ct82c710_exit
)paren
suffix:semicolon
eof
