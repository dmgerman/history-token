multiline_comment|/*&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* Board Control Register */
DECL|macro|BCR_BASE
mdefine_line|#define BCR_BASE  0xf0000000
DECL|macro|BCR
mdefine_line|#define BCR (*(volatile unsigned int *)(BCR_BASE))
DECL|macro|BCR_DB1110
mdefine_line|#define BCR_DB1110&t;(0x00A07410)
DECL|macro|BCR_FREEBIRD_AUDIO_PWR
mdefine_line|#define BCR_FREEBIRD_AUDIO_PWR&t;(1&lt;&lt;0)&t;/* Audio Power (1 = on, 0 = off) */
DECL|macro|BCR_FREEBIRD_LCD_PWR
mdefine_line|#define BCR_FREEBIRD_LCD_PWR&t;&t;(1&lt;&lt;1)&t;/* LCD Power (1 = on) */
DECL|macro|BCR_FREEBIRD_CODEC_RST
mdefine_line|#define BCR_FREEBIRD_CODEC_RST&t;(1&lt;&lt;2)&t;/* 0 = Holds UCB1300, ADI7171, and UDA1341 in reset */
DECL|macro|BCR_FREEBIRD_IRDA_FSEL
mdefine_line|#define BCR_FREEBIRD_IRDA_FSEL&t;(1&lt;&lt;3)&t;/* IRDA Frequency select (0 = SIR, 1 = MIR/ FIR) */
DECL|macro|BCR_FREEBIRD_IRDA_MD0
mdefine_line|#define BCR_FREEBIRD_IRDA_MD0&t;(1&lt;&lt;4)&t;/* Range/Power select */
DECL|macro|BCR_FREEBIRD_IRDA_MD1
mdefine_line|#define BCR_FREEBIRD_IRDA_MD1&t;(1&lt;&lt;5)&t;/* Range/Power select */
DECL|macro|BCR_FREEBIRD_LCD_DISP
mdefine_line|#define BCR_FREEBIRD_LCD_DISP&t;(1&lt;&lt;7)&t;/* LCD display (1 = on, 0 = off */
DECL|macro|BCR_FREEBIRD_LCD_BACKLIGHT
mdefine_line|#define BCR_FREEBIRD_LCD_BACKLIGHT&t;(1&lt;&lt;16)&t;/* LCD backlight ,1=on */
DECL|macro|BCR_FREEBIRD_LCD_LIGHT_INC
mdefine_line|#define BCR_FREEBIRD_LCD_LIGHT_INC&t;(1&lt;&lt;17)&t;/* LCD backlight brightness */
DECL|macro|BCR_FREEBIRD_LCD_LIGHT_DU
mdefine_line|#define BCR_FREEBIRD_LCD_LIGHT_DU&t;(1&lt;&lt;18)&t;/* LCD backlight brightness */
DECL|macro|BCR_FREEBIRD_LCD_INC
mdefine_line|#define BCR_FREEBIRD_LCD_INC&t;&t;&t;(1&lt;&lt;19)&t;/* LCD contrast  */
DECL|macro|BCR_FREEBIRD_LCD_DU
mdefine_line|#define BCR_FREEBIRD_LCD_DU&t;&t;&t;(1&lt;&lt;20)&t;/* LCD contrast */
DECL|macro|BCR_FREEBIRD_QMUTE
mdefine_line|#define BCR_FREEBIRD_QMUTE&t;&t;&t;(1&lt;&lt;21)&t;/* Quick Mute */
DECL|macro|BCR_FREEBIRD_ALARM_LED
mdefine_line|#define BCR_FREEBIRD_ALARM_LED&t;&t;(1&lt;&lt;22)&t;/* ALARM LED control */
DECL|macro|BCR_FREEBIRD_SPK_OFF
mdefine_line|#define BCR_FREEBIRD_SPK_OFF&t;(1&lt;&lt;23)&t;/* 1 = Speaker amplifier power off */
macro_line|#ifndef __ASSEMBLY__
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
DECL|macro|GPIO_FREEBIRD_NPOWER_BUTTON
mdefine_line|#define GPIO_FREEBIRD_NPOWER_BUTTON&t;&t;GPIO_GPIO(0)
DECL|macro|GPIO_FREEBIRD_APP1_BUTTON
mdefine_line|#define GPIO_FREEBIRD_APP1_BUTTON&t;&t;GPIO_GPIO(1)
DECL|macro|GPIO_FREEBIRD_APP2_BUTTON
mdefine_line|#define GPIO_FREEBIRD_APP2_BUTTON&t;&t;GPIO_GPIO(2)
DECL|macro|GPIO_FREEBIRD_APP3_BUTTOM
mdefine_line|#define GPIO_FREEBIRD_APP3_BUTTOM&t;&t;GPIO_GPIO(3)
DECL|macro|GPIO_FREEBIRD_UCB1300
mdefine_line|#define GPIO_FREEBIRD_UCB1300&t;&t;&t;GPIO_GPIO(4)
DECL|macro|GPIO_FREEBIRD_EXPWR
mdefine_line|#define GPIO_FREEBIRD_EXPWR&t;&t;&t;&t;GPIO_GPIO(8)
DECL|macro|GPIO_FREEBIRD_CHARGING
mdefine_line|#define GPIO_FREEBIRD_CHARGING&t;&t;&t;GPIO_GPIO(9)
DECL|macro|GPIO_FREEBIRD_RAMD
mdefine_line|#define GPIO_FREEBIRD_RAMD&t;&t;&t;&t;GPIO_GPIO(14)
DECL|macro|GPIO_FREEBIRD_L3_DATA
mdefine_line|#define GPIO_FREEBIRD_L3_DATA&t;&t;&t;GPIO_GPIO(15)
DECL|macro|GPIO_FREEBIRD_L3_MODE
mdefine_line|#define GPIO_FREEBIRD_L3_MODE&t;&t;&t;GPIO_GPIO(17)
DECL|macro|GPIO_FREEBIRD_L3_CLOCK
mdefine_line|#define GPIO_FREEBIRD_L3_CLOCK&t;&t;&t;GPIO_GPIO(18)
DECL|macro|GPIO_FREEBIRD_STEREO_64FS_CLK
mdefine_line|#define GPIO_FREEBIRD_STEREO_64FS_CLK&t;GPIO_GPIO(10)
DECL|macro|GPIO_FREEBIRD_CF_CD
mdefine_line|#define GPIO_FREEBIRD_CF_CD&t;&t;&t;&t;GPIO_GPIO(22)
DECL|macro|GPIO_FREEBIRD_CF_IRQ
mdefine_line|#define GPIO_FREEBIRD_CF_IRQ&t;&t;&t;GPIO_GPIO(21)
DECL|macro|GPIO_FREEBIRD_CF_BVD
mdefine_line|#define GPIO_FREEBIRD_CF_BVD&t;&t;&t;GPIO_GPIO(25)
DECL|macro|IRQ_GPIO_FREEBIRD_NPOWER_BUTTON
mdefine_line|#define IRQ_GPIO_FREEBIRD_NPOWER_BUTTON&t;IRQ_GPIO0
DECL|macro|IRQ_GPIO_FREEBIRD_APP1_BUTTON
mdefine_line|#define IRQ_GPIO_FREEBIRD_APP1_BUTTON&t;IRQ_GPIO1
DECL|macro|IRQ_GPIO_FREEBIRD_APP2_BUTTON
mdefine_line|#define IRQ_GPIO_FREEBIRD_APP2_BUTTON&t;IRQ_GPIO2
DECL|macro|IRQ_GPIO_FREEBIRD_APP3_BUTTON
mdefine_line|#define IRQ_GPIO_FREEBIRD_APP3_BUTTON&t;IRQ_GPIO3
DECL|macro|IRQ_GPIO_FREEBIRD_UCB1300_IRQ
mdefine_line|#define IRQ_GPIO_FREEBIRD_UCB1300_IRQ&t;IRQ_GPIO4
DECL|macro|IRQ_GPIO_FREEBIRD_CF_IRQ
mdefine_line|#define IRQ_GPIO_FREEBIRD_CF_IRQ&t;&t;IRQ_GPIO21
DECL|macro|IRQ_GPIO_FREEBIRD_CF_CD
mdefine_line|#define IRQ_GPIO_FREEBIRD_CF_CD&t;&t;&t;IRQ_GPIO22
DECL|macro|IRQ_GPIO_FREEBIRD_CF_BVD
mdefine_line|#define IRQ_GPIO_FREEBIRD_CF_BVD&t;&t;IRQ_GPIO25
eof
