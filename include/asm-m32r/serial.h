macro_line|#ifndef _ASM_M32R_SERIAL_H
DECL|macro|_ASM_M32R_SERIAL_H
mdefine_line|#define _ASM_M32R_SERIAL_H
multiline_comment|/*&n; * include/asm-m32r/serial.h&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
multiline_comment|/* Standard PORT definitions */
macro_line|#if defined(CONFIG_PLAT_USRV)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&t;&t;&t;&bslash;&n;       /* UART  CLK     PORT   IRQ            FLAGS */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, PLD_IRQ_UART0, STD_COM_FLAGS }, /* ttyS0 */ &bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, PLD_IRQ_UART1, STD_COM_FLAGS }, /* ttyS1 */
macro_line|#else /* !CONFIG_PLAT_USRV */
macro_line|#if defined(CONFIG_SERIAL_M32R_PLDSIO)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, ((unsigned long)PLD_ESIO0CR), PLD_IRQ_SIO0_RCV,&t;&bslash;&n;&t;  STD_COM_FLAGS }, /* ttyS0 */
macro_line|#else
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, M32R_SIO_OFFSET, M32R_IRQ_SIO0_R,&t;&t;&bslash;&n;&t;  STD_COM_FLAGS }, /* ttyS0 */
macro_line|#endif
macro_line|#endif /* !CONFIG_PLAT_USRV */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;STD_SERIAL_PORT_DEFNS
macro_line|#endif  /* _ASM_M32R_SERIAL_H */
eof
