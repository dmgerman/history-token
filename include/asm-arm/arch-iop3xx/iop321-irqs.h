multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/irqs.h&n; *&n; * Author:&t;Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright:&t;(C) 2002 Rory Bolt&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef _IOP321_IRQS_H_
DECL|macro|_IOP321_IRQS_H_
mdefine_line|#define _IOP321_IRQS_H_
multiline_comment|/*&n; * IOP80321 chipset interrupts&n; */
DECL|macro|IOP321_IRQ_OFS
mdefine_line|#define IOP321_IRQ_OFS&t;&t;0
DECL|macro|IOP321_IRQ
mdefine_line|#define IOP321_IRQ(x)&t;&t;(IOP321_IRQ_OFS + (x))
multiline_comment|/*&n; * On IRQ or FIQ register&n; */
DECL|macro|IRQ_IOP321_DMA0_EOT
mdefine_line|#define IRQ_IOP321_DMA0_EOT&t;IOP321_IRQ(0)
DECL|macro|IRQ_IOP321_DMA0_EOC
mdefine_line|#define IRQ_IOP321_DMA0_EOC&t;IOP321_IRQ(1)
DECL|macro|IRQ_IOP321_DMA1_EOT
mdefine_line|#define IRQ_IOP321_DMA1_EOT&t;IOP321_IRQ(2)
DECL|macro|IRQ_IOP321_DMA1_EOC
mdefine_line|#define IRQ_IOP321_DMA1_EOC&t;IOP321_IRQ(3)
DECL|macro|IRQ_IOP321_RSVD_4
mdefine_line|#define IRQ_IOP321_RSVD_4&t;IOP321_IRQ(4)
DECL|macro|IRQ_IOP321_RSVD_5
mdefine_line|#define IRQ_IOP321_RSVD_5&t;IOP321_IRQ(5)
DECL|macro|IRQ_IOP321_AA_EOT
mdefine_line|#define IRQ_IOP321_AA_EOT&t;IOP321_IRQ(6)
DECL|macro|IRQ_IOP321_AA_EOC
mdefine_line|#define IRQ_IOP321_AA_EOC&t;IOP321_IRQ(7)
DECL|macro|IRQ_IOP321_CORE_PMON
mdefine_line|#define IRQ_IOP321_CORE_PMON&t;IOP321_IRQ(8)
DECL|macro|IRQ_IOP321_TIMER0
mdefine_line|#define IRQ_IOP321_TIMER0&t;IOP321_IRQ(9)
DECL|macro|IRQ_IOP321_TIMER1
mdefine_line|#define IRQ_IOP321_TIMER1&t;IOP321_IRQ(10)
DECL|macro|IRQ_IOP321_I2C_0
mdefine_line|#define IRQ_IOP321_I2C_0&t;IOP321_IRQ(11)
DECL|macro|IRQ_IOP321_I2C_1
mdefine_line|#define IRQ_IOP321_I2C_1&t;IOP321_IRQ(12)
DECL|macro|IRQ_IOP321_MESSAGING
mdefine_line|#define IRQ_IOP321_MESSAGING&t;IOP321_IRQ(13)
DECL|macro|IRQ_IOP321_ATU_BIST
mdefine_line|#define IRQ_IOP321_ATU_BIST&t;IOP321_IRQ(14)
DECL|macro|IRQ_IOP321_PERFMON
mdefine_line|#define IRQ_IOP321_PERFMON&t;IOP321_IRQ(15)
DECL|macro|IRQ_IOP321_CORE_PMU
mdefine_line|#define IRQ_IOP321_CORE_PMU&t;IOP321_IRQ(16)
DECL|macro|IRQ_IOP321_BIU_ERR
mdefine_line|#define IRQ_IOP321_BIU_ERR&t;IOP321_IRQ(17)
DECL|macro|IRQ_IOP321_ATU_ERR
mdefine_line|#define IRQ_IOP321_ATU_ERR&t;IOP321_IRQ(18)
DECL|macro|IRQ_IOP321_MCU_ERR
mdefine_line|#define IRQ_IOP321_MCU_ERR&t;IOP321_IRQ(19)
DECL|macro|IRQ_IOP321_DMA0_ERR
mdefine_line|#define IRQ_IOP321_DMA0_ERR&t;IOP321_IRQ(20)
DECL|macro|IRQ_IOP321_DMA1_ERR
mdefine_line|#define IRQ_IOP321_DMA1_ERR&t;IOP321_IRQ(21)
DECL|macro|IRQ_IOP321_RSVD_22
mdefine_line|#define IRQ_IOP321_RSVD_22&t;IOP321_IRQ(22)
DECL|macro|IRQ_IOP321_AA_ERR
mdefine_line|#define IRQ_IOP321_AA_ERR&t;IOP321_IRQ(23)
DECL|macro|IRQ_IOP321_MSG_ERR
mdefine_line|#define IRQ_IOP321_MSG_ERR&t;IOP321_IRQ(24)
DECL|macro|IRQ_IOP321_SSP
mdefine_line|#define IRQ_IOP321_SSP&t;&t;IOP321_IRQ(25)
DECL|macro|IRQ_IOP321_RSVD_26
mdefine_line|#define IRQ_IOP321_RSVD_26&t;IOP321_IRQ(26)
DECL|macro|IRQ_IOP321_XINT0
mdefine_line|#define IRQ_IOP321_XINT0&t;IOP321_IRQ(27)
DECL|macro|IRQ_IOP321_XINT1
mdefine_line|#define IRQ_IOP321_XINT1&t;IOP321_IRQ(28)
DECL|macro|IRQ_IOP321_XINT2
mdefine_line|#define IRQ_IOP321_XINT2&t;IOP321_IRQ(29)
DECL|macro|IRQ_IOP321_XINT3
mdefine_line|#define IRQ_IOP321_XINT3&t;IOP321_IRQ(30)
DECL|macro|IRQ_IOP321_HPI
mdefine_line|#define IRQ_IOP321_HPI&t;&t;IOP321_IRQ(31)
DECL|macro|NR_IOP321_IRQS
mdefine_line|#define NR_IOP321_IRQS&t;&t;(IOP321_IRQ(31) + 1)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;NR_IOP321_IRQS
multiline_comment|/*&n; * Interrupts available on the IQ80321 board&n; */
multiline_comment|/*&n; * On board devices&n; */
DECL|macro|IRQ_IQ80321_I82544
mdefine_line|#define&t;IRQ_IQ80321_I82544&t;IRQ_IOP321_XINT0
DECL|macro|IRQ_IQ80321_UART
mdefine_line|#define IRQ_IQ80321_UART&t;IRQ_IOP321_XINT1
multiline_comment|/*&n; * PCI interrupts&n; */
DECL|macro|IRQ_IQ80321_INTA
mdefine_line|#define&t;IRQ_IQ80321_INTA&t;IRQ_IOP321_XINT0
DECL|macro|IRQ_IQ80321_INTB
mdefine_line|#define&t;IRQ_IQ80321_INTB&t;IRQ_IOP321_XINT1
DECL|macro|IRQ_IQ80321_INTC
mdefine_line|#define&t;IRQ_IQ80321_INTC&t;IRQ_IOP321_XINT2
DECL|macro|IRQ_IQ80321_INTD
mdefine_line|#define&t;IRQ_IQ80321_INTD&t;IRQ_IOP321_XINT3
multiline_comment|/*&n; * Interrupts on the IQ31244 board&n; */
multiline_comment|/*&n; * On board devices&n; */
DECL|macro|IRQ_IQ31244_UART
mdefine_line|#define IRQ_IQ31244_UART&t;IRQ_IOP321_XINT1
DECL|macro|IRQ_IQ31244_I82546
mdefine_line|#define&t;IRQ_IQ31244_I82546&t;IRQ_IOP321_XINT0
DECL|macro|IRQ_IQ31244_SATA
mdefine_line|#define IRQ_IQ31244_SATA&t;IRQ_IOP321_XINT2
DECL|macro|IRQ_IQ31244_PCIX_SLOT
mdefine_line|#define&t;IRQ_IQ31244_PCIX_SLOT&t;IRQ_IOP321_XINT3
multiline_comment|/*&n; * PCI interrupts&n; */
DECL|macro|IRQ_IQ31244_INTA
mdefine_line|#define&t;IRQ_IQ31244_INTA&t;IRQ_IOP321_XINT0
DECL|macro|IRQ_IQ31244_INTB
mdefine_line|#define&t;IRQ_IQ31244_INTB&t;IRQ_IOP321_XINT1
DECL|macro|IRQ_IQ31244_INTC
mdefine_line|#define&t;IRQ_IQ31244_INTC&t;IRQ_IOP321_XINT2
DECL|macro|IRQ_IQ31244_INTD
mdefine_line|#define&t;IRQ_IQ31244_INTD&t;IRQ_IOP321_XINT3
macro_line|#endif 
singleline_comment|// _IOP321_IRQ_H_
eof
