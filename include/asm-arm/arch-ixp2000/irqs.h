multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp2000/irqs.h&n; *&n; * Original Author: Naeem Afzal &lt;naeem.m.afzal@intel.com&gt;&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002 Intel Corp.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IRQS_H
DECL|macro|_IRQS_H
mdefine_line|#define _IRQS_H
multiline_comment|/*&n; * Do NOT add #ifdef MACHINE_FOO in here.&n; * Simpy add your machine IRQs here and increase NR_IRQS if needed to&n; * hold your machine&squot;s IRQ table.&n; */
multiline_comment|/*&n; * Some interrupt numbers go unused b/c the IRQ mask/ummask/status&n; * register has those bit reserved. We just mark those interrupts&n; * as invalid and this allows us to do mask/unmask with a single&n; * shift operation instead of having to map the IRQ number to&n; * a HW IRQ number.&n; */
DECL|macro|IRQ_IXP2000_SWI
mdefine_line|#define&t;IRQ_IXP2000_SWI&t;&t;&t;0 /* soft interrupt */
DECL|macro|IRQ_IXP2000_ERRSUM
mdefine_line|#define&t;IRQ_IXP2000_ERRSUM&t;&t;1 /* OR of all bits in ErrorStatus reg*/
DECL|macro|IRQ_IXP2000_UART
mdefine_line|#define&t;IRQ_IXP2000_UART&t;&t;2
DECL|macro|IRQ_IXP2000_GPIO
mdefine_line|#define&t;IRQ_IXP2000_GPIO&t;&t;3
DECL|macro|IRQ_IXP2000_TIMER1
mdefine_line|#define&t;IRQ_IXP2000_TIMER1     &t;&t;4
DECL|macro|IRQ_IXP2000_TIMER2
mdefine_line|#define&t;IRQ_IXP2000_TIMER2     &t;&t;5
DECL|macro|IRQ_IXP2000_TIMER3
mdefine_line|#define&t;IRQ_IXP2000_TIMER3     &t;&t;6
DECL|macro|IRQ_IXP2000_TIMER4
mdefine_line|#define&t;IRQ_IXP2000_TIMER4     &t;&t;7
DECL|macro|IRQ_IXP2000_PMU
mdefine_line|#define&t;IRQ_IXP2000_PMU        &t;&t;8               
DECL|macro|IRQ_IXP2000_SPF
mdefine_line|#define&t;IRQ_IXP2000_SPF        &t;&t;9  /* Slow port framer IRQ */
DECL|macro|IRQ_IXP2000_DMA1
mdefine_line|#define&t;IRQ_IXP2000_DMA1      &t;&t;10
DECL|macro|IRQ_IXP2000_DMA2
mdefine_line|#define&t;IRQ_IXP2000_DMA2      &t;&t;11
DECL|macro|IRQ_IXP2000_DMA3
mdefine_line|#define&t;IRQ_IXP2000_DMA3      &t;&t;12
DECL|macro|IRQ_IXP2000_PCI_DOORBELL
mdefine_line|#define&t;IRQ_IXP2000_PCI_DOORBELL&t;13
DECL|macro|IRQ_IXP2000_ME_ATTN
mdefine_line|#define&t;IRQ_IXP2000_ME_ATTN       &t;14 
DECL|macro|IRQ_IXP2000_PCI
mdefine_line|#define&t;IRQ_IXP2000_PCI   &t;&t;15 /* PCI INTA or INTB */
DECL|macro|IRQ_IXP2000_THDA0
mdefine_line|#define&t;IRQ_IXP2000_THDA0   &t;&t;16 /* thread 0-31A */
DECL|macro|IRQ_IXP2000_THDA1
mdefine_line|#define&t;IRQ_IXP2000_THDA1  &t;&t;17 /* thread 32-63A */
DECL|macro|IRQ_IXP2000_THDA2
mdefine_line|#define&t;IRQ_IXP2000_THDA2&t;&t;18 /* thread 64-95A, IXP2800 only */
DECL|macro|IRQ_IXP2000_THDA3
mdefine_line|#define&t;IRQ_IXP2000_THDA3 &t;&t;19 /* thread 96-127A, IXP2800 only */
DECL|macro|IRQ_IXP2000_THDB0
mdefine_line|#define&t;IRQ_IXP2000_THDB0&t;&t;24 /* thread 0-31B */
DECL|macro|IRQ_IXP2000_THDB1
mdefine_line|#define&t;IRQ_IXP2000_THDB1&t;&t;25 /* thread 32-63B */
DECL|macro|IRQ_IXP2000_THDB2
mdefine_line|#define&t;IRQ_IXP2000_THDB2&t;&t;26 /* thread 64-95B, IXP2800 only */
DECL|macro|IRQ_IXP2000_THDB3
mdefine_line|#define&t;IRQ_IXP2000_THDB3&t;&t;27 /* thread 96-127B, IXP2800 only */
multiline_comment|/* define generic GPIOs */
DECL|macro|IRQ_IXP2000_GPIO0
mdefine_line|#define IRQ_IXP2000_GPIO0&t;&t;32
DECL|macro|IRQ_IXP2000_GPIO1
mdefine_line|#define IRQ_IXP2000_GPIO1&t;&t;33
DECL|macro|IRQ_IXP2000_GPIO2
mdefine_line|#define IRQ_IXP2000_GPIO2&t;&t;34
DECL|macro|IRQ_IXP2000_GPIO3
mdefine_line|#define IRQ_IXP2000_GPIO3&t;&t;35
DECL|macro|IRQ_IXP2000_GPIO4
mdefine_line|#define IRQ_IXP2000_GPIO4&t;&t;36
DECL|macro|IRQ_IXP2000_GPIO5
mdefine_line|#define IRQ_IXP2000_GPIO5&t;&t;37
DECL|macro|IRQ_IXP2000_GPIO6
mdefine_line|#define IRQ_IXP2000_GPIO6&t;&t;38
DECL|macro|IRQ_IXP2000_GPIO7
mdefine_line|#define IRQ_IXP2000_GPIO7&t;&t;39
multiline_comment|/* split off the 2 PCI sources */
DECL|macro|IRQ_IXP2000_PCIA
mdefine_line|#define IRQ_IXP2000_PCIA&t;&t;40
DECL|macro|IRQ_IXP2000_PCIB
mdefine_line|#define IRQ_IXP2000_PCIB&t;&t;41
multiline_comment|/* Int sources from IRQ_ERROR_STATUS */
DECL|macro|IRQ_IXP2000_DRAM0_MIN_ERR
mdefine_line|#define IRQ_IXP2000_DRAM0_MIN_ERR&t;42
DECL|macro|IRQ_IXP2000_DRAM0_MAJ_ERR
mdefine_line|#define IRQ_IXP2000_DRAM0_MAJ_ERR&t;43
DECL|macro|IRQ_IXP2000_DRAM1_MIN_ERR
mdefine_line|#define IRQ_IXP2000_DRAM1_MIN_ERR&t;44
DECL|macro|IRQ_IXP2000_DRAM1_MAJ_ERR
mdefine_line|#define IRQ_IXP2000_DRAM1_MAJ_ERR&t;45
DECL|macro|IRQ_IXP2000_DRAM2_MIN_ERR
mdefine_line|#define IRQ_IXP2000_DRAM2_MIN_ERR&t;46
DECL|macro|IRQ_IXP2000_DRAM2_MAJ_ERR
mdefine_line|#define IRQ_IXP2000_DRAM2_MAJ_ERR&t;47
DECL|macro|IRQ_IXP2000_SRAM0_ERR
mdefine_line|#define IRQ_IXP2000_SRAM0_ERR&t;&t;48
DECL|macro|IRQ_IXP2000_SRAM1_ERR
mdefine_line|#define IRQ_IXP2000_SRAM1_ERR&t;&t;49
DECL|macro|IRQ_IXP2000_SRAM2_ERR
mdefine_line|#define IRQ_IXP2000_SRAM2_ERR           50
DECL|macro|IRQ_IXP2000_SRAM3_ERR
mdefine_line|#define IRQ_IXP2000_SRAM3_ERR&t;&t;51
DECL|macro|IRQ_IXP2000_MEDIA_ERR
mdefine_line|#define IRQ_IXP2000_MEDIA_ERR&t;&t;52
DECL|macro|IRQ_IXP2000_PCI_ERR
mdefine_line|#define IRQ_IXP2000_PCI_ERR&t;&t;53
DECL|macro|IRQ_IXP2000_SP_INT
mdefine_line|#define IRQ_IXP2000_SP_INT&t;&t;54
DECL|macro|NR_IXP2000_IRQS
mdefine_line|#define NR_IXP2000_IRQS                 55
DECL|macro|IXP2000_BOARD_IRQ
mdefine_line|#define&t;IXP2000_BOARD_IRQ(x)&t;&t;(NR_IXP2000_IRQS + (x))
DECL|macro|IXP2000_BOARD_IRQ_MASK
mdefine_line|#define&t;IXP2000_BOARD_IRQ_MASK(irq)&t;(1 &lt;&lt; (irq - NR_IXP2000_IRQS))&t;
multiline_comment|/*&n; * This allows for all the on-chip sources plus up to 32 CPLD based&n; * IRQs. Should be more than enough.&n; */
DECL|macro|IXP2000_BOARD_IRQS
mdefine_line|#define&t;IXP2000_BOARD_IRQS&t;&t;32
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;&t;(NR_IXP2000_IRQS + IXP2000_BOARD_IRQS)
multiline_comment|/* &n; * IXDP2400 specific IRQs&n; */
DECL|macro|IRQ_IXDP2400_INGRESS_NPU
mdefine_line|#define&t;IRQ_IXDP2400_INGRESS_NPU&t;IXP2000_BOARD_IRQ(0) 
DECL|macro|IRQ_IXDP2400_ENET
mdefine_line|#define&t;IRQ_IXDP2400_ENET&t;&t;IXP2000_BOARD_IRQ(1) 
DECL|macro|IRQ_IXDP2400_MEDIA_PCI
mdefine_line|#define&t;IRQ_IXDP2400_MEDIA_PCI&t;&t;IXP2000_BOARD_IRQ(2) 
DECL|macro|IRQ_IXDP2400_MEDIA_SP
mdefine_line|#define&t;IRQ_IXDP2400_MEDIA_SP&t;&t;IXP2000_BOARD_IRQ(3) 
DECL|macro|IRQ_IXDP2400_SF_PCI
mdefine_line|#define&t;IRQ_IXDP2400_SF_PCI&t;&t;IXP2000_BOARD_IRQ(4) 
DECL|macro|IRQ_IXDP2400_SF_SP
mdefine_line|#define&t;IRQ_IXDP2400_SF_SP&t;&t;IXP2000_BOARD_IRQ(5) 
DECL|macro|IRQ_IXDP2400_PMC
mdefine_line|#define&t;IRQ_IXDP2400_PMC&t;&t;IXP2000_BOARD_IRQ(6) 
DECL|macro|IRQ_IXDP2400_TVM
mdefine_line|#define&t;IRQ_IXDP2400_TVM&t;&t;IXP2000_BOARD_IRQ(7) 
DECL|macro|NR_IXDP2400_IRQS
mdefine_line|#define&t;NR_IXDP2400_IRQS&t;&t;((IRQ_IXDP2400_TVM)+1)  
DECL|macro|IXDP2400_NR_IRQS
mdefine_line|#define&t;IXDP2400_NR_IRQS&t;&t;NR_IXDP2400_IRQS - NR_IXP2000_IRQS
multiline_comment|/* IXDP2800 specific IRQs */
DECL|macro|IRQ_IXDP2800_EGRESS_ENET
mdefine_line|#define IRQ_IXDP2800_EGRESS_ENET&t;IXP2000_BOARD_IRQ(0)
DECL|macro|IRQ_IXDP2800_INGRESS_NPU
mdefine_line|#define IRQ_IXDP2800_INGRESS_NPU&t;IXP2000_BOARD_IRQ(1)
DECL|macro|IRQ_IXDP2800_PMC
mdefine_line|#define IRQ_IXDP2800_PMC&t;&t;IXP2000_BOARD_IRQ(2)
DECL|macro|IRQ_IXDP2800_FABRIC_PCI
mdefine_line|#define IRQ_IXDP2800_FABRIC_PCI&t;&t;IXP2000_BOARD_IRQ(3)
DECL|macro|IRQ_IXDP2800_FABRIC
mdefine_line|#define IRQ_IXDP2800_FABRIC&t;&t;IXP2000_BOARD_IRQ(4)
DECL|macro|IRQ_IXDP2800_MEDIA
mdefine_line|#define IRQ_IXDP2800_MEDIA&t;&t;IXP2000_BOARD_IRQ(5)
DECL|macro|NR_IXDP2800_IRQS
mdefine_line|#define&t;NR_IXDP2800_IRQS&t;&t;((IRQ_IXDP2800_MEDIA)+1)
DECL|macro|IXDP2800_NR_IRQS
mdefine_line|#define&t;IXDP2800_NR_IRQS&t;&t;NR_IXDP2800_IRQS - NR_IXP2000_IRQS
multiline_comment|/* &n; * IRQs on both IXDP2x01 boards&n; */
DECL|macro|IRQ_IXDP2X01_SPCI_DB_0
mdefine_line|#define IRQ_IXDP2X01_SPCI_DB_0&t;&t;IXP2000_BOARD_IRQ(2)
DECL|macro|IRQ_IXDP2X01_SPCI_DB_1
mdefine_line|#define IRQ_IXDP2X01_SPCI_DB_1&t;&t;IXP2000_BOARD_IRQ(3)
DECL|macro|IRQ_IXDP2X01_SPCI_PMC_INTA
mdefine_line|#define IRQ_IXDP2X01_SPCI_PMC_INTA&t;IXP2000_BOARD_IRQ(4)
DECL|macro|IRQ_IXDP2X01_SPCI_PMC_INTB
mdefine_line|#define IRQ_IXDP2X01_SPCI_PMC_INTB&t;IXP2000_BOARD_IRQ(5)
DECL|macro|IRQ_IXDP2X01_SPCI_PMC_INTC
mdefine_line|#define IRQ_IXDP2X01_SPCI_PMC_INTC&t;IXP2000_BOARD_IRQ(6)
DECL|macro|IRQ_IXDP2X01_SPCI_PMC_INTD
mdefine_line|#define IRQ_IXDP2X01_SPCI_PMC_INTD&t;IXP2000_BOARD_IRQ(7)
DECL|macro|IRQ_IXDP2X01_SPCI_FIC_INT
mdefine_line|#define IRQ_IXDP2X01_SPCI_FIC_INT&t;IXP2000_BOARD_IRQ(8)
DECL|macro|IRQ_IXDP2X01_IPMI_FROM
mdefine_line|#define IRQ_IXDP2X01_IPMI_FROM&t;&t;IXP2000_BOARD_IRQ(16)
DECL|macro|IRQ_IXDP2X01_125US
mdefine_line|#define IRQ_IXDP2X01_125US&t;&t;IXP2000_BOARD_IRQ(17)
DECL|macro|IRQ_IXDP2X01_DB_0_ADD
mdefine_line|#define IRQ_IXDP2X01_DB_0_ADD&t;&t;IXP2000_BOARD_IRQ(18)
DECL|macro|IRQ_IXDP2X01_DB_1_ADD
mdefine_line|#define IRQ_IXDP2X01_DB_1_ADD&t;&t;IXP2000_BOARD_IRQ(19)
DECL|macro|IRQ_IXDP2X01_UART1
mdefine_line|#define IRQ_IXDP2X01_UART1&t;&t;IXP2000_BOARD_IRQ(21)
DECL|macro|IRQ_IXDP2X01_UART2
mdefine_line|#define IRQ_IXDP2X01_UART2&t;&t;IXP2000_BOARD_IRQ(22)
DECL|macro|IRQ_IXDP2X01_FIC_ADD_INT
mdefine_line|#define IRQ_IXDP2X01_FIC_ADD_INT&t;IXP2000_BOARD_IRQ(24)
DECL|macro|IRQ_IXDP2X01_CS8900
mdefine_line|#define IRQ_IXDP2X01_CS8900&t;&t;IXP2000_BOARD_IRQ(25)
DECL|macro|IRQ_IXDP2X01_BBSRAM
mdefine_line|#define IRQ_IXDP2X01_BBSRAM&t;&t;IXP2000_BOARD_IRQ(26)
DECL|macro|IXDP2X01_VALID_IRQ_MASK
mdefine_line|#define IXDP2X01_VALID_IRQ_MASK ( &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_DB_0) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_DB_1) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_PMC_INTA) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_PMC_INTB) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_PMC_INTC) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_PMC_INTD) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_SPCI_FIC_INT) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_IPMI_FROM) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_125US) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_DB_0_ADD) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_DB_1_ADD) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_UART1) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_UART2) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_FIC_ADD_INT) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_CS8900) | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2X01_BBSRAM) )
multiline_comment|/* &n; * IXDP2401 specific IRQs&n; */
DECL|macro|IRQ_IXDP2401_INTA_82546
mdefine_line|#define IRQ_IXDP2401_INTA_82546&t;&t;IXP2000_BOARD_IRQ(0)
DECL|macro|IRQ_IXDP2401_INTB_82546
mdefine_line|#define IRQ_IXDP2401_INTB_82546&t;&t;IXP2000_BOARD_IRQ(1)
DECL|macro|IXDP2401_VALID_IRQ_MASK
mdefine_line|#define&t;IXDP2401_VALID_IRQ_MASK ( &bslash;&n;&t;&t;IXDP2X01_VALID_IRQ_MASK | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2401_INTA_82546) |&bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2401_INTB_82546))
multiline_comment|/*&n; * IXDP2801-specific IRQs&n; */
DECL|macro|IRQ_IXDP2801_RIV
mdefine_line|#define IRQ_IXDP2801_RIV&t;&t;IXP2000_BOARD_IRQ(0)
DECL|macro|IRQ_IXDP2801_CNFG_MEDIA
mdefine_line|#define IRQ_IXDP2801_CNFG_MEDIA&t;&t;IXP2000_BOARD_IRQ(27)
DECL|macro|IRQ_IXDP2801_CLOCK_REF
mdefine_line|#define IRQ_IXDP2801_CLOCK_REF&t;&t;IXP2000_BOARD_IRQ(28)
DECL|macro|IXDP2801_VALID_IRQ_MASK
mdefine_line|#define&t;IXDP2801_VALID_IRQ_MASK ( &bslash;&n;&t;&t;IXDP2X01_VALID_IRQ_MASK | &bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2801_RIV) |&bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2801_CNFG_MEDIA) |&bslash;&n;&t;&t;IXP2000_BOARD_IRQ_MASK(IRQ_IXDP2801_CLOCK_REF))
DECL|macro|NR_IXDP2X01_IRQS
mdefine_line|#define&t;NR_IXDP2X01_IRQS&t;&t;((IRQ_IXDP2801_CLOCK_REF) + 1)
macro_line|#endif /*_IRQS_H*/
eof
