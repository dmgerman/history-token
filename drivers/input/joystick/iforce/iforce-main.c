multiline_comment|/*&n; * $Id: iforce-main.c,v 1.19 2002/07/07 10:22:50 jdeneux Exp $&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&n; *  Copyright (c) 2001-2002 Johann Deneux &lt;deneux@ifrance.com&gt;&n; *&n; *  USB/RS232 I-Force joysticks and wheels.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &quot;iforce.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;, Johann Deneux &lt;deneux@ifrance.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;USB/RS232 I-Force joysticks and wheels driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|btn_joystick
r_static
r_int
r_int
id|btn_joystick
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_TOP
comma
id|BTN_THUMB
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
id|BTN_BASE5
comma
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|btn_avb_pegasus
r_static
r_int
r_int
id|btn_avb_pegasus
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_TOP
comma
id|BTN_THUMB
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|btn_wheel
r_static
r_int
r_int
id|btn_wheel
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_TOP
comma
id|BTN_THUMB
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
id|BTN_BASE5
comma
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|btn_avb_tw
r_static
r_int
r_int
id|btn_avb_tw
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_THUMB
comma
id|BTN_TOP
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|btn_avb_wheel
r_static
r_int
r_int
id|btn_avb_wheel
(braket
)braket
op_assign
(brace
id|BTN_GEAR_DOWN
comma
id|BTN_GEAR_UP
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
id|BTN_BASE5
comma
id|BTN_BASE6
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|abs_joystick
r_static
r_int
r_int
id|abs_joystick
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_THROTTLE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|abs_avb_pegasus
r_static
r_int
r_int
id|abs_avb_pegasus
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_THROTTLE
comma
id|ABS_RUDDER
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
id|ABS_HAT1X
comma
id|ABS_HAT1Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|abs_wheel
r_static
r_int
r_int
id|abs_wheel
(braket
)braket
op_assign
(brace
id|ABS_WHEEL
comma
id|ABS_GAS
comma
id|ABS_BRAKE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|ff_iforce
r_static
r_int
r_int
id|ff_iforce
(braket
)braket
op_assign
(brace
id|FF_PERIODIC
comma
id|FF_CONSTANT
comma
id|FF_SPRING
comma
id|FF_DAMPER
comma
id|FF_SQUARE
comma
id|FF_TRIANGLE
comma
id|FF_SINE
comma
id|FF_SAW_UP
comma
id|FF_SAW_DOWN
comma
id|FF_GAIN
comma
id|FF_AUTOCENTER
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|iforce_device
r_static
r_struct
id|iforce_device
id|iforce_device
(braket
)braket
op_assign
(brace
(brace
l_int|0x044f
comma
l_int|0xa01c
comma
l_string|&quot;Thrustmaster Motor Sport GT&quot;
comma
id|btn_wheel
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
(brace
l_int|0x046d
comma
l_int|0xc281
comma
l_string|&quot;Logitech WingMan Force&quot;
comma
id|btn_joystick
comma
id|abs_joystick
comma
id|ff_iforce
)brace
comma
(brace
l_int|0x046d
comma
l_int|0xc291
comma
l_string|&quot;Logitech WingMan Formula Force&quot;
comma
id|btn_wheel
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
(brace
l_int|0x05ef
comma
l_int|0x020a
comma
l_string|&quot;AVB Top Shot Pegasus&quot;
comma
id|btn_avb_pegasus
comma
id|abs_avb_pegasus
comma
id|ff_iforce
)brace
comma
(brace
l_int|0x05ef
comma
l_int|0x8884
comma
l_string|&quot;AVB Mag Turbo Force&quot;
comma
id|btn_avb_wheel
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
(brace
l_int|0x05ef
comma
l_int|0x8888
comma
l_string|&quot;AVB Top Shot Force Feedback Racing Wheel&quot;
comma
id|btn_avb_tw
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
singleline_comment|//?
(brace
l_int|0x061c
comma
l_int|0xc0a4
comma
l_string|&quot;ACT LABS Force RS&quot;
comma
id|btn_wheel
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
singleline_comment|//?
(brace
l_int|0x06f8
comma
l_int|0x0001
comma
l_string|&quot;Guillemot Race Leader Force Feedback&quot;
comma
id|btn_wheel
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
singleline_comment|//?
(brace
l_int|0x06f8
comma
l_int|0x0004
comma
l_string|&quot;Guillemot Force Feedback Racing Wheel&quot;
comma
id|btn_wheel
comma
id|abs_wheel
comma
id|ff_iforce
)brace
comma
singleline_comment|//?
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_string|&quot;Unknown I-Force Device [%04x:%04x]&quot;
comma
id|btn_joystick
comma
id|abs_joystick
comma
id|ff_iforce
)brace
)brace
suffix:semicolon
DECL|function|iforce_input_event
r_static
r_int
id|iforce_input_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
(paren
r_struct
id|iforce
op_star
)paren
(paren
id|dev
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_int
r_char
id|data
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|EV_FF
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|FF_GAIN
suffix:colon
id|data
(braket
l_int|0
)braket
op_assign
id|value
op_rshift
l_int|9
suffix:semicolon
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_GAIN
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FF_AUTOCENTER
suffix:colon
id|data
(braket
l_int|0
)braket
op_assign
l_int|0x03
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
id|value
op_rshift
l_int|9
suffix:semicolon
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_AUTOCENTER
comma
id|data
)paren
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
l_int|0x01
suffix:semicolon
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_AUTOCENTER
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Play or stop an effect */
r_if
c_cond
(paren
op_logical_neg
id|CHECK_OWNERSHIP
c_func
(paren
id|code
comma
id|iforce
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
OG
l_int|0
)paren
(brace
id|set_bit
c_func
(paren
id|FF_CORE_SHOULD_PLAY
comma
id|iforce-&gt;core_effects
(braket
id|code
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_bit
c_func
(paren
id|FF_CORE_SHOULD_PLAY
comma
id|iforce-&gt;core_effects
(braket
id|code
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
id|iforce_control_playback
c_func
(paren
id|iforce
comma
id|code
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Function called when an ioctl is performed on the event dev entry.&n; * It uploads an effect to the device&n; */
DECL|function|iforce_upload_effect
r_static
r_int
id|iforce_upload_effect
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|ff_effect
op_star
id|effect
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
(paren
r_struct
id|iforce
op_star
)paren
(paren
id|dev
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_int
id|id
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|is_update
suffix:semicolon
multiline_comment|/* Check this effect type is supported by this device */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|effect-&gt;type
comma
id|iforce-&gt;dev.ffbit
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n; * If we want to create a new effect, get a free id&n; */
r_if
c_cond
(paren
id|effect-&gt;id
op_eq
op_minus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|id
op_assign
l_int|0
suffix:semicolon
id|id
OL
id|FF_EFFECTS_MAX
suffix:semicolon
op_increment
id|id
)paren
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|FF_CORE_IS_USED
comma
id|iforce-&gt;core_effects
(braket
id|id
)braket
dot
id|flags
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
id|FF_EFFECTS_MAX
op_logical_or
id|id
op_ge
id|iforce-&gt;dev.ff_effects_max
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|effect-&gt;id
op_assign
id|id
suffix:semicolon
id|iforce-&gt;core_effects
(braket
id|id
)braket
dot
id|owner
op_assign
id|current-&gt;pid
suffix:semicolon
id|iforce-&gt;core_effects
(braket
id|id
)braket
dot
id|flags
(braket
l_int|0
)braket
op_assign
(paren
l_int|1
op_lshift
id|FF_CORE_IS_USED
)paren
suffix:semicolon
multiline_comment|/* Only IS_USED bit must be set */
id|is_update
op_assign
id|FALSE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We want to update an effect */
r_if
c_cond
(paren
op_logical_neg
id|CHECK_OWNERSHIP
c_func
(paren
id|effect-&gt;id
comma
id|iforce
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* Parameter type cannot be updated */
r_if
c_cond
(paren
id|effect-&gt;type
op_ne
id|iforce-&gt;core_effects
(braket
id|effect-&gt;id
)braket
dot
id|effect.type
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Check the effect is not already being updated */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FF_CORE_UPDATE
comma
id|iforce-&gt;core_effects
(braket
id|effect-&gt;id
)braket
dot
id|flags
)paren
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|is_update
op_assign
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n; * Upload the effect&n; */
r_switch
c_cond
(paren
id|effect-&gt;type
)paren
(brace
r_case
id|FF_PERIODIC
suffix:colon
id|ret
op_assign
id|iforce_upload_periodic
c_func
(paren
id|iforce
comma
id|effect
comma
id|is_update
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FF_CONSTANT
suffix:colon
id|ret
op_assign
id|iforce_upload_constant
c_func
(paren
id|iforce
comma
id|effect
comma
id|is_update
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FF_SPRING
suffix:colon
r_case
id|FF_DAMPER
suffix:colon
id|ret
op_assign
id|iforce_upload_condition
c_func
(paren
id|iforce
comma
id|effect
comma
id|is_update
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
multiline_comment|/* A packet was sent, forbid new updates until we are notified&n;&t;&t; * that the packet was updated&n;&t;&t; */
id|set_bit
c_func
(paren
id|FF_CORE_UPDATE
comma
id|iforce-&gt;core_effects
(braket
id|effect-&gt;id
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
id|iforce-&gt;core_effects
(braket
id|effect-&gt;id
)braket
dot
id|effect
op_assign
op_star
id|effect
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Erases an effect: it frees the effect id and mark as unused the memory&n; * allocated for the parameters&n; */
DECL|function|iforce_erase_effect
r_static
r_int
id|iforce_erase_effect
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
id|effect_id
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
(paren
r_struct
id|iforce
op_star
)paren
(paren
id|dev
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|iforce_core_effect
op_star
id|core_effect
suffix:semicolon
multiline_comment|/* Check who is trying to erase this effect */
r_if
c_cond
(paren
id|iforce-&gt;core_effects
(braket
id|effect_id
)braket
dot
id|owner
op_ne
id|current-&gt;pid
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-main.c: %d tried to erase an effect belonging to %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|iforce-&gt;core_effects
(braket
id|effect_id
)braket
dot
id|owner
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|effect_id
OL
l_int|0
op_logical_or
id|effect_id
op_ge
id|FF_EFFECTS_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|core_effect
op_assign
id|iforce-&gt;core_effects
op_plus
id|effect_id
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FF_MOD1_IS_USED
comma
id|core_effect-&gt;flags
)paren
)paren
id|err
op_assign
id|release_resource
c_func
(paren
op_amp
(paren
id|iforce-&gt;core_effects
(braket
id|effect_id
)braket
dot
id|mod1_chunk
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|test_bit
c_func
(paren
id|FF_MOD2_IS_USED
comma
id|core_effect-&gt;flags
)paren
)paren
id|err
op_assign
id|release_resource
c_func
(paren
op_amp
(paren
id|iforce-&gt;core_effects
(braket
id|effect_id
)braket
dot
id|mod2_chunk
)paren
)paren
suffix:semicolon
multiline_comment|/*TODO: remember to change that if more FF_MOD* bits are added */
id|core_effect-&gt;flags
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|iforce_open
r_static
r_int
id|iforce_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_switch
c_cond
(paren
id|iforce-&gt;bus
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
r_case
id|IFORCE_USB
suffix:colon
id|iforce-&gt;irq-&gt;dev
op_assign
id|iforce-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|iforce-&gt;irq
comma
id|GFP_KERNEL
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Enable force feedback */
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_ENABLE
comma
l_string|&quot;&bslash;004&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iforce_flush
r_static
r_int
id|iforce_flush
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Erase all effects this process owns */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;ff_effects_max
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
id|current-&gt;pid
op_eq
id|iforce-&gt;core_effects
(braket
id|i
)braket
dot
id|owner
)paren
(brace
multiline_comment|/* Stop effect */
id|input_report_ff
c_func
(paren
id|dev
comma
id|i
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Free ressources assigned to effect */
r_if
c_cond
(paren
id|iforce_erase_effect
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce_flush: erase effect %d failed&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iforce_release
r_static
r_void
id|iforce_release
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Check: no effect should be present in memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;ff_effects_max
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
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|dev-&gt;ff_effects_max
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce_release: Device still owns effects&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable force feedback playback */
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_ENABLE
comma
l_string|&quot;&bslash;001&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|iforce-&gt;bus
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
r_case
id|IFORCE_USB
suffix:colon
id|usb_unlink_urb
c_func
(paren
id|iforce-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* The device was unplugged before the file&n;&t;&t;&t; * was released */
r_if
c_cond
(paren
id|iforce-&gt;usbdev
op_eq
l_int|NULL
)paren
(brace
id|iforce_delete_device
c_func
(paren
id|iforce
)paren
suffix:semicolon
id|kfree
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
)brace
DECL|function|iforce_delete_device
r_void
id|iforce_delete_device
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
(brace
r_switch
c_cond
(paren
id|iforce-&gt;bus
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
r_case
id|IFORCE_USB
suffix:colon
id|iforce_usb_delete
c_func
(paren
id|iforce
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
r_case
id|IFORCE_232
suffix:colon
singleline_comment|//TODO: Wait for the last packets to be sent
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|iforce_init_device
r_int
id|iforce_init_device
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
(brace
r_int
r_char
id|c
(braket
)braket
op_assign
l_string|&quot;CEOV&quot;
suffix:semicolon
r_int
id|i
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|iforce-&gt;mem_mutex
)paren
suffix:semicolon
id|iforce-&gt;xmit.buf
op_assign
id|iforce-&gt;xmit_data
suffix:semicolon
id|iforce-&gt;dev.ff_effects_max
op_assign
l_int|10
suffix:semicolon
multiline_comment|/*&n; * Input device fields.&n; */
r_switch
c_cond
(paren
id|iforce-&gt;bus
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
r_case
id|IFORCE_USB
suffix:colon
id|iforce-&gt;dev.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|iforce-&gt;dev.dev
op_assign
op_amp
id|iforce-&gt;usbdev-&gt;dev
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
r_case
id|IFORCE_232
suffix:colon
id|iforce-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|iforce-&gt;dev.dev
op_assign
op_amp
id|iforce-&gt;serio-&gt;dev
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
id|iforce-&gt;dev
dot
r_private
op_assign
id|iforce
suffix:semicolon
id|iforce-&gt;dev.name
op_assign
l_string|&quot;Unknown I-Force device&quot;
suffix:semicolon
id|iforce-&gt;dev.open
op_assign
id|iforce_open
suffix:semicolon
id|iforce-&gt;dev.close
op_assign
id|iforce_release
suffix:semicolon
id|iforce-&gt;dev.flush
op_assign
id|iforce_flush
suffix:semicolon
id|iforce-&gt;dev.event
op_assign
id|iforce_input_event
suffix:semicolon
id|iforce-&gt;dev.upload_effect
op_assign
id|iforce_upload_effect
suffix:semicolon
id|iforce-&gt;dev.erase_effect
op_assign
id|iforce_erase_effect
suffix:semicolon
multiline_comment|/*&n; * On-device memory allocation.&n; */
id|iforce-&gt;device_memory.name
op_assign
l_string|&quot;I-Force device effect memory&quot;
suffix:semicolon
id|iforce-&gt;device_memory.start
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;device_memory.end
op_assign
l_int|200
suffix:semicolon
id|iforce-&gt;device_memory.flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|iforce-&gt;device_memory.parent
op_assign
l_int|NULL
suffix:semicolon
id|iforce-&gt;device_memory.child
op_assign
l_int|NULL
suffix:semicolon
id|iforce-&gt;device_memory.sibling
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Wait until device ready - until it sends its first response.&n; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|20
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|iforce_get_id_packet
c_func
(paren
id|iforce
comma
l_string|&quot;O&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|20
)paren
(brace
multiline_comment|/* 5 seconds */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;iforce-main.c: Timeout waiting for response from device.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Get device info.&n; */
r_if
c_cond
(paren
op_logical_neg
id|iforce_get_id_packet
c_func
(paren
id|iforce
comma
l_string|&quot;M&quot;
)paren
)paren
id|iforce-&gt;dev.id.vendor
op_assign
(paren
id|iforce-&gt;edata
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|iforce-&gt;edata
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-main.c: Device does not respond to id packet M&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iforce_get_id_packet
c_func
(paren
id|iforce
comma
l_string|&quot;P&quot;
)paren
)paren
id|iforce-&gt;dev.id.product
op_assign
(paren
id|iforce-&gt;edata
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|iforce-&gt;edata
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-main.c: Device does not respond to id packet P&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iforce_get_id_packet
c_func
(paren
id|iforce
comma
l_string|&quot;B&quot;
)paren
)paren
id|iforce-&gt;device_memory.end
op_assign
(paren
id|iforce-&gt;edata
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|iforce-&gt;edata
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-main.c: Device does not respond to id packet B&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iforce_get_id_packet
c_func
(paren
id|iforce
comma
l_string|&quot;N&quot;
)paren
)paren
id|iforce-&gt;dev.ff_effects_max
op_assign
id|iforce-&gt;edata
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-main.c: Device does not respond to id packet N&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Check if the device can store more effects than the driver can really handle */
r_if
c_cond
(paren
id|iforce-&gt;dev.ff_effects_max
OG
id|FF_EFFECTS_MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;input??: Device can handle %d effects, but N_EFFECTS_MAX is set to %d in iforce.h&bslash;n&quot;
comma
id|iforce-&gt;dev.ff_effects_max
comma
id|FF_EFFECTS_MAX
)paren
suffix:semicolon
id|iforce-&gt;dev.ff_effects_max
op_assign
id|FF_EFFECTS_MAX
suffix:semicolon
)brace
multiline_comment|/*&n; * Display additional info.&n; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|c
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|iforce_get_id_packet
c_func
(paren
id|iforce
comma
id|c
op_plus
id|i
)paren
)paren
id|iforce_dump_packet
c_func
(paren
l_string|&quot;info&quot;
comma
id|iforce-&gt;ecmd
comma
id|iforce-&gt;edata
)paren
suffix:semicolon
multiline_comment|/*&n; * Disable spring, enable force feedback.&n; * FIXME: We should use iforce_set_autocenter() et al here.&n; */
id|iforce_send_packet
c_func
(paren
id|iforce
comma
id|FF_CMD_AUTOCENTER
comma
l_string|&quot;&bslash;004&bslash;000&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Find appropriate device entry&n; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|iforce_device
(braket
id|i
)braket
dot
id|idvendor
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|iforce_device
(braket
id|i
)braket
dot
id|idvendor
op_eq
id|iforce-&gt;dev.id.vendor
op_logical_and
id|iforce_device
(braket
id|i
)braket
dot
id|idproduct
op_eq
id|iforce-&gt;dev.id.product
)paren
r_break
suffix:semicolon
id|iforce-&gt;type
op_assign
id|iforce_device
op_plus
id|i
suffix:semicolon
id|iforce-&gt;dev.name
op_assign
id|iforce-&gt;type-&gt;name
suffix:semicolon
multiline_comment|/*&n; * Set input device bitfields and ranges.&n; */
id|iforce-&gt;dev.evbit
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
id|EV_ABS
)paren
op_or
id|BIT
c_func
(paren
id|EV_FF
)paren
op_or
id|BIT
c_func
(paren
id|EV_FF_STATUS
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
(brace
r_int
r_int
id|t
op_assign
id|iforce-&gt;type-&gt;btn
(braket
id|i
)braket
suffix:semicolon
id|set_bit
c_func
(paren
id|t
comma
id|iforce-&gt;dev.keybit
)paren
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|BTN_DEAD
comma
id|iforce-&gt;dev.keybit
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;type-&gt;abs
(braket
id|i
)braket
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|t
op_assign
id|iforce-&gt;type-&gt;abs
(braket
id|i
)braket
suffix:semicolon
id|set_bit
c_func
(paren
id|t
comma
id|iforce-&gt;dev.absbit
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|t
)paren
(brace
r_case
id|ABS_X
suffix:colon
r_case
id|ABS_Y
suffix:colon
r_case
id|ABS_WHEEL
suffix:colon
id|iforce-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|1920
suffix:semicolon
id|iforce-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|1920
suffix:semicolon
id|iforce-&gt;dev.absflat
(braket
id|t
)braket
op_assign
l_int|128
suffix:semicolon
id|iforce-&gt;dev.absfuzz
(braket
id|t
)braket
op_assign
l_int|16
suffix:semicolon
id|set_bit
c_func
(paren
id|t
comma
id|iforce-&gt;dev.ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_THROTTLE
suffix:colon
r_case
id|ABS_GAS
suffix:colon
r_case
id|ABS_BRAKE
suffix:colon
id|iforce-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|255
suffix:semicolon
id|iforce-&gt;dev.absmin
(braket
id|t
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_RUDDER
suffix:colon
id|iforce-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|127
suffix:semicolon
id|iforce-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|128
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_HAT0X
suffix:colon
r_case
id|ABS_HAT0Y
suffix:colon
r_case
id|ABS_HAT1X
suffix:colon
r_case
id|ABS_HAT1Y
suffix:colon
id|iforce-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
id|iforce-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;type-&gt;ff
(braket
id|i
)braket
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|iforce-&gt;type-&gt;ff
(braket
id|i
)braket
comma
id|iforce-&gt;dev.ffbit
)paren
suffix:semicolon
multiline_comment|/*&n; * Register input device.&n; */
id|input_register_device
c_func
(paren
op_amp
id|iforce-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;iforce-&gt;dev.open = %p&bslash;n&quot;
comma
id|iforce-&gt;dev.open
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s [%d effects, %ld bytes memory]&bslash;n&quot;
comma
id|iforce-&gt;dev.name
comma
id|iforce-&gt;dev.ff_effects_max
comma
id|iforce-&gt;device_memory.end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iforce_init
r_static
r_int
id|__init
id|iforce_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
id|usb_register
c_func
(paren
op_amp
id|iforce_usb_driver
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
id|serio_register_driver
c_func
(paren
op_amp
id|iforce_serio_drv
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iforce_exit
r_static
r_void
id|__exit
id|iforce_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_USB
id|usb_deregister
c_func
(paren
op_amp
id|iforce_usb_driver
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JOYSTICK_IFORCE_232
id|serio_unregister_driver
c_func
(paren
op_amp
id|iforce_serio_drv
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|iforce_init
id|module_init
c_func
(paren
id|iforce_init
)paren
suffix:semicolon
DECL|variable|iforce_exit
id|module_exit
c_func
(paren
id|iforce_exit
)paren
suffix:semicolon
eof
