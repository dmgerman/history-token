macro_line|#ifndef __ASM_SH_HP6XX_H
DECL|macro|__ASM_SH_HP6XX_H
mdefine_line|#define __ASM_SH_HP6XX_H
multiline_comment|/*&n; * Copyright (C) 2003  Andriy Skulysh&n; */
DECL|macro|HP680_TS_IRQ
mdefine_line|#define HP680_TS_IRQ IRQ3_IRQ
DECL|macro|DAC_LCD_BRIGHTNESS
mdefine_line|#define DAC_LCD_BRIGHTNESS&t;0
DECL|macro|DAC_SPEAKER_VOLUME
mdefine_line|#define DAC_SPEAKER_VOLUME&t;1
DECL|macro|PHDR_TS_PEN_DOWN
mdefine_line|#define PHDR_TS_PEN_DOWN&t;0x08
DECL|macro|SCPDR_TS_SCAN_ENABLE
mdefine_line|#define SCPDR_TS_SCAN_ENABLE&t;0x20
DECL|macro|SCPDR_TS_SCAN_Y
mdefine_line|#define SCPDR_TS_SCAN_Y&t;&t;0x02
DECL|macro|SCPDR_TS_SCAN_X
mdefine_line|#define SCPDR_TS_SCAN_X&t;&t;0x01
DECL|macro|SCPCR_TS_ENABLE
mdefine_line|#define SCPCR_TS_ENABLE&t;&t;0x405
DECL|macro|SCPCR_TS_MASK
mdefine_line|#define SCPCR_TS_MASK&t;&t;0xc0f
DECL|macro|ADC_CHANNEL_TS_Y
mdefine_line|#define ADC_CHANNEL_TS_Y&t;1
DECL|macro|ADC_CHANNEL_TS_X
mdefine_line|#define ADC_CHANNEL_TS_X&t;2
DECL|macro|HD64461_GPADR_SPEAKER
mdefine_line|#define HD64461_GPADR_SPEAKER&t;0x01
DECL|macro|HD64461_GPADR_PCMCIA0
mdefine_line|#define HD64461_GPADR_PCMCIA0&t;(0x02|0x08)
DECL|macro|HD64461_GPBDR_LCDOFF
mdefine_line|#define HD64461_GPBDR_LCDOFF&t;0x01
DECL|macro|HD64461_GPBDR_LED_RED
mdefine_line|#define HD64461_GPBDR_LED_RED&t;0x80
macro_line|#endif /* __ASM_SH_HP6XX_H */
eof
