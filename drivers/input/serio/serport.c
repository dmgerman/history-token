multiline_comment|/*&n; * $Id: serport_old.c,v 1.10 2002/01/24 19:52:57 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This is a module that converts a tty line into a much simpler&n; * &squot;serial io port&squot; abstraction that the input device drivers use.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; *  Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Input device TTY line discipline&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|struct|serport
r_struct
id|serport
(brace
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|serio
r_struct
id|serio
id|serio
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|serport_name
r_char
id|serport_name
(braket
)braket
op_assign
l_string|&quot;Serial port&quot;
suffix:semicolon
multiline_comment|/*&n; * Callback functions from the serio code.&n; */
DECL|function|serport_serio_write
r_static
r_int
id|serport_serio_write
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
)paren
(brace
r_struct
id|serport
op_star
id|serport
op_assign
id|serio-&gt;driver
suffix:semicolon
r_return
op_minus
(paren
id|serport-&gt;tty-&gt;driver
dot
id|write
c_func
(paren
id|serport-&gt;tty
comma
l_int|0
comma
op_amp
id|data
comma
l_int|1
)paren
op_ne
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|serport_serio_open
r_static
r_int
id|serport_serio_open
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serport_serio_close
r_static
r_void
id|serport_serio_close
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serport
op_star
id|serport
op_assign
id|serio-&gt;driver
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|serport-&gt;wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_open() is the routine that is called upon setting our line&n; * discipline on a tty. It looks for the Mag, and if found, registers&n; * it as a joystick device.&n; */
DECL|function|serport_ldisc_open
r_static
r_int
id|serport_ldisc_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|serport
op_star
id|serport
suffix:semicolon
r_char
id|ttyname
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|serport
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serport
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|serport
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serport
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_DO_WRITE_WAKEUP
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
id|serport-&gt;tty
op_assign
id|tty
suffix:semicolon
id|tty-&gt;disc_data
op_assign
id|serport
suffix:semicolon
id|strcpy
c_func
(paren
id|ttyname
comma
id|tty-&gt;driver.name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|ttyname
(braket
id|i
)braket
op_ne
l_int|0
op_logical_and
id|ttyname
(braket
id|i
)braket
op_ne
l_char|&squot;/&squot;
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|ttyname
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|serport-&gt;phys
comma
l_string|&quot;%s%d/serio0&quot;
comma
id|ttyname
comma
id|minor
c_func
(paren
id|tty-&gt;device
)paren
op_minus
id|tty-&gt;driver.minor_start
)paren
suffix:semicolon
id|serport-&gt;serio.name
op_assign
id|serport_name
suffix:semicolon
id|serport-&gt;serio.phys
op_assign
id|serport-&gt;phys
suffix:semicolon
id|serport-&gt;serio.type
op_assign
id|SERIO_RS232
suffix:semicolon
id|serport-&gt;serio.write
op_assign
id|serport_serio_write
suffix:semicolon
id|serport-&gt;serio.open
op_assign
id|serport_serio_open
suffix:semicolon
id|serport-&gt;serio.close
op_assign
id|serport_serio_close
suffix:semicolon
id|serport-&gt;serio.driver
op_assign
id|serport
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|serport-&gt;wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_close() is the opposite of serport_ldisc_open()&n; */
DECL|function|serport_ldisc_close
r_static
r_void
id|serport_ldisc_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|serport
op_star
id|serport
op_assign
(paren
r_struct
id|serport
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
id|kfree
c_func
(paren
id|serport
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_receive() is called by the low level tty driver when characters&n; * are ready for us. We forward the characters, one by one to the &squot;interrupt&squot;&n; * routine.&n; */
DECL|function|serport_ldisc_receive
r_static
r_void
id|serport_ldisc_receive
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_const
r_int
r_char
op_star
id|cp
comma
r_char
op_star
id|fp
comma
r_int
id|count
)paren
(brace
r_struct
id|serport
op_star
id|serport
op_assign
(paren
r_struct
id|serport
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
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
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|serport-&gt;serio.dev
)paren
id|serport-&gt;serio.dev
op_member_access_from_pointer
id|interrupt
c_func
(paren
op_amp
id|serport-&gt;serio
comma
id|cp
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_room() reports how much room we do have for receiving data.&n; * Although we in fact have infinite room, we need to specify some value&n; * here, and 256 seems to be reasonable.&n; */
DECL|function|serport_ldisc_room
r_static
r_int
id|serport_ldisc_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
l_int|256
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_read() just waits indefinitely if everything goes well. &n; * However, when the serio driver closes the serio port, it finishes,&n; * returning 0 characters.&n; */
DECL|function|serport_ldisc_read
r_static
id|ssize_t
id|serport_ldisc_read
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|nr
)paren
(brace
r_struct
id|serport
op_star
id|serport
op_assign
(paren
r_struct
id|serport
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|sprintf
c_func
(paren
id|name
comma
id|tty-&gt;driver.name
comma
id|minor
c_func
(paren
id|tty-&gt;device
)paren
op_minus
id|tty-&gt;driver.minor_start
)paren
suffix:semicolon
macro_line|#else
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s%d&quot;
comma
id|tty-&gt;driver.name
comma
id|minor
c_func
(paren
id|tty-&gt;device
)paren
op_minus
id|tty-&gt;driver.minor_start
)paren
suffix:semicolon
macro_line|#endif
id|serio_register_port
c_func
(paren
op_amp
id|serport-&gt;serio
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: Serial port %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|serport-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|serport-&gt;serio.type
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|serport-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|serio_unregister_port
c_func
(paren
op_amp
id|serport-&gt;serio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_ioctl() allows to set the port protocol, and device ID&n; */
DECL|function|serport_ldisc_ioctl
r_static
r_int
id|serport_ldisc_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|serport
op_star
id|serport
op_assign
(paren
r_struct
id|serport
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SPIOCSTYPE
suffix:colon
r_return
id|get_user
c_func
(paren
id|serport-&gt;serio.type
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|serport_ldisc_write_wakeup
r_static
r_void
id|serport_ldisc_write_wakeup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|serport
op_star
id|sp
op_assign
(paren
r_struct
id|serport
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
id|serio_dev_write_wakeup
c_func
(paren
op_amp
id|sp-&gt;serio
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The line discipline structure.&n; */
DECL|variable|serport_ldisc
r_static
r_struct
id|tty_ldisc
id|serport_ldisc
op_assign
(brace
id|name
suffix:colon
l_string|&quot;input&quot;
comma
id|open
suffix:colon
id|serport_ldisc_open
comma
id|close
suffix:colon
id|serport_ldisc_close
comma
id|read
suffix:colon
id|serport_ldisc_read
comma
id|ioctl
suffix:colon
id|serport_ldisc_ioctl
comma
id|receive_buf
suffix:colon
id|serport_ldisc_receive
comma
id|receive_room
suffix:colon
id|serport_ldisc_room
comma
id|write_wakeup
suffix:colon
id|serport_ldisc_write_wakeup
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for insering/removing us as a module.&n; */
DECL|function|serport_init
r_int
id|__init
id|serport_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tty_register_ldisc
c_func
(paren
id|N_MOUSE
comma
op_amp
id|serport_ldisc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;serport.c: Error registering line discipline.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serport_exit
r_void
id|__exit
id|serport_exit
c_func
(paren
r_void
)paren
(brace
id|tty_register_ldisc
c_func
(paren
id|N_MOUSE
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|serport_init
id|module_init
c_func
(paren
id|serport_init
)paren
suffix:semicolon
DECL|variable|serport_exit
id|module_exit
c_func
(paren
id|serport_exit
)paren
suffix:semicolon
eof
