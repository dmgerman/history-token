multiline_comment|/*********************************************************************&n; *&n; * Filename:      act200l.c&n; * Version:       0.8&n; * Description:   Implementation for the ACTiSYS ACT-IR200L dongle&n; * Status:        Experimental.&n; * Author:        SHIMIZU Takuya &lt;tshimizu@ga2.so-net.ne.jp&gt;&n; * Created at:    Fri Aug  3 17:35:42 2001&n; * Modified at:   Fri Aug 17 10:22:40 2001&n; * Modified by:   SHIMIZU Takuya &lt;tshimizu@ga2.so-net.ne.jp&gt;&n; *&n; *     Copyright (c) 2001 SHIMIZU Takuya, All Rights Reserved.&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
r_static
r_int
id|act200l_reset
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|act200l_open
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|act200l_close
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|act200l_change_speed
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
suffix:semicolon
multiline_comment|/* Regsiter 0: Control register #1 */
DECL|macro|ACT200L_REG0
mdefine_line|#define ACT200L_REG0    0x00
DECL|macro|ACT200L_TXEN
mdefine_line|#define ACT200L_TXEN    0x01 /* Enable transmitter */
DECL|macro|ACT200L_RXEN
mdefine_line|#define ACT200L_RXEN    0x02 /* Enable receiver */
multiline_comment|/* Register 1: Control register #2 */
DECL|macro|ACT200L_REG1
mdefine_line|#define ACT200L_REG1    0x10
DECL|macro|ACT200L_LODB
mdefine_line|#define ACT200L_LODB    0x01 /* Load new baud rate count value */
DECL|macro|ACT200L_WIDE
mdefine_line|#define ACT200L_WIDE    0x04 /* Expand the maximum allowable pulse */
multiline_comment|/* Register 4: Output Power register */
DECL|macro|ACT200L_REG4
mdefine_line|#define ACT200L_REG4    0x40
DECL|macro|ACT200L_OP0
mdefine_line|#define ACT200L_OP0     0x01 /* Enable LED1C output */
DECL|macro|ACT200L_OP1
mdefine_line|#define ACT200L_OP1     0x02 /* Enable LED2C output */
DECL|macro|ACT200L_BLKR
mdefine_line|#define ACT200L_BLKR    0x04
multiline_comment|/* Register 5: Receive Mode register */
DECL|macro|ACT200L_REG5
mdefine_line|#define ACT200L_REG5    0x50
DECL|macro|ACT200L_RWIDL
mdefine_line|#define ACT200L_RWIDL   0x01 /* fixed 1.6us pulse mode */
multiline_comment|/* Register 6: Receive Sensitivity register #1 */
DECL|macro|ACT200L_REG6
mdefine_line|#define ACT200L_REG6    0x60
DECL|macro|ACT200L_RS0
mdefine_line|#define ACT200L_RS0     0x01 /* receive threshold bit 0 */
DECL|macro|ACT200L_RS1
mdefine_line|#define ACT200L_RS1     0x02 /* receive threshold bit 1 */
multiline_comment|/* Register 7: Receive Sensitivity register #2 */
DECL|macro|ACT200L_REG7
mdefine_line|#define ACT200L_REG7    0x70
DECL|macro|ACT200L_ENPOS
mdefine_line|#define ACT200L_ENPOS   0x04 /* Ignore the falling edge */
multiline_comment|/* Register 8,9: Baud Rate Dvider register #1,#2 */
DECL|macro|ACT200L_REG8
mdefine_line|#define ACT200L_REG8    0x80
DECL|macro|ACT200L_REG9
mdefine_line|#define ACT200L_REG9    0x90
DECL|macro|ACT200L_2400
mdefine_line|#define ACT200L_2400    0x5f
DECL|macro|ACT200L_9600
mdefine_line|#define ACT200L_9600    0x17
DECL|macro|ACT200L_19200
mdefine_line|#define ACT200L_19200   0x0b
DECL|macro|ACT200L_38400
mdefine_line|#define ACT200L_38400   0x05
DECL|macro|ACT200L_57600
mdefine_line|#define ACT200L_57600   0x03
DECL|macro|ACT200L_115200
mdefine_line|#define ACT200L_115200  0x01
multiline_comment|/* Register 13: Control register #3 */
DECL|macro|ACT200L_REG13
mdefine_line|#define ACT200L_REG13   0xd0
DECL|macro|ACT200L_SHDW
mdefine_line|#define ACT200L_SHDW    0x01 /* Enable access to shadow registers */
multiline_comment|/* Register 15: Status register */
DECL|macro|ACT200L_REG15
mdefine_line|#define ACT200L_REG15   0xf0
multiline_comment|/* Register 21: Control register #4 */
DECL|macro|ACT200L_REG21
mdefine_line|#define ACT200L_REG21   0x50
DECL|macro|ACT200L_EXCK
mdefine_line|#define ACT200L_EXCK    0x02 /* Disable clock output driver */
DECL|macro|ACT200L_OSCL
mdefine_line|#define ACT200L_OSCL    0x04 /* oscillator in low power, medium accuracy mode */
DECL|variable|act200l
r_static
r_struct
id|dongle_driver
id|act200l
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
l_string|&quot;ACTiSYS ACT-IR200L&quot;
comma
dot
id|type
op_assign
id|IRDA_ACT200L_DONGLE
comma
dot
id|open
op_assign
id|act200l_open
comma
dot
id|close
op_assign
id|act200l_close
comma
dot
id|reset
op_assign
id|act200l_reset
comma
dot
id|set_speed
op_assign
id|act200l_change_speed
comma
)brace
suffix:semicolon
DECL|function|act200l_sir_init
r_static
r_int
id|__init
id|act200l_sir_init
c_func
(paren
r_void
)paren
(brace
r_return
id|irda_register_dongle
c_func
(paren
op_amp
id|act200l
)paren
suffix:semicolon
)brace
DECL|function|act200l_sir_cleanup
r_static
r_void
id|__exit
id|act200l_sir_cleanup
c_func
(paren
r_void
)paren
(brace
id|irda_unregister_dongle
c_func
(paren
op_amp
id|act200l
)paren
suffix:semicolon
)brace
DECL|function|act200l_open
r_static
r_int
id|act200l_open
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
multiline_comment|/* Power on the dongle */
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
id|qos-&gt;min_turn_time.bits
op_assign
l_int|0x03
suffix:semicolon
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
DECL|function|act200l_close
r_static
r_int
id|act200l_close
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
multiline_comment|/* Power off the dongle */
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
multiline_comment|/*&n; * Function act200l_change_speed (dev, speed)&n; *&n; *    Set the speed for the ACTiSYS ACT-IR200L type dongle.&n; *&n; */
DECL|function|act200l_change_speed
r_static
r_int
id|act200l_change_speed
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
id|u8
id|control
(braket
l_int|3
)braket
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
multiline_comment|/* Clear DTR and set RTS to enter command mode */
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
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|9600
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|ACT200L_REG8
op_or
(paren
id|ACT200L_9600
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|control
(braket
l_int|1
)braket
op_assign
id|ACT200L_REG9
op_or
(paren
(paren
id|ACT200L_9600
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
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
id|ACT200L_REG8
op_or
(paren
id|ACT200L_19200
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|control
(braket
l_int|1
)braket
op_assign
id|ACT200L_REG9
op_or
(paren
(paren
id|ACT200L_19200
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38400
suffix:colon
id|control
(braket
l_int|0
)braket
op_assign
id|ACT200L_REG8
op_or
(paren
id|ACT200L_38400
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|control
(braket
l_int|1
)braket
op_assign
id|ACT200L_REG9
op_or
(paren
(paren
id|ACT200L_38400
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
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
id|ACT200L_REG8
op_or
(paren
id|ACT200L_57600
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|control
(braket
l_int|1
)braket
op_assign
id|ACT200L_REG9
op_or
(paren
(paren
id|ACT200L_57600
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
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
id|ACT200L_REG8
op_or
(paren
id|ACT200L_115200
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|control
(braket
l_int|1
)braket
op_assign
id|ACT200L_REG9
op_or
(paren
(paren
id|ACT200L_115200
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|control
(braket
l_int|2
)braket
op_assign
id|ACT200L_REG1
op_or
id|ACT200L_LODB
op_or
id|ACT200L_WIDE
suffix:semicolon
multiline_comment|/* Write control bytes */
id|sirdev_raw_write
c_func
(paren
id|dev
comma
id|control
comma
l_int|3
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Go back to normal mode */
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
id|dev-&gt;speed
op_assign
id|speed
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function act200l_reset (driver)&n; *&n; *    Reset the ACTiSYS ACT-IR200L type dongle.&n; */
DECL|macro|ACT200L_STATE_WAIT1_RESET
mdefine_line|#define ACT200L_STATE_WAIT1_RESET&t;(SIRDEV_STATE_DONGLE_RESET+1)
DECL|macro|ACT200L_STATE_WAIT2_RESET
mdefine_line|#define ACT200L_STATE_WAIT2_RESET&t;(SIRDEV_STATE_DONGLE_RESET+2)
DECL|function|act200l_reset
r_static
r_int
id|act200l_reset
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
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
id|control
(braket
l_int|9
)braket
op_assign
(brace
id|ACT200L_REG15
comma
id|ACT200L_REG13
op_or
id|ACT200L_SHDW
comma
id|ACT200L_REG21
op_or
id|ACT200L_EXCK
op_or
id|ACT200L_OSCL
comma
id|ACT200L_REG13
comma
id|ACT200L_REG7
op_or
id|ACT200L_ENPOS
comma
id|ACT200L_REG6
op_or
id|ACT200L_RS0
op_or
id|ACT200L_RS1
comma
id|ACT200L_REG5
op_or
id|ACT200L_RWIDL
comma
id|ACT200L_REG4
op_or
id|ACT200L_OP0
op_or
id|ACT200L_OP1
op_or
id|ACT200L_BLKR
comma
id|ACT200L_REG0
op_or
id|ACT200L_TXEN
op_or
id|ACT200L_RXEN
)brace
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
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|SIRDEV_STATE_DONGLE_RESET
suffix:colon
multiline_comment|/* Reset the dongle : set RTS low for 25 ms */
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
id|state
op_assign
id|ACT200L_STATE_WAIT1_RESET
suffix:semicolon
id|delay
op_assign
l_int|50
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACT200L_STATE_WAIT1_RESET
suffix:colon
multiline_comment|/* Clear DTR and set RTS to enter command mode */
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
id|udelay
c_func
(paren
l_int|25
)paren
suffix:semicolon
multiline_comment|/* better wait for some short while */
multiline_comment|/* Write control bytes */
id|sirdev_raw_write
c_func
(paren
id|dev
comma
id|control
comma
r_sizeof
(paren
id|control
)paren
)paren
suffix:semicolon
id|state
op_assign
id|ACT200L_STATE_WAIT2_RESET
suffix:semicolon
id|delay
op_assign
l_int|15
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACT200L_STATE_WAIT2_RESET
suffix:colon
multiline_comment|/* Go back to normal mode */
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
id|dev-&gt;speed
op_assign
l_int|9600
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
id|state
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
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
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;SHIMIZU Takuya &lt;tshimizu@ga2.so-net.ne.jp&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ACTiSYS ACT-IR200L dongle driver&quot;
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
l_string|&quot;irda-dongle-10&quot;
)paren
suffix:semicolon
multiline_comment|/* IRDA_ACT200L_DONGLE */
DECL|variable|act200l_sir_init
id|module_init
c_func
(paren
id|act200l_sir_init
)paren
suffix:semicolon
DECL|variable|act200l_sir_cleanup
id|module_exit
c_func
(paren
id|act200l_sir_cleanup
)paren
suffix:semicolon
eof
