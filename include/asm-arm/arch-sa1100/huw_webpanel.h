multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/huw_webpanel.h&n; *&n; * based of assabet.h&n; *&n; * This file contains the hardware specific definitions for HUW_Webpanel&n; *&n; * 2000/11/13 Roman Jordan &lt;jor@hoeft-wessel.de&gt;&n; */
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
DECL|macro|BCR_PSIO_DTR1
mdefine_line|#define BCR_PSIO_DTR1      (1&lt;&lt;29)
DECL|macro|BCR_TFT_NPWR
mdefine_line|#define BCR_TFT_NPWR       (1&lt;&lt;28)
DECL|macro|BCR_PSIO_DTR3
mdefine_line|#define BCR_PSIO_DTR3      (1&lt;&lt;27)
DECL|macro|BCR_TFT_ENA
mdefine_line|#define BCR_TFT_ENA        (1&lt;&lt;26)
DECL|macro|BCR_CCFL_POW
mdefine_line|#define BCR_CCFL_POW       (1&lt;&lt;25)
DECL|macro|BCR_PSIO_RTS1
mdefine_line|#define BCR_PSIO_RTS1      (1&lt;&lt;24)
DECL|macro|BCR_PWM_BACKLIGHT
mdefine_line|#define BCR_PWM_BACKLIGHT  (1&lt;&lt;23)
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
eof
