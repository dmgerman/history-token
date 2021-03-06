multiline_comment|/*&n; * drivers/base/power/sysfs.c - sysfs entries for device PM&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;power.h&quot;
multiline_comment|/**&n; *&t;state - Control current power state of device&n; *&n; *&t;show() returns the current power state of the device. &squot;0&squot; indicates&n; *&t;the device is on. Other values (1-3) indicate the device is in a low&n; *&t;power state.&n; *&n; *&t;store() sets the current power state, which is an integer value&n; *&t;between 0-3. If the device is on (&squot;0&squot;), and the value written is&n; *&t;greater than 0, then the device is placed directly into the low-power&n; *&t;state (via its driver&squot;s -&gt;suspend() method).&n; *&t;If the device is currently in a low-power state, and the value is 0,&n; *&t;the device is powered back on (via the -&gt;resume() method).&n; *&t;If the device is in a low-power state, and a different low-power state&n; *&t;is requested, the device is first resumed, then suspended into the new&n; *&t;low-power state.&n; */
DECL|function|state_show
r_static
id|ssize_t
id|state_show
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
id|dev-&gt;power.power_state
)paren
suffix:semicolon
)brace
DECL|function|state_store
r_static
id|ssize_t
id|state_store
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
r_char
op_star
id|rest
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|rest
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rest
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|error
op_assign
id|dpm_runtime_suspend
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
r_else
id|dpm_runtime_resume
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|error
ques
c_cond
id|error
suffix:colon
id|n
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|state
comma
l_int|0644
comma
id|state_show
comma
id|state_store
)paren
suffix:semicolon
DECL|variable|power_attrs
r_static
r_struct
id|attribute
op_star
id|power_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_state.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|pm_attr_group
r_static
r_struct
id|attribute_group
id|pm_attr_group
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;power&quot;
comma
dot
id|attrs
op_assign
id|power_attrs
comma
)brace
suffix:semicolon
DECL|function|dpm_sysfs_add
r_int
id|dpm_sysfs_add
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|sysfs_create_group
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|pm_attr_group
)paren
suffix:semicolon
)brace
DECL|function|dpm_sysfs_remove
r_void
id|dpm_sysfs_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|sysfs_remove_group
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|pm_attr_group
)paren
suffix:semicolon
)brace
eof
