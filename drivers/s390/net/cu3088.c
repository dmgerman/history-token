multiline_comment|/*&n; * $Id: cu3088.c,v 1.31 2003/09/29 15:24:27 cohuck Exp $&n; *&n; * CTC / LCS ccw_device driver&n; *&n; * Copyright (C) 2002 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Arnd Bergmann &lt;arndb@de.ibm.com&gt;&n; *            Cornelia Huck &lt;cohuck@de.ibm.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
"&f;"
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/ccwgroup.h&gt;
macro_line|#include &quot;cu3088.h&quot;
DECL|variable|cu3088_type
r_const
r_char
op_star
id|cu3088_type
(braket
)braket
op_assign
(brace
l_string|&quot;not a channel&quot;
comma
l_string|&quot;CTC/A&quot;
comma
l_string|&quot;ESCON channel&quot;
comma
l_string|&quot;FICON channel&quot;
comma
l_string|&quot;P390 LCS card&quot;
comma
l_string|&quot;OSA2 card&quot;
comma
l_string|&quot;unknown channel type&quot;
comma
l_string|&quot;unsupported channel type&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* static definitions */
DECL|variable|cu3088_ids
r_static
r_struct
id|ccw_device_id
id|cu3088_ids
(braket
)braket
op_assign
(brace
(brace
id|CCW_DEVICE
c_func
(paren
l_int|0x3088
comma
l_int|0x08
)paren
comma
dot
id|driver_info
op_assign
id|channel_type_parallel
)brace
comma
(brace
id|CCW_DEVICE
c_func
(paren
l_int|0x3088
comma
l_int|0x1f
)paren
comma
dot
id|driver_info
op_assign
id|channel_type_escon
)brace
comma
(brace
id|CCW_DEVICE
c_func
(paren
l_int|0x3088
comma
l_int|0x1e
)paren
comma
dot
id|driver_info
op_assign
id|channel_type_ficon
)brace
comma
(brace
id|CCW_DEVICE
c_func
(paren
l_int|0x3088
comma
l_int|0x01
)paren
comma
dot
id|driver_info
op_assign
id|channel_type_p390
)brace
comma
(brace
id|CCW_DEVICE
c_func
(paren
l_int|0x3088
comma
l_int|0x60
)paren
comma
dot
id|driver_info
op_assign
id|channel_type_osa2
)brace
comma
(brace
multiline_comment|/* end of list */
)brace
)brace
suffix:semicolon
DECL|variable|cu3088_driver
r_static
r_struct
id|ccw_driver
id|cu3088_driver
suffix:semicolon
r_static
r_void
DECL|function|cu3088_root_dev_release
id|cu3088_root_dev_release
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
)brace
DECL|variable|cu3088_root_dev
r_struct
id|device
id|cu3088_root_dev
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;cu3088&quot;
comma
dot
id|release
op_assign
id|cu3088_root_dev_release
comma
)brace
suffix:semicolon
r_static
id|ssize_t
DECL|function|group_write
id|group_write
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_const
r_char
op_star
id|start
comma
op_star
id|end
suffix:semicolon
r_char
id|bus_ids
(braket
l_int|2
)braket
(braket
id|BUS_ID_SIZE
)braket
comma
op_star
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|ccwgroup_driver
op_star
id|cdrv
suffix:semicolon
id|cdrv
op_assign
id|to_ccwgroupdrv
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdrv
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|start
op_assign
id|buf
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_static
r_const
r_char
id|delim
(braket
)braket
op_assign
(brace
l_char|&squot;,&squot;
comma
l_char|&squot;&bslash;n&squot;
)brace
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|end
op_assign
id|strchr
c_func
(paren
id|start
comma
id|delim
(braket
id|i
)braket
)paren
)paren
)paren
r_return
id|count
suffix:semicolon
id|len
op_assign
id|min_t
c_func
(paren
r_int
comma
id|BUS_ID_SIZE
comma
id|end
op_minus
id|start
op_plus
l_int|1
)paren
suffix:semicolon
id|strlcpy
(paren
id|bus_ids
(braket
id|i
)braket
comma
id|start
comma
id|len
)paren
suffix:semicolon
id|argv
(braket
id|i
)braket
op_assign
id|bus_ids
(braket
id|i
)braket
suffix:semicolon
id|start
op_assign
id|end
op_plus
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|ccwgroup_create
c_func
(paren
op_amp
id|cu3088_root_dev
comma
id|cdrv-&gt;driver_id
comma
op_amp
id|cu3088_driver
comma
l_int|2
comma
id|argv
)paren
suffix:semicolon
r_return
(paren
id|ret
op_eq
l_int|0
)paren
ques
c_cond
id|count
suffix:colon
id|ret
suffix:semicolon
)brace
r_static
id|DRIVER_ATTR
c_func
(paren
id|group
comma
l_int|0200
comma
l_int|NULL
comma
id|group_write
)paren
suffix:semicolon
multiline_comment|/* Register-unregister for ctc&amp;lcs */
r_int
DECL|function|register_cu3088_discipline
id|register_cu3088_discipline
c_func
(paren
r_struct
id|ccwgroup_driver
op_star
id|dcp
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dcp
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Register discipline.*/
id|rc
op_assign
id|ccwgroup_driver_register
c_func
(paren
id|dcp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|driver_create_file
c_func
(paren
op_amp
id|dcp-&gt;driver
comma
op_amp
id|driver_attr_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|ccwgroup_driver_unregister
c_func
(paren
id|dcp
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_void
DECL|function|unregister_cu3088_discipline
id|unregister_cu3088_discipline
c_func
(paren
r_struct
id|ccwgroup_driver
op_star
id|dcp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dcp
)paren
r_return
suffix:semicolon
id|driver_remove_file
c_func
(paren
op_amp
id|dcp-&gt;driver
comma
op_amp
id|driver_attr_group
)paren
suffix:semicolon
id|ccwgroup_driver_unregister
c_func
(paren
id|dcp
)paren
suffix:semicolon
)brace
DECL|variable|cu3088_driver
r_static
r_struct
id|ccw_driver
id|cu3088_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ids
op_assign
id|cu3088_ids
comma
dot
id|name
op_assign
l_string|&quot;cu3088&quot;
comma
dot
id|probe
op_assign
id|ccwgroup_probe_ccwdev
comma
dot
id|remove
op_assign
id|ccwgroup_remove_ccwdev
comma
)brace
suffix:semicolon
multiline_comment|/* module setup */
r_static
r_int
id|__init
DECL|function|cu3088_init
id|cu3088_init
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|device_register
c_func
(paren
op_amp
id|cu3088_root_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|ccw_driver_register
c_func
(paren
op_amp
id|cu3088_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|device_unregister
c_func
(paren
op_amp
id|cu3088_root_dev
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cu3088_exit
id|cu3088_exit
(paren
r_void
)paren
(brace
id|ccw_driver_unregister
c_func
(paren
op_amp
id|cu3088_driver
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|cu3088_root_dev
)paren
suffix:semicolon
)brace
id|MODULE_DEVICE_TABLE
c_func
(paren
id|ccw
comma
id|cu3088_ids
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Arnd Bergmann &lt;arndb@de.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cu3088_init
id|module_init
c_func
(paren
id|cu3088_init
)paren
suffix:semicolon
DECL|variable|cu3088_exit
id|module_exit
c_func
(paren
id|cu3088_exit
)paren
suffix:semicolon
DECL|variable|cu3088_type
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cu3088_type
)paren
suffix:semicolon
DECL|variable|register_cu3088_discipline
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|register_cu3088_discipline
)paren
suffix:semicolon
DECL|variable|unregister_cu3088_discipline
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|unregister_cu3088_discipline
)paren
suffix:semicolon
eof
