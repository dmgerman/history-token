macro_line|#include &lt;asm/lasat/lasat.h&gt;
multiline_comment|/* Lasat 100 boards serial configuration */
DECL|macro|LASAT_BASE_BAUD_100
mdefine_line|#define LASAT_BASE_BAUD_100 &t;&t;( 7372800 / 16 ) 
DECL|macro|LASAT_UART_REGS_BASE_100
mdefine_line|#define LASAT_UART_REGS_BASE_100&t;0x1c8b0000
DECL|macro|LASAT_UART_REGS_SHIFT_100
mdefine_line|#define LASAT_UART_REGS_SHIFT_100&t;2
DECL|macro|LASATINT_UART_100
mdefine_line|#define LASATINT_UART_100&t;&t;8
multiline_comment|/* * LASAT 200 boards serial configuration */
DECL|macro|LASAT_BASE_BAUD_200
mdefine_line|#define LASAT_BASE_BAUD_200&t;&t;(100000000 / 16 / 12) 
DECL|macro|LASAT_UART_REGS_BASE_200
mdefine_line|#define LASAT_UART_REGS_BASE_200&t;(Vrc5074_PHYS_BASE + 0x0300)
DECL|macro|LASAT_UART_REGS_SHIFT_200
mdefine_line|#define LASAT_UART_REGS_SHIFT_200&t;3
DECL|macro|LASATINT_UART_200
mdefine_line|#define LASATINT_UART_200&t;&t;13
eof
