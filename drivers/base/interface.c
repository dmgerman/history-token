multiline_comment|/*&n; * drivers/base/interface.c - common driverfs interface that&squot;s exported to &n; * &t;the world for all devices.&n; * Copyright (c) 2002 Patrick Mochel&n; *&t;&t; 2002 Open Source Development Lab&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
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
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_return
id|off
ques
c_cond
l_int|0
suffix:colon
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
r_static
id|ssize_t
DECL|function|device_read_power
id|device_read_power
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|page
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_return
id|off
ques
c_cond
l_int|0
suffix:colon
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|dev-&gt;power_state
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|device_write_power
id|device_write_power
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
id|count
comma
id|loff_t
id|off
)paren
(brace
r_char
id|str_command
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|str_level
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|num_args
suffix:semicolon
id|u32
id|state
suffix:semicolon
id|u32
id|int_level
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;driver
)paren
r_goto
id|done
suffix:semicolon
id|num_args
op_assign
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%10s %10s %u&quot;
comma
id|str_command
comma
id|str_level
comma
op_amp
id|state
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_args
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_command
comma
l_string|&quot;suspend&quot;
comma
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
id|num_args
op_ne
l_int|3
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;notify&quot;
comma
l_int|6
)paren
)paren
id|int_level
op_assign
id|SUSPEND_NOTIFY
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;save&quot;
comma
l_int|4
)paren
)paren
id|int_level
op_assign
id|SUSPEND_SAVE_STATE
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;disable&quot;
comma
l_int|7
)paren
)paren
id|int_level
op_assign
id|SUSPEND_DISABLE
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;powerdown&quot;
comma
l_int|8
)paren
)paren
id|int_level
op_assign
id|SUSPEND_POWER_DOWN
suffix:semicolon
r_else
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;suspend
)paren
id|error
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
comma
id|int_level
)paren
suffix:semicolon
r_else
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_command
comma
l_string|&quot;resume&quot;
comma
l_int|6
)paren
)paren
(brace
r_if
c_cond
(paren
id|num_args
op_ne
l_int|2
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;poweron&quot;
comma
l_int|7
)paren
)paren
id|int_level
op_assign
id|RESUME_POWER_ON
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;restore&quot;
comma
l_int|7
)paren
)paren
id|int_level
op_assign
id|RESUME_RESTORE_STATE
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|str_level
comma
l_string|&quot;enable&quot;
comma
l_int|6
)paren
)paren
id|int_level
op_assign
id|RESUME_ENABLE
suffix:semicolon
r_else
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;resume
)paren
id|error
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|int_level
)paren
suffix:semicolon
r_else
id|error
op_assign
l_int|0
suffix:semicolon
)brace
id|done
suffix:colon
r_return
id|error
OL
l_int|0
ques
c_cond
id|error
suffix:colon
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|power
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|device_read_power
comma
id|device_write_power
)paren
suffix:semicolon
DECL|variable|device_default_files
r_struct
id|device_attribute
op_star
id|device_default_files
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_name
comma
op_amp
id|dev_attr_power
comma
l_int|NULL
comma
)brace
suffix:semicolon
eof
