multiline_comment|/*&n; * $Id: serio.c,v 1.5 2000/06/04 17:44:59 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; *  The Serio abstraction module&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|serio_register_port
id|EXPORT_SYMBOL
c_func
(paren
id|serio_register_port
)paren
suffix:semicolon
DECL|variable|serio_unregister_port
id|EXPORT_SYMBOL
c_func
(paren
id|serio_unregister_port
)paren
suffix:semicolon
DECL|variable|serio_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|serio_register_device
)paren
suffix:semicolon
DECL|variable|serio_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|serio_unregister_device
)paren
suffix:semicolon
DECL|variable|serio_open
id|EXPORT_SYMBOL
c_func
(paren
id|serio_open
)paren
suffix:semicolon
DECL|variable|serio_close
id|EXPORT_SYMBOL
c_func
(paren
id|serio_close
)paren
suffix:semicolon
DECL|variable|serio_rescan
id|EXPORT_SYMBOL
c_func
(paren
id|serio_rescan
)paren
suffix:semicolon
DECL|variable|serio_list
r_static
r_struct
id|serio
op_star
id|serio_list
suffix:semicolon
DECL|variable|serio_dev
r_static
r_struct
id|serio_dev
op_star
id|serio_dev
suffix:semicolon
DECL|variable|serio_number
r_static
r_int
id|serio_number
suffix:semicolon
DECL|function|serio_find_dev
r_static
r_void
id|serio_find_dev
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio_dev
op_star
id|dev
op_assign
id|serio_dev
suffix:semicolon
r_while
c_loop
(paren
id|dev
op_logical_and
op_logical_neg
id|serio-&gt;dev
)paren
(brace
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
id|serio
comma
id|dev
)paren
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|serio_rescan
r_void
id|serio_rescan
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
id|serio-&gt;dev
op_logical_and
id|serio-&gt;dev-&gt;disconnect
)paren
id|serio-&gt;dev
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_find_dev
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
DECL|function|serio_register_port
r_void
id|serio_register_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|serio-&gt;number
op_assign
id|serio_number
op_increment
suffix:semicolon
id|serio-&gt;next
op_assign
id|serio_list
suffix:semicolon
id|serio_list
op_assign
id|serio
suffix:semicolon
id|serio_find_dev
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
DECL|function|serio_unregister_port
r_void
id|serio_unregister_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio
op_star
op_star
id|serioptr
op_assign
op_amp
id|serio_list
suffix:semicolon
r_while
c_loop
(paren
op_star
id|serioptr
op_logical_and
(paren
op_star
id|serioptr
op_ne
id|serio
)paren
)paren
id|serioptr
op_assign
op_amp
(paren
(paren
op_star
id|serioptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|serioptr
op_assign
(paren
op_star
id|serioptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;dev
op_logical_and
id|serio-&gt;dev-&gt;disconnect
)paren
id|serio-&gt;dev
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_number
op_decrement
suffix:semicolon
)brace
DECL|function|serio_register_device
r_void
id|serio_register_device
c_func
(paren
r_struct
id|serio_dev
op_star
id|dev
)paren
(brace
r_struct
id|serio
op_star
id|serio
op_assign
id|serio_list
suffix:semicolon
id|dev-&gt;next
op_assign
id|serio_dev
suffix:semicolon
id|serio_dev
op_assign
id|dev
suffix:semicolon
r_while
c_loop
(paren
id|serio
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|serio-&gt;dev
op_logical_and
id|dev-&gt;connect
)paren
id|dev
op_member_access_from_pointer
id|connect
c_func
(paren
id|serio
comma
id|dev
)paren
suffix:semicolon
id|serio
op_assign
id|serio-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|serio_unregister_device
r_void
id|serio_unregister_device
c_func
(paren
r_struct
id|serio_dev
op_star
id|dev
)paren
(brace
r_struct
id|serio_dev
op_star
op_star
id|devptr
op_assign
op_amp
id|serio_dev
suffix:semicolon
r_struct
id|serio
op_star
id|serio
op_assign
id|serio_list
suffix:semicolon
r_while
c_loop
(paren
op_star
id|devptr
op_logical_and
(paren
op_star
id|devptr
op_ne
id|dev
)paren
)paren
id|devptr
op_assign
op_amp
(paren
(paren
op_star
id|devptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|devptr
op_assign
(paren
op_star
id|devptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_while
c_loop
(paren
id|serio
)paren
(brace
r_if
c_cond
(paren
id|serio-&gt;dev
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
id|serio
)paren
suffix:semicolon
id|serio_find_dev
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio
op_assign
id|serio-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|serio_open
r_int
id|serio_open
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
r_if
c_cond
(paren
id|serio
op_member_access_from_pointer
id|open
c_func
(paren
id|serio
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|serio-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serio_close
r_void
id|serio_close
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|serio
op_member_access_from_pointer
id|close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
)brace
eof