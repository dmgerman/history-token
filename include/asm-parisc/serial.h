multiline_comment|/*&n; * include/asm-parisc/serial.h&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/gsc.h&gt;
multiline_comment|/*&n; * This assumes you have a 7.272727 MHz clock for your UART.&n; * The documentation implies a 40Mhz clock, and elsewhere a 7Mhz clock&n; * Clarified: 7.2727MHz on LASI. Not yet clarified for DINO&n; */
DECL|macro|LASI_BASE_BAUD
mdefine_line|#define LASI_BASE_BAUD ( 7272727 / 16 )
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  LASI_BASE_BAUD
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
DECL|macro|HUB6_FLAGS
mdefine_line|#define HUB6_FLAGS 0
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
multiline_comment|/*&n; *&t;The base is relative to the LASI base. We can fix that&n; *&t;up later. We could also virtually map LASI so that we get&n; *&t;nice constants all over our kernel...&n; */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, LASI_BASE_BAUD, -1, 4, ASYNC_SKIP_TEST, 0, PORT_UNKNOWN,}, /* ttyS0 */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS
eof
