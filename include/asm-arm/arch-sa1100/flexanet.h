multiline_comment|/*&n; * include/asm-arm/arch-sa1100/flexanet.h&n; *&n; * Created 2001/05/04 by Jordi Colomer &lt;jco@ict.es&gt;&n; *&n; * This file contains the hardware specific definitions for FlexaNet&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* Board Control Register (virtual address) */
DECL|macro|FHH_BCR_PHYS
mdefine_line|#define FHH_BCR_PHYS  0x10000000
DECL|macro|FHH_BCR_VIRT
mdefine_line|#define FHH_BCR_VIRT  0xf0000000
DECL|macro|FHH_BCR
mdefine_line|#define FHH_BCR (*(volatile unsigned int *)(FHH_BCR_VIRT))
multiline_comment|/* Power-up value */
DECL|macro|FHH_BCR_POWERUP
mdefine_line|#define FHH_BCR_POWERUP&t;0x00000000
multiline_comment|/* Mandatory bits */
DECL|macro|FHH_BCR_LED_GREEN
mdefine_line|#define FHH_BCR_LED_GREEN  (1&lt;&lt;0)  /* General-purpose green LED (1 = on) */
DECL|macro|FHH_BCR_SPARE_1
mdefine_line|#define FHH_BCR_SPARE_1    (1&lt;&lt;1)  /* Not defined */
DECL|macro|FHH_BCR_CF1_RST
mdefine_line|#define FHH_BCR_CF1_RST    (1&lt;&lt;2)  /* Compact Flash Slot #1 Reset (1 = reset) */
DECL|macro|FHH_BCR_CF2_RST
mdefine_line|#define FHH_BCR_CF2_RST    (1&lt;&lt;3)  /* Compact Flash Slot #2 Reset (1 = reset) */
DECL|macro|FHH_BCR_GUI_NRST
mdefine_line|#define FHH_BCR_GUI_NRST   (1&lt;&lt;4)  /* GUI board reset (0 = reset) */
DECL|macro|FHH_BCR_RTS1
mdefine_line|#define FHH_BCR_RTS1       (1&lt;&lt;5)  /* RS232 RTS for UART-1 */
DECL|macro|FHH_BCR_RTS3
mdefine_line|#define FHH_BCR_RTS3       (1&lt;&lt;6)  /* RS232 RTS for UART-3 */
DECL|macro|FHH_BCR_XCDBG0
mdefine_line|#define FHH_BCR_XCDBG0     (1&lt;&lt;7)  /* Not defined. Wired to XPLA3 for debug */
multiline_comment|/* BCR extension, only required by L3-bus in some audio codecs */
DECL|macro|FHH_BCR_L3MOD
mdefine_line|#define FHH_BCR_L3MOD      (1&lt;&lt;8)  /* L3-bus MODE signal */
DECL|macro|FHH_BCR_L3DAT
mdefine_line|#define FHH_BCR_L3DAT      (1&lt;&lt;9)  /* L3-bus DATA signal */
DECL|macro|FHH_BCR_L3CLK
mdefine_line|#define FHH_BCR_L3CLK      (1&lt;&lt;10) /* L3-bus CLK signal */
DECL|macro|FHH_BCR_SPARE_11
mdefine_line|#define FHH_BCR_SPARE_11   (1&lt;&lt;11) /* Not defined */
DECL|macro|FHH_BCR_SPARE_12
mdefine_line|#define FHH_BCR_SPARE_12   (1&lt;&lt;12) /* Not defined */
DECL|macro|FHH_BCR_SPARE_13
mdefine_line|#define FHH_BCR_SPARE_13   (1&lt;&lt;13) /* Not defined */
DECL|macro|FHH_BCR_SPARE_14
mdefine_line|#define FHH_BCR_SPARE_14   (1&lt;&lt;14) /* Not defined */
DECL|macro|FHH_BCR_SPARE_15
mdefine_line|#define FHH_BCR_SPARE_15   (1&lt;&lt;15) /* Not defined */
multiline_comment|/* Board Status Register (virtual address) */
DECL|macro|FHH_BSR_BASE
mdefine_line|#define FHH_BSR_BASE  FHH_BCR_VIRT
DECL|macro|FHH_BSR
mdefine_line|#define FHH_BSR (*(volatile unsigned int *)(FHH_BSR_BASE))
DECL|macro|FHH_BSR_CTS1
mdefine_line|#define FHH_BSR_CTS1       (1&lt;&lt;0)  /* RS232 CTS for UART-1 */
DECL|macro|FHH_BSR_CTS3
mdefine_line|#define FHH_BSR_CTS3       (1&lt;&lt;1)  /* RS232 CTS for UART-3 */
DECL|macro|FHH_BSR_DSR1
mdefine_line|#define FHH_BSR_DSR1       (1&lt;&lt;2)  /* RS232 DSR for UART-1 */
DECL|macro|FHH_BSR_DSR3
mdefine_line|#define FHH_BSR_DSR3       (1&lt;&lt;3)  /* RS232 DSR for UART-3 */
DECL|macro|FHH_BSR_ID0
mdefine_line|#define FHH_BSR_ID0        (1&lt;&lt;4)  /* Board identification */
DECL|macro|FHH_BSR_ID1
mdefine_line|#define FHH_BSR_ID1        (1&lt;&lt;5)
DECL|macro|FHH_BSR_CFG0
mdefine_line|#define FHH_BSR_CFG0       (1&lt;&lt;6)  /* Board configuration options */
DECL|macro|FHH_BSR_CFG1
mdefine_line|#define FHH_BSR_CFG1       (1&lt;&lt;7)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|flexanet_BCR
suffix:semicolon
multiline_comment|/* Image of the BCR */
DECL|macro|FLEXANET_BCR_set
mdefine_line|#define FLEXANET_BCR_set( x )    FHH_BCR = (flexanet_BCR |= (x))
DECL|macro|FLEXANET_BCR_clear
mdefine_line|#define FLEXANET_BCR_clear( x )  FHH_BCR = (flexanet_BCR &amp;= ~(x))
macro_line|#endif
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|GPIO_CF1_NCD
mdefine_line|#define GPIO_CF1_NCD       GPIO_GPIO (14)  /* Card Detect from CF slot #1 */
DECL|macro|GPIO_CF2_NCD
mdefine_line|#define GPIO_CF2_NCD       GPIO_GPIO (15)  /* Card Detect from CF slot #2 */
DECL|macro|GPIO_CF1_IRQ
mdefine_line|#define GPIO_CF1_IRQ       GPIO_GPIO (16)  /* IRQ from CF slot #1 */
DECL|macro|GPIO_CF2_IRQ
mdefine_line|#define GPIO_CF2_IRQ       GPIO_GPIO (17)  /* IRQ from CF slot #2 */
DECL|macro|GPIO_APP_IRQ
mdefine_line|#define GPIO_APP_IRQ       GPIO_GPIO (18)  /* Extra IRQ from application bus */
DECL|macro|GPIO_RADIO_REF
mdefine_line|#define GPIO_RADIO_REF     GPIO_GPIO (20)  /* Ref. clock for UART3 (Radio) */
DECL|macro|GPIO_CF1_BVD1
mdefine_line|#define GPIO_CF1_BVD1      GPIO_GPIO (21)  /* BVD1 from CF slot #1 */
DECL|macro|GPIO_CF2_BVD1
mdefine_line|#define GPIO_CF2_BVD1      GPIO_GPIO (22)  /* BVD1 from CF slot #2 */
DECL|macro|GPIO_GUI_IRQ
mdefine_line|#define GPIO_GUI_IRQ       GPIO_GPIO (23)  /* IRQ from GUI board (i.e., UCB1300) */
DECL|macro|GPIO_ETH_IRQ
mdefine_line|#define GPIO_ETH_IRQ       GPIO_GPIO (24)  /* IRQ from Ethernet controller */
DECL|macro|GPIO_INTIP_IRQ
mdefine_line|#define GPIO_INTIP_IRQ     GPIO_GPIO (25)  /* Measurement IRQ (INTIP) */
DECL|macro|GPIO_LED_RED
mdefine_line|#define GPIO_LED_RED       GPIO_GPIO (26)  /* General-purpose red LED */
multiline_comment|/* IRQ sources from GPIOs */
DECL|macro|IRQ_GPIO_CF1_CD
mdefine_line|#define IRQ_GPIO_CF1_CD    IRQ_GPIO14
DECL|macro|IRQ_GPIO_CF2_CD
mdefine_line|#define IRQ_GPIO_CF2_CD    IRQ_GPIO15
DECL|macro|IRQ_GPIO_CF1_IRQ
mdefine_line|#define IRQ_GPIO_CF1_IRQ   IRQ_GPIO16
DECL|macro|IRQ_GPIO_CF2_IRQ
mdefine_line|#define IRQ_GPIO_CF2_IRQ   IRQ_GPIO17
DECL|macro|IRQ_GPIO_APP
mdefine_line|#define IRQ_GPIO_APP       IRQ_GPIO18
DECL|macro|IRQ_GPIO_CF1_BVD1
mdefine_line|#define IRQ_GPIO_CF1_BVD1  IRQ_GPIO21
DECL|macro|IRQ_GPIO_CF2_BVD1
mdefine_line|#define IRQ_GPIO_CF2_BVD1  IRQ_GPIO22
DECL|macro|IRQ_GPIO_GUI
mdefine_line|#define IRQ_GPIO_GUI       IRQ_GPIO23
DECL|macro|IRQ_GPIO_ETH
mdefine_line|#define IRQ_GPIO_ETH       IRQ_GPIO24
DECL|macro|IRQ_GPIO_INTIP
mdefine_line|#define IRQ_GPIO_INTIP     IRQ_GPIO25
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
eof
