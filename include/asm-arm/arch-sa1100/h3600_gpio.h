multiline_comment|/*&n; *&n; * Definitions for H3600 Handheld Computer&n; *&n; * Copyright 2000 Compaq Computer Corporation.&n; *&n; * Use consistent with the GNU GPL is permitted,&n; * provided that this copyright notice is&n; * preserved in its entirety in all copies and derived works.&n; *&n; * COMPAQ COMPUTER CORPORATION MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n; * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n; * FITNESS FOR ANY PARTICULAR PURPOSE.&n; *&n; * Author: Jamey Hicks.&n; *&n; * History:&n; *&n; * 2001-10-??   Andrew Christian   Added support for iPAQ H3800&n; *&n; */
macro_line|#ifndef _INCLUDE_H3600_GPIO_H_
DECL|macro|_INCLUDE_H3600_GPIO_H_
mdefine_line|#define _INCLUDE_H3600_GPIO_H_
multiline_comment|/*&n; * GPIO lines that are common across ALL iPAQ models are in &quot;h3600.h&quot;&n; * This file contains machine-specific definitions&n; */
DECL|macro|GPIO_H3600_SUSPEND
mdefine_line|#define GPIO_H3600_SUSPEND              GPIO_GPIO (0)
multiline_comment|/* GPIO[2:9] used by LCD on H3600/3800, used as GPIO on H3100 */
DECL|macro|GPIO_H3100_BT_ON
mdefine_line|#define GPIO_H3100_BT_ON&t;&t;GPIO_GPIO (2)
DECL|macro|GPIO_H3100_GPIO3
mdefine_line|#define GPIO_H3100_GPIO3&t;&t;GPIO_GPIO (3)
DECL|macro|GPIO_H3100_QMUTE
mdefine_line|#define GPIO_H3100_QMUTE&t;&t;GPIO_GPIO (4)
DECL|macro|GPIO_H3100_LCD_3V_ON
mdefine_line|#define GPIO_H3100_LCD_3V_ON&t;&t;GPIO_GPIO (5)
DECL|macro|GPIO_H3100_AUD_ON
mdefine_line|#define GPIO_H3100_AUD_ON&t;&t;GPIO_GPIO (6)
DECL|macro|GPIO_H3100_AUD_PWR_ON
mdefine_line|#define GPIO_H3100_AUD_PWR_ON&t;&t;GPIO_GPIO (7)
DECL|macro|GPIO_H3100_IR_ON
mdefine_line|#define GPIO_H3100_IR_ON&t;&t;GPIO_GPIO (8)
DECL|macro|GPIO_H3100_IR_FSEL
mdefine_line|#define GPIO_H3100_IR_FSEL&t;&t;GPIO_GPIO (9)
multiline_comment|/* for H3600, audio sample rate clock generator */
DECL|macro|GPIO_H3600_CLK_SET0
mdefine_line|#define GPIO_H3600_CLK_SET0&t;&t;GPIO_GPIO (12)
DECL|macro|GPIO_H3600_CLK_SET1
mdefine_line|#define GPIO_H3600_CLK_SET1&t;&t;GPIO_GPIO (13)
DECL|macro|GPIO_H3600_ACTION_BUTTON
mdefine_line|#define GPIO_H3600_ACTION_BUTTON&t;GPIO_GPIO (18)
DECL|macro|GPIO_H3600_SOFT_RESET
mdefine_line|#define GPIO_H3600_SOFT_RESET           GPIO_GPIO (20)   /* Also known as BATT_FAULT */
DECL|macro|GPIO_H3600_OPT_LOCK
mdefine_line|#define GPIO_H3600_OPT_LOCK&t;&t;GPIO_GPIO (22)
DECL|macro|GPIO_H3600_OPT_DET
mdefine_line|#define GPIO_H3600_OPT_DET&t;&t;GPIO_GPIO (27)
multiline_comment|/* H3800 specific pins */
DECL|macro|GPIO_H3800_AC_IN
mdefine_line|#define GPIO_H3800_AC_IN                GPIO_GPIO (12)
DECL|macro|GPIO_H3800_COM_DSR
mdefine_line|#define GPIO_H3800_COM_DSR              GPIO_GPIO (13)
DECL|macro|GPIO_H3800_MMC_INT
mdefine_line|#define GPIO_H3800_MMC_INT              GPIO_GPIO (18)
DECL|macro|GPIO_H3800_NOPT_IND
mdefine_line|#define GPIO_H3800_NOPT_IND             GPIO_GPIO (20)   /* Almost exactly the same as GPIO_H3600_OPT_DET */
DECL|macro|GPIO_H3800_OPT_BAT_FAULT
mdefine_line|#define GPIO_H3800_OPT_BAT_FAULT        GPIO_GPIO (22)
DECL|macro|GPIO_H3800_CLK_OUT
mdefine_line|#define GPIO_H3800_CLK_OUT              GPIO_GPIO (27)
multiline_comment|/****************************************************/
DECL|macro|IRQ_GPIO_H3600_ACTION_BUTTON
mdefine_line|#define IRQ_GPIO_H3600_ACTION_BUTTON    IRQ_GPIO18
DECL|macro|IRQ_GPIO_H3600_OPT_DET
mdefine_line|#define IRQ_GPIO_H3600_OPT_DET&t;&t;IRQ_GPIO27
DECL|macro|IRQ_GPIO_H3800_MMC_INT
mdefine_line|#define IRQ_GPIO_H3800_MMC_INT          IRQ_GPIO18
DECL|macro|IRQ_GPIO_H3800_NOPT_IND
mdefine_line|#define IRQ_GPIO_H3800_NOPT_IND         IRQ_GPIO20 /* almost same as OPT_DET */
multiline_comment|/* H3100 / 3600 EGPIO pins */
DECL|macro|EGPIO_H3600_VPP_ON
mdefine_line|#define EGPIO_H3600_VPP_ON&t;&t;(1 &lt;&lt; 0)
DECL|macro|EGPIO_H3600_CARD_RESET
mdefine_line|#define EGPIO_H3600_CARD_RESET&t;&t;(1 &lt;&lt; 1)   /* reset the attached pcmcia/compactflash card.  active high. */
DECL|macro|EGPIO_H3600_OPT_RESET
mdefine_line|#define EGPIO_H3600_OPT_RESET&t;&t;(1 &lt;&lt; 2)   /* reset the attached option pack.  active high. */
DECL|macro|EGPIO_H3600_CODEC_NRESET
mdefine_line|#define EGPIO_H3600_CODEC_NRESET&t;(1 &lt;&lt; 3)   /* reset the onboard UDA1341.  active low. */
DECL|macro|EGPIO_H3600_OPT_NVRAM_ON
mdefine_line|#define EGPIO_H3600_OPT_NVRAM_ON&t;(1 &lt;&lt; 4)   /* apply power to optionpack nvram, active high. */
DECL|macro|EGPIO_H3600_OPT_ON
mdefine_line|#define EGPIO_H3600_OPT_ON&t;&t;(1 &lt;&lt; 5)   /* full power to option pack.  active high. */
DECL|macro|EGPIO_H3600_LCD_ON
mdefine_line|#define EGPIO_H3600_LCD_ON&t;&t;(1 &lt;&lt; 6)   /* enable 3.3V to LCD.  active high. */
DECL|macro|EGPIO_H3600_RS232_ON
mdefine_line|#define EGPIO_H3600_RS232_ON&t;&t;(1 &lt;&lt; 7)   /* UART3 transceiver force on.  Active high. */
multiline_comment|/* H3600 only EGPIO pins */
DECL|macro|EGPIO_H3600_LCD_PCI
mdefine_line|#define EGPIO_H3600_LCD_PCI&t;&t;(1 &lt;&lt; 8)   /* LCD control IC enable.  active high. */
DECL|macro|EGPIO_H3600_IR_ON
mdefine_line|#define EGPIO_H3600_IR_ON&t;&t;(1 &lt;&lt; 9)   /* apply power to IR module.  active high. */
DECL|macro|EGPIO_H3600_AUD_AMP_ON
mdefine_line|#define EGPIO_H3600_AUD_AMP_ON&t;&t;(1 &lt;&lt; 10)  /* apply power to audio power amp.  active high. */
DECL|macro|EGPIO_H3600_AUD_PWR_ON
mdefine_line|#define EGPIO_H3600_AUD_PWR_ON&t;&t;(1 &lt;&lt; 11)  /* apply power to reset of audio circuit.  active high. */
DECL|macro|EGPIO_H3600_QMUTE
mdefine_line|#define EGPIO_H3600_QMUTE&t;&t;(1 &lt;&lt; 12)  /* mute control for onboard UDA1341.  active high. */
DECL|macro|EGPIO_H3600_IR_FSEL
mdefine_line|#define EGPIO_H3600_IR_FSEL&t;&t;(1 &lt;&lt; 13)  /* IR speed select: 1-&gt;fast, 0-&gt;slow */
DECL|macro|EGPIO_H3600_LCD_5V_ON
mdefine_line|#define EGPIO_H3600_LCD_5V_ON&t;&t;(1 &lt;&lt; 14)  /* enable 5V to LCD. active high. */
DECL|macro|EGPIO_H3600_LVDD_ON
mdefine_line|#define EGPIO_H3600_LVDD_ON&t;&t;(1 &lt;&lt; 15)  /* enable 9V and -6.5V to LCD. */
multiline_comment|/********************* H3800, ASIC #2 ********************/
DECL|macro|_H3800_ASIC2_Base
mdefine_line|#define _H3800_ASIC2_Base            (H3600_EGPIO_VIRT)
DECL|macro|H3800_ASIC2_OFFSET
mdefine_line|#define H3800_ASIC2_OFFSET(s,x,y)    &bslash;&n;    (*((volatile s *) (_H3800_ASIC2_Base + _H3800_ASIC2_ ## x ## _Base + _H3800_ASIC2_ ## x ## _ ## y)))
DECL|macro|H3800_ASIC2_NOFFSET
mdefine_line|#define H3800_ASIC2_NOFFSET(s,x,n,y) &bslash;&n;    (*((volatile s *) (_H3800_ASIC2_Base + _H3800_ASIC2_ ## x ## _ ## n ## _Base + _H3800_ASIC2_ ## x ## _ ## y)))
DECL|macro|_H3800_ASIC2_GPIO_Base
mdefine_line|#define _H3800_ASIC2_GPIO_Base                 0x0000
DECL|macro|_H3800_ASIC2_GPIO_Direction
mdefine_line|#define _H3800_ASIC2_GPIO_Direction            0x0000    /* R/W, 16 bits 1:input, 0:output */
DECL|macro|_H3800_ASIC2_GPIO_InterruptType
mdefine_line|#define _H3800_ASIC2_GPIO_InterruptType        0x0004    /* R/W, 12 bits 1:edge, 0:level          */
DECL|macro|_H3800_ASIC2_GPIO_InterruptEdgeType
mdefine_line|#define _H3800_ASIC2_GPIO_InterruptEdgeType    0x0008    /* R/W, 12 bits 1:rising, 0:falling */
DECL|macro|_H3800_ASIC2_GPIO_InterruptLevelType
mdefine_line|#define _H3800_ASIC2_GPIO_InterruptLevelType   0x000C    /* R/W, 12 bits 1:high, 0:low  */
DECL|macro|_H3800_ASIC2_GPIO_InterruptClear
mdefine_line|#define _H3800_ASIC2_GPIO_InterruptClear       0x0010    /* W,   12 bits */
DECL|macro|_H3800_ASIC2_GPIO_InterruptFlag
mdefine_line|#define _H3800_ASIC2_GPIO_InterruptFlag        0x0010    /* R,   12 bits - reads int status */
DECL|macro|_H3800_ASIC2_GPIO_Data
mdefine_line|#define _H3800_ASIC2_GPIO_Data                 0x0014    /* R/W, 16 bits */
DECL|macro|_H3800_ASIC2_GPIO_BattFaultOut
mdefine_line|#define _H3800_ASIC2_GPIO_BattFaultOut         0x0018    /* R/W, 16 bit - sets level on batt fault */
DECL|macro|_H3800_ASIC2_GPIO_InterruptEnable
mdefine_line|#define _H3800_ASIC2_GPIO_InterruptEnable      0x001c    /* R/W, 12 bits 1:enable interrupt */
DECL|macro|_H3800_ASIC2_GPIO_Alternate
mdefine_line|#define _H3800_ASIC2_GPIO_Alternate            0x003c    /* R/W, 12+1 bits - set alternate functions */
DECL|macro|H3800_ASIC2_GPIO_Direction
mdefine_line|#define H3800_ASIC2_GPIO_Direction          H3800_ASIC2_OFFSET( u16, GPIO, Direction )
DECL|macro|H3800_ASIC2_GPIO_InterruptType
mdefine_line|#define H3800_ASIC2_GPIO_InterruptType      H3800_ASIC2_OFFSET( u16, GPIO, InterruptType )
DECL|macro|H3800_ASIC2_GPIO_InterruptEdgeType
mdefine_line|#define H3800_ASIC2_GPIO_InterruptEdgeType  H3800_ASIC2_OFFSET( u16, GPIO, InterruptEdgeType )
DECL|macro|H3800_ASIC2_GPIO_InterruptLevelType
mdefine_line|#define H3800_ASIC2_GPIO_InterruptLevelType H3800_ASIC2_OFFSET( u16, GPIO, InterruptLevelType )
DECL|macro|H3800_ASIC2_GPIO_InterruptClear
mdefine_line|#define H3800_ASIC2_GPIO_InterruptClear     H3800_ASIC2_OFFSET( u16, GPIO, InterruptClear )
DECL|macro|H3800_ASIC2_GPIO_InterruptFlag
mdefine_line|#define H3800_ASIC2_GPIO_InterruptFlag      H3800_ASIC2_OFFSET( u16, GPIO, InterruptFlag )
DECL|macro|H3800_ASIC2_GPIO_Data
mdefine_line|#define H3800_ASIC2_GPIO_Data               H3800_ASIC2_OFFSET( u16, GPIO, Data )
DECL|macro|H3800_ASIC2_GPIO_BattFaultOut
mdefine_line|#define H3800_ASIC2_GPIO_BattFaultOut       H3800_ASIC2_OFFSET( u16, GPIO, BattFaultOut )
DECL|macro|H3800_ASIC2_GPIO_InterruptEnable
mdefine_line|#define H3800_ASIC2_GPIO_InterruptEnable    H3800_ASIC2_OFFSET( u16, GPIO, InterruptEnable )
DECL|macro|H3800_ASIC2_GPIO_Alternate
mdefine_line|#define H3800_ASIC2_GPIO_Alternate          H3800_ASIC2_OFFSET( u16, GPIO, Alternate )
DECL|macro|GPIO_H3800_ASIC2_IN_Y1_N
mdefine_line|#define GPIO_H3800_ASIC2_IN_Y1_N          (1 &lt;&lt; 0)   /* Output: Touchscreen Y1 */
DECL|macro|GPIO_H3800_ASIC2_IN_X0
mdefine_line|#define GPIO_H3800_ASIC2_IN_X0            (1 &lt;&lt; 1)   /* Output: Touchscreen X0 */
DECL|macro|GPIO_H3800_ASIC2_IN_Y0
mdefine_line|#define GPIO_H3800_ASIC2_IN_Y0            (1 &lt;&lt; 2)   /* Output: Touchscreen Y0 */
DECL|macro|GPIO_H3800_ASIC2_IN_X1_N
mdefine_line|#define GPIO_H3800_ASIC2_IN_X1_N          (1 &lt;&lt; 3)   /* Output: Touchscreen X1 */
DECL|macro|GPIO_H3800_ASIC2_BT_RST
mdefine_line|#define GPIO_H3800_ASIC2_BT_RST           (1 &lt;&lt; 4)   /* Output: Bluetooth reset */
DECL|macro|GPIO_H3800_ASIC2_PEN_IRQ
mdefine_line|#define GPIO_H3800_ASIC2_PEN_IRQ          (1 &lt;&lt; 5)   /* Input : Pen down        */
DECL|macro|GPIO_H3800_ASIC2_SD_DETECT
mdefine_line|#define GPIO_H3800_ASIC2_SD_DETECT        (1 &lt;&lt; 6)   /* Input : SD detect */
DECL|macro|GPIO_H3800_ASIC2_EAR_IN_N
mdefine_line|#define GPIO_H3800_ASIC2_EAR_IN_N         (1 &lt;&lt; 7)   /* Input : Audio jack plug inserted */
DECL|macro|GPIO_H3800_ASIC2_OPT_PCM_RESET
mdefine_line|#define GPIO_H3800_ASIC2_OPT_PCM_RESET    (1 &lt;&lt; 8)   /* Output: */
DECL|macro|GPIO_H3800_ASIC2_OPT_RESET
mdefine_line|#define GPIO_H3800_ASIC2_OPT_RESET        (1 &lt;&lt; 9)   /* Output: */
DECL|macro|GPIO_H3800_ASIC2_USB_DETECT_N
mdefine_line|#define GPIO_H3800_ASIC2_USB_DETECT_N     (1 &lt;&lt; 10)  /* Input : */
DECL|macro|GPIO_H3800_ASIC2_SD_CON_SLT
mdefine_line|#define GPIO_H3800_ASIC2_SD_CON_SLT       (1 &lt;&lt; 11)  /* Input : */
DECL|macro|_H3800_ASIC2_KPIO_Base
mdefine_line|#define _H3800_ASIC2_KPIO_Base                 0x0200
DECL|macro|_H3800_ASIC2_KPIO_Direction
mdefine_line|#define _H3800_ASIC2_KPIO_Direction            0x0000    /* R/W, 12 bits 1:input, 0:output */
DECL|macro|_H3800_ASIC2_KPIO_InterruptType
mdefine_line|#define _H3800_ASIC2_KPIO_InterruptType        0x0004    /* R/W, 12 bits 1:edge, 0:level          */
DECL|macro|_H3800_ASIC2_KPIO_InterruptEdgeType
mdefine_line|#define _H3800_ASIC2_KPIO_InterruptEdgeType    0x0008    /* R/W, 12 bits 1:rising, 0:falling */
DECL|macro|_H3800_ASIC2_KPIO_InterruptLevelType
mdefine_line|#define _H3800_ASIC2_KPIO_InterruptLevelType   0x000C    /* R/W, 12 bits 1:high, 0:low  */
DECL|macro|_H3800_ASIC2_KPIO_InterruptClear
mdefine_line|#define _H3800_ASIC2_KPIO_InterruptClear       0x0010    /* W,   20 bits - 8 special */
DECL|macro|_H3800_ASIC2_KPIO_InterruptFlag
mdefine_line|#define _H3800_ASIC2_KPIO_InterruptFlag        0x0010    /* R,   20 bits - 8 special - reads int status */
DECL|macro|_H3800_ASIC2_KPIO_Data
mdefine_line|#define _H3800_ASIC2_KPIO_Data                 0x0014    /* R/W, 16 bits */
DECL|macro|_H3800_ASIC2_KPIO_BattFaultOut
mdefine_line|#define _H3800_ASIC2_KPIO_BattFaultOut         0x0018    /* R/W, 16 bit - sets level on batt fault */
DECL|macro|_H3800_ASIC2_KPIO_InterruptEnable
mdefine_line|#define _H3800_ASIC2_KPIO_InterruptEnable      0x001c    /* R/W, 20 bits - 8 special */
DECL|macro|_H3800_ASIC2_KPIO_Alternate
mdefine_line|#define _H3800_ASIC2_KPIO_Alternate            0x003c    /* R/W, 6 bits */
DECL|macro|H3800_ASIC2_KPIO_Direction
mdefine_line|#define H3800_ASIC2_KPIO_Direction          H3800_ASIC2_OFFSET( u16, KPIO, Direction )
DECL|macro|H3800_ASIC2_KPIO_InterruptType
mdefine_line|#define H3800_ASIC2_KPIO_InterruptType      H3800_ASIC2_OFFSET( u16, KPIO, InterruptType )
DECL|macro|H3800_ASIC2_KPIO_InterruptEdgeType
mdefine_line|#define H3800_ASIC2_KPIO_InterruptEdgeType  H3800_ASIC2_OFFSET( u16, KPIO, InterruptEdgeType )
DECL|macro|H3800_ASIC2_KPIO_InterruptLevelType
mdefine_line|#define H3800_ASIC2_KPIO_InterruptLevelType H3800_ASIC2_OFFSET( u16, KPIO, InterruptLevelType )
DECL|macro|H3800_ASIC2_KPIO_InterruptClear
mdefine_line|#define H3800_ASIC2_KPIO_InterruptClear     H3800_ASIC2_OFFSET( u32, KPIO, InterruptClear )
DECL|macro|H3800_ASIC2_KPIO_InterruptFlag
mdefine_line|#define H3800_ASIC2_KPIO_InterruptFlag      H3800_ASIC2_OFFSET( u32, KPIO, InterruptFlag )
DECL|macro|H3800_ASIC2_KPIO_Data
mdefine_line|#define H3800_ASIC2_KPIO_Data               H3800_ASIC2_OFFSET( u16, KPIO, Data )
DECL|macro|H3800_ASIC2_KPIO_BattFaultOut
mdefine_line|#define H3800_ASIC2_KPIO_BattFaultOut       H3800_ASIC2_OFFSET( u16, KPIO, BattFaultOut )
DECL|macro|H3800_ASIC2_KPIO_InterruptEnable
mdefine_line|#define H3800_ASIC2_KPIO_InterruptEnable    H3800_ASIC2_OFFSET( u32, KPIO, InterruptEnable )
DECL|macro|H3800_ASIC2_KPIO_Alternate
mdefine_line|#define H3800_ASIC2_KPIO_Alternate          H3800_ASIC2_OFFSET( u16, KPIO, Alternate )
DECL|macro|H3800_ASIC2_KPIO_SPI_INT
mdefine_line|#define H3800_ASIC2_KPIO_SPI_INT        ( 1 &lt;&lt; 16 )
DECL|macro|H3800_ASIC2_KPIO_OWM_INT
mdefine_line|#define H3800_ASIC2_KPIO_OWM_INT        ( 1 &lt;&lt; 17 )
DECL|macro|H3800_ASIC2_KPIO_ADC_INT
mdefine_line|#define H3800_ASIC2_KPIO_ADC_INT        ( 1 &lt;&lt; 18 )
DECL|macro|H3800_ASIC2_KPIO_UART_0_INT
mdefine_line|#define H3800_ASIC2_KPIO_UART_0_INT     ( 1 &lt;&lt; 19 )
DECL|macro|H3800_ASIC2_KPIO_UART_1_INT
mdefine_line|#define H3800_ASIC2_KPIO_UART_1_INT     ( 1 &lt;&lt; 20 )
DECL|macro|H3800_ASIC2_KPIO_TIMER_0_INT
mdefine_line|#define H3800_ASIC2_KPIO_TIMER_0_INT    ( 1 &lt;&lt; 21 )
DECL|macro|H3800_ASIC2_KPIO_TIMER_1_INT
mdefine_line|#define H3800_ASIC2_KPIO_TIMER_1_INT    ( 1 &lt;&lt; 22 )
DECL|macro|H3800_ASIC2_KPIO_TIMER_2_INT
mdefine_line|#define H3800_ASIC2_KPIO_TIMER_2_INT    ( 1 &lt;&lt; 23 )
DECL|macro|KPIO_H3800_ASIC2_RECORD_BTN_N
mdefine_line|#define KPIO_H3800_ASIC2_RECORD_BTN_N     (1 &lt;&lt; 0)   /* Record button */
DECL|macro|KPIO_H3800_ASIC2_KEY_5W1_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_5W1_N        (1 &lt;&lt; 1)   /* Keypad */
DECL|macro|KPIO_H3800_ASIC2_KEY_5W2_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_5W2_N        (1 &lt;&lt; 2)   /* */
DECL|macro|KPIO_H3800_ASIC2_KEY_5W3_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_5W3_N        (1 &lt;&lt; 3)   /* */
DECL|macro|KPIO_H3800_ASIC2_KEY_5W4_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_5W4_N        (1 &lt;&lt; 4)   /* */
DECL|macro|KPIO_H3800_ASIC2_KEY_5W5_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_5W5_N        (1 &lt;&lt; 5)   /* */
DECL|macro|KPIO_H3800_ASIC2_KEY_LEFT_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_LEFT_N       (1 &lt;&lt; 6)   /* */
DECL|macro|KPIO_H3800_ASIC2_KEY_RIGHT_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_RIGHT_N      (1 &lt;&lt; 7)   /* */
DECL|macro|KPIO_H3800_ASIC2_KEY_AP1_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_AP1_N        (1 &lt;&lt; 8)   /* Old &quot;Calendar&quot; */
DECL|macro|KPIO_H3800_ASIC2_KEY_AP2_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_AP2_N        (1 &lt;&lt; 9)   /* Old &quot;Schedule&quot; */
DECL|macro|KPIO_H3800_ASIC2_KEY_AP3_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_AP3_N        (1 &lt;&lt; 10)  /* Old &quot;Q&quot;        */
DECL|macro|KPIO_H3800_ASIC2_KEY_AP4_N
mdefine_line|#define KPIO_H3800_ASIC2_KEY_AP4_N        (1 &lt;&lt; 11)  /* Old &quot;Undo&quot;     */
multiline_comment|/* Alternate KPIO functions (set by default) */
DECL|macro|KPIO_ALT_H3800_ASIC2_KEY_5W1_N
mdefine_line|#define KPIO_ALT_H3800_ASIC2_KEY_5W1_N        (1 &lt;&lt; 1)   /* Action key */
DECL|macro|KPIO_ALT_H3800_ASIC2_KEY_5W2_N
mdefine_line|#define KPIO_ALT_H3800_ASIC2_KEY_5W2_N        (1 &lt;&lt; 2)   /* J1 of keypad input */
DECL|macro|KPIO_ALT_H3800_ASIC2_KEY_5W3_N
mdefine_line|#define KPIO_ALT_H3800_ASIC2_KEY_5W3_N        (1 &lt;&lt; 3)   /* J2 of keypad input */
DECL|macro|KPIO_ALT_H3800_ASIC2_KEY_5W4_N
mdefine_line|#define KPIO_ALT_H3800_ASIC2_KEY_5W4_N        (1 &lt;&lt; 4)   /* J3 of keypad input */
DECL|macro|KPIO_ALT_H3800_ASIC2_KEY_5W5_N
mdefine_line|#define KPIO_ALT_H3800_ASIC2_KEY_5W5_N        (1 &lt;&lt; 5)   /* J4 of keypad input */
DECL|macro|_H3800_ASIC2_SPI_Base
mdefine_line|#define _H3800_ASIC2_SPI_Base                  0x0400
DECL|macro|_H3800_ASIC2_SPI_Control
mdefine_line|#define _H3800_ASIC2_SPI_Control               0x0000    /* R/W 8 bits */
DECL|macro|_H3800_ASIC2_SPI_Data
mdefine_line|#define _H3800_ASIC2_SPI_Data                  0x0004    /* R/W 8 bits */
DECL|macro|_H3800_ASIC2_SPI_ChipSelectDisabled
mdefine_line|#define _H3800_ASIC2_SPI_ChipSelectDisabled    0x0008    /* W   8 bits */
DECL|macro|H3800_ASIC2_SPI_Control
mdefine_line|#define H3800_ASIC2_SPI_Control             H3800_ASIC2_OFFSET( u8, SPI, Control )
DECL|macro|H3800_ASIC2_SPI_Data
mdefine_line|#define H3800_ASIC2_SPI_Data                H3800_ASIC2_OFFSET( u8, SPI, Data )
DECL|macro|H3800_ASIC2_SPI_ChipSelectDisabled
mdefine_line|#define H3800_ASIC2_SPI_ChipSelectDisabled  H3800_ASIC2_OFFSET( u8, SPI, ChipSelectDisabled )
DECL|macro|_H3800_ASIC2_PWM_0_Base
mdefine_line|#define _H3800_ASIC2_PWM_0_Base                0x0600
DECL|macro|_H3800_ASIC2_PWM_1_Base
mdefine_line|#define _H3800_ASIC2_PWM_1_Base                0x0700
DECL|macro|_H3800_ASIC2_PWM_TimeBase
mdefine_line|#define _H3800_ASIC2_PWM_TimeBase              0x0000    /* R/W 6 bits */
DECL|macro|_H3800_ASIC2_PWM_PeriodTime
mdefine_line|#define _H3800_ASIC2_PWM_PeriodTime            0x0004    /* R/W 12 bits */
DECL|macro|_H3800_ASIC2_PWM_DutyTime
mdefine_line|#define _H3800_ASIC2_PWM_DutyTime              0x0008    /* R/W 12 bits */
DECL|macro|H3800_ASIC2_PWM_0_TimeBase
mdefine_line|#define H3800_ASIC2_PWM_0_TimeBase          H3800_ASIC2_NOFFSET(  u8, PWM, 0, TimeBase )
DECL|macro|H3800_ASIC2_PWM_0_PeriodTime
mdefine_line|#define H3800_ASIC2_PWM_0_PeriodTime        H3800_ASIC2_NOFFSET( u16, PWM, 0, PeriodTime )
DECL|macro|H3800_ASIC2_PWM_0_DutyTime
mdefine_line|#define H3800_ASIC2_PWM_0_DutyTime          H3800_ASIC2_NOFFSET( u16, PWM, 0, DutyTime )
DECL|macro|H3800_ASIC2_PWM_1_TimeBase
mdefine_line|#define H3800_ASIC2_PWM_1_TimeBase          H3800_ASIC2_NOFFSET(  u8, PWM, 1, TimeBase )
DECL|macro|H3800_ASIC2_PWM_1_PeriodTime
mdefine_line|#define H3800_ASIC2_PWM_1_PeriodTime        H3800_ASIC2_NOFFSET( u16, PWM, 1, PeriodTime )
DECL|macro|H3800_ASIC2_PWM_1_DutyTime
mdefine_line|#define H3800_ASIC2_PWM_1_DutyTime          H3800_ASIC2_NOFFSET( u16, PWM, 1, DutyTime )
DECL|macro|H3800_ASIC2_PWM_TIMEBASE_MASK
mdefine_line|#define H3800_ASIC2_PWM_TIMEBASE_MASK             0xf    /* Low 4 bits sets time base, max = 8 */
DECL|macro|H3800_ASIC2_PWM_TIMEBASE_ENABLE
mdefine_line|#define H3800_ASIC2_PWM_TIMEBASE_ENABLE    ( 1 &lt;&lt; 4 )    /* Enable clock */
DECL|macro|H3800_ASIC2_PWM_TIMEBASE_CLEAR
mdefine_line|#define H3800_ASIC2_PWM_TIMEBASE_CLEAR     ( 1 &lt;&lt; 5 )    /* Clear the PWM */
DECL|macro|_H3800_ASIC2_LED_0_Base
mdefine_line|#define _H3800_ASIC2_LED_0_Base                0x0800
DECL|macro|_H3800_ASIC2_LED_1_Base
mdefine_line|#define _H3800_ASIC2_LED_1_Base                0x0880
DECL|macro|_H3800_ASIC2_LED_2_Base
mdefine_line|#define _H3800_ASIC2_LED_2_Base                0x0900
DECL|macro|_H3800_ASIC2_LED_TimeBase
mdefine_line|#define _H3800_ASIC2_LED_TimeBase              0x0000    /* R/W  7 bits */
DECL|macro|_H3800_ASIC2_LED_PeriodTime
mdefine_line|#define _H3800_ASIC2_LED_PeriodTime            0x0004    /* R/W 12 bits */
DECL|macro|_H3800_ASIC2_LED_DutyTime
mdefine_line|#define _H3800_ASIC2_LED_DutyTime              0x0008    /* R/W 12 bits */
DECL|macro|_H3800_ASIC2_LED_AutoStopCount
mdefine_line|#define _H3800_ASIC2_LED_AutoStopCount         0x000c    /* R/W 16 bits */
DECL|macro|H3800_ASIC2_LED_0_TimeBase
mdefine_line|#define H3800_ASIC2_LED_0_TimeBase          H3800_ASIC2_NOFFSET(  u8, LED, 0, TimeBase )
DECL|macro|H3800_ASIC2_LED_0_PeriodTime
mdefine_line|#define H3800_ASIC2_LED_0_PeriodTime        H3800_ASIC2_NOFFSET( u16, LED, 0, PeriodTime )
DECL|macro|H3800_ASIC2_LED_0_DutyTime
mdefine_line|#define H3800_ASIC2_LED_0_DutyTime          H3800_ASIC2_NOFFSET( u16, LED, 0, DutyTime )
DECL|macro|H3800_ASIC2_LED_0_AutoStopClock
mdefine_line|#define H3800_ASIC2_LED_0_AutoStopClock     H3800_ASIC2_NOFFSET( u16, LED, 0, AutoStopClock )
DECL|macro|H3800_ASIC2_LED_1_TimeBase
mdefine_line|#define H3800_ASIC2_LED_1_TimeBase          H3800_ASIC2_NOFFSET(  u8, LED, 1, TimeBase )
DECL|macro|H3800_ASIC2_LED_1_PeriodTime
mdefine_line|#define H3800_ASIC2_LED_1_PeriodTime        H3800_ASIC2_NOFFSET( u16, LED, 1, PeriodTime )
DECL|macro|H3800_ASIC2_LED_1_DutyTime
mdefine_line|#define H3800_ASIC2_LED_1_DutyTime          H3800_ASIC2_NOFFSET( u16, LED, 1, DutyTime )
DECL|macro|H3800_ASIC2_LED_1_AutoStopClock
mdefine_line|#define H3800_ASIC2_LED_1_AutoStopClock     H3800_ASIC2_NOFFSET( u16, LED, 1, AutoStopClock )
DECL|macro|H3800_ASIC2_LED_2_TimeBase
mdefine_line|#define H3800_ASIC2_LED_2_TimeBase          H3800_ASIC2_NOFFSET(  u8, LED, 2, TimeBase )
DECL|macro|H3800_ASIC2_LED_2_PeriodTime
mdefine_line|#define H3800_ASIC2_LED_2_PeriodTime        H3800_ASIC2_NOFFSET( u16, LED, 2, PeriodTime )
DECL|macro|H3800_ASIC2_LED_2_DutyTime
mdefine_line|#define H3800_ASIC2_LED_2_DutyTime          H3800_ASIC2_NOFFSET( u16, LED, 2, DutyTime )
DECL|macro|H3800_ASIC2_LED_2_AutoStopClock
mdefine_line|#define H3800_ASIC2_LED_2_AutoStopClock     H3800_ASIC2_NOFFSET( u16, LED, 2, AutoStopClock )
DECL|macro|H3800_ASIC2_LED_TIMEBASE_MASK
mdefine_line|#define H3800_ASIC2_LED_TIMEBASE_MASK            0x0f    /* Low 4 bits sets time base, max = 13 */
DECL|macro|H3800_ASIC2_LED_TIMEBASE_BLINK
mdefine_line|#define H3800_ASIC2_LED_TIMEBASE_BLINK     ( 1 &lt;&lt; 4 )    /* Enable blinking */
DECL|macro|H3800_ASIC2_LED_TIMEBASE_AUTOSTOP
mdefine_line|#define H3800_ASIC2_LED_TIMEBASE_AUTOSTOP  ( 1 &lt;&lt; 5 )
DECL|macro|H3800_ASIC2_LED_TIMEBASE_ALWAYS
mdefine_line|#define H3800_ASIC2_LED_TIMEBASE_ALWAYS    ( 1 &lt;&lt; 6 )    /* Enable blink always */
DECL|macro|_H3800_ASIC2_UART_0_Base
mdefine_line|#define _H3800_ASIC2_UART_0_Base               0x0A00
DECL|macro|_H3800_ASIC2_UART_1_Base
mdefine_line|#define _H3800_ASIC2_UART_1_Base               0x0C00
DECL|macro|_H3800_ASIC2_UART_Receive
mdefine_line|#define _H3800_ASIC2_UART_Receive              0x0000    /* R    8 bits */
DECL|macro|_H3800_ASIC2_UART_Transmit
mdefine_line|#define _H3800_ASIC2_UART_Transmit             0x0000    /*   W  8 bits */
DECL|macro|_H3800_ASIC2_UART_IntEnable
mdefine_line|#define _H3800_ASIC2_UART_IntEnable            0x0004    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_IntVerify
mdefine_line|#define _H3800_ASIC2_UART_IntVerify            0x0008    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_FIFOControl
mdefine_line|#define _H3800_ASIC2_UART_FIFOControl          0x000c    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_LineControl
mdefine_line|#define _H3800_ASIC2_UART_LineControl          0x0010    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_ModemStatus
mdefine_line|#define _H3800_ASIC2_UART_ModemStatus          0x0014    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_LineStatus
mdefine_line|#define _H3800_ASIC2_UART_LineStatus           0x0018    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_ScratchPad
mdefine_line|#define _H3800_ASIC2_UART_ScratchPad           0x001c    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_DivisorLatchL
mdefine_line|#define _H3800_ASIC2_UART_DivisorLatchL        0x0020    /* R/W  8 bits */
DECL|macro|_H3800_ASIC2_UART_DivisorLatchH
mdefine_line|#define _H3800_ASIC2_UART_DivisorLatchH        0x0024    /* R/W  8 bits */
DECL|macro|H3800_ASIC2_UART_0_Receive
mdefine_line|#define H3800_ASIC2_UART_0_Receive          H3800_ASIC2_NOFFSET(  u8, UART, 0, Receive )
DECL|macro|H3800_ASIC2_UART_0_Transmit
mdefine_line|#define H3800_ASIC2_UART_0_Transmit         H3800_ASIC2_NOFFSET(  u8, UART, 0, Transmit )
DECL|macro|H3800_ASIC2_UART_0_IntEnable
mdefine_line|#define H3800_ASIC2_UART_0_IntEnable        H3800_ASIC2_NOFFSET(  u8, UART, 0, IntEnable )
DECL|macro|H3800_ASIC2_UART_0_IntVerify
mdefine_line|#define H3800_ASIC2_UART_0_IntVerify        H3800_ASIC2_NOFFSET(  u8, UART, 0, IntVerify )
DECL|macro|H3800_ASIC2_UART_0_FIFOControl
mdefine_line|#define H3800_ASIC2_UART_0_FIFOControl      H3800_ASIC2_NOFFSET(  u8, UART, 0, FIFOControl )
DECL|macro|H3800_ASIC2_UART_0_LineControl
mdefine_line|#define H3800_ASIC2_UART_0_LineControl      H3800_ASIC2_NOFFSET(  u8, UART, 0, LineControl )
DECL|macro|H3800_ASIC2_UART_0_ModemStatus
mdefine_line|#define H3800_ASIC2_UART_0_ModemStatus      H3800_ASIC2_NOFFSET(  u8, UART, 0, ModemStatus )
DECL|macro|H3800_ASIC2_UART_0_LineStatus
mdefine_line|#define H3800_ASIC2_UART_0_LineStatus       H3800_ASIC2_NOFFSET(  u8, UART, 0, LineStatus )
DECL|macro|H3800_ASIC2_UART_0_ScratchPad
mdefine_line|#define H3800_ASIC2_UART_0_ScratchPad       H3800_ASIC2_NOFFSET(  u8, UART, 0, ScratchPad )
DECL|macro|H3800_ASIC2_UART_0_DivisorLatchL
mdefine_line|#define H3800_ASIC2_UART_0_DivisorLatchL    H3800_ASIC2_NOFFSET(  u8, UART, 0, DivisorLatchL )
DECL|macro|H3800_ASIC2_UART_0_DivisorLatchH
mdefine_line|#define H3800_ASIC2_UART_0_DivisorLatchH    H3800_ASIC2_NOFFSET(  u8, UART, 0, DivisorLatchH )
DECL|macro|H3800_ASIC2_UART_1_Receive
mdefine_line|#define H3800_ASIC2_UART_1_Receive          H3800_ASIC2_NOFFSET(  u8, UART, 1, Receive )
DECL|macro|H3800_ASIC2_UART_1_Transmit
mdefine_line|#define H3800_ASIC2_UART_1_Transmit         H3800_ASIC2_NOFFSET(  u8, UART, 1, Transmit )
DECL|macro|H3800_ASIC2_UART_1_IntEnable
mdefine_line|#define H3800_ASIC2_UART_1_IntEnable        H3800_ASIC2_NOFFSET(  u8, UART, 1, IntEnable )
DECL|macro|H3800_ASIC2_UART_1_IntVerify
mdefine_line|#define H3800_ASIC2_UART_1_IntVerify        H3800_ASIC2_NOFFSET(  u8, UART, 1, IntVerify )
DECL|macro|H3800_ASIC2_UART_1_FIFOControl
mdefine_line|#define H3800_ASIC2_UART_1_FIFOControl      H3800_ASIC2_NOFFSET(  u8, UART, 1, FIFOControl )
DECL|macro|H3800_ASIC2_UART_1_LineControl
mdefine_line|#define H3800_ASIC2_UART_1_LineControl      H3800_ASIC2_NOFFSET(  u8, UART, 1, LineControl )
DECL|macro|H3800_ASIC2_UART_1_ModemStatus
mdefine_line|#define H3800_ASIC2_UART_1_ModemStatus      H3800_ASIC2_NOFFSET(  u8, UART, 1, ModemStatus )
DECL|macro|H3800_ASIC2_UART_1_LineStatus
mdefine_line|#define H3800_ASIC2_UART_1_LineStatus       H3800_ASIC2_NOFFSET(  u8, UART, 1, LineStatus )
DECL|macro|H3800_ASIC2_UART_1_ScratchPad
mdefine_line|#define H3800_ASIC2_UART_1_ScratchPad       H3800_ASIC2_NOFFSET(  u8, UART, 1, ScratchPad )
DECL|macro|H3800_ASIC2_UART_1_DivisorLatchL
mdefine_line|#define H3800_ASIC2_UART_1_DivisorLatchL    H3800_ASIC2_NOFFSET(  u8, UART, 1, DivisorLatchL )
DECL|macro|H3800_ASIC2_UART_1_DivisorLatchH
mdefine_line|#define H3800_ASIC2_UART_1_DivisorLatchH    H3800_ASIC2_NOFFSET(  u8, UART, 1, DivisorLatchH )
DECL|macro|_H3800_ASIC2_TIMER_Base
mdefine_line|#define _H3800_ASIC2_TIMER_Base                0x0E00
DECL|macro|_H3800_ASIC2_TIMER_Command
mdefine_line|#define _H3800_ASIC2_TIMER_Command             0x0000    /* R/W  8 bits */
DECL|macro|H3800_ASIC2_TIMER_Command
mdefine_line|#define H3800_ASIC2_TIMER_Command           H3800_ASIC2_OFFSET( u8, Timer, Command )
DECL|macro|H3800_ASIC2_TIMER_GAT_0
mdefine_line|#define H3800_ASIC2_TIMER_GAT_0            ( 1 &lt;&lt; 0 )    /* Gate enable, counter 0 */
DECL|macro|H3800_ASIC2_TIMER_GAT_1
mdefine_line|#define H3800_ASIC2_TIMER_GAT_1            ( 1 &lt;&lt; 1 )    /* Gate enable, counter 1 */
DECL|macro|H3800_ASIC2_TIMER_GAT_2
mdefine_line|#define H3800_ASIC2_TIMER_GAT_2            ( 1 &lt;&lt; 2 )    /* Gate enable, counter 2 */
DECL|macro|H3800_ASIC2_TIMER_CLK_0
mdefine_line|#define H3800_ASIC2_TIMER_CLK_0            ( 1 &lt;&lt; 3 )    /* Clock enable, counter 0 */
DECL|macro|H3800_ASIC2_TIMER_CLK_1
mdefine_line|#define H3800_ASIC2_TIMER_CLK_1            ( 1 &lt;&lt; 4 )    /* Clock enable, counter 1 */
DECL|macro|H3800_ASIC2_TIMER_CLK_2
mdefine_line|#define H3800_ASIC2_TIMER_CLK_2            ( 1 &lt;&lt; 5 )    /* Clock enable, counter 2 */
DECL|macro|H3800_ASIC2_TIMER_MODE_0
mdefine_line|#define H3800_ASIC2_TIMER_MODE_0           ( 1 &lt;&lt; 6 )    /* Mode 0 enable, counter 0 */
DECL|macro|H3800_ASIC2_TIMER_MODE_1
mdefine_line|#define H3800_ASIC2_TIMER_MODE_1           ( 1 &lt;&lt; 7 )    /* Mode 0 enable, counter 1 */
DECL|macro|_H3800_ASIC2_CLOCK_Base
mdefine_line|#define _H3800_ASIC2_CLOCK_Base                0x1000
DECL|macro|_H3800_ASIC2_CLOCK_Enable
mdefine_line|#define _H3800_ASIC2_CLOCK_Enable              0x0000    /* R/W  18 bits */
DECL|macro|H3800_ASIC2_CLOCK_Enable
mdefine_line|#define H3800_ASIC2_CLOCK_Enable            H3800_ASIC2_OFFSET( u32, CLOCK, Enable )
DECL|macro|H3800_ASIC2_CLOCK_AUDIO_1
mdefine_line|#define H3800_ASIC2_CLOCK_AUDIO_1              0x0001    /* Enable 4.1 MHz clock for 8Khz and 4khz sample rate */
DECL|macro|H3800_ASIC2_CLOCK_AUDIO_2
mdefine_line|#define H3800_ASIC2_CLOCK_AUDIO_2              0x0002    /* Enable 12.3 MHz clock for 48Khz and 32khz sample rate */
DECL|macro|H3800_ASIC2_CLOCK_AUDIO_3
mdefine_line|#define H3800_ASIC2_CLOCK_AUDIO_3              0x0004    /* Enable 5.6 MHz clock for 11 kHZ sample rate */
DECL|macro|H3800_ASIC2_CLOCK_AUDIO_4
mdefine_line|#define H3800_ASIC2_CLOCK_AUDIO_4              0x0008    /* Enable 11.289 MHz clock for 44 and 22 kHz sample rate */
DECL|macro|H3800_ASIC2_CLOCK_ADC
mdefine_line|#define H3800_ASIC2_CLOCK_ADC              ( 1 &lt;&lt; 4 )    /* 1.024 MHz clock to ADC */
DECL|macro|H3800_ASIC2_CLOCK_SPI
mdefine_line|#define H3800_ASIC2_CLOCK_SPI              ( 1 &lt;&lt; 5 )    /* 4.096 MHz clock to SPI */
DECL|macro|H3800_ASIC2_CLOCK_OWM
mdefine_line|#define H3800_ASIC2_CLOCK_OWM              ( 1 &lt;&lt; 6 )    /* 4.096 MHz clock to OWM */
DECL|macro|H3800_ASIC2_CLOCK_PWM
mdefine_line|#define H3800_ASIC2_CLOCK_PWM              ( 1 &lt;&lt; 7 )    /* 2.048 MHz clock to PWM */
DECL|macro|H3800_ASIC2_CLOCK_UART_1
mdefine_line|#define H3800_ASIC2_CLOCK_UART_1           ( 1 &lt;&lt; 8 )    /* 24.576 MHz clock to UART1 (turn off bit 16) */
DECL|macro|H3800_ASIC2_CLOCK_UART_0
mdefine_line|#define H3800_ASIC2_CLOCK_UART_0           ( 1 &lt;&lt; 9 )    /* 24.576 MHz clock to UART0 (turn off bit 17) */
DECL|macro|H3800_ASIC2_CLOCK_SD_1
mdefine_line|#define H3800_ASIC2_CLOCK_SD_1             ( 1 &lt;&lt; 10 )   /* 16.934 MHz to SD */
DECL|macro|H3800_ASIC2_CLOCK_SD_2
mdefine_line|#define H3800_ASIC2_CLOCK_SD_2             ( 2 &lt;&lt; 10 )   /* 24.576 MHz to SD */
DECL|macro|H3800_ASIC2_CLOCK_SD_3
mdefine_line|#define H3800_ASIC2_CLOCK_SD_3             ( 3 &lt;&lt; 10 )   /* 33.869 MHz to SD */
DECL|macro|H3800_ASIC2_CLOCK_SD_4
mdefine_line|#define H3800_ASIC2_CLOCK_SD_4             ( 4 &lt;&lt; 10 )   /* 49.152 MHz to SD */
DECL|macro|H3800_ASIC2_CLOCK_EX0
mdefine_line|#define H3800_ASIC2_CLOCK_EX0              ( 1 &lt;&lt; 13 )   /* Enable 32.768 kHz crystal */
DECL|macro|H3800_ASIC2_CLOCK_EX1
mdefine_line|#define H3800_ASIC2_CLOCK_EX1              ( 1 &lt;&lt; 14 )   /* Enable 24.576 MHz crystal */
DECL|macro|H3800_ASIC2_CLOCK_EX2
mdefine_line|#define H3800_ASIC2_CLOCK_EX2              ( 1 &lt;&lt; 15 )   /* Enable 33.869 MHz crystal */
DECL|macro|H3800_ASIC2_CLOCK_SLOW_UART_1
mdefine_line|#define H3800_ASIC2_CLOCK_SLOW_UART_1      ( 1 &lt;&lt; 16 )   /* Enable 3.686 MHz to UART1 (turn off bit 8) */
DECL|macro|H3800_ASIC2_CLOCK_SLOW_UART_0
mdefine_line|#define H3800_ASIC2_CLOCK_SLOW_UART_0      ( 1 &lt;&lt; 17 )   /* Enable 3.686 MHz to UART0 (turn off bit 9) */
DECL|macro|_H3800_ASIC2_ADC_Base
mdefine_line|#define _H3800_ASIC2_ADC_Base                  0x1200
DECL|macro|_H3800_ASIC2_ADC_Multiplexer
mdefine_line|#define _H3800_ASIC2_ADC_Multiplexer           0x0000    /* R/W 4 bits - low 3 bits set channel */
DECL|macro|_H3800_ASIC2_ADC_ControlStatus
mdefine_line|#define _H3800_ASIC2_ADC_ControlStatus         0x0004    /* R/W 8 bits */
DECL|macro|_H3800_ASIC2_ADC_Data
mdefine_line|#define _H3800_ASIC2_ADC_Data                  0x0008    /* R   10 bits */
DECL|macro|H3800_ASIC2_ADC_Multiplexer
mdefine_line|#define H3800_ASIC2_ADC_Multiplexer       H3800_ASIC2_OFFSET(  u8, ADC, Multiplexer )
DECL|macro|H3800_ASIC2_ADC_ControlStatus
mdefine_line|#define H3800_ASIC2_ADC_ControlStatus     H3800_ASIC2_OFFSET(  u8, ADC, ControlStatus )
DECL|macro|H3800_ASIC2_ADC_Data
mdefine_line|#define H3800_ASIC2_ADC_Data              H3800_ASIC2_OFFSET( u16, ADC, Data )
DECL|macro|H3600_ASIC2_ADC_MUX_CHANNEL_MASK
mdefine_line|#define H3600_ASIC2_ADC_MUX_CHANNEL_MASK         0x07    /* Low 3 bits sets channel.  max = 4 */
DECL|macro|H3600_ASIC2_ADC_MUX_CLKEN
mdefine_line|#define H3600_ASIC2_ADC_MUX_CLKEN          ( 1 &lt;&lt; 3 )    /* Enable clock */
DECL|macro|H3600_ASIC2_ADC_CSR_ADPS_MASK
mdefine_line|#define H3600_ASIC2_ADC_CSR_ADPS_MASK            0x0f    /* Low 4 bits sets prescale, max = 8 */
DECL|macro|H3600_ASIC2_ADC_CSR_FREE_RUN
mdefine_line|#define H3600_ASIC2_ADC_CSR_FREE_RUN       ( 1 &lt;&lt; 4 )
DECL|macro|H3600_ASIC2_ADC_CSR_INT_ENABLE
mdefine_line|#define H3600_ASIC2_ADC_CSR_INT_ENABLE     ( 1 &lt;&lt; 5 )
DECL|macro|H3600_ASIC2_ADC_CSR_START
mdefine_line|#define H3600_ASIC2_ADC_CSR_START          ( 1 &lt;&lt; 6 )    /* Set to start conversion.  Goes to 0 when done */
DECL|macro|H3600_ASIC2_ADC_CSR_ENABLE
mdefine_line|#define H3600_ASIC2_ADC_CSR_ENABLE         ( 1 &lt;&lt; 7 )    /* 1:power up ADC, 0:power down */
DECL|macro|_H3800_ASIC2_INTR_Base
mdefine_line|#define _H3800_ASIC2_INTR_Base                 0x1600
DECL|macro|_H3800_ASIC2_INTR_MaskAndFlag
mdefine_line|#define _H3800_ASIC2_INTR_MaskAndFlag          0x0000    /* R/(W) 8bits */
DECL|macro|_H3800_ASIC2_INTR_ClockPrescale
mdefine_line|#define _H3800_ASIC2_INTR_ClockPrescale        0x0004    /* R/(W) 5bits */
DECL|macro|_H3800_ASIC2_INTR_TimerSet
mdefine_line|#define _H3800_ASIC2_INTR_TimerSet             0x0008    /* R/(W) 8bits */
DECL|macro|H3800_ASIC2_INTR_MaskAndFlag
mdefine_line|#define H3800_ASIC2_INTR_MaskAndFlag      H3800_ASIC2_OFFSET( u8, INTR, MaskAndFlag )
DECL|macro|H3800_ASIC2_INTR_ClockPrescale
mdefine_line|#define H3800_ASIC2_INTR_ClockPrescale    H3800_ASIC2_OFFSET( u8, INTR, ClockPrescale )
DECL|macro|H3800_ASIC2_INTR_TimerSet
mdefine_line|#define H3800_ASIC2_INTR_TimerSet         H3800_ASIC2_OFFSET( u8, INTR, TimerSet )
DECL|macro|H3800_ASIC2_INTR_GLOBAL_MASK
mdefine_line|#define H3800_ASIC2_INTR_GLOBAL_MASK       ( 1 &lt;&lt; 0 )    /* Global interrupt mask */
DECL|macro|H3800_ASIC2_INTR_POWER_ON_RESET
mdefine_line|#define H3800_ASIC2_INTR_POWER_ON_RESET    ( 1 &lt;&lt; 1 )    /* 01: Power on reset (bits 1 &amp; 2 ) */
DECL|macro|H3800_ASIC2_INTR_EXTERNAL_RESET
mdefine_line|#define H3800_ASIC2_INTR_EXTERNAL_RESET    ( 2 &lt;&lt; 1 )    /* 10: External reset (bits 1 &amp; 2 ) */
DECL|macro|H3800_ASIC2_INTR_MASK_UART_0
mdefine_line|#define H3800_ASIC2_INTR_MASK_UART_0       ( 1 &lt;&lt; 4 )
DECL|macro|H3800_ASIC2_INTR_MASK_UART_1
mdefine_line|#define H3800_ASIC2_INTR_MASK_UART_1       ( 1 &lt;&lt; 5 )
DECL|macro|H3800_ASIC2_INTR_MASK_TIMER
mdefine_line|#define H3800_ASIC2_INTR_MASK_TIMER        ( 1 &lt;&lt; 6 )
DECL|macro|H3800_ASIC2_INTR_MASK_OWM
mdefine_line|#define H3800_ASIC2_INTR_MASK_OWM          ( 1 &lt;&lt; 7 )
DECL|macro|H3800_ASIC2_INTR_CLOCK_PRESCALE
mdefine_line|#define H3800_ASIC2_INTR_CLOCK_PRESCALE          0x0f    /* 4 bits, max 14 */
DECL|macro|H3800_ASIC2_INTR_SET
mdefine_line|#define H3800_ASIC2_INTR_SET               ( 1 &lt;&lt; 4 )    /* Time base enable */
DECL|macro|_H3800_ASIC2_OWM_Base
mdefine_line|#define _H3800_ASIC2_OWM_Base                  0x1800
DECL|macro|_H3800_ASIC2_OWM_Command
mdefine_line|#define _H3800_ASIC2_OWM_Command               0x0000    /* R/W 4 bits command register */
DECL|macro|_H3800_ASIC2_OWM_Data
mdefine_line|#define _H3800_ASIC2_OWM_Data                  0x0004    /* R/W 8 bits, transmit / receive buffer */
DECL|macro|_H3800_ASIC2_OWM_Interrupt
mdefine_line|#define _H3800_ASIC2_OWM_Interrupt             0x0008    /* R/W Command register */
DECL|macro|_H3800_ASIC2_OWM_InterruptEnable
mdefine_line|#define _H3800_ASIC2_OWM_InterruptEnable       0x000c    /* R/W Command register */
DECL|macro|_H3800_ASIC2_OWM_ClockDivisor
mdefine_line|#define _H3800_ASIC2_OWM_ClockDivisor          0x0010    /* R/W 5 bits of divisor and pre-scale */
DECL|macro|H3800_ASIC2_OWM_Command
mdefine_line|#define H3800_ASIC2_OWM_Command            H3800_ASIC2_OFFSET( u8, OWM, Command )
DECL|macro|H3800_ASIC2_OWM_Data
mdefine_line|#define H3800_ASIC2_OWM_Data               H3800_ASIC2_OFFSET( u8, OWM, Data )
DECL|macro|H3800_ASIC2_OWM_Interrupt
mdefine_line|#define H3800_ASIC2_OWM_Interrupt          H3800_ASIC2_OFFSET( u8, OWM, Interrupt )
DECL|macro|H3800_ASIC2_OWM_InterruptEnable
mdefine_line|#define H3800_ASIC2_OWM_InterruptEnable    H3800_ASIC2_OFFSET( u8, OWM, InterruptEnable )
DECL|macro|H3800_ASIC2_OWM_ClockDivisor
mdefine_line|#define H3800_ASIC2_OWM_ClockDivisor       H3800_ASIC2_OFFSET( u8, OWM, ClockDivisor )
DECL|macro|H3800_ASIC2_OWM_CMD_ONE_WIRE_RESET
mdefine_line|#define H3800_ASIC2_OWM_CMD_ONE_WIRE_RESET ( 1 &lt;&lt; 0 )    /* Set to force reset on 1-wire bus */
DECL|macro|H3800_ASIC2_OWM_CMD_SRA
mdefine_line|#define H3800_ASIC2_OWM_CMD_SRA            ( 1 &lt;&lt; 1 )    /* Set to switch to Search ROM accelerator mode */
DECL|macro|H3800_ASIC2_OWM_CMD_DQ_OUTPUT
mdefine_line|#define H3800_ASIC2_OWM_CMD_DQ_OUTPUT      ( 1 &lt;&lt; 2 )    /* Write only - forces bus low */
DECL|macro|H3800_ASIC2_OWM_CMD_DQ_INPUT
mdefine_line|#define H3800_ASIC2_OWM_CMD_DQ_INPUT       ( 1 &lt;&lt; 3 )    /* Read only - reflects state of bus */
DECL|macro|H3800_ASIC2_OWM_INT_PD
mdefine_line|#define H3800_ASIC2_OWM_INT_PD             ( 1 &lt;&lt; 0 )    /* Presence detect */
DECL|macro|H3800_ASIC2_OWM_INT_PDR
mdefine_line|#define H3800_ASIC2_OWM_INT_PDR            ( 1 &lt;&lt; 1 )    /* Presence detect result */
DECL|macro|H3800_ASIC2_OWM_INT_TBE
mdefine_line|#define H3800_ASIC2_OWM_INT_TBE            ( 1 &lt;&lt; 2 )    /* Transmit buffer empty */
DECL|macro|H3800_ASIC2_OWM_INT_TEMT
mdefine_line|#define H3800_ASIC2_OWM_INT_TEMT           ( 1 &lt;&lt; 3 )    /* Transmit shift register empty */
DECL|macro|H3800_ASIC2_OWM_INT_RBF
mdefine_line|#define H3800_ASIC2_OWM_INT_RBF            ( 1 &lt;&lt; 4 )    /* Receive buffer full */
DECL|macro|H3800_ASIC2_OWM_INTEN_EPD
mdefine_line|#define H3800_ASIC2_OWM_INTEN_EPD          ( 1 &lt;&lt; 0 )    /* Enable receive buffer full interrupt */
DECL|macro|H3800_ASIC2_OWM_INTEN_IAS
mdefine_line|#define H3800_ASIC2_OWM_INTEN_IAS          ( 1 &lt;&lt; 1 )    /* Enable transmit shift register empty interrupt */
DECL|macro|H3800_ASIC2_OWM_INTEN_ETBE
mdefine_line|#define H3800_ASIC2_OWM_INTEN_ETBE         ( 1 &lt;&lt; 2 )    /* Enable transmit buffer empty interrupt */
DECL|macro|H3800_ASIC2_OWM_INTEN_ETMT
mdefine_line|#define H3800_ASIC2_OWM_INTEN_ETMT         ( 1 &lt;&lt; 3 )    /* INTR active state */
DECL|macro|H3800_ASIC2_OWM_INTEN_ERBF
mdefine_line|#define H3800_ASIC2_OWM_INTEN_ERBF         ( 1 &lt;&lt; 4 )    /* Enable presence detect interrupt */
DECL|macro|_H3800_ASIC2_FlashCtl_Base
mdefine_line|#define _H3800_ASIC2_FlashCtl_Base             0x1A00
multiline_comment|/****************************************************/
multiline_comment|/* H3800, ASIC #1&n; * This ASIC is accesed through ASIC #2, and&n; * mapped into the 1c00 - 1f00 region&n; */
DECL|macro|H3800_ASIC1_OFFSET
mdefine_line|#define H3800_ASIC1_OFFSET(s,x,y)   &bslash;&n;     (*((volatile s *) (_H3800_ASIC2_Base + _H3800_ASIC1_ ## x ## _Base + (_H3800_ASIC1_ ## x ## _ ## y &lt;&lt; 1))))
DECL|macro|_H3800_ASIC1_MMC_Base
mdefine_line|#define _H3800_ASIC1_MMC_Base             0x1c00
DECL|macro|_H3800_ASIC1_MMC_StartStopClock
mdefine_line|#define _H3800_ASIC1_MMC_StartStopClock     0x00    /* R/W 8bit                                  */
DECL|macro|_H3800_ASIC1_MMC_Status
mdefine_line|#define _H3800_ASIC1_MMC_Status             0x02    /* R   See below, default 0x0040             */
DECL|macro|_H3800_ASIC1_MMC_ClockRate
mdefine_line|#define _H3800_ASIC1_MMC_ClockRate          0x04    /* R/W 8bit, low 3 bits are clock divisor    */
DECL|macro|_H3800_ASIC1_MMC_SPIRegister
mdefine_line|#define _H3800_ASIC1_MMC_SPIRegister        0x08    /* R/W 8bit, see below                       */
DECL|macro|_H3800_ASIC1_MMC_CmdDataCont
mdefine_line|#define _H3800_ASIC1_MMC_CmdDataCont        0x0a    /* R/W 8bit, write to start MMC adapter      */
DECL|macro|_H3800_ASIC1_MMC_ResponseTimeout
mdefine_line|#define _H3800_ASIC1_MMC_ResponseTimeout    0x0c    /* R/W 8bit, clocks before response timeout  */
DECL|macro|_H3800_ASIC1_MMC_ReadTimeout
mdefine_line|#define _H3800_ASIC1_MMC_ReadTimeout        0x0e    /* R/W 16bit, clocks before received data timeout */
DECL|macro|_H3800_ASIC1_MMC_BlockLength
mdefine_line|#define _H3800_ASIC1_MMC_BlockLength        0x10    /* R/W 10bit */
DECL|macro|_H3800_ASIC1_MMC_NumOfBlocks
mdefine_line|#define _H3800_ASIC1_MMC_NumOfBlocks        0x12    /* R/W 16bit, in block mode, number of blocks  */
DECL|macro|_H3800_ASIC1_MMC_InterruptMask
mdefine_line|#define _H3800_ASIC1_MMC_InterruptMask      0x1a    /* R/W 8bit */
DECL|macro|_H3800_ASIC1_MMC_CommandNumber
mdefine_line|#define _H3800_ASIC1_MMC_CommandNumber      0x1c    /* R/W 6 bits */
DECL|macro|_H3800_ASIC1_MMC_ArgumentH
mdefine_line|#define _H3800_ASIC1_MMC_ArgumentH          0x1e    /* R/W 16 bits  */
DECL|macro|_H3800_ASIC1_MMC_ArgumentL
mdefine_line|#define _H3800_ASIC1_MMC_ArgumentL          0x20    /* R/W 16 bits */
DECL|macro|_H3800_ASIC1_MMC_ResFifo
mdefine_line|#define _H3800_ASIC1_MMC_ResFifo            0x22    /* R   8 x 16 bits - contains response FIFO */
DECL|macro|_H3800_ASIC1_MMC_BufferPartFull
mdefine_line|#define _H3800_ASIC1_MMC_BufferPartFull     0x28    /* R/W 8 bits */
DECL|macro|H3800_ASIC1_MMC_StartStopClock
mdefine_line|#define H3800_ASIC1_MMC_StartStopClock    H3800_ASIC1_OFFSET(  u8, MMC, StartStopClock )
DECL|macro|H3800_ASIC1_MMC_Status
mdefine_line|#define H3800_ASIC1_MMC_Status            H3800_ASIC1_OFFSET( u16, MMC, Status )
DECL|macro|H3800_ASIC1_MMC_ClockRate
mdefine_line|#define H3800_ASIC1_MMC_ClockRate         H3800_ASIC1_OFFSET(  u8, MMC, ClockRate )
DECL|macro|H3800_ASIC1_MMC_SPIRegister
mdefine_line|#define H3800_ASIC1_MMC_SPIRegister       H3800_ASIC1_OFFSET(  u8, MMC, SPIRegister )
DECL|macro|H3800_ASIC1_MMC_CmdDataCont
mdefine_line|#define H3800_ASIC1_MMC_CmdDataCont       H3800_ASIC1_OFFSET(  u8, MMC, CmdDataCont )
DECL|macro|H3800_ASIC1_MMC_ResponseTimeout
mdefine_line|#define H3800_ASIC1_MMC_ResponseTimeout   H3800_ASIC1_OFFSET(  u8, MMC, ResponseTimeout )
DECL|macro|H3800_ASIC1_MMC_ReadTimeout
mdefine_line|#define H3800_ASIC1_MMC_ReadTimeout       H3800_ASIC1_OFFSET( u16, MMC, ReadTimeout )
DECL|macro|H3800_ASIC1_MMC_BlockLength
mdefine_line|#define H3800_ASIC1_MMC_BlockLength       H3800_ASIC1_OFFSET( u16, MMC, BlockLength )
DECL|macro|H3800_ASIC1_MMC_NumOfBlocks
mdefine_line|#define H3800_ASIC1_MMC_NumOfBlocks       H3800_ASIC1_OFFSET( u16, MMC, NumOfBlocks )
DECL|macro|H3800_ASIC1_MMC_InterruptMask
mdefine_line|#define H3800_ASIC1_MMC_InterruptMask     H3800_ASIC1_OFFSET(  u8, MMC, InterruptMask )
DECL|macro|H3800_ASIC1_MMC_CommandNumber
mdefine_line|#define H3800_ASIC1_MMC_CommandNumber     H3800_ASIC1_OFFSET(  u8, MMC, CommandNumber )
DECL|macro|H3800_ASIC1_MMC_ArgumentH
mdefine_line|#define H3800_ASIC1_MMC_ArgumentH         H3800_ASIC1_OFFSET( u16, MMC, ArgumentH )
DECL|macro|H3800_ASIC1_MMC_ArgumentL
mdefine_line|#define H3800_ASIC1_MMC_ArgumentL         H3800_ASIC1_OFFSET( u16, MMC, ArgumentL )
DECL|macro|H3800_ASIC1_MMC_ResFifo
mdefine_line|#define H3800_ASIC1_MMC_ResFifo           H3800_ASIC1_OFFSET( u16, MMC, ResFifo )
DECL|macro|H3800_ASIC1_MMC_BufferPartFull
mdefine_line|#define H3800_ASIC1_MMC_BufferPartFull    H3800_ASIC1_OFFSET(  u8, MMC, BufferPartFull )
DECL|macro|H3800_ASIC1_MMC_STOP_CLOCK
mdefine_line|#define H3800_ASIC1_MMC_STOP_CLOCK                   (1 &lt;&lt; 0)   /* Write to &quot;StartStopClock&quot; register */
DECL|macro|H3800_ASIC1_MMC_START_CLOCK
mdefine_line|#define H3800_ASIC1_MMC_START_CLOCK                  (1 &lt;&lt; 1)
DECL|macro|H3800_ASIC1_MMC_STATUS_READ_TIMEOUT
mdefine_line|#define H3800_ASIC1_MMC_STATUS_READ_TIMEOUT          (1 &lt;&lt; 0)
DECL|macro|H3800_ASIC1_MMC_STATUS_RESPONSE_TIMEOUT
mdefine_line|#define H3800_ASIC1_MMC_STATUS_RESPONSE_TIMEOUT      (1 &lt;&lt; 1)
DECL|macro|H3800_ASIC1_MMC_STATUS_CRC_WRITE_ERROR
mdefine_line|#define H3800_ASIC1_MMC_STATUS_CRC_WRITE_ERROR       (1 &lt;&lt; 2)
DECL|macro|H3800_ASIC1_MMC_STATUS_CRC_READ_ERROR
mdefine_line|#define H3800_ASIC1_MMC_STATUS_CRC_READ_ERROR        (1 &lt;&lt; 3)
DECL|macro|H3800_ASIC1_MMC_STATUS_SPI_READ_ERROR
mdefine_line|#define H3800_ASIC1_MMC_STATUS_SPI_READ_ERROR        (1 &lt;&lt; 4)  /* SPI data token error received */
DECL|macro|H3800_ASIC1_MMC_STATUS_CRC_RESPONSE_ERROR
mdefine_line|#define H3800_ASIC1_MMC_STATUS_CRC_RESPONSE_ERROR    (1 &lt;&lt; 5)
DECL|macro|H3800_ASIC1_MMC_STATUS_FIFO_EMPTY
mdefine_line|#define H3800_ASIC1_MMC_STATUS_FIFO_EMPTY            (1 &lt;&lt; 6)
DECL|macro|H3800_ASIC1_MMC_STATUS_FIFO_FULL
mdefine_line|#define H3800_ASIC1_MMC_STATUS_FIFO_FULL             (1 &lt;&lt; 7)
DECL|macro|H3800_ASIC1_MMC_STATUS_CLOCK_ENABLE
mdefine_line|#define H3800_ASIC1_MMC_STATUS_CLOCK_ENABLE          (1 &lt;&lt; 8)  /* MultiMediaCard clock stopped */
DECL|macro|H3800_ASIC1_MMC_STATUS_DATA_TRANSFER_DONE
mdefine_line|#define H3800_ASIC1_MMC_STATUS_DATA_TRANSFER_DONE    (1 &lt;&lt; 11) /* Write operation, indicates transfer finished */
DECL|macro|H3800_ASIC1_MMC_STATUS_END_PROGRAM
mdefine_line|#define H3800_ASIC1_MMC_STATUS_END_PROGRAM           (1 &lt;&lt; 12) /* End write and read operations */
DECL|macro|H3800_ASIC1_MMC_STATUS_END_COMMAND_RESPONSE
mdefine_line|#define H3800_ASIC1_MMC_STATUS_END_COMMAND_RESPONSE  (1 &lt;&lt; 13) /* End command response */
DECL|macro|H3800_ASIC1_MMC_SPI_REG_SPI_ENABLE
mdefine_line|#define H3800_ASIC1_MMC_SPI_REG_SPI_ENABLE           (1 &lt;&lt; 0)  /* Enables SPI mode */
DECL|macro|H3800_ASIC1_MMC_SPI_REG_CRC_ON
mdefine_line|#define H3800_ASIC1_MMC_SPI_REG_CRC_ON               (1 &lt;&lt; 1)  /* 1:turn on CRC    */
DECL|macro|H3800_ASIC1_MMC_SPI_REG_SPI_CS_ENABLE
mdefine_line|#define H3800_ASIC1_MMC_SPI_REG_SPI_CS_ENABLE        (1 &lt;&lt; 2)  /* 1:turn on SPI CS */
DECL|macro|H3800_ASIC1_MMC_SPI_REG_CS_ADDRESS_MASK
mdefine_line|#define H3800_ASIC1_MMC_SPI_REG_CS_ADDRESS_MASK      0x38      /* Bits 3,4,5 are the SPI CS relative address */
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_NO_RESPONSE
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_NO_RESPONSE  0x00
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_R1
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_R1           0x01
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_R2
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_R2           0x02
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_R3
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_FORMAT_R3           0x03
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_DATA_ENABLE
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_DATA_ENABLE         (1 &lt;&lt; 2)  /* This command contains a data transfer */
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_WRITE
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_WRITE               (1 &lt;&lt; 3)  /* This data transfer is a write */
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_STREAM_MODE
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_STREAM_MODE         (1 &lt;&lt; 4)  /* This data transfer is in stream mode */
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_BUSY_BIT
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_BUSY_BIT            (1 &lt;&lt; 5)  /* Busy signal expected after current cmd */
DECL|macro|H3800_ASIC1_MMC_CMD_DATA_CONT_INITIALIZE
mdefine_line|#define H3800_ASIC1_MMC_CMD_DATA_CONT_INITIALIZE          (1 &lt;&lt; 6)  /* Enables the 80 bits for initializing card */
DECL|macro|H3800_ASIC1_MMC_INT_MASK_DATA_TRANSFER_DONE
mdefine_line|#define H3800_ASIC1_MMC_INT_MASK_DATA_TRANSFER_DONE       (1 &lt;&lt; 0)
DECL|macro|H3800_ASIC1_MMC_INT_MASK_PROGRAM_DONE
mdefine_line|#define H3800_ASIC1_MMC_INT_MASK_PROGRAM_DONE             (1 &lt;&lt; 1)
DECL|macro|H3800_ASIC1_MMC_INT_MASK_END_COMMAND_RESPONSE
mdefine_line|#define H3800_ASIC1_MMC_INT_MASK_END_COMMAND_RESPONSE     (1 &lt;&lt; 2)
DECL|macro|H3800_ASIC1_MMC_INT_MASK_BUFFER_READY
mdefine_line|#define H3800_ASIC1_MMC_INT_MASK_BUFFER_READY             (1 &lt;&lt; 3)
DECL|macro|H3800_ASIC1_MMC_BUFFER_PART_FULL
mdefine_line|#define H3800_ASIC1_MMC_BUFFER_PART_FULL                  (1 &lt;&lt; 0)
multiline_comment|/********* GPIO **********/
DECL|macro|_H3800_ASIC1_GPIO_Base
mdefine_line|#define _H3800_ASIC1_GPIO_Base        0x1e00
DECL|macro|_H3800_ASIC1_GPIO_Mask
mdefine_line|#define _H3800_ASIC1_GPIO_Mask          0x30    /* R/W 0:don&squot;t mask, 1:mask interrupt */
DECL|macro|_H3800_ASIC1_GPIO_Direction
mdefine_line|#define _H3800_ASIC1_GPIO_Direction     0x32    /* R/W 0:input, 1:output              */
DECL|macro|_H3800_ASIC1_GPIO_Out
mdefine_line|#define _H3800_ASIC1_GPIO_Out           0x34    /* R/W 0:output low, 1:output high    */
DECL|macro|_H3800_ASIC1_GPIO_TriggerType
mdefine_line|#define _H3800_ASIC1_GPIO_TriggerType   0x36    /* R/W 0:level, 1:edge                */
DECL|macro|_H3800_ASIC1_GPIO_EdgeTrigger
mdefine_line|#define _H3800_ASIC1_GPIO_EdgeTrigger   0x38    /* R/W 0:falling, 1:rising            */
DECL|macro|_H3800_ASIC1_GPIO_LevelTrigger
mdefine_line|#define _H3800_ASIC1_GPIO_LevelTrigger  0x3A    /* R/W 0:low, 1:high level detect     */
DECL|macro|_H3800_ASIC1_GPIO_LevelStatus
mdefine_line|#define _H3800_ASIC1_GPIO_LevelStatus   0x3C    /* R/W 0:none, 1:detect               */
DECL|macro|_H3800_ASIC1_GPIO_EdgeStatus
mdefine_line|#define _H3800_ASIC1_GPIO_EdgeStatus    0x3E    /* R/W 0:none, 1:detect               */
DECL|macro|_H3800_ASIC1_GPIO_State
mdefine_line|#define _H3800_ASIC1_GPIO_State         0x40    /* R   See masks below  (default 0)         */
DECL|macro|_H3800_ASIC1_GPIO_Reset
mdefine_line|#define _H3800_ASIC1_GPIO_Reset         0x42    /* R/W See masks below  (default 0x04)      */
DECL|macro|_H3800_ASIC1_GPIO_SleepMask
mdefine_line|#define _H3800_ASIC1_GPIO_SleepMask     0x44    /* R/W 0:don&squot;t mask, 1:mask trigger in sleep mode  */
DECL|macro|_H3800_ASIC1_GPIO_SleepDir
mdefine_line|#define _H3800_ASIC1_GPIO_SleepDir      0x46    /* R/W direction 0:input, 1:ouput in sleep mode    */
DECL|macro|_H3800_ASIC1_GPIO_SleepOut
mdefine_line|#define _H3800_ASIC1_GPIO_SleepOut      0x48    /* R/W level 0:low, 1:high in sleep mode           */
DECL|macro|_H3800_ASIC1_GPIO_Status
mdefine_line|#define _H3800_ASIC1_GPIO_Status        0x4A    /* R   Pin status                                  */
DECL|macro|_H3800_ASIC1_GPIO_BattFaultDir
mdefine_line|#define _H3800_ASIC1_GPIO_BattFaultDir  0x4C    /* R/W direction 0:input, 1:output in batt_fault   */
DECL|macro|_H3800_ASIC1_GPIO_BattFaultOut
mdefine_line|#define _H3800_ASIC1_GPIO_BattFaultOut  0x4E    /* R/W level 0:low, 1:high in batt_fault           */
DECL|macro|H3800_ASIC1_GPIO_Mask
mdefine_line|#define H3800_ASIC1_GPIO_Mask         H3800_ASIC1_OFFSET( u16, GPIO, Mask )
DECL|macro|H3800_ASIC1_GPIO_Direction
mdefine_line|#define H3800_ASIC1_GPIO_Direction    H3800_ASIC1_OFFSET( u16, GPIO, Direction )
DECL|macro|H3800_ASIC1_GPIO_Out
mdefine_line|#define H3800_ASIC1_GPIO_Out          H3800_ASIC1_OFFSET( u16, GPIO, Out )
DECL|macro|H3800_ASIC1_GPIO_TriggerType
mdefine_line|#define H3800_ASIC1_GPIO_TriggerType  H3800_ASIC1_OFFSET( u16, GPIO, TriggerType )
DECL|macro|H3800_ASIC1_GPIO_EdgeTrigger
mdefine_line|#define H3800_ASIC1_GPIO_EdgeTrigger  H3800_ASIC1_OFFSET( u16, GPIO, EdgeTrigger )
DECL|macro|H3800_ASIC1_GPIO_LevelTrigger
mdefine_line|#define H3800_ASIC1_GPIO_LevelTrigger H3800_ASIC1_OFFSET( u16, GPIO, LevelTrigger )
DECL|macro|H3800_ASIC1_GPIO_LevelStatus
mdefine_line|#define H3800_ASIC1_GPIO_LevelStatus  H3800_ASIC1_OFFSET( u16, GPIO, LevelStatus )
DECL|macro|H3800_ASIC1_GPIO_EdgeStatus
mdefine_line|#define H3800_ASIC1_GPIO_EdgeStatus   H3800_ASIC1_OFFSET( u16, GPIO, EdgeStatus )
DECL|macro|H3800_ASIC1_GPIO_State
mdefine_line|#define H3800_ASIC1_GPIO_State        H3800_ASIC1_OFFSET(  u8, GPIO, State )
DECL|macro|H3800_ASIC1_GPIO_Reset
mdefine_line|#define H3800_ASIC1_GPIO_Reset        H3800_ASIC1_OFFSET(  u8, GPIO, Reset )
DECL|macro|H3800_ASIC1_GPIO_SleepMask
mdefine_line|#define H3800_ASIC1_GPIO_SleepMask    H3800_ASIC1_OFFSET( u16, GPIO, SleepMask )
DECL|macro|H3800_ASIC1_GPIO_SleepDir
mdefine_line|#define H3800_ASIC1_GPIO_SleepDir     H3800_ASIC1_OFFSET( u16, GPIO, SleepDir )
DECL|macro|H3800_ASIC1_GPIO_SleepOut
mdefine_line|#define H3800_ASIC1_GPIO_SleepOut     H3800_ASIC1_OFFSET( u16, GPIO, SleepOut )
DECL|macro|H3800_ASIC1_GPIO_Status
mdefine_line|#define H3800_ASIC1_GPIO_Status       H3800_ASIC1_OFFSET( u16, GPIO, Status )
DECL|macro|H3800_ASIC1_GPIO_BattFaultDir
mdefine_line|#define H3800_ASIC1_GPIO_BattFaultDir H3800_ASIC1_OFFSET( u16, GPIO, BattFaultDir )
DECL|macro|H3800_ASIC1_GPIO_BattFaultOut
mdefine_line|#define H3800_ASIC1_GPIO_BattFaultOut H3800_ASIC1_OFFSET( u16, GPIO, BattFaultOut )
DECL|macro|H3800_ASIC1_GPIO_STATE_MASK
mdefine_line|#define H3800_ASIC1_GPIO_STATE_MASK            (1 &lt;&lt; 0)
DECL|macro|H3800_ASIC1_GPIO_STATE_DIRECTION
mdefine_line|#define H3800_ASIC1_GPIO_STATE_DIRECTION       (1 &lt;&lt; 1)
DECL|macro|H3800_ASIC1_GPIO_STATE_OUT
mdefine_line|#define H3800_ASIC1_GPIO_STATE_OUT             (1 &lt;&lt; 2)
DECL|macro|H3800_ASIC1_GPIO_STATE_TRIGGER_TYPE
mdefine_line|#define H3800_ASIC1_GPIO_STATE_TRIGGER_TYPE    (1 &lt;&lt; 3)
DECL|macro|H3800_ASIC1_GPIO_STATE_EDGE_TRIGGER
mdefine_line|#define H3800_ASIC1_GPIO_STATE_EDGE_TRIGGER    (1 &lt;&lt; 4)
DECL|macro|H3800_ASIC1_GPIO_STATE_LEVEL_TRIGGER
mdefine_line|#define H3800_ASIC1_GPIO_STATE_LEVEL_TRIGGER   (1 &lt;&lt; 5)
DECL|macro|H3800_ASIC1_GPIO_RESET_SOFTWARE
mdefine_line|#define H3800_ASIC1_GPIO_RESET_SOFTWARE        (1 &lt;&lt; 0)
DECL|macro|H3800_ASIC1_GPIO_RESET_AUTO_SLEEP
mdefine_line|#define H3800_ASIC1_GPIO_RESET_AUTO_SLEEP      (1 &lt;&lt; 1)
DECL|macro|H3800_ASIC1_GPIO_RESET_FIRST_PWR_ON
mdefine_line|#define H3800_ASIC1_GPIO_RESET_FIRST_PWR_ON    (1 &lt;&lt; 2)
multiline_comment|/* These are all outputs */
DECL|macro|GPIO_H3800_ASIC1_IR_ON_N
mdefine_line|#define GPIO_H3800_ASIC1_IR_ON_N          (1 &lt;&lt; 0)   /* Apply power to the IR Module */
DECL|macro|GPIO_H3800_ASIC1_SD_PWR_ON
mdefine_line|#define GPIO_H3800_ASIC1_SD_PWR_ON        (1 &lt;&lt; 1)   /* Secure Digital power on */
DECL|macro|GPIO_H3800_ASIC1_RS232_ON
mdefine_line|#define GPIO_H3800_ASIC1_RS232_ON         (1 &lt;&lt; 2)   /* Turn on power to the RS232 chip ? */
DECL|macro|GPIO_H3800_ASIC1_PULSE_GEN
mdefine_line|#define GPIO_H3800_ASIC1_PULSE_GEN        (1 &lt;&lt; 3)   /* Goes to speaker / earphone */
DECL|macro|GPIO_H3800_ASIC1_CH_TIMER
mdefine_line|#define GPIO_H3800_ASIC1_CH_TIMER         (1 &lt;&lt; 4)   /* */
DECL|macro|GPIO_H3800_ASIC1_LCD_5V_ON
mdefine_line|#define GPIO_H3800_ASIC1_LCD_5V_ON        (1 &lt;&lt; 5)   /* Enables LCD_5V */
DECL|macro|GPIO_H3800_ASIC1_LCD_ON
mdefine_line|#define GPIO_H3800_ASIC1_LCD_ON           (1 &lt;&lt; 6)   /* Enables LCD_3V */
DECL|macro|GPIO_H3800_ASIC1_LCD_PCI
mdefine_line|#define GPIO_H3800_ASIC1_LCD_PCI          (1 &lt;&lt; 7)   /* Connects to PDWN on LCD controller */
DECL|macro|GPIO_H3800_ASIC1_VGH_ON
mdefine_line|#define GPIO_H3800_ASIC1_VGH_ON           (1 &lt;&lt; 8)   /* Drives VGH on the LCD (+9??) */
DECL|macro|GPIO_H3800_ASIC1_VGL_ON
mdefine_line|#define GPIO_H3800_ASIC1_VGL_ON           (1 &lt;&lt; 9)   /* Drivers VGL on the LCD (-6??) */
DECL|macro|GPIO_H3800_ASIC1_FL_PWR_ON
mdefine_line|#define GPIO_H3800_ASIC1_FL_PWR_ON        (1 &lt;&lt; 10)  /* Frontlight power on */
DECL|macro|GPIO_H3800_ASIC1_BT_PWR_ON
mdefine_line|#define GPIO_H3800_ASIC1_BT_PWR_ON        (1 &lt;&lt; 11)  /* Bluetooth power on */
DECL|macro|GPIO_H3800_ASIC1_SPK_ON
mdefine_line|#define GPIO_H3800_ASIC1_SPK_ON           (1 &lt;&lt; 12)  /* */
DECL|macro|GPIO_H3800_ASIC1_EAR_ON_N
mdefine_line|#define GPIO_H3800_ASIC1_EAR_ON_N         (1 &lt;&lt; 13)  /* */
DECL|macro|GPIO_H3800_ASIC1_AUD_PWR_ON
mdefine_line|#define GPIO_H3800_ASIC1_AUD_PWR_ON       (1 &lt;&lt; 14)  /* */
multiline_comment|/* Write enable for the flash */
DECL|macro|_H3800_ASIC1_FlashWP_Base
mdefine_line|#define _H3800_ASIC1_FlashWP_Base         0x1F00
DECL|macro|_H3800_ASIC1_FlashWP_VPP_ON
mdefine_line|#define _H3800_ASIC1_FlashWP_VPP_ON         0x00    /* R   1: write, 0: protect */
DECL|macro|H3800_ASIC1_FlashWP_VPP_ON
mdefine_line|#define H3800_ASIC1_FlashWP_VPP_ON       H3800_ASIC1_OFFSET( u8, FlashWP, VPP_ON )
macro_line|#endif /* _INCLUDE_H3600_GPIO_H_ */
eof
