multiline_comment|/*&n; * include/asm-v850/v850e_uarta.h -- original V850E on-chip UART&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* This is the original V850E UART implementation is called just `UART&squot; in&n;   the docs, but we name this header file &lt;asm/v850e_uarta.h&gt; because the&n;   name &lt;asm/v850e_uart.h&gt; is used for the common driver that handles both&n;   `UART&squot; and `UARTB&squot; implementations.  */
macro_line|#ifndef __V850_V850E_UARTA_H__
DECL|macro|__V850_V850E_UARTA_H__
mdefine_line|#define __V850_V850E_UARTA_H__
"&f;"
multiline_comment|/* Raw hardware interface.  */
multiline_comment|/* The base address of the UART control registers for channel N.&n;   The default is the address used on the V850E/MA1.  */
macro_line|#ifndef V850E_UART_BASE_ADDR
DECL|macro|V850E_UART_BASE_ADDR
mdefine_line|#define V850E_UART_BASE_ADDR(n)&t;&t;(0xFFFFFA00 + 0x10 * (n))
macro_line|#endif 
multiline_comment|/* Addresses of specific UART control registers for channel N.&n;   The defaults are the addresses used on the V850E/MA1; if a platform&n;   wants to redefine any of these, it must redefine them all.  */
macro_line|#ifndef V850E_UART_ASIM_ADDR
DECL|macro|V850E_UART_ASIM_ADDR
mdefine_line|#define V850E_UART_ASIM_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x0)
DECL|macro|V850E_UART_RXB_ADDR
mdefine_line|#define V850E_UART_RXB_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x2)
DECL|macro|V850E_UART_ASIS_ADDR
mdefine_line|#define V850E_UART_ASIS_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x3)
DECL|macro|V850E_UART_TXB_ADDR
mdefine_line|#define V850E_UART_TXB_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x4)
DECL|macro|V850E_UART_ASIF_ADDR
mdefine_line|#define V850E_UART_ASIF_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x5)
DECL|macro|V850E_UART_CKSR_ADDR
mdefine_line|#define V850E_UART_CKSR_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x6)
DECL|macro|V850E_UART_BRGC_ADDR
mdefine_line|#define V850E_UART_BRGC_ADDR(n)&t;&t;(V850E_UART_BASE_ADDR(n) + 0x7)
macro_line|#endif
multiline_comment|/* UART config registers.  */
DECL|macro|V850E_UART_ASIM
mdefine_line|#define V850E_UART_ASIM(n)&t;(*(volatile u8 *)V850E_UART_ASIM_ADDR(n))
multiline_comment|/* Control bits for config registers.  */
DECL|macro|V850E_UART_ASIM_CAE
mdefine_line|#define V850E_UART_ASIM_CAE&t;0x80 /* clock enable */
DECL|macro|V850E_UART_ASIM_TXE
mdefine_line|#define V850E_UART_ASIM_TXE&t;0x40 /* transmit enable */
DECL|macro|V850E_UART_ASIM_RXE
mdefine_line|#define V850E_UART_ASIM_RXE&t;0x20 /* receive enable */
DECL|macro|V850E_UART_ASIM_PS_MASK
mdefine_line|#define V850E_UART_ASIM_PS_MASK&t;0x18 /* mask covering parity-select bits */
DECL|macro|V850E_UART_ASIM_PS_NONE
mdefine_line|#define V850E_UART_ASIM_PS_NONE&t;0x00 /* no parity */
DECL|macro|V850E_UART_ASIM_PS_ZERO
mdefine_line|#define V850E_UART_ASIM_PS_ZERO&t;0x08 /* zero parity */
DECL|macro|V850E_UART_ASIM_PS_ODD
mdefine_line|#define V850E_UART_ASIM_PS_ODD&t;0x10 /* odd parity */
DECL|macro|V850E_UART_ASIM_PS_EVEN
mdefine_line|#define V850E_UART_ASIM_PS_EVEN&t;0x18 /* even parity */
DECL|macro|V850E_UART_ASIM_CL_8
mdefine_line|#define V850E_UART_ASIM_CL_8&t;0x04 /* char len is 8 bits (otherwise, 7) */
DECL|macro|V850E_UART_ASIM_SL_2
mdefine_line|#define V850E_UART_ASIM_SL_2&t;0x02 /* 2 stop bits (otherwise, 1) */
DECL|macro|V850E_UART_ASIM_ISRM
mdefine_line|#define V850E_UART_ASIM_ISRM&t;0x01 /* generate INTSR interrupt on errors&n;&t;&t;&t;&t;&t;(otherwise, generate INTSER) */
multiline_comment|/* UART serial interface status registers.  */
DECL|macro|V850E_UART_ASIS
mdefine_line|#define V850E_UART_ASIS(n)&t;(*(volatile u8 *)V850E_UART_ASIS_ADDR(n))
multiline_comment|/* Control bits for status registers.  */
DECL|macro|V850E_UART_ASIS_PE
mdefine_line|#define V850E_UART_ASIS_PE&t;0x04 /* parity error */
DECL|macro|V850E_UART_ASIS_FE
mdefine_line|#define V850E_UART_ASIS_FE&t;0x02 /* framing error */
DECL|macro|V850E_UART_ASIS_OVE
mdefine_line|#define V850E_UART_ASIS_OVE&t;0x01 /* overrun error */
multiline_comment|/* UART serial interface transmission status registers.  */
DECL|macro|V850E_UART_ASIF
mdefine_line|#define V850E_UART_ASIF(n)&t;(*(volatile u8 *)V850E_UART_ASIF_ADDR(n))
DECL|macro|V850E_UART_ASIF_TXBF
mdefine_line|#define V850E_UART_ASIF_TXBF&t;0x02 /* transmit buffer flag (data in TXB) */
DECL|macro|V850E_UART_ASIF_TXSF
mdefine_line|#define V850E_UART_ASIF_TXSF&t;0x01 /* transmit shift flag (sending data) */
multiline_comment|/* UART receive buffer register.  */
DECL|macro|V850E_UART_RXB
mdefine_line|#define V850E_UART_RXB(n)&t;(*(volatile u8 *)V850E_UART_RXB_ADDR(n))
multiline_comment|/* UART transmit buffer register.  */
DECL|macro|V850E_UART_TXB
mdefine_line|#define V850E_UART_TXB(n)&t;(*(volatile u8 *)V850E_UART_TXB_ADDR(n))
multiline_comment|/* UART baud-rate generator control registers.  */
DECL|macro|V850E_UART_CKSR
mdefine_line|#define V850E_UART_CKSR(n)&t;(*(volatile u8 *)V850E_UART_CKSR_ADDR(n))
DECL|macro|V850E_UART_CKSR_MAX
mdefine_line|#define V850E_UART_CKSR_MAX&t;11
DECL|macro|V850E_UART_BRGC
mdefine_line|#define V850E_UART_BRGC(n)&t;(*(volatile u8 *)V850E_UART_BRGC_ADDR(n))
DECL|macro|V850E_UART_BRGC_MIN
mdefine_line|#define V850E_UART_BRGC_MIN&t;8
macro_line|#ifndef V850E_UART_CKSR_MAX_FREQ
DECL|macro|V850E_UART_CKSR_MAX_FREQ
mdefine_line|#define V850E_UART_CKSR_MAX_FREQ (25*1000*1000)
macro_line|#endif
multiline_comment|/* Calculate the minimum value for CKSR on this processor.  */
DECL|function|v850e_uart_cksr_min
r_static
r_inline
r_int
id|v850e_uart_cksr_min
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
id|V850E_UART_BASE_FREQ
suffix:semicolon
r_while
c_loop
(paren
id|freq
OG
id|V850E_UART_CKSR_MAX_FREQ
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
"&f;"
multiline_comment|/* Slightly abstract interface used by driver.  */
multiline_comment|/* Interrupts used by the UART.  */
multiline_comment|/* Received when the most recently transmitted character has been sent.  */
DECL|macro|V850E_UART_TX_IRQ
mdefine_line|#define V850E_UART_TX_IRQ(chan)&t;&t;IRQ_INTST (chan)
multiline_comment|/* Received when a new character has been received.  */
DECL|macro|V850E_UART_RX_IRQ
mdefine_line|#define V850E_UART_RX_IRQ(chan)&t;&t;IRQ_INTSR (chan)
multiline_comment|/* UART clock generator interface.  */
multiline_comment|/* This type encapsulates a particular uart frequency.  */
r_typedef
r_struct
(brace
DECL|member|clk_divlog2
r_int
id|clk_divlog2
suffix:semicolon
DECL|member|brgen_count
r_int
id|brgen_count
suffix:semicolon
DECL|typedef|v850e_uart_speed_t
)brace
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
multiline_comment|/* Calculate the log2 clock divider and baud-rate counter values&n;&t;   (note that the UART divides the resulting clock by 2, so&n;&t;   multiply BAUD by 2 here to compensate).  */
id|calc_counter_params
(paren
id|V850E_UART_BASE_FREQ
comma
id|baud
op_star
l_int|2
comma
id|v850e_uart_cksr_min
c_func
(paren
)paren
comma
id|V850E_UART_CKSR_MAX
comma
l_int|8
multiline_comment|/*bits*/
comma
op_amp
id|speed.clk_divlog2
comma
op_amp
id|speed.brgen_count
)paren
suffix:semicolon
r_return
id|speed
suffix:semicolon
)brace
multiline_comment|/* Return the current speed of uart channel CHAN.  */
DECL|function|v850e_uart_speed
r_static
r_inline
id|v850e_uart_speed_t
id|v850e_uart_speed
(paren
r_int
id|chan
)paren
(brace
id|v850e_uart_speed_t
id|speed
suffix:semicolon
id|speed.clk_divlog2
op_assign
id|V850E_UART_CKSR
(paren
id|chan
)paren
suffix:semicolon
id|speed.brgen_count
op_assign
id|V850E_UART_BRGC
(paren
id|chan
)paren
suffix:semicolon
r_return
id|speed
suffix:semicolon
)brace
multiline_comment|/* Set the current speed of uart channel CHAN.  */
DECL|function|v850e_uart_set_speed
r_static
r_inline
r_void
id|v850e_uart_set_speed
c_func
(paren
r_int
id|chan
comma
id|v850e_uart_speed_t
id|speed
)paren
(brace
id|V850E_UART_CKSR
(paren
id|chan
)paren
op_assign
id|speed.clk_divlog2
suffix:semicolon
id|V850E_UART_BRGC
(paren
id|chan
)paren
op_assign
id|speed.brgen_count
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|v850e_uart_speed_eq
id|v850e_uart_speed_eq
(paren
id|v850e_uart_speed_t
id|speed1
comma
id|v850e_uart_speed_t
id|speed2
)paren
(brace
r_return
id|speed1.clk_divlog2
op_eq
id|speed2.clk_divlog2
op_logical_and
id|speed1.brgen_count
op_eq
id|speed2.brgen_count
suffix:semicolon
)brace
multiline_comment|/* Minimum baud rate possible.  */
DECL|macro|v850e_uart_min_baud
mdefine_line|#define v850e_uart_min_baud() &bslash;&n;   ((V850E_UART_BASE_FREQ &gt;&gt; V850E_UART_CKSR_MAX) / (2 * 255) + 1)
multiline_comment|/* Maximum baud rate possible.  The error is quite high at max, though.  */
DECL|macro|v850e_uart_max_baud
mdefine_line|#define v850e_uart_max_baud() &bslash;&n;   ((V850E_UART_BASE_FREQ &gt;&gt; v850e_uart_cksr_min()) / (2 *V850E_UART_BRGC_MIN))
multiline_comment|/* The `maximum&squot; clock rate the uart can used, which is wanted (though not&n;   really used in any useful way) by the serial framework.  */
DECL|macro|v850e_uart_max_clock
mdefine_line|#define v850e_uart_max_clock() &bslash;&n;   ((V850E_UART_BASE_FREQ &gt;&gt; v850e_uart_cksr_min()) / 2)
multiline_comment|/* UART configuration interface.  */
multiline_comment|/* Type of the uart config register; must be a scalar.  */
DECL|typedef|v850e_uart_config_t
r_typedef
id|u16
id|v850e_uart_config_t
suffix:semicolon
multiline_comment|/* The uart hardware config register for channel CHAN.  */
DECL|macro|V850E_UART_CONFIG
mdefine_line|#define V850E_UART_CONFIG(chan)&t;&t;V850E_UART_ASIM (chan)
multiline_comment|/* This config bit set if the uart is enabled.  */
DECL|macro|V850E_UART_CONFIG_ENABLED
mdefine_line|#define V850E_UART_CONFIG_ENABLED&t;V850E_UART_ASIM_CAE
multiline_comment|/* If the uart _isn&squot;t_ enabled, store this value to it to do so.  */
DECL|macro|V850E_UART_CONFIG_INIT
mdefine_line|#define V850E_UART_CONFIG_INIT&t;&t;V850E_UART_ASIM_CAE
multiline_comment|/* Store this config value to disable the uart channel completely.  */
DECL|macro|V850E_UART_CONFIG_FINI
mdefine_line|#define V850E_UART_CONFIG_FINI&t;&t;0
multiline_comment|/* Setting/clearing these bits enable/disable TX/RX, respectively (but&n;   otherwise generally leave things running).  */
DECL|macro|V850E_UART_CONFIG_RX_ENABLE
mdefine_line|#define V850E_UART_CONFIG_RX_ENABLE&t;V850E_UART_ASIM_RXE
DECL|macro|V850E_UART_CONFIG_TX_ENABLE
mdefine_line|#define V850E_UART_CONFIG_TX_ENABLE&t;V850E_UART_ASIM_TXE
multiline_comment|/* These masks define which config bits affect TX/RX modes, respectively.  */
DECL|macro|V850E_UART_CONFIG_RX_BITS
mdefine_line|#define V850E_UART_CONFIG_RX_BITS &bslash;&n;  (V850E_UART_ASIM_PS_MASK | V850E_UART_ASIM_CL_8 | V850E_UART_ASIM_ISRM)
DECL|macro|V850E_UART_CONFIG_TX_BITS
mdefine_line|#define V850E_UART_CONFIG_TX_BITS &bslash;&n;  (V850E_UART_ASIM_PS_MASK | V850E_UART_ASIM_CL_8 | V850E_UART_ASIM_SL_2)
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
id|V850E_UART_ASIM_SL_2
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
id|V850E_UART_ASIM_CL_8
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
id|V850E_UART_ASIM_PS_NONE
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
id|V850E_UART_ASIM_PS_ODD
suffix:semicolon
r_else
multiline_comment|/* Even parity check/generation.  */
id|config
op_or_assign
id|V850E_UART_ASIM_PS_EVEN
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
id|V850E_UART_ASIM_RXE
suffix:semicolon
id|config
op_or_assign
id|V850E_UART_ASIM_CAE
suffix:semicolon
id|config
op_or_assign
id|V850E_UART_ASIM_TXE
suffix:semicolon
multiline_comment|/* Writing is always enabled.  */
id|config
op_or_assign
id|V850E_UART_ASIM_ISRM
suffix:semicolon
multiline_comment|/* Errors generate a read-irq.  */
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
id|speed.clk_divlog2
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
mdefine_line|#define v850e_uart_xmit_done(n)&t;&t;&t;&t;&t;&t;      &bslash;&n;   (! (V850E_UART_ASIF(n) &amp; V850E_UART_ASIF_TXBF))
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
mdefine_line|#define v850e_uart_putc(chan, ch)&t;(V850E_UART_TXB(chan) = (ch))
multiline_comment|/* Return latest character read on channel CHAN.  */
DECL|macro|v850e_uart_getc
mdefine_line|#define v850e_uart_getc(chan)&t;&t;V850E_UART_RXB (chan)
multiline_comment|/* Return bit-mask of uart error status.  */
DECL|macro|v850e_uart_err
mdefine_line|#define v850e_uart_err(chan)&t;&t;V850E_UART_ASIS (chan)
multiline_comment|/* Various error bits set in the error result.  */
DECL|macro|V850E_UART_ERR_OVERRUN
mdefine_line|#define V850E_UART_ERR_OVERRUN&t;&t;V850E_UART_ASIS_OVE
DECL|macro|V850E_UART_ERR_FRAME
mdefine_line|#define V850E_UART_ERR_FRAME&t;&t;V850E_UART_ASIS_FE
DECL|macro|V850E_UART_ERR_PARITY
mdefine_line|#define V850E_UART_ERR_PARITY&t;&t;V850E_UART_ASIS_PE
macro_line|#endif /* __V850_V850E_UARTA_H__ */
eof
