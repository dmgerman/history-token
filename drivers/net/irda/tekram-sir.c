multiline_comment|/*********************************************************************&n; *                &n; * Filename:      tekram.c&n; * Version:       1.3&n; * Description:   Implementation of the Tekram IrMate IR-210B dongle&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Wed Oct 21 20:02:35 1998&n; * Modified at:   Sun Oct 27 22:02:38 2002&n; * Modified by:   Martin Diehl &lt;mad@mdiehl.de&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli,&n; *     Copyright (c) 2002 Martin Diehl,&n; *     All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
DECL|variable|tekram_delay
r_static
r_int
id|tekram_delay
op_assign
l_int|150
suffix:semicolon
multiline_comment|/* default is 150 ms */
id|module_param
c_func
(paren
id|tekram_delay
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|tekram_delay
comma
l_string|&quot;tekram dongle write complete delay&quot;
)paren
suffix:semicolon
r_static
r_int
id|tekram_open
c_func
(paren
r_struct
id|sir_dev
op_star
)paren
suffix:semicolon
r_static
r_int
id|tekram_close
c_func
(paren
r_struct
id|sir_dev
op_star
)paren
suffix:semicolon
r_static
r_int
id|tekram_change_speed
c_func
(paren
r_struct
id|sir_dev
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|tekram_reset
c_func
(paren
r_struct
id|sir_dev
op_star
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
DECL|variable|tekram
r_static
r_struct
id|dongle_driver
id|tekram
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|driver_name
op_assign
l_string|&quot;Tekram IR-210B&quot;
comma
dot
id|type
op_assign
id|IRDA_TEKRAM_DONGLE
comma
dot
id|open
op_assign
id|tekram_open
comma
dot
id|close
op_assign
id|tekram_close
comma
dot
id|reset
op_assign
id|tekram_reset
comma
dot
id|set_speed
op_assign
id|tekram_change_speed
comma
)brace
suffix:semicolon
DECL|function|tekram_sir_init
r_static
r_int
id|__init
id|tekram_sir_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tekram_delay
template_param
l_int|500
)paren
id|tekram_delay
op_assign
l_int|200
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;%s - using %d ms delay&bslash;n&quot;
comma
id|tekram.driver_name
comma
id|tekram_delay
)paren
suffix:semicolon
r_return
id|irda_register_dongle
c_func
(paren
op_amp
id|tekram
)paren
suffix:semicolon
)brace
DECL|function|tekram_sir_cleanup
r_static
r_void
id|__exit
id|tekram_sir_cleanup
c_func
(paren
r_void
)paren
(brace
id|irda_unregister_dongle
c_func
(paren
op_amp
id|tekram
)paren
suffix:semicolon
)brace
DECL|function|tekram_open
r_static
r_int
id|tekram_open
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_struct
id|qos_info
op_star
id|qos
op_assign
op_amp
id|dev-&gt;qos
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
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
comma
id|TRUE
comma
id|TRUE
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
multiline_comment|/* irda thread waits 50 msec for power settling */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tekram_close
r_static
r_int
id|tekram_close
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
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
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
comma
id|FALSE
comma
id|FALSE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function tekram_change_speed (dev, state, speed)&n; *&n; *    Set the speed for the Tekram IRMate 210 type dongle. Warning, this &n; *    function must be called with a process context!&n; *&n; *    Algorithm&n; *    1. clear DTR &n; *    2. set RTS, and wait at least 7 us&n; *    3. send Control Byte to the IR-210 through TXD to set new baud rate&n; *       wait until the stop bit of Control Byte is sent (for 9600 baud rate, &n; *       it takes about 100 msec)&n; *&n; *&t;[oops, why 100 msec? sending 1 byte (10 bits) takes 1.05 msec&n; *&t; - is this probably to compensate for delays in tty layer?]&n; *&n; *    5. clear RTS (return to NORMAL Operation)&n; *    6. wait at least 50 us, new setting (baud rate, etc) takes effect here &n; *       after&n; */
DECL|macro|TEKRAM_STATE_WAIT_SPEED
mdefine_line|#define TEKRAM_STATE_WAIT_SPEED&t;(SIRDEV_STATE_DONGLE_SPEED + 1)
DECL|function|tekram_change_speed
r_static
r_int
id|tekram_change_speed
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_int
id|speed
)paren
(brace
r_int
id|state
op_assign
id|dev-&gt;fsm.substate
suffix:semicolon
r_int
id|delay
op_assign
l_int|0
suffix:semicolon
id|u8
id|byte
suffix:semicolon
r_static
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
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|SIRDEV_STATE_DONGLE_SPEED
suffix:colon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_default
suffix:colon
id|speed
op_assign
l_int|9600
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* fall thru */
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
multiline_comment|/* Set DTR, Clear RTS */
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
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
id|sirdev_raw_write
c_func
(paren
id|dev
comma
op_amp
id|byte
comma
l_int|1
)paren
suffix:semicolon
id|dev-&gt;speed
op_assign
id|speed
suffix:semicolon
id|state
op_assign
id|TEKRAM_STATE_WAIT_SPEED
suffix:semicolon
id|delay
op_assign
id|tekram_delay
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TEKRAM_STATE_WAIT_SPEED
suffix:colon
multiline_comment|/* Set DTR, Set RTS */
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
comma
id|TRUE
comma
id|TRUE
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_ERROR
c_func
(paren
l_string|&quot;%s - undefined state %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|state
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dev-&gt;fsm.substate
op_assign
id|state
suffix:semicolon
r_return
(paren
id|delay
OG
l_int|0
)paren
ques
c_cond
id|delay
suffix:colon
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function tekram_reset (driver)&n; *&n; *      This function resets the tekram dongle. Warning, this function &n; *      must be called with a process context!! &n; *&n; *      Algorithm:&n; *    &t;  0. Clear RTS and DTR, and wait 50 ms (power off the IR-210 )&n; *        1. clear RTS &n; *        2. set DTR, and wait at least 1 ms &n; *        3. clear DTR to SPACE state, wait at least 50 us for further &n; *         operation&n; */
DECL|function|tekram_reset
r_static
r_int
id|tekram_reset
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
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
multiline_comment|/* Clear DTR, Set RTS */
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
comma
id|FALSE
comma
id|TRUE
)paren
suffix:semicolon
multiline_comment|/* Should sleep 1 ms */
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set DTR, Set RTS */
id|sirdev_set_dtr_rts
c_func
(paren
id|dev
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
id|dev-&gt;speed
op_assign
l_int|9600
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
l_string|&quot;Tekram IrMate IR-210B dongle driver&quot;
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
l_string|&quot;irda-dongle-0&quot;
)paren
suffix:semicolon
multiline_comment|/* IRDA_TEKRAM_DONGLE */
DECL|variable|tekram_sir_init
id|module_init
c_func
(paren
id|tekram_sir_init
)paren
suffix:semicolon
DECL|variable|tekram_sir_cleanup
id|module_exit
c_func
(paren
id|tekram_sir_cleanup
)paren
suffix:semicolon
eof
