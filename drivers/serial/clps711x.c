multiline_comment|/*&n; *  linux/drivers/char/clps711x.c&n; *&n; *  Driver for CLPS711x serial ports&n; *&n; *  Based on drivers/char/serial.c, by Linus Torvalds, Theodore Ts&squot;o.&n; *&n; *  Copyright 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  $Id: clps711x.c,v 1.42 2002/07/28 10:03:28 rmk Exp $&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#if defined(CONFIG_SERIAL_CLPS711X_CONSOLE) &amp;&amp; defined(CONFIG_MAGIC_SYSRQ)
DECL|macro|SUPPORT_SYSRQ
mdefine_line|#define SUPPORT_SYSRQ
macro_line|#endif
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
DECL|macro|UART_NR
mdefine_line|#define UART_NR&t;&t;2
macro_line|#ifndef CONFIG_SERIAL_CLPS711X_OLD_NAME
DECL|macro|SERIAL_CLPS711X_MAJOR
mdefine_line|#define SERIAL_CLPS711X_MAJOR&t;204
DECL|macro|SERIAL_CLPS711X_MINOR
mdefine_line|#define SERIAL_CLPS711X_MINOR&t;40
DECL|macro|SERIAL_CLPS711X_NR
mdefine_line|#define SERIAL_CLPS711X_NR&t;UART_NR
macro_line|#else
macro_line|#warning The old names/device number for this driver if compatabity is needed
DECL|macro|SERIAL_CLPS711X_MAJOR
mdefine_line|#define SERIAL_CLPS711X_MAJOR   204
DECL|macro|SERIAL_CLPS711X_MINOR
mdefine_line|#define SERIAL_CLPS711X_MINOR   16
DECL|macro|SERIAL_CLPS711X_NR
mdefine_line|#define SERIAL_CLPS711X_NR      UART_NR
macro_line|#endif
multiline_comment|/*&n; * We use the relevant SYSCON register as a base address for these ports.&n; */
DECL|macro|UBRLCR
mdefine_line|#define UBRLCR(port)&t;&t;((port)-&gt;iobase + UBRLCR1 - SYSCON1)
DECL|macro|UARTDR
mdefine_line|#define UARTDR(port)&t;&t;((port)-&gt;iobase + UARTDR1 - SYSCON1)
DECL|macro|SYSFLG
mdefine_line|#define SYSFLG(port)&t;&t;((port)-&gt;iobase + SYSFLG1 - SYSCON1)
DECL|macro|SYSCON
mdefine_line|#define SYSCON(port)&t;&t;((port)-&gt;iobase + SYSCON1 - SYSCON1)
DECL|macro|TX_IRQ
mdefine_line|#define TX_IRQ(port)&t;&t;((port)-&gt;irq)
DECL|macro|RX_IRQ
mdefine_line|#define RX_IRQ(port)&t;&t;((port)-&gt;irq + 1)
DECL|macro|UART_ANY_ERR
mdefine_line|#define UART_ANY_ERR&t;&t;(UARTDR_FRMERR | UARTDR_PARERR | UARTDR_OVERR)
DECL|macro|tx_enabled
mdefine_line|#define tx_enabled(port)&t;((port)-&gt;unused[0])
r_static
r_void
DECL|function|clps711xuart_stop_tx
id|clps711xuart_stop_tx
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
r_if
c_cond
(paren
id|tx_enabled
c_func
(paren
id|port
)paren
)paren
(brace
id|disable_irq
c_func
(paren
id|TX_IRQ
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|tx_enabled
c_func
(paren
id|port
)paren
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|clps711xuart_start_tx
id|clps711xuart_start_tx
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
r_if
c_cond
(paren
op_logical_neg
id|tx_enabled
c_func
(paren
id|port
)paren
)paren
(brace
id|enable_irq
c_func
(paren
id|TX_IRQ
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|tx_enabled
c_func
(paren
id|port
)paren
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|clps711xuart_stop_rx
r_static
r_void
id|clps711xuart_stop_rx
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|disable_irq
c_func
(paren
id|RX_IRQ
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|clps711xuart_enable_ms
r_static
r_void
id|clps711xuart_enable_ms
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
)brace
DECL|function|clps711xuart_int_rx
r_static
r_void
id|clps711xuart_int_rx
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
r_struct
id|uart_port
op_star
id|port
op_assign
id|dev_id
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|port-&gt;info-&gt;tty
suffix:semicolon
r_int
r_int
id|status
comma
id|ch
comma
id|flg
comma
id|ignored
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|clps_readl
c_func
(paren
id|SYSFLG
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|status
op_amp
id|SYSFLG_URXFE
)paren
)paren
(brace
id|ch
op_assign
id|clps_readl
c_func
(paren
id|UARTDR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;flip.count
op_ge
id|TTY_FLIPBUF_SIZE
)paren
r_goto
id|ignore_char
suffix:semicolon
id|port-&gt;icount.rx
op_increment
suffix:semicolon
id|flg
op_assign
id|TTY_NORMAL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note that the error handling code is&n;&t;&t; * out of the main execution path&n;&t;&t; */
r_if
c_cond
(paren
id|ch
op_amp
id|UART_ANY_ERR
)paren
r_goto
id|handle_error
suffix:semicolon
r_if
c_cond
(paren
id|uart_handle_sysrq_char
c_func
(paren
id|port
comma
id|ch
comma
id|regs
)paren
)paren
r_goto
id|ignore_char
suffix:semicolon
id|error_return
suffix:colon
op_star
id|tty-&gt;flip.flag_buf_ptr
op_increment
op_assign
id|flg
suffix:semicolon
op_star
id|tty-&gt;flip.char_buf_ptr
op_increment
op_assign
id|ch
suffix:semicolon
id|tty-&gt;flip.count
op_increment
suffix:semicolon
id|ignore_char
suffix:colon
id|status
op_assign
id|clps_readl
c_func
(paren
id|SYSFLG
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
suffix:semicolon
id|handle_error
suffix:colon
r_if
c_cond
(paren
id|ch
op_amp
id|UARTDR_PARERR
)paren
id|port-&gt;icount.parity
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ch
op_amp
id|UARTDR_FRMERR
)paren
id|port-&gt;icount.frame
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_amp
id|UARTDR_OVERR
)paren
id|port-&gt;icount.overrun
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_amp
id|port-&gt;ignore_status_mask
)paren
(brace
r_if
c_cond
(paren
op_increment
id|ignored
OG
l_int|100
)paren
r_goto
id|out
suffix:semicolon
r_goto
id|ignore_char
suffix:semicolon
)brace
id|ch
op_and_assign
id|port-&gt;read_status_mask
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_amp
id|UARTDR_PARERR
)paren
id|flg
op_assign
id|TTY_PARITY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ch
op_amp
id|UARTDR_FRMERR
)paren
id|flg
op_assign
id|TTY_FRAME
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_amp
id|UARTDR_OVERR
)paren
(brace
multiline_comment|/*&n;&t;&t; * CHECK: does overrun affect the current character?&n;&t;&t; * ASSUMPTION: it does not.&n;&t;&t; */
op_star
id|tty-&gt;flip.flag_buf_ptr
op_increment
op_assign
id|flg
suffix:semicolon
op_star
id|tty-&gt;flip.char_buf_ptr
op_increment
op_assign
id|ch
suffix:semicolon
id|tty-&gt;flip.count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;flip.count
op_ge
id|TTY_FLIPBUF_SIZE
)paren
r_goto
id|ignore_char
suffix:semicolon
id|ch
op_assign
l_int|0
suffix:semicolon
id|flg
op_assign
id|TTY_OVERRUN
suffix:semicolon
)brace
macro_line|#ifdef SUPPORT_SYSRQ
id|port-&gt;sysrq
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_goto
id|error_return
suffix:semicolon
)brace
DECL|function|clps711xuart_int_tx
r_static
r_void
id|clps711xuart_int_tx
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
r_struct
id|uart_port
op_star
id|port
op_assign
id|dev_id
suffix:semicolon
r_struct
id|circ_buf
op_star
id|xmit
op_assign
op_amp
id|port-&gt;info-&gt;xmit
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;x_char
)paren
(brace
id|clps_writel
c_func
(paren
id|port-&gt;x_char
comma
id|UARTDR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|port-&gt;icount.tx
op_increment
suffix:semicolon
id|port-&gt;x_char
op_assign
l_int|0
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
id|clps711xuart_stop_tx
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
id|count
op_assign
id|port-&gt;fifosize
op_rshift
l_int|1
suffix:semicolon
r_do
(brace
id|clps_writel
c_func
(paren
id|xmit-&gt;buf
(braket
id|xmit-&gt;tail
)braket
comma
id|UARTDR
c_func
(paren
id|port
)paren
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
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|count
OG
l_int|0
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
id|uart_write_wakeup
c_func
(paren
id|port
)paren
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
id|clps711xuart_stop_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|clps711xuart_tx_empty
r_static
r_int
r_int
id|clps711xuart_tx_empty
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
id|clps_readl
c_func
(paren
id|SYSFLG
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_return
id|status
op_amp
id|SYSFLG_UBUSY
ques
c_cond
l_int|0
suffix:colon
id|TIOCSER_TEMT
suffix:semicolon
)brace
DECL|function|clps711xuart_get_mctrl
r_static
r_int
r_int
id|clps711xuart_get_mctrl
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
id|port_addr
suffix:semicolon
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|port_addr
op_assign
id|SYSFLG
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port_addr
op_eq
id|SYSFLG1
)paren
(brace
id|status
op_assign
id|clps_readl
c_func
(paren
id|SYSFLG1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SYSFLG1_DCD
)paren
id|result
op_or_assign
id|TIOCM_CAR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SYSFLG1_DSR
)paren
id|result
op_or_assign
id|TIOCM_DSR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SYSFLG1_CTS
)paren
id|result
op_or_assign
id|TIOCM_CTS
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
r_static
r_void
DECL|function|clps711xuart_set_mctrl_null
id|clps711xuart_set_mctrl_null
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
)brace
DECL|function|clps711xuart_break_ctl
r_static
r_void
id|clps711xuart_break_ctl
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
id|ubrlcr
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
id|ubrlcr
op_assign
id|clps_readl
c_func
(paren
id|UBRLCR
c_func
(paren
id|port
)paren
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
id|ubrlcr
op_or_assign
id|UBRLCR_BREAK
suffix:semicolon
r_else
id|ubrlcr
op_and_assign
op_complement
id|UBRLCR_BREAK
suffix:semicolon
id|clps_writel
c_func
(paren
id|ubrlcr
comma
id|UBRLCR
c_func
(paren
id|port
)paren
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
DECL|function|clps711xuart_startup
r_static
r_int
id|clps711xuart_startup
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
id|syscon
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|tx_enabled
c_func
(paren
id|port
)paren
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the IRQs&n;&t; */
id|retval
op_assign
id|request_irq
c_func
(paren
id|TX_IRQ
c_func
(paren
id|port
)paren
comma
id|clps711xuart_int_tx
comma
l_int|0
comma
l_string|&quot;clps711xuart_tx&quot;
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
id|retval
op_assign
id|request_irq
c_func
(paren
id|RX_IRQ
c_func
(paren
id|port
)paren
comma
id|clps711xuart_int_rx
comma
l_int|0
comma
l_string|&quot;clps711xuart_rx&quot;
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|free_irq
c_func
(paren
id|TX_IRQ
c_func
(paren
id|port
)paren
comma
id|port
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * enable the port&n;&t; */
id|syscon
op_assign
id|clps_readl
c_func
(paren
id|SYSCON
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|syscon
op_or_assign
id|SYSCON_UARTEN
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon
comma
id|SYSCON
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|clps711xuart_shutdown
r_static
r_void
id|clps711xuart_shutdown
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
id|ubrlcr
comma
id|syscon
suffix:semicolon
multiline_comment|/*&n;&t; * Free the interrupt&n;&t; */
id|free_irq
c_func
(paren
id|TX_IRQ
c_func
(paren
id|port
)paren
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* TX interrupt */
id|free_irq
c_func
(paren
id|RX_IRQ
c_func
(paren
id|port
)paren
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* RX interrupt */
multiline_comment|/*&n;&t; * disable the port&n;&t; */
id|syscon
op_assign
id|clps_readl
c_func
(paren
id|SYSCON
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|syscon
op_and_assign
op_complement
id|SYSCON_UARTEN
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon
comma
id|SYSCON
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * disable break condition and fifos&n;&t; */
id|ubrlcr
op_assign
id|clps_readl
c_func
(paren
id|UBRLCR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|ubrlcr
op_and_assign
op_complement
(paren
id|UBRLCR_FIFOEN
op_or
id|UBRLCR_BREAK
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|ubrlcr
comma
id|UBRLCR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|clps711xuart_set_termios
id|clps711xuart_set_termios
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|termios
op_star
id|termios
comma
r_struct
id|termios
op_star
id|old
)paren
(brace
r_int
r_int
id|ubrlcr
comma
id|baud
comma
id|quot
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t implement CREAD.&n;&t; */
id|termios-&gt;c_cflag
op_or_assign
id|CREAD
suffix:semicolon
multiline_comment|/*&n;&t; * Ask the core to calculate the divisor for us.&n;&t; */
id|baud
op_assign
id|uart_get_baud_rate
c_func
(paren
id|port
comma
id|termios
comma
id|old
comma
l_int|0
comma
id|port-&gt;uartclk
op_div
l_int|16
)paren
suffix:semicolon
id|quot
op_assign
id|uart_get_divisor
c_func
(paren
id|port
comma
id|baud
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|termios-&gt;c_cflag
op_amp
id|CSIZE
)paren
(brace
r_case
id|CS5
suffix:colon
id|ubrlcr
op_assign
id|UBRLCR_WRDLEN5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|ubrlcr
op_assign
id|UBRLCR_WRDLEN6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|ubrlcr
op_assign
id|UBRLCR_WRDLEN7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
singleline_comment|// CS8
id|ubrlcr
op_assign
id|UBRLCR_WRDLEN8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|termios-&gt;c_cflag
op_amp
id|CSTOPB
)paren
id|ubrlcr
op_or_assign
id|UBRLCR_XSTOP
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_cflag
op_amp
id|PARENB
)paren
(brace
id|ubrlcr
op_or_assign
id|UBRLCR_PRTEN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|termios-&gt;c_cflag
op_amp
id|PARODD
)paren
)paren
id|ubrlcr
op_or_assign
id|UBRLCR_EVENPRT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;fifosize
OG
l_int|1
)paren
id|ubrlcr
op_or_assign
id|UBRLCR_FIFOEN
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
multiline_comment|/*&n;&t; * Update the per-port timeout.&n;&t; */
id|uart_update_timeout
c_func
(paren
id|port
comma
id|termios-&gt;c_cflag
comma
id|baud
)paren
suffix:semicolon
id|port-&gt;read_status_mask
op_assign
id|UARTDR_OVERR
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
id|INPCK
)paren
id|port-&gt;read_status_mask
op_or_assign
id|UARTDR_PARERR
op_or
id|UARTDR_FRMERR
suffix:semicolon
multiline_comment|/*&n;&t; * Characters to ignore&n;&t; */
id|port-&gt;ignore_status_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
id|IGNPAR
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|UARTDR_FRMERR
op_or
id|UARTDR_PARERR
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
id|IGNBRK
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we&squot;re ignoring parity and break indicators,&n;&t;&t; * ignore overruns to (for real raw support).&n;&t;&t; */
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
id|IGNPAR
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|UARTDR_OVERR
suffix:semicolon
)brace
id|quot
op_sub_assign
l_int|1
suffix:semicolon
id|clps_writel
c_func
(paren
id|ubrlcr
op_or
id|quot
comma
id|UBRLCR
c_func
(paren
id|port
)paren
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
DECL|function|clps711xuart_type
r_static
r_const
r_char
op_star
id|clps711xuart_type
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|port-&gt;type
op_eq
id|PORT_CLPS711X
ques
c_cond
l_string|&quot;CLPS711x&quot;
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure/autoconfigure the port.&n; */
DECL|function|clps711xuart_config_port
r_static
r_void
id|clps711xuart_config_port
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|UART_CONFIG_TYPE
)paren
id|port-&gt;type
op_assign
id|PORT_CLPS711X
suffix:semicolon
)brace
DECL|function|clps711xuart_release_port
r_static
r_void
id|clps711xuart_release_port
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
)brace
DECL|function|clps711xuart_request_port
r_static
r_int
id|clps711xuart_request_port
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|clps711x_pops
r_static
r_struct
id|uart_ops
id|clps711x_pops
op_assign
(brace
dot
id|tx_empty
op_assign
id|clps711xuart_tx_empty
comma
dot
id|set_mctrl
op_assign
id|clps711xuart_set_mctrl_null
comma
dot
id|get_mctrl
op_assign
id|clps711xuart_get_mctrl
comma
dot
id|stop_tx
op_assign
id|clps711xuart_stop_tx
comma
dot
id|start_tx
op_assign
id|clps711xuart_start_tx
comma
dot
id|stop_rx
op_assign
id|clps711xuart_stop_rx
comma
dot
id|enable_ms
op_assign
id|clps711xuart_enable_ms
comma
dot
id|break_ctl
op_assign
id|clps711xuart_break_ctl
comma
dot
id|startup
op_assign
id|clps711xuart_startup
comma
dot
id|shutdown
op_assign
id|clps711xuart_shutdown
comma
dot
id|set_termios
op_assign
id|clps711xuart_set_termios
comma
dot
id|type
op_assign
id|clps711xuart_type
comma
dot
id|config_port
op_assign
id|clps711xuart_config_port
comma
dot
id|release_port
op_assign
id|clps711xuart_release_port
comma
dot
id|request_port
op_assign
id|clps711xuart_request_port
comma
)brace
suffix:semicolon
DECL|variable|clps711x_ports
r_static
r_struct
id|uart_port
id|clps711x_ports
(braket
id|UART_NR
)braket
op_assign
(brace
(brace
dot
id|iobase
op_assign
id|SYSCON1
comma
dot
id|irq
op_assign
id|IRQ_UTXINT1
comma
multiline_comment|/* IRQ_URXINT1, IRQ_UMSINT */
dot
id|uartclk
op_assign
l_int|3686400
comma
dot
id|fifosize
op_assign
l_int|16
comma
dot
id|ops
op_assign
op_amp
id|clps711x_pops
comma
dot
id|line
op_assign
l_int|0
comma
dot
id|flags
op_assign
id|ASYNC_BOOT_AUTOCONF
comma
)brace
comma
(brace
dot
id|iobase
op_assign
id|SYSCON2
comma
dot
id|irq
op_assign
id|IRQ_UTXINT2
comma
multiline_comment|/* IRQ_URXINT2 */
dot
id|uartclk
op_assign
l_int|3686400
comma
dot
id|fifosize
op_assign
l_int|16
comma
dot
id|ops
op_assign
op_amp
id|clps711x_pops
comma
dot
id|line
op_assign
l_int|1
comma
dot
id|flags
op_assign
id|ASYNC_BOOT_AUTOCONF
comma
)brace
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_CLPS711X_CONSOLE
multiline_comment|/*&n; *&t;Print a string to the serial port trying not to disturb&n; *&t;any possible real use of the port...&n; *&n; *&t;The console_lock must be held when we get here.&n; *&n; *&t;Note that this is called with interrupts already disabled&n; */
r_static
r_void
DECL|function|clps711xuart_console_write
id|clps711xuart_console_write
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
id|clps711x_ports
op_plus
id|co-&gt;index
suffix:semicolon
r_int
r_int
id|status
comma
id|syscon
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Ensure that the port is enabled.&n;&t; */
id|syscon
op_assign
id|clps_readl
c_func
(paren
id|SYSCON
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon
op_or
id|SYSCON_UARTEN
comma
id|SYSCON
c_func
(paren
id|port
)paren
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
)paren
(brace
r_do
(brace
id|status
op_assign
id|clps_readl
c_func
(paren
id|SYSFLG
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|SYSFLG_UTXFF
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|s
(braket
id|i
)braket
comma
id|UARTDR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_do
(brace
id|status
op_assign
id|clps_readl
c_func
(paren
id|SYSFLG
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|SYSFLG_UTXFF
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
id|UARTDR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Finally, wait for transmitter to become empty&n;&t; *&t;and restore the uart state.&n;&t; */
r_do
(brace
id|status
op_assign
id|clps_readl
c_func
(paren
id|SYSFLG
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|SYSFLG_UBUSY
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon
comma
id|SYSCON
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|clps711xuart_console_device
r_static
id|kdev_t
id|clps711xuart_console_device
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
id|SERIAL_CLPS711X_MAJOR
comma
id|SERIAL_CLPS711X_MINOR
op_plus
id|co-&gt;index
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|clps711xuart_console_get_options
id|clps711xuart_console_get_options
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
r_if
c_cond
(paren
id|clps_readl
c_func
(paren
id|SYSCON
c_func
(paren
id|port
)paren
)paren
op_amp
id|SYSCON_UARTEN
)paren
(brace
r_int
r_int
id|ubrlcr
comma
id|quot
suffix:semicolon
id|ubrlcr
op_assign
id|clps_readl
c_func
(paren
id|UBRLCR
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
op_star
id|parity
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|ubrlcr
op_amp
id|UBRLCR_PRTEN
)paren
(brace
r_if
c_cond
(paren
id|ubrlcr
op_amp
id|UBRLCR_EVENPRT
)paren
op_star
id|parity
op_assign
l_char|&squot;e&squot;
suffix:semicolon
r_else
op_star
id|parity
op_assign
l_char|&squot;o&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ubrlcr
op_amp
id|UBRLCR_WRDLEN_MASK
)paren
op_eq
id|UBRLCR_WRDLEN7
)paren
op_star
id|bits
op_assign
l_int|7
suffix:semicolon
r_else
op_star
id|bits
op_assign
l_int|8
suffix:semicolon
id|quot
op_assign
id|ubrlcr
op_amp
id|UBRLCR_BAUD_MASK
suffix:semicolon
op_star
id|baud
op_assign
id|port-&gt;uartclk
op_div
(paren
l_int|16
op_star
(paren
id|quot
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|clps711xuart_console_setup
r_static
r_int
id|__init
id|clps711xuart_console_setup
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
l_int|38400
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
r_int
id|flow
op_assign
l_char|&squot;n&squot;
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether an invalid uart number has been specified, and&n;&t; * if so, search for the first available port that does have&n;&t; * console support.&n;&t; */
id|port
op_assign
id|uart_get_console
c_func
(paren
id|clps711x_ports
comma
id|UART_NR
comma
id|co
)paren
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
comma
op_amp
id|flow
)paren
suffix:semicolon
r_else
id|clps711xuart_console_get_options
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
comma
id|flow
)paren
suffix:semicolon
)brace
DECL|variable|clps711x_console
r_static
r_struct
id|console
id|clps711x_console
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyCL&quot;
comma
dot
id|write
op_assign
id|clps711xuart_console_write
comma
dot
id|device
op_assign
id|clps711xuart_console_device
comma
dot
id|setup
op_assign
id|clps711xuart_console_setup
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|clps711xuart_console_init
r_void
id|__init
id|clps711xuart_console_init
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|clps711x_console
)paren
suffix:semicolon
)brace
DECL|macro|CLPS711X_CONSOLE
mdefine_line|#define CLPS711X_CONSOLE&t;&amp;clps711x_console
macro_line|#else
DECL|macro|CLPS711X_CONSOLE
mdefine_line|#define CLPS711X_CONSOLE&t;NULL
macro_line|#endif
DECL|variable|clps711x_reg
r_static
r_struct
id|uart_driver
id|clps711x_reg
op_assign
(brace
dot
id|driver_name
op_assign
l_string|&quot;ttyCL&quot;
comma
dot
id|dev_name
op_assign
l_string|&quot;ttyCL%d&quot;
comma
dot
id|major
op_assign
id|SERIAL_CLPS711X_MAJOR
comma
dot
id|minor
op_assign
id|SERIAL_CLPS711X_MINOR
comma
dot
id|nr
op_assign
id|UART_NR
comma
dot
id|cons
op_assign
id|CLPS711X_CONSOLE
comma
)brace
suffix:semicolon
DECL|function|clps711xuart_init
r_static
r_int
id|__init
id|clps711xuart_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
comma
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Serial: CLPS711x driver $Revision: 1.42 $&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|uart_register_driver
c_func
(paren
op_amp
id|clps711x_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
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
id|clps711x_reg
comma
op_amp
id|clps711x_ports
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|clps711xuart_exit
r_static
r_void
id|__exit
id|clps711xuart_exit
c_func
(paren
r_void
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
id|uart_remove_one_port
c_func
(paren
op_amp
id|clps711x_reg
comma
op_amp
id|clps711x_ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|uart_unregister_driver
c_func
(paren
op_amp
id|clps711x_reg
)paren
suffix:semicolon
)brace
DECL|variable|clps711xuart_init
id|module_init
c_func
(paren
id|clps711xuart_init
)paren
suffix:semicolon
DECL|variable|clps711xuart_exit
id|module_exit
c_func
(paren
id|clps711xuart_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Deep Blue Solutions Ltd&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CLPS-711x generic serial driver $Revision: 1.42 $&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
