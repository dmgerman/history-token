multiline_comment|/*&n; * Logitech PS/2++ mouse driver&n; *&n; * Copyright (c) 1999-2003 Vojtech Pavlik &lt;vojtech@suse.cz&gt;&n; * Copyright (c) 2003 Eric Wong &lt;eric@yhbt.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/libps2.h&gt;
macro_line|#include &quot;psmouse.h&quot;
macro_line|#include &quot;logips2pp.h&quot;
multiline_comment|/* Logitech mouse types */
DECL|macro|PS2PP_KIND_WHEEL
mdefine_line|#define PS2PP_KIND_WHEEL&t;1
DECL|macro|PS2PP_KIND_MX
mdefine_line|#define PS2PP_KIND_MX&t;&t;2
DECL|macro|PS2PP_KIND_TP3
mdefine_line|#define PS2PP_KIND_TP3&t;&t;3
multiline_comment|/* Logitech mouse features */
DECL|macro|PS2PP_WHEEL
mdefine_line|#define PS2PP_WHEEL&t;&t;0x01
DECL|macro|PS2PP_HWHEEL
mdefine_line|#define PS2PP_HWHEEL&t;&t;0x02
DECL|macro|PS2PP_SIDE_BTN
mdefine_line|#define PS2PP_SIDE_BTN&t;&t;0x04
DECL|macro|PS2PP_EXTRA_BTN
mdefine_line|#define PS2PP_EXTRA_BTN&t;&t;0x08
DECL|macro|PS2PP_TASK_BTN
mdefine_line|#define PS2PP_TASK_BTN&t;&t;0x10
DECL|macro|PS2PP_NAV_BTN
mdefine_line|#define PS2PP_NAV_BTN&t;&t;0x20
DECL|struct|ps2pp_info
r_struct
id|ps2pp_info
(brace
DECL|member|model
r_const
r_int
id|model
suffix:semicolon
DECL|member|kind
r_int
r_const
r_int
id|kind
suffix:semicolon
DECL|member|features
r_int
r_const
r_int
id|features
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Process a PS2++ or PS2T++ packet.&n; */
DECL|function|ps2pp_process_packet
r_void
id|ps2pp_process_packet
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
r_int
r_char
op_star
id|packet
op_assign
id|psmouse-&gt;packet
suffix:semicolon
r_if
c_cond
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x48
)paren
op_eq
l_int|0x48
op_logical_and
(paren
id|packet
(braket
l_int|1
)braket
op_amp
l_int|0x02
)paren
op_eq
l_int|0x02
)paren
(brace
r_switch
c_cond
(paren
(paren
id|packet
(braket
l_int|1
)braket
op_rshift
l_int|4
)paren
op_or
(paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x30
)paren
)paren
(brace
r_case
l_int|0x0d
suffix:colon
multiline_comment|/* Mouse extra info */
id|input_report_rel
c_func
(paren
id|dev
comma
id|packet
(braket
l_int|2
)braket
op_amp
l_int|0x80
ques
c_cond
id|REL_HWHEEL
suffix:colon
id|REL_WHEEL
comma
(paren
r_int
)paren
(paren
id|packet
(braket
l_int|2
)braket
op_amp
l_int|8
)paren
op_minus
(paren
r_int
)paren
(paren
id|packet
(braket
l_int|2
)braket
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_EXTRA
comma
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0e
suffix:colon
multiline_comment|/* buttons 4, 5, 6, 7, 8, 9, 10 info */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
(paren
id|packet
(braket
l_int|2
)braket
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_EXTRA
comma
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_BACK
comma
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_FORWARD
comma
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TASK
comma
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0f
suffix:colon
multiline_comment|/* TouchPad extra info */
id|input_report_rel
c_func
(paren
id|dev
comma
id|packet
(braket
l_int|2
)braket
op_amp
l_int|0x08
ques
c_cond
id|REL_HWHEEL
suffix:colon
id|REL_WHEEL
comma
(paren
r_int
)paren
(paren
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|8
)paren
op_minus
(paren
r_int
)paren
(paren
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|packet
(braket
l_int|0
)braket
op_assign
id|packet
(braket
l_int|2
)braket
op_or
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef DEBUG
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;psmouse.c: Received PS2++ packet #%x, but don&squot;t know how to handle.&bslash;n&quot;
comma
(paren
id|packet
(braket
l_int|1
)braket
op_rshift
l_int|4
)paren
op_or
(paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x30
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
id|packet
(braket
l_int|0
)braket
op_and_assign
l_int|0x0f
suffix:semicolon
id|packet
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|packet
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * ps2pp_cmd() sends a PS2++ command, sliced into two bit&n; * pieces through the SETRES command. This is needed to send extended&n; * commands to mice on notebooks that try to understand the PS/2 protocol&n; * Ugly.&n; */
DECL|function|ps2pp_cmd
r_static
r_int
id|ps2pp_cmd
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_char
op_star
id|param
comma
r_int
r_char
id|command
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
id|command
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
op_amp
id|psmouse-&gt;ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_POLL
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
multiline_comment|/*&n; * SmartScroll / CruiseControl for some newer Logitech mice Defaults to&n; * enabled if we do nothing to it. Of course I put this in because I want it&n; * disabled :P&n; * 1 - enabled (if previously disabled, also default)&n; * 0 - disabled&n; */
DECL|function|ps2pp_set_smartscroll
r_static
r_void
id|ps2pp_set_smartscroll
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_int
id|smartscroll
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|smartscroll
OG
l_int|1
)paren
id|smartscroll
op_assign
l_int|1
suffix:semicolon
id|ps2pp_cmd
c_func
(paren
id|psmouse
comma
id|param
comma
l_int|0x32
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
id|smartscroll
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
)brace
DECL|function|psmouse_attr_show_smartscroll
r_static
id|ssize_t
id|psmouse_attr_show_smartscroll
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
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
l_string|&quot;%d&bslash;n&quot;
comma
id|psmouse-&gt;smartscroll
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|psmouse_attr_set_smartscroll
r_static
id|ssize_t
id|psmouse_attr_set_smartscroll
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
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
r_int
r_int
id|value
suffix:semicolon
r_char
op_star
id|rest
suffix:semicolon
id|value
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
op_logical_or
id|value
OG
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ps2pp_set_smartscroll
c_func
(paren
id|psmouse
comma
id|value
)paren
suffix:semicolon
id|psmouse-&gt;smartscroll
op_assign
id|value
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|smartscroll
id|PSMOUSE_DEFINE_ATTR
c_func
(paren
id|smartscroll
)paren
suffix:semicolon
multiline_comment|/*&n; * Support 800 dpi resolution _only_ if the user wants it (there are good&n; * reasons to not use it even if the mouse supports it, and of course there are&n; * also good reasons to use it, let the user decide).&n; */
DECL|function|ps2pp_set_resolution
r_static
r_void
id|ps2pp_set_resolution
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_int
id|resolution
)paren
(brace
r_if
c_cond
(paren
id|resolution
OG
l_int|400
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
r_int
r_char
id|param
op_assign
l_int|3
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
op_amp
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|psmouse-&gt;resolution
op_assign
l_int|800
suffix:semicolon
)brace
r_else
id|psmouse_set_resolution
c_func
(paren
id|psmouse
comma
id|resolution
)paren
suffix:semicolon
)brace
DECL|function|ps2pp_disconnect
r_static
r_void
id|ps2pp_disconnect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
id|device_remove_file
c_func
(paren
op_amp
id|psmouse-&gt;ps2dev.serio-&gt;dev
comma
op_amp
id|psmouse_attr_smartscroll
)paren
suffix:semicolon
)brace
DECL|function|get_model_info
r_static
r_struct
id|ps2pp_info
op_star
id|get_model_info
c_func
(paren
r_int
r_char
id|model
)paren
(brace
r_static
r_struct
id|ps2pp_info
id|ps2pp_list
(braket
)braket
op_assign
(brace
(brace
l_int|12
comma
l_int|0
comma
id|PS2PP_SIDE_BTN
)brace
comma
(brace
l_int|13
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|40
comma
l_int|0
comma
id|PS2PP_SIDE_BTN
)brace
comma
(brace
l_int|41
comma
l_int|0
comma
id|PS2PP_SIDE_BTN
)brace
comma
(brace
l_int|42
comma
l_int|0
comma
id|PS2PP_SIDE_BTN
)brace
comma
(brace
l_int|43
comma
l_int|0
comma
id|PS2PP_SIDE_BTN
)brace
comma
(brace
l_int|50
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|51
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|52
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_SIDE_BTN
op_or
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|53
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|61
comma
id|PS2PP_KIND_MX
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_SIDE_BTN
op_or
id|PS2PP_TASK_BTN
op_or
id|PS2PP_EXTRA_BTN
op_or
id|PS2PP_NAV_BTN
)brace
comma
multiline_comment|/* MX700 */
(brace
l_int|73
comma
l_int|0
comma
id|PS2PP_SIDE_BTN
)brace
comma
(brace
l_int|75
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|76
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|80
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_SIDE_BTN
op_or
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|81
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|83
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|88
comma
id|PS2PP_KIND_WHEEL
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|96
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|97
comma
id|PS2PP_KIND_TP3
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_HWHEEL
)brace
comma
(brace
l_int|100
comma
id|PS2PP_KIND_MX
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_SIDE_BTN
op_or
id|PS2PP_TASK_BTN
op_or
id|PS2PP_EXTRA_BTN
op_or
id|PS2PP_NAV_BTN
)brace
comma
multiline_comment|/* MX510 */
(brace
l_int|112
comma
id|PS2PP_KIND_MX
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_SIDE_BTN
op_or
id|PS2PP_TASK_BTN
op_or
id|PS2PP_EXTRA_BTN
op_or
id|PS2PP_NAV_BTN
)brace
comma
multiline_comment|/* MX500 */
(brace
l_int|114
comma
id|PS2PP_KIND_MX
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_SIDE_BTN
op_or
id|PS2PP_TASK_BTN
op_or
id|PS2PP_EXTRA_BTN
)brace
comma
multiline_comment|/* M310 */
(brace
)brace
)brace
suffix:semicolon
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
id|ps2pp_list
(braket
id|i
)braket
dot
id|model
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|model
op_eq
id|ps2pp_list
(braket
id|i
)braket
dot
id|model
)paren
r_return
op_amp
id|ps2pp_list
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up input device&squot;s properties based on the detected mouse model.&n; */
DECL|function|ps2pp_set_model_properties
r_static
r_void
id|ps2pp_set_model_properties
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_struct
id|ps2pp_info
op_star
id|model_info
)paren
(brace
r_if
c_cond
(paren
id|model_info-&gt;features
op_amp
id|PS2PP_SIDE_BTN
)paren
id|set_bit
c_func
(paren
id|BTN_SIDE
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model_info-&gt;features
op_amp
id|PS2PP_EXTRA_BTN
)paren
id|set_bit
c_func
(paren
id|BTN_EXTRA
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model_info-&gt;features
op_amp
id|PS2PP_TASK_BTN
)paren
id|set_bit
c_func
(paren
id|BTN_TASK
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model_info-&gt;features
op_amp
id|PS2PP_NAV_BTN
)paren
(brace
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
)brace
r_if
c_cond
(paren
id|model_info-&gt;features
op_amp
id|PS2PP_WHEEL
)paren
id|set_bit
c_func
(paren
id|REL_WHEEL
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model_info-&gt;features
op_amp
id|PS2PP_HWHEEL
)paren
id|set_bit
c_func
(paren
id|REL_HWHEEL
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|model_info-&gt;kind
)paren
(brace
r_case
id|PS2PP_KIND_WHEEL
suffix:colon
id|psmouse-&gt;name
op_assign
l_string|&quot;Wheel Mouse&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PS2PP_KIND_MX
suffix:colon
id|psmouse-&gt;name
op_assign
l_string|&quot;MX Mouse&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PS2PP_KIND_TP3
suffix:colon
id|psmouse-&gt;name
op_assign
l_string|&quot;TouchPad 3&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Logitech magic init. Detect whether the mouse is a Logitech one&n; * and its exact model and try turning on extended protocol for ones&n; * that support it.&n; */
DECL|function|ps2pp_init
r_int
id|ps2pp_init
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
id|set_properties
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_char
id|protocol
op_assign
id|PSMOUSE_PS2
suffix:semicolon
r_int
r_char
id|model
comma
id|buttons
suffix:semicolon
r_struct
id|ps2pp_info
op_star
id|model_info
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|param
(braket
l_int|1
)braket
op_ne
l_int|0
)paren
(brace
id|model
op_assign
(paren
(paren
id|param
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
)paren
op_or
(paren
(paren
id|param
(braket
l_int|0
)braket
op_lshift
l_int|3
)paren
op_amp
l_int|0x78
)paren
suffix:semicolon
id|buttons
op_assign
id|param
(braket
l_int|1
)braket
suffix:semicolon
id|model_info
op_assign
id|get_model_info
c_func
(paren
id|model
)paren
suffix:semicolon
multiline_comment|/*&n; * Do Logitech PS2++ / PS2T++ magic init.&n; */
r_if
c_cond
(paren
id|model
op_eq
l_int|97
)paren
(brace
multiline_comment|/* Touch Pad 3 */
multiline_comment|/* Unprotect RAM */
id|param
(braket
l_int|0
)braket
op_assign
l_int|0x11
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
l_int|0x04
suffix:semicolon
id|param
(braket
l_int|2
)braket
op_assign
l_int|0x68
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
l_int|0x30d1
)paren
suffix:semicolon
multiline_comment|/* Enable features */
id|param
(braket
l_int|0
)braket
op_assign
l_int|0x11
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
l_int|0x05
suffix:semicolon
id|param
(braket
l_int|2
)braket
op_assign
l_int|0x0b
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
l_int|0x30d1
)paren
suffix:semicolon
multiline_comment|/* Enable PS2++ */
id|param
(braket
l_int|0
)braket
op_assign
l_int|0x11
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
l_int|0x09
suffix:semicolon
id|param
(braket
l_int|2
)braket
op_assign
l_int|0xc3
suffix:semicolon
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
l_int|0x30d1
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
l_int|0x13d1
)paren
op_logical_and
id|param
(braket
l_int|0
)braket
op_eq
l_int|0x06
op_logical_and
id|param
(braket
l_int|1
)braket
op_eq
l_int|0x00
op_logical_and
id|param
(braket
l_int|2
)braket
op_eq
l_int|0x14
)paren
(brace
id|protocol
op_assign
id|PSMOUSE_PS2TPP
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|model_info
op_ne
l_int|NULL
)paren
(brace
id|param
(braket
l_int|0
)braket
op_assign
id|param
(braket
l_int|1
)braket
op_assign
id|param
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|ps2pp_cmd
c_func
(paren
id|psmouse
comma
id|param
comma
l_int|0x39
)paren
suffix:semicolon
multiline_comment|/* Magic knock */
id|ps2pp_cmd
c_func
(paren
id|psmouse
comma
id|param
comma
l_int|0xDB
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|param
(braket
l_int|0
)braket
op_amp
l_int|0x78
)paren
op_eq
l_int|0x48
op_logical_and
(paren
id|param
(braket
l_int|1
)braket
op_amp
l_int|0xf3
)paren
op_eq
l_int|0xc2
op_logical_and
(paren
id|param
(braket
l_int|2
)braket
op_amp
l_int|0x03
)paren
op_eq
(paren
(paren
id|param
(braket
l_int|1
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|3
)paren
)paren
(brace
id|ps2pp_set_smartscroll
c_func
(paren
id|psmouse
comma
id|psmouse-&gt;smartscroll
)paren
suffix:semicolon
id|protocol
op_assign
id|PSMOUSE_PS2PP
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|set_properties
)paren
(brace
id|psmouse-&gt;vendor
op_assign
l_string|&quot;Logitech&quot;
suffix:semicolon
id|psmouse-&gt;model
op_assign
id|model
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
id|PSMOUSE_PS2PP
)paren
(brace
id|psmouse-&gt;set_resolution
op_assign
id|ps2pp_set_resolution
suffix:semicolon
id|psmouse-&gt;disconnect
op_assign
id|ps2pp_disconnect
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|psmouse-&gt;ps2dev.serio-&gt;dev
comma
op_amp
id|psmouse_attr_smartscroll
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buttons
OL
l_int|3
)paren
id|clear_bit
c_func
(paren
id|BTN_MIDDLE
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buttons
OL
l_int|2
)paren
id|clear_bit
c_func
(paren
id|BTN_RIGHT
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model_info
)paren
id|ps2pp_set_model_properties
c_func
(paren
id|psmouse
comma
id|model_info
)paren
suffix:semicolon
)brace
)brace
r_return
id|protocol
suffix:semicolon
)brace
eof
