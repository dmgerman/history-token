multiline_comment|/*&n; * include/asm-arm/arch-sa1100/serial.h&n; * (C) 1999 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * All this is intended to be used with a 16550-like UART on the SA1100&squot;s &n; * PCMCIA bus.  It has nothing to do with the SA1100&squot;s internal serial ports.&n; * This is included by serial.c -- serial_sa1100.c makes no use of it.&n; */
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
multiline_comment|/*&n; * Rather empty table...&n; * Hardwired serial ports should be defined here.&n; * PCMCIA will fill it dynamically.&n; */
macro_line|#ifdef CONFIG_SA1100_TRIZEPS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 2
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&bslash;&n;       /* UART&t;CLK     &t;PORT&t;&t;IRQ&t;&t;FLAGS&t;&t;*/ &bslash;&n;&t;{ 0,&t;1500000,&t;TRIZEPS_UART5,&t;IRQ_GPIO16,&t;STD_COM_FLAGS },   &bslash;&n;&t;{ 0,&t;1500000,&t;TRIZEPS_UART6,&t;IRQ_GPIO17,&t;STD_COM_FLAGS }
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 4
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&bslash;&n;       /* UART&t;CLK     &t;PORT&t;&t;IRQ&t;FLAGS&t;&t;*/ &bslash;&n;&t;{ 0,&t;BASE_BAUD,&t;0, &t;&t;0,&t;STD_COM_FLAGS },   &bslash;&n;&t;{ 0,&t;BASE_BAUD,&t;0, &t;&t;0,&t;STD_COM_FLAGS },   &bslash;&n;&t;{ 0,&t;BASE_BAUD,&t;0, &t;&t;0,&t;STD_COM_FLAGS },   &bslash;&n;&t;{ 0,&t;BASE_BAUD,&t;0, &t;&t;0,&t;STD_COM_FLAGS }
macro_line|#endif
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
eof
