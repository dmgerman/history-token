multiline_comment|/*&n;&t;stork.h&n;&n;*/
macro_line|#ifndef STORK_SA1100_H
DECL|macro|STORK_SA1100_H
mdefine_line|#define STORK_SA1100_H
multiline_comment|/* ugly - this will make sure we build sa1100fb for the Nec display not the Kyocera */
DECL|macro|STORK_TFT
mdefine_line|#define STORK_TFT&t;1
DECL|macro|GPIO_STORK_SWITCH_1
mdefine_line|#define GPIO_STORK_SWITCH_1&t;&t;(1 &lt;&lt; 0)    /* Switch 1 - input */
DECL|macro|GPIO_STORK_SWITCH_2
mdefine_line|#define GPIO_STORK_SWITCH_2&t;&t;(1 &lt;&lt; 1)    /* Switch 2 - input */
DECL|macro|GPIO_STORK_TOUCH_SCREEN_BUSY
mdefine_line|#define GPIO_STORK_TOUCH_SCREEN_BUSY&t;(1 &lt;&lt; 10)   /* TOUCH_SCREEN_BUSY - input */
DECL|macro|GPIO_STORK_TOUCH_SCREEN_DATA
mdefine_line|#define GPIO_STORK_TOUCH_SCREEN_DATA&t;(1 &lt;&lt; 11)   /* TOUCH_SCREEN_DATA - input */
DECL|macro|GPIO_STORK_CODEC_AGCSTAT
mdefine_line|#define GPIO_STORK_CODEC_AGCSTAT&t;(1 &lt;&lt; 12)   /* CODEC_AGCSTAT -input */
DECL|macro|GPIO_STORK_RS232_ON
mdefine_line|#define GPIO_STORK_RS232_ON&t;&t;(1 &lt;&lt; 13)   /* enable RS232 (UART1) */
DECL|macro|GPIO_STORK_TEST_POINT
mdefine_line|#define GPIO_STORK_TEST_POINT&t;&t;(1 &lt;&lt; 14)   /* to test point */
DECL|macro|GPIO_STORK_L3_I2C_SDA
mdefine_line|#define GPIO_STORK_L3_I2C_SDA&t;&t;(1 &lt;&lt; 15)   /* L3_I2C_SDA - bidirectional */
DECL|macro|GPIO_STORK_PSU_SYNC_MODE
mdefine_line|#define GPIO_STORK_PSU_SYNC_MODE&t;(1 &lt;&lt; 16)   /* PSU_SYNC_MODE - output */
DECL|macro|GPIO_STORK_L3_MODE
mdefine_line|#define GPIO_STORK_L3_MODE&t;&t;(1 &lt;&lt; 17)   /* L3 mode - output (??) */
DECL|macro|GPIO_STORK_L3_I2C_SCL
mdefine_line|#define GPIO_STORK_L3_I2C_SCL&t;&t;(1 &lt;&lt; 18)   /* L3_I2C_SCL - bidirectional */
DECL|macro|GPIO_STORK_AUDIO_CLK
mdefine_line|#define GPIO_STORK_AUDIO_CLK&t;&t;(1 &lt;&lt; 19)   /* SSP external clock (Audio clock) - input */
DECL|macro|GPIO_STORK_PCMCIA_A_CARD_DETECT
mdefine_line|#define GPIO_STORK_PCMCIA_A_CARD_DETECT&t;(1 &lt;&lt; 20)   /* PCMCIA_A_CARD_DETECT - input */
DECL|macro|GPIO_STORK_PCMCIA_B_CARD_DETECT
mdefine_line|#define GPIO_STORK_PCMCIA_B_CARD_DETECT&t;(1 &lt;&lt; 21)   /* PCMCIA_B_CARD_DETECT - input */
DECL|macro|GPIO_STORK_PCMCIA_A_RDY
mdefine_line|#define GPIO_STORK_PCMCIA_A_RDY&t;&t;(1 &lt;&lt; 22)   /* PCMCIA_A_RDY - input */
DECL|macro|GPIO_STORK_PCMCIA_B_RDY
mdefine_line|#define GPIO_STORK_PCMCIA_B_RDY&t;&t;(1 &lt;&lt; 23)   /* PCMCIA_B_RDY - input */
DECL|macro|GPIO_STORK_SWITCH_EXTRA_IRQ
mdefine_line|#define GPIO_STORK_SWITCH_EXTRA_IRQ&t;(1 &lt;&lt; 24)   /* Extra IRQ from switch detect logic - input  */
DECL|macro|GPIO_STORK_SWITCH_IRQ
mdefine_line|#define GPIO_STORK_SWITCH_IRQ&t;&t;(1 &lt;&lt; 25)   /* Sitch irq - input */
DECL|macro|GPIO_STORK_BATTERY_LOW_IRQ
mdefine_line|#define GPIO_STORK_BATTERY_LOW_IRQ&t;(1 &lt;&lt; 26)   /* BATTERY_LOW_IRQ - input */
DECL|macro|GPIO_STORK_TOUCH_SCREEN_PEN_IRQ
mdefine_line|#define GPIO_STORK_TOUCH_SCREEN_PEN_IRQ&t;(1 &lt;&lt; 27)   /* TOUCH_SCREEN_PEN_IRQ -input */
DECL|macro|IRQ_GPIO_STORK_PCMCIA_A_CARD_DETECT
mdefine_line|#define IRQ_GPIO_STORK_PCMCIA_A_CARD_DETECT&t;IRQ_GPIO20   /* PCMCIA_A_CARD_DETECT - input */
DECL|macro|IRQ_GPIO_STORK_PCMCIA_B_CARD_DETECT
mdefine_line|#define IRQ_GPIO_STORK_PCMCIA_B_CARD_DETECT&t;IRQ_GPIO21   /* PCMCIA_B_CARD_DETECT - input */
DECL|macro|IRQ_GPIO_STORK_SWITCH_1
mdefine_line|#define IRQ_GPIO_STORK_SWITCH_1&t;&t;&t;IRQ_GPIO0    /* Switch 1 - input - active low */
DECL|macro|IRQ_GPIO_STORK_SWITCH_2
mdefine_line|#define IRQ_GPIO_STORK_SWITCH_2&t;&t;&t;IRQ_GPIO1    /* Switch 2 - input - active low */
DECL|macro|IRQ_GPIO_STORK_SWITCH_EXTRA_IRQ
mdefine_line|#define IRQ_GPIO_STORK_SWITCH_EXTRA_IRQ&t;&t;IRQ_GPIO24   /* Extra IRQ from switch detect logic - input - active low  */
DECL|macro|IRQ_GPIO_STORK_SWITCH_IRQ
mdefine_line|#define IRQ_GPIO_STORK_SWITCH_IRQ&t;&t;IRQ_GPIO25   /* Switch irq - input- active low  */
DECL|macro|IRQ_GPIO_STORK_BATTERY_LOW_IRQ
mdefine_line|#define IRQ_GPIO_STORK_BATTERY_LOW_IRQ&t;&t;IRQ_GPIO26   /* BATTERY_LOW_IRQ - input - active low */
DECL|macro|IRQ_GPIO_STORK_TOUCH_SCREEN_PEN_IRQ
mdefine_line|#define IRQ_GPIO_STORK_TOUCH_SCREEN_PEN_IRQ&t;IRQ_GPIO27   /* TOUCH_SCREEN_PEN_IRQ -input - goes low when it happens */
multiline_comment|/* this may be bogus - no it&squot;s not the RDY line becomes the IRQ line when we&squot;re up as an IO device */
DECL|macro|IRQ_GPIO_STORK_PCMCIA_A_RDY
mdefine_line|#define IRQ_GPIO_STORK_PCMCIA_A_RDY&t;&t;IRQ_GPIO22   /* PCMCIA_A_RDY - input */
DECL|macro|IRQ_GPIO_STORK_PCMCIA_B_RDY
mdefine_line|#define IRQ_GPIO_STORK_PCMCIA_B_RDY&t;&t;IRQ_GPIO23   /* PCMCIA_B_RDY - input */
multiline_comment|/* the default outputs, others are optional - I&squot;ll set these in the bootldr for now */
DECL|macro|GPIO_STORK_OUTPUT_BITS
mdefine_line|#define GPIO_STORK_OUTPUT_BITS (GPIO_STORK_RS232_ON | GPIO_STORK_PSU_SYNC_MODE | GPIO_STORK_L3_MODE)
DECL|macro|STORK_LATCH_A_ADDR
mdefine_line|#define STORK_LATCH_A_ADDR&t;&t;0x08000000  /* cs1 A5 = 0 */
DECL|macro|STORK_LATCH_B_ADDR
mdefine_line|#define STORK_LATCH_B_ADDR&t;&t;0x08000020  /* cs1 A5 = 1 */
DECL|macro|STORK_LCDCPLD_BASE_ADDR
mdefine_line|#define STORK_LCDCPLD_BASE_ADDR&t;&t;0x10000000  /* cs2 A5 = 0 */
multiline_comment|/* bit defs for latch A - these are write only and will need to be mirrored!  */
DECL|macro|STORK_TEMP_IC_POWER_ON
mdefine_line|#define STORK_TEMP_IC_POWER_ON&t;&t;(1 &lt;&lt; 0)
DECL|macro|STORK_SED1386_POWER_ON
mdefine_line|#define STORK_SED1386_POWER_ON&t;&t;(1 &lt;&lt; 1)
DECL|macro|STORK_LCD_3V3_POWER_ON
mdefine_line|#define STORK_LCD_3V3_POWER_ON&t;&t;(1 &lt;&lt; 2)
DECL|macro|STORK_LCD_5V_POWER_ON
mdefine_line|#define STORK_LCD_5V_POWER_ON&t;&t;(1 &lt;&lt; 3)
DECL|macro|STORK_LCD_BACKLIGHT_INVERTER_ON
mdefine_line|#define STORK_LCD_BACKLIGHT_INVERTER_ON&t;(1 &lt;&lt; 4)
DECL|macro|STORK_PCMCIA_PULL_UPS_POWER_ON
mdefine_line|#define STORK_PCMCIA_PULL_UPS_POWER_ON&t;(1 &lt;&lt; 5)
DECL|macro|STORK_PCMCIA_A_POWER_ON
mdefine_line|#define STORK_PCMCIA_A_POWER_ON&t;&t;(1 &lt;&lt; 6)
DECL|macro|STORK_PCMCIA_B_POWER_ON
mdefine_line|#define STORK_PCMCIA_B_POWER_ON&t;&t;(1 &lt;&lt; 7)
DECL|macro|STORK_AUDIO_POWER_ON
mdefine_line|#define STORK_AUDIO_POWER_ON&t;&t;(1 &lt;&lt; 8)
DECL|macro|STORK_AUDIO_AMP_ON
mdefine_line|#define STORK_AUDIO_AMP_ON&t;&t;(1 &lt;&lt; 9)
DECL|macro|STORK_BAR_CODE_POWER_ON
mdefine_line|#define STORK_BAR_CODE_POWER_ON&t;&t;(1 &lt;&lt; 10)
DECL|macro|STORK_BATTERY_CHARGER_ON
mdefine_line|#define STORK_BATTERY_CHARGER_ON&t;(1 &lt;&lt; 11)
DECL|macro|STORK_SED1386_RESET
mdefine_line|#define STORK_SED1386_RESET&t;&t;(1 &lt;&lt; 12)
DECL|macro|STORK_IRDA_FREQUENCY_SELECT
mdefine_line|#define STORK_IRDA_FREQUENCY_SELECT&t;(1 &lt;&lt; 13)
DECL|macro|STORK_IRDA_MODE_0
mdefine_line|#define STORK_IRDA_MODE_0&t;&t;(1 &lt;&lt; 14)
DECL|macro|STORK_IRDA_MODE_1
mdefine_line|#define STORK_IRDA_MODE_1&t;&t;(1 &lt;&lt; 15)
multiline_comment|/* and for B */
DECL|macro|STORK_AUX_AD_SEL_0
mdefine_line|#define STORK_AUX_AD_SEL_0&t;&t;(1 &lt;&lt; 0)
DECL|macro|STORK_AUX_AD_SEL_1
mdefine_line|#define STORK_AUX_AD_SEL_1&t;&t;(1 &lt;&lt; 1)
DECL|macro|STORK_TOUCH_SCREEN_DCLK
mdefine_line|#define STORK_TOUCH_SCREEN_DCLK&t;&t;(1 &lt;&lt; 2)
DECL|macro|STORK_TOUCH_SCREEN_DIN
mdefine_line|#define STORK_TOUCH_SCREEN_DIN&t;&t;(1 &lt;&lt; 3)
DECL|macro|STORK_TOUCH_SCREEN_CS
mdefine_line|#define STORK_TOUCH_SCREEN_CS&t;&t;(1 &lt;&lt; 4)
DECL|macro|STORK_DA_CS
mdefine_line|#define STORK_DA_CS&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|STORK_DA_LD
mdefine_line|#define STORK_DA_LD&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|STORK_RED_LED
mdefine_line|#define STORK_RED_LED&t;&t;&t;(1 &lt;&lt; 7)&t;/* active LOW */
DECL|macro|STORK_GREEN_LED
mdefine_line|#define STORK_GREEN_LED&t;&t;&t;(1 &lt;&lt; 8)&t;/* active LOW */
DECL|macro|STORK_YELLOW_LED
mdefine_line|#define STORK_YELLOW_LED&t;&t;(1 &lt;&lt; 9)&t;/* active LOW */
DECL|macro|STORK_PCMCIA_B_RESET
mdefine_line|#define STORK_PCMCIA_B_RESET&t;&t;(1 &lt;&lt; 10)
DECL|macro|STORK_PCMCIA_A_RESET
mdefine_line|#define STORK_PCMCIA_A_RESET&t;&t;(1 &lt;&lt; 11)
DECL|macro|STORK_AUDIO_CODEC_RESET
mdefine_line|#define STORK_AUDIO_CODEC_RESET&t;&t;(1 &lt;&lt; 12)
DECL|macro|STORK_CODEC_QMUTE
mdefine_line|#define STORK_CODEC_QMUTE&t;&t;(1 &lt;&lt; 13)
DECL|macro|STORK_AUDIO_CLOCK_SEL0
mdefine_line|#define STORK_AUDIO_CLOCK_SEL0&t;&t;(1 &lt;&lt; 14)
DECL|macro|STORK_AUDIO_CLOCK_SEL1
mdefine_line|#define STORK_AUDIO_CLOCK_SEL1&t;&t;(1 &lt;&lt; 15)
multiline_comment|/*&n;&n;    There are 8 control bits in the touch screen controller (AD7873)&n;&n;    S A2 A1 A0 MODE SER/DFR# PD1 PD0&n;&n;    S &t;&t;Start bit, always one.&n;    A2 - A0&t;Channel select bits&n;    MODE&t;0 =&gt; 12 bit resolution, 1 =&gt; 8 bit&n;    SER/DFR#&t;Single ender/Differential Reference Select bit&n;    PD1, PD0&t;Power management bits (usually 10)&n;&n;&n;From Table 1.&n;&n;&t;A2-A0&n;&n;  &t;0 Temp0 (SER must be 1)&n;&t;1 X+ (is this a typo? - is this X- really?)&n;&t;2 VBAT,&n;&t;3 read X+ (Z1),&n;&t;4 read Y- (Z2), 5 =&gt; read Y+,&n;&n;*/
DECL|macro|AD7873_START
mdefine_line|#define AD7873_START&t;&t;0x80&t;&t;/* all commands need this to be set */
DECL|macro|AD7873_ADDR_BITS
mdefine_line|#define AD7873_ADDR_BITS&t;4&t;&t;/* ie shift by this */
DECL|macro|AD7873_8BITMODE
mdefine_line|#define AD7873_8BITMODE&t;&t;0x08&t;&t;/* 0 =&gt; 12 bit convertions */
DECL|macro|AD7873_SER_DFR
mdefine_line|#define AD7873_SER_DFR&t;&t;0x04
DECL|macro|AD7873_PD1
mdefine_line|#define AD7873_PD1&t;&t;0x02
DECL|macro|AD7873_PD0
mdefine_line|#define AD7873_PD0&t;&t;0x01
DECL|macro|AD7873_TEMP0
mdefine_line|#define AD7873_TEMP0&t;&t;AD7873_SER_DFR
DECL|macro|AD7873_X
mdefine_line|#define AD7873_X&t;&t;(1 &lt;&lt; AD7873_ADDR_BITS)
DECL|macro|AD7873_VBAT
mdefine_line|#define AD7873_VBAT&t;&t;((2 &lt;&lt; AD7873_ADDR_BITS) | AD7873_SER_DFR)
DECL|macro|AD7873_X_Z1
mdefine_line|#define AD7873_X_Z1&t;&t;(3 &lt;&lt; AD7873_ADDR_BITS)
DECL|macro|AD7873_Y_Z2
mdefine_line|#define AD7873_Y_Z2&t;&t;(4 &lt;&lt; AD7873_ADDR_BITS)
DECL|macro|AD7873_Y
mdefine_line|#define AD7873_Y&t;&t;(5 &lt;&lt; AD7873_ADDR_BITS)
DECL|macro|AD7873_AUX
mdefine_line|#define AD7873_AUX&t;&t;((6 &lt;&lt; AD7873_ADDR_BITS) | AD7873_SER_DFR)
DECL|macro|AD7873_TEMP1
mdefine_line|#define AD7873_TEMP1&t;&t;((7 &lt;&lt; AD7873_ADDR_BITS) | AD7873_SER_DFR)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
id|storkSetLatchA
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|storkClearLatchA
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|storkSetLatchB
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|storkClearLatchB
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|storkSetLCDCPLD
c_func
(paren
r_int
id|which
comma
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|storkClearLCDCPLD
c_func
(paren
r_int
id|which
comma
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_void
id|storkSetGPIO
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_void
id|storkClearGPIO
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
r_extern
r_int
id|storkGetGPIO
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|storkClockShortToDtoA
c_func
(paren
r_int
id|word
)paren
suffix:semicolon
r_extern
r_int
id|storkClockByteToTS
c_func
(paren
r_int
id|byte
)paren
suffix:semicolon
multiline_comment|/* this will return the current state of the hardware ANDED with the given bits&n;   so NE =&gt; at least one bit was set, but maybe not all of them! */
r_extern
r_int
id|storkTestGPIO
c_func
(paren
r_int
id|bits
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
