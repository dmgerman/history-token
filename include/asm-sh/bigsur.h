multiline_comment|/*&n; *&n; * Hitachi Big Sur Eval Board support&n; *&n; * Dustin McIntire (dustin@sensoria.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Derived from Hitachi SH7751 reference manual&n; * &n; */
macro_line|#ifndef _ASM_BIGSUR_H_
DECL|macro|_ASM_BIGSUR_H_
mdefine_line|#define _ASM_BIGSUR_H_
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hd64465.h&gt;
multiline_comment|/* 7751 Internal IRQ&squot;s used by external CPLD controller */
DECL|macro|BIGSUR_IRQ_LOW
mdefine_line|#define BIGSUR_IRQ_LOW&t;0
DECL|macro|BIGSUR_IRQ_NUM
mdefine_line|#define BIGSUR_IRQ_NUM  14         /* External CPLD level 1 IRQs */
DECL|macro|BIGSUR_IRQ_HIGH
mdefine_line|#define BIGSUR_IRQ_HIGH (BIGSUR_IRQ_LOW + BIGSUR_IRQ_NUM)
DECL|macro|BIGSUR_2NDLVL_IRQ_LOW
mdefine_line|#define BIGSUR_2NDLVL_IRQ_LOW   (HD64465_IRQ_BASE+HD64465_IRQ_NUM)  
DECL|macro|BIGSUR_2NDLVL_IRQ_NUM
mdefine_line|#define BIGSUR_2NDLVL_IRQ_NUM   32 /* Level 2 IRQs = 4 regs * 8 bits */
DECL|macro|BIGSUR_2NDLVL_IRQ_HIGH
mdefine_line|#define BIGSUR_2NDLVL_IRQ_HIGH  (BIGSUR_2NDLVL_IRQ_LOW + &bslash;&n;                                 BIGSUR_2NDLVL_IRQ_NUM)
multiline_comment|/* PCI interrupt base number (A_INTA-A_INTD) */
DECL|macro|BIGSUR_SH7751_PCI_IRQ_BASE
mdefine_line|#define BIGSUR_SH7751_PCI_IRQ_BASE  (BIGSUR_2NDLVL_IRQ_LOW+10)  
multiline_comment|/* CPLD registers and external chip addresses */
DECL|macro|BIGSUR_HD64464_ADDR
mdefine_line|#define BIGSUR_HD64464_ADDR&t;0xB2000000
DECL|macro|BIGSUR_DGDR
mdefine_line|#define BIGSUR_DGDR&t;0xB1FFFE00
DECL|macro|BIGSUR_BIDR
mdefine_line|#define BIGSUR_BIDR&t;0xB1FFFD00
DECL|macro|BIGSUR_CSLR
mdefine_line|#define BIGSUR_CSLR&t;0xB1FFFC00
DECL|macro|BIGSUR_SW1R
mdefine_line|#define BIGSUR_SW1R&t;0xB1FFFB00
DECL|macro|BIGSUR_DBGR
mdefine_line|#define BIGSUR_DBGR&t;0xB1FFFA00
DECL|macro|BIGSUR_BDTR
mdefine_line|#define BIGSUR_BDTR&t;0xB1FFF900
DECL|macro|BIGSUR_BDRR
mdefine_line|#define BIGSUR_BDRR&t;0xB1FFF800
DECL|macro|BIGSUR_PPR1
mdefine_line|#define BIGSUR_PPR1&t;0xB1FFF700
DECL|macro|BIGSUR_PPR2
mdefine_line|#define BIGSUR_PPR2&t;0xB1FFF600
DECL|macro|BIGSUR_IDE2
mdefine_line|#define BIGSUR_IDE2&t;0xB1FFF500
DECL|macro|BIGSUR_IDE3
mdefine_line|#define BIGSUR_IDE3&t;0xB1FFF400
DECL|macro|BIGSUR_SPCR
mdefine_line|#define BIGSUR_SPCR&t;0xB1FFF300
DECL|macro|BIGSUR_ETHR
mdefine_line|#define BIGSUR_ETHR&t;0xB1FE0000
DECL|macro|BIGSUR_PPDR
mdefine_line|#define BIGSUR_PPDR&t;0xB1FDFF00
DECL|macro|BIGSUR_ICTL
mdefine_line|#define BIGSUR_ICTL&t;0xB1FDFE00
DECL|macro|BIGSUR_ICMD
mdefine_line|#define BIGSUR_ICMD&t;0xB1FDFD00
DECL|macro|BIGSUR_DMA0
mdefine_line|#define BIGSUR_DMA0&t;0xB1FDFC00
DECL|macro|BIGSUR_DMA1
mdefine_line|#define BIGSUR_DMA1&t;0xB1FDFB00
DECL|macro|BIGSUR_IRQ0
mdefine_line|#define BIGSUR_IRQ0&t;0xB1FDFA00
DECL|macro|BIGSUR_IRQ1
mdefine_line|#define BIGSUR_IRQ1&t;0xB1FDF900
DECL|macro|BIGSUR_IRQ2
mdefine_line|#define BIGSUR_IRQ2&t;0xB1FDF800
DECL|macro|BIGSUR_IRQ3
mdefine_line|#define BIGSUR_IRQ3&t;0xB1FDF700
DECL|macro|BIGSUR_IMR0
mdefine_line|#define BIGSUR_IMR0&t;0xB1FDF600
DECL|macro|BIGSUR_IMR1
mdefine_line|#define BIGSUR_IMR1&t;0xB1FDF500
DECL|macro|BIGSUR_IMR2
mdefine_line|#define BIGSUR_IMR2&t;0xB1FDF400
DECL|macro|BIGSUR_IMR3
mdefine_line|#define BIGSUR_IMR3&t;0xB1FDF300
DECL|macro|BIGSUR_IRLMR0
mdefine_line|#define BIGSUR_IRLMR0&t;0xB1FDF200
DECL|macro|BIGSUR_IRLMR1
mdefine_line|#define BIGSUR_IRLMR1&t;0xB1FDF100
DECL|macro|BIGSUR_V320USC_ADDR
mdefine_line|#define BIGSUR_V320USC_ADDR  0xB1000000
DECL|macro|BIGSUR_HD64465_ADDR
mdefine_line|#define BIGSUR_HD64465_ADDR  0xB0000000
DECL|macro|BIGSUR_INTERNAL_BASE
mdefine_line|#define BIGSUR_INTERNAL_BASE 0xB0000000
multiline_comment|/* SMC ethernet card parameters */
DECL|macro|BIGSUR_ETHER_IOPORT
mdefine_line|#define BIGSUR_ETHER_IOPORT&t;&t;0x220
multiline_comment|/* IDE register paramters */
DECL|macro|BIGSUR_IDECMD_IOPORT
mdefine_line|#define BIGSUR_IDECMD_IOPORT&t;0x1f0
DECL|macro|BIGSUR_IDECTL_IOPORT
mdefine_line|#define BIGSUR_IDECTL_IOPORT&t;0x1f8
multiline_comment|/* LED bit position in BIGSUR_CSLR */
DECL|macro|BIGSUR_LED
mdefine_line|#define BIGSUR_LED  (1&lt;&lt;4)
multiline_comment|/* PCI: default LOCAL memory window sizes (seen from PCI bus) */
DECL|macro|BIGSUR_LSR0_SIZE
mdefine_line|#define BIGSUR_LSR0_SIZE    (64*(1&lt;&lt;20)) 
singleline_comment|//64MB
DECL|macro|BIGSUR_LSR1_SIZE
mdefine_line|#define BIGSUR_LSR1_SIZE    (64*(1&lt;&lt;20)) 
singleline_comment|//64MB
macro_line|#endif /* _ASM_BIGSUR_H_ */
eof
