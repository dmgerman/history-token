multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ma600.c&n; * Version:       0.1&n; * Description:   Implementation of the MA600 dongle&n; * Status:        Experimental.&n; * Author:        Leung &lt;95Etwl@alumni.ee.ust.hk&gt; http://www.engsvr.ust/~eetwl95&n; * Created at:    Sat Jun 10 20:02:35 2000&n; * Modified at:   &n; * Modified by:   &n; *&n; * Note: very thanks to Mr. Maru Wang &lt;maru@mobileaction.com.tw&gt; for providing &n; *       information on the MA600 dongle&n; * &n; *     Copyright (c) 2000 Leung, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
multiline_comment|/* define this macro for release version */
singleline_comment|//#define NDEBUG
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#ifndef NDEBUG
DECL|macro|IRDA_DEBUG
macro_line|#undef IRDA_DEBUG
DECL|macro|IRDA_DEBUG
mdefine_line|#define IRDA_DEBUG(n, args...) (printk(KERN_DEBUG args))
DECL|macro|ASSERT
macro_line|#undef ASSERT
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func) &bslash;&n;&t;if(!(expr)) { &bslash;&n;&t;        printk( &quot;Assertion failed! %s,%s,%s,line=%d&bslash;n&quot;,&bslash;&n;        &t;#expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;&t;        func}
macro_line|#endif
multiline_comment|/* convert hex value to ascii hex */
DECL|variable|hexTbl
r_static
r_const
r_char
id|hexTbl
(braket
)braket
op_assign
l_string|&quot;0123456789ABCDEF&quot;
suffix:semicolon
r_static
r_void
id|ma600_open
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
id|ma600_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
suffix:semicolon
r_static
r_int
id|ma600_change_speed
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
id|ma600_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
multiline_comment|/* control byte for MA600 */
DECL|macro|MA600_9600
mdefine_line|#define MA600_9600&t;0x00
DECL|macro|MA600_19200
mdefine_line|#define MA600_19200&t;0x01
DECL|macro|MA600_38400
mdefine_line|#define MA600_38400&t;0x02
DECL|macro|MA600_57600
mdefine_line|#define MA600_57600&t;0x03
DECL|macro|MA600_115200
mdefine_line|#define MA600_115200&t;0x04
DECL|macro|MA600_DEV_ID1
mdefine_line|#define MA600_DEV_ID1&t;0x05
DECL|macro|MA600_DEV_ID2
mdefine_line|#define MA600_DEV_ID2&t;0x06
DECL|macro|MA600_2400
mdefine_line|#define MA600_2400&t;0x08
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
id|IRDA_MA600_DONGLE
comma
dot
id|open
op_assign
id|ma600_open
comma
dot
id|close
op_assign
id|ma600_close
comma
dot
id|reset
op_assign
id|ma600_reset
comma
dot
id|change_speed
op_assign
id|ma600_change_speed
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|ma600_init
r_static
r_int
id|__init
id|ma600_init
c_func
(paren
r_void
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|irda_device_register_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
DECL|function|ma600_cleanup
r_static
r_void
id|__exit
id|ma600_cleanup
c_func
(paren
r_void
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|irda_device_unregister_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Power on:&n;&t;&t;(0) Clear RTS and DTR for 1 second&n;&t;&t;(1) Set RTS and DTR for 1 second&n;&t;&t;(2) 9600 bps now&n;&t;Note: assume RTS, DTR are clear before&n;*/
DECL|function|ma600_open
r_static
r_void
id|ma600_open
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
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|qos-&gt;baud_rate.bits
op_and_assign
id|IR_2400
op_or
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
l_int|0x01
suffix:semicolon
multiline_comment|/* Needs at least 1 ms */
id|irda_qos_bits_to_value
c_func
(paren
id|qos
)paren
suffix:semicolon
singleline_comment|//self-&gt;set_dtr_rts(self-&gt;dev, FALSE, FALSE);
singleline_comment|// should wait 1 second
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
singleline_comment|// should wait 1 second
)brace
DECL|function|ma600_close
r_static
r_void
id|ma600_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
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
)brace
DECL|function|get_control_byte
r_static
id|__u8
id|get_control_byte
c_func
(paren
id|__u32
id|speed
)paren
(brace
id|__u8
id|byte
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_default
suffix:colon
r_case
l_int|115200
suffix:colon
id|byte
op_assign
id|MA600_115200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|57600
suffix:colon
id|byte
op_assign
id|MA600_57600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38400
suffix:colon
id|byte
op_assign
id|MA600_38400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19200
suffix:colon
id|byte
op_assign
id|MA600_19200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9600
suffix:colon
id|byte
op_assign
id|MA600_9600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2400
suffix:colon
id|byte
op_assign
id|MA600_2400
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|byte
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ma600_change_speed (dev, state, speed)&n; *&n; *    Set the speed for the MA600 type dongle. Warning, this &n; *    function must be called with a process context!&n; *&n; *    Algorithm&n; *    1. Reset&n; *    2. clear RTS, set DTR and wait for 1ms&n; *    3. send Control Byte to the MA600 through TXD to set new baud rate&n; *       wait until the stop bit of Control Byte is sent (for 9600 baud rate, &n; *       it takes about 10 msec)&n; *    4. set RTS, set DTR (return to NORMAL Operation)&n; *    5. wait at least 10 ms, new setting (baud rate, etc) takes effect here &n; *       after&n; */
DECL|function|ma600_change_speed
r_static
r_int
id|ma600_change_speed
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
r_static
id|__u8
id|byte
suffix:semicolon
id|__u8
id|byte_echo
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
r_if
c_cond
(paren
id|self-&gt;speed_task
op_logical_and
id|self-&gt;speed_task
op_ne
id|task
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), busy!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_else
(brace
id|self-&gt;speed_task
op_assign
id|task
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|task-&gt;state
)paren
(brace
r_case
id|IRDA_TASK_INIT
suffix:colon
r_case
id|IRDA_TASK_CHILD_INIT
suffix:colon
multiline_comment|/* &n;&t;&t; * Need to reset the dongle and go to 9600 bps before&n;                 * programming &n;&t;&t; */
r_if
c_cond
(paren
id|irda_task_execute
c_func
(paren
id|self
comma
id|ma600_reset
comma
l_int|NULL
comma
id|task
comma
(paren
r_void
op_star
)paren
id|speed
)paren
)paren
(brace
multiline_comment|/* Dongle need more time to reset */
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_CHILD_WAIT
)paren
suffix:semicolon
multiline_comment|/* give 1 second to finish */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
r_else
(brace
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_CHILD_DONE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IRDA_TASK_CHILD_WAIT
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;%s(), resetting dongle timed out!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_CHILD_DONE
suffix:colon
multiline_comment|/* Set DTR, Clear RTS */
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
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Sleep 1 ms */
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
id|speed
op_assign
(paren
id|__u32
)paren
id|task-&gt;param
suffix:semicolon
id|byte
op_assign
id|get_control_byte
c_func
(paren
id|speed
)paren
suffix:semicolon
multiline_comment|/* Write control byte */
id|self
op_member_access_from_pointer
id|write
c_func
(paren
id|self-&gt;dev
comma
op_amp
id|byte
comma
r_sizeof
(paren
id|byte
)paren
)paren
suffix:semicolon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT1
)paren
suffix:semicolon
multiline_comment|/* Wait at least 10 ms */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|15
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT1
suffix:colon
multiline_comment|/* Read control byte echo */
id|self
op_member_access_from_pointer
id|read
c_func
(paren
id|self-&gt;dev
comma
op_amp
id|byte_echo
comma
r_sizeof
(paren
id|byte_echo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|byte
op_ne
id|byte_echo
)paren
(brace
multiline_comment|/* if control byte != echo, I don&squot;t know what to do */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s() control byte written != read!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;control byte = 0x%c%c&bslash;n&quot;
comma
id|hexTbl
(braket
(paren
id|byte
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)braket
comma
id|hexTbl
(braket
id|byte
op_amp
l_int|0x0f
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;byte echo = 0x%c%c&bslash;n&quot;
comma
id|hexTbl
(braket
(paren
id|byte_echo
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)braket
comma
id|hexTbl
(braket
id|byte_echo
op_amp
l_int|0x0f
)braket
)paren
suffix:semicolon
macro_line|#ifndef NDEBUG
)brace
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s() control byte write read OK&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
macro_line|#endif
)brace
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
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT2
)paren
suffix:semicolon
multiline_comment|/* Wait at least 10 ms */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT2
suffix:colon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
id|self-&gt;speed_task
op_assign
l_int|NULL
suffix:semicolon
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
id|self-&gt;speed_task
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
multiline_comment|/*&n; * Function ma600_reset (driver)&n; *&n; *      This function resets the ma600 dongle. Warning, this function &n; *      must be called with a process context!! &n; *&n; *      Algorithm:&n; *    &t;  0. DTR=0, RTS=1 and wait 10 ms&n; *    &t;  1. DTR=1, RTS=1 and wait 10 ms&n; *        2. 9600 bps now&n; */
DECL|function|ma600_reset
r_int
id|ma600_reset
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
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
r_if
c_cond
(paren
id|self-&gt;reset_task
op_logical_and
id|self-&gt;reset_task
op_ne
id|task
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), busy!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_else
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
multiline_comment|/* Clear DTR and Set RTS */
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
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT1
)paren
suffix:semicolon
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Sleep 10 ms */
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT1
suffix:colon
multiline_comment|/* Set DTR and RTS */
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
id|IRDA_TASK_WAIT2
)paren
suffix:semicolon
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Sleep 10 ms */
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT2
suffix:colon
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
)brace
r_return
id|ret
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Leung &lt;95Etwl@alumni.ee.ust.hk&gt; http://www.engsvr.ust/~eetwl95&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MA600 dongle driver version 0.1&quot;
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
l_string|&quot;irda-dongle-11&quot;
)paren
suffix:semicolon
multiline_comment|/* IRDA_MA600_DONGLE */
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize MA600 module&n; *&n; */
DECL|variable|ma600_init
id|module_init
c_func
(paren
id|ma600_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup MA600 module&n; *&n; */
DECL|variable|ma600_cleanup
id|module_exit
c_func
(paren
id|ma600_cleanup
)paren
suffix:semicolon
eof
