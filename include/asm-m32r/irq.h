macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_M32R_IRQ_H
DECL|macro|_ASM_M32R_IRQ_H
mdefine_line|#define _ASM_M32R_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_PLAT_M32700UT_Alpha) || defined(CONFIG_PLAT_USRV)
multiline_comment|/*&n; * IRQ definitions for M32700UT&n; *  M32700 Chip: 64 interrupts&n; *  ICU of M32700UT-on-board PLD: 32 interrupts cascaded to INT1# chip pin&n; */
DECL|macro|M32700UT_NUM_CPU_IRQ
mdefine_line|#define&t;M32700UT_NUM_CPU_IRQ&t;(64)
DECL|macro|M32700UT_NUM_PLD_IRQ
mdefine_line|#define M32700UT_NUM_PLD_IRQ&t;(32)
DECL|macro|M32700UT_IRQ_BASE
mdefine_line|#define M32700UT_IRQ_BASE&t;0
DECL|macro|M32700UT_CPU_IRQ_BASE
mdefine_line|#define M32700UT_CPU_IRQ_BASE&t;M32700UT_IRQ_BASE
DECL|macro|M32700UT_PLD_IRQ_BASE
mdefine_line|#define M32700UT_PLD_IRQ_BASE&t;(M32700UT_CPU_IRQ_BASE + M32700UT_NUM_CPU_IRQ)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;(M32700UT_NUM_CPU_IRQ + M32700UT_NUM_PLD_IRQ)
macro_line|#elif defined(CONFIG_PLAT_M32700UT)
multiline_comment|/*&n; * IRQ definitions for M32700UT(Rev.C) + M32R-LAN&n; *  M32700 Chip: 64 interrupts&n; *  ICU of M32700UT-on-board PLD: 32 interrupts cascaded to INT1# chip pin&n; *  ICU of M32R-LCD-on-board PLD: 32 interrupts cascaded to INT2# chip pin&n; *  ICU of M32R-LAN-on-board PLD: 32 interrupts cascaded to INT0# chip pin&n; */
DECL|macro|M32700UT_NUM_CPU_IRQ
mdefine_line|#define M32700UT_NUM_CPU_IRQ&t;&t;(64)
DECL|macro|M32700UT_NUM_PLD_IRQ
mdefine_line|#define M32700UT_NUM_PLD_IRQ&t;&t;(32)
DECL|macro|M32700UT_NUM_LCD_PLD_IRQ
mdefine_line|#define M32700UT_NUM_LCD_PLD_IRQ&t;(32)
DECL|macro|M32700UT_NUM_LAN_PLD_IRQ
mdefine_line|#define M32700UT_NUM_LAN_PLD_IRQ&t;(32)
DECL|macro|M32700UT_IRQ_BASE
mdefine_line|#define M32700UT_IRQ_BASE&t;&t;0
DECL|macro|M32700UT_CPU_IRQ_BASE
mdefine_line|#define M32700UT_CPU_IRQ_BASE&t;&t;(M32700UT_IRQ_BASE)
DECL|macro|M32700UT_PLD_IRQ_BASE
mdefine_line|#define M32700UT_PLD_IRQ_BASE &bslash;&n;&t;(M32700UT_CPU_IRQ_BASE + M32700UT_NUM_CPU_IRQ)
DECL|macro|M32700UT_LCD_PLD_IRQ_BASE
mdefine_line|#define M32700UT_LCD_PLD_IRQ_BASE &bslash;&n;&t;(M32700UT_PLD_IRQ_BASE + M32700UT_NUM_PLD_IRQ)
DECL|macro|M32700UT_LAN_PLD_IRQ_BASE
mdefine_line|#define M32700UT_LAN_PLD_IRQ_BASE &bslash;&n;&t;(M32700UT_LCD_PLD_IRQ_BASE + M32700UT_NUM_LCD_PLD_IRQ)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS &bslash;&n;&t;(M32700UT_NUM_CPU_IRQ + M32700UT_NUM_PLD_IRQ &bslash;&n;&t;+ M32700UT_NUM_LCD_PLD_IRQ + M32700UT_NUM_LAN_PLD_IRQ)
macro_line|#elif defined(CONFIG_PLAT_OPSPUT)
multiline_comment|/*&n; * IRQ definitions for OPSPUT + M32R-LAN&n; *  OPSP Chip: 64 interrupts&n; *  ICU of OPSPUT-on-board PLD: 32 interrupts cascaded to INT1# chip pin&n; *  ICU of M32R-LCD-on-board PLD: 32 interrupts cascaded to INT2# chip pin&n; *  ICU of M32R-LAN-on-board PLD: 32 interrupts cascaded to INT0# chip pin&n; */
DECL|macro|OPSPUT_NUM_CPU_IRQ
mdefine_line|#define OPSPUT_NUM_CPU_IRQ&t;&t;(64)
DECL|macro|OPSPUT_NUM_PLD_IRQ
mdefine_line|#define OPSPUT_NUM_PLD_IRQ&t;&t;(32)
DECL|macro|OPSPUT_NUM_LCD_PLD_IRQ
mdefine_line|#define OPSPUT_NUM_LCD_PLD_IRQ&t;(32)
DECL|macro|OPSPUT_NUM_LAN_PLD_IRQ
mdefine_line|#define OPSPUT_NUM_LAN_PLD_IRQ&t;(32)
DECL|macro|OPSPUT_IRQ_BASE
mdefine_line|#define OPSPUT_IRQ_BASE&t;&t;0
DECL|macro|OPSPUT_CPU_IRQ_BASE
mdefine_line|#define OPSPUT_CPU_IRQ_BASE&t;&t;(OPSPUT_IRQ_BASE)
DECL|macro|OPSPUT_PLD_IRQ_BASE
mdefine_line|#define OPSPUT_PLD_IRQ_BASE &bslash;&n;&t;(OPSPUT_CPU_IRQ_BASE + OPSPUT_NUM_CPU_IRQ)
DECL|macro|OPSPUT_LCD_PLD_IRQ_BASE
mdefine_line|#define OPSPUT_LCD_PLD_IRQ_BASE &bslash;&n;&t;(OPSPUT_PLD_IRQ_BASE + OPSPUT_NUM_PLD_IRQ)
DECL|macro|OPSPUT_LAN_PLD_IRQ_BASE
mdefine_line|#define OPSPUT_LAN_PLD_IRQ_BASE &bslash;&n;&t;(OPSPUT_LCD_PLD_IRQ_BASE + OPSPUT_NUM_LCD_PLD_IRQ)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS &bslash;&n;&t;(OPSPUT_NUM_CPU_IRQ + OPSPUT_NUM_PLD_IRQ &bslash;&n;&t;+ OPSPUT_NUM_LCD_PLD_IRQ + OPSPUT_NUM_LAN_PLD_IRQ)
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;64
macro_line|#endif
DECL|macro|irq_canonicalize
mdefine_line|#define irq_canonicalize(irq)&t;(irq)
macro_line|#endif /* _ASM_M32R_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
