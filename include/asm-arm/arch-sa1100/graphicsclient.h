multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/graphicsclient.h&n; *&n; * Created 2000/06/11 by Nicolas Pitre &lt;nico@cam.org&gt;&n; * Modified 7/27/00 by Woojung &lt;whuh@applieddata.net&gt;&n; *&n; * This file contains the hardware specific definitions for the &n; * ADS GraphicsClient/ThinClient boards.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
DECL|macro|ADS_CPLD_BASE
mdefine_line|#define ADS_CPLD_BASE&t;&t;(0x10000000)
DECL|macro|ADS_p2v
mdefine_line|#define ADS_p2v( x )&t;&t;((x) - ADS_CPLD_BASE + 0xf0000000)
DECL|macro|ADS_v2p
mdefine_line|#define ADS_v2p( x )&t;&t;((x) - 0xf0000000 + ADS_CPLD_BASE)
multiline_comment|/* Parallel Port */
DECL|macro|_ADS_PPDR
mdefine_line|#define _ADS_PPDR&t;&t;0x10020000&t;/* parallel port data reg */
DECL|macro|_ADS_PPSR
mdefine_line|#define _ADS_PPSR&t;&t;0x10020004&t;/* parallel port status reg */
multiline_comment|/* PCMCIA */
DECL|macro|_ADS_CS_STATUS
mdefine_line|#define _ADS_CS_STATUS&t;&t;0x10040000&t;/* PCMCIA status reg */
DECL|macro|ADS_CS_ST_A_READY
mdefine_line|#define ADS_CS_ST_A_READY&t;(1 &lt;&lt; 0)&t;/* Socket A Card Ready */
DECL|macro|ADS_CS_ST_A_CD
mdefine_line|#define ADS_CS_ST_A_CD&t;&t;(1 &lt;&lt; 2)&t;/* Socket A Card Detect */
DECL|macro|ADS_CS_ST_A_BUSY
mdefine_line|#define ADS_CS_ST_A_BUSY&t;(1 &lt;&lt; 4)&t;/* Socket A Card Busy */
DECL|macro|ADS_CS_ST_A_STS
mdefine_line|#define ADS_CS_ST_A_STS&t;&t;(1 &lt;&lt; 6)&t;/* Socket A Card STS */
DECL|macro|_ADS_CS_PR
mdefine_line|#define _ADS_CS_PR&t;&t;0x10040004&t;/* PCMCIA Power/Reset */
DECL|macro|ADS_CS_PR_A_5V_POWER
mdefine_line|#define ADS_CS_PR_A_5V_POWER&t;(1 &lt;&lt; 0)&t;/* Socket A Enable 5V Power */
DECL|macro|ADS_CS_PR_A_3V_POWER
mdefine_line|#define ADS_CS_PR_A_3V_POWER&t;(1 &lt;&lt; 0)&t;/* Socket A Enable 3.3V Power */
DECL|macro|ADS_CS_PR_A_RESET
mdefine_line|#define ADS_CS_PR_A_RESET&t;&t;(1 &lt;&lt; 2)&t;/* Socket A Reset */
DECL|macro|_ADS_SW_SWITCHES
mdefine_line|#define _ADS_SW_SWITCHES&t;0x10060000&t;/* Software Switches */
multiline_comment|/* Extra IRQ Controller */
DECL|macro|_ADS_INT_ST1
mdefine_line|#define _ADS_INT_ST1&t;&t;0x10080000&t;/* IRQ Status #1 */
DECL|macro|_ADS_INT_ST2
mdefine_line|#define _ADS_INT_ST2&t;&t;0x10080004&t;/* IRQ Status #2 */
DECL|macro|_ADS_INT_EN1
mdefine_line|#define _ADS_INT_EN1&t;&t;0x10080008&t;/* IRQ Enable #1 */
DECL|macro|_ADS_INT_EN2
mdefine_line|#define _ADS_INT_EN2&t;&t;0x1008000c&t;/* IRQ Enable #2 */
multiline_comment|/* Discrete Controller (AVR:Atmel AT90LS8535) */
DECL|macro|_ADS_AVR_REG
mdefine_line|#define _ADS_AVR_REG&t;&t;0x10080018
multiline_comment|/* On-Board Ethernet */
DECL|macro|_ADS_ETHERNET
mdefine_line|#define _ADS_ETHERNET&t;&t;0x100e0000&t;/* Ethernet */
multiline_comment|/* Extra UARTs */
DECL|macro|_ADS_UARTA
mdefine_line|#define _ADS_UARTA&t;&t;0x10100000&t;/* UART A */
DECL|macro|_ADS_UARTB
mdefine_line|#define _ADS_UARTB&t;&t;0x10120000&t;/* UART B */
DECL|macro|_ADS_UARTC
mdefine_line|#define _ADS_UARTC&t;&t;0x10140000&t;/* UART C */
DECL|macro|_ADS_UARTD
mdefine_line|#define _ADS_UARTD&t;&t;0x10160000&t;/* UART D */
multiline_comment|/* LEDs */
DECL|macro|ADS_LED0
mdefine_line|#define ADS_LED0&t;GPIO_GPIO20&t;&t;/* on-board D22 */
DECL|macro|ADS_LED1
mdefine_line|#define ADS_LED1&t;GPIO_GPIO21&t;&t;/* on-board D21 */
DECL|macro|ADS_LED2
mdefine_line|#define ADS_LED2&t;GPIO_GPIO22&t;&t;/* on-board D20 */
DECL|macro|ADS_LED3
mdefine_line|#define ADS_LED3&t;GPIO_GPIO23&t;&t;/* external */
DECL|macro|ADS_LED4
mdefine_line|#define ADS_LED4&t;GPIO_GPIO24&t;&t;/* external */
DECL|macro|ADS_LED5
mdefine_line|#define ADS_LED5&t;GPIO_GPIO25&t;&t;/* external */
DECL|macro|ADS_LED6
mdefine_line|#define ADS_LED6&t;GPIO_GPIO26&t;&t;/* external */
DECL|macro|ADS_LED7
mdefine_line|#define ADS_LED7&t;GPIO_GPIO27&t;&t;/* external */
multiline_comment|/* Virtual register addresses */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|ADS_INT_ST1
mdefine_line|#define ADS_INT_ST1&t;(*((volatile u_char *) ADS_p2v(_ADS_INT_ST1)))
DECL|macro|ADS_INT_ST2
mdefine_line|#define ADS_INT_ST2&t;(*((volatile u_char *) ADS_p2v(_ADS_INT_ST2)))
DECL|macro|ADS_INT_EN1
mdefine_line|#define ADS_INT_EN1&t;(*((volatile u_char *) ADS_p2v(_ADS_INT_EN1)))
DECL|macro|ADS_INT_EN2
mdefine_line|#define ADS_INT_EN2&t;(*((volatile u_char *) ADS_p2v(_ADS_INT_EN2)))
DECL|macro|ADS_ETHERNET
mdefine_line|#define ADS_ETHERNET&t;((int) ADS_p2v(_ADS_ETHERNET))
DECL|macro|ADS_AVR_REG
mdefine_line|#define ADS_AVR_REG&t;(*((volatile u_char *) ADS_p2v(_ADS_AVR_REG)))
macro_line|#endif
eof
