multiline_comment|/*&n; *  PID Force feedback support for hid devices.&n; *&n; *  Copyright (c) 2002 Rodrigo Damazio.&n; *  Portions by Johann Deneux and Bjorn Augustson&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;rdamazio@lsi.usp.br&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;hid.h&quot;
macro_line|#include &quot;pid.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
DECL|macro|CHECK_OWNERSHIP
mdefine_line|#define CHECK_OWNERSHIP(i, hid_pid)&t;&bslash;&n;&t;((i) &lt; FF_EFFECTS_MAX &amp;&amp; i &gt;= 0 &amp;&amp; &bslash;&n;&t;test_bit(FF_PID_FLAGS_USED, &amp;hid_pid-&gt;effects[(i)].flags) &amp;&amp; &bslash;&n;&t;(current-&gt;pid == 0 || &bslash;&n;&t;(hid_pid)-&gt;effects[(i)].owner == current-&gt;pid))
multiline_comment|/* Called when a transfer is completed */
DECL|function|hid_pid_ctrl_out
r_static
r_void
id|hid_pid_ctrl_out
c_func
(paren
r_struct
id|urb
op_star
id|u
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hid_pid_ctrl_out - Transfer Completed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|hid_pid_exit
r_static
r_void
id|hid_pid_exit
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|hid_ff_pid
op_star
r_private
op_assign
id|hid-&gt;ff_private
suffix:semicolon
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|urbffout
)paren
(brace
id|usb_unlink_urb
c_func
(paren
r_private
op_member_access_from_pointer
id|urbffout
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
r_private
op_member_access_from_pointer
id|urbffout
)paren
suffix:semicolon
)brace
)brace
DECL|function|pid_upload_periodic
r_static
r_int
id|pid_upload_periodic
c_func
(paren
r_struct
id|hid_ff_pid
op_star
id|pid
comma
r_struct
id|ff_effect
op_star
id|effect
comma
r_int
id|is_update
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Requested periodic force upload&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pid_upload_constant
r_static
r_int
id|pid_upload_constant
c_func
(paren
r_struct
id|hid_ff_pid
op_star
id|pid
comma
r_struct
id|ff_effect
op_star
id|effect
comma
r_int
id|is_update
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Requested constant force upload&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pid_upload_condition
r_static
r_int
id|pid_upload_condition
c_func
(paren
r_struct
id|hid_ff_pid
op_star
id|pid
comma
r_struct
id|ff_effect
op_star
id|effect
comma
r_int
id|is_update
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Requested Condition force upload&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pid_upload_ramp
r_static
r_int
id|pid_upload_ramp
c_func
(paren
r_struct
id|hid_ff_pid
op_star
id|pid
comma
r_struct
id|ff_effect
op_star
id|effect
comma
r_int
id|is_update
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Request ramp force upload&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hid_pid_event
r_static
r_int
id|hid_pid_event
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
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;PID event received: type=%d,code=%d,value=%d.&bslash;n&quot;
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
macro_line|#endif
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Lock must be held by caller */
DECL|function|hid_pid_ctrl_playback
r_static
r_void
id|hid_pid_ctrl_playback
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|hid_pid_effect
op_star
id|effect
comma
r_int
id|play
)paren
(brace
r_if
c_cond
(paren
id|play
)paren
(brace
id|set_bit
c_func
(paren
id|FF_PID_FLAGS_PLAYING
comma
op_amp
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_bit
c_func
(paren
id|FF_PID_FLAGS_PLAYING
comma
op_amp
id|effect-&gt;flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|hid_pid_erase
r_static
r_int
id|hid_pid_erase
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
id|hid_field
op_star
id|field
suffix:semicolon
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
r_struct
id|hid_ff_pid
op_star
id|pid
op_assign
id|hid-&gt;ff_private
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|wanted_report
op_assign
id|HID_UP_PID
op_or
id|FF_PID_USAGE_BLOCK_FREE
suffix:semicolon
multiline_comment|/*  PID Block Free Report */
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CHECK_OWNERSHIP
c_func
(paren
id|id
comma
id|pid
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* Find report */
id|ret
op_assign
id|hid_find_report_by_usage
c_func
(paren
id|hid
comma
id|wanted_report
comma
op_amp
id|report
comma
id|HID_OUTPUT_REPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t find report&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Find field */
id|field
op_assign
(paren
r_struct
id|hid_field
op_star
)paren
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
id|ret
op_assign
id|hid_set_field
c_func
(paren
id|field
comma
id|ret
comma
id|pid-&gt;effects
(braket
id|id
)braket
dot
id|device_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t set field&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|hid_submit_report
c_func
(paren
id|hid
comma
id|report
comma
id|USB_DIR_OUT
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pid-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|hid_pid_ctrl_playback
c_func
(paren
id|hid
comma
id|pid-&gt;effects
op_plus
id|id
comma
l_int|0
)paren
suffix:semicolon
id|pid-&gt;effects
(braket
id|id
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pid-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Erase all effects this process owns */
DECL|function|hid_pid_flush
r_static
r_int
id|hid_pid_flush
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
id|hid_ff_pid
op_star
id|pid
op_assign
id|hid-&gt;ff_private
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*NOTE: no need to lock here. The only times EFFECT_USED is&n;&t;  modified is when effects are uploaded or when an effect is&n;&t;  erased. But a process cannot close its dev/input/eventX fd&n;&t;  and perform ioctls on the same fd all at the same time */
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
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
id|pid-&gt;effects
(braket
id|i
)braket
dot
id|owner
op_logical_and
id|test_bit
c_func
(paren
id|FF_PID_FLAGS_USED
comma
op_amp
id|pid-&gt;effects
(braket
id|i
)braket
dot
id|flags
)paren
)paren
r_if
c_cond
(paren
id|hid_pid_erase
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hid_pid_upload_effect
r_static
r_int
id|hid_pid_upload_effect
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
id|hid_ff_pid
op_star
id|pid_private
op_assign
(paren
r_struct
id|hid_ff_pid
op_star
)paren
(paren
id|dev
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|is_update
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Upload effect called: effect_type=%x&bslash;n&quot;
comma
id|effect-&gt;type
)paren
suffix:semicolon
macro_line|#endif
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
id|dev-&gt;ffbit
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Invalid kind of effect requested.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we want to create a new effect, get a free id&n;&t; */
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
id|id
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Spinlock so we don`t get a race condition when choosing IDs
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pid_private-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|id
OL
id|FF_EFFECTS_MAX
)paren
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|FF_PID_FLAGS_USED
comma
op_amp
id|pid_private-&gt;effects
(braket
id|id
op_increment
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
)paren
(brace
singleline_comment|// TEMP - We need to get ff_effects_max correctly first:  || id &gt;= dev-&gt;ff_effects_max) {
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Not enough device memory&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|effect-&gt;id
op_assign
id|id
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Effect ID is %d&bslash;n.&quot;
comma
id|id
)paren
suffix:semicolon
macro_line|#endif
id|pid_private-&gt;effects
(braket
id|id
)braket
dot
id|owner
op_assign
id|current-&gt;pid
suffix:semicolon
id|pid_private-&gt;effects
(braket
id|id
)braket
dot
id|flags
op_assign
(paren
l_int|1
op_lshift
id|FF_PID_FLAGS_USED
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pid_private-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|is_update
op_assign
id|FF_PID_FALSE
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
id|pid_private
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
id|pid_private-&gt;effects
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
id|FF_PID_FLAGS_UPDATING
comma
op_amp
id|pid_private-&gt;effects
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
id|FF_PID_TRUE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Upload the effect&n;&t; */
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
id|pid_upload_periodic
c_func
(paren
id|pid_private
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
id|pid_upload_constant
c_func
(paren
id|pid_private
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
id|FF_FRICTION
suffix:colon
r_case
id|FF_DAMPER
suffix:colon
r_case
id|FF_INERTIA
suffix:colon
id|ret
op_assign
id|pid_upload_condition
c_func
(paren
id|pid_private
comma
id|effect
comma
id|is_update
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FF_RAMP
suffix:colon
id|ret
op_assign
id|pid_upload_ramp
c_func
(paren
id|pid_private
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
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Invalid type of effect requested - %x.&bslash;n&quot;
comma
id|effect-&gt;type
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* If a packet was sent, forbid new updates until we are notified&n;&t; * that the packet was updated&n;&t; */
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|set_bit
c_func
(paren
id|FF_PID_FLAGS_UPDATING
comma
op_amp
id|pid_private-&gt;effects
(braket
id|effect-&gt;id
)braket
dot
id|flags
)paren
suffix:semicolon
id|pid_private-&gt;effects
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
DECL|function|hid_pid_init
r_int
id|hid_pid_init
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|hid_ff_pid
op_star
r_private
suffix:semicolon
r_private
op_assign
id|hid-&gt;ff_private
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hid_ff_pid
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
id|hid_ff_pid
)paren
)paren
suffix:semicolon
id|hid-&gt;ff_private
op_assign
r_private
suffix:semicolon
multiline_comment|/* &squot;cause memset can move the block away */
r_private
op_member_access_from_pointer
id|hid
op_assign
id|hid
suffix:semicolon
id|hid-&gt;ff_exit
op_assign
id|hid_pid_exit
suffix:semicolon
id|hid-&gt;ff_event
op_assign
id|hid_pid_event
suffix:semicolon
multiline_comment|/* Open output URB */
r_if
c_cond
(paren
op_logical_neg
(paren
r_private
op_member_access_from_pointer
id|urbffout
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
)paren
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
id|usb_fill_control_urb
c_func
(paren
r_private
op_member_access_from_pointer
id|urbffout
comma
id|hid-&gt;dev
comma
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
r_private
op_member_access_from_pointer
id|ffcr
comma
r_private
op_member_access_from_pointer
id|ctrl_buffer
comma
l_int|8
comma
id|hid_pid_ctrl_out
comma
id|hid
)paren
suffix:semicolon
id|hid-&gt;input.upload_effect
op_assign
id|hid_pid_upload_effect
suffix:semicolon
id|hid-&gt;input.flush
op_assign
id|hid_pid_flush
suffix:semicolon
id|hid-&gt;input.ff_effects_max
op_assign
l_int|8
suffix:semicolon
singleline_comment|// A random default
id|set_bit
c_func
(paren
id|EV_FF
comma
id|hid-&gt;input.evbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_FF_STATUS
comma
id|hid-&gt;input.evbit
)paren
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Force feedback driver for PID devices by Rodrigo Damazio &lt;rdamazio@lsi.usp.br&gt;.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
