multiline_comment|/*********************************************************************&n; *                &n; * Filename:      girbil.c&n; * Version:       1.2&n; * Description:   Implementation for the Greenwich GIrBIL dongle&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Feb  6 21:02:33 1999&n; * Modified at:   Fri Dec 17 09:13:20 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/irtty.h&gt;
r_static
r_int
id|girbil_reset
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
id|girbil_open
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
id|girbil_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
suffix:semicolon
r_static
r_int
id|girbil_change_speed
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
multiline_comment|/* Control register 1 */
DECL|macro|GIRBIL_TXEN
mdefine_line|#define GIRBIL_TXEN    0x01 /* Enable transmitter */
DECL|macro|GIRBIL_RXEN
mdefine_line|#define GIRBIL_RXEN    0x02 /* Enable receiver */
DECL|macro|GIRBIL_ECAN
mdefine_line|#define GIRBIL_ECAN    0x04 /* Cancel self emmited data */
DECL|macro|GIRBIL_ECHO
mdefine_line|#define GIRBIL_ECHO    0x08 /* Echo control characters */
multiline_comment|/* LED Current Register (0x2) */
DECL|macro|GIRBIL_HIGH
mdefine_line|#define GIRBIL_HIGH    0x20
DECL|macro|GIRBIL_MEDIUM
mdefine_line|#define GIRBIL_MEDIUM  0x21
DECL|macro|GIRBIL_LOW
mdefine_line|#define GIRBIL_LOW     0x22
multiline_comment|/* Baud register (0x3) */
DECL|macro|GIRBIL_2400
mdefine_line|#define GIRBIL_2400    0x30
DECL|macro|GIRBIL_4800
mdefine_line|#define GIRBIL_4800    0x31&t;
DECL|macro|GIRBIL_9600
mdefine_line|#define GIRBIL_9600    0x32
DECL|macro|GIRBIL_19200
mdefine_line|#define GIRBIL_19200   0x33
DECL|macro|GIRBIL_38400
mdefine_line|#define GIRBIL_38400   0x34&t;
DECL|macro|GIRBIL_57600
mdefine_line|#define GIRBIL_57600   0x35&t;
DECL|macro|GIRBIL_115200
mdefine_line|#define GIRBIL_115200  0x36
multiline_comment|/* Mode register (0x4) */
DECL|macro|GIRBIL_IRDA
mdefine_line|#define GIRBIL_IRDA    0x40
DECL|macro|GIRBIL_ASK
mdefine_line|#define GIRBIL_ASK     0x41
multiline_comment|/* Control register 2 (0x5) */
DECL|macro|GIRBIL_LOAD
mdefine_line|#define GIRBIL_LOAD    0x51 /* Load the new baud rate value */
DECL|variable|dongle
r_static
r_struct
id|dongle_reg
id|dongle
op_assign
(brace
id|Q_NULL
comma
id|IRDA_GIRBIL_DONGLE
comma
id|girbil_open
comma
id|girbil_close
comma
id|girbil_reset
comma
id|girbil_change_speed
comma
)brace
suffix:semicolon
DECL|function|girbil_init
r_int
id|__init
id|girbil_init
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
DECL|function|girbil_cleanup
r_void
id|__exit
id|girbil_cleanup
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
DECL|function|girbil_open
r_static
r_void
id|girbil_open
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
l_int|0x03
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|girbil_close
r_static
r_void
id|girbil_close
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
multiline_comment|/*&n; * Function girbil_change_speed (dev, speed)&n; *&n; *    Set the speed for the Girbil type dongle.&n; *&n; */
DECL|function|girbil_change_speed
r_static
r_int
id|girbil_change_speed
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
id|control
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|self-&gt;speed_task
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
multiline_comment|/* Need to reset the dongle and go to 9600 bps before&n;                   programming */
r_if
c_cond
(paren
id|irda_task_execute
c_func
(paren
id|self
comma
id|girbil_reset
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
multiline_comment|/* Set DTR and Clear RTS to enter command mode */
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
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
l_int|9600
suffix:colon
r_default
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|GIRBIL_9600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19200
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|GIRBIL_19200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|34800
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|GIRBIL_38400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|57600
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|GIRBIL_57600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|115200
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|GIRBIL_115200
suffix:semicolon
r_break
suffix:semicolon
)brace
id|control
(braket
l_int|1
)braket
op_assign
id|GIRBIL_LOAD
suffix:semicolon
multiline_comment|/* Write control bytes */
id|self
op_member_access_from_pointer
id|write
c_func
(paren
id|self-&gt;dev
comma
id|control
comma
l_int|2
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
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|100
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT
suffix:colon
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
multiline_comment|/*&n; * Function girbil_reset (driver)&n; *&n; *      This function resets the girbil dongle.&n; *&n; *      Algorithm:&n; *    &t;  0. set RTS, and wait at least 5 ms &n; *        1. clear RTS &n; */
DECL|function|girbil_reset
r_static
r_int
id|girbil_reset
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
id|__u8
id|control
op_assign
id|GIRBIL_TXEN
op_or
id|GIRBIL_RXEN
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
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
multiline_comment|/* Reset dongle */
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
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT1
)paren
suffix:semicolon
multiline_comment|/* Sleep at least 5 ms */
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT1
suffix:colon
multiline_comment|/* Set DTR and clear RTS to enter command mode */
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
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT2
suffix:colon
multiline_comment|/* Write control byte */
id|self
op_member_access_from_pointer
id|write
c_func
(paren
id|self-&gt;dev
comma
op_amp
id|control
comma
l_int|1
)paren
suffix:semicolon
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_WAIT3
)paren
suffix:semicolon
id|ret
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TASK_WAIT3
suffix:colon
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
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Greenwich GIrBIL dongle driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize Girbil module&n; *&n; */
DECL|variable|girbil_init
id|module_init
c_func
(paren
id|girbil_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup Girbil module&n; *&n; */
DECL|variable|girbil_cleanup
id|module_exit
c_func
(paren
id|girbil_cleanup
)paren
suffix:semicolon
eof
