multiline_comment|/*&n; * Hardware specific definitions for SL-C7xx series of PDAs&n; *&n; * Copyright (c) 2004-2005 Richard Purdie&n; *&n; * Based on Sharp&squot;s 2.4 kernel patches&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_CORGI_H
DECL|macro|__ASM_ARCH_CORGI_H
mdefine_line|#define __ASM_ARCH_CORGI_H  1
multiline_comment|/*&n; * Corgi (Non Standard) GPIO Definitions&n; */
DECL|macro|CORGI_GPIO_KEY_INT
mdefine_line|#define CORGI_GPIO_KEY_INT&t;&t;&t;(0)&t;/* Keyboard Interrupt */
DECL|macro|CORGI_GPIO_AC_IN
mdefine_line|#define CORGI_GPIO_AC_IN&t;&t;&t;(1)
DECL|macro|CORGI_GPIO_WAKEUP
mdefine_line|#define CORGI_GPIO_WAKEUP&t;&t;&t;(3)
DECL|macro|CORGI_GPIO_AK_INT
mdefine_line|#define CORGI_GPIO_AK_INT&t;&t;&t;(4)&t;/* IR Controller Interrupt */
DECL|macro|CORGI_GPIO_TP_INT
mdefine_line|#define CORGI_GPIO_TP_INT&t;&t;&t;(5)&t;/* Touch Panel Interrupt */
DECL|macro|CORGI_GPIO_nSD_WP
mdefine_line|#define CORGI_GPIO_nSD_WP&t;&t;&t;(7)
DECL|macro|CORGI_GPIO_nSD_DETECT
mdefine_line|#define CORGI_GPIO_nSD_DETECT&t;&t;(9) /* MMC/SD Card Detect */
DECL|macro|CORGI_GPIO_nSD_INT
mdefine_line|#define CORGI_GPIO_nSD_INT&t;&t;&t;(10)
DECL|macro|CORGI_GPIO_MAIN_BAT_LOW
mdefine_line|#define CORGI_GPIO_MAIN_BAT_LOW&t;&t;(11)
DECL|macro|CORGI_GPIO_BAT_COVER
mdefine_line|#define CORGI_GPIO_BAT_COVER&t;&t;(11)
DECL|macro|CORGI_GPIO_LED_ORANGE
mdefine_line|#define CORGI_GPIO_LED_ORANGE&t;&t;(13)
DECL|macro|CORGI_GPIO_CF_CD
mdefine_line|#define CORGI_GPIO_CF_CD&t;&t;&t;(14) /* Compact Flash Card Detect */
DECL|macro|CORGI_GPIO_CHRG_FULL
mdefine_line|#define CORGI_GPIO_CHRG_FULL&t;&t;(16)
DECL|macro|CORGI_GPIO_CF_IRQ
mdefine_line|#define CORGI_GPIO_CF_IRQ&t;&t;&t;(17) /* Compact Flash Interrupt */
DECL|macro|CORGI_GPIO_LCDCON_CS
mdefine_line|#define CORGI_GPIO_LCDCON_CS&t;&t;(19) /* LCD Control Chip Select */
DECL|macro|CORGI_GPIO_MAX1111_CS
mdefine_line|#define CORGI_GPIO_MAX1111_CS&t;&t;(20) /* MAX111 Chip Select */
DECL|macro|CORGI_GPIO_ADC_TEMP_ON
mdefine_line|#define CORGI_GPIO_ADC_TEMP_ON&t;&t;(21)
DECL|macro|CORGI_GPIO_IR_ON
mdefine_line|#define CORGI_GPIO_IR_ON&t;&t;&t;(22)
DECL|macro|CORGI_GPIO_ADS7846_CS
mdefine_line|#define CORGI_GPIO_ADS7846_CS&t;&t;(24) /* ADS7846 Chip Select */
DECL|macro|CORGI_GPIO_SD_PWR
mdefine_line|#define CORGI_GPIO_SD_PWR&t;&t;&t;(33) /* MMC/SD Power */
DECL|macro|CORGI_GPIO_CHRG_ON
mdefine_line|#define CORGI_GPIO_CHRG_ON&t;&t;&t;(38)
DECL|macro|CORGI_GPIO_DISCHARGE_ON
mdefine_line|#define CORGI_GPIO_DISCHARGE_ON&t;&t;(42)
DECL|macro|CORGI_GPIO_HSYNC
mdefine_line|#define CORGI_GPIO_HSYNC&t;&t;&t;(44) /* LCD HSync Pulse */
DECL|macro|CORGI_GPIO_USB_PULLUP
mdefine_line|#define CORGI_GPIO_USB_PULLUP&t;&t;(45)
multiline_comment|/*&n; * Corgi Keyboard Definitions&n; */
DECL|macro|CORGI_KEY_STROBE_NUM
mdefine_line|#define CORGI_KEY_STROBE_NUM&t;&t;(12)
DECL|macro|CORGI_KEY_SENSE_NUM
mdefine_line|#define CORGI_KEY_SENSE_NUM&t;&t;&t;(8)
DECL|macro|CORGI_GPIO_ALL_STROBE_BIT
mdefine_line|#define CORGI_GPIO_ALL_STROBE_BIT&t;(0x00003ffc)
DECL|macro|CORGI_GPIO_HIGH_SENSE_BIT
mdefine_line|#define CORGI_GPIO_HIGH_SENSE_BIT&t;(0xfc000000)
DECL|macro|CORGI_GPIO_HIGH_SENSE_RSHIFT
mdefine_line|#define CORGI_GPIO_HIGH_SENSE_RSHIFT&t;(26)
DECL|macro|CORGI_GPIO_LOW_SENSE_BIT
mdefine_line|#define CORGI_GPIO_LOW_SENSE_BIT&t;(0x00000003)
DECL|macro|CORGI_GPIO_LOW_SENSE_LSHIFT
mdefine_line|#define CORGI_GPIO_LOW_SENSE_LSHIFT&t;(6)
DECL|macro|CORGI_GPIO_STROBE_BIT
mdefine_line|#define CORGI_GPIO_STROBE_BIT(a)&t;GPIO_bit(66+(a))
DECL|macro|CORGI_GPIO_SENSE_BIT
mdefine_line|#define CORGI_GPIO_SENSE_BIT(a)&t;&t;GPIO_bit(58+(a))
DECL|macro|CORGI_GAFR_ALL_STROBE_BIT
mdefine_line|#define CORGI_GAFR_ALL_STROBE_BIT&t;(0x0ffffff0)
DECL|macro|CORGI_GAFR_HIGH_SENSE_BIT
mdefine_line|#define CORGI_GAFR_HIGH_SENSE_BIT&t;(0xfff00000)
DECL|macro|CORGI_GAFR_LOW_SENSE_BIT
mdefine_line|#define CORGI_GAFR_LOW_SENSE_BIT&t;(0x0000000f)
DECL|macro|CORGI_GPIO_KEY_SENSE
mdefine_line|#define CORGI_GPIO_KEY_SENSE(a)&t;&t;(58+(a))
DECL|macro|CORGI_GPIO_KEY_STROBE
mdefine_line|#define CORGI_GPIO_KEY_STROBE(a)&t;(66+(a))
multiline_comment|/*&n; * Corgi Interrupts&n; */
DECL|macro|CORGI_IRQ_GPIO_KEY_INT
mdefine_line|#define CORGI_IRQ_GPIO_KEY_INT&t;&t;IRQ_GPIO(0)
DECL|macro|CORGI_IRQ_GPIO_AC_IN
mdefine_line|#define CORGI_IRQ_GPIO_AC_IN&t;&t;IRQ_GPIO(1)
DECL|macro|CORGI_IRQ_GPIO_WAKEUP
mdefine_line|#define CORGI_IRQ_GPIO_WAKEUP&t;&t;IRQ_GPIO(3)
DECL|macro|CORGI_IRQ_GPIO_AK_INT
mdefine_line|#define CORGI_IRQ_GPIO_AK_INT&t;&t;IRQ_GPIO(4)
DECL|macro|CORGI_IRQ_GPIO_TP_INT
mdefine_line|#define CORGI_IRQ_GPIO_TP_INT&t;&t;IRQ_GPIO(5)
DECL|macro|CORGI_IRQ_GPIO_nSD_DETECT
mdefine_line|#define CORGI_IRQ_GPIO_nSD_DETECT&t;IRQ_GPIO(9)
DECL|macro|CORGI_IRQ_GPIO_nSD_INT
mdefine_line|#define CORGI_IRQ_GPIO_nSD_INT&t;&t;IRQ_GPIO(10)
DECL|macro|CORGI_IRQ_GPIO_MAIN_BAT_LOW
mdefine_line|#define CORGI_IRQ_GPIO_MAIN_BAT_LOW&t;IRQ_GPIO(11)
DECL|macro|CORGI_IRQ_GPIO_CF_CD
mdefine_line|#define CORGI_IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO(14)
DECL|macro|CORGI_IRQ_GPIO_CHRG_FULL
mdefine_line|#define CORGI_IRQ_GPIO_CHRG_FULL&t;IRQ_GPIO(16)&t;/* Battery fully charged */
DECL|macro|CORGI_IRQ_GPIO_CF_IRQ
mdefine_line|#define CORGI_IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO(17)
DECL|macro|CORGI_IRQ_GPIO_KEY_SENSE
mdefine_line|#define CORGI_IRQ_GPIO_KEY_SENSE(a)&t;IRQ_GPIO(58+(a))&t;/* Keyboard Sense lines */
multiline_comment|/*&n; * Corgi SCOOP GPIOs and Config&n; */
DECL|macro|CORGI_SCP_LED_GREEN
mdefine_line|#define CORGI_SCP_LED_GREEN&t;&t;SCOOP_GPCR_PA11
DECL|macro|CORGI_SCP_SWA
mdefine_line|#define CORGI_SCP_SWA&t;&t;&t;SCOOP_GPCR_PA12  /* Hinge Switch A */
DECL|macro|CORGI_SCP_SWB
mdefine_line|#define CORGI_SCP_SWB&t;&t;&t;SCOOP_GPCR_PA13  /* Hinge Switch B */
DECL|macro|CORGI_SCP_MUTE_L
mdefine_line|#define CORGI_SCP_MUTE_L&t;&t;SCOOP_GPCR_PA14
DECL|macro|CORGI_SCP_MUTE_R
mdefine_line|#define CORGI_SCP_MUTE_R&t;&t;SCOOP_GPCR_PA15
DECL|macro|CORGI_SCP_AKIN_PULLUP
mdefine_line|#define CORGI_SCP_AKIN_PULLUP&t;SCOOP_GPCR_PA16
DECL|macro|CORGI_SCP_APM_ON
mdefine_line|#define CORGI_SCP_APM_ON&t;&t;SCOOP_GPCR_PA17
DECL|macro|CORGI_SCP_BACKLIGHT_CONT
mdefine_line|#define CORGI_SCP_BACKLIGHT_CONT&t;SCOOP_GPCR_PA18
DECL|macro|CORGI_SCP_MIC_BIAS
mdefine_line|#define CORGI_SCP_MIC_BIAS&t;&t;SCOOP_GPCR_PA19
DECL|macro|CORGI_SCOOP_IO_DIR
mdefine_line|#define CORGI_SCOOP_IO_DIR&t;( CORGI_SCP_LED_GREEN | CORGI_SCP_MUTE_L | CORGI_SCP_MUTE_R | &bslash;&n;&t;&t;&t;CORGI_SCP_AKIN_PULLUP | CORGI_SCP_APM_ON | CORGI_SCP_BACKLIGHT_CONT | &bslash;&n;&t;&t;&t;CORGI_SCP_MIC_BIAS )
DECL|macro|CORGI_SCOOP_IO_OUT
mdefine_line|#define CORGI_SCOOP_IO_OUT&t;( CORGI_SCP_MUTE_L | CORGI_SCP_MUTE_R )
multiline_comment|/*&n; * Corgi Parameter Area Definitions&n; */
DECL|macro|FLASH_MEM_BASE
mdefine_line|#define FLASH_MEM_BASE&t;0xa0000a00
DECL|macro|FLASH_MAGIC_CHG
mdefine_line|#define FLASH_MAGIC_CHG(a,b,c,d) ( ( d &lt;&lt; 24 ) | ( c &lt;&lt; 16 )  | ( b &lt;&lt; 8 ) | a )
DECL|macro|FLASH_COMADJ_MAJIC
mdefine_line|#define FLASH_COMADJ_MAJIC&t;FLASH_MAGIC_CHG(&squot;C&squot;,&squot;M&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_COMADJ_MAGIC_ADR
mdefine_line|#define&t;FLASH_COMADJ_MAGIC_ADR&t;0x00
DECL|macro|FLASH_COMADJ_DATA_ADR
mdefine_line|#define&t;FLASH_COMADJ_DATA_ADR&t;0x04
DECL|macro|FLASH_PHAD_MAJIC
mdefine_line|#define FLASH_PHAD_MAJIC&t;FLASH_MAGIC_CHG(&squot;P&squot;,&squot;H&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_PHAD_MAGIC_ADR
mdefine_line|#define&t;FLASH_PHAD_MAGIC_ADR&t;0x38
DECL|macro|FLASH_PHAD_DATA_ADR
mdefine_line|#define&t;FLASH_PHAD_DATA_ADR&t;0x3C
DECL|struct|sharpsl_flash_param_info
r_struct
id|sharpsl_flash_param_info
(brace
DECL|member|comadj_keyword
r_int
r_int
id|comadj_keyword
suffix:semicolon
DECL|member|comadj
r_int
r_int
id|comadj
suffix:semicolon
DECL|member|uuid_keyword
r_int
r_int
id|uuid_keyword
suffix:semicolon
DECL|member|uuid
r_int
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|touch_keyword
r_int
r_int
id|touch_keyword
suffix:semicolon
DECL|member|touch1
r_int
r_int
id|touch1
suffix:semicolon
DECL|member|touch2
r_int
r_int
id|touch2
suffix:semicolon
DECL|member|touch3
r_int
r_int
id|touch3
suffix:semicolon
DECL|member|touch4
r_int
r_int
id|touch4
suffix:semicolon
DECL|member|adadj_keyword
r_int
r_int
id|adadj_keyword
suffix:semicolon
DECL|member|adadj
r_int
r_int
id|adadj
suffix:semicolon
DECL|member|phad_keyword
r_int
r_int
id|phad_keyword
suffix:semicolon
DECL|member|phadadj
r_int
r_int
id|phadadj
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASM_ARCH_CORGI_H  */
eof
