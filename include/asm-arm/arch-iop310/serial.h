multiline_comment|/*&n; * include/asm-arm/arch-iop310/serial.h&n; */
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
macro_line|#ifdef CONFIG_ARCH_IQ80310
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1&t;IRQ_IQ80310_UART1
DECL|macro|IRQ_UART2
mdefine_line|#define IRQ_UART2&t;IRQ_IQ80310_UART2
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 2
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;       /* UART CLK      PORT        IRQ        FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0xfe810000, IRQ_UART2, STD_COM_FLAGS },  /* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0xfe800000, IRQ_UART1, STD_COM_FLAGS }  /* ttyS1 */
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ80310
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
eof
