multiline_comment|/*********************************************************************&n; *                &n; * Filename:      litelink.c&n; * Version:       1.1&n; * Description:   Driver for the Parallax LiteLink dongle&n; * Status:        Stable&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri May  7 12:50:33 1999&n; * Modified at:   Fri Dec 17 09:14:23 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
DECL|macro|MIN_DELAY
mdefine_line|#define MIN_DELAY 25      /* 15 us, but wait a little more to be sure */
DECL|macro|MAX_DELAY
mdefine_line|#define MAX_DELAY 10000   /* 1 ms */
r_static
r_void
id|litelink_open
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
id|litelink_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
suffix:semicolon
r_static
r_int
id|litelink_change_speed
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
id|litelink_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
multiline_comment|/* These are the baudrates supported */
DECL|variable|baud_rates
r_static
id|__u32
id|baud_rates
(braket
)braket
op_assign
(brace
l_int|115200
comma
l_int|57600
comma
l_int|38400
comma
l_int|19200
comma
l_int|9600
)brace
suffix:semicolon
DECL|variable|dongle
r_static
r_struct
id|dongle_reg
id|dongle
op_assign
(brace
id|Q_NULL
comma
id|IRDA_LITELINK_DONGLE
comma
id|litelink_open
comma
id|litelink_close
comma
id|litelink_reset
comma
id|litelink_change_speed
comma
)brace
suffix:semicolon
DECL|function|litelink_init
r_int
id|__init
id|litelink_init
c_func
(paren
r_void
)paren
(brace
r_return
id|irda_device_register_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
DECL|function|litelink_cleanup
r_void
id|__exit
id|litelink_cleanup
c_func
(paren
r_void
)paren
(brace
id|irda_device_unregister_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
DECL|function|litelink_open
r_static
r_void
id|litelink_open
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
id|qos-&gt;min_turn_time.bits
op_assign
l_int|0x7f
suffix:semicolon
multiline_comment|/* Needs 0.01 ms */
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|litelink_close
r_static
r_void
id|litelink_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
(brace
multiline_comment|/* Power off dongle */
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Function litelink_change_speed (task)&n; *&n; *    Change speed of the Litelink dongle. To cycle through the available &n; *    baud rates, pulse RTS low for a few ms.  &n; */
DECL|function|litelink_change_speed
r_static
r_int
id|litelink_change_speed
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
r_int
id|i
suffix:semicolon
multiline_comment|/* Clear RTS to reset dongle */
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
multiline_comment|/* Sleep a minimum of 15 us */
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
multiline_comment|/* Sleep a minimum of 15 us */
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Cycle through avaiable baudrates until we reach the correct one */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|5
op_logical_and
id|baud_rates
(braket
id|i
)braket
op_ne
id|speed
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Set DTR, clear RTS */
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
multiline_comment|/* Sleep a minimum of 15 us */
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Set DTR, Set RTS */
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
multiline_comment|/* Sleep a minimum of 15 us */
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
)brace
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function litelink_reset (task)&n; *&n; *      Reset the Litelink type dongle.&n; *&n; */
DECL|function|litelink_reset
r_static
r_int
id|litelink_reset
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
multiline_comment|/* Power on dongle */
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
multiline_comment|/* Sleep a minimum of 15 us */
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* Clear RTS to reset dongle */
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
multiline_comment|/* Sleep a minimum of 15 us */
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
multiline_comment|/* Sleep a minimum of 15 us */
id|udelay
c_func
(paren
id|MIN_DELAY
)paren
suffix:semicolon
multiline_comment|/* This dongles speed defaults to 115200 bps */
id|self-&gt;speed
op_assign
l_int|115200
suffix:semicolon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Parallax Litelink dongle driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize Litelink module&n; *&n; */
DECL|variable|litelink_init
id|module_init
c_func
(paren
id|litelink_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup Litelink module&n; *&n; */
DECL|variable|litelink_cleanup
id|module_exit
c_func
(paren
id|litelink_cleanup
)paren
suffix:semicolon
eof
