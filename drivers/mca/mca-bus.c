multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/*&n; * MCA bus support functions for sysfs.&n; *&n; * (C) 2002 James Bottomley &lt;James.Bottomley@HansenPartnership.com&gt;&n; *&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
multiline_comment|/* Very few machines have more than one MCA bus.  However, there are&n; * those that do (Voyager 35xx/5xxx), so we do it this way for future&n; * expansion.  None that I know have more than 2 */
DECL|variable|mca_root_busses
r_struct
id|mca_bus
op_star
id|mca_root_busses
(braket
id|MAX_MCA_BUSSES
)braket
suffix:semicolon
DECL|macro|MCA_DEVINFO
mdefine_line|#define MCA_DEVINFO(i,s) { .pos = i, .name = s }
DECL|struct|mca_device_info
r_struct
id|mca_device_info
(brace
DECL|member|pos_id
r_int
id|pos_id
suffix:semicolon
multiline_comment|/* the 2 byte pos id for this card */
DECL|member|name
r_char
id|name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|mca_bus_match
r_static
r_int
id|mca_bus_match
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|mca_driver
op_star
id|mca_drv
op_assign
id|to_mca_driver
(paren
id|drv
)paren
suffix:semicolon
r_const
r_int
op_star
id|mca_ids
op_assign
id|mca_drv-&gt;id_table
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_ids
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|mca_ids
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mca_ids
(braket
id|i
)braket
op_eq
id|mca_dev-&gt;pos_id
)paren
(brace
id|mca_dev-&gt;index
op_assign
id|i
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mca_bus_type
r_struct
id|bus_type
id|mca_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MCA&quot;
comma
dot
id|match
op_assign
id|mca_bus_match
comma
)brace
suffix:semicolon
DECL|variable|mca_bus_type
id|EXPORT_SYMBOL
(paren
id|mca_bus_type
)paren
suffix:semicolon
DECL|function|mca_show_pos_id
r_static
id|ssize_t
id|mca_show_pos_id
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
multiline_comment|/* four digits, &bslash;n and trailing &bslash;0 */
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|mca_dev-&gt;pos_id
OL
id|MCA_DUMMY_POS_START
)paren
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%04x&bslash;n&quot;
comma
id|mca_dev-&gt;pos_id
)paren
suffix:semicolon
)brace
r_else
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;none&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|mca_show_pos
r_static
id|ssize_t
id|mca_show_pos
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
multiline_comment|/* enough for 8 two byte hex chars plus space and new line */
r_int
id|j
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%02x &quot;
comma
id|mca_dev-&gt;pos
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* change last trailing space to new line */
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|id
comma
id|S_IRUGO
comma
id|mca_show_pos_id
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|pos
comma
id|S_IRUGO
comma
id|mca_show_pos
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|mca_register_device
r_int
id|__init
id|mca_register_device
c_func
(paren
r_int
id|bus
comma
r_struct
id|mca_device
op_star
id|mca_dev
)paren
(brace
r_struct
id|mca_bus
op_star
id|mca_bus
op_assign
id|mca_root_busses
(braket
id|bus
)braket
suffix:semicolon
id|mca_dev-&gt;dev.parent
op_assign
op_amp
id|mca_bus-&gt;dev
suffix:semicolon
id|mca_dev-&gt;dev.bus
op_assign
op_amp
id|mca_bus_type
suffix:semicolon
id|sprintf
(paren
id|mca_dev-&gt;dev.bus_id
comma
l_string|&quot;%02d:%02X&quot;
comma
id|bus
comma
id|mca_dev-&gt;slot
)paren
suffix:semicolon
id|mca_dev-&gt;dma_mask
op_assign
id|mca_bus-&gt;default_dma_mask
suffix:semicolon
id|mca_dev-&gt;dev.dma_mask
op_assign
op_amp
id|mca_dev-&gt;dma_mask
suffix:semicolon
r_if
c_cond
(paren
id|device_register
c_func
(paren
op_amp
id|mca_dev-&gt;dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|mca_dev-&gt;dev
comma
op_amp
id|dev_attr_id
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|mca_dev-&gt;dev
comma
op_amp
id|dev_attr_pos
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* */
DECL|function|mca_attach_bus
r_struct
id|mca_bus
op_star
id|__devinit
id|mca_attach_bus
c_func
(paren
r_int
id|bus
)paren
(brace
r_struct
id|mca_bus
op_star
id|mca_bus
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|mca_root_busses
(braket
id|bus
)braket
op_ne
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* This should never happen, but just in case */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;MCA tried to add already existing bus %d&bslash;n&quot;
comma
id|bus
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|mca_bus
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mca_bus
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_bus
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|mca_bus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mca_bus
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|mca_bus-&gt;dev.bus_id
comma
l_string|&quot;mca%d&quot;
comma
id|bus
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|mca_bus-&gt;dev.name
comma
l_string|&quot;Host %s MCA Bridge&quot;
comma
id|bus
ques
c_cond
l_string|&quot;Secondary&quot;
suffix:colon
l_string|&quot;Primary&quot;
)paren
suffix:semicolon
id|device_register
c_func
(paren
op_amp
id|mca_bus-&gt;dev
)paren
suffix:semicolon
id|mca_root_busses
(braket
id|bus
)braket
op_assign
id|mca_bus
suffix:semicolon
r_return
id|mca_bus
suffix:semicolon
)brace
DECL|function|mca_system_init
r_int
id|__init
id|mca_system_init
(paren
r_void
)paren
(brace
r_return
id|bus_register
c_func
(paren
op_amp
id|mca_bus_type
)paren
suffix:semicolon
)brace
eof
