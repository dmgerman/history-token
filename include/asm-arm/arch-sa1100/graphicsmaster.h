multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/graphicsmaster.h&n; *&n; * Created 2000/12/18 by Woojung Huh &lt;whuh@applieddata.net&gt;&n; *&n; * This file comes from graphicsclient.h of Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware specific definitions for the&n; * ADS GraphicsMaster&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
DECL|macro|ADS_CPLD_BASE
mdefine_line|#define ADS_CPLD_BASE&t;&t;(0x10000000)
DECL|macro|ADS_p2v
mdefine_line|#define ADS_p2v( x )&t;&t;((x) - ADS_CPLD_BASE + 0xf0000000)
DECL|macro|ADS_v2p
mdefine_line|#define ADS_v2p( x )&t;&t;((x) - 0xf0000000 + ADS_CPLD_BASE)
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
DECL|macro|_ADS_DCR
mdefine_line|#define _ADS_DCR&t;&t;&t;0x10080018&t;/* Discrete Control Reg */
multiline_comment|/* Discrete Controller (AVR:Atmel AT90LS8535) */
DECL|macro|_ADS_AVR_REG
mdefine_line|#define _ADS_AVR_REG&t;&t;0x10080018
multiline_comment|/* On-Board Ethernet */
DECL|macro|_ADS_ETHERNET
mdefine_line|#define _ADS_ETHERNET&t;&t;0x100e0000&t;/* Ethernet */
multiline_comment|/* On-Board Quad UART 16C554 */
DECL|macro|ADS_QUAD_UART1
mdefine_line|#define&t;ADS_QUAD_UART1&t;&t;0x10100000
DECL|macro|ADS_QUAD_UART2
mdefine_line|#define&t;ADS_QUAD_UART2&t;&t;0x10120000
DECL|macro|ADS_QUAD_UART3
mdefine_line|#define&t;ADS_QUAD_UART3&t;&t;0x10140000
DECL|macro|ADS_QUAD_UART4
mdefine_line|#define&t;ADS_QUAD_UART4&t;&t;0x10160000
multiline_comment|/* LEDs */
DECL|macro|ADS_LED0
mdefine_line|#define ADS_LED0&t;GPIO_GPIO20&t;&t;/* on-board Green */
DECL|macro|ADS_LED1
mdefine_line|#define ADS_LED1&t;GPIO_GPIO25&t;&t;/* on-board Yellow */
DECL|macro|ADS_LED2
mdefine_line|#define ADS_LED2&t;GPIO_GPIO26&t;&t;/* on-board Red */
multiline_comment|/* DCR */
DECL|macro|DCR_AVR_RESET
mdefine_line|#define DCR_AVR_RESET&t;&t;0x01
DECL|macro|DCR_SA1111_RESET
mdefine_line|#define DCR_SA1111_RESET&t;0x02
DECL|macro|DCR_BACKLITE_ON
mdefine_line|#define&t;DCR_BACKLITE_ON&t;&t;0x04
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
DECL|macro|ADS_DCR
mdefine_line|#define ADS_DCR&t;&t;(*((volatile u_char *) ADS_p2v(_ADS_DCR)))
macro_line|#endif
DECL|macro|SA1111_BASE
mdefine_line|#define&t;SA1111_BASE&t;(0x18000000)
macro_line|#include &quot;SA-1111.h&quot;
eof
