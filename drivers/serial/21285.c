multiline_comment|/*&n; * linux/drivers/char/21285.c&n; *&n; * Driver for the serial port on the 21285 StrongArm-110 core logic chip.&n; *&n; * Based on drivers/char/serial.c&n; *&n; *  $Id: 21285.c,v 1.34 2002/07/22 15:27:32 rmk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
DECL|macro|BAUD_BASE
mdefine_line|#define BAUD_BASE&t;&t;(mem_fclk_21285/64)
DECL|macro|SERIAL_21285_NAME
mdefine_line|#define SERIAL_21285_NAME&t;&quot;ttyFB&quot;
DECL|macro|SERIAL_21285_MAJOR
mdefine_line|#define SERIAL_21285_MAJOR&t;204
DECL|macro|SERIAL_21285_MINOR
mdefine_line|#define SERIAL_21285_MINOR&t;4
DECL|macro|RXSTAT_DUMMY_READ
mdefine_line|#define RXSTAT_DUMMY_READ&t;0x80000000
DECL|macro|RXSTAT_FRAME
mdefine_line|#define RXSTAT_FRAME&t;&t;(1 &lt;&lt; 0)
DECL|macro|RXSTAT_PARITY
mdefine_line|#define RXSTAT_PARITY&t;&t;(1 &lt;&lt; 1)
DECL|macro|RXSTAT_OVERRUN
mdefine_line|#define RXSTAT_OVERRUN&t;&t;(1 &lt;&lt; 2)
DECL|macro|RXSTAT_ANYERR
mdefine_line|#define RXSTAT_ANYERR&t;&t;(RXSTAT_FRAME|RXSTAT_PARITY|RXSTAT_OVERRUN)
DECL|macro|H_UBRLCR_BREAK
mdefine_line|#define H_UBRLCR_BREAK&t;&t;(1 &lt;&lt; 0)
DECL|macro|H_UBRLCR_PARENB
mdefine_line|#define H_UBRLCR_PARENB&t;&t;(1 &lt;&lt; 1)
DECL|macro|H_UBRLCR_PAREVN
mdefine_line|#define H_UBRLCR_PAREVN&t;&t;(1 &lt;&lt; 2)
DECL|macro|H_UBRLCR_STOPB
mdefine_line|#define H_UBRLCR_STOPB&t;&t;(1 &lt;&lt; 3)
DECL|macro|H_UBRLCR_FIFO
mdefine_line|#define H_UBRLCR_FIFO&t;&t;(1 &lt;&lt; 4)
DECL|variable|serial21285_name
r_static
r_const
r_char
id|serial21285_name
(braket
)braket
op_assign
l_string|&quot;Footbridge UART&quot;
suffix:semicolon
DECL|macro|tx_enabled
mdefine_line|#define tx_enabled(port)&t;((port)-&gt;unused[0])
DECL|macro|rx_enabled
mdefine_line|#define rx_enabled(port)&t;((port)-&gt;unused[1])
multiline_comment|/*&n; * The documented expression for selecting the divisor is:&n; *  BAUD_BASE / baud - 1&n; * However, typically BAUD_BASE is not divisible by baud, so&n; * we want to select the divisor that gives us the minimum&n; * error.  Therefore, we want:&n; *  int(BAUD_BASE / baud - 0.5) -&gt;&n; *  int(BAUD_BASE / baud - (baud &gt;&gt; 1) / baud) -&gt;&n; *  int((BAUD_BASE - (baud &gt;&gt; 1)) / baud)&n; */
r_static
r_void
DECL|function|serial21285_stop_tx
id|serial21285_stop_tx
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
id|IRQ_CONTX
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
DECL|function|serial21285_start_tx
id|serial21285_start_tx
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
id|IRQ_CONTX
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
DECL|function|serial21285_stop_rx
r_static
r_void
id|serial21285_stop_rx
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|rx_enabled
c_func
(paren
id|port
)paren
)paren
(brace
id|disable_irq
c_func
(paren
id|IRQ_CONRX
)paren
suffix:semicolon
id|rx_enabled
c_func
(paren
id|port
)paren
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|serial21285_enable_ms
r_static
r_void
id|serial21285_enable_ms
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
)brace
DECL|function|serial21285_rx_chars
r_static
r_void
id|serial21285_rx_chars
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
id|rxs
comma
id|max_count
op_assign
l_int|256
suffix:semicolon
id|status
op_assign
op_star
id|CSR_UARTFLG
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|status
op_amp
l_int|0x10
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
id|tty-&gt;flip.tqueue
dot
id|routine
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
op_star
id|CSR_UARTDR
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
id|rxs
op_assign
op_star
id|CSR_RXSTAT
op_or
id|RXSTAT_DUMMY_READ
suffix:semicolon
r_if
c_cond
(paren
id|rxs
op_amp
id|RXSTAT_ANYERR
)paren
(brace
r_if
c_cond
(paren
id|rxs
op_amp
id|RXSTAT_PARITY
)paren
id|port-&gt;icount.parity
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rxs
op_amp
id|RXSTAT_FRAME
)paren
id|port-&gt;icount.frame
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rxs
op_amp
id|RXSTAT_OVERRUN
)paren
id|port-&gt;icount.overrun
op_increment
suffix:semicolon
id|rxs
op_and_assign
id|port-&gt;read_status_mask
suffix:semicolon
r_if
c_cond
(paren
id|rxs
op_amp
id|RXSTAT_PARITY
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
id|rxs
op_amp
id|RXSTAT_FRAME
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
(paren
id|rxs
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
id|rxs
op_amp
id|RXSTAT_OVERRUN
)paren
op_logical_and
id|tty-&gt;flip.count
OL
id|TTY_FLIPBUF_SIZE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Overrun is special, since it&squot;s reported&n;&t;&t;&t; * immediately, and doesn&squot;t affect the current&n;&t;&t;&t; * character.&n;&t;&t;&t; */
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
id|status
op_assign
op_star
id|CSR_UARTFLG
suffix:semicolon
)brace
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
DECL|function|serial21285_tx_chars
r_static
r_void
id|serial21285_tx_chars
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
op_assign
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;x_char
)paren
(brace
op_star
id|CSR_UARTDR
op_assign
id|port-&gt;x_char
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
id|serial21285_stop_tx
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
r_do
(brace
op_star
id|CSR_UARTDR
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
op_logical_and
op_logical_neg
(paren
op_star
id|CSR_UARTFLG
op_amp
l_int|0x20
)paren
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
r_if
c_cond
(paren
id|uart_circ_empty
c_func
(paren
id|xmit
)paren
)paren
id|serial21285_stop_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|serial21285_tx_empty
r_static
r_int
r_int
id|serial21285_tx_empty
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
(paren
op_star
id|CSR_UARTFLG
op_amp
l_int|8
)paren
ques
c_cond
l_int|0
suffix:colon
id|TIOCSER_TEMT
suffix:semicolon
)brace
multiline_comment|/* no modem control lines */
DECL|function|serial21285_get_mctrl
r_static
r_int
r_int
id|serial21285_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|TIOCM_CAR
op_or
id|TIOCM_DSR
op_or
id|TIOCM_CTS
suffix:semicolon
)brace
DECL|function|serial21285_set_mctrl
r_static
r_void
id|serial21285_set_mctrl
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
DECL|function|serial21285_break_ctl
r_static
r_void
id|serial21285_break_ctl
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
id|h_lcr
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
id|h_lcr
op_assign
op_star
id|CSR_H_UBRLCR
suffix:semicolon
r_if
c_cond
(paren
id|break_state
)paren
id|h_lcr
op_or_assign
id|H_UBRLCR_BREAK
suffix:semicolon
r_else
id|h_lcr
op_and_assign
op_complement
id|H_UBRLCR_BREAK
suffix:semicolon
op_star
id|CSR_H_UBRLCR
op_assign
id|h_lcr
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
DECL|function|serial21285_startup
r_static
r_int
id|serial21285_startup
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
id|ret
suffix:semicolon
id|tx_enabled
c_func
(paren
id|port
)paren
op_assign
l_int|1
suffix:semicolon
id|rx_enabled
c_func
(paren
id|port
)paren
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|IRQ_CONRX
comma
id|serial21285_rx_chars
comma
l_int|0
comma
id|serial21285_name
comma
id|port
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
id|ret
op_assign
id|request_irq
c_func
(paren
id|IRQ_CONTX
comma
id|serial21285_tx_chars
comma
l_int|0
comma
id|serial21285_name
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|free_irq
c_func
(paren
id|IRQ_CONRX
comma
id|port
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|serial21285_shutdown
r_static
r_void
id|serial21285_shutdown
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|free_irq
c_func
(paren
id|IRQ_CONTX
comma
id|port
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_CONRX
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|serial21285_change_speed
id|serial21285_change_speed
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
id|h_lcr
suffix:semicolon
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
id|h_lcr
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|h_lcr
op_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|h_lcr
op_assign
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* CS8 */
id|h_lcr
op_assign
l_int|0x60
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
id|h_lcr
op_or_assign
id|H_UBRLCR_STOPB
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
(brace
id|h_lcr
op_or_assign
id|H_UBRLCR_PARENB
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
id|h_lcr
op_or_assign
id|H_UBRLCR_PAREVN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;fifosize
)paren
id|h_lcr
op_or_assign
id|H_UBRLCR_FIFO
suffix:semicolon
id|port-&gt;read_status_mask
op_assign
id|RXSTAT_OVERRUN
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
id|RXSTAT_FRAME
op_or
id|RXSTAT_PARITY
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
id|RXSTAT_FRAME
op_or
id|RXSTAT_PARITY
suffix:semicolon
r_if
c_cond
(paren
id|iflag
op_amp
id|IGNBRK
op_logical_and
id|iflag
op_amp
id|IGNPAR
)paren
id|port-&gt;ignore_status_mask
op_or_assign
id|RXSTAT_OVERRUN
suffix:semicolon
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
id|RXSTAT_DUMMY_READ
suffix:semicolon
id|quot
op_sub_assign
l_int|1
suffix:semicolon
op_star
id|CSR_UARTCON
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_L_UBRLCR
op_assign
id|quot
op_amp
l_int|0xff
suffix:semicolon
op_star
id|CSR_M_UBRLCR
op_assign
(paren
id|quot
op_rshift
l_int|8
)paren
op_amp
l_int|0x0f
suffix:semicolon
op_star
id|CSR_H_UBRLCR
op_assign
id|h_lcr
suffix:semicolon
op_star
id|CSR_UARTCON
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|serial21285_type
r_static
r_const
r_char
op_star
id|serial21285_type
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
id|PORT_21285
ques
c_cond
l_string|&quot;DC21285&quot;
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|serial21285_release_port
r_static
r_void
id|serial21285_release_port
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
l_int|32
)paren
suffix:semicolon
)brace
DECL|function|serial21285_request_port
r_static
r_int
id|serial21285_request_port
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
l_int|32
comma
id|serial21285_name
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
DECL|function|serial21285_config_port
r_static
r_void
id|serial21285_config_port
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
op_logical_and
id|serial21285_request_port
c_func
(paren
id|port
)paren
op_eq
l_int|0
)paren
id|port-&gt;type
op_assign
id|PORT_21285
suffix:semicolon
)brace
multiline_comment|/*&n; * verify the new serial_struct (for TIOCSSERIAL).&n; */
DECL|function|serial21285_verify_port
r_static
r_int
id|serial21285_verify_port
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
id|PORT_21285
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
op_ne
id|NO_IRQ
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
op_ne
id|port-&gt;uartclk
op_div
l_int|16
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
DECL|variable|serial21285_ops
r_static
r_struct
id|uart_ops
id|serial21285_ops
op_assign
(brace
dot
id|tx_empty
op_assign
id|serial21285_tx_empty
comma
dot
id|get_mctrl
op_assign
id|serial21285_get_mctrl
comma
dot
id|set_mctrl
op_assign
id|serial21285_set_mctrl
comma
dot
id|stop_tx
op_assign
id|serial21285_stop_tx
comma
dot
id|start_tx
op_assign
id|serial21285_start_tx
comma
dot
id|stop_rx
op_assign
id|serial21285_stop_rx
comma
dot
id|enable_ms
op_assign
id|serial21285_enable_ms
comma
dot
id|break_ctl
op_assign
id|serial21285_break_ctl
comma
dot
id|startup
op_assign
id|serial21285_startup
comma
dot
id|shutdown
op_assign
id|serial21285_shutdown
comma
dot
id|change_speed
op_assign
id|serial21285_change_speed
comma
dot
id|type
op_assign
id|serial21285_type
comma
dot
id|release_port
op_assign
id|serial21285_release_port
comma
dot
id|request_port
op_assign
id|serial21285_request_port
comma
dot
id|config_port
op_assign
id|serial21285_config_port
comma
dot
id|verify_port
op_assign
id|serial21285_verify_port
comma
)brace
suffix:semicolon
DECL|variable|serial21285_port
r_static
r_struct
id|uart_port
id|serial21285_port
op_assign
(brace
dot
id|membase
op_assign
l_int|0
comma
dot
id|mapbase
op_assign
l_int|0x42000160
comma
dot
id|iotype
op_assign
id|SERIAL_IO_MEM
comma
dot
id|irq
op_assign
id|NO_IRQ
comma
dot
id|uartclk
op_assign
l_int|0
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
id|serial21285_ops
comma
dot
id|flags
op_assign
id|ASYNC_BOOT_AUTOCONF
comma
)brace
suffix:semicolon
DECL|function|serial21285_setup_ports
r_static
r_void
id|serial21285_setup_ports
c_func
(paren
r_void
)paren
(brace
id|serial21285_port.uartclk
op_assign
id|mem_fclk_21285
op_div
l_int|4
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_21285_CONSOLE
r_static
r_void
DECL|function|serial21285_console_write
id|serial21285_console_write
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_while
c_loop
(paren
op_star
id|CSR_UARTFLG
op_amp
l_int|0x20
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
op_star
id|CSR_UARTDR
op_assign
id|s
(braket
id|i
)braket
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
r_while
c_loop
(paren
op_star
id|CSR_UARTFLG
op_amp
l_int|0x20
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
op_star
id|CSR_UARTDR
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
)brace
DECL|function|serial21285_console_device
r_static
id|kdev_t
id|serial21285_console_device
c_func
(paren
r_struct
id|console
op_star
id|c
)paren
(brace
r_return
id|mk_kdev
c_func
(paren
id|SERIAL_21285_MAJOR
comma
id|SERIAL_21285_MINOR
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|serial21285_get_options
id|serial21285_get_options
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
op_star
id|CSR_UARTCON
op_eq
l_int|1
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
op_star
id|CSR_H_UBRLCR
suffix:semicolon
r_switch
c_cond
(paren
id|tmp
op_amp
l_int|0x60
)paren
(brace
r_case
l_int|0x00
suffix:colon
op_star
id|bits
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20
suffix:colon
op_star
id|bits
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
op_star
id|bits
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
l_int|0x60
suffix:colon
op_star
id|bits
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp
op_amp
id|H_UBRLCR_PARENB
)paren
(brace
op_star
id|parity
op_assign
l_char|&squot;o&squot;
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|H_UBRLCR_PAREVN
)paren
op_star
id|parity
op_assign
l_char|&squot;e&squot;
suffix:semicolon
)brace
id|tmp
op_assign
op_star
id|CSR_L_UBRLCR
op_or
(paren
op_star
id|CSR_M_UBRLCR
op_lshift
l_int|8
)paren
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
id|tmp
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|serial21285_console_setup
r_static
r_int
id|__init
id|serial21285_console_setup
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
op_assign
op_amp
id|serial21285_port
suffix:semicolon
r_int
id|baud
op_assign
l_int|9600
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
id|machine_is_personal_server
c_func
(paren
)paren
)paren
id|baud
op_assign
l_int|57600
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether an invalid uart number has been specified, and&n;&t; * if so, search for the first available port that does have&n;&t; * console support.&n;&t; */
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
id|serial21285_get_options
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
macro_line|#ifdef CONFIG_SERIAL_21285_OLD
DECL|variable|serial21285_old_cons
r_static
r_struct
id|console
id|serial21285_old_cons
op_assign
(brace
dot
id|name
op_assign
id|SERIAL_21285_OLD_NAME
comma
dot
id|write
op_assign
id|serial21285_console_write
comma
dot
id|device
op_assign
id|serial21285_console_device
comma
dot
id|setup
op_assign
id|serial21285_console_setup
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
macro_line|#endif
DECL|variable|serial21285_console
r_static
r_struct
id|console
id|serial21285_console
op_assign
(brace
dot
id|name
op_assign
id|SERIAL_21285_NAME
comma
dot
id|write
op_assign
id|serial21285_console_write
comma
dot
id|device
op_assign
id|serial21285_console_device
comma
dot
id|setup
op_assign
id|serial21285_console_setup
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
DECL|function|rs285_console_init
r_void
id|__init
id|rs285_console_init
c_func
(paren
r_void
)paren
(brace
id|serial21285_setup_ports
c_func
(paren
)paren
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|serial21285_console
)paren
suffix:semicolon
)brace
DECL|macro|SERIAL_21285_CONSOLE
mdefine_line|#define SERIAL_21285_CONSOLE&t;&amp;serial21285_console
macro_line|#else
DECL|macro|SERIAL_21285_CONSOLE
mdefine_line|#define SERIAL_21285_CONSOLE&t;NULL
macro_line|#endif
DECL|variable|serial21285_reg
r_static
r_struct
id|uart_driver
id|serial21285_reg
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
l_string|&quot;ttyFB&quot;
comma
macro_line|#ifdef CONFIG_DEVFS_FS
dot
id|dev_name
op_assign
l_string|&quot;ttyFB%d&quot;
comma
macro_line|#else
dot
id|dev_name
op_assign
l_string|&quot;ttyFB&quot;
comma
macro_line|#endif
dot
id|major
op_assign
id|SERIAL_21285_MAJOR
comma
dot
id|minor
op_assign
id|SERIAL_21285_MINOR
comma
dot
id|nr
op_assign
l_int|1
comma
dot
id|cons
op_assign
id|SERIAL_21285_CONSOLE
comma
)brace
suffix:semicolon
DECL|function|serial21285_init
r_static
r_int
id|__init
id|serial21285_init
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
l_string|&quot;Serial: 21285 driver $Revision: 1.34 $&bslash;n&quot;
)paren
suffix:semicolon
id|serial21285_setup_ports
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|uart_register_driver
c_func
(paren
op_amp
id|serial21285_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|uart_add_one_port
c_func
(paren
op_amp
id|serial21285_reg
comma
op_amp
id|serial21285_port
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|serial21285_exit
r_static
r_void
id|__exit
id|serial21285_exit
c_func
(paren
r_void
)paren
(brace
id|uart_remove_one_port
c_func
(paren
op_amp
id|serial21285_reg
comma
op_amp
id|serial21285_port
)paren
suffix:semicolon
id|uart_unregister_driver
c_func
(paren
op_amp
id|serial21285_reg
)paren
suffix:semicolon
)brace
DECL|variable|serial21285_init
id|module_init
c_func
(paren
id|serial21285_init
)paren
suffix:semicolon
DECL|variable|serial21285_exit
id|module_exit
c_func
(paren
id|serial21285_exit
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Intel Footbridge (21285) serial driver $Revision: 1.34 $&quot;
)paren
suffix:semicolon
eof
