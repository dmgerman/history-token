multiline_comment|/*&n; * $$&n; *&n; * Force feedback support for hid-compliant for some of the devices from&n; * Logitech, namely:&n; * - WingMan Cordless RumblePad&n; * - WingMan Force 3D&n; *&n; *  Copyright (c) 2002-2004 Johann Deneux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;johann.deneux@it.uu.se&gt;&n; */
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
singleline_comment|//#define DEBUG
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
macro_line|#include &quot;hid.h&quot;
macro_line|#include &quot;fixp-arith.h&quot;
multiline_comment|/* Periodicity of the update */
DECL|macro|PERIOD
mdefine_line|#define PERIOD (HZ/10)
DECL|macro|RUN_AT
mdefine_line|#define RUN_AT(t) (jiffies + (t))
multiline_comment|/* Effect status */
DECL|macro|EFFECT_STARTED
mdefine_line|#define EFFECT_STARTED 0     /* Effect is going to play after some time&n;&t;&t;&t;&t;(ff_replay.delay) */
DECL|macro|EFFECT_PLAYING
mdefine_line|#define EFFECT_PLAYING 1     /* Effect is being played */
DECL|macro|EFFECT_USED
mdefine_line|#define EFFECT_USED    2
singleline_comment|// For lgff_device::flags
DECL|macro|DEVICE_CLOSING
mdefine_line|#define DEVICE_CLOSING 0     /* The driver is being unitialised */
multiline_comment|/* Check that the current process can access an effect */
DECL|macro|CHECK_OWNERSHIP
mdefine_line|#define CHECK_OWNERSHIP(effect) (current-&gt;pid == 0 &bslash;&n;        || effect.owner == current-&gt;pid)
DECL|macro|LGFF_CHECK_OWNERSHIP
mdefine_line|#define LGFF_CHECK_OWNERSHIP(i, l) &bslash;&n;        (i&gt;=0 &amp;&amp; i&lt;LGFF_EFFECTS &bslash;&n;        &amp;&amp; test_bit(EFFECT_USED, l-&gt;effects[i].flags) &bslash;&n;        &amp;&amp; CHECK_OWNERSHIP(l-&gt;effects[i]))
DECL|macro|LGFF_EFFECTS
mdefine_line|#define LGFF_EFFECTS 8
DECL|struct|device_type
r_struct
id|device_type
(brace
DECL|member|idVendor
id|u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|u16
id|idProduct
suffix:semicolon
DECL|member|ff
r_int
r_int
op_star
id|ff
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lgff_effect
r_struct
id|lgff_effect
(brace
DECL|member|owner
id|pid_t
id|owner
suffix:semicolon
DECL|member|effect
r_struct
id|ff_effect
id|effect
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* Number of times left to play */
DECL|member|started_at
r_int
r_int
id|started_at
suffix:semicolon
multiline_comment|/* When the effect started to play */
)brace
suffix:semicolon
DECL|struct|lgff_device
r_struct
id|lgff_device
(brace
DECL|member|hid
r_struct
id|hid_device
op_star
id|hid
suffix:semicolon
DECL|member|constant
r_struct
id|hid_report
op_star
id|constant
suffix:semicolon
DECL|member|rumble
r_struct
id|hid_report
op_star
id|rumble
suffix:semicolon
DECL|member|condition
r_struct
id|hid_report
op_star
id|condition
suffix:semicolon
DECL|member|effects
r_struct
id|lgff_effect
id|effects
(braket
id|LGFF_EFFECTS
)braket
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* device-level lock. Having locks on&n;&t;&t;&t;&t;&t;a per-effect basis could be nice, but&n;&t;&t;&t;&t;&t;isn&squot;t really necessary */
DECL|member|flags
r_int
r_int
id|flags
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Contains various information about the&n;&t;&t;&t;&t;        state of the driver for this device */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Callbacks */
r_static
r_void
id|hid_lgff_exit
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
r_static
r_int
id|hid_lgff_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|input_dev
op_star
id|input
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
suffix:semicolon
r_static
r_int
id|hid_lgff_flush
c_func
(paren
r_struct
id|input_dev
op_star
id|input
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|hid_lgff_upload_effect
c_func
(paren
r_struct
id|input_dev
op_star
id|input
comma
r_struct
id|ff_effect
op_star
id|effect
)paren
suffix:semicolon
r_static
r_int
id|hid_lgff_erase
c_func
(paren
r_struct
id|input_dev
op_star
id|input
comma
r_int
id|id
)paren
suffix:semicolon
multiline_comment|/* Local functions */
r_static
r_void
id|hid_lgff_input_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
suffix:semicolon
r_static
r_void
id|hid_lgff_timer
c_func
(paren
r_int
r_int
id|timer_data
)paren
suffix:semicolon
r_static
r_struct
id|hid_report
op_star
id|hid_lgff_duplicate_report
c_func
(paren
r_struct
id|hid_report
op_star
)paren
suffix:semicolon
r_static
r_void
id|hid_lgff_delete_report
c_func
(paren
r_struct
id|hid_report
op_star
)paren
suffix:semicolon
DECL|variable|ff_rumble
r_static
r_int
r_int
id|ff_rumble
(braket
)braket
op_assign
(brace
id|FF_RUMBLE
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|ff_joystick
r_static
r_int
r_int
id|ff_joystick
(braket
)braket
op_assign
(brace
id|FF_CONSTANT
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|devices
r_static
r_struct
id|device_type
id|devices
(braket
)braket
op_assign
(brace
(brace
l_int|0x046d
comma
l_int|0xc211
comma
id|ff_rumble
)brace
comma
(brace
l_int|0x046d
comma
l_int|0xc219
comma
id|ff_rumble
)brace
comma
(brace
l_int|0x046d
comma
l_int|0xc283
comma
id|ff_joystick
)brace
comma
(brace
l_int|0x0000
comma
l_int|0x0000
comma
id|ff_joystick
)brace
)brace
suffix:semicolon
DECL|function|hid_lgff_init
r_int
id|hid_lgff_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|lgff_device
op_star
r_private
suffix:semicolon
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
r_struct
id|hid_field
op_star
id|field
suffix:semicolon
multiline_comment|/* Find the report to use */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|hid-&gt;report_enum
(braket
id|HID_OUTPUT_REPORT
)braket
dot
id|report_list
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;No output report found&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Check that the report looks ok */
id|report
op_assign
(paren
r_struct
id|hid_report
op_star
)paren
id|hid-&gt;report_enum
(braket
id|HID_OUTPUT_REPORT
)braket
dot
id|report_list.next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|report
)paren
(brace
id|err
c_func
(paren
l_string|&quot;NULL output report&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|field
op_assign
id|report-&gt;field
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|field
)paren
(brace
id|err
c_func
(paren
l_string|&quot;NULL field&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_private
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|lgff_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_private
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memset
c_func
(paren
r_private
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|lgff_device
)paren
)paren
suffix:semicolon
id|hid-&gt;ff_private
op_assign
r_private
suffix:semicolon
multiline_comment|/* Input init */
id|hid_lgff_input_init
c_func
(paren
id|hid
)paren
suffix:semicolon
r_private
op_member_access_from_pointer
id|constant
op_assign
id|hid_lgff_duplicate_report
c_func
(paren
id|report
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_private
op_member_access_from_pointer
id|constant
)paren
(brace
id|kfree
c_func
(paren
r_private
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_private
op_member_access_from_pointer
id|constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|0
)braket
op_assign
l_int|0x51
suffix:semicolon
r_private
op_member_access_from_pointer
id|constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|1
)braket
op_assign
l_int|0x08
suffix:semicolon
r_private
op_member_access_from_pointer
id|constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|2
)braket
op_assign
l_int|0x7f
suffix:semicolon
r_private
op_member_access_from_pointer
id|constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|3
)braket
op_assign
l_int|0x7f
suffix:semicolon
r_private
op_member_access_from_pointer
id|rumble
op_assign
id|hid_lgff_duplicate_report
c_func
(paren
id|report
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_private
op_member_access_from_pointer
id|rumble
)paren
(brace
id|hid_lgff_delete_report
c_func
(paren
r_private
op_member_access_from_pointer
id|constant
)paren
suffix:semicolon
id|kfree
c_func
(paren
r_private
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_private
op_member_access_from_pointer
id|rumble-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|0
)braket
op_assign
l_int|0x42
suffix:semicolon
r_private
op_member_access_from_pointer
id|condition
op_assign
id|hid_lgff_duplicate_report
c_func
(paren
id|report
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_private
op_member_access_from_pointer
id|condition
)paren
(brace
id|hid_lgff_delete_report
c_func
(paren
r_private
op_member_access_from_pointer
id|rumble
)paren
suffix:semicolon
id|hid_lgff_delete_report
c_func
(paren
r_private
op_member_access_from_pointer
id|constant
)paren
suffix:semicolon
id|kfree
c_func
(paren
r_private
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_private
op_member_access_from_pointer
id|hid
op_assign
id|hid
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|timer
)paren
suffix:semicolon
r_private
op_member_access_from_pointer
id|timer.data
op_assign
(paren
r_int
r_int
)paren
r_private
suffix:semicolon
r_private
op_member_access_from_pointer
id|timer.function
op_assign
id|hid_lgff_timer
suffix:semicolon
multiline_comment|/* Event and exit callbacks */
id|hid-&gt;ff_exit
op_assign
id|hid_lgff_exit
suffix:semicolon
id|hid-&gt;ff_event
op_assign
id|hid_lgff_event
suffix:semicolon
multiline_comment|/* Start the update task */
r_private
op_member_access_from_pointer
id|timer.expires
op_assign
id|RUN_AT
c_func
(paren
id|PERIOD
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|timer
)paren
suffix:semicolon
multiline_comment|/*TODO: only run the timer when at least&n;&t;&t;&t;&t;       one effect is playing */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Force feedback for Logitech force feedback devices by Johann Deneux &lt;johann.deneux@it.uu.se&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hid_lgff_duplicate_report
r_static
r_struct
id|hid_report
op_star
id|hid_lgff_duplicate_report
c_func
(paren
r_struct
id|hid_report
op_star
id|report
)paren
(brace
r_struct
id|hid_report
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|lgff_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|ret
op_assign
op_star
id|report
suffix:semicolon
id|ret-&gt;field
(braket
l_int|0
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hid_field
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret-&gt;field
(braket
l_int|0
)braket
)paren
(brace
id|kfree
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|ret-&gt;field
(braket
l_int|0
)braket
op_assign
op_star
id|report-&gt;field
(braket
l_int|0
)braket
suffix:semicolon
id|ret-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|s32
(braket
l_int|8
)braket
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
)paren
(brace
id|kfree
c_func
(paren
id|ret-&gt;field
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ret-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
comma
l_int|0
comma
r_sizeof
(paren
id|s32
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hid_lgff_delete_report
r_static
r_void
id|hid_lgff_delete_report
c_func
(paren
r_struct
id|hid_report
op_star
id|report
)paren
(brace
r_if
c_cond
(paren
id|report
)paren
(brace
id|kfree
c_func
(paren
id|report-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|report-&gt;field
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|report
)paren
suffix:semicolon
)brace
)brace
DECL|function|hid_lgff_input_init
r_static
r_void
id|hid_lgff_input_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|device_type
op_star
id|dev
op_assign
id|devices
suffix:semicolon
r_int
r_int
op_star
id|ff
suffix:semicolon
id|u16
id|idVendor
op_assign
id|le16_to_cpu
c_func
(paren
id|hid-&gt;dev-&gt;descriptor.idVendor
)paren
suffix:semicolon
id|u16
id|idProduct
op_assign
id|le16_to_cpu
c_func
(paren
id|hid-&gt;dev-&gt;descriptor.idProduct
)paren
suffix:semicolon
r_struct
id|hid_input
op_star
id|hidinput
op_assign
id|list_entry
c_func
(paren
id|hid-&gt;inputs.next
comma
r_struct
id|hid_input
comma
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;idVendor
op_logical_and
(paren
id|idVendor
op_ne
id|dev-&gt;idVendor
op_logical_or
id|idProduct
op_ne
id|dev-&gt;idProduct
)paren
)paren
id|dev
op_increment
suffix:semicolon
id|ff
op_assign
id|dev-&gt;ff
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ff
op_ge
l_int|0
)paren
(brace
id|set_bit
c_func
(paren
op_star
id|ff
comma
id|hidinput-&gt;input.ffbit
)paren
suffix:semicolon
op_increment
id|ff
suffix:semicolon
)brace
id|hidinput-&gt;input.upload_effect
op_assign
id|hid_lgff_upload_effect
suffix:semicolon
id|hidinput-&gt;input.flush
op_assign
id|hid_lgff_flush
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_FF
comma
id|hidinput-&gt;input.evbit
)paren
suffix:semicolon
id|hidinput-&gt;input.ff_effects_max
op_assign
id|LGFF_EFFECTS
suffix:semicolon
)brace
DECL|function|hid_lgff_exit
r_static
r_void
id|hid_lgff_exit
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|lgff_device
op_star
id|lgff
op_assign
id|hid-&gt;ff_private
suffix:semicolon
id|set_bit
c_func
(paren
id|DEVICE_CLOSING
comma
id|lgff-&gt;flags
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|lgff-&gt;timer
)paren
suffix:semicolon
id|hid_lgff_delete_report
c_func
(paren
id|lgff-&gt;condition
)paren
suffix:semicolon
id|hid_lgff_delete_report
c_func
(paren
id|lgff-&gt;rumble
)paren
suffix:semicolon
id|hid_lgff_delete_report
c_func
(paren
id|lgff-&gt;constant
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lgff
)paren
suffix:semicolon
)brace
DECL|function|hid_lgff_event
r_static
r_int
id|hid_lgff_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|input_dev
op_star
id|input
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
id|lgff_device
op_star
id|lgff
op_assign
id|hid-&gt;ff_private
suffix:semicolon
r_struct
id|lgff_effect
op_star
id|effect
op_assign
id|lgff-&gt;effects
op_plus
id|code
suffix:semicolon
r_int
r_int
id|flags
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
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LGFF_CHECK_OWNERSHIP
c_func
(paren
id|code
comma
id|lgff
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|value
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|effect-&gt;flags
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|effect-&gt;flags
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|effect-&gt;count
op_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|effect-&gt;effect.replay.delay
)paren
(brace
id|set_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
id|effect-&gt;started_at
op_assign
id|jiffies
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* value == 0 */
id|clear_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|effect-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Erase all effects this process owns */
DECL|function|hid_lgff_flush
r_static
r_int
id|hid_lgff_flush
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
id|hid_device
op_star
id|hid
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|lgff_device
op_star
id|lgff
op_assign
id|hid-&gt;ff_private
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
id|dev-&gt;ff_effects_max
suffix:semicolon
op_increment
id|i
)paren
(brace
multiline_comment|/*NOTE: no need to lock here. The only times EFFECT_USED is&n;&t;&t;  modified is when effects are uploaded or when an effect is&n;&t;&t;  erased. But a process cannot close its dev/input/eventX fd&n;&t;&t;  and perform ioctls on the same fd all at the same time */
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|owner
op_logical_and
id|test_bit
c_func
(paren
id|EFFECT_USED
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
)paren
(brace
r_if
c_cond
(paren
id|hid_lgff_erase
c_func
(paren
id|dev
comma
id|i
)paren
)paren
id|warn
c_func
(paren
l_string|&quot;erase effect %d failed&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hid_lgff_erase
r_static
r_int
id|hid_lgff_erase
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
id|id
)paren
(brace
r_struct
id|hid_device
op_star
id|hid
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|lgff_device
op_star
id|lgff
op_assign
id|hid-&gt;ff_private
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LGFF_CHECK_OWNERSHIP
c_func
(paren
id|id
comma
id|lgff
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|lgff-&gt;effects
(braket
id|id
)braket
dot
id|flags
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hid_lgff_upload_effect
r_static
r_int
id|hid_lgff_upload_effect
c_func
(paren
r_struct
id|input_dev
op_star
id|input
comma
r_struct
id|ff_effect
op_star
id|effect
)paren
(brace
r_struct
id|hid_device
op_star
id|hid
op_assign
id|input
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|lgff_device
op_star
id|lgff
op_assign
id|hid-&gt;ff_private
suffix:semicolon
r_struct
id|lgff_effect
r_new
suffix:semicolon
r_int
id|id
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;ioctl rumble&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|effect-&gt;type
comma
id|input-&gt;ffbit
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|effect-&gt;id
op_eq
op_minus
l_int|1
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
id|LGFF_EFFECTS
op_logical_and
id|test_bit
c_func
(paren
id|EFFECT_USED
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
op_increment
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|LGFF_EFFECTS
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|effect-&gt;id
op_assign
id|i
suffix:semicolon
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|owner
op_assign
id|current-&gt;pid
suffix:semicolon
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|EFFECT_USED
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|LGFF_CHECK_OWNERSHIP
c_func
(paren
id|effect-&gt;id
comma
id|lgff
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|id
op_assign
id|effect-&gt;id
suffix:semicolon
r_new
op_assign
id|lgff-&gt;effects
(braket
id|id
)braket
suffix:semicolon
r_new
dot
id|effect
op_assign
op_star
id|effect
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|lgff-&gt;effects
(braket
id|id
)braket
dot
id|flags
)paren
op_logical_or
id|test_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|lgff-&gt;effects
(braket
id|id
)braket
dot
id|flags
)paren
)paren
(brace
multiline_comment|/* Changing replay parameters is not allowed (for the time&n;&t;&t;   being) */
r_if
c_cond
(paren
r_new
dot
id|effect.replay.delay
op_ne
id|lgff-&gt;effects
(braket
id|id
)braket
dot
id|effect.replay.delay
op_logical_or
r_new
dot
id|effect.replay.length
op_ne
id|lgff-&gt;effects
(braket
id|id
)braket
dot
id|effect.replay.length
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
id|lgff-&gt;effects
(braket
id|id
)braket
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
id|lgff-&gt;effects
(braket
id|id
)braket
op_assign
r_new
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hid_lgff_timer
r_static
r_void
id|hid_lgff_timer
c_func
(paren
r_int
r_int
id|timer_data
)paren
(brace
r_struct
id|lgff_device
op_star
id|lgff
op_assign
(paren
r_struct
id|lgff_device
op_star
)paren
id|timer_data
suffix:semicolon
r_struct
id|hid_device
op_star
id|hid
op_assign
id|lgff-&gt;hid
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|x
op_assign
l_int|0x7f
comma
id|y
op_assign
l_int|0x7f
suffix:semicolon
singleline_comment|// Coordinates of constant effects
r_int
r_int
id|left
op_assign
l_int|0
comma
id|right
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Rumbling
r_int
id|i
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
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
id|LGFF_EFFECTS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|lgff_effect
op_star
id|effect
op_assign
id|lgff-&gt;effects
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|effect-&gt;flags
)paren
)paren
(brace
r_switch
c_cond
(paren
id|effect-&gt;effect.type
)paren
(brace
r_case
id|FF_CONSTANT
suffix:colon
(brace
singleline_comment|//TODO: handle envelopes
r_int
id|degrees
op_assign
id|effect-&gt;effect.direction
op_star
l_int|360
op_rshift
l_int|16
suffix:semicolon
id|x
op_add_assign
id|fixp_mult
c_func
(paren
id|fixp_sin
c_func
(paren
id|degrees
)paren
comma
id|fixp_new16
c_func
(paren
id|effect-&gt;effect.u.constant.level
)paren
)paren
suffix:semicolon
id|y
op_add_assign
id|fixp_mult
c_func
(paren
op_minus
id|fixp_cos
c_func
(paren
id|degrees
)paren
comma
id|fixp_new16
c_func
(paren
id|effect-&gt;effect.u.constant.level
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|FF_RUMBLE
suffix:colon
id|right
op_add_assign
id|effect-&gt;effect.u.rumble.strong_magnitude
suffix:semicolon
id|left
op_add_assign
id|effect-&gt;effect.u.rumble.weak_magnitude
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* One run of the effect is finished playing */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|effect-&gt;started_at
op_plus
id|effect-&gt;effect.replay.delay
op_star
id|HZ
op_div
l_int|1000
op_plus
id|effect-&gt;effect.replay.length
op_star
id|HZ
op_div
l_int|1000
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;Finished playing once %d&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|effect-&gt;count
op_le
l_int|0
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;Stopped %d&quot;
comma
id|i
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|dbg
c_func
(paren
l_string|&quot;Start again %d&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|effect-&gt;effect.replay.length
op_ne
l_int|0
)paren
(brace
id|clear_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|effect-&gt;flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
id|effect-&gt;started_at
op_assign
id|jiffies
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
)paren
(brace
multiline_comment|/* Check if we should start playing the effect */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|started_at
op_plus
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|effect.replay.delay
op_star
id|HZ
op_div
l_int|1000
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;Now playing %d&quot;
comma
id|i
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|EFFECT_STARTED
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|EFFECT_PLAYING
comma
id|lgff-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|macro|CLAMP
mdefine_line|#define CLAMP(x) if (x &lt; 0) x = 0; if (x &gt; 0xff) x = 0xff
singleline_comment|// Clamp values
id|CLAMP
c_func
(paren
id|x
)paren
suffix:semicolon
id|CLAMP
c_func
(paren
id|y
)paren
suffix:semicolon
id|CLAMP
c_func
(paren
id|left
)paren
suffix:semicolon
id|CLAMP
c_func
(paren
id|right
)paren
suffix:semicolon
DECL|macro|CLAMP
macro_line|#undef CLAMP
r_if
c_cond
(paren
id|x
op_ne
id|lgff-&gt;constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|2
)braket
op_logical_or
id|y
op_ne
id|lgff-&gt;constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|3
)braket
)paren
(brace
id|lgff-&gt;constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|2
)braket
op_assign
id|x
suffix:semicolon
id|lgff-&gt;constant-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|3
)braket
op_assign
id|y
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;(x,y)=(%04x, %04x)&quot;
comma
id|x
comma
id|y
)paren
suffix:semicolon
id|hid_submit_report
c_func
(paren
id|hid
comma
id|lgff-&gt;constant
comma
id|USB_DIR_OUT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|left
op_ne
id|lgff-&gt;rumble-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|2
)braket
op_logical_or
id|right
op_ne
id|lgff-&gt;rumble-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|3
)braket
)paren
(brace
id|lgff-&gt;rumble-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|2
)braket
op_assign
id|left
suffix:semicolon
id|lgff-&gt;rumble-&gt;field
(braket
l_int|0
)braket
op_member_access_from_pointer
id|value
(braket
l_int|3
)braket
op_assign
id|right
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;(left,right)=(%04x, %04x)&quot;
comma
id|left
comma
id|right
)paren
suffix:semicolon
id|hid_submit_report
c_func
(paren
id|hid
comma
id|lgff-&gt;rumble
comma
id|USB_DIR_OUT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|DEVICE_CLOSING
comma
id|lgff-&gt;flags
)paren
)paren
(brace
id|lgff-&gt;timer.expires
op_assign
id|RUN_AT
c_func
(paren
id|PERIOD
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|lgff-&gt;timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lgff-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
eof
