multiline_comment|/* drivers/serial/serial_lh7a40x.c&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
multiline_comment|/* Driver for Sharp LH7A40X embedded serial ports&n; *&n; *  Based on drivers/char/serial.c, by Linus Torvalds, Theodore Ts&squot;o.&n; *  Based on drivers/serial/amba.c, by Deep Blue Solutions Ltd.&n; *&n; *  ---&n; *&n; * This driver supports the embedded UARTs of the Sharp LH7A40X series&n; * CPUs.  While similar to the 16550 and other UART chips, there is&n; * nothing close to register compatibility.  Moreover, some of the&n; * modem control lines are not available, either in the chip or they&n; * are lacking in the board-level implementation.&n; *&n; * - Use of SIRDIS&n; *   For simplicity, we disable the IR functions of any UART whenever&n; *   we enable it.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_SERIAL_LH7A40X_CONSOLE) &amp;&amp; defined(CONFIG_MAGIC_SYSRQ)
DECL|macro|SUPPORT_SYSRQ
mdefine_line|#define SUPPORT_SYSRQ
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|DEV_MAJOR
mdefine_line|#define DEV_MAJOR&t;204
DECL|macro|DEV_MINOR
mdefine_line|#define DEV_MINOR&t;16
DECL|macro|DEV_NR
mdefine_line|#define DEV_NR&t;&t;3
DECL|macro|ISR_LOOP_LIMIT
mdefine_line|#define ISR_LOOP_LIMIT&t;256
DECL|macro|UR
mdefine_line|#define UR(p,o)&t;_UR ((p)-&gt;membase, o)
DECL|macro|_UR
mdefine_line|#define _UR(b,o) (*((volatile unsigned int*)(((unsigned char*) b) + (o))))
DECL|macro|BIT_CLR
mdefine_line|#define BIT_CLR(p,o,m)&t;UR(p,o) = UR(p,o) &amp; (~(unsigned int)m)
DECL|macro|BIT_SET
mdefine_line|#define BIT_SET(p,o,m)&t;UR(p,o) = UR(p,o) | ( (unsigned int)m)
DECL|macro|UART_REG_SIZE
mdefine_line|#define UART_REG_SIZE&t;32
DECL|macro|UART_R_DATA
mdefine_line|#define UART_R_DATA&t;(0x00)
DECL|macro|UART_R_FCON
mdefine_line|#define UART_R_FCON&t;(0x04)
DECL|macro|UART_R_BRCON
mdefine_line|#define UART_R_BRCON&t;(0x08)
DECL|macro|UART_R_CON
mdefine_line|#define UART_R_CON&t;(0x0c)
DECL|macro|UART_R_STATUS
mdefine_line|#define UART_R_STATUS&t;(0x10)
DECL|macro|UART_R_RAWISR
mdefine_line|#define UART_R_RAWISR&t;(0x14)
DECL|macro|UART_R_INTEN
mdefine_line|#define UART_R_INTEN&t;(0x18)
DECL|macro|UART_R_ISR
mdefine_line|#define UART_R_ISR&t;(0x1c)
DECL|macro|UARTEN
mdefine_line|#define UARTEN&t;&t;(0x01)&t;&t;/* UART enable */
DECL|macro|SIRDIS
mdefine_line|#define SIRDIS&t;&t;(0x02)&t;&t;/* Serial IR disable (UART1 only) */
DECL|macro|RxEmpty
mdefine_line|#define RxEmpty&t;&t;(0x10)
DECL|macro|TxEmpty
mdefine_line|#define TxEmpty&t;&t;(0x80)
DECL|macro|TxFull
mdefine_line|#define TxFull&t;&t;(0x20)
DECL|macro|nRxRdy
mdefine_line|#define nRxRdy&t;&t;RxEmpty
DECL|macro|nTxRdy
mdefine_line|#define nTxRdy&t;&t;TxFull
DECL|macro|TxBusy
mdefine_line|#define TxBusy&t;&t;(0x08)
DECL|macro|RxBreak
mdefine_line|#define RxBreak&t;&t;(0x0800)
DECL|macro|RxOverrunError
mdefine_line|#define RxOverrunError&t;(0x0400)
DECL|macro|RxParityError
mdefine_line|#define RxParityError&t;(0x0200)
DECL|macro|RxFramingError
mdefine_line|#define RxFramingError&t;(0x0100)
DECL|macro|RxError
mdefine_line|#define RxError     (RxBreak | RxOverrunError | RxParityError | RxFramingError)
DECL|macro|DCD
mdefine_line|#define DCD&t;&t;(0x04)
DECL|macro|DSR
mdefine_line|#define DSR&t;&t;(0x02)
DECL|macro|CTS
mdefine_line|#define CTS&t;&t;(0x01)
DECL|macro|RxInt
mdefine_line|#define RxInt&t;&t;(0x01)
DECL|macro|TxInt
mdefine_line|#define TxInt&t;&t;(0x02)
DECL|macro|ModemInt
mdefine_line|#define ModemInt&t;(0x04)
DECL|macro|RxTimeoutInt
mdefine_line|#define RxTimeoutInt&t;(0x08)
DECL|macro|MSEOI
mdefine_line|#define MSEOI&t;&t;(0x10)
DECL|macro|WLEN_8
mdefine_line|#define WLEN_8&t;&t;(0x60)
DECL|macro|WLEN_7
mdefine_line|#define WLEN_7&t;&t;(0x40)
DECL|macro|WLEN_6
mdefine_line|#define WLEN_6&t;&t;(0x20)
DECL|macro|WLEN_5
mdefine_line|#define WLEN_5&t;&t;(0x00)
DECL|macro|WLEN
mdefine_line|#define WLEN&t;&t;(0x60)&t;/* Mask for all word-length bits */
DECL|macro|STP2
mdefine_line|#define STP2&t;&t;(0x08)
DECL|macro|PEN
mdefine_line|#define PEN&t;&t;(0x02)&t;/* Parity Enable */
DECL|macro|EPS
mdefine_line|#define EPS&t;&t;(0x04)&t;/* Even Parity Set */
DECL|macro|FEN
mdefine_line|#define FEN&t;&t;(0x10)&t;/* FIFO Enable */
DECL|macro|BRK
mdefine_line|#define BRK&t;&t;(0x01)&t;/* Send Break */
DECL|struct|uart_port_lh7a40x
r_struct
id|uart_port_lh7a40x
(brace
DECL|member|port
r_struct
id|uart_port
id|port
suffix:semicolon
DECL|member|statusPrev
r_int
r_int
id|statusPrev
suffix:semicolon
multiline_comment|/* Most recently read modem status */
)brace
suffix:semicolon
DECL|function|lh7a40xuart_stop_tx
r_static
r_void
id|lh7a40xuart_stop_tx
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
id|BIT_CLR
(paren
id|port
comma
id|UART_R_INTEN
comma
id|TxInt
)paren
suffix:semicolon
)brace
DECL|function|lh7a40xuart_start_tx
r_static
r_void
id|lh7a40xuart_start_tx
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
id|BIT_SET
(paren
id|port
comma
id|UART_R_INTEN
comma
id|TxInt
)paren
suffix:semicolon
multiline_comment|/* *** FIXME: do I need to check for startup of the&n;&t;&t;      transmitter?  The old driver did, but AMBA&n;&t;&t;      doesn&squot;t . */
)brace
DECL|function|lh7a40xuart_stop_rx
r_static
r_void
id|lh7a40xuart_stop_rx
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|BIT_SET
(paren
id|port
comma
id|UART_R_INTEN
comma
id|RxTimeoutInt
op_or
id|RxInt
)paren
suffix:semicolon
)brace
DECL|function|lh7a40xuart_enable_ms
r_static
r_void
id|lh7a40xuart_enable_ms
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|BIT_SET
(paren
id|port
comma
id|UART_R_INTEN
comma
id|ModemInt
)paren
suffix:semicolon
)brace
r_static
r_void
macro_line|#ifdef SUPPORT_SYSRQ
DECL|function|lh7a40xuart_rx_chars
id|lh7a40xuart_rx_chars
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
id|lh7a40xuart_rx_chars
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
id|cbRxMax
op_assign
l_int|256
suffix:semicolon
multiline_comment|/* (Gross) limit on receive */
r_int
r_int
id|data
comma
id|flag
suffix:semicolon
multiline_comment|/* Received data and status */
r_while
c_loop
(paren
op_logical_neg
(paren
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
op_amp
id|nRxRdy
)paren
op_logical_and
op_decrement
id|cbRxMax
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
r_if
c_cond
(paren
id|tty-&gt;low_latency
)paren
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If this failed then we will throw away the&n;&t;&t;&t; * bytes but must do so to clear interrupts&n;&t;&t;&t; */
)brace
id|data
op_assign
id|UR
(paren
id|port
comma
id|UART_R_DATA
)paren
suffix:semicolon
id|flag
op_assign
id|TTY_NORMAL
suffix:semicolon
op_increment
id|port-&gt;icount.rx
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|RxError
)paren
(brace
multiline_comment|/* Quick check, short-circuit */
r_if
c_cond
(paren
id|data
op_amp
id|RxBreak
)paren
(brace
id|data
op_and_assign
op_complement
(paren
id|RxFramingError
op_or
id|RxParityError
)paren
suffix:semicolon
op_increment
id|port-&gt;icount.brk
suffix:semicolon
r_if
c_cond
(paren
id|uart_handle_break
(paren
id|port
)paren
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data
op_amp
id|RxParityError
)paren
op_increment
id|port-&gt;icount.parity
suffix:semicolon
r_else
r_if
c_cond
(paren
id|data
op_amp
id|RxFramingError
)paren
op_increment
id|port-&gt;icount.frame
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|RxOverrunError
)paren
op_increment
id|port-&gt;icount.overrun
suffix:semicolon
multiline_comment|/* Mask by termios, leave Rx&squot;d byte */
id|data
op_and_assign
id|port-&gt;read_status_mask
op_or
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|RxBreak
)paren
id|flag
op_assign
id|TTY_BREAK
suffix:semicolon
r_else
r_if
c_cond
(paren
id|data
op_amp
id|RxParityError
)paren
id|flag
op_assign
id|TTY_PARITY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|data
op_amp
id|RxFramingError
)paren
id|flag
op_assign
id|TTY_FRAME
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uart_handle_sysrq_char
(paren
id|port
comma
(paren
r_int
r_char
)paren
id|data
comma
id|regs
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data
op_amp
id|port-&gt;ignore_status_mask
)paren
op_eq
l_int|0
)paren
(brace
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
id|data
comma
id|flag
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|data
op_amp
id|RxOverrunError
)paren
op_logical_and
id|tty-&gt;flip.count
OL
id|TTY_FLIPBUF_SIZE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Overrun is special, since it&squot;s reported&n;&t;&t;&t; * immediately, and doesn&squot;t affect the current&n;&t;&t;&t; * character&n;&t;&t;&t; */
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
l_int|0
comma
id|TTY_OVERRUN
)paren
suffix:semicolon
)brace
)brace
id|tty_flip_buffer_push
(paren
id|tty
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|lh7a40xuart_tx_chars
r_static
r_void
id|lh7a40xuart_tx_chars
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
id|cbTxMax
op_assign
id|port-&gt;fifosize
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;x_char
)paren
(brace
id|UR
(paren
id|port
comma
id|UART_R_DATA
)paren
op_assign
id|port-&gt;x_char
suffix:semicolon
op_increment
id|port-&gt;icount.tx
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
(paren
id|xmit
)paren
op_logical_or
id|uart_tx_stopped
(paren
id|port
)paren
)paren
(brace
id|lh7a40xuart_stop_tx
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Unlike the AMBA UART, the lh7a40x UART does not guarantee&n;&t;   that at least half of the FIFO is empty.  Instead, we check&n;&t;   status for every character.  Using the AMBA method causes&n;&t;   the transmitter to drop characters. */
r_do
(brace
id|UR
(paren
id|port
comma
id|UART_R_DATA
)paren
op_assign
id|xmit-&gt;buf
(braket
id|xmit-&gt;tail
)braket
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
op_increment
id|port-&gt;icount.tx
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
op_logical_neg
(paren
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
op_amp
id|nTxRdy
)paren
op_logical_and
id|cbTxMax
op_decrement
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uart_circ_chars_pending
(paren
id|xmit
)paren
OL
id|WAKEUP_CHARS
)paren
id|uart_write_wakeup
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uart_circ_empty
(paren
id|xmit
)paren
)paren
id|lh7a40xuart_stop_tx
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|lh7a40xuart_modem_status
r_static
r_void
id|lh7a40xuart_modem_status
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
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
suffix:semicolon
r_int
r_int
id|delta
op_assign
id|status
op_xor
(paren
(paren
r_struct
id|uart_port_lh7a40x
op_star
)paren
id|port
)paren
op_member_access_from_pointer
id|statusPrev
suffix:semicolon
id|BIT_SET
(paren
id|port
comma
id|UART_R_RAWISR
comma
id|MSEOI
)paren
suffix:semicolon
multiline_comment|/* Clear modem status intr */
r_if
c_cond
(paren
op_logical_neg
id|delta
)paren
multiline_comment|/* Only happens if we missed 2 transitions */
r_return
suffix:semicolon
(paren
(paren
r_struct
id|uart_port_lh7a40x
op_star
)paren
id|port
)paren
op_member_access_from_pointer
id|statusPrev
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
id|DCD
)paren
id|uart_handle_dcd_change
(paren
id|port
comma
id|status
op_amp
id|DCD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
id|DSR
)paren
op_increment
id|port-&gt;icount.dsr
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
id|CTS
)paren
id|uart_handle_cts_change
(paren
id|port
comma
id|status
op_amp
id|CTS
)paren
suffix:semicolon
id|wake_up_interruptible
(paren
op_amp
id|port-&gt;info-&gt;delta_msr_wait
)paren
suffix:semicolon
)brace
DECL|function|lh7a40xuart_int
r_static
id|irqreturn_t
id|lh7a40xuart_int
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
id|cLoopLimit
op_assign
id|ISR_LOOP_LIMIT
suffix:semicolon
r_int
r_int
id|isr
op_assign
id|UR
(paren
id|port
comma
id|UART_R_ISR
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|isr
op_amp
(paren
id|RxInt
op_or
id|RxTimeoutInt
)paren
)paren
macro_line|#ifdef SUPPORT_SYSRQ
id|lh7a40xuart_rx_chars
c_func
(paren
id|port
comma
id|regs
)paren
suffix:semicolon
macro_line|#else
id|lh7a40xuart_rx_chars
c_func
(paren
id|port
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|isr
op_amp
id|ModemInt
)paren
id|lh7a40xuart_modem_status
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isr
op_amp
id|TxInt
)paren
id|lh7a40xuart_tx_chars
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|cLoopLimit
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|isr
op_assign
id|UR
(paren
id|port
comma
id|UART_R_ISR
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|isr
op_amp
(paren
id|RxInt
op_or
id|TxInt
op_or
id|RxTimeoutInt
)paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|lh7a40xuart_tx_empty
r_static
r_int
r_int
id|lh7a40xuart_tx_empty
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
(paren
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
op_amp
id|TxEmpty
)paren
ques
c_cond
id|TIOCSER_TEMT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|lh7a40xuart_get_mctrl
r_static
r_int
r_int
id|lh7a40xuart_get_mctrl
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
op_assign
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|DCD
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
id|DSR
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
id|CTS
)paren
id|result
op_or_assign
id|TIOCM_CTS
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|lh7a40xuart_set_mctrl
r_static
r_void
id|lh7a40xuart_set_mctrl
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
multiline_comment|/* None of the ports supports DTR. UART1 supports RTS through GPIO. */
multiline_comment|/* Note, kernel appears to be setting DTR and RTS on console. */
multiline_comment|/* *** FIXME: this deserves more work.  There&squot;s some work in&n;               tracing all of the IO pins. */
macro_line|#if 0
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|UART1_PHYS
)paren
(brace
id|gpioRegs_t
op_star
id|gpio
op_assign
(paren
id|gpioRegs_t
op_star
)paren
id|IO_ADDRESS
c_func
(paren
id|GPIO_PHYS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|gpio-&gt;pbdr
op_and_assign
op_complement
id|GPIOB_UART1_RTS
suffix:semicolon
r_else
id|gpio-&gt;pbdr
op_or_assign
id|GPIOB_UART1_RTS
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|lh7a40xuart_break_ctl
r_static
r_void
id|lh7a40xuart_break_ctl
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;lock
comma
id|flags
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
id|BIT_SET
(paren
id|port
comma
id|UART_R_FCON
comma
id|BRK
)paren
suffix:semicolon
multiline_comment|/* Assert break */
r_else
id|BIT_CLR
(paren
id|port
comma
id|UART_R_FCON
comma
id|BRK
)paren
suffix:semicolon
multiline_comment|/* Deassert break */
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
DECL|function|lh7a40xuart_startup
r_static
r_int
id|lh7a40xuart_startup
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
id|retval
op_assign
id|request_irq
(paren
id|port-&gt;irq
comma
id|lh7a40xuart_int
comma
l_int|0
comma
l_string|&quot;serial_lh7a40x&quot;
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
multiline_comment|/* Initial modem control-line settings */
(paren
(paren
r_struct
id|uart_port_lh7a40x
op_star
)paren
id|port
)paren
op_member_access_from_pointer
id|statusPrev
op_assign
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
suffix:semicolon
multiline_comment|/* There is presently no configuration option to enable IR.&n;&t;   Thus, we always disable it. */
id|BIT_SET
(paren
id|port
comma
id|UART_R_CON
comma
id|UARTEN
op_or
id|SIRDIS
)paren
suffix:semicolon
id|BIT_SET
(paren
id|port
comma
id|UART_R_INTEN
comma
id|RxTimeoutInt
op_or
id|RxInt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lh7a40xuart_shutdown
r_static
r_void
id|lh7a40xuart_shutdown
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|free_irq
(paren
id|port-&gt;irq
comma
id|port
)paren
suffix:semicolon
id|BIT_CLR
(paren
id|port
comma
id|UART_R_FCON
comma
id|BRK
op_or
id|FEN
)paren
suffix:semicolon
id|BIT_CLR
(paren
id|port
comma
id|UART_R_CON
comma
id|UARTEN
)paren
suffix:semicolon
)brace
DECL|function|lh7a40xuart_set_termios
r_static
r_void
id|lh7a40xuart_set_termios
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
id|con
suffix:semicolon
r_int
r_int
id|inten
suffix:semicolon
r_int
r_int
id|fcon
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|baud
suffix:semicolon
r_int
r_int
id|quot
suffix:semicolon
id|baud
op_assign
id|uart_get_baud_rate
(paren
id|port
comma
id|termios
comma
id|old
comma
l_int|8
comma
id|port-&gt;uartclk
op_div
l_int|16
)paren
suffix:semicolon
id|quot
op_assign
id|uart_get_divisor
(paren
id|port
comma
id|baud
)paren
suffix:semicolon
multiline_comment|/* -1 performed elsewhere */
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
id|fcon
op_assign
id|WLEN_5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|fcon
op_assign
id|WLEN_6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|fcon
op_assign
id|WLEN_7
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS8
suffix:colon
r_default
suffix:colon
id|fcon
op_assign
id|WLEN_8
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
id|fcon
op_or_assign
id|STP2
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_cflag
op_amp
id|PARENB
)paren
(brace
id|fcon
op_or_assign
id|PEN
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
id|fcon
op_or_assign
id|EPS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;fifosize
OG
l_int|1
)paren
id|fcon
op_or_assign
id|FEN
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|uart_update_timeout
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
id|RxOverrunError
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
id|RxFramingError
op_or
id|RxParityError
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
(paren
id|BRKINT
op_or
id|PARMRK
)paren
)paren
id|port-&gt;read_status_mask
op_or_assign
id|RxBreak
suffix:semicolon
multiline_comment|/* Figure mask for status we ignore */
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
id|RxFramingError
op_or
id|RxParityError
suffix:semicolon
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
id|IGNBRK
)paren
(brace
id|port-&gt;ignore_status_mask
op_or_assign
id|RxBreak
suffix:semicolon
multiline_comment|/* Ignore overrun when ignorning parity */
multiline_comment|/* *** FIXME: is this in the right place? */
r_if
c_cond
(paren
id|termios-&gt;c_iflag
op_amp
id|IGNPAR
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|RxOverrunError
suffix:semicolon
)brace
multiline_comment|/* Ignore all receive errors when receive disabled */
r_if
c_cond
(paren
(paren
id|termios-&gt;c_cflag
op_amp
id|CREAD
)paren
op_eq
l_int|0
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|RxError
suffix:semicolon
id|con
op_assign
id|UR
(paren
id|port
comma
id|UART_R_CON
)paren
suffix:semicolon
id|inten
op_assign
(paren
id|UR
(paren
id|port
comma
id|UART_R_INTEN
)paren
op_amp
op_complement
id|ModemInt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UART_ENABLE_MS
(paren
id|port
comma
id|termios-&gt;c_cflag
)paren
)paren
id|inten
op_or_assign
id|ModemInt
suffix:semicolon
id|BIT_CLR
(paren
id|port
comma
id|UART_R_CON
comma
id|UARTEN
)paren
suffix:semicolon
multiline_comment|/* Disable UART */
id|UR
(paren
id|port
comma
id|UART_R_INTEN
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Disable interrupts */
id|UR
(paren
id|port
comma
id|UART_R_BRCON
)paren
op_assign
id|quot
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Set baud rate divisor */
id|UR
(paren
id|port
comma
id|UART_R_FCON
)paren
op_assign
id|fcon
suffix:semicolon
multiline_comment|/* Set FIFO and frame ctrl */
id|UR
(paren
id|port
comma
id|UART_R_INTEN
)paren
op_assign
id|inten
suffix:semicolon
multiline_comment|/* Enable interrupts */
id|UR
(paren
id|port
comma
id|UART_R_CON
)paren
op_assign
id|con
suffix:semicolon
multiline_comment|/* Restore UART mode */
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
DECL|function|lh7a40xuart_type
r_static
r_const
r_char
op_star
id|lh7a40xuart_type
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
id|PORT_LH7A40X
ques
c_cond
l_string|&quot;LH7A40X&quot;
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|lh7a40xuart_release_port
r_static
r_void
id|lh7a40xuart_release_port
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|release_mem_region
(paren
id|port-&gt;mapbase
comma
id|UART_REG_SIZE
)paren
suffix:semicolon
)brace
DECL|function|lh7a40xuart_request_port
r_static
r_int
id|lh7a40xuart_request_port
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|request_mem_region
(paren
id|port-&gt;mapbase
comma
id|UART_REG_SIZE
comma
l_string|&quot;serial_lh7a40x&quot;
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
DECL|function|lh7a40xuart_config_port
r_static
r_void
id|lh7a40xuart_config_port
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
id|PORT_LH7A40X
suffix:semicolon
id|lh7a40xuart_request_port
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|lh7a40xuart_verify_port
r_static
r_int
id|lh7a40xuart_verify_port
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
id|PORT_LH7A40X
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
multiline_comment|/* *** FIXME: is this true? */
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|lh7a40x_uart_ops
r_static
r_struct
id|uart_ops
id|lh7a40x_uart_ops
op_assign
(brace
dot
id|tx_empty
op_assign
id|lh7a40xuart_tx_empty
comma
dot
id|set_mctrl
op_assign
id|lh7a40xuart_set_mctrl
comma
dot
id|get_mctrl
op_assign
id|lh7a40xuart_get_mctrl
comma
dot
id|stop_tx
op_assign
id|lh7a40xuart_stop_tx
comma
dot
id|start_tx
op_assign
id|lh7a40xuart_start_tx
comma
dot
id|stop_rx
op_assign
id|lh7a40xuart_stop_rx
comma
dot
id|enable_ms
op_assign
id|lh7a40xuart_enable_ms
comma
dot
id|break_ctl
op_assign
id|lh7a40xuart_break_ctl
comma
dot
id|startup
op_assign
id|lh7a40xuart_startup
comma
dot
id|shutdown
op_assign
id|lh7a40xuart_shutdown
comma
dot
id|set_termios
op_assign
id|lh7a40xuart_set_termios
comma
dot
id|type
op_assign
id|lh7a40xuart_type
comma
dot
id|release_port
op_assign
id|lh7a40xuart_release_port
comma
dot
id|request_port
op_assign
id|lh7a40xuart_request_port
comma
dot
id|config_port
op_assign
id|lh7a40xuart_config_port
comma
dot
id|verify_port
op_assign
id|lh7a40xuart_verify_port
comma
)brace
suffix:semicolon
DECL|variable|lh7a40x_ports
r_static
r_struct
id|uart_port_lh7a40x
id|lh7a40x_ports
(braket
id|DEV_NR
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
id|io_p2v
(paren
id|UART1_PHYS
)paren
comma
dot
id|mapbase
op_assign
id|UART1_PHYS
comma
dot
id|iotype
op_assign
id|SERIAL_IO_MEM
comma
dot
id|irq
op_assign
id|IRQ_UART1INTR
comma
dot
id|uartclk
op_assign
l_int|14745600
op_div
l_int|2
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
id|lh7a40x_uart_ops
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
id|io_p2v
(paren
id|UART2_PHYS
)paren
comma
dot
id|mapbase
op_assign
id|UART2_PHYS
comma
dot
id|iotype
op_assign
id|SERIAL_IO_MEM
comma
dot
id|irq
op_assign
id|IRQ_UART2INTR
comma
dot
id|uartclk
op_assign
l_int|14745600
op_div
l_int|2
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
id|lh7a40x_uart_ops
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
id|io_p2v
(paren
id|UART3_PHYS
)paren
comma
dot
id|mapbase
op_assign
id|UART3_PHYS
comma
dot
id|iotype
op_assign
id|SERIAL_IO_MEM
comma
dot
id|irq
op_assign
id|IRQ_UART3INTR
comma
dot
id|uartclk
op_assign
l_int|14745600
op_div
l_int|2
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
id|lh7a40x_uart_ops
comma
dot
id|flags
op_assign
id|ASYNC_BOOT_AUTOCONF
comma
dot
id|line
op_assign
l_int|2
comma
)brace
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#ifndef CONFIG_SERIAL_LH7A40X_CONSOLE
DECL|macro|LH7A40X_CONSOLE
macro_line|# define LH7A40X_CONSOLE NULL
macro_line|#else
DECL|macro|LH7A40X_CONSOLE
macro_line|# define LH7A40X_CONSOLE &amp;lh7a40x_console
DECL|function|lh7a40xuart_console_write
r_static
r_void
id|lh7a40xuart_console_write
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
id|lh7a40x_ports
(braket
id|co-&gt;index
)braket
dot
id|port
suffix:semicolon
r_int
r_int
id|con
op_assign
id|UR
(paren
id|port
comma
id|UART_R_CON
)paren
suffix:semicolon
r_int
r_int
id|inten
op_assign
id|UR
(paren
id|port
comma
id|UART_R_INTEN
)paren
suffix:semicolon
id|UR
(paren
id|port
comma
id|UART_R_INTEN
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Disable all interrupts */
id|BIT_SET
(paren
id|port
comma
id|UART_R_CON
comma
id|UARTEN
op_or
id|SIRDIS
)paren
suffix:semicolon
multiline_comment|/* Enable UART */
r_for
c_loop
(paren
suffix:semicolon
id|count
op_decrement
OG
l_int|0
suffix:semicolon
op_increment
id|s
)paren
(brace
r_while
c_loop
(paren
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
op_amp
id|nTxRdy
)paren
suffix:semicolon
id|UR
(paren
id|port
comma
id|UART_R_DATA
)paren
op_assign
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
(paren
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
op_amp
id|TxBusy
)paren
)paren
suffix:semicolon
id|UR
(paren
id|port
comma
id|UART_R_DATA
)paren
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
multiline_comment|/* Wait until all characters are sent */
r_while
c_loop
(paren
id|UR
(paren
id|port
comma
id|UART_R_STATUS
)paren
op_amp
id|TxBusy
)paren
suffix:semicolon
multiline_comment|/* Restore control and interrupt mask */
id|UR
(paren
id|port
comma
id|UART_R_CON
)paren
op_assign
id|con
suffix:semicolon
id|UR
(paren
id|port
comma
id|UART_R_INTEN
)paren
op_assign
id|inten
suffix:semicolon
)brace
DECL|function|lh7a40xuart_console_get_options
r_static
r_void
id|__init
id|lh7a40xuart_console_get_options
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
id|UR
(paren
id|port
comma
id|UART_R_CON
)paren
op_amp
id|UARTEN
)paren
(brace
r_int
r_int
id|fcon
op_assign
id|UR
(paren
id|port
comma
id|UART_R_FCON
)paren
suffix:semicolon
r_int
r_int
id|quot
op_assign
id|UR
(paren
id|port
comma
id|UART_R_BRCON
)paren
op_plus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|fcon
op_amp
(paren
id|PEN
op_or
id|EPS
)paren
)paren
(brace
r_default
suffix:colon
op_star
id|parity
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PEN
suffix:colon
op_star
id|parity
op_assign
l_char|&squot;o&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PEN
op_or
id|EPS
suffix:colon
op_star
id|parity
op_assign
l_char|&squot;e&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|fcon
op_amp
id|WLEN
)paren
(brace
r_default
suffix:colon
r_case
id|WLEN_8
suffix:colon
op_star
id|bits
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WLEN_7
suffix:colon
op_star
id|bits
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WLEN_6
suffix:colon
op_star
id|bits
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WLEN_5
suffix:colon
op_star
id|bits
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|baud
op_assign
id|port-&gt;uartclk
op_div
(paren
l_int|16
op_star
id|quot
)paren
suffix:semicolon
)brace
)brace
DECL|function|lh7a40xuart_console_setup
r_static
r_int
id|__init
id|lh7a40xuart_console_setup
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
r_if
c_cond
(paren
id|co-&gt;index
op_ge
id|DEV_NR
)paren
multiline_comment|/* Bounds check on device number */
id|co-&gt;index
op_assign
l_int|0
suffix:semicolon
id|port
op_assign
op_amp
id|lh7a40x_ports
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
id|lh7a40xuart_console_get_options
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
r_extern
r_struct
id|uart_driver
id|lh7a40x_reg
suffix:semicolon
DECL|variable|lh7a40x_console
r_static
r_struct
id|console
id|lh7a40x_console
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
id|lh7a40xuart_console_write
comma
dot
id|device
op_assign
id|uart_console_device
comma
dot
id|setup
op_assign
id|lh7a40xuart_console_setup
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
dot
id|data
op_assign
op_amp
id|lh7a40x_reg
comma
)brace
suffix:semicolon
DECL|function|lh7a40xuart_console_init
r_static
r_int
id|__init
id|lh7a40xuart_console_init
c_func
(paren
r_void
)paren
(brace
id|register_console
(paren
op_amp
id|lh7a40x_console
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lh7a40xuart_console_init
id|console_initcall
(paren
id|lh7a40xuart_console_init
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|lh7a40x_reg
r_static
r_struct
id|uart_driver
id|lh7a40x_reg
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
l_string|&quot;ttyAM&quot;
comma
dot
id|major
op_assign
id|DEV_MAJOR
comma
dot
id|minor
op_assign
id|DEV_MINOR
comma
dot
id|nr
op_assign
id|DEV_NR
comma
dot
id|cons
op_assign
id|LH7A40X_CONSOLE
comma
)brace
suffix:semicolon
DECL|function|lh7a40xuart_init
r_static
r_int
id|__init
id|lh7a40xuart_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;serial: LH7A40X serial driver&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|uart_register_driver
(paren
op_amp
id|lh7a40x_reg
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
id|DEV_NR
suffix:semicolon
id|i
op_increment
)paren
id|uart_add_one_port
(paren
op_amp
id|lh7a40x_reg
comma
op_amp
id|lh7a40x_ports
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
DECL|function|lh7a40xuart_exit
r_static
r_void
id|__exit
id|lh7a40xuart_exit
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
id|DEV_NR
suffix:semicolon
id|i
op_increment
)paren
id|uart_remove_one_port
(paren
op_amp
id|lh7a40x_reg
comma
op_amp
id|lh7a40x_ports
(braket
id|i
)braket
dot
id|port
)paren
suffix:semicolon
id|uart_unregister_driver
(paren
op_amp
id|lh7a40x_reg
)paren
suffix:semicolon
)brace
DECL|variable|lh7a40xuart_init
id|module_init
(paren
id|lh7a40xuart_init
)paren
suffix:semicolon
DECL|variable|lh7a40xuart_exit
id|module_exit
(paren
id|lh7a40xuart_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Marc Singer&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Sharp LH7A40X serial port driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
