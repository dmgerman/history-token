multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/serial.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; * serial definitions&n; *&n; * NOTE: There is an error in the description of the transmit trigger levels of&n; * OMAP5910 TRM from January 2003. The transmit trigger level 56 is not 56 but&n; * 32, the transmit trigger level 60 is not 60 but 56!&n; * Additionally, the description of these trigger levels is a little bit&n; * unclear. The trigger level define the number of EMPTY entries in the FIFO.&n; * Thus, if TRIGGER_8 is used, an interrupt is requested if 8 FIFO entries are&n; * empty (and 56 entries are still filled [the FIFO size is 64]). Or: If&n; * TRIGGER_56 is selected, everytime there are less than 8 characters in the&n; * FIFO, an interrrupt is spawned. In other words: The trigger number is equal&n; * the number of characters which can be written without FIFO overrun.&n; */
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
DECL|macro|is_omap_port
mdefine_line|#define is_omap_port(p)&t;({int __ret = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (p == (char*)IO_ADDRESS(OMAP_UART1_BASE) ||&t;&bslash;&n;&t;&t;&t;    p == (char*)IO_ADDRESS(OMAP_UART2_BASE) ||&t;&bslash;&n;&t;&t;&t;    p == (char*)IO_ADDRESS(OMAP_UART3_BASE))&t;&bslash;&n;&t;&t;&t;&t;__ret = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;})
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|OMAP1510_BASE_BAUD
mdefine_line|#define OMAP1510_BASE_BAUD&t;(12000000/16)
DECL|macro|OMAP16XX_BASE_BAUD
mdefine_line|#define OMAP16XX_BASE_BAUD&t;(48000000/16)
DECL|macro|UART_SYSC
mdefine_line|#define UART_SYSC&t;&t;0x15
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD 0
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif&t;/* __ASM_ARCH_SERIAL_H */
eof
