multiline_comment|/*&n; * Synaptics TouchPad PS/2 mouse driver&n; *&n; *   2003 Dmitry Torokhov &lt;dtor@mail.ru&gt;&n; *     Added support for pass-through port. Special thanks to Peter Berg Larsen&n; *     for explaining various Synaptics quirks.&n; *&n; *   2003 Peter Osterlund &lt;petero2@telia.com&gt;&n; *     Ported to 2.5 input device infrastructure.&n; *&n; *   Copyright (C) 2001 Stefan Gmeiner &lt;riddlebox@freesurf.ch&gt;&n; *     start merging tpconfig and gpm code to a xfree-input module&n; *     adding some changes and extensions (ex. 3rd and 4th button)&n; *&n; *   Copyright (c) 1997 C. Scott Ananian &lt;cananian@alumni.priceton.edu&gt;&n; *   Copyright (c) 1998-2000 Bruce Kalk &lt;kall@compass.com&gt;&n; *     code for the special synaptics commands (from the tpconfig-source)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * Trademarks are the property of their respective owners.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &quot;psmouse.h&quot;
macro_line|#include &quot;synaptics.h&quot;
multiline_comment|/*&n; * The x/y limits are taken from the Synaptics TouchPad interfacing Guide,&n; * section 2.3.2, which says that they should be valid regardless of the&n; * actual size of the sensor.&n; */
DECL|macro|XMIN_NOMINAL
mdefine_line|#define XMIN_NOMINAL 1472
DECL|macro|XMAX_NOMINAL
mdefine_line|#define XMAX_NOMINAL 5472
DECL|macro|YMIN_NOMINAL
mdefine_line|#define YMIN_NOMINAL 1408
DECL|macro|YMAX_NOMINAL
mdefine_line|#define YMAX_NOMINAL 4448
multiline_comment|/*****************************************************************************&n; *&t;Synaptics communications functions&n; ****************************************************************************/
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
id|psmouse_sliced_command
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
DECL|function|synaptics_mode_cmd
r_static
r_int
id|synaptics_mode_cmd
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
id|psmouse_sliced_command
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
id|SYN_PS_SET_MODE2
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
id|priv-&gt;model_id
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
id|priv-&gt;capabilities
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
id|priv-&gt;ext_cap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SYN_CAP_VALID
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Unless capExtended is set the rest of the flags should be ignored&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|SYN_CAP_EXTENDED
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|priv-&gt;capabilities
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|SYN_EXT_CAP_REQUESTS
c_func
(paren
id|priv-&gt;capabilities
)paren
op_ge
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|synaptics_send_cmd
c_func
(paren
id|psmouse
comma
id|SYN_QUE_EXT_CAPAB
comma
id|cap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Synaptics claims to have extended capabilities,&quot;
l_string|&quot; but I&squot;m not able to read them.&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|priv-&gt;ext_cap
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
multiline_comment|/*&n;&t;&t;&t; * if nExtBtn is greater than 8 it should be considered&n;&t;&t;&t; * invalid and treated as 0&n;&t;&t;&t; */
r_if
c_cond
(paren
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
OG
l_int|8
)paren
id|priv-&gt;ext_cap
op_and_assign
l_int|0xff0fff
suffix:semicolon
)brace
)brace
r_return
l_int|0
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
id|priv-&gt;identity
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
id|priv-&gt;identity
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
l_string|&quot; Firmware: %ld.%ld&bslash;n&quot;
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
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; -&gt; %d multi-buttons, i.e. besides standard buttons&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_MIDDLE_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; -&gt; middle button&bslash;n&quot;
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
r_if
c_cond
(paren
id|SYN_CAP_PASS_THROUGH
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; -&gt; pass-through port&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|synaptics_query_hardware
r_static
r_int
id|synaptics_query_hardware
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|retries
op_increment
OL
l_int|3
)paren
op_logical_and
id|psmouse_reset
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
id|mode
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
id|mode
op_or_assign
id|SYN_BIT_ABSOLUTE_MODE
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_rate
op_ge
l_int|80
)paren
id|mode
op_or_assign
id|SYN_BIT_HIGH_RATE
suffix:semicolon
r_if
c_cond
(paren
id|SYN_ID_MAJOR
c_func
(paren
id|priv-&gt;identity
)paren
op_ge
l_int|4
)paren
id|mode
op_or_assign
id|SYN_BIT_DISABLE_GESTURE
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
id|mode
op_or_assign
id|SYN_BIT_W_MODE
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_mode_cmd
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&t;Synaptics pass-through PS/2 port support&n; ****************************************************************************/
DECL|function|synaptics_pt_write
r_static
r_int
id|synaptics_pt_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
r_int
r_char
id|c
)paren
(brace
r_struct
id|psmouse_ptport
op_star
id|ptport
op_assign
id|port-&gt;port_data
suffix:semicolon
r_char
id|rate_param
op_assign
id|SYN_PS_CLIENT_CMD
suffix:semicolon
multiline_comment|/* indicates that we want pass-through port */
r_if
c_cond
(paren
id|psmouse_sliced_command
c_func
(paren
id|ptport-&gt;parent
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
id|ptport-&gt;parent
comma
op_amp
id|rate_param
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
DECL|function|synaptics_is_pt_packet
r_static
r_inline
r_int
id|synaptics_is_pt_packet
c_func
(paren
r_int
r_char
op_star
id|buf
)paren
(brace
r_return
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0xFC
)paren
op_eq
l_int|0x84
op_logical_and
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0xCC
)paren
op_eq
l_int|0xC4
suffix:semicolon
)brace
DECL|function|synaptics_pass_pt_packet
r_static
r_void
id|synaptics_pass_pt_packet
c_func
(paren
r_struct
id|serio
op_star
id|ptport
comma
r_int
r_char
op_star
id|packet
)paren
(brace
r_struct
id|psmouse
op_star
id|child
op_assign
id|ptport
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
(brace
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|PSMOUSE_ACTIVATED
)paren
(brace
id|serio_interrupt
c_func
(paren
id|ptport
comma
id|packet
(braket
l_int|1
)braket
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|serio_interrupt
c_func
(paren
id|ptport
comma
id|packet
(braket
l_int|4
)braket
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|serio_interrupt
c_func
(paren
id|ptport
comma
id|packet
(braket
l_int|5
)braket
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;type
op_ge
id|PSMOUSE_GENPS
)paren
id|serio_interrupt
c_func
(paren
id|ptport
comma
id|packet
(braket
l_int|2
)braket
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|PSMOUSE_IGNORE
)paren
(brace
id|serio_interrupt
c_func
(paren
id|ptport
comma
id|packet
(braket
l_int|1
)braket
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|synaptics_pt_activate
r_static
r_void
id|synaptics_pt_activate
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|psmouse
op_star
id|child
op_assign
id|psmouse-&gt;ptport-&gt;serio
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* adjust the touchpad to child&squot;s choice of protocol */
r_if
c_cond
(paren
id|child
op_logical_and
id|child-&gt;type
op_ge
id|PSMOUSE_GENPS
)paren
(brace
r_if
c_cond
(paren
id|synaptics_set_mode
c_func
(paren
id|psmouse
comma
id|SYN_BIT_FOUR_BYTE_CLIENT
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;synaptics: failed to enable 4-byte guest protocol&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|synaptics_pt_create
r_static
r_void
id|synaptics_pt_create
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|psmouse_ptport
op_star
id|port
suffix:semicolon
r_struct
id|serio
op_star
id|serio
suffix:semicolon
id|port
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|psmouse_ptport
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|serio
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serio
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
op_logical_or
op_logical_neg
id|serio
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;synaptics: not enough memory to allocate pass-through port&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|port
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|psmouse_ptport
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|serio
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serio
)paren
)paren
suffix:semicolon
id|serio-&gt;type
op_assign
id|SERIO_PS_PSTHRU
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;name
comma
l_string|&quot;Synaptics pass-through&quot;
comma
r_sizeof
(paren
id|serio-&gt;name
)paren
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;phys
comma
l_string|&quot;synaptics-pt/serio0&quot;
comma
r_sizeof
(paren
id|serio-&gt;name
)paren
)paren
suffix:semicolon
id|serio-&gt;write
op_assign
id|synaptics_pt_write
suffix:semicolon
id|serio-&gt;port_data
op_assign
id|port
suffix:semicolon
id|port-&gt;serio
op_assign
id|serio
suffix:semicolon
id|port-&gt;parent
op_assign
id|psmouse
suffix:semicolon
id|port-&gt;activate
op_assign
id|synaptics_pt_activate
suffix:semicolon
id|psmouse-&gt;ptport
op_assign
id|port
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&t;Functions to interpret the absolute mode packets&n; ****************************************************************************/
DECL|function|synaptics_parse_hw_state
r_static
r_void
id|synaptics_parse_hw_state
c_func
(paren
r_int
r_char
id|buf
(braket
)braket
comma
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
id|memset
c_func
(paren
id|hw
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|synaptics_hw_state
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
(brace
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
l_int|0x02
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
id|SYN_CAP_MIDDLE_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|hw-&gt;middle
op_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_xor
id|buf
(braket
l_int|3
)braket
)paren
op_amp
l_int|0x01
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
id|SYN_CAP_FOUR_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
(brace
id|hw-&gt;up
op_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_xor
id|buf
(braket
l_int|3
)braket
)paren
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;down
op_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_xor
id|buf
(braket
l_int|3
)braket
)paren
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
op_logical_and
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_xor
id|buf
(braket
l_int|3
)braket
)paren
op_amp
l_int|0x02
)paren
)paren
(brace
r_switch
c_cond
(paren
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
op_amp
op_complement
l_int|0x01
)paren
(brace
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * if nExtBtn is greater than 8 it should be&n;&t;&t;&t;&t; * considered invalid and treated as 0&n;&t;&t;&t;&t; */
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|5
)braket
op_amp
l_int|0x08
)paren
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|4
)braket
op_amp
l_int|0x08
)paren
)paren
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
suffix:semicolon
r_case
l_int|6
suffix:colon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|5
)braket
op_amp
l_int|0x04
)paren
)paren
ques
c_cond
l_int|0x20
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|4
)braket
op_amp
l_int|0x04
)paren
)paren
ques
c_cond
l_int|0x10
suffix:colon
l_int|0
suffix:semicolon
r_case
l_int|4
suffix:colon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|5
)braket
op_amp
l_int|0x02
)paren
)paren
ques
c_cond
l_int|0x08
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|4
)braket
op_amp
l_int|0x02
)paren
)paren
ques
c_cond
l_int|0x04
suffix:colon
l_int|0
suffix:semicolon
r_case
l_int|2
suffix:colon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|5
)braket
op_amp
l_int|0x01
)paren
)paren
ques
c_cond
l_int|0x02
suffix:colon
l_int|0
suffix:semicolon
id|hw-&gt;ext_buttons
op_or_assign
(paren
(paren
id|buf
(braket
l_int|4
)braket
op_amp
l_int|0x01
)paren
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|hw-&gt;x
op_assign
(paren
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|2
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
l_int|4
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|8
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
op_lshift
l_int|2
)paren
op_or
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x3F
)paren
)paren
suffix:semicolon
id|hw-&gt;w
op_assign
(paren
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
op_rshift
l_int|4
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
l_int|0x02
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
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
r_int
id|num_fingers
suffix:semicolon
r_int
id|finger_width
suffix:semicolon
r_int
id|i
suffix:semicolon
id|synaptics_parse_hw_state
c_func
(paren
id|psmouse-&gt;packet
comma
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
id|num_fingers
op_assign
l_int|1
suffix:semicolon
id|finger_width
op_assign
l_int|5
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
r_if
c_cond
(paren
id|SYN_CAP_MULTIFINGER
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|num_fingers
op_assign
id|hw.w
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|SYN_MODEL_PEN
c_func
(paren
id|priv-&gt;model_id
)paren
)paren
suffix:semicolon
multiline_comment|/* Nothing, treat a pen as a single finger */
r_break
suffix:semicolon
r_case
l_int|4
dot
dot
dot
l_int|15
suffix:colon
r_if
c_cond
(paren
id|SYN_CAP_PALMDETECT
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|finger_width
op_assign
id|hw.w
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|num_fingers
op_assign
l_int|0
suffix:semicolon
id|finger_width
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Post events&n;&t; * BTN_TOUCH has to be first as mousedev relies on it when doing&n;&t; * absolute -&gt; relative conversion&n;&t; */
r_if
c_cond
(paren
id|hw.z
OG
l_int|30
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw.z
OL
l_int|25
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|0
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
id|YMAX_NOMINAL
op_plus
id|YMIN_NOMINAL
op_minus
id|hw.y
)paren
suffix:semicolon
)brace
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
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_TOOL_WIDTH
comma
id|finger_width
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_FINGER
comma
id|num_fingers
op_eq
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_DOUBLETAP
comma
id|num_fingers
op_eq
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_TRIPLETAP
comma
id|num_fingers
op_eq
l_int|3
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|SYN_CAP_MIDDLE_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|hw.middle
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
(brace
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
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_0
op_plus
id|i
comma
id|hw.ext_buttons
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|synaptics_validate_byte
r_static
r_int
id|synaptics_validate_byte
c_func
(paren
r_int
r_char
id|packet
(braket
)braket
comma
r_int
id|idx
comma
r_int
r_char
id|pkt_type
)paren
(brace
r_static
r_int
r_char
id|newabs_mask
(braket
)braket
op_assign
(brace
l_int|0xC8
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xC8
comma
l_int|0x00
)brace
suffix:semicolon
r_static
r_int
r_char
id|newabs_rel_mask
(braket
)braket
op_assign
(brace
l_int|0xC0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x00
)brace
suffix:semicolon
r_static
r_int
r_char
id|newabs_rslt
(braket
)braket
op_assign
(brace
l_int|0x80
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x00
)brace
suffix:semicolon
r_static
r_int
r_char
id|oldabs_mask
(braket
)braket
op_assign
(brace
l_int|0xC0
comma
l_int|0x60
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x60
)brace
suffix:semicolon
r_static
r_int
r_char
id|oldabs_rslt
(braket
)braket
op_assign
(brace
l_int|0xC0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x80
comma
l_int|0x00
)brace
suffix:semicolon
r_if
c_cond
(paren
id|idx
template_param
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|pkt_type
)paren
(brace
r_case
id|SYN_NEWABS
suffix:colon
r_case
id|SYN_NEWABS_RELAXED
suffix:colon
r_return
(paren
id|packet
(braket
id|idx
)braket
op_amp
id|newabs_rel_mask
(braket
id|idx
)braket
)paren
op_eq
id|newabs_rslt
(braket
id|idx
)braket
suffix:semicolon
r_case
id|SYN_NEWABS_STRICT
suffix:colon
r_return
(paren
id|packet
(braket
id|idx
)braket
op_amp
id|newabs_mask
(braket
id|idx
)braket
)paren
op_eq
id|newabs_rslt
(braket
id|idx
)braket
suffix:semicolon
r_case
id|SYN_OLDABS
suffix:colon
r_return
(paren
id|packet
(braket
id|idx
)braket
op_amp
id|oldabs_mask
(braket
id|idx
)braket
)paren
op_eq
id|oldabs_rslt
(braket
id|idx
)braket
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;synaptics: unknown packet type %d&bslash;n&quot;
comma
id|pkt_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|synaptics_detect_pkt_type
r_static
r_int
r_char
id|synaptics_detect_pkt_type
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_int
id|i
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|synaptics_validate_byte
c_func
(paren
id|psmouse-&gt;packet
comma
id|i
comma
id|SYN_NEWABS_STRICT
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;synaptics: using relaxed packet validation&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|SYN_NEWABS_RELAXED
suffix:semicolon
)brace
r_return
id|SYN_NEWABS_STRICT
suffix:semicolon
)brace
DECL|function|synaptics_process_byte
r_static
id|psmouse_ret_t
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
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_ge
l_int|6
)paren
(brace
multiline_comment|/* Full packet received */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|priv-&gt;pkt_type
op_eq
id|SYN_NEWABS
)paren
)paren
id|priv-&gt;pkt_type
op_assign
id|synaptics_detect_pkt_type
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;ptport
op_logical_and
id|psmouse-&gt;ptport-&gt;serio-&gt;drv
op_logical_and
id|synaptics_is_pt_packet
c_func
(paren
id|psmouse-&gt;packet
)paren
)paren
id|synaptics_pass_pt_packet
c_func
(paren
id|psmouse-&gt;ptport-&gt;serio
comma
id|psmouse-&gt;packet
)paren
suffix:semicolon
r_else
id|synaptics_process_packet
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_return
id|PSMOUSE_FULL_PACKET
suffix:semicolon
)brace
r_return
id|synaptics_validate_byte
c_func
(paren
id|psmouse-&gt;packet
comma
id|psmouse-&gt;pktcnt
op_minus
l_int|1
comma
id|priv-&gt;pkt_type
)paren
ques
c_cond
id|PSMOUSE_GOOD_DATA
suffix:colon
id|PSMOUSE_BAD_DATA
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&t;Driver initialization/cleanup functions&n; ****************************************************************************/
DECL|function|set_input_params
r_static
r_void
id|set_input_params
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|synaptics_data
op_star
id|priv
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_ABS
comma
id|dev-&gt;evbit
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
id|dev
comma
id|ABS_X
comma
id|XMIN_NOMINAL
comma
id|XMAX_NOMINAL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
id|dev
comma
id|ABS_Y
comma
id|YMIN_NOMINAL
comma
id|YMAX_NOMINAL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
id|dev
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
id|ABS_TOOL_WIDTH
comma
id|dev-&gt;absbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_KEY
comma
id|dev-&gt;evbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_TOUCH
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_TOOL_FINGER
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_TOOL_DOUBLETAP
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_TOOL_TRIPLETAP
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_LEFT
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_RIGHT
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_MIDDLE_BUTTON
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|set_bit
c_func
(paren
id|BTN_MIDDLE
comma
id|dev-&gt;keybit
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
(brace
id|set_bit
c_func
(paren
id|BTN_FORWARD
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_BACK
comma
id|dev-&gt;keybit
)paren
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
id|SYN_CAP_MULTI_BUTTON_NO
c_func
(paren
id|priv-&gt;ext_cap
)paren
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|BTN_0
op_plus
id|i
comma
id|dev-&gt;keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|EV_REL
comma
id|dev-&gt;evbit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|REL_X
comma
id|dev-&gt;relbit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|REL_Y
comma
id|dev-&gt;relbit
)paren
suffix:semicolon
)brace
DECL|function|synaptics_reset
r_void
id|synaptics_reset
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
multiline_comment|/* reset touchpad back to relative mode, gestures enabled */
id|synaptics_mode_cmd
c_func
(paren
id|psmouse
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|synaptics_disconnect
r_static
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
id|synaptics_reset
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|psmouse
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
)brace
DECL|function|synaptics_reconnect
r_static
r_int
id|synaptics_reconnect
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
r_struct
id|synaptics_data
id|old_priv
op_assign
op_star
id|priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|synaptics_detect
c_func
(paren
id|psmouse
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|synaptics_query_hardware
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
l_string|&quot;Unable to query Synaptics hardware.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_priv.identity
op_ne
id|priv-&gt;identity
op_logical_or
id|old_priv.model_id
op_ne
id|priv-&gt;model_id
op_logical_or
id|old_priv.capabilities
op_ne
id|priv-&gt;capabilities
op_logical_or
id|old_priv.ext_cap
op_ne
id|priv-&gt;ext_cap
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
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to initialize Synaptics hardware.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|synaptics_detect
r_int
id|synaptics_detect
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
id|param
(braket
l_int|4
)braket
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
suffix:semicolon
r_return
id|param
(braket
l_int|1
)braket
op_eq
l_int|0x47
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
r_if
c_cond
(paren
id|synaptics_query_hardware
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
l_string|&quot;Unable to query Synaptics hardware.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|init_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|synaptics_set_mode
c_func
(paren
id|psmouse
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to initialize Synaptics hardware.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|init_fail
suffix:semicolon
)brace
id|priv-&gt;pkt_type
op_assign
id|SYN_MODEL_NEWABS
c_func
(paren
id|priv-&gt;model_id
)paren
ques
c_cond
id|SYN_NEWABS
suffix:colon
id|SYN_OLDABS
suffix:semicolon
r_if
c_cond
(paren
id|SYN_CAP_PASS_THROUGH
c_func
(paren
id|priv-&gt;capabilities
)paren
)paren
id|synaptics_pt_create
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
id|set_input_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|priv
)paren
suffix:semicolon
id|psmouse-&gt;protocol_handler
op_assign
id|synaptics_process_byte
suffix:semicolon
id|psmouse-&gt;disconnect
op_assign
id|synaptics_disconnect
suffix:semicolon
id|psmouse-&gt;reconnect
op_assign
id|synaptics_reconnect
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
eof
