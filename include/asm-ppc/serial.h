multiline_comment|/*&n; * BK Id: SCCS/s.serial.h 1.12 05/17/01 18:14:25 cort&n; */
multiline_comment|/*&n; * include/asm-ppc/serial.h&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_GEMINI
macro_line|#include &lt;asm/gemini_serial.h&gt;
macro_line|#elif defined(CONFIG_4xx)
macro_line|#include &lt;asm/ppc4xx_serial.h&gt;
macro_line|#else
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
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
DECL|macro|HUB6_FLAGS
mdefine_line|#define HUB6_FLAGS 0
macro_line|#endif
multiline_comment|/*&n; * The following define the access methods for the HUB6 card. All&n; * access is through two ports for all 24 possible chips. The card is&n; * selected through the high 2 bits, the port on that card with the&n; * &quot;middle&quot; 3 bits, and the register on that port with the bottom&n; * 3 bits.&n; *&n; * While the access port and interrupt is configurable, the default&n; * port locations are 0x302 for the port control register, and 0x303&n; * for the data read/write register. Normally, the interrupt is at irq3&n; * but can be anything from 3 to 7 inclusive. Note that using 3 will&n; * require disabling com2.&n; */
DECL|macro|C_P
mdefine_line|#define C_P(card,port) (((card)&lt;&lt;6|(port)&lt;&lt;3) + 1)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, 4, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, 3, STD_COM_FLAGS },&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3E8, 4, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2E8, 3, STD_COM4_FLAGS },&t;/* ttyS3 */
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1A0, 9, FOURPORT_FLAGS }, &t;/* ttyS4 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1A8, 9, FOURPORT_FLAGS },&t;/* ttyS5 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1B0, 9, FOURPORT_FLAGS },&t;/* ttyS6 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1B8, 9, FOURPORT_FLAGS },&t;/* ttyS7 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2A0, 5, FOURPORT_FLAGS },&t;/* ttyS8 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2A8, 5, FOURPORT_FLAGS },&t;/* ttyS9 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2B0, 5, FOURPORT_FLAGS },&t;/* ttyS10 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2B8, 5, FOURPORT_FLAGS },&t;/* ttyS11 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x330, 4, ACCENT_FLAGS },&t;/* ttyS12 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x338, 4, ACCENT_FLAGS },&t;/* ttyS13 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x000, 0, 0 },&t;/* ttyS14 (spare) */&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x000, 0, 0 },&t;/* ttyS15 (spare) */&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x100, 12, BOCA_FLAGS },&t;/* ttyS16 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x108, 12, BOCA_FLAGS },&t;/* ttyS17 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x110, 12, BOCA_FLAGS },&t;/* ttyS18 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x118, 12, BOCA_FLAGS },&t;/* ttyS19 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x120, 12, BOCA_FLAGS },&t;/* ttyS20 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x128, 12, BOCA_FLAGS },&t;/* ttyS21 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x130, 12, BOCA_FLAGS },&t;/* ttyS22 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x138, 12, BOCA_FLAGS },&t;/* ttyS23 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x140, 12, BOCA_FLAGS },&t;/* ttyS24 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x148, 12, BOCA_FLAGS },&t;/* ttyS25 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x150, 12, BOCA_FLAGS },&t;/* ttyS26 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x158, 12, BOCA_FLAGS },&t;/* ttyS27 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x160, 12, BOCA_FLAGS },&t;/* ttyS28 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x168, 12, BOCA_FLAGS },&t;/* ttyS29 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x170, 12, BOCA_FLAGS },&t;/* ttyS30 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x178, 12, BOCA_FLAGS },&t;/* ttyS31 */
macro_line|#else
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
multiline_comment|/* You can have up to four HUB6&squot;s in the system, but I&squot;ve only&n; * included two cards here for a total of twelve ports.&n; */
macro_line|#if (defined(CONFIG_HUB6) &amp;&amp; defined(CONFIG_SERIAL_MANY_PORTS))
DECL|macro|HUB6_SERIAL_PORT_DFNS
mdefine_line|#define HUB6_SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,0) },  /* ttyS32 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,1) },  /* ttyS33 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,2) },  /* ttyS34 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,3) },  /* ttyS35 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,4) },  /* ttyS36 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,5) },  /* ttyS37 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,0) },  /* ttyS38 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,1) },  /* ttyS39 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,2) },  /* ttyS40 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,3) },  /* ttyS41 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,4) },  /* ttyS42 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,5) },  /* ttyS43 */
macro_line|#else
DECL|macro|HUB6_SERIAL_PORT_DFNS
mdefine_line|#define HUB6_SERIAL_PORT_DFNS
macro_line|#endif
DECL|macro|MCA_SERIAL_PORT_DFNS
mdefine_line|#define MCA_SERIAL_PORT_DFNS
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;EXTRA_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;HUB6_SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;MCA_SERIAL_PORT_DFNS
macro_line|#endif /* !CONFIG_GEMINI and others */
macro_line|#endif /* __KERNEL__ */
eof
