multiline_comment|/*&n; * include/asm-parisc/serial.h&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This assumes you have a 7.272727 MHz clock for your UART.&n; * The documentation implies a 40Mhz clock, and elsewhere a 7Mhz clock&n; * Clarified: 7.2727MHz on LASI. Not yet clarified for DINO&n; */
DECL|macro|LASI_BASE_BAUD
mdefine_line|#define LASI_BASE_BAUD ( 7272727 / 16 )
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  LASI_BASE_BAUD
multiline_comment|/*&n; * We don&squot;t use the ISA probing code, so these entries are just to reserve&n; * space.  Some example (maximal) configurations:&n; * - 712 w/ additional Lasi &amp; RJ16 ports: 4&n; * - J5k w/ PCI serial cards: 2 + 4 * card ~= 34&n; * A500 w/ PCI serial cards: 5 + 4 * card ~= 17&n; */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS3 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS4 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS5 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS6 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS7 */&t;&bslash;&n;&t;{ 0, },&t;&t;/* ttyS8 */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS
eof
