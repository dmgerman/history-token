multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/irqs.h &n; *&n; * IRQ definitions for IXP4XX based systems&n; *&n; * Copyright (C) 2002 Intel Corporation.&n; * Copyright (C) 2003 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef _ARCH_IXP4XX_IRQS_H_
DECL|macro|_ARCH_IXP4XX_IRQS_H_
mdefine_line|#define _ARCH_IXP4XX_IRQS_H_
DECL|macro|IRQ_IXP4XX_NPEA
mdefine_line|#define IRQ_IXP4XX_NPEA&t;&t;0
DECL|macro|IRQ_IXP4XX_NPEB
mdefine_line|#define IRQ_IXP4XX_NPEB&t;&t;1
DECL|macro|IRQ_IXP4XX_NPEC
mdefine_line|#define IRQ_IXP4XX_NPEC&t;&t;2
DECL|macro|IRQ_IXP4XX_QM1
mdefine_line|#define IRQ_IXP4XX_QM1&t;&t;3
DECL|macro|IRQ_IXP4XX_QM2
mdefine_line|#define IRQ_IXP4XX_QM2&t;&t;4
DECL|macro|IRQ_IXP4XX_TIMER1
mdefine_line|#define IRQ_IXP4XX_TIMER1&t;5
DECL|macro|IRQ_IXP4XX_GPIO0
mdefine_line|#define IRQ_IXP4XX_GPIO0&t;6
DECL|macro|IRQ_IXP4XX_GPIO1
mdefine_line|#define IRQ_IXP4XX_GPIO1&t;7
DECL|macro|IRQ_IXP4XX_PCI_INT
mdefine_line|#define IRQ_IXP4XX_PCI_INT&t;8
DECL|macro|IRQ_IXP4XX_PCI_DMA1
mdefine_line|#define IRQ_IXP4XX_PCI_DMA1&t;9
DECL|macro|IRQ_IXP4XX_PCI_DMA2
mdefine_line|#define IRQ_IXP4XX_PCI_DMA2&t;10
DECL|macro|IRQ_IXP4XX_TIMER2
mdefine_line|#define IRQ_IXP4XX_TIMER2&t;11
DECL|macro|IRQ_IXP4XX_USB
mdefine_line|#define IRQ_IXP4XX_USB&t;&t;12
DECL|macro|IRQ_IXP4XX_UART2
mdefine_line|#define IRQ_IXP4XX_UART2&t;13
DECL|macro|IRQ_IXP4XX_TIMESTAMP
mdefine_line|#define IRQ_IXP4XX_TIMESTAMP&t;14
DECL|macro|IRQ_IXP4XX_UART1
mdefine_line|#define IRQ_IXP4XX_UART1&t;15
DECL|macro|IRQ_IXP4XX_WDOG
mdefine_line|#define IRQ_IXP4XX_WDOG&t;&t;16
DECL|macro|IRQ_IXP4XX_AHB_PMU
mdefine_line|#define IRQ_IXP4XX_AHB_PMU&t;17
DECL|macro|IRQ_IXP4XX_XSCALE_PMU
mdefine_line|#define IRQ_IXP4XX_XSCALE_PMU&t;18
DECL|macro|IRQ_IXP4XX_GPIO2
mdefine_line|#define IRQ_IXP4XX_GPIO2&t;19
DECL|macro|IRQ_IXP4XX_GPIO3
mdefine_line|#define IRQ_IXP4XX_GPIO3&t;20
DECL|macro|IRQ_IXP4XX_GPIO4
mdefine_line|#define IRQ_IXP4XX_GPIO4&t;21
DECL|macro|IRQ_IXP4XX_GPIO5
mdefine_line|#define IRQ_IXP4XX_GPIO5&t;22
DECL|macro|IRQ_IXP4XX_GPIO6
mdefine_line|#define IRQ_IXP4XX_GPIO6&t;23
DECL|macro|IRQ_IXP4XX_GPIO7
mdefine_line|#define IRQ_IXP4XX_GPIO7&t;24
DECL|macro|IRQ_IXP4XX_GPIO8
mdefine_line|#define IRQ_IXP4XX_GPIO8&t;25
DECL|macro|IRQ_IXP4XX_GPIO9
mdefine_line|#define IRQ_IXP4XX_GPIO9&t;26
DECL|macro|IRQ_IXP4XX_GPIO10
mdefine_line|#define IRQ_IXP4XX_GPIO10&t;27
DECL|macro|IRQ_IXP4XX_GPIO11
mdefine_line|#define IRQ_IXP4XX_GPIO11&t;28
DECL|macro|IRQ_IXP4XX_GPIO12
mdefine_line|#define IRQ_IXP4XX_GPIO12&t;29
DECL|macro|IRQ_IXP4XX_SW_INT1
mdefine_line|#define IRQ_IXP4XX_SW_INT1&t;30
DECL|macro|IRQ_IXP4XX_SW_INT2
mdefine_line|#define IRQ_IXP4XX_SW_INT2&t;31
macro_line|#ifndef&t;CONFIG_CPU_IXP46X
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;32
macro_line|#else
multiline_comment|/*&n; * IXP465 adds new sources&n; */
DECL|macro|IRQ_IXP4XX_USB_HOST
mdefine_line|#define IRQ_IXP4XX_USB_HOST&t;32
DECL|macro|IRQ_IXP4XX_I2C
mdefine_line|#define IRQ_IXP4XX_I2C&t;&t;33
DECL|macro|IRQ_IXP4XX_SSP
mdefine_line|#define IRQ_IXP4XX_SSP&t;&t;34
DECL|macro|IRQ_IXP4XX_TSYNC
mdefine_line|#define IRQ_IXP4XX_TSYNC&t;35
DECL|macro|IRQ_IXP4XX_EAU_DONE
mdefine_line|#define IRQ_IXP4XX_EAU_DONE&t;36
DECL|macro|IRQ_IXP4XX_SHA_DONE
mdefine_line|#define IRQ_IXP4XX_SHA_DONE&t;37
DECL|macro|IRQ_IXP4XX_SWCP_PE
mdefine_line|#define IRQ_IXP4XX_SWCP_PE&t;58
DECL|macro|IRQ_IXP4XX_QM_PE
mdefine_line|#define IRQ_IXP4XX_QM_PE&t;60
DECL|macro|IRQ_IXP4XX_MCU_ECC
mdefine_line|#define IRQ_IXP4XX_MCU_ECC&t;61
DECL|macro|IRQ_IXP4XX_EXP_PE
mdefine_line|#define IRQ_IXP4XX_EXP_PE&t;62
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;64
macro_line|#endif
DECL|macro|XSCALE_PMU_IRQ
mdefine_line|#define&t;XSCALE_PMU_IRQ&t;&t;(IRQ_IXP4XX_XSCALE_PMU)
multiline_comment|/*&n; * IXDP425 board IRQs&n; */
DECL|macro|IRQ_IXDP425_PCI_INTA
mdefine_line|#define&t;IRQ_IXDP425_PCI_INTA&t;IRQ_IXP4XX_GPIO11
DECL|macro|IRQ_IXDP425_PCI_INTB
mdefine_line|#define&t;IRQ_IXDP425_PCI_INTB&t;IRQ_IXP4XX_GPIO10
DECL|macro|IRQ_IXDP425_PCI_INTC
mdefine_line|#define&t;IRQ_IXDP425_PCI_INTC&t;IRQ_IXP4XX_GPIO9
DECL|macro|IRQ_IXDP425_PCI_INTD
mdefine_line|#define&t;IRQ_IXDP425_PCI_INTD&t;IRQ_IXP4XX_GPIO8
multiline_comment|/*&n; * PrPMC1100 Board IRQs&n; */
DECL|macro|IRQ_PRPMC1100_PCI_INTA
mdefine_line|#define&t;IRQ_PRPMC1100_PCI_INTA&t;IRQ_IXP4XX_GPIO11
DECL|macro|IRQ_PRPMC1100_PCI_INTB
mdefine_line|#define&t;IRQ_PRPMC1100_PCI_INTB&t;IRQ_IXP4XX_GPIO10
DECL|macro|IRQ_PRPMC1100_PCI_INTC
mdefine_line|#define&t;IRQ_PRPMC1100_PCI_INTC&t;IRQ_IXP4XX_GPIO9
DECL|macro|IRQ_PRPMC1100_PCI_INTD
mdefine_line|#define&t;IRQ_PRPMC1100_PCI_INTD&t;IRQ_IXP4XX_GPIO8
multiline_comment|/*&n; * ADI Coyote Board IRQs&n; */
DECL|macro|IRQ_COYOTE_PCI_SLOT0
mdefine_line|#define&t;IRQ_COYOTE_PCI_SLOT0&t;IRQ_IXP4XX_GPIO6
DECL|macro|IRQ_COYOTE_PCI_SLOT1
mdefine_line|#define&t;IRQ_COYOTE_PCI_SLOT1&t;IRQ_IXP4XX_GPIO11
DECL|macro|IRQ_COYOTE_IDE
mdefine_line|#define&t;IRQ_COYOTE_IDE&t;&t;IRQ_IXP4XX_GPIO5
macro_line|#endif
eof
