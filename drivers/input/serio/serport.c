multiline_comment|/*&n; * Input device TTY line discipline&n; *&n; * Copyright (c) 1999-2002 Vojtech Pavlik&n; *&n; * This is a module that converts a tty line into a much simpler&n; * &squot;serial io port&squot; abstraction that the input device drivers use.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
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
DECL|variable|N_MOUSE
id|MODULE_ALIAS_LDISC
c_func
(paren
id|N_MOUSE
)paren
suffix:semicolon
DECL|macro|SERPORT_BUSY
mdefine_line|#define SERPORT_BUSY&t;1
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
op_star
id|serio
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
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
id|serio-&gt;port_data
suffix:semicolon
r_return
op_minus
(paren
id|serport-&gt;tty-&gt;driver
op_member_access_from_pointer
id|write
c_func
(paren
id|serport-&gt;tty
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
id|serio-&gt;port_data
suffix:semicolon
id|serport-&gt;serio-&gt;id.type
op_assign
l_int|0
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|serport-&gt;wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * serport_ldisc_open() is the routine that is called upon setting our line&n; * discipline on a tty. It prepares the serio struct.&n; */
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
r_struct
id|serio
op_star
id|serio
suffix:semicolon
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
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
id|unlikely
c_func
(paren
op_logical_neg
id|serport
op_logical_or
op_logical_neg
id|serio
)paren
)paren
(brace
id|kfree
c_func
(paren
id|serport
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|serio
)paren
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
id|serport-&gt;serio
op_assign
id|serio
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
id|strlcpy
c_func
(paren
id|serio-&gt;name
comma
l_string|&quot;Serial port&quot;
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
l_string|&quot;%s/serio0&quot;
comma
id|tty_name
c_func
(paren
id|tty
comma
id|name
)paren
)paren
suffix:semicolon
id|serio-&gt;id.type
op_assign
id|SERIO_RS232
suffix:semicolon
id|serio-&gt;write
op_assign
id|serport_serio_write
suffix:semicolon
id|serio-&gt;close
op_assign
id|serport_serio_close
suffix:semicolon
id|serio-&gt;port_data
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
)brace
multiline_comment|/*&n; * serport_ldisc_receive() is called by the low level tty driver when characters&n; * are ready for us. We forward the characters, one by one to the &squot;interrupt&squot;&n; * routine.&n; *&n; * FIXME: We should get pt_regs from the tty layer and forward them to&n; *&t;  serio_interrupt here.&n; */
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
id|serio_interrupt
c_func
(paren
id|serport-&gt;serio
comma
id|cp
(braket
id|i
)braket
comma
l_int|0
comma
l_int|NULL
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
multiline_comment|/*&n; * serport_ldisc_read() just waits indefinitely if everything goes well.&n; * However, when the serio driver closes the serio port, it finishes,&n; * returning 0 characters.&n; */
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
id|__user
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
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|SERPORT_BUSY
comma
op_amp
id|serport-&gt;flags
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|serio_register_port
c_func
(paren
id|serport-&gt;serio
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: Serial port %s&bslash;n&quot;
comma
id|tty_name
c_func
(paren
id|tty
comma
id|name
)paren
)paren
suffix:semicolon
id|wait_event_interruptible
c_func
(paren
id|serport-&gt;wait
comma
op_logical_neg
id|serport-&gt;serio-&gt;id.type
)paren
suffix:semicolon
id|serio_unregister_port
c_func
(paren
id|serport-&gt;serio
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|SERPORT_BUSY
comma
op_amp
id|serport-&gt;flags
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
r_struct
id|serio
op_star
id|serio
op_assign
id|serport-&gt;serio
suffix:semicolon
r_int
r_int
id|type
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|SPIOCSTYPE
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|type
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|serio-&gt;id.proto
op_assign
id|type
op_amp
l_int|0x000000ff
suffix:semicolon
id|serio-&gt;id.id
op_assign
(paren
id|type
op_amp
l_int|0x0000ff00
)paren
op_rshift
l_int|8
suffix:semicolon
id|serio-&gt;id.extra
op_assign
(paren
id|type
op_amp
l_int|0x00ff0000
)paren
op_rshift
l_int|16
suffix:semicolon
r_return
l_int|0
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
id|serio_drv_write_wakeup
c_func
(paren
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;input&quot;
comma
dot
id|open
op_assign
id|serport_ldisc_open
comma
dot
id|close
op_assign
id|serport_ldisc_close
comma
dot
id|read
op_assign
id|serport_ldisc_read
comma
dot
id|ioctl
op_assign
id|serport_ldisc_ioctl
comma
dot
id|receive_buf
op_assign
id|serport_ldisc_receive
comma
dot
id|receive_room
op_assign
id|serport_ldisc_room
comma
dot
id|write_wakeup
op_assign
id|serport_ldisc_write_wakeup
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for insering/removing us as a module.&n; */
DECL|function|serport_init
r_static
r_int
id|__init
id|serport_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|tty_register_ldisc
c_func
(paren
id|N_MOUSE
comma
op_amp
id|serport_ldisc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;serport.c: Error registering line discipline.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|serport_exit
r_static
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
