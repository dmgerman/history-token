multiline_comment|/*&n; * Logitech PS/2++ mouse driver&n; *&n; * Copyright (c) 1999-2003 Vojtech Pavlik &lt;vojtech@suse.cz&gt;&n; * Copyright (c) 2003 Eric Wong &lt;eric@yhbt.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &quot;psmouse.h&quot;
macro_line|#include &quot;logips2pp.h&quot;
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
r_int
r_char
id|d
suffix:semicolon
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
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n; * SmartScroll / CruiseControl for some newer Logitech mice Defaults to&n; * enabled if we do nothing to it. Of course I put this in because I want it&n; * disabled :P&n; * 1 - enabled (if previously disabled, also default)&n; * 0/2 - disabled &n; */
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
)paren
(brace
r_int
r_char
id|param
(braket
l_int|4
)braket
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
r_if
c_cond
(paren
id|psmouse_smartscroll
op_eq
l_int|1
)paren
id|param
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|psmouse_smartscroll
OG
l_int|2
)paren
r_return
suffix:semicolon
multiline_comment|/* else leave param[0] == 0 to disable */
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
)brace
multiline_comment|/*&n; * Support 800 dpi resolution _only_ if the user wants it (there are good&n; * reasons to not use it even if the mouse supports it, and of course there are&n; * also good reasons to use it, let the user decide).&n; */
DECL|function|ps2pp_set_800dpi
r_void
id|ps2pp_set_800dpi
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
op_assign
l_int|3
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
op_amp
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Detect the exact model and features of a PS2++ or PS2T++ Logitech mouse or&n; * touchpad.&n; */
DECL|function|ps2pp_detect_model
r_static
r_int
id|ps2pp_detect_model
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
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_struct
id|_logips2_list
(brace
r_const
r_int
id|model
suffix:semicolon
r_int
r_const
r_int
id|features
suffix:semicolon
)brace
id|logips2pp_list
(braket
)braket
op_assign
(brace
(brace
l_int|12
comma
id|PS2PP_4BTN
)brace
comma
(brace
l_int|13
comma
l_int|0
)brace
comma
(brace
l_int|40
comma
id|PS2PP_4BTN
)brace
comma
(brace
l_int|41
comma
id|PS2PP_4BTN
)brace
comma
(brace
l_int|42
comma
id|PS2PP_4BTN
)brace
comma
(brace
l_int|43
comma
id|PS2PP_4BTN
)brace
comma
(brace
l_int|50
comma
l_int|0
)brace
comma
(brace
l_int|51
comma
l_int|0
)brace
comma
(brace
l_int|52
comma
id|PS2PP_4BTN
op_or
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|53
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|61
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_MX
)brace
comma
multiline_comment|/* MX700 */
(brace
l_int|73
comma
id|PS2PP_4BTN
)brace
comma
(brace
l_int|75
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|76
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|80
comma
id|PS2PP_4BTN
op_or
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|81
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|83
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|88
comma
id|PS2PP_WHEEL
)brace
comma
(brace
l_int|96
comma
l_int|0
)brace
comma
(brace
l_int|97
comma
l_int|0
)brace
comma
(brace
l_int|100
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_MX
)brace
comma
multiline_comment|/* MX510 */
(brace
l_int|112
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_MX
)brace
comma
multiline_comment|/* MX500 */
(brace
l_int|114
comma
id|PS2PP_WHEEL
op_or
id|PS2PP_MX
op_or
id|PS2PP_MX310
)brace
comma
multiline_comment|/* MX310 */
(brace
)brace
)brace
suffix:semicolon
id|psmouse-&gt;vendor
op_assign
l_string|&quot;Logitech&quot;
suffix:semicolon
id|psmouse-&gt;model
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
r_if
c_cond
(paren
id|param
(braket
l_int|1
)braket
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
id|param
(braket
l_int|1
)braket
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
id|psmouse-&gt;type
op_assign
id|PSMOUSE_PS2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|logips2pp_list
(braket
id|i
)braket
dot
id|model
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|logips2pp_list
(braket
id|i
)braket
dot
id|model
op_eq
id|psmouse-&gt;model
)paren
(brace
id|psmouse-&gt;type
op_assign
id|PSMOUSE_PS2PP
suffix:semicolon
r_if
c_cond
(paren
id|logips2pp_list
(braket
id|i
)braket
dot
id|features
op_amp
id|PS2PP_4BTN
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
id|logips2pp_list
(braket
id|i
)braket
dot
id|features
op_amp
id|PS2PP_WHEEL
)paren
(brace
id|set_bit
c_func
(paren
id|REL_WHEEL
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
id|psmouse-&gt;name
op_assign
l_string|&quot;Wheel Mouse&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|logips2pp_list
(braket
id|i
)braket
dot
id|features
op_amp
id|PS2PP_MX
)paren
(brace
id|set_bit
c_func
(paren
id|BTN_SIDE
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_EXTRA
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
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
op_logical_neg
(paren
id|logips2pp_list
(braket
id|i
)braket
dot
id|features
op_amp
id|PS2PP_MX310
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|BTN_BACK
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
)brace
id|psmouse-&gt;name
op_assign
l_string|&quot;MX Mouse&quot;
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Do Logitech PS2++ / PS2T++ magic init.&n; */
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_PS2PP
)paren
(brace
r_if
c_cond
(paren
id|psmouse-&gt;model
op_eq
l_int|97
)paren
(brace
multiline_comment|/* TouchPad 3 */
id|set_bit
c_func
(paren
id|REL_WHEEL
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|REL_HWHEEL
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
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
multiline_comment|/* Unprotect RAM */
id|psmouse_command
c_func
(paren
id|psmouse
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
multiline_comment|/* Enable features */
id|psmouse_command
c_func
(paren
id|psmouse
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
multiline_comment|/* Enable PS2++ */
id|psmouse_command
c_func
(paren
id|psmouse
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
id|psmouse_command
c_func
(paren
id|psmouse
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
id|psmouse-&gt;name
op_assign
l_string|&quot;TouchPad 3&quot;
suffix:semicolon
r_return
id|PSMOUSE_PS2TPP
suffix:semicolon
)brace
)brace
r_else
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
l_int|3
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
)paren
suffix:semicolon
r_return
id|PSMOUSE_PS2PP
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Logitech magic init.&n; */
DECL|function|ps2pp_detect
r_int
id|ps2pp_detect
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
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
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
op_ne
l_int|0
ques
c_cond
id|ps2pp_detect_model
c_func
(paren
id|psmouse
comma
id|param
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
