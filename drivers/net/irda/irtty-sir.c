multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irtty-sir.c&n; * Version:       2.0&n; * Description:   IrDA line discipline implementation&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:18:38 1997&n; * Modified at:   Sun Oct 27 22:13:30 2002&n; * Modified by:   Martin Diehl &lt;mad@mdiehl.de&gt;&n; * Sources:       slip.c by Laurence Culhane,   &lt;loz@holmes.demon.co.uk&gt;&n; *                          Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; * &n; *     Copyright (c) 1998-2000 Dag Brattli,&n; *     Copyright (c) 2002 Martin Diehl,&n; *     All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
macro_line|#include &quot;irtty-sir.h&quot;
DECL|variable|qos_mtt_bits
r_static
r_int
id|qos_mtt_bits
op_assign
l_int|0x03
suffix:semicolon
multiline_comment|/* 5 ms or more */
id|module_param
c_func
(paren
id|qos_mtt_bits
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|qos_mtt_bits
comma
l_string|&quot;Minimum Turn Time&quot;
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------- */
multiline_comment|/* device configuration callbacks always invoked with irda-thread context */
multiline_comment|/* find out, how many chars we have in buffers below us&n; * this is allowed to lie, i.e. return less chars than we&n; * actually have. The returned value is used to determine&n; * how long the irdathread should wait before doing the&n; * real blocking wait_until_sent()&n; */
DECL|function|irtty_chars_in_buffer
r_static
r_int
id|irtty_chars_in_buffer
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_return
id|priv-&gt;tty-&gt;driver
op_member_access_from_pointer
id|chars_in_buffer
c_func
(paren
id|priv-&gt;tty
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait (sleep) until underlaying hardware finished transmission&n; * i.e. hardware buffers are drained&n; * this must block and not return before all characters are really sent&n; *&n; * If the tty sits on top of a 16550A-like uart, there are typically&n; * up to 16 bytes in the fifo - f.e. 9600 bps 8N1 needs 16.7 msec&n; *&n; * With usbserial the uart-fifo is basically replaced by the converter&squot;s&n; * outgoing endpoint buffer, which can usually hold 64 bytes (at least).&n; * With pl2303 it appears we are safe with 60msec here.&n; *&n; * I really wish all serial drivers would provide&n; * correct implementation of wait_until_sent()&n; */
DECL|macro|USBSERIAL_TX_DONE_DELAY
mdefine_line|#define USBSERIAL_TX_DONE_DELAY&t;60
DECL|function|irtty_wait_until_sent
r_static
r_void
id|irtty_wait_until_sent
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|tty
op_assign
id|priv-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;wait_until_sent
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|tty-&gt;driver
op_member_access_from_pointer
id|wait_until_sent
c_func
(paren
id|tty
comma
id|msecs_to_jiffies
c_func
(paren
l_int|100
)paren
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|msleep
c_func
(paren
id|USBSERIAL_TX_DONE_DELAY
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; *  Function irtty_change_speed (dev, speed)&n; *&n; *    Change the speed of the serial port.&n; *&n; * This may sleep in set_termios (usbserial driver f.e.) and must&n; * not be called from interrupt/timer/tasklet therefore.&n; * All such invocations are deferred to kIrDAd now so we can sleep there.&n; */
DECL|function|irtty_change_speed
r_static
r_int
id|irtty_change_speed
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
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_struct
id|termios
id|old_termios
suffix:semicolon
r_int
id|cflag
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|tty
op_assign
id|priv-&gt;tty
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|old_termios
op_assign
op_star
(paren
id|tty-&gt;termios
)paren
suffix:semicolon
id|cflag
op_assign
id|tty-&gt;termios-&gt;c_cflag
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|CBAUD
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), Setting speed to %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|speed
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
l_int|1200
suffix:colon
id|cflag
op_or_assign
id|B1200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2400
suffix:colon
id|cflag
op_or_assign
id|B2400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4800
suffix:colon
id|cflag
op_or_assign
id|B4800
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19200
suffix:colon
id|cflag
op_or_assign
id|B19200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38400
suffix:colon
id|cflag
op_or_assign
id|B38400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|57600
suffix:colon
id|cflag
op_or_assign
id|B57600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|115200
suffix:colon
id|cflag
op_or_assign
id|B115200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9600
suffix:colon
r_default
suffix:colon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tty-&gt;termios-&gt;c_cflag
op_assign
id|cflag
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;set_termios
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|set_termios
c_func
(paren
id|tty
comma
op_amp
id|old_termios
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|priv-&gt;io.speed
op_assign
id|speed
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irtty_set_dtr_rts (dev, dtr, rts)&n; *&n; *    This function can be used by dongles etc. to set or reset the status&n; *    of the dtr and rts lines&n; */
DECL|function|irtty_set_dtr_rts
r_static
r_int
id|irtty_set_dtr_rts
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_int
id|dtr
comma
r_int
id|rts
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|set
op_assign
l_int|0
suffix:semicolon
r_int
id|clear
op_assign
l_int|0
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
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
id|rts
)paren
id|set
op_or_assign
id|TIOCM_RTS
suffix:semicolon
r_else
id|clear
op_or_assign
id|TIOCM_RTS
suffix:semicolon
r_if
c_cond
(paren
id|dtr
)paren
id|set
op_or_assign
id|TIOCM_DTR
suffix:semicolon
r_else
id|clear
op_or_assign
id|TIOCM_DTR
suffix:semicolon
multiline_comment|/*&n;&t; * We can&squot;t use ioctl() because it expects a non-null file structure,&n;&t; * and we don&squot;t have that here.&n;&t; * This function is not yet defined for all tty driver, so&n;&t; * let&squot;s be careful... Jean II&n;&t; */
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;tty-&gt;driver-&gt;tiocmset
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|priv-&gt;tty-&gt;driver
op_member_access_from_pointer
id|tiocmset
c_func
(paren
id|priv-&gt;tty
comma
l_int|NULL
comma
id|set
comma
id|clear
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------- */
multiline_comment|/* called from sir_dev when there is more data to send&n; * context is either netdev-&gt;hard_xmit or some transmit-completion bh&n; * i.e. we are under spinlock here and must not sleep.&n; */
DECL|function|irtty_do_write
r_static
r_int
id|irtty_do_write
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_const
r_int
r_char
op_star
id|ptr
comma
r_int
id|len
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
id|writelen
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|tty
op_assign
id|priv-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty-&gt;driver-&gt;write
)paren
r_return
l_int|0
suffix:semicolon
id|tty-&gt;flags
op_or_assign
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;write_room
)paren
(brace
id|writelen
op_assign
id|tty-&gt;driver
op_member_access_from_pointer
id|write_room
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writelen
OG
id|len
)paren
id|writelen
op_assign
id|len
suffix:semicolon
)brace
r_else
id|writelen
op_assign
id|len
suffix:semicolon
r_return
id|tty-&gt;driver
op_member_access_from_pointer
id|write
c_func
(paren
id|tty
comma
id|ptr
comma
id|writelen
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------- */
multiline_comment|/* irda line discipline callbacks */
multiline_comment|/* &n; *  Function irtty_receive_buf( tty, cp, count)&n; *&n; *    Handle the &squot;receiver data ready&squot; interrupt.  This function is called&n; *    by the &squot;tty_io&squot; module in the kernel when a block of IrDA data has&n; *    been received, which can now be decapsulated and delivered for&n; *    further processing &n; *&n; * calling context depends on underlying driver and tty-&gt;low_latency!&n; * for example (low_latency: 1 / 0):&n; * serial.c:&t;uart-interrupt / softint&n; * usbserial:&t;urb-complete-interrupt / softint&n; */
DECL|function|irtty_receive_buf
r_static
r_void
id|irtty_receive_buf
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_const
r_int
r_char
op_star
id|cp
comma
r_char
op_star
id|fp
comma
r_int
id|count
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
suffix:semicolon
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|tty-&gt;disc_data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|count
op_eq
l_int|0
)paren
)paren
multiline_comment|/* yes, this happens */
r_return
suffix:semicolon
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|IRDA_WARNING
c_func
(paren
l_string|&quot;%s(), not ready yet!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* &n;&t;&t; *  Characters received with a parity error, etc?&n;&t;&t; */
r_if
c_cond
(paren
id|fp
op_logical_and
op_star
id|fp
op_increment
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Framing or parity error!&bslash;n&quot;
)paren
suffix:semicolon
id|sirdev_receive
c_func
(paren
id|dev
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* notify sir_dev (updating stats) */
r_return
suffix:semicolon
)brace
)brace
id|sirdev_receive
c_func
(paren
id|dev
comma
id|cp
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irtty_receive_room (tty)&n; *&n; *    Used by the TTY to find out how much data we can receive at a time&n; * &n;*/
DECL|function|irtty_receive_room
r_static
r_int
id|irtty_receive_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|tty-&gt;disc_data
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
l_int|0
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
l_int|0
suffix:semicolon
)paren
suffix:semicolon
r_return
l_int|65536
suffix:semicolon
multiline_comment|/* We can handle an infinite amount of data. :-) */
)brace
multiline_comment|/*&n; * Function irtty_write_wakeup (tty)&n; *&n; *    Called by the driver when there&squot;s room for more data.  If we have&n; *    more packets to send, we send them here.&n; *&n; */
DECL|function|irtty_write_wakeup
r_static
r_void
id|irtty_write_wakeup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|tty-&gt;disc_data
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|tty-&gt;flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;dev
)paren
id|sirdev_write_complete
c_func
(paren
id|priv-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------- */
multiline_comment|/*&n; * Function irtty_stop_receiver (tty, stop)&n; *&n; */
DECL|function|irtty_stop_receiver
r_static
r_inline
r_void
id|irtty_stop_receiver
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|stop
)paren
(brace
r_struct
id|termios
id|old_termios
suffix:semicolon
r_int
id|cflag
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|old_termios
op_assign
op_star
(paren
id|tty-&gt;termios
)paren
suffix:semicolon
id|cflag
op_assign
id|tty-&gt;termios-&gt;c_cflag
suffix:semicolon
r_if
c_cond
(paren
id|stop
)paren
id|cflag
op_and_assign
op_complement
id|CREAD
suffix:semicolon
r_else
id|cflag
op_or_assign
id|CREAD
suffix:semicolon
id|tty-&gt;termios-&gt;c_cflag
op_assign
id|cflag
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;set_termios
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|set_termios
c_func
(paren
id|tty
comma
op_amp
id|old_termios
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************/
multiline_comment|/* serialize ldisc open/close with sir_dev */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|irtty_sem
)paren
suffix:semicolon
multiline_comment|/* notifier from sir_dev when irda% device gets opened (ifup) */
DECL|function|irtty_start_dev
r_static
r_int
id|irtty_start_dev
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* serialize with ldisc open/close */
id|down
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|priv
op_logical_or
id|priv-&gt;magic
op_ne
id|IRTTY_MAGIC
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
r_return
op_minus
id|ESTALE
suffix:semicolon
)brace
id|tty
op_assign
id|priv-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;start
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|start
c_func
(paren
id|tty
)paren
suffix:semicolon
multiline_comment|/* Make sure we can receive more data */
id|irtty_stop_receiver
c_func
(paren
id|tty
comma
id|FALSE
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* notifier from sir_dev when irda% device gets closed (ifdown) */
DECL|function|irtty_stop_dev
r_static
r_int
id|irtty_stop_dev
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* serialize with ldisc open/close */
id|down
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|priv
op_logical_or
id|priv-&gt;magic
op_ne
id|IRTTY_MAGIC
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
r_return
op_minus
id|ESTALE
suffix:semicolon
)brace
id|tty
op_assign
id|priv-&gt;tty
suffix:semicolon
multiline_comment|/* Make sure we don&squot;t receive more data */
id|irtty_stop_receiver
c_func
(paren
id|tty
comma
id|TRUE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;stop
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|stop
c_func
(paren
id|tty
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------- */
DECL|variable|sir_tty_drv
r_static
r_struct
id|sir_driver
id|sir_tty_drv
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
l_string|&quot;sir_tty&quot;
comma
dot
id|start_dev
op_assign
id|irtty_start_dev
comma
dot
id|stop_dev
op_assign
id|irtty_stop_dev
comma
dot
id|do_write
op_assign
id|irtty_do_write
comma
dot
id|chars_in_buffer
op_assign
id|irtty_chars_in_buffer
comma
dot
id|wait_until_sent
op_assign
id|irtty_wait_until_sent
comma
dot
id|set_speed
op_assign
id|irtty_change_speed
comma
dot
id|set_dtr_rts
op_assign
id|irtty_set_dtr_rts
comma
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------- */
multiline_comment|/*&n; * Function irtty_ioctl (tty, file, cmd, arg)&n; *&n; *     The Swiss army knife of system calls :-)&n; *&n; */
DECL|function|irtty_ioctl
r_static
r_int
id|irtty_ioctl
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
id|irtty_info
(brace
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
)brace
id|info
suffix:semicolon
r_struct
id|sir_dev
op_star
id|dev
suffix:semicolon
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|tty-&gt;disc_data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENODEV
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
op_minus
id|EBADR
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s(cmd=0x%X)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|cmd
)paren
suffix:semicolon
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|dev
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TCGETS
suffix:colon
r_case
id|TCGETA
suffix:colon
id|err
op_assign
id|n_tty_ioctl
c_func
(paren
id|tty
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRTTY_IOCTDONGLE
suffix:colon
multiline_comment|/* this call blocks for completion */
id|err
op_assign
id|sirdev_set_dongle
c_func
(paren
id|dev
comma
(paren
id|IRDA_DONGLE
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRTTY_IOCGET
suffix:colon
id|IRDA_ASSERT
c_func
(paren
id|dev-&gt;netdev
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
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
id|strncpy
c_func
(paren
id|info.name
comma
id|dev-&gt;netdev-&gt;name
comma
r_sizeof
(paren
id|info.name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* &n; *  Function irtty_open(tty)&n; *&n; *    This function is called by the TTY module when the IrDA line&n; *    discipline is called for.  Because we are sure the tty line exists,&n; *    we only have to link it to a free IrDA channel.  &n; */
DECL|function|irtty_open
r_static
r_int
id|irtty_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
suffix:semicolon
r_struct
id|sirtty_cb
op_star
id|priv
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Module stuff handled via irda_ldisc.owner - Jean II */
multiline_comment|/* First make sure we&squot;re not already connected. */
r_if
c_cond
(paren
id|tty-&gt;disc_data
op_ne
l_int|NULL
)paren
(brace
id|priv
op_assign
id|tty-&gt;disc_data
suffix:semicolon
r_if
c_cond
(paren
id|priv
op_logical_and
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
)paren
(brace
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|tty-&gt;disc_data
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ### */
)brace
multiline_comment|/* stop the underlying  driver */
id|irtty_stop_receiver
c_func
(paren
id|tty
comma
id|TRUE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;stop
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|stop
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;flush_buffer
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
multiline_comment|/* apply mtt override */
id|sir_tty_drv.qos_mtt_bits
op_assign
id|qos_mtt_bits
suffix:semicolon
multiline_comment|/* get a sir device instance for this driver */
id|dev
op_assign
id|sirdev_get_instance
c_func
(paren
op_amp
id|sir_tty_drv
comma
id|tty-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* allocate private device info block */
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
r_goto
id|out_put
suffix:semicolon
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|priv
)paren
)paren
suffix:semicolon
id|priv-&gt;magic
op_assign
id|IRTTY_MAGIC
suffix:semicolon
id|priv-&gt;tty
op_assign
id|tty
suffix:semicolon
id|priv-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* serialize with start_dev - in case we were racing with ifup */
id|down
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
id|priv
suffix:semicolon
id|tty-&gt;disc_data
op_assign
id|priv
suffix:semicolon
id|up
c_func
(paren
op_amp
id|irtty_sem
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s - %s: irda line discipline opened&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|tty-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_put
suffix:colon
id|sirdev_put_instance
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* &n; *  Function irtty_close (tty)&n; *&n; *    Close down a IrDA channel. This means flushing out any pending queues,&n; *    and then restoring the TTY line discipline to what it was before it got&n; *    hooked to IrDA (which usually is TTY again).  &n; */
DECL|function|irtty_close
r_static
r_void
id|irtty_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|sirtty_cb
op_star
id|priv
op_assign
id|tty-&gt;disc_data
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|priv-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Hm, with a dongle attached the dongle driver wants&n;&t; * to close the dongle - which requires the use of&n;&t; * some tty write and/or termios or ioctl operations.&n;&t; * Are we allowed to call those when already requested&n;&t; * to shutdown the ldisc?&n;&t; * If not, we should somehow mark the dev being staled.&n;&t; * Question remains, how to close the dongle in this case...&n;&t; * For now let&squot;s assume we are granted to issue tty driver calls&n;&t; * until we return here from the ldisc close. I&squot;m just wondering&n;&t; * how this behaves with hotpluggable serial hardware like&n;&t; * rs232-pcmcia card or usb-serial...&n;&t; *&n;&t; * priv-&gt;tty = NULL?;&n;&t; */
multiline_comment|/* we are dead now */
id|tty-&gt;disc_data
op_assign
l_int|NULL
suffix:semicolon
id|sirdev_put_instance
c_func
(paren
id|priv-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Stop tty */
id|irtty_stop_receiver
c_func
(paren
id|tty
comma
id|TRUE
)paren
suffix:semicolon
id|tty-&gt;flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver-&gt;stop
)paren
id|tty-&gt;driver
op_member_access_from_pointer
id|stop
c_func
(paren
id|tty
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s - %s: irda line discipline closed&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|tty-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------- */
DECL|variable|irda_ldisc
r_static
r_struct
id|tty_ldisc
id|irda_ldisc
op_assign
(brace
dot
id|magic
op_assign
id|TTY_LDISC_MAGIC
comma
dot
id|name
op_assign
l_string|&quot;irda&quot;
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|open
op_assign
id|irtty_open
comma
dot
id|close
op_assign
id|irtty_close
comma
dot
id|read
op_assign
l_int|NULL
comma
dot
id|write
op_assign
l_int|NULL
comma
dot
id|ioctl
op_assign
id|irtty_ioctl
comma
dot
id|poll
op_assign
l_int|NULL
comma
dot
id|receive_buf
op_assign
id|irtty_receive_buf
comma
dot
id|receive_room
op_assign
id|irtty_receive_room
comma
dot
id|write_wakeup
op_assign
id|irtty_write_wakeup
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------- */
DECL|function|irtty_sir_init
r_static
r_int
id|__init
id|irtty_sir_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|tty_register_ldisc
c_func
(paren
id|N_IRDA
comma
op_amp
id|irda_ldisc
)paren
)paren
op_ne
l_int|0
)paren
id|IRDA_ERROR
c_func
(paren
l_string|&quot;IrDA: can&squot;t register line discipline (err = %d)&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|irtty_sir_cleanup
r_static
r_void
id|__exit
id|irtty_sir_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|tty_register_ldisc
c_func
(paren
id|N_IRDA
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|IRDA_ERROR
c_func
(paren
l_string|&quot;%s(), can&squot;t unregister line discipline (err = %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
)paren
suffix:semicolon
)brace
)brace
DECL|variable|irtty_sir_init
id|module_init
c_func
(paren
id|irtty_sir_init
)paren
suffix:semicolon
DECL|variable|irtty_sir_cleanup
id|module_exit
c_func
(paren
id|irtty_sir_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dag Brattli &lt;dagb@cs.uit.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IrDA TTY device driver&quot;
)paren
suffix:semicolon
DECL|variable|N_IRDA
id|MODULE_ALIAS_LDISC
c_func
(paren
id|N_IRDA
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
