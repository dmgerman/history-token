multiline_comment|/*&n; * include/asm-v850/v850e_uartb.h -- V850E on-chip `UARTB&squot; UART&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* The V850E UARTB is basically a superset of the original V850E UART, but&n;   even where it&squot;s the same, the names and details have changed a bit.&n;   It&squot;s similar enough to use the same driver (v850e_uart.c), but the&n;   details have been abstracted slightly to do so.  */
macro_line|#ifndef __V850_V850E_UARTB_H__
DECL|macro|__V850_V850E_UARTB_H__
mdefine_line|#define __V850_V850E_UARTB_H__
"&f;"
multiline_comment|/* Raw hardware interface.  */
DECL|macro|V850E_UARTB_BASE_ADDR
mdefine_line|#define V850E_UARTB_BASE_ADDR(n)&t;(0xFFFFFA00 + 0x10 * (n))
multiline_comment|/* Addresses of specific UART control registers for channel N.  */
DECL|macro|V850E_UARTB_CTL0_ADDR
mdefine_line|#define V850E_UARTB_CTL0_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0x0)
DECL|macro|V850E_UARTB_CTL2_ADDR
mdefine_line|#define V850E_UARTB_CTL2_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0x2)
DECL|macro|V850E_UARTB_STR_ADDR
mdefine_line|#define V850E_UARTB_STR_ADDR(n)&t;&t;(V850E_UARTB_BASE_ADDR(n) + 0x4)
DECL|macro|V850E_UARTB_RX_ADDR
mdefine_line|#define V850E_UARTB_RX_ADDR(n)&t;&t;(V850E_UARTB_BASE_ADDR(n) + 0x6)
DECL|macro|V850E_UARTB_RXAP_ADDR
mdefine_line|#define V850E_UARTB_RXAP_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0x6)
DECL|macro|V850E_UARTB_TX_ADDR
mdefine_line|#define V850E_UARTB_TX_ADDR(n)&t;&t;(V850E_UARTB_BASE_ADDR(n) + 0x8)
DECL|macro|V850E_UARTB_FIC0_ADDR
mdefine_line|#define V850E_UARTB_FIC0_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0xA)
DECL|macro|V850E_UARTB_FIC1_ADDR
mdefine_line|#define V850E_UARTB_FIC1_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0xB)
DECL|macro|V850E_UARTB_FIC2_ADDR
mdefine_line|#define V850E_UARTB_FIC2_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0xC)
DECL|macro|V850E_UARTB_FIS0_ADDR
mdefine_line|#define V850E_UARTB_FIS0_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0xE)
DECL|macro|V850E_UARTB_FIS1_ADDR
mdefine_line|#define V850E_UARTB_FIS1_ADDR(n)&t;(V850E_UARTB_BASE_ADDR(n) + 0xF)
multiline_comment|/* UARTB control register 0 (general config).  */
DECL|macro|V850E_UARTB_CTL0
mdefine_line|#define V850E_UARTB_CTL0(n)&t;(*(volatile u8 *)V850E_UARTB_CTL0_ADDR(n))
multiline_comment|/* Control bits for config registers.  */
DECL|macro|V850E_UARTB_CTL0_PWR
mdefine_line|#define V850E_UARTB_CTL0_PWR&t;&t;0x80&t;/* clock enable */
DECL|macro|V850E_UARTB_CTL0_TXE
mdefine_line|#define V850E_UARTB_CTL0_TXE&t;&t;0x40&t;/* transmit enable */
DECL|macro|V850E_UARTB_CTL0_RXE
mdefine_line|#define V850E_UARTB_CTL0_RXE&t;&t;0x20&t;/* receive enable */
DECL|macro|V850E_UARTB_CTL0_DIR
mdefine_line|#define V850E_UARTB_CTL0_DIR&t;&t;0x10&t;/*  */
DECL|macro|V850E_UARTB_CTL0_PS1
mdefine_line|#define V850E_UARTB_CTL0_PS1&t;&t;0x08&t;/* parity */
DECL|macro|V850E_UARTB_CTL0_PS0
mdefine_line|#define V850E_UARTB_CTL0_PS0&t;&t;0x04&t;/* parity */
DECL|macro|V850E_UARTB_CTL0_CL
mdefine_line|#define V850E_UARTB_CTL0_CL&t;&t;0x02&t;/* char len 1:8bit, 0:7bit */
DECL|macro|V850E_UARTB_CTL0_SL
mdefine_line|#define V850E_UARTB_CTL0_SL&t;&t;0x01&t;/* stop bit 1:2bit, 0:1bit */
DECL|macro|V850E_UARTB_CTL0_PS_MASK
mdefine_line|#define V850E_UARTB_CTL0_PS_MASK&t;0x0C&t;/* mask covering parity bits */
DECL|macro|V850E_UARTB_CTL0_PS_NONE
mdefine_line|#define V850E_UARTB_CTL0_PS_NONE&t;0x00&t;/* no parity */
DECL|macro|V850E_UARTB_CTL0_PS_ZERO
mdefine_line|#define V850E_UARTB_CTL0_PS_ZERO&t;0x04&t;/* zero parity */
DECL|macro|V850E_UARTB_CTL0_PS_ODD
mdefine_line|#define V850E_UARTB_CTL0_PS_ODD&t;&t;0x08&t;/* odd parity */
DECL|macro|V850E_UARTB_CTL0_PS_EVEN
mdefine_line|#define V850E_UARTB_CTL0_PS_EVEN&t;0x0C&t;/* even parity */
DECL|macro|V850E_UARTB_CTL0_CL_8
mdefine_line|#define V850E_UARTB_CTL0_CL_8&t;&t;0x02&t;/* char len 1:8bit, 0:7bit */
DECL|macro|V850E_UARTB_CTL0_SL_2
mdefine_line|#define V850E_UARTB_CTL0_SL_2&t;&t;0x01&t;/* stop bit 1:2bit, 0:1bit */
multiline_comment|/* UARTB control register 2 (clock divider).  */
DECL|macro|V850E_UARTB_CTL2
mdefine_line|#define V850E_UARTB_CTL2(n)&t;(*(volatile u16 *)V850E_UARTB_CTL2_ADDR(n))
DECL|macro|V850E_UARTB_CTL2_MIN
mdefine_line|#define V850E_UARTB_CTL2_MIN&t;4
DECL|macro|V850E_UARTB_CTL2_MAX
mdefine_line|#define V850E_UARTB_CTL2_MAX&t;0xFFFF
multiline_comment|/* UARTB serial interface status register.  */
DECL|macro|V850E_UARTB_STR
mdefine_line|#define V850E_UARTB_STR(n)&t;(*(volatile u8 *)V850E_UARTB_STR_ADDR(n))
multiline_comment|/* Control bits for status registers.  */
DECL|macro|V850E_UARTB_STR_TSF
mdefine_line|#define V850E_UARTB_STR_TSF&t;0x80&t;/* UBTX or FIFO exist data  */
DECL|macro|V850E_UARTB_STR_OVF
mdefine_line|#define V850E_UARTB_STR_OVF&t;0x08&t;/* overflow error */
DECL|macro|V850E_UARTB_STR_PE
mdefine_line|#define V850E_UARTB_STR_PE&t;0x04&t;/* parity error */
DECL|macro|V850E_UARTB_STR_FE
mdefine_line|#define V850E_UARTB_STR_FE&t;0x02&t;/* framing error */
DECL|macro|V850E_UARTB_STR_OVE
mdefine_line|#define V850E_UARTB_STR_OVE&t;0x01&t;/* overrun error */
multiline_comment|/* UARTB receive data register.  */
DECL|macro|V850E_UARTB_RX
mdefine_line|#define V850E_UARTB_RX(n)&t;(*(volatile u8 *)V850E_UARTB_RX_ADDR(n))
DECL|macro|V850E_UARTB_RXAP
mdefine_line|#define V850E_UARTB_RXAP(n)&t;(*(volatile u16 *)V850E_UARTB_RXAP_ADDR(n))
multiline_comment|/* Control bits for status registers.  */
DECL|macro|V850E_UARTB_RXAP_PEF
mdefine_line|#define V850E_UARTB_RXAP_PEF&t;0x0200 /* parity error */
DECL|macro|V850E_UARTB_RXAP_FEF
mdefine_line|#define V850E_UARTB_RXAP_FEF&t;0x0100 /* framing error */
multiline_comment|/* UARTB transmit data register.  */
DECL|macro|V850E_UARTB_TX
mdefine_line|#define V850E_UARTB_TX(n)&t;(*(volatile u8 *)V850E_UARTB_TX_ADDR(n))
multiline_comment|/* UARTB FIFO control register 0.  */
DECL|macro|V850E_UARTB_FIC0
mdefine_line|#define V850E_UARTB_FIC0(n)&t;(*(volatile u8 *)V850E_UARTB_FIC0_ADDR(n))
multiline_comment|/* UARTB FIFO control register 1.  */
DECL|macro|V850E_UARTB_FIC1
mdefine_line|#define V850E_UARTB_FIC1(n)&t;(*(volatile u8 *)V850E_UARTB_FIC1_ADDR(n))
multiline_comment|/* UARTB FIFO control register 2.  */
DECL|macro|V850E_UARTB_FIC2
mdefine_line|#define V850E_UARTB_FIC2(n)&t;(*(volatile u16 *)V850E_UARTB_FIC2_ADDR(n))
multiline_comment|/* UARTB FIFO status register 0.  */
DECL|macro|V850E_UARTB_FIS0
mdefine_line|#define V850E_UARTB_FIS0(n)&t;(*(volatile u8 *)V850E_UARTB_FIS0_ADDR(n))
multiline_comment|/* UARTB FIFO status register 1.  */
DECL|macro|V850E_UARTB_FIS1
mdefine_line|#define V850E_UARTB_FIS1(n)&t;(*(volatile u8 *)V850E_UARTB_FIS1_ADDR(n))
"&f;"
multiline_comment|/* Slightly abstract interface used by driver.  */
multiline_comment|/* Interrupts used by the UART.  */
multiline_comment|/* Received when the most recently transmitted character has been sent.  */
DECL|macro|V850E_UART_TX_IRQ
mdefine_line|#define V850E_UART_TX_IRQ(chan)&t;&t;IRQ_INTUBTIT (chan)
multiline_comment|/* Received when a new character has been received.  */
DECL|macro|V850E_UART_RX_IRQ
mdefine_line|#define V850E_UART_RX_IRQ(chan)&t;&t;IRQ_INTUBTIR (chan)
multiline_comment|/* Use by serial driver for information purposes.  */
DECL|macro|V850E_UART_BASE_ADDR
mdefine_line|#define V850E_UART_BASE_ADDR(chan)&t;V850E_UARTB_BASE_ADDR(chan)
multiline_comment|/* UART clock generator interface.  */
multiline_comment|/* This type encapsulates a particular uart frequency.  */
DECL|typedef|v850e_uart_speed_t
r_typedef
id|u16
id|v850e_uart_speed_t
suffix:semicolon
multiline_comment|/* Calculate a uart speed from BAUD for this uart.  */
DECL|function|v850e_uart_calc_speed
r_static
r_inline
id|v850e_uart_speed_t
id|v850e_uart_calc_speed
(paren
r_int
id|baud
)paren
(brace
id|v850e_uart_speed_t
id|speed
suffix:semicolon
multiline_comment|/*&n;&t; * V850E/ME2 UARTB baud rate is determined by the value of UBCTL2&n;&t; * fx = V850E_UARTB_BASE_FREQ = CPU_CLOCK_FREQ/4&n;&t; * baud = fx / 2*speed   [ speed &gt;= 4 ]&n;&t; */
id|speed
op_assign
id|V850E_UARTB_CTL2_MIN
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|V850E_UARTB_BASE_FREQ
op_div
l_int|2
)paren
op_div
id|speed
)paren
OG
id|baud
)paren
id|speed
op_increment
suffix:semicolon
r_return
id|speed
suffix:semicolon
)brace
multiline_comment|/* Return the current speed of uart channel CHAN.  */
DECL|macro|v850e_uart_speed
mdefine_line|#define v850e_uart_speed(chan)&t;&t;    V850E_UARTB_CTL2 (chan)
multiline_comment|/* Set the current speed of uart channel CHAN.  */
DECL|macro|v850e_uart_set_speed
mdefine_line|#define v850e_uart_set_speed(chan, speed)   (V850E_UARTB_CTL2 (chan) = (speed))
multiline_comment|/* Return true if SPEED1 and SPEED2 are the same.  */
DECL|macro|v850e_uart_speed_eq
mdefine_line|#define v850e_uart_speed_eq(speed1, speed2) ((speed1) == (speed2))
multiline_comment|/* Minimum baud rate possible.  */
DECL|macro|v850e_uart_min_baud
mdefine_line|#define v850e_uart_min_baud() &bslash;&n;   ((V850E_UARTB_BASE_FREQ / 2) / V850E_UARTB_CTL2_MAX)
multiline_comment|/* Maximum baud rate possible.  The error is quite high at max, though.  */
DECL|macro|v850e_uart_max_baud
mdefine_line|#define v850e_uart_max_baud() &bslash;&n;   ((V850E_UARTB_BASE_FREQ / 2) / V850E_UARTB_CTL2_MIN)
multiline_comment|/* The `maximum&squot; clock rate the uart can used, which is wanted (though not&n;   really used in any useful way) by the serial framework.  */
DECL|macro|v850e_uart_max_clock
mdefine_line|#define v850e_uart_max_clock() &bslash;&n;   (V850E_UARTB_BASE_FREQ / 2)
multiline_comment|/* UART configuration interface.  */
multiline_comment|/* Type of the uart config register; must be a scalar.  */
DECL|typedef|v850e_uart_config_t
r_typedef
id|u16
id|v850e_uart_config_t
suffix:semicolon
multiline_comment|/* The uart hardware config register for channel CHAN.  */
DECL|macro|V850E_UART_CONFIG
mdefine_line|#define V850E_UART_CONFIG(chan)&t;&t;V850E_UARTB_CTL0 (chan)
multiline_comment|/* This config bit set if the uart is enabled.  */
DECL|macro|V850E_UART_CONFIG_ENABLED
mdefine_line|#define V850E_UART_CONFIG_ENABLED&t;V850E_UARTB_CTL0_PWR
multiline_comment|/* If the uart _isn&squot;t_ enabled, store this value to it to do so.  */
DECL|macro|V850E_UART_CONFIG_INIT
mdefine_line|#define V850E_UART_CONFIG_INIT&t;&t;V850E_UARTB_CTL0_PWR
multiline_comment|/* Store this config value to disable the uart channel completely.  */
DECL|macro|V850E_UART_CONFIG_FINI
mdefine_line|#define V850E_UART_CONFIG_FINI&t;&t;0
multiline_comment|/* Setting/clearing these bits enable/disable TX/RX, respectively (but&n;   otherwise generally leave things running).  */
DECL|macro|V850E_UART_CONFIG_RX_ENABLE
mdefine_line|#define V850E_UART_CONFIG_RX_ENABLE&t;V850E_UARTB_CTL0_RXE
DECL|macro|V850E_UART_CONFIG_TX_ENABLE
mdefine_line|#define V850E_UART_CONFIG_TX_ENABLE&t;V850E_UARTB_CTL0_TXE
multiline_comment|/* These masks define which config bits affect TX/RX modes, respectively.  */
DECL|macro|V850E_UART_CONFIG_RX_BITS
mdefine_line|#define V850E_UART_CONFIG_RX_BITS &bslash;&n;  (V850E_UARTB_CTL0_PS_MASK | V850E_UARTB_CTL0_CL_8)
DECL|macro|V850E_UART_CONFIG_TX_BITS
mdefine_line|#define V850E_UART_CONFIG_TX_BITS &bslash;&n;  (V850E_UARTB_CTL0_PS_MASK | V850E_UARTB_CTL0_CL_8 | V850E_UARTB_CTL0_SL_2)
DECL|function|v850e_uart_calc_config
r_static
r_inline
id|v850e_uart_config_t
id|v850e_uart_calc_config
(paren
r_int
id|cflags
)paren
(brace
id|v850e_uart_config_t
id|config
op_assign
l_int|0
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
id|config
op_or_assign
id|V850E_UARTB_CTL0_SL_2
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
id|config
op_or_assign
id|V850E_UARTB_CTL0_CL_8
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
id|config
op_or_assign
id|V850E_UARTB_CTL0_PS_NONE
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
id|config
op_or_assign
id|V850E_UARTB_CTL0_PS_ODD
suffix:semicolon
r_else
multiline_comment|/* Even parity check/generation.  */
id|config
op_or_assign
id|V850E_UARTB_CTL0_PS_EVEN
suffix:semicolon
r_if
c_cond
(paren
id|cflags
op_amp
id|CREAD
)paren
multiline_comment|/* Reading enabled.  */
id|config
op_or_assign
id|V850E_UARTB_CTL0_RXE
suffix:semicolon
id|config
op_or_assign
id|V850E_UARTB_CTL0_PWR
suffix:semicolon
id|config
op_or_assign
id|V850E_UARTB_CTL0_TXE
suffix:semicolon
multiline_comment|/* Writing is always enabled.  */
id|config
op_or_assign
id|V850E_UARTB_CTL0_DIR
suffix:semicolon
multiline_comment|/* LSB first.  */
r_return
id|config
suffix:semicolon
)brace
multiline_comment|/* This should delay as long as necessary for a recently written config&n;   setting to settle, before we turn the uart back on.  */
r_static
r_inline
r_void
DECL|function|v850e_uart_config_delay
id|v850e_uart_config_delay
(paren
id|v850e_uart_config_t
id|config
comma
id|v850e_uart_speed_t
id|speed
)paren
(brace
multiline_comment|/* The UART may not be reset properly unless we wait at least 2&n;&t;   `basic-clocks&squot; until turning on the TXE/RXE bits again.&n;&t;   A `basic clock&squot; is the clock used by the baud-rate generator,&n;&t;   i.e., the cpu clock divided by the 2^new_clk_divlog2.&n;&t;   The loop takes 2 insns, so loop CYCLES / 2 times.  */
r_register
r_int
id|count
op_assign
l_int|1
op_lshift
id|speed
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
multiline_comment|/* RX/TX interface.  */
multiline_comment|/* Return true if all characters awaiting transmission on uart channel N&n;   have been transmitted.  */
DECL|macro|v850e_uart_xmit_done
mdefine_line|#define v850e_uart_xmit_done(n)&t;&t;&t;&t;&t;&t;      &bslash;&n;   (! (V850E_UARTB_STR(n) &amp; V850E_UARTB_STR_TSF))
multiline_comment|/* Wait for this to be true.  */
DECL|macro|v850e_uart_wait_for_xmit_done
mdefine_line|#define v850e_uart_wait_for_xmit_done(n)&t;&t;&t;&t;      &bslash;&n;   do { } while (! v850e_uart_xmit_done (n))
multiline_comment|/* Return true if uart channel N is ready to transmit a character.  */
DECL|macro|v850e_uart_xmit_ok
mdefine_line|#define v850e_uart_xmit_ok(n)&t;&t;&t;&t;&t;&t;      &bslash;&n;   (v850e_uart_xmit_done(n) &amp;&amp; v850e_uart_cts(n))
multiline_comment|/* Wait for this to be true.  */
DECL|macro|v850e_uart_wait_for_xmit_ok
mdefine_line|#define v850e_uart_wait_for_xmit_ok(n)&t;&t;&t;&t;&t;      &bslash;&n;   do { } while (! v850e_uart_xmit_ok (n))
multiline_comment|/* Write character CH to uart channel CHAN.  */
DECL|macro|v850e_uart_putc
mdefine_line|#define v850e_uart_putc(chan, ch)&t;(V850E_UARTB_TX(chan) = (ch))
multiline_comment|/* Return latest character read on channel CHAN.  */
DECL|macro|v850e_uart_getc
mdefine_line|#define v850e_uart_getc(chan)&t;&t;V850E_UARTB_RX (chan)
multiline_comment|/* Return bit-mask of uart error status.  */
DECL|macro|v850e_uart_err
mdefine_line|#define v850e_uart_err(chan)&t;&t;V850E_UARTB_STR (chan)
multiline_comment|/* Various error bits set in the error result.  */
DECL|macro|V850E_UART_ERR_OVERRUN
mdefine_line|#define V850E_UART_ERR_OVERRUN&t;&t;V850E_UARTB_STR_OVE
DECL|macro|V850E_UART_ERR_FRAME
mdefine_line|#define V850E_UART_ERR_FRAME&t;&t;V850E_UARTB_STR_FE
DECL|macro|V850E_UART_ERR_PARITY
mdefine_line|#define V850E_UART_ERR_PARITY&t;&t;V850E_UARTB_STR_PE
macro_line|#endif /* __V850_V850E_UARTB_H__ */
eof
