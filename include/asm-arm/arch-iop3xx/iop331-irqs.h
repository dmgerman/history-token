multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/irqs.h&n; *&n; * Author:&t;Dave Jiang (dave.jiang@intel.com)&n; * Copyright:&t;(C) 2003 Intel Corp.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef _IOP331_IRQS_H_
DECL|macro|_IOP331_IRQS_H_
mdefine_line|#define _IOP331_IRQS_H_
multiline_comment|/*&n; * IOP80331 chipset interrupts&n; */
DECL|macro|IOP331_IRQ_OFS
mdefine_line|#define IOP331_IRQ_OFS&t;&t;0
DECL|macro|IOP331_IRQ
mdefine_line|#define IOP331_IRQ(x)&t;&t;(IOP331_IRQ_OFS + (x))
multiline_comment|/*&n; * On IRQ or FIQ register&n; */
DECL|macro|IRQ_IOP331_DMA0_EOT
mdefine_line|#define IRQ_IOP331_DMA0_EOT&t;IOP331_IRQ(0)
DECL|macro|IRQ_IOP331_DMA0_EOC
mdefine_line|#define IRQ_IOP331_DMA0_EOC&t;IOP331_IRQ(1)
DECL|macro|IRQ_IOP331_DMA1_EOT
mdefine_line|#define IRQ_IOP331_DMA1_EOT&t;IOP331_IRQ(2)
DECL|macro|IRQ_IOP331_DMA1_EOC
mdefine_line|#define IRQ_IOP331_DMA1_EOC&t;IOP331_IRQ(3)
DECL|macro|IRQ_IOP331_RSVD_4
mdefine_line|#define IRQ_IOP331_RSVD_4&t;IOP331_IRQ(4)
DECL|macro|IRQ_IOP331_RSVD_5
mdefine_line|#define IRQ_IOP331_RSVD_5&t;IOP331_IRQ(5)
DECL|macro|IRQ_IOP331_AA_EOT
mdefine_line|#define IRQ_IOP331_AA_EOT&t;IOP331_IRQ(6)
DECL|macro|IRQ_IOP331_AA_EOC
mdefine_line|#define IRQ_IOP331_AA_EOC&t;IOP331_IRQ(7)
DECL|macro|IRQ_IOP331_TIMER0
mdefine_line|#define IRQ_IOP331_TIMER0&t;IOP331_IRQ(8)
DECL|macro|IRQ_IOP331_TIMER1
mdefine_line|#define IRQ_IOP331_TIMER1&t;IOP331_IRQ(9)
DECL|macro|IRQ_IOP331_I2C_0
mdefine_line|#define IRQ_IOP331_I2C_0&t;IOP331_IRQ(10)
DECL|macro|IRQ_IOP331_I2C_1
mdefine_line|#define IRQ_IOP331_I2C_1&t;IOP331_IRQ(11)
DECL|macro|IRQ_IOP331_MSG
mdefine_line|#define IRQ_IOP331_MSG&t;    IOP331_IRQ(12)
DECL|macro|IRQ_IOP331_MSGIBQ
mdefine_line|#define IRQ_IOP331_MSGIBQ   IOP331_IRQ(13)
DECL|macro|IRQ_IOP331_ATU_BIST
mdefine_line|#define IRQ_IOP331_ATU_BIST&t;IOP331_IRQ(14)
DECL|macro|IRQ_IOP331_PERFMON
mdefine_line|#define IRQ_IOP331_PERFMON&t;IOP331_IRQ(15)
DECL|macro|IRQ_IOP331_CORE_PMU
mdefine_line|#define IRQ_IOP331_CORE_PMU&t;IOP331_IRQ(16)
DECL|macro|IRQ_IOP331_RSVD_17
mdefine_line|#define IRQ_IOP331_RSVD_17&t;IOP331_IRQ(17)
DECL|macro|IRQ_IOP331_RSVD_18
mdefine_line|#define IRQ_IOP331_RSVD_18&t;IOP331_IRQ(18)
DECL|macro|IRQ_IOP331_RSVD_19
mdefine_line|#define IRQ_IOP331_RSVD_19&t;IOP331_IRQ(19)
DECL|macro|IRQ_IOP331_RSVD_20
mdefine_line|#define IRQ_IOP331_RSVD_20&t;IOP331_IRQ(20)
DECL|macro|IRQ_IOP331_RSVD_21
mdefine_line|#define IRQ_IOP331_RSVD_21&t;IOP331_IRQ(21)
DECL|macro|IRQ_IOP331_RSVD_22
mdefine_line|#define IRQ_IOP331_RSVD_22&t;IOP331_IRQ(22)
DECL|macro|IRQ_IOP331_RSVD_23
mdefine_line|#define IRQ_IOP331_RSVD_23&t;IOP331_IRQ(23)
DECL|macro|IRQ_IOP331_XINT0
mdefine_line|#define IRQ_IOP331_XINT0&t;IOP331_IRQ(24)
DECL|macro|IRQ_IOP331_XINT1
mdefine_line|#define IRQ_IOP331_XINT1&t;IOP331_IRQ(25)
DECL|macro|IRQ_IOP331_XINT2
mdefine_line|#define IRQ_IOP331_XINT2&t;IOP331_IRQ(26)
DECL|macro|IRQ_IOP331_XINT3
mdefine_line|#define IRQ_IOP331_XINT3&t;IOP331_IRQ(27)
DECL|macro|IRQ_IOP331_RSVD_28
mdefine_line|#define IRQ_IOP331_RSVD_28  IOP331_IRQ(28)
DECL|macro|IRQ_IOP331_RSVD_29
mdefine_line|#define IRQ_IOP331_RSVD_29  IOP331_IRQ(29)
DECL|macro|IRQ_IOP331_RSVD_30
mdefine_line|#define IRQ_IOP331_RSVD_30  IOP331_IRQ(30)
DECL|macro|IRQ_IOP331_RSVD_31
mdefine_line|#define IRQ_IOP331_RSVD_31  IOP331_IRQ(31)
DECL|macro|IRQ_IOP331_XINT8
mdefine_line|#define IRQ_IOP331_XINT8    IOP331_IRQ(32)  
singleline_comment|// 0
DECL|macro|IRQ_IOP331_XINT9
mdefine_line|#define IRQ_IOP331_XINT9    IOP331_IRQ(33)  
singleline_comment|// 1
DECL|macro|IRQ_IOP331_XINT10
mdefine_line|#define IRQ_IOP331_XINT10   IOP331_IRQ(34)  
singleline_comment|// 2
DECL|macro|IRQ_IOP331_XINT11
mdefine_line|#define IRQ_IOP331_XINT11   IOP331_IRQ(35)  
singleline_comment|// 3
DECL|macro|IRQ_IOP331_XINT12
mdefine_line|#define IRQ_IOP331_XINT12   IOP331_IRQ(36)  
singleline_comment|// 4
DECL|macro|IRQ_IOP331_XINT13
mdefine_line|#define IRQ_IOP331_XINT13   IOP331_IRQ(37)  
singleline_comment|// 5
DECL|macro|IRQ_IOP331_XINT14
mdefine_line|#define IRQ_IOP331_XINT14   IOP331_IRQ(38)  
singleline_comment|// 6
DECL|macro|IRQ_IOP331_XINT15
mdefine_line|#define IRQ_IOP331_XINT15   IOP331_IRQ(39)  
singleline_comment|// 7
DECL|macro|IRQ_IOP331_RSVD_40
mdefine_line|#define IRQ_IOP331_RSVD_40  IOP331_IRQ(40)  
singleline_comment|// 8
DECL|macro|IRQ_IOP331_RSVD_41
mdefine_line|#define IRQ_IOP331_RSVD_41  IOP331_IRQ(41)  
singleline_comment|// 9
DECL|macro|IRQ_IOP331_RSVD_42
mdefine_line|#define IRQ_IOP331_RSVD_42  IOP331_IRQ(42)  
singleline_comment|// 10
DECL|macro|IRQ_IOP331_RSVD_43
mdefine_line|#define IRQ_IOP331_RSVD_43  IOP331_IRQ(43)  
singleline_comment|// 11
DECL|macro|IRQ_IOP331_RSVD_44
mdefine_line|#define IRQ_IOP331_RSVD_44  IOP331_IRQ(44)  
singleline_comment|// 12
DECL|macro|IRQ_IOP331_RSVD_45
mdefine_line|#define IRQ_IOP331_RSVD_45  IOP331_IRQ(45)  
singleline_comment|// 13
DECL|macro|IRQ_IOP331_RSVD_46
mdefine_line|#define IRQ_IOP331_RSVD_46  IOP331_IRQ(46)  
singleline_comment|// 14
DECL|macro|IRQ_IOP331_RSVD_47
mdefine_line|#define IRQ_IOP331_RSVD_47  IOP331_IRQ(47)  
singleline_comment|// 15
DECL|macro|IRQ_IOP331_RSVD_48
mdefine_line|#define IRQ_IOP331_RSVD_48  IOP331_IRQ(48)  
singleline_comment|// 16
DECL|macro|IRQ_IOP331_RSVD_49
mdefine_line|#define IRQ_IOP331_RSVD_49  IOP331_IRQ(49)  
singleline_comment|// 17
DECL|macro|IRQ_IOP331_RSVD_50
mdefine_line|#define IRQ_IOP331_RSVD_50  IOP331_IRQ(50)  
singleline_comment|// 18
DECL|macro|IRQ_IOP331_UART0
mdefine_line|#define IRQ_IOP331_UART0    IOP331_IRQ(51)  
singleline_comment|// 19
DECL|macro|IRQ_IOP331_UART1
mdefine_line|#define IRQ_IOP331_UART1    IOP331_IRQ(52)  
singleline_comment|// 20
DECL|macro|IRQ_IOP331_PBIE
mdefine_line|#define IRQ_IOP331_PBIE     IOP331_IRQ(53)  
singleline_comment|// 21
DECL|macro|IRQ_IOP331_ATU_CRW
mdefine_line|#define IRQ_IOP331_ATU_CRW  IOP331_IRQ(54)  
singleline_comment|// 22
DECL|macro|IRQ_IOP331_ATU_ERR
mdefine_line|#define IRQ_IOP331_ATU_ERR&t;IOP331_IRQ(55)  
singleline_comment|// 23
DECL|macro|IRQ_IOP331_MCU_ERR
mdefine_line|#define IRQ_IOP331_MCU_ERR&t;IOP331_IRQ(56)  
singleline_comment|// 24
DECL|macro|IRQ_IOP331_DMA0_ERR
mdefine_line|#define IRQ_IOP331_DMA0_ERR&t;IOP331_IRQ(57)  
singleline_comment|// 25
DECL|macro|IRQ_IOP331_DMA1_ERR
mdefine_line|#define IRQ_IOP331_DMA1_ERR&t;IOP331_IRQ(58)  
singleline_comment|// 26
DECL|macro|IRQ_IOP331_RSVD_59
mdefine_line|#define IRQ_IOP331_RSVD_59  IOP331_IRQ(59)  
singleline_comment|// 27
DECL|macro|IRQ_IOP331_AA_ERR
mdefine_line|#define IRQ_IOP331_AA_ERR&t;IOP331_IRQ(60)  
singleline_comment|// 28
DECL|macro|IRQ_IOP331_RSVD_61
mdefine_line|#define IRQ_IOP331_RSVD_61  IOP331_IRQ(61)  
singleline_comment|// 29
DECL|macro|IRQ_IOP331_MSG_ERR
mdefine_line|#define IRQ_IOP331_MSG_ERR&t;IOP331_IRQ(62)  
singleline_comment|// 30
DECL|macro|IRQ_IOP331_HPI
mdefine_line|#define IRQ_IOP331_HPI&t;&t;IOP331_IRQ(63)  
singleline_comment|// 31
DECL|macro|NR_IOP331_IRQS
mdefine_line|#define NR_IOP331_IRQS&t;&t;(IOP331_IRQ(63) + 1)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;NR_IOP331_IRQS
macro_line|#if defined(CONFIG_ARCH_IQ80331)
multiline_comment|/*&n; * Interrupts available on the IQ80331 board&n; */
multiline_comment|/*&n; * On board devices&n; */
DECL|macro|IRQ_IQ80331_I82544
mdefine_line|#define&t;IRQ_IQ80331_I82544&t;IRQ_IOP331_XINT0
DECL|macro|IRQ_IQ80331_UART0
mdefine_line|#define IRQ_IQ80331_UART0&t;IRQ_IOP331_UART0
DECL|macro|IRQ_IQ80331_UART1
mdefine_line|#define IRQ_IQ80331_UART1&t;IRQ_IOP331_UART1
multiline_comment|/*&n; * PCI interrupts&n; */
DECL|macro|IRQ_IQ80331_INTA
mdefine_line|#define&t;IRQ_IQ80331_INTA&t;IRQ_IOP331_XINT0
DECL|macro|IRQ_IQ80331_INTB
mdefine_line|#define&t;IRQ_IQ80331_INTB&t;IRQ_IOP331_XINT1
DECL|macro|IRQ_IQ80331_INTC
mdefine_line|#define&t;IRQ_IQ80331_INTC&t;IRQ_IOP331_XINT2
DECL|macro|IRQ_IQ80331_INTD
mdefine_line|#define&t;IRQ_IQ80331_INTD&t;IRQ_IOP331_XINT3
macro_line|#elif defined(CONFIG_MACH_IQ80332)
multiline_comment|/*&n; * Interrupts available on the IQ80332 board&n; */
multiline_comment|/*&n; * On board devices&n; */
DECL|macro|IRQ_IQ80332_I82544
mdefine_line|#define&t;IRQ_IQ80332_I82544&t;IRQ_IOP331_XINT0
DECL|macro|IRQ_IQ80332_UART0
mdefine_line|#define IRQ_IQ80332_UART0&t;IRQ_IOP331_UART0
DECL|macro|IRQ_IQ80332_UART1
mdefine_line|#define IRQ_IQ80332_UART1&t;IRQ_IOP331_UART1
multiline_comment|/*&n; * PCI interrupts&n; */
DECL|macro|IRQ_IQ80332_INTA
mdefine_line|#define&t;IRQ_IQ80332_INTA&t;IRQ_IOP331_XINT0
DECL|macro|IRQ_IQ80332_INTB
mdefine_line|#define&t;IRQ_IQ80332_INTB&t;IRQ_IOP331_XINT1
DECL|macro|IRQ_IQ80332_INTC
mdefine_line|#define&t;IRQ_IQ80332_INTC&t;IRQ_IOP331_XINT2
DECL|macro|IRQ_IQ80332_INTD
mdefine_line|#define&t;IRQ_IQ80332_INTD&t;IRQ_IOP331_XINT3
macro_line|#endif
macro_line|#endif 
singleline_comment|// _IOP331_IRQ_H_
eof
