multiline_comment|/*&n; * drivers/serial/nb85e_uart.c -- Serial I/O using V850E/NB85E on-chip UART&n; *&n; *  Copyright (C) 2001,02,03  NEC Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/nb85e_uart.h&gt;
macro_line|#include &lt;asm/nb85e_utils.h&gt;
multiline_comment|/* Initial UART state.  This may be overridden by machine-dependent headers. */
macro_line|#ifndef NB85E_UART_INIT_BAUD
DECL|macro|NB85E_UART_INIT_BAUD
mdefine_line|#define NB85E_UART_INIT_BAUD&t;115200
macro_line|#endif
macro_line|#ifndef NB85E_UART_INIT_CFLAGS
DECL|macro|NB85E_UART_INIT_CFLAGS
mdefine_line|#define NB85E_UART_INIT_CFLAGS&t;(B115200 | CS8 | CREAD)
macro_line|#endif
multiline_comment|/* XXX This should be in a header file.  */
DECL|macro|NB85E_UART_BRGC_MIN
mdefine_line|#define NB85E_UART_BRGC_MIN&t;8
multiline_comment|/* A string used for prefixing printed descriptions; since the same UART&n;   macro is actually used on other chips than the V850E/NB85E.  This must&n;   be a constant string.  */
macro_line|#ifndef NB85E_UART_CHIP_NAME
DECL|macro|NB85E_UART_CHIP_NAME
mdefine_line|#define NB85E_UART_CHIP_NAME &quot;V850E/NB85E&quot;
macro_line|#endif
"&f;"
multiline_comment|/* Helper functions for doing baud-rate/frequency calculations.  */
multiline_comment|/* Calculate the minimum value for CKSR on this processor.  */
DECL|function|cksr_min
r_static
r_inline
r_int
id|cksr_min
(paren
r_void
)paren
(brace
r_int
id|min
op_assign
l_int|0
suffix:semicolon
r_int
id|freq
op_assign
id|NB85E_UART_BASE_FREQ
suffix:semicolon
r_while
c_loop
(paren
id|freq
OG
id|NB85E_UART_CKSR_MAX_FREQ
)paren
(brace
id|freq
op_rshift_assign
l_int|1
suffix:semicolon
id|min
op_increment
suffix:semicolon
)brace
r_return
id|min
suffix:semicolon
)brace
multiline_comment|/* Minimum baud rate possible.  */
DECL|macro|min_baud
mdefine_line|#define min_baud() &bslash;&n;   ((NB85E_UART_BASE_FREQ &gt;&gt; NB85E_UART_CKSR_MAX) / (2 * 255) + 1)
multiline_comment|/* Maximum baud rate possible.  The error is quite high at max, though.  */
DECL|macro|max_baud
mdefine_line|#define max_baud() &bslash;&n;   ((NB85E_UART_BASE_FREQ &gt;&gt; cksr_min()) / (2 * NB85E_UART_BRGC_MIN))
"&f;"
multiline_comment|/* Low-level UART functions.  */
multiline_comment|/* These masks define which control bits affect TX/RX modes, respectively.  */
DECL|macro|RX_BITS
mdefine_line|#define RX_BITS &bslash;&n;  (NB85E_UART_ASIM_PS_MASK | NB85E_UART_ASIM_CL_8 | NB85E_UART_ASIM_ISRM)
DECL|macro|TX_BITS
mdefine_line|#define TX_BITS &bslash;&n;  (NB85E_UART_ASIM_PS_MASK | NB85E_UART_ASIM_CL_8 | NB85E_UART_ASIM_SL_2)
multiline_comment|/* The UART require various delays after writing control registers.  */
DECL|function|nb85e_uart_delay
r_static
r_inline
r_void
id|nb85e_uart_delay
(paren
r_int
id|cycles
)paren
(brace
multiline_comment|/* The loop takes 2 insns, so loop CYCLES / 2 times.  */
r_register
r_int
id|count
op_assign
id|cycles
op_rshift
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|count
op_ne
l_int|0
)paren
multiline_comment|/* nothing */
suffix:semicolon
)brace
multiline_comment|/* Configure and turn on uart channel CHAN, using the termios `control&n;   modes&squot; bits in CFLAGS, and a baud-rate of BAUD.  */
DECL|function|nb85e_uart_configure
r_void
id|nb85e_uart_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
id|new_config
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* What we&squot;ll write to the control reg. */
r_int
id|new_clk_divlog2
suffix:semicolon
multiline_comment|/* New baud-rate generate clock divider. */
r_int
id|new_brgen_count
suffix:semicolon
multiline_comment|/* New counter max for baud-rate generator.*/
multiline_comment|/* These are the current values corresponding to the above.  */
r_int
id|old_config
comma
id|old_clk_divlog2
comma
id|old_brgen_count
suffix:semicolon
multiline_comment|/* Calculate new baud-rate generator config values.  */
multiline_comment|/* Calculate the log2 clock divider and baud-rate counter values&n;&t;   (note that the UART divides the resulting clock by 2, so&n;&t;   multiply BAUD by 2 here to compensate).  */
id|calc_counter_params
(paren
id|NB85E_UART_BASE_FREQ
comma
id|baud
op_star
l_int|2
comma
id|cksr_min
c_func
(paren
)paren
comma
id|NB85E_UART_CKSR_MAX
comma
l_int|8
multiline_comment|/*bits*/
comma
op_amp
id|new_clk_divlog2
comma
op_amp
id|new_brgen_count
)paren
suffix:semicolon
multiline_comment|/* Figure out new configuration of control register.  */
r_if
c_cond
(paren
id|cflags
op_amp
id|CSTOPB
)paren
multiline_comment|/* Number of stop bits, 1 or 2.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_SL_2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cflags
op_amp
id|CSIZE
)paren
op_eq
id|CS8
)paren
multiline_comment|/* Number of data bits, 7 or 8.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_CL_8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cflags
op_amp
id|PARENB
)paren
)paren
multiline_comment|/* No parity check/generation.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_PS_NONE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cflags
op_amp
id|PARODD
)paren
multiline_comment|/* Odd parity check/generation.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_PS_ODD
suffix:semicolon
r_else
multiline_comment|/* Even parity check/generation.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_PS_EVEN
suffix:semicolon
r_if
c_cond
(paren
id|cflags
op_amp
id|CREAD
)paren
multiline_comment|/* Reading enabled.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_RXE
suffix:semicolon
id|new_config
op_or_assign
id|NB85E_UART_ASIM_TXE
suffix:semicolon
multiline_comment|/* Writing is always enabled.  */
id|new_config
op_or_assign
id|NB85E_UART_ASIM_CAE
suffix:semicolon
id|new_config
op_or_assign
id|NB85E_UART_ASIM_ISRM
suffix:semicolon
multiline_comment|/* Errors generate a read-irq.  */
multiline_comment|/* Disable interrupts while we&squot;re twiddling the hardware.  */
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
macro_line|#ifdef NB85E_UART_PRE_CONFIGURE
id|NB85E_UART_PRE_CONFIGURE
(paren
id|chan
comma
id|cflags
comma
id|baud
)paren
suffix:semicolon
macro_line|#endif
id|old_config
op_assign
id|NB85E_UART_ASIM
(paren
id|chan
)paren
suffix:semicolon
id|old_clk_divlog2
op_assign
id|NB85E_UART_CKSR
(paren
id|chan
)paren
suffix:semicolon
id|old_brgen_count
op_assign
id|NB85E_UART_BRGC
(paren
id|chan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_clk_divlog2
op_ne
id|old_clk_divlog2
op_logical_or
id|new_brgen_count
op_ne
id|old_brgen_count
)paren
(brace
multiline_comment|/* The baud rate has changed.  First, disable the UART.  */
id|NB85E_UART_ASIM
(paren
id|chan
)paren
op_assign
l_int|0
suffix:semicolon
id|old_config
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Reprogram the baud-rate generator.  */
id|NB85E_UART_CKSR
(paren
id|chan
)paren
op_assign
id|new_clk_divlog2
suffix:semicolon
id|NB85E_UART_BRGC
(paren
id|chan
)paren
op_assign
id|new_brgen_count
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|old_config
op_amp
id|NB85E_UART_ASIM_CAE
)paren
)paren
(brace
multiline_comment|/* If we are enabling the uart for the first time, start&n;&t;&t;   by turning on the enable bit, which must be done&n;&t;&t;   before turning on any other bits.  */
id|NB85E_UART_ASIM
(paren
id|chan
)paren
op_assign
id|NB85E_UART_ASIM_CAE
suffix:semicolon
multiline_comment|/* Enabling the uart also resets it.  */
id|old_config
op_assign
id|NB85E_UART_ASIM_CAE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_config
op_ne
id|old_config
)paren
(brace
multiline_comment|/* Which of the TXE/RXE bits we&squot;ll temporarily turn off&n;&t;&t;   before changing other control bits.  */
r_int
id|temp_disable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Which of the TXE/RXE bits will be enabled.  */
r_int
id|enable
op_assign
l_int|0
suffix:semicolon
r_int
id|changed_bits
op_assign
id|new_config
op_xor
id|old_config
suffix:semicolon
multiline_comment|/* Which of RX/TX will be enabled in the new configuration.  */
r_if
c_cond
(paren
id|new_config
op_amp
id|RX_BITS
)paren
id|enable
op_or_assign
(paren
id|new_config
op_amp
id|NB85E_UART_ASIM_RXE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_config
op_amp
id|TX_BITS
)paren
id|enable
op_or_assign
(paren
id|new_config
op_amp
id|NB85E_UART_ASIM_TXE
)paren
suffix:semicolon
multiline_comment|/* Figure out which of RX/TX needs to be disabled; note&n;&t;&t;   that this will only happen if they&squot;re not already&n;&t;&t;   disabled.  */
r_if
c_cond
(paren
id|changed_bits
op_amp
id|RX_BITS
)paren
id|temp_disable
op_or_assign
(paren
id|old_config
op_amp
id|NB85E_UART_ASIM_RXE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|changed_bits
op_amp
id|TX_BITS
)paren
id|temp_disable
op_or_assign
(paren
id|old_config
op_amp
id|NB85E_UART_ASIM_TXE
)paren
suffix:semicolon
multiline_comment|/* We have to turn off RX and/or TX mode before changing&n;&t;&t;   any associated control bits.  */
r_if
c_cond
(paren
id|temp_disable
)paren
id|NB85E_UART_ASIM
(paren
id|chan
)paren
op_assign
id|old_config
op_amp
op_complement
id|temp_disable
suffix:semicolon
multiline_comment|/* Write the new control bits, while RX/TX are disabled. */
r_if
c_cond
(paren
id|changed_bits
op_amp
op_complement
id|enable
)paren
id|NB85E_UART_ASIM
(paren
id|chan
)paren
op_assign
id|new_config
op_amp
op_complement
id|enable
suffix:semicolon
multiline_comment|/* The UART may not be reset properly unless we&n;&t;&t;   wait at least 2 `basic-clocks&squot; until turning&n;&t;&t;   on the TXE/RXE bits again.  A `basic clock&squot;&n;&t;&t;   is the clock used by the baud-rate generator, i.e.,&n;&t;&t;   the cpu clock divided by the 2^new_clk_divlog2.  */
id|nb85e_uart_delay
(paren
l_int|1
op_lshift
(paren
id|new_clk_divlog2
op_plus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Write the final version, with enable bits turned on.  */
id|NB85E_UART_ASIM
(paren
id|chan
)paren
op_assign
id|new_config
suffix:semicolon
)brace
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/*  Low-level console. */
macro_line|#ifdef CONFIG_V850E_NB85E_UART_CONSOLE
DECL|function|nb85e_uart_cons_write
r_static
r_void
id|nb85e_uart_cons_write
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
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
id|chan
op_assign
id|co-&gt;index
suffix:semicolon
r_int
id|irq
op_assign
id|IRQ_INTST
(paren
id|chan
)paren
suffix:semicolon
r_int
id|irq_was_enabled
comma
id|irq_was_pending
comma
id|flags
suffix:semicolon
multiline_comment|/* We don&squot;t want to get `transmission completed&squot; (INTST)&n;&t;&t;   interrupts, since we&squot;re busy-waiting, so we disable&n;&t;&t;   them while sending (we don&squot;t disable interrupts&n;&t;&t;   entirely because sending over a serial line is really&n;&t;&t;   slow).  We save the status of INTST and restore it&n;&t;&t;   when we&squot;re done so that using printk doesn&squot;t&n;&t;&t;   interfere with normal serial transmission (other than&n;&t;&t;   interleaving the output, of course!).  This should&n;&t;&t;   work correctly even if this function is interrupted&n;&t;&t;   and the interrupt printks something.  */
multiline_comment|/* Disable interrupts while fiddling with INTST.  */
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Get current INTST status.  */
id|irq_was_enabled
op_assign
id|nb85e_intc_irq_enabled
(paren
id|irq
)paren
suffix:semicolon
id|irq_was_pending
op_assign
id|nb85e_intc_irq_pending
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* Disable INTST if necessary.  */
r_if
c_cond
(paren
id|irq_was_enabled
)paren
id|nb85e_intc_disable_irq
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* Turn interrupts back on.  */
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Send characters.  */
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
id|ch
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* We don&squot;t have the benefit of a tty&n;&t;&t;&t;&t;   driver, so translate NL into CR LF.  */
id|nb85e_uart_wait_for_xmit_ok
(paren
id|chan
)paren
suffix:semicolon
id|nb85e_uart_putc
(paren
id|chan
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
id|nb85e_uart_wait_for_xmit_ok
(paren
id|chan
)paren
suffix:semicolon
id|nb85e_uart_putc
(paren
id|chan
comma
id|ch
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Restore saved INTST status.  */
r_if
c_cond
(paren
id|irq_was_enabled
)paren
(brace
multiline_comment|/* Wait for the last character we sent to be&n;&t;&t;&t;   completely transmitted (as we&squot;ll get an INTST&n;&t;&t;&t;   interrupt at that point).  */
id|nb85e_uart_wait_for_xmit_done
(paren
id|chan
)paren
suffix:semicolon
multiline_comment|/* Clear pending interrupts received due&n;&t;&t;&t;   to our transmission, unless there was already&n;&t;&t;&t;   one pending, in which case we want the&n;&t;&t;&t;   handler to be called.  */
r_if
c_cond
(paren
op_logical_neg
id|irq_was_pending
)paren
id|nb85e_intc_clear_pending_irq
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* ... and then turn back on handling.  */
id|nb85e_intc_enable_irq
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|nb85e_uart_cons_device
r_static
id|kdev_t
id|nb85e_uart_cons_device
(paren
r_struct
id|console
op_star
id|c
)paren
(brace
r_return
id|mk_kdev
(paren
id|TTY_MAJOR
comma
id|NB85E_UART_MINOR_BASE
op_plus
id|c-&gt;index
)paren
suffix:semicolon
)brace
DECL|variable|nb85e_uart_cons
r_static
r_struct
id|console
id|nb85e_uart_cons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyS&quot;
comma
dot
id|write
op_assign
id|nb85e_uart_cons_write
comma
dot
id|device
op_assign
id|nb85e_uart_cons_device
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|cflag
op_assign
id|NB85E_UART_INIT_CFLAGS
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|nb85e_uart_cons_init
r_void
id|nb85e_uart_cons_init
(paren
r_int
id|chan
)paren
(brace
id|nb85e_uart_configure
(paren
id|chan
comma
id|NB85E_UART_INIT_CFLAGS
comma
id|NB85E_UART_INIT_BAUD
)paren
suffix:semicolon
id|nb85e_uart_cons.index
op_assign
id|chan
suffix:semicolon
id|register_console
(paren
op_amp
id|nb85e_uart_cons
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Console: %s on-chip UART channel %d&bslash;n&quot;
comma
id|NB85E_UART_CHIP_NAME
comma
id|chan
)paren
suffix:semicolon
)brace
DECL|macro|NB85E_UART_CONSOLE
mdefine_line|#define NB85E_UART_CONSOLE &amp;nb85e_uart_cons
macro_line|#else /* !CONFIG_V850E_NB85E_UART_CONSOLE */
DECL|macro|NB85E_UART_CONSOLE
mdefine_line|#define NB85E_UART_CONSOLE 0
macro_line|#endif /* CONFIG_V850E_NB85E_UART_CONSOLE */
"&f;"
multiline_comment|/* TX/RX interrupt handlers.  */
r_static
r_void
id|nb85e_uart_stop_tx
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|tty_stop
)paren
suffix:semicolon
DECL|function|nb85e_uart_tx
r_void
id|nb85e_uart_tx
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
id|stopped
op_assign
id|uart_tx_stopped
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nb85e_uart_xmit_ok
(paren
id|port-&gt;line
)paren
)paren
(brace
r_int
id|tx_ch
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;x_char
)paren
(brace
id|tx_ch
op_assign
id|port-&gt;x_char
suffix:semicolon
id|port-&gt;x_char
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|uart_circ_empty
(paren
id|xmit
)paren
op_logical_and
op_logical_neg
id|stopped
)paren
(brace
id|tx_ch
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
)brace
r_else
r_goto
id|no_xmit
suffix:semicolon
id|nb85e_uart_putc
(paren
id|port-&gt;line
comma
id|tx_ch
)paren
suffix:semicolon
id|port-&gt;icount.tx
op_increment
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
)brace
id|no_xmit
suffix:colon
r_if
c_cond
(paren
id|uart_circ_empty
(paren
id|xmit
)paren
op_logical_or
id|stopped
)paren
id|nb85e_uart_stop_tx
(paren
id|port
comma
id|stopped
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_tx_irq
r_static
r_void
id|nb85e_uart_tx_irq
(paren
r_int
id|irq
comma
r_void
op_star
id|data
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
id|data
suffix:semicolon
id|nb85e_uart_tx
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_rx_irq
r_static
r_void
id|nb85e_uart_rx_irq
(paren
r_int
id|irq
comma
r_void
op_star
id|data
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
id|data
suffix:semicolon
r_int
id|ch_stat
op_assign
id|TTY_NORMAL
suffix:semicolon
r_int
id|ch
op_assign
id|NB85E_UART_RXB
(paren
id|port-&gt;line
)paren
suffix:semicolon
r_int
id|err
op_assign
id|NB85E_UART_ASIS
(paren
id|port-&gt;line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_if
c_cond
(paren
id|err
op_amp
id|NB85E_UART_ASIS_OVE
)paren
(brace
id|ch_stat
op_assign
id|TTY_OVERRUN
suffix:semicolon
id|port-&gt;icount.overrun
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|err
op_amp
id|NB85E_UART_ASIS_FE
)paren
(brace
id|ch_stat
op_assign
id|TTY_FRAME
suffix:semicolon
id|port-&gt;icount.frame
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|err
op_amp
id|NB85E_UART_ASIS_PE
)paren
(brace
id|ch_stat
op_assign
id|TTY_PARITY
suffix:semicolon
id|port-&gt;icount.parity
op_increment
suffix:semicolon
)brace
)brace
id|port-&gt;icount.rx
op_increment
suffix:semicolon
id|tty_insert_flip_char
(paren
id|port-&gt;info-&gt;tty
comma
id|ch
comma
id|ch_stat
)paren
suffix:semicolon
id|tty_schedule_flip
(paren
id|port-&gt;info-&gt;tty
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Control functions for the serial framework.  */
DECL|function|nb85e_uart_nop
r_static
r_void
id|nb85e_uart_nop
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
)brace
DECL|function|nb85e_uart_success
r_static
r_int
id|nb85e_uart_success
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
DECL|function|nb85e_uart_tx_empty
r_static
r_int
id|nb85e_uart_tx_empty
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_return
id|TIOCSER_TEMT
suffix:semicolon
multiline_comment|/* Can&squot;t detect.  */
)brace
DECL|function|nb85e_uart_set_mctrl
r_static
r_void
id|nb85e_uart_set_mctrl
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|mctrl
)paren
(brace
macro_line|#ifdef NB85E_UART_SET_RTS
id|NB85E_UART_SET_RTS
(paren
id|port-&gt;line
comma
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|nb85e_uart_get_mctrl
r_static
r_int
id|nb85e_uart_get_mctrl
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
multiline_comment|/* We don&squot;t support DCD or DSR, so consider them permanently active. */
r_int
id|mctrl
op_assign
id|TIOCM_CAR
op_or
id|TIOCM_DSR
suffix:semicolon
multiline_comment|/* We may support CTS.  */
macro_line|#ifdef NB85E_UART_CTS
id|mctrl
op_or_assign
id|NB85E_UART_CTS
c_func
(paren
id|port-&gt;line
)paren
ques
c_cond
id|TIOCM_CTS
suffix:colon
l_int|0
suffix:semicolon
macro_line|#else
id|mctrl
op_or_assign
id|TIOCM_CTS
suffix:semicolon
macro_line|#endif
r_return
id|mctrl
suffix:semicolon
)brace
DECL|function|nb85e_uart_start_tx
r_static
r_void
id|nb85e_uart_start_tx
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|tty_start
)paren
(brace
id|nb85e_intc_disable_irq
(paren
id|IRQ_INTST
(paren
id|port-&gt;line
)paren
)paren
suffix:semicolon
id|nb85e_uart_tx
(paren
id|port
)paren
suffix:semicolon
id|nb85e_intc_enable_irq
(paren
id|IRQ_INTST
(paren
id|port-&gt;line
)paren
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_stop_tx
r_static
r_void
id|nb85e_uart_stop_tx
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|tty_stop
)paren
(brace
id|nb85e_intc_disable_irq
(paren
id|IRQ_INTST
(paren
id|port-&gt;line
)paren
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_start_rx
r_static
r_void
id|nb85e_uart_start_rx
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|nb85e_intc_enable_irq
(paren
id|IRQ_INTSR
(paren
id|port-&gt;line
)paren
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_stop_rx
r_static
r_void
id|nb85e_uart_stop_rx
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|nb85e_intc_disable_irq
(paren
id|IRQ_INTSR
(paren
id|port-&gt;line
)paren
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_break_ctl
r_static
r_void
id|nb85e_uart_break_ctl
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
id|break_ctl
)paren
(brace
multiline_comment|/* Umm, do this later.  */
)brace
DECL|function|nb85e_uart_startup
r_static
r_int
id|nb85e_uart_startup
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* Alloc RX irq.  */
id|err
op_assign
id|request_irq
(paren
id|IRQ_INTSR
(paren
id|port-&gt;line
)paren
comma
id|nb85e_uart_rx_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;nb85e_uart&quot;
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* Alloc TX irq.  */
id|err
op_assign
id|request_irq
(paren
id|IRQ_INTST
(paren
id|port-&gt;line
)paren
comma
id|nb85e_uart_tx_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;nb85e_uart&quot;
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|free_irq
(paren
id|IRQ_INTSR
(paren
id|port-&gt;line
)paren
comma
id|port
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|nb85e_uart_start_rx
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nb85e_uart_shutdown
r_static
r_void
id|nb85e_uart_shutdown
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
multiline_comment|/* Disable port interrupts.  */
id|free_irq
(paren
id|IRQ_INTST
(paren
id|port-&gt;line
)paren
comma
id|port
)paren
suffix:semicolon
id|free_irq
(paren
id|IRQ_INTSR
(paren
id|port-&gt;line
)paren
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* Turn off xmit/recv enable bits.  */
id|NB85E_UART_ASIM
(paren
id|port-&gt;line
)paren
op_and_assign
op_complement
(paren
id|NB85E_UART_ASIM_TXE
op_or
id|NB85E_UART_ASIM_RXE
)paren
suffix:semicolon
multiline_comment|/* Then reset the channel.  */
id|NB85E_UART_ASIM
(paren
id|port-&gt;line
)paren
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|nb85e_uart_set_termios
id|nb85e_uart_set_termios
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
id|cflags
op_assign
id|termios-&gt;c_cflag
suffix:semicolon
multiline_comment|/* Restrict flags to legal values.  */
r_if
c_cond
(paren
(paren
id|cflags
op_amp
id|CSIZE
)paren
op_ne
id|CS7
op_logical_and
(paren
id|cflags
op_amp
id|CSIZE
)paren
op_ne
id|CS8
)paren
multiline_comment|/* The new value of CSIZE is invalid, use the old value.  */
id|cflags
op_assign
(paren
id|cflags
op_amp
op_complement
id|CSIZE
)paren
op_or
(paren
id|old
ques
c_cond
(paren
id|old-&gt;c_cflag
op_amp
id|CSIZE
)paren
suffix:colon
id|CS8
)paren
suffix:semicolon
id|termios-&gt;c_cflag
op_assign
id|cflags
suffix:semicolon
id|nb85e_uart_configure
(paren
id|port-&gt;line
comma
id|cflags
comma
id|uart_get_baud_rate
(paren
id|port
comma
id|termios
comma
id|old
comma
id|min_baud
c_func
(paren
)paren
comma
id|max_baud
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|nb85e_uart_type
r_static
r_const
r_char
op_star
id|nb85e_uart_type
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
id|PORT_NB85E_UART
ques
c_cond
l_string|&quot;nb85e_uart&quot;
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|nb85e_uart_config_port
r_static
r_void
id|nb85e_uart_config_port
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
id|PORT_NB85E_UART
suffix:semicolon
)brace
r_static
r_int
DECL|function|nb85e_uart_verify_port
id|nb85e_uart_verify_port
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
r_if
c_cond
(paren
id|ser-&gt;type
op_ne
id|PORT_UNKNOWN
op_logical_and
id|ser-&gt;type
op_ne
id|PORT_NB85E_UART
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ser-&gt;irq
op_ne
id|IRQ_INTST
(paren
id|port-&gt;line
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nb85e_uart_ops
r_static
r_struct
id|uart_ops
id|nb85e_uart_ops
op_assign
(brace
dot
id|tx_empty
op_assign
id|nb85e_uart_tx_empty
comma
dot
id|get_mctrl
op_assign
id|nb85e_uart_get_mctrl
comma
dot
id|set_mctrl
op_assign
id|nb85e_uart_set_mctrl
comma
dot
id|start_tx
op_assign
id|nb85e_uart_start_tx
comma
dot
id|stop_tx
op_assign
id|nb85e_uart_stop_tx
comma
dot
id|stop_rx
op_assign
id|nb85e_uart_stop_rx
comma
dot
id|enable_ms
op_assign
id|nb85e_uart_nop
comma
dot
id|break_ctl
op_assign
id|nb85e_uart_break_ctl
comma
dot
id|startup
op_assign
id|nb85e_uart_startup
comma
dot
id|shutdown
op_assign
id|nb85e_uart_shutdown
comma
dot
id|set_termios
op_assign
id|nb85e_uart_set_termios
comma
dot
id|type
op_assign
id|nb85e_uart_type
comma
dot
id|release_port
op_assign
id|nb85e_uart_nop
comma
dot
id|request_port
op_assign
id|nb85e_uart_success
comma
dot
id|config_port
op_assign
id|nb85e_uart_config_port
comma
dot
id|verify_port
op_assign
id|nb85e_uart_verify_port
comma
)brace
suffix:semicolon
"&f;"
multiline_comment|/* Initialization and cleanup.  */
DECL|variable|nb85e_uart_driver
r_static
r_struct
id|uart_driver
id|nb85e_uart_driver
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
l_string|&quot;nb85e_uart&quot;
comma
macro_line|#ifdef CONFIG_DEVFS_FS
dot
id|dev_name
op_assign
l_string|&quot;tts/&quot;
comma
macro_line|#else
dot
id|dev_name
op_assign
l_string|&quot;ttyS&quot;
comma
macro_line|#endif
dot
id|major
op_assign
id|TTY_MAJOR
comma
dot
id|minor
op_assign
id|NB85E_UART_MINOR_BASE
comma
dot
id|nr
op_assign
id|NB85E_UART_NUM_CHANNELS
comma
dot
id|cons
op_assign
id|NB85E_UART_CONSOLE
comma
)brace
suffix:semicolon
DECL|variable|nb85e_uart_ports
r_static
r_struct
id|uart_port
id|nb85e_uart_ports
(braket
id|NB85E_UART_NUM_CHANNELS
)braket
suffix:semicolon
DECL|function|nb85e_uart_init
r_static
r_int
id|__init
id|nb85e_uart_init
(paren
r_void
)paren
(brace
r_int
id|rval
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s on-chip UART&bslash;n&quot;
comma
id|NB85E_UART_CHIP_NAME
)paren
suffix:semicolon
id|rval
op_assign
id|uart_register_driver
(paren
op_amp
id|nb85e_uart_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rval
op_eq
l_int|0
)paren
(brace
r_int
id|chan
suffix:semicolon
r_for
c_loop
(paren
id|chan
op_assign
l_int|0
suffix:semicolon
id|chan
OL
id|NB85E_UART_NUM_CHANNELS
suffix:semicolon
id|chan
op_increment
)paren
(brace
r_struct
id|uart_port
op_star
id|port
op_assign
op_amp
id|nb85e_uart_ports
(braket
id|chan
)braket
suffix:semicolon
id|memset
(paren
id|port
comma
l_int|0
comma
r_sizeof
op_star
id|port
)paren
suffix:semicolon
id|port-&gt;ops
op_assign
op_amp
id|nb85e_uart_ops
suffix:semicolon
id|port-&gt;line
op_assign
id|chan
suffix:semicolon
id|port-&gt;iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|port-&gt;flags
op_assign
id|UPF_BOOT_AUTOCONF
suffix:semicolon
multiline_comment|/* We actually use multiple IRQs, but the serial&n;&t;&t;&t;   framework seems to mainly use this for&n;&t;&t;&t;   informational purposes anyway.  Here we use the TX&n;&t;&t;&t;   irq.  */
id|port-&gt;irq
op_assign
id|IRQ_INTST
(paren
id|chan
)paren
suffix:semicolon
multiline_comment|/* The serial framework doesn&squot;t really use these&n;&t;&t;&t;   membase/mapbase fields for anything useful, but&n;&t;&t;&t;   it requires that they be something non-zero to&n;&t;&t;&t;   consider the port `valid&squot;, and also uses them&n;&t;&t;&t;   for informational purposes.  */
id|port-&gt;membase
op_assign
(paren
r_void
op_star
)paren
id|NB85E_UART_BASE_ADDR
(paren
id|chan
)paren
suffix:semicolon
id|port-&gt;mapbase
op_assign
id|NB85E_UART_BASE_ADDR
(paren
id|chan
)paren
suffix:semicolon
multiline_comment|/* The framework insists on knowing the uart&squot;s master&n;&t;&t;&t;   clock freq, though it doesn&squot;t seem to do anything&n;&t;&t;&t;   useful for us with it.  We must make it at least&n;&t;&t;&t;   higher than (the maximum baud rate * 16), otherwise&n;&t;&t;&t;   the framework will puke during its internal&n;&t;&t;&t;   calculations, and force the baud rate to be 9600.&n;&t;&t;&t;   To be accurate though, just repeat the calculation&n;&t;&t;&t;   we use when actually setting the speed.&n;&n;&t;&t;&t;   The `* 8&squot; means `* 16 / 2&squot;:  16 to account for for&n;&t;&t;&t;   the serial framework&squot;s built-in bias, and 2 because&n;&t;&t;&t;   there&squot;s an additional / 2 in the hardware.  */
id|port-&gt;uartclk
op_assign
(paren
id|NB85E_UART_BASE_FREQ
op_rshift
id|cksr_min
c_func
(paren
)paren
)paren
op_star
l_int|8
suffix:semicolon
id|uart_add_one_port
(paren
op_amp
id|nb85e_uart_driver
comma
id|port
)paren
suffix:semicolon
)brace
)brace
r_return
id|rval
suffix:semicolon
)brace
DECL|function|nb85e_uart_exit
r_static
r_void
id|__exit
id|nb85e_uart_exit
(paren
r_void
)paren
(brace
r_int
id|chan
suffix:semicolon
r_for
c_loop
(paren
id|chan
op_assign
l_int|0
suffix:semicolon
id|chan
OL
id|NB85E_UART_NUM_CHANNELS
suffix:semicolon
id|chan
op_increment
)paren
id|uart_remove_one_port
(paren
op_amp
id|nb85e_uart_driver
comma
op_amp
id|nb85e_uart_ports
(braket
id|chan
)braket
)paren
suffix:semicolon
id|uart_unregister_driver
(paren
op_amp
id|nb85e_uart_driver
)paren
suffix:semicolon
)brace
DECL|variable|nb85e_uart_init
id|module_init
(paren
id|nb85e_uart_init
)paren
suffix:semicolon
DECL|variable|nb85e_uart_exit
id|module_exit
(paren
id|nb85e_uart_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Miles Bader&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;NEC &quot;
id|NB85E_UART_CHIP_NAME
l_string|&quot; on-chip UART&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
