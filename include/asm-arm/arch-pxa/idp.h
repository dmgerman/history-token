multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/idp.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Copyright (c) 2001 Cliff Brake, Accelent Systems Inc.&n; *&n; * 2001-09-13: Cliff Brake &lt;cbrake@accelent.com&gt;&n; *             Initial code&n; *&n; */
multiline_comment|/*&n; * Note: this file must be safe to include in assembly files&n; */
multiline_comment|/* comment out following if you have a rev01 board */
DECL|macro|PXA_IDP_REV02
mdefine_line|#define PXA_IDP_REV02&t;1
singleline_comment|//#undef PXA_IDP_REV02
macro_line|#ifdef PXA_IDP_REV02
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
DECL|macro|IDP_IDE_BASE
mdefine_line|#define IDP_IDE_BASE&t;&t;(0xf0000000)
DECL|macro|IDP_IDE_SIZE
mdefine_line|#define IDP_IDE_SIZE&t;&t;(1*1024*1024)
DECL|macro|IDP_ETH_BASE
mdefine_line|#define IDP_ETH_BASE&t;&t;(IDP_IDE_BASE + IDP_IDE_SIZE)
DECL|macro|IDP_ETH_SIZE
mdefine_line|#define IDP_ETH_SIZE&t;&t;(1*1024*1024)
DECL|macro|ETH_BASE
mdefine_line|#define ETH_BASE&t;&t;IDP_ETH_BASE 
singleline_comment|//smc9194 driver compatibility issue
DECL|macro|IDP_COREVOLT_BASE
mdefine_line|#define IDP_COREVOLT_BASE&t;(IDP_ETH_BASE + IDP_ETH_SIZE)
DECL|macro|IDP_COREVOLT_SIZE
mdefine_line|#define IDP_COREVOLT_SIZE&t;(1*1024*1024)
DECL|macro|IDP_CPLD_BASE
mdefine_line|#define IDP_CPLD_BASE&t;&t;(IDP_COREVOLT_BASE + IDP_COREVOLT_SIZE)
DECL|macro|IDP_CPLD_SIZE
mdefine_line|#define IDP_CPLD_SIZE&t;&t;(1*1024*1024)
macro_line|#if (IDP_CPLD_BASE + IDP_CPLD_SIZE) &gt; 0xfc000000
macro_line|#error Your custom IO space is getting a bit large !!
macro_line|#endif
DECL|macro|CPLD_P2V
mdefine_line|#define CPLD_P2V(x)&t;&t;((x) - IDP_CPLD_PHYS + IDP_CPLD_BASE)
DECL|macro|CPLD_V2P
mdefine_line|#define CPLD_V2P(x)&t;&t;((x) - IDP_CPLD_BASE + IDP_CPLD_PHYS)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__CPLD_REG
macro_line|#  define __CPLD_REG(x)&t;&t;(*((volatile unsigned long *)CPLD_P2V(x)))
macro_line|#else
DECL|macro|__CPLD_REG
macro_line|#  define __CPLD_REG(x)&t;&t;CPLD_P2V(x)
macro_line|#endif
multiline_comment|/* board level registers in the CPLD: (offsets from CPLD_BASE) */
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
multiline_comment|/*&n; * Macros for LCD Driver&n; */
macro_line|#ifdef CONFIG_FB_PXA
DECL|macro|FB_BACKLIGHT_ON
mdefine_line|#define FB_BACKLIGHT_ON()&t;(IDP_CPLD_LCD |= (1&lt;&lt;1))
DECL|macro|FB_BACKLIGHT_OFF
mdefine_line|#define FB_BACKLIGHT_OFF() &t;(IDP_CPLD_LCD &amp;= ~(1&lt;&lt;1))
DECL|macro|FB_PWR_ON
mdefine_line|#define FB_PWR_ON() &t;&t;(IDP_CPLD_LCD |= (1&lt;&lt; 0))
DECL|macro|FB_PWR_OFF
mdefine_line|#define FB_PWR_OFF() &t;&t;(IDP_CPLD_LCD &amp;= ~(1&lt;&lt;0))
DECL|macro|FB_VLCD_ON
mdefine_line|#define FB_VLCD_ON()&t;&t;(IDP_CPLD_LCD |= (1&lt;&lt;2))
DECL|macro|FB_VLCD_OFF
mdefine_line|#define FB_VLCD_OFF() &t;&t;(IDP_CPLD_LCD &amp;= ~(1&lt;&lt;2))
macro_line|#endif
multiline_comment|/*&n; * Macros for LED Driver&n; */
multiline_comment|/* leds 0 = ON */
DECL|macro|IDP_HB_LED
mdefine_line|#define IDP_HB_LED&t;(1&lt;&lt;5)
DECL|macro|IDP_BUSY_LED
mdefine_line|#define IDP_BUSY_LED&t;(1&lt;&lt;6)
DECL|macro|IDP_LEDS_MASK
mdefine_line|#define IDP_LEDS_MASK&t;(IDP_HB_LED | IDP_BUSY_LED)
DECL|macro|IDP_WRITE_LEDS
mdefine_line|#define IDP_WRITE_LEDS(value)&t;(IDP_CPLD_LED_CONTROL = (IDP_CPLD_LED_CONTROL &amp; (~(IDP_LEDS_MASK)) | value))
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
multiline_comment|/* A listing of interrupts used by external hardware devices */
DECL|macro|TOUCH_PANEL_IRQ
mdefine_line|#define TOUCH_PANEL_IRQ&t;&t;&t;IRQ_GPIO(21)
DECL|macro|TOUCH_PANEL_IRQ_EGDE
mdefine_line|#define TOUCH_PANEL_IRQ_EGDE&t;&t;GPIO_FALLING_EDGE
DECL|macro|ETHERNET_IRQ
mdefine_line|#define ETHERNET_IRQ&t;&t;&t;IRQ_GPIO(4)
DECL|macro|ETHERNET_IRQ_EDGE
mdefine_line|#define ETHERNET_IRQ_EDGE&t;&t;GPIO_RISING_EDGE
macro_line|#else
multiline_comment|/*&n; * following is for rev01 boards only&n; */
DECL|macro|IDP_FLASH_PHYS
mdefine_line|#define IDP_FLASH_PHYS&t;&t;(PXA_CS0_PHYS)
DECL|macro|IDP_ALT_FLASH_PHYS
mdefine_line|#define IDP_ALT_FLASH_PHYS&t;(PXA_CS1_PHYS)
DECL|macro|IDP_MEDIAQ_PHYS
mdefine_line|#define IDP_MEDIAQ_PHYS&t;&t;(PXA_CS3_PHYS)
DECL|macro|IDP_CTRL_PORT_PHYS
mdefine_line|#define IDP_CTRL_PORT_PHYS&t;(PXA_CS5_PHYS + 0x02C00000)
DECL|macro|IDP_IDE_PHYS
mdefine_line|#define IDP_IDE_PHYS&t;&t;(PXA_CS5_PHYS + 0x03000000)
DECL|macro|IDP_ETH_PHYS
mdefine_line|#define IDP_ETH_PHYS&t;&t;(PXA_CS5_PHYS + 0x03400000)
DECL|macro|IDP_COREVOLT_PHYS
mdefine_line|#define IDP_COREVOLT_PHYS&t;(PXA_CS5_PHYS + 0x03800000)
DECL|macro|IDP_CPLD_PHYS
mdefine_line|#define IDP_CPLD_PHYS&t;&t;(PXA_CS5_PHYS + 0x03C00000)
multiline_comment|/*&n; * virtual memory map&n; */
DECL|macro|IDP_CTRL_PORT_BASE
mdefine_line|#define IDP_CTRL_PORT_BASE&t;(0xf0000000)
DECL|macro|IDP_CTRL_PORT_SIZE
mdefine_line|#define IDP_CTRL_PORT_SIZE&t;(1*1024*1024)
DECL|macro|IDP_IDE_BASE
mdefine_line|#define IDP_IDE_BASE&t;&t;(IDP_CTRL_PORT_BASE + IDP_CTRL_PORT_SIZE)
DECL|macro|IDP_IDE_SIZE
mdefine_line|#define IDP_IDE_SIZE&t;&t;(1*1024*1024)
DECL|macro|IDP_ETH_BASE
mdefine_line|#define IDP_ETH_BASE&t;&t;(IDP_IDE_BASE + IDP_IDE_SIZE)
DECL|macro|IDP_ETH_SIZE
mdefine_line|#define IDP_ETH_SIZE&t;&t;(1*1024*1024)
DECL|macro|IDP_COREVOLT_BASE
mdefine_line|#define IDP_COREVOLT_BASE&t;(IDP_ETH_BASE + IDP_ETH_SIZE)
DECL|macro|IDP_COREVOLT_SIZE
mdefine_line|#define IDP_COREVOLT_SIZE&t;(1*1024*1024)
DECL|macro|IDP_CPLD_BASE
mdefine_line|#define IDP_CPLD_BASE&t;&t;(IDP_COREVOLT_BASE + IDP_COREVOLT_SIZE)
DECL|macro|IDP_CPLD_SIZE
mdefine_line|#define IDP_CPLD_SIZE&t;&t;(1*1024*1024)
macro_line|#if (IDP_CPLD_BASE + IDP_CPLD_SIZE) &gt; 0xfc000000
macro_line|#error Your custom IO space is getting a bit large !!
macro_line|#endif
DECL|macro|CPLD_P2V
mdefine_line|#define CPLD_P2V(x)&t;&t;((x) - IDP_CPLD_PHYS + IDP_CPLD_BASE)
DECL|macro|CPLD_V2P
mdefine_line|#define CPLD_V2P(x)&t;&t;((x) - IDP_CPLD_BASE + IDP_CPLD_PHYS)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__CPLD_REG
macro_line|#  define __CPLD_REG(x)&t;&t;(*((volatile unsigned long *)CPLD_P2V(x)))
macro_line|#else
DECL|macro|__CPLD_REG
macro_line|#  define __CPLD_REG(x)&t;&t;CPLD_P2V(x)
macro_line|#endif
multiline_comment|/* board level registers in the CPLD: (offsets from CPLD_BASE) */
DECL|macro|_IDP_CPLD_LED_CONTROL
mdefine_line|#define _IDP_CPLD_LED_CONTROL&t;&t;(IDP_CPLD_PHYS + 0x00)
DECL|macro|_IDP_CPLD_PERIPH_PWR
mdefine_line|#define _IDP_CPLD_PERIPH_PWR&t;&t;(IDP_CPLD_PHYS + 0x04)
DECL|macro|_IDP_CPLD_CIR
mdefine_line|#define _IDP_CPLD_CIR&t;&t;&t;(IDP_CPLD_PHYS + 0x08)
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
DECL|macro|_IDP_CPLD_MISC
mdefine_line|#define _IDP_CPLD_MISC&t;&t;&t;(IDP_CPLD_PHYS + 0x28)
DECL|macro|_IDP_CPLD_PCCARD0_STATUS
mdefine_line|#define _IDP_CPLD_PCCARD0_STATUS&t;(IDP_CPLD_PHYS + 0x2C)
DECL|macro|_IDP_CPLD_PCCARD1_STATUS
mdefine_line|#define _IDP_CPLD_PCCARD1_STATUS&t;(IDP_CPLD_PHYS + 0x30)
multiline_comment|/* FPGA register virtual addresses */
DECL|macro|IDP_CPLD_LED_CONTROL
mdefine_line|#define IDP_CPLD_LED_CONTROL&t;&t;__CPLD_REG(_IDP_CPLD_LED_CONTROL)&t;/* write only */
DECL|macro|IDP_CPLD_PERIPH_PWR
mdefine_line|#define IDP_CPLD_PERIPH_PWR&t;&t;__CPLD_REG(_IDP_CPLD_PERIPH_PWR)&t;/* write only */
DECL|macro|IDP_CPLD_CIR
mdefine_line|#define IDP_CPLD_CIR&t;&t;&t;__CPLD_REG(_IDP_CPLD_CIR)&t;&t;/* write only */
DECL|macro|IDP_CPLD_KB_COL_HIGH
mdefine_line|#define IDP_CPLD_KB_COL_HIGH&t;&t;__CPLD_REG(_IDP_CPLD_KB_COL_HIGH)&t;/* write only */
DECL|macro|IDP_CPLD_KB_COL_LOW
mdefine_line|#define IDP_CPLD_KB_COL_LOW&t;&t;__CPLD_REG(_IDP_CPLD_KB_COL_LOW)&t;/* write only */
DECL|macro|IDP_CPLD_PCCARD_EN
mdefine_line|#define IDP_CPLD_PCCARD_EN&t;&t;__CPLD_REG(_IDP_CPLD_PCCARD_EN)&t;&t;/* write only */
DECL|macro|IDP_CPLD_GPIOH_DIR
mdefine_line|#define IDP_CPLD_GPIOH_DIR&t;&t;__CPLD_REG(_IDP_CPLD_GPIOH_DIR)&t;&t;/* write only */
DECL|macro|IDP_CPLD_GPIOH_VALUE
mdefine_line|#define IDP_CPLD_GPIOH_VALUE&t;&t;__CPLD_REG(_IDP_CPLD_GPIOH_VALUE)&t;/* write only */
DECL|macro|IDP_CPLD_GPIOL_DIR
mdefine_line|#define IDP_CPLD_GPIOL_DIR&t;&t;__CPLD_REG(_IDP_CPLD_GPIOL_DIR)&t;&t;/* write only */
DECL|macro|IDP_CPLD_GPIOL_VALUE
mdefine_line|#define IDP_CPLD_GPIOL_VALUE&t;&t;__CPLD_REG(_IDP_CPLD_GPIOL_VALUE)&t;/* write only */
DECL|macro|IDP_CPLD_MISC
mdefine_line|#define IDP_CPLD_MISC&t;&t;&t;__CPLD_REG(_IDP_CPLD_MISC)&t;&t;/* read only */
DECL|macro|IDP_CPLD_PCCARD0_STATUS
mdefine_line|#define IDP_CPLD_PCCARD0_STATUS&t;&t;__CPLD_REG(_IDP_CPLD_PCCARD0_STATUS)&t;/* read only */
DECL|macro|IDP_CPLD_PCCARD1_STATUS
mdefine_line|#define IDP_CPLD_PCCARD1_STATUS&t;&t;__CPLD_REG(_IDP_CPLD_PCCARD1_STATUS)&t;/* read only */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* shadow registers for write only registers */
r_extern
r_int
r_int
id|idp_cpld_led_control_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_periph_pwr_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_cir_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_kb_col_high_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_kb_col_low_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_pccard_en_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_gpioh_dir_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_gpioh_value_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_gpiol_dir_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_cpld_gpiol_value_shadow
suffix:semicolon
r_extern
r_int
r_int
id|idp_control_port_shadow
suffix:semicolon
multiline_comment|/*&n; * macros to write to write only register&n; *&n; * none of these macros are protected from&n; * multiple drivers using them in interrupt context.&n; */
DECL|macro|WRITE_IDP_CPLD_LED_CONTROL
mdefine_line|#define WRITE_IDP_CPLD_LED_CONTROL(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_led_control_shadow = ((value &amp; mask) | (idp_cpld_led_control_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_LED_CONTROL = idp_cpld_led_control_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_PERIPH_PWR
mdefine_line|#define WRITE_IDP_CPLD_PERIPH_PWR(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_periph_pwr_shadow = ((value &amp; mask) | (idp_cpld_periph_pwr_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_PERIPH_PWR = idp_cpld_periph_pwr_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_CIR
mdefine_line|#define WRITE_IDP_CPLD_CIR(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_cir_shadow = ((value &amp; mask) | (idp_cpld_cir_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_CIR = idp_cpld_cir_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_KB_COL_HIGH
mdefine_line|#define WRITE_IDP_CPLD_KB_COL_HIGH(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_kb_col_high_shadow = ((value &amp; mask) | (idp_cpld_kb_col_high_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_KB_COL_HIGH = idp_cpld_kb_col_high_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_KB_COL_LOW
mdefine_line|#define WRITE_IDP_CPLD_KB_COL_LOW(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_kb_col_low_shadow = ((value &amp; mask) | (idp_cpld_kb_col_low_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_KB_COL_LOW = idp_cpld_kb_col_low_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_PCCARD_EN
mdefine_line|#define WRITE_IDP_CPLD_PCCARD_EN(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_ = ((value &amp; mask) | (idp_cpld_led_control_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_LED_CONTROL = idp_cpld_led_control_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_GPIOH_DIR
mdefine_line|#define WRITE_IDP_CPLD_GPIOH_DIR(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_gpioh_dir_shadow = ((value &amp; mask) | (idp_cpld_gpioh_dir_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_GPIOH_DIR = idp_cpld_gpioh_dir_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_GPIOH_VALUE
mdefine_line|#define WRITE_IDP_CPLD_GPIOH_VALUE(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_gpioh_value_shadow = ((value &amp; mask) | (idp_cpld_gpioh_value_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_GPIOH_VALUE = idp_cpld_gpioh_value_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_GPIOL_DIR
mdefine_line|#define WRITE_IDP_CPLD_GPIOL_DIR(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_gpiol_dir_shadow = ((value &amp; mask) | (idp_cpld_gpiol_dir_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_GPIOL_DIR = idp_cpld_gpiol_dir_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CPLD_GPIOL_VALUE
mdefine_line|#define WRITE_IDP_CPLD_GPIOL_VALUE(value, mask) &bslash;&n;{&bslash;&n;&t;idp_cpld_gpiol_value_shadow = ((value &amp; mask) | (idp_cpld_gpiol_value_shadow &amp; ~mask));&bslash;&n;&t;IDP_CPLD_GPIOL_VALUE = idp_cpld_gpiol_value_shadow;&bslash;&n;}
DECL|macro|WRITE_IDP_CONTROL_PORT
mdefine_line|#define WRITE_IDP_CONTROL_PORT(value, mask) &bslash;&n;{&bslash;&n;&t;idp_control_port_shadow = ((value &amp; mask) | (idp_control_port_shadow &amp; ~mask));&bslash;&n;&t;(*((volatile unsigned long *)IDP_CTRL_PORT_BASE)) = idp_control_port_shadow;&bslash;&n;}
macro_line|#endif
multiline_comment|/* A listing of interrupts used by external hardware devices */
DECL|macro|TOUCH_PANEL_IRQ
mdefine_line|#define TOUCH_PANEL_IRQ&t;&t;&t;IRQ_GPIO(21)
DECL|macro|TOUCH_PANEL_IRQ_EGDE
mdefine_line|#define TOUCH_PANEL_IRQ_EGDE&t;&t;GPIO_FALLING_EDGE
DECL|macro|ETHERNET_IRQ
mdefine_line|#define ETHERNET_IRQ&t;&t;&t;IRQ_GPIO(4)
DECL|macro|ETHERNET_IRQ_EDGE
mdefine_line|#define ETHERNET_IRQ_EDGE&t;&t;GPIO_RISING_EDGE
multiline_comment|/*&n; * Bit masks for various registers&n; */
multiline_comment|/* control port */
DECL|macro|IDP_CONTROL_PORT_PCSLOT0_0
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT0_0&t;(1 &lt;&lt; 0)
DECL|macro|IDP_CONTROL_PORT_PCSLOT0_1
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT0_1&t;(1 &lt;&lt; 1)
DECL|macro|IDP_CONTROL_PORT_PCSLOT0_2
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT0_2&t;(1 &lt;&lt; 2)
DECL|macro|IDP_CONTROL_PORT_PCSLOT0_3
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT0_3&t;(1 &lt;&lt; 3)
DECL|macro|IDP_CONTROL_PORT_PCSLOT1_1
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT1_1&t;(1 &lt;&lt; 4)
DECL|macro|IDP_CONTROL_PORT_PCSLOT1_2
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT1_2&t;(1 &lt;&lt; 5)
DECL|macro|IDP_CONTROL_PORT_PCSLOT1_3
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT1_3&t;(1 &lt;&lt; 6)
DECL|macro|IDP_CONTROL_PORT_PCSLOT1_4
mdefine_line|#define IDP_CONTROL_PORT_PCSLOT1_4&t;(1 &lt;&lt; 7)
DECL|macro|IDP_CONTROL_PORT_SERIAL1_EN
mdefine_line|#define IDP_CONTROL_PORT_SERIAL1_EN&t;(1 &lt;&lt; 9)
DECL|macro|IDP_CONTROL_PORT_SERIAL2_EN
mdefine_line|#define IDP_CONTROL_PORT_SERIAL2_EN&t;(1 &lt;&lt; 10)
DECL|macro|IDP_CONTROL_PORT_SERIAL3_EN
mdefine_line|#define IDP_CONTROL_PORT_SERIAL3_EN&t;(1 &lt;&lt; 11)
DECL|macro|IDP_CONTROL_PORT_IRDA_FIR
mdefine_line|#define IDP_CONTROL_PORT_IRDA_FIR&t;(1 &lt;&lt; 12)
DECL|macro|IDP_CONTROL_PORT_IRDA_M0
mdefine_line|#define IDP_CONTROL_PORT_IRDA_M0&t;(1 &lt;&lt; 13)
DECL|macro|IDP_CONTROL_PORT_IRDA_M1
mdefine_line|#define IDP_CONTROL_PORT_IRDA_M1&t;(1 &lt;&lt; 14)
DECL|macro|IDP_CONTROL_PORT_I2S_PWR
mdefine_line|#define IDP_CONTROL_PORT_I2S_PWR&t;(1 &lt;&lt; 15)
DECL|macro|IDP_CONTROL_PORT_FLASH_WP
mdefine_line|#define IDP_CONTROL_PORT_FLASH_WP&t;(1 &lt;&lt; 19)
DECL|macro|IDP_CONTROL_PORT_MILL_EN
mdefine_line|#define IDP_CONTROL_PORT_MILL_EN&t;(1 &lt;&lt; 20)
DECL|macro|IDP_CONTROL_PORT_LCD_PWR
mdefine_line|#define IDP_CONTROL_PORT_LCD_PWR&t;(1 &lt;&lt; 21)
DECL|macro|IDP_CONTROL_PORT_LCD_BKLEN
mdefine_line|#define IDP_CONTROL_PORT_LCD_BKLEN&t;(1 &lt;&lt; 22)
DECL|macro|IDP_CONTROL_PORT_LCD_ENAVLCD
mdefine_line|#define IDP_CONTROL_PORT_LCD_ENAVLCD&t;(1 &lt;&lt; 23)
multiline_comment|/*&n; * Macros for LCD Driver&n; */
macro_line|#ifdef CONFIG_FB_PXA
DECL|macro|FB_BACKLIGHT_ON
mdefine_line|#define FB_BACKLIGHT_ON() WRITE_IDP_CONTROL_PORT(IDP_CONTROL_PORT_LCD_BKLEN, IDP_CONTROL_PORT_LCD_BKLEN)
DECL|macro|FB_BACKLIGHT_OFF
mdefine_line|#define FB_BACKLIGHT_OFF() WRITE_IDP_CONTROL_PORT(0, IDP_CONTROL_PORT_LCD_BKLEN)
DECL|macro|FB_PWR_ON
mdefine_line|#define FB_PWR_ON() WRITE_IDP_CONTROL_PORT(IDP_CONTROL_PORT_LCD_PWR, IDP_CONTROL_PORT_LCD_PWR)
DECL|macro|FB_PWR_OFF
mdefine_line|#define FB_PWR_OFF() WRITE_IDP_CONTROL_PORT(0, IDP_CONTROL_PORT_LCD_PWR)
DECL|macro|FB_VLCD_ON
mdefine_line|#define FB_VLCD_ON() WRITE_IDP_CONTROL_PORT(IDP_CONTROL_PORT_LCD_ENAVLCD, IDP_CONTROL_PORT_LCD_ENAVLCD)
DECL|macro|FB_VLCD_OFF
mdefine_line|#define FB_VLCD_OFF() WRITE_IDP_CONTROL_PORT(0, IDP_CONTROL_PORT_LCD_ENAVLCD)
macro_line|#endif
multiline_comment|/*&n; * Macros for LED Driver&n; */
multiline_comment|/* leds 0 = ON */
DECL|macro|IDP_HB_LED
mdefine_line|#define IDP_HB_LED&t;0x1
DECL|macro|IDP_BUSY_LED
mdefine_line|#define IDP_BUSY_LED&t;0x2
DECL|macro|IDP_LEDS_MASK
mdefine_line|#define IDP_LEDS_MASK&t;(IDP_HB_LED | IDP_BUSY_LED)
DECL|macro|IDP_WRITE_LEDS
mdefine_line|#define IDP_WRITE_LEDS(value) &t;WRITE_IDP_CPLD_LED_CONTROL(value, IDP_LEDS_MASK)
multiline_comment|/*&n; * macros for MTD driver&n; */
DECL|macro|FLASH_WRITE_PROTECT_DISABLE
mdefine_line|#define FLASH_WRITE_PROTECT_DISABLE()&t;WRITE_IDP_CONTROL_PORT(0, IDP_CONTROL_PORT_FLASH_WP)
DECL|macro|FLASH_WRITE_PROTECT_ENABLE
mdefine_line|#define FLASH_WRITE_PROTECT_ENABLE()&t;WRITE_IDP_CONTROL_PORT(IDP_CONTROL_PORT_FLASH_WP, IDP_CONTROL_PORT_FLASH_WP)
macro_line|#endif
eof
