multiline_comment|/*&n; * $Id: hid-ff.c,v 1.3 2002/06/09 11:06:38 jdeneux Exp $&n; *&n; *  Force feedback support for hid devices.&n; *  Not all hid devices use the same protocol. For example, some use PID,&n; *  other use their own proprietary procotol.&n; *&n; *  Copyright (c) 2002 Johann Deneux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;deneux@ifrance.com&gt;&n; */
macro_line|#include &lt;linux/input.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;hid.h&quot;
multiline_comment|/* Drivers&squot; initializing functions */
r_extern
r_int
id|hid_lgff_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
r_extern
r_int
id|hid_lg3d_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
r_extern
r_int
id|hid_pid_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
multiline_comment|/*&n; * This table contains pointers to initializers. To add support for new&n; * devices, you need to add the USB vendor and product ids here.&n; */
DECL|struct|hid_ff_initializer
r_struct
id|hid_ff_initializer
(brace
DECL|member|idVendor
id|__u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|__u16
id|idProduct
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|hid_device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|inits
r_static
r_struct
id|hid_ff_initializer
id|inits
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_LOGITECH_RUMBLE
(brace
l_int|0x46d
comma
l_int|0xc211
comma
id|hid_lgff_init
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_LOGITECH_3D
(brace
l_int|0x46d
comma
l_int|0xc283
comma
id|hid_lg3d_init
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_HID_PID
(brace
l_int|0x45e
comma
l_int|0x001b
comma
id|hid_pid_init
)brace
comma
macro_line|#endif
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
DECL|function|hid_get_ff_init
r_static
r_struct
id|hid_ff_initializer
op_star
id|hid_get_ff_init
c_func
(paren
id|__u16
id|idVendor
comma
id|__u16
id|idProduct
)paren
(brace
r_struct
id|hid_ff_initializer
op_star
id|init
suffix:semicolon
r_for
c_loop
(paren
id|init
op_assign
id|inits
suffix:semicolon
id|init-&gt;idVendor
op_logical_and
op_logical_neg
(paren
id|init-&gt;idVendor
op_eq
id|idVendor
op_logical_and
id|init-&gt;idProduct
op_eq
id|idProduct
)paren
suffix:semicolon
id|init
op_increment
)paren
suffix:semicolon
r_return
id|init-&gt;idVendor
ques
c_cond
id|init
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|hid_ff_init
r_int
id|hid_ff_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|hid_ff_initializer
op_star
id|init
suffix:semicolon
id|init
op_assign
id|hid_get_ff_init
c_func
(paren
id|hid-&gt;dev-&gt;descriptor.idVendor
comma
id|hid-&gt;dev-&gt;descriptor.idProduct
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;hid_ff_init could not find initializer&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_return
id|init
op_member_access_from_pointer
id|init
c_func
(paren
id|hid
)paren
suffix:semicolon
)brace
eof