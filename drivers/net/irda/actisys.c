multiline_comment|/*********************************************************************&n; *                &n; * Filename:      actisys.c&n; * Version:       1.0&n; * Description:   Implementation for the ACTiSYS IR-220L and IR-220L+ &n; *                dongles&n; * Status:        Beta.&n; * Authors:       Dag Brattli &lt;dagb@cs.uit.no&gt; (initially)&n; *&t;&t;  Jean Tourrilhes &lt;jt@hpl.hp.com&gt; (new version)&n; * Created at:    Wed Oct 21 20:02:35 1998&n; * Modified at:   Fri Dec 17 09:10:43 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 1999 Jean Tourrilhes&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
multiline_comment|/*&n; * Changelog&n; *&n; * 0.8 -&gt; 0.9999 - Jean&n; *&t;o New initialisation procedure : much safer and correct&n; *&t;o New procedure the change speed : much faster and simpler&n; *&t;o Other cleanups &amp; comments&n; *&t;Thanks to Lichen Wang @ Actisys for his excellent help...&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
multiline_comment|/* &n; * Define the timing of the pulses we send to the dongle (to reset it, and&n; * to toggle speeds). Basically, the limit here is the propagation speed of&n; * the signals through the serial port, the dongle being much faster.  Any&n; * serial port support 115 kb/s, so we are sure that pulses 8.5 us wide can&n; * go through cleanly . If you are on the wild side, you can try to lower&n; * this value (Actisys recommended me 2 us, and 0 us work for me on a P233!)&n; */
DECL|macro|MIN_DELAY
mdefine_line|#define MIN_DELAY 10&t;/* 10 us to be on the conservative side */
r_static
r_int
id|actisys_change_speed
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
r_static
r_int
id|actisys_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
r_static
r_void
id|actisys_open
c_func
(paren
id|dongle_t
op_star
id|self
comma
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
r_static
r_void
id|actisys_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
suffix:semicolon
multiline_comment|/* These are the baudrates supported, in the order available */
multiline_comment|/* Note : the 220L doesn&squot;t support 38400, but we will fix that below */
DECL|variable|baud_rates
r_static
id|__u32
id|baud_rates
(braket
)braket
op_assign
(brace
l_int|9600
comma
l_int|19200
comma
l_int|57600
comma
l_int|115200
comma
l_int|38400
)brace
suffix:semicolon
DECL|macro|MAX_SPEEDS
mdefine_line|#define MAX_SPEEDS 5
DECL|variable|dongle
r_static
r_struct
id|dongle_reg
id|dongle
op_assign
(brace
dot
id|type
op_assign
id|IRDA_ACTISYS_DONGLE
comma
dot
id|open
op_assign
id|actisys_open
comma
dot
id|close
op_assign
id|actisys_close
comma
dot
id|reset
op_assign
id|actisys_reset
comma
dot
id|change_speed
op_assign
id|actisys_change_speed
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|dongle_plus
r_static
r_struct
id|dongle_reg
id|dongle_plus
op_assign
(brace
dot
id|type
op_assign
id|IRDA_ACTISYS_PLUS_DONGLE
comma
dot
id|open
op_assign
id|actisys_open
comma
dot
id|close
op_assign
id|actisys_close
comma
dot
id|reset
op_assign
id|actisys_reset
comma
dot
id|change_speed
op_assign
id|actisys_change_speed
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Function actisys_change_speed (task)&n; *&n; *&t;There is two model of Actisys dongle we are dealing with,&n; * the 220L and 220L+. At this point, only irattach knows with&n; * kind the user has requested (it was an argument on irattach&n; * command line).&n; *&t;So, we register a dongle of each sort and let irattach&n; * pick the right one...&n; */
DECL|function|actisys_init
r_static
r_int
id|__init
id|actisys_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* First, register an Actisys 220L dongle */
id|ret
op_assign
id|irda_device_register_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* Now, register an Actisys 220L+ dongle */
id|ret
op_assign
id|irda_device_register_dongle
c_func
(paren
op_amp
id|dongle_plus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|irda_device_unregister_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|actisys_cleanup
r_static
r_void
id|__exit
id|actisys_cleanup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We have to remove both dongles */
id|irda_device_unregister_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
id|irda_device_unregister_dongle
c_func
(paren
op_amp
id|dongle_plus
)paren
suffix:semicolon
)brace
DECL|function|actisys_open
r_static
r_void
id|actisys_open
c_func
(paren
id|dongle_t
op_star
id|self
comma
r_struct
id|qos_info
op_star
id|qos
)paren
(brace
multiline_comment|/* Power on the dongle */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
multiline_comment|/* Set the speeds we can accept */
id|qos-&gt;baud_rate.bits
op_and_assign
id|IR_9600
op_or
id|IR_19200
op_or
id|IR_38400
op_or
id|IR_57600
op_or
id|IR_115200
suffix:semicolon
multiline_comment|/* Remove support for 38400 if this is not a 220L+ dongle */
r_if
c_cond
(paren
id|self-&gt;issue-&gt;type
op_eq
id|IRDA_ACTISYS_DONGLE
)paren
id|qos-&gt;baud_rate.bits
op_and_assign
op_complement
id|IR_38400
suffix:semicolon
id|qos-&gt;min_turn_time.bits
op_assign
l_int|0x7f
suffix:semicolon
multiline_comment|/* Needs 0.01 ms */
)brace
DECL|function|actisys_close
r_static
r_void
id|actisys_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
(brace
multiline_comment|/* Power off the dongle */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|FALSE
comma
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function actisys_change_speed (task)&n; *&n; *    Change speed of the ACTiSYS IR-220L and IR-220L+ type IrDA dongles.&n; *    To cycle through the available baud rates, pulse RTS low for a few us.&n; *&n; *&t;First, we reset the dongle to always start from a known state.&n; *&t;Then, we cycle through the speeds by pulsing RTS low and then up.&n; *&t;The dongle allow us to pulse quite fast, se we can set speed in one go,&n; * which is must faster ( &lt; 100 us) and less complex than what is found&n; * in some other dongle drivers...&n; *&t;Note that even if the new speed is the same as the current speed,&n; * we reassert the speed. This make sure that things are all right,&n; * and it&squot;s fast anyway...&n; *&t;By the way, this function will work for both type of dongles,&n; * because the additional speed is at the end of the sequence...&n; */
DECL|function|actisys_change_speed
r_static
r_int
id|actisys_change_speed
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
id|dongle_t
op_star
id|self
op_assign
(paren
id|dongle_t
op_star
)paren
id|task-&gt;instance
suffix:semicolon
id|__u32
id|speed
op_assign
(paren
id|__u32
)paren
id|task-&gt;param
suffix:semicolon
multiline_comment|/* Target speed */
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), speed=%d (was %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|speed
comma
id|self-&gt;speed
)paren
suffix:semicolon
multiline_comment|/* Go to a known state by reseting the dongle */
multiline_comment|/* Reset the dongle : set DTR low for 10 us */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|FALSE
comma
id|TRUE
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Go back to normal mode (we are now at 9600 b/s) */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Now, we can set the speed requested. Send RTS pulses until we&n;         * reach the target speed &n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_SPEEDS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|speed
op_eq
id|baud_rates
(braket
id|i
)braket
)paren
(brace
id|self-&gt;speed
op_assign
id|baud_rates
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Make sure previous pulse is finished */
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Set RTS low for 10 us */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|TRUE
comma
id|FALSE
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Set RTS high for 10 us */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if life is sweet... */
r_if
c_cond
(paren
id|i
op_ge
id|MAX_SPEEDS
)paren
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* This should not happen */
multiline_comment|/* Basta lavoro, on se casse d&squot;ici... */
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function actisys_reset (task)&n; *&n; *      Reset the Actisys type dongle. Warning, this function must only be&n; *      called with a process context!&n; *&n; * We need to do two things in this function :&n; *&t;o first make sure that the dongle is in a state where it can operate&n; *&t;o second put the dongle in a know state&n; *&n; *&t;The dongle is powered of the RTS and DTR lines. In the dongle, there&n; * is a big capacitor to accommodate the current spikes. This capacitor&n; * takes a least 50 ms to be charged. In theory, the Bios set those lines&n; * up, so by the time we arrive here we should be set. It doesn&squot;t hurt&n; * to be on the conservative side, so we will wait...&n; *&t;Then, we set the speed to 9600 b/s to get in a known state (see in&n; * change_speed for details). It is needed because the IrDA stack&n; * has tried to set the speed immediately after our first return,&n; * so before we can be sure the dongle is up and running.&n; */
DECL|function|actisys_reset
r_static
r_int
id|actisys_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
id|dongle_t
op_star
id|self
op_assign
(paren
id|dongle_t
op_star
)paren
id|task-&gt;instance
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ASSERT
c_func
(paren
id|task
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;reset_task
op_assign
id|task
suffix:semicolon
r_switch
c_cond
(paren
id|task-&gt;state
)paren
(brace
r_case
id|IRDA_TASK_INIT
suffix:colon
multiline_comment|/* Set both DTR &amp; RTS to power up the dongle */
multiline_comment|/* In theory redundant with power up in actisys_open() */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
multiline_comment|/* Sleep 50 ms to make sure capacitor is charged */
id|ret
op_assign
id|msecs_to_jiffies
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT
suffix:colon
multiline_comment|/* Reset the dongle : set DTR low for 10 us */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|FALSE
comma
id|TRUE
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Go back to normal mode */
id|self
op_member_access_from_pointer
id|set_dtr_rts
c_func
(paren
id|self-&gt;dev
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
id|self-&gt;reset_task
op_assign
l_int|NULL
suffix:semicolon
id|self-&gt;speed
op_assign
l_int|9600
suffix:semicolon
multiline_comment|/* That&squot;s the default */
r_break
suffix:semicolon
r_default
suffix:colon
id|ERROR
c_func
(paren
l_string|&quot;%s(), unknown state %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|task-&gt;state
)paren
suffix:semicolon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
id|self-&gt;reset_task
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt; - Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ACTiSYS IR-220L and IR-220L+ dongle driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;irda-dongle-2&quot;
)paren
suffix:semicolon
multiline_comment|/* IRDA_ACTISYS_DONGLE */
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;irda-dongle-3&quot;
)paren
suffix:semicolon
multiline_comment|/* IRDA_ACTISYS_PLUS_DONGLE */
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize Actisys module&n; *&n; */
DECL|variable|actisys_init
id|module_init
c_func
(paren
id|actisys_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup Actisys module&n; *&n; */
DECL|variable|actisys_cleanup
id|module_exit
c_func
(paren
id|actisys_cleanup
)paren
suffix:semicolon
eof
