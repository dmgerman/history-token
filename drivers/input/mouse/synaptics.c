multiline_comment|/*&n; * Synaptics TouchPad PS/2 mouse driver&n; *&n; *   2003 Peter Osterlund &lt;petero2@telia.com&gt;&n; *     Ported to 2.5 input device infrastructure.&n; *&n; *   Copyright (C) 2001 Stefan Gmeiner &lt;riddlebox@freesurf.ch&gt;&n; *     start merging tpconfig and gpm code to a xfree-input module&n; *     adding some changes and extensions (ex. 3rd and 4th button)&n; *&n; *   Copyright (c) 1997 C. Scott Ananian &lt;cananian@alumni.priceton.edu&gt;&n; *   Copyright (c) 1998-2000 Bruce Kalk &lt;kall@compass.com&gt;&n; *     code for the special synaptics commands (from the tpconfig-source)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * Trademarks are the property of their respective owners.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &quot;psmouse.h&quot;
macro_line|#include &quot;synaptics.h&quot;
multiline_comment|/*****************************************************************************&n; *&t;Synaptics communications functions&n; ****************************************************************************/
multiline_comment|/*&n; * Use the Synaptics extended ps/2 syntax to write a special command byte.&n; * special command: 0xE8 rr 0xE8 ss 0xE8 tt 0xE8 uu where (rr*64)+(ss*16)+(tt*4)+uu&n; *                  is the command. A 0xF3 or 0xE9 must follow (see synaptics_send_cmd&n; *                  and synaptics_set_mode)&n; */
DECL|function|synaptics_special_cmd
r_static
r_int
id|synaptics_special_cmd
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_char
id|command
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|6
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_sub_assign
l_int|2
)paren
(brace
r_int
r_char
id|d
op_assign
(paren
id|command
op_rshift
id|i
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_command
c_func
(paren
id|psmouse
comma
op_amp
id|d
comma
id|PSMOUSE_CMD_SETRES
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Send a command to the synpatics touchpad by special commands&n; */
DECL|function|synaptics_send_cmd
r_static
r_int
id|synaptics_send_cmd
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_char
id|c
comma
r_int
r_char
op_star
id|param
)paren
(brace
r_if
c_cond
(paren
id|synaptics_special_cmd
c_func
(paren
id|psmouse
comma
id|c
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the synaptics touchpad mode byte by special commands&n; */
DECL|function|synaptics_set_mode
r_static
r_int
id|synaptics_set_mode
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_char
id|mode
)paren
(brace
r_int
r_char
id|param
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_special_cmd
c_func
(paren
id|psmouse
comma
id|mode
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|0x14
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|synaptics_reset
r_static
r_int
id|synaptics_reset
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_int
r_char
id|r
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|r
comma
id|PSMOUSE_CMD_RESET_BAT
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|r
(braket
l_int|0
)braket
op_eq
l_int|0xAA
op_logical_and
id|r
(braket
l_int|1
)braket
op_eq
l_int|0x00
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the model-id bytes from the touchpad&n; * see also SYN_MODEL_* macros&n; */
DECL|function|synaptics_model_id
r_static
r_int
id|synaptics_model_id
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_int
r_int
op_star
id|model_id
)paren
(brace
r_int
r_char
id|mi
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_send_cmd
c_func
(paren
id|psmouse
comma
id|SYN_QUE_MODEL
comma
id|mi
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|model_id
op_assign
(paren
id|mi
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|mi
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|mi
(braket
l_int|2
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the capability-bits from the touchpad&n; * see also the SYN_CAP_* macros&n; */
DECL|function|synaptics_capability
r_static
r_int
id|synaptics_capability
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_int
r_int
op_star
id|capability
)paren
(brace
r_int
r_char
id|cap
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_send_cmd
c_func
(paren
id|psmouse
comma
id|SYN_QUE_CAPABILITIES
comma
id|cap
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|capability
op_assign
(paren
id|cap
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|cap
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|cap
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_VALID
c_func
(paren
op_star
id|capability
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Identify Touchpad&n; * See also the SYN_ID_* macros&n; */
DECL|function|synaptics_identify
r_static
r_int
id|synaptics_identify
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_int
r_int
op_star
id|ident
)paren
(brace
r_int
r_char
id|id
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_send_cmd
c_func
(paren
id|psmouse
comma
id|SYN_QUE_IDENTIFY
comma
id|id
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|ident
op_assign
(paren
id|id
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|id
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|id
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|SYN_ID_IS_SYNAPTICS
c_func
(paren
op_star
id|ident
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|synaptics_enable_device
r_static
r_int
id|synaptics_enable_device
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_if
c_cond
(paren
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_ENABLE
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_ident
r_static
r_void
id|print_ident
c_func
(paren
r_struct
id|synaptics_data
op_star
id|priv
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Synaptics Touchpad, model: %ld&bslash;n&quot;
comma
id|SYN_ID_MODEL
c_func
(paren
id|priv-&gt;identity
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; Firware: %ld.%ld&bslash;n&quot;
comma
id|SYN_ID_MAJOR
c_func
(paren
id|priv-&gt;identity
)paren
comma
id|SYN_ID_MINOR
c_func
(paren
id|priv-&gt;identity
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_MODEL_ROT180
c_func
(paren
id|priv-&gt;model_id
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; 180 degree mounted touchpad&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_MODEL_PORTRAIT
c_func
(paren
id|priv-&gt;model_id
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; portrait touchpad&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; Sensor: %ld&bslash;n&quot;
comma
id|SYN_MODEL_SENSOR
c_func
(paren
id|priv-&gt;model_id
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_MODEL_NEWABS
c_func
(paren
id|priv-&gt;model_id
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; new absolute packet format&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_MODEL_PEN
c_func
(paren
id|priv-&gt;model_id
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; pen detection&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_EXTENDED
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; Touchpad has extended capability bits&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_FOUR_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; -&gt; four buttons&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_MULTIFINGER
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; -&gt; multifinger detection&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_PALMDETECT
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; -&gt; palm detection&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|query_hardware
r_static
r_int
id|query_hardware
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|synaptics_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|retries
op_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
(paren
id|retries
op_increment
op_le
l_int|3
)paren
op_logical_and
id|synaptics_reset
c_func
(paren
id|psmouse
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;synaptics reset failed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_identify
c_func
(paren
id|psmouse
comma
op_amp
id|priv-&gt;identity
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_model_id
c_func
(paren
id|psmouse
comma
op_amp
id|priv-&gt;model_id
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_capability
c_func
(paren
id|psmouse
comma
op_amp
id|priv-&gt;capabilities
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_set_mode
c_func
(paren
id|psmouse
comma
(paren
id|SYN_BIT_ABSOLUTE_MODE
op_or
id|SYN_BIT_HIGH_RATE
op_or
id|SYN_BIT_DISABLE_GESTURE
op_or
id|SYN_BIT_W_MODE
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|synaptics_enable_device
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|print_ident
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&t;Driver initialization/cleanup functions&n; ****************************************************************************/
DECL|function|set_abs_params
r_static
r_inline
r_void
id|set_abs_params
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
id|axis
comma
r_int
id|min
comma
r_int
id|max
comma
r_int
id|fuzz
comma
r_int
id|flat
)paren
(brace
id|dev-&gt;absmin
(braket
id|axis
)braket
op_assign
id|min
suffix:semicolon
id|dev-&gt;absmax
(braket
id|axis
)braket
op_assign
id|max
suffix:semicolon
id|dev-&gt;absfuzz
(braket
id|axis
)braket
op_assign
id|fuzz
suffix:semicolon
id|dev-&gt;absflat
(braket
id|axis
)braket
op_assign
id|flat
suffix:semicolon
id|set_bit
c_func
(paren
id|axis
comma
id|dev-&gt;absbit
)paren
suffix:semicolon
)brace
DECL|function|synaptics_init
r_int
id|synaptics_init
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|synaptics_data
op_star
id|priv
suffix:semicolon
id|psmouse
op_member_access_from_pointer
r_private
op_assign
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|synaptics_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|synaptics_data
)paren
)paren
suffix:semicolon
id|priv-&gt;inSync
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|query_hardware
c_func
(paren
id|psmouse
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to query/initialize Synaptics hardware.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|init_fail
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The x/y limits are taken from the Synaptics TouchPad interfacing Guide,&n;&t; * which says that they should be valid regardless of the actual size of&n;&t; * the senser.&n;&t; */
id|set_bit
c_func
(paren
id|EV_ABS
comma
id|psmouse-&gt;dev.evbit
)paren
suffix:semicolon
id|set_abs_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|ABS_X
comma
l_int|1472
comma
l_int|5472
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|set_abs_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|ABS_Y
comma
l_int|1408
comma
l_int|4448
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|set_abs_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|ABS_PRESSURE
comma
l_int|0
comma
l_int|255
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_MSC
comma
id|psmouse-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|MSC_GESTURE
comma
id|psmouse-&gt;dev.mscbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_KEY
comma
id|psmouse-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_LEFT
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_RIGHT
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_FORWARD
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_BACK
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|EV_REL
comma
id|psmouse-&gt;dev.evbit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|REL_X
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|REL_Y
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|init_fail
suffix:colon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|synaptics_disconnect
r_void
id|synaptics_disconnect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|synaptics_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&t;Functions to interpret the absolute mode packets&n; ****************************************************************************/
DECL|function|synaptics_parse_hw_state
r_static
r_void
id|synaptics_parse_hw_state
c_func
(paren
r_struct
id|synaptics_data
op_star
id|priv
comma
r_struct
id|synaptics_hw_state
op_star
id|hw
)paren
(brace
r_int
r_char
op_star
id|buf
op_assign
id|priv-&gt;proto_buf
suffix:semicolon
id|hw-&gt;x
op_assign
(paren
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x10
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x0f
)paren
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|hw-&gt;y
op_assign
(paren
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x20
)paren
op_lshift
l_int|7
)paren
op_or
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0xf0
)paren
op_lshift
l_int|4
)paren
op_or
id|buf
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|hw-&gt;z
op_assign
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|hw-&gt;w
op_assign
(paren
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x30
)paren
op_rshift
l_int|2
)paren
op_or
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x04
)paren
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
id|hw-&gt;left
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;right
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x2
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;up
op_assign
l_int|0
suffix:semicolon
id|hw-&gt;down
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_EXTENDED
c_func
(paren
id|priv-&gt;capabilities
)paren
op_logical_and
(paren
id|SYN_CAP_FOUR_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
)paren
(brace
id|hw-&gt;up
op_assign
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x01
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;left
)paren
id|hw-&gt;up
op_assign
op_logical_neg
id|hw-&gt;up
suffix:semicolon
id|hw-&gt;down
op_assign
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x02
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;right
)paren
id|hw-&gt;down
op_assign
op_logical_neg
id|hw-&gt;down
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  called for each full received packet from the touchpad&n; */
DECL|function|synaptics_process_packet
r_static
r_void
id|synaptics_process_packet
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|psmouse-&gt;dev
suffix:semicolon
r_struct
id|synaptics_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|synaptics_hw_state
id|hw
suffix:semicolon
id|synaptics_parse_hw_state
c_func
(paren
id|priv
comma
op_amp
id|hw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw.z
OG
l_int|0
)paren
(brace
r_int
id|w_ok
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Use capability bits to decide if the w value is valid.&n;&t;&t; * If not, set it to 5, which corresponds to a finger of&n;&t;&t; * normal width.&n;&t;&t; */
r_if
c_cond
(paren
id|SYN_CAP_EXTENDED
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
(brace
r_switch
c_cond
(paren
id|hw.w
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|1
suffix:colon
id|w_ok
op_assign
id|SYN_CAP_MULTIFINGER
c_func
(paren
id|priv-&gt;capabilities
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w_ok
op_assign
id|SYN_MODEL_PEN
c_func
(paren
id|priv-&gt;model_id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
dot
dot
dot
l_int|15
suffix:colon
id|w_ok
op_assign
id|SYN_CAP_PALMDETECT
c_func
(paren
id|priv-&gt;capabilities
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|w_ok
)paren
id|hw.w
op_assign
l_int|5
suffix:semicolon
)brace
multiline_comment|/* Post events */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
id|hw.x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
id|hw.y
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_PRESSURE
comma
id|hw.z
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw.w
op_ne
id|priv-&gt;old_w
)paren
(brace
id|input_event
c_func
(paren
id|dev
comma
id|EV_MSC
comma
id|MSC_GESTURE
comma
id|hw.w
)paren
suffix:semicolon
id|priv-&gt;old_w
op_assign
id|hw.w
suffix:semicolon
)brace
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|hw.left
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|hw.right
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_FORWARD
comma
id|hw.up
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_BACK
comma
id|hw.down
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|synaptics_process_byte
r_void
id|synaptics_process_byte
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|psmouse-&gt;dev
suffix:semicolon
r_struct
id|synaptics_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_char
op_star
id|pBuf
op_assign
id|priv-&gt;proto_buf
suffix:semicolon
r_int
r_char
id|u
op_assign
id|psmouse-&gt;packet
(braket
l_int|0
)braket
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|pBuf
(braket
id|priv-&gt;proto_buf_tail
op_increment
)braket
op_assign
id|u
suffix:semicolon
multiline_comment|/* check first byte */
r_if
c_cond
(paren
(paren
id|priv-&gt;proto_buf_tail
op_eq
l_int|1
)paren
op_logical_and
(paren
(paren
id|u
op_amp
l_int|0xC8
)paren
op_ne
l_int|0x80
)paren
)paren
(brace
id|priv-&gt;inSync
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;proto_buf_tail
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Synaptics driver lost sync at 1st byte&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* check 4th byte */
r_if
c_cond
(paren
(paren
id|priv-&gt;proto_buf_tail
op_eq
l_int|4
)paren
op_logical_and
(paren
(paren
id|u
op_amp
l_int|0xc8
)paren
op_ne
l_int|0xc0
)paren
)paren
(brace
id|priv-&gt;inSync
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;proto_buf_tail
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Synaptics driver lost sync at 4th byte&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;proto_buf_tail
op_ge
l_int|6
)paren
(brace
multiline_comment|/* Full packet received */
r_if
c_cond
(paren
op_logical_neg
id|priv-&gt;inSync
)paren
(brace
id|priv-&gt;inSync
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Synaptics driver resynced.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|synaptics_process_packet
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|priv-&gt;proto_buf_tail
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
