macro_line|#ifndef __ASM_SH_IRQ_SH73180_H
DECL|macro|__ASM_SH_IRQ_SH73180_H
mdefine_line|#define __ASM_SH_IRQ_SH73180_H
multiline_comment|/*&n; * linux/include/asm-sh/irq-sh73180.h&n; *&n; * Copyright (C) 2004 Takashi SHUDO &lt;shudo@hitachi-ul.co.jp&gt;&n; */
DECL|macro|INTC_IPRA
macro_line|#undef INTC_IPRA
DECL|macro|INTC_IPRB
macro_line|#undef INTC_IPRB
DECL|macro|INTC_IPRC
macro_line|#undef INTC_IPRC
DECL|macro|INTC_IPRD
macro_line|#undef INTC_IPRD
DECL|macro|DMTE0_IRQ
macro_line|#undef DMTE0_IRQ
DECL|macro|DMTE1_IRQ
macro_line|#undef DMTE1_IRQ
DECL|macro|DMTE2_IRQ
macro_line|#undef DMTE2_IRQ
DECL|macro|DMTE3_IRQ
macro_line|#undef DMTE3_IRQ
DECL|macro|DMTE4_IRQ
macro_line|#undef DMTE4_IRQ
DECL|macro|DMTE5_IRQ
macro_line|#undef DMTE5_IRQ
DECL|macro|DMTE6_IRQ
macro_line|#undef DMTE6_IRQ
DECL|macro|DMTE7_IRQ
macro_line|#undef DMTE7_IRQ
DECL|macro|DMAE_IRQ
macro_line|#undef DMAE_IRQ
DECL|macro|DMA_IPR_ADDR
macro_line|#undef DMA_IPR_ADDR
DECL|macro|DMA_IPR_POS
macro_line|#undef DMA_IPR_POS
DECL|macro|DMA_PRIORITY
macro_line|#undef DMA_PRIORITY
DECL|macro|NR_IRQS
macro_line|#undef NR_IRQS
DECL|macro|__irq_demux
macro_line|#undef __irq_demux
DECL|macro|irq_demux
macro_line|#undef irq_demux
DECL|macro|INTC_IMCR0
macro_line|#undef INTC_IMCR0
DECL|macro|INTC_IMCR1
macro_line|#undef INTC_IMCR1
DECL|macro|INTC_IMCR2
macro_line|#undef INTC_IMCR2
DECL|macro|INTC_IMCR3
macro_line|#undef INTC_IMCR3
DECL|macro|INTC_IMCR4
macro_line|#undef INTC_IMCR4
DECL|macro|INTC_IMCR5
macro_line|#undef INTC_IMCR5
DECL|macro|INTC_IMCR6
macro_line|#undef INTC_IMCR6
DECL|macro|INTC_IMCR7
macro_line|#undef INTC_IMCR7
DECL|macro|INTC_IMCR8
macro_line|#undef INTC_IMCR8
DECL|macro|INTC_IMCR9
macro_line|#undef INTC_IMCR9
DECL|macro|INTC_IMCR10
macro_line|#undef INTC_IMCR10
DECL|macro|INTC_IPRA
mdefine_line|#define INTC_IPRA  &t;0xA4080000UL
DECL|macro|INTC_IPRB
mdefine_line|#define INTC_IPRB  &t;0xA4080004UL
DECL|macro|INTC_IPRC
mdefine_line|#define INTC_IPRC  &t;0xA4080008UL
DECL|macro|INTC_IPRD
mdefine_line|#define INTC_IPRD  &t;0xA408000CUL
DECL|macro|INTC_IPRE
mdefine_line|#define INTC_IPRE  &t;0xA4080010UL
DECL|macro|INTC_IPRF
mdefine_line|#define INTC_IPRF  &t;0xA4080014UL
DECL|macro|INTC_IPRG
mdefine_line|#define INTC_IPRG  &t;0xA4080018UL
DECL|macro|INTC_IPRH
mdefine_line|#define INTC_IPRH  &t;0xA408001CUL
DECL|macro|INTC_IPRI
mdefine_line|#define INTC_IPRI  &t;0xA4080020UL
DECL|macro|INTC_IPRJ
mdefine_line|#define INTC_IPRJ  &t;0xA4080024UL
DECL|macro|INTC_IPRK
mdefine_line|#define INTC_IPRK  &t;0xA4080028UL
DECL|macro|INTC_IMR0
mdefine_line|#define INTC_IMR0&t;0xA4080080UL
DECL|macro|INTC_IMR1
mdefine_line|#define INTC_IMR1&t;0xA4080084UL
DECL|macro|INTC_IMR2
mdefine_line|#define INTC_IMR2&t;0xA4080088UL
DECL|macro|INTC_IMR3
mdefine_line|#define INTC_IMR3&t;0xA408008CUL
DECL|macro|INTC_IMR4
mdefine_line|#define INTC_IMR4&t;0xA4080090UL
DECL|macro|INTC_IMR5
mdefine_line|#define INTC_IMR5&t;0xA4080094UL
DECL|macro|INTC_IMR6
mdefine_line|#define INTC_IMR6&t;0xA4080098UL
DECL|macro|INTC_IMR7
mdefine_line|#define INTC_IMR7&t;0xA408009CUL
DECL|macro|INTC_IMR8
mdefine_line|#define INTC_IMR8&t;0xA40800A0UL
DECL|macro|INTC_IMR9
mdefine_line|#define INTC_IMR9&t;0xA40800A4UL
DECL|macro|INTC_IMR10
mdefine_line|#define INTC_IMR10&t;0xA40800A8UL
DECL|macro|INTC_IMR11
mdefine_line|#define INTC_IMR11&t;0xA40800ACUL
DECL|macro|INTC_IMCR0
mdefine_line|#define INTC_IMCR0&t;0xA40800C0UL
DECL|macro|INTC_IMCR1
mdefine_line|#define INTC_IMCR1&t;0xA40800C4UL
DECL|macro|INTC_IMCR2
mdefine_line|#define INTC_IMCR2&t;0xA40800C8UL
DECL|macro|INTC_IMCR3
mdefine_line|#define INTC_IMCR3&t;0xA40800CCUL
DECL|macro|INTC_IMCR4
mdefine_line|#define INTC_IMCR4&t;0xA40800D0UL
DECL|macro|INTC_IMCR5
mdefine_line|#define INTC_IMCR5&t;0xA40800D4UL
DECL|macro|INTC_IMCR6
mdefine_line|#define INTC_IMCR6&t;0xA40800D8UL
DECL|macro|INTC_IMCR7
mdefine_line|#define INTC_IMCR7&t;0xA40800DCUL
DECL|macro|INTC_IMCR8
mdefine_line|#define INTC_IMCR8&t;0xA40800E0UL
DECL|macro|INTC_IMCR9
mdefine_line|#define INTC_IMCR9&t;0xA40800E4UL
DECL|macro|INTC_IMCR10
mdefine_line|#define INTC_IMCR10&t;0xA40800E8UL
DECL|macro|INTC_IMCR11
mdefine_line|#define INTC_IMCR11&t;0xA40800ECUL
DECL|macro|INTC_ICR0
mdefine_line|#define INTC_ICR0&t;0xA4140000UL
DECL|macro|INTC_ICR1
mdefine_line|#define INTC_ICR1&t;0xA414001CUL
DECL|macro|INTMSK0
mdefine_line|#define INTMSK0&t;&t;0xa4140044
DECL|macro|INTMSKCLR0
mdefine_line|#define INTMSKCLR0&t;0xa4140064
DECL|macro|INTC_INTPRI0
mdefine_line|#define INTC_INTPRI0&t;0xa4140010
multiline_comment|/*&n;  NOTE:&n;&n;  *_IRQ = (INTEVT2 - 0x200)/0x20&n;*/
multiline_comment|/* TMU0 */
DECL|macro|TMU0_IRQ
mdefine_line|#define TMU0_IRQ&t;16
DECL|macro|TMU0_IPR_ADDR
mdefine_line|#define TMU0_IPR_ADDR&t;INTC_IPRA
DECL|macro|TMU0_IPR_POS
mdefine_line|#define TMU0_IPR_POS&t; 3
DECL|macro|TMU0_PRIORITY
mdefine_line|#define TMU0_PRIORITY&t; 2
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ       16
DECL|macro|TIMER_IPR_ADDR
mdefine_line|#define TIMER_IPR_ADDR  INTC_IPRA
DECL|macro|TIMER_IPR_POS
mdefine_line|#define TIMER_IPR_POS    3
DECL|macro|TIMER_PRIORITY
mdefine_line|#define TIMER_PRIORITY   2
multiline_comment|/* TMU1 */
DECL|macro|TMU1_IRQ
mdefine_line|#define TMU1_IRQ&t;17
DECL|macro|TMU1_IPR_ADDR
mdefine_line|#define TMU1_IPR_ADDR&t;INTC_IPRA
DECL|macro|TMU1_IPR_POS
mdefine_line|#define TMU1_IPR_POS&t; 2
DECL|macro|TMU1_PRIORITY
mdefine_line|#define TMU1_PRIORITY&t; 2
multiline_comment|/* TMU2 */
DECL|macro|TMU2_IRQ
mdefine_line|#define TMU2_IRQ&t;18
DECL|macro|TMU2_IPR_ADDR
mdefine_line|#define TMU2_IPR_ADDR&t;INTC_IPRA
DECL|macro|TMU2_IPR_POS
mdefine_line|#define TMU2_IPR_POS&t; 1
DECL|macro|TMU2_PRIORITY
mdefine_line|#define TMU2_PRIORITY&t; 2
multiline_comment|/* LCDC */
DECL|macro|LCDC_IRQ
mdefine_line|#define LCDC_IRQ&t;28
DECL|macro|LCDC_IPR_ADDR
mdefine_line|#define LCDC_IPR_ADDR&t;INTC_IPRB
DECL|macro|LCDC_IPR_POS
mdefine_line|#define LCDC_IPR_POS&t; 2
DECL|macro|LCDC_PRIORITY
mdefine_line|#define LCDC_PRIORITY&t; 2
multiline_comment|/* VIO (Video I/O) */
DECL|macro|CEU_IRQ
mdefine_line|#define CEU_IRQ&t;&t;52
DECL|macro|BEU_IRQ
mdefine_line|#define BEU_IRQ&t;&t;53
DECL|macro|VEU_IRQ
mdefine_line|#define VEU_IRQ&t;&t;54
DECL|macro|VOU_IRQ
mdefine_line|#define VOU_IRQ&t;&t;55
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
multiline_comment|/* 3DG */
DECL|macro|TDG_IRQ
mdefine_line|#define TDG_IRQ&t;&t;63
DECL|macro|TDG_IPR_ADDR
mdefine_line|#define TDG_IPR_ADDR&t;INTC_IPRJ
DECL|macro|TDG_IPR_POS
mdefine_line|#define TDG_IPR_POS&t; 2
DECL|macro|TDG_PRIORITY
mdefine_line|#define TDG_PRIORITY&t; 2
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
multiline_comment|/* SCIF0 */
DECL|macro|SCIF_ERI_IRQ
mdefine_line|#define SCIF_ERI_IRQ&t;80
DECL|macro|SCIF_RXI_IRQ
mdefine_line|#define SCIF_RXI_IRQ&t;81
DECL|macro|SCIF_BRI_IRQ
mdefine_line|#define SCIF_BRI_IRQ&t;82
DECL|macro|SCIF_TXI_IRQ
mdefine_line|#define SCIF_TXI_IRQ&t;83
DECL|macro|SCIF_IPR_ADDR
mdefine_line|#define SCIF_IPR_ADDR&t;INTC_IPRG
DECL|macro|SCIF_IPR_POS
mdefine_line|#define SCIF_IPR_POS&t;3
DECL|macro|SCIF_PRIORITY
mdefine_line|#define SCIF_PRIORITY&t;3
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
multiline_comment|/* IIC(0) (IIC Bus Interface) */
DECL|macro|IIC0_ALI_IRQ
mdefine_line|#define IIC0_ALI_IRQ&t;96
DECL|macro|IIC0_TACKI_IRQ
mdefine_line|#define IIC0_TACKI_IRQ&t;97
DECL|macro|IIC0_WAITI_IRQ
mdefine_line|#define IIC0_WAITI_IRQ&t;98
DECL|macro|IIC0_DTEI_IRQ
mdefine_line|#define IIC0_DTEI_IRQ&t;99
DECL|macro|IIC0_IPR_ADDR
mdefine_line|#define IIC0_IPR_ADDR&t;INTC_IPRH
DECL|macro|IIC0_IPR_POS
mdefine_line|#define IIC0_IPR_POS&t;0
DECL|macro|IIC0_PRIORITY
mdefine_line|#define IIC0_PRIORITY&t;3
multiline_comment|/* IIC(1) (IIC Bus Interface) */
DECL|macro|IIC1_ALI_IRQ
mdefine_line|#define IIC1_ALI_IRQ&t;44
DECL|macro|IIC1_TACKI_IRQ
mdefine_line|#define IIC1_TACKI_IRQ&t;45
DECL|macro|IIC1_WAITI_IRQ
mdefine_line|#define IIC1_WAITI_IRQ&t;46
DECL|macro|IIC1_DTEI_IRQ
mdefine_line|#define IIC1_DTEI_IRQ&t;47
DECL|macro|IIC1_IPR_ADDR
mdefine_line|#define IIC1_IPR_ADDR&t;INTC_IPRG
DECL|macro|IIC1_IPR_POS
mdefine_line|#define IIC1_IPR_POS&t;0
DECL|macro|IIC1_PRIORITY
mdefine_line|#define IIC1_PRIORITY&t;3
multiline_comment|/* SIO0 */
DECL|macro|SIO0_IRQ
mdefine_line|#define SIO0_IRQ&t;88
DECL|macro|SIO0_IPR_ADDR
mdefine_line|#define SIO0_IPR_ADDR&t;INTC_IPRI
DECL|macro|SIO0_IPR_POS
mdefine_line|#define SIO0_IPR_POS&t;3
DECL|macro|SIO0_PRIORITY
mdefine_line|#define SIO0_PRIORITY&t;3
multiline_comment|/* SDHI */
DECL|macro|SDHI_SDHII0_IRQ
mdefine_line|#define SDHI_SDHII0_IRQ&t;100
DECL|macro|SDHI_SDHII1_IRQ
mdefine_line|#define SDHI_SDHII1_IRQ&t;101
DECL|macro|SDHI_SDHII2_IRQ
mdefine_line|#define SDHI_SDHII2_IRQ&t;102
DECL|macro|SDHI_SDHII3_IRQ
mdefine_line|#define SDHI_SDHII3_IRQ&t;103
DECL|macro|SDHI_IPR_ADDR
mdefine_line|#define SDHI_IPR_ADDR&t;INTC_IPRK
DECL|macro|SDHI_IPR_POS
mdefine_line|#define SDHI_IPR_POS&t;0
DECL|macro|SDHI_PRIORITY
mdefine_line|#define SDHI_PRIORITY&t;3
multiline_comment|/* SIU (Sound Interface Unit) */
DECL|macro|SIU_IRQ
mdefine_line|#define SIU_IRQ&t;&t;108
DECL|macro|SIU_IPR_ADDR
mdefine_line|#define SIU_IPR_ADDR&t;INTC_IPRJ
DECL|macro|SIU_IPR_POS
mdefine_line|#define SIU_IPR_POS&t;1
DECL|macro|SIU_PRIORITY
mdefine_line|#define SIU_PRIORITY&t;3
multiline_comment|/* ONCHIP_NR_IRQS */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 109
multiline_comment|/* In a generic kernel, NR_IRQS is an upper bound, and we should use&n; * ACTUAL_NR_IRQS (which uses the machine vector) to get the correct value.&n; */
DECL|macro|ACTUAL_NR_IRQS
mdefine_line|#define ACTUAL_NR_IRQS NR_IRQS
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
DECL|macro|PORT_PRCR
mdefine_line|#define PORT_PRCR&t;0xA405011EUL
DECL|macro|PORT_PTCR
mdefine_line|#define PORT_PTCR&t;0xA405014CUL
DECL|macro|PORT_PUCR
mdefine_line|#define PORT_PUCR&t;0xA405014EUL
DECL|macro|PORT_PVCR
mdefine_line|#define PORT_PVCR&t;0xA4050150UL
DECL|macro|PORT_PSELA
mdefine_line|#define PORT_PSELA&t;0xA4050140UL
DECL|macro|PORT_PSELB
mdefine_line|#define PORT_PSELB&t;0xA4050142UL
DECL|macro|PORT_PSELC
mdefine_line|#define PORT_PSELC&t;0xA4050144UL
DECL|macro|PORT_PSELE
mdefine_line|#define PORT_PSELE&t;0xA4050158UL
DECL|macro|PORT_HIZCRA
mdefine_line|#define PORT_HIZCRA&t;0xA4050146UL
DECL|macro|PORT_HIZCRB
mdefine_line|#define PORT_HIZCRB&t;0xA4050148UL
DECL|macro|PORT_DRVCR
mdefine_line|#define PORT_DRVCR&t;0xA405014AUL
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
DECL|macro|PORT_PRDR
mdefine_line|#define PORT_PRDR  &t;0xA405013EUL
DECL|macro|PORT_PTDR
mdefine_line|#define PORT_PTDR  &t;0xA405016CUL
DECL|macro|PORT_PUDR
mdefine_line|#define PORT_PUDR  &t;0xA405016EUL
DECL|macro|PORT_PVDR
mdefine_line|#define PORT_PVDR  &t;0xA4050170UL
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
DECL|macro|IRQ6_IRQ
mdefine_line|#define IRQ6_IRQ&t;38
DECL|macro|IRQ7_IRQ
mdefine_line|#define IRQ7_IRQ&t;39
DECL|macro|INTPRI00
mdefine_line|#define INTPRI00&t;0xA4140010UL
DECL|macro|IRQ0_IPR_ADDR
mdefine_line|#define IRQ0_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ1_IPR_ADDR
mdefine_line|#define IRQ1_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ2_IPR_ADDR
mdefine_line|#define IRQ2_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ3_IPR_ADDR
mdefine_line|#define IRQ3_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ4_IPR_ADDR
mdefine_line|#define IRQ4_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ5_IPR_ADDR
mdefine_line|#define IRQ5_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ6_IPR_ADDR
mdefine_line|#define IRQ6_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ7_IPR_ADDR
mdefine_line|#define IRQ7_IPR_ADDR&t;INTPRI00
DECL|macro|IRQ0_IPR_POS
mdefine_line|#define IRQ0_IPR_POS&t;7
DECL|macro|IRQ1_IPR_POS
mdefine_line|#define IRQ1_IPR_POS&t;6
DECL|macro|IRQ2_IPR_POS
mdefine_line|#define IRQ2_IPR_POS&t;5
DECL|macro|IRQ3_IPR_POS
mdefine_line|#define IRQ3_IPR_POS&t;4
DECL|macro|IRQ4_IPR_POS
mdefine_line|#define IRQ4_IPR_POS&t;3
DECL|macro|IRQ5_IPR_POS
mdefine_line|#define IRQ5_IPR_POS&t;2
DECL|macro|IRQ6_IPR_POS
mdefine_line|#define IRQ6_IPR_POS&t;1
DECL|macro|IRQ7_IPR_POS
mdefine_line|#define IRQ7_IPR_POS&t;0
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
DECL|macro|IRQ6_PRIORITY
mdefine_line|#define IRQ6_PRIORITY&t;1
DECL|macro|IRQ7_PRIORITY
mdefine_line|#define IRQ7_PRIORITY&t;1
r_extern
r_int
id|shmse_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|__irq_demux
mdefine_line|#define __irq_demux(irq) shmse_irq_demux(irq)
DECL|macro|irq_demux
mdefine_line|#define irq_demux(irq) __irq_demux(irq)
macro_line|#endif /* __ASM_SH_IRQ_SH73180_H */
eof
