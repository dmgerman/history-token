multiline_comment|/*&n; * $Id: iforce-serio.c,v 1.4 2002/01/28 22:45:00 jdeneux Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&n; *  Copyright (c) 2001 Johann Deneux &lt;deneux@ifrance.com&gt;&n; *&n; *  USB/RS232 I-Force joysticks and wheels.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &quot;iforce.h&quot;
DECL|function|iforce_serial_xmit
r_void
id|iforce_serial_xmit
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
(brace
r_int
r_char
id|cs
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|IFORCE_XMIT_RUNNING
comma
id|iforce-&gt;xmit_flags
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|IFORCE_XMIT_AGAIN
comma
id|iforce-&gt;xmit_flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
id|again
suffix:colon
r_if
c_cond
(paren
id|iforce-&gt;xmit.head
op_eq
id|iforce-&gt;xmit.tail
)paren
(brace
id|clear_bit
c_func
(paren
id|IFORCE_XMIT_RUNNING
comma
id|iforce-&gt;xmit_flags
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cs
op_assign
l_int|0x2b
suffix:semicolon
id|serio_write
c_func
(paren
id|iforce-&gt;serio
comma
l_int|0x2b
)paren
suffix:semicolon
id|serio_write
c_func
(paren
id|iforce-&gt;serio
comma
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
)paren
suffix:semicolon
id|cs
op_xor_assign
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|iforce-&gt;xmit.tail
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|serio_write
c_func
(paren
id|iforce-&gt;serio
comma
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
)paren
suffix:semicolon
id|cs
op_xor_assign
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|iforce-&gt;xmit.tail
comma
l_int|1
)paren
suffix:semicolon
)brace
id|serio_write
c_func
(paren
id|iforce-&gt;serio
comma
id|cs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|IFORCE_XMIT_AGAIN
comma
id|iforce-&gt;xmit_flags
)paren
)paren
r_goto
id|again
suffix:semicolon
id|clear_bit
c_func
(paren
id|IFORCE_XMIT_RUNNING
comma
id|iforce-&gt;xmit_flags
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|iforce_serio_write_wakeup
r_static
r_void
id|iforce_serio_write_wakeup
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|iforce_serial_xmit
c_func
(paren
(paren
r_struct
id|iforce
op_star
)paren
id|serio
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
)brace
DECL|function|iforce_serio_irq
r_static
r_void
id|iforce_serio_irq
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iforce-&gt;pkt
)paren
(brace
r_if
c_cond
(paren
id|data
op_ne
l_int|0x2b
)paren
(brace
r_return
suffix:semicolon
)brace
id|iforce-&gt;pkt
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|iforce-&gt;id
)paren
(brace
r_if
c_cond
(paren
id|data
OG
l_int|3
op_logical_and
id|data
op_ne
l_int|0xff
)paren
(brace
id|iforce-&gt;pkt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iforce-&gt;id
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|iforce-&gt;len
)paren
(brace
r_if
c_cond
(paren
id|data
OG
id|IFORCE_MAX_LENGTH
)paren
(brace
id|iforce-&gt;pkt
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;id
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iforce-&gt;len
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iforce-&gt;idx
OL
id|iforce-&gt;len
)paren
(brace
id|iforce-&gt;csum
op_add_assign
id|iforce-&gt;data
(braket
id|iforce-&gt;idx
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iforce-&gt;idx
op_eq
id|iforce-&gt;len
)paren
(brace
id|iforce_process_packet
c_func
(paren
id|iforce
comma
(paren
id|iforce-&gt;id
op_lshift
l_int|8
)paren
op_or
id|iforce-&gt;idx
comma
id|iforce-&gt;data
)paren
suffix:semicolon
id|iforce-&gt;pkt
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;id
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;len
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;idx
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;csum
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|iforce_serio_connect
r_static
r_void
id|iforce_serio_connect
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_dev
op_star
id|dev
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;type
op_ne
(paren
id|SERIO_RS232
op_or
id|SERIO_IFORCE
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iforce
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iforce
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|iforce
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|iforce
)paren
)paren
suffix:semicolon
id|iforce-&gt;bus
op_assign
id|IFORCE_232
suffix:semicolon
id|iforce-&gt;serio
op_assign
id|serio
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|iforce
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|dev
)paren
)paren
(brace
id|kfree
c_func
(paren
id|iforce
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iforce_init_device
c_func
(paren
id|iforce
)paren
)paren
(brace
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iforce
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|iforce_serio_disconnect
r_static
r_void
id|iforce_serio_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|iforce-&gt;dev
)paren
suffix:semicolon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iforce
)paren
suffix:semicolon
)brace
DECL|variable|iforce_serio_dev
r_struct
id|serio_dev
id|iforce_serio_dev
op_assign
(brace
dot
id|write_wakeup
op_assign
id|iforce_serio_write_wakeup
comma
dot
id|interrupt
op_assign
id|iforce_serio_irq
comma
dot
id|connect
op_assign
id|iforce_serio_connect
comma
dot
id|disconnect
op_assign
id|iforce_serio_disconnect
comma
)brace
suffix:semicolon
eof
