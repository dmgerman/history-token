multiline_comment|/*&n; * &t;w1_smem.c&n; *&n; * Copyright (c) 2004 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; * &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the smems of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;w1.h&quot;
macro_line|#include &quot;w1_io.h&quot;
macro_line|#include &quot;w1_int.h&quot;
macro_line|#include &quot;w1_family.h&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for 1-wire Dallas network protocol, 64bit memory family.&quot;
)paren
suffix:semicolon
r_static
id|ssize_t
id|w1_smem_read_name
c_func
(paren
r_struct
id|device
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|w1_smem_read_val
c_func
(paren
r_struct
id|device
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|w1_smem_read_bin
c_func
(paren
r_struct
id|kobject
op_star
comma
r_char
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
DECL|variable|w1_smem_fops
r_static
r_struct
id|w1_family_ops
id|w1_smem_fops
op_assign
(brace
dot
id|rname
op_assign
op_amp
id|w1_smem_read_name
comma
dot
id|rbin
op_assign
op_amp
id|w1_smem_read_bin
comma
dot
id|rval
op_assign
op_amp
id|w1_smem_read_val
comma
dot
id|rvalname
op_assign
l_string|&quot;id&quot;
comma
)brace
suffix:semicolon
DECL|function|w1_smem_read_name
r_static
id|ssize_t
id|w1_smem_read_name
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|w1_slave
op_star
id|sl
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|w1_slave
comma
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|sl-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|w1_smem_read_val
r_static
id|ssize_t
id|w1_smem_read_val
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|w1_slave
op_star
id|sl
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|w1_slave
comma
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ssize_t
id|count
op_assign
l_int|0
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
l_int|9
suffix:semicolon
op_increment
id|i
)paren
id|count
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|count
comma
l_string|&quot;%02x &quot;
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|sl-&gt;reg_num
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|count
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|count
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|w1_smem_read_bin
r_static
id|ssize_t
id|w1_smem_read_bin
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|w1_slave
op_star
id|sl
op_assign
id|container_of
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
comma
r_struct
id|w1_slave
comma
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sl-&gt;refcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|sl-&gt;master-&gt;mutex
)paren
)paren
(brace
id|count
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_dec
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
OG
id|W1_SLAVE_DATA_SIZE
)paren
(brace
id|count
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
id|W1_SLAVE_DATA_SIZE
)paren
(brace
id|count
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|9
suffix:semicolon
op_increment
id|i
)paren
id|count
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|count
comma
l_string|&quot;%02x &quot;
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|sl-&gt;reg_num
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|count
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|count
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|sl-&gt;master-&gt;mutex
)paren
suffix:semicolon
id|out_dec
suffix:colon
id|atomic_dec
c_func
(paren
op_amp
id|sl-&gt;refcnt
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|w1_smem_family
r_static
r_struct
id|w1_family
id|w1_smem_family
op_assign
(brace
dot
id|fid
op_assign
id|W1_FAMILY_SMEM
comma
dot
id|fops
op_assign
op_amp
id|w1_smem_fops
comma
)brace
suffix:semicolon
DECL|function|w1_smem_init
r_static
r_int
id|__init
id|w1_smem_init
c_func
(paren
r_void
)paren
(brace
r_return
id|w1_register_family
c_func
(paren
op_amp
id|w1_smem_family
)paren
suffix:semicolon
)brace
DECL|function|w1_smem_fini
r_static
r_void
id|__exit
id|w1_smem_fini
c_func
(paren
r_void
)paren
(brace
id|w1_unregister_family
c_func
(paren
op_amp
id|w1_smem_family
)paren
suffix:semicolon
)brace
DECL|variable|w1_smem_init
id|module_init
c_func
(paren
id|w1_smem_init
)paren
suffix:semicolon
DECL|variable|w1_smem_fini
id|module_exit
c_func
(paren
id|w1_smem_fini
)paren
suffix:semicolon
eof
