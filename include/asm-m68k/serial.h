multiline_comment|/*&n; * include/asm-m68k/serial.h&n; *&n; * currently this seems useful only for a Q40,&n; * its an almost exact copy of ../asm-alpha/serial.h &n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
multiline_comment|/* Standard COM flags (except for COM4, because of the 8514 problem) */
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST | ASYNC_AUTO_IRQ)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS ASYNC_BOOT_AUTOCONF
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|FOURPORT_FLAGS
mdefine_line|#define FOURPORT_FLAGS ASYNC_FOURPORT
DECL|macro|ACCENT_FLAGS
mdefine_line|#define ACCENT_FLAGS 0
DECL|macro|BOCA_FLAGS
mdefine_line|#define BOCA_FLAGS 0
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, 4, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, 3, STD_COM_FLAGS },&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3E8, 4, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2E8, 3, STD_COM4_FLAGS },&t;/* ttyS3 */
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1A0, 9, FOURPORT_FLAGS }, &t;/* ttyS4 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1A8, 9, FOURPORT_FLAGS },&t;/* ttyS5 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1B0, 9, FOURPORT_FLAGS },&t;/* ttyS6 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1B8, 9, FOURPORT_FLAGS },&t;/* ttyS7 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2A0, 5, FOURPORT_FLAGS },&t;/* ttyS8 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2A8, 5, FOURPORT_FLAGS },&t;/* ttyS9 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2B0, 5, FOURPORT_FLAGS },&t;/* ttyS10 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2B8, 5, FOURPORT_FLAGS },&t;/* ttyS11 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x330, 4, ACCENT_FLAGS },&t;/* ttyS12 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x338, 4, ACCENT_FLAGS },&t;/* ttyS13 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x000, 0, 0 },&t;/* ttyS14 (spare) */&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x000, 0, 0 },&t;/* ttyS15 (spare) */&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x100, 12, BOCA_FLAGS },&t;/* ttyS16 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x108, 12, BOCA_FLAGS },&t;/* ttyS17 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x110, 12, BOCA_FLAGS },&t;/* ttyS18 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x118, 12, BOCA_FLAGS },&t;/* ttyS19 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x120, 12, BOCA_FLAGS },&t;/* ttyS20 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x128, 12, BOCA_FLAGS },&t;/* ttyS21 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x130, 12, BOCA_FLAGS },&t;/* ttyS22 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x138, 12, BOCA_FLAGS },&t;/* ttyS23 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x140, 12, BOCA_FLAGS },&t;/* ttyS24 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x148, 12, BOCA_FLAGS },&t;/* ttyS25 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x150, 12, BOCA_FLAGS },&t;/* ttyS26 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x158, 12, BOCA_FLAGS },&t;/* ttyS27 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x160, 12, BOCA_FLAGS },&t;/* ttyS28 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x168, 12, BOCA_FLAGS },&t;/* ttyS29 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x170, 12, BOCA_FLAGS },&t;/* ttyS30 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x178, 12, BOCA_FLAGS },&t;/* ttyS31 */
macro_line|#else
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;EXTRA_SERIAL_PORT_DEFNS
eof
