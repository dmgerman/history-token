multiline_comment|/* include/asm-m68knommu/MC68328.h: &squot;328 control registers&n; *&n; * Copyright (C) 1999  Vladimir Gurevich &lt;vgurevic@cisco.com&gt;&n; *                     Bear &amp; Hare Software, Inc.&n; *&n; * Based on include/asm-m68knommu/MC68332.h&n; * Copyright (C) 1998  Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *&n; */
macro_line|#ifndef _MC68328_H_
DECL|macro|_MC68328_H_
mdefine_line|#define _MC68328_H_
DECL|macro|BYTE_REF
mdefine_line|#define BYTE_REF(addr) (*((volatile unsigned char*)addr))
DECL|macro|WORD_REF
mdefine_line|#define WORD_REF(addr) (*((volatile unsigned short*)addr))
DECL|macro|LONG_REF
mdefine_line|#define LONG_REF(addr) (*((volatile unsigned long*)addr))
DECL|macro|PUT_FIELD
mdefine_line|#define PUT_FIELD(field, val) (((val) &lt;&lt; field##_SHIFT) &amp; field##_MASK)
DECL|macro|GET_FIELD
mdefine_line|#define GET_FIELD(reg, field) (((reg) &amp; field##_MASK) &gt;&gt; field##_SHIFT)
multiline_comment|/********** &n; *&n; * 0xFFFFF0xx -- System Control&n; *&n; **********/
multiline_comment|/*&n; * System Control Register (SCR)&n; */
DECL|macro|SCR_ADDR
mdefine_line|#define SCR_ADDR&t;0xfffff000
DECL|macro|SCR
mdefine_line|#define SCR&t;&t;BYTE_REF(SCR_ADDR)
DECL|macro|SCR_WDTH8
mdefine_line|#define SCR_WDTH8&t;0x01&t;/* 8-Bit Width Select */
DECL|macro|SCR_DMAP
mdefine_line|#define SCR_DMAP&t;0x04&t;/* Double Map */
DECL|macro|SCR_SO
mdefine_line|#define SCR_SO&t;&t;0x08&t;/* Supervisor Only */
DECL|macro|SCR_BETEN
mdefine_line|#define SCR_BETEN&t;0x10&t;/* Bus-Error Time-Out Enable */
DECL|macro|SCR_PRV
mdefine_line|#define SCR_PRV&t;&t;0x20&t;/* Privilege Violation */
DECL|macro|SCR_WPV
mdefine_line|#define SCR_WPV&t;&t;0x40&t;/* Write Protect Violation */
DECL|macro|SCR_BETO
mdefine_line|#define SCR_BETO&t;0x80&t;/* Bus-Error TimeOut */
multiline_comment|/*&n; * Mask Revision Register&n; */
DECL|macro|MRR_ADDR
mdefine_line|#define MRR_ADDR 0xfffff004
DECL|macro|MRR
mdefine_line|#define MRR      LONG_REF(MRR_ADDR)
multiline_comment|/********** &n; *&n; * 0xFFFFF1xx -- Chip-Select logic&n; *&n; **********/
multiline_comment|/********** &n; *&n; * 0xFFFFF2xx -- Phase Locked Loop (PLL) &amp; Power Control&n; *&n; **********/
multiline_comment|/*&n; * Group Base Address Registers&n; */
DECL|macro|GRPBASEA_ADDR
mdefine_line|#define GRPBASEA_ADDR&t;0xfffff100
DECL|macro|GRPBASEB_ADDR
mdefine_line|#define GRPBASEB_ADDR&t;0xfffff102
DECL|macro|GRPBASEC_ADDR
mdefine_line|#define GRPBASEC_ADDR&t;0xfffff104
DECL|macro|GRPBASED_ADDR
mdefine_line|#define GRPBASED_ADDR&t;0xfffff106
DECL|macro|GRPBASEA
mdefine_line|#define GRPBASEA&t;WORD_REF(GRPBASEA_ADDR)
DECL|macro|GRPBASEB
mdefine_line|#define GRPBASEB&t;WORD_REF(GRPBASEB_ADDR)
DECL|macro|GRPBASEC
mdefine_line|#define GRPBASEC&t;WORD_REF(GRPBASEC_ADDR)
DECL|macro|GRPBASED
mdefine_line|#define GRPBASED&t;WORD_REF(GRPBASED_ADDR)
DECL|macro|GRPBASE_V
mdefine_line|#define GRPBASE_V&t;  0x0001&t;/* Valid */
DECL|macro|GRPBASE_GBA_MASK
mdefine_line|#define GRPBASE_GBA_MASK  0xfff0&t;/* Group Base Address (bits 31-20) */
multiline_comment|/*&n; * Group Base Address Mask Registers &n; */
DECL|macro|GRPMASKA_ADDR
mdefine_line|#define GRPMASKA_ADDR&t;0xfffff108
DECL|macro|GRPMASKB_ADDR
mdefine_line|#define GRPMASKB_ADDR&t;0xfffff10a
DECL|macro|GRPMASKC_ADDR
mdefine_line|#define GRPMASKC_ADDR&t;0xfffff10c
DECL|macro|GRPMASKD_ADDR
mdefine_line|#define GRPMASKD_ADDR&t;0xfffff10e
DECL|macro|GRPMASKA
mdefine_line|#define GRPMASKA&t;WORD_REF(GRPMASKA_ADDR)
DECL|macro|GRPMASKB
mdefine_line|#define GRPMASKB&t;WORD_REF(GRPMASKB_ADDR)
DECL|macro|GRPMASKC
mdefine_line|#define GRPMASKC&t;WORD_REF(GRPMASKC_ADDR)
DECL|macro|GRPMASKD
mdefine_line|#define GRPMASKD&t;WORD_REF(GRPMASKD_ADDR)
DECL|macro|GRMMASK_GMA_MASK
mdefine_line|#define GRMMASK_GMA_MASK 0xfffff0&t;/* Group Base Mask (bits 31-20) */
multiline_comment|/*&n; * Chip-Select Option Registers (group A)&n; */
DECL|macro|CSA0_ADDR
mdefine_line|#define CSA0_ADDR&t;0xfffff110
DECL|macro|CSA1_ADDR
mdefine_line|#define CSA1_ADDR&t;0xfffff114
DECL|macro|CSA2_ADDR
mdefine_line|#define CSA2_ADDR&t;0xfffff118
DECL|macro|CSA3_ADDR
mdefine_line|#define CSA3_ADDR&t;0xfffff11c
DECL|macro|CSA0
mdefine_line|#define CSA0&t;&t;LONG_REF(CSA0_ADDR)
DECL|macro|CSA1
mdefine_line|#define CSA1&t;&t;LONG_REF(CSA1_ADDR)
DECL|macro|CSA2
mdefine_line|#define CSA2&t;&t;LONG_REF(CSA2_ADDR)
DECL|macro|CSA3
mdefine_line|#define CSA3&t;&t;LONG_REF(CSA3_ADDR)
DECL|macro|CSA_WAIT_MASK
mdefine_line|#define CSA_WAIT_MASK&t;0x00000007&t;/* Wait State Selection */
DECL|macro|CSA_WAIT_SHIFT
mdefine_line|#define CSA_WAIT_SHIFT&t;0
DECL|macro|CSA_RO
mdefine_line|#define CSA_RO&t;&t;0x00000008&t;/* Read-Only */
DECL|macro|CSA_AM_MASK
mdefine_line|#define CSA_AM_MASK&t;0x0000ff00&t;/* Address Mask (bits 23-16) */
DECL|macro|CSA_AM_SHIFT
mdefine_line|#define CSA_AM_SHIFT&t;8
DECL|macro|CSA_BUSW
mdefine_line|#define CSA_BUSW&t;0x00010000&t;/* Bus Width Select */
DECL|macro|CSA_AC_MASK
mdefine_line|#define CSA_AC_MASK&t;0xff000000&t;/* Address Compare (bits 23-16) */
DECL|macro|CSA_AC_SHIFT
mdefine_line|#define CSA_AC_SHIFT&t;24
multiline_comment|/*&n; * Chip-Select Option Registers (group B)&n; */
DECL|macro|CSB0_ADDR
mdefine_line|#define CSB0_ADDR&t;0xfffff120
DECL|macro|CSB1_ADDR
mdefine_line|#define CSB1_ADDR&t;0xfffff124
DECL|macro|CSB2_ADDR
mdefine_line|#define CSB2_ADDR&t;0xfffff128
DECL|macro|CSB3_ADDR
mdefine_line|#define CSB3_ADDR&t;0xfffff12c
DECL|macro|CSB0
mdefine_line|#define CSB0&t;&t;LONG_REF(CSB0_ADDR)
DECL|macro|CSB1
mdefine_line|#define CSB1&t;&t;LONG_REF(CSB1_ADDR)
DECL|macro|CSB2
mdefine_line|#define CSB2&t;&t;LONG_REF(CSB2_ADDR)
DECL|macro|CSB3
mdefine_line|#define CSB3&t;&t;LONG_REF(CSB3_ADDR)
DECL|macro|CSB_WAIT_MASK
mdefine_line|#define CSB_WAIT_MASK&t;0x00000007&t;/* Wait State Selection */
DECL|macro|CSB_WAIT_SHIFT
mdefine_line|#define CSB_WAIT_SHIFT&t;0
DECL|macro|CSB_RO
mdefine_line|#define CSB_RO&t;&t;0x00000008&t;/* Read-Only */
DECL|macro|CSB_AM_MASK
mdefine_line|#define CSB_AM_MASK&t;0x0000ff00&t;/* Address Mask (bits 23-16) */
DECL|macro|CSB_AM_SHIFT
mdefine_line|#define CSB_AM_SHIFT&t;8
DECL|macro|CSB_BUSW
mdefine_line|#define CSB_BUSW&t;0x00010000&t;/* Bus Width Select */
DECL|macro|CSB_AC_MASK
mdefine_line|#define CSB_AC_MASK&t;0xff000000&t;/* Address Compare (bits 23-16) */
DECL|macro|CSB_AC_SHIFT
mdefine_line|#define CSB_AC_SHIFT&t;24
multiline_comment|/*&n; * Chip-Select Option Registers (group C)&n; */
DECL|macro|CSC0_ADDR
mdefine_line|#define CSC0_ADDR&t;0xfffff130
DECL|macro|CSC1_ADDR
mdefine_line|#define CSC1_ADDR&t;0xfffff134
DECL|macro|CSC2_ADDR
mdefine_line|#define CSC2_ADDR&t;0xfffff138
DECL|macro|CSC3_ADDR
mdefine_line|#define CSC3_ADDR&t;0xfffff13c
DECL|macro|CSC0
mdefine_line|#define CSC0&t;&t;LONG_REF(CSC0_ADDR)
DECL|macro|CSC1
mdefine_line|#define CSC1&t;&t;LONG_REF(CSC1_ADDR)
DECL|macro|CSC2
mdefine_line|#define CSC2&t;&t;LONG_REF(CSC2_ADDR)
DECL|macro|CSC3
mdefine_line|#define CSC3&t;&t;LONG_REF(CSC3_ADDR)
DECL|macro|CSC_WAIT_MASK
mdefine_line|#define CSC_WAIT_MASK&t;0x00000007&t;/* Wait State Selection */
DECL|macro|CSC_WAIT_SHIFT
mdefine_line|#define CSC_WAIT_SHIFT&t;0
DECL|macro|CSC_RO
mdefine_line|#define CSC_RO&t;&t;0x00000008&t;/* Read-Only */
DECL|macro|CSC_AM_MASK
mdefine_line|#define CSC_AM_MASK&t;0x0000fff0&t;/* Address Mask (bits 23-12) */
DECL|macro|CSC_AM_SHIFT
mdefine_line|#define CSC_AM_SHIFT&t;4
DECL|macro|CSC_BUSW
mdefine_line|#define CSC_BUSW&t;0x00010000&t;/* Bus Width Select */
DECL|macro|CSC_AC_MASK
mdefine_line|#define CSC_AC_MASK&t;0xfff00000&t;/* Address Compare (bits 23-12) */
DECL|macro|CSC_AC_SHIFT
mdefine_line|#define CSC_AC_SHIFT&t;20
multiline_comment|/*&n; * Chip-Select Option Registers (group D)&n; */
DECL|macro|CSD0_ADDR
mdefine_line|#define CSD0_ADDR&t;0xfffff140
DECL|macro|CSD1_ADDR
mdefine_line|#define CSD1_ADDR&t;0xfffff144
DECL|macro|CSD2_ADDR
mdefine_line|#define CSD2_ADDR&t;0xfffff148
DECL|macro|CSD3_ADDR
mdefine_line|#define CSD3_ADDR&t;0xfffff14c
DECL|macro|CSD0
mdefine_line|#define CSD0&t;&t;LONG_REF(CSD0_ADDR)
DECL|macro|CSD1
mdefine_line|#define CSD1&t;&t;LONG_REF(CSD1_ADDR)
DECL|macro|CSD2
mdefine_line|#define CSD2&t;&t;LONG_REF(CSD2_ADDR)
DECL|macro|CSD3
mdefine_line|#define CSD3&t;&t;LONG_REF(CSD3_ADDR)
DECL|macro|CSD_WAIT_MASK
mdefine_line|#define CSD_WAIT_MASK&t;0x00000007&t;/* Wait State Selection */
DECL|macro|CSD_WAIT_SHIFT
mdefine_line|#define CSD_WAIT_SHIFT&t;0
DECL|macro|CSD_RO
mdefine_line|#define CSD_RO&t;&t;0x00000008&t;/* Read-Only */
DECL|macro|CSD_AM_MASK
mdefine_line|#define CSD_AM_MASK&t;0x0000fff0&t;/* Address Mask (bits 23-12) */
DECL|macro|CSD_AM_SHIFT
mdefine_line|#define CSD_AM_SHIFT&t;4
DECL|macro|CSD_BUSW
mdefine_line|#define CSD_BUSW&t;0x00010000&t;/* Bus Width Select */
DECL|macro|CSD_AC_MASK
mdefine_line|#define CSD_AC_MASK&t;0xfff00000&t;/* Address Compare (bits 23-12) */
DECL|macro|CSD_AC_SHIFT
mdefine_line|#define CSD_AC_SHIFT&t;20
multiline_comment|/**********&n; *&n; * 0xFFFFF2xx -- Phase Locked Loop (PLL) &amp; Power Control&n; *&n; **********/
multiline_comment|/*&n; * PLL Control Register &n; */
DECL|macro|PLLCR_ADDR
mdefine_line|#define PLLCR_ADDR&t;0xfffff200
DECL|macro|PLLCR
mdefine_line|#define PLLCR&t;&t;WORD_REF(PLLCR_ADDR)
DECL|macro|PLLCR_DISPLL
mdefine_line|#define PLLCR_DISPLL&t;       0x0008&t;/* Disable PLL */
DECL|macro|PLLCR_CLKEN
mdefine_line|#define PLLCR_CLKEN&t;       0x0010&t;/* Clock (CLKO pin) enable */
DECL|macro|PLLCR_SYSCLK_SEL_MASK
mdefine_line|#define PLLCR_SYSCLK_SEL_MASK  0x0700&t;/* System Clock Selection */
DECL|macro|PLLCR_SYSCLK_SEL_SHIFT
mdefine_line|#define PLLCR_SYSCLK_SEL_SHIFT 8
DECL|macro|PLLCR_PIXCLK_SEL_MASK
mdefine_line|#define PLLCR_PIXCLK_SEL_MASK  0x3800&t;/* LCD Clock Selection */
DECL|macro|PLLCR_PIXCLK_SEL_SHIFT
mdefine_line|#define PLLCR_PIXCLK_SEL_SHIFT 11
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|PLLCR_LCDCLK_SEL_MASK
mdefine_line|#define PLLCR_LCDCLK_SEL_MASK&t;PLLCR_PIXCLK_SEL_MASK
DECL|macro|PLLCR_LCDCLK_SEL_SHIFT
mdefine_line|#define PLLCR_LCDCLK_SEL_SHIFT&t;PLLCR_PIXCLK_SEL_SHIFT
multiline_comment|/*&n; * PLL Frequency Select Register&n; */
DECL|macro|PLLFSR_ADDR
mdefine_line|#define PLLFSR_ADDR&t;0xfffff202
DECL|macro|PLLFSR
mdefine_line|#define PLLFSR&t;&t;WORD_REF(PLLFSR_ADDR)
DECL|macro|PLLFSR_PC_MASK
mdefine_line|#define PLLFSR_PC_MASK&t;0x00ff&t;&t;/* P Count */
DECL|macro|PLLFSR_PC_SHIFT
mdefine_line|#define PLLFSR_PC_SHIFT 0
DECL|macro|PLLFSR_QC_MASK
mdefine_line|#define PLLFSR_QC_MASK&t;0x0f00&t;&t;/* Q Count */
DECL|macro|PLLFSR_QC_SHIFT
mdefine_line|#define PLLFSR_QC_SHIFT 8
DECL|macro|PLLFSR_PROT
mdefine_line|#define PLLFSR_PROT&t;0x4000&t;&t;/* Protect P &amp; Q */
DECL|macro|PLLFSR_CLK32
mdefine_line|#define PLLFSR_CLK32&t;0x8000&t;&t;/* Clock 32 (kHz) */
multiline_comment|/*&n; * Power Control Register&n; */
DECL|macro|PCTRL_ADDR
mdefine_line|#define PCTRL_ADDR&t;0xfffff207
DECL|macro|PCTRL
mdefine_line|#define PCTRL&t;&t;BYTE_REF(PCTRL_ADDR)
DECL|macro|PCTRL_WIDTH_MASK
mdefine_line|#define PCTRL_WIDTH_MASK&t;0x1f&t;/* CPU Clock bursts width */
DECL|macro|PCTRL_WIDTH_SHIFT
mdefine_line|#define PCTRL_WIDTH_SHIFT&t;0
DECL|macro|PCTRL_STOP
mdefine_line|#define PCTRL_STOP&t;&t;0x40&t;/* Enter power-save mode immediately */ 
DECL|macro|PCTRL_PCEN
mdefine_line|#define PCTRL_PCEN&t;&t;0x80&t;/* Power Control Enable */
multiline_comment|/**********&n; *&n; * 0xFFFFF3xx -- Interrupt Controller&n; *&n; **********/
multiline_comment|/* &n; * Interrupt Vector Register&n; */
DECL|macro|IVR_ADDR
mdefine_line|#define IVR_ADDR&t;0xfffff300
DECL|macro|IVR
mdefine_line|#define IVR&t;&t;BYTE_REF(IVR_ADDR)
DECL|macro|IVR_VECTOR_MASK
mdefine_line|#define IVR_VECTOR_MASK 0xF8
multiline_comment|/*&n; * Interrupt control Register&n; */
DECL|macro|ICR_ADRR
mdefine_line|#define ICR_ADRR&t;0xfffff302
DECL|macro|ICR
mdefine_line|#define ICR&t;&t;WORD_REF(ICR_ADDR)
DECL|macro|ICR_ET6
mdefine_line|#define ICR_ET6&t;&t;0x0100&t;/* Edge Trigger Select for IRQ6 */
DECL|macro|ICR_ET3
mdefine_line|#define ICR_ET3&t;&t;0x0200&t;/* Edge Trigger Select for IRQ3 */
DECL|macro|ICR_ET2
mdefine_line|#define ICR_ET2&t;&t;0x0400&t;/* Edge Trigger Select for IRQ2 */
DECL|macro|ICR_ET1
mdefine_line|#define ICR_ET1&t;&t;0x0800&t;/* Edge Trigger Select for IRQ1 */
DECL|macro|ICR_POL6
mdefine_line|#define ICR_POL6&t;0x1000&t;/* Polarity Control for IRQ6 */
DECL|macro|ICR_POL3
mdefine_line|#define ICR_POL3&t;0x2000&t;/* Polarity Control for IRQ3 */
DECL|macro|ICR_POL2
mdefine_line|#define ICR_POL2&t;0x4000&t;/* Polarity Control for IRQ2 */
DECL|macro|ICR_POL1
mdefine_line|#define ICR_POL1&t;0x8000&t;/* Polarity Control for IRQ1 */
multiline_comment|/*&n; * Interrupt Mask Register&n; */
DECL|macro|IMR_ADDR
mdefine_line|#define IMR_ADDR&t;0xfffff304
DECL|macro|IMR
mdefine_line|#define IMR&t;&t;LONG_REF(IMR_ADDR)
multiline_comment|/*&n; * Define the names for bit positions first. This is useful for&n; * request_irq&n; */
DECL|macro|SPIM_IRQ_NUM
mdefine_line|#define SPIM_IRQ_NUM&t;0&t;/* SPI Master interrupt */
DECL|macro|TMR2_IRQ_NUM
mdefine_line|#define&t;TMR2_IRQ_NUM&t;1&t;/* Timer 2 interrupt */
DECL|macro|UART_IRQ_NUM
mdefine_line|#define UART_IRQ_NUM&t;2&t;/* UART interrupt */&t;
DECL|macro|WDT_IRQ_NUM
mdefine_line|#define&t;WDT_IRQ_NUM&t;3&t;/* Watchdog Timer interrupt */
DECL|macro|RTC_IRQ_NUM
mdefine_line|#define RTC_IRQ_NUM&t;4&t;/* RTC interrupt */
DECL|macro|KB_IRQ_NUM
mdefine_line|#define&t;KB_IRQ_NUM&t;6&t;/* Keyboard Interrupt */
DECL|macro|PWM_IRQ_NUM
mdefine_line|#define PWM_IRQ_NUM&t;7&t;/* Pulse-Width Modulator int. */
DECL|macro|INT0_IRQ_NUM
mdefine_line|#define&t;INT0_IRQ_NUM&t;8&t;/* External INT0 */
DECL|macro|INT1_IRQ_NUM
mdefine_line|#define&t;INT1_IRQ_NUM&t;9&t;/* External INT1 */
DECL|macro|INT2_IRQ_NUM
mdefine_line|#define&t;INT2_IRQ_NUM&t;10&t;/* External INT2 */
DECL|macro|INT3_IRQ_NUM
mdefine_line|#define&t;INT3_IRQ_NUM&t;11&t;/* External INT3 */
DECL|macro|INT4_IRQ_NUM
mdefine_line|#define&t;INT4_IRQ_NUM&t;12&t;/* External INT4 */
DECL|macro|INT5_IRQ_NUM
mdefine_line|#define&t;INT5_IRQ_NUM&t;13&t;/* External INT5 */
DECL|macro|INT6_IRQ_NUM
mdefine_line|#define&t;INT6_IRQ_NUM&t;14&t;/* External INT6 */
DECL|macro|INT7_IRQ_NUM
mdefine_line|#define&t;INT7_IRQ_NUM&t;15&t;/* External INT7 */
DECL|macro|IRQ1_IRQ_NUM
mdefine_line|#define IRQ1_IRQ_NUM&t;16&t;/* IRQ1 */
DECL|macro|IRQ2_IRQ_NUM
mdefine_line|#define IRQ2_IRQ_NUM&t;17&t;/* IRQ2 */
DECL|macro|IRQ3_IRQ_NUM
mdefine_line|#define IRQ3_IRQ_NUM&t;18&t;/* IRQ3 */
DECL|macro|IRQ6_IRQ_NUM
mdefine_line|#define IRQ6_IRQ_NUM&t;19&t;/* IRQ6 */
DECL|macro|PEN_IRQ_NUM
mdefine_line|#define PEN_IRQ_NUM&t;20&t;/* Pen Interrupt */
DECL|macro|SPIS_IRQ_NUM
mdefine_line|#define SPIS_IRQ_NUM&t;21&t;/* SPI Slave Interrupt */
DECL|macro|TMR1_IRQ_NUM
mdefine_line|#define TMR1_IRQ_NUM&t;22&t;/* Timer 1 interrupt */
DECL|macro|IRQ7_IRQ_NUM
mdefine_line|#define IRQ7_IRQ_NUM&t;23&t;/* IRQ7 */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|SPI_IRQ_NUM
mdefine_line|#define SPI_IRQ_NUM&t;SPIM_IRQ_NUM
DECL|macro|TMR_IRQ_NUM
mdefine_line|#define TMR_IRQ_NUM&t;TMR1_IRQ_NUM
multiline_comment|/*&n; * Here go the bitmasks themselves&n; */
DECL|macro|IMR_MSPIM
mdefine_line|#define IMR_MSPIM &t;(1 &lt;&lt; SPIM _IRQ_NUM)&t;/* Mask SPI Master interrupt */
DECL|macro|IMR_MTMR2
mdefine_line|#define&t;IMR_MTMR2&t;(1 &lt;&lt; TMR2_IRQ_NUM)&t;/* Mask Timer 2 interrupt */
DECL|macro|IMR_MUART
mdefine_line|#define IMR_MUART&t;(1 &lt;&lt; UART_IRQ_NUM)&t;/* Mask UART interrupt */&t;
DECL|macro|IMR_MWDT
mdefine_line|#define&t;IMR_MWDT&t;(1 &lt;&lt; WDT_IRQ_NUM)&t;/* Mask Watchdog Timer interrupt */
DECL|macro|IMR_MRTC
mdefine_line|#define IMR_MRTC&t;(1 &lt;&lt; RTC_IRQ_NUM)&t;/* Mask RTC interrupt */
DECL|macro|IMR_MKB
mdefine_line|#define&t;IMR_MKB&t;&t;(1 &lt;&lt; KB_IRQ_NUM)&t;/* Mask Keyboard Interrupt */
DECL|macro|IMR_MPWM
mdefine_line|#define IMR_MPWM&t;(1 &lt;&lt; PWM_IRQ_NUM)&t;/* Mask Pulse-Width Modulator int. */
DECL|macro|IMR_MINT0
mdefine_line|#define&t;IMR_MINT0&t;(1 &lt;&lt; INT0_IRQ_NUM)&t;/* Mask External INT0 */
DECL|macro|IMR_MINT1
mdefine_line|#define&t;IMR_MINT1&t;(1 &lt;&lt; INT1_IRQ_NUM)&t;/* Mask External INT1 */
DECL|macro|IMR_MINT2
mdefine_line|#define&t;IMR_MINT2&t;(1 &lt;&lt; INT2_IRQ_NUM)&t;/* Mask External INT2 */
DECL|macro|IMR_MINT3
mdefine_line|#define&t;IMR_MINT3&t;(1 &lt;&lt; INT3_IRQ_NUM)&t;/* Mask External INT3 */
DECL|macro|IMR_MINT4
mdefine_line|#define&t;IMR_MINT4&t;(1 &lt;&lt; INT4_IRQ_NUM)&t;/* Mask External INT4 */
DECL|macro|IMR_MINT5
mdefine_line|#define&t;IMR_MINT5&t;(1 &lt;&lt; INT5_IRQ_NUM)&t;/* Mask External INT5 */
DECL|macro|IMR_MINT6
mdefine_line|#define&t;IMR_MINT6&t;(1 &lt;&lt; INT6_IRQ_NUM)&t;/* Mask External INT6 */
DECL|macro|IMR_MINT7
mdefine_line|#define&t;IMR_MINT7&t;(1 &lt;&lt; INT7_IRQ_NUM)&t;/* Mask External INT7 */
DECL|macro|IMR_MIRQ1
mdefine_line|#define IMR_MIRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* Mask IRQ1 */
DECL|macro|IMR_MIRQ2
mdefine_line|#define IMR_MIRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* Mask IRQ2 */
DECL|macro|IMR_MIRQ3
mdefine_line|#define IMR_MIRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* Mask IRQ3 */
DECL|macro|IMR_MIRQ6
mdefine_line|#define IMR_MIRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* Mask IRQ6 */
DECL|macro|IMR_MPEN
mdefine_line|#define IMR_MPEN&t;(1 &lt;&lt; PEN_IRQ_NUM)&t;/* Mask Pen Interrupt */
DECL|macro|IMR_MSPIS
mdefine_line|#define IMR_MSPIS&t;(1 &lt;&lt; SPIS_IRQ_NUM)&t;/* Mask SPI Slave Interrupt */
DECL|macro|IMR_MTMR1
mdefine_line|#define IMR_MTMR1&t;(1 &lt;&lt; TMR1_IRQ_NUM)&t;/* Mask Timer 1 interrupt */
DECL|macro|IMR_MIRQ7
mdefine_line|#define IMR_MIRQ7&t;(1 &lt;&lt; IRQ7_IRQ_NUM)&t;/* Mask IRQ7 */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|IMR_MSPI
mdefine_line|#define IMR_MSPI&t;IMR_MSPIM
DECL|macro|IMR_MTMR
mdefine_line|#define IMR_MTMR&t;IMR_MTMR1
multiline_comment|/* &n; * Interrupt Wake-Up Enable Register&n; */
DECL|macro|IWR_ADDR
mdefine_line|#define IWR_ADDR&t;0xfffff308
DECL|macro|IWR
mdefine_line|#define IWR&t;&t;LONG_REF(IWR_ADDR)
DECL|macro|IWR_SPIM
mdefine_line|#define IWR_SPIM &t;(1 &lt;&lt; SPIM _IRQ_NUM)&t;/* SPI Master interrupt */
DECL|macro|IWR_TMR2
mdefine_line|#define&t;IWR_TMR2&t;(1 &lt;&lt; TMR2_IRQ_NUM)&t;/* Timer 2 interrupt */
DECL|macro|IWR_UART
mdefine_line|#define IWR_UART&t;(1 &lt;&lt; UART_IRQ_NUM)&t;/* UART interrupt */&t;
DECL|macro|IWR_WDT
mdefine_line|#define&t;IWR_WDT&t;&t;(1 &lt;&lt; WDT_IRQ_NUM)&t;/* Watchdog Timer interrupt */
DECL|macro|IWR_RTC
mdefine_line|#define IWR_RTC&t;&t;(1 &lt;&lt; RTC_IRQ_NUM)&t;/* RTC interrupt */
DECL|macro|IWR_KB
mdefine_line|#define&t;IWR_KB&t;&t;(1 &lt;&lt; KB_IRQ_NUM)&t;/* Keyboard Interrupt */
DECL|macro|IWR_PWM
mdefine_line|#define IWR_PWM&t;&t;(1 &lt;&lt; PWM_IRQ_NUM)&t;/* Pulse-Width Modulator int. */
DECL|macro|IWR_INT0
mdefine_line|#define&t;IWR_INT0&t;(1 &lt;&lt; INT0_IRQ_NUM)&t;/* External INT0 */
DECL|macro|IWR_INT1
mdefine_line|#define&t;IWR_INT1&t;(1 &lt;&lt; INT1_IRQ_NUM)&t;/* External INT1 */
DECL|macro|IWR_INT2
mdefine_line|#define&t;IWR_INT2&t;(1 &lt;&lt; INT2_IRQ_NUM)&t;/* External INT2 */
DECL|macro|IWR_INT3
mdefine_line|#define&t;IWR_INT3&t;(1 &lt;&lt; INT3_IRQ_NUM)&t;/* External INT3 */
DECL|macro|IWR_INT4
mdefine_line|#define&t;IWR_INT4&t;(1 &lt;&lt; INT4_IRQ_NUM)&t;/* External INT4 */
DECL|macro|IWR_INT5
mdefine_line|#define&t;IWR_INT5&t;(1 &lt;&lt; INT5_IRQ_NUM)&t;/* External INT5 */
DECL|macro|IWR_INT6
mdefine_line|#define&t;IWR_INT6&t;(1 &lt;&lt; INT6_IRQ_NUM)&t;/* External INT6 */
DECL|macro|IWR_INT7
mdefine_line|#define&t;IWR_INT7&t;(1 &lt;&lt; INT7_IRQ_NUM)&t;/* External INT7 */
DECL|macro|IWR_IRQ1
mdefine_line|#define IWR_IRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* IRQ1 */
DECL|macro|IWR_IRQ2
mdefine_line|#define IWR_IRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* IRQ2 */
DECL|macro|IWR_IRQ3
mdefine_line|#define IWR_IRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* IRQ3 */
DECL|macro|IWR_IRQ6
mdefine_line|#define IWR_IRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* IRQ6 */
DECL|macro|IWR_PEN
mdefine_line|#define IWR_PEN&t;&t;(1 &lt;&lt; PEN_IRQ_NUM)&t;/* Pen Interrupt */
DECL|macro|IWR_SPIS
mdefine_line|#define IWR_SPIS&t;(1 &lt;&lt; SPIS_IRQ_NUM)&t;/* SPI Slave Interrupt */
DECL|macro|IWR_TMR1
mdefine_line|#define IWR_TMR1&t;(1 &lt;&lt; TMR1_IRQ_NUM)&t;/* Timer 1 interrupt */
DECL|macro|IWR_IRQ7
mdefine_line|#define IWR_IRQ7&t;(1 &lt;&lt; IRQ7_IRQ_NUM)&t;/* IRQ7 */
multiline_comment|/* &n; * Interrupt Status Register &n; */
DECL|macro|ISR_ADDR
mdefine_line|#define ISR_ADDR&t;0xfffff30c
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;LONG_REF(ISR_ADDR)
DECL|macro|ISR_SPIM
mdefine_line|#define ISR_SPIM &t;(1 &lt;&lt; SPIM _IRQ_NUM)&t;/* SPI Master interrupt */
DECL|macro|ISR_TMR2
mdefine_line|#define&t;ISR_TMR2&t;(1 &lt;&lt; TMR2_IRQ_NUM)&t;/* Timer 2 interrupt */
DECL|macro|ISR_UART
mdefine_line|#define ISR_UART&t;(1 &lt;&lt; UART_IRQ_NUM)&t;/* UART interrupt */&t;
DECL|macro|ISR_WDT
mdefine_line|#define&t;ISR_WDT&t;&t;(1 &lt;&lt; WDT_IRQ_NUM)&t;/* Watchdog Timer interrupt */
DECL|macro|ISR_RTC
mdefine_line|#define ISR_RTC&t;&t;(1 &lt;&lt; RTC_IRQ_NUM)&t;/* RTC interrupt */
DECL|macro|ISR_KB
mdefine_line|#define&t;ISR_KB&t;&t;(1 &lt;&lt; KB_IRQ_NUM)&t;/* Keyboard Interrupt */
DECL|macro|ISR_PWM
mdefine_line|#define ISR_PWM&t;&t;(1 &lt;&lt; PWM_IRQ_NUM)&t;/* Pulse-Width Modulator int. */
DECL|macro|ISR_INT0
mdefine_line|#define&t;ISR_INT0&t;(1 &lt;&lt; INT0_IRQ_NUM)&t;/* External INT0 */
DECL|macro|ISR_INT1
mdefine_line|#define&t;ISR_INT1&t;(1 &lt;&lt; INT1_IRQ_NUM)&t;/* External INT1 */
DECL|macro|ISR_INT2
mdefine_line|#define&t;ISR_INT2&t;(1 &lt;&lt; INT2_IRQ_NUM)&t;/* External INT2 */
DECL|macro|ISR_INT3
mdefine_line|#define&t;ISR_INT3&t;(1 &lt;&lt; INT3_IRQ_NUM)&t;/* External INT3 */
DECL|macro|ISR_INT4
mdefine_line|#define&t;ISR_INT4&t;(1 &lt;&lt; INT4_IRQ_NUM)&t;/* External INT4 */
DECL|macro|ISR_INT5
mdefine_line|#define&t;ISR_INT5&t;(1 &lt;&lt; INT5_IRQ_NUM)&t;/* External INT5 */
DECL|macro|ISR_INT6
mdefine_line|#define&t;ISR_INT6&t;(1 &lt;&lt; INT6_IRQ_NUM)&t;/* External INT6 */
DECL|macro|ISR_INT7
mdefine_line|#define&t;ISR_INT7&t;(1 &lt;&lt; INT7_IRQ_NUM)&t;/* External INT7 */
DECL|macro|ISR_IRQ1
mdefine_line|#define ISR_IRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* IRQ1 */
DECL|macro|ISR_IRQ2
mdefine_line|#define ISR_IRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* IRQ2 */
DECL|macro|ISR_IRQ3
mdefine_line|#define ISR_IRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* IRQ3 */
DECL|macro|ISR_IRQ6
mdefine_line|#define ISR_IRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* IRQ6 */
DECL|macro|ISR_PEN
mdefine_line|#define ISR_PEN&t;&t;(1 &lt;&lt; PEN_IRQ_NUM)&t;/* Pen Interrupt */
DECL|macro|ISR_SPIS
mdefine_line|#define ISR_SPIS&t;(1 &lt;&lt; SPIS_IRQ_NUM)&t;/* SPI Slave Interrupt */
DECL|macro|ISR_TMR1
mdefine_line|#define ISR_TMR1&t;(1 &lt;&lt; TMR1_IRQ_NUM)&t;/* Timer 1 interrupt */
DECL|macro|ISR_IRQ7
mdefine_line|#define ISR_IRQ7&t;(1 &lt;&lt; IRQ7_IRQ_NUM)&t;/* IRQ7 */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|ISR_SPI
mdefine_line|#define ISR_SPI&t;ISR_SPIM
DECL|macro|ISR_TMR
mdefine_line|#define ISR_TMR&t;ISR_TMR1
multiline_comment|/* &n; * Interrupt Pending Register &n; */
DECL|macro|IPR_ADDR
mdefine_line|#define IPR_ADDR&t;0xfffff310
DECL|macro|IPR
mdefine_line|#define IPR&t;&t;LONG_REF(IPR_ADDR)
DECL|macro|IPR_SPIM
mdefine_line|#define IPR_SPIM &t;(1 &lt;&lt; SPIM _IRQ_NUM)&t;/* SPI Master interrupt */
DECL|macro|IPR_TMR2
mdefine_line|#define&t;IPR_TMR2&t;(1 &lt;&lt; TMR2_IRQ_NUM)&t;/* Timer 2 interrupt */
DECL|macro|IPR_UART
mdefine_line|#define IPR_UART&t;(1 &lt;&lt; UART_IRQ_NUM)&t;/* UART interrupt */&t;
DECL|macro|IPR_WDT
mdefine_line|#define&t;IPR_WDT&t;&t;(1 &lt;&lt; WDT_IRQ_NUM)&t;/* Watchdog Timer interrupt */
DECL|macro|IPR_RTC
mdefine_line|#define IPR_RTC&t;&t;(1 &lt;&lt; RTC_IRQ_NUM)&t;/* RTC interrupt */
DECL|macro|IPR_KB
mdefine_line|#define&t;IPR_KB&t;&t;(1 &lt;&lt; KB_IRQ_NUM)&t;/* Keyboard Interrupt */
DECL|macro|IPR_PWM
mdefine_line|#define IPR_PWM&t;&t;(1 &lt;&lt; PWM_IRQ_NUM)&t;/* Pulse-Width Modulator int. */
DECL|macro|IPR_INT0
mdefine_line|#define&t;IPR_INT0&t;(1 &lt;&lt; INT0_IRQ_NUM)&t;/* External INT0 */
DECL|macro|IPR_INT1
mdefine_line|#define&t;IPR_INT1&t;(1 &lt;&lt; INT1_IRQ_NUM)&t;/* External INT1 */
DECL|macro|IPR_INT2
mdefine_line|#define&t;IPR_INT2&t;(1 &lt;&lt; INT2_IRQ_NUM)&t;/* External INT2 */
DECL|macro|IPR_INT3
mdefine_line|#define&t;IPR_INT3&t;(1 &lt;&lt; INT3_IRQ_NUM)&t;/* External INT3 */
DECL|macro|IPR_INT4
mdefine_line|#define&t;IPR_INT4&t;(1 &lt;&lt; INT4_IRQ_NUM)&t;/* External INT4 */
DECL|macro|IPR_INT5
mdefine_line|#define&t;IPR_INT5&t;(1 &lt;&lt; INT5_IRQ_NUM)&t;/* External INT5 */
DECL|macro|IPR_INT6
mdefine_line|#define&t;IPR_INT6&t;(1 &lt;&lt; INT6_IRQ_NUM)&t;/* External INT6 */
DECL|macro|IPR_INT7
mdefine_line|#define&t;IPR_INT7&t;(1 &lt;&lt; INT7_IRQ_NUM)&t;/* External INT7 */
DECL|macro|IPR_IRQ1
mdefine_line|#define IPR_IRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* IRQ1 */
DECL|macro|IPR_IRQ2
mdefine_line|#define IPR_IRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* IRQ2 */
DECL|macro|IPR_IRQ3
mdefine_line|#define IPR_IRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* IRQ3 */
DECL|macro|IPR_IRQ6
mdefine_line|#define IPR_IRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* IRQ6 */
DECL|macro|IPR_PEN
mdefine_line|#define IPR_PEN&t;&t;(1 &lt;&lt; PEN_IRQ_NUM)&t;/* Pen Interrupt */
DECL|macro|IPR_SPIS
mdefine_line|#define IPR_SPIS&t;(1 &lt;&lt; SPIS_IRQ_NUM)&t;/* SPI Slave Interrupt */
DECL|macro|IPR_TMR1
mdefine_line|#define IPR_TMR1&t;(1 &lt;&lt; TMR1_IRQ_NUM)&t;/* Timer 1 interrupt */
DECL|macro|IPR_IRQ7
mdefine_line|#define IPR_IRQ7&t;(1 &lt;&lt; IRQ7_IRQ_NUM)&t;/* IRQ7 */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|IPR_SPI
mdefine_line|#define IPR_SPI&t;IPR_SPIM
DECL|macro|IPR_TMR
mdefine_line|#define IPR_TMR&t;IPR_TMR1
multiline_comment|/**********&n; *&n; * 0xFFFFF4xx -- Parallel Ports&n; *&n; **********/
multiline_comment|/*&n; * Port A&n; */
DECL|macro|PADIR_ADDR
mdefine_line|#define PADIR_ADDR&t;0xfffff400&t;&t;/* Port A direction reg */
DECL|macro|PADATA_ADDR
mdefine_line|#define PADATA_ADDR&t;0xfffff401&t;&t;/* Port A data register */
DECL|macro|PASEL_ADDR
mdefine_line|#define PASEL_ADDR&t;0xfffff403&t;&t;/* Port A Select register */
DECL|macro|PADIR
mdefine_line|#define PADIR&t;&t;BYTE_REF(PADIR_ADDR)
DECL|macro|PADATA
mdefine_line|#define PADATA&t;&t;BYTE_REF(PADATA_ADDR)
DECL|macro|PASEL
mdefine_line|#define PASEL&t;&t;BYTE_REF(PASEL_ADDR)
DECL|macro|PA
mdefine_line|#define PA(x)           (1 &lt;&lt; (x))
DECL|macro|PA_A
mdefine_line|#define PA_A(x)&t;&t;PA((x) - 16)&t;/* This is specific to PA only! */
DECL|macro|PA_A16
mdefine_line|#define PA_A16&t;&t;PA(0)&t;&t;/* Use A16 as PA(0) */
DECL|macro|PA_A17
mdefine_line|#define PA_A17&t;&t;PA(1)&t;&t;/* Use A17 as PA(1) */
DECL|macro|PA_A18
mdefine_line|#define PA_A18&t;&t;PA(2)&t;&t;/* Use A18 as PA(2) */
DECL|macro|PA_A19
mdefine_line|#define PA_A19&t;&t;PA(3)&t;&t;/* Use A19 as PA(3) */
DECL|macro|PA_A20
mdefine_line|#define PA_A20&t;&t;PA(4)&t;&t;/* Use A20 as PA(4) */
DECL|macro|PA_A21
mdefine_line|#define PA_A21&t;&t;PA(5)&t;&t;/* Use A21 as PA(5) */
DECL|macro|PA_A22
mdefine_line|#define PA_A22&t;&t;PA(6)&t;&t;/* Use A22 as PA(6) */
DECL|macro|PA_A23
mdefine_line|#define PA_A23&t;&t;PA(7)&t;&t;/* Use A23 as PA(7) */
multiline_comment|/* &n; * Port B&n; */
DECL|macro|PBDIR_ADDR
mdefine_line|#define PBDIR_ADDR&t;0xfffff408&t;&t;/* Port B direction reg */
DECL|macro|PBDATA_ADDR
mdefine_line|#define PBDATA_ADDR&t;0xfffff409&t;&t;/* Port B data register */
DECL|macro|PBSEL_ADDR
mdefine_line|#define PBSEL_ADDR&t;0xfffff40b&t;&t;/* Port B Select Register */
DECL|macro|PBDIR
mdefine_line|#define PBDIR&t;&t;BYTE_REF(PBDIR_ADDR)
DECL|macro|PBDATA
mdefine_line|#define PBDATA&t;&t;BYTE_REF(PBDATA_ADDR)
DECL|macro|PBSEL
mdefine_line|#define PBSEL&t;&t;BYTE_REF(PBSEL_ADDR)
DECL|macro|PB
mdefine_line|#define PB(x)           (1 &lt;&lt; (x))
DECL|macro|PB_D
mdefine_line|#define PB_D(x)&t;&t;PB(x)&t;&t;/* This is specific to port B only */
DECL|macro|PB_D0
mdefine_line|#define PB_D0&t;&t;PB(0)&t;&t;/* Use D0 as PB(0) */
DECL|macro|PB_D1
mdefine_line|#define PB_D1&t;&t;PB(1)&t;&t;/* Use D1 as PB(1) */
DECL|macro|PB_D2
mdefine_line|#define PB_D2&t;&t;PB(2)&t;&t;/* Use D2 as PB(2) */
DECL|macro|PB_D3
mdefine_line|#define PB_D3&t;&t;PB(3)&t;&t;/* Use D3 as PB(3) */
DECL|macro|PB_D4
mdefine_line|#define PB_D4&t;&t;PB(4)&t;&t;/* Use D4 as PB(4) */
DECL|macro|PB_D5
mdefine_line|#define PB_D5&t;&t;PB(5)&t;&t;/* Use D5 as PB(5) */
DECL|macro|PB_D6
mdefine_line|#define PB_D6&t;&t;PB(6)&t;&t;/* Use D6 as PB(6) */
DECL|macro|PB_D7
mdefine_line|#define PB_D7&t;&t;PB(7)&t;&t;/* Use D7 as PB(7) */
multiline_comment|/* &n; * Port C&n; */
DECL|macro|PCDIR_ADDR
mdefine_line|#define PCDIR_ADDR&t;0xfffff410&t;&t;/* Port C direction reg */
DECL|macro|PCDATA_ADDR
mdefine_line|#define PCDATA_ADDR&t;0xfffff411&t;&t;/* Port C data register */
DECL|macro|PCSEL_ADDR
mdefine_line|#define PCSEL_ADDR&t;0xfffff413&t;&t;/* Port C Select Register */
DECL|macro|PCDIR
mdefine_line|#define PCDIR&t;&t;BYTE_REF(PCDIR_ADDR)
DECL|macro|PCDATA
mdefine_line|#define PCDATA&t;&t;BYTE_REF(PCDATA_ADDR)
DECL|macro|PCSEL
mdefine_line|#define PCSEL&t;&t;BYTE_REF(PCSEL_ADDR)
DECL|macro|PC
mdefine_line|#define PC(x)           (1 &lt;&lt; (x))
DECL|macro|PC_WE
mdefine_line|#define PC_WE&t;&t;PC(6)&t;&t;/* Use WE    as PC(6) */
DECL|macro|PC_DTACK
mdefine_line|#define PC_DTACK&t;PC(5)&t;&t;/* Use DTACK as PC(5) */
DECL|macro|PC_IRQ7
mdefine_line|#define PC_IRQ7&t;&t;PC(4)&t;&t;/* Use IRQ7  as PC(4) */
DECL|macro|PC_LDS
mdefine_line|#define PC_LDS&t;&t;PC(2)&t;&t;/* Use LDS   as PC(2) */
DECL|macro|PC_UDS
mdefine_line|#define PC_UDS&t;&t;PC(1)&t;&t;/* Use UDS   as PC(1) */
DECL|macro|PC_MOCLK
mdefine_line|#define PC_MOCLK&t;PC(0)&t;&t;/* Use MOCLK as PC(0) */
multiline_comment|/* &n; * Port D&n; */
DECL|macro|PDDIR_ADDR
mdefine_line|#define PDDIR_ADDR&t;0xfffff418&t;&t;/* Port D direction reg */
DECL|macro|PDDATA_ADDR
mdefine_line|#define PDDATA_ADDR&t;0xfffff419&t;&t;/* Port D data register */
DECL|macro|PDPUEN_ADDR
mdefine_line|#define PDPUEN_ADDR&t;0xfffff41a&t;&t;/* Port D Pull-Up enable reg */
DECL|macro|PDPOL_ADDR
mdefine_line|#define PDPOL_ADDR&t;0xfffff41c&t;&t;/* Port D Polarity Register */
DECL|macro|PDIRQEN_ADDR
mdefine_line|#define PDIRQEN_ADDR&t;0xfffff41d&t;&t;/* Port D IRQ enable register */
DECL|macro|PDIQEG_ADDR
mdefine_line|#define&t;PDIQEG_ADDR&t;0xfffff41f&t;&t;/* Port D IRQ Edge Register */
DECL|macro|PDDIR
mdefine_line|#define PDDIR&t;&t;BYTE_REF(PDDIR_ADDR)
DECL|macro|PDDATA
mdefine_line|#define PDDATA&t;&t;BYTE_REF(PDDATA_ADDR)
DECL|macro|PDPUEN
mdefine_line|#define PDPUEN&t;&t;BYTE_REF(PDPUEN_ADDR)
DECL|macro|PDPOL
mdefine_line|#define&t;PDPOL&t;&t;BYTE_REF(PDPOL_ADDR)
DECL|macro|PDIRQEN
mdefine_line|#define PDIRQEN&t;&t;BYTE_REF(PDIRQEN_ADDR)
DECL|macro|PDIQEG
mdefine_line|#define PDIQEG&t;&t;BYTE_REF(PDIQEG_ADDR)
DECL|macro|PD
mdefine_line|#define PD(x)           (1 &lt;&lt; (x))
DECL|macro|PD_KB
mdefine_line|#define PD_KB(x)&t;PD(x)&t;&t;/* This is specific for Port D only */
DECL|macro|PD_KB0
mdefine_line|#define PD_KB0&t;&t;PD(0)&t;/* Use KB0 as PD(0) */
DECL|macro|PD_KB1
mdefine_line|#define PD_KB1&t;&t;PD(1)&t;/* Use KB1 as PD(1) */
DECL|macro|PD_KB2
mdefine_line|#define PD_KB2&t;&t;PD(2)&t;/* Use KB2 as PD(2) */
DECL|macro|PD_KB3
mdefine_line|#define PD_KB3&t;&t;PD(3)&t;/* Use KB3 as PD(3) */
DECL|macro|PD_KB4
mdefine_line|#define PD_KB4&t;&t;PD(4)&t;/* Use KB4 as PD(4) */
DECL|macro|PD_KB5
mdefine_line|#define PD_KB5&t;&t;PD(5)&t;/* Use KB5 as PD(5) */
DECL|macro|PD_KB6
mdefine_line|#define PD_KB6&t;&t;PD(6)&t;/* Use KB6 as PD(6) */
DECL|macro|PD_KB7
mdefine_line|#define PD_KB7&t;&t;PD(7)&t;/* Use KB7 as PD(7) */
multiline_comment|/* &n; * Port E&n; */
DECL|macro|PEDIR_ADDR
mdefine_line|#define PEDIR_ADDR&t;0xfffff420&t;&t;/* Port E direction reg */
DECL|macro|PEDATA_ADDR
mdefine_line|#define PEDATA_ADDR&t;0xfffff421&t;&t;/* Port E data register */
DECL|macro|PEPUEN_ADDR
mdefine_line|#define PEPUEN_ADDR&t;0xfffff422&t;&t;/* Port E Pull-Up enable reg */
DECL|macro|PESEL_ADDR
mdefine_line|#define PESEL_ADDR&t;0xfffff423&t;&t;/* Port E Select Register */
DECL|macro|PEDIR
mdefine_line|#define PEDIR&t;&t;BYTE_REF(PEDIR_ADDR)
DECL|macro|PEDATA
mdefine_line|#define PEDATA&t;&t;BYTE_REF(PEDATA_ADDR)
DECL|macro|PEPUEN
mdefine_line|#define PEPUEN&t;&t;BYTE_REF(PEPUEN_ADDR)
DECL|macro|PESEL
mdefine_line|#define PESEL&t;&t;BYTE_REF(PESEL_ADDR)
DECL|macro|PE
mdefine_line|#define PE(x)           (1 &lt;&lt; (x))
DECL|macro|PE_CSA1
mdefine_line|#define PE_CSA1&t;&t;PE(1)&t;/* Use CSA1 as PE(1) */
DECL|macro|PE_CSA2
mdefine_line|#define PE_CSA2&t;&t;PE(2)&t;/* Use CSA2 as PE(2) */
DECL|macro|PE_CSA3
mdefine_line|#define PE_CSA3&t;&t;PE(3)&t;/* Use CSA3 as PE(3) */
DECL|macro|PE_CSB0
mdefine_line|#define PE_CSB0&t;&t;PE(4)&t;/* Use CSB0 as PE(4) */
DECL|macro|PE_CSB1
mdefine_line|#define PE_CSB1&t;&t;PE(5)&t;/* Use CSB1 as PE(5) */
DECL|macro|PE_CSB2
mdefine_line|#define PE_CSB2&t;&t;PE(6)&t;/* Use CSB2 as PE(6) */
DECL|macro|PE_CSB3
mdefine_line|#define PE_CSB3&t;&t;PE(7)&t;/* Use CSB3 as PE(7) */
multiline_comment|/* &n; * Port F&n; */
DECL|macro|PFDIR_ADDR
mdefine_line|#define PFDIR_ADDR&t;0xfffff428&t;&t;/* Port F direction reg */
DECL|macro|PFDATA_ADDR
mdefine_line|#define PFDATA_ADDR&t;0xfffff429&t;&t;/* Port F data register */
DECL|macro|PFPUEN_ADDR
mdefine_line|#define PFPUEN_ADDR&t;0xfffff42a&t;&t;/* Port F Pull-Up enable reg */
DECL|macro|PFSEL_ADDR
mdefine_line|#define PFSEL_ADDR&t;0xfffff42b&t;&t;/* Port F Select Register */
DECL|macro|PFDIR
mdefine_line|#define PFDIR&t;&t;BYTE_REF(PFDIR_ADDR)
DECL|macro|PFDATA
mdefine_line|#define PFDATA&t;&t;BYTE_REF(PFDATA_ADDR)
DECL|macro|PFPUEN
mdefine_line|#define PFPUEN&t;&t;BYTE_REF(PFPUEN_ADDR)
DECL|macro|PFSEL
mdefine_line|#define PFSEL&t;&t;BYTE_REF(PFSEL_ADDR)
DECL|macro|PF
mdefine_line|#define PF(x)           (1 &lt;&lt; (x))
DECL|macro|PF_A
mdefine_line|#define PF_A(x)&t;&t;PF((x) - 24)&t;/* This is Port F specific only */
DECL|macro|PF_A24
mdefine_line|#define PF_A24&t;&t;PF(0)&t;/* Use A24 as PF(0) */
DECL|macro|PF_A25
mdefine_line|#define PF_A25&t;&t;PF(1)&t;/* Use A25 as PF(1) */
DECL|macro|PF_A26
mdefine_line|#define PF_A26&t;&t;PF(2)&t;/* Use A26 as PF(2) */
DECL|macro|PF_A27
mdefine_line|#define PF_A27&t;&t;PF(3)&t;/* Use A27 as PF(3) */
DECL|macro|PF_A28
mdefine_line|#define PF_A28&t;&t;PF(4)&t;/* Use A28 as PF(4) */
DECL|macro|PF_A29
mdefine_line|#define PF_A29&t;&t;PF(5)&t;/* Use A29 as PF(5) */
DECL|macro|PF_A30
mdefine_line|#define PF_A30&t;&t;PF(6)&t;/* Use A30 as PF(6) */
DECL|macro|PF_A31
mdefine_line|#define PF_A31&t;&t;PF(7)&t;/* Use A31 as PF(7) */
multiline_comment|/* &n; * Port G&n; */
DECL|macro|PGDIR_ADDR
mdefine_line|#define PGDIR_ADDR&t;0xfffff430&t;&t;/* Port G direction reg */
DECL|macro|PGDATA_ADDR
mdefine_line|#define PGDATA_ADDR&t;0xfffff431&t;&t;/* Port G data register */
DECL|macro|PGPUEN_ADDR
mdefine_line|#define PGPUEN_ADDR&t;0xfffff432&t;&t;/* Port G Pull-Up enable reg */
DECL|macro|PGSEL_ADDR
mdefine_line|#define PGSEL_ADDR&t;0xfffff433&t;&t;/* Port G Select Register */
DECL|macro|PGDIR
mdefine_line|#define PGDIR&t;&t;BYTE_REF(PGDIR_ADDR)
DECL|macro|PGDATA
mdefine_line|#define PGDATA&t;&t;BYTE_REF(PGDATA_ADDR)
DECL|macro|PGPUEN
mdefine_line|#define PGPUEN&t;&t;BYTE_REF(PGPUEN_ADDR)
DECL|macro|PGSEL
mdefine_line|#define PGSEL&t;&t;BYTE_REF(PGSEL_ADDR)
DECL|macro|PG
mdefine_line|#define PG(x)           (1 &lt;&lt; (x))
DECL|macro|PG_UART_TXD
mdefine_line|#define PG_UART_TXD&t;PG(0)&t;/* Use UART_TXD as PG(0) */
DECL|macro|PG_UART_RXD
mdefine_line|#define PG_UART_RXD&t;PG(1)&t;/* Use UART_RXD as PG(1) */
DECL|macro|PG_PWMOUT
mdefine_line|#define PG_PWMOUT&t;PG(2)&t;/* Use PWMOUT   as PG(2) */
DECL|macro|PG_TOUT2
mdefine_line|#define PG_TOUT2&t;PG(3)   /* Use TOUT2    as PG(3) */
DECL|macro|PG_TIN2
mdefine_line|#define PG_TIN2&t;&t;PG(4)&t;/* Use TIN2     as PG(4) */
DECL|macro|PG_TOUT1
mdefine_line|#define PG_TOUT1&t;PG(5)   /* Use TOUT1    as PG(5) */
DECL|macro|PG_TIN1
mdefine_line|#define PG_TIN1&t;&t;PG(6)&t;/* Use TIN1     as PG(6) */
DECL|macro|PG_RTCOUT
mdefine_line|#define PG_RTCOUT&t;PG(7)&t;/* Use RTCOUT   as PG(7) */
multiline_comment|/* &n; * Port J&n; */
DECL|macro|PJDIR_ADDR
mdefine_line|#define PJDIR_ADDR&t;0xfffff438&t;&t;/* Port J direction reg */
DECL|macro|PJDATA_ADDR
mdefine_line|#define PJDATA_ADDR&t;0xfffff439&t;&t;/* Port J data register */
DECL|macro|PJSEL_ADDR
mdefine_line|#define PJSEL_ADDR&t;0xfffff43b&t;&t;/* Port J Select Register */
DECL|macro|PJDIR
mdefine_line|#define PJDIR&t;&t;BYTE_REF(PJDIR_ADDR)
DECL|macro|PJDATA
mdefine_line|#define PJDATA&t;&t;BYTE_REF(PJDATA_ADDR)
DECL|macro|PJSEL
mdefine_line|#define PJSEL&t;&t;BYTE_REF(PJSEL_ADDR)
DECL|macro|PJ
mdefine_line|#define PJ(x)           (1 &lt;&lt; (x)) 
DECL|macro|PJ_CSD3
mdefine_line|#define PJ_CSD3&t;&t;PJ(7)&t;/* Use CSD3 as PJ(7) */
multiline_comment|/* &n; * Port K&n; */
DECL|macro|PKDIR_ADDR
mdefine_line|#define PKDIR_ADDR&t;0xfffff440&t;&t;/* Port K direction reg */
DECL|macro|PKDATA_ADDR
mdefine_line|#define PKDATA_ADDR&t;0xfffff441&t;&t;/* Port K data register */
DECL|macro|PKPUEN_ADDR
mdefine_line|#define PKPUEN_ADDR&t;0xfffff442&t;&t;/* Port K Pull-Up enable reg */
DECL|macro|PKSEL_ADDR
mdefine_line|#define PKSEL_ADDR&t;0xfffff443&t;&t;/* Port K Select Register */
DECL|macro|PKDIR
mdefine_line|#define PKDIR&t;&t;BYTE_REF(PKDIR_ADDR)
DECL|macro|PKDATA
mdefine_line|#define PKDATA&t;&t;BYTE_REF(PKDATA_ADDR)
DECL|macro|PKPUEN
mdefine_line|#define PKPUEN&t;&t;BYTE_REF(PKPUEN_ADDR)
DECL|macro|PKSEL
mdefine_line|#define PKSEL&t;&t;BYTE_REF(PKSEL_ADDR)
DECL|macro|PK
mdefine_line|#define PK(x)           (1 &lt;&lt; (x))
multiline_comment|/* &n; * Port M&n; */
DECL|macro|PMDIR_ADDR
mdefine_line|#define PMDIR_ADDR&t;0xfffff438&t;&t;/* Port M direction reg */
DECL|macro|PMDATA_ADDR
mdefine_line|#define PMDATA_ADDR&t;0xfffff439&t;&t;/* Port M data register */
DECL|macro|PMPUEN_ADDR
mdefine_line|#define PMPUEN_ADDR&t;0xfffff43a&t;&t;/* Port M Pull-Up enable reg */
DECL|macro|PMSEL_ADDR
mdefine_line|#define PMSEL_ADDR&t;0xfffff43b&t;&t;/* Port M Select Register */
DECL|macro|PMDIR
mdefine_line|#define PMDIR&t;&t;BYTE_REF(PMDIR_ADDR)
DECL|macro|PMDATA
mdefine_line|#define PMDATA&t;&t;BYTE_REF(PMDATA_ADDR)
DECL|macro|PMPUEN
mdefine_line|#define PMPUEN&t;&t;BYTE_REF(PMPUEN_ADDR)
DECL|macro|PMSEL
mdefine_line|#define PMSEL&t;&t;BYTE_REF(PMSEL_ADDR)
DECL|macro|PM
mdefine_line|#define PM(x)           (1 &lt;&lt; (x))
multiline_comment|/**********&n; *&n; * 0xFFFFF5xx -- Pulse-Width Modulator (PWM)&n; *&n; **********/
multiline_comment|/*&n; * PWM Control Register &n; */
DECL|macro|PWMC_ADDR
mdefine_line|#define PWMC_ADDR&t;0xfffff500
DECL|macro|PWMC
mdefine_line|#define PWMC&t;&t;WORD_REF(PWMC_ADDR)
DECL|macro|PWMC_CLKSEL_MASK
mdefine_line|#define PWMC_CLKSEL_MASK&t;0x0007&t;/* Clock Selection */
DECL|macro|PWMC_CLKSEL_SHIFT
mdefine_line|#define PWMC_CLKSEL_SHIFT&t;0
DECL|macro|PWMC_PWMEN
mdefine_line|#define PWMC_PWMEN&t;&t;0x0010&t;/* Enable PWM */
DECL|macro|PMNC_POL
mdefine_line|#define PMNC_POL&t;&t;0x0020&t;/* PWM Output Bit Polarity */
DECL|macro|PWMC_PIN
mdefine_line|#define PWMC_PIN&t;&t;0x0080&t;/* Current PWM output pin status */
DECL|macro|PWMC_LOAD
mdefine_line|#define PWMC_LOAD&t;&t;0x0100&t;/* Force a new period */
DECL|macro|PWMC_IRQEN
mdefine_line|#define PWMC_IRQEN&t;&t;0x4000&t;/* Interrupt Request Enable */
DECL|macro|PWMC_CLKSRC
mdefine_line|#define PWMC_CLKSRC&t;&t;0x8000&t;/* Clock Source Select */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|PWMC_EN
mdefine_line|#define PWMC_EN&t;PWMC_PWMEN
multiline_comment|/*&n; * PWM Period Register&n; */
DECL|macro|PWMP_ADDR
mdefine_line|#define PWMP_ADDR&t;0xfffff502
DECL|macro|PWMP
mdefine_line|#define PWMP&t;&t;WORD_REF(PWMP_ADDR)
multiline_comment|/* &n; * PWM Width Register &n; */
DECL|macro|PWMW_ADDR
mdefine_line|#define PWMW_ADDR&t;0xfffff504
DECL|macro|PWMW
mdefine_line|#define PWMW&t;&t;WORD_REF(PWMW_ADDR)
multiline_comment|/*&n; * PWM Counter Register&n; */
DECL|macro|PWMCNT_ADDR
mdefine_line|#define PWMCNT_ADDR&t;0xfffff506
DECL|macro|PWMCNT
mdefine_line|#define PWMCNT&t;&t;WORD_REF(PWMCNT_ADDR)
multiline_comment|/**********&n; *&n; * 0xFFFFF6xx -- General-Purpose Timers&n; *&n; **********/
multiline_comment|/* &n; * Timer Unit 1 and 2 Control Registers&n; */
DECL|macro|TCTL1_ADDR
mdefine_line|#define TCTL1_ADDR&t;0xfffff600
DECL|macro|TCTL1
mdefine_line|#define TCTL1&t;&t;WORD_REF(TCTL1_ADDR)
DECL|macro|TCTL2_ADDR
mdefine_line|#define TCTL2_ADDR&t;0xfffff60c
DECL|macro|TCTL2
mdefine_line|#define TCTL2&t;&t;WORD_REF(TCTL2_ADDR)
DECL|macro|TCTL_TEN
mdefine_line|#define&t;TCTL_TEN&t;&t;0x0001&t;/* Timer Enable  */
DECL|macro|TCTL_CLKSOURCE_MASK
mdefine_line|#define TCTL_CLKSOURCE_MASK &t;0x000e&t;/* Clock Source: */
DECL|macro|TCTL_CLKSOURCE_STOP
mdefine_line|#define   TCTL_CLKSOURCE_STOP&t;   0x0000&t;/* Stop count (disabled)    */
DECL|macro|TCTL_CLKSOURCE_SYSCLK
mdefine_line|#define   TCTL_CLKSOURCE_SYSCLK&t;   0x0002&t;/* SYSCLK to prescaler      */
DECL|macro|TCTL_CLKSOURCE_SYSCLK_16
mdefine_line|#define   TCTL_CLKSOURCE_SYSCLK_16 0x0004&t;/* SYSCLK/16 to prescaler   */
DECL|macro|TCTL_CLKSOURCE_TIN
mdefine_line|#define   TCTL_CLKSOURCE_TIN&t;   0x0006&t;/* TIN to prescaler         */
DECL|macro|TCTL_CLKSOURCE_32KHZ
mdefine_line|#define   TCTL_CLKSOURCE_32KHZ&t;   0x0008&t;/* 32kHz clock to prescaler */
DECL|macro|TCTL_IRQEN
mdefine_line|#define TCTL_IRQEN&t;&t;0x0010&t;/* IRQ Enable    */
DECL|macro|TCTL_OM
mdefine_line|#define TCTL_OM&t;&t;&t;0x0020&t;/* Output Mode   */
DECL|macro|TCTL_CAP_MASK
mdefine_line|#define TCTL_CAP_MASK&t;&t;0x00c0&t;/* Capture Edge: */
DECL|macro|TCTL_CAP_RE
mdefine_line|#define&t;  TCTL_CAP_RE&t;&t;0x0040&t;&t;/* Capture on rizing edge   */
DECL|macro|TCTL_CAP_FE
mdefine_line|#define   TCTL_CAP_FE&t;&t;0x0080&t;&t;/* Capture on falling edge  */
DECL|macro|TCTL_FRR
mdefine_line|#define TCTL_FRR&t;&t;0x0010&t;/* Free-Run Mode */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|TCTL_ADDR
mdefine_line|#define TCTL_ADDR&t;TCTL1_ADDR
DECL|macro|TCTL
mdefine_line|#define TCTL&t;&t;TCTL1
multiline_comment|/*&n; * Timer Unit 1 and 2 Prescaler Registers&n; */
DECL|macro|TPRER1_ADDR
mdefine_line|#define TPRER1_ADDR&t;0xfffff602
DECL|macro|TPRER1
mdefine_line|#define TPRER1&t;&t;WORD_REF(TPRER1_ADDR)
DECL|macro|TPRER2_ADDR
mdefine_line|#define TPRER2_ADDR&t;0xfffff60e
DECL|macro|TPRER2
mdefine_line|#define TPRER2&t;&t;WORD_REF(TPRER2_ADDR)
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|TPRER_ADDR
mdefine_line|#define TPRER_ADDR&t;TPRER1_ADDR
DECL|macro|TPRER
mdefine_line|#define TPRER&t;&t;TPRER1
multiline_comment|/*&n; * Timer Unit 1 and 2 Compare Registers&n; */
DECL|macro|TCMP1_ADDR
mdefine_line|#define TCMP1_ADDR&t;0xfffff604
DECL|macro|TCMP1
mdefine_line|#define TCMP1&t;&t;WORD_REF(TCMP1_ADDR)
DECL|macro|TCMP2_ADDR
mdefine_line|#define TCMP2_ADDR&t;0xfffff610
DECL|macro|TCMP2
mdefine_line|#define TCMP2&t;&t;WORD_REF(TCMP2_ADDR)
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|TCMP_ADDR
mdefine_line|#define TCMP_ADDR&t;TCMP1_ADDR
DECL|macro|TCMP
mdefine_line|#define TCMP&t;&t;TCMP1
multiline_comment|/*&n; * Timer Unit 1 and 2 Capture Registers&n; */
DECL|macro|TCR1_ADDR
mdefine_line|#define TCR1_ADDR&t;0xfffff606
DECL|macro|TCR1
mdefine_line|#define TCR1&t;&t;WORD_REF(TCR1_ADDR)
DECL|macro|TCR2_ADDR
mdefine_line|#define TCR2_ADDR&t;0xfffff612
DECL|macro|TCR2
mdefine_line|#define TCR2&t;&t;WORD_REF(TCR2_ADDR)
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|TCR_ADDR
mdefine_line|#define TCR_ADDR&t;TCR1_ADDR
DECL|macro|TCR
mdefine_line|#define TCR&t;&t;TCR1
multiline_comment|/*&n; * Timer Unit 1 and 2 Counter Registers&n; */
DECL|macro|TCN1_ADDR
mdefine_line|#define TCN1_ADDR&t;0xfffff608
DECL|macro|TCN1
mdefine_line|#define TCN1&t;&t;WORD_REF(TCN1_ADDR)
DECL|macro|TCN2_ADDR
mdefine_line|#define TCN2_ADDR&t;0xfffff614
DECL|macro|TCN2
mdefine_line|#define TCN2&t;&t;WORD_REF(TCN2_ADDR)
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|TCN_ADDR
mdefine_line|#define TCN_ADDR&t;TCN1_ADDR
DECL|macro|TCN
mdefine_line|#define TCN&t;&t;TCN
multiline_comment|/*&n; * Timer Unit 1 and 2 Status Registers&n; */
DECL|macro|TSTAT1_ADDR
mdefine_line|#define TSTAT1_ADDR&t;0xfffff60a
DECL|macro|TSTAT1
mdefine_line|#define TSTAT1&t;&t;WORD_REF(TSTAT1_ADDR)
DECL|macro|TSTAT2_ADDR
mdefine_line|#define TSTAT2_ADDR&t;0xfffff616
DECL|macro|TSTAT2
mdefine_line|#define TSTAT2&t;&t;WORD_REF(TSTAT2_ADDR)
DECL|macro|TSTAT_COMP
mdefine_line|#define TSTAT_COMP&t;0x0001&t;&t;/* Compare Event occurred */
DECL|macro|TSTAT_CAPT
mdefine_line|#define TSTAT_CAPT&t;0x0001&t;&t;/* Capture Event occurred */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|TSTAT_ADDR
mdefine_line|#define TSTAT_ADDR&t;TSTAT1_ADDR
DECL|macro|TSTAT
mdefine_line|#define TSTAT&t;&t;TSTAT1
multiline_comment|/*&n; * Watchdog Compare Register &n; */
DECL|macro|WRR_ADDR
mdefine_line|#define WRR_ADDR&t;0xfffff61a
DECL|macro|WRR
mdefine_line|#define WRR&t;&t;WORD_REF(WRR_ADDR)
multiline_comment|/*&n; * Watchdog Counter Register &n; */
DECL|macro|WCN_ADDR
mdefine_line|#define WCN_ADDR&t;0xfffff61c
DECL|macro|WCN
mdefine_line|#define WCN&t;&t;WORD_REF(WCN_ADDR)
multiline_comment|/*&n; * Watchdog Control and Status Register&n; */
DECL|macro|WCSR_ADDR
mdefine_line|#define WCSR_ADDR&t;0xfffff618
DECL|macro|WCSR
mdefine_line|#define WCSR&t;&t;WORD_REF(WCSR_ADDR)
DECL|macro|WCSR_WDEN
mdefine_line|#define WCSR_WDEN&t;0x0001&t;/* Watchdog Enable */
DECL|macro|WCSR_FI
mdefine_line|#define WCSR_FI&t;&t;0x0002&t;/* Forced Interrupt (instead of SW reset)*/
DECL|macro|WCSR_WRST
mdefine_line|#define WCSR_WRST&t;0x0004&t;/* Watchdog Reset */
multiline_comment|/**********&n; *&n; * 0xFFFFF7xx -- Serial Periferial Interface Slave (SPIS)&n; *&n; **********/
multiline_comment|/*&n; * SPI Slave Register&n; */
DECL|macro|SPISR_ADDR
mdefine_line|#define SPISR_ADDR&t;0xfffff700
DECL|macro|SPISR
mdefine_line|#define SPISR&t;&t;WORD_REF(SPISR_ADDR)
DECL|macro|SPISR_DATA_ADDR
mdefine_line|#define SPISR_DATA_ADDR&t;0xfffff701
DECL|macro|SPISR_DATA
mdefine_line|#define SPISR_DATA&t;BYTE_REF(SPISR_DATA_ADDR)
DECL|macro|SPISR_DATA_MASK
mdefine_line|#define SPISR_DATA_MASK&t; 0x00ff&t;/* Shifted data from the external device */
DECL|macro|SPISR_DATA_SHIFT
mdefine_line|#define SPISR_DATA_SHIFT 0
DECL|macro|SPISR_SPISEN
mdefine_line|#define SPISR_SPISEN&t; 0x0100&t;/* SPIS module enable */
DECL|macro|SPISR_POL
mdefine_line|#define SPISR_POL&t; 0x0200&t;/* SPSCLK polarity control */
DECL|macro|SPISR_PHA
mdefine_line|#define SPISR_PHA&t; 0x0400&t;/* Phase relationship between SPSCLK &amp; SPSRxD */
DECL|macro|SPISR_OVWR
mdefine_line|#define SPISR_OVWR&t; 0x0800&t;/* Data buffer has been overwritten */
DECL|macro|SPISR_DATARDY
mdefine_line|#define SPISR_DATARDY&t; 0x1000&t;/* Data ready */
DECL|macro|SPISR_ENPOL
mdefine_line|#define SPISR_ENPOL&t; 0x2000&t;/* Enable Polarity */
DECL|macro|SPISR_IRQEN
mdefine_line|#define SPISR_IRQEN&t; 0x4000&t;/* SPIS IRQ Enable */
DECL|macro|SPISR_SPISIRQ
mdefine_line|#define SPISR_SPISIRQ&t; 0x8000&t;/* SPIS IRQ posted */
multiline_comment|/**********&n; *&n; * 0xFFFFF8xx -- Serial Periferial Interface Master (SPIM)&n; *&n; **********/
multiline_comment|/*&n; * SPIM Data Register&n; */
DECL|macro|SPIMDATA_ADDR
mdefine_line|#define SPIMDATA_ADDR&t;0xfffff800
DECL|macro|SPIMDATA
mdefine_line|#define SPIMDATA&t;WORD_REF(SPIMDATA_ADDR)
multiline_comment|/*&n; * SPIM Control/Status Register&n; */
DECL|macro|SPIMCONT_ADDR
mdefine_line|#define SPIMCONT_ADDR&t;0xfffff802
DECL|macro|SPIMCONT
mdefine_line|#define SPIMCONT&t;WORD_REF(SPIMCONT_ADDR)
DECL|macro|SPIMCONT_BIT_COUNT_MASK
mdefine_line|#define SPIMCONT_BIT_COUNT_MASK&t; 0x000f&t;/* Transfer Length in Bytes */
DECL|macro|SPIMCONT_BIT_COUNT_SHIFT
mdefine_line|#define SPIMCONT_BIT_COUNT_SHIFT 0
DECL|macro|SPIMCONT_POL
mdefine_line|#define SPIMCONT_POL&t;&t; 0x0010&t;/* SPMCLK Signel Polarity */
DECL|macro|SPIMCONT_PHA
mdefine_line|#define&t;SPIMCONT_PHA&t;&t; 0x0020&t;/* Clock/Data phase relationship */
DECL|macro|SPIMCONT_IRQEN
mdefine_line|#define SPIMCONT_IRQEN&t;&t; 0x0040 /* IRQ Enable */
DECL|macro|SPIMCONT_SPIMIRQ
mdefine_line|#define SPIMCONT_SPIMIRQ&t; 0x0080&t;/* Interrupt Request */
DECL|macro|SPIMCONT_XCH
mdefine_line|#define SPIMCONT_XCH&t;&t; 0x0100&t;/* Exchange */
DECL|macro|SPIMCONT_RSPIMEN
mdefine_line|#define SPIMCONT_RSPIMEN&t; 0x0200&t;/* Enable SPIM */
DECL|macro|SPIMCONT_DATA_RATE_MASK
mdefine_line|#define SPIMCONT_DATA_RATE_MASK&t; 0xe000&t;/* SPIM Data Rate */
DECL|macro|SPIMCONT_DATA_RATE_SHIFT
mdefine_line|#define SPIMCONT_DATA_RATE_SHIFT 13
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|SPIMCONT_IRQ
mdefine_line|#define SPIMCONT_IRQ&t;SPIMCONT_SPIMIRQ
DECL|macro|SPIMCONT_ENABLE
mdefine_line|#define SPIMCONT_ENABLE&t;SPIMCONT_SPIMEN
multiline_comment|/**********&n; *&n; * 0xFFFFF9xx -- UART&n; *&n; **********/
multiline_comment|/*&n; * UART Status/Control Register&n; */
DECL|macro|USTCNT_ADDR
mdefine_line|#define USTCNT_ADDR&t;0xfffff900
DECL|macro|USTCNT
mdefine_line|#define USTCNT&t;&t;WORD_REF(USTCNT_ADDR)
DECL|macro|USTCNT_TXAVAILEN
mdefine_line|#define USTCNT_TXAVAILEN&t;0x0001&t;/* Transmitter Available Int Enable */
DECL|macro|USTCNT_TXHALFEN
mdefine_line|#define USTCNT_TXHALFEN&t;&t;0x0002&t;/* Transmitter Half Empty Int Enable */
DECL|macro|USTCNT_TXEMPTYEN
mdefine_line|#define USTCNT_TXEMPTYEN&t;0x0004&t;/* Transmitter Empty Int Enable */
DECL|macro|USTCNT_RXREADYEN
mdefine_line|#define USTCNT_RXREADYEN&t;0x0008&t;/* Receiver Ready Interrupt Enable */
DECL|macro|USTCNT_RXHALFEN
mdefine_line|#define USTCNT_RXHALFEN&t;&t;0x0010&t;/* Receiver Half-Full Int Enable */
DECL|macro|USTCNT_RXFULLEN
mdefine_line|#define USTCNT_RXFULLEN&t;&t;0x0020&t;/* Receiver Full Interrupt Enable */
DECL|macro|USTCNT_CTSDELTAEN
mdefine_line|#define USTCNT_CTSDELTAEN&t;0x0040&t;/* CTS Delta Interrupt Enable */
DECL|macro|USTCNT_GPIODELTAEN
mdefine_line|#define USTCNT_GPIODELTAEN&t;0x0080&t;/* Old Data Interrupt Enable */
DECL|macro|USTCNT_8_7
mdefine_line|#define USTCNT_8_7&t;&t;0x0100&t;/* Eight or seven-bit transmission */
DECL|macro|USTCNT_STOP
mdefine_line|#define USTCNT_STOP&t;&t;0x0200&t;/* Stop bit transmission */
DECL|macro|USTCNT_ODD_EVEN
mdefine_line|#define USTCNT_ODD_EVEN&t;&t;0x0400&t;/* Odd Parity */
DECL|macro|USTCNT_PARITYEN
mdefine_line|#define&t;USTCNT_PARITYEN&t;&t;0x0800&t;/* Parity Enable */
DECL|macro|USTCNT_CLKMODE
mdefine_line|#define USTCNT_CLKMODE&t;&t;0x1000&t;/* Clock Mode Select */
DECL|macro|USTCNT_TXEN
mdefine_line|#define&t;USTCNT_TXEN&t;&t;0x2000&t;/* Transmitter Enable */
DECL|macro|USTCNT_RXEN
mdefine_line|#define USTCNT_RXEN&t;&t;0x4000&t;/* Receiver Enable */
DECL|macro|USTCNT_UARTEN
mdefine_line|#define USTCNT_UARTEN&t;&t;0x8000&t;/* UART Enable */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|USTCNT_TXAE
mdefine_line|#define USTCNT_TXAE&t;USTCNT_TXAVAILEN 
DECL|macro|USTCNT_TXHE
mdefine_line|#define USTCNT_TXHE&t;USTCNT_TXHALFEN
DECL|macro|USTCNT_TXEE
mdefine_line|#define USTCNT_TXEE&t;USTCNT_TXEMPTYEN
DECL|macro|USTCNT_RXRE
mdefine_line|#define USTCNT_RXRE&t;USTCNT_RXREADYEN
DECL|macro|USTCNT_RXHE
mdefine_line|#define USTCNT_RXHE&t;USTCNT_RXHALFEN
DECL|macro|USTCNT_RXFE
mdefine_line|#define USTCNT_RXFE&t;USTCNT_RXFULLEN
DECL|macro|USTCNT_CTSD
mdefine_line|#define USTCNT_CTSD&t;USTCNT_CTSDELTAEN
DECL|macro|USTCNT_ODD
mdefine_line|#define USTCNT_ODD&t;USTCNT_ODD_EVEN
DECL|macro|USTCNT_PEN
mdefine_line|#define USTCNT_PEN&t;USTCNT_PARITYEN
DECL|macro|USTCNT_CLKM
mdefine_line|#define USTCNT_CLKM&t;USTCNT_CLKMODE
DECL|macro|USTCNT_UEN
mdefine_line|#define USTCNT_UEN&t;USTCNT_UARTEN
multiline_comment|/*&n; * UART Baud Control Register&n; */
DECL|macro|UBAUD_ADDR
mdefine_line|#define UBAUD_ADDR&t;0xfffff902
DECL|macro|UBAUD
mdefine_line|#define UBAUD&t;&t;WORD_REF(UBAUD_ADDR)
DECL|macro|UBAUD_PRESCALER_MASK
mdefine_line|#define UBAUD_PRESCALER_MASK&t;0x003f&t;/* Actual divisor is 65 - PRESCALER */
DECL|macro|UBAUD_PRESCALER_SHIFT
mdefine_line|#define UBAUD_PRESCALER_SHIFT&t;0
DECL|macro|UBAUD_DIVIDE_MASK
mdefine_line|#define UBAUD_DIVIDE_MASK&t;0x0700&t;/* Baud Rate freq. divizor */
DECL|macro|UBAUD_DIVIDE_SHIFT
mdefine_line|#define UBAUD_DIVIDE_SHIFT&t;8
DECL|macro|UBAUD_BAUD_SRC
mdefine_line|#define UBAUD_BAUD_SRC&t;&t;0x0800&t;/* Baud Rate Source */
DECL|macro|UBAUD_GPIOSRC
mdefine_line|#define UBAUD_GPIOSRC&t;&t;0x1000&t;/* GPIO source */
DECL|macro|UBAUD_GPIODIR
mdefine_line|#define UBAUD_GPIODIR&t;&t;0x2000&t;/* GPIO Direction */
DECL|macro|UBAUD_GPIO
mdefine_line|#define UBAUD_GPIO&t;&t;0x4000&t;/* Current GPIO pin status */
DECL|macro|UBAUD_GPIODELTA
mdefine_line|#define UBAUD_GPIODELTA&t;&t;0x8000&t;/* GPIO pin value changed */
multiline_comment|/*&n; * UART Receiver Register &n; */
DECL|macro|URX_ADDR
mdefine_line|#define URX_ADDR&t;0xfffff904
DECL|macro|URX
mdefine_line|#define URX&t;&t;WORD_REF(URX_ADDR)
DECL|macro|URX_RXDATA_ADDR
mdefine_line|#define URX_RXDATA_ADDR&t;0xfffff905
DECL|macro|URX_RXDATA
mdefine_line|#define URX_RXDATA&t;BYTE_REF(URX_RXDATA_ADDR)
DECL|macro|URX_RXDATA_MASK
mdefine_line|#define URX_RXDATA_MASK&t; 0x00ff&t;/* Received data */
DECL|macro|URX_RXDATA_SHIFT
mdefine_line|#define URX_RXDATA_SHIFT 0
DECL|macro|URX_PARITY_ERROR
mdefine_line|#define URX_PARITY_ERROR 0x0100&t;/* Parity Error */
DECL|macro|URX_BREAK
mdefine_line|#define URX_BREAK&t; 0x0200&t;/* Break Detected */
DECL|macro|URX_FRAME_ERROR
mdefine_line|#define URX_FRAME_ERROR&t; 0x0400&t;/* Framing Error */
DECL|macro|URX_OVRUN
mdefine_line|#define URX_OVRUN&t; 0x0800&t;/* Serial Overrun */
DECL|macro|URX_DATA_READY
mdefine_line|#define URX_DATA_READY&t; 0x2000&t;/* Data Ready (FIFO not empty) */
DECL|macro|URX_FIFO_HALF
mdefine_line|#define URX_FIFO_HALF&t; 0x4000 /* FIFO is Half-Full */
DECL|macro|URX_FIFO_FULL
mdefine_line|#define URX_FIFO_FULL&t; 0x8000&t;/* FIFO is Full */
multiline_comment|/*&n; * UART Transmitter Register &n; */
DECL|macro|UTX_ADDR
mdefine_line|#define UTX_ADDR&t;0xfffff906
DECL|macro|UTX
mdefine_line|#define UTX&t;&t;WORD_REF(UTX_ADDR)
DECL|macro|UTX_TXDATA_ADDR
mdefine_line|#define UTX_TXDATA_ADDR&t;0xfffff907
DECL|macro|UTX_TXDATA
mdefine_line|#define UTX_TXDATA&t;BYTE_REF(UTX_TXDATA_ADDR)
DECL|macro|UTX_TXDATA_MASK
mdefine_line|#define UTX_TXDATA_MASK&t; 0x00ff&t;/* Data to be transmitted */
DECL|macro|UTX_TXDATA_SHIFT
mdefine_line|#define UTX_TXDATA_SHIFT 0
DECL|macro|UTX_CTS_DELTA
mdefine_line|#define UTX_CTS_DELTA&t; 0x0100&t;/* CTS changed */
DECL|macro|UTX_CTS_STATUS
mdefine_line|#define UTX_CTS_STATUS&t; 0x0200&t;/* CTS State */
DECL|macro|UTX_IGNORE_CTS
mdefine_line|#define&t;UTX_IGNORE_CTS&t; 0x0800&t;/* Ignore CTS */
DECL|macro|UTX_SEND_BREAK
mdefine_line|#define UTX_SEND_BREAK&t; 0x1000&t;/* Send a BREAK */
DECL|macro|UTX_TX_AVAIL
mdefine_line|#define UTX_TX_AVAIL&t; 0x2000&t;/* Transmit FIFO has a slot available */
DECL|macro|UTX_FIFO_HALF
mdefine_line|#define UTX_FIFO_HALF&t; 0x4000&t;/* Transmit FIFO is half empty */
DECL|macro|UTX_FIFO_EMPTY
mdefine_line|#define UTX_FIFO_EMPTY&t; 0x8000&t;/* Transmit FIFO is empty */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|UTX_CTS_STAT
mdefine_line|#define UTX_CTS_STAT&t;UTX_CTS_STATUS
DECL|macro|UTX_NOCTS
mdefine_line|#define UTX_NOCTS&t;UTX_IGNORE_CTS
multiline_comment|/*&n; * UART Miscellaneous Register &n; */
DECL|macro|UMISC_ADDR
mdefine_line|#define UMISC_ADDR&t;0xfffff908
DECL|macro|UMISC
mdefine_line|#define UMISC&t;&t;WORD_REF(UMISC_ADDR)
DECL|macro|UMISC_TX_POL
mdefine_line|#define UMISC_TX_POL&t; 0x0004&t;/* Transmit Polarity */
DECL|macro|UMISC_RX_POL
mdefine_line|#define UMISC_RX_POL&t; 0x0008&t;/* Receive Polarity */
DECL|macro|UMISC_IRDA_LOOP
mdefine_line|#define UMISC_IRDA_LOOP&t; 0x0010&t;/* IrDA Loopback Enable */
DECL|macro|UMISC_IRDA_EN
mdefine_line|#define UMISC_IRDA_EN&t; 0x0020&t;/* Infra-Red Enable */
DECL|macro|UMISC_RTS
mdefine_line|#define UMISC_RTS&t; 0x0040&t;/* Set RTS status */
DECL|macro|UMISC_RTSCONT
mdefine_line|#define UMISC_RTSCONT&t; 0x0080&t;/* Choose RTS control */
DECL|macro|UMISC_LOOP
mdefine_line|#define UMISC_LOOP&t; 0x1000&t;/* Serial Loopback Enable */
DECL|macro|UMISC_FORCE_PERR
mdefine_line|#define UMISC_FORCE_PERR 0x2000&t;/* Force Parity Error */
DECL|macro|UMISC_CLKSRC
mdefine_line|#define UMISC_CLKSRC&t; 0x4000&t;/* Clock Source */
multiline_comment|/* generalization of uart control registers to support multiple ports: */
r_typedef
r_volatile
r_struct
(brace
DECL|member|ustcnt
r_volatile
r_int
r_int
r_int
id|ustcnt
suffix:semicolon
DECL|member|ubaud
r_volatile
r_int
r_int
r_int
id|ubaud
suffix:semicolon
r_union
(brace
DECL|member|w
r_volatile
r_int
r_int
r_int
id|w
suffix:semicolon
r_struct
(brace
DECL|member|status
r_volatile
r_int
r_char
id|status
suffix:semicolon
DECL|member|rxdata
r_volatile
r_int
r_char
id|rxdata
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|member|urx
)brace
id|urx
suffix:semicolon
r_union
(brace
DECL|member|w
r_volatile
r_int
r_int
r_int
id|w
suffix:semicolon
r_struct
(brace
DECL|member|status
r_volatile
r_int
r_char
id|status
suffix:semicolon
DECL|member|txdata
r_volatile
r_int
r_char
id|txdata
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|member|utx
)brace
id|utx
suffix:semicolon
DECL|member|umisc
r_volatile
r_int
r_int
r_int
id|umisc
suffix:semicolon
DECL|member|pad1
r_volatile
r_int
r_int
r_int
id|pad1
suffix:semicolon
DECL|member|pad2
r_volatile
r_int
r_int
r_int
id|pad2
suffix:semicolon
DECL|member|pad3
r_volatile
r_int
r_int
r_int
id|pad3
suffix:semicolon
DECL|typedef|m68328_uart
)brace
id|m68328_uart
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/**********&n; *&n; * 0xFFFFFAxx -- LCD Controller&n; *&n; **********/
multiline_comment|/*&n; * LCD Screen Starting Address Register &n; */
DECL|macro|LSSA_ADDR
mdefine_line|#define LSSA_ADDR&t;0xfffffa00
DECL|macro|LSSA
mdefine_line|#define LSSA&t;&t;LONG_REF(LSSA_ADDR)
DECL|macro|LSSA_SSA_MASK
mdefine_line|#define LSSA_SSA_MASK&t;0xfffffffe&t;/* Bit 0 is reserved */
multiline_comment|/*&n; * LCD Virtual Page Width Register &n; */
DECL|macro|LVPW_ADDR
mdefine_line|#define LVPW_ADDR&t;0xfffffa05
DECL|macro|LVPW
mdefine_line|#define LVPW&t;&t;BYTE_REF(LVPW_ADDR)
multiline_comment|/*&n; * LCD Screen Width Register (not compatible with &squot;EZ328 !!!)&n; */
DECL|macro|LXMAX_ADDR
mdefine_line|#define LXMAX_ADDR&t;0xfffffa08
DECL|macro|LXMAX
mdefine_line|#define LXMAX&t;&t;WORD_REF(LXMAX_ADDR)
DECL|macro|LXMAX_XM_MASK
mdefine_line|#define LXMAX_XM_MASK&t;0x02ff&t;&t;/* Bits 0-3 are reserved */
multiline_comment|/*&n; * LCD Screen Height Register&n; */
DECL|macro|LYMAX_ADDR
mdefine_line|#define LYMAX_ADDR&t;0xfffffa0a
DECL|macro|LYMAX
mdefine_line|#define LYMAX&t;&t;WORD_REF(LYMAX_ADDR)
DECL|macro|LYMAX_YM_MASK
mdefine_line|#define LYMAX_YM_MASK&t;0x02ff&t;&t;/* Bits 10-15 are reserved */
multiline_comment|/*&n; * LCD Cursor X Position Register&n; */
DECL|macro|LCXP_ADDR
mdefine_line|#define LCXP_ADDR&t;0xfffffa18
DECL|macro|LCXP
mdefine_line|#define LCXP&t;&t;WORD_REF(LCXP_ADDR)
DECL|macro|LCXP_CC_MASK
mdefine_line|#define LCXP_CC_MASK&t;0xc000&t;&t;/* Cursor Control */
DECL|macro|LCXP_CC_TRAMSPARENT
mdefine_line|#define   LCXP_CC_TRAMSPARENT&t;0x0000
DECL|macro|LCXP_CC_BLACK
mdefine_line|#define   LCXP_CC_BLACK&t;&t;0x4000
DECL|macro|LCXP_CC_REVERSED
mdefine_line|#define   LCXP_CC_REVERSED&t;0x8000
DECL|macro|LCXP_CC_WHITE
mdefine_line|#define   LCXP_CC_WHITE&t;&t;0xc000
DECL|macro|LCXP_CXP_MASK
mdefine_line|#define LCXP_CXP_MASK&t;0x02ff&t;&t;/* Cursor X position */
multiline_comment|/*&n; * LCD Cursor Y Position Register&n; */
DECL|macro|LCYP_ADDR
mdefine_line|#define LCYP_ADDR&t;0xfffffa1a
DECL|macro|LCYP
mdefine_line|#define LCYP&t;&t;WORD_REF(LCYP_ADDR)
DECL|macro|LCYP_CYP_MASK
mdefine_line|#define LCYP_CYP_MASK&t;0x01ff&t;&t;/* Cursor Y Position */
multiline_comment|/*&n; * LCD Cursor Width and Heigth Register&n; */
DECL|macro|LCWCH_ADDR
mdefine_line|#define LCWCH_ADDR&t;0xfffffa1c
DECL|macro|LCWCH
mdefine_line|#define LCWCH&t;&t;WORD_REF(LCWCH_ADDR)
DECL|macro|LCWCH_CH_MASK
mdefine_line|#define LCWCH_CH_MASK&t;0x001f&t;&t;/* Cursor Height */
DECL|macro|LCWCH_CH_SHIFT
mdefine_line|#define LCWCH_CH_SHIFT&t;0
DECL|macro|LCWCH_CW_MASK
mdefine_line|#define LCWCH_CW_MASK&t;0x1f00&t;&t;/* Cursor Width */
DECL|macro|LCWCH_CW_SHIFT
mdefine_line|#define LCWCH_CW_SHIFT&t;8
multiline_comment|/*&n; * LCD Blink Control Register&n; */
DECL|macro|LBLKC_ADDR
mdefine_line|#define LBLKC_ADDR&t;0xfffffa1f
DECL|macro|LBLKC
mdefine_line|#define LBLKC&t;&t;BYTE_REF(LBLKC_ADDR)
DECL|macro|LBLKC_BD_MASK
mdefine_line|#define LBLKC_BD_MASK&t;0x7f&t;/* Blink Divisor */
DECL|macro|LBLKC_BD_SHIFT
mdefine_line|#define LBLKC_BD_SHIFT&t;0
DECL|macro|LBLKC_BKEN
mdefine_line|#define LBLKC_BKEN&t;0x80&t;/* Blink Enabled */
multiline_comment|/*&n; * LCD Panel Interface Configuration Register &n; */
DECL|macro|LPICF_ADDR
mdefine_line|#define LPICF_ADDR&t;0xfffffa20
DECL|macro|LPICF
mdefine_line|#define LPICF&t;&t;BYTE_REF(LPICF_ADDR)
DECL|macro|LPICF_GS_MASK
mdefine_line|#define LPICF_GS_MASK&t; 0x01&t; /* Gray-Scale Mode */
DECL|macro|LPICF_GS_BW
mdefine_line|#define&t;  LPICF_GS_BW&t;   0x00
DECL|macro|LPICF_GS_GRAY_4
mdefine_line|#define   LPICF_GS_GRAY_4  0x01
DECL|macro|LPICF_PBSIZ_MASK
mdefine_line|#define LPICF_PBSIZ_MASK 0x06&t;/* Panel Bus Width */
DECL|macro|LPICF_PBSIZ_1
mdefine_line|#define   LPICF_PBSIZ_1&t;   0x00
DECL|macro|LPICF_PBSIZ_2
mdefine_line|#define   LPICF_PBSIZ_2    0x02
DECL|macro|LPICF_PBSIZ_4
mdefine_line|#define   LPICF_PBSIZ_4    0x04
multiline_comment|/*&n; * LCD Polarity Configuration Register &n; */
DECL|macro|LPOLCF_ADDR
mdefine_line|#define LPOLCF_ADDR&t;0xfffffa21
DECL|macro|LPOLCF
mdefine_line|#define LPOLCF&t;&t;BYTE_REF(LPOLCF_ADDR)
DECL|macro|LPOLCF_PIXPOL
mdefine_line|#define LPOLCF_PIXPOL&t;0x01&t;/* Pixel Polarity */
DECL|macro|LPOLCF_LPPOL
mdefine_line|#define LPOLCF_LPPOL&t;0x02&t;/* Line Pulse Polarity */
DECL|macro|LPOLCF_FLMPOL
mdefine_line|#define LPOLCF_FLMPOL&t;0x04&t;/* Frame Marker Polarity */
DECL|macro|LPOLCF_LCKPOL
mdefine_line|#define LPOLCF_LCKPOL&t;0x08&t;/* LCD Shift Lock Polarity */
multiline_comment|/*&n; * LACD (LCD Alternate Crystal Direction) Rate Control Register&n; */
DECL|macro|LACDRC_ADDR
mdefine_line|#define LACDRC_ADDR&t;0xfffffa23
DECL|macro|LACDRC
mdefine_line|#define LACDRC&t;&t;BYTE_REF(LACDRC_ADDR)
DECL|macro|LACDRC_ACD_MASK
mdefine_line|#define LACDRC_ACD_MASK&t; 0x0f&t;/* Alternate Crystal Direction Control */
DECL|macro|LACDRC_ACD_SHIFT
mdefine_line|#define LACDRC_ACD_SHIFT 0
multiline_comment|/*&n; * LCD Pixel Clock Divider Register&n; */
DECL|macro|LPXCD_ADDR
mdefine_line|#define LPXCD_ADDR&t;0xfffffa25
DECL|macro|LPXCD
mdefine_line|#define LPXCD&t;&t;BYTE_REF(LPXCD_ADDR)
DECL|macro|LPXCD_PCD_MASK
mdefine_line|#define&t;LPXCD_PCD_MASK&t;0x3f &t;/* Pixel Clock Divider */
DECL|macro|LPXCD_PCD_SHIFT
mdefine_line|#define LPXCD_PCD_SHIFT&t;0
multiline_comment|/*&n; * LCD Clocking Control Register&n; */
DECL|macro|LCKCON_ADDR
mdefine_line|#define LCKCON_ADDR&t;0xfffffa27
DECL|macro|LCKCON
mdefine_line|#define LCKCON&t;&t;BYTE_REF(LCKCON_ADDR)
DECL|macro|LCKCON_PCDS
mdefine_line|#define LCKCON_PCDS&t; 0x01&t;/* Pixel Clock Divider Source Select */
DECL|macro|LCKCON_DWIDTH
mdefine_line|#define LCKCON_DWIDTH&t; 0x02&t;/* Display Memory Width  */
DECL|macro|LCKCON_DWS_MASK
mdefine_line|#define LCKCON_DWS_MASK&t; 0x3c&t;/* Display Wait-State */
DECL|macro|LCKCON_DWS_SHIFT
mdefine_line|#define LCKCON_DWS_SHIFT 2
DECL|macro|LCKCON_DMA16
mdefine_line|#define LCKCON_DMA16&t; 0x40&t;/* DMA burst length */
DECL|macro|LCKCON_LCDON
mdefine_line|#define LCKCON_LCDON&t; 0x80&t;/* Enable LCD Controller */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|LCKCON_DW_MASK
mdefine_line|#define LCKCON_DW_MASK&t;LCKCON_DWS_MASK
DECL|macro|LCKCON_DW_SHIFT
mdefine_line|#define LCKCON_DW_SHIFT&t;LCKCON_DWS_SHIFT
multiline_comment|/*&n; * LCD Last Buffer Address Register&n; */
DECL|macro|LLBAR_ADDR
mdefine_line|#define LLBAR_ADDR&t;0xfffffa29
DECL|macro|LLBAR
mdefine_line|#define LLBAR&t;&t;BYTE_REF(LLBAR_ADDR)
DECL|macro|LLBAR_LBAR_MASK
mdefine_line|#define LLBAR_LBAR_MASK&t; 0x7f&t;/* Number of memory words to fill 1 line */
DECL|macro|LLBAR_LBAR_SHIFT
mdefine_line|#define LLBAR_LBAR_SHIFT 0
multiline_comment|/*&n; * LCD Octet Terminal Count Register &n; */
DECL|macro|LOTCR_ADDR
mdefine_line|#define LOTCR_ADDR&t;0xfffffa2b
DECL|macro|LOTCR
mdefine_line|#define LOTCR&t;&t;BYTE_REF(LOTCR_ADDR)
multiline_comment|/*&n; * LCD Panning Offset Register&n; */
DECL|macro|LPOSR_ADDR
mdefine_line|#define LPOSR_ADDR&t;0xfffffa2d
DECL|macro|LPOSR
mdefine_line|#define LPOSR&t;&t;BYTE_REF(LPOSR_ADDR)
DECL|macro|LPOSR_BOS
mdefine_line|#define LPOSR_BOS&t;0x08&t;/* Byte offset (for B/W mode only */
DECL|macro|LPOSR_POS_MASK
mdefine_line|#define LPOSR_POS_MASK&t;0x07&t;/* Pixel Offset Code */
DECL|macro|LPOSR_POS_SHIFT
mdefine_line|#define LPOSR_POS_SHIFT&t;0
multiline_comment|/*&n; * LCD Frame Rate Control Modulation Register&n; */
DECL|macro|LFRCM_ADDR
mdefine_line|#define LFRCM_ADDR&t;0xfffffa31
DECL|macro|LFRCM
mdefine_line|#define LFRCM&t;&t;BYTE_REF(LFRCM_ADDR)
DECL|macro|LFRCM_YMOD_MASK
mdefine_line|#define LFRCM_YMOD_MASK&t; 0x0f&t;/* Vertical Modulation */
DECL|macro|LFRCM_YMOD_SHIFT
mdefine_line|#define LFRCM_YMOD_SHIFT 0
DECL|macro|LFRCM_XMOD_MASK
mdefine_line|#define LFRCM_XMOD_MASK&t; 0xf0&t;/* Horizontal Modulation */
DECL|macro|LFRCM_XMOD_SHIFT
mdefine_line|#define LFRCM_XMOD_SHIFT 4
multiline_comment|/*&n; * LCD Gray Palette Mapping Register&n; */
DECL|macro|LGPMR_ADDR
mdefine_line|#define LGPMR_ADDR&t;0xfffffa32
DECL|macro|LGPMR
mdefine_line|#define LGPMR&t;&t;WORD_REF(LGPMR_ADDR)
DECL|macro|LGPMR_GLEVEL3_MASK
mdefine_line|#define LGPMR_GLEVEL3_MASK&t;0x000f
DECL|macro|LGPMR_GLEVEL3_SHIFT
mdefine_line|#define LGPMR_GLEVEL3_SHIFT&t;0 
DECL|macro|LGPMR_GLEVEL2_MASK
mdefine_line|#define LGPMR_GLEVEL2_MASK&t;0x00f0
DECL|macro|LGPMR_GLEVEL2_SHIFT
mdefine_line|#define LGPMR_GLEVEL2_SHIFT&t;4 
DECL|macro|LGPMR_GLEVEL0_MASK
mdefine_line|#define LGPMR_GLEVEL0_MASK&t;0x0f00
DECL|macro|LGPMR_GLEVEL0_SHIFT
mdefine_line|#define LGPMR_GLEVEL0_SHIFT&t;8 
DECL|macro|LGPMR_GLEVEL1_MASK
mdefine_line|#define LGPMR_GLEVEL1_MASK&t;0xf000
DECL|macro|LGPMR_GLEVEL1_SHIFT
mdefine_line|#define LGPMR_GLEVEL1_SHIFT&t;12
multiline_comment|/**********&n; *&n; * 0xFFFFFBxx -- Real-Time Clock (RTC)&n; *&n; **********/
multiline_comment|/*&n; * RTC Hours Minutes and Seconds Register&n; */
DECL|macro|RTCTIME_ADDR
mdefine_line|#define RTCTIME_ADDR&t;0xfffffb00
DECL|macro|RTCTIME
mdefine_line|#define RTCTIME&t;&t;LONG_REF(RTCTIME_ADDR)
DECL|macro|RTCTIME_SECONDS_MASK
mdefine_line|#define RTCTIME_SECONDS_MASK&t;0x0000003f&t;/* Seconds */
DECL|macro|RTCTIME_SECONDS_SHIFT
mdefine_line|#define RTCTIME_SECONDS_SHIFT&t;0
DECL|macro|RTCTIME_MINUTES_MASK
mdefine_line|#define RTCTIME_MINUTES_MASK&t;0x003f0000&t;/* Minutes */
DECL|macro|RTCTIME_MINUTES_SHIFT
mdefine_line|#define RTCTIME_MINUTES_SHIFT&t;16
DECL|macro|RTCTIME_HOURS_MASK
mdefine_line|#define RTCTIME_HOURS_MASK&t;0x1f000000&t;/* Hours */
DECL|macro|RTCTIME_HOURS_SHIFT
mdefine_line|#define RTCTIME_HOURS_SHIFT&t;24
multiline_comment|/*&n; *  RTC Alarm Register &n; */
DECL|macro|RTCALRM_ADDR
mdefine_line|#define RTCALRM_ADDR    0xfffffb04
DECL|macro|RTCALRM
mdefine_line|#define RTCALRM         LONG_REF(RTCALRM_ADDR)
DECL|macro|RTCALRM_SECONDS_MASK
mdefine_line|#define RTCALRM_SECONDS_MASK    0x0000003f      /* Seconds */
DECL|macro|RTCALRM_SECONDS_SHIFT
mdefine_line|#define RTCALRM_SECONDS_SHIFT   0
DECL|macro|RTCALRM_MINUTES_MASK
mdefine_line|#define RTCALRM_MINUTES_MASK    0x003f0000      /* Minutes */
DECL|macro|RTCALRM_MINUTES_SHIFT
mdefine_line|#define RTCALRM_MINUTES_SHIFT   16
DECL|macro|RTCALRM_HOURS_MASK
mdefine_line|#define RTCALRM_HOURS_MASK      0x1f000000      /* Hours */
DECL|macro|RTCALRM_HOURS_SHIFT
mdefine_line|#define RTCALRM_HOURS_SHIFT     24
multiline_comment|/*&n; * RTC Control Register&n; */
DECL|macro|RTCCTL_ADDR
mdefine_line|#define RTCCTL_ADDR&t;0xfffffb0c
DECL|macro|RTCCTL
mdefine_line|#define RTCCTL&t;&t;WORD_REF(RTCCTL_ADDR)
DECL|macro|RTCCTL_384
mdefine_line|#define RTCCTL_384&t;0x0020&t;/* Crystal Selection */
DECL|macro|RTCCTL_ENABLE
mdefine_line|#define RTCCTL_ENABLE&t;0x0080&t;/* RTC Enable */
multiline_comment|/* &squot;EZ328-compatible definitions */
DECL|macro|RTCCTL_XTL
mdefine_line|#define RTCCTL_XTL&t;RTCCTL_384
DECL|macro|RTCCTL_EN
mdefine_line|#define RTCCTL_EN&t;RTCCTL_ENABLE
multiline_comment|/*&n; * RTC Interrupt Status Register &n; */
DECL|macro|RTCISR_ADDR
mdefine_line|#define RTCISR_ADDR&t;0xfffffb0e
DECL|macro|RTCISR
mdefine_line|#define RTCISR&t;&t;WORD_REF(RTCISR_ADDR)
DECL|macro|RTCISR_SW
mdefine_line|#define RTCISR_SW&t;0x0001&t;/* Stopwatch timed out */
DECL|macro|RTCISR_MIN
mdefine_line|#define RTCISR_MIN&t;0x0002&t;/* 1-minute interrupt has occured */
DECL|macro|RTCISR_ALM
mdefine_line|#define RTCISR_ALM&t;0x0004&t;/* Alarm interrupt has occured */
DECL|macro|RTCISR_DAY
mdefine_line|#define RTCISR_DAY&t;0x0008&t;/* 24-hour rollover interrupt has occured */
DECL|macro|RTCISR_1HZ
mdefine_line|#define RTCISR_1HZ&t;0x0010&t;/* 1Hz interrupt has occured */
multiline_comment|/*&n; * RTC Interrupt Enable Register&n; */
DECL|macro|RTCIENR_ADDR
mdefine_line|#define RTCIENR_ADDR&t;0xfffffb10
DECL|macro|RTCIENR
mdefine_line|#define RTCIENR&t;&t;WORD_REF(RTCIENR_ADDR)
DECL|macro|RTCIENR_SW
mdefine_line|#define RTCIENR_SW&t;0x0001&t;/* Stopwatch interrupt enable */
DECL|macro|RTCIENR_MIN
mdefine_line|#define RTCIENR_MIN&t;0x0002&t;/* 1-minute interrupt enable */
DECL|macro|RTCIENR_ALM
mdefine_line|#define RTCIENR_ALM&t;0x0004&t;/* Alarm interrupt enable */
DECL|macro|RTCIENR_DAY
mdefine_line|#define RTCIENR_DAY&t;0x0008&t;/* 24-hour rollover interrupt enable */
DECL|macro|RTCIENR_1HZ
mdefine_line|#define RTCIENR_1HZ&t;0x0010&t;/* 1Hz interrupt enable */
multiline_comment|/* &n; * Stopwatch Minutes Register&n; */
DECL|macro|STPWCH_ADDR
mdefine_line|#define STPWCH_ADDR&t;0xfffffb12
DECL|macro|STPWCH
mdefine_line|#define STPWCH&t;&t;WORD_REF(STPWCH)
DECL|macro|STPWCH_CNT_MASK
mdefine_line|#define STPWCH_CNT_MASK&t; 0x00ff&t;/* Stopwatch countdown value */
DECL|macro|SPTWCH_CNT_SHIFT
mdefine_line|#define SPTWCH_CNT_SHIFT 0
macro_line|#endif /* _MC68328_H_ */
eof
