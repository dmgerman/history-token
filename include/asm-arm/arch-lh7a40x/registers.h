multiline_comment|/* include/asm-arm/arch-lh7a40x/registers.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/constants.h&gt;
macro_line|#ifndef __ASM_ARCH_REGISTERS_H
DECL|macro|__ASM_ARCH_REGISTERS_H
mdefine_line|#define __ASM_ARCH_REGISTERS_H
multiline_comment|/* Physical register base addresses */
DECL|macro|AC97_PHYS
mdefine_line|#define AC97_PHYS&t;(0x80000000)&t;/* AC97 Controller */
DECL|macro|MMC_PHYS
mdefine_line|#define MMC_PHYS&t;(0x80000100)&t;/* Multimedia Card Controller */
DECL|macro|USB_PHYS
mdefine_line|#define USB_PHYS&t;(0x80000200)&t;/* USB Client */
DECL|macro|SCI_PHYS
mdefine_line|#define SCI_PHYS&t;(0x80000300)&t;/* Secure Card Interface */
DECL|macro|CSC_PHYS
mdefine_line|#define CSC_PHYS&t;(0x80000400)&t;/* Clock/State Controller  */
DECL|macro|INTC_PHYS
mdefine_line|#define INTC_PHYS&t;(0x80000500)&t;/* Interrupt Controller */
DECL|macro|UART1_PHYS
mdefine_line|#define UART1_PHYS&t;(0x80000600)&t;/* UART1 Controller */
DECL|macro|SIR_PHYS
mdefine_line|#define SIR_PHYS&t;(0x80000600)&t;/* IR Controller, same are UART1 */
DECL|macro|UART2_PHYS
mdefine_line|#define UART2_PHYS&t;(0x80000700)&t;/* UART2 Controller */
DECL|macro|UART3_PHYS
mdefine_line|#define UART3_PHYS&t;(0x80000800)&t;/* UART3 Controller */
DECL|macro|DCDC_PHYS
mdefine_line|#define DCDC_PHYS&t;(0x80000900)&t;/* DC to DC Controller */
DECL|macro|ACI_PHYS
mdefine_line|#define ACI_PHYS&t;(0x80000a00)&t;/* Audio Codec Interface */
DECL|macro|SSP_PHYS
mdefine_line|#define SSP_PHYS&t;(0x80000b00)&t;/* Synchronous ... */
DECL|macro|TIMER_PHYS
mdefine_line|#define TIMER_PHYS&t;(0x80000c00)&t;/* Timer Controller */
DECL|macro|RTC_PHYS
mdefine_line|#define RTC_PHYS&t;(0x80000d00)&t;/* Real-time Clock */
DECL|macro|GPIO_PHYS
mdefine_line|#define GPIO_PHYS&t;(0x80000e00)&t;/* General Purpose IO */
DECL|macro|BMI_PHYS
mdefine_line|#define BMI_PHYS&t;(0x80000f00)&t;/* Battery Monitor Interface */
DECL|macro|WDT_PHYS
mdefine_line|#define WDT_PHYS&t;(0x80001400)&t;/* Watchdog Timer */
DECL|macro|SMC_PHYS
mdefine_line|#define SMC_PHYS&t;(0x80002000)&t;/* Static Memory Controller */
DECL|macro|SDRC_PHYS
mdefine_line|#define SDRC_PHYS&t;(0x80002400)&t;/* SDRAM Controller */
DECL|macro|DMAC_PHYS
mdefine_line|#define DMAC_PHYS&t;(0x80002800)&t;/* DMA Controller */
DECL|macro|CLCDC_PHYS
mdefine_line|#define CLCDC_PHYS&t;(0x80003000)&t;/* Color LCD Controller */
multiline_comment|/* Physical registers of the LH7A404 */
DECL|macro|VIC1_PHYS
mdefine_line|#define VIC1_PHYS&t;(0x80008000)&t;/* Vectored Interrupt Controller 1 */
DECL|macro|USBH_PHYS
mdefine_line|#define USBH_PHYS&t;(0x80009000)&t;/* USB OHCI host controller */
DECL|macro|VIC2_PHYS
mdefine_line|#define VIC2_PHYS&t;(0x8000a000)&t;/* Vectored Interrupt Controller 2 */
multiline_comment|/*#define KBD_PHYS&t;(0x80000e00) */
multiline_comment|/*#define LCDICP_PHYS&t;(0x80001000) */
multiline_comment|/* Clock/State Controller register */
DECL|macro|CSC_PWRCNT
mdefine_line|#define CSC_PWRCNT&t;__REG(CSC_PHYS + 0x04) /* Power control */
DECL|macro|CSC_PWRCNT_USBH_EN
mdefine_line|#define CSC_PWRCNT_USBH_EN&t;(1&lt;&lt;28)&t;/* USB Host power enable */
multiline_comment|/* Interrupt Controller registers */
DECL|macro|INTC_INTSR
mdefine_line|#define INTC_INTSR&t;__REG(INTC_PHYS + 0x00)&t;/* Status */
DECL|macro|INTC_INTRSR
mdefine_line|#define INTC_INTRSR&t;__REG(INTC_PHYS + 0x04)&t;/* Raw Status */
DECL|macro|INTC_INTENS
mdefine_line|#define INTC_INTENS&t;__REG(INTC_PHYS + 0x08)&t;/* Enable Set */
DECL|macro|INTC_INTENC
mdefine_line|#define INTC_INTENC&t;__REG(INTC_PHYS + 0x0c)&t;/* Enable Clear */
multiline_comment|/* Vectored Interrupted Controller registers */
DECL|macro|VIC1_IRQSTATUS
mdefine_line|#define VIC1_IRQSTATUS&t;__REG(VIC1_PHYS + 0x00)
DECL|macro|VIC1_FIQSTATUS
mdefine_line|#define VIC1_FIQSTATUS&t;__REG(VIC1_PHYS + 0x04)
DECL|macro|VIC1_RAWINTR
mdefine_line|#define VIC1_RAWINTR&t;__REG(VIC1_PHYS + 0x08)
DECL|macro|VIC1_INTSEL
mdefine_line|#define VIC1_INTSEL&t;__REG(VIC1_PHYS + 0x0c)
DECL|macro|VIC1_INTEN
mdefine_line|#define VIC1_INTEN&t;__REG(VIC1_PHYS + 0x10)
DECL|macro|VIC1_INTENCLR
mdefine_line|#define VIC1_INTENCLR&t;__REG(VIC1_PHYS + 0x14)
DECL|macro|VIC1_SOFTINT
mdefine_line|#define VIC1_SOFTINT&t;__REG(VIC1_PHYS + 0x18)
DECL|macro|VIC1_SOFTINTCLR
mdefine_line|#define VIC1_SOFTINTCLR&t;__REG(VIC1_PHYS + 0x1c)
DECL|macro|VIC1_PROTECT
mdefine_line|#define VIC1_PROTECT&t;__REG(VIC1_PHYS + 0x20)
DECL|macro|VIC1_VECTADDR
mdefine_line|#define VIC1_VECTADDR&t;__REG(VIC1_PHYS + 0x30)
DECL|macro|VIC1_NVADDR
mdefine_line|#define VIC1_NVADDR&t;__REG(VIC1_PHYS + 0x34)
DECL|macro|VIC1_VAD0
mdefine_line|#define VIC1_VAD0&t;__REG(VIC1_PHYS + 0x100)
DECL|macro|VIC1_VECTCNTL0
mdefine_line|#define VIC1_VECTCNTL0&t;__REG(VIC1_PHYS + 0x200)
DECL|macro|VIC2_IRQSTATUS
mdefine_line|#define VIC2_IRQSTATUS&t;__REG(VIC2_PHYS + 0x00)
DECL|macro|VIC2_FIQSTATUS
mdefine_line|#define VIC2_FIQSTATUS&t;__REG(VIC2_PHYS + 0x04)
DECL|macro|VIC2_RAWINTR
mdefine_line|#define VIC2_RAWINTR&t;__REG(VIC2_PHYS + 0x08)
DECL|macro|VIC2_INTSEL
mdefine_line|#define VIC2_INTSEL&t;__REG(VIC2_PHYS + 0x0c)
DECL|macro|VIC2_INTEN
mdefine_line|#define VIC2_INTEN&t;__REG(VIC2_PHYS + 0x10)
DECL|macro|VIC2_INTENCLR
mdefine_line|#define VIC2_INTENCLR&t;__REG(VIC2_PHYS + 0x14)
DECL|macro|VIC2_SOFTINT
mdefine_line|#define VIC2_SOFTINT&t;__REG(VIC2_PHYS + 0x18)
DECL|macro|VIC2_SOFTINTCLR
mdefine_line|#define VIC2_SOFTINTCLR&t;__REG(VIC2_PHYS + 0x1c)
DECL|macro|VIC2_PROTECT
mdefine_line|#define VIC2_PROTECT&t;__REG(VIC2_PHYS + 0x20)
DECL|macro|VIC2_VECTADDR
mdefine_line|#define VIC2_VECTADDR&t;__REG(VIC2_PHYS + 0x30)
DECL|macro|VIC2_NVADDR
mdefine_line|#define VIC2_NVADDR&t;__REG(VIC2_PHYS + 0x34)
DECL|macro|VIC2_VAD0
mdefine_line|#define VIC2_VAD0&t;__REG(VIC2_PHYS + 0x100)
DECL|macro|VIC2_VECTCNTL0
mdefine_line|#define VIC2_VECTCNTL0&t;__REG(VIC2_PHYS + 0x200)
DECL|macro|VIC_CNTL_ENABLE
mdefine_line|#define VIC_CNTL_ENABLE&t;(0x20)
multiline_comment|/* USB Host registers (Open HCI compatible) */
DECL|macro|USBH_CMDSTATUS
mdefine_line|#define USBH_CMDSTATUS&t;__REG(USBH_PHYS + 0x08)
multiline_comment|/* GPIO registers */
DECL|macro|GPIO_INTTYPE1
mdefine_line|#define GPIO_INTTYPE1&t;__REG(GPIO_PHYS + 0x4c)&t;/* Interrupt Type 1 (Edge) */
DECL|macro|GPIO_INTTYPE2
mdefine_line|#define GPIO_INTTYPE2&t;__REG(GPIO_PHYS + 0x50)&t;/* Interrupt Type 2 */
DECL|macro|GPIO_GPIOFEOI
mdefine_line|#define GPIO_GPIOFEOI&t;__REG(GPIO_PHYS + 0x54)&t;/* GPIO End-of-Interrupt */
DECL|macro|GPIO_GPIOINTEN
mdefine_line|#define GPIO_GPIOINTEN&t;__REG(GPIO_PHYS + 0x58)&t;/* GPIO Interrupt Enable */
DECL|macro|GPIO_INTSTATUS
mdefine_line|#define GPIO_INTSTATUS&t;__REG(GPIO_PHYS + 0x5c)&t;/* GPIO Interrupt Status */
multiline_comment|/* Static Memory Controller registers */
DECL|macro|SMC_BCR0
mdefine_line|#define SMC_BCR0&t;__REG(SMC_PHYS + 0x00)&t;/* Bank 0 Configuration */
DECL|macro|SMC_BCR1
mdefine_line|#define SMC_BCR1&t;__REG(SMC_PHYS + 0x04)&t;/* Bank 1 Configuration */
DECL|macro|SMC_BCR2
mdefine_line|#define SMC_BCR2&t;__REG(SMC_PHYS + 0x08)&t;/* Bank 2 Configuration */
DECL|macro|SMC_BCR3
mdefine_line|#define SMC_BCR3&t;__REG(SMC_PHYS + 0x0C)&t;/* Bank 3 Configuration */
DECL|macro|SMC_BCR6
mdefine_line|#define SMC_BCR6&t;__REG(SMC_PHYS + 0x18)&t;/* Bank 6 Configuration */
DECL|macro|SMC_BCR7
mdefine_line|#define SMC_BCR7&t;__REG(SMC_PHYS + 0x1c)&t;/* Bank 7 Configuration */
macro_line|#ifdef CONFIG_MACH_KEV7A400
DECL|macro|CPLD_RD_OPT_DIP_SW
macro_line|# define CPLD_RD_OPT_DIP_SW&t;__REG16(CPLD_PHYS + 0x00) /* Read Option SW */
DECL|macro|CPLD_WR_IO_BRD_CTL
macro_line|# define CPLD_WR_IO_BRD_CTL&t;__REG16(CPLD_PHYS + 0x00) /* Write Control */
DECL|macro|CPLD_RD_PB_KEYS
macro_line|# define CPLD_RD_PB_KEYS&t;__REG16(CPLD_PHYS + 0x02) /* Read Btn Keys */
DECL|macro|CPLD_LATCHED_INTS
macro_line|# define CPLD_LATCHED_INTS&t;__REG16(CPLD_PHYS + 0x04) /* Read INTR stat. */
DECL|macro|CPLD_CL_INT
macro_line|# define CPLD_CL_INT&t;&t;__REG16(CPLD_PHYS + 0x04) /* Clear INTR stat */
DECL|macro|CPLD_BOOT_MMC_STATUS
macro_line|# define CPLD_BOOT_MMC_STATUS&t;__REG16(CPLD_PHYS + 0x06) /* R/O */
DECL|macro|CPLD_RD_KPD_ROW_SENSE
macro_line|# define CPLD_RD_KPD_ROW_SENSE&t;__REG16(CPLD_PHYS + 0x08)
DECL|macro|CPLD_WR_PB_INT_MASK
macro_line|# define CPLD_WR_PB_INT_MASK&t;__REG16(CPLD_PHYS + 0x08)
DECL|macro|CPLD_RD_BRD_DISP_SW
macro_line|# define CPLD_RD_BRD_DISP_SW&t;__REG16(CPLD_PHYS + 0x0a)
DECL|macro|CPLD_WR_EXT_INT_MASK
macro_line|# define CPLD_WR_EXT_INT_MASK&t;__REG16(CPLD_PHYS + 0x0a)
DECL|macro|CPLD_LCD_PWR_CNTL
macro_line|# define CPLD_LCD_PWR_CNTL&t;__REG16(CPLD_PHYS + 0x0c)
DECL|macro|CPLD_SEVEN_SEG
macro_line|# define CPLD_SEVEN_SEG&t;&t;__REG16(CPLD_PHYS + 0x0e) /* 7 seg. LED mask */
macro_line|#endif
macro_line|#if defined (CONFIG_MACH_LPD7A400) || defined (CONFIG_MACH_LPD7A404)
DECL|macro|CPLD_CONTROL
macro_line|# define CPLD_CONTROL&t;&t;__REG8(CPLD02_PHYS)
DECL|macro|CPLD_SPI_DATA
macro_line|# define CPLD_SPI_DATA&t;&t;__REG8(CPLD06_PHYS)
DECL|macro|CPLD_SPI_CONTROL
macro_line|# define CPLD_SPI_CONTROL&t;__REG8(CPLD08_PHYS)
DECL|macro|CPLD_SPI_EEPROM
macro_line|# define CPLD_SPI_EEPROM&t;__REG8(CPLD0A_PHYS)
DECL|macro|CPLD_INTERRUPTS
macro_line|# define CPLD_INTERRUPTS&t;__REG8(CPLD0C_PHYS) /* IRQ mask/status */
DECL|macro|CPLD_BOOT_MODE
macro_line|# define CPLD_BOOT_MODE&t;&t;__REG8(CPLD0E_PHYS)
DECL|macro|CPLD_FLASH
macro_line|# define CPLD_FLASH&t;&t;__REG8(CPLD10_PHYS)
DECL|macro|CPLD_POWER_MGMT
macro_line|# define CPLD_POWER_MGMT&t;__REG8(CPLD12_PHYS)
DECL|macro|CPLD_REVISION
macro_line|# define CPLD_REVISION&t;&t;__REG8(CPLD14_PHYS)
DECL|macro|CPLD_GPIO_EXT
macro_line|# define CPLD_GPIO_EXT&t;&t;__REG8(CPLD16_PHYS)
DECL|macro|CPLD_GPIO_DATA
macro_line|# define CPLD_GPIO_DATA&t;&t;__REG8(CPLD18_PHYS)
DECL|macro|CPLD_GPIO_DIR
macro_line|# define CPLD_GPIO_DIR&t;&t;__REG8(CPLD1A_PHYS)
macro_line|#endif
multiline_comment|/* Timer registers */
DECL|macro|TIMER_LOAD1
mdefine_line|#define TIMER_LOAD1&t;__REG(TIMER_PHYS + 0x00) /* Timer 1 initial value */
DECL|macro|TIMER_VALUE1
mdefine_line|#define TIMER_VALUE1&t;__REG(TIMER_PHYS + 0x04) /* Timer 1 current value */
DECL|macro|TIMER_CONTROL1
mdefine_line|#define TIMER_CONTROL1&t;__REG(TIMER_PHYS + 0x08) /* Timer 1 control word */
DECL|macro|TIMER_EOI1
mdefine_line|#define TIMER_EOI1&t;__REG(TIMER_PHYS + 0x0c) /* Timer 1 interrupt clear */
DECL|macro|TIMER_LOAD2
mdefine_line|#define TIMER_LOAD2&t;__REG(TIMER_PHYS + 0x20) /* Timer 2 initial value */
DECL|macro|TIMER_VALUE2
mdefine_line|#define TIMER_VALUE2&t;__REG(TIMER_PHYS + 0x24) /* Timer 2 current value */
DECL|macro|TIMER_CONTROL2
mdefine_line|#define TIMER_CONTROL2&t;__REG(TIMER_PHYS + 0x28) /* Timer 2 control word */
DECL|macro|TIMER_EOI2
mdefine_line|#define TIMER_EOI2&t;__REG(TIMER_PHYS + 0x2c) /* Timer 2 interrupt clear */
DECL|macro|TIMER_BUZZCON
mdefine_line|#define TIMER_BUZZCON&t;__REG(TIMER_PHYS + 0x40) /* Buzzer configuration */
DECL|macro|TIMER_LOAD3
mdefine_line|#define TIMER_LOAD3&t;__REG(TIMER_PHYS + 0x80) /* Timer 3 initial value */
DECL|macro|TIMER_VALUE3
mdefine_line|#define TIMER_VALUE3&t;__REG(TIMER_PHYS + 0x84) /* Timer 3 current value */
DECL|macro|TIMER_CONTROL3
mdefine_line|#define TIMER_CONTROL3&t;__REG(TIMER_PHYS + 0x88) /* Timer 3 control word */
DECL|macro|TIMER_EOI3
mdefine_line|#define TIMER_EOI3&t;__REG(TIMER_PHYS + 0x8c) /* Timer 3 interrupt clear */
DECL|macro|TIMER_C_ENABLE
mdefine_line|#define TIMER_C_ENABLE&t;&t;(1&lt;&lt;7)
DECL|macro|TIMER_C_PERIODIC
mdefine_line|#define TIMER_C_PERIODIC&t;(1&lt;&lt;6)
DECL|macro|TIMER_C_FREERUNNING
mdefine_line|#define TIMER_C_FREERUNNING&t;(0)
DECL|macro|TIMER_C_2KHZ
mdefine_line|#define TIMER_C_2KHZ&t;&t;(0x00)&t;&t;/* 1.986 kHz */
DECL|macro|TIMER_C_508KHZ
mdefine_line|#define TIMER_C_508KHZ&t;&t;(0x08)
multiline_comment|/* GPIO registers */
DECL|macro|GPIO_PFDD
mdefine_line|#define GPIO_PFDD&t;&t;__REG(GPIO_PHYS + 0x34)&t;/* PF direction */
DECL|macro|GPIO_INTTYPE1
mdefine_line|#define GPIO_INTTYPE1&t;&t;__REG(GPIO_PHYS + 0x4c)&t;/* IRQ edge or lvl  */
DECL|macro|GPIO_INTTYPE2
mdefine_line|#define GPIO_INTTYPE2&t;&t;__REG(GPIO_PHYS + 0x50)&t;/* IRQ activ hi/lo */
DECL|macro|GPIO_GPIOFEOI
mdefine_line|#define GPIO_GPIOFEOI&t;&t;__REG(GPIO_PHYS + 0x54)&t;/* GPIOF end of IRQ */
DECL|macro|GPIO_GPIOFINTEN
mdefine_line|#define GPIO_GPIOFINTEN&t;&t;__REG(GPIO_PHYS + 0x58)&t;/* GPIOF IRQ enable */
DECL|macro|GPIO_INTSTATUS
mdefine_line|#define GPIO_INTSTATUS&t;&t;__REG(GPIO_PHYS + 0x5c)&t;/* GPIOF IRQ latch */
DECL|macro|GPIO_RAWINTSTATUS
mdefine_line|#define GPIO_RAWINTSTATUS&t;__REG(GPIO_PHYS + 0x60)&t;/* GPIOF IRQ raw */
macro_line|#endif  /* _ASM_ARCH_REGISTERS_H */
eof
