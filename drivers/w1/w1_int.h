multiline_comment|/*&n; * &t;w1_int.h&n; *&n; * Copyright (c) 2004 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; * &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef __W1_INT_H
DECL|macro|__W1_INT_H
mdefine_line|#define __W1_INT_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;w1.h&quot;
r_struct
id|w1_master
op_star
id|w1_alloc_dev
c_func
(paren
id|u32
comma
r_int
comma
r_int
comma
r_struct
id|device_driver
op_star
comma
r_struct
id|device
op_star
)paren
suffix:semicolon
r_void
id|w1_free_dev
c_func
(paren
r_struct
id|w1_master
op_star
id|dev
)paren
suffix:semicolon
r_int
id|w1_add_master_device
c_func
(paren
r_struct
id|w1_bus_master
op_star
)paren
suffix:semicolon
r_void
id|w1_remove_master_device
c_func
(paren
r_struct
id|w1_bus_master
op_star
)paren
suffix:semicolon
r_void
id|__w1_remove_master_device
c_func
(paren
r_struct
id|w1_master
op_star
)paren
suffix:semicolon
macro_line|#endif /* __W1_INT_H */
eof
