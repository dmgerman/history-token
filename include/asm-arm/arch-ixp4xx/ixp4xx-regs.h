multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/ixp4xx-regs.h&n; *&n; * Register definitions for IXP4xx chipset. This file contains &n; * register location and bit definitions only. Platform specific &n; * definitions and helper function declarations are in platform.h &n; * and machine-name.h.&n; *&n; * Copyright (C) 2002 Intel Corporation.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
macro_line|#error &quot;Do not include this directly, instead #include &lt;asm/hardware.h&gt;&quot;
macro_line|#endif
macro_line|#ifndef _ASM_ARM_IXP4XX_H_
DECL|macro|_ASM_ARM_IXP4XX_H_
mdefine_line|#define _ASM_ARM_IXP4XX_H_
multiline_comment|/*&n; * IXP4xx Linux Memory Map:&n; *&n; * Phy&t;&t;Size&t;&t;Virt&t;&t;Description&n; * =========================================================================&n; *&n; * 0x00000000&t;0x10000000(max)&t;PAGE_OFFSET&t;System RAM&n; *&n; * 0x48000000&t;0x04000000&t;ioremap&squot;d&t;PCI Memory Space&n; *&n; * 0x50000000&t;0x10000000&t;ioremap&squot;d&t;EXP BUS&n; *&n; * 0x6000000&t;0x00004000&t;ioremap&squot;d&t;QMgr&n; *&n; * 0xC0000000&t;0x00001000&t;0xffbfe000&t;PCI CFG &n; *&n; * 0xC4000000&t;0x00001000&t;0xffbfd000&t;EXP CFG &n; *&n; * 0xC8000000&t;0x0000C000&t;0xffbf2000&t;On-Chip Peripherals&n; */
multiline_comment|/*&n; * Queue Manager&n; */
DECL|macro|IXP4XX_QMGR_BASE_PHYS
mdefine_line|#define IXP4XX_QMGR_BASE_PHYS&t;&t;(0x60000000)
multiline_comment|/*&n; * Expansion BUS Configuration registers&n; */
DECL|macro|IXP4XX_EXP_CFG_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_CFG_BASE_PHYS&t;(0xC4000000)
DECL|macro|IXP4XX_EXP_CFG_BASE_VIRT
mdefine_line|#define IXP4XX_EXP_CFG_BASE_VIRT&t;(0xFFBFD000)
DECL|macro|IXP4XX_EXP_CFG_REGION_SIZE
mdefine_line|#define IXP4XX_EXP_CFG_REGION_SIZE&t;(0x00001000)
multiline_comment|/*&n; * PCI Config registers&n; */
DECL|macro|IXP4XX_PCI_CFG_BASE_PHYS
mdefine_line|#define IXP4XX_PCI_CFG_BASE_PHYS&t;(0xC0000000)
DECL|macro|IXP4XX_PCI_CFG_BASE_VIRT
mdefine_line|#define&t;IXP4XX_PCI_CFG_BASE_VIRT&t;(0xFFBFE000)
DECL|macro|IXP4XX_PCI_CFG_REGION_SIZE
mdefine_line|#define IXP4XX_PCI_CFG_REGION_SIZE&t;(0x00001000)
multiline_comment|/*&n; * Peripheral space&n; */
DECL|macro|IXP4XX_PERIPHERAL_BASE_PHYS
mdefine_line|#define IXP4XX_PERIPHERAL_BASE_PHYS&t;(0xC8000000)
DECL|macro|IXP4XX_PERIPHERAL_BASE_VIRT
mdefine_line|#define IXP4XX_PERIPHERAL_BASE_VIRT&t;(0xFFBF2000)
DECL|macro|IXP4XX_PERIPHERAL_REGION_SIZE
mdefine_line|#define IXP4XX_PERIPHERAL_REGION_SIZE&t;(0x0000C000)
DECL|macro|IXP4XX_EXP_CS0_OFFSET
mdefine_line|#define IXP4XX_EXP_CS0_OFFSET&t;0x00
DECL|macro|IXP4XX_EXP_CS1_OFFSET
mdefine_line|#define IXP4XX_EXP_CS1_OFFSET   0x04
DECL|macro|IXP4XX_EXP_CS2_OFFSET
mdefine_line|#define IXP4XX_EXP_CS2_OFFSET   0x08
DECL|macro|IXP4XX_EXP_CS3_OFFSET
mdefine_line|#define IXP4XX_EXP_CS3_OFFSET   0x0C
DECL|macro|IXP4XX_EXP_CS4_OFFSET
mdefine_line|#define IXP4XX_EXP_CS4_OFFSET   0x10
DECL|macro|IXP4XX_EXP_CS5_OFFSET
mdefine_line|#define IXP4XX_EXP_CS5_OFFSET   0x14
DECL|macro|IXP4XX_EXP_CS6_OFFSET
mdefine_line|#define IXP4XX_EXP_CS6_OFFSET   0x18
DECL|macro|IXP4XX_EXP_CS7_OFFSET
mdefine_line|#define IXP4XX_EXP_CS7_OFFSET   0x1C
DECL|macro|IXP4XX_EXP_CFG0_OFFSET
mdefine_line|#define IXP4XX_EXP_CFG0_OFFSET&t;0x20
DECL|macro|IXP4XX_EXP_CFG1_OFFSET
mdefine_line|#define IXP4XX_EXP_CFG1_OFFSET&t;0x24
DECL|macro|IXP4XX_EXP_CFG2_OFFSET
mdefine_line|#define IXP4XX_EXP_CFG2_OFFSET&t;0x28
DECL|macro|IXP4XX_EXP_CFG3_OFFSET
mdefine_line|#define IXP4XX_EXP_CFG3_OFFSET&t;0x2C
multiline_comment|/*&n; * Expansion Bus Controller registers.&n; */
DECL|macro|IXP4XX_EXP_REG
mdefine_line|#define IXP4XX_EXP_REG(x) ((volatile u32 *)(IXP4XX_EXP_CFG_BASE_VIRT+(x)))
DECL|macro|IXP4XX_EXP_CS0
mdefine_line|#define IXP4XX_EXP_CS0      IXP4XX_EXP_REG(IXP4XX_EXP_CS0_OFFSET)
DECL|macro|IXP4XX_EXP_CS1
mdefine_line|#define IXP4XX_EXP_CS1      IXP4XX_EXP_REG(IXP4XX_EXP_CS1_OFFSET)
DECL|macro|IXP4XX_EXP_CS2
mdefine_line|#define IXP4XX_EXP_CS2      IXP4XX_EXP_REG(IXP4XX_EXP_CS2_OFFSET) 
DECL|macro|IXP4XX_EXP_CS3
mdefine_line|#define IXP4XX_EXP_CS3      IXP4XX_EXP_REG(IXP4XX_EXP_CS3_OFFSET)
DECL|macro|IXP4XX_EXP_CS4
mdefine_line|#define IXP4XX_EXP_CS4      IXP4XX_EXP_REG(IXP4XX_EXP_CS4_OFFSET)
DECL|macro|IXP4XX_EXP_CS5
mdefine_line|#define IXP4XX_EXP_CS5      IXP4XX_EXP_REG(IXP4XX_EXP_CS5_OFFSET)
DECL|macro|IXP4XX_EXP_CS6
mdefine_line|#define IXP4XX_EXP_CS6      IXP4XX_EXP_REG(IXP4XX_EXP_CS6_OFFSET)     
DECL|macro|IXP4XX_EXP_CS7
mdefine_line|#define IXP4XX_EXP_CS7      IXP4XX_EXP_REG(IXP4XX_EXP_CS7_OFFSET)
DECL|macro|IXP4XX_EXP_CFG0
mdefine_line|#define IXP4XX_EXP_CFG0     IXP4XX_EXP_REG(IXP4XX_EXP_CFG0_OFFSET) 
DECL|macro|IXP4XX_EXP_CFG1
mdefine_line|#define IXP4XX_EXP_CFG1     IXP4XX_EXP_REG(IXP4XX_EXP_CFG1_OFFSET) 
DECL|macro|IXP4XX_EXP_CFG2
mdefine_line|#define IXP4XX_EXP_CFG2     IXP4XX_EXP_REG(IXP4XX_EXP_CFG2_OFFSET) 
DECL|macro|IXP4XX_EXP_CFG3
mdefine_line|#define IXP4XX_EXP_CFG3     IXP4XX_EXP_REG(IXP4XX_EXP_CFG3_OFFSET)
multiline_comment|/*&n; * Peripheral Space Register Region Base Addresses&n; */
DECL|macro|IXP4XX_UART1_BASE_PHYS
mdefine_line|#define IXP4XX_UART1_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x0000)
DECL|macro|IXP4XX_UART2_BASE_PHYS
mdefine_line|#define IXP4XX_UART2_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x1000)
DECL|macro|IXP4XX_PMU_BASE_PHYS
mdefine_line|#define IXP4XX_PMU_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x2000)
DECL|macro|IXP4XX_INTC_BASE_PHYS
mdefine_line|#define IXP4XX_INTC_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x3000)
DECL|macro|IXP4XX_GPIO_BASE_PHYS
mdefine_line|#define IXP4XX_GPIO_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x4000)
DECL|macro|IXP4XX_TIMER_BASE_PHYS
mdefine_line|#define IXP4XX_TIMER_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x5000)
DECL|macro|IXP4XX_EthA_BASE_PHYS
mdefine_line|#define IXP4XX_EthA_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0x9000)
DECL|macro|IXP4XX_EthB_BASE_PHYS
mdefine_line|#define IXP4XX_EthB_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0xA000)
DECL|macro|IXP4XX_USB_BASE_PHYS
mdefine_line|#define IXP4XX_USB_BASE_PHYS&t;(IXP4XX_PERIPHERAL_BASE_PHYS + 0xB000)
DECL|macro|IXP4XX_UART1_BASE_VIRT
mdefine_line|#define IXP4XX_UART1_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x0000)
DECL|macro|IXP4XX_UART2_BASE_VIRT
mdefine_line|#define IXP4XX_UART2_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x1000)
DECL|macro|IXP4XX_PMU_BASE_VIRT
mdefine_line|#define IXP4XX_PMU_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x2000)
DECL|macro|IXP4XX_INTC_BASE_VIRT
mdefine_line|#define IXP4XX_INTC_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x3000)
DECL|macro|IXP4XX_GPIO_BASE_VIRT
mdefine_line|#define IXP4XX_GPIO_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x4000)
DECL|macro|IXP4XX_TIMER_BASE_VIRT
mdefine_line|#define IXP4XX_TIMER_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x5000)
DECL|macro|IXP4XX_EthA_BASE_VIRT
mdefine_line|#define IXP4XX_EthA_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0x9000)
DECL|macro|IXP4XX_EthB_BASE_VIRT
mdefine_line|#define IXP4XX_EthB_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0xA000)
DECL|macro|IXP4XX_USB_BASE_VIRT
mdefine_line|#define IXP4XX_USB_BASE_VIRT&t;(IXP4XX_PERIPHERAL_BASE_VIRT + 0xB000)
multiline_comment|/*&n; * Constants to make it easy to access  Interrupt Controller registers&n; */
DECL|macro|IXP4XX_ICPR_OFFSET
mdefine_line|#define IXP4XX_ICPR_OFFSET&t;0x00 /* Interrupt Status */
DECL|macro|IXP4XX_ICMR_OFFSET
mdefine_line|#define IXP4XX_ICMR_OFFSET&t;0x04 /* Interrupt Enable */
DECL|macro|IXP4XX_ICLR_OFFSET
mdefine_line|#define IXP4XX_ICLR_OFFSET&t;0x08 /* Interrupt IRQ/FIQ Select */
DECL|macro|IXP4XX_ICIP_OFFSET
mdefine_line|#define IXP4XX_ICIP_OFFSET      0x0C /* IRQ Status */
DECL|macro|IXP4XX_ICFP_OFFSET
mdefine_line|#define IXP4XX_ICFP_OFFSET&t;0x10 /* FIQ Status */
DECL|macro|IXP4XX_ICHR_OFFSET
mdefine_line|#define IXP4XX_ICHR_OFFSET&t;0x14 /* Interrupt Priority */
DECL|macro|IXP4XX_ICIH_OFFSET
mdefine_line|#define IXP4XX_ICIH_OFFSET&t;0x18 /* IRQ Highest Pri Int */
DECL|macro|IXP4XX_ICFH_OFFSET
mdefine_line|#define IXP4XX_ICFH_OFFSET&t;0x1C /* FIQ Highest Pri Int */
multiline_comment|/*&n; * IXP465-only&n; */
DECL|macro|IXP4XX_ICPR2_OFFSET
mdefine_line|#define&t;IXP4XX_ICPR2_OFFSET&t;0x20 /* Interrupt Status 2 */
DECL|macro|IXP4XX_ICMR2_OFFSET
mdefine_line|#define&t;IXP4XX_ICMR2_OFFSET&t;0x24 /* Interrupt Enable 2 */
DECL|macro|IXP4XX_ICLR2_OFFSET
mdefine_line|#define&t;IXP4XX_ICLR2_OFFSET&t;0x28 /* Interrupt IRQ/FIQ Select 2 */
DECL|macro|IXP4XX_ICIP2_OFFSET
mdefine_line|#define IXP4XX_ICIP2_OFFSET     0x2C /* IRQ Status */
DECL|macro|IXP4XX_ICFP2_OFFSET
mdefine_line|#define IXP4XX_ICFP2_OFFSET&t;0x30 /* FIQ Status */
DECL|macro|IXP4XX_ICEEN_OFFSET
mdefine_line|#define IXP4XX_ICEEN_OFFSET&t;0x34 /* Error High Pri Enable */
multiline_comment|/*&n; * Interrupt Controller Register Definitions.&n; */
DECL|macro|IXP4XX_INTC_REG
mdefine_line|#define IXP4XX_INTC_REG(x) ((volatile u32 *)(IXP4XX_INTC_BASE_VIRT+(x)))
DECL|macro|IXP4XX_ICPR
mdefine_line|#define IXP4XX_ICPR&t;IXP4XX_INTC_REG(IXP4XX_ICPR_OFFSET)
DECL|macro|IXP4XX_ICMR
mdefine_line|#define IXP4XX_ICMR     IXP4XX_INTC_REG(IXP4XX_ICMR_OFFSET)
DECL|macro|IXP4XX_ICLR
mdefine_line|#define IXP4XX_ICLR     IXP4XX_INTC_REG(IXP4XX_ICLR_OFFSET)
DECL|macro|IXP4XX_ICIP
mdefine_line|#define IXP4XX_ICIP     IXP4XX_INTC_REG(IXP4XX_ICIP_OFFSET)
DECL|macro|IXP4XX_ICFP
mdefine_line|#define IXP4XX_ICFP     IXP4XX_INTC_REG(IXP4XX_ICFP_OFFSET)
DECL|macro|IXP4XX_ICHR
mdefine_line|#define IXP4XX_ICHR     IXP4XX_INTC_REG(IXP4XX_ICHR_OFFSET)
DECL|macro|IXP4XX_ICIH
mdefine_line|#define IXP4XX_ICIH     IXP4XX_INTC_REG(IXP4XX_ICIH_OFFSET) 
DECL|macro|IXP4XX_ICFH
mdefine_line|#define IXP4XX_ICFH     IXP4XX_INTC_REG(IXP4XX_ICFH_OFFSET)
DECL|macro|IXP4XX_ICPR2
mdefine_line|#define IXP4XX_ICPR2&t;IXP4XX_INTC_REG(IXP4XX_ICPR2_OFFSET)
DECL|macro|IXP4XX_ICMR2
mdefine_line|#define IXP4XX_ICMR2    IXP4XX_INTC_REG(IXP4XX_ICMR2_OFFSET)
DECL|macro|IXP4XX_ICLR2
mdefine_line|#define IXP4XX_ICLR2    IXP4XX_INTC_REG(IXP4XX_ICLR2_OFFSET)
DECL|macro|IXP4XX_ICIP2
mdefine_line|#define IXP4XX_ICIP2    IXP4XX_INTC_REG(IXP4XX_ICIP2_OFFSET)
DECL|macro|IXP4XX_ICFP2
mdefine_line|#define IXP4XX_ICFP2    IXP4XX_INTC_REG(IXP4XX_ICFP2_OFFSET)
DECL|macro|IXP4XX_ICEEN
mdefine_line|#define IXP4XX_ICEEN    IXP4XX_INTC_REG(IXP4XX_ICEEN_OFFSET)
multiline_comment|/*&n; * Constants to make it easy to access GPIO registers&n; */
DECL|macro|IXP4XX_GPIO_GPOUTR_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPOUTR_OFFSET       0x00
DECL|macro|IXP4XX_GPIO_GPOER_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPOER_OFFSET        0x04
DECL|macro|IXP4XX_GPIO_GPINR_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPINR_OFFSET        0x08
DECL|macro|IXP4XX_GPIO_GPISR_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPISR_OFFSET        0x0C
DECL|macro|IXP4XX_GPIO_GPIT1R_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPIT1R_OFFSET&t;0x10
DECL|macro|IXP4XX_GPIO_GPIT2R_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPIT2R_OFFSET&t;0x14
DECL|macro|IXP4XX_GPIO_GPCLKR_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPCLKR_OFFSET&t;0x18
DECL|macro|IXP4XX_GPIO_GPDBSELR_OFFSET
mdefine_line|#define IXP4XX_GPIO_GPDBSELR_OFFSET&t;0x1C
multiline_comment|/* &n; * GPIO Register Definitions.&n; * [Only perform 32bit reads/writes]&n; */
DECL|macro|IXP4XX_GPIO_REG
mdefine_line|#define IXP4XX_GPIO_REG(x) ((volatile u32 *)(IXP4XX_GPIO_BASE_VIRT+(x)))
DECL|macro|IXP4XX_GPIO_GPOUTR
mdefine_line|#define IXP4XX_GPIO_GPOUTR&t;IXP4XX_GPIO_REG(IXP4XX_GPIO_GPOUTR_OFFSET)
DECL|macro|IXP4XX_GPIO_GPOER
mdefine_line|#define IXP4XX_GPIO_GPOER       IXP4XX_GPIO_REG(IXP4XX_GPIO_GPOER_OFFSET)
DECL|macro|IXP4XX_GPIO_GPINR
mdefine_line|#define IXP4XX_GPIO_GPINR       IXP4XX_GPIO_REG(IXP4XX_GPIO_GPINR_OFFSET)
DECL|macro|IXP4XX_GPIO_GPISR
mdefine_line|#define IXP4XX_GPIO_GPISR       IXP4XX_GPIO_REG(IXP4XX_GPIO_GPISR_OFFSET)
DECL|macro|IXP4XX_GPIO_GPIT1R
mdefine_line|#define IXP4XX_GPIO_GPIT1R      IXP4XX_GPIO_REG(IXP4XX_GPIO_GPIT1R_OFFSET)
DECL|macro|IXP4XX_GPIO_GPIT2R
mdefine_line|#define IXP4XX_GPIO_GPIT2R      IXP4XX_GPIO_REG(IXP4XX_GPIO_GPIT2R_OFFSET)
DECL|macro|IXP4XX_GPIO_GPCLKR
mdefine_line|#define IXP4XX_GPIO_GPCLKR      IXP4XX_GPIO_REG(IXP4XX_GPIO_GPCLKR_OFFSET)
DECL|macro|IXP4XX_GPIO_GPDBSELR
mdefine_line|#define IXP4XX_GPIO_GPDBSELR    IXP4XX_GPIO_REG(IXP4XX_GPIO_GPDBSELR_OFFSET)
multiline_comment|/*&n; * GPIO register bit definitions&n; */
multiline_comment|/* Interrupt styles&n; */
DECL|macro|IXP4XX_GPIO_STYLE_ACTIVE_HIGH
mdefine_line|#define IXP4XX_GPIO_STYLE_ACTIVE_HIGH&t;0x0
DECL|macro|IXP4XX_GPIO_STYLE_ACTIVE_LOW
mdefine_line|#define IXP4XX_GPIO_STYLE_ACTIVE_LOW&t;0x1
DECL|macro|IXP4XX_GPIO_STYLE_RISING_EDGE
mdefine_line|#define IXP4XX_GPIO_STYLE_RISING_EDGE&t;0x2
DECL|macro|IXP4XX_GPIO_STYLE_FALLING_EDGE
mdefine_line|#define IXP4XX_GPIO_STYLE_FALLING_EDGE&t;0x3
DECL|macro|IXP4XX_GPIO_STYLE_TRANSITIONAL
mdefine_line|#define IXP4XX_GPIO_STYLE_TRANSITIONAL&t;0x4
multiline_comment|/* &n; * Mask used to clear interrupt styles &n; */
DECL|macro|IXP4XX_GPIO_STYLE_CLEAR
mdefine_line|#define IXP4XX_GPIO_STYLE_CLEAR&t;&t;0x7
DECL|macro|IXP4XX_GPIO_STYLE_SIZE
mdefine_line|#define IXP4XX_GPIO_STYLE_SIZE&t;&t;3
multiline_comment|/*&n; * Constants to make it easy to access Timer Control/Status registers&n; */
DECL|macro|IXP4XX_OSTS_OFFSET
mdefine_line|#define IXP4XX_OSTS_OFFSET&t;0x00  /* Continious TimeStamp */
DECL|macro|IXP4XX_OST1_OFFSET
mdefine_line|#define IXP4XX_OST1_OFFSET&t;0x04  /* Timer 1 Timestamp */
DECL|macro|IXP4XX_OSRT1_OFFSET
mdefine_line|#define IXP4XX_OSRT1_OFFSET&t;0x08  /* Timer 1 Reload */
DECL|macro|IXP4XX_OST2_OFFSET
mdefine_line|#define IXP4XX_OST2_OFFSET&t;0x0C  /* Timer 2 Timestamp */
DECL|macro|IXP4XX_OSRT2_OFFSET
mdefine_line|#define IXP4XX_OSRT2_OFFSET&t;0x10  /* Timer 2 Reload */
DECL|macro|IXP4XX_OSWT_OFFSET
mdefine_line|#define IXP4XX_OSWT_OFFSET&t;0x14  /* Watchdog Timer */
DECL|macro|IXP4XX_OSWE_OFFSET
mdefine_line|#define IXP4XX_OSWE_OFFSET&t;0x18  /* Watchdog Enable */
DECL|macro|IXP4XX_OSWK_OFFSET
mdefine_line|#define IXP4XX_OSWK_OFFSET&t;0x1C  /* Watchdog Key */
DECL|macro|IXP4XX_OSST_OFFSET
mdefine_line|#define IXP4XX_OSST_OFFSET&t;0x20  /* Timer Status */
multiline_comment|/*&n; * Operating System Timer Register Definitions.&n; */
DECL|macro|IXP4XX_TIMER_REG
mdefine_line|#define IXP4XX_TIMER_REG(x) ((volatile u32 *)(IXP4XX_TIMER_BASE_VIRT+(x)))
DECL|macro|IXP4XX_OSTS
mdefine_line|#define IXP4XX_OSTS&t;IXP4XX_TIMER_REG(IXP4XX_OSTS_OFFSET)
DECL|macro|IXP4XX_OST1
mdefine_line|#define IXP4XX_OST1&t;IXP4XX_TIMER_REG(IXP4XX_OST1_OFFSET)
DECL|macro|IXP4XX_OSRT1
mdefine_line|#define IXP4XX_OSRT1&t;IXP4XX_TIMER_REG(IXP4XX_OSRT1_OFFSET)
DECL|macro|IXP4XX_OST2
mdefine_line|#define IXP4XX_OST2&t;IXP4XX_TIMER_REG(IXP4XX_OST2_OFFSET)
DECL|macro|IXP4XX_OSRT2
mdefine_line|#define IXP4XX_OSRT2&t;IXP4XX_TIMER_REG(IXP4XX_OSRT2_OFFSET)
DECL|macro|IXP4XX_OSWT
mdefine_line|#define IXP4XX_OSWT&t;IXP4XX_TIMER_REG(IXP4XX_OSWT_OFFSET)
DECL|macro|IXP4XX_OSWE
mdefine_line|#define IXP4XX_OSWE&t;IXP4XX_TIMER_REG(IXP4XX_OSWE_OFFSET)
DECL|macro|IXP4XX_OSWK
mdefine_line|#define IXP4XX_OSWK&t;IXP4XX_TIMER_REG(IXP4XX_OSWK_OFFSET)
DECL|macro|IXP4XX_OSST
mdefine_line|#define IXP4XX_OSST&t;IXP4XX_TIMER_REG(IXP4XX_OSST_OFFSET)
multiline_comment|/*&n; * Timer register values and bit definitions &n; */
DECL|macro|IXP4XX_OST_ENABLE
mdefine_line|#define IXP4XX_OST_ENABLE&t;&t;0x00000001
DECL|macro|IXP4XX_OST_ONE_SHOT
mdefine_line|#define IXP4XX_OST_ONE_SHOT&t;&t;0x00000002
multiline_comment|/* Low order bits of reload value ignored */
DECL|macro|IXP4XX_OST_RELOAD_MASK
mdefine_line|#define IXP4XX_OST_RELOAD_MASK&t;&t;0x00000003
DECL|macro|IXP4XX_OST_DISABLED
mdefine_line|#define IXP4XX_OST_DISABLED&t;&t;0x00000000
DECL|macro|IXP4XX_OSST_TIMER_1_PEND
mdefine_line|#define IXP4XX_OSST_TIMER_1_PEND&t;0x00000001
DECL|macro|IXP4XX_OSST_TIMER_2_PEND
mdefine_line|#define IXP4XX_OSST_TIMER_2_PEND&t;0x00000002
DECL|macro|IXP4XX_OSST_TIMER_TS_PEND
mdefine_line|#define IXP4XX_OSST_TIMER_TS_PEND&t;0x00000004
DECL|macro|IXP4XX_OSST_TIMER_WDOG_PEND
mdefine_line|#define IXP4XX_OSST_TIMER_WDOG_PEND&t;0x00000008
DECL|macro|IXP4XX_OSST_TIMER_WARM_RESET
mdefine_line|#define IXP4XX_OSST_TIMER_WARM_RESET&t;0x00000010
DECL|macro|IXP4XX_WDT_KEY
mdefine_line|#define&t;IXP4XX_WDT_KEY&t;&t;&t;0x0000482E
DECL|macro|IXP4XX_WDT_RESET_ENABLE
mdefine_line|#define&t;IXP4XX_WDT_RESET_ENABLE&t;&t;0x00000001
DECL|macro|IXP4XX_WDT_IRQ_ENABLE
mdefine_line|#define&t;IXP4XX_WDT_IRQ_ENABLE&t;&t;0x00000002
DECL|macro|IXP4XX_WDT_COUNT_ENABLE
mdefine_line|#define&t;IXP4XX_WDT_COUNT_ENABLE&t;&t;0x00000004
multiline_comment|/*&n; * Constants to make it easy to access PCI Control/Status registers&n; */
DECL|macro|PCI_NP_AD_OFFSET
mdefine_line|#define PCI_NP_AD_OFFSET            0x00
DECL|macro|PCI_NP_CBE_OFFSET
mdefine_line|#define PCI_NP_CBE_OFFSET           0x04
DECL|macro|PCI_NP_WDATA_OFFSET
mdefine_line|#define PCI_NP_WDATA_OFFSET         0x08
DECL|macro|PCI_NP_RDATA_OFFSET
mdefine_line|#define PCI_NP_RDATA_OFFSET         0x0c
DECL|macro|PCI_CRP_AD_CBE_OFFSET
mdefine_line|#define PCI_CRP_AD_CBE_OFFSET       0x10
DECL|macro|PCI_CRP_WDATA_OFFSET
mdefine_line|#define PCI_CRP_WDATA_OFFSET        0x14
DECL|macro|PCI_CRP_RDATA_OFFSET
mdefine_line|#define PCI_CRP_RDATA_OFFSET        0x18
DECL|macro|PCI_CSR_OFFSET
mdefine_line|#define PCI_CSR_OFFSET              0x1c
DECL|macro|PCI_ISR_OFFSET
mdefine_line|#define PCI_ISR_OFFSET              0x20
DECL|macro|PCI_INTEN_OFFSET
mdefine_line|#define PCI_INTEN_OFFSET            0x24
DECL|macro|PCI_DMACTRL_OFFSET
mdefine_line|#define PCI_DMACTRL_OFFSET          0x28
DECL|macro|PCI_AHBMEMBASE_OFFSET
mdefine_line|#define PCI_AHBMEMBASE_OFFSET       0x2c
DECL|macro|PCI_AHBIOBASE_OFFSET
mdefine_line|#define PCI_AHBIOBASE_OFFSET        0x30
DECL|macro|PCI_PCIMEMBASE_OFFSET
mdefine_line|#define PCI_PCIMEMBASE_OFFSET       0x34
DECL|macro|PCI_AHBDOORBELL_OFFSET
mdefine_line|#define PCI_AHBDOORBELL_OFFSET      0x38
DECL|macro|PCI_PCIDOORBELL_OFFSET
mdefine_line|#define PCI_PCIDOORBELL_OFFSET      0x3C
DECL|macro|PCI_ATPDMA0_AHBADDR_OFFSET
mdefine_line|#define PCI_ATPDMA0_AHBADDR_OFFSET  0x40
DECL|macro|PCI_ATPDMA0_PCIADDR_OFFSET
mdefine_line|#define PCI_ATPDMA0_PCIADDR_OFFSET  0x44
DECL|macro|PCI_ATPDMA0_LENADDR_OFFSET
mdefine_line|#define PCI_ATPDMA0_LENADDR_OFFSET  0x48
DECL|macro|PCI_ATPDMA1_AHBADDR_OFFSET
mdefine_line|#define PCI_ATPDMA1_AHBADDR_OFFSET  0x4C
DECL|macro|PCI_ATPDMA1_PCIADDR_OFFSET
mdefine_line|#define PCI_ATPDMA1_PCIADDR_OFFSET  0x50
DECL|macro|PCI_ATPDMA1_LENADDR_OFFSET
mdefine_line|#define PCI_ATPDMA1_LENADDR_OFFSET&t;0x54
multiline_comment|/*&n; * PCI Control/Status Registers&n; */
DECL|macro|IXP4XX_PCI_CSR
mdefine_line|#define IXP4XX_PCI_CSR(x) ((volatile u32 *)(IXP4XX_PCI_CFG_BASE_VIRT+(x)))
DECL|macro|PCI_NP_AD
mdefine_line|#define PCI_NP_AD               IXP4XX_PCI_CSR(PCI_NP_AD_OFFSET)
DECL|macro|PCI_NP_CBE
mdefine_line|#define PCI_NP_CBE              IXP4XX_PCI_CSR(PCI_NP_CBE_OFFSET)
DECL|macro|PCI_NP_WDATA
mdefine_line|#define PCI_NP_WDATA            IXP4XX_PCI_CSR(PCI_NP_WDATA_OFFSET)
DECL|macro|PCI_NP_RDATA
mdefine_line|#define PCI_NP_RDATA            IXP4XX_PCI_CSR(PCI_NP_RDATA_OFFSET)
DECL|macro|PCI_CRP_AD_CBE
mdefine_line|#define PCI_CRP_AD_CBE          IXP4XX_PCI_CSR(PCI_CRP_AD_CBE_OFFSET)
DECL|macro|PCI_CRP_WDATA
mdefine_line|#define PCI_CRP_WDATA           IXP4XX_PCI_CSR(PCI_CRP_WDATA_OFFSET)
DECL|macro|PCI_CRP_RDATA
mdefine_line|#define PCI_CRP_RDATA           IXP4XX_PCI_CSR(PCI_CRP_RDATA_OFFSET)
DECL|macro|PCI_CSR
mdefine_line|#define PCI_CSR                 IXP4XX_PCI_CSR(PCI_CSR_OFFSET) 
DECL|macro|PCI_ISR
mdefine_line|#define PCI_ISR                 IXP4XX_PCI_CSR(PCI_ISR_OFFSET)
DECL|macro|PCI_INTEN
mdefine_line|#define PCI_INTEN               IXP4XX_PCI_CSR(PCI_INTEN_OFFSET)
DECL|macro|PCI_DMACTRL
mdefine_line|#define PCI_DMACTRL             IXP4XX_PCI_CSR(PCI_DMACTRL_OFFSET)
DECL|macro|PCI_AHBMEMBASE
mdefine_line|#define PCI_AHBMEMBASE          IXP4XX_PCI_CSR(PCI_AHBMEMBASE_OFFSET)
DECL|macro|PCI_AHBIOBASE
mdefine_line|#define PCI_AHBIOBASE           IXP4XX_PCI_CSR(PCI_AHBIOBASE_OFFSET)
DECL|macro|PCI_PCIMEMBASE
mdefine_line|#define PCI_PCIMEMBASE          IXP4XX_PCI_CSR(PCI_PCIMEMBASE_OFFSET)
DECL|macro|PCI_AHBDOORBELL
mdefine_line|#define PCI_AHBDOORBELL         IXP4XX_PCI_CSR(PCI_AHBDOORBELL_OFFSET)
DECL|macro|PCI_PCIDOORBELL
mdefine_line|#define PCI_PCIDOORBELL         IXP4XX_PCI_CSR(PCI_PCIDOORBELL_OFFSET)
DECL|macro|PCI_ATPDMA0_AHBADDR
mdefine_line|#define PCI_ATPDMA0_AHBADDR     IXP4XX_PCI_CSR(PCI_ATPDMA0_AHBADDR_OFFSET)
DECL|macro|PCI_ATPDMA0_PCIADDR
mdefine_line|#define PCI_ATPDMA0_PCIADDR     IXP4XX_PCI_CSR(PCI_ATPDMA0_PCIADDR_OFFSET)
DECL|macro|PCI_ATPDMA0_LENADDR
mdefine_line|#define PCI_ATPDMA0_LENADDR     IXP4XX_PCI_CSR(PCI_ATPDMA0_LENADDR_OFFSET)
DECL|macro|PCI_ATPDMA1_AHBADDR
mdefine_line|#define PCI_ATPDMA1_AHBADDR     IXP4XX_PCI_CSR(PCI_ATPDMA1_AHBADDR_OFFSET)
DECL|macro|PCI_ATPDMA1_PCIADDR
mdefine_line|#define PCI_ATPDMA1_PCIADDR     IXP4XX_PCI_CSR(PCI_ATPDMA1_PCIADDR_OFFSET)
DECL|macro|PCI_ATPDMA1_LENADDR
mdefine_line|#define PCI_ATPDMA1_LENADDR     IXP4XX_PCI_CSR(PCI_ATPDMA1_LENADDR_OFFSET)
multiline_comment|/*&n; * PCI register values and bit definitions &n; */
multiline_comment|/* CSR bit definitions */
DECL|macro|PCI_CSR_HOST
mdefine_line|#define PCI_CSR_HOST    &t;0x00000001
DECL|macro|PCI_CSR_ARBEN
mdefine_line|#define PCI_CSR_ARBEN   &t;0x00000002
DECL|macro|PCI_CSR_ADS
mdefine_line|#define PCI_CSR_ADS     &t;0x00000004
DECL|macro|PCI_CSR_PDS
mdefine_line|#define PCI_CSR_PDS     &t;0x00000008
DECL|macro|PCI_CSR_ABE
mdefine_line|#define PCI_CSR_ABE     &t;0x00000010
DECL|macro|PCI_CSR_DBT
mdefine_line|#define PCI_CSR_DBT     &t;0x00000020
DECL|macro|PCI_CSR_ASE
mdefine_line|#define PCI_CSR_ASE     &t;0x00000100
DECL|macro|PCI_CSR_IC
mdefine_line|#define PCI_CSR_IC      &t;0x00008000
multiline_comment|/* ISR (Interrupt status) Register bit definitions */
DECL|macro|PCI_ISR_PSE
mdefine_line|#define PCI_ISR_PSE     &t;0x00000001
DECL|macro|PCI_ISR_PFE
mdefine_line|#define PCI_ISR_PFE     &t;0x00000002
DECL|macro|PCI_ISR_PPE
mdefine_line|#define PCI_ISR_PPE     &t;0x00000004
DECL|macro|PCI_ISR_AHBE
mdefine_line|#define PCI_ISR_AHBE    &t;0x00000008
DECL|macro|PCI_ISR_APDC
mdefine_line|#define PCI_ISR_APDC    &t;0x00000010
DECL|macro|PCI_ISR_PADC
mdefine_line|#define PCI_ISR_PADC    &t;0x00000020
DECL|macro|PCI_ISR_ADB
mdefine_line|#define PCI_ISR_ADB     &t;0x00000040
DECL|macro|PCI_ISR_PDB
mdefine_line|#define PCI_ISR_PDB     &t;0x00000080
multiline_comment|/* INTEN (Interrupt Enable) Register bit definitions */
DECL|macro|PCI_INTEN_PSE
mdefine_line|#define PCI_INTEN_PSE   &t;0x00000001
DECL|macro|PCI_INTEN_PFE
mdefine_line|#define PCI_INTEN_PFE   &t;0x00000002
DECL|macro|PCI_INTEN_PPE
mdefine_line|#define PCI_INTEN_PPE   &t;0x00000004
DECL|macro|PCI_INTEN_AHBE
mdefine_line|#define PCI_INTEN_AHBE  &t;0x00000008
DECL|macro|PCI_INTEN_APDC
mdefine_line|#define PCI_INTEN_APDC  &t;0x00000010
DECL|macro|PCI_INTEN_PADC
mdefine_line|#define PCI_INTEN_PADC  &t;0x00000020
DECL|macro|PCI_INTEN_ADB
mdefine_line|#define PCI_INTEN_ADB   &t;0x00000040
DECL|macro|PCI_INTEN_PDB
mdefine_line|#define PCI_INTEN_PDB   &t;0x00000080
multiline_comment|/*&n; * Shift value for byte enable on NP cmd/byte enable register&n; */
DECL|macro|IXP4XX_PCI_NP_CBE_BESL
mdefine_line|#define IXP4XX_PCI_NP_CBE_BESL&t;&t;4
multiline_comment|/*&n; * PCI commands supported by NP access unit&n; */
DECL|macro|NP_CMD_IOREAD
mdefine_line|#define NP_CMD_IOREAD&t;&t;&t;0x2
DECL|macro|NP_CMD_IOWRITE
mdefine_line|#define NP_CMD_IOWRITE&t;&t;&t;0x3
DECL|macro|NP_CMD_CONFIGREAD
mdefine_line|#define NP_CMD_CONFIGREAD&t;&t;0xa
DECL|macro|NP_CMD_CONFIGWRITE
mdefine_line|#define NP_CMD_CONFIGWRITE&t;&t;0xb
DECL|macro|NP_CMD_MEMREAD
mdefine_line|#define NP_CMD_MEMREAD&t;&t;&t;0x6
DECL|macro|NP_CMD_MEMWRITE
mdefine_line|#define&t;NP_CMD_MEMWRITE&t;&t;&t;0x7
multiline_comment|/*&n; * Constants for CRP access into local config space&n; */
DECL|macro|CRP_AD_CBE_BESL
mdefine_line|#define CRP_AD_CBE_BESL         20
DECL|macro|CRP_AD_CBE_WRITE
mdefine_line|#define CRP_AD_CBE_WRITE&t;0x00010000
multiline_comment|/*&n; * USB Device Controller&n; *&n; * These are used by the USB gadget driver, so they don&squot;t follow the&n; * IXP4XX_ naming convetions.&n; *&n; */
DECL|macro|IXP4XX_USB_REG
macro_line|# define IXP4XX_USB_REG(x)       (*((volatile u32 *)(x)))
multiline_comment|/* UDC Undocumented - Reserved1 */
DECL|macro|UDC_RES1
mdefine_line|#define UDC_RES1&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0004)  
multiline_comment|/* UDC Undocumented - Reserved2 */
DECL|macro|UDC_RES2
mdefine_line|#define UDC_RES2&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0008)  
multiline_comment|/* UDC Undocumented - Reserved3 */
DECL|macro|UDC_RES3
mdefine_line|#define UDC_RES3&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x000C)  
multiline_comment|/* UDC Control Register */
DECL|macro|UDCCR
mdefine_line|#define UDCCR&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0000)  
multiline_comment|/* UDC Endpoint 0 Control/Status Register */
DECL|macro|UDCCS0
mdefine_line|#define UDCCS0&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0010)  
multiline_comment|/* UDC Endpoint 1 (IN) Control/Status Register */
DECL|macro|UDCCS1
mdefine_line|#define UDCCS1&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0014)  
multiline_comment|/* UDC Endpoint 2 (OUT) Control/Status Register */
DECL|macro|UDCCS2
mdefine_line|#define UDCCS2&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0018)  
multiline_comment|/* UDC Endpoint 3 (IN) Control/Status Register */
DECL|macro|UDCCS3
mdefine_line|#define UDCCS3&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x001C)  
multiline_comment|/* UDC Endpoint 4 (OUT) Control/Status Register */
DECL|macro|UDCCS4
mdefine_line|#define UDCCS4&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0020)  
multiline_comment|/* UDC Endpoint 5 (Interrupt) Control/Status Register */
DECL|macro|UDCCS5
mdefine_line|#define UDCCS5&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0024)  
multiline_comment|/* UDC Endpoint 6 (IN) Control/Status Register */
DECL|macro|UDCCS6
mdefine_line|#define UDCCS6&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0028)  
multiline_comment|/* UDC Endpoint 7 (OUT) Control/Status Register */
DECL|macro|UDCCS7
mdefine_line|#define UDCCS7&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x002C)  
multiline_comment|/* UDC Endpoint 8 (IN) Control/Status Register */
DECL|macro|UDCCS8
mdefine_line|#define UDCCS8&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0030)  
multiline_comment|/* UDC Endpoint 9 (OUT) Control/Status Register */
DECL|macro|UDCCS9
mdefine_line|#define UDCCS9&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0034)  
multiline_comment|/* UDC Endpoint 10 (Interrupt) Control/Status Register */
DECL|macro|UDCCS10
mdefine_line|#define UDCCS10&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0038)  
multiline_comment|/* UDC Endpoint 11 (IN) Control/Status Register */
DECL|macro|UDCCS11
mdefine_line|#define UDCCS11&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x003C)  
multiline_comment|/* UDC Endpoint 12 (OUT) Control/Status Register */
DECL|macro|UDCCS12
mdefine_line|#define UDCCS12&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0040)  
multiline_comment|/* UDC Endpoint 13 (IN) Control/Status Register */
DECL|macro|UDCCS13
mdefine_line|#define UDCCS13&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0044)  
multiline_comment|/* UDC Endpoint 14 (OUT) Control/Status Register */
DECL|macro|UDCCS14
mdefine_line|#define UDCCS14&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0048)  
multiline_comment|/* UDC Endpoint 15 (Interrupt) Control/Status Register */
DECL|macro|UDCCS15
mdefine_line|#define UDCCS15&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x004C)  
multiline_comment|/* UDC Frame Number Register High */
DECL|macro|UFNRH
mdefine_line|#define UFNRH&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0060)  
multiline_comment|/* UDC Frame Number Register Low */
DECL|macro|UFNRL
mdefine_line|#define UFNRL&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0064)  
multiline_comment|/* UDC Byte Count Reg 2 */
DECL|macro|UBCR2
mdefine_line|#define UBCR2&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0068)  
multiline_comment|/* UDC Byte Count Reg 4 */
DECL|macro|UBCR4
mdefine_line|#define UBCR4&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x006c)  
multiline_comment|/* UDC Byte Count Reg 7 */
DECL|macro|UBCR7
mdefine_line|#define UBCR7&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0070)  
multiline_comment|/* UDC Byte Count Reg 9 */
DECL|macro|UBCR9
mdefine_line|#define UBCR9&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0074)  
multiline_comment|/* UDC Byte Count Reg 12 */
DECL|macro|UBCR12
mdefine_line|#define UBCR12&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0078)  
multiline_comment|/* UDC Byte Count Reg 14 */
DECL|macro|UBCR14
mdefine_line|#define UBCR14&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x007c)  
multiline_comment|/* UDC Endpoint 0 Data Register */
DECL|macro|UDDR0
mdefine_line|#define UDDR0&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0080)  
multiline_comment|/* UDC Endpoint 1 Data Register */
DECL|macro|UDDR1
mdefine_line|#define UDDR1&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0100)  
multiline_comment|/* UDC Endpoint 2 Data Register */
DECL|macro|UDDR2
mdefine_line|#define UDDR2&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0180)  
multiline_comment|/* UDC Endpoint 3 Data Register */
DECL|macro|UDDR3
mdefine_line|#define UDDR3&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0200)  
multiline_comment|/* UDC Endpoint 4 Data Register */
DECL|macro|UDDR4
mdefine_line|#define UDDR4&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0400)  
multiline_comment|/* UDC Endpoint 5 Data Register */
DECL|macro|UDDR5
mdefine_line|#define UDDR5&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x00A0)  
multiline_comment|/* UDC Endpoint 6 Data Register */
DECL|macro|UDDR6
mdefine_line|#define UDDR6&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0600)  
multiline_comment|/* UDC Endpoint 7 Data Register */
DECL|macro|UDDR7
mdefine_line|#define UDDR7&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0680)  
multiline_comment|/* UDC Endpoint 8 Data Register */
DECL|macro|UDDR8
mdefine_line|#define UDDR8&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0700)  
multiline_comment|/* UDC Endpoint 9 Data Register */
DECL|macro|UDDR9
mdefine_line|#define UDDR9&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0900)  
multiline_comment|/* UDC Endpoint 10 Data Register */
DECL|macro|UDDR10
mdefine_line|#define UDDR10&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x00C0)  
multiline_comment|/* UDC Endpoint 11 Data Register */
DECL|macro|UDDR11
mdefine_line|#define UDDR11&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0B00)  
multiline_comment|/* UDC Endpoint 12 Data Register */
DECL|macro|UDDR12
mdefine_line|#define UDDR12&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0B80)  
multiline_comment|/* UDC Endpoint 13 Data Register */
DECL|macro|UDDR13
mdefine_line|#define UDDR13&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0C00)  
multiline_comment|/* UDC Endpoint 14 Data Register */
DECL|macro|UDDR14
mdefine_line|#define UDDR14&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0E00)  
multiline_comment|/* UDC Endpoint 15 Data Register */
DECL|macro|UDDR15
mdefine_line|#define UDDR15&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x00E0)  
multiline_comment|/* UDC Interrupt Control Register 0 */
DECL|macro|UICR0
mdefine_line|#define UICR0&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0050)  
multiline_comment|/* UDC Interrupt Control Register 1 */
DECL|macro|UICR1
mdefine_line|#define UICR1&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0054)  
multiline_comment|/* UDC Status Interrupt Register 0 */
DECL|macro|USIR0
mdefine_line|#define USIR0&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x0058)  
multiline_comment|/* UDC Status Interrupt Register 1 */
DECL|macro|USIR1
mdefine_line|#define USIR1&t;&t;IXP4XX_USB_REG(IXP4XX_USB_BASE_VIRT+0x005C)  
DECL|macro|UDCCR_UDE
mdefine_line|#define UDCCR_UDE&t;(1 &lt;&lt; 0)&t;/* UDC enable */
DECL|macro|UDCCR_UDA
mdefine_line|#define UDCCR_UDA&t;(1 &lt;&lt; 1)&t;/* UDC active */
DECL|macro|UDCCR_RSM
mdefine_line|#define UDCCR_RSM&t;(1 &lt;&lt; 2)&t;/* Device resume */
DECL|macro|UDCCR_RESIR
mdefine_line|#define UDCCR_RESIR&t;(1 &lt;&lt; 3)&t;/* Resume interrupt request */
DECL|macro|UDCCR_SUSIR
mdefine_line|#define UDCCR_SUSIR&t;(1 &lt;&lt; 4)&t;/* Suspend interrupt request */
DECL|macro|UDCCR_SRM
mdefine_line|#define UDCCR_SRM&t;(1 &lt;&lt; 5)&t;/* Suspend/resume interrupt mask */
DECL|macro|UDCCR_RSTIR
mdefine_line|#define UDCCR_RSTIR&t;(1 &lt;&lt; 6)&t;/* Reset interrupt request */
DECL|macro|UDCCR_REM
mdefine_line|#define UDCCR_REM&t;(1 &lt;&lt; 7)&t;/* Reset interrupt mask */
DECL|macro|UDCCS0_OPR
mdefine_line|#define UDCCS0_OPR&t;(1 &lt;&lt; 0)&t;/* OUT packet ready */
DECL|macro|UDCCS0_IPR
mdefine_line|#define UDCCS0_IPR&t;(1 &lt;&lt; 1)&t;/* IN packet ready */
DECL|macro|UDCCS0_FTF
mdefine_line|#define UDCCS0_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS0_DRWF
mdefine_line|#define UDCCS0_DRWF&t;(1 &lt;&lt; 3)&t;/* Device remote wakeup feature */
DECL|macro|UDCCS0_SST
mdefine_line|#define UDCCS0_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS0_FST
mdefine_line|#define UDCCS0_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS0_RNE
mdefine_line|#define UDCCS0_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO no empty */
DECL|macro|UDCCS0_SA
mdefine_line|#define UDCCS0_SA&t;(1 &lt;&lt; 7)&t;/* Setup active */
DECL|macro|UDCCS_BI_TFS
mdefine_line|#define UDCCS_BI_TFS&t;(1 &lt;&lt; 0)&t;/* Transmit FIFO service */
DECL|macro|UDCCS_BI_TPC
mdefine_line|#define UDCCS_BI_TPC&t;(1 &lt;&lt; 1)&t;/* Transmit packet complete */
DECL|macro|UDCCS_BI_FTF
mdefine_line|#define UDCCS_BI_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS_BI_TUR
mdefine_line|#define UDCCS_BI_TUR&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO underrun */
DECL|macro|UDCCS_BI_SST
mdefine_line|#define UDCCS_BI_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS_BI_FST
mdefine_line|#define UDCCS_BI_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS_BI_TSP
mdefine_line|#define UDCCS_BI_TSP&t;(1 &lt;&lt; 7)&t;/* Transmit short packet */
DECL|macro|UDCCS_BO_RFS
mdefine_line|#define UDCCS_BO_RFS&t;(1 &lt;&lt; 0)&t;/* Receive FIFO service */
DECL|macro|UDCCS_BO_RPC
mdefine_line|#define UDCCS_BO_RPC&t;(1 &lt;&lt; 1)&t;/* Receive packet complete */
DECL|macro|UDCCS_BO_DME
mdefine_line|#define UDCCS_BO_DME&t;(1 &lt;&lt; 3)&t;/* DMA enable */
DECL|macro|UDCCS_BO_SST
mdefine_line|#define UDCCS_BO_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS_BO_FST
mdefine_line|#define UDCCS_BO_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS_BO_RNE
mdefine_line|#define UDCCS_BO_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO not empty */
DECL|macro|UDCCS_BO_RSP
mdefine_line|#define UDCCS_BO_RSP&t;(1 &lt;&lt; 7)&t;/* Receive short packet */
DECL|macro|UDCCS_II_TFS
mdefine_line|#define UDCCS_II_TFS&t;(1 &lt;&lt; 0)&t;/* Transmit FIFO service */
DECL|macro|UDCCS_II_TPC
mdefine_line|#define UDCCS_II_TPC&t;(1 &lt;&lt; 1)&t;/* Transmit packet complete */
DECL|macro|UDCCS_II_FTF
mdefine_line|#define UDCCS_II_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS_II_TUR
mdefine_line|#define UDCCS_II_TUR&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO underrun */
DECL|macro|UDCCS_II_TSP
mdefine_line|#define UDCCS_II_TSP&t;(1 &lt;&lt; 7)&t;/* Transmit short packet */
DECL|macro|UDCCS_IO_RFS
mdefine_line|#define UDCCS_IO_RFS&t;(1 &lt;&lt; 0)&t;/* Receive FIFO service */
DECL|macro|UDCCS_IO_RPC
mdefine_line|#define UDCCS_IO_RPC&t;(1 &lt;&lt; 1)&t;/* Receive packet complete */
DECL|macro|UDCCS_IO_ROF
mdefine_line|#define UDCCS_IO_ROF&t;(1 &lt;&lt; 3)&t;/* Receive overflow */
DECL|macro|UDCCS_IO_DME
mdefine_line|#define UDCCS_IO_DME&t;(1 &lt;&lt; 3)&t;/* DMA enable */
DECL|macro|UDCCS_IO_RNE
mdefine_line|#define UDCCS_IO_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO not empty */
DECL|macro|UDCCS_IO_RSP
mdefine_line|#define UDCCS_IO_RSP&t;(1 &lt;&lt; 7)&t;/* Receive short packet */
DECL|macro|UDCCS_INT_TFS
mdefine_line|#define UDCCS_INT_TFS&t;(1 &lt;&lt; 0)&t;/* Transmit FIFO service */
DECL|macro|UDCCS_INT_TPC
mdefine_line|#define UDCCS_INT_TPC&t;(1 &lt;&lt; 1)&t;/* Transmit packet complete */
DECL|macro|UDCCS_INT_FTF
mdefine_line|#define UDCCS_INT_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS_INT_TUR
mdefine_line|#define UDCCS_INT_TUR&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO underrun */
DECL|macro|UDCCS_INT_SST
mdefine_line|#define UDCCS_INT_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS_INT_FST
mdefine_line|#define UDCCS_INT_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS_INT_TSP
mdefine_line|#define UDCCS_INT_TSP&t;(1 &lt;&lt; 7)&t;/* Transmit short packet */
DECL|macro|UICR0_IM0
mdefine_line|#define UICR0_IM0&t;(1 &lt;&lt; 0)&t;/* Interrupt mask ep 0 */
DECL|macro|UICR0_IM1
mdefine_line|#define UICR0_IM1&t;(1 &lt;&lt; 1)&t;/* Interrupt mask ep 1 */
DECL|macro|UICR0_IM2
mdefine_line|#define UICR0_IM2&t;(1 &lt;&lt; 2)&t;/* Interrupt mask ep 2 */
DECL|macro|UICR0_IM3
mdefine_line|#define UICR0_IM3&t;(1 &lt;&lt; 3)&t;/* Interrupt mask ep 3 */
DECL|macro|UICR0_IM4
mdefine_line|#define UICR0_IM4&t;(1 &lt;&lt; 4)&t;/* Interrupt mask ep 4 */
DECL|macro|UICR0_IM5
mdefine_line|#define UICR0_IM5&t;(1 &lt;&lt; 5)&t;/* Interrupt mask ep 5 */
DECL|macro|UICR0_IM6
mdefine_line|#define UICR0_IM6&t;(1 &lt;&lt; 6)&t;/* Interrupt mask ep 6 */
DECL|macro|UICR0_IM7
mdefine_line|#define UICR0_IM7&t;(1 &lt;&lt; 7)&t;/* Interrupt mask ep 7 */
DECL|macro|UICR1_IM8
mdefine_line|#define UICR1_IM8&t;(1 &lt;&lt; 0)&t;/* Interrupt mask ep 8 */
DECL|macro|UICR1_IM9
mdefine_line|#define UICR1_IM9&t;(1 &lt;&lt; 1)&t;/* Interrupt mask ep 9 */
DECL|macro|UICR1_IM10
mdefine_line|#define UICR1_IM10&t;(1 &lt;&lt; 2)&t;/* Interrupt mask ep 10 */
DECL|macro|UICR1_IM11
mdefine_line|#define UICR1_IM11&t;(1 &lt;&lt; 3)&t;/* Interrupt mask ep 11 */
DECL|macro|UICR1_IM12
mdefine_line|#define UICR1_IM12&t;(1 &lt;&lt; 4)&t;/* Interrupt mask ep 12 */
DECL|macro|UICR1_IM13
mdefine_line|#define UICR1_IM13&t;(1 &lt;&lt; 5)&t;/* Interrupt mask ep 13 */
DECL|macro|UICR1_IM14
mdefine_line|#define UICR1_IM14&t;(1 &lt;&lt; 6)&t;/* Interrupt mask ep 14 */
DECL|macro|UICR1_IM15
mdefine_line|#define UICR1_IM15&t;(1 &lt;&lt; 7)&t;/* Interrupt mask ep 15 */
DECL|macro|USIR0_IR0
mdefine_line|#define USIR0_IR0&t;(1 &lt;&lt; 0)&t;/* Interrup request ep 0 */
DECL|macro|USIR0_IR1
mdefine_line|#define USIR0_IR1&t;(1 &lt;&lt; 1)&t;/* Interrup request ep 1 */
DECL|macro|USIR0_IR2
mdefine_line|#define USIR0_IR2&t;(1 &lt;&lt; 2)&t;/* Interrup request ep 2 */
DECL|macro|USIR0_IR3
mdefine_line|#define USIR0_IR3&t;(1 &lt;&lt; 3)&t;/* Interrup request ep 3 */
DECL|macro|USIR0_IR4
mdefine_line|#define USIR0_IR4&t;(1 &lt;&lt; 4)&t;/* Interrup request ep 4 */
DECL|macro|USIR0_IR5
mdefine_line|#define USIR0_IR5&t;(1 &lt;&lt; 5)&t;/* Interrup request ep 5 */
DECL|macro|USIR0_IR6
mdefine_line|#define USIR0_IR6&t;(1 &lt;&lt; 6)&t;/* Interrup request ep 6 */
DECL|macro|USIR0_IR7
mdefine_line|#define USIR0_IR7&t;(1 &lt;&lt; 7)&t;/* Interrup request ep 7 */
DECL|macro|USIR1_IR8
mdefine_line|#define USIR1_IR8&t;(1 &lt;&lt; 0)&t;/* Interrup request ep 8 */
DECL|macro|USIR1_IR9
mdefine_line|#define USIR1_IR9&t;(1 &lt;&lt; 1)&t;/* Interrup request ep 9 */
DECL|macro|USIR1_IR10
mdefine_line|#define USIR1_IR10&t;(1 &lt;&lt; 2)&t;/* Interrup request ep 10 */
DECL|macro|USIR1_IR11
mdefine_line|#define USIR1_IR11&t;(1 &lt;&lt; 3)&t;/* Interrup request ep 11 */
DECL|macro|USIR1_IR12
mdefine_line|#define USIR1_IR12&t;(1 &lt;&lt; 4)&t;/* Interrup request ep 12 */
DECL|macro|USIR1_IR13
mdefine_line|#define USIR1_IR13&t;(1 &lt;&lt; 5)&t;/* Interrup request ep 13 */
DECL|macro|USIR1_IR14
mdefine_line|#define USIR1_IR14&t;(1 &lt;&lt; 6)&t;/* Interrup request ep 14 */
DECL|macro|USIR1_IR15
mdefine_line|#define USIR1_IR15&t;(1 &lt;&lt; 7)&t;/* Interrup request ep 15 */
DECL|macro|DCMD_LENGTH
mdefine_line|#define DCMD_LENGTH&t;0x01fff&t;&t;/* length mask (max = 8K - 1) */
macro_line|#ifndef __ASSEMBLY__
DECL|function|cpu_is_ixp46x
r_static
r_inline
r_int
id|cpu_is_ixp46x
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CPU_IXP46X
r_int
r_int
id|processor_id
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mrc p15, 0, %0, cr0, cr0, 0;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|processor_id
)paren
suffix:colon
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|processor_id
op_amp
l_int|0xffffff00
)paren
op_eq
l_int|0x69054200
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
