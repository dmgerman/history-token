multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/irqs.h&n; *&n; * Copyright (C) 2000 Jungjun Kim&n; *           (C) 2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *           (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *&n; */
macro_line|#ifndef __ASM_ARCH_IRQS_H
DECL|macro|__ASM_ARCH_IRQS_H
mdefine_line|#define __ASM_ARCH_IRQS_H
macro_line|#if defined (CONFIG_CPU_H7201)
DECL|macro|IRQ_PMU
mdefine_line|#define IRQ_PMU&t;&t;0&t;&t;/* 0x000001 */
DECL|macro|IRQ_DMA
mdefine_line|#define IRQ_DMA&t;&t;1 &t;&t;/* 0x000002 */
DECL|macro|IRQ_LCD
mdefine_line|#define IRQ_LCD&t;&t;2&t;&t;/* 0x000004 */
DECL|macro|IRQ_VGA
mdefine_line|#define IRQ_VGA&t;&t;3 &t;&t;/* 0x000008 */
DECL|macro|IRQ_PCMCIA1
mdefine_line|#define IRQ_PCMCIA1 &t;4 &t;&t;/* 0x000010 */
DECL|macro|IRQ_PCMCIA2
mdefine_line|#define IRQ_PCMCIA2 &t;5 &t;&t;/* 0x000020 */
DECL|macro|IRQ_AFE
mdefine_line|#define IRQ_AFE&t;&t;6 &t;&t;/* 0x000040 */
DECL|macro|IRQ_AIC
mdefine_line|#define IRQ_AIC&t;&t;7 &t;&t;/* 0x000080 */
DECL|macro|IRQ_KEYBOARD
mdefine_line|#define IRQ_KEYBOARD &t;8 &t;&t;/* 0x000100 */
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0&t;9 &t;&t;/* 0x000200 */
DECL|macro|IRQ_RTC
mdefine_line|#define IRQ_RTC&t;&t;10&t;&t;/* 0x000400 */
DECL|macro|IRQ_SOUND
mdefine_line|#define IRQ_SOUND&t;11&t;&t;/* 0x000800 */
DECL|macro|IRQ_USB
mdefine_line|#define IRQ_USB&t;&t;12&t;&t;/* 0x001000 */
DECL|macro|IRQ_IrDA
mdefine_line|#define IRQ_IrDA &t;13&t;&t;/* 0x002000 */
DECL|macro|IRQ_UART0
mdefine_line|#define IRQ_UART0&t;14&t;&t;/* 0x004000 */
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1&t;15&t;&t;/* 0x008000 */
DECL|macro|IRQ_SPI
mdefine_line|#define IRQ_SPI&t;&t;16&t;&t;/* 0x010000 */
DECL|macro|IRQ_GPIOA
mdefine_line|#define IRQ_GPIOA &t;17&t;&t;/* 0x020000 */
DECL|macro|IRQ_GPIOB
mdefine_line|#define IRQ_GPIOB&t;18&t;&t;/* 0x040000 */
DECL|macro|IRQ_GPIOC
mdefine_line|#define IRQ_GPIOC&t;19&t;&t;/* 0x080000 */
DECL|macro|IRQ_GPIOD
mdefine_line|#define IRQ_GPIOD&t;20&t;&t;/* 0x100000 */
DECL|macro|IRQ_CommRX
mdefine_line|#define IRQ_CommRX&t;21&t;&t;/* 0x200000 */
DECL|macro|IRQ_CommTX
mdefine_line|#define IRQ_CommTX&t;22&t;&t;/* 0x400000 */
DECL|macro|IRQ_Soft
mdefine_line|#define IRQ_Soft&t;23&t;&t;/* 0x800000 */
DECL|macro|NR_GLBL_IRQS
mdefine_line|#define NR_GLBL_IRQS&t;24
DECL|macro|IRQ_CHAINED_GPIOA
mdefine_line|#define IRQ_CHAINED_GPIOA(x)  (NR_GLBL_IRQS + x)
DECL|macro|IRQ_CHAINED_GPIOB
mdefine_line|#define IRQ_CHAINED_GPIOB(x)  (IRQ_CHAINED_GPIOA(32) + x)
DECL|macro|IRQ_CHAINED_GPIOC
mdefine_line|#define IRQ_CHAINED_GPIOC(x)  (IRQ_CHAINED_GPIOB(32) + x)
DECL|macro|IRQ_CHAINED_GPIOD
mdefine_line|#define IRQ_CHAINED_GPIOD(x)  (IRQ_CHAINED_GPIOC(32) + x)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS               IRQ_CHAINED_GPIOD(32)
multiline_comment|/* Enable mask for multiplexed interrupts */
DECL|macro|IRQ_ENA_MUX
mdefine_line|#define IRQ_ENA_MUX&t;(1&lt;&lt;IRQ_GPIOA) | (1&lt;&lt;IRQ_GPIOB) &bslash;&n;&t;&t;&t;| (1&lt;&lt;IRQ_GPIOC) | (1&lt;&lt;IRQ_GPIOD)
macro_line|#elif defined (CONFIG_CPU_H7202)
DECL|macro|IRQ_PMU
mdefine_line|#define IRQ_PMU&t;&t;0&t;&t;/* 0x00000001 */
DECL|macro|IRQ_DMA
mdefine_line|#define IRQ_DMA&t;&t;1&t;&t;/* 0x00000002 */
DECL|macro|IRQ_LCD
mdefine_line|#define IRQ_LCD&t;&t;2&t;&t;/* 0x00000004 */
DECL|macro|IRQ_SOUND
mdefine_line|#define IRQ_SOUND&t;3&t;&t;/* 0x00000008 */
DECL|macro|IRQ_I2S
mdefine_line|#define IRQ_I2S&t;&t;4&t;&t;/* 0x00000010 */
DECL|macro|IRQ_USB
mdefine_line|#define IRQ_USB &t;5&t;&t;/* 0x00000020 */
DECL|macro|IRQ_MMC
mdefine_line|#define IRQ_MMC &t;6&t;&t;/* 0x00000040 */
DECL|macro|IRQ_RTC
mdefine_line|#define IRQ_RTC &t;7&t;&t;/* 0x00000080 */
DECL|macro|IRQ_UART0
mdefine_line|#define IRQ_UART0 &t;8&t;&t;/* 0x00000100 */
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1 &t;9&t;&t;/* 0x00000200 */
DECL|macro|IRQ_UART2
mdefine_line|#define IRQ_UART2 &t;10&t;&t;/* 0x00000400 */
DECL|macro|IRQ_UART3
mdefine_line|#define IRQ_UART3 &t;11&t;&t;/* 0x00000800 */
DECL|macro|IRQ_KBD
mdefine_line|#define IRQ_KBD &t;12&t;&t;/* 0x00001000 */
DECL|macro|IRQ_PS2
mdefine_line|#define IRQ_PS2 &t;13&t;&t;/* 0x00002000 */
DECL|macro|IRQ_AIC
mdefine_line|#define IRQ_AIC &t;14&t;&t;/* 0x00004000 */
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0 &t;15&t;&t;/* 0x00008000 */
DECL|macro|IRQ_TIMERX
mdefine_line|#define IRQ_TIMERX &t;16&t;&t;/* 0x00010000 */
DECL|macro|IRQ_WDT
mdefine_line|#define IRQ_WDT &t;17&t;&t;/* 0x00020000 */
DECL|macro|IRQ_CAN0
mdefine_line|#define IRQ_CAN0 &t;18&t;&t;/* 0x00040000 */
DECL|macro|IRQ_CAN1
mdefine_line|#define IRQ_CAN1 &t;19&t;&t;/* 0x00080000 */
DECL|macro|IRQ_EXT0
mdefine_line|#define IRQ_EXT0 &t;20&t;&t;/* 0x00100000 */
DECL|macro|IRQ_EXT1
mdefine_line|#define IRQ_EXT1 &t;21&t;&t;/* 0x00200000 */
DECL|macro|IRQ_GPIOA
mdefine_line|#define IRQ_GPIOA &t;22&t;&t;/* 0x00400000 */
DECL|macro|IRQ_GPIOB
mdefine_line|#define IRQ_GPIOB &t;23&t;&t;/* 0x00800000 */
DECL|macro|IRQ_GPIOC
mdefine_line|#define IRQ_GPIOC &t;24&t;&t;/* 0x01000000 */
DECL|macro|IRQ_GPIOD
mdefine_line|#define IRQ_GPIOD &t;25&t;&t;/* 0x02000000 */
DECL|macro|IRQ_GPIOE
mdefine_line|#define IRQ_GPIOE &t;26&t;&t;/* 0x04000000 */
DECL|macro|IRQ_COMMRX
mdefine_line|#define IRQ_COMMRX &t;27&t;&t;/* 0x08000000 */
DECL|macro|IRQ_COMMTX
mdefine_line|#define IRQ_COMMTX &t;28&t;&t;/* 0x10000000 */
DECL|macro|IRQ_SMC
mdefine_line|#define IRQ_SMC &t;29&t;&t;/* 0x20000000 */
DECL|macro|IRQ_Soft
mdefine_line|#define IRQ_Soft &t;30&t;&t;/* 0x40000000 */
DECL|macro|IRQ_RESERVED1
mdefine_line|#define IRQ_RESERVED1 &t;31&t;&t;/* 0x80000000 */
DECL|macro|NR_GLBL_IRQS
mdefine_line|#define NR_GLBL_IRQS&t;32
DECL|macro|NR_TIMERX_IRQS
mdefine_line|#define NR_TIMERX_IRQS&t;3
DECL|macro|IRQ_CHAINED_GPIOA
mdefine_line|#define IRQ_CHAINED_GPIOA(x)  (NR_GLBL_IRQS + x)
DECL|macro|IRQ_CHAINED_GPIOB
mdefine_line|#define IRQ_CHAINED_GPIOB(x)  (IRQ_CHAINED_GPIOA(32) + x)
DECL|macro|IRQ_CHAINED_GPIOC
mdefine_line|#define IRQ_CHAINED_GPIOC(x)  (IRQ_CHAINED_GPIOB(32) + x)
DECL|macro|IRQ_CHAINED_GPIOD
mdefine_line|#define IRQ_CHAINED_GPIOD(x)  (IRQ_CHAINED_GPIOC(32) + x)
DECL|macro|IRQ_CHAINED_GPIOE
mdefine_line|#define IRQ_CHAINED_GPIOE(x)  (IRQ_CHAINED_GPIOD(32) + x)
DECL|macro|IRQ_CHAINED_TIMERX
mdefine_line|#define IRQ_CHAINED_TIMERX(x) (IRQ_CHAINED_GPIOE(32) + x)
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1            (IRQ_CHAINED_TIMERX(0))
DECL|macro|IRQ_TIMER2
mdefine_line|#define IRQ_TIMER2            (IRQ_CHAINED_TIMERX(1))
DECL|macro|IRQ_TIMER64B
mdefine_line|#define IRQ_TIMER64B          (IRQ_CHAINED_TIMERX(2))
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(IRQ_CHAINED_TIMERX(NR_TIMERX_IRQS))
multiline_comment|/* Enable mask for multiplexed interrupts */
DECL|macro|IRQ_ENA_MUX
mdefine_line|#define IRQ_ENA_MUX&t;(1&lt;&lt;IRQ_TIMERX) | (1&lt;&lt;IRQ_GPIOA) | (1&lt;&lt;IRQ_GPIOB) | &bslash;&n;&t;&t;&t;(1&lt;&lt;IRQ_GPIOC) &t;| (1&lt;&lt;IRQ_GPIOD) | (1&lt;&lt;IRQ_GPIOE) | &bslash;&n;&t;&t;&t;(1&lt;&lt;IRQ_TIMERX)
macro_line|#else
macro_line|#error cpu definition mismatch
macro_line|#endif
multiline_comment|/* decode irq number to register number */
DECL|macro|IRQ_TO_REGNO
mdefine_line|#define IRQ_TO_REGNO(irq) ((irq - NR_GLBL_IRQS) &gt;&gt; 5)
DECL|macro|IRQ_TO_BIT
mdefine_line|#define IRQ_TO_BIT(irq) (1 &lt;&lt; ((irq - NR_GLBL_IRQS) % 32))
macro_line|#endif
eof
