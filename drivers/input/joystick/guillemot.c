multiline_comment|/*&n; * $Id: guillemot.c,v 1.10 2002/01/22 20:28:12 vojtech Exp $&n; *&n; *  Copyright (c) 2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * Guillemot Digital Interface Protocol driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;Guillemot Digital joystick driver&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|GUILLEMOT_MAX_START
mdefine_line|#define GUILLEMOT_MAX_START&t;600&t;/* 600 us */
DECL|macro|GUILLEMOT_MAX_STROBE
mdefine_line|#define GUILLEMOT_MAX_STROBE&t;60&t;/* 60 us */
DECL|macro|GUILLEMOT_MAX_LENGTH
mdefine_line|#define GUILLEMOT_MAX_LENGTH&t;17&t;/* 17 bytes */
DECL|variable|guillemot_abs_pad
r_static
r_int
id|guillemot_abs_pad
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
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|guillemot_btn_pad
r_static
r_int
id|guillemot_btn_pad
(braket
)braket
op_assign
(brace
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
comma
id|BTN_X
comma
id|BTN_Y
comma
id|BTN_Z
comma
id|BTN_TL
comma
id|BTN_TR
comma
id|BTN_MODE
comma
id|BTN_SELECT
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|variable|guillemot_hat_to_axis
)brace
id|guillemot_hat_to_axis
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
DECL|struct|guillemot_type
r_struct
id|guillemot_type
(brace
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
DECL|member|abs
r_int
op_star
id|abs
suffix:semicolon
DECL|member|btn
r_int
op_star
id|btn
suffix:semicolon
DECL|member|hat
r_int
id|hat
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|guillemot
r_struct
id|guillemot
(brace
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|bads
r_int
id|bads
suffix:semicolon
DECL|member|reads
r_int
id|reads
suffix:semicolon
DECL|member|type
r_struct
id|guillemot_type
op_star
id|type
suffix:semicolon
DECL|member|length
r_int
r_char
id|length
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
DECL|variable|guillemot_type
r_static
r_struct
id|guillemot_type
id|guillemot_type
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
id|guillemot_abs_pad
comma
id|guillemot_btn_pad
comma
l_int|1
comma
l_string|&quot;Guillemot Pad&quot;
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * guillemot_read_packet() reads Guillemot joystick data.&n; */
DECL|function|guillemot_read_packet
r_static
r_int
id|guillemot_read_packet
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
id|u8
op_star
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|u
comma
id|v
suffix:semicolon
r_int
r_int
id|t
comma
id|s
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
id|i
OL
id|GUILLEMOT_MAX_LENGTH
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|t
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GUILLEMOT_MAX_START
)paren
suffix:semicolon
id|s
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GUILLEMOT_MAX_STROBE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|v
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_while
c_loop
(paren
id|t
OG
l_int|0
op_logical_and
id|i
OL
id|GUILLEMOT_MAX_LENGTH
op_star
l_int|8
)paren
(brace
id|t
op_decrement
suffix:semicolon
id|u
op_assign
id|v
suffix:semicolon
id|v
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_amp
op_complement
id|u
op_amp
l_int|0x10
)paren
(brace
id|data
(braket
id|i
op_rshift
l_int|3
)braket
op_or_assign
(paren
(paren
id|v
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
op_lshift
(paren
id|i
op_amp
l_int|7
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|t
op_assign
id|s
suffix:semicolon
)brace
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * guillemot_poll() reads and analyzes Guillemot joystick data.&n; */
DECL|function|guillemot_poll
r_static
r_void
id|guillemot_poll
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|guillemot
op_star
id|guillemot
op_assign
id|gameport_get_drvdata
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|guillemot-&gt;dev
suffix:semicolon
id|u8
id|data
(braket
id|GUILLEMOT_MAX_LENGTH
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|guillemot-&gt;reads
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|guillemot_read_packet
c_func
(paren
id|guillemot-&gt;gameport
comma
id|data
)paren
op_ne
id|GUILLEMOT_MAX_LENGTH
op_star
l_int|8
op_logical_or
id|data
(braket
l_int|0
)braket
op_ne
l_int|0x55
op_logical_or
id|data
(braket
l_int|16
)braket
op_ne
l_int|0xaa
)paren
(brace
id|guillemot-&gt;bads
op_increment
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
op_logical_and
id|guillemot-&gt;type-&gt;abs
(braket
id|i
)braket
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|guillemot-&gt;type-&gt;abs
(braket
id|i
)braket
comma
id|data
(braket
id|i
op_plus
l_int|5
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|guillemot-&gt;type-&gt;hat
)paren
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
id|guillemot_hat_to_axis
(braket
id|data
(braket
l_int|4
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
id|guillemot_hat_to_axis
(braket
id|data
(braket
l_int|4
)braket
op_rshift
l_int|4
)braket
dot
id|y
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
l_int|16
op_logical_and
id|guillemot-&gt;type-&gt;btn
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
id|guillemot-&gt;type-&gt;btn
(braket
id|i
)braket
comma
(paren
id|data
(braket
l_int|2
op_plus
(paren
id|i
op_rshift
l_int|3
)paren
)braket
op_rshift
(paren
id|i
op_amp
l_int|7
)paren
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * guillemot_open() is a callback from the input open routine.&n; */
DECL|function|guillemot_open
r_static
r_int
id|guillemot_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|guillemot
op_star
id|guillemot
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|gameport_start_polling
c_func
(paren
id|guillemot-&gt;gameport
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * guillemot_close() is a callback from the input close routine.&n; */
DECL|function|guillemot_close
r_static
r_void
id|guillemot_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|guillemot
op_star
id|guillemot
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|gameport_stop_polling
c_func
(paren
id|guillemot-&gt;gameport
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * guillemot_connect() probes for Guillemot joysticks.&n; */
DECL|function|guillemot_connect
r_static
r_int
id|guillemot_connect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_struct
id|gameport_driver
op_star
id|drv
)paren
(brace
r_struct
id|guillemot
op_star
id|guillemot
suffix:semicolon
id|u8
id|data
(braket
id|GUILLEMOT_MAX_LENGTH
)braket
suffix:semicolon
r_int
id|i
comma
id|t
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|guillemot
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|guillemot
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|guillemot-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|gameport_set_drvdata
c_func
(paren
id|gameport
comma
id|guillemot
)paren
suffix:semicolon
id|err
op_assign
id|gameport_open
c_func
(paren
id|gameport
comma
id|drv
comma
id|GAMEPORT_MODE_RAW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail1
suffix:semicolon
id|i
op_assign
id|guillemot_read_packet
c_func
(paren
id|gameport
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|GUILLEMOT_MAX_LENGTH
op_star
l_int|8
op_logical_or
id|data
(braket
l_int|0
)braket
op_ne
l_int|0x55
op_logical_or
id|data
(braket
l_int|16
)braket
op_ne
l_int|0xaa
)paren
(brace
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail2
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|guillemot_type
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|guillemot_type
(braket
id|i
)braket
dot
id|id
op_eq
id|data
(braket
l_int|11
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|guillemot_type
(braket
id|i
)braket
dot
id|name
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;guillemot.c: Unknown joystick on %s. [ %02x%02x:%04x, ver %d.%02d ]&bslash;n&quot;
comma
id|gameport-&gt;phys
comma
id|data
(braket
l_int|12
)braket
comma
id|data
(braket
l_int|13
)braket
comma
id|data
(braket
l_int|11
)braket
comma
id|data
(braket
l_int|14
)braket
comma
id|data
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail2
suffix:semicolon
)brace
id|gameport_set_poll_handler
c_func
(paren
id|gameport
comma
id|guillemot_poll
)paren
suffix:semicolon
id|gameport_set_poll_interval
c_func
(paren
id|gameport
comma
l_int|20
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|guillemot-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|gameport-&gt;phys
)paren
suffix:semicolon
id|guillemot-&gt;type
op_assign
id|guillemot_type
op_plus
id|i
suffix:semicolon
id|guillemot-&gt;dev
dot
r_private
op_assign
id|guillemot
suffix:semicolon
id|guillemot-&gt;dev.open
op_assign
id|guillemot_open
suffix:semicolon
id|guillemot-&gt;dev.close
op_assign
id|guillemot_close
suffix:semicolon
id|guillemot-&gt;dev.name
op_assign
id|guillemot_type
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|guillemot-&gt;dev.phys
op_assign
id|guillemot-&gt;phys
suffix:semicolon
id|guillemot-&gt;dev.id.bustype
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|guillemot-&gt;dev.id.vendor
op_assign
id|GAMEPORT_ID_VENDOR_GUILLEMOT
suffix:semicolon
id|guillemot-&gt;dev.id.product
op_assign
id|guillemot_type
(braket
id|i
)braket
dot
id|id
suffix:semicolon
id|guillemot-&gt;dev.id.version
op_assign
(paren
r_int
)paren
id|data
(braket
l_int|14
)braket
op_lshift
l_int|8
op_or
id|data
(braket
l_int|15
)braket
suffix:semicolon
id|guillemot-&gt;dev.evbit
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
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|t
op_assign
id|guillemot-&gt;type-&gt;abs
(braket
id|i
)braket
)paren
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|input_set_abs_params
c_func
(paren
op_amp
id|guillemot-&gt;dev
comma
id|t
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
r_if
c_cond
(paren
id|guillemot-&gt;type-&gt;hat
)paren
(brace
id|input_set_abs_params
c_func
(paren
op_amp
id|guillemot-&gt;dev
comma
id|ABS_HAT0X
comma
op_minus
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|guillemot-&gt;dev
comma
id|ABS_HAT0Y
comma
op_minus
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
(paren
id|t
op_assign
id|guillemot-&gt;type-&gt;btn
(braket
id|i
)braket
)paren
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|t
comma
id|guillemot-&gt;dev.keybit
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|guillemot-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s ver %d.%02d on %s&bslash;n&quot;
comma
id|guillemot-&gt;type-&gt;name
comma
id|data
(braket
l_int|14
)braket
comma
id|data
(braket
l_int|15
)braket
comma
id|gameport-&gt;phys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail2
suffix:colon
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|fail1
suffix:colon
id|gameport_set_drvdata
c_func
(paren
id|gameport
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|guillemot
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|guillemot_disconnect
r_static
r_void
id|guillemot_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|guillemot
op_star
id|guillemot
op_assign
id|gameport_get_drvdata
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;guillemot.c: Failed %d reads out of %d on %s&bslash;n&quot;
comma
id|guillemot-&gt;reads
comma
id|guillemot-&gt;bads
comma
id|guillemot-&gt;phys
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|guillemot-&gt;dev
)paren
suffix:semicolon
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|guillemot
)paren
suffix:semicolon
)brace
DECL|variable|guillemot_drv
r_static
r_struct
id|gameport_driver
id|guillemot_drv
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;guillemot&quot;
comma
)brace
comma
dot
id|description
op_assign
id|DRIVER_DESC
comma
dot
id|connect
op_assign
id|guillemot_connect
comma
dot
id|disconnect
op_assign
id|guillemot_disconnect
comma
)brace
suffix:semicolon
DECL|function|guillemot_init
r_static
r_int
id|__init
id|guillemot_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_driver
c_func
(paren
op_amp
id|guillemot_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|guillemot_exit
r_static
r_void
id|__exit
id|guillemot_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_driver
c_func
(paren
op_amp
id|guillemot_drv
)paren
suffix:semicolon
)brace
DECL|variable|guillemot_init
id|module_init
c_func
(paren
id|guillemot_init
)paren
suffix:semicolon
DECL|variable|guillemot_exit
id|module_exit
c_func
(paren
id|guillemot_exit
)paren
suffix:semicolon
eof
