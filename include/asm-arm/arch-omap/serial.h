multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/serial.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; * serial definitions&n; *&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
DECL|macro|OMAP_UART1_BASE
mdefine_line|#define OMAP_UART1_BASE&t;&t;(unsigned char *)0xfffb0000
DECL|macro|OMAP_UART2_BASE
mdefine_line|#define OMAP_UART2_BASE&t;&t;(unsigned char *)0xfffb0800
DECL|macro|OMAP_UART3_BASE
mdefine_line|#define OMAP_UART3_BASE&t;&t;(unsigned char *)0xfffb9800
DECL|macro|OMAP_MAX_NR_PORTS
mdefine_line|#define OMAP_MAX_NR_PORTS&t;3
DECL|macro|PORT_OMAP
mdefine_line|#define PORT_OMAP&t;&t;16&t;/* Temporary */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|OMAP1510_BASE_BAUD
mdefine_line|#define OMAP1510_BASE_BAUD&t;(12000000/16)
DECL|macro|OMAP16XX_BASE_BAUD
mdefine_line|#define OMAP16XX_BASE_BAUD&t;(48000000/16)
DECL|macro|UART_SYSC
mdefine_line|#define UART_SYSC&t;&t;0x15
multiline_comment|/* OMAP FCR trigger  redefinitions */
DECL|macro|UART_FCR_R_TRIGGER_8
mdefine_line|#define UART_FCR_R_TRIGGER_8&t;0x00&t;/* Mask for receive trigger set at 8 */
DECL|macro|UART_FCR_R_TRIGGER_16
mdefine_line|#define UART_FCR_R_TRIGGER_16&t;0x40&t;/* Mask for receive trigger set at 16 */
DECL|macro|UART_FCR_R_TRIGGER_56
mdefine_line|#define UART_FCR_R_TRIGGER_56&t;0x80&t;/* Mask for receive trigger set at 56 */
DECL|macro|UART_FCR_R_TRIGGER_60
mdefine_line|#define UART_FCR_R_TRIGGER_60&t;0xC0&t;/* Mask for receive trigger set at 60 */
multiline_comment|/* There is an error in the description of the transmit trigger levels of&n;   OMAP5910 TRM from January 2003. The transmit trigger level 56 is not&n;   56 but 32, the transmit trigger level 60 is not 60 but 56!&n;   Additionally, the descritption of these trigger levels is&n;   a little bit unclear. The trigger level define the number of EMPTY&n;   entries in the FIFO. Thus, if TRIGGER_8 is used, an interrupt is requested&n;   if 8 FIFO entries are empty (and 56 entries are still filled [the FIFO&n;   size is 64]). Or: If TRIGGER_56 is selected, everytime there are less than&n;   8 characters in the FIFO, an interrrupt is spawned. In other words: The&n;   trigger number is equal the number of characters which can be&n;   written without FIFO overrun */
DECL|macro|UART_FCR_T_TRIGGER_8
mdefine_line|#define UART_FCR_T_TRIGGER_8&t;0x00&t;/* Mask for transmit trigger set at 8 */
DECL|macro|UART_FCR_T_TRIGGER_16
mdefine_line|#define UART_FCR_T_TRIGGER_16&t;0x10&t;/* Mask for transmit trigger set at 16 */
DECL|macro|UART_FCR_T_TRIGGER_32
mdefine_line|#define UART_FCR_T_TRIGGER_32&t;0x20&t;/* Mask for transmit trigger set at 32 */
DECL|macro|UART_FCR_T_TRIGGER_56
mdefine_line|#define UART_FCR_T_TRIGGER_56&t;0x30&t;/* Mask for transmit trigger set at 56 */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD 0
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif&t;/* __ASM_ARCH_SERIAL_H */
eof
