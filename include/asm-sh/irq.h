macro_line|#ifndef __ASM_SH_IRQ_H
DECL|macro|__ASM_SH_IRQ_H
mdefine_line|#define __ASM_SH_IRQ_H
multiline_comment|/*&n; *&n; * linux/include/asm-sh/irq.h&n; *&n; * Copyright (C) 1999  Niibe Yutaka &amp; Takeshi Yaegashi&n; * Copyright (C) 2000  Kazumoto Kojima&n; * Copyright (C) 2003  Paul Mundt&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;&t;&t;/* for pt_regs */
macro_line|#if defined(CONFIG_CPU_SH3)
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA  &t;0xfffffee2UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB  &t;0xfffffee4UL
macro_line|#elif defined(CONFIG_CPU_SH4)
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA&t;0xffd00004UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB&t;0xffd00008UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC&t;0xffd0000cUL
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD&t;0xffd00010UL
macro_line|#endif
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;16
DECL|macro|TIMER_IPR_ADDR
mdefine_line|#define TIMER_IPR_ADDR&t;INTC_IPRA
DECL|macro|TIMER_IPR_POS
mdefine_line|#define TIMER_IPR_POS&t; 3
DECL|macro|TIMER_PRIORITY
mdefine_line|#define TIMER_PRIORITY&t; 2
DECL|macro|TIMER1_IRQ
mdefine_line|#define TIMER1_IRQ&t;17
DECL|macro|TIMER1_IPR_ADDR
mdefine_line|#define TIMER1_IPR_ADDR&t;INTC_IPRA
DECL|macro|TIMER1_IPR_POS
mdefine_line|#define TIMER1_IPR_POS&t; 2
DECL|macro|TIMER1_PRIORITY
mdefine_line|#define TIMER1_PRIORITY&t; 4
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;22
DECL|macro|RTC_IPR_ADDR
mdefine_line|#define RTC_IPR_ADDR&t;INTC_IPRA
DECL|macro|RTC_IPR_POS
mdefine_line|#define RTC_IPR_POS&t; 0
DECL|macro|RTC_PRIORITY
mdefine_line|#define RTC_PRIORITY&t;TIMER_PRIORITY
macro_line|#if defined(CONFIG_CPU_SH3)
DECL|macro|DMTE0_IRQ
mdefine_line|#define DMTE0_IRQ&t;48
DECL|macro|DMTE1_IRQ
mdefine_line|#define DMTE1_IRQ&t;49
DECL|macro|DMTE2_IRQ
mdefine_line|#define DMTE2_IRQ&t;50
DECL|macro|DMTE3_IRQ
mdefine_line|#define DMTE3_IRQ&t;51
DECL|macro|DMA_IPR_ADDR
mdefine_line|#define DMA_IPR_ADDR&t;INTC_IPRE
DECL|macro|DMA_IPR_POS
mdefine_line|#define DMA_IPR_POS&t;3
DECL|macro|DMA_PRIORITY
mdefine_line|#define DMA_PRIORITY&t;7
macro_line|#elif defined(CONFIG_CPU_SH4)
DECL|macro|DMTE0_IRQ
mdefine_line|#define DMTE0_IRQ&t;34
DECL|macro|DMTE1_IRQ
mdefine_line|#define DMTE1_IRQ&t;35
DECL|macro|DMTE2_IRQ
mdefine_line|#define DMTE2_IRQ&t;36
DECL|macro|DMTE3_IRQ
mdefine_line|#define DMTE3_IRQ&t;37
DECL|macro|DMTE4_IRQ
mdefine_line|#define DMTE4_IRQ&t;44&t;/* 7751R only */
DECL|macro|DMTE5_IRQ
mdefine_line|#define DMTE5_IRQ&t;45&t;/* 7751R only */
DECL|macro|DMTE6_IRQ
mdefine_line|#define DMTE6_IRQ&t;46&t;/* 7751R only */
DECL|macro|DMTE7_IRQ
mdefine_line|#define DMTE7_IRQ&t;47&t;/* 7751R only */
DECL|macro|DMAE_IRQ
mdefine_line|#define DMAE_IRQ&t;38
DECL|macro|DMA_IPR_ADDR
mdefine_line|#define DMA_IPR_ADDR&t;INTC_IPRC
DECL|macro|DMA_IPR_POS
mdefine_line|#define DMA_IPR_POS&t;2
DECL|macro|DMA_PRIORITY
mdefine_line|#define DMA_PRIORITY&t;7
macro_line|#endif
macro_line|#if defined (CONFIG_CPU_SUBTYPE_SH7707) || defined (CONFIG_CPU_SUBTYPE_SH7708) || &bslash;&n;    defined (CONFIG_CPU_SUBTYPE_SH7709) || defined (CONFIG_CPU_SUBTYPE_SH7750) || &bslash;&n;    defined (CONFIG_CPU_SUBTYPE_SH7751)
DECL|macro|SCI_ERI_IRQ
mdefine_line|#define SCI_ERI_IRQ&t;23
DECL|macro|SCI_RXI_IRQ
mdefine_line|#define SCI_RXI_IRQ&t;24
DECL|macro|SCI_TXI_IRQ
mdefine_line|#define SCI_TXI_IRQ&t;25
DECL|macro|SCI_IPR_ADDR
mdefine_line|#define SCI_IPR_ADDR&t;INTC_IPRB
DECL|macro|SCI_IPR_POS
mdefine_line|#define SCI_IPR_POS&t;1
DECL|macro|SCI_PRIORITY
mdefine_line|#define SCI_PRIORITY&t;3
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7707) || defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|SCIF_ERI_IRQ
mdefine_line|#define SCIF_ERI_IRQ&t;56
DECL|macro|SCIF_RXI_IRQ
mdefine_line|#define SCIF_RXI_IRQ&t;57
DECL|macro|SCIF_BRI_IRQ
mdefine_line|#define SCIF_BRI_IRQ&t;58
DECL|macro|SCIF_TXI_IRQ
mdefine_line|#define SCIF_TXI_IRQ&t;59
DECL|macro|SCIF_IPR_ADDR
mdefine_line|#define SCIF_IPR_ADDR&t;INTC_IPRE
DECL|macro|SCIF_IPR_POS
mdefine_line|#define SCIF_IPR_POS&t;1
DECL|macro|SCIF_PRIORITY
mdefine_line|#define SCIF_PRIORITY&t;3
DECL|macro|IRDA_ERI_IRQ
mdefine_line|#define IRDA_ERI_IRQ&t;52
DECL|macro|IRDA_RXI_IRQ
mdefine_line|#define IRDA_RXI_IRQ&t;53
DECL|macro|IRDA_BRI_IRQ
mdefine_line|#define IRDA_BRI_IRQ&t;54
DECL|macro|IRDA_TXI_IRQ
mdefine_line|#define IRDA_TXI_IRQ&t;55
DECL|macro|IRDA_IPR_ADDR
mdefine_line|#define IRDA_IPR_ADDR&t;INTC_IPRE
DECL|macro|IRDA_IPR_POS
mdefine_line|#define IRDA_IPR_POS&t;2
DECL|macro|IRDA_PRIORITY
mdefine_line|#define IRDA_PRIORITY&t;3
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|SCIF_ERI_IRQ
mdefine_line|#define SCIF_ERI_IRQ&t;40
DECL|macro|SCIF_RXI_IRQ
mdefine_line|#define SCIF_RXI_IRQ&t;41
DECL|macro|SCIF_BRI_IRQ
mdefine_line|#define SCIF_BRI_IRQ&t;42
DECL|macro|SCIF_TXI_IRQ
mdefine_line|#define SCIF_TXI_IRQ&t;43
DECL|macro|SCIF_IPR_ADDR
mdefine_line|#define SCIF_IPR_ADDR&t;INTC_IPRC
DECL|macro|SCIF_IPR_POS
mdefine_line|#define SCIF_IPR_POS&t;1
DECL|macro|SCIF_PRIORITY
mdefine_line|#define SCIF_PRIORITY&t;3
macro_line|#if defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|SCIF1_ERI_IRQ
mdefine_line|#define SCIF1_ERI_IRQ&t;23
DECL|macro|SCIF1_RXI_IRQ
mdefine_line|#define SCIF1_RXI_IRQ&t;24
DECL|macro|SCIF1_BRI_IRQ
mdefine_line|#define SCIF1_BRI_IRQ&t;25
DECL|macro|SCIF1_TXI_IRQ
mdefine_line|#define SCIF1_TXI_IRQ&t;26
DECL|macro|SCIF1_IPR_ADDR
mdefine_line|#define SCIF1_IPR_ADDR&t;INTC_IPRB
DECL|macro|SCIF1_IPR_POS
mdefine_line|#define SCIF1_IPR_POS&t;1
DECL|macro|SCIF1_PRIORITY
mdefine_line|#define SCIF1_PRIORITY&t;3
macro_line|#endif
macro_line|#endif
multiline_comment|/* NR_IRQS is made from three components:&n; *   1. ONCHIP_NR_IRQS - number of IRLS + on-chip peripherial modules&n; *   2. PINT_NR_IRQS   - number of PINT interrupts&n; *   3. OFFCHIP_NR_IRQS - numbe of IRQs from off-chip peripherial modules&n; */
multiline_comment|/* 1. ONCHIP_NR_IRQS */
macro_line|#ifdef CONFIG_SH_GENERIC
DECL|macro|ONCHIP_NR_IRQS
macro_line|# define ONCHIP_NR_IRQS 144
macro_line|#else
macro_line|# if defined(CONFIG_CPU_SUBTYPE_SH7604)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 24&t;
singleline_comment|// Actually 21
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7707)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 64
DECL|macro|PINT_NR_IRQS
macro_line|#  define PINT_NR_IRQS   16
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7708)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 32
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 64&t;
singleline_comment|// Actually 61
DECL|macro|PINT_NR_IRQS
macro_line|#  define PINT_NR_IRQS   16
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7750)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 48&t;
singleline_comment|// Actually 44
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7751)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 72
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7760)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 110
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 144
macro_line|# endif
macro_line|#endif
multiline_comment|/* 2. PINT_NR_IRQS */
macro_line|#ifdef CONFIG_SH_GENERIC
DECL|macro|PINT_NR_IRQS
macro_line|# define PINT_NR_IRQS 16
macro_line|#else
macro_line|# ifndef PINT_NR_IRQS
DECL|macro|PINT_NR_IRQS
macro_line|#  define PINT_NR_IRQS 0
macro_line|# endif
macro_line|#endif
macro_line|#if PINT_NR_IRQS &gt; 0
DECL|macro|PINT_IRQ_BASE
macro_line|# define PINT_IRQ_BASE  ONCHIP_NR_IRQS
macro_line|#endif
multiline_comment|/* 3. OFFCHIP_NR_IRQS */
macro_line|#ifdef CONFIG_SH_GENERIC
DECL|macro|OFFCHIP_NR_IRQS
macro_line|# define OFFCHIP_NR_IRQS 16
macro_line|#else
macro_line|# if defined(CONFIG_HD64461)
DECL|macro|OFFCHIP_NR_IRQS
macro_line|#  define OFFCHIP_NR_IRQS 18
macro_line|# elif defined (CONFIG_SH_BIGSUR) /* must be before CONFIG_HD64465 */
DECL|macro|OFFCHIP_NR_IRQS
macro_line|#  define OFFCHIP_NR_IRQS 48
macro_line|# elif defined(CONFIG_HD64465)
DECL|macro|OFFCHIP_NR_IRQS
macro_line|#  define OFFCHIP_NR_IRQS 16
macro_line|# elif defined (CONFIG_SH_EC3104)
DECL|macro|OFFCHIP_NR_IRQS
macro_line|#  define OFFCHIP_NR_IRQS 16
macro_line|# elif defined (CONFIG_SH_DREAMCAST)
DECL|macro|OFFCHIP_NR_IRQS
macro_line|#  define OFFCHIP_NR_IRQS 96
macro_line|# else
DECL|macro|OFFCHIP_NR_IRQS
macro_line|#  define OFFCHIP_NR_IRQS 0
macro_line|# endif
macro_line|#endif
macro_line|#if OFFCHIP_NR_IRQS &gt; 0
DECL|macro|OFFCHIP_IRQ_BASE
macro_line|# define OFFCHIP_IRQ_BASE (ONCHIP_NR_IRQS + PINT_NR_IRQS)
macro_line|#endif
multiline_comment|/* NR_IRQS. 1+2+3 */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (ONCHIP_NR_IRQS + PINT_NR_IRQS + OFFCHIP_NR_IRQS)
multiline_comment|/* In a generic kernel, NR_IRQS is an upper bound, and we should use&n; * ACTUAL_NR_IRQS (which uses the machine vector) to get the correct value.&n; */
macro_line|#ifdef CONFIG_SH_GENERIC
DECL|macro|ACTUAL_NR_IRQS
macro_line|# define ACTUAL_NR_IRQS (sh_mv.mv_nr_irqs)
macro_line|#else
DECL|macro|ACTUAL_NR_IRQS
macro_line|# define ACTUAL_NR_IRQS NR_IRQS
macro_line|#endif
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Simple Mask Register Support&n; */
r_extern
r_void
id|make_maskreg_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|irq_mask_register
suffix:semicolon
multiline_comment|/*&n; * Function for &quot;on chip support modules&quot;.&n; */
r_extern
r_void
id|make_ipr_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|addr
comma
r_int
id|pos
comma
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|make_imask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7604)
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA&t;0xfffffee2UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB&t;0xfffffe60UL
DECL|macro|INTC_VCRA
mdefine_line|#define INTC_VCRA&t;0xfffffe62UL
DECL|macro|INTC_VCRB
mdefine_line|#define INTC_VCRB&t;0xfffffe64UL
DECL|macro|INTC_VCRC
mdefine_line|#define INTC_VCRC&t;0xfffffe66UL
DECL|macro|INTC_VCRD
mdefine_line|#define INTC_VCRD&t;0xfffffe68UL
DECL|macro|INTC_VCRWDT
mdefine_line|#define INTC_VCRWDT&t;0xfffffee4UL
DECL|macro|INTC_VCRDIV
mdefine_line|#define INTC_VCRDIV&t;0xffffff0cUL
DECL|macro|INTC_VCRDMA0
mdefine_line|#define INTC_VCRDMA0&t;0xffffffa0UL
DECL|macro|INTC_VCRDMA1
mdefine_line|#define INTC_VCRDMA1&t;0xffffffa8UL
DECL|macro|INTC_ICR
mdefine_line|#define INTC_ICR&t;0xfffffee0UL
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7707) || defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|INTC_IRR0
mdefine_line|#define INTC_IRR0&t;0xa4000004UL
DECL|macro|INTC_IRR1
mdefine_line|#define INTC_IRR1&t;0xa4000006UL
DECL|macro|INTC_IRR2
mdefine_line|#define INTC_IRR2&t;0xa4000008UL
DECL|macro|INTC_ICR0
mdefine_line|#define INTC_ICR0  &t;0xfffffee0UL
DECL|macro|INTC_ICR1
mdefine_line|#define INTC_ICR1  &t;0xa4000010UL
DECL|macro|INTC_ICR2
mdefine_line|#define INTC_ICR2  &t;0xa4000012UL
DECL|macro|INTC_INTER
mdefine_line|#define INTC_INTER &t;0xa4000014UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC  &t;0xa4000016UL
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD  &t;0xa4000018UL
DECL|macro|INTC_IPRE
mdefine_line|#define INTC_IPRE  &t;0xa400001aUL
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7707)
DECL|macro|INTC_IPRF
mdefine_line|#define INTC_IPRF&t;0xa400001cUL
macro_line|#endif
DECL|macro|PORT_PACR
mdefine_line|#define PORT_PACR&t;0xa4000100UL
DECL|macro|PORT_PBCR
mdefine_line|#define PORT_PBCR&t;0xa4000102UL
DECL|macro|PORT_PCCR
mdefine_line|#define PORT_PCCR&t;0xa4000104UL
DECL|macro|PORT_PFCR
mdefine_line|#define PORT_PFCR&t;0xa400010aUL
DECL|macro|PORT_PADR
mdefine_line|#define PORT_PADR  &t;0xa4000120UL
DECL|macro|PORT_PBDR
mdefine_line|#define PORT_PBDR  &t;0xa4000122UL
DECL|macro|PORT_PCDR
mdefine_line|#define PORT_PCDR  &t;0xa4000124UL
DECL|macro|PORT_PFDR
mdefine_line|#define PORT_PFDR  &t;0xa400012aUL
DECL|macro|IRQ0_IRQ
mdefine_line|#define IRQ0_IRQ&t;32
DECL|macro|IRQ1_IRQ
mdefine_line|#define IRQ1_IRQ&t;33
DECL|macro|IRQ2_IRQ
mdefine_line|#define IRQ2_IRQ&t;34
DECL|macro|IRQ3_IRQ
mdefine_line|#define IRQ3_IRQ&t;35
DECL|macro|IRQ4_IRQ
mdefine_line|#define IRQ4_IRQ&t;36
DECL|macro|IRQ5_IRQ
mdefine_line|#define IRQ5_IRQ&t;37
DECL|macro|IRQ0_IPR_ADDR
mdefine_line|#define IRQ0_IPR_ADDR&t;INTC_IPRC
DECL|macro|IRQ1_IPR_ADDR
mdefine_line|#define IRQ1_IPR_ADDR&t;INTC_IPRC
DECL|macro|IRQ2_IPR_ADDR
mdefine_line|#define IRQ2_IPR_ADDR&t;INTC_IPRC
DECL|macro|IRQ3_IPR_ADDR
mdefine_line|#define IRQ3_IPR_ADDR&t;INTC_IPRC
DECL|macro|IRQ4_IPR_ADDR
mdefine_line|#define IRQ4_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRQ5_IPR_ADDR
mdefine_line|#define IRQ5_IPR_ADDR&t;INTC_IPRD
DECL|macro|IRQ0_IPR_POS
mdefine_line|#define IRQ0_IPR_POS&t;0
DECL|macro|IRQ1_IPR_POS
mdefine_line|#define IRQ1_IPR_POS&t;1
DECL|macro|IRQ2_IPR_POS
mdefine_line|#define IRQ2_IPR_POS&t;2
DECL|macro|IRQ3_IPR_POS
mdefine_line|#define IRQ3_IPR_POS&t;3
DECL|macro|IRQ4_IPR_POS
mdefine_line|#define IRQ4_IPR_POS&t;0
DECL|macro|IRQ5_IPR_POS
mdefine_line|#define IRQ5_IPR_POS&t;1
DECL|macro|IRQ0_PRIORITY
mdefine_line|#define IRQ0_PRIORITY&t;1
DECL|macro|IRQ1_PRIORITY
mdefine_line|#define IRQ1_PRIORITY&t;1
DECL|macro|IRQ2_PRIORITY
mdefine_line|#define IRQ2_PRIORITY&t;1
DECL|macro|IRQ3_PRIORITY
mdefine_line|#define IRQ3_PRIORITY&t;1
DECL|macro|IRQ4_PRIORITY
mdefine_line|#define IRQ4_PRIORITY&t;1
DECL|macro|IRQ5_PRIORITY
mdefine_line|#define IRQ5_PRIORITY&t;1
DECL|macro|PINT0_IRQ
mdefine_line|#define PINT0_IRQ&t;40
DECL|macro|PINT8_IRQ
mdefine_line|#define PINT8_IRQ&t;41
DECL|macro|PINT0_IPR_ADDR
mdefine_line|#define PINT0_IPR_ADDR&t;INTC_IPRD
DECL|macro|PINT8_IPR_ADDR
mdefine_line|#define PINT8_IPR_ADDR&t;INTC_IPRD
DECL|macro|PINT0_IPR_POS
mdefine_line|#define PINT0_IPR_POS&t;3
DECL|macro|PINT8_IPR_POS
mdefine_line|#define PINT8_IPR_POS&t;2
DECL|macro|PINT0_PRIORITY
mdefine_line|#define PINT0_PRIORITY&t;2
DECL|macro|PINT8_PRIORITY
mdefine_line|#define PINT8_PRIORITY&t;2
r_extern
r_int
id|ipr_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|__irq_demux
mdefine_line|#define __irq_demux(irq) ipr_irq_demux(irq)
macro_line|#else
DECL|macro|__irq_demux
mdefine_line|#define __irq_demux(irq) irq
macro_line|#endif /* CONFIG_CPU_SUBTYPE_SH7707 || CONFIG_CPU_SUBTYPE_SH7709 */
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751) || &bslash;&n;    defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|INTC_ICR
mdefine_line|#define INTC_ICR        0xffd00000
DECL|macro|INTC_ICR_NMIL
mdefine_line|#define INTC_ICR_NMIL&t;(1&lt;&lt;15)
DECL|macro|INTC_ICR_MAI
mdefine_line|#define INTC_ICR_MAI&t;(1&lt;&lt;14)
DECL|macro|INTC_ICR_NMIB
mdefine_line|#define INTC_ICR_NMIB&t;(1&lt;&lt;9)
DECL|macro|INTC_ICR_NMIE
mdefine_line|#define INTC_ICR_NMIE&t;(1&lt;&lt;8)
DECL|macro|INTC_ICR_IRLM
mdefine_line|#define INTC_ICR_IRLM&t;(1&lt;&lt;7)
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_SUBTYPE_ST40STB1
DECL|macro|INTC2_FIRST_IRQ
mdefine_line|#define INTC2_FIRST_IRQ 64
DECL|macro|NR_INTC2_IRQS
mdefine_line|#define NR_INTC2_IRQS 25
DECL|macro|INTC2_BASE0
mdefine_line|#define INTC2_BASE0 0xfe080000
DECL|macro|INTC2_INTC2MODE
mdefine_line|#define INTC2_INTC2MODE  (INTC2_BASE0+0x80)
DECL|macro|INTC2_INTPRI_OFFSET
mdefine_line|#define INTC2_INTPRI_OFFSET&t;0x00
DECL|macro|INTC2_INTREQ_OFFSET
mdefine_line|#define INTC2_INTREQ_OFFSET&t;0x20
DECL|macro|INTC2_INTMSK_OFFSET
mdefine_line|#define INTC2_INTMSK_OFFSET&t;0x40
DECL|macro|INTC2_INTMSKCLR_OFFSET
mdefine_line|#define INTC2_INTMSKCLR_OFFSET&t;0x60
r_extern
r_void
id|make_intc2_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|group
comma
r_int
id|pos
comma
r_int
id|priority
)paren
suffix:semicolon
macro_line|#endif                                                                        
DECL|function|generic_irq_demux
r_static
r_inline
r_int
id|generic_irq_demux
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
DECL|macro|irq_canonicalize
mdefine_line|#define irq_canonicalize(irq)&t;(irq)
DECL|macro|irq_demux
mdefine_line|#define irq_demux(irq)&t;&t;__irq_demux(sh_mv.mv_irq_demux(irq))
macro_line|#endif /* __ASM_SH_IRQ_H */
eof
