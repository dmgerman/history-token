multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/idp.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Copyright (c) 2001 Cliff Brake, Accelent Systems Inc.&n; *&n; * 2001-09-13: Cliff Brake &lt;cbrake@accelent.com&gt;&n; *             Initial code&n; *&n; * 2005-02-15: Cliff Brake &lt;cliff.brake@gmail.com&gt;&n; *             &lt;http://www.vibren.com&gt; &lt;http://bec-systems.com&gt;&n; *             Changes for 2.6 kernel.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Note: this file must be safe to include in assembly files&n; *&n; * Support for the Vibren PXA255 IDP requires rev04 or later&n; * IDP hardware.&n; */
DECL|macro|IDP_FLASH_PHYS
mdefine_line|#define IDP_FLASH_PHYS&t;&t;(PXA_CS0_PHYS)
DECL|macro|IDP_ALT_FLASH_PHYS
mdefine_line|#define IDP_ALT_FLASH_PHYS&t;(PXA_CS1_PHYS)
DECL|macro|IDP_MEDIAQ_PHYS
mdefine_line|#define IDP_MEDIAQ_PHYS&t;&t;(PXA_CS3_PHYS)
DECL|macro|IDP_IDE_PHYS
mdefine_line|#define IDP_IDE_PHYS&t;&t;(PXA_CS5_PHYS + 0x03000000)
DECL|macro|IDP_ETH_PHYS
mdefine_line|#define IDP_ETH_PHYS&t;&t;(PXA_CS5_PHYS + 0x03400000)
DECL|macro|IDP_COREVOLT_PHYS
mdefine_line|#define IDP_COREVOLT_PHYS&t;(PXA_CS5_PHYS + 0x03800000)
DECL|macro|IDP_CPLD_PHYS
mdefine_line|#define IDP_CPLD_PHYS&t;&t;(PXA_CS5_PHYS + 0x03C00000)
multiline_comment|/*&n; * virtual memory map&n; */
DECL|macro|IDP_COREVOLT_VIRT
mdefine_line|#define IDP_COREVOLT_VIRT&t;(0xf0000000)
DECL|macro|IDP_COREVOLT_SIZE
mdefine_line|#define IDP_COREVOLT_SIZE&t;(1*1024*1024)
DECL|macro|IDP_CPLD_VIRT
mdefine_line|#define IDP_CPLD_VIRT&t;&t;(IDP_COREVOLT_VIRT + IDP_COREVOLT_SIZE)
DECL|macro|IDP_CPLD_SIZE
mdefine_line|#define IDP_CPLD_SIZE&t;&t;(1*1024*1024)
macro_line|#if (IDP_CPLD_VIRT + IDP_CPLD_SIZE) &gt; 0xfc000000
macro_line|#error Your custom IO space is getting a bit large !!
macro_line|#endif
DECL|macro|CPLD_P2V
mdefine_line|#define CPLD_P2V(x)&t;&t;((x) - IDP_CPLD_PHYS + IDP_CPLD_VIRT)
DECL|macro|CPLD_V2P
mdefine_line|#define CPLD_V2P(x)&t;&t;((x) - IDP_CPLD_VIRT + IDP_CPLD_PHYS)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__CPLD_REG
macro_line|#  define __CPLD_REG(x)&t;&t;(*((volatile unsigned long *)CPLD_P2V(x)))
macro_line|#else
DECL|macro|__CPLD_REG
macro_line|#  define __CPLD_REG(x)&t;&t;CPLD_P2V(x)
macro_line|#endif
multiline_comment|/* board level registers in the CPLD: (offsets from CPLD_VIRT) */
DECL|macro|_IDP_CPLD_REV
mdefine_line|#define _IDP_CPLD_REV&t;&t;&t;(IDP_CPLD_PHYS + 0x00)
DECL|macro|_IDP_CPLD_PERIPH_PWR
mdefine_line|#define _IDP_CPLD_PERIPH_PWR&t;&t;(IDP_CPLD_PHYS + 0x04)
DECL|macro|_IDP_CPLD_LED_CONTROL
mdefine_line|#define _IDP_CPLD_LED_CONTROL&t;&t;(IDP_CPLD_PHYS + 0x08)
DECL|macro|_IDP_CPLD_KB_COL_HIGH
mdefine_line|#define _IDP_CPLD_KB_COL_HIGH&t;&t;(IDP_CPLD_PHYS + 0x0C)
DECL|macro|_IDP_CPLD_KB_COL_LOW
mdefine_line|#define _IDP_CPLD_KB_COL_LOW&t;&t;(IDP_CPLD_PHYS + 0x10)
DECL|macro|_IDP_CPLD_PCCARD_EN
mdefine_line|#define _IDP_CPLD_PCCARD_EN&t;&t;(IDP_CPLD_PHYS + 0x14)
DECL|macro|_IDP_CPLD_GPIOH_DIR
mdefine_line|#define _IDP_CPLD_GPIOH_DIR&t;&t;(IDP_CPLD_PHYS + 0x18)
DECL|macro|_IDP_CPLD_GPIOH_VALUE
mdefine_line|#define _IDP_CPLD_GPIOH_VALUE&t;&t;(IDP_CPLD_PHYS + 0x1C)
DECL|macro|_IDP_CPLD_GPIOL_DIR
mdefine_line|#define _IDP_CPLD_GPIOL_DIR&t;&t;(IDP_CPLD_PHYS + 0x20)
DECL|macro|_IDP_CPLD_GPIOL_VALUE
mdefine_line|#define _IDP_CPLD_GPIOL_VALUE&t;&t;(IDP_CPLD_PHYS + 0x24)
DECL|macro|_IDP_CPLD_PCCARD_PWR
mdefine_line|#define _IDP_CPLD_PCCARD_PWR&t;&t;(IDP_CPLD_PHYS + 0x28)
DECL|macro|_IDP_CPLD_MISC_CTRL
mdefine_line|#define _IDP_CPLD_MISC_CTRL&t;&t;(IDP_CPLD_PHYS + 0x2C)
DECL|macro|_IDP_CPLD_LCD
mdefine_line|#define _IDP_CPLD_LCD&t;&t;&t;(IDP_CPLD_PHYS + 0x30)
DECL|macro|_IDP_CPLD_FLASH_WE
mdefine_line|#define _IDP_CPLD_FLASH_WE&t;&t;(IDP_CPLD_PHYS + 0x34)
DECL|macro|_IDP_CPLD_KB_ROW
mdefine_line|#define _IDP_CPLD_KB_ROW&t;&t;(IDP_CPLD_PHYS + 0x50)
DECL|macro|_IDP_CPLD_PCCARD0_STATUS
mdefine_line|#define _IDP_CPLD_PCCARD0_STATUS&t;(IDP_CPLD_PHYS + 0x54)
DECL|macro|_IDP_CPLD_PCCARD1_STATUS
mdefine_line|#define _IDP_CPLD_PCCARD1_STATUS&t;(IDP_CPLD_PHYS + 0x58)
DECL|macro|_IDP_CPLD_MISC_STATUS
mdefine_line|#define _IDP_CPLD_MISC_STATUS&t;&t;(IDP_CPLD_PHYS + 0x5C)
multiline_comment|/* FPGA register virtual addresses */
DECL|macro|IDP_CPLD_REV
mdefine_line|#define IDP_CPLD_REV&t;&t;&t;__CPLD_REG(_IDP_CPLD_REV)
DECL|macro|IDP_CPLD_PERIPH_PWR
mdefine_line|#define IDP_CPLD_PERIPH_PWR&t;&t;__CPLD_REG(_IDP_CPLD_PERIPH_PWR)
DECL|macro|IDP_CPLD_LED_CONTROL
mdefine_line|#define IDP_CPLD_LED_CONTROL&t;&t;__CPLD_REG(_IDP_CPLD_LED_CONTROL)
DECL|macro|IDP_CPLD_KB_COL_HIGH
mdefine_line|#define IDP_CPLD_KB_COL_HIGH&t;&t;__CPLD_REG(_IDP_CPLD_KB_COL_HIGH)
DECL|macro|IDP_CPLD_KB_COL_LOW
mdefine_line|#define IDP_CPLD_KB_COL_LOW&t;&t;__CPLD_REG(_IDP_CPLD_KB_COL_LOW)
DECL|macro|IDP_CPLD_PCCARD_EN
mdefine_line|#define IDP_CPLD_PCCARD_EN&t;&t;__CPLD_REG(_IDP_CPLD_PCCARD_EN)
DECL|macro|IDP_CPLD_GPIOH_DIR
mdefine_line|#define IDP_CPLD_GPIOH_DIR&t;&t;__CPLD_REG(_IDP_CPLD_GPIOH_DIR)
DECL|macro|IDP_CPLD_GPIOH_VALUE
mdefine_line|#define IDP_CPLD_GPIOH_VALUE&t;&t;__CPLD_REG(_IDP_CPLD_GPIOH_VALUE)
DECL|macro|IDP_CPLD_GPIOL_DIR
mdefine_line|#define IDP_CPLD_GPIOL_DIR&t;&t;__CPLD_REG(_IDP_CPLD_GPIOL_DIR)
DECL|macro|IDP_CPLD_GPIOL_VALUE
mdefine_line|#define IDP_CPLD_GPIOL_VALUE&t;&t;__CPLD_REG(_IDP_CPLD_GPIOL_VALUE)
DECL|macro|IDP_CPLD_PCCARD_PWR
mdefine_line|#define IDP_CPLD_PCCARD_PWR&t;&t;__CPLD_REG(_IDP_CPLD_PCCARD_PWR)
DECL|macro|IDP_CPLD_MISC_CTRL
mdefine_line|#define IDP_CPLD_MISC_CTRL&t;&t;__CPLD_REG(_IDP_CPLD_MISC_CTRL)
DECL|macro|IDP_CPLD_LCD
mdefine_line|#define IDP_CPLD_LCD&t;&t;&t;__CPLD_REG(_IDP_CPLD_LCD)
DECL|macro|IDP_CPLD_FLASH_WE
mdefine_line|#define IDP_CPLD_FLASH_WE&t;&t;__CPLD_REG(_IDP_CPLD_FLASH_WE)
DECL|macro|IDP_CPLD_KB_ROW
mdefine_line|#define IDP_CPLD_KB_ROW&t;&t;        __CPLD_REG(_IDP_CPLD_KB_ROW)
DECL|macro|IDP_CPLD_PCCARD0_STATUS
mdefine_line|#define IDP_CPLD_PCCARD0_STATUS&t;        __CPLD_REG(_IDP_CPLD_PCCARD0_STATUS)
DECL|macro|IDP_CPLD_PCCARD1_STATUS
mdefine_line|#define IDP_CPLD_PCCARD1_STATUS&t;        __CPLD_REG(_IDP_CPLD_PCCARD1_STATUS)
DECL|macro|IDP_CPLD_MISC_STATUS
mdefine_line|#define IDP_CPLD_MISC_STATUS&t;&t;__CPLD_REG(_IDP_CPLD_MISC_STATUS)
multiline_comment|/*&n; * Bit masks for various registers&n; */
singleline_comment|// IDP_CPLD_PCCARD_PWR
DECL|macro|PCC0_PWR0
mdefine_line|#define PCC0_PWR0&t;(1 &lt;&lt; 0)
DECL|macro|PCC0_PWR1
mdefine_line|#define PCC0_PWR1&t;(1 &lt;&lt; 1)
DECL|macro|PCC0_PWR2
mdefine_line|#define PCC0_PWR2&t;(1 &lt;&lt; 2)
DECL|macro|PCC0_PWR3
mdefine_line|#define PCC0_PWR3&t;(1 &lt;&lt; 3)
DECL|macro|PCC1_PWR0
mdefine_line|#define PCC1_PWR0&t;(1 &lt;&lt; 4)
DECL|macro|PCC1_PWR1
mdefine_line|#define PCC1_PWR1&t;(1 &lt;&lt; 5)
DECL|macro|PCC1_PWR2
mdefine_line|#define PCC1_PWR2&t;(1 &lt;&lt; 6)
DECL|macro|PCC1_PWR3
mdefine_line|#define PCC1_PWR3&t;(1 &lt;&lt; 7)
singleline_comment|// IDP_CPLD_PCCARD_EN
DECL|macro|PCC0_RESET
mdefine_line|#define PCC0_RESET&t;(1 &lt;&lt; 6)
DECL|macro|PCC1_RESET
mdefine_line|#define PCC1_RESET&t;(1 &lt;&lt; 7)
DECL|macro|PCC0_ENABLE
mdefine_line|#define PCC0_ENABLE&t;(1 &lt;&lt; 0)
DECL|macro|PCC1_ENABLE
mdefine_line|#define PCC1_ENABLE&t;(1 &lt;&lt; 1)
singleline_comment|// IDP_CPLD_PCCARDx_STATUS
DECL|macro|_PCC_WRPROT
mdefine_line|#define _PCC_WRPROT&t;(1 &lt;&lt; 7) 
singleline_comment|// 7-4 read as low true
DECL|macro|_PCC_RESET
mdefine_line|#define _PCC_RESET&t;(1 &lt;&lt; 6)
DECL|macro|_PCC_IRQ
mdefine_line|#define _PCC_IRQ&t;(1 &lt;&lt; 5)
DECL|macro|_PCC_INPACK
mdefine_line|#define _PCC_INPACK&t;(1 &lt;&lt; 4)
DECL|macro|PCC_BVD2
mdefine_line|#define PCC_BVD2&t;(1 &lt;&lt; 3)
DECL|macro|PCC_BVD1
mdefine_line|#define PCC_BVD1&t;(1 &lt;&lt; 2)
DECL|macro|PCC_VS2
mdefine_line|#define PCC_VS2&t;&t;(1 &lt;&lt; 1)
DECL|macro|PCC_VS1
mdefine_line|#define PCC_VS1&t;&t;(1 &lt;&lt; 0)
DECL|macro|PCC_DETECT
mdefine_line|#define PCC_DETECT(x)&t;(GPLR(7 + (x)) &amp; GPIO_bit(7 + (x)))
multiline_comment|/* A listing of interrupts used by external hardware devices */
DECL|macro|TOUCH_PANEL_IRQ
mdefine_line|#define TOUCH_PANEL_IRQ&t;&t;&t;IRQ_GPIO(5)
DECL|macro|IDE_IRQ
mdefine_line|#define IDE_IRQ&t;&t;&t;&t;IRQ_GPIO(21)
DECL|macro|TOUCH_PANEL_IRQ_EDGE
mdefine_line|#define TOUCH_PANEL_IRQ_EDGE&t;&t;IRQT_FALLING
DECL|macro|ETHERNET_IRQ
mdefine_line|#define ETHERNET_IRQ&t;&t;&t;IRQ_GPIO(4)
DECL|macro|ETHERNET_IRQ_EDGE
mdefine_line|#define ETHERNET_IRQ_EDGE&t;&t;IRQT_RISING
DECL|macro|IDE_IRQ_EDGE
mdefine_line|#define IDE_IRQ_EDGE&t;&t;&t;IRQT_RISING
DECL|macro|PCMCIA_S0_CD_VALID
mdefine_line|#define PCMCIA_S0_CD_VALID&t;&t;IRQ_GPIO(7)
DECL|macro|PCMCIA_S0_CD_VALID_EDGE
mdefine_line|#define PCMCIA_S0_CD_VALID_EDGE&t;&t;IRQT_BOTHEDGE
DECL|macro|PCMCIA_S1_CD_VALID
mdefine_line|#define PCMCIA_S1_CD_VALID&t;&t;IRQ_GPIO(8)
DECL|macro|PCMCIA_S1_CD_VALID_EDGE
mdefine_line|#define PCMCIA_S1_CD_VALID_EDGE&t;&t;IRQT_BOTHEDGE
DECL|macro|PCMCIA_S0_RDYINT
mdefine_line|#define PCMCIA_S0_RDYINT&t;&t;IRQ_GPIO(19)
DECL|macro|PCMCIA_S1_RDYINT
mdefine_line|#define PCMCIA_S1_RDYINT&t;&t;IRQ_GPIO(22)
multiline_comment|/*&n; * Macros for LED Driver&n; */
multiline_comment|/* leds 0 = ON */
DECL|macro|IDP_HB_LED
mdefine_line|#define IDP_HB_LED&t;(1&lt;&lt;5)
DECL|macro|IDP_BUSY_LED
mdefine_line|#define IDP_BUSY_LED&t;(1&lt;&lt;6)
DECL|macro|IDP_LEDS_MASK
mdefine_line|#define IDP_LEDS_MASK&t;(IDP_HB_LED | IDP_BUSY_LED)
DECL|macro|IDP_WRITE_LEDS
mdefine_line|#define IDP_WRITE_LEDS(value)&t;(IDP_CPLD_LED_CONTROL = (IDP_CPLD_LED_CONTROL &amp; ((~(IDP_LEDS_MASK)) | value)))
multiline_comment|/*&n; * macros for MTD driver&n; */
DECL|macro|FLASH_WRITE_PROTECT_DISABLE
mdefine_line|#define FLASH_WRITE_PROTECT_DISABLE()&t;((IDP_CPLD_FLASH_WE) &amp;= ~(0x1))
DECL|macro|FLASH_WRITE_PROTECT_ENABLE
mdefine_line|#define FLASH_WRITE_PROTECT_ENABLE()&t;((IDP_CPLD_FLASH_WE) |= (0x1))
multiline_comment|/*&n; * macros for matrix keyboard driver&n; */
DECL|macro|KEYBD_MATRIX_NUMBER_INPUTS
mdefine_line|#define KEYBD_MATRIX_NUMBER_INPUTS&t;7
DECL|macro|KEYBD_MATRIX_NUMBER_OUTPUTS
mdefine_line|#define KEYBD_MATRIX_NUMBER_OUTPUTS&t;14
DECL|macro|KEYBD_MATRIX_INVERT_OUTPUT_LOGIC
mdefine_line|#define KEYBD_MATRIX_INVERT_OUTPUT_LOGIC&t;FALSE
DECL|macro|KEYBD_MATRIX_INVERT_INPUT_LOGIC
mdefine_line|#define KEYBD_MATRIX_INVERT_INPUT_LOGIC&t;&t;FALSE
DECL|macro|KEYBD_MATRIX_SETTLING_TIME_US
mdefine_line|#define KEYBD_MATRIX_SETTLING_TIME_US&t;&t;&t;100
DECL|macro|KEYBD_MATRIX_KEYSTATE_DEBOUNCE_CONSTANT
mdefine_line|#define KEYBD_MATRIX_KEYSTATE_DEBOUNCE_CONSTANT&t;&t;2
DECL|macro|KEYBD_MATRIX_SET_OUTPUTS
mdefine_line|#define KEYBD_MATRIX_SET_OUTPUTS(outputs) &bslash;&n;{&bslash;&n;&t;IDP_CPLD_KB_COL_LOW = outputs;&bslash;&n;&t;IDP_CPLD_KB_COL_HIGH = outputs &gt;&gt; 7;&bslash;&n;}
DECL|macro|KEYBD_MATRIX_GET_INPUTS
mdefine_line|#define KEYBD_MATRIX_GET_INPUTS(inputs) &bslash;&n;{&bslash;&n;&t;inputs = (IDP_CPLD_KB_ROW &amp; 0x7f);&bslash;&n;}
eof
