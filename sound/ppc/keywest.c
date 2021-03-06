multiline_comment|/*&n; * common keywest i2c layer&n; *&n; * Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/i2c-dev.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;pmac.h&quot;
multiline_comment|/*&n; * we have to keep a static variable here since i2c attach_adapter&n; * callback cannot pass a private data.&n; */
DECL|variable|keywest_ctx
r_static
id|pmac_keywest_t
op_star
id|keywest_ctx
suffix:semicolon
DECL|macro|I2C_DRIVERID_KEYWEST
mdefine_line|#define I2C_DRIVERID_KEYWEST&t;0xFEBA
r_static
r_int
id|keywest_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_int
id|keywest_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
DECL|variable|keywest_driver
r_struct
id|i2c_driver
id|keywest_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PMac Keywest Audio&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_KEYWEST
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
op_amp
id|keywest_attach_adapter
comma
dot
id|detach_client
op_assign
op_amp
id|keywest_detach_client
comma
)brace
suffix:semicolon
macro_line|#ifndef i2c_device_name
DECL|macro|i2c_device_name
mdefine_line|#define i2c_device_name(x)&t;((x)-&gt;name)
macro_line|#endif
DECL|function|keywest_attach_adapter
r_static
r_int
id|keywest_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|keywest_ctx
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|i2c_device_name
c_func
(paren
id|adapter
)paren
comma
l_string|&quot;mac-io&quot;
comma
l_int|6
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ignored */
id|new_client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_client
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|new_client
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|new_client
)paren
)paren
suffix:semicolon
id|new_client-&gt;addr
op_assign
id|keywest_ctx-&gt;addr
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|new_client
comma
id|keywest_ctx
)paren
suffix:semicolon
id|new_client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|new_client-&gt;driver
op_assign
op_amp
id|keywest_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|i2c_device_name
c_func
(paren
id|new_client
)paren
comma
id|keywest_ctx-&gt;name
)paren
suffix:semicolon
id|keywest_ctx-&gt;client
op_assign
id|new_client
suffix:semicolon
multiline_comment|/* Tell the i2c layer a new client has arrived */
r_if
c_cond
(paren
id|i2c_attach_client
c_func
(paren
id|new_client
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tumbler: cannot attach i2c client&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|__err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|__err
suffix:colon
id|kfree
c_func
(paren
id|new_client
)paren
suffix:semicolon
id|keywest_ctx-&gt;client
op_assign
l_int|NULL
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|keywest_detach_client
r_static
r_int
id|keywest_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|keywest_ctx
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|client
op_eq
id|keywest_ctx-&gt;client
)paren
id|keywest_ctx-&gt;client
op_assign
l_int|NULL
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* exported */
DECL|function|snd_pmac_keywest_cleanup
r_void
id|snd_pmac_keywest_cleanup
c_func
(paren
id|pmac_keywest_t
op_star
id|i2c
)paren
(brace
r_if
c_cond
(paren
id|keywest_ctx
op_logical_and
id|keywest_ctx
op_eq
id|i2c
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|keywest_driver
)paren
suffix:semicolon
id|keywest_ctx
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|snd_pmac_tumbler_post_init
r_int
id|__init
id|snd_pmac_tumbler_post_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|keywest_ctx
op_member_access_from_pointer
id|init_client
c_func
(paren
id|keywest_ctx
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tumbler: %i :cannot initialize the MCS&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* exported */
DECL|function|snd_pmac_keywest_init
r_int
id|__init
id|snd_pmac_keywest_init
c_func
(paren
id|pmac_keywest_t
op_star
id|i2c
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|keywest_ctx
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|keywest_ctx
op_assign
id|i2c
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c_add_driver
c_func
(paren
op_amp
id|keywest_driver
)paren
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cannot register keywest i2c driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
