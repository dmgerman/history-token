multiline_comment|/*********************************************************************&n; *                &n; * Filename:      tekram.c&n; * Version:       1.2&n; * Description:   Implementation of the Tekram IrMate IR-210B dongle&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Wed Oct 21 20:02:35 1998&n; * Modified at:   Fri Dec 17 09:13:09 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/irtty.h&gt;
r_static
r_void
id|tekram_open
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
id|tekram_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
suffix:semicolon
r_static
r_int
id|tekram_change_speed
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
id|tekram_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
DECL|macro|TEKRAM_115200
mdefine_line|#define TEKRAM_115200 0x00
DECL|macro|TEKRAM_57600
mdefine_line|#define TEKRAM_57600  0x01
DECL|macro|TEKRAM_38400
mdefine_line|#define TEKRAM_38400  0x02
DECL|macro|TEKRAM_19200
mdefine_line|#define TEKRAM_19200  0x03
DECL|macro|TEKRAM_9600
mdefine_line|#define TEKRAM_9600   0x04
DECL|macro|TEKRAM_PW
mdefine_line|#define TEKRAM_PW     0x10 /* Pulse select bit */
DECL|variable|dongle
r_static
r_struct
id|dongle_reg
id|dongle
op_assign
(brace
id|Q_NULL
comma
id|IRDA_TEKRAM_DONGLE
comma
id|tekram_open
comma
id|tekram_close
comma
id|tekram_reset
comma
id|tekram_change_speed
comma
)brace
suffix:semicolon
DECL|function|tekram_init
r_int
id|__init
id|tekram_init
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
DECL|function|tekram_cleanup
r_void
id|__exit
id|tekram_cleanup
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
DECL|function|tekram_open
r_static
r_void
id|tekram_open
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
multiline_comment|/* Needs at least 10 ms */
id|irda_qos_bits_to_value
c_func
(paren
id|qos
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|tekram_close
r_static
r_void
id|tekram_close
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
r_if
c_cond
(paren
id|self-&gt;reset_task
)paren
id|irda_task_delete
c_func
(paren
id|self-&gt;reset_task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;speed_task
)paren
id|irda_task_delete
c_func
(paren
id|self-&gt;speed_task
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Function tekram_change_speed (dev, state, speed)&n; *&n; *    Set the speed for the Tekram IRMate 210 type dongle. Warning, this &n; *    function must be called with a process context!&n; *&n; *    Algorithm&n; *    1. clear DTR &n; *    2. set RTS, and wait at least 7 us&n; *    3. send Control Byte to the IR-210 through TXD to set new baud rate&n; *       wait until the stop bit of Control Byte is sent (for 9600 baud rate, &n; *       it takes about 100 msec)&n; *    5. clear RTS (return to NORMAL Operation)&n; *    6. wait at least 50 us, new setting (baud rate, etc) takes effect here &n; *       after&n; */
DECL|function|tekram_change_speed
r_static
r_int
id|tekram_change_speed
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
id|__u8
id|byte
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
id|self-&gt;speed_task
op_assign
id|task
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
l_int|9600
suffix:colon
id|byte
op_assign
id|TEKRAM_PW
op_or
id|TEKRAM_9600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19200
suffix:colon
id|byte
op_assign
id|TEKRAM_PW
op_or
id|TEKRAM_19200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38400
suffix:colon
id|byte
op_assign
id|TEKRAM_PW
op_or
id|TEKRAM_38400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|57600
suffix:colon
id|byte
op_assign
id|TEKRAM_PW
op_or
id|TEKRAM_57600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|115200
suffix:colon
id|byte
op_assign
id|TEKRAM_115200
suffix:semicolon
r_break
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
id|tekram_reset
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
multiline_comment|/* Give reset 1 sec to finish */
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
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_CHILD_DONE
)paren
suffix:semicolon
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
multiline_comment|/* Wait at least 7us */
id|udelay
c_func
(paren
l_int|14
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
l_int|1
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
multiline_comment|/* Wait at least 100 ms */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|150
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT
suffix:colon
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
multiline_comment|/*&n; * Function tekram_reset (driver)&n; *&n; *      This function resets the tekram dongle. Warning, this function &n; *      must be called with a process context!! &n; *&n; *      Algorithm:&n; *    &t;  0. Clear RTS and DTR, and wait 50 ms (power off the IR-210 )&n; *        1. clear RTS &n; *        2. set DTR, and wait at least 1 ms &n; *        3. clear DTR to SPACE state, wait at least 50 us for further &n; *         operation&n; */
DECL|function|tekram_reset
r_int
id|tekram_reset
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
multiline_comment|/* Power off dongle */
singleline_comment|//self-&gt;set_dtr_rts(self-&gt;dev, FALSE, FALSE);
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
r_switch
c_cond
(paren
id|task-&gt;state
)paren
(brace
r_case
id|IRDA_TASK_INIT
suffix:colon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT1
)paren
suffix:semicolon
multiline_comment|/* Sleep 50 ms */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT1
suffix:colon
multiline_comment|/* Clear DTR, Set RTS */
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
id|IRDA_TASK_WAIT2
)paren
suffix:semicolon
multiline_comment|/* Should sleep 1 ms */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT2
suffix:colon
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
multiline_comment|/* Wait at least 50 us */
id|udelay
c_func
(paren
l_int|75
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
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Tekram IrMate IR-210B dongle driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize Tekram module&n; *&n; */
DECL|variable|tekram_init
id|module_init
c_func
(paren
id|tekram_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup Tekram module&n; *&n; */
DECL|variable|tekram_cleanup
id|module_exit
c_func
(paren
id|tekram_cleanup
)paren
suffix:semicolon
eof
