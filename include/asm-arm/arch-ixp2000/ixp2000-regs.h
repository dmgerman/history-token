multiline_comment|/*&n; * include/asm-arm/arch-ixp2000/ixp2000-regs.h&n; *&n; * Chipset register definitions for IXP2400/2800 based systems.&n; *&n; * Original Author: Naeem Afzal &lt;naeem.m.afzal@intel.com&gt;&n; *&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002 Intel Corp.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#ifndef _IXP2000_REGS_H_
DECL|macro|_IXP2000_REGS_H_
mdefine_line|#define _IXP2000_REGS_H_
multiline_comment|/* &n; * Static I/O regions. The manual defines each region as being several&n; * MB in size, but all the registers are within the first 4K, so there&squot;s&n; * no purpose in mapping the whole region in.&n; */
DECL|macro|IXP2000_SLOWPORT_CSR_PHYS_BASE
mdefine_line|#define&t;IXP2000_SLOWPORT_CSR_PHYS_BASE&t;0xc0080000
DECL|macro|IXP2000_SLOWPORT_CSR_VIRT_BASE
mdefine_line|#define&t;IXP2000_SLOWPORT_CSR_VIRT_BASE&t;0xfefff000
DECL|macro|IXP2000_SLOWPORT_CSR_SIZE
mdefine_line|#define&t;IXP2000_SLOWPORT_CSR_SIZE&t;0x1000
DECL|macro|IXP2000_GLOBAL_REG_PHYS_BASE
mdefine_line|#define&t;IXP2000_GLOBAL_REG_PHYS_BASE&t;0xc0004000
DECL|macro|IXP2000_GLOBAL_REG_VIRT_BASE
mdefine_line|#define&t;IXP2000_GLOBAL_REG_VIRT_BASE&t;0xfeffe000
DECL|macro|IXP2000_GLOBAL_REG_SIZE
mdefine_line|#define&t;IXP2000_GLOBAL_REG_SIZE&t;&t;0x1000
DECL|macro|IXP2000_UART_PHYS_BASE
mdefine_line|#define&t;IXP2000_UART_PHYS_BASE&t;&t;0xc0030000
DECL|macro|IXP2000_UART_VIRT_BASE
mdefine_line|#define&t;IXP2000_UART_VIRT_BASE&t;&t;0xfef30000
DECL|macro|IXP2000_UART_SIZE
mdefine_line|#define IXP2000_UART_SIZE&t;&t;0x1000
DECL|macro|IXP2000_TIMER_PHYS_BASE
mdefine_line|#define&t;IXP2000_TIMER_PHYS_BASE&t;&t;0xc0020000
DECL|macro|IXP2000_TIMER_VIRT_BASE
mdefine_line|#define&t;IXP2000_TIMER_VIRT_BASE&t;&t;0xfeffc000
DECL|macro|IXP2000_TIMER_SIZE
mdefine_line|#define&t;IXP2000_TIMER_SIZE&t;&t;0x1000
DECL|macro|IXP2000_GPIO_PHYS_BASE
mdefine_line|#define&t;IXP2000_GPIO_PHYS_BASE&t;&t;0xc0010000
DECL|macro|IXP2000_GPIO_VIRT_BASE
mdefine_line|#define&t;IXP2000_GPIO_VIRT_BASE&t;&t;0xfeffb000
DECL|macro|IXP2000_GPIO_SIZE
mdefine_line|#define&t;IXP2000_GPIO_SIZE&t;&t;0x1000
DECL|macro|IXP2000_INTCTL_PHYS_BASE
mdefine_line|#define IXP2000_INTCTL_PHYS_BASE&t;0xd6000000
DECL|macro|IXP2000_INTCTL_VIRT_BASE
mdefine_line|#define&t;IXP2000_INTCTL_VIRT_BASE&t;0xfeffa000
DECL|macro|IXP2000_INTCTL_SIZE
mdefine_line|#define&t;IXP2000_INTCTL_SIZE&t;&t;0x01000
DECL|macro|IXP2000_PCI_CREG_PHYS_BASE
mdefine_line|#define IXP2000_PCI_CREG_PHYS_BASE&t;0xde000000
DECL|macro|IXP2000_PCI_CREG_VIRT_BASE
mdefine_line|#define&t;IXP2000_PCI_CREG_VIRT_BASE&t;0xfeff0000
DECL|macro|IXP2000_PCI_CREG_SIZE
mdefine_line|#define&t;IXP2000_PCI_CREG_SIZE&t;&t;0x1000
DECL|macro|IXP2000_PCI_CSR_PHYS_BASE
mdefine_line|#define IXP2000_PCI_CSR_PHYS_BASE&t;0xdf000000
DECL|macro|IXP2000_PCI_CSR_VIRT_BASE
mdefine_line|#define&t;IXP2000_PCI_CSR_VIRT_BASE&t;0xfefde000
DECL|macro|IXP2000_PCI_CSR_SIZE
mdefine_line|#define&t;IXP2000_PCI_CSR_SIZE&t;&t;0x1000
DECL|macro|IXP2000_PCI_IO_PHYS_BASE
mdefine_line|#define IXP2000_PCI_IO_PHYS_BASE&t;0xd8000000
DECL|macro|IXP2000_PCI_IO_VIRT_BASE
mdefine_line|#define&t;IXP2000_PCI_IO_VIRT_BASE&t;0xfd000000
DECL|macro|IXP2000_PCI_IO_SIZE
mdefine_line|#define IXP2000_PCI_IO_SIZE     &t;0x01000000
DECL|macro|IXP2000_PCI_CFG0_PHYS_BASE
mdefine_line|#define IXP2000_PCI_CFG0_PHYS_BASE&t;0xda000000
DECL|macro|IXP2000_PCI_CFG0_VIRT_BASE
mdefine_line|#define IXP2000_PCI_CFG0_VIRT_BASE&t;0xfc000000
DECL|macro|IXP2000_PCI_CFG0_SIZE
mdefine_line|#define IXP2000_PCI_CFG0_SIZE   &t;0x01000000
DECL|macro|IXP2000_PCI_CFG1_PHYS_BASE
mdefine_line|#define IXP2000_PCI_CFG1_PHYS_BASE&t;0xdb000000
DECL|macro|IXP2000_PCI_CFG1_VIRT_BASE
mdefine_line|#define IXP2000_PCI_CFG1_VIRT_BASE&t;0xfb000000
DECL|macro|IXP2000_PCI_CFG1_SIZE
mdefine_line|#define IXP2000_PCI_CFG1_SIZE&t;&t;0x01000000
multiline_comment|/* &n; * Timers&n; */
DECL|macro|IXP2000_TIMER_REG
mdefine_line|#define&t;IXP2000_TIMER_REG(x)&t;&t;((volatile unsigned long*)(IXP2000_TIMER_VIRT_BASE | (x)))
multiline_comment|/* Timer control */
DECL|macro|IXP2000_T1_CTL
mdefine_line|#define&t;IXP2000_T1_CTL&t;&t;&t;IXP2000_TIMER_REG(0x00)
DECL|macro|IXP2000_T2_CTL
mdefine_line|#define&t;IXP2000_T2_CTL&t;&t;&t;IXP2000_TIMER_REG(0x04)
DECL|macro|IXP2000_T3_CTL
mdefine_line|#define&t;IXP2000_T3_CTL&t;&t;&t;IXP2000_TIMER_REG(0x08)
DECL|macro|IXP2000_T4_CTL
mdefine_line|#define&t;IXP2000_T4_CTL&t;&t;&t;IXP2000_TIMER_REG(0x0c)
multiline_comment|/* Store initial value */
DECL|macro|IXP2000_T1_CLD
mdefine_line|#define&t;IXP2000_T1_CLD&t;&t;&t;IXP2000_TIMER_REG(0x10)
DECL|macro|IXP2000_T2_CLD
mdefine_line|#define&t;IXP2000_T2_CLD&t;&t;&t;IXP2000_TIMER_REG(0x14)
DECL|macro|IXP2000_T3_CLD
mdefine_line|#define&t;IXP2000_T3_CLD&t;&t;&t;IXP2000_TIMER_REG(0x18)
DECL|macro|IXP2000_T4_CLD
mdefine_line|#define&t;IXP2000_T4_CLD&t;&t;&t;IXP2000_TIMER_REG(0x1c)
multiline_comment|/* Read current value */
DECL|macro|IXP2000_T1_CSR
mdefine_line|#define&t;IXP2000_T1_CSR&t;&t;&t;IXP2000_TIMER_REG(0x20)
DECL|macro|IXP2000_T2_CSR
mdefine_line|#define&t;IXP2000_T2_CSR&t;&t;&t;IXP2000_TIMER_REG(0x24)
DECL|macro|IXP2000_T3_CSR
mdefine_line|#define&t;IXP2000_T3_CSR&t;&t;&t;IXP2000_TIMER_REG(0x28)
DECL|macro|IXP2000_T4_CSR
mdefine_line|#define&t;IXP2000_T4_CSR&t;&t;&t;IXP2000_TIMER_REG(0x2c)
multiline_comment|/* Clear associated timer interrupt */
DECL|macro|IXP2000_T1_CLR
mdefine_line|#define&t;IXP2000_T1_CLR&t;&t;&t;IXP2000_TIMER_REG(0x30)
DECL|macro|IXP2000_T2_CLR
mdefine_line|#define&t;IXP2000_T2_CLR&t;&t;&t;IXP2000_TIMER_REG(0x34)
DECL|macro|IXP2000_T3_CLR
mdefine_line|#define&t;IXP2000_T3_CLR&t;&t;&t;IXP2000_TIMER_REG(0x38)
DECL|macro|IXP2000_T4_CLR
mdefine_line|#define&t;IXP2000_T4_CLR&t;&t;&t;IXP2000_TIMER_REG(0x3c)
multiline_comment|/* Timer watchdog enable for T4 */
DECL|macro|IXP2000_TWDE
mdefine_line|#define&t;IXP2000_TWDE&t;&t;&t;IXP2000_TIMER_REG(0x40)
DECL|macro|WDT_ENABLE
mdefine_line|#define&t;WDT_ENABLE&t;&t;&t;0x00000001
DECL|macro|TIMER_DIVIDER_256
mdefine_line|#define&t;TIMER_DIVIDER_256&t;&t;0x00000008
DECL|macro|TIMER_ENABLE
mdefine_line|#define&t;TIMER_ENABLE&t;&t;&t;0x00000080
DECL|macro|IRQ_MASK_TIMER1
mdefine_line|#define&t;IRQ_MASK_TIMER1         &t;(1 &lt;&lt; 4)
multiline_comment|/*&n; * Interrupt controller registers&n; */
DECL|macro|IXP2000_INTCTL_REG
mdefine_line|#define IXP2000_INTCTL_REG(x)&t;&t;(volatile unsigned long*)(IXP2000_INTCTL_VIRT_BASE | (x))
DECL|macro|IXP2000_IRQ_STATUS
mdefine_line|#define IXP2000_IRQ_STATUS&t;&t;IXP2000_INTCTL_REG(0x08)
DECL|macro|IXP2000_IRQ_ENABLE
mdefine_line|#define IXP2000_IRQ_ENABLE&t;&t;IXP2000_INTCTL_REG(0x10)
DECL|macro|IXP2000_IRQ_ENABLE_SET
mdefine_line|#define IXP2000_IRQ_ENABLE_SET&t;&t;IXP2000_INTCTL_REG(0x10)
DECL|macro|IXP2000_IRQ_ENABLE_CLR
mdefine_line|#define IXP2000_IRQ_ENABLE_CLR&t;&t;IXP2000_INTCTL_REG(0x18)
DECL|macro|IXP2000_FIQ_ENABLE_CLR
mdefine_line|#define IXP2000_FIQ_ENABLE_CLR&t;&t;IXP2000_INTCTL_REG(0x14)
DECL|macro|IXP2000_IRQ_ERR_STATUS
mdefine_line|#define IXP2000_IRQ_ERR_STATUS&t;&t;IXP2000_INTCTL_REG(0x24)
DECL|macro|IXP2000_IRQ_ERR_ENABLE_SET
mdefine_line|#define IXP2000_IRQ_ERR_ENABLE_SET&t;IXP2000_INTCTL_REG(0x2c)
DECL|macro|IXP2000_FIQ_ERR_ENABLE_CLR
mdefine_line|#define IXP2000_FIQ_ERR_ENABLE_CLR&t;IXP2000_INTCTL_REG(0x30)
DECL|macro|IXP2000_IRQ_ERR_ENABLE_CLR
mdefine_line|#define IXP2000_IRQ_ERR_ENABLE_CLR&t;IXP2000_INTCTL_REG(0x34)
multiline_comment|/*&n; * Mask of valid IRQs in the 32-bit IRQ register. We use&n; * this to mark certain IRQs as being invalid.&n; */
DECL|macro|IXP2000_VALID_IRQ_MASK
mdefine_line|#define&t;IXP2000_VALID_IRQ_MASK&t;0x0f0fffff
multiline_comment|/*&n; * PCI config register access from core&n; */
DECL|macro|IXP2000_PCI_CREG
mdefine_line|#define IXP2000_PCI_CREG(x)&t;&t;(volatile unsigned long*)(IXP2000_PCI_CREG_VIRT_BASE | (x))
DECL|macro|IXP2000_PCI_CMDSTAT
mdefine_line|#define IXP2000_PCI_CMDSTAT &t;&t;IXP2000_PCI_CREG(0x04)
DECL|macro|IXP2000_PCI_CSR_BAR
mdefine_line|#define IXP2000_PCI_CSR_BAR&t;&t;IXP2000_PCI_CREG(0x10)
DECL|macro|IXP2000_PCI_SRAM_BAR
mdefine_line|#define IXP2000_PCI_SRAM_BAR&t;&t;IXP2000_PCI_CREG(0x14)
DECL|macro|IXP2000_PCI_SDRAM_BAR
mdefine_line|#define IXP2000_PCI_SDRAM_BAR&t;&t;IXP2000_PCI_CREG(0x18)
multiline_comment|/*&n; * PCI CSRs&n; */
DECL|macro|IXP2000_PCI_CSR
mdefine_line|#define IXP2000_PCI_CSR(x)&t;&t;(volatile unsigned long*)(IXP2000_PCI_CSR_VIRT_BASE | (x))
multiline_comment|/*&n; * PCI outbound interrupts&n; */
DECL|macro|IXP2000_PCI_OUT_INT_STATUS
mdefine_line|#define IXP2000_PCI_OUT_INT_STATUS&t;IXP2000_PCI_CSR(0x30)
DECL|macro|IXP2000_PCI_OUT_INT_MASK
mdefine_line|#define IXP2000_PCI_OUT_INT_MASK&t;IXP2000_PCI_CSR(0x34)
multiline_comment|/*&n; * PCI communications&n; */
DECL|macro|IXP2000_PCI_MAILBOX0
mdefine_line|#define IXP2000_PCI_MAILBOX0&t;&t;IXP2000_PCI_CSR(0x50)
DECL|macro|IXP2000_PCI_MAILBOX1
mdefine_line|#define IXP2000_PCI_MAILBOX1&t;&t;IXP2000_PCI_CSR(0x54)
DECL|macro|IXP2000_PCI_MAILBOX2
mdefine_line|#define IXP2000_PCI_MAILBOX2&t;&t;IXP2000_PCI_CSR(0x58)
DECL|macro|IXP2000_PCI_MAILBOX3
mdefine_line|#define IXP2000_PCI_MAILBOX3&t;&t;IXP2000_PCI_CSR(0x5C)
DECL|macro|IXP2000_XSCALE_DOORBELL
mdefine_line|#define IXP2000_XSCALE_DOORBELL&t;&t;IXP2000_PCI_CSR(0x60)
DECL|macro|IXP2000_XSCALE_DOORBELL_SETUP
mdefine_line|#define IXP2000_XSCALE_DOORBELL_SETUP&t;IXP2000_PCI_CSR(0x64)
DECL|macro|IXP2000_PCI_DOORBELL
mdefine_line|#define IXP2000_PCI_DOORBELL&t;&t;IXP2000_PCI_CSR(0x70)
DECL|macro|IXP2000_PCI_DOORBELL_SETUP
mdefine_line|#define IXP2000_PCI_DOORBELL_SETUP&t;IXP2000_PCI_CSR(0x74)
multiline_comment|/*&n; * DMA engines&n; */
DECL|macro|IXP2000_PCI_CH1_BYTE_CNT
mdefine_line|#define IXP2000_PCI_CH1_BYTE_CNT&t;IXP2000_PCI_CSR(0x80)
DECL|macro|IXP2000_PCI_CH1_ADDR
mdefine_line|#define IXP2000_PCI_CH1_ADDR&t;&t;IXP2000_PCI_CSR(0x84)
DECL|macro|IXP2000_PCI_CH1_DRAM_ADDR
mdefine_line|#define IXP2000_PCI_CH1_DRAM_ADDR&t;IXP2000_PCI_CSR(0x88)
DECL|macro|IXP2000_PCI_CH1_DESC_PTR
mdefine_line|#define IXP2000_PCI_CH1_DESC_PTR&t;IXP2000_PCI_CSR(0x8C)
DECL|macro|IXP2000_PCI_CH1_CNTRL
mdefine_line|#define IXP2000_PCI_CH1_CNTRL&t;&t;IXP2000_PCI_CSR(0x90)
DECL|macro|IXP2000_PCI_CH1_ME_PARAM
mdefine_line|#define IXP2000_PCI_CH1_ME_PARAM&t;IXP2000_PCI_CSR(0x94)
DECL|macro|IXP2000_PCI_CH2_BYTE_CNT
mdefine_line|#define IXP2000_PCI_CH2_BYTE_CNT&t;IXP2000_PCI_CSR(0xA0)
DECL|macro|IXP2000_PCI_CH2_ADDR
mdefine_line|#define IXP2000_PCI_CH2_ADDR&t;&t;IXP2000_PCI_CSR(0xA4)
DECL|macro|IXP2000_PCI_CH2_DRAM_ADDR
mdefine_line|#define IXP2000_PCI_CH2_DRAM_ADDR&t;IXP2000_PCI_CSR(0xA8)
DECL|macro|IXP2000_PCI_CH2_DESC_PTR
mdefine_line|#define IXP2000_PCI_CH2_DESC_PTR&t;IXP2000_PCI_CSR(0xAC)
DECL|macro|IXP2000_PCI_CH2_CNTRL
mdefine_line|#define IXP2000_PCI_CH2_CNTRL&t;&t;IXP2000_PCI_CSR(0xB0)
DECL|macro|IXP2000_PCI_CH2_ME_PARAM
mdefine_line|#define IXP2000_PCI_CH2_ME_PARAM&t;IXP2000_PCI_CSR(0xB4)
DECL|macro|IXP2000_PCI_CH3_BYTE_CNT
mdefine_line|#define IXP2000_PCI_CH3_BYTE_CNT&t;IXP2000_PCI_CSR(0xC0)
DECL|macro|IXP2000_PCI_CH3_ADDR
mdefine_line|#define IXP2000_PCI_CH3_ADDR&t;&t;IXP2000_PCI_CSR(0xC4)
DECL|macro|IXP2000_PCI_CH3_DRAM_ADDR
mdefine_line|#define IXP2000_PCI_CH3_DRAM_ADDR&t;IXP2000_PCI_CSR(0xC8)
DECL|macro|IXP2000_PCI_CH3_DESC_PTR
mdefine_line|#define IXP2000_PCI_CH3_DESC_PTR&t;IXP2000_PCI_CSR(0xCC)
DECL|macro|IXP2000_PCI_CH3_CNTRL
mdefine_line|#define IXP2000_PCI_CH3_CNTRL&t;&t;IXP2000_PCI_CSR(0xD0)
DECL|macro|IXP2000_PCI_CH3_ME_PARAM
mdefine_line|#define IXP2000_PCI_CH3_ME_PARAM&t;IXP2000_PCI_CSR(0xD4)
DECL|macro|IXP2000_DMA_INF_MODE
mdefine_line|#define IXP2000_DMA_INF_MODE&t;&t;IXP2000_PCI_CSR(0xE0)
multiline_comment|/*&n; * Size masks for BARs&n; */
DECL|macro|IXP2000_PCI_SRAM_BASE_ADDR_MASK
mdefine_line|#define IXP2000_PCI_SRAM_BASE_ADDR_MASK&t;IXP2000_PCI_CSR(0xFC)
DECL|macro|IXP2000_PCI_DRAM_BASE_ADDR_MASK
mdefine_line|#define IXP2000_PCI_DRAM_BASE_ADDR_MASK&t;IXP2000_PCI_CSR(0x100)
multiline_comment|/*&n; * Control and uEngine related&n; */
DECL|macro|IXP2000_PCI_CONTROL
mdefine_line|#define IXP2000_PCI_CONTROL&t;&t;IXP2000_PCI_CSR(0x13C)
DECL|macro|IXP2000_PCI_ADDR_EXT
mdefine_line|#define IXP2000_PCI_ADDR_EXT&t;&t;IXP2000_PCI_CSR(0x140)
DECL|macro|IXP2000_PCI_ME_PUSH_STATUS
mdefine_line|#define IXP2000_PCI_ME_PUSH_STATUS&t;IXP2000_PCI_CSR(0x148)
DECL|macro|IXP2000_PCI_ME_PUSH_EN
mdefine_line|#define IXP2000_PCI_ME_PUSH_EN&t;&t;IXP2000_PCI_CSR(0x14C)
DECL|macro|IXP2000_PCI_ERR_STATUS
mdefine_line|#define IXP2000_PCI_ERR_STATUS&t;&t;IXP2000_PCI_CSR(0x150)
DECL|macro|IXP2000_PCI_ERR_ENABLE
mdefine_line|#define IXP2000_PCI_ERR_ENABLE&t;&t;IXP2000_PCI_CSR(0x154)
multiline_comment|/*&n; * Inbound PCI interrupt control&n; */
DECL|macro|IXP2000_PCI_XSCALE_INT_STATUS
mdefine_line|#define IXP2000_PCI_XSCALE_INT_STATUS&t;IXP2000_PCI_CSR(0x158)
DECL|macro|IXP2000_PCI_XSCALE_INT_ENABLE
mdefine_line|#define IXP2000_PCI_XSCALE_INT_ENABLE&t;IXP2000_PCI_CSR(0x15C)
DECL|macro|IXP2000_PCICNTL_PNR
mdefine_line|#define IXP2000_PCICNTL_PNR&t;&t;(1&lt;&lt;17)&t;/* PCI not Reset bit of PCI_CONTROL */
DECL|macro|IXP2000_PCICNTL_PCF
mdefine_line|#define IXP2000_PCICNTL_PCF&t;&t;(1&lt;&lt;28)&t;/* PCI Centrolfunction bit */
DECL|macro|IXP2000_XSCALE_INT
mdefine_line|#define IXP2000_XSCALE_INT&t;&t;(1&lt;&lt;1)&t;/* Interrupt from  XScale to PCI */
multiline_comment|/* These are from the IRQ register in the PCI ISR register */
DECL|macro|PCI_CONTROL_BE_DEO
mdefine_line|#define PCI_CONTROL_BE_DEO&t;&t;(1 &lt;&lt; 22)&t;/* Big Endian Data Enable Out */
DECL|macro|PCI_CONTROL_BE_DEI
mdefine_line|#define PCI_CONTROL_BE_DEI&t;&t;(1 &lt;&lt; 21)&t;/* Big Endian Data Enable In  */
DECL|macro|PCI_CONTROL_BE_BEO
mdefine_line|#define PCI_CONTROL_BE_BEO&t;&t;(1 &lt;&lt; 20)&t;/* Big Endian Byte Enable Out */
DECL|macro|PCI_CONTROL_BE_BEI
mdefine_line|#define PCI_CONTROL_BE_BEI&t;&t;(1 &lt;&lt; 19)&t;/* Big Endian Byte Enable In  */
DECL|macro|PCI_CONTROL_PNR
mdefine_line|#define PCI_CONTROL_PNR&t;&t;&t;(1 &lt;&lt; 17)&t;/* PCI Not Reset bit */
DECL|macro|IXP2000_PCI_RST_REL
mdefine_line|#define IXP2000_PCI_RST_REL&t;&t;(1 &lt;&lt; 2)
DECL|macro|CFG_RST_DIR
mdefine_line|#define CFG_RST_DIR&t;&t;&t;(*IXP2000_PCI_CONTROL &amp; IXP2000_PCICNTL_PCF)
DECL|macro|CFG_PCI_BOOT_HOST
mdefine_line|#define CFG_PCI_BOOT_HOST&t;&t;(1 &lt;&lt; 2)
DECL|macro|CFG_BOOT_PROM
mdefine_line|#define CFG_BOOT_PROM&t;&t;&t;(1 &lt;&lt; 1)
multiline_comment|/*&n; * SlowPort CSRs&n; *&n; * The slowport is used to access things like flash, SONET framer control&n; * ports, slave microprocessors, CPLDs, and others of chip memory mapped&n; * peripherals.&n; */
DECL|macro|SLOWPORT_CSR
mdefine_line|#define&t;SLOWPORT_CSR(x)&t;&t;(volatile unsigned long*)(IXP2000_SLOWPORT_CSR_VIRT_BASE | (x))
DECL|macro|IXP2000_SLOWPORT_CCR
mdefine_line|#define&t;IXP2000_SLOWPORT_CCR&t;&t;SLOWPORT_CSR(0x00)
DECL|macro|IXP2000_SLOWPORT_WTC1
mdefine_line|#define&t;IXP2000_SLOWPORT_WTC1&t;&t;SLOWPORT_CSR(0x04)
DECL|macro|IXP2000_SLOWPORT_WTC2
mdefine_line|#define&t;IXP2000_SLOWPORT_WTC2&t;&t;SLOWPORT_CSR(0x08)
DECL|macro|IXP2000_SLOWPORT_RTC1
mdefine_line|#define&t;IXP2000_SLOWPORT_RTC1&t;&t;SLOWPORT_CSR(0x0c)
DECL|macro|IXP2000_SLOWPORT_RTC2
mdefine_line|#define&t;IXP2000_SLOWPORT_RTC2&t;&t;SLOWPORT_CSR(0x10)
DECL|macro|IXP2000_SLOWPORT_FSR
mdefine_line|#define&t;IXP2000_SLOWPORT_FSR&t;&t;SLOWPORT_CSR(0x14)
DECL|macro|IXP2000_SLOWPORT_PCR
mdefine_line|#define&t;IXP2000_SLOWPORT_PCR&t;&t;SLOWPORT_CSR(0x18)
DECL|macro|IXP2000_SLOWPORT_ADC
mdefine_line|#define&t;IXP2000_SLOWPORT_ADC&t;&t;SLOWPORT_CSR(0x1C)
DECL|macro|IXP2000_SLOWPORT_FAC
mdefine_line|#define&t;IXP2000_SLOWPORT_FAC&t;&t;SLOWPORT_CSR(0x20)
DECL|macro|IXP2000_SLOWPORT_FRM
mdefine_line|#define&t;IXP2000_SLOWPORT_FRM&t;&t;SLOWPORT_CSR(0x24)
DECL|macro|IXP2000_SLOWPORT_FIN
mdefine_line|#define&t;IXP2000_SLOWPORT_FIN&t;&t;SLOWPORT_CSR(0x28)
multiline_comment|/*&n; * CCR values.  &n; * The CCR configures the clock division for the slowport interface.&n; */
DECL|macro|SLOWPORT_CCR_DIV_1
mdefine_line|#define&t;SLOWPORT_CCR_DIV_1&t;&t;0x00
DECL|macro|SLOWPORT_CCR_DIV_2
mdefine_line|#define&t;SLOWPORT_CCR_DIV_2&t;&t;0x01
DECL|macro|SLOWPORT_CCR_DIV_4
mdefine_line|#define&t;SLOWPORT_CCR_DIV_4&t;&t;0x02
DECL|macro|SLOWPORT_CCR_DIV_6
mdefine_line|#define&t;SLOWPORT_CCR_DIV_6&t;&t;0x03
DECL|macro|SLOWPORT_CCR_DIV_8
mdefine_line|#define&t;SLOWPORT_CCR_DIV_8&t;&t;0x04
DECL|macro|SLOWPORT_CCR_DIV_10
mdefine_line|#define&t;SLOWPORT_CCR_DIV_10&t;&t;0x05
DECL|macro|SLOWPORT_CCR_DIV_12
mdefine_line|#define&t;SLOWPORT_CCR_DIV_12&t;&t;0x06
DECL|macro|SLOWPORT_CCR_DIV_14
mdefine_line|#define&t;SLOWPORT_CCR_DIV_14&t;&t;0x07
DECL|macro|SLOWPORT_CCR_DIV_16
mdefine_line|#define&t;SLOWPORT_CCR_DIV_16&t;&t;0x08
DECL|macro|SLOWPORT_CCR_DIV_18
mdefine_line|#define&t;SLOWPORT_CCR_DIV_18&t;&t;0x09
DECL|macro|SLOWPORT_CCR_DIV_20
mdefine_line|#define&t;SLOWPORT_CCR_DIV_20&t;&t;0x0a
DECL|macro|SLOWPORT_CCR_DIV_22
mdefine_line|#define&t;SLOWPORT_CCR_DIV_22&t;&t;0x0b
DECL|macro|SLOWPORT_CCR_DIV_24
mdefine_line|#define&t;SLOWPORT_CCR_DIV_24&t;&t;0x0c
DECL|macro|SLOWPORT_CCR_DIV_26
mdefine_line|#define&t;SLOWPORT_CCR_DIV_26&t;&t;0x0d
DECL|macro|SLOWPORT_CCR_DIV_28
mdefine_line|#define&t;SLOWPORT_CCR_DIV_28&t;&t;0x0e
DECL|macro|SLOWPORT_CCR_DIV_30
mdefine_line|#define&t;SLOWPORT_CCR_DIV_30&t;&t;0x0f
multiline_comment|/*&n; * PCR values.  PCR configure the mode of the interface.&n; */
DECL|macro|SLOWPORT_MODE_FLASH
mdefine_line|#define&t;SLOWPORT_MODE_FLASH&t;&t;0x00
DECL|macro|SLOWPORT_MODE_LUCENT
mdefine_line|#define&t;SLOWPORT_MODE_LUCENT&t;&t;0x01
DECL|macro|SLOWPORT_MODE_PMC_SIERRA
mdefine_line|#define&t;SLOWPORT_MODE_PMC_SIERRA&t;0x02
DECL|macro|SLOWPORT_MODE_INTEL_UP
mdefine_line|#define&t;SLOWPORT_MODE_INTEL_UP&t;&t;0x03
DECL|macro|SLOWPORT_MODE_MOTOROLA_UP
mdefine_line|#define&t;SLOWPORT_MODE_MOTOROLA_UP&t;0x04
multiline_comment|/*&n; * ADC values.  Defines data and address bus widths.&n; */
DECL|macro|SLOWPORT_ADDR_WIDTH_8
mdefine_line|#define&t;SLOWPORT_ADDR_WIDTH_8&t;&t;0x00
DECL|macro|SLOWPORT_ADDR_WIDTH_16
mdefine_line|#define&t;SLOWPORT_ADDR_WIDTH_16&t;&t;0x01
DECL|macro|SLOWPORT_ADDR_WIDTH_24
mdefine_line|#define&t;SLOWPORT_ADDR_WIDTH_24&t;&t;0x02
DECL|macro|SLOWPORT_ADDR_WIDTH_32
mdefine_line|#define&t;SLOWPORT_ADDR_WIDTH_32&t;&t;0x03
DECL|macro|SLOWPORT_DATA_WIDTH_8
mdefine_line|#define&t;SLOWPORT_DATA_WIDTH_8&t;&t;0x00
DECL|macro|SLOWPORT_DATA_WIDTH_16
mdefine_line|#define&t;SLOWPORT_DATA_WIDTH_16&t;&t;0x10
DECL|macro|SLOWPORT_DATA_WIDTH_24
mdefine_line|#define&t;SLOWPORT_DATA_WIDTH_24&t;&t;0x20
DECL|macro|SLOWPORT_DATA_WIDTH_32
mdefine_line|#define&t;SLOWPORT_DATA_WIDTH_32&t;&t;0x30
multiline_comment|/*&n; * Masks and shifts for various fields in the WTC and RTC registers.&n; */
DECL|macro|SLOWPORT_WRTC_MASK_HD
mdefine_line|#define&t;SLOWPORT_WRTC_MASK_HD&t;&t;0x0003
DECL|macro|SLOWPORT_WRTC_MASK_SU
mdefine_line|#define&t;SLOWPORT_WRTC_MASK_SU&t;&t;0x003c
DECL|macro|SLOWPORT_WRTC_MASK_PW
mdefine_line|#define&t;SLOWPORT_WRTC_MASK_PW&t;&t;0x03c0
DECL|macro|SLOWPORT_WRTC_SHIFT_HD
mdefine_line|#define&t;SLOWPORT_WRTC_SHIFT_HD&t;&t;0x00
DECL|macro|SLOWPORT_WRTC_SHIFT_SU
mdefine_line|#define&t;SLOWPORT_WRTC_SHIFT_SU&t;&t;0x02
DECL|macro|SLOWPORT_WRTC_SHFIT_PW
mdefine_line|#define&t;SLOWPORT_WRTC_SHFIT_PW&t;&t;0x06
multiline_comment|/*&n; * GPIO registers &amp; GPIO interface.&n; */
DECL|macro|IXP2000_GPIO_REG
mdefine_line|#define IXP2000_GPIO_REG(x)&t;&t;((volatile unsigned long*)(IXP2000_GPIO_VIRT_BASE+(x)))
DECL|macro|IXP2000_GPIO_PLR
mdefine_line|#define IXP2000_GPIO_PLR&t;&t;IXP2000_GPIO_REG(0x00)
DECL|macro|IXP2000_GPIO_PDPR
mdefine_line|#define IXP2000_GPIO_PDPR&t;&t;IXP2000_GPIO_REG(0x04)
DECL|macro|IXP2000_GPIO_PDSR
mdefine_line|#define IXP2000_GPIO_PDSR&t;&t;IXP2000_GPIO_REG(0x08)
DECL|macro|IXP2000_GPIO_PDCR
mdefine_line|#define IXP2000_GPIO_PDCR&t;&t;IXP2000_GPIO_REG(0x0c)
DECL|macro|IXP2000_GPIO_POPR
mdefine_line|#define IXP2000_GPIO_POPR&t;&t;IXP2000_GPIO_REG(0x10)
DECL|macro|IXP2000_GPIO_POSR
mdefine_line|#define IXP2000_GPIO_POSR&t;&t;IXP2000_GPIO_REG(0x14)
DECL|macro|IXP2000_GPIO_POCR
mdefine_line|#define IXP2000_GPIO_POCR&t;&t;IXP2000_GPIO_REG(0x18)
DECL|macro|IXP2000_GPIO_REDR
mdefine_line|#define IXP2000_GPIO_REDR&t;&t;IXP2000_GPIO_REG(0x1c)
DECL|macro|IXP2000_GPIO_FEDR
mdefine_line|#define IXP2000_GPIO_FEDR&t;&t;IXP2000_GPIO_REG(0x20)
DECL|macro|IXP2000_GPIO_EDSR
mdefine_line|#define IXP2000_GPIO_EDSR&t;&t;IXP2000_GPIO_REG(0x24)
DECL|macro|IXP2000_GPIO_LSHR
mdefine_line|#define IXP2000_GPIO_LSHR&t;&t;IXP2000_GPIO_REG(0x28)
DECL|macro|IXP2000_GPIO_LSLR
mdefine_line|#define IXP2000_GPIO_LSLR&t;&t;IXP2000_GPIO_REG(0x2c)
DECL|macro|IXP2000_GPIO_LDSR
mdefine_line|#define IXP2000_GPIO_LDSR&t;&t;IXP2000_GPIO_REG(0x30)
DECL|macro|IXP2000_GPIO_INER
mdefine_line|#define IXP2000_GPIO_INER&t;&t;IXP2000_GPIO_REG(0x34)
DECL|macro|IXP2000_GPIO_INSR
mdefine_line|#define IXP2000_GPIO_INSR&t;&t;IXP2000_GPIO_REG(0x38)
DECL|macro|IXP2000_GPIO_INCR
mdefine_line|#define IXP2000_GPIO_INCR&t;&t;IXP2000_GPIO_REG(0x3c)
DECL|macro|IXP2000_GPIO_INST
mdefine_line|#define IXP2000_GPIO_INST&t;&t;IXP2000_GPIO_REG(0x40)
multiline_comment|/*&n; * &quot;Global&quot; registers...whatever that&squot;s supposed to mean.&n; */
DECL|macro|GLOBAL_REG_BASE
mdefine_line|#define GLOBAL_REG_BASE&t;&t;&t;(IXP2000_GLOBAL_REG_VIRT_BASE + 0x0a00)
DECL|macro|GLOBAL_REG
mdefine_line|#define GLOBAL_REG(x)&t;&t;&t;(volatile unsigned long*)(GLOBAL_REG_BASE | (x))
DECL|macro|IXP2000_PROD_ID
mdefine_line|#define IXP2000_PROD_ID&t;&t;&t;GLOBAL_REG(0x00)
DECL|macro|IXP2000_MAJ_PROD_TYPE_MASK
mdefine_line|#define IXP2000_MAJ_PROD_TYPE_MASK&t;0x001F0000
DECL|macro|IXP2000_MAJ_PROD_TYPE_IXP2000
mdefine_line|#define IXP2000_MAJ_PROD_TYPE_IXP2000&t;0x00000000
DECL|macro|IXP2000_MIN_PROD_TYPE_MASK
mdefine_line|#define IXP2000_MIN_PROD_TYPE_MASK &t;0x0000FF00
DECL|macro|IXP2000_MIN_PROD_TYPE_IXP2400
mdefine_line|#define IXP2000_MIN_PROD_TYPE_IXP2400&t;0x00000200
DECL|macro|IXP2000_MIN_PROD_TYPE_IXP2850
mdefine_line|#define IXP2000_MIN_PROD_TYPE_IXP2850&t;0x00000100
DECL|macro|IXP2000_MIN_PROD_TYPE_IXP2800
mdefine_line|#define IXP2000_MIN_PROD_TYPE_IXP2800&t;0x00000000
DECL|macro|IXP2000_MAJ_REV_MASK
mdefine_line|#define IXP2000_MAJ_REV_MASK&t;      &t;0x000000F0
DECL|macro|IXP2000_MIN_REV_MASK
mdefine_line|#define IXP2000_MIN_REV_MASK&t;      &t;0x0000000F
DECL|macro|IXP2000_PROD_ID_MASK
mdefine_line|#define IXP2000_PROD_ID_MASK&t;&t;0xFFFFFFFF
DECL|macro|IXP2000_MISC_CONTROL
mdefine_line|#define IXP2000_MISC_CONTROL&t;&t;GLOBAL_REG(0x04)
DECL|macro|IXP2000_MSF_CLK_CNTRL
mdefine_line|#define IXP2000_MSF_CLK_CNTRL  &t;&t;GLOBAL_REG(0x08)
DECL|macro|IXP2000_RESET0
mdefine_line|#define IXP2000_RESET0      &t;&t;GLOBAL_REG(0x0c)
DECL|macro|IXP2000_RESET1
mdefine_line|#define IXP2000_RESET1      &t;&t;GLOBAL_REG(0x10)
DECL|macro|IXP2000_CCR
mdefine_line|#define IXP2000_CCR            &t;&t;GLOBAL_REG(0x14)
DECL|macro|IXP2000_STRAP_OPTIONS
mdefine_line|#define&t;IXP2000_STRAP_OPTIONS  &t;&t;GLOBAL_REG(0x18)
DECL|macro|RSTALL
mdefine_line|#define&t;RSTALL&t;&t;&t;&t;(1 &lt;&lt; 16)
DECL|macro|WDT_RESET_ENABLE
mdefine_line|#define&t;WDT_RESET_ENABLE&t;&t;0x01000000
macro_line|#endif&t;&t;&t;&t;/* _IXP2000_H_ */
eof
