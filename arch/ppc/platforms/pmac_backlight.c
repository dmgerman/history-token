multiline_comment|/*&n; * Miscellaneous procedures for dealing with the PowerMac hardware.&n; * Contains support for the backlight.&n; * &n; *   Copyright (C) 2000 Benjamin Herrenschmidt&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/backlight.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
DECL|variable|backlighter
r_static
r_struct
id|backlight_controller
op_star
id|backlighter
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|backlighter_data
r_static
r_void
op_star
id|backlighter_data
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|backlight_autosave
r_static
r_int
id|backlight_autosave
op_assign
l_int|0
suffix:semicolon
DECL|variable|backlight_level
r_static
r_int
id|backlight_level
op_assign
id|BACKLIGHT_MAX
suffix:semicolon
DECL|variable|backlight_enabled
r_static
r_int
id|backlight_enabled
op_assign
l_int|1
suffix:semicolon
r_void
id|__pmac
DECL|function|register_backlight_controller
id|register_backlight_controller
c_func
(paren
r_struct
id|backlight_controller
op_star
id|ctrler
comma
r_void
op_star
id|data
comma
r_char
op_star
id|type
)paren
(brace
r_struct
id|device_node
op_star
id|bk_node
suffix:semicolon
r_char
op_star
id|prop
suffix:semicolon
r_int
id|valid
op_assign
l_int|0
suffix:semicolon
id|bk_node
op_assign
id|find_devices
c_func
(paren
l_string|&quot;backlight&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ADB_PMU
multiline_comment|/* Special case for the old PowerBook since I can&squot;t test on it */
id|backlight_autosave
op_assign
id|machine_is_compatible
c_func
(paren
l_string|&quot;AAPL,3400/2400&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;AAPL,3500&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|backlight_autosave
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;AAPL,PowerBook1998&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook1,1&quot;
)paren
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;pmu&quot;
)paren
)paren
id|valid
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bk_node
)paren
(brace
id|prop
op_assign
id|get_property
c_func
(paren
id|bk_node
comma
l_string|&quot;backlight-control&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prop
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|prop
comma
id|type
comma
id|strlen
c_func
(paren
id|type
)paren
)paren
)paren
id|valid
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|valid
)paren
r_return
suffix:semicolon
id|backlighter
op_assign
id|ctrler
suffix:semicolon
id|backlighter_data
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|bk_node
op_logical_and
op_logical_neg
id|backlight_autosave
)paren
id|prop
op_assign
id|get_property
c_func
(paren
id|bk_node
comma
l_string|&quot;bklt&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|prop
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|prop
)paren
(brace
id|backlight_level
op_assign
(paren
(paren
op_star
id|prop
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|backlight_level
OG
id|BACKLIGHT_MAX
)paren
id|backlight_level
op_assign
id|BACKLIGHT_MAX
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ADB_PMU
r_if
c_cond
(paren
id|backlight_autosave
)paren
(brace
r_struct
id|adb_request
id|req
suffix:semicolon
id|pmu_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|2
comma
l_int|0xd9
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|pmu_poll
c_func
(paren
)paren
suffix:semicolon
id|backlight_level
op_assign
id|req.reply
(braket
l_int|0
)braket
op_rshift
l_int|4
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|backlighter
op_member_access_from_pointer
id|set_enable
c_func
(paren
l_int|1
comma
id|backlight_level
comma
id|data
)paren
)paren
id|backlight_enabled
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Registered &bslash;&quot;%s&bslash;&quot; backlight controller, level: %d/15&bslash;n&quot;
comma
id|type
comma
id|backlight_level
)paren
suffix:semicolon
)brace
r_void
id|__pmac
DECL|function|unregister_backlight_controller
id|unregister_backlight_controller
c_func
(paren
r_struct
id|backlight_controller
op_star
id|ctrler
comma
r_void
op_star
id|data
)paren
(brace
multiline_comment|/* We keep the current backlight level (for now) */
r_if
c_cond
(paren
id|ctrler
op_eq
id|backlighter
op_logical_and
id|data
op_eq
id|backlighter_data
)paren
id|backlighter
op_assign
l_int|NULL
suffix:semicolon
)brace
r_int
id|__pmac
DECL|function|set_backlight_enable
id|set_backlight_enable
c_func
(paren
r_int
id|enable
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|backlighter
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|rc
op_assign
id|backlighter
op_member_access_from_pointer
id|set_enable
c_func
(paren
id|enable
comma
id|backlight_level
comma
id|backlighter_data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|backlight_enabled
op_assign
id|enable
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_int
id|__pmac
DECL|function|get_backlight_enable
id|get_backlight_enable
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|backlighter
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|backlight_enabled
suffix:semicolon
)brace
r_int
id|__pmac
DECL|function|set_backlight_level
id|set_backlight_level
c_func
(paren
r_int
id|level
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|backlighter
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|level
OL
id|BACKLIGHT_MIN
)paren
id|level
op_assign
id|BACKLIGHT_OFF
suffix:semicolon
r_if
c_cond
(paren
id|level
OG
id|BACKLIGHT_MAX
)paren
id|level
op_assign
id|BACKLIGHT_MAX
suffix:semicolon
r_if
c_cond
(paren
id|backlight_enabled
)paren
id|rc
op_assign
id|backlighter
op_member_access_from_pointer
id|set_level
c_func
(paren
id|level
comma
id|backlighter_data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|backlight_level
op_assign
id|level
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_and
op_logical_neg
id|backlight_autosave
)paren
(brace
id|level
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|level
op_amp
l_int|0x10
)paren
id|level
op_or_assign
l_int|0x01
suffix:semicolon
singleline_comment|// -- todo: save to property &quot;bklt&quot;
)brace
r_return
id|rc
suffix:semicolon
)brace
r_int
id|__pmac
DECL|function|get_backlight_level
id|get_backlight_level
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|backlighter
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|backlight_level
suffix:semicolon
)brace
eof
