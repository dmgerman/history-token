multiline_comment|/*&n; * include/asm-arm/arch-sa1100/serial.h&n; * (C) 1999 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * All this is intended to be used with a 16550-like UART on the SA1100&squot;s &n; * PCMCIA bus.  It has nothing to do with the SA1100&squot;s internal serial ports.&n; * This is included by serial.c -- serial_sa1100.c makes no use of it.&n; */
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 4
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, IRQ_GPIO3, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, IRQ_GPIO3, STD_COM_FLAGS },&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3E8, IRQ_GPIO3, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2E8, IRQ_GPIO3, STD_COM4_FLAGS }&t;/* ttyS3 */
eof
