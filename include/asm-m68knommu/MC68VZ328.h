multiline_comment|/* include/asm-m68knommu/MC68VZ328.h: &squot;VZ328 control registers&n; *&n; * Copyright (c) 2000-2001&t;Lineo Inc. &lt;www.lineo.com&gt;&n; * Copyright (c) 2000-2001&t;Lineo Canada Corp. &lt;www.lineo.ca&gt;&n; * Copyright (C) 1999&t;&t;Vladimir Gurevich &lt;vgurevic@cisco.com&gt;&n; * &t;&t;&t;&t;Bare &amp; Hare Software, Inc.&n; * Based on include/asm-m68knommu/MC68332.h&n; * Copyright (C) 1998  Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *                     The Silver Hammer Group, Ltd.&n; *&n; * M68VZ328 fixes by Evan Stawnyczy &lt;evan@lineo.com&gt;&n; * vz multiport fixes by Michael Leslie &lt;mleslie@lineo.com&gt;&n; */
macro_line|#ifndef _MC68VZ328_H_
DECL|macro|_MC68VZ328_H_
mdefine_line|#define _MC68VZ328_H_
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
multiline_comment|/*&n; * Silicon ID Register (Mask Revision Register (MRR) for &squot;328 Compatibility)&n; */
DECL|macro|MRR_ADDR
mdefine_line|#define MRR_ADDR 0xfffff004
DECL|macro|MRR
mdefine_line|#define MRR&t; LONG_REF(MRR_ADDR)
multiline_comment|/********** &n; *&n; * 0xFFFFF1xx -- Chip-Select logic&n; *&n; **********/
multiline_comment|/*&n; * Chip Select Group Base Registers &n; */
DECL|macro|CSGBA_ADDR
mdefine_line|#define CSGBA_ADDR&t;0xfffff100
DECL|macro|CSGBB_ADDR
mdefine_line|#define CSGBB_ADDR&t;0xfffff102
DECL|macro|CSGBC_ADDR
mdefine_line|#define CSGBC_ADDR&t;0xfffff104
DECL|macro|CSGBD_ADDR
mdefine_line|#define CSGBD_ADDR&t;0xfffff106
DECL|macro|CSGBA
mdefine_line|#define CSGBA&t;&t;WORD_REF(CSGBA_ADDR)
DECL|macro|CSGBB
mdefine_line|#define CSGBB&t;&t;WORD_REF(CSGBB_ADDR)
DECL|macro|CSGBC
mdefine_line|#define CSGBC&t;&t;WORD_REF(CSGBC_ADDR)
DECL|macro|CSGBD
mdefine_line|#define CSGBD&t;&t;WORD_REF(CSGBD_ADDR)
multiline_comment|/*&n; * Chip Select Registers &n; */
DECL|macro|CSA_ADDR
mdefine_line|#define CSA_ADDR&t;0xfffff110
DECL|macro|CSB_ADDR
mdefine_line|#define CSB_ADDR&t;0xfffff112
DECL|macro|CSC_ADDR
mdefine_line|#define CSC_ADDR&t;0xfffff114
DECL|macro|CSD_ADDR
mdefine_line|#define CSD_ADDR&t;0xfffff116
DECL|macro|CSA
mdefine_line|#define CSA&t;&t;WORD_REF(CSA_ADDR)
DECL|macro|CSB
mdefine_line|#define CSB&t;&t;WORD_REF(CSB_ADDR)
DECL|macro|CSC
mdefine_line|#define CSC&t;&t;WORD_REF(CSC_ADDR)
DECL|macro|CSD
mdefine_line|#define CSD&t;&t;WORD_REF(CSD_ADDR)
DECL|macro|CSA_EN
mdefine_line|#define CSA_EN&t;&t;0x0001&t;&t;/* Chip-Select Enable */
DECL|macro|CSA_SIZ_MASK
mdefine_line|#define CSA_SIZ_MASK&t;0x000e&t;&t;/* Chip-Select Size */
DECL|macro|CSA_SIZ_SHIFT
mdefine_line|#define CSA_SIZ_SHIFT   1
DECL|macro|CSA_WS_MASK
mdefine_line|#define CSA_WS_MASK&t;0x0070&t;&t;/* Wait State */
DECL|macro|CSA_WS_SHIFT
mdefine_line|#define CSA_WS_SHIFT    4
DECL|macro|CSA_BSW
mdefine_line|#define CSA_BSW&t;&t;0x0080&t;&t;/* Data Bus Width */
DECL|macro|CSA_FLASH
mdefine_line|#define CSA_FLASH&t;0x0100&t;&t;/* FLASH Memory Support */
DECL|macro|CSA_RO
mdefine_line|#define CSA_RO&t;&t;0x8000&t;&t;/* Read-Only */
DECL|macro|CSB_EN
mdefine_line|#define CSB_EN&t;&t;0x0001&t;&t;/* Chip-Select Enable */
DECL|macro|CSB_SIZ_MASK
mdefine_line|#define CSB_SIZ_MASK&t;0x000e&t;&t;/* Chip-Select Size */
DECL|macro|CSB_SIZ_SHIFT
mdefine_line|#define CSB_SIZ_SHIFT   1
DECL|macro|CSB_WS_MASK
mdefine_line|#define CSB_WS_MASK&t;0x0070&t;&t;/* Wait State */
DECL|macro|CSB_WS_SHIFT
mdefine_line|#define CSB_WS_SHIFT    4
DECL|macro|CSB_BSW
mdefine_line|#define CSB_BSW&t;&t;0x0080&t;&t;/* Data Bus Width */
DECL|macro|CSB_FLASH
mdefine_line|#define CSB_FLASH&t;0x0100&t;&t;/* FLASH Memory Support */
DECL|macro|CSB_UPSIZ_MASK
mdefine_line|#define CSB_UPSIZ_MASK&t;0x1800&t;&t;/* Unprotected memory block size */
DECL|macro|CSB_UPSIZ_SHIFT
mdefine_line|#define CSB_UPSIZ_SHIFT 11
DECL|macro|CSB_ROP
mdefine_line|#define CSB_ROP&t;&t;0x2000&t;&t;/* Readonly if protected */
DECL|macro|CSB_SOP
mdefine_line|#define CSB_SOP&t;&t;0x4000&t;&t;/* Supervisor only if protected */
DECL|macro|CSB_RO
mdefine_line|#define CSB_RO&t;&t;0x8000&t;&t;/* Read-Only */
DECL|macro|CSC_EN
mdefine_line|#define CSC_EN&t;&t;0x0001&t;&t;/* Chip-Select Enable */
DECL|macro|CSC_SIZ_MASK
mdefine_line|#define CSC_SIZ_MASK&t;0x000e&t;&t;/* Chip-Select Size */
DECL|macro|CSC_SIZ_SHIFT
mdefine_line|#define CSC_SIZ_SHIFT   1
DECL|macro|CSC_WS_MASK
mdefine_line|#define CSC_WS_MASK&t;0x0070&t;&t;/* Wait State */
DECL|macro|CSC_WS_SHIFT
mdefine_line|#define CSC_WS_SHIFT    4
DECL|macro|CSC_BSW
mdefine_line|#define CSC_BSW&t;&t;0x0080&t;&t;/* Data Bus Width */
DECL|macro|CSC_FLASH
mdefine_line|#define CSC_FLASH&t;0x0100&t;&t;/* FLASH Memory Support */
DECL|macro|CSC_UPSIZ_MASK
mdefine_line|#define CSC_UPSIZ_MASK&t;0x1800&t;&t;/* Unprotected memory block size */
DECL|macro|CSC_UPSIZ_SHIFT
mdefine_line|#define CSC_UPSIZ_SHIFT 11
DECL|macro|CSC_ROP
mdefine_line|#define CSC_ROP&t;&t;0x2000&t;&t;/* Readonly if protected */
DECL|macro|CSC_SOP
mdefine_line|#define CSC_SOP&t;&t;0x4000&t;&t;/* Supervisor only if protected */
DECL|macro|CSC_RO
mdefine_line|#define CSC_RO&t;&t;0x8000&t;&t;/* Read-Only */
DECL|macro|CSD_EN
mdefine_line|#define CSD_EN&t;&t;0x0001&t;&t;/* Chip-Select Enable */
DECL|macro|CSD_SIZ_MASK
mdefine_line|#define CSD_SIZ_MASK&t;0x000e&t;&t;/* Chip-Select Size */
DECL|macro|CSD_SIZ_SHIFT
mdefine_line|#define CSD_SIZ_SHIFT   1
DECL|macro|CSD_WS_MASK
mdefine_line|#define CSD_WS_MASK&t;0x0070&t;&t;/* Wait State */
DECL|macro|CSD_WS_SHIFT
mdefine_line|#define CSD_WS_SHIFT    4
DECL|macro|CSD_BSW
mdefine_line|#define CSD_BSW&t;&t;0x0080&t;&t;/* Data Bus Width */
DECL|macro|CSD_FLASH
mdefine_line|#define CSD_FLASH&t;0x0100&t;&t;/* FLASH Memory Support */
DECL|macro|CSD_DRAM
mdefine_line|#define CSD_DRAM&t;0x0200&t;&t;/* Dram Selection */
DECL|macro|CSD_COMB
mdefine_line|#define&t;CSD_COMB&t;0x0400&t;&t;/* Combining */
DECL|macro|CSD_UPSIZ_MASK
mdefine_line|#define CSD_UPSIZ_MASK&t;0x1800&t;&t;/* Unprotected memory block size */
DECL|macro|CSD_UPSIZ_SHIFT
mdefine_line|#define CSD_UPSIZ_SHIFT 11
DECL|macro|CSD_ROP
mdefine_line|#define CSD_ROP&t;&t;0x2000&t;&t;/* Readonly if protected */
DECL|macro|CSD_SOP
mdefine_line|#define CSD_SOP&t;&t;0x4000&t;&t;/* Supervisor only if protected */
DECL|macro|CSD_RO
mdefine_line|#define CSD_RO&t;&t;0x8000&t;&t;/* Read-Only */
multiline_comment|/*&n; * Emulation Chip-Select Register &n; */
DECL|macro|EMUCS_ADDR
mdefine_line|#define EMUCS_ADDR&t;0xfffff118
DECL|macro|EMUCS
mdefine_line|#define EMUCS&t;&t;WORD_REF(EMUCS_ADDR)
DECL|macro|EMUCS_WS_MASK
mdefine_line|#define EMUCS_WS_MASK&t;0x0070
DECL|macro|EMUCS_WS_SHIFT
mdefine_line|#define EMUCS_WS_SHIFT&t;4
multiline_comment|/********** &n; *&n; * 0xFFFFF2xx -- Phase Locked Loop (PLL) &amp; Power Control&n; *&n; **********/
multiline_comment|/*&n; * PLL Control Register &n; */
DECL|macro|PLLCR_ADDR
mdefine_line|#define PLLCR_ADDR&t;0xfffff200
DECL|macro|PLLCR
mdefine_line|#define PLLCR&t;&t;WORD_REF(PLLCR_ADDR)
DECL|macro|PLLCR_DISPLL
mdefine_line|#define PLLCR_DISPLL&t;       0x0008&t;/* Disable PLL */
DECL|macro|PLLCR_CLKEN
mdefine_line|#define PLLCR_CLKEN&t;       0x0010&t;/* Clock (CLKO pin) enable */
DECL|macro|PLLCR_PRESC
mdefine_line|#define PLLCR_PRESC&t;       0x0020&t;/* VCO prescaler */
DECL|macro|PLLCR_SYSCLK_SEL_MASK
mdefine_line|#define PLLCR_SYSCLK_SEL_MASK  0x0700&t;/* System Clock Selection */
DECL|macro|PLLCR_SYSCLK_SEL_SHIFT
mdefine_line|#define PLLCR_SYSCLK_SEL_SHIFT 8
DECL|macro|PLLCR_LCDCLK_SEL_MASK
mdefine_line|#define PLLCR_LCDCLK_SEL_MASK  0x3800&t;/* LCD Clock Selection */
DECL|macro|PLLCR_LCDCLK_SEL_SHIFT
mdefine_line|#define PLLCR_LCDCLK_SEL_SHIFT 11
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|PLLCR_PIXCLK_SEL_MASK
mdefine_line|#define PLLCR_PIXCLK_SEL_MASK&t;PLLCR_LCDCLK_SEL_MASK
DECL|macro|PLLCR_PIXCLK_SEL_SHIFT
mdefine_line|#define PLLCR_PIXCLK_SEL_SHIFT&t;PLLCR_LCDCLK_SEL_SHIFT
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
DECL|macro|ICR_ADDR
mdefine_line|#define ICR_ADDR&t;0xfffff302
DECL|macro|ICR
mdefine_line|#define ICR&t;&t;WORD_REF(ICR_ADDR)
DECL|macro|ICR_POL5
mdefine_line|#define ICR_POL5&t;0x0080&t;/* Polarity Control for IRQ5 */
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
multiline_comment|/*&n; * Define the names for bit positions first. This is useful for &n; * request_irq&n; */
DECL|macro|SPI2_IRQ_NUM
mdefine_line|#define SPI2_IRQ_NUM&t;0&t;/* SPI 2 interrupt */
DECL|macro|TMR_IRQ_NUM
mdefine_line|#define TMR_IRQ_NUM&t;1&t;/* Timer 1 interrupt */
DECL|macro|UART1_IRQ_NUM
mdefine_line|#define UART1_IRQ_NUM&t;2&t;/* UART 1 interrupt */&t;
DECL|macro|WDT_IRQ_NUM
mdefine_line|#define&t;WDT_IRQ_NUM&t;3&t;/* Watchdog Timer interrupt */
DECL|macro|RTC_IRQ_NUM
mdefine_line|#define RTC_IRQ_NUM&t;4&t;/* RTC interrupt */
DECL|macro|TMR2_IRQ_NUM
mdefine_line|#define TMR2_IRQ_NUM&t;5&t;/* Timer 2 interrupt */
DECL|macro|KB_IRQ_NUM
mdefine_line|#define&t;KB_IRQ_NUM&t;6&t;/* Keyboard Interrupt */
DECL|macro|PWM1_IRQ_NUM
mdefine_line|#define PWM1_IRQ_NUM&t;7&t;/* Pulse-Width Modulator 1 int. */
DECL|macro|INT0_IRQ_NUM
mdefine_line|#define&t;INT0_IRQ_NUM&t;8&t;/* External INT0 */
DECL|macro|INT1_IRQ_NUM
mdefine_line|#define&t;INT1_IRQ_NUM&t;9&t;/* External INT1 */
DECL|macro|INT2_IRQ_NUM
mdefine_line|#define&t;INT2_IRQ_NUM&t;10&t;/* External INT2 */
DECL|macro|INT3_IRQ_NUM
mdefine_line|#define&t;INT3_IRQ_NUM&t;11&t;/* External INT3 */
DECL|macro|UART2_IRQ_NUM
mdefine_line|#define UART2_IRQ_NUM&t;12&t;/* UART 2 interrupt */&t;
DECL|macro|PWM2_IRQ_NUM
mdefine_line|#define PWM2_IRQ_NUM&t;13&t;/* Pulse-Width Modulator 1 int. */
DECL|macro|IRQ1_IRQ_NUM
mdefine_line|#define IRQ1_IRQ_NUM&t;16&t;/* IRQ1 */
DECL|macro|IRQ2_IRQ_NUM
mdefine_line|#define IRQ2_IRQ_NUM&t;17&t;/* IRQ2 */
DECL|macro|IRQ3_IRQ_NUM
mdefine_line|#define IRQ3_IRQ_NUM&t;18&t;/* IRQ3 */
DECL|macro|IRQ6_IRQ_NUM
mdefine_line|#define IRQ6_IRQ_NUM&t;19&t;/* IRQ6 */
DECL|macro|IRQ5_IRQ_NUM
mdefine_line|#define IRQ5_IRQ_NUM&t;20&t;/* IRQ5 */
DECL|macro|SPI1_IRQ_NUM
mdefine_line|#define SPI1_IRQ_NUM&t;21&t;/* SPI 1 interrupt */
DECL|macro|SAM_IRQ_NUM
mdefine_line|#define SAM_IRQ_NUM&t;22&t;/* Sampling Timer for RTC */
DECL|macro|EMIQ_IRQ_NUM
mdefine_line|#define EMIQ_IRQ_NUM&t;23&t;/* Emulator Interrupt */
DECL|macro|SPI_IRQ_NUM
mdefine_line|#define SPI_IRQ_NUM&t;SPI2_IRQ_NUM
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|SPIM_IRQ_NUM
mdefine_line|#define SPIM_IRQ_NUM&t;SPI_IRQ_NUM
DECL|macro|TMR1_IRQ_NUM
mdefine_line|#define TMR1_IRQ_NUM&t;TMR_IRQ_NUM
DECL|macro|UART_IRQ_NUM
mdefine_line|#define UART_IRQ_NUM&t;UART1_IRQ_NUM
multiline_comment|/* &n; * Here go the bitmasks themselves&n; */
DECL|macro|IMR_MSPI
mdefine_line|#define IMR_MSPI &t;(1 &lt;&lt; SPI_IRQ_NUM)&t;/* Mask SPI interrupt */
DECL|macro|IMR_MTMR
mdefine_line|#define&t;IMR_MTMR&t;(1 &lt;&lt; TMR_IRQ_NUM)&t;/* Mask Timer interrupt */
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
DECL|macro|IMR_MIRQ1
mdefine_line|#define IMR_MIRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* Mask IRQ1 */
DECL|macro|IMR_MIRQ2
mdefine_line|#define IMR_MIRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* Mask IRQ2 */
DECL|macro|IMR_MIRQ3
mdefine_line|#define IMR_MIRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* Mask IRQ3 */
DECL|macro|IMR_MIRQ6
mdefine_line|#define IMR_MIRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* Mask IRQ6 */
DECL|macro|IMR_MIRQ5
mdefine_line|#define IMR_MIRQ5&t;(1 &lt;&lt; IRQ5_IRQ_NUM)&t;/* Mask IRQ5 */
DECL|macro|IMR_MSAM
mdefine_line|#define IMR_MSAM&t;(1 &lt;&lt; SAM_IRQ_NUM)&t;/* Mask Sampling Timer for RTC */
DECL|macro|IMR_MEMIQ
mdefine_line|#define IMR_MEMIQ&t;(1 &lt;&lt; EMIQ_IRQ_NUM)&t;/* Mask Emulator Interrupt */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|IMR_MSPIM
mdefine_line|#define IMR_MSPIM&t;IMR_MSPI
DECL|macro|IMR_MTMR1
mdefine_line|#define IMR_MTMR1&t;IMR_MTMR
multiline_comment|/* &n; * Interrupt Status Register &n; */
DECL|macro|ISR_ADDR
mdefine_line|#define ISR_ADDR&t;0xfffff30c
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;LONG_REF(ISR_ADDR)
DECL|macro|ISR_SPI
mdefine_line|#define ISR_SPI &t;(1 &lt;&lt; SPI_IRQ_NUM)&t;/* SPI interrupt */
DECL|macro|ISR_TMR
mdefine_line|#define&t;ISR_TMR&t;&t;(1 &lt;&lt; TMR_IRQ_NUM)&t;/* Timer interrupt */
DECL|macro|ISR_UART
mdefine_line|#define ISR_UART&t;(1 &lt;&lt; UART_IRQ_NUM)&t;/* UART interrupt */&t;
DECL|macro|ISR_WDT
mdefine_line|#define&t;ISR_WDT&t;&t;(1 &lt;&lt; WDT_IRQ_NUM)&t;/* Watchdog Timer interrupt */
DECL|macro|ISR_RTC
mdefine_line|#define ISR_RTC&t;&t;(1 &lt;&lt; RTC_IRQ_NUM)&t;/* RTC interrupt */
DECL|macro|ISR_KB
mdefine_line|#define&t;ISR_KB&t;&t;(1 &lt;&lt; KB_IRQ_NUM)&t;/* Keyboard Interrupt */
DECL|macro|ISR_PWM
mdefine_line|#define ISR_PWM&t;&t;(1 &lt;&lt; PWM_IRQ_NUM)&t;/* Pulse-Width Modulator interrupt */
DECL|macro|ISR_INT0
mdefine_line|#define&t;ISR_INT0&t;(1 &lt;&lt; INT0_IRQ_NUM)&t;/* External INT0 */
DECL|macro|ISR_INT1
mdefine_line|#define&t;ISR_INT1&t;(1 &lt;&lt; INT1_IRQ_NUM)&t;/* External INT1 */
DECL|macro|ISR_INT2
mdefine_line|#define&t;ISR_INT2&t;(1 &lt;&lt; INT2_IRQ_NUM)&t;/* External INT2 */
DECL|macro|ISR_INT3
mdefine_line|#define&t;ISR_INT3&t;(1 &lt;&lt; INT3_IRQ_NUM)&t;/* External INT3 */
DECL|macro|ISR_IRQ1
mdefine_line|#define ISR_IRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* IRQ1 */
DECL|macro|ISR_IRQ2
mdefine_line|#define ISR_IRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* IRQ2 */
DECL|macro|ISR_IRQ3
mdefine_line|#define ISR_IRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* IRQ3 */
DECL|macro|ISR_IRQ6
mdefine_line|#define ISR_IRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* IRQ6 */
DECL|macro|ISR_IRQ5
mdefine_line|#define ISR_IRQ5&t;(1 &lt;&lt; IRQ5_IRQ_NUM)&t;/* IRQ5 */
DECL|macro|ISR_SAM
mdefine_line|#define ISR_SAM&t;&t;(1 &lt;&lt; SAM_IRQ_NUM)&t;/* Sampling Timer for RTC */
DECL|macro|ISR_EMIQ
mdefine_line|#define ISR_EMIQ&t;(1 &lt;&lt; EMIQ_IRQ_NUM)&t;/* Emulator Interrupt */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|ISR_SPIM
mdefine_line|#define ISR_SPIM&t;ISR_SPI
DECL|macro|ISR_TMR1
mdefine_line|#define ISR_TMR1&t;ISR_TMR
multiline_comment|/* &n; * Interrupt Pending Register &n; */
DECL|macro|IPR_ADDR
mdefine_line|#define IPR_ADDR&t;0xfffff30c
DECL|macro|IPR
mdefine_line|#define IPR&t;&t;LONG_REF(IPR_ADDR)
DECL|macro|IPR_SPI
mdefine_line|#define IPR_SPI &t;(1 &lt;&lt; SPI_IRQ_NUM)&t;/* SPI interrupt */
DECL|macro|IPR_TMR
mdefine_line|#define&t;IPR_TMR&t;&t;(1 &lt;&lt; TMR_IRQ_NUM)&t;/* Timer interrupt */
DECL|macro|IPR_UART
mdefine_line|#define IPR_UART&t;(1 &lt;&lt; UART_IRQ_NUM)&t;/* UART interrupt */&t;
DECL|macro|IPR_WDT
mdefine_line|#define&t;IPR_WDT&t;&t;(1 &lt;&lt; WDT_IRQ_NUM)&t;/* Watchdog Timer interrupt */
DECL|macro|IPR_RTC
mdefine_line|#define IPR_RTC&t;&t;(1 &lt;&lt; RTC_IRQ_NUM)&t;/* RTC interrupt */
DECL|macro|IPR_KB
mdefine_line|#define&t;IPR_KB&t;&t;(1 &lt;&lt; KB_IRQ_NUM)&t;/* Keyboard Interrupt */
DECL|macro|IPR_PWM
mdefine_line|#define IPR_PWM&t;&t;(1 &lt;&lt; PWM_IRQ_NUM)&t;/* Pulse-Width Modulator interrupt */
DECL|macro|IPR_INT0
mdefine_line|#define&t;IPR_INT0&t;(1 &lt;&lt; INT0_IRQ_NUM)&t;/* External INT0 */
DECL|macro|IPR_INT1
mdefine_line|#define&t;IPR_INT1&t;(1 &lt;&lt; INT1_IRQ_NUM)&t;/* External INT1 */
DECL|macro|IPR_INT2
mdefine_line|#define&t;IPR_INT2&t;(1 &lt;&lt; INT2_IRQ_NUM)&t;/* External INT2 */
DECL|macro|IPR_INT3
mdefine_line|#define&t;IPR_INT3&t;(1 &lt;&lt; INT3_IRQ_NUM)&t;/* External INT3 */
DECL|macro|IPR_IRQ1
mdefine_line|#define IPR_IRQ1&t;(1 &lt;&lt; IRQ1_IRQ_NUM)&t;/* IRQ1 */
DECL|macro|IPR_IRQ2
mdefine_line|#define IPR_IRQ2&t;(1 &lt;&lt; IRQ2_IRQ_NUM)&t;/* IRQ2 */
DECL|macro|IPR_IRQ3
mdefine_line|#define IPR_IRQ3&t;(1 &lt;&lt; IRQ3_IRQ_NUM)&t;/* IRQ3 */
DECL|macro|IPR_IRQ6
mdefine_line|#define IPR_IRQ6&t;(1 &lt;&lt; IRQ6_IRQ_NUM)&t;/* IRQ6 */
DECL|macro|IPR_IRQ5
mdefine_line|#define IPR_IRQ5&t;(1 &lt;&lt; IRQ5_IRQ_NUM)&t;/* IRQ5 */
DECL|macro|IPR_SAM
mdefine_line|#define IPR_SAM&t;&t;(1 &lt;&lt; SAM_IRQ_NUM)&t;/* Sampling Timer for RTC */
DECL|macro|IPR_EMIQ
mdefine_line|#define IPR_EMIQ&t;(1 &lt;&lt; EMIQ_IRQ_NUM)&t;/* Emulator Interrupt */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|IPR_SPIM
mdefine_line|#define IPR_SPIM&t;IPR_SPI
DECL|macro|IPR_TMR1
mdefine_line|#define IPR_TMR1&t;IPR_TMR
multiline_comment|/**********&n; *&n; * 0xFFFFF4xx -- Parallel Ports&n; *&n; **********/
multiline_comment|/*&n; * Port A&n; */
DECL|macro|PADIR_ADDR
mdefine_line|#define PADIR_ADDR&t;0xfffff400&t;&t;/* Port A direction reg */
DECL|macro|PADATA_ADDR
mdefine_line|#define PADATA_ADDR&t;0xfffff401&t;&t;/* Port A data register */
DECL|macro|PAPUEN_ADDR
mdefine_line|#define PAPUEN_ADDR&t;0xfffff402&t;&t;/* Port A Pull-Up enable reg */
DECL|macro|PADIR
mdefine_line|#define PADIR&t;&t;BYTE_REF(PADIR_ADDR)
DECL|macro|PADATA
mdefine_line|#define PADATA&t;&t;BYTE_REF(PADATA_ADDR)
DECL|macro|PAPUEN
mdefine_line|#define PAPUEN&t;&t;BYTE_REF(PAPUEN_ADDR)
DECL|macro|PA
mdefine_line|#define PA(x)&t;&t;(1 &lt;&lt; (x))
multiline_comment|/* &n; * Port B&n; */
DECL|macro|PBDIR_ADDR
mdefine_line|#define PBDIR_ADDR&t;0xfffff408&t;&t;/* Port B direction reg */
DECL|macro|PBDATA_ADDR
mdefine_line|#define PBDATA_ADDR&t;0xfffff409&t;&t;/* Port B data register */
DECL|macro|PBPUEN_ADDR
mdefine_line|#define PBPUEN_ADDR&t;0xfffff40a&t;&t;/* Port B Pull-Up enable reg */
DECL|macro|PBSEL_ADDR
mdefine_line|#define PBSEL_ADDR&t;0xfffff40b&t;&t;/* Port B Select Register */
DECL|macro|PBDIR
mdefine_line|#define PBDIR&t;&t;BYTE_REF(PBDIR_ADDR)
DECL|macro|PBDATA
mdefine_line|#define PBDATA&t;&t;BYTE_REF(PBDATA_ADDR)
DECL|macro|PBPUEN
mdefine_line|#define PBPUEN&t;&t;BYTE_REF(PBPUEN_ADDR)
DECL|macro|PBSEL
mdefine_line|#define PBSEL&t;&t;BYTE_REF(PBSEL_ADDR)
DECL|macro|PB
mdefine_line|#define PB(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PB_CSB0
mdefine_line|#define PB_CSB0&t;&t;0x01&t;/* Use CSB0      as PB[0] */
DECL|macro|PB_CSB1
mdefine_line|#define PB_CSB1&t;&t;0x02&t;/* Use CSB1      as PB[1] */
DECL|macro|PB_CSC0_RAS0
mdefine_line|#define PB_CSC0_RAS0&t;0x04    /* Use CSC0/RAS0 as PB[2] */&t;
DECL|macro|PB_CSC1_RAS1
mdefine_line|#define PB_CSC1_RAS1&t;0x08    /* Use CSC1/RAS1 as PB[3] */&t;
DECL|macro|PB_CSD0_CAS0
mdefine_line|#define PB_CSD0_CAS0&t;0x10    /* Use CSD0/CAS0 as PB[4] */&t;
DECL|macro|PB_CSD1_CAS1
mdefine_line|#define PB_CSD1_CAS1&t;0x20    /* Use CSD1/CAS1 as PB[5] */
DECL|macro|PB_TIN_TOUT
mdefine_line|#define PB_TIN_TOUT&t;0x40&t;/* Use TIN/TOUT  as PB[6] */
DECL|macro|PB_PWMO
mdefine_line|#define PB_PWMO&t;&t;0x80&t;/* Use PWMO      as PB[7] */
multiline_comment|/* &n; * Port C&n; */
DECL|macro|PCDIR_ADDR
mdefine_line|#define PCDIR_ADDR&t;0xfffff410&t;&t;/* Port C direction reg */
DECL|macro|PCDATA_ADDR
mdefine_line|#define PCDATA_ADDR&t;0xfffff411&t;&t;/* Port C data register */
DECL|macro|PCPDEN_ADDR
mdefine_line|#define PCPDEN_ADDR&t;0xfffff412&t;&t;/* Port C Pull-Down enb. reg */
DECL|macro|PCSEL_ADDR
mdefine_line|#define PCSEL_ADDR&t;0xfffff413&t;&t;/* Port C Select Register */
DECL|macro|PCDIR
mdefine_line|#define PCDIR&t;&t;BYTE_REF(PCDIR_ADDR)
DECL|macro|PCDATA
mdefine_line|#define PCDATA&t;&t;BYTE_REF(PCDATA_ADDR)
DECL|macro|PCPDEN
mdefine_line|#define PCPDEN&t;&t;BYTE_REF(PCPDEN_ADDR)
DECL|macro|PCSEL
mdefine_line|#define PCSEL&t;&t;BYTE_REF(PCSEL_ADDR)
DECL|macro|PC
mdefine_line|#define PC(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PC_LD0
mdefine_line|#define PC_LD0&t;&t;0x01&t;/* Use LD0  as PC[0] */
DECL|macro|PC_LD1
mdefine_line|#define PC_LD1&t;&t;0x02&t;/* Use LD1  as PC[1] */
DECL|macro|PC_LD2
mdefine_line|#define PC_LD2&t;&t;0x04&t;/* Use LD2  as PC[2] */
DECL|macro|PC_LD3
mdefine_line|#define PC_LD3&t;&t;0x08&t;/* Use LD3  as PC[3] */
DECL|macro|PC_LFLM
mdefine_line|#define PC_LFLM&t;&t;0x10&t;/* Use LFLM as PC[4] */
DECL|macro|PC_LLP
mdefine_line|#define PC_LLP &t;&t;0x20&t;/* Use LLP  as PC[5] */
DECL|macro|PC_LCLK
mdefine_line|#define PC_LCLK&t;&t;0x40&t;/* Use LCLK as PC[6] */
DECL|macro|PC_LACD
mdefine_line|#define PC_LACD&t;&t;0x80&t;/* Use LACD as PC[7] */
multiline_comment|/* &n; * Port D&n; */
DECL|macro|PDDIR_ADDR
mdefine_line|#define PDDIR_ADDR&t;0xfffff418&t;&t;/* Port D direction reg */
DECL|macro|PDDATA_ADDR
mdefine_line|#define PDDATA_ADDR&t;0xfffff419&t;&t;/* Port D data register */
DECL|macro|PDPUEN_ADDR
mdefine_line|#define PDPUEN_ADDR&t;0xfffff41a&t;&t;/* Port D Pull-Up enable reg */
DECL|macro|PDSEL_ADDR
mdefine_line|#define PDSEL_ADDR&t;0xfffff41b&t;&t;/* Port D Select Register */
DECL|macro|PDPOL_ADDR
mdefine_line|#define PDPOL_ADDR&t;0xfffff41c&t;&t;/* Port D Polarity Register */
DECL|macro|PDIRQEN_ADDR
mdefine_line|#define PDIRQEN_ADDR&t;0xfffff41d&t;&t;/* Port D IRQ enable register */
DECL|macro|PDKBEN_ADDR
mdefine_line|#define PDKBEN_ADDR&t;0xfffff41e&t;&t;/* Port D Keyboard Enable reg */
DECL|macro|PDIQEG_ADDR
mdefine_line|#define&t;PDIQEG_ADDR&t;0xfffff41f&t;&t;/* Port D IRQ Edge Register */
DECL|macro|PDDIR
mdefine_line|#define PDDIR&t;&t;BYTE_REF(PDDIR_ADDR)
DECL|macro|PDDATA
mdefine_line|#define PDDATA&t;&t;BYTE_REF(PDDATA_ADDR)
DECL|macro|PDPUEN
mdefine_line|#define PDPUEN&t;&t;BYTE_REF(PDPUEN_ADDR)
DECL|macro|PDSEL
mdefine_line|#define PDSEL&t;&t;BYTE_REF(PDSEL_ADDR)
DECL|macro|PDPOL
mdefine_line|#define&t;PDPOL&t;&t;BYTE_REF(PDPOL_ADDR)
DECL|macro|PDIRQEN
mdefine_line|#define PDIRQEN&t;&t;BYTE_REF(PDIRQEN_ADDR)
DECL|macro|PDKBEN
mdefine_line|#define PDKBEN&t;&t;BYTE_REF(PDKBEN_ADDR)
DECL|macro|PDIQEG
mdefine_line|#define PDIQEG&t;&t;BYTE_REF(PDIQEG_ADDR)
DECL|macro|PD
mdefine_line|#define PD(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PD_INT0
mdefine_line|#define PD_INT0&t;&t;0x01&t;/* Use INT0 as PD[0] */
DECL|macro|PD_INT1
mdefine_line|#define PD_INT1&t;&t;0x02&t;/* Use INT1 as PD[1] */
DECL|macro|PD_INT2
mdefine_line|#define PD_INT2&t;&t;0x04&t;/* Use INT2 as PD[2] */
DECL|macro|PD_INT3
mdefine_line|#define PD_INT3&t;&t;0x08&t;/* Use INT3 as PD[3] */
DECL|macro|PD_IRQ1
mdefine_line|#define PD_IRQ1&t;&t;0x10&t;/* Use IRQ1 as PD[4] */
DECL|macro|PD_IRQ2
mdefine_line|#define PD_IRQ2&t;&t;0x20&t;/* Use IRQ2 as PD[5] */
DECL|macro|PD_IRQ3
mdefine_line|#define PD_IRQ3&t;&t;0x40&t;/* Use IRQ3 as PD[6] */
DECL|macro|PD_IRQ6
mdefine_line|#define PD_IRQ6&t;&t;0x80&t;/* Use IRQ6 as PD[7] */
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
mdefine_line|#define PE(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PE_SPMTXD
mdefine_line|#define PE_SPMTXD&t;0x01&t;/* Use SPMTXD as PE[0] */
DECL|macro|PE_SPMRXD
mdefine_line|#define PE_SPMRXD&t;0x02&t;/* Use SPMRXD as PE[1] */
DECL|macro|PE_SPMCLK
mdefine_line|#define PE_SPMCLK&t;0x04&t;/* Use SPMCLK as PE[2] */
DECL|macro|PE_DWE
mdefine_line|#define PE_DWE&t;&t;0x08&t;/* Use DWE    as PE[3] */
DECL|macro|PE_RXD
mdefine_line|#define PE_RXD&t;&t;0x10&t;/* Use RXD    as PE[4] */
DECL|macro|PE_TXD
mdefine_line|#define PE_TXD&t;&t;0x20&t;/* Use TXD    as PE[5] */
DECL|macro|PE_RTS
mdefine_line|#define PE_RTS&t;&t;0x40&t;/* Use RTS    as PE[6] */
DECL|macro|PE_CTS
mdefine_line|#define PE_CTS&t;&t;0x80&t;/* Use CTS    as PE[7] */
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
mdefine_line|#define PF(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PF_LCONTRAST
mdefine_line|#define PF_LCONTRAST&t;0x01&t;/* Use LCONTRAST as PF[0] */
DECL|macro|PF_IRQ5
mdefine_line|#define PF_IRQ5         0x02    /* Use IRQ5      as PF[1] */
DECL|macro|PF_CLKO
mdefine_line|#define PF_CLKO         0x04    /* Use CLKO      as PF[2] */
DECL|macro|PF_A20
mdefine_line|#define PF_A20          0x08    /* Use A20       as PF[3] */
DECL|macro|PF_A21
mdefine_line|#define PF_A21          0x10    /* Use A21       as PF[4] */
DECL|macro|PF_A22
mdefine_line|#define PF_A22          0x20    /* Use A22       as PF[5] */
DECL|macro|PF_A23
mdefine_line|#define PF_A23          0x40    /* Use A23       as PF[6] */
DECL|macro|PF_CSA1
mdefine_line|#define PF_CSA1&t;&t;0x80    /* Use CSA1      as PF[7] */
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
mdefine_line|#define PG(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PG_BUSW_DTACK
mdefine_line|#define PG_BUSW_DTACK&t;0x01&t;/* Use BUSW/DTACK as PG[0] */
DECL|macro|PG_A0
mdefine_line|#define PG_A0&t;&t;0x02&t;/* Use A0         as PG[1] */
DECL|macro|PG_EMUIRQ
mdefine_line|#define PG_EMUIRQ&t;0x04&t;/* Use EMUIRQ     as PG[2] */
DECL|macro|PG_HIZ_P_D
mdefine_line|#define PG_HIZ_P_D&t;0x08&t;/* Use HIZ/P/D    as PG[3] */
DECL|macro|PG_EMUCS
mdefine_line|#define PG_EMUCS        0x10&t;/* Use EMUCS      as PG[4] */
DECL|macro|PG_EMUBRK
mdefine_line|#define PG_EMUBRK&t;0x20&t;/* Use EMUBRK     as PG[5] */
multiline_comment|/* &n; * Port J&n; */
DECL|macro|PJDIR_ADDR
mdefine_line|#define PJDIR_ADDR&t;0xfffff438&t;&t;/* Port J direction reg */
DECL|macro|PJDATA_ADDR
mdefine_line|#define PJDATA_ADDR&t;0xfffff439&t;&t;/* Port J data register */
DECL|macro|PJPUEN_ADDR
mdefine_line|#define PJPUEN_ADDR&t;0xfffff43A&t;&t;/* Port J Pull-Up enb. reg */
DECL|macro|PJSEL_ADDR
mdefine_line|#define PJSEL_ADDR&t;0xfffff43B&t;&t;/* Port J Select Register */
DECL|macro|PJDIR
mdefine_line|#define PJDIR&t;&t;BYTE_REF(PJDIR_ADDR)
DECL|macro|PJDATA
mdefine_line|#define PJDATA&t;&t;BYTE_REF(PJDATA_ADDR)
DECL|macro|PJPUEN
mdefine_line|#define PJPUEN&t;&t;BYTE_REF(PJPUEN_ADDR)
DECL|macro|PJSEL
mdefine_line|#define PJSEL&t;&t;BYTE_REF(PJSEL_ADDR)
DECL|macro|PJ
mdefine_line|#define PJ(x)&t;&t;(1 &lt;&lt; (x))
multiline_comment|/*&n; * Port K&n; */
DECL|macro|PKDIR_ADDR
mdefine_line|#define PKDIR_ADDR&t;0xfffff440&t;&t;/* Port K direction reg */
DECL|macro|PKDATA_ADDR
mdefine_line|#define PKDATA_ADDR&t;0xfffff441&t;&t;/* Port K data register */
DECL|macro|PKPUEN_ADDR
mdefine_line|#define PKPUEN_ADDR&t;0xfffff442&t;&t;/* Port K Pull-Up enb. reg */
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
mdefine_line|#define PK(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PK_DATAREADY
mdefine_line|#define PK_DATAREADY&t;&t;0x01&t;/* Use ~DATA_READY  as PK[0] */
DECL|macro|PK_PWM2
mdefine_line|#define PK_PWM2&t;&t;0x01&t;/* Use PWM2  as PK[0] */
DECL|macro|PK_R_W
mdefine_line|#define PK_R_W&t;&t;0x02&t;/* Use R/W  as PK[1] */
DECL|macro|PK_LDS
mdefine_line|#define PK_LDS&t;&t;0x04&t;/* Use /LDS  as PK[2] */
DECL|macro|PK_UDS
mdefine_line|#define PK_UDS&t;&t;0x08&t;/* Use /UDS  as PK[3] */
DECL|macro|PK_LD4
mdefine_line|#define PK_LD4&t;&t;0x10&t;/* Use LD4 as PK[4] */
DECL|macro|PK_LD5
mdefine_line|#define PK_LD5 &t;&t;0x20&t;/* Use LD5  as PK[5] */
DECL|macro|PK_LD6
mdefine_line|#define PK_LD6&t;&t;0x40&t;/* Use LD6 as PK[6] */
DECL|macro|PK_LD7
mdefine_line|#define PK_LD7&t;&t;0x80&t;/* Use LD7 as PK[7] */
DECL|macro|PJDIR_ADDR
mdefine_line|#define PJDIR_ADDR&t;0xfffff438&t;&t;/* Port J direction reg */
DECL|macro|PJDATA_ADDR
mdefine_line|#define PJDATA_ADDR&t;0xfffff439&t;&t;/* Port J data register */
DECL|macro|PJPUEN_ADDR
mdefine_line|#define PJPUEN_ADDR&t;0xfffff43A&t;&t;/* Port J Pull-Up enable reg */
DECL|macro|PJSEL_ADDR
mdefine_line|#define PJSEL_ADDR&t;0xfffff43B&t;&t;/* Port J Select Register */
DECL|macro|PJDIR
mdefine_line|#define PJDIR&t;&t;BYTE_REF(PJDIR_ADDR)
DECL|macro|PJDATA
mdefine_line|#define PJDATA&t;&t;BYTE_REF(PJDATA_ADDR)
DECL|macro|PJPUEN
mdefine_line|#define PJPUEN&t;&t;BYTE_REF(PJPUEN_ADDR)
DECL|macro|PJSEL
mdefine_line|#define PJSEL&t;&t;BYTE_REF(PJSEL_ADDR)
DECL|macro|PJ
mdefine_line|#define PJ(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PJ_MOSI
mdefine_line|#define PJ_MOSI &t;0x01&t;/* Use MOSI       as PJ[0] */
DECL|macro|PJ_MISO
mdefine_line|#define PJ_MISO&t;&t;0x02&t;/* Use MISO       as PJ[1] */
DECL|macro|PJ_SPICLK1
mdefine_line|#define PJ_SPICLK1  &t;0x04&t;/* Use SPICLK1    as PJ[2] */
DECL|macro|PJ_SS
mdefine_line|#define PJ_SS   &t;0x08&t;/* Use SS         as PJ[3] */
DECL|macro|PJ_RXD2
mdefine_line|#define PJ_RXD2         0x10&t;/* Use RXD2       as PJ[4] */
DECL|macro|PJ_TXD2
mdefine_line|#define PJ_TXD2  &t;0x20&t;/* Use TXD2       as PJ[5] */
DECL|macro|PJ_RTS2
mdefine_line|#define PJ_RTS2  &t;0x40&t;/* Use RTS2       as PJ[5] */
DECL|macro|PJ_CTS2
mdefine_line|#define PJ_CTS2  &t;0x80&t;/* Use CTS2       as PJ[5] */
multiline_comment|/*&n; * Port M&n; */
DECL|macro|PMDIR_ADDR
mdefine_line|#define PMDIR_ADDR&t;0xfffff448&t;&t;/* Port M direction reg */
DECL|macro|PMDATA_ADDR
mdefine_line|#define PMDATA_ADDR&t;0xfffff449&t;&t;/* Port M data register */
DECL|macro|PMPUEN_ADDR
mdefine_line|#define PMPUEN_ADDR&t;0xfffff44a&t;&t;/* Port M Pull-Up enable reg */
DECL|macro|PMSEL_ADDR
mdefine_line|#define PMSEL_ADDR&t;0xfffff44b&t;&t;/* Port M Select Register */
DECL|macro|PMDIR
mdefine_line|#define PMDIR&t;&t;BYTE_REF(PMDIR_ADDR)
DECL|macro|PMDATA
mdefine_line|#define PMDATA&t;&t;BYTE_REF(PMDATA_ADDR)
DECL|macro|PMPUEN
mdefine_line|#define PMPUEN&t;&t;BYTE_REF(PMPUEN_ADDR)
DECL|macro|PMSEL
mdefine_line|#define PMSEL&t;&t;BYTE_REF(PMSEL_ADDR)
DECL|macro|PM
mdefine_line|#define PM(x)&t;&t;(1 &lt;&lt; (x))
DECL|macro|PM_SDCLK
mdefine_line|#define PM_SDCLK&t;0x01&t;/* Use SDCLK      as PM[0] */
DECL|macro|PM_SDCE
mdefine_line|#define PM_SDCE&t;&t;0x02&t;/* Use SDCE       as PM[1] */
DECL|macro|PM_DQMH
mdefine_line|#define PM_DQMH &t;0x04&t;/* Use DQMH       as PM[2] */
DECL|macro|PM_DQML
mdefine_line|#define PM_DQML &t;0x08&t;/* Use DQML       as PM[3] */
DECL|macro|PM_SDA10
mdefine_line|#define PM_SDA10        0x10&t;/* Use SDA10      as PM[4] */
DECL|macro|PM_DMOE
mdefine_line|#define PM_DMOE &t;0x20&t;/* Use DMOE       as PM[5] */
multiline_comment|/**********&n; *&n; * 0xFFFFF5xx -- Pulse-Width Modulator (PWM)&n; *&n; **********/
multiline_comment|/*&n; * PWM Control Register&n; */
DECL|macro|PWMC_ADDR
mdefine_line|#define PWMC_ADDR&t;0xfffff500
DECL|macro|PWMC
mdefine_line|#define PWMC&t;&t;WORD_REF(PWMC_ADDR)
DECL|macro|PWMC_CLKSEL_MASK
mdefine_line|#define PWMC_CLKSEL_MASK&t;0x0003&t;/* Clock Selection */
DECL|macro|PWMC_CLKSEL_SHIFT
mdefine_line|#define PWMC_CLKSEL_SHIFT&t;0
DECL|macro|PWMC_REPEAT_MASK
mdefine_line|#define PWMC_REPEAT_MASK&t;0x000c&t;/* Sample Repeats */
DECL|macro|PWMC_REPEAT_SHIFT
mdefine_line|#define PWMC_REPEAT_SHIFT&t;2
DECL|macro|PWMC_EN
mdefine_line|#define PWMC_EN&t;&t;&t;0x0010&t;/* Enable PWM */
DECL|macro|PMNC_FIFOAV
mdefine_line|#define PMNC_FIFOAV&t;&t;0x0020&t;/* FIFO Available */
DECL|macro|PWMC_IRQEN
mdefine_line|#define PWMC_IRQEN&t;&t;0x0040&t;/* Interrupt Request Enable */
DECL|macro|PWMC_IRQ
mdefine_line|#define PWMC_IRQ&t;&t;0x0080&t;/* Interrupt Request (FIFO empty) */
DECL|macro|PWMC_PRESCALER_MASK
mdefine_line|#define PWMC_PRESCALER_MASK&t;0x7f00&t;/* Incoming Clock prescaler */
DECL|macro|PWMC_PRESCALER_SHIFT
mdefine_line|#define PWMC_PRESCALER_SHIFT&t;8
DECL|macro|PWMC_CLKSRC
mdefine_line|#define PWMC_CLKSRC&t;&t;0x8000&t;/* Clock Source Select */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|PWMC_PWMEN
mdefine_line|#define PWMC_PWMEN&t;PWMC_EN
multiline_comment|/*&n; * PWM Sample Register &n; */
DECL|macro|PWMS_ADDR
mdefine_line|#define PWMS_ADDR&t;0xfffff502
DECL|macro|PWMS
mdefine_line|#define PWMS&t;&t;WORD_REF(PWMS_ADDR)
multiline_comment|/*&n; * PWM Period Register&n; */
DECL|macro|PWMP_ADDR
mdefine_line|#define PWMP_ADDR&t;0xfffff504
DECL|macro|PWMP
mdefine_line|#define PWMP&t;&t;BYTE_REF(PWMP_ADDR)
multiline_comment|/*&n; * PWM Counter Register&n; */
DECL|macro|PWMCNT_ADDR
mdefine_line|#define PWMCNT_ADDR&t;0xfffff505
DECL|macro|PWMCNT
mdefine_line|#define PWMCNT&t;&t;BYTE_REF(PWMCNT_ADDR)
multiline_comment|/**********&n; *&n; * 0xFFFFF6xx -- General-Purpose Timer&n; *&n; **********/
multiline_comment|/* &n; * Timer Control register&n; */
DECL|macro|TCTL_ADDR
mdefine_line|#define TCTL_ADDR&t;0xfffff600
DECL|macro|TCTL
mdefine_line|#define TCTL&t;&t;WORD_REF(TCTL_ADDR)
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
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|TCTL1_ADDR
mdefine_line|#define TCTL1_ADDR&t;TCTL_ADDR
DECL|macro|TCTL1
mdefine_line|#define TCTL1&t;&t;TCTL
multiline_comment|/*&n; * Timer Prescaler Register&n; */
DECL|macro|TPRER_ADDR
mdefine_line|#define TPRER_ADDR&t;0xfffff602
DECL|macro|TPRER
mdefine_line|#define TPRER&t;&t;WORD_REF(TPRER_ADDR)
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|TPRER1_ADDR
mdefine_line|#define TPRER1_ADDR&t;TPRER_ADDR
DECL|macro|TPRER1
mdefine_line|#define TPRER1&t;&t;TPRER
multiline_comment|/*&n; * Timer Compare Register&n; */
DECL|macro|TCMP_ADDR
mdefine_line|#define TCMP_ADDR&t;0xfffff604
DECL|macro|TCMP
mdefine_line|#define TCMP&t;&t;WORD_REF(TCMP_ADDR)
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|TCMP1_ADDR
mdefine_line|#define TCMP1_ADDR&t;TCMP_ADDR
DECL|macro|TCMP1
mdefine_line|#define TCMP1&t;&t;TCMP
multiline_comment|/*&n; * Timer Capture register&n; */
DECL|macro|TCR_ADDR
mdefine_line|#define TCR_ADDR&t;0xfffff606
DECL|macro|TCR
mdefine_line|#define TCR&t;&t;WORD_REF(TCR_ADDR)
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|TCR1_ADDR
mdefine_line|#define TCR1_ADDR&t;TCR_ADDR
DECL|macro|TCR1
mdefine_line|#define TCR1&t;&t;TCR
multiline_comment|/*&n; * Timer Counter Register&n; */
DECL|macro|TCN_ADDR
mdefine_line|#define TCN_ADDR&t;0xfffff608
DECL|macro|TCN
mdefine_line|#define TCN&t;&t;WORD_REF(TCN_ADDR)
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|TCN1_ADDR
mdefine_line|#define TCN1_ADDR&t;TCN_ADDR
DECL|macro|TCN1
mdefine_line|#define TCN1&t;&t;TCN
multiline_comment|/*&n; * Timer Status Register&n; */
DECL|macro|TSTAT_ADDR
mdefine_line|#define TSTAT_ADDR&t;0xfffff60a
DECL|macro|TSTAT
mdefine_line|#define TSTAT&t;&t;WORD_REF(TSTAT_ADDR)
DECL|macro|TSTAT_COMP
mdefine_line|#define TSTAT_COMP&t;0x0001&t;&t;/* Compare Event occurred */
DECL|macro|TSTAT_CAPT
mdefine_line|#define TSTAT_CAPT&t;0x0001&t;&t;/* Capture Event occurred */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|TSTAT1_ADDR
mdefine_line|#define TSTAT1_ADDR&t;TSTAT_ADDR
DECL|macro|TSTAT1
mdefine_line|#define TSTAT1&t;&t;TSTAT
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
DECL|macro|SPIMCONT_IRQ
mdefine_line|#define SPIMCONT_IRQ&t;&t; 0x0080&t;/* Interrupt Request */
DECL|macro|SPIMCONT_XCH
mdefine_line|#define SPIMCONT_XCH&t;&t; 0x0100&t;/* Exchange */
DECL|macro|SPIMCONT_ENABLE
mdefine_line|#define SPIMCONT_ENABLE&t;&t; 0x0200&t;/* Enable SPIM */
DECL|macro|SPIMCONT_DATA_RATE_MASK
mdefine_line|#define SPIMCONT_DATA_RATE_MASK&t; 0xe000&t;/* SPIM Data Rate */
DECL|macro|SPIMCONT_DATA_RATE_SHIFT
mdefine_line|#define SPIMCONT_DATA_RATE_SHIFT 13
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|SPIMCONT_SPIMIRQ
mdefine_line|#define SPIMCONT_SPIMIRQ&t;SPIMCONT_IRQ
DECL|macro|SPIMCONT_SPIMEN
mdefine_line|#define SPIMCONT_SPIMEN&t;&t;SPIMCONT_ENABLE
multiline_comment|/**********&n; *&n; * 0xFFFFF9xx -- UART&n; *&n; **********/
multiline_comment|/*&n; * UART Status/Control Register&n; */
DECL|macro|USTCNT_ADDR
mdefine_line|#define USTCNT_ADDR&t;0xfffff900
DECL|macro|USTCNT
mdefine_line|#define USTCNT&t;&t;WORD_REF(USTCNT_ADDR)
DECL|macro|USTCNT_TXAE
mdefine_line|#define USTCNT_TXAE&t;0x0001&t;/* Transmitter Available Interrupt Enable */
DECL|macro|USTCNT_TXHE
mdefine_line|#define USTCNT_TXHE&t;0x0002&t;/* Transmitter Half Empty Enable */
DECL|macro|USTCNT_TXEE
mdefine_line|#define USTCNT_TXEE&t;0x0004&t;/* Transmitter Empty Interrupt Enable */
DECL|macro|USTCNT_RXRE
mdefine_line|#define USTCNT_RXRE&t;0x0008&t;/* Receiver Ready Interrupt Enable */
DECL|macro|USTCNT_RXHE
mdefine_line|#define USTCNT_RXHE&t;0x0010&t;/* Receiver Half-Full Interrupt Enable */
DECL|macro|USTCNT_RXFE
mdefine_line|#define USTCNT_RXFE&t;0x0020&t;/* Receiver Full Interrupt Enable */
DECL|macro|USTCNT_CTSD
mdefine_line|#define USTCNT_CTSD&t;0x0040&t;/* CTS Delta Interrupt Enable */
DECL|macro|USTCNT_ODEN
mdefine_line|#define USTCNT_ODEN&t;0x0080&t;/* Old Data Interrupt Enable */
DECL|macro|USTCNT_8_7
mdefine_line|#define USTCNT_8_7&t;0x0100&t;/* Eight or seven-bit transmission */
DECL|macro|USTCNT_STOP
mdefine_line|#define USTCNT_STOP&t;0x0200&t;/* Stop bit transmission */
DECL|macro|USTCNT_ODD
mdefine_line|#define USTCNT_ODD&t;0x0400&t;/* Odd Parity */
DECL|macro|USTCNT_PEN
mdefine_line|#define&t;USTCNT_PEN&t;0x0800&t;/* Parity Enable */
DECL|macro|USTCNT_CLKM
mdefine_line|#define USTCNT_CLKM&t;0x1000&t;/* Clock Mode Select */
DECL|macro|USTCNT_TXEN
mdefine_line|#define&t;USTCNT_TXEN&t;0x2000&t;/* Transmitter Enable */
DECL|macro|USTCNT_RXEN
mdefine_line|#define USTCNT_RXEN&t;0x4000&t;/* Receiver Enable */
DECL|macro|USTCNT_UEN
mdefine_line|#define USTCNT_UEN&t;0x8000&t;/* UART Enable */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|USTCNT_TXAVAILEN
mdefine_line|#define USTCNT_TXAVAILEN&t;USTCNT_TXAE
DECL|macro|USTCNT_TXHALFEN
mdefine_line|#define USTCNT_TXHALFEN&t;&t;USTCNT_TXHE
DECL|macro|USTCNT_TXEMPTYEN
mdefine_line|#define USTCNT_TXEMPTYEN&t;USTCNT_TXEE
DECL|macro|USTCNT_RXREADYEN
mdefine_line|#define USTCNT_RXREADYEN&t;USTCNT_RXRE
DECL|macro|USTCNT_RXHALFEN
mdefine_line|#define USTCNT_RXHALFEN&t;&t;USTCNT_RXHE
DECL|macro|USTCNT_RXFULLEN
mdefine_line|#define USTCNT_RXFULLEN&t;&t;USTCNT_RXFE
DECL|macro|USTCNT_CTSDELTAEN
mdefine_line|#define USTCNT_CTSDELTAEN&t;USTCNT_CTSD
DECL|macro|USTCNT_ODD_EVEN
mdefine_line|#define USTCNT_ODD_EVEN&t;&t;USTCNT_ODD
DECL|macro|USTCNT_PARITYEN
mdefine_line|#define USTCNT_PARITYEN&t;&t;USTCNT_PEN
DECL|macro|USTCNT_CLKMODE
mdefine_line|#define USTCNT_CLKMODE&t;&t;USTCNT_CLKM
DECL|macro|USTCNT_UARTEN
mdefine_line|#define USTCNT_UARTEN&t;&t;USTCNT_UEN
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
DECL|macro|UBAUD_UCLKDIR
mdefine_line|#define UBAUD_UCLKDIR&t;&t;0x2000&t;/* UCLK Direction */
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
DECL|macro|URX_OLD_DATA
mdefine_line|#define URX_OLD_DATA&t; 0x1000&t;/* Old data in FIFO */
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
DECL|macro|UTX_CTS_STAT
mdefine_line|#define UTX_CTS_STAT&t; 0x0200&t;/* CTS State */
DECL|macro|UTX_BUSY
mdefine_line|#define&t;UTX_BUSY&t; 0x0400&t;/* FIFO is busy, sending a character */
DECL|macro|UTX_NOCTS
mdefine_line|#define&t;UTX_NOCTS&t; 0x0800&t;/* Ignore CTS */
DECL|macro|UTX_SEND_BREAK
mdefine_line|#define UTX_SEND_BREAK&t; 0x1000&t;/* Send a BREAK */
DECL|macro|UTX_TX_AVAIL
mdefine_line|#define UTX_TX_AVAIL&t; 0x2000&t;/* Transmit FIFO has a slot available */
DECL|macro|UTX_FIFO_HALF
mdefine_line|#define UTX_FIFO_HALF&t; 0x4000&t;/* Transmit FIFO is half empty */
DECL|macro|UTX_FIFO_EMPTY
mdefine_line|#define UTX_FIFO_EMPTY&t; 0x8000&t;/* Transmit FIFO is empty */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|UTX_CTS_STATUS
mdefine_line|#define UTX_CTS_STATUS&t;UTX_CTS_STAT
DECL|macro|UTX_IGNORE_CTS
mdefine_line|#define UTX_IGNORE_CTS&t;UTX_NOCTS
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
DECL|macro|UMISC_IR_TEST
mdefine_line|#define UMISC_IR_TEST&t; 0x0400&t;/* IRDA Test Enable */
DECL|macro|UMISC_BAUD_RESET
mdefine_line|#define UMISC_BAUD_RESET 0x0800&t;/* Reset Baud Rate Generation Counters */
DECL|macro|UMISC_LOOP
mdefine_line|#define UMISC_LOOP&t; 0x1000&t;/* Serial Loopback Enable */
DECL|macro|UMISC_FORCE_PERR
mdefine_line|#define UMISC_FORCE_PERR 0x2000&t;/* Force Parity Error */
DECL|macro|UMISC_CLKSRC
mdefine_line|#define UMISC_CLKSRC&t; 0x4000&t;/* Clock Source */
DECL|macro|UMISC_BAUD_TEST
mdefine_line|#define UMISC_BAUD_TEST&t; 0x8000&t;/* Enable Baud Test Mode */
multiline_comment|/* &n; * UART Non-integer Prescaler Register&n; */
DECL|macro|NIPR_ADDR
mdefine_line|#define NIPR_ADDR&t;0xfffff90a
DECL|macro|NIPR
mdefine_line|#define NIPR&t;&t;WORD_REF(NIPR_ADDR)
DECL|macro|NIPR_STEP_VALUE_MASK
mdefine_line|#define NIPR_STEP_VALUE_MASK&t;0x00ff&t;/* NI prescaler step value */
DECL|macro|NIPR_STEP_VALUE_SHIFT
mdefine_line|#define NIPR_STEP_VALUE_SHIFT&t;0
DECL|macro|NIPR_SELECT_MASK
mdefine_line|#define NIPR_SELECT_MASK&t;0x0700&t;/* Tap Selection */
DECL|macro|NIPR_SELECT_SHIFT
mdefine_line|#define NIPR_SELECT_SHIFT&t;8
DECL|macro|NIPR_PRE_SEL
mdefine_line|#define NIPR_PRE_SEL&t;&t;0x8000&t;/* Non-integer prescaler select */
multiline_comment|/* generalization of uart control registers to support multiple ports: */
r_typedef
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
DECL|member|nipr
r_volatile
r_int
r_int
r_int
id|nipr
suffix:semicolon
DECL|member|hmark
r_volatile
r_int
r_int
r_int
id|hmark
suffix:semicolon
DECL|member|unused
r_volatile
r_int
r_int
r_int
id|unused
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
mdefine_line|#define LSSA_SSA_MASK&t;0x1ffffffe&t;/* Bits 0 and 29-31 are reserved */
multiline_comment|/*&n; * LCD Virtual Page Width Register &n; */
DECL|macro|LVPW_ADDR
mdefine_line|#define LVPW_ADDR&t;0xfffffa05
DECL|macro|LVPW
mdefine_line|#define LVPW&t;&t;BYTE_REF(LVPW_ADDR)
multiline_comment|/*&n; * LCD Screen Width Register (not compatible with &squot;328 !!!) &n; */
DECL|macro|LXMAX_ADDR
mdefine_line|#define LXMAX_ADDR&t;0xfffffa08
DECL|macro|LXMAX
mdefine_line|#define LXMAX&t;&t;WORD_REF(LXMAX_ADDR)
DECL|macro|LXMAX_XM_MASK
mdefine_line|#define LXMAX_XM_MASK&t;0x02f0&t;&t;/* Bits 0-3 and 10-15 are reserved */
multiline_comment|/*&n; * LCD Screen Height Register&n; */
DECL|macro|LYMAX_ADDR
mdefine_line|#define LYMAX_ADDR&t;0xfffffa0a
DECL|macro|LYMAX
mdefine_line|#define LYMAX&t;&t;WORD_REF(LYMAX_ADDR)
DECL|macro|LYMAX_YM_MASK
mdefine_line|#define LYMAX_YM_MASK&t;0x01ff&t;&t;/* Bits 9-15 are reserved */
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
mdefine_line|#define LPICF_GS_MASK&t; 0x03&t; /* Gray-Scale Mode */
DECL|macro|LPICF_GS_BW
mdefine_line|#define&t;  LPICF_GS_BW&t;   0x00
DECL|macro|LPICF_GS_GRAY_4
mdefine_line|#define   LPICF_GS_GRAY_4  0x01
DECL|macro|LPICF_GS_GRAY_16
mdefine_line|#define   LPICF_GS_GRAY_16 0x02
DECL|macro|LPICF_PBSIZ_MASK
mdefine_line|#define LPICF_PBSIZ_MASK 0x0c&t;/* Panel Bus Width */
DECL|macro|LPICF_PBSIZ_1
mdefine_line|#define   LPICF_PBSIZ_1&t;   0x00
DECL|macro|LPICF_PBSIZ_2
mdefine_line|#define   LPICF_PBSIZ_2    0x04
DECL|macro|LPICF_PBSIZ_4
mdefine_line|#define   LPICF_PBSIZ_4    0x08
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
DECL|macro|LACDRC_ACDSLT
mdefine_line|#define LACDRC_ACDSLT&t; 0x80&t;/* Signal Source Select */
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
DECL|macro|LCKCON_DWS_MASK
mdefine_line|#define LCKCON_DWS_MASK&t; 0x0f&t;/* Display Wait-State */
DECL|macro|LCKCON_DWS_SHIFT
mdefine_line|#define LCKCON_DWS_SHIFT 0
DECL|macro|LCKCON_DWIDTH
mdefine_line|#define LCKCON_DWIDTH&t; 0x40&t;/* Display Memory Width  */
DECL|macro|LCKCON_LCDON
mdefine_line|#define LCKCON_LCDON&t; 0x80&t;/* Enable LCD Controller */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|LCKCON_DW_MASK
mdefine_line|#define LCKCON_DW_MASK  LCKCON_DWS_MASK
DECL|macro|LCKCON_DW_SHIFT
mdefine_line|#define LCKCON_DW_SHIFT LCKCON_DWS_SHIFT
multiline_comment|/*&n; * LCD Refresh Rate Adjustment Register &n; */
DECL|macro|LRRA_ADDR
mdefine_line|#define LRRA_ADDR&t;0xfffffa29
DECL|macro|LRRA
mdefine_line|#define LRRA&t;&t;BYTE_REF(LRRA_ADDR)
multiline_comment|/*&n; * LCD Panning Offset Register&n; */
DECL|macro|LPOSR_ADDR
mdefine_line|#define LPOSR_ADDR&t;0xfffffa2d
DECL|macro|LPOSR
mdefine_line|#define LPOSR&t;&t;BYTE_REF(LPOSR_ADDR)
DECL|macro|LPOSR_POS_MASK
mdefine_line|#define LPOSR_POS_MASK&t;0x0f&t;/* Pixel Offset Code */
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
mdefine_line|#define LGPMR_ADDR&t;0xfffffa33
DECL|macro|LGPMR
mdefine_line|#define LGPMR&t;&t;BYTE_REF(LGPMR_ADDR)
DECL|macro|LGPMR_G1_MASK
mdefine_line|#define LGPMR_G1_MASK&t;0x0f
DECL|macro|LGPMR_G1_SHIFT
mdefine_line|#define LGPMR_G1_SHIFT&t;0
DECL|macro|LGPMR_G2_MASK
mdefine_line|#define LGPMR_G2_MASK&t;0xf0
DECL|macro|LGPMR_G2_SHIFT
mdefine_line|#define LGPMR_G2_SHIFT&t;4
multiline_comment|/* &n; * PWM Contrast Control Register&n; */
DECL|macro|PWMR_ADDR
mdefine_line|#define PWMR_ADDR&t;0xfffffa36
DECL|macro|PWMR
mdefine_line|#define PWMR&t;&t;WORD_REF(PWMR_ADDR)
DECL|macro|PWMR_PW_MASK
mdefine_line|#define PWMR_PW_MASK&t;0x00ff&t;/* Pulse Width */
DECL|macro|PWMR_PW_SHIFT
mdefine_line|#define PWMR_PW_SHIFT&t;0
DECL|macro|PWMR_CCPEN
mdefine_line|#define PWMR_CCPEN&t;0x0100&t;/* Contrast Control Enable */
DECL|macro|PWMR_SRC_MASK
mdefine_line|#define PWMR_SRC_MASK&t;0x0600&t;/* Input Clock Source */
DECL|macro|PWMR_SRC_LINE
mdefine_line|#define   PWMR_SRC_LINE&t;  0x0000&t;/* Line Pulse  */
DECL|macro|PWMR_SRC_PIXEL
mdefine_line|#define   PWMR_SRC_PIXEL  0x0200&t;/* Pixel Clock */
DECL|macro|PWMR_SRC_LCD
mdefine_line|#define   PWMR_SRC_LCD    0x4000&t;/* LCD clock   */
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
multiline_comment|/*&n; * Watchdog Timer Register &n; */
DECL|macro|WATCHDOG_ADDR
mdefine_line|#define WATCHDOG_ADDR&t;0xfffffb0a
DECL|macro|WATCHDOG
mdefine_line|#define WATCHDOG&t;WORD_REF(WATCHDOG_ADDR)
DECL|macro|WATCHDOG_EN
mdefine_line|#define WATCHDOG_EN&t;0x0001&t;/* Watchdog Enabled */
DECL|macro|WATCHDOG_ISEL
mdefine_line|#define WATCHDOG_ISEL&t;0x0002&t;/* Select the watchdog interrupt */
DECL|macro|WATCHDOG_INTF
mdefine_line|#define WATCHDOG_INTF&t;0x0080&t;/* Watchdog interrupt occcured */
DECL|macro|WATCHDOG_CNT_MASK
mdefine_line|#define WATCHDOG_CNT_MASK  0x0300&t;/* Watchdog Counter */
DECL|macro|WATCHDOG_CNT_SHIFT
mdefine_line|#define WATCHDOG_CNT_SHIFT 8
multiline_comment|/*&n; * RTC Control Register&n; */
DECL|macro|RTCCTL_ADDR
mdefine_line|#define RTCCTL_ADDR&t;0xfffffb0c
DECL|macro|RTCCTL
mdefine_line|#define RTCCTL&t;&t;WORD_REF(RTCCTL_ADDR)
DECL|macro|RTCCTL_XTL
mdefine_line|#define RTCCTL_XTL&t;0x0020&t;/* Crystal Selection */
DECL|macro|RTCCTL_EN
mdefine_line|#define RTCCTL_EN&t;0x0080&t;/* RTC Enable */
multiline_comment|/* &squot;328-compatible definitions */
DECL|macro|RTCCTL_384
mdefine_line|#define RTCCTL_384&t;RTCCTL_XTL
DECL|macro|RTCCTL_ENABLE
mdefine_line|#define RTCCTL_ENABLE&t;RTCCTL_EN
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
DECL|macro|RTCISR_HR
mdefine_line|#define RTCISR_HR&t;0x0020&t;/* 1-hour interrupt has occured */
DECL|macro|RTCISR_SAM0
mdefine_line|#define RTCISR_SAM0&t;0x0100&t;/*   4Hz /   4.6875Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM1
mdefine_line|#define RTCISR_SAM1&t;0x0200&t;/*   8Hz /   9.3750Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM2
mdefine_line|#define RTCISR_SAM2&t;0x0400&t;/*  16Hz /  18.7500Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM3
mdefine_line|#define RTCISR_SAM3&t;0x0800&t;/*  32Hz /  37.5000Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM4
mdefine_line|#define RTCISR_SAM4&t;0x1000&t;/*  64Hz /  75.0000Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM5
mdefine_line|#define RTCISR_SAM5&t;0x2000&t;/* 128Hz / 150.0000Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM6
mdefine_line|#define RTCISR_SAM6&t;0x4000&t;/* 256Hz / 300.0000Hz interrupt has occured */ 
DECL|macro|RTCISR_SAM7
mdefine_line|#define RTCISR_SAM7&t;0x8000&t;/* 512Hz / 600.0000Hz interrupt has occured */ 
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
DECL|macro|RTCIENR_HR
mdefine_line|#define RTCIENR_HR&t;0x0020&t;/* 1-hour interrupt enable */
DECL|macro|RTCIENR_SAM0
mdefine_line|#define RTCIENR_SAM0&t;0x0100&t;/*   4Hz /   4.6875Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM1
mdefine_line|#define RTCIENR_SAM1&t;0x0200&t;/*   8Hz /   9.3750Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM2
mdefine_line|#define RTCIENR_SAM2&t;0x0400&t;/*  16Hz /  18.7500Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM3
mdefine_line|#define RTCIENR_SAM3&t;0x0800&t;/*  32Hz /  37.5000Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM4
mdefine_line|#define RTCIENR_SAM4&t;0x1000&t;/*  64Hz /  75.0000Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM5
mdefine_line|#define RTCIENR_SAM5&t;0x2000&t;/* 128Hz / 150.0000Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM6
mdefine_line|#define RTCIENR_SAM6&t;0x4000&t;/* 256Hz / 300.0000Hz interrupt enable */ 
DECL|macro|RTCIENR_SAM7
mdefine_line|#define RTCIENR_SAM7&t;0x8000&t;/* 512Hz / 600.0000Hz interrupt enable */ 
multiline_comment|/* &n; * Stopwatch Minutes Register&n; */
DECL|macro|STPWCH_ADDR
mdefine_line|#define STPWCH_ADDR&t;0xfffffb12
DECL|macro|STPWCH
mdefine_line|#define STPWCH&t;&t;WORD_REF(STPWCH_ADDR)
DECL|macro|STPWCH_CNT_MASK
mdefine_line|#define STPWCH_CNT_MASK&t; 0x003f&t;/* Stopwatch countdown value */
DECL|macro|SPTWCH_CNT_SHIFT
mdefine_line|#define SPTWCH_CNT_SHIFT 0
multiline_comment|/*&n; * RTC Day Count Register &n; */
DECL|macro|DAYR_ADDR
mdefine_line|#define DAYR_ADDR&t;0xfffffb1a
DECL|macro|DAYR
mdefine_line|#define DAYR&t;&t;WORD_REF(DAYR_ADDR)
DECL|macro|DAYR_DAYS_MASK
mdefine_line|#define DAYR_DAYS_MASK&t;0x1ff&t;/* Day Setting */
DECL|macro|DAYR_DAYS_SHIFT
mdefine_line|#define DAYR_DAYS_SHIFT 0
multiline_comment|/*&n; * RTC Day Alarm Register &n; */
DECL|macro|DAYALARM_ADDR
mdefine_line|#define DAYALARM_ADDR&t;0xfffffb1c
DECL|macro|DAYALARM
mdefine_line|#define DAYALARM&t;WORD_REF(DAYALARM_ADDR)
DECL|macro|DAYALARM_DAYSAL_MASK
mdefine_line|#define DAYALARM_DAYSAL_MASK&t;0x01ff&t;/* Day Setting of the Alarm */
DECL|macro|DAYALARM_DAYSAL_SHIFT
mdefine_line|#define DAYALARM_DAYSAL_SHIFT &t;0
multiline_comment|/**********&n; *&n; * 0xFFFFFCxx -- DRAM Controller&n; *&n; **********/
multiline_comment|/*&n; * DRAM Memory Configuration Register &n; */
DECL|macro|DRAMMC_ADDR
mdefine_line|#define DRAMMC_ADDR&t;0xfffffc00
DECL|macro|DRAMMC
mdefine_line|#define DRAMMC&t;&t;WORD_REF(DRAMMC_ADDR)
DECL|macro|DRAMMC_ROW12_MASK
mdefine_line|#define DRAMMC_ROW12_MASK&t;0xc000&t;/* Row address bit for MD12 */
DECL|macro|DRAMMC_ROW12_PA10
mdefine_line|#define   DRAMMC_ROW12_PA10&t;0x0000
DECL|macro|DRAMMC_ROW12_PA21
mdefine_line|#define   DRAMMC_ROW12_PA21&t;0x4000&t;
DECL|macro|DRAMMC_ROW12_PA23
mdefine_line|#define   DRAMMC_ROW12_PA23&t;0x8000
DECL|macro|DRAMMC_ROW0_MASK
mdefine_line|#define&t;DRAMMC_ROW0_MASK&t;0x3000&t;/* Row address bit for MD0 */
DECL|macro|DRAMMC_ROW0_PA11
mdefine_line|#define&t;  DRAMMC_ROW0_PA11&t;0x0000
DECL|macro|DRAMMC_ROW0_PA22
mdefine_line|#define   DRAMMC_ROW0_PA22&t;0x1000
DECL|macro|DRAMMC_ROW0_PA23
mdefine_line|#define   DRAMMC_ROW0_PA23&t;0x2000
DECL|macro|DRAMMC_ROW11
mdefine_line|#define DRAMMC_ROW11&t;&t;0x0800&t;/* Row address bit for MD11 PA20/PA22 */
DECL|macro|DRAMMC_ROW10
mdefine_line|#define DRAMMC_ROW10&t;&t;0x0400&t;/* Row address bit for MD10 PA19/PA21 */
DECL|macro|DRAMMC_ROW9
mdefine_line|#define&t;DRAMMC_ROW9&t;&t;0x0200&t;/* Row address bit for MD9  PA9/PA19  */
DECL|macro|DRAMMC_ROW8
mdefine_line|#define DRAMMC_ROW8&t;&t;0x0100&t;/* Row address bit for MD8  PA10/PA20 */
DECL|macro|DRAMMC_COL10
mdefine_line|#define DRAMMC_COL10&t;&t;0x0080&t;/* Col address bit for MD10 PA11/PA0  */
DECL|macro|DRAMMC_COL9
mdefine_line|#define DRAMMC_COL9&t;&t;0x0040&t;/* Col address bit for MD9  PA10/PA0  */
DECL|macro|DRAMMC_COL8
mdefine_line|#define DRAMMC_COL8&t;&t;0x0020&t;/* Col address bit for MD8  PA9/PA0   */
DECL|macro|DRAMMC_REF_MASK
mdefine_line|#define DRAMMC_REF_MASK&t;&t;0x001f&t;/* Reresh Cycle */
DECL|macro|DRAMMC_REF_SHIFT
mdefine_line|#define DRAMMC_REF_SHIFT&t;0
multiline_comment|/*&n; * DRAM Control Register&n; */
DECL|macro|DRAMC_ADDR
mdefine_line|#define DRAMC_ADDR&t;0xfffffc02
DECL|macro|DRAMC
mdefine_line|#define DRAMC&t;&t;WORD_REF(DRAMC_ADDR)
DECL|macro|DRAMC_DWE
mdefine_line|#define DRAMC_DWE&t;   0x0001&t;/* DRAM Write Enable */
DECL|macro|DRAMC_RST
mdefine_line|#define DRAMC_RST&t;   0x0002&t;/* Reset Burst Refresh Enable */
DECL|macro|DRAMC_LPR
mdefine_line|#define DRAMC_LPR&t;   0x0004&t;/* Low-Power Refresh Enable */
DECL|macro|DRAMC_SLW
mdefine_line|#define DRAMC_SLW&t;   0x0008&t;/* Slow RAM */
DECL|macro|DRAMC_LSP
mdefine_line|#define DRAMC_LSP&t;   0x0010&t;/* Light Sleep */
DECL|macro|DRAMC_MSW
mdefine_line|#define DRAMC_MSW&t;   0x0020&t;/* Slow Multiplexing */
DECL|macro|DRAMC_WS_MASK
mdefine_line|#define DRAMC_WS_MASK&t;   0x00c0&t;/* Wait-states */
DECL|macro|DRAMC_WS_SHIFT
mdefine_line|#define DRAMC_WS_SHIFT&t;   6
DECL|macro|DRAMC_PGSZ_MASK
mdefine_line|#define DRAMC_PGSZ_MASK    0x0300&t;/* Page Size for fast page mode */
DECL|macro|DRAMC_PGSZ_SHIFT
mdefine_line|#define DRAMC_PGSZ_SHIFT   8
DECL|macro|DRAMC_PGSZ_256K
mdefine_line|#define   DRAMC_PGSZ_256K  0x0000&t;
DECL|macro|DRAMC_PGSZ_512K
mdefine_line|#define   DRAMC_PGSZ_512K  0x0100
DECL|macro|DRAMC_PGSZ_1024K
mdefine_line|#define   DRAMC_PGSZ_1024K 0x0200
DECL|macro|DRAMC_PGSZ_2048K
mdefine_line|#define&t;  DRAMC_PGSZ_2048K 0x0300
DECL|macro|DRAMC_EDO
mdefine_line|#define DRAMC_EDO&t;   0x0400&t;/* EDO DRAM */
DECL|macro|DRAMC_CLK
mdefine_line|#define DRAMC_CLK&t;   0x0800&t;/* Refresh Timer Clock source select */
DECL|macro|DRAMC_BC_MASK
mdefine_line|#define DRAMC_BC_MASK&t;   0x3000&t;/* Page Access Clock Cycle (FP mode) */
DECL|macro|DRAMC_BC_SHIFT
mdefine_line|#define DRAMC_BC_SHIFT&t;   12
DECL|macro|DRAMC_RM
mdefine_line|#define DRAMC_RM&t;   0x4000&t;/* Refresh Mode */
DECL|macro|DRAMC_EN
mdefine_line|#define DRAMC_EN&t;   0x8000&t;/* DRAM Controller enable */
multiline_comment|/**********&n; *&n; * 0xFFFFFDxx -- In-Circuit Emulation (ICE)&n; *&n; **********/
multiline_comment|/*&n; * ICE Module Address Compare Register&n; */
DECL|macro|ICEMACR_ADDR
mdefine_line|#define ICEMACR_ADDR&t;0xfffffd00
DECL|macro|ICEMACR
mdefine_line|#define ICEMACR&t;&t;LONG_REF(ICEMACR_ADDR)
multiline_comment|/*&n; * ICE Module Address Mask Register&n; */
DECL|macro|ICEMAMR_ADDR
mdefine_line|#define ICEMAMR_ADDR&t;0xfffffd04
DECL|macro|ICEMAMR
mdefine_line|#define ICEMAMR&t;&t;LONG_REF(ICEMAMR_ADDR)
multiline_comment|/*&n; * ICE Module Control Compare Register&n; */
DECL|macro|ICEMCCR_ADDR
mdefine_line|#define ICEMCCR_ADDR&t;0xfffffd08
DECL|macro|ICEMCCR
mdefine_line|#define ICEMCCR&t;&t;WORD_REF(ICEMCCR_ADDR)
DECL|macro|ICEMCCR_PD
mdefine_line|#define ICEMCCR_PD&t;0x0001&t;/* Program/Data Cycle Selection */
DECL|macro|ICEMCCR_RW
mdefine_line|#define ICEMCCR_RW&t;0x0002&t;/* Read/Write Cycle Selection */
multiline_comment|/*&n; * ICE Module Control Mask Register&n; */
DECL|macro|ICEMCMR_ADDR
mdefine_line|#define ICEMCMR_ADDR&t;0xfffffd0a
DECL|macro|ICEMCMR
mdefine_line|#define ICEMCMR&t;&t;WORD_REF(ICEMCMR_ADDR)
DECL|macro|ICEMCMR_PDM
mdefine_line|#define ICEMCMR_PDM&t;0x0001&t;/* Program/Data Cycle Mask */
DECL|macro|ICEMCMR_RWM
mdefine_line|#define ICEMCMR_RWM&t;0x0002&t;/* Read/Write Cycle Mask */
multiline_comment|/*&n; * ICE Module Control Register &n; */
DECL|macro|ICEMCR_ADDR
mdefine_line|#define ICEMCR_ADDR&t;0xfffffd0c
DECL|macro|ICEMCR
mdefine_line|#define ICEMCR&t;&t;WORD_REF(ICEMCR_ADDR)
DECL|macro|ICEMCR_CEN
mdefine_line|#define ICEMCR_CEN&t;0x0001&t;/* Compare Enable */
DECL|macro|ICEMCR_PBEN
mdefine_line|#define ICEMCR_PBEN&t;0x0002&t;/* Program Break Enable */
DECL|macro|ICEMCR_SB
mdefine_line|#define ICEMCR_SB&t;0x0004&t;/* Single Breakpoint */
DECL|macro|ICEMCR_HMDIS
mdefine_line|#define ICEMCR_HMDIS&t;0x0008&t;/* HardMap disable */
DECL|macro|ICEMCR_BBIEN
mdefine_line|#define ICEMCR_BBIEN&t;0x0010&t;/* Bus Break Interrupt Enable */
multiline_comment|/*&n; * ICE Module Status Register &n; */
DECL|macro|ICEMSR_ADDR
mdefine_line|#define ICEMSR_ADDR&t;0xfffffd0e
DECL|macro|ICEMSR
mdefine_line|#define ICEMSR&t;&t;WORD_REF(ICEMSR_ADDR)
DECL|macro|ICEMSR_EMUEN
mdefine_line|#define ICEMSR_EMUEN&t;0x0001&t;/* Emulation Enable */
DECL|macro|ICEMSR_BRKIRQ
mdefine_line|#define ICEMSR_BRKIRQ&t;0x0002&t;/* A-Line Vector Fetch Detected */
DECL|macro|ICEMSR_BBIRQ
mdefine_line|#define ICEMSR_BBIRQ&t;0x0004&t;/* Bus Break Interrupt Detected */
DECL|macro|ICEMSR_EMIRQ
mdefine_line|#define ICEMSR_EMIRQ&t;0x0008&t;/* EMUIRQ Falling Edge Detected */
macro_line|#endif /* _MC68VZ328_H_ */
eof
