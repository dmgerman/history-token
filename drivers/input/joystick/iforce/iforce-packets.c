multiline_comment|/*&n; * $Id: iforce-packets.c,v 1.16 2002/07/07 10:22:50 jdeneux Exp $&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&n; *  Copyright (c) 2001-2002 Johann Deneux &lt;deneux@ifrance.com&gt;&n; *&n; *  USB/RS232 I-Force joysticks and wheels.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &quot;iforce.h&quot;
r_static
r_struct
(brace
DECL|member|x
id|__s32
id|x
suffix:semicolon
DECL|member|y
id|__s32
id|y
suffix:semicolon
DECL|variable|iforce_hat_to_axis
)brace
id|iforce_hat_to_axis
(braket
l_int|16
)braket
op_assign
(brace
(brace
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|1
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|0
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
DECL|function|iforce_dump_packet
r_void
id|iforce_dump_packet
c_func
(paren
r_char
op_star
id|msg
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;iforce.c: %s ( cmd = %04x, data = &quot;
comma
id|msg
comma
id|cmd
)paren
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
id|LO
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Send a packet of bytes to the device&n; */
DECL|function|iforce_send_packet
r_int
id|iforce_send_packet
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
(brace
multiline_comment|/* Copy data to buffer */
r_int
id|n
op_assign
id|LO
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_int
id|c
suffix:semicolon
r_int
id|empty
suffix:semicolon
r_int
id|head
comma
id|tail
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n; * Update head and tail of xmit buffer&n; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
id|head
op_assign
id|iforce-&gt;xmit.head
suffix:semicolon
id|tail
op_assign
id|iforce-&gt;xmit.tail
suffix:semicolon
r_if
c_cond
(paren
id|CIRC_SPACE
c_func
(paren
id|head
comma
id|tail
comma
id|XMIT_SIZE
)paren
OL
id|n
op_plus
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce.c: not enough space in xmit buffer to send new packet&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|empty
op_assign
id|head
op_eq
id|tail
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|iforce-&gt;xmit.head
comma
id|n
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n; * Store packet in xmit buffer&n; */
id|iforce-&gt;xmit.buf
(braket
id|head
)braket
op_assign
id|HI
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|head
comma
l_int|1
)paren
suffix:semicolon
id|iforce-&gt;xmit.buf
(braket
id|head
)braket
op_assign
id|LO
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|head
comma
l_int|1
)paren
suffix:semicolon
id|c
op_assign
id|CIRC_SPACE_TO_END
c_func
(paren
id|head
comma
id|tail
comma
id|XMIT_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|c
)paren
id|c
op_assign
id|n
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|iforce-&gt;xmit.buf
(braket
id|head
)braket
comma
id|data
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
id|c
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|iforce-&gt;xmit.buf
(braket
l_int|0
)braket
comma
id|data
op_plus
id|c
comma
id|n
op_minus
id|c
)paren
suffix:semicolon
)brace
id|XMIT_INC
c_func
(paren
id|head
comma
id|n
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * If necessary, start the transmission&n; */
r_switch
c_cond
(paren
id|iforce-&gt;bus
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
r_case
id|IFORCE_232
suffix:colon
r_if
c_cond
(paren
id|empty
)paren
id|iforce_serial_xmit
c_func
(paren
id|iforce
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
r_case
id|IFORCE_USB
suffix:colon
r_if
c_cond
(paren
id|iforce-&gt;usbdev
op_logical_and
id|empty
op_logical_and
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|IFORCE_XMIT_RUNNING
comma
id|iforce-&gt;xmit_flags
)paren
)paren
(brace
id|iforce_usb_xmit
c_func
(paren
id|iforce
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Start or stop an effect */
DECL|function|iforce_control_playback
r_int
id|iforce_control_playback
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
id|u16
id|id
comma
r_int
r_int
id|value
)paren
(brace
r_int
r_char
id|data
(braket
l_int|3
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;iforce-packets.c: control_playback %d %d&bslash;n&quot;
comma
id|id
comma
id|value
)paren
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
id|LO
c_func
(paren
id|id
)paren
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
(paren
id|value
OG
l_int|0
)paren
ques
c_cond
(paren
(paren
id|value
OG
l_int|1
)paren
ques
c_cond
l_int|0x41
suffix:colon
l_int|0x01
)paren
suffix:colon
l_int|0
suffix:semicolon
id|data
(braket
l_int|2
)braket
op_assign
id|LO
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_PLAY
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark an effect that was being updated as ready. That means it can be updated&n; * again */
DECL|function|mark_core_as_ready
r_static
r_int
id|mark_core_as_ready
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
r_int
r_int
id|addr
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
id|iforce-&gt;dev.ff_effects_max
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FF_CORE_IS_USED
comma
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|flags
)paren
op_logical_and
(paren
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|mod1_chunk.start
op_eq
id|addr
op_logical_or
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|mod2_chunk.start
op_eq
id|addr
)paren
)paren
(brace
id|clear_bit
c_func
(paren
id|FF_CORE_UPDATE
comma
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-packets.c: unused effect %04x updated !!!&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|iforce_process_packet
r_void
id|iforce_process_packet
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|iforce-&gt;dev
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
r_int
id|being_used
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|being_used
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-packets.c: re-entrant call to iforce_process %d&bslash;n&quot;
comma
id|being_used
)paren
suffix:semicolon
id|being_used
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
r_if
c_cond
(paren
id|HI
c_func
(paren
id|iforce-&gt;expect_packet
)paren
op_eq
id|HI
c_func
(paren
id|cmd
)paren
)paren
(brace
id|iforce-&gt;expect_packet
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;ecmd
op_assign
id|cmd
suffix:semicolon
id|memcpy
c_func
(paren
id|iforce-&gt;edata
comma
id|data
comma
id|IFORCE_MAX_LENGTH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|iforce-&gt;type
)paren
(brace
id|being_used
op_decrement
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|HI
c_func
(paren
id|cmd
)paren
)paren
(brace
r_case
l_int|0x01
suffix:colon
multiline_comment|/* joystick position data */
r_case
l_int|0x03
suffix:colon
multiline_comment|/* wheel position data */
r_if
c_cond
(paren
id|HI
c_func
(paren
id|cmd
)paren
op_eq
l_int|1
)paren
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_THROTTLE
comma
l_int|255
op_minus
id|data
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LO
c_func
(paren
id|cmd
)paren
op_ge
l_int|8
op_logical_and
id|test_bit
c_func
(paren
id|ABS_RUDDER
comma
id|dev-&gt;absbit
)paren
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RUDDER
comma
(paren
id|__s8
)paren
id|data
(braket
l_int|7
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_WHEEL
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_GAS
comma
l_int|255
op_minus
id|data
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_BRAKE
comma
l_int|255
op_minus
id|data
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
id|iforce_hat_to_axis
(braket
id|data
(braket
l_int|6
)braket
op_rshift
l_int|4
)braket
dot
id|x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0Y
comma
id|iforce_hat_to_axis
(braket
id|data
(braket
l_int|6
)braket
op_rshift
l_int|4
)braket
dot
id|y
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;type-&gt;btn
(braket
id|i
)braket
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|iforce-&gt;type-&gt;btn
(braket
id|i
)braket
comma
id|data
(braket
(paren
id|i
op_rshift
l_int|3
)paren
op_plus
l_int|5
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|i
op_amp
l_int|7
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* If there are untouched bits left, interpret them as the second hat */
r_if
c_cond
(paren
id|i
op_le
l_int|8
)paren
(brace
r_int
id|btns
op_assign
id|data
(braket
l_int|6
)braket
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ABS_HAT1X
comma
id|dev-&gt;absbit
)paren
)paren
(brace
r_if
c_cond
(paren
id|btns
op_amp
l_int|8
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1X
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|btns
op_amp
l_int|2
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1X
comma
l_int|1
)paren
suffix:semicolon
r_else
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1X
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ABS_HAT1Y
comma
id|dev-&gt;absbit
)paren
)paren
(brace
r_if
c_cond
(paren
id|btns
op_amp
l_int|1
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1Y
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|btns
op_amp
l_int|4
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1Y
comma
l_int|1
)paren
suffix:semicolon
r_else
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1Y
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
multiline_comment|/* status report */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_DEAD
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* Check if an effect was just started or stopped */
id|i
op_assign
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|FF_CORE_IS_PLAYED
comma
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|flags
)paren
)paren
(brace
multiline_comment|/* Report play event */
id|input_report_ff_status
c_func
(paren
id|dev
comma
id|i
comma
id|FF_STATUS_PLAYING
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|FF_CORE_IS_PLAYED
comma
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|flags
)paren
)paren
(brace
multiline_comment|/* Report stop event */
id|input_report_ff_status
c_func
(paren
id|dev
comma
id|i
comma
id|FF_STATUS_STOPPED
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|LO
c_func
(paren
id|cmd
)paren
OG
l_int|3
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|3
suffix:semicolon
id|j
OL
id|LO
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
id|mark_core_as_ready
c_func
(paren
id|iforce
comma
id|data
(braket
id|j
)braket
op_or
(paren
id|data
(braket
id|j
op_plus
l_int|1
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
id|being_used
op_decrement
suffix:semicolon
)brace
DECL|function|iforce_get_id_packet
r_int
id|iforce_get_id_packet
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
r_char
op_star
id|packet
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|timeout
op_assign
id|HZ
suffix:semicolon
multiline_comment|/* 1 second */
r_switch
c_cond
(paren
id|iforce-&gt;bus
)paren
(brace
r_case
id|IFORCE_USB
suffix:colon
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
id|iforce-&gt;cr.bRequest
op_assign
id|packet
(braket
l_int|0
)braket
suffix:semicolon
id|iforce-&gt;ctrl-&gt;dev
op_assign
id|iforce-&gt;usbdev
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|iforce-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|iforce-&gt;ctrl
comma
id|GFP_KERNEL
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|iforce-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|timeout
op_logical_and
id|iforce-&gt;ctrl-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
id|timeout
op_assign
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|iforce-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|iforce-&gt;ctrl
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;iforce_get_id_packet: iforce-&gt;bus = USB!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|IFORCE_232
suffix:colon
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
id|iforce-&gt;expect_packet
op_assign
id|FF_CMD_QUERY
suffix:semicolon
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_QUERY
comma
id|packet
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|iforce-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_logical_and
id|iforce-&gt;expect_packet
)paren
id|timeout
op_assign
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|iforce-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
(brace
id|iforce-&gt;expect_packet
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;iforce_get_id_packet: iforce-&gt;bus = SERIO!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;iforce_get_id_packet: iforce-&gt;bus = %d&bslash;n&quot;
comma
id|iforce-&gt;bus
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
op_minus
(paren
id|iforce-&gt;edata
(braket
l_int|0
)braket
op_ne
id|packet
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
eof