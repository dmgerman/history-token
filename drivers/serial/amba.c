multiline_comment|/*&n; *  linux/drivers/char/amba.c&n; *&n; *  Driver for AMBA serial ports&n; *&n; *  Based on drivers/char/serial.c, by Linus Torvalds, Theodore Ts&squot;o.&n; *&n; *  Copyright 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  $Id: amba.c,v 1.41 2002/07/28 10:03:27 rmk Exp $&n; *&n; * This is a generic driver for ARM AMBA-type serial ports.  They&n; * have a lot of 16550-like features, but are not register compatable.&n; * Note that although they do have CTS, DCD and DSR inputs, they do&n; * not have an RI input, nor do they have DTR or RTS outputs.  If&n; * required, these have to be supplied via some other means (eg, GPIO)&n; * and hooked into this driver.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#if defined(CONFIG_SERIAL_AMBA_CONSOLE) &amp;&amp; defined(CONFIG_MAGIC_SYSRQ)
DECL|macro|SUPPORT_SYSRQ
mdefine_line|#define SUPPORT_SYSRQ
macro_line|#endif
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/hardware/serial_amba.h&gt;
DECL|macro|UART_NR
mdefine_line|#define UART_NR&t;&t;2
DECL|macro|SERIAL_AMBA_MAJOR
mdefine_line|#define SERIAL_AMBA_MAJOR&t;204
DECL|macro|SERIAL_AMBA_MINOR
mdefine_line|#define SERIAL_AMBA_MINOR&t;16
DECL|macro|SERIAL_AMBA_NR
mdefine_line|#define SERIAL_AMBA_NR&t;&t;UART_NR
DECL|macro|AMBA_ISR_PASS_LIMIT
mdefine_line|#define AMBA_ISR_PASS_LIMIT&t;256
multiline_comment|/*&n; * Access macros for the AMBA UARTs&n; */
DECL|macro|UART_GET_INT_STATUS
mdefine_line|#define UART_GET_INT_STATUS(p)&t;readb((p)-&gt;membase + AMBA_UARTIIR)
DECL|macro|UART_PUT_ICR
mdefine_line|#define UART_PUT_ICR(p, c)&t;writel((c), (p)-&gt;membase + AMBA_UARTICR)
DECL|macro|UART_GET_FR
mdefine_line|#define UART_GET_FR(p)&t;&t;readb((p)-&gt;membase + AMBA_UARTFR)
DECL|macro|UART_GET_CHAR
mdefine_line|#define UART_GET_CHAR(p)&t;readb((p)-&gt;membase + AMBA_UARTDR)
DECL|macro|UART_PUT_CHAR
mdefine_line|#define UART_PUT_CHAR(p, c)&t;writel((c), (p)-&gt;membase + AMBA_UARTDR)
DECL|macro|UART_GET_RSR
mdefine_line|#define UART_GET_RSR(p)&t;&t;readb((p)-&gt;membase + AMBA_UARTRSR)
DECL|macro|UART_GET_CR
mdefine_line|#define UART_GET_CR(p)&t;&t;readb((p)-&gt;membase + AMBA_UARTCR)
DECL|macro|UART_PUT_CR
mdefine_line|#define UART_PUT_CR(p,c)&t;writel((c), (p)-&gt;membase + AMBA_UARTCR)
DECL|macro|UART_GET_LCRL
mdefine_line|#define UART_GET_LCRL(p)&t;readb((p)-&gt;membase + AMBA_UARTLCR_L)
DECL|macro|UART_PUT_LCRL
mdefine_line|#define UART_PUT_LCRL(p,c)&t;writel((c), (p)-&gt;membase + AMBA_UARTLCR_L)
DECL|macro|UART_GET_LCRM
mdefine_line|#define UART_GET_LCRM(p)&t;readb((p)-&gt;membase + AMBA_UARTLCR_M)
DECL|macro|UART_PUT_LCRM
mdefine_line|#define UART_PUT_LCRM(p,c)&t;writel((c), (p)-&gt;membase + AMBA_UARTLCR_M)
DECL|macro|UART_GET_LCRH
mdefine_line|#define UART_GET_LCRH(p)&t;readb((p)-&gt;membase + AMBA_UARTLCR_H)
DECL|macro|UART_PUT_LCRH
mdefine_line|#define UART_PUT_LCRH(p,c)&t;writel((c), (p)-&gt;membase + AMBA_UARTLCR_H)
DECL|macro|UART_RX_DATA
mdefine_line|#define UART_RX_DATA(s)&t;&t;(((s) &amp; AMBA_UARTFR_RXFE) == 0)
DECL|macro|UART_TX_READY
mdefine_line|#define UART_TX_READY(s)&t;(((s) &amp; AMBA_UARTFR_TXFF) == 0)
DECL|macro|UART_TX_EMPTY
mdefine_line|#define UART_TX_EMPTY(p)&t;((UART_GET_FR(p) &amp; AMBA_UARTFR_TMSK) == 0)
DECL|macro|UART_DUMMY_RSR_RX
mdefine_line|#define UART_DUMMY_RSR_RX&t;256
DECL|macro|UART_PORT_SIZE
mdefine_line|#define UART_PORT_SIZE&t;&t;64
multiline_comment|/*&n; * On the Integrator platform, the port RTS and DTR are provided by&n; * bits in the following SC_CTRLS register bits:&n; *        RTS  DTR&n; *  UART0  7    6&n; *  UART1  5    4&n; */
DECL|macro|SC_CTRLC
mdefine_line|#define SC_CTRLC&t;(IO_ADDRESS(INTEGRATOR_SC_BASE) + INTEGRATOR_SC_CTRLC_OFFSET)
DECL|macro|SC_CTRLS
mdefine_line|#define SC_CTRLS&t;(IO_ADDRESS(INTEGRATOR_SC_BASE) + INTEGRATOR_SC_CTRLS_OFFSET)
multiline_comment|/*&n; * We wrap our port structure around the generic uart_port.&n; */
DECL|struct|uart_amba_port
r_struct
id|uart_amba_port
(brace
DECL|member|port
r_struct
id|uart_port
id|port
suffix:semicolon
DECL|member|dtr_mask
r_int
r_int
id|dtr_mask
suffix:semicolon
DECL|member|rts_mask
r_int
r_int
id|rts_mask
suffix:semicolon
DECL|member|old_status
r_int
r_int
id|old_status
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ambauart_stop_tx
r_static
r_void
id|ambauart_stop_tx
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
r_int
r_int
id|cr
suffix:semicolon
id|cr
op_assign
id|UART_GET_CR
c_func
(paren
id|port
)paren
suffix:semicolon
id|cr
op_and_assign
op_complement
id|AMBA_UARTCR_TIE
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|cr
)paren
suffix:semicolon
)brace
DECL|function|ambauart_start_tx
r_static
r_void
id|ambauart_start_tx
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
id|cr
suffix:semicolon
id|cr
op_assign
id|UART_GET_CR
c_func
(paren
id|port
)paren
suffix:semicolon
id|cr
op_or_assign
id|AMBA_UARTCR_TIE
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|cr
)paren
suffix:semicolon
)brace
DECL|function|ambauart_stop_rx
r_static
r_void
id|ambauart_stop_rx
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
id|cr
suffix:semicolon
id|cr
op_assign
id|UART_GET_CR
c_func
(paren
id|port
)paren
suffix:semicolon
id|cr
op_and_assign
op_complement
(paren
id|AMBA_UARTCR_RIE
op_or
id|AMBA_UARTCR_RTIE
)paren
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|cr
)paren
suffix:semicolon
)brace
DECL|function|ambauart_enable_ms
r_static
r_void
id|ambauart_enable_ms
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
id|cr
suffix:semicolon
id|cr
op_assign
id|UART_GET_CR
c_func
(paren
id|port
)paren
suffix:semicolon
id|cr
op_or_assign
id|AMBA_UARTCR_MSIE
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|cr
)paren
suffix:semicolon
)brace
r_static
r_void
macro_line|#ifdef SUPPORT_SYSRQ
DECL|function|ambauart_rx_chars
id|ambauart_rx_chars
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
macro_line|#else
id|ambauart_rx_chars
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
macro_line|#endif
(brace
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
id|rsr
comma
id|max_count
op_assign
l_int|256
suffix:semicolon
id|status
op_assign
id|UART_GET_FR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|UART_RX_DATA
c_func
(paren
id|status
)paren
op_logical_and
id|max_count
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;flip.count
op_ge
id|TTY_FLIPBUF_SIZE
)paren
(brace
id|tty-&gt;flip.work
dot
id|func
c_func
(paren
(paren
r_void
op_star
)paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;flip.count
op_ge
id|TTY_FLIPBUF_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TTY_DONT_FLIP set&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|ch
op_assign
id|UART_GET_CHAR
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|tty-&gt;flip.char_buf_ptr
op_assign
id|ch
suffix:semicolon
op_star
id|tty-&gt;flip.flag_buf_ptr
op_assign
id|TTY_NORMAL
suffix:semicolon
id|port-&gt;icount.rx
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note that the error handling code is&n;&t;&t; * out of the main execution path&n;&t;&t; */
id|rsr
op_assign
id|UART_GET_RSR
c_func
(paren
id|port
)paren
op_or
id|UART_DUMMY_RSR_RX
suffix:semicolon
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_ANY
)paren
(brace
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_BE
)paren
(brace
id|rsr
op_and_assign
op_complement
(paren
id|AMBA_UARTRSR_FE
op_or
id|AMBA_UARTRSR_PE
)paren
suffix:semicolon
id|port-&gt;icount.brk
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|uart_handle_break
c_func
(paren
id|port
)paren
)paren
r_goto
id|ignore_char
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_PE
)paren
id|port-&gt;icount.parity
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_FE
)paren
id|port-&gt;icount.frame
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_OE
)paren
id|port-&gt;icount.overrun
op_increment
suffix:semicolon
id|rsr
op_and_assign
id|port-&gt;read_status_mask
suffix:semicolon
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_BE
)paren
op_star
id|tty-&gt;flip.flag_buf_ptr
op_assign
id|TTY_BREAK
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_PE
)paren
op_star
id|tty-&gt;flip.flag_buf_ptr
op_assign
id|TTY_PARITY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_FE
)paren
op_star
id|tty-&gt;flip.flag_buf_ptr
op_assign
id|TTY_FRAME
suffix:semicolon
)brace
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
r_if
c_cond
(paren
(paren
id|rsr
op_amp
id|port-&gt;ignore_status_mask
)paren
op_eq
l_int|0
)paren
(brace
id|tty-&gt;flip.flag_buf_ptr
op_increment
suffix:semicolon
id|tty-&gt;flip.char_buf_ptr
op_increment
suffix:semicolon
id|tty-&gt;flip.count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rsr
op_amp
id|AMBA_UARTRSR_OE
)paren
op_logical_and
id|tty-&gt;flip.count
OL
id|TTY_FLIPBUF_SIZE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Overrun is special, since it&squot;s reported&n;&t;&t;&t; * immediately, and doesn&squot;t affect the current&n;&t;&t;&t; * character&n;&t;&t;&t; */
op_star
id|tty-&gt;flip.char_buf_ptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|tty-&gt;flip.flag_buf_ptr
op_increment
op_assign
id|TTY_OVERRUN
suffix:semicolon
id|tty-&gt;flip.count
op_increment
suffix:semicolon
)brace
id|ignore_char
suffix:colon
id|status
op_assign
id|UART_GET_FR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|ambauart_tx_chars
r_static
r_void
id|ambauart_tx_chars
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
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;x_char
)paren
(brace
id|UART_PUT_CHAR
c_func
(paren
id|port
comma
id|port-&gt;x_char
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
id|ambauart_stop_tx
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
id|UART_PUT_CHAR
c_func
(paren
id|port
comma
id|xmit-&gt;buf
(braket
id|xmit-&gt;tail
)braket
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
id|ambauart_stop_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ambauart_modem_status
r_static
r_void
id|ambauart_modem_status
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_struct
id|uart_amba_port
op_star
id|uap
op_assign
(paren
r_struct
id|uart_amba_port
op_star
)paren
id|port
suffix:semicolon
r_int
r_int
id|status
comma
id|delta
suffix:semicolon
id|UART_PUT_ICR
c_func
(paren
op_amp
id|uap-&gt;port
comma
l_int|0
)paren
suffix:semicolon
id|status
op_assign
id|UART_GET_FR
c_func
(paren
op_amp
id|uap-&gt;port
)paren
op_amp
id|AMBA_UARTFR_MODEM_ANY
suffix:semicolon
id|delta
op_assign
id|status
op_xor
id|uap-&gt;old_status
suffix:semicolon
id|uap-&gt;old_status
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|delta
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
id|AMBA_UARTFR_DCD
)paren
id|uart_handle_dcd_change
c_func
(paren
op_amp
id|uap-&gt;port
comma
id|status
op_amp
id|AMBA_UARTFR_DCD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
id|AMBA_UARTFR_DSR
)paren
id|uap-&gt;port.icount.dsr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
id|AMBA_UARTFR_CTS
)paren
id|uart_handle_cts_change
c_func
(paren
op_amp
id|uap-&gt;port
comma
id|status
op_amp
id|AMBA_UARTFR_CTS
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|uap-&gt;port.info-&gt;delta_msr_wait
)paren
suffix:semicolon
)brace
DECL|function|ambauart_int
r_static
r_void
id|ambauart_int
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
r_int
r_int
id|status
comma
id|pass_counter
op_assign
id|AMBA_ISR_PASS_LIMIT
suffix:semicolon
id|status
op_assign
id|UART_GET_INT_STATUS
c_func
(paren
id|port
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|AMBA_UARTIIR_RTIS
op_or
id|AMBA_UARTIIR_RIS
)paren
)paren
macro_line|#ifdef SUPPORT_SYSRQ
id|ambauart_rx_chars
c_func
(paren
id|port
comma
id|regs
)paren
suffix:semicolon
macro_line|#else
id|ambauart_rx_chars
c_func
(paren
id|port
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|status
op_amp
id|AMBA_UARTIIR_MIS
)paren
id|ambauart_modem_status
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
id|AMBA_UARTIIR_TIS
)paren
id|ambauart_tx_chars
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pass_counter
op_decrement
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|status
op_assign
id|UART_GET_INT_STATUS
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
(paren
id|AMBA_UARTIIR_RTIS
op_or
id|AMBA_UARTIIR_RIS
op_or
id|AMBA_UARTIIR_TIS
)paren
)paren
suffix:semicolon
)brace
DECL|function|ambauart_tx_empty
r_static
r_int
r_int
id|ambauart_tx_empty
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|UART_GET_FR
c_func
(paren
id|port
)paren
op_amp
id|AMBA_UARTFR_BUSY
ques
c_cond
l_int|0
suffix:colon
id|TIOCSER_TEMT
suffix:semicolon
)brace
DECL|function|ambauart_get_mctrl
r_static
r_int
r_int
id|ambauart_get_mctrl
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
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|status
op_assign
id|UART_GET_FR
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
id|AMBA_UARTFR_DCD
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
id|AMBA_UARTFR_DSR
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
id|AMBA_UARTFR_CTS
)paren
id|result
op_or_assign
id|TIOCM_CTS
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ambauart_set_mctrl
r_static
r_void
id|ambauart_set_mctrl
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
r_struct
id|uart_amba_port
op_star
id|uap
op_assign
(paren
r_struct
id|uart_amba_port
op_star
)paren
id|port
suffix:semicolon
r_int
r_int
id|ctrls
op_assign
l_int|0
comma
id|ctrlc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|ctrlc
op_or_assign
id|uap-&gt;rts_mask
suffix:semicolon
r_else
id|ctrls
op_or_assign
id|uap-&gt;rts_mask
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_DTR
)paren
id|ctrlc
op_or_assign
id|uap-&gt;dtr_mask
suffix:semicolon
r_else
id|ctrls
op_or_assign
id|uap-&gt;dtr_mask
suffix:semicolon
id|__raw_writel
c_func
(paren
id|ctrls
comma
id|SC_CTRLS
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|ctrlc
comma
id|SC_CTRLC
)paren
suffix:semicolon
)brace
DECL|function|ambauart_break_ctl
r_static
r_void
id|ambauart_break_ctl
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
id|lcr_h
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
id|lcr_h
op_assign
id|UART_GET_LCRH
c_func
(paren
id|port
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
id|lcr_h
op_or_assign
id|AMBA_UARTLCR_H_BRK
suffix:semicolon
r_else
id|lcr_h
op_and_assign
op_complement
id|AMBA_UARTLCR_H_BRK
suffix:semicolon
id|UART_PUT_LCRH
c_func
(paren
id|port
comma
id|lcr_h
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
DECL|function|ambauart_startup
r_static
r_int
id|ambauart_startup
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_struct
id|uart_amba_port
op_star
id|uap
op_assign
(paren
r_struct
id|uart_amba_port
op_star
)paren
id|port
suffix:semicolon
r_int
id|retval
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the IRQ&n;&t; */
id|retval
op_assign
id|request_irq
c_func
(paren
id|port-&gt;irq
comma
id|ambauart_int
comma
l_int|0
comma
l_string|&quot;amba&quot;
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
id|uap-&gt;old_status
op_assign
id|UART_GET_FR
c_func
(paren
id|port
)paren
op_amp
id|AMBA_UARTFR_MODEM_ANY
suffix:semicolon
multiline_comment|/*&n;&t; * Finally, enable interrupts&n;&t; */
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|AMBA_UARTCR_UARTEN
op_or
id|AMBA_UARTCR_RIE
op_or
id|AMBA_UARTCR_RTIE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ambauart_shutdown
r_static
r_void
id|ambauart_shutdown
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
id|UART_PUT_CR
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* disable break condition and fifos */
id|UART_PUT_LCRH
c_func
(paren
id|port
comma
id|UART_GET_LCRH
c_func
(paren
id|port
)paren
op_amp
op_complement
(paren
id|AMBA_UARTLCR_H_BRK
op_or
id|AMBA_UARTLCR_H_FEN
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ambauart_change_speed
id|ambauart_change_speed
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
id|lcr_h
comma
id|old_cr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* byte size and parity */
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
id|lcr_h
op_assign
id|AMBA_UARTLCR_H_WLEN_5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|lcr_h
op_assign
id|AMBA_UARTLCR_H_WLEN_6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|lcr_h
op_assign
id|AMBA_UARTLCR_H_WLEN_7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
singleline_comment|// CS8
id|lcr_h
op_assign
id|AMBA_UARTLCR_H_WLEN_8
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
id|lcr_h
op_or_assign
id|AMBA_UARTLCR_H_STP2
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
(brace
id|lcr_h
op_or_assign
id|AMBA_UARTLCR_H_PEN
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
id|lcr_h
op_or_assign
id|AMBA_UARTLCR_H_EPS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;fifosize
OG
l_int|1
)paren
id|lcr_h
op_or_assign
id|AMBA_UARTLCR_H_FEN
suffix:semicolon
id|port-&gt;read_status_mask
op_assign
id|AMBA_UARTRSR_OE
suffix:semicolon
r_if
c_cond
(paren
id|iflag
op_amp
id|INPCK
)paren
id|port-&gt;read_status_mask
op_or_assign
id|AMBA_UARTRSR_FE
op_or
id|AMBA_UARTRSR_PE
suffix:semicolon
r_if
c_cond
(paren
id|iflag
op_amp
(paren
id|BRKINT
op_or
id|PARMRK
)paren
)paren
id|port-&gt;read_status_mask
op_or_assign
id|AMBA_UARTRSR_BE
suffix:semicolon
multiline_comment|/*&n;&t; * Characters to ignore&n;&t; */
id|port-&gt;ignore_status_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iflag
op_amp
id|IGNPAR
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|AMBA_UARTRSR_FE
op_or
id|AMBA_UARTRSR_PE
suffix:semicolon
r_if
c_cond
(paren
id|iflag
op_amp
id|IGNBRK
)paren
(brace
id|port-&gt;ignore_status_mask
op_or_assign
id|AMBA_UARTRSR_BE
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we&squot;re ignoring parity and break indicators,&n;&t;&t; * ignore overruns too (for real raw support).&n;&t;&t; */
r_if
c_cond
(paren
id|iflag
op_amp
id|IGNPAR
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|AMBA_UARTRSR_OE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ignore all characters if CREAD is not set.&n;&t; */
r_if
c_cond
(paren
(paren
id|cflag
op_amp
id|CREAD
)paren
op_eq
l_int|0
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|UART_DUMMY_RSR_RX
suffix:semicolon
multiline_comment|/* first, disable everything */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|old_cr
op_assign
id|UART_GET_CR
c_func
(paren
id|port
)paren
op_amp
op_complement
id|AMBA_UARTCR_MSIE
suffix:semicolon
r_if
c_cond
(paren
id|UART_ENABLE_MS
c_func
(paren
id|port
comma
id|cflag
)paren
)paren
id|old_cr
op_or_assign
id|AMBA_UARTCR_MSIE
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set baud rate */
id|quot
op_sub_assign
l_int|1
suffix:semicolon
id|UART_PUT_LCRM
c_func
(paren
id|port
comma
(paren
(paren
id|quot
op_amp
l_int|0xf00
)paren
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
id|UART_PUT_LCRL
c_func
(paren
id|port
comma
(paren
id|quot
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * ----------v----------v----------v----------v-----&n;&t; * NOTE: MUST BE WRITTEN AFTER UARTLCR_M &amp; UARTLCR_L&n;&t; * ----------^----------^----------^----------^-----&n;&t; */
id|UART_PUT_LCRH
c_func
(paren
id|port
comma
id|lcr_h
)paren
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|old_cr
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
DECL|function|ambauart_type
r_static
r_const
r_char
op_star
id|ambauart_type
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
id|PORT_AMBA
ques
c_cond
l_string|&quot;AMBA&quot;
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Release the memory region(s) being used by &squot;port&squot;&n; */
DECL|function|ambauart_release_port
r_static
r_void
id|ambauart_release_port
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|release_mem_region
c_func
(paren
id|port-&gt;mapbase
comma
id|UART_PORT_SIZE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Request the memory region(s) being used by &squot;port&squot;&n; */
DECL|function|ambauart_request_port
r_static
r_int
id|ambauart_request_port
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|request_mem_region
c_func
(paren
id|port-&gt;mapbase
comma
id|UART_PORT_SIZE
comma
l_string|&quot;serial_amba&quot;
)paren
op_ne
l_int|NULL
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure/autoconfigure the port.&n; */
DECL|function|ambauart_config_port
r_static
r_void
id|ambauart_config_port
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
(brace
id|port-&gt;type
op_assign
id|PORT_AMBA
suffix:semicolon
id|ambauart_request_port
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * verify the new serial_struct (for TIOCSSERIAL).&n; */
DECL|function|ambauart_verify_port
r_static
r_int
id|ambauart_verify_port
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|serial_struct
op_star
id|ser
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ser-&gt;type
op_ne
id|PORT_UNKNOWN
op_logical_and
id|ser-&gt;type
op_ne
id|PORT_AMBA
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ser-&gt;irq
OL
l_int|0
op_logical_or
id|ser-&gt;irq
op_ge
id|NR_IRQS
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ser-&gt;baud_base
OL
l_int|9600
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|amba_pops
r_static
r_struct
id|uart_ops
id|amba_pops
op_assign
(brace
dot
id|tx_empty
op_assign
id|ambauart_tx_empty
comma
dot
id|set_mctrl
op_assign
id|ambauart_set_mctrl
comma
dot
id|get_mctrl
op_assign
id|ambauart_get_mctrl
comma
dot
id|stop_tx
op_assign
id|ambauart_stop_tx
comma
dot
id|start_tx
op_assign
id|ambauart_start_tx
comma
dot
id|stop_rx
op_assign
id|ambauart_stop_rx
comma
dot
id|enable_ms
op_assign
id|ambauart_enable_ms
comma
dot
id|break_ctl
op_assign
id|ambauart_break_ctl
comma
dot
id|startup
op_assign
id|ambauart_startup
comma
dot
id|shutdown
op_assign
id|ambauart_shutdown
comma
dot
id|change_speed
op_assign
id|ambauart_change_speed
comma
dot
id|type
op_assign
id|ambauart_type
comma
dot
id|release_port
op_assign
id|ambauart_release_port
comma
dot
id|request_port
op_assign
id|ambauart_request_port
comma
dot
id|config_port
op_assign
id|ambauart_config_port
comma
dot
id|verify_port
op_assign
id|ambauart_verify_port
comma
)brace
suffix:semicolon
DECL|variable|amba_ports
r_static
r_struct
id|uart_amba_port
id|amba_ports
(braket
id|UART_NR
)braket
op_assign
(brace
(brace
dot
id|port
op_assign
(brace
dot
id|membase
op_assign
(paren
r_void
op_star
)paren
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_UART0_BASE
)paren
comma
dot
id|mapbase
op_assign
id|INTEGRATOR_UART0_BASE
comma
dot
id|iotype
op_assign
id|SERIAL_IO_MEM
comma
dot
id|irq
op_assign
id|IRQ_UARTINT0
comma
dot
id|uartclk
op_assign
l_int|14745600
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
id|amba_pops
comma
dot
id|flags
op_assign
id|ASYNC_BOOT_AUTOCONF
comma
dot
id|line
op_assign
l_int|0
comma
)brace
comma
dot
id|dtr_mask
op_assign
l_int|1
op_lshift
l_int|5
comma
dot
id|rts_mask
op_assign
l_int|1
op_lshift
l_int|4
comma
)brace
comma
(brace
dot
id|port
op_assign
(brace
dot
id|membase
op_assign
(paren
r_void
op_star
)paren
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_UART1_BASE
)paren
comma
dot
id|mapbase
op_assign
id|INTEGRATOR_UART1_BASE
comma
dot
id|iotype
op_assign
id|SERIAL_IO_MEM
comma
dot
id|irq
op_assign
id|IRQ_UARTINT1
comma
dot
id|uartclk
op_assign
l_int|14745600
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
id|amba_pops
comma
dot
id|flags
op_assign
id|ASYNC_BOOT_AUTOCONF
comma
dot
id|line
op_assign
l_int|1
comma
)brace
comma
dot
id|dtr_mask
op_assign
l_int|1
op_lshift
l_int|7
comma
dot
id|rts_mask
op_assign
l_int|1
op_lshift
l_int|6
comma
)brace
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_AMBA_CONSOLE
r_static
r_void
DECL|function|ambauart_console_write
id|ambauart_console_write
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
id|amba_ports
(braket
id|co-&gt;index
)braket
dot
id|port
suffix:semicolon
r_int
r_int
id|status
comma
id|old_cr
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *&t;First save the CR then disable the interrupts&n;&t; */
id|old_cr
op_assign
id|UART_GET_CR
c_func
(paren
id|port
)paren
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|AMBA_UARTCR_UARTEN
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
id|UART_GET_FR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|UART_TX_READY
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
id|UART_PUT_CHAR
c_func
(paren
id|port
comma
id|s
(braket
id|i
)braket
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
id|UART_GET_FR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|UART_TX_READY
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
id|UART_PUT_CHAR
c_func
(paren
id|port
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Finally, wait for transmitter to become empty&n;&t; *&t;and restore the TCR&n;&t; */
r_do
(brace
id|status
op_assign
id|UART_GET_FR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|AMBA_UARTFR_BUSY
)paren
suffix:semicolon
id|UART_PUT_CR
c_func
(paren
id|port
comma
id|old_cr
)paren
suffix:semicolon
)brace
DECL|function|ambauart_console_device
r_static
id|kdev_t
id|ambauart_console_device
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
id|SERIAL_AMBA_MAJOR
comma
id|SERIAL_AMBA_MINOR
op_plus
id|co-&gt;index
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ambauart_console_get_options
id|ambauart_console_get_options
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
id|UART_GET_CR
c_func
(paren
id|port
)paren
op_amp
id|AMBA_UARTCR_UARTEN
)paren
(brace
r_int
r_int
id|lcr_h
comma
id|quot
suffix:semicolon
id|lcr_h
op_assign
id|UART_GET_LCRH
c_func
(paren
id|port
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
id|lcr_h
op_amp
id|AMBA_UARTLCR_H_PEN
)paren
(brace
r_if
c_cond
(paren
id|lcr_h
op_amp
id|AMBA_UARTLCR_H_EPS
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
id|lcr_h
op_amp
l_int|0x60
)paren
op_eq
id|AMBA_UARTLCR_H_WLEN_7
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
id|UART_GET_LCRL
c_func
(paren
id|port
)paren
op_or
id|UART_GET_LCRM
c_func
(paren
id|port
)paren
op_lshift
l_int|8
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
DECL|function|ambauart_console_setup
r_static
r_int
id|__init
id|ambauart_console_setup
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
id|amba_ports
(braket
id|co-&gt;index
)braket
dot
id|port
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
id|ambauart_console_get_options
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
DECL|variable|amba_console
r_static
r_struct
id|console
id|amba_console
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyAM&quot;
comma
dot
id|write
op_assign
id|ambauart_console_write
comma
dot
id|device
op_assign
id|ambauart_console_device
comma
dot
id|setup
op_assign
id|ambauart_console_setup
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
DECL|function|ambauart_console_init
r_void
id|__init
id|ambauart_console_init
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|amba_console
)paren
suffix:semicolon
)brace
DECL|macro|AMBA_CONSOLE
mdefine_line|#define AMBA_CONSOLE&t;&amp;amba_console
macro_line|#else
DECL|macro|AMBA_CONSOLE
mdefine_line|#define AMBA_CONSOLE&t;NULL
macro_line|#endif
DECL|variable|amba_reg
r_static
r_struct
id|uart_driver
id|amba_reg
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
l_string|&quot;ttyAM&quot;
comma
dot
id|dev_name
op_assign
l_string|&quot;ttyAM%d&quot;
comma
dot
id|major
op_assign
id|SERIAL_AMBA_MAJOR
comma
dot
id|minor
op_assign
id|SERIAL_AMBA_MINOR
comma
dot
id|nr
op_assign
id|UART_NR
comma
dot
id|cons
op_assign
id|AMBA_CONSOLE
comma
)brace
suffix:semicolon
DECL|function|ambauart_init
r_static
r_int
id|__init
id|ambauart_init
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
l_string|&quot;Serial: AMBA driver $Revision: 1.41 $&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|uart_register_driver
c_func
(paren
op_amp
id|amba_reg
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
id|amba_reg
comma
op_amp
id|amba_ports
(braket
id|i
)braket
dot
id|port
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ambauart_exit
r_static
r_void
id|__exit
id|ambauart_exit
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
id|amba_reg
comma
op_amp
id|amba_ports
(braket
id|i
)braket
dot
id|port
)paren
suffix:semicolon
id|uart_unregister_driver
c_func
(paren
op_amp
id|amba_reg
)paren
suffix:semicolon
)brace
DECL|variable|ambauart_init
id|module_init
c_func
(paren
id|ambauart_init
)paren
suffix:semicolon
DECL|variable|ambauart_exit
id|module_exit
c_func
(paren
id|ambauart_exit
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;ARM Ltd/Deep Blue Solutions Ltd&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ARM AMBA serial port driver $Revision: 1.41 $&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
