multiline_comment|/*&n; * include/asm-v850/nb85e_uart.h -- On-chip UART often used with the&n; *&t;NB85E cpu core&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* There&squot;s not actually a single UART implementation used by nb85e&n;   derivatives, but rather a series of implementations that are all&n;   `close&squot; to one another.  This file attempts to capture some&n;   commonality between them.  */
macro_line|#ifndef __V850_NB85E_UART_H__
DECL|macro|__V850_NB85E_UART_H__
mdefine_line|#define __V850_NB85E_UART_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;/* Pick up chip-specific defs.  */
multiline_comment|/* The base address of the UART control registers for channel N.&n;   The default is the address used on the V850E/MA1.  */
macro_line|#ifndef NB85E_UART_BASE_ADDR
DECL|macro|NB85E_UART_BASE_ADDR
mdefine_line|#define NB85E_UART_BASE_ADDR(n)&t;&t;(0xFFFFFA00 + 0x10 * (n))
macro_line|#endif 
multiline_comment|/* Addresses of specific UART control registers for channel N.&n;   The defaults are the addresses used on the V850E/MA1; if a platform&n;   wants to redefine any of these, it must redefine them all.  */
macro_line|#ifndef NB85E_UART_ASIM_ADDR
DECL|macro|NB85E_UART_ASIM_ADDR
mdefine_line|#define NB85E_UART_ASIM_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x0)
DECL|macro|NB85E_UART_RXB_ADDR
mdefine_line|#define NB85E_UART_RXB_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x2)
DECL|macro|NB85E_UART_ASIS_ADDR
mdefine_line|#define NB85E_UART_ASIS_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x3)
DECL|macro|NB85E_UART_TXB_ADDR
mdefine_line|#define NB85E_UART_TXB_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x4)
DECL|macro|NB85E_UART_ASIF_ADDR
mdefine_line|#define NB85E_UART_ASIF_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x5)
DECL|macro|NB85E_UART_CKSR_ADDR
mdefine_line|#define NB85E_UART_CKSR_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x6)
DECL|macro|NB85E_UART_BRGC_ADDR
mdefine_line|#define NB85E_UART_BRGC_ADDR(n)&t;&t;(NB85E_UART_BASE_ADDR(n) + 0x7)
macro_line|#endif
multiline_comment|/* UART config registers.  */
DECL|macro|NB85E_UART_ASIM
mdefine_line|#define NB85E_UART_ASIM(n)&t;(*(volatile u8 *)NB85E_UART_ASIM_ADDR(n))
multiline_comment|/* Control bits for config registers.  */
DECL|macro|NB85E_UART_ASIM_CAE
mdefine_line|#define NB85E_UART_ASIM_CAE&t;0x80 /* clock enable */
DECL|macro|NB85E_UART_ASIM_TXE
mdefine_line|#define NB85E_UART_ASIM_TXE&t;0x40 /* transmit enable */
DECL|macro|NB85E_UART_ASIM_RXE
mdefine_line|#define NB85E_UART_ASIM_RXE&t;0x20 /* receive enable */
DECL|macro|NB85E_UART_ASIM_PS_MASK
mdefine_line|#define NB85E_UART_ASIM_PS_MASK&t;0x18 /* mask covering parity-select bits */
DECL|macro|NB85E_UART_ASIM_PS_NONE
mdefine_line|#define NB85E_UART_ASIM_PS_NONE&t;0x00 /* no parity */
DECL|macro|NB85E_UART_ASIM_PS_ZERO
mdefine_line|#define NB85E_UART_ASIM_PS_ZERO&t;0x08 /* zero parity */
DECL|macro|NB85E_UART_ASIM_PS_ODD
mdefine_line|#define NB85E_UART_ASIM_PS_ODD&t;0x10 /* odd parity */
DECL|macro|NB85E_UART_ASIM_PS_EVEN
mdefine_line|#define NB85E_UART_ASIM_PS_EVEN&t;0x18 /* even parity */
DECL|macro|NB85E_UART_ASIM_CL_8
mdefine_line|#define NB85E_UART_ASIM_CL_8&t;0x04 /* char len is 8 bits (otherwise, 7) */
DECL|macro|NB85E_UART_ASIM_SL_2
mdefine_line|#define NB85E_UART_ASIM_SL_2&t;0x02 /* 2 stop bits (otherwise, 1) */
DECL|macro|NB85E_UART_ASIM_ISRM
mdefine_line|#define NB85E_UART_ASIM_ISRM&t;0x01 /* generate INTSR interrupt on errors&n;&t;&t;&t;&t;&t;(otherwise, generate INTSER) */
multiline_comment|/* UART serial interface status registers.  */
DECL|macro|NB85E_UART_ASIS
mdefine_line|#define NB85E_UART_ASIS(n)&t;(*(volatile u8 *)NB85E_UART_ASIS_ADDR(n))
multiline_comment|/* Control bits for status registers.  */
DECL|macro|NB85E_UART_ASIS_PE
mdefine_line|#define NB85E_UART_ASIS_PE&t;0x04 /* parity error */
DECL|macro|NB85E_UART_ASIS_FE
mdefine_line|#define NB85E_UART_ASIS_FE&t;0x02 /* framing error */
DECL|macro|NB85E_UART_ASIS_OVE
mdefine_line|#define NB85E_UART_ASIS_OVE&t;0x01 /* overrun error */
multiline_comment|/* UART serial interface transmission status registers.  */
DECL|macro|NB85E_UART_ASIF
mdefine_line|#define NB85E_UART_ASIF(n)&t;(*(volatile u8 *)NB85E_UART_ASIF_ADDR(n))
DECL|macro|NB85E_UART_ASIF_TXBF
mdefine_line|#define NB85E_UART_ASIF_TXBF&t;0x02 /* transmit buffer flag (data in TXB) */
DECL|macro|NB85E_UART_ASIF_TXSF
mdefine_line|#define NB85E_UART_ASIF_TXSF&t;0x01 /* transmit shift flag (sending data) */
multiline_comment|/* UART receive buffer register.  */
DECL|macro|NB85E_UART_RXB
mdefine_line|#define NB85E_UART_RXB(n)&t;(*(volatile u8 *)NB85E_UART_RXB_ADDR(n))
multiline_comment|/* UART transmit buffer register.  */
DECL|macro|NB85E_UART_TXB
mdefine_line|#define NB85E_UART_TXB(n)&t;(*(volatile u8 *)NB85E_UART_TXB_ADDR(n))
multiline_comment|/* UART baud-rate generator control registers.  */
DECL|macro|NB85E_UART_CKSR
mdefine_line|#define NB85E_UART_CKSR(n)&t;(*(volatile u8 *)NB85E_UART_CKSR_ADDR(n))
DECL|macro|NB85E_UART_CKSR_MAX
mdefine_line|#define NB85E_UART_CKSR_MAX&t;11
DECL|macro|NB85E_UART_CKSR_MAX_FREQ
mdefine_line|#define NB85E_UART_CKSR_MAX_FREQ (25*1000*1000)
DECL|macro|NB85E_UART_BRGC
mdefine_line|#define NB85E_UART_BRGC(n)&t;(*(volatile u8 *)NB85E_UART_BRGC_ADDR(n))
multiline_comment|/* This UART doesn&squot;t implement RTS/CTS by default, but some platforms&n;   implement them externally, so check to see if &lt;asm/machdep.h&gt; defined&n;   anything.  */
macro_line|#ifdef NB85E_UART_CTS
DECL|macro|nb85e_uart_cts
mdefine_line|#define nb85e_uart_cts(n)&t;NB85E_UART_CTS(n)
macro_line|#else
DECL|macro|nb85e_uart_cts
mdefine_line|#define nb85e_uart_cts(n)&t;(1)
macro_line|#endif
multiline_comment|/* Do the same for RTS.  */
macro_line|#ifdef NB85E_UART_SET_RTS
DECL|macro|nb85e_uart_set_rts
mdefine_line|#define nb85e_uart_set_rts(n,v)&t;NB85E_UART_SET_RTS(n,v)
macro_line|#else
DECL|macro|nb85e_uart_set_rts
mdefine_line|#define nb85e_uart_set_rts(n,v)&t;((void)0)
macro_line|#endif
multiline_comment|/* Return true if all characters awaiting transmission on uart channel N&n;   have been transmitted.  */
DECL|macro|nb85e_uart_xmit_done
mdefine_line|#define nb85e_uart_xmit_done(n)&t;&t;&t;&t;&t;&t;      &bslash;&n;   (! (NB85E_UART_ASIF(n) &amp; NB85E_UART_ASIF_TXBF))
multiline_comment|/* Wait for this to be true.  */
DECL|macro|nb85e_uart_wait_for_xmit_done
mdefine_line|#define nb85e_uart_wait_for_xmit_done(n)&t;&t;&t;&t;      &bslash;&n;   do { } while (! nb85e_uart_xmit_done (n))
multiline_comment|/* Return true if uart channel N is ready to transmit a character.  */
DECL|macro|nb85e_uart_xmit_ok
mdefine_line|#define nb85e_uart_xmit_ok(n)&t;&t;&t;&t;&t;&t;      &bslash;&n;   (nb85e_uart_xmit_done(n) &amp;&amp; nb85e_uart_cts(n))
multiline_comment|/* Wait for this to be true.  */
DECL|macro|nb85e_uart_wait_for_xmit_ok
mdefine_line|#define nb85e_uart_wait_for_xmit_ok(n)&t;&t;&t;&t;&t;      &bslash;&n;   do { } while (! nb85e_uart_xmit_ok (n))
multiline_comment|/* Write character CH to uart channel N.  */
DECL|macro|nb85e_uart_putc
mdefine_line|#define nb85e_uart_putc(n, ch)&t;(NB85E_UART_TXB(n) = (ch))
DECL|macro|NB85E_UART_MINOR_BASE
mdefine_line|#define NB85E_UART_MINOR_BASE&t;64
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Setup a console using channel 0 of the builtin uart.  */
r_extern
r_void
id|nb85e_uart_cons_init
(paren
r_int
id|chan
)paren
suffix:semicolon
multiline_comment|/* Configure and turn on uart channel CHAN, using the termios `control&n;   modes&squot; bits in CFLAGS, and a baud-rate of BAUD.  */
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
suffix:semicolon
multiline_comment|/* If the macro NB85E_UART_PRE_CONFIGURE is defined (presumably by a&n;   &lt;asm/machdep.h&gt;), it is called from nb85e_uart_pre_configure before&n;   anything else is done, with interrupts disabled.  */
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_NB85E_UART_H__ */
eof
