macro_line|#ifndef _INCLUDE_BITSY_H_
DECL|macro|_INCLUDE_BITSY_H_
mdefine_line|#define _INCLUDE_BITSY_H_
DECL|macro|GPIO_BITSY_PCMCIA_CD0
mdefine_line|#define GPIO_BITSY_PCMCIA_CD0  GPIO_GPIO (17)
DECL|macro|GPIO_BITSY_PCMCIA_CD1
mdefine_line|#define GPIO_BITSY_PCMCIA_CD1  GPIO_GPIO (10)
DECL|macro|GPIO_BITSY_PCMCIA_IRQ0
mdefine_line|#define GPIO_BITSY_PCMCIA_IRQ0 GPIO_GPIO (21)
DECL|macro|GPIO_BITSY_PCMCIA_IRQ1
mdefine_line|#define GPIO_BITSY_PCMCIA_IRQ1 GPIO_GPIO (11)
multiline_comment|/* audio sample rate clock generator */
DECL|macro|GPIO_BITSY_CLK_SET0
mdefine_line|#define GPIO_BITSY_CLK_SET0    GPIO_GPIO (12)
DECL|macro|GPIO_BITSY_CLK_SET1
mdefine_line|#define GPIO_BITSY_CLK_SET1    GPIO_GPIO (13)
multiline_comment|/* UDA1341 L3 Interface */
DECL|macro|GPIO_BITSY_L3_DATA
mdefine_line|#define GPIO_BITSY_L3_DATA     GPIO_GPIO (14)
DECL|macro|GPIO_BITSY_L3_CLOCK
mdefine_line|#define GPIO_BITSY_L3_CLOCK    GPIO_GPIO (16)
DECL|macro|GPIO_BITSY_L3_MODE
mdefine_line|#define GPIO_BITSY_L3_MODE     GPIO_GPIO (15)
DECL|macro|IRQ_GPIO_BITSY_PCMCIA_CD0
mdefine_line|#define IRQ_GPIO_BITSY_PCMCIA_CD0&t;IRQ_GPIO17
DECL|macro|IRQ_GPIO_BITSY_PCMCIA_CD1
mdefine_line|#define IRQ_GPIO_BITSY_PCMCIA_CD1&t;IRQ_GPIO10
DECL|macro|IRQ_GPIO_BITSY_PCMCIA_IRQ0
mdefine_line|#define IRQ_GPIO_BITSY_PCMCIA_IRQ0&t;IRQ_GPIO21
DECL|macro|IRQ_GPIO_BITSY_PCMCIA_IRQ1
mdefine_line|#define IRQ_GPIO_BITSY_PCMCIA_IRQ1&t;IRQ_GPIO22
DECL|macro|EGPIO_BITSY_VPP_ON
mdefine_line|#define EGPIO_BITSY_VPP_ON      (1 &lt;&lt; 0)
DECL|macro|EGPIO_BITSY_CARD_RESET
mdefine_line|#define EGPIO_BITSY_CARD_RESET  (1 &lt;&lt; 1)    /* reset the attached pcmcia/compactflash card.  active high. */
DECL|macro|EGPIO_BITSY_OPT_RESET
mdefine_line|#define EGPIO_BITSY_OPT_RESET   (1 &lt;&lt; 2)    /* reset the attached option pack.  active high. */
DECL|macro|EGPIO_BITSY_CODEC_NRESET
mdefine_line|#define EGPIO_BITSY_CODEC_NRESET (1 &lt;&lt; 3)   /* reset the onboard UDA1341.  active low. */
DECL|macro|EGPIO_BITSY_OPT_NVRAM_ON
mdefine_line|#define EGPIO_BITSY_OPT_NVRAM_ON (1 &lt;&lt; 4)   /* apply power to optionpack nvram, active high. */
DECL|macro|EGPIO_BITSY_OPT_ON
mdefine_line|#define EGPIO_BITSY_OPT_ON       (1 &lt;&lt; 5)   /* full power to option pack.  active high. */
DECL|macro|EGPIO_BITSY_LCD_ON
mdefine_line|#define EGPIO_BITSY_LCD_ON       (1 &lt;&lt; 6)   /* enable 3.3V to LCD.  active high. */
DECL|macro|EGPIO_BITSY_RS232_ON
mdefine_line|#define EGPIO_BITSY_RS232_ON     (1 &lt;&lt; 7)   /* UART3 transceiver force on.  Active high. */
DECL|macro|EGPIO_BITSY_LCD_PCI
mdefine_line|#define EGPIO_BITSY_LCD_PCI      (1 &lt;&lt; 8)   /* LCD control IC enable.  active high. */
DECL|macro|EGPIO_BITSY_IR_ON
mdefine_line|#define EGPIO_BITSY_IR_ON        (1 &lt;&lt; 9)   /* apply power to IR module.  active high. */
DECL|macro|EGPIO_BITSY_AUD_AMP_ON
mdefine_line|#define EGPIO_BITSY_AUD_AMP_ON   (1 &lt;&lt; 10)  /* apply power to audio power amp.  active high. */
DECL|macro|EGPIO_BITSY_AUD_PWR_ON
mdefine_line|#define EGPIO_BITSY_AUD_PWR_ON   (1 &lt;&lt; 11)  /* apply poewr to reset of audio circuit.  active high. */
DECL|macro|EGPIO_BITSY_QMUTE
mdefine_line|#define EGPIO_BITSY_QMUTE        (1 &lt;&lt; 12)  /* mute control for onboard UDA1341.  active high. */
DECL|macro|EGPIO_BITSY_IR_FSEL
mdefine_line|#define EGPIO_BITSY_IR_FSEL      (1 &lt;&lt; 13)  /* IR speed select: 1-&gt;fast, 0-&gt;slow */
DECL|macro|EGPIO_BITSY_LCD_5V_ON
mdefine_line|#define EGPIO_BITSY_LCD_5V_ON    (1 &lt;&lt; 14)  /* enable 5V to LCD. active high. */
DECL|macro|EGPIO_BITSY_LVDD_ON
mdefine_line|#define EGPIO_BITSY_LVDD_ON      (1 &lt;&lt; 15)  /* enable 9V and -6.5V to LCD. */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|BITSY_EGPIO
mdefine_line|#define BITSY_EGPIO  (*(volatile int *)0xf0000000)
r_extern
r_void
id|clr_bitsy_egpio
c_func
(paren
r_int
r_int
id|x
)paren
suffix:semicolon
r_extern
r_void
id|set_bitsy_egpio
c_func
(paren
r_int
r_int
id|x
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
