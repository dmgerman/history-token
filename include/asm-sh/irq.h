macro_line|#ifndef __ASM_SH_IRQ_H
DECL|macro|__ASM_SH_IRQ_H
mdefine_line|#define __ASM_SH_IRQ_H
multiline_comment|/*&n; *&n; * linux/include/asm-sh/irq.h&n; *&n; * Copyright (C) 1999  Niibe Yutaka &amp; Takeshi Yaegashi&n; * Copyright (C) 2000  Kazumoto Kojima&n; * Copyright (C) 2003  Paul Mundt&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;&t;&t;/* for pt_regs */
macro_line|#if defined(CONFIG_SH_HP600) || &bslash;&n;    defined(CONFIG_SH_RTS7751R2D) || &bslash;&n;    defined(CONFIG_SH_HS7751RVOIP)
macro_line|#include &lt;asm/mach/ide.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SH3)
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA&t;0xfffffee2UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB&t;0xfffffee4UL
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
macro_line|#ifdef CONFIG_IDE
macro_line|# ifndef IRQ_CFCARD
DECL|macro|IRQ_CFCARD
macro_line|#  define IRQ_CFCARD&t;14
macro_line|# endif
macro_line|# ifndef IRQ_PCMCIA
DECL|macro|IRQ_PCMCIA
macro_line|#  define IRQ_PCMCIA&t;15
macro_line|# endif
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
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300)
multiline_comment|/* TMU2 */
DECL|macro|TIMER2_IRQ
mdefine_line|#define TIMER2_IRQ      18
DECL|macro|TIMER2_IPR_ADDR
mdefine_line|#define TIMER2_IPR_ADDR INTC_IPRA
DECL|macro|TIMER2_IPR_POS
mdefine_line|#define TIMER2_IPR_POS   1
DECL|macro|TIMER2_PRIORITY
mdefine_line|#define TIMER2_PRIORITY  2
multiline_comment|/* WDT */
DECL|macro|WDT_IRQ
mdefine_line|#define WDT_IRQ&t;&t;27
DECL|macro|WDT_IPR_ADDR
mdefine_line|#define WDT_IPR_ADDR&t;INTC_IPRB
DECL|macro|WDT_IPR_POS
mdefine_line|#define WDT_IPR_POS&t; 3
DECL|macro|WDT_PRIORITY
mdefine_line|#define WDT_PRIORITY&t; 2
multiline_comment|/* SIM (SIM Card Module) */
DECL|macro|SIM_ERI_IRQ
mdefine_line|#define SIM_ERI_IRQ&t;23
DECL|macro|SIM_RXI_IRQ
mdefine_line|#define SIM_RXI_IRQ&t;24
DECL|macro|SIM_TXI_IRQ
mdefine_line|#define SIM_TXI_IRQ&t;25
DECL|macro|SIM_TEND_IRQ
mdefine_line|#define SIM_TEND_IRQ&t;26
DECL|macro|SIM_IPR_ADDR
mdefine_line|#define SIM_IPR_ADDR&t;INTC_IPRB
DECL|macro|SIM_IPR_POS
mdefine_line|#define SIM_IPR_POS&t; 1
DECL|macro|SIM_PRIORITY
mdefine_line|#define SIM_PRIORITY&t; 2
multiline_comment|/* VIO (Video I/O) */
DECL|macro|VIO_IRQ
mdefine_line|#define VIO_IRQ&t;&t;52
DECL|macro|VIO_IPR_ADDR
mdefine_line|#define VIO_IPR_ADDR&t;INTC_IPRE
DECL|macro|VIO_IPR_POS
mdefine_line|#define VIO_IPR_POS&t; 2
DECL|macro|VIO_PRIORITY
mdefine_line|#define VIO_PRIORITY&t; 2
multiline_comment|/* MFI (Multi Functional Interface) */
DECL|macro|MFI_IRQ
mdefine_line|#define MFI_IRQ&t;&t;56
DECL|macro|MFI_IPR_ADDR
mdefine_line|#define MFI_IPR_ADDR&t;INTC_IPRE
DECL|macro|MFI_IPR_POS
mdefine_line|#define MFI_IPR_POS&t; 1
DECL|macro|MFI_PRIORITY
mdefine_line|#define MFI_PRIORITY&t; 2
multiline_comment|/* VPU (Video Processing Unit) */
DECL|macro|VPU_IRQ
mdefine_line|#define VPU_IRQ&t;&t;60
DECL|macro|VPU_IPR_ADDR
mdefine_line|#define VPU_IPR_ADDR&t;INTC_IPRE
DECL|macro|VPU_IPR_POS
mdefine_line|#define VPU_IPR_POS&t; 0
DECL|macro|VPU_PRIORITY
mdefine_line|#define VPU_PRIORITY&t; 2
multiline_comment|/* KEY (Key Scan Interface) */
DECL|macro|KEY_IRQ
mdefine_line|#define KEY_IRQ&t;&t;79
DECL|macro|KEY_IPR_ADDR
mdefine_line|#define KEY_IPR_ADDR&t;INTC_IPRF
DECL|macro|KEY_IPR_POS
mdefine_line|#define KEY_IPR_POS&t; 3
DECL|macro|KEY_PRIORITY
mdefine_line|#define KEY_PRIORITY&t; 2
multiline_comment|/* CMT (Compare Match Timer) */
DECL|macro|CMT_IRQ
mdefine_line|#define CMT_IRQ&t;&t;104
DECL|macro|CMT_IPR_ADDR
mdefine_line|#define CMT_IPR_ADDR&t;INTC_IPRF
DECL|macro|CMT_IPR_POS
mdefine_line|#define CMT_IPR_POS&t; 0
DECL|macro|CMT_PRIORITY
mdefine_line|#define CMT_PRIORITY&t; 2
multiline_comment|/* DMAC(1) */
DECL|macro|DMTE0_IRQ
mdefine_line|#define DMTE0_IRQ&t;48
DECL|macro|DMTE1_IRQ
mdefine_line|#define DMTE1_IRQ&t;49
DECL|macro|DMTE2_IRQ
mdefine_line|#define DMTE2_IRQ&t;50
DECL|macro|DMTE3_IRQ
mdefine_line|#define DMTE3_IRQ&t;51
DECL|macro|DMA1_IPR_ADDR
mdefine_line|#define DMA1_IPR_ADDR&t;INTC_IPRE
DECL|macro|DMA1_IPR_POS
mdefine_line|#define DMA1_IPR_POS&t;3
DECL|macro|DMA1_PRIORITY
mdefine_line|#define DMA1_PRIORITY&t;7
multiline_comment|/* DMAC(2) */
DECL|macro|DMTE4_IRQ
mdefine_line|#define DMTE4_IRQ&t;76
DECL|macro|DMTE5_IRQ
mdefine_line|#define DMTE5_IRQ&t;77
DECL|macro|DMA2_IPR_ADDR
mdefine_line|#define DMA2_IPR_ADDR&t;INTC_IPRF
DECL|macro|DMA2_IPR_POS
mdefine_line|#define DMA2_IPR_POS&t;2
DECL|macro|DMA2_PRIORITY
mdefine_line|#define DMA2_PRIORITY&t;7
multiline_comment|/* SIOF0 */
DECL|macro|SIOF0_IRQ
mdefine_line|#define SIOF0_IRQ&t;84
DECL|macro|SIOF0_IPR_ADDR
mdefine_line|#define SIOF0_IPR_ADDR&t;INTC_IPRH
DECL|macro|SIOF0_IPR_POS
mdefine_line|#define SIOF0_IPR_POS&t;3
DECL|macro|SIOF0_PRIORITY
mdefine_line|#define SIOF0_PRIORITY&t;3
multiline_comment|/* FLCTL (Flash Memory Controller) */
DECL|macro|FLSTE_IRQ
mdefine_line|#define FLSTE_IRQ&t;92
DECL|macro|FLTEND_IRQ
mdefine_line|#define FLTEND_IRQ&t;93
DECL|macro|FLTRQ0_IRQ
mdefine_line|#define FLTRQ0_IRQ&t;94
DECL|macro|FLTRQ1_IRQ
mdefine_line|#define FLTRQ1_IRQ&t;95
DECL|macro|FLCTL_IPR_ADDR
mdefine_line|#define FLCTL_IPR_ADDR&t;INTC_IPRH
DECL|macro|FLCTL_IPR_POS
mdefine_line|#define FLCTL_IPR_POS&t;1
DECL|macro|FLCTL_PRIORITY
mdefine_line|#define FLCTL_PRIORITY&t;3
multiline_comment|/* IIC (IIC Bus Interface) */
DECL|macro|IIC_ALI_IRQ
mdefine_line|#define IIC_ALI_IRQ&t;96
DECL|macro|IIC_TACKI_IRQ
mdefine_line|#define IIC_TACKI_IRQ&t;97
DECL|macro|IIC_WAITI_IRQ
mdefine_line|#define IIC_WAITI_IRQ&t;98
DECL|macro|IIC_DTEI_IRQ
mdefine_line|#define IIC_DTEI_IRQ&t;99
DECL|macro|IIC_IPR_ADDR
mdefine_line|#define IIC_IPR_ADDR&t;INTC_IPRH
DECL|macro|IIC_IPR_POS
mdefine_line|#define IIC_IPR_POS&t;0
DECL|macro|IIC_PRIORITY
mdefine_line|#define IIC_PRIORITY&t;3
multiline_comment|/* SIO0 */
DECL|macro|SIO0_IRQ
mdefine_line|#define SIO0_IRQ&t;88
DECL|macro|SIO0_IPR_ADDR
mdefine_line|#define SIO0_IPR_ADDR&t;INTC_IPRI
DECL|macro|SIO0_IPR_POS
mdefine_line|#define SIO0_IPR_POS&t;3
DECL|macro|SIO0_PRIORITY
mdefine_line|#define SIO0_PRIORITY&t;3
multiline_comment|/* SIU (Sound Interface Unit) */
DECL|macro|SIU_IRQ
mdefine_line|#define SIU_IRQ&t;&t;108
DECL|macro|SIU_IPR_ADDR
mdefine_line|#define SIU_IPR_ADDR&t;INTC_IPRJ
DECL|macro|SIU_IPR_POS
mdefine_line|#define SIU_IPR_POS&t;1
DECL|macro|SIU_PRIORITY
mdefine_line|#define SIU_PRIORITY&t;3
macro_line|#endif
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
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300)
DECL|macro|SCIF0_IRQ
mdefine_line|#define SCIF0_IRQ&t;80
DECL|macro|SCIF0_IPR_ADDR
mdefine_line|#define SCIF0_IPR_ADDR&t;INTC_IPRG
DECL|macro|SCIF0_IPR_POS
mdefine_line|#define SCIF0_IPR_POS&t;3
DECL|macro|SCIF0_PRIORITY
mdefine_line|#define SCIF0_PRIORITY&t;3
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7705) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_SH7707) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_SH7709)
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
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_ST40STB1) || defined(CONFIG_CPU_SUBTYPE_SH4_202)
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
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7709) || &bslash;&n;       defined(CONFIG_CPU_SUBTYPE_SH7705)
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
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH4_202)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 72
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_ST40STB1)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 144
macro_line|# elif defined(CONFIG_CPU_SUBTYPE_SH7300)
DECL|macro|ONCHIP_NR_IRQS
macro_line|#  define ONCHIP_NR_IRQS 109
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
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300)
DECL|macro|INTC_IPRA
macro_line|#undef INTC_IPRA
DECL|macro|INTC_IPRB
macro_line|#undef INTC_IPRB
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA  &t;0xA414FEE2UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB  &t;0xA414FEE4UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC  &t;0xA4140016UL
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD  &t;0xA4140018UL
DECL|macro|INTC_IPRE
mdefine_line|#define INTC_IPRE  &t;0xA414001AUL
DECL|macro|INTC_IPRF
mdefine_line|#define INTC_IPRF  &t;0xA4080000UL
DECL|macro|INTC_IPRG
mdefine_line|#define INTC_IPRG  &t;0xA4080002UL
DECL|macro|INTC_IPRH
mdefine_line|#define INTC_IPRH  &t;0xA4080004UL
DECL|macro|INTC_IPRI
mdefine_line|#define INTC_IPRI  &t;0xA4080006UL
DECL|macro|INTC_IPRJ
mdefine_line|#define INTC_IPRJ  &t;0xA4080008UL
DECL|macro|INTC_IMR0
mdefine_line|#define INTC_IMR0&t;0xA4080040UL
DECL|macro|INTC_IMR1
mdefine_line|#define INTC_IMR1&t;0xA4080042UL
DECL|macro|INTC_IMR2
mdefine_line|#define INTC_IMR2&t;0xA4080044UL
DECL|macro|INTC_IMR3
mdefine_line|#define INTC_IMR3&t;0xA4080046UL
DECL|macro|INTC_IMR4
mdefine_line|#define INTC_IMR4&t;0xA4080048UL
DECL|macro|INTC_IMR5
mdefine_line|#define INTC_IMR5&t;0xA408004AUL
DECL|macro|INTC_IMR6
mdefine_line|#define INTC_IMR6&t;0xA408004CUL
DECL|macro|INTC_IMR7
mdefine_line|#define INTC_IMR7&t;0xA408004EUL
DECL|macro|INTC_IMR8
mdefine_line|#define INTC_IMR8&t;0xA4080050UL
DECL|macro|INTC_IMR9
mdefine_line|#define INTC_IMR9&t;0xA4080052UL
DECL|macro|INTC_IMR10
mdefine_line|#define INTC_IMR10&t;0xA4080054UL
DECL|macro|INTC_IMCR0
mdefine_line|#define INTC_IMCR0&t;0xA4080060UL
DECL|macro|INTC_IMCR1
mdefine_line|#define INTC_IMCR1&t;0xA4080062UL
DECL|macro|INTC_IMCR2
mdefine_line|#define INTC_IMCR2&t;0xA4080064UL
DECL|macro|INTC_IMCR3
mdefine_line|#define INTC_IMCR3&t;0xA4080066UL
DECL|macro|INTC_IMCR4
mdefine_line|#define INTC_IMCR4&t;0xA4080068UL
DECL|macro|INTC_IMCR5
mdefine_line|#define INTC_IMCR5&t;0xA408006AUL
DECL|macro|INTC_IMCR6
mdefine_line|#define INTC_IMCR6&t;0xA408006CUL
DECL|macro|INTC_IMCR7
mdefine_line|#define INTC_IMCR7&t;0xA408006EUL
DECL|macro|INTC_IMCR8
mdefine_line|#define INTC_IMCR8&t;0xA4080070UL
DECL|macro|INTC_IMCR9
mdefine_line|#define INTC_IMCR9&t;0xA4080072UL
DECL|macro|INTC_IMCR10
mdefine_line|#define INTC_IMCR10&t;0xA4080074UL
DECL|macro|INTC_ICR0
mdefine_line|#define INTC_ICR0&t;0xA414FEE0UL
DECL|macro|INTC_ICR1
mdefine_line|#define INTC_ICR1&t;0xA4140010UL
DECL|macro|INTC_IRR0
mdefine_line|#define INTC_IRR0&t;0xA4140004UL
DECL|macro|PORT_PACR
mdefine_line|#define PORT_PACR&t;0xA4050100UL
DECL|macro|PORT_PBCR
mdefine_line|#define PORT_PBCR&t;0xA4050102UL
DECL|macro|PORT_PCCR
mdefine_line|#define PORT_PCCR&t;0xA4050104UL
DECL|macro|PORT_PDCR
mdefine_line|#define PORT_PDCR&t;0xA4050106UL
DECL|macro|PORT_PECR
mdefine_line|#define PORT_PECR&t;0xA4050108UL
DECL|macro|PORT_PFCR
mdefine_line|#define PORT_PFCR&t;0xA405010AUL
DECL|macro|PORT_PGCR
mdefine_line|#define PORT_PGCR&t;0xA405010CUL
DECL|macro|PORT_PHCR
mdefine_line|#define PORT_PHCR&t;0xA405010EUL
DECL|macro|PORT_PJCR
mdefine_line|#define PORT_PJCR&t;0xA4050110UL
DECL|macro|PORT_PKCR
mdefine_line|#define PORT_PKCR&t;0xA4050112UL
DECL|macro|PORT_PLCR
mdefine_line|#define PORT_PLCR&t;0xA4050114UL
DECL|macro|PORT_SCPCR
mdefine_line|#define PORT_SCPCR&t;0xA4050116UL
DECL|macro|PORT_PMCR
mdefine_line|#define PORT_PMCR&t;0xA4050118UL
DECL|macro|PORT_PNCR
mdefine_line|#define PORT_PNCR&t;0xA405011AUL
DECL|macro|PORT_PQCR
mdefine_line|#define PORT_PQCR&t;0xA405011CUL
DECL|macro|PORT_PSELA
mdefine_line|#define PORT_PSELA&t;0xA4050140UL
DECL|macro|PORT_PSELB
mdefine_line|#define PORT_PSELB&t;0xA4050142UL
DECL|macro|PORT_PSELC
mdefine_line|#define PORT_PSELC&t;0xA4050144UL
DECL|macro|PORT_HIZCRA
mdefine_line|#define PORT_HIZCRA&t;0xA4050146UL
DECL|macro|PORT_HIZCRB
mdefine_line|#define PORT_HIZCRB&t;0xA4050148UL
DECL|macro|PORT_DRVCR
mdefine_line|#define PORT_DRVCR&t;0xA4050150UL
DECL|macro|PORT_PADR
mdefine_line|#define PORT_PADR  &t;0xA4050120UL
DECL|macro|PORT_PBDR
mdefine_line|#define PORT_PBDR  &t;0xA4050122UL
DECL|macro|PORT_PCDR
mdefine_line|#define PORT_PCDR  &t;0xA4050124UL
DECL|macro|PORT_PDDR
mdefine_line|#define PORT_PDDR  &t;0xA4050126UL
DECL|macro|PORT_PEDR
mdefine_line|#define PORT_PEDR  &t;0xA4050128UL
DECL|macro|PORT_PFDR
mdefine_line|#define PORT_PFDR  &t;0xA405012AUL
DECL|macro|PORT_PGDR
mdefine_line|#define PORT_PGDR  &t;0xA405012CUL
DECL|macro|PORT_PHDR
mdefine_line|#define PORT_PHDR  &t;0xA405012EUL
DECL|macro|PORT_PJDR
mdefine_line|#define PORT_PJDR  &t;0xA4050130UL
DECL|macro|PORT_PKDR
mdefine_line|#define PORT_PKDR  &t;0xA4050132UL
DECL|macro|PORT_PLDR
mdefine_line|#define PORT_PLDR  &t;0xA4050134UL
DECL|macro|PORT_SCPDR
mdefine_line|#define PORT_SCPDR  &t;0xA4050136UL
DECL|macro|PORT_PMDR
mdefine_line|#define PORT_PMDR  &t;0xA4050138UL
DECL|macro|PORT_PNDR
mdefine_line|#define PORT_PNDR  &t;0xA405013AUL
DECL|macro|PORT_PQDR
mdefine_line|#define PORT_PQDR  &t;0xA405013CUL
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
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7604)
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
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7705) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_SH7707) || &bslash;&n;      defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|INTC_IRR0
mdefine_line|#define INTC_IRR0&t;0xa4000004UL
DECL|macro|INTC_IRR1
mdefine_line|#define INTC_IRR1&t;0xa4000006UL
DECL|macro|INTC_IRR2
mdefine_line|#define INTC_IRR2&t;0xa4000008UL
DECL|macro|INTC_ICR0
mdefine_line|#define INTC_ICR0&t;0xfffffee0UL
DECL|macro|INTC_ICR1
mdefine_line|#define INTC_ICR1&t;0xa4000010UL
DECL|macro|INTC_ICR2
mdefine_line|#define INTC_ICR2&t;0xa4000012UL
DECL|macro|INTC_INTER
mdefine_line|#define INTC_INTER&t;0xa4000014UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC&t;0xa4000016UL
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD&t;0xa4000018UL
DECL|macro|INTC_IPRE
mdefine_line|#define INTC_IPRE&t;0xa400001aUL
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7707)
DECL|macro|INTC_IPRF
mdefine_line|#define INTC_IPRF&t;0xa400001cUL
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7705)
DECL|macro|INTC_IPRF
mdefine_line|#define INTC_IPRF&t;0xa4080000UL
DECL|macro|INTC_IPRG
mdefine_line|#define INTC_IPRG&t;0xa4080002UL
DECL|macro|INTC_IPRH
mdefine_line|#define INTC_IPRH&t;0xa4080004UL
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
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751) || &bslash;&n;    defined(CONFIG_CPU_SUBTYPE_ST40STB1) || defined(CONFIG_CPU_SUBTYPE_SH4_202)
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
DECL|macro|INTC2_BASE
mdefine_line|#define INTC2_BASE&t;0xfe080000
DECL|macro|INTC2_INTC2MODE
mdefine_line|#define INTC2_INTC2MODE&t;(INTC2_BASE+0x80)
DECL|macro|INTC2_INTPRI_OFFSET
mdefine_line|#define INTC2_INTPRI_OFFSET&t;0x00
DECL|macro|INTC2_INTREQ_OFFSET
mdefine_line|#define INTC2_INTREQ_OFFSET&t;0x20
DECL|macro|INTC2_INTMSK_OFFSET
mdefine_line|#define INTC2_INTMSK_OFFSET&t;0x40
DECL|macro|INTC2_INTMSKCLR_OFFSET
mdefine_line|#define INTC2_INTMSKCLR_OFFSET&t;0x60
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
id|ipr_offset
comma
r_int
r_int
id|ipr_shift
comma
r_int
r_int
id|msk_offset
comma
r_int
r_int
id|msk_shift
comma
r_int
r_int
id|priority
)paren
suffix:semicolon
r_void
id|init_IRQ_intc2
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|intc2_add_clear_irq
c_func
(paren
r_int
id|irq
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_CPU_SUBTYPE_ST40STB1 */
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
r_struct
id|irqaction
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_int
id|handle_IRQ_event
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH73180)
macro_line|#include &lt;asm/irq-sh73180.h&gt;
macro_line|#endif
macro_line|#endif /* __ASM_SH_IRQ_H */
eof
