macro_line|#include &lt;asm/ec3104.h&gt;
multiline_comment|/* Naturally we don&squot;t know the exact value but 115200 baud has a divisor&n; * of 9 and 19200 baud has a divisor of 52, so this seems like a good&n; * guess.  */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (16800000 / 16)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  3
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
multiline_comment|/* there is a fourth serial port with the expected values as well, but&n; * it&squot;s got the keyboard controller behind it so we can&squot;t really use it&n; * (without moving the keyboard driver to userspace, which doesn&squot;t sound&n; * like a very good idea) */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x11C00, EC3104_IRQBASE+7, STD_COM_FLAGS }, /* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x12000, EC3104_IRQBASE+8, STD_COM_FLAGS }, /* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x12400, EC3104_IRQBASE+9, STD_COM_FLAGS }, /* ttyS2 */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS STD_SERIAL_PORT_DEFNS
multiline_comment|/* XXX: This should be moved ino irq.h */
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(x) (x)
eof
