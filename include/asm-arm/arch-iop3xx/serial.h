multiline_comment|/*&n; * include/asm-arm/arch-iop3xx/serial.h&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
macro_line|#ifdef CONFIG_ARCH_IQ80321
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1&t;IRQ_IQ80321_UART
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 1
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;       /* UART CLK      PORT        IRQ        FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0xfe800000, IRQ_UART1, STD_COM_FLAGS },  /* ttyS0 */
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ80321
macro_line|#ifdef CONFIG_ARCH_IQ31244
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1&t;IRQ_IQ31244_UART
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 1
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;       /* UART CLK      PORT        IRQ        FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0xfe800000, IRQ_UART1, STD_COM_FLAGS },  /* ttyS0 */
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ31244
macro_line|#ifdef CONFIG_ARCH_IQ80331
DECL|macro|BASE_BAUD
macro_line|#undef BASE_BAUD
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 33334000 / 16 )
DECL|macro|IRQ_UART0
mdefine_line|#define IRQ_UART0&t;IRQ_IQ80331_UART0
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1&t;IRQ_IQ80331_UART1
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 2
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  /*type: PORT_XSCALE,*/&t;&t;&t;&bslash;&n;&t;  /*xmit_fifo_size: 32,*/&t;&t;&t;&bslash;&n;&t;  baud_base: BASE_BAUD,&t;&t;&t;&t;&bslash;&n;&t;  irq: IRQ_UART0,&t;&t;&t;  &t;&bslash;&n;&t;  flags: STD_COM_FLAGS,&t;&t;&t;&t;&bslash;&n;&t;  iomem_base: IQ80331_UART0_VIRT,&t;&t;&bslash;&n;&t;  io_type: SERIAL_IO_MEM,&t;&t;&t;&bslash;&n;&t;  iomem_reg_shift: 2&t;&t;&t;&t;&bslash;&n;&t;}, /* ttyS0 */&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  /*type: PORT_XSCALE,*/&t;&t;&t;&bslash;&n;&t;  /*xmit_fifo_size: 32,*/&t;&t;&t;&bslash;&n;&t;  baud_base: BASE_BAUD,&t;&t;&t;&t;&bslash;&n;&t;  irq: IRQ_UART1,&t;&t;&t;  &t;&bslash;&n;&t;  flags: STD_COM_FLAGS,&t;&t;&t;&t;&bslash;&n;&t;  iomem_base: IQ80331_UART1_VIRT,&t;&t;&bslash;&n;&t;  io_type: SERIAL_IO_MEM,&t;&t;&t;&bslash;&n;&t;  iomem_reg_shift: 2&t;&t;&t;&t;&bslash;&n;&t;} /* ttyS1 */
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ80331
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
eof
