multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/flexanet.h&n; *&n; * Created 2001/05/04 by Jordi Colomer &lt;jco@ict.es&gt;&n; *&n; * This file contains the hardware specific definitions for FlexaNet&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* Board Control Register (virtual address) */
DECL|macro|BCR_PHYS
mdefine_line|#define BCR_PHYS  0x10000000
DECL|macro|BCR_VIRT
mdefine_line|#define BCR_VIRT  0xf0000000
DECL|macro|BCR
mdefine_line|#define BCR (*(volatile unsigned int *)(BCR_VIRT))
multiline_comment|/* Power-up value */
DECL|macro|BCR_POWERUP
mdefine_line|#define BCR_POWERUP&t;0x00000000
multiline_comment|/* Mandatory bits */
DECL|macro|BCR_LED_GREEN
mdefine_line|#define BCR_LED_GREEN&t;(1&lt;&lt;0)&t;/* General-purpose green LED (1 = on) */
DECL|macro|BCR_GUI_NRST
mdefine_line|#define BCR_GUI_NRST&t;(1&lt;&lt;4)&t;/* GUI board reset (0 = reset) */
multiline_comment|/* Board Status Register (virtual address) */
DECL|macro|BSR_BASE
mdefine_line|#define BSR_BASE  BCR_BASE
DECL|macro|BSR
mdefine_line|#define BSR (*(volatile unsigned int *)(BSR_BASE))
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|BCR_value
suffix:semicolon
multiline_comment|/* Image of the BCR */
DECL|macro|BCR_set
mdefine_line|#define BCR_set( x )&t;BCR = (BCR_value |= (x))
DECL|macro|BCR_clear
mdefine_line|#define BCR_clear( x )&t;BCR = (BCR_value &amp;= ~(x))
macro_line|#endif
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|GPIO_GUI_IRQ
mdefine_line|#define GPIO_GUI_IRQ&t;&t;GPIO_GPIO (23)&t;/* IRQ from GUI board (i.e., UCB1300) */
DECL|macro|GPIO_ETH_IRQ
mdefine_line|#define GPIO_ETH_IRQ&t;&t;GPIO_GPIO (24)&t;/* IRQ from Ethernet controller */
DECL|macro|GPIO_LED_RED
mdefine_line|#define GPIO_LED_RED&t;&t;GPIO_GPIO (26)&t;/* General-purpose red LED */
multiline_comment|/* IRQ sources from GPIOs */
DECL|macro|IRQ_GPIO_GUI
mdefine_line|#define IRQ_GPIO_GUI&t;&t;IRQ_GPIO23
DECL|macro|IRQ_GPIO_ETH
mdefine_line|#define IRQ_GPIO_ETH&t;&t;IRQ_GPIO24
multiline_comment|/* On-Board Ethernet */
DECL|macro|_FHH_ETH_IOBASE
mdefine_line|#define _FHH_ETH_IOBASE&t;&t;0x18000000&t;/* I/O base (physical addr) */
DECL|macro|_FHH_ETH_MMBASE
mdefine_line|#define _FHH_ETH_MMBASE&t;&t;0x18800000&t;/* Attribute-memory base */
DECL|macro|FHH_ETH_SIZE
mdefine_line|#define FHH_ETH_SIZE&t;&t;0x01000000&t;/* total size */
DECL|macro|FHH_ETH_VIRT
mdefine_line|#define FHH_ETH_VIRT&t;&t;0xF1000000&t;/* Ethernet virtual address */
DECL|macro|FHH_ETH_p2v
mdefine_line|#define FHH_ETH_p2v( x )&t;((x) - _FHH_ETH_IOBASE + FHH_ETH_VIRT)
DECL|macro|FHH_ETH_v2p
mdefine_line|#define FHH_ETH_v2p( x )&t;((x) - FHH_ETH_VIRT + _FHH_ETH_IOBASE)
DECL|macro|FHH_ETH_IOBASE
mdefine_line|#define FHH_ETH_IOBASE&t;&t;FHH_ETH_p2v(_FHH_ETH_IOBASE) /* Virtual base addr */
DECL|macro|FHH_ETH_MMBASE
mdefine_line|#define FHH_ETH_MMBASE&t;&t;FHH_ETH_p2v(_FHH_ETH_MMBASE)
multiline_comment|/* Types of GUI */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|GUI_type
suffix:semicolon
macro_line|#endif
DECL|macro|FHH_GUI_ERROR
mdefine_line|#define FHH_GUI_ERROR&t;&t;0xFFFFFFFF
DECL|macro|FHH_GUI_NONE
mdefine_line|#define FHH_GUI_NONE&t;&t;0x0000000F
DECL|macro|FHH_GUI_TYPE_0
mdefine_line|#define FHH_GUI_TYPE_0&t;&t;0
DECL|macro|FHH_GUI_TYPE_1
mdefine_line|#define FHH_GUI_TYPE_1&t;&t;1
DECL|macro|FHH_GUI_TYPE_2
mdefine_line|#define FHH_GUI_TYPE_2&t;&t;2
eof
