multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/assabet.h&n; *&n; * Created 2000/06/05 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware specific definitions for Assabet&n; *&n; * 2000/05/23 John Dorsey &lt;john+@cs.cmu.edu&gt;&n; *      Definitions for Neponset added.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* System Configuration Register flags */
DECL|macro|SCR_SDRAM_LOW
mdefine_line|#define SCR_SDRAM_LOW&t;(1&lt;&lt;2)&t;/* SDRAM size (low bit) */
DECL|macro|SCR_SDRAM_HIGH
mdefine_line|#define SCR_SDRAM_HIGH&t;(1&lt;&lt;3)&t;/* SDRAM size (high bit) */
DECL|macro|SCR_FLASH_LOW
mdefine_line|#define SCR_FLASH_LOW&t;(1&lt;&lt;4)&t;/* Flash size (low bit) */
DECL|macro|SCR_FLASH_HIGH
mdefine_line|#define SCR_FLASH_HIGH&t;(1&lt;&lt;5)&t;/* Flash size (high bit) */
DECL|macro|SCR_GFX
mdefine_line|#define SCR_GFX&t;&t;(1&lt;&lt;8)&t;/* Graphics Accelerator (0 = present) */
DECL|macro|SCR_SA1111
mdefine_line|#define SCR_SA1111&t;(1&lt;&lt;9)&t;/* Neponset (0 = present) */
DECL|macro|SCR_INIT
mdefine_line|#define SCR_INIT&t;-1
multiline_comment|/* Board Control Register */
DECL|macro|BCR_BASE
mdefine_line|#define BCR_BASE  0xf1000000
DECL|macro|BCR
mdefine_line|#define BCR (*(volatile unsigned int *)(BCR_BASE))
DECL|macro|BCR_DB1110
mdefine_line|#define BCR_DB1110&t;(0x00A07410)
DECL|macro|BCR_DB1111
mdefine_line|#define BCR_DB1111&t;(0x00A074E2)
DECL|macro|BCR_CF_PWR
mdefine_line|#define BCR_CF_PWR&t;(1&lt;&lt;0)&t;/* Compact Flash Power (1 = 3.3v, 0 = off) */
DECL|macro|BCR_CF_RST
mdefine_line|#define BCR_CF_RST&t;(1&lt;&lt;1)&t;/* Compact Flash Reset (1 = power up reset) */
DECL|macro|BCR_GFX_RST
mdefine_line|#define BCR_GFX_RST&t;(1&lt;&lt;1)&t;/* Graphics Accelerator Reset (0 = hold reset) */
DECL|macro|BCR_CODEC_RST
mdefine_line|#define BCR_CODEC_RST&t;(1&lt;&lt;2)&t;/* 0 = Holds UCB1300, ADI7171, and UDA1341 in reset */
DECL|macro|BCR_IRDA_FSEL
mdefine_line|#define BCR_IRDA_FSEL&t;(1&lt;&lt;3)&t;/* IRDA Frequency select (0 = SIR, 1 = MIR/ FIR) */
DECL|macro|BCR_IRDA_MD0
mdefine_line|#define BCR_IRDA_MD0&t;(1&lt;&lt;4)&t;/* Range/Power select */
DECL|macro|BCR_IRDA_MD1
mdefine_line|#define BCR_IRDA_MD1&t;(1&lt;&lt;5)&t;/* Range/Power select */
DECL|macro|BCR_STEREO_LB
mdefine_line|#define BCR_STEREO_LB&t;(1&lt;&lt;6)&t;/* Stereo Loopback */
DECL|macro|BCR_CF_BUS_OFF
mdefine_line|#define BCR_CF_BUS_OFF&t;(1&lt;&lt;7)&t;/* Compact Flash bus (0 = on, 1 = off (float)) */
DECL|macro|BCR_AUDIO_ON
mdefine_line|#define BCR_AUDIO_ON&t;(1&lt;&lt;8)&t;/* Audio power on */
DECL|macro|BCR_LIGHT_ON
mdefine_line|#define BCR_LIGHT_ON&t;(1&lt;&lt;9)&t;/* Backlight */
DECL|macro|BCR_LCD_12RGB
mdefine_line|#define BCR_LCD_12RGB&t;(1&lt;&lt;10)&t;/* 0 = 16RGB, 1 = 12RGB */
DECL|macro|BCR_LCD_ON
mdefine_line|#define BCR_LCD_ON&t;(1&lt;&lt;11)&t;/* LCD power on */
DECL|macro|BCR_RS232EN
mdefine_line|#define BCR_RS232EN&t;(1&lt;&lt;12)&t;/* RS232 transceiver enable */
DECL|macro|BCR_LED_RED
mdefine_line|#define BCR_LED_RED&t;(1&lt;&lt;13)&t;/* D9 (0 = on, 1 = off) */
DECL|macro|BCR_LED_GREEN
mdefine_line|#define BCR_LED_GREEN&t;(1&lt;&lt;14)&t;/* D8 (0 = on, 1 = off) */
DECL|macro|BCR_VIB_ON
mdefine_line|#define BCR_VIB_ON&t;(1&lt;&lt;15)&t;/* Vibration motor (quiet alert) */
DECL|macro|BCR_COM_DTR
mdefine_line|#define BCR_COM_DTR&t;(1&lt;&lt;16)&t;/* COMport Data Terminal Ready */
DECL|macro|BCR_COM_RTS
mdefine_line|#define BCR_COM_RTS&t;(1&lt;&lt;17)&t;/* COMport Request To Send */
DECL|macro|BCR_RAD_WU
mdefine_line|#define BCR_RAD_WU&t;(1&lt;&lt;18)&t;/* Radio wake up interrupt */
DECL|macro|BCR_SMB_EN
mdefine_line|#define BCR_SMB_EN&t;(1&lt;&lt;19)&t;/* System management bus enable */
DECL|macro|BCR_TV_IR_DEC
mdefine_line|#define BCR_TV_IR_DEC&t;(1&lt;&lt;20)&t;/* TV IR Decode Enable */
DECL|macro|BCR_QMUTE
mdefine_line|#define BCR_QMUTE&t;(1&lt;&lt;21)&t;/* Quick Mute */
DECL|macro|BCR_RAD_ON
mdefine_line|#define BCR_RAD_ON&t;(1&lt;&lt;22)&t;/* Radio Power On */
DECL|macro|BCR_SPK_OFF
mdefine_line|#define BCR_SPK_OFF&t;(1&lt;&lt;23)&t;/* 1 = Speaker amplifier power off */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|SCR_value
suffix:semicolon
r_extern
r_int
r_int
id|BCR_value
suffix:semicolon
DECL|macro|BCR_set
mdefine_line|#define BCR_set( x )&t;BCR = (BCR_value |= (x))
DECL|macro|BCR_clear
mdefine_line|#define BCR_clear( x )&t;BCR = (BCR_value &amp;= ~(x))
macro_line|#endif
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|GPIO_RADIO_IRQ
mdefine_line|#define GPIO_RADIO_IRQ&t;&t;GPIO_GPIO (14)&t;/* Radio interrupt request  */
DECL|macro|GPIO_L3_I2C_SDA
mdefine_line|#define GPIO_L3_I2C_SDA&t;&t;GPIO_GPIO (15)&t;/* L3 and SMB control ports */
DECL|macro|GPIO_PS_MODE_SYNC
mdefine_line|#define GPIO_PS_MODE_SYNC&t;GPIO_GPIO (16)&t;/* Power supply mode/sync   */
DECL|macro|GPIO_L3_MODE
mdefine_line|#define GPIO_L3_MODE&t;&t;GPIO_GPIO (17)&t;/* L3 mode signal with LED  */
DECL|macro|GPIO_L3_I2C_SCL
mdefine_line|#define GPIO_L3_I2C_SCL&t;&t;GPIO_GPIO (18)&t;/* L3 and I2C control ports */
DECL|macro|GPIO_STEREO_64FS_CLK
mdefine_line|#define GPIO_STEREO_64FS_CLK&t;GPIO_GPIO (19)&t;/* SSP UDA1341 clock input  */
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ&t;&t;GPIO_GPIO (21)&t;/* CF IRQ   */
DECL|macro|GPIO_MBGNT
mdefine_line|#define GPIO_MBGNT&t;&t;GPIO_GPIO (21)&t;/* 1111 MBGNT */
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD&t;&t;GPIO_GPIO (22)&t;/* CF CD */
DECL|macro|GPIO_MBREQ
mdefine_line|#define GPIO_MBREQ&t;&t;GPIO_GPIO (22)&t;/* 1111 MBREQ */
DECL|macro|GPIO_UCB1300_IRQ
mdefine_line|#define GPIO_UCB1300_IRQ&t;GPIO_GPIO (23)&t;/* UCB GPIO and touchscreen */
DECL|macro|GPIO_CF_BVD2
mdefine_line|#define GPIO_CF_BVD2&t;&t;GPIO_GPIO (24)&t;/* CF BVD */
DECL|macro|GPIO_GFX_IRQ
mdefine_line|#define GPIO_GFX_IRQ&t;&t;GPIO_GPIO (24)&t;/* Graphics IRQ */
DECL|macro|GPIO_CF_BVD1
mdefine_line|#define GPIO_CF_BVD1&t;&t;GPIO_GPIO (25)&t;/* CF BVD */
DECL|macro|GPIO_NEP_IRQ
mdefine_line|#define GPIO_NEP_IRQ&t;&t;GPIO_GPIO (25)&t;/* Neponset IRQ */
DECL|macro|GPIO_BATT_LOW
mdefine_line|#define GPIO_BATT_LOW&t;&t;GPIO_GPIO (26)&t;/* Low battery */
DECL|macro|GPIO_RCLK
mdefine_line|#define GPIO_RCLK&t;&t;GPIO_GPIO (26)&t;/* CCLK/2  */
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO21
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO22
DECL|macro|IRQ_GPIO_MBREQ
mdefine_line|#define IRQ_GPIO_MBREQ&t;&t;IRQ_GPIO22
DECL|macro|IRQ_GPIO_UCB1300_IRQ
mdefine_line|#define IRQ_GPIO_UCB1300_IRQ&t;IRQ_GPIO23
DECL|macro|IRQ_GPIO_CF_BVD2
mdefine_line|#define IRQ_GPIO_CF_BVD2&t;IRQ_GPIO24
DECL|macro|IRQ_GPIO_CF_BVD1
mdefine_line|#define IRQ_GPIO_CF_BVD1&t;IRQ_GPIO25
DECL|macro|IRQ_GPIO_NEP_IRQ
mdefine_line|#define IRQ_GPIO_NEP_IRQ&t;IRQ_GPIO25
multiline_comment|/*&n; * Neponset definitions: &n; */
DECL|macro|SA1111_BASE
mdefine_line|#define SA1111_BASE             (0x40000000)
DECL|macro|NEPONSET_ETHERNET_IRQ
mdefine_line|#define NEPONSET_ETHERNET_IRQ&t;MISC_IRQ0
DECL|macro|NEPONSET_USAR_IRQ
mdefine_line|#define NEPONSET_USAR_IRQ&t;MISC_IRQ1
DECL|macro|NEPONSET_CPLD_BASE
mdefine_line|#define NEPONSET_CPLD_BASE      (0x10000000)
DECL|macro|Nep_p2v
mdefine_line|#define Nep_p2v( x )            ((x) - NEPONSET_CPLD_BASE + 0xf0000000)
DECL|macro|Nep_v2p
mdefine_line|#define Nep_v2p( x )            ((x) - 0xf0000000 + NEPONSET_CPLD_BASE)
DECL|macro|_IRR
mdefine_line|#define _IRR                    0x10000024      /* Interrupt Reason Register */
DECL|macro|_AUD_CTL
mdefine_line|#define _AUD_CTL                0x100000c0      /* Audio controls (RW)       */
DECL|macro|_MDM_CTL_0
mdefine_line|#define _MDM_CTL_0              0x100000b0      /* Modem control 0 (RW)      */
DECL|macro|_MDM_CTL_1
mdefine_line|#define _MDM_CTL_1              0x100000b4      /* Modem control 1 (RW)      */
DECL|macro|_NCR_0
mdefine_line|#define _NCR_0&t;                0x100000a0      /* Control Register (RW)     */
DECL|macro|_KP_X_OUT
mdefine_line|#define _KP_X_OUT               0x10000090      /* Keypad row write (RW)     */
DECL|macro|_KP_Y_IN
mdefine_line|#define _KP_Y_IN                0x10000080      /* Keypad column read (RO)   */
DECL|macro|_SWPK
mdefine_line|#define _SWPK                   0x10000020      /* Switch pack (RO)          */
DECL|macro|_WHOAMI
mdefine_line|#define _WHOAMI                 0x10000000      /* System ID Register (RO)   */
DECL|macro|_LEDS
mdefine_line|#define _LEDS                   0x10000010      /* LEDs [31:0] (WO)          */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|IRR
mdefine_line|#define IRR                     (*((volatile u_char *) Nep_p2v(_IRR)))
DECL|macro|AUD_CTL
mdefine_line|#define AUD_CTL                 (*((volatile u_char *) Nep_p2v(_AUD_CTL)))
DECL|macro|MDM_CTL_0
mdefine_line|#define MDM_CTL_0               (*((volatile u_char *) Nep_p2v(_MDM_CTL_0)))
DECL|macro|MDM_CTL_1
mdefine_line|#define MDM_CTL_1               (*((volatile u_char *) Nep_p2v(_MDM_CTL_1)))
DECL|macro|NCR_0
mdefine_line|#define NCR_0&t;&t;&t;(*((volatile u_char *) Nep_p2v(_NCR_0)))
DECL|macro|KP_X_OUT
mdefine_line|#define KP_X_OUT                (*((volatile u_char *) Nep_p2v(_KP_X_OUT)))
DECL|macro|KP_Y_IN
mdefine_line|#define KP_Y_IN                 (*((volatile u_char *) Nep_p2v(_KP_Y_IN)))
DECL|macro|SWPK
mdefine_line|#define SWPK                    (*((volatile u_char *) Nep_p2v(_SWPK)))
DECL|macro|WHOAMI
mdefine_line|#define WHOAMI                  (*((volatile u_char *) Nep_p2v(_WHOAMI)))
DECL|macro|LEDS
mdefine_line|#define LEDS                    (*((volatile Word   *) Nep_p2v(_LEDS)))
macro_line|#endif
DECL|macro|IRR_ETHERNET
mdefine_line|#define IRR_ETHERNET&t;&t;(1&lt;&lt;0)
DECL|macro|IRR_USAR
mdefine_line|#define IRR_USAR&t;&t;(1&lt;&lt;1)
DECL|macro|IRR_SA1111
mdefine_line|#define IRR_SA1111&t;&t;(1&lt;&lt;2)
DECL|macro|AUD_SEL_1341
mdefine_line|#define AUD_SEL_1341            (1&lt;&lt;0)
DECL|macro|AUD_MUTE_1341
mdefine_line|#define AUD_MUTE_1341           (1&lt;&lt;1)
DECL|macro|NCR_GP01_OFF
mdefine_line|#define NCR_GP01_OFF&t;&t;(1&lt;&lt;0)
DECL|macro|NCR_TP_PWR_EN
mdefine_line|#define NCR_TP_PWR_EN&t;&t;(1&lt;&lt;1)
DECL|macro|NCR_MS_PWR_EN
mdefine_line|#define NCR_MS_PWR_EN&t;&t;(1&lt;&lt;2)
DECL|macro|NCR_ENET_OSC_EN
mdefine_line|#define NCR_ENET_OSC_EN&t;&t;(1&lt;&lt;3)
DECL|macro|NCR_SPI_KB_WK_UP
mdefine_line|#define NCR_SPI_KB_WK_UP&t;(1&lt;&lt;4)
DECL|macro|NCR_A0VPP
mdefine_line|#define NCR_A0VPP&t;&t;(1&lt;&lt;5)
DECL|macro|NCR_A1VPP
mdefine_line|#define NCR_A1VPP&t;&t;(1&lt;&lt;6)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|machine_has_neponset
mdefine_line|#define machine_has_neponset()  ((SCR_value &amp; SCR_SA1111) == 0)
macro_line|#endif
eof
