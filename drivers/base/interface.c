multiline_comment|/*&n; * drivers/base/interface.c - common driverfs interface that&squot;s exported to &n; * &t;the world for all devices.&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; * &n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|function|device_read_name
r_static
id|ssize_t
id|device_read_name
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
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|name
comma
id|S_IRUGO
comma
id|device_read_name
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;detach_state - control the default power state for the device.&n; *&t;&n; *&t;This is the state the device enters when it&squot;s driver module is &n; *&t;unloaded. The value is an unsigned integer, in the range of 0-4.&n; *&t;&squot;0&squot; indicates &squot;On&squot;, so no action will be taken when the driver is&n; *&t;unloaded. This is the default behavior.&n; *&t;&squot;4&squot; indicates &squot;Off&squot;, meaning the driver core will call the driver&squot;s&n; *&t;shutdown method to quiesce the device.&n; *&t;1-3 indicate a low-power state for the device to enter via the &n; *&t;driver&squot;s suspend method. &n; */
DECL|function|detach_show
r_static
id|ssize_t
id|detach_show
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
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%u&bslash;n&quot;
comma
id|dev-&gt;detach_state
)paren
suffix:semicolon
)brace
DECL|function|detach_store
r_static
id|ssize_t
id|detach_store
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|n
)paren
(brace
id|u32
id|state
suffix:semicolon
id|state
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
OG
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;detach_state
op_assign
id|state
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|detach_state
comma
l_int|0644
comma
id|detach_show
comma
id|detach_store
)paren
suffix:semicolon
DECL|variable|dev_default_attrs
r_struct
id|attribute
op_star
id|dev_default_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_name.attr
comma
op_amp
id|dev_attr_detach_state.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
eof
