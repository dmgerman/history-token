multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/assabet.h&n; *&n; * Created 2000/06/05 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware specific definitions for Assabet&n; * Only include this file from SA1100-specific files.&n; *&n; * 2000/05/23 John Dorsey &lt;john+@cs.cmu.edu&gt;&n; *      Definitions for Neponset added.&n; */
macro_line|#ifndef __ASM_ARCH_ASSABET_H
DECL|macro|__ASM_ARCH_ASSABET_H
mdefine_line|#define __ASM_ARCH_ASSABET_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* System Configuration Register flags */
DECL|macro|ASSABET_SCR_SDRAM_LOW
mdefine_line|#define ASSABET_SCR_SDRAM_LOW&t;(1&lt;&lt;2)&t;/* SDRAM size (low bit) */
DECL|macro|ASSABET_SCR_SDRAM_HIGH
mdefine_line|#define ASSABET_SCR_SDRAM_HIGH&t;(1&lt;&lt;3)&t;/* SDRAM size (high bit) */
DECL|macro|ASSABET_SCR_FLASH_LOW
mdefine_line|#define ASSABET_SCR_FLASH_LOW&t;(1&lt;&lt;4)&t;/* Flash size (low bit) */
DECL|macro|ASSABET_SCR_FLASH_HIGH
mdefine_line|#define ASSABET_SCR_FLASH_HIGH&t;(1&lt;&lt;5)&t;/* Flash size (high bit) */
DECL|macro|ASSABET_SCR_GFX
mdefine_line|#define ASSABET_SCR_GFX&t;&t;(1&lt;&lt;8)&t;/* Graphics Accelerator (0 = present) */
DECL|macro|ASSABET_SCR_SA1111
mdefine_line|#define ASSABET_SCR_SA1111&t;(1&lt;&lt;9)&t;/* Neponset (0 = present) */
DECL|macro|ASSABET_SCR_INIT
mdefine_line|#define ASSABET_SCR_INIT&t;-1
r_extern
r_int
r_int
id|SCR_value
suffix:semicolon
macro_line|#ifdef CONFIG_ASSABET_NEPONSET
DECL|macro|machine_has_neponset
mdefine_line|#define machine_has_neponset()  ((SCR_value &amp; ASSABET_SCR_SA1111) == 0)
macro_line|#else
DECL|macro|machine_has_neponset
mdefine_line|#define machine_has_neponset()&t;(0)
macro_line|#endif
multiline_comment|/* Board Control Register */
DECL|macro|ASSABET_BCR_BASE
mdefine_line|#define ASSABET_BCR_BASE  0xf1000000
DECL|macro|ASSABET_BCR
mdefine_line|#define ASSABET_BCR (*(volatile unsigned int *)(ASSABET_BCR_BASE))
DECL|macro|ASSABET_BCR_CF_PWR
mdefine_line|#define ASSABET_BCR_CF_PWR&t;(1&lt;&lt;0)&t;/* Compact Flash Power (1 = 3.3v, 0 = off) */
DECL|macro|ASSABET_BCR_CF_RST
mdefine_line|#define ASSABET_BCR_CF_RST&t;(1&lt;&lt;1)&t;/* Compact Flash Reset (1 = power up reset) */
DECL|macro|ASSABET_BCR_GFX_RST
mdefine_line|#define ASSABET_BCR_GFX_RST&t;(1&lt;&lt;1)&t;/* Graphics Accelerator Reset (0 = hold reset) */
DECL|macro|ASSABET_BCR_CODEC_RST
mdefine_line|#define ASSABET_BCR_CODEC_RST&t;(1&lt;&lt;2)&t;/* 0 = Holds UCB1300, ADI7171, and UDA1341 in reset */
DECL|macro|ASSABET_BCR_IRDA_FSEL
mdefine_line|#define ASSABET_BCR_IRDA_FSEL&t;(1&lt;&lt;3)&t;/* IRDA Frequency select (0 = SIR, 1 = MIR/ FIR) */
DECL|macro|ASSABET_BCR_IRDA_MD0
mdefine_line|#define ASSABET_BCR_IRDA_MD0&t;(1&lt;&lt;4)&t;/* Range/Power select */
DECL|macro|ASSABET_BCR_IRDA_MD1
mdefine_line|#define ASSABET_BCR_IRDA_MD1&t;(1&lt;&lt;5)&t;/* Range/Power select */
DECL|macro|ASSABET_BCR_STEREO_LB
mdefine_line|#define ASSABET_BCR_STEREO_LB&t;(1&lt;&lt;6)&t;/* Stereo Loopback */
DECL|macro|ASSABET_BCR_CF_BUS_OFF
mdefine_line|#define ASSABET_BCR_CF_BUS_OFF&t;(1&lt;&lt;7)&t;/* Compact Flash bus (0 = on, 1 = off (float)) */
DECL|macro|ASSABET_BCR_AUDIO_ON
mdefine_line|#define ASSABET_BCR_AUDIO_ON&t;(1&lt;&lt;8)&t;/* Audio power on */
DECL|macro|ASSABET_BCR_LIGHT_ON
mdefine_line|#define ASSABET_BCR_LIGHT_ON&t;(1&lt;&lt;9)&t;/* Backlight */
DECL|macro|ASSABET_BCR_LCD_12RGB
mdefine_line|#define ASSABET_BCR_LCD_12RGB&t;(1&lt;&lt;10)&t;/* 0 = 16RGB, 1 = 12RGB */
DECL|macro|ASSABET_BCR_LCD_ON
mdefine_line|#define ASSABET_BCR_LCD_ON&t;(1&lt;&lt;11)&t;/* LCD power on */
DECL|macro|ASSABET_BCR_RS232EN
mdefine_line|#define ASSABET_BCR_RS232EN&t;(1&lt;&lt;12)&t;/* RS232 transceiver enable */
DECL|macro|ASSABET_BCR_LED_RED
mdefine_line|#define ASSABET_BCR_LED_RED&t;(1&lt;&lt;13)&t;/* D9 (0 = on, 1 = off) */
DECL|macro|ASSABET_BCR_LED_GREEN
mdefine_line|#define ASSABET_BCR_LED_GREEN&t;(1&lt;&lt;14)&t;/* D8 (0 = on, 1 = off) */
DECL|macro|ASSABET_BCR_VIB_ON
mdefine_line|#define ASSABET_BCR_VIB_ON&t;(1&lt;&lt;15)&t;/* Vibration motor (quiet alert) */
DECL|macro|ASSABET_BCR_COM_DTR
mdefine_line|#define ASSABET_BCR_COM_DTR&t;(1&lt;&lt;16)&t;/* COMport Data Terminal Ready */
DECL|macro|ASSABET_BCR_COM_RTS
mdefine_line|#define ASSABET_BCR_COM_RTS&t;(1&lt;&lt;17)&t;/* COMport Request To Send */
DECL|macro|ASSABET_BCR_RAD_WU
mdefine_line|#define ASSABET_BCR_RAD_WU&t;(1&lt;&lt;18)&t;/* Radio wake up interrupt */
DECL|macro|ASSABET_BCR_SMB_EN
mdefine_line|#define ASSABET_BCR_SMB_EN&t;(1&lt;&lt;19)&t;/* System management bus enable */
DECL|macro|ASSABET_BCR_TV_IR_DEC
mdefine_line|#define ASSABET_BCR_TV_IR_DEC&t;(1&lt;&lt;20)&t;/* TV IR Decode Enable (not implemented) */
DECL|macro|ASSABET_BCR_QMUTE
mdefine_line|#define ASSABET_BCR_QMUTE&t;(1&lt;&lt;21)&t;/* Quick Mute */
DECL|macro|ASSABET_BCR_RAD_ON
mdefine_line|#define ASSABET_BCR_RAD_ON&t;(1&lt;&lt;22)&t;/* Radio Power On */
DECL|macro|ASSABET_BCR_SPK_OFF
mdefine_line|#define ASSABET_BCR_SPK_OFF&t;(1&lt;&lt;23)&t;/* 1 = Speaker amplifier power off */
macro_line|#ifdef CONFIG_SA1100_ASSABET
r_extern
r_void
id|ASSABET_BCR_frob
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
id|set
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ASSABET_BCR_frob
mdefine_line|#define ASSABET_BCR_frob(x,y)&t;do { } while (0)
macro_line|#endif
DECL|macro|ASSABET_BCR_set
mdefine_line|#define ASSABET_BCR_set(x)&t;ASSABET_BCR_frob((x), (x))
DECL|macro|ASSABET_BCR_clear
mdefine_line|#define ASSABET_BCR_clear(x)&t;ASSABET_BCR_frob((x), 0)
DECL|macro|ASSABET_BSR_BASE
mdefine_line|#define ASSABET_BSR_BASE&t;0xf1000000
DECL|macro|ASSABET_BSR
mdefine_line|#define ASSABET_BSR (*(volatile unsigned int*)(ASSABET_BSR_BASE))
DECL|macro|ASSABET_BSR_RS232_VALID
mdefine_line|#define ASSABET_BSR_RS232_VALID&t;(1 &lt;&lt; 24)
DECL|macro|ASSABET_BSR_COM_DCD
mdefine_line|#define ASSABET_BSR_COM_DCD&t;(1 &lt;&lt; 25)
DECL|macro|ASSABET_BSR_COM_CTS
mdefine_line|#define ASSABET_BSR_COM_CTS&t;(1 &lt;&lt; 26)
DECL|macro|ASSABET_BSR_COM_DSR
mdefine_line|#define ASSABET_BSR_COM_DSR&t;(1 &lt;&lt; 27)
DECL|macro|ASSABET_BSR_RAD_CTS
mdefine_line|#define ASSABET_BSR_RAD_CTS&t;(1 &lt;&lt; 28)
DECL|macro|ASSABET_BSR_RAD_DSR
mdefine_line|#define ASSABET_BSR_RAD_DSR&t;(1 &lt;&lt; 29)
DECL|macro|ASSABET_BSR_RAD_DCD
mdefine_line|#define ASSABET_BSR_RAD_DCD&t;(1 &lt;&lt; 30)
DECL|macro|ASSABET_BSR_RAD_RI
mdefine_line|#define ASSABET_BSR_RAD_RI&t;(1 &lt;&lt; 31)
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|ASSABET_GPIO_RADIO_IRQ
mdefine_line|#define ASSABET_GPIO_RADIO_IRQ&t;&t;GPIO_GPIO (14)&t;/* Radio interrupt request  */
DECL|macro|ASSABET_GPIO_PS_MODE_SYNC
mdefine_line|#define ASSABET_GPIO_PS_MODE_SYNC&t;GPIO_GPIO (16)&t;/* Power supply mode/sync   */
DECL|macro|ASSABET_GPIO_STEREO_64FS_CLK
mdefine_line|#define ASSABET_GPIO_STEREO_64FS_CLK&t;GPIO_GPIO (19)&t;/* SSP UDA1341 clock input  */
DECL|macro|ASSABET_GPIO_CF_IRQ
mdefine_line|#define ASSABET_GPIO_CF_IRQ&t;&t;GPIO_GPIO (21)&t;/* CF IRQ   */
DECL|macro|ASSABET_GPIO_CF_CD
mdefine_line|#define ASSABET_GPIO_CF_CD&t;&t;GPIO_GPIO (22)&t;/* CF CD */
DECL|macro|ASSABET_GPIO_CF_BVD2
mdefine_line|#define ASSABET_GPIO_CF_BVD2&t;&t;GPIO_GPIO (24)&t;/* CF BVD */
DECL|macro|ASSABET_GPIO_GFX_IRQ
mdefine_line|#define ASSABET_GPIO_GFX_IRQ&t;&t;GPIO_GPIO (24)&t;/* Graphics IRQ */
DECL|macro|ASSABET_GPIO_CF_BVD1
mdefine_line|#define ASSABET_GPIO_CF_BVD1&t;&t;GPIO_GPIO (25)&t;/* CF BVD */
DECL|macro|ASSABET_GPIO_BATT_LOW
mdefine_line|#define ASSABET_GPIO_BATT_LOW&t;&t;GPIO_GPIO (26)&t;/* Low battery */
DECL|macro|ASSABET_GPIO_RCLK
mdefine_line|#define ASSABET_GPIO_RCLK&t;&t;GPIO_GPIO (26)&t;/* CCLK/2  */
DECL|macro|ASSABET_IRQ_GPIO_CF_IRQ
mdefine_line|#define ASSABET_IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO21
DECL|macro|ASSABET_IRQ_GPIO_CF_CD
mdefine_line|#define ASSABET_IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO22
DECL|macro|ASSABET_IRQ_GPIO_CF_BVD2
mdefine_line|#define ASSABET_IRQ_GPIO_CF_BVD2&t;IRQ_GPIO24
DECL|macro|ASSABET_IRQ_GPIO_CF_BVD1
mdefine_line|#define ASSABET_IRQ_GPIO_CF_BVD1&t;IRQ_GPIO25
macro_line|#endif
eof
