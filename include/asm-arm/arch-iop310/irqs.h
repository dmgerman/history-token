multiline_comment|/*&n; * linux/include/asm-arm/arch-iop310/irqs.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * 06/13/01: Added 80310 on-chip interrupt sources &lt;dsaxena@mvista.com&gt;&n; *&n; */
multiline_comment|/*&n; * XS80200 specific IRQs&n; */
DECL|macro|IRQ_XS80200_BCU
mdefine_line|#define IRQ_XS80200_BCU&t;&t;0&t;/* Bus Control Unit */
DECL|macro|IRQ_XS80200_PMU
mdefine_line|#define IRQ_XS80200_PMU&t;&t;1&t;/* Performance Monitoring Unit */
DECL|macro|IRQ_XS80200_EXTIRQ
mdefine_line|#define IRQ_XS80200_EXTIRQ&t;2&t;/* external IRQ signal */
DECL|macro|IRQ_XS80200_EXTFIQ
mdefine_line|#define IRQ_XS80200_EXTFIQ&t;3&t;/* external IRQ signal */
DECL|macro|NR_XS80200_IRQS
mdefine_line|#define NR_XS80200_IRQS&t;&t;4
DECL|macro|XSCALE_PMU_IRQ
mdefine_line|#define XSCALE_PMU_IRQ&t;&t;IRQ_XS80200_PMU
multiline_comment|/*&n; * IOP80310 chipset interrupts&n; */
DECL|macro|IOP310_IRQ_OFS
mdefine_line|#define IOP310_IRQ_OFS&t;&t;NR_XS80200_IRQS
DECL|macro|IOP310_IRQ
mdefine_line|#define IOP310_IRQ(x)&t;&t;(IOP310_IRQ_OFS + (x))
multiline_comment|/*&n; * On FIQ1ISR register&n; */
DECL|macro|IRQ_IOP310_DMA0
mdefine_line|#define IRQ_IOP310_DMA0&t;&t;IOP310_IRQ(0)&t;/* DMA Channel 0 */
DECL|macro|IRQ_IOP310_DMA1
mdefine_line|#define IRQ_IOP310_DMA1&t;&t;IOP310_IRQ(1)&t;/* DMA Channel 1 */
DECL|macro|IRQ_IOP310_DMA2
mdefine_line|#define IRQ_IOP310_DMA2&t;&t;IOP310_IRQ(2)&t;/* DMA Channel 2 */
DECL|macro|IRQ_IOP310_PMON
mdefine_line|#define IRQ_IOP310_PMON&t;&t;IOP310_IRQ(3)&t;/* Bus performance Unit */
DECL|macro|IRQ_IOP310_AAU
mdefine_line|#define IRQ_IOP310_AAU&t;&t;IOP310_IRQ(4)&t;/* Application Accelator Unit */
multiline_comment|/*&n; * On FIQ2ISR register&n; */
DECL|macro|IRQ_IOP310_I2C
mdefine_line|#define IRQ_IOP310_I2C&t;&t;IOP310_IRQ(5)&t;/* I2C unit */
DECL|macro|IRQ_IOP310_MU
mdefine_line|#define IRQ_IOP310_MU&t;&t;IOP310_IRQ(6)&t;/* messaging unit */
DECL|macro|NR_IOP310_IRQS
mdefine_line|#define NR_IOP310_IRQS&t;&t;(IOP310_IRQ(6) + 1)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;NR_IOP310_IRQS
multiline_comment|/*&n; * Interrupts available on the Cyclone IQ80310 board&n; */
macro_line|#ifdef CONFIG_ARCH_IQ80310
DECL|macro|IQ80310_IRQ_OFS
mdefine_line|#define IQ80310_IRQ_OFS&t;&t;NR_IOP310_IRQS
DECL|macro|IQ80310_IRQ
mdefine_line|#define IQ80310_IRQ(y)&t;&t;((IQ80310_IRQ_OFS) + (y))
DECL|macro|IRQ_IQ80310_TIMER
mdefine_line|#define IRQ_IQ80310_TIMER&t;IQ80310_IRQ(0)&t;/* Timer Interrupt */
DECL|macro|IRQ_IQ80310_I82559
mdefine_line|#define IRQ_IQ80310_I82559&t;IQ80310_IRQ(1)&t;/* I82559 Ethernet Interrupt */
DECL|macro|IRQ_IQ80310_UART1
mdefine_line|#define IRQ_IQ80310_UART1&t;IQ80310_IRQ(2)&t;/* UART1 Interrupt */
DECL|macro|IRQ_IQ80310_UART2
mdefine_line|#define IRQ_IQ80310_UART2&t;IQ80310_IRQ(3)&t;/* UART2 Interrupt */
DECL|macro|IRQ_IQ80310_INTD
mdefine_line|#define IRQ_IQ80310_INTD&t;IQ80310_IRQ(4)&t;/* PCI INTD */
multiline_comment|/*&n; * ONLY AVAILABLE ON REV F OR NEWER BOARDS!&n; */
DECL|macro|IRQ_IQ80310_INTA
mdefine_line|#define&t;IRQ_IQ80310_INTA&t;IQ80310_IRQ(5)&t;/* PCI INTA */
DECL|macro|IRQ_IQ80310_INTB
mdefine_line|#define&t;IRQ_IQ80310_INTB&t;IQ80310_IRQ(6)&t;/* PCI INTB */
DECL|macro|IRQ_IQ80310_INTC
mdefine_line|#define&t;IRQ_IQ80310_INTC&t;IQ80310_IRQ(7)&t;/* PCI INTC */
DECL|macro|NR_IRQS
macro_line|#undef&t;NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(IQ80310_IRQ(7) + 1)
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_IQ80310
eof
