multiline_comment|/*&n; * include/asm-sh/serial.h&n; *&n; * Configuration details for 8250, 16450, 16550, etc. serial ports&n; */
macro_line|#ifndef _ASM_SERIAL_H
DECL|macro|_ASM_SERIAL_H
mdefine_line|#define _ASM_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, 4, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, 3, STD_COM_FLAGS }&t;/* ttyS1 */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS STD_SERIAL_PORT_DEFNS
multiline_comment|/* XXX: This should be moved ino irq.h */
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(x) (x)
macro_line|#endif /* _ASM_SERIAL_H */
eof
