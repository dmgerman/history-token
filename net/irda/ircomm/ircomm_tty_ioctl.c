multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_tty_ioctl.c&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Thu Jun 10 14:39:09 1999&n; * Modified at:   Wed Jan  5 14:45:43 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999-2000 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/ircomm_core.h&gt;
macro_line|#include &lt;net/irda/ircomm_param.h&gt;
macro_line|#include &lt;net/irda/ircomm_tty_attach.h&gt;
macro_line|#include &lt;net/irda/ircomm_tty.h&gt;
DECL|macro|RELEVANT_IFLAG
mdefine_line|#define RELEVANT_IFLAG(iflag) (iflag &amp; (IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK))
multiline_comment|/*&n; * Function ircomm_tty_change_speed (driver)&n; *&n; *    Change speed of the driver. If the remote device is a DCE, then this&n; *    should make it change the speed of its serial port&n; */
DECL|function|ircomm_tty_change_speed
r_void
id|ircomm_tty_change_speed
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
)paren
(brace
r_int
id|cflag
comma
id|cval
suffix:semicolon
r_int
id|baud
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
r_if
c_cond
(paren
op_logical_neg
id|self-&gt;tty
op_logical_or
op_logical_neg
id|self-&gt;tty-&gt;termios
op_logical_or
op_logical_neg
id|self-&gt;ircomm
)paren
r_return
suffix:semicolon
id|cflag
op_assign
id|self-&gt;tty-&gt;termios-&gt;c_cflag
suffix:semicolon
multiline_comment|/*  byte size and parity */
r_switch
c_cond
(paren
id|cflag
op_amp
id|CSIZE
)paren
(brace
r_case
id|CS5
suffix:colon
id|cval
op_assign
id|IRCOMM_WSIZE_5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|cval
op_assign
id|IRCOMM_WSIZE_6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|cval
op_assign
id|IRCOMM_WSIZE_7
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS8
suffix:colon
id|cval
op_assign
id|IRCOMM_WSIZE_8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cval
op_assign
id|IRCOMM_WSIZE_5
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cflag
op_amp
id|CSTOPB
)paren
id|cval
op_or_assign
id|IRCOMM_2_STOP_BIT
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
id|cval
op_or_assign
id|IRCOMM_PARITY_ENABLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cflag
op_amp
id|PARODD
)paren
)paren
id|cval
op_or_assign
id|IRCOMM_PARITY_EVEN
suffix:semicolon
multiline_comment|/* Determine divisor based on baud rate */
id|baud
op_assign
id|tty_get_baud_rate
c_func
(paren
id|self-&gt;tty
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|baud
)paren
id|baud
op_assign
l_int|9600
suffix:semicolon
multiline_comment|/* B0 transition handled in rs_set_termios */
id|self-&gt;settings.data_rate
op_assign
id|baud
suffix:semicolon
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DATA_RATE
comma
id|FALSE
)paren
suffix:semicolon
multiline_comment|/* CTS flow control flag and modem status interrupts */
r_if
c_cond
(paren
id|cflag
op_amp
id|CRTSCTS
)paren
(brace
id|self-&gt;flags
op_or_assign
id|ASYNC_CTS_FLOW
suffix:semicolon
id|self-&gt;settings.flow_control
op_or_assign
id|IRCOMM_RTS_CTS_IN
suffix:semicolon
multiline_comment|/* This got me. Bummer. Jean II */
r_if
c_cond
(paren
id|self-&gt;service_type
op_eq
id|IRCOMM_3_WIRE_RAW
)paren
id|WARNING
c_func
(paren
l_string|&quot;%s(), enabling RTS/CTS on link that doesn&squot;t support it (3-wire-raw)&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_else
(brace
id|self-&gt;flags
op_and_assign
op_complement
id|ASYNC_CTS_FLOW
suffix:semicolon
id|self-&gt;settings.flow_control
op_and_assign
op_complement
id|IRCOMM_RTS_CTS_IN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cflag
op_amp
id|CLOCAL
)paren
id|self-&gt;flags
op_and_assign
op_complement
id|ASYNC_CHECK_CD
suffix:semicolon
r_else
id|self-&gt;flags
op_or_assign
id|ASYNC_CHECK_CD
suffix:semicolon
macro_line|#if 0&t;
multiline_comment|/*&n;&t; * Set up parity check flag&n;&t; */
r_if
c_cond
(paren
id|I_INPCK
c_func
(paren
id|self-&gt;tty
)paren
)paren
id|driver-&gt;read_status_mask
op_or_assign
id|LSR_FE
op_or
id|LSR_PE
suffix:semicolon
r_if
c_cond
(paren
id|I_BRKINT
c_func
(paren
id|driver-&gt;tty
)paren
op_logical_or
id|I_PARMRK
c_func
(paren
id|driver-&gt;tty
)paren
)paren
id|driver-&gt;read_status_mask
op_or_assign
id|LSR_BI
suffix:semicolon
multiline_comment|/*&n;&t; * Characters to ignore&n;&t; */
id|driver-&gt;ignore_status_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|I_IGNPAR
c_func
(paren
id|driver-&gt;tty
)paren
)paren
id|driver-&gt;ignore_status_mask
op_or_assign
id|LSR_PE
op_or
id|LSR_FE
suffix:semicolon
r_if
c_cond
(paren
id|I_IGNBRK
c_func
(paren
id|self-&gt;tty
)paren
)paren
(brace
id|self-&gt;ignore_status_mask
op_or_assign
id|LSR_BI
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we&squot;re ignore parity and break indicators, ignore &n;&t;&t; * overruns too. (For real raw support).&n;&t;&t; */
r_if
c_cond
(paren
id|I_IGNPAR
c_func
(paren
id|self-&gt;tty
)paren
)paren
id|self-&gt;ignore_status_mask
op_or_assign
id|LSR_OE
suffix:semicolon
)brace
macro_line|#endif
id|self-&gt;settings.data_format
op_assign
id|cval
suffix:semicolon
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DATA_FORMAT
comma
id|FALSE
)paren
suffix:semicolon
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_FLOW_CONTROL
comma
id|TRUE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_tty_set_termios (tty, old_termios)&n; *&n; *    This routine allows the tty driver to be notified when device&squot;s&n; *    termios settings have changed.  Note that a well-designed tty driver&n; *    should be prepared to accept the case where old == NULL, and try to&n; *    do something rational.&n; */
DECL|function|ircomm_tty_set_termios
r_void
id|ircomm_tty_set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old_termios
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
r_int
r_int
id|cflag
op_assign
id|tty-&gt;termios-&gt;c_cflag
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
r_if
c_cond
(paren
(paren
id|cflag
op_eq
id|old_termios-&gt;c_cflag
)paren
op_logical_and
(paren
id|RELEVANT_IFLAG
c_func
(paren
id|tty-&gt;termios-&gt;c_iflag
)paren
op_eq
id|RELEVANT_IFLAG
c_func
(paren
id|old_termios-&gt;c_iflag
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|ircomm_tty_change_speed
c_func
(paren
id|self
)paren
suffix:semicolon
multiline_comment|/* Handle transition to B0 status */
r_if
c_cond
(paren
(paren
id|old_termios-&gt;c_cflag
op_amp
id|CBAUD
)paren
op_logical_and
op_logical_neg
(paren
id|cflag
op_amp
id|CBAUD
)paren
)paren
(brace
id|self-&gt;settings.dte
op_and_assign
op_complement
(paren
id|IRCOMM_DTR
op_or
id|IRCOMM_RTS
)paren
suffix:semicolon
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DTE
comma
id|TRUE
)paren
suffix:semicolon
)brace
multiline_comment|/* Handle transition away from B0 status */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old_termios-&gt;c_cflag
op_amp
id|CBAUD
)paren
op_logical_and
(paren
id|cflag
op_amp
id|CBAUD
)paren
)paren
(brace
id|self-&gt;settings.dte
op_or_assign
id|IRCOMM_DTR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tty-&gt;termios-&gt;c_cflag
op_amp
id|CRTSCTS
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
)paren
)paren
(brace
id|self-&gt;settings.dte
op_or_assign
id|IRCOMM_RTS
suffix:semicolon
)brace
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DTE
comma
id|TRUE
)paren
suffix:semicolon
)brace
multiline_comment|/* Handle turning off CRTSCTS */
r_if
c_cond
(paren
(paren
id|old_termios-&gt;c_cflag
op_amp
id|CRTSCTS
)paren
op_logical_and
op_logical_neg
(paren
id|tty-&gt;termios-&gt;c_cflag
op_amp
id|CRTSCTS
)paren
)paren
(brace
id|tty-&gt;hw_stopped
op_assign
l_int|0
suffix:semicolon
id|ircomm_tty_start
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_tty_get_modem_info (self, value)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_tty_get_modem_info
r_static
r_int
id|ircomm_tty_get_modem_info
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
comma
r_int
r_int
op_star
id|value
)paren
(brace
r_int
r_int
id|result
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
id|result
op_assign
(paren
(paren
id|self-&gt;settings.dte
op_amp
id|IRCOMM_RTS
)paren
ques
c_cond
id|TIOCM_RTS
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|self-&gt;settings.dte
op_amp
id|IRCOMM_DTR
)paren
ques
c_cond
id|TIOCM_DTR
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|self-&gt;settings.dce
op_amp
id|IRCOMM_CD
)paren
ques
c_cond
id|TIOCM_CAR
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|self-&gt;settings.dce
op_amp
id|IRCOMM_RI
)paren
ques
c_cond
id|TIOCM_RNG
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|self-&gt;settings.dce
op_amp
id|IRCOMM_DSR
)paren
ques
c_cond
id|TIOCM_DSR
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|self-&gt;settings.dce
op_amp
id|IRCOMM_CTS
)paren
ques
c_cond
id|TIOCM_CTS
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|result
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function set_modem_info (driver, cmd, value)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_tty_set_modem_info
r_static
r_int
id|ircomm_tty_set_modem_info
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
comma
r_int
r_int
id|cmd
comma
r_int
r_int
op_star
id|value
)paren
(brace
r_int
r_int
id|arg
suffix:semicolon
id|__u8
id|old_rts
comma
id|old_dtr
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
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
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
id|get_user
c_func
(paren
id|arg
comma
id|value
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|old_rts
op_assign
id|self-&gt;settings.dte
op_amp
id|IRCOMM_RTS
suffix:semicolon
id|old_dtr
op_assign
id|self-&gt;settings.dte
op_amp
id|IRCOMM_DTR
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCMBIS
suffix:colon
r_if
c_cond
(paren
id|arg
op_amp
id|TIOCM_RTS
)paren
id|self-&gt;settings.dte
op_or_assign
id|IRCOMM_RTS
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_amp
id|TIOCM_DTR
)paren
id|self-&gt;settings.dte
op_or_assign
id|IRCOMM_DTR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMBIC
suffix:colon
r_if
c_cond
(paren
id|arg
op_amp
id|TIOCM_RTS
)paren
id|self-&gt;settings.dte
op_and_assign
op_complement
id|IRCOMM_RTS
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_amp
id|TIOCM_DTR
)paren
id|self-&gt;settings.dte
op_and_assign
op_complement
id|IRCOMM_DTR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMSET
suffix:colon
id|self-&gt;settings.dte
op_assign
(paren
(paren
id|self-&gt;settings.dte
op_amp
op_complement
(paren
id|IRCOMM_RTS
op_or
id|IRCOMM_DTR
)paren
)paren
op_or
(paren
(paren
id|arg
op_amp
id|TIOCM_RTS
)paren
ques
c_cond
id|IRCOMM_RTS
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|arg
op_amp
id|TIOCM_DTR
)paren
ques
c_cond
id|IRCOMM_DTR
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;settings.dte
op_amp
id|IRCOMM_RTS
)paren
op_ne
id|old_rts
)paren
id|self-&gt;settings.dte
op_or_assign
id|IRCOMM_DELTA_RTS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|self-&gt;settings.dte
op_amp
id|IRCOMM_DTR
)paren
op_ne
id|old_dtr
)paren
id|self-&gt;settings.dte
op_or_assign
id|IRCOMM_DELTA_DTR
suffix:semicolon
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DTE
comma
id|TRUE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function get_serial_info (driver, retinfo)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_tty_get_serial_info
r_static
r_int
id|ircomm_tty_get_serial_info
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
comma
r_struct
id|serial_struct
op_star
id|retinfo
)paren
(brace
r_struct
id|serial_struct
id|info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retinfo
)paren
r_return
op_minus
id|EFAULT
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
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.line
op_assign
id|self-&gt;line
suffix:semicolon
id|info.flags
op_assign
id|self-&gt;flags
suffix:semicolon
id|info.baud_base
op_assign
id|self-&gt;settings.data_rate
suffix:semicolon
id|info.close_delay
op_assign
id|self-&gt;close_delay
suffix:semicolon
id|info.closing_wait
op_assign
id|self-&gt;closing_wait
suffix:semicolon
multiline_comment|/* For compatibility  */
id|info.type
op_assign
id|PORT_16550A
suffix:semicolon
id|info.port
op_assign
l_int|0
suffix:semicolon
id|info.irq
op_assign
l_int|0
suffix:semicolon
id|info.xmit_fifo_size
op_assign
l_int|0
suffix:semicolon
id|info.hub6
op_assign
l_int|0
suffix:semicolon
id|info.custom_divisor
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|retinfo
comma
op_amp
id|info
comma
r_sizeof
(paren
op_star
id|retinfo
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function set_serial_info (driver, new_info)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_tty_set_serial_info
r_static
r_int
id|ircomm_tty_set_serial_info
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
comma
r_struct
id|serial_struct
op_star
id|new_info
)paren
(brace
macro_line|#if 0
r_struct
id|serial_struct
id|new_serial
suffix:semicolon
r_struct
id|ircomm_tty_cb
id|old_state
comma
op_star
id|state
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_serial
comma
id|new_info
comma
r_sizeof
(paren
id|new_serial
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|state
op_assign
id|self
id|old_state
op_assign
op_star
id|self
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|new_serial.baud_base
op_ne
id|state-&gt;settings.data_rate
)paren
op_logical_or
(paren
id|new_serial.close_delay
op_ne
id|state-&gt;close_delay
)paren
op_logical_or
(paren
(paren
id|new_serial.flags
op_amp
op_complement
id|ASYNC_USR_MASK
)paren
op_ne
(paren
id|self-&gt;flags
op_amp
op_complement
id|ASYNC_USR_MASK
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|state-&gt;flags
op_assign
(paren
(paren
id|state-&gt;flags
op_amp
op_complement
id|ASYNC_USR_MASK
)paren
op_or
(paren
id|new_serial.flags
op_amp
id|ASYNC_USR_MASK
)paren
)paren
suffix:semicolon
id|self-&gt;flags
op_assign
(paren
(paren
id|self-&gt;flags
op_amp
op_complement
id|ASYNC_USR_MASK
)paren
op_or
(paren
id|new_serial.flags
op_amp
id|ASYNC_USR_MASK
)paren
)paren
suffix:semicolon
multiline_comment|/* self-&gt;custom_divisor = new_serial.custom_divisor; */
r_goto
id|check_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * OK, past this point, all the error checking has been done.&n;&t; * At this point, we start making changes.....&n;&t; */
r_if
c_cond
(paren
id|self-&gt;settings.data_rate
op_ne
id|new_serial.baud_base
)paren
(brace
id|self-&gt;settings.data_rate
op_assign
id|new_serial.baud_base
suffix:semicolon
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DATA_RATE
comma
id|TRUE
)paren
suffix:semicolon
)brace
id|self-&gt;close_delay
op_assign
id|new_serial.close_delay
op_star
id|HZ
op_div
l_int|100
suffix:semicolon
id|self-&gt;closing_wait
op_assign
id|new_serial.closing_wait
op_star
id|HZ
op_div
l_int|100
suffix:semicolon
multiline_comment|/* self-&gt;custom_divisor = new_serial.custom_divisor; */
id|self-&gt;flags
op_assign
(paren
(paren
id|self-&gt;flags
op_amp
op_complement
id|ASYNC_FLAGS
)paren
op_or
(paren
id|new_serial.flags
op_amp
id|ASYNC_FLAGS
)paren
)paren
suffix:semicolon
id|self-&gt;tty-&gt;low_latency
op_assign
(paren
id|self-&gt;flags
op_amp
id|ASYNC_LOW_LATENCY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|check_and_exit
suffix:colon
r_if
c_cond
(paren
id|self-&gt;flags
op_amp
id|ASYNC_INITIALIZED
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|old_state.flags
op_amp
id|ASYNC_SPD_MASK
)paren
op_ne
(paren
id|self-&gt;flags
op_amp
id|ASYNC_SPD_MASK
)paren
)paren
op_logical_or
(paren
id|old_driver.custom_divisor
op_ne
id|driver-&gt;custom_divisor
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|driver-&gt;flags
op_amp
id|ASYNC_SPD_MASK
)paren
op_eq
id|ASYNC_SPD_HI
)paren
id|driver-&gt;tty-&gt;alt_speed
op_assign
l_int|57600
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;flags
op_amp
id|ASYNC_SPD_MASK
)paren
op_eq
id|ASYNC_SPD_VHI
)paren
id|driver-&gt;tty-&gt;alt_speed
op_assign
l_int|115200
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;flags
op_amp
id|ASYNC_SPD_MASK
)paren
op_eq
id|ASYNC_SPD_SHI
)paren
id|driver-&gt;tty-&gt;alt_speed
op_assign
l_int|230400
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;flags
op_amp
id|ASYNC_SPD_MASK
)paren
op_eq
id|ASYNC_SPD_WARP
)paren
id|driver-&gt;tty-&gt;alt_speed
op_assign
l_int|460800
suffix:semicolon
id|ircomm_tty_change_speed
c_func
(paren
id|driver
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_tty_ioctl (tty, file, cmd, arg)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_tty_ioctl
r_int
id|ircomm_tty_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|tty-&gt;driver_data
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
r_if
c_cond
(paren
(paren
id|cmd
op_ne
id|TIOCGSERIAL
)paren
op_logical_and
(paren
id|cmd
op_ne
id|TIOCSSERIAL
)paren
op_logical_and
(paren
id|cmd
op_ne
id|TIOCSERCONFIG
)paren
op_logical_and
(paren
id|cmd
op_ne
id|TIOCSERGSTRUCT
)paren
op_logical_and
(paren
id|cmd
op_ne
id|TIOCMIWAIT
)paren
op_logical_and
(paren
id|cmd
op_ne
id|TIOCGICOUNT
)paren
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|TTY_IO_ERROR
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCMGET
suffix:colon
id|ret
op_assign
id|ircomm_tty_get_modem_info
c_func
(paren
id|self
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMBIS
suffix:colon
r_case
id|TIOCMBIC
suffix:colon
r_case
id|TIOCMSET
suffix:colon
id|ret
op_assign
id|ircomm_tty_set_modem_info
c_func
(paren
id|self
comma
id|cmd
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCGSERIAL
suffix:colon
id|ret
op_assign
id|ircomm_tty_get_serial_info
c_func
(paren
id|self
comma
(paren
r_struct
id|serial_struct
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCSSERIAL
suffix:colon
id|ret
op_assign
id|ircomm_tty_set_serial_info
c_func
(paren
id|self
comma
(paren
r_struct
id|serial_struct
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMIWAIT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;(), TIOCMIWAIT, not impl!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCGICOUNT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), TIOCGICOUNT not impl!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
macro_line|#if 0
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cnow
op_assign
id|driver-&gt;icount
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|p_cuser
op_assign
(paren
r_struct
id|serial_icounter_struct
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|cnow.cts
comma
op_amp
id|p_cuser-&gt;cts
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.dsr
comma
op_amp
id|p_cuser-&gt;dsr
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.rng
comma
op_amp
id|p_cuser-&gt;rng
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.dcd
comma
op_amp
id|p_cuser-&gt;dcd
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.rx
comma
op_amp
id|p_cuser-&gt;rx
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.tx
comma
op_amp
id|p_cuser-&gt;tx
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.frame
comma
op_amp
id|p_cuser-&gt;frame
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.overrun
comma
op_amp
id|p_cuser-&gt;overrun
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.parity
comma
op_amp
id|p_cuser-&gt;parity
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.brk
comma
op_amp
id|p_cuser-&gt;brk
)paren
op_logical_or
id|put_user
c_func
(paren
id|cnow.buf_overrun
comma
op_amp
id|p_cuser-&gt;buf_overrun
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
macro_line|#endif&t;&t;
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|ENOIOCTLCMD
suffix:semicolon
multiline_comment|/* ioctls which we must ignore */
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
