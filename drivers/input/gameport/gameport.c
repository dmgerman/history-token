multiline_comment|/*&n; * Generic gameport layer&n; *&n; * Copyright (c) 1999-2002 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic gameport layer&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|gameport_register_port
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_register_port
)paren
suffix:semicolon
DECL|variable|gameport_unregister_port
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_unregister_port
)paren
suffix:semicolon
DECL|variable|gameport_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_register_device
)paren
suffix:semicolon
DECL|variable|gameport_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_unregister_device
)paren
suffix:semicolon
DECL|variable|gameport_open
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_open
)paren
suffix:semicolon
DECL|variable|gameport_close
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_close
)paren
suffix:semicolon
DECL|variable|gameport_rescan
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_rescan
)paren
suffix:semicolon
DECL|variable|gameport_cooked_read
id|EXPORT_SYMBOL
c_func
(paren
id|gameport_cooked_read
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|gameport_list
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|gameport_dev_list
)paren
suffix:semicolon
macro_line|#ifdef __i386__
DECL|macro|DELTA
mdefine_line|#define DELTA(x,y)      ((y)-(x)+((y)&lt;(x)?1193180/HZ:0))
DECL|macro|GET_TIME
mdefine_line|#define GET_TIME(x)     do { x = get_time_pit(); } while (0)
DECL|function|get_time_pit
r_static
r_int
r_int
id|get_time_pit
c_func
(paren
r_void
)paren
(brace
r_extern
id|spinlock_t
id|i8253_lock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
id|count
op_or_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * gameport_measure_speed() measures the gameport i/o speed.&n; */
DECL|function|gameport_measure_speed
r_static
r_int
id|gameport_measure_speed
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
macro_line|#ifdef __i386__
r_int
r_int
id|i
comma
id|t
comma
id|t1
comma
id|t2
comma
id|t3
comma
id|tx
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|gameport_open
c_func
(paren
id|gameport
comma
l_int|NULL
comma
id|GAMEPORT_MODE_RAW
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|tx
op_assign
l_int|1
op_lshift
l_int|30
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
l_int|50
suffix:semicolon
id|i
op_increment
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|GET_TIME
c_func
(paren
id|t1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|t
op_assign
l_int|0
suffix:semicolon
id|t
OL
l_int|50
suffix:semicolon
id|t
op_increment
)paren
(brace
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
id|GET_TIME
c_func
(paren
id|t2
)paren
suffix:semicolon
id|GET_TIME
c_func
(paren
id|t3
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|i
op_star
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t
op_assign
id|DELTA
c_func
(paren
id|t2
comma
id|t1
)paren
op_minus
id|DELTA
c_func
(paren
id|t3
comma
id|t2
)paren
)paren
OL
id|tx
)paren
id|tx
op_assign
id|t
suffix:semicolon
)brace
r_return
l_int|59659
op_div
(paren
id|tx
OL
l_int|1
ques
c_cond
l_int|1
suffix:colon
id|tx
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|j
comma
id|t
op_assign
l_int|0
suffix:semicolon
id|j
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|j
op_eq
id|jiffies
)paren
suffix:semicolon
id|j
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|j
op_eq
id|jiffies
)paren
(brace
id|t
op_increment
suffix:semicolon
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
r_return
id|t
op_star
id|HZ
op_div
l_int|1000
suffix:semicolon
macro_line|#endif
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
DECL|function|gameport_find_dev
r_static
r_void
id|gameport_find_dev
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|gameport_dev
op_star
id|dev
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|gameport_dev_list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
id|gameport-&gt;dev
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;connect
)paren
id|dev
op_member_access_from_pointer
id|connect
c_func
(paren
id|gameport
comma
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|gameport_rescan
r_void
id|gameport_rescan
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|gameport_find_dev
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
DECL|function|gameport_register_port
r_void
id|gameport_register_port
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|gameport-&gt;node
comma
op_amp
id|gameport_list
)paren
suffix:semicolon
id|gameport-&gt;speed
op_assign
id|gameport_measure_speed
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|gameport_find_dev
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
DECL|function|gameport_unregister_port
r_void
id|gameport_unregister_port
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|gameport-&gt;node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gameport-&gt;dev
op_logical_and
id|gameport-&gt;dev-&gt;disconnect
)paren
id|gameport-&gt;dev
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
DECL|function|gameport_register_device
r_void
id|gameport_register_device
c_func
(paren
r_struct
id|gameport_dev
op_star
id|dev
)paren
(brace
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;node
comma
op_amp
id|gameport_dev_list
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|gameport
comma
op_amp
id|gameport_list
comma
id|node
)paren
r_if
c_cond
(paren
op_logical_neg
id|gameport-&gt;dev
op_logical_and
id|dev-&gt;connect
)paren
id|dev
op_member_access_from_pointer
id|connect
c_func
(paren
id|gameport
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|gameport_unregister_device
r_void
id|gameport_unregister_device
c_func
(paren
r_struct
id|gameport_dev
op_star
id|dev
)paren
(brace
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|dev-&gt;node
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|gameport
comma
op_amp
id|gameport_list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
id|gameport-&gt;dev
op_eq
id|dev
op_logical_and
id|dev-&gt;disconnect
)paren
id|dev
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|gameport_find_dev
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
)brace
DECL|function|gameport_open
r_int
id|gameport_open
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_struct
id|gameport_dev
op_star
id|dev
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|gameport-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|gameport
op_member_access_from_pointer
id|open
c_func
(paren
id|gameport
comma
id|mode
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mode
op_ne
id|GAMEPORT_MODE_RAW
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gameport-&gt;dev
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|gameport-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gameport_close
r_void
id|gameport_close
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|gameport-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|gameport-&gt;close
)paren
id|gameport
op_member_access_from_pointer
id|close
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
eof
