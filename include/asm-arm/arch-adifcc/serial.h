multiline_comment|/*&n; * include/asm-arm/arch-adifcc/serial.h&n; *&n; * Author: Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; *&n; * Copyright (c) 2001 MontaVista Software, Inc.&n; */
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1852000 / 16 )
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
macro_line|#ifdef CONFIG_ARCH_ADI_EVB
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 1
multiline_comment|/*&n; * One serial port, int goes to FIQ, so we run in polled mode&n; */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;       /* UART CLK      PORT        IRQ        FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0xff400000, 0,  STD_COM_FLAGS }  /* ttyS0 */
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
eof
