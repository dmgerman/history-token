multiline_comment|/*&n; * include/asm-v850/v850e_uart.h -- common V850E on-chip UART driver&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* There&squot;s not actually a single UART implementation used by V850E CPUs,&n;   but rather a series of implementations that are all `close&squot; to one&n;   another.  This file corresponds to the single driver which handles all&n;   of them.  */
macro_line|#ifndef __V850_V850E_UART_H__
DECL|macro|__V850_V850E_UART_H__
mdefine_line|#define __V850_V850E_UART_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;asm/v850e_utils.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;/* Pick up chip-specific defs.  */
multiline_comment|/* Include model-specific definitions.  */
macro_line|#ifdef CONFIG_V850E_UART
macro_line|# ifdef CONFIG_V850E_UARTB
macro_line|#  include &lt;asm-v850/v850e_uartb.h&gt;
macro_line|# else
macro_line|#  include &lt;asm-v850/v850e_uarta.h&gt; /* original V850E UART */
macro_line|# endif
macro_line|#endif
multiline_comment|/* Optional capabilities some hardware provides.  */
multiline_comment|/* This UART doesn&squot;t implement RTS/CTS by default, but some platforms&n;   implement them externally, so check to see if &lt;asm/machdep.h&gt; defined&n;   anything.  */
macro_line|#ifdef V850E_UART_CTS
DECL|macro|v850e_uart_cts
mdefine_line|#define v850e_uart_cts(n)&t;&t;V850E_UART_CTS(n)
macro_line|#else
DECL|macro|v850e_uart_cts
mdefine_line|#define v850e_uart_cts(n)&t;&t;(1)
macro_line|#endif
multiline_comment|/* Do the same for RTS.  */
macro_line|#ifdef V850E_UART_SET_RTS
DECL|macro|v850e_uart_set_rts
mdefine_line|#define v850e_uart_set_rts(n,v)&t;&t;V850E_UART_SET_RTS(n,v)
macro_line|#else
DECL|macro|v850e_uart_set_rts
mdefine_line|#define v850e_uart_set_rts(n,v)&t;&t;((void)0)
macro_line|#endif
multiline_comment|/* This is the serial channel to use for the boot console (if desired).  */
macro_line|#ifndef V850E_UART_CONSOLE_CHANNEL
DECL|macro|V850E_UART_CONSOLE_CHANNEL
macro_line|# define V850E_UART_CONSOLE_CHANNEL 0
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Setup a console using channel 0 of the builtin uart.  */
r_extern
r_void
id|v850e_uart_cons_init
(paren
r_int
id|chan
)paren
suffix:semicolon
multiline_comment|/* Configure and turn on uart channel CHAN, using the termios `control&n;   modes&squot; bits in CFLAGS, and a baud-rate of BAUD.  */
r_void
id|v850e_uart_configure
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
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_V850E_UART_H__ */
eof
