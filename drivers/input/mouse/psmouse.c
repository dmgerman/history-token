multiline_comment|/*&n; * PS/2 mouse driver&n; *&n; * Copyright (c) 1999-2002 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
id|MODULE_PARM
c_func
(paren
id|psmouse_noext
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|psmouse_noext
r_static
r_int
id|psmouse_noext
suffix:semicolon
DECL|macro|PSMOUSE_CMD_SETSCALE11
mdefine_line|#define PSMOUSE_CMD_SETSCALE11&t;0x00e6
DECL|macro|PSMOUSE_CMD_SETRES
mdefine_line|#define PSMOUSE_CMD_SETRES&t;0x10e8
DECL|macro|PSMOUSE_CMD_GETINFO
mdefine_line|#define PSMOUSE_CMD_GETINFO&t;0x03e9
DECL|macro|PSMOUSE_CMD_SETSTREAM
mdefine_line|#define PSMOUSE_CMD_SETSTREAM&t;0x00ea
DECL|macro|PSMOUSE_CMD_POLL
mdefine_line|#define PSMOUSE_CMD_POLL&t;0x03eb&t;
DECL|macro|PSMOUSE_CMD_GETID
mdefine_line|#define PSMOUSE_CMD_GETID&t;0x02f2
DECL|macro|PSMOUSE_CMD_SETRATE
mdefine_line|#define PSMOUSE_CMD_SETRATE&t;0x10f3
DECL|macro|PSMOUSE_CMD_ENABLE
mdefine_line|#define PSMOUSE_CMD_ENABLE&t;0x00f4
DECL|macro|PSMOUSE_CMD_RESET_DIS
mdefine_line|#define PSMOUSE_CMD_RESET_DIS&t;0x00f6
DECL|macro|PSMOUSE_CMD_RESET_BAT
mdefine_line|#define PSMOUSE_CMD_RESET_BAT&t;0x02ff
DECL|macro|PSMOUSE_RET_BAT
mdefine_line|#define PSMOUSE_RET_BAT&t;&t;0xaa
DECL|macro|PSMOUSE_RET_ACK
mdefine_line|#define PSMOUSE_RET_ACK&t;&t;0xfa
DECL|macro|PSMOUSE_RET_NAK
mdefine_line|#define PSMOUSE_RET_NAK&t;&t;0xfe
DECL|struct|psmouse
r_struct
id|psmouse
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|cmdbuf
r_int
r_char
id|cmdbuf
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|packet
r_int
r_char
id|packet
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|cmdcnt
r_int
r_char
id|cmdcnt
suffix:semicolon
DECL|member|pktcnt
r_int
r_char
id|pktcnt
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|model
r_int
r_char
id|model
suffix:semicolon
DECL|member|last
r_int
r_int
id|last
suffix:semicolon
DECL|member|acking
r_char
id|acking
suffix:semicolon
DECL|member|ack
r_volatile
r_char
id|ack
suffix:semicolon
DECL|member|error
r_char
id|error
suffix:semicolon
DECL|member|devname
r_char
id|devname
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PSMOUSE_PS2
mdefine_line|#define PSMOUSE_PS2&t;1
DECL|macro|PSMOUSE_PS2PP
mdefine_line|#define PSMOUSE_PS2PP&t;2
DECL|macro|PSMOUSE_PS2TPP
mdefine_line|#define PSMOUSE_PS2TPP&t;3
DECL|macro|PSMOUSE_GENPS
mdefine_line|#define PSMOUSE_GENPS&t;4
DECL|macro|PSMOUSE_IMPS
mdefine_line|#define PSMOUSE_IMPS&t;5
DECL|macro|PSMOUSE_IMEX
mdefine_line|#define PSMOUSE_IMEX&t;6
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
)brace
suffix:semicolon
multiline_comment|/*&n; * psmouse_process_packet() anlyzes the PS/2 mouse packet contents and&n; * reports relevant events to the input module.&n; */
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
(brace
r_if
c_cond
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x40
)paren
op_eq
l_int|0x40
op_logical_and
id|abs
c_func
(paren
(paren
r_int
)paren
id|packet
(braket
l_int|1
)braket
op_minus
(paren
(paren
(paren
r_int
)paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x10
)paren
op_lshift
l_int|4
)paren
)paren
OG
l_int|191
)paren
(brace
r_switch
c_cond
(paren
(paren
(paren
id|packet
(braket
l_int|1
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x03
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x0c
)paren
)paren
(brace
r_case
l_int|1
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
l_int|3
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
(paren
id|packet
(braket
l_int|1
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x03
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x0c
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
r_void
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
r_return
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
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
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
l_string|&quot;psmouse.c: Lost synchronization, throwing %d bytes away.&bslash;n&quot;
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
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_eq
l_int|1
op_logical_and
id|psmouse-&gt;packet
(braket
l_int|0
)braket
op_eq
id|PSMOUSE_RET_BAT
)paren
(brace
id|serio_rescan
c_func
(paren
id|serio
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
r_static
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
l_int|2000000
suffix:semicolon
multiline_comment|/* 2 sec */
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
multiline_comment|/*&n; * psmouse_ps2pp_cmd() sends a PS2++ command, sliced into two bit&n; * pieces through the SETRES command. This is needed to send extended&n; * commands to mice on notebooks that try to understand the PS/2 protocol&n; * Ugly.&n; */
DECL|function|psmouse_ps2pp_cmd
r_static
r_int
id|psmouse_ps2pp_cmd
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
r_if
c_cond
(paren
id|psmouse_noext
)paren
r_return
id|PSMOUSE_PS2
suffix:semicolon
multiline_comment|/*&n; * Try Synaptics TouchPad magic ID&n; */
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
r_if
c_cond
(paren
id|param
(braket
l_int|1
)braket
op_eq
l_int|0x47
)paren
(brace
multiline_comment|/* We could do more here. But it&squot;s sufficient just&n;                  to stop the subsequent probes from screwing the&n;                  thing up. */
id|psmouse-&gt;vendor
op_assign
l_string|&quot;Synaptics&quot;
suffix:semicolon
id|psmouse-&gt;name
op_assign
l_string|&quot;TouchPad&quot;
suffix:semicolon
r_return
id|PSMOUSE_PS2
suffix:semicolon
)brace
multiline_comment|/*&n; * Try Genius NetMouse magic init.&n; */
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
r_if
c_cond
(paren
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
multiline_comment|/*&n; * Try Logitech magic ID.&n; */
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
r_if
c_cond
(paren
id|param
(braket
l_int|1
)braket
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_int
id|logitech_4btn
(braket
)braket
op_assign
(brace
l_int|12
comma
l_int|40
comma
l_int|41
comma
l_int|42
comma
l_int|43
comma
l_int|52
comma
l_int|73
comma
l_int|80
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|logitech_wheel
(braket
)braket
op_assign
(brace
l_int|52
comma
l_int|53
comma
l_int|75
comma
l_int|76
comma
l_int|80
comma
l_int|81
comma
l_int|83
comma
l_int|88
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|logitech_ps2pp
(braket
)braket
op_assign
(brace
l_int|12
comma
l_int|13
comma
l_int|40
comma
l_int|41
comma
l_int|42
comma
l_int|43
comma
l_int|50
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|73
comma
l_int|75
comma
l_int|76
comma
l_int|80
comma
l_int|81
comma
l_int|83
comma
l_int|88
comma
l_int|96
comma
l_int|97
comma
op_minus
l_int|1
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
id|logitech_ps2pp
(braket
id|i
)braket
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|logitech_ps2pp
(braket
id|i
)braket
op_eq
id|psmouse-&gt;model
)paren
id|psmouse-&gt;type
op_assign
id|PSMOUSE_PS2PP
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;type
op_eq
id|PSMOUSE_PS2PP
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|logitech_4btn
(braket
id|i
)braket
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|logitech_4btn
(braket
id|i
)braket
op_eq
id|psmouse-&gt;model
)paren
id|set_bit
c_func
(paren
id|BTN_SIDE
comma
id|psmouse-&gt;dev.keybit
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|logitech_wheel
(braket
id|i
)braket
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|logitech_wheel
(braket
id|i
)braket
op_eq
id|psmouse-&gt;model
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
multiline_comment|/*&n; * Do Logitech PS2++ / PS2T++ magic init.&n; */
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
r_return
id|PSMOUSE_PS2TPP
suffix:semicolon
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
id|psmouse_ps2pp_cmd
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
id|psmouse_ps2pp_cmd
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
r_return
id|PSMOUSE_PS2PP
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Try IntelliMouse magic init.&n; */
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
r_if
c_cond
(paren
id|param
(braket
l_int|0
)braket
op_eq
l_int|3
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
multiline_comment|/*&n; * Try IntelliMouse/Explorer magic init.&n; */
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
r_if
c_cond
(paren
id|param
(braket
l_int|0
)braket
op_eq
l_int|4
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
multiline_comment|/*&n; * We set the mouse report rate to a highest possible value.&n; * We try 100 first in case mouse fails to set 200.&n; */
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
multiline_comment|/*&n; * We also set the resolution and scaling.&n; */
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
multiline_comment|/*&n; * Last, we enable the mouse so that we get reports from it.&n; */
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
multiline_comment|/*&n; * psmouse_connect() is a callback form the serio module when&n; * an unhandled serio port is found.&n; */
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
macro_line|#ifndef MODULE
DECL|function|psmouse_setup
r_static
r_int
id|__init
id|psmouse_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|psmouse_noext
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;psmouse_noext&quot;
comma
id|psmouse_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|function|psmouse_init
r_int
id|__init
id|psmouse_init
c_func
(paren
r_void
)paren
(brace
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
