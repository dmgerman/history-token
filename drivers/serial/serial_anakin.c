multiline_comment|/*&n; *  linux/drivers/char/serial_anakin.c&n; *&n; *  Based on driver for AMBA serial ports, by ARM Limited,&n; *  Deep Blue Solutions Ltd., Linus Torvalds and Theodore Ts&squot;o.&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; *  Copyright (C) 2001 Blue Mug, Inc. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   20-Apr-2001 TTC&t;Created&n; *   05-May-2001 W/TTC&t;Updated for serial_core.c&n; *   27-Jun-2001 jonm&t;Minor changes; add mctrl support, switch to &n; *   &t;&t;&t;SA_INTERRUPT. Works reliably now. No longer requires&n; *   &t;&t;&t;changes to the serial_core API.&n; *&n; *  $Id: serial_anakin.c,v 1.27 2002/07/20 17:10:03 rmk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/arch/serial_reg.h&gt;
DECL|macro|UART_NR
mdefine_line|#define UART_NR&t;&t;&t;5
DECL|macro|SERIAL_ANAKIN_NAME
mdefine_line|#define SERIAL_ANAKIN_NAME&t;&quot;ttyAN&quot;
DECL|macro|SERIAL_ANAKIN_MAJOR
mdefine_line|#define SERIAL_ANAKIN_MAJOR&t;204
DECL|macro|SERIAL_ANAKIN_MINOR
mdefine_line|#define SERIAL_ANAKIN_MINOR&t;32
DECL|variable|txenable
r_static
r_int
r_int
id|txenable
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/* Software interrupt register */
r_static
r_inline
r_int
r_int
DECL|function|anakin_in
id|anakin_in
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|offset
)paren
(brace
r_return
id|__raw_readl
c_func
(paren
id|port-&gt;base
op_plus
id|offset
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|anakin_out
id|anakin_out
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|value
)paren
(brace
id|__raw_writel
c_func
(paren
id|value
comma
id|port-&gt;base
op_plus
id|offset
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_stop_tx
id|anakin_stop_tx
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|tty_stop
)paren
(brace
id|txenable
(braket
id|port-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|anakin_transmit_buffer
id|anakin_transmit_buffer
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_struct
id|circ_buf
op_star
id|xmit
op_assign
op_amp
id|port-&gt;info-&gt;xmit
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
)paren
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x14
comma
id|xmit-&gt;buf
(braket
id|xmit-&gt;tail
)braket
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_or
id|SENDREQUEST
)paren
suffix:semicolon
id|xmit-&gt;tail
op_assign
(paren
id|xmit-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
id|UART_XMIT_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|port-&gt;icount.tx
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|uart_circ_empty
c_func
(paren
id|xmit
)paren
)paren
id|anakin_stop_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|anakin_transmit_x_char
id|anakin_transmit_x_char
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x14
comma
id|port-&gt;x_char
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_or
id|SENDREQUEST
)paren
suffix:semicolon
id|port-&gt;icount.tx
op_increment
suffix:semicolon
id|port-&gt;x_char
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_start_tx
id|anakin_start_tx
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|tty_start
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// is it this... or below
r_if
c_cond
(paren
op_logical_neg
id|txenable
(braket
id|port-&gt;irq
)braket
)paren
(brace
id|txenable
(braket
id|port-&gt;irq
)braket
op_assign
id|TXENABLE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
)paren
)paren
(brace
id|anakin_transmit_buffer
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_stop_rx
id|anakin_stop_rx
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|RXRELEASE
)paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x14
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_or
id|BLOCKRX
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_enable_ms
id|anakin_enable_ms
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|anakin_rx_chars
id|anakin_rx_chars
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
r_int
id|ch
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|port-&gt;info-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|RXRELEASE
)paren
)paren
r_return
suffix:semicolon
id|ch
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x14
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;flip.count
OL
id|TTY_FLIPBUF_SIZE
)paren
(brace
op_star
id|tty-&gt;flip.char_buf_ptr
op_increment
op_assign
id|ch
suffix:semicolon
op_star
id|tty-&gt;flip.flag_buf_ptr
op_increment
op_assign
id|TTY_NORMAL
suffix:semicolon
id|port-&gt;icount.rx
op_increment
suffix:semicolon
id|tty-&gt;flip.count
op_increment
suffix:semicolon
)brace
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|anakin_overrun_chars
id|anakin_overrun_chars
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
r_int
id|ch
suffix:semicolon
id|ch
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x14
)paren
suffix:semicolon
id|port-&gt;icount.overrun
op_increment
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|anakin_tx_chars
id|anakin_tx_chars
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_struct
id|circ_buf
op_star
id|xmit
op_assign
op_amp
id|port-&gt;info-&gt;xmit
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;x_char
)paren
(brace
id|anakin_transmit_x_char
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uart_circ_empty
c_func
(paren
id|xmit
)paren
op_logical_or
id|uart_tx_stopped
c_func
(paren
id|port
)paren
)paren
(brace
id|anakin_stop_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|anakin_transmit_buffer
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uart_circ_chars_pending
c_func
(paren
id|xmit
)paren
OL
id|WAKEUP_CHARS
)paren
id|uart_event
c_func
(paren
id|port
comma
id|EVT_WRITE_WAKEUP
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_int
id|anakin_int
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
r_struct
id|uart_port
op_star
id|port
op_assign
id|dev_id
suffix:semicolon
id|status
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x1c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RX
)paren
id|anakin_rx_chars
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|OVERRUN
)paren
id|anakin_overrun_chars
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|txenable
(braket
id|port-&gt;irq
)braket
op_logical_and
(paren
id|status
op_amp
id|TX
)paren
)paren
id|anakin_tx_chars
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|anakin_tx_empty
id|anakin_tx_empty
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
ques
c_cond
id|TIOCSER_TEMT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|anakin_get_mctrl
id|anakin_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|status
op_or_assign
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|CTS
ques
c_cond
id|TIOCM_CTS
suffix:colon
l_int|0
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_amp
id|DCD
ques
c_cond
id|TIOCM_CAR
suffix:colon
l_int|0
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_amp
id|DTR
ques
c_cond
id|TIOCM_DTR
suffix:colon
l_int|0
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_amp
id|RTS
ques
c_cond
id|TIOCM_RTS
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_set_mctrl
id|anakin_set_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|mctrl
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
id|status
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|status
op_or_assign
id|RTS
suffix:semicolon
r_else
id|status
op_and_assign
op_complement
id|RTS
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_CAR
)paren
id|status
op_or_assign
id|DCD
suffix:semicolon
r_else
id|status
op_and_assign
op_complement
id|DCD
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|status
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_break_ctl
id|anakin_break_ctl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|break_state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|break_state
op_eq
op_minus
l_int|1
)paren
id|status
op_or_assign
id|SETBREAK
suffix:semicolon
r_else
id|status
op_and_assign
op_complement
id|SETBREAK
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x20
comma
id|status
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|anakin_startup
r_static
r_int
id|anakin_startup
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
r_int
id|read
comma
id|write
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the IRQ&n;&t; */
id|retval
op_assign
id|request_irq
c_func
(paren
id|port-&gt;irq
comma
id|anakin_int
comma
id|SA_INTERRUPT
comma
l_string|&quot;serial_anakin&quot;
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/*&n;&t; * initialise the old status of the modem signals&n;&t; */
id|port-&gt;old_status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Finally, disable IRQ and softIRQs for first byte)&n;&t; */
id|txenable
(braket
id|port-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
id|read
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
suffix:semicolon
id|write
op_assign
(paren
id|read
op_amp
op_complement
(paren
id|RTS
op_or
id|DTR
op_or
id|BLOCKRX
)paren
)paren
op_or
id|IRQENABLE
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|write
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|anakin_shutdown
r_static
r_void
id|anakin_shutdown
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
multiline_comment|/*&n;&t; * Free the interrupt&n;&t; */
id|free_irq
c_func
(paren
id|port-&gt;irq
comma
id|port
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * disable all interrupts, disable the port&n;&t; */
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_amp
op_complement
id|IRQENABLE
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_change_speed
id|anakin_change_speed
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|cflag
comma
r_int
r_int
id|iflag
comma
r_int
r_int
id|quot
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
)paren
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x10
comma
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
op_complement
id|PRESCALER
)paren
op_or
(paren
id|quot
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
singleline_comment|//parity always set to none
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_amp
op_complement
id|PARITY
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|anakin_type
r_static
r_const
r_char
op_star
id|anakin_type
c_func
(paren
r_struct
id|port
op_star
id|port
)paren
(brace
r_return
id|port-&gt;type
op_eq
id|PORT_ANAKIN
ques
c_cond
l_string|&quot;ANAKIN&quot;
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|variable|anakin_pops
r_static
r_struct
id|uart_ops
id|anakin_pops
op_assign
(brace
id|tx_empty
suffix:colon
id|anakin_tx_empty
comma
id|set_mctrl
suffix:colon
id|anakin_set_mctrl
comma
id|get_mctrl
suffix:colon
id|anakin_get_mctrl
comma
id|stop_tx
suffix:colon
id|anakin_stop_tx
comma
id|start_tx
suffix:colon
id|anakin_start_tx
comma
id|stop_rx
suffix:colon
id|anakin_stop_rx
comma
id|enable_ms
suffix:colon
id|anakin_enable_ms
comma
id|break_ctl
suffix:colon
id|anakin_break_ctl
comma
id|startup
suffix:colon
id|anakin_startup
comma
id|shutdown
suffix:colon
id|anakin_shutdown
comma
id|change_speed
suffix:colon
id|anakin_change_speed
comma
id|type
suffix:colon
id|anakin_type
comma
)brace
suffix:semicolon
DECL|variable|anakin_ports
r_static
r_struct
id|uart_port
id|anakin_ports
(braket
id|UART_NR
)braket
op_assign
(brace
(brace
id|base
suffix:colon
id|IO_BASE
op_plus
id|UART0
comma
id|irq
suffix:colon
id|IRQ_UART0
comma
id|uartclk
suffix:colon
l_int|3686400
comma
id|fifosize
suffix:colon
l_int|0
comma
id|ops
suffix:colon
op_amp
id|anakin_pops
comma
id|flags
suffix:colon
id|ASYNC_BOOT_AUTOCONF
comma
id|line
suffix:colon
l_int|0
comma
)brace
comma
(brace
id|base
suffix:colon
id|IO_BASE
op_plus
id|UART1
comma
id|irq
suffix:colon
id|IRQ_UART1
comma
id|uartclk
suffix:colon
l_int|3686400
comma
id|fifosize
suffix:colon
l_int|0
comma
id|ops
suffix:colon
op_amp
id|anakin_pops
comma
id|flags
suffix:colon
id|ASYNC_BOOT_AUTOCONF
comma
id|line
suffix:colon
l_int|1
comma
)brace
comma
(brace
id|base
suffix:colon
id|IO_BASE
op_plus
id|UART2
comma
id|irq
suffix:colon
id|IRQ_UART2
comma
id|uartclk
suffix:colon
l_int|3686400
comma
id|fifosize
suffix:colon
l_int|0
comma
id|ops
suffix:colon
op_amp
id|anakin_pops
comma
id|flags
suffix:colon
id|ASYNC_BOOT_AUTOCONF
comma
id|line
suffix:colon
l_int|2
comma
)brace
comma
(brace
id|base
suffix:colon
id|IO_BASE
op_plus
id|UART3
comma
id|irq
suffix:colon
id|IRQ_UART3
comma
id|uartclk
suffix:colon
l_int|3686400
comma
id|fifosize
suffix:colon
l_int|0
comma
id|ops
suffix:colon
op_amp
id|anakin_pops
comma
id|flags
suffix:colon
id|ASYNC_BOOT_AUTOCONF
comma
id|line
suffix:colon
l_int|3
comma
)brace
comma
(brace
id|base
suffix:colon
id|IO_BASE
op_plus
id|UART4
comma
id|irq
suffix:colon
id|IRQ_UART4
comma
id|uartclk
suffix:colon
l_int|3686400
comma
id|fifosize
suffix:colon
l_int|0
comma
id|ops
suffix:colon
op_amp
id|anakin_pops
comma
id|flags
suffix:colon
id|ASYNC_BOOT_AUTOCONF
comma
id|line
suffix:colon
l_int|4
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_ANAKIN_CONSOLE
r_static
r_void
DECL|function|anakin_console_write
id|anakin_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|uart_port
op_star
id|port
op_assign
op_amp
id|anakin_ports
(braket
id|co-&gt;index
)braket
suffix:semicolon
r_int
r_int
id|flags
comma
id|status
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *&t;First save the status then disable the interrupts&n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|status
op_amp
op_complement
id|IRQENABLE
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now, do each character&n;&t; */
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
comma
id|s
op_increment
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Send the character out.&n;&t;&t; *&t;If a LF, also do CR...&n;&t;&t; */
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x14
comma
op_star
id|s
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_or
id|SENDREQUEST
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_int|10
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
)paren
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x14
comma
l_int|13
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_or
id|SENDREQUEST
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Finally, wait for transmitter to become empty&n;&t; *&t;and restore the interrupts&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|TXEMPTY
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQENABLE
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|anakin_out
c_func
(paren
id|port
comma
l_int|0x18
comma
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_or
id|IRQENABLE
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
id|kdev_t
DECL|function|anakin_console_device
id|anakin_console_device
c_func
(paren
r_struct
id|console
op_star
id|co
)paren
(brace
r_return
id|mk_kdev
c_func
(paren
id|SERIAL_ANAKIN_MAJOR
comma
id|SERIAL_ANAKIN_MINOR
op_plus
id|co-&gt;index
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the current UART setup.&n; */
r_static
r_void
id|__init
DECL|function|anakin_console_get_options
id|anakin_console_get_options
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
op_star
id|baud
comma
r_int
op_star
id|parity
comma
r_int
op_star
id|bits
)paren
(brace
r_int
id|paritycode
suffix:semicolon
op_star
id|baud
op_assign
id|GETBAUD
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x10
)paren
op_amp
id|PRESCALER
)paren
suffix:semicolon
id|paritycode
op_assign
id|GETPARITY
c_func
(paren
id|anakin_in
c_func
(paren
id|port
comma
l_int|0x18
)paren
op_amp
id|PARITY
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|paritycode
)paren
(brace
r_case
id|NONEPARITY
suffix:colon
op_star
id|parity
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ODDPARITY
suffix:colon
op_star
id|parity
op_assign
l_char|&squot;o&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EVENPARITY
suffix:colon
op_star
id|parity
op_assign
l_char|&squot;e&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|bits
op_assign
l_int|8
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|anakin_console_setup
id|anakin_console_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
r_struct
id|uart_port
op_star
id|port
suffix:semicolon
r_int
id|baud
op_assign
id|CONFIG_ANAKIN_DEFAULT_BAUDRATE
suffix:semicolon
r_int
id|bits
op_assign
l_int|8
suffix:semicolon
r_int
id|parity
op_assign
l_char|&squot;n&squot;
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether an invalid uart number has been specified, and&n;&t; * if so, search for the first available port that does have&n;&t; * console support.&n;&t; */
r_if
c_cond
(paren
id|co-&gt;index
op_ge
id|UART_NR
)paren
id|co-&gt;index
op_assign
l_int|0
suffix:semicolon
id|port
op_assign
op_amp
id|anakin_ports
(braket
id|co-&gt;index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|options
)paren
id|uart_parse_options
c_func
(paren
id|options
comma
op_amp
id|baud
comma
op_amp
id|parity
comma
op_amp
id|bits
)paren
suffix:semicolon
r_else
id|anakin_console_get_options
c_func
(paren
id|port
comma
op_amp
id|baud
comma
op_amp
id|parity
comma
op_amp
id|bits
)paren
suffix:semicolon
r_return
id|uart_set_options
c_func
(paren
id|port
comma
id|co
comma
id|baud
comma
id|parity
comma
id|bits
)paren
suffix:semicolon
)brace
DECL|variable|anakin_console
r_static
r_struct
id|console
id|anakin_console
op_assign
(brace
id|name
suffix:colon
id|SERIAL_ANAKIN_NAME
comma
id|write
suffix:colon
id|anakin_console_write
comma
id|device
suffix:colon
id|anakin_console_device
comma
id|setup
suffix:colon
id|anakin_console_setup
comma
id|flags
suffix:colon
id|CON_PRINTBUFFER
comma
id|index
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
r_void
id|__init
DECL|function|anakin_console_init
id|anakin_console_init
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|anakin_console
)paren
suffix:semicolon
)brace
DECL|macro|ANAKIN_CONSOLE
mdefine_line|#define ANAKIN_CONSOLE&t;&t;&amp;anakin_console
macro_line|#else
DECL|macro|ANAKIN_CONSOLE
mdefine_line|#define ANAKIN_CONSOLE&t;&t;NULL
macro_line|#endif
DECL|variable|anakin_reg
r_static
r_struct
id|uart_register
id|anakin_reg
op_assign
(brace
id|driver_name
suffix:colon
id|SERIAL_ANAKIN_NAME
comma
id|dev_name
suffix:colon
id|SERIAL_ANAKIN_NAME
comma
id|major
suffix:colon
id|SERIAL_ANAKIN_MAJOR
comma
id|minor
suffix:colon
id|SERIAL_ANAKIN_MINOR
comma
id|nr
suffix:colon
id|UART_NR
comma
id|cons
suffix:colon
id|ANAKIN_CONSOLE
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|anakin_init
id|anakin_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Serial: Anakin driver $Revision: 1.27 $&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|uart_register_driver
c_func
(paren
op_amp
id|anakin_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|UART_NR
suffix:semicolon
id|i
op_increment
)paren
id|uart_add_one_port
c_func
(paren
op_amp
id|anakin_reg
comma
op_amp
id|anakin_ports
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|anakin_init
id|__initcall
c_func
(paren
id|anakin_init
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Anakin serial driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Tak-Shing Chan &lt;chan@aleph1.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;ttyAN&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
eof