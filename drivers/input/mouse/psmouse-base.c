multiline_comment|/*&n; * PS/2 mouse driver&n; *&n; * Copyright (c) 1999-2002 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;psmouse.h&quot;
macro_line|#include &quot;synaptics.h&quot;
macro_line|#include &quot;logips2pp.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PS/2 mouse driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_proto
r_static
r_char
op_star
id|psmouse_proto
suffix:semicolon
DECL|variable|psmouse_max_proto
r_static
r_int
r_int
id|psmouse_max_proto
op_assign
op_minus
l_int|1U
suffix:semicolon
id|module_param_named
c_func
(paren
id|proto
comma
id|psmouse_proto
comma
id|charp
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|proto
comma
l_string|&quot;Highest protocol extension to probe (bare, imps, exps). Useful for KVM switches.&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_resolution
r_int
id|psmouse_resolution
op_assign
l_int|200
suffix:semicolon
id|module_param_named
c_func
(paren
id|resolution
comma
id|psmouse_resolution
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|resolution
comma
l_string|&quot;Resolution, in dpi.&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_rate
r_int
r_int
id|psmouse_rate
op_assign
l_int|100
suffix:semicolon
id|module_param_named
c_func
(paren
id|rate
comma
id|psmouse_rate
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rate
comma
l_string|&quot;Report rate, in reports per second.&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_smartscroll
r_int
id|psmouse_smartscroll
op_assign
l_int|1
suffix:semicolon
id|module_param_named
c_func
(paren
id|smartscroll
comma
id|psmouse_smartscroll
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|smartscroll
comma
l_string|&quot;Logitech Smartscroll autorepeat, 1 = enabled (default), 0 = disabled.&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_resetafter
r_int
r_int
id|psmouse_resetafter
suffix:semicolon
id|module_param_named
c_func
(paren
id|resetafter
comma
id|psmouse_resetafter
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|resetafter
comma
l_string|&quot;Reset Synaptics Touchpad after so many bad packets (0 = never).&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_protocols
r_static
r_char
op_star
id|psmouse_protocols
(braket
)braket
op_assign
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;PS/2&quot;
comma
l_string|&quot;PS2++&quot;
comma
l_string|&quot;PS2T++&quot;
comma
l_string|&quot;GenPS/2&quot;
comma
l_string|&quot;ImPS/2&quot;
comma
l_string|&quot;ImExPS/2&quot;
comma
l_string|&quot;SynPS/2&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * psmouse_process_packet() analyzes the PS/2 mouse packet contents and&n; * reports relevant events to the input module.&n; */
DECL|function|psmouse_process_packet
r_static
r_void
id|psmouse_process_packet
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
r_int
r_char
op_star
id|packet
op_assign
id|psmouse-&gt;packet
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * The PS2++ protocol is a little bit complex&n; */
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_PS2PP
op_logical_or
id|psmouse-&gt;type
op_eq
id|PSMOUSE_PS2TPP
)paren
id|ps2pp_process_packet
c_func
(paren
id|psmouse
)paren
suffix:semicolon
multiline_comment|/*&n; * Scroll wheel on IntelliMice, scroll buttons on NetMice&n; */
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_IMPS
op_logical_or
id|psmouse-&gt;type
op_eq
id|PSMOUSE_GENPS
)paren
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
op_minus
(paren
r_int
r_char
)paren
id|packet
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/*&n; * Scroll wheel and buttons on IntelliMouse Explorer&n; */
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_IMEX
)paren
(brace
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
(paren
r_int
)paren
(paren
id|packet
(braket
l_int|3
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
l_int|3
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
l_int|3
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
l_int|3
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Extra buttons on Genius NewNet 3D&n; */
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_GENPS
)paren
(brace
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
l_int|0
)braket
op_rshift
l_int|6
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
l_int|0
)braket
op_rshift
l_int|7
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic PS/2 Mouse&n; */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|packet
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|2
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
id|BTN_RIGHT
comma
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|packet
(braket
l_int|1
)braket
ques
c_cond
(paren
r_int
)paren
id|packet
(braket
l_int|1
)braket
op_minus
(paren
r_int
)paren
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_lshift
l_int|4
)paren
op_amp
l_int|0x100
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
id|packet
(braket
l_int|2
)braket
ques
c_cond
(paren
r_int
)paren
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_lshift
l_int|3
)paren
op_amp
l_int|0x100
)paren
op_minus
(paren
r_int
)paren
id|packet
(braket
l_int|2
)braket
suffix:colon
l_int|0
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_interrupt() handles incoming characters, either gathering them into&n; * packets or passing them to the command routine as command output.&n; */
DECL|function|psmouse_interrupt
r_static
id|irqreturn_t
id|psmouse_interrupt
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|psmouse
op_star
id|psmouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;state
op_eq
id|PSMOUSE_IGNORE
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;acking
)paren
(brace
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
id|PSMOUSE_RET_ACK
suffix:colon
id|psmouse-&gt;ack
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PSMOUSE_RET_NAK
suffix:colon
id|psmouse-&gt;ack
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|psmouse-&gt;ack
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Workaround for mice which don&squot;t ACK the Get ID command */
r_if
c_cond
(paren
id|psmouse-&gt;cmdcnt
)paren
id|psmouse-&gt;cmdbuf
(braket
op_decrement
id|psmouse-&gt;cmdcnt
)braket
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
)brace
id|psmouse-&gt;acking
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse-&gt;cmdcnt
)paren
(brace
id|psmouse-&gt;cmdbuf
(braket
op_decrement
id|psmouse-&gt;cmdcnt
)braket
op_assign
id|data
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse-&gt;state
op_eq
id|PSMOUSE_ACTIVATED
op_logical_and
id|psmouse-&gt;pktcnt
op_logical_and
id|time_after
c_func
(paren
id|jiffies
comma
id|psmouse-&gt;last
op_plus
id|HZ
op_div
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;psmouse.c: %s at %s lost synchronization, throwing %d bytes away.&bslash;n&quot;
comma
id|psmouse-&gt;name
comma
id|psmouse-&gt;phys
comma
id|psmouse-&gt;pktcnt
)paren
suffix:semicolon
id|psmouse-&gt;pktcnt
op_assign
l_int|0
suffix:semicolon
)brace
id|psmouse-&gt;last
op_assign
id|jiffies
suffix:semicolon
id|psmouse-&gt;packet
(braket
id|psmouse-&gt;pktcnt
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;packet
(braket
l_int|0
)braket
op_eq
id|PSMOUSE_RET_BAT
)paren
(brace
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_eq
l_int|1
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|psmouse-&gt;packet
(braket
l_int|1
)braket
op_eq
id|PSMOUSE_RET_ID
)paren
(brace
id|psmouse-&gt;state
op_assign
id|PSMOUSE_IGNORE
suffix:semicolon
id|serio_rescan
c_func
(paren
id|serio
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_SYNAPTICS
)paren
(brace
multiline_comment|/* neither 0xAA nor 0x00 are valid first bytes&n;&t;&t;&t;&t; * for a packet in absolute mode&n;&t;&t;&t;&t; */
id|psmouse-&gt;pktcnt
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_SYNAPTICS
)paren
(brace
multiline_comment|/*&n;&t;&t; * The synaptics driver has its own resync logic,&n;&t;&t; * so it needs to receive all bytes one at a time.&n;&t;&t; */
id|synaptics_process_byte
c_func
(paren
id|psmouse
comma
id|regs
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_eq
l_int|3
op_plus
(paren
id|psmouse-&gt;type
op_ge
id|PSMOUSE_GENPS
)paren
)paren
(brace
id|psmouse_process_packet
c_func
(paren
id|psmouse
comma
id|regs
)paren
suffix:semicolon
id|psmouse-&gt;pktcnt
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_sendbyte() sends a byte to the mouse, and waits for acknowledge.&n; * It doesn&squot;t handle retransmission, though it could - because when there would&n; * be need for retransmissions, the mouse has to be replaced anyway.&n; */
DECL|function|psmouse_sendbyte
r_static
r_int
id|psmouse_sendbyte
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
r_char
id|byte
)paren
(brace
r_int
id|timeout
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* 100 msec */
id|psmouse-&gt;ack
op_assign
l_int|0
suffix:semicolon
id|psmouse-&gt;acking
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|serio_write
c_func
(paren
id|psmouse-&gt;serio
comma
id|byte
)paren
)paren
(brace
id|psmouse-&gt;acking
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|psmouse-&gt;ack
op_logical_and
id|timeout
op_decrement
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
op_minus
(paren
id|psmouse-&gt;ack
op_le
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_command() sends a command and its parameters to the mouse,&n; * then waits for the response and puts it in the param array.&n; */
DECL|function|psmouse_command
r_int
id|psmouse_command
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
id|command
)paren
(brace
r_int
id|timeout
op_assign
l_int|500000
suffix:semicolon
multiline_comment|/* 500 msec */
r_int
id|send
op_assign
(paren
id|command
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
suffix:semicolon
r_int
id|receive
op_assign
(paren
id|command
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
suffix:semicolon
r_int
id|i
suffix:semicolon
id|psmouse-&gt;cmdcnt
op_assign
id|receive
suffix:semicolon
r_if
c_cond
(paren
id|command
op_eq
id|PSMOUSE_CMD_RESET_BAT
)paren
id|timeout
op_assign
l_int|4000000
suffix:semicolon
multiline_comment|/* 4 sec */
r_if
c_cond
(paren
id|command
op_amp
l_int|0xff
)paren
r_if
c_cond
(paren
id|psmouse_sendbyte
c_func
(paren
id|psmouse
comma
id|command
op_amp
l_int|0xff
)paren
)paren
r_return
(paren
id|psmouse-&gt;cmdcnt
op_assign
l_int|0
)paren
op_minus
l_int|1
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
id|send
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|psmouse_sendbyte
c_func
(paren
id|psmouse
comma
id|param
(braket
id|i
)braket
)paren
)paren
r_return
(paren
id|psmouse-&gt;cmdcnt
op_assign
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|psmouse-&gt;cmdcnt
op_logical_and
id|timeout
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|psmouse-&gt;cmdcnt
op_eq
l_int|1
op_logical_and
id|command
op_eq
id|PSMOUSE_CMD_RESET_BAT
)paren
id|timeout
op_assign
l_int|100000
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;cmdcnt
op_eq
l_int|1
op_logical_and
id|command
op_eq
id|PSMOUSE_CMD_GETID
op_logical_and
id|psmouse-&gt;cmdbuf
(braket
l_int|1
)braket
op_ne
l_int|0xab
op_logical_and
id|psmouse-&gt;cmdbuf
(braket
l_int|1
)braket
op_ne
l_int|0xac
)paren
(brace
id|psmouse-&gt;cmdcnt
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|1
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
id|receive
suffix:semicolon
id|i
op_increment
)paren
id|param
(braket
id|i
)braket
op_assign
id|psmouse-&gt;cmdbuf
(braket
(paren
id|receive
op_minus
l_int|1
)paren
op_minus
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;cmdcnt
)paren
r_return
(paren
id|psmouse-&gt;cmdcnt
op_assign
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Genius NetMouse magic init.&n; */
DECL|function|genius_detect
r_static
r_int
id|genius_detect
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
l_int|3
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
l_int|0
)braket
op_eq
l_int|0x00
op_logical_and
id|param
(braket
l_int|1
)braket
op_eq
l_int|0x33
op_logical_and
id|param
(braket
l_int|2
)braket
op_eq
l_int|0x55
suffix:semicolon
)brace
multiline_comment|/*&n; * IntelliMouse magic init.&n; */
DECL|function|intellimouse_detect
r_static
r_int
id|intellimouse_detect
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
l_int|2
)braket
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|200
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|100
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|80
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_GETID
)paren
suffix:semicolon
r_return
id|param
(braket
l_int|0
)braket
op_eq
l_int|3
suffix:semicolon
)brace
multiline_comment|/*&n; * Try IntelliMouse/Explorer magic init.&n; */
DECL|function|im_explorer_detect
r_static
r_int
id|im_explorer_detect
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
l_int|2
)braket
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|200
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|200
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
l_int|80
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_GETID
)paren
suffix:semicolon
r_return
id|param
(braket
l_int|0
)braket
op_eq
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_extensions() probes for any extensions to the basic PS/2 protocol&n; * the mouse may have.&n; */
DECL|function|psmouse_extensions
r_static
r_int
id|psmouse_extensions
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_int
id|synaptics_hardware
op_assign
l_int|0
suffix:semicolon
id|psmouse-&gt;vendor
op_assign
l_string|&quot;Generic&quot;
suffix:semicolon
id|psmouse-&gt;name
op_assign
l_string|&quot;Mouse&quot;
suffix:semicolon
id|psmouse-&gt;model
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Try Synaptics TouchPad&n; */
r_if
c_cond
(paren
id|psmouse_max_proto
OG
id|PSMOUSE_PS2
op_logical_and
id|synaptics_detect
c_func
(paren
id|psmouse
)paren
)paren
(brace
id|synaptics_hardware
op_assign
l_int|1
suffix:semicolon
id|psmouse-&gt;vendor
op_assign
l_string|&quot;Synaptics&quot;
suffix:semicolon
id|psmouse-&gt;name
op_assign
l_string|&quot;TouchPad&quot;
suffix:semicolon
r_if
c_cond
(paren
id|psmouse_max_proto
OG
id|PSMOUSE_IMEX
)paren
(brace
r_if
c_cond
(paren
id|synaptics_init
c_func
(paren
id|psmouse
)paren
op_eq
l_int|0
)paren
r_return
id|PSMOUSE_SYNAPTICS
suffix:semicolon
multiline_comment|/*&n; * Some Synaptics touchpads can emulate extended protocols (like IMPS/2).&n; * Unfortunately Logitech/Genius probes confuse some firmware versions so&n; * we&squot;ll have to skip them.&n; */
id|psmouse_max_proto
op_assign
id|PSMOUSE_IMEX
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|psmouse_max_proto
OG
id|PSMOUSE_IMEX
op_logical_and
id|genius_detect
c_func
(paren
id|psmouse
)paren
)paren
(brace
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
id|BTN_SIDE
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|REL_WHEEL
comma
id|psmouse-&gt;dev.relbit
)paren
suffix:semicolon
id|psmouse-&gt;vendor
op_assign
l_string|&quot;Genius&quot;
suffix:semicolon
id|psmouse-&gt;name
op_assign
l_string|&quot;Wheel Mouse&quot;
suffix:semicolon
r_return
id|PSMOUSE_GENPS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse_max_proto
OG
id|PSMOUSE_IMEX
)paren
(brace
r_int
id|type
op_assign
id|ps2pp_detect
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
r_return
id|type
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse_max_proto
op_ge
id|PSMOUSE_IMPS
op_logical_and
id|intellimouse_detect
c_func
(paren
id|psmouse
)paren
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
r_if
c_cond
(paren
id|psmouse_max_proto
op_ge
id|PSMOUSE_IMEX
op_logical_and
id|im_explorer_detect
c_func
(paren
id|psmouse
)paren
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
id|psmouse-&gt;name
op_assign
l_string|&quot;Explorer Mouse&quot;
suffix:semicolon
r_return
id|PSMOUSE_IMEX
suffix:semicolon
)brace
id|psmouse-&gt;name
op_assign
l_string|&quot;Wheel Mouse&quot;
suffix:semicolon
r_return
id|PSMOUSE_IMPS
suffix:semicolon
)brace
multiline_comment|/*&n; * Okay, all failed, we have a standard mouse here. The number of the buttons&n; * is still a question, though. We assume 3.&n; */
r_if
c_cond
(paren
id|synaptics_hardware
)paren
(brace
multiline_comment|/*&n; * We detected Synaptics hardware but it did not respond to IMPS/2 probes.&n; * We need to reset the touchpad because if there is a track point on the&n; * pass through port it could get disabled while probing for protocol&n; * extensions.&n; */
id|psmouse_command
c_func
(paren
id|psmouse
comma
l_int|NULL
comma
id|PSMOUSE_CMD_RESET_DIS
)paren
suffix:semicolon
)brace
r_return
id|PSMOUSE_PS2
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_probe() probes for a PS/2 mouse.&n; */
DECL|function|psmouse_probe
r_static
r_int
id|psmouse_probe
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
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n; * First, we check if it&squot;s a mouse. It should send 0x00 or 0x03&n; * in case of an IntelliMouse in 4-byte mode or 0x04 for IM Explorer.&n; */
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
l_int|0xa5
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
id|PSMOUSE_CMD_GETID
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|param
(braket
l_int|0
)braket
op_ne
l_int|0x00
op_logical_and
id|param
(braket
l_int|0
)braket
op_ne
l_int|0x03
op_logical_and
id|param
(braket
l_int|0
)braket
op_ne
l_int|0x04
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Then we reset and disable the mouse so that it doesn&squot;t generate events.&n; */
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
id|PSMOUSE_CMD_RESET_DIS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * And here we try to determine if it has any extensions over the&n; * basic PS/2 3-button mouse.&n; */
r_return
id|psmouse-&gt;type
op_assign
id|psmouse_extensions
c_func
(paren
id|psmouse
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Here we set the mouse resolution.&n; */
DECL|function|psmouse_set_resolution
r_static
r_void
id|psmouse_set_resolution
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
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_PS2PP
op_logical_and
id|psmouse_resolution
OG
l_int|400
)paren
(brace
id|ps2pp_set_800dpi
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|psmouse_resolution
op_logical_or
id|psmouse_resolution
op_ge
l_int|200
)paren
id|param
(braket
l_int|0
)braket
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|psmouse_resolution
op_ge
l_int|100
)paren
id|param
(braket
l_int|0
)braket
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|psmouse_resolution
op_ge
l_int|50
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
id|psmouse_resolution
)paren
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
)brace
multiline_comment|/*&n; * Here we set the mouse report rate.&n; */
DECL|function|psmouse_set_rate
r_static
r_void
id|psmouse_set_rate
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
id|rates
(braket
)braket
op_assign
(brace
l_int|200
comma
l_int|100
comma
l_int|80
comma
l_int|60
comma
l_int|40
comma
l_int|20
comma
l_int|10
comma
l_int|0
)brace
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|rates
(braket
id|i
)braket
OG
id|psmouse_rate
)paren
id|i
op_increment
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|rates
op_plus
id|i
comma
id|PSMOUSE_CMD_SETRATE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_initialize() initializes the mouse to a sane state.&n; */
DECL|function|psmouse_initialize
r_static
r_void
id|psmouse_initialize
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
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n; * We set the mouse report rate, resolution and scaling.&n; */
r_if
c_cond
(paren
id|psmouse_max_proto
op_ne
id|PSMOUSE_PS2
)paren
(brace
id|psmouse_set_rate
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|psmouse_set_resolution
c_func
(paren
id|psmouse
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
)brace
multiline_comment|/*&n; * We set the mouse into streaming mode.&n; */
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_SETSTREAM
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_activate() enables the mouse so that we get motion reports from it.&n; */
DECL|function|psmouse_activate
r_static
r_void
id|psmouse_activate
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;psmouse.c: Failed to enable mouse on %s&bslash;n&quot;
comma
id|psmouse-&gt;serio-&gt;phys
)paren
suffix:semicolon
id|psmouse-&gt;state
op_assign
id|PSMOUSE_ACTIVATED
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_cleanup() resets the mouse into power-on state.&n; */
DECL|function|psmouse_cleanup
r_static
r_void
id|psmouse_cleanup
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|psmouse
op_star
id|psmouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|2
)braket
suffix:semicolon
id|psmouse_command
c_func
(paren
id|psmouse
comma
id|param
comma
id|PSMOUSE_CMD_RESET_BAT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_disconnect() closes and frees.&n; */
DECL|function|psmouse_disconnect
r_static
r_void
id|psmouse_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|psmouse
op_star
id|psmouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|psmouse-&gt;state
op_assign
id|PSMOUSE_IGNORE
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;ptport
)paren
(brace
r_if
c_cond
(paren
id|psmouse-&gt;ptport-&gt;deactivate
)paren
id|psmouse-&gt;ptport
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|__serio_unregister_port
c_func
(paren
op_amp
id|psmouse-&gt;ptport-&gt;serio
)paren
suffix:semicolon
multiline_comment|/* we have serio_sem */
id|kfree
c_func
(paren
id|psmouse-&gt;ptport
)paren
suffix:semicolon
id|psmouse-&gt;ptport
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse-&gt;disconnect
)paren
id|psmouse
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|psmouse-&gt;dev
)paren
suffix:semicolon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|psmouse
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * psmouse_connect() is a callback from the serio module when&n; * an unhandled serio port is found.&n; */
DECL|function|psmouse_connect
r_static
r_void
id|psmouse_connect
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_dev
op_star
id|dev
)paren
(brace
r_struct
id|psmouse
op_star
id|psmouse
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_TYPE
)paren
op_ne
id|SERIO_8042
op_logical_and
(paren
id|serio-&gt;type
op_amp
id|SERIO_TYPE
)paren
op_ne
id|SERIO_PS_PSTHRU
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|psmouse
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|psmouse
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|psmouse
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|psmouse
)paren
)paren
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|psmouse-&gt;dev
)paren
suffix:semicolon
id|psmouse-&gt;dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REL
)paren
suffix:semicolon
id|psmouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
suffix:semicolon
id|psmouse-&gt;dev.relbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|REL_X
)paren
op_or
id|BIT
c_func
(paren
id|REL_Y
)paren
suffix:semicolon
id|psmouse-&gt;state
op_assign
id|PSMOUSE_NEW_DEVICE
suffix:semicolon
id|psmouse-&gt;serio
op_assign
id|serio
suffix:semicolon
id|psmouse-&gt;dev
dot
r_private
op_assign
id|psmouse
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|psmouse
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|dev
)paren
)paren
(brace
id|kfree
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse_probe
c_func
(paren
id|psmouse
)paren
op_le
l_int|0
)paren
(brace
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|psmouse-&gt;devname
comma
l_string|&quot;%s %s %s&quot;
comma
id|psmouse_protocols
(braket
id|psmouse-&gt;type
)braket
comma
id|psmouse-&gt;vendor
comma
id|psmouse-&gt;name
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|psmouse-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|psmouse-&gt;dev.name
op_assign
id|psmouse-&gt;devname
suffix:semicolon
id|psmouse-&gt;dev.phys
op_assign
id|psmouse-&gt;phys
suffix:semicolon
id|psmouse-&gt;dev.id.bustype
op_assign
id|BUS_I8042
suffix:semicolon
id|psmouse-&gt;dev.id.vendor
op_assign
l_int|0x0002
suffix:semicolon
id|psmouse-&gt;dev.id.product
op_assign
id|psmouse-&gt;type
suffix:semicolon
id|psmouse-&gt;dev.id.version
op_assign
id|psmouse-&gt;model
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|psmouse-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|psmouse-&gt;devname
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|psmouse_initialize
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;ptport
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: %s port at %s&bslash;n&quot;
comma
id|psmouse-&gt;ptport-&gt;serio.name
comma
id|psmouse-&gt;phys
)paren
suffix:semicolon
id|__serio_register_port
c_func
(paren
op_amp
id|psmouse-&gt;ptport-&gt;serio
)paren
suffix:semicolon
multiline_comment|/* we have serio_sem */
r_if
c_cond
(paren
id|psmouse-&gt;ptport-&gt;activate
)paren
id|psmouse-&gt;ptport
op_member_access_from_pointer
id|activate
c_func
(paren
id|psmouse
)paren
suffix:semicolon
)brace
id|psmouse_activate
c_func
(paren
id|psmouse
)paren
suffix:semicolon
)brace
DECL|function|psmouse_reconnect
r_static
r_int
id|psmouse_reconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|psmouse
op_star
id|psmouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|serio_dev
op_star
id|dev
op_assign
id|serio-&gt;dev
suffix:semicolon
r_int
id|old_type
op_assign
id|psmouse-&gt;type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;psmouse: reconnect request, but serio is disconnected, ignoring...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|psmouse-&gt;state
op_assign
id|PSMOUSE_NEW_DEVICE
suffix:semicolon
id|psmouse-&gt;type
op_assign
id|psmouse-&gt;acking
op_assign
id|psmouse-&gt;cmdcnt
op_assign
id|psmouse-&gt;pktcnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;reconnect
)paren
(brace
r_if
c_cond
(paren
id|psmouse
op_member_access_from_pointer
id|reconnect
c_func
(paren
id|psmouse
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|psmouse_probe
c_func
(paren
id|psmouse
)paren
op_ne
id|old_type
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* ok, the device type (and capabilities) match the old one,&n;&t; * we can continue using it, complete intialization&n;&t; */
id|psmouse-&gt;type
op_assign
id|old_type
suffix:semicolon
id|psmouse_initialize
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;ptport
)paren
(brace
r_if
c_cond
(paren
id|psmouse_reconnect
c_func
(paren
op_amp
id|psmouse-&gt;ptport-&gt;serio
)paren
)paren
(brace
id|__serio_unregister_port
c_func
(paren
op_amp
id|psmouse-&gt;ptport-&gt;serio
)paren
suffix:semicolon
id|__serio_register_port
c_func
(paren
op_amp
id|psmouse-&gt;ptport-&gt;serio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;ptport-&gt;activate
)paren
id|psmouse-&gt;ptport
op_member_access_from_pointer
id|activate
c_func
(paren
id|psmouse
)paren
suffix:semicolon
)brace
)brace
id|psmouse_activate
c_func
(paren
id|psmouse
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|psmouse_dev
r_static
r_struct
id|serio_dev
id|psmouse_dev
op_assign
(brace
dot
id|interrupt
op_assign
id|psmouse_interrupt
comma
dot
id|connect
op_assign
id|psmouse_connect
comma
dot
id|reconnect
op_assign
id|psmouse_reconnect
comma
dot
id|disconnect
op_assign
id|psmouse_disconnect
comma
dot
id|cleanup
op_assign
id|psmouse_cleanup
comma
)brace
suffix:semicolon
DECL|function|psmouse_parse_proto
r_static
r_inline
r_void
id|psmouse_parse_proto
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|psmouse_proto
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|psmouse_proto
comma
l_string|&quot;bare&quot;
)paren
)paren
id|psmouse_max_proto
op_assign
id|PSMOUSE_PS2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|psmouse_proto
comma
l_string|&quot;imps&quot;
)paren
)paren
id|psmouse_max_proto
op_assign
id|PSMOUSE_IMPS
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|psmouse_proto
comma
l_string|&quot;exps&quot;
)paren
)paren
id|psmouse_max_proto
op_assign
id|PSMOUSE_IMEX
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;psmouse: unknown protocol type &squot;%s&squot;&bslash;n&quot;
comma
id|psmouse_proto
)paren
suffix:semicolon
)brace
)brace
DECL|function|psmouse_init
r_int
id|__init
id|psmouse_init
c_func
(paren
r_void
)paren
(brace
id|psmouse_parse_proto
c_func
(paren
)paren
suffix:semicolon
id|serio_register_device
c_func
(paren
op_amp
id|psmouse_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|psmouse_exit
r_void
id|__exit
id|psmouse_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|psmouse_dev
)paren
suffix:semicolon
)brace
DECL|variable|psmouse_init
id|module_init
c_func
(paren
id|psmouse_init
)paren
suffix:semicolon
DECL|variable|psmouse_exit
id|module_exit
c_func
(paren
id|psmouse_exit
)paren
suffix:semicolon
eof
