macro_line|#ifndef __SOUND_PRODIGY_H
DECL|macro|__SOUND_PRODIGY_H
mdefine_line|#define __SOUND_PRODIGY_H
multiline_comment|/*&n; *   ALSA driver for VIA VT1724 (Envy24HT)&n; *&n; *   Lowlevel functions for Terratec PRODIGY cards&n; *&n; *&t;Copyright (c) 2003 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|PRODIGY_DEVICE_DESC
mdefine_line|#define  PRODIGY_DEVICE_DESC &t;       &quot;{AudioTrak,Prodigy 7.1},&quot;
DECL|macro|VT1724_SUBDEVICE_PRODIGY71
mdefine_line|#define VT1724_SUBDEVICE_PRODIGY71&t;0x33495345&t;/* PRODIGY 7.1 */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_prodigy_cards
(braket
)braket
suffix:semicolon
multiline_comment|/* GPIO bits */
DECL|macro|PRODIGY_CS8415_CS
mdefine_line|#define PRODIGY_CS8415_CS&t;(1 &lt;&lt; 23)
DECL|macro|PRODIGY_CS8415_CDTO
mdefine_line|#define PRODIGY_CS8415_CDTO&t;(1 &lt;&lt; 22)
DECL|macro|PRODIGY_WM_RESET
mdefine_line|#define PRODIGY_WM_RESET&t;(1 &lt;&lt; 20)
DECL|macro|PRODIGY_WM_CLK
mdefine_line|#define PRODIGY_WM_CLK&t;&t;(1 &lt;&lt; 19)
DECL|macro|PRODIGY_WM_DATA
mdefine_line|#define PRODIGY_WM_DATA&t;&t;(1 &lt;&lt; 18)
DECL|macro|PRODIGY_WM_RW
mdefine_line|#define PRODIGY_WM_RW&t;&t;(1 &lt;&lt; 17)
DECL|macro|PRODIGY_AC97_RESET
mdefine_line|#define PRODIGY_AC97_RESET&t;(1 &lt;&lt; 16)
DECL|macro|PRODIGY_DIGITAL_SEL1
mdefine_line|#define PRODIGY_DIGITAL_SEL1&t;(1 &lt;&lt; 15)
singleline_comment|// #define PRODIGY_HP_SEL&t;&t;(1 &lt;&lt; 14)
DECL|macro|PRODIGY_WM_CS
mdefine_line|#define PRODIGY_WM_CS&t;&t;(1 &lt;&lt; 12)
DECL|macro|PRODIGY_HP_AMP_EN
mdefine_line|#define PRODIGY_HP_AMP_EN&t;(1 &lt;&lt; 14)
multiline_comment|/* WM8770 registers */
DECL|macro|WM_DAC_ATTEN
mdefine_line|#define WM_DAC_ATTEN&t;&t;0x00&t;/* DAC1-8 analog attenuation */
DECL|macro|WM_DAC_MASTER_ATTEN
mdefine_line|#define WM_DAC_MASTER_ATTEN&t;0x08&t;/* DAC master analog attenuation */
DECL|macro|WM_DAC_DIG_ATTEN
mdefine_line|#define WM_DAC_DIG_ATTEN&t;0x09&t;/* DAC1-8 digital attenuation */
DECL|macro|WM_DAC_DIG_MATER_ATTEN
mdefine_line|#define WM_DAC_DIG_MATER_ATTEN&t;0x11&t;/* DAC master digital attenuation */
DECL|macro|WM_PHASE_SWAP
mdefine_line|#define WM_PHASE_SWAP&t;&t;0x12&t;/* DAC phase */
DECL|macro|WM_DAC_CTRL1
mdefine_line|#define WM_DAC_CTRL1&t;&t;0x13&t;/* DAC control bits */
DECL|macro|WM_MUTE
mdefine_line|#define WM_MUTE&t;&t;&t;0x14&t;/* mute controls */
DECL|macro|WM_DAC_CTRL2
mdefine_line|#define WM_DAC_CTRL2&t;&t;0x15&t;/* de-emphasis and zefo-flag */
DECL|macro|WM_INT_CTRL
mdefine_line|#define WM_INT_CTRL&t;&t;0x16&t;/* interface control */
DECL|macro|WM_MASTER
mdefine_line|#define WM_MASTER&t;&t;0x17&t;/* master clock and mode */
DECL|macro|WM_POWERDOWN
mdefine_line|#define WM_POWERDOWN&t;&t;0x18&t;/* power-down controls */
DECL|macro|WM_ADC_GAIN
mdefine_line|#define WM_ADC_GAIN&t;&t;0x19&t;/* ADC gain L(19)/R(1a) */
DECL|macro|WM_ADC_MUX
mdefine_line|#define WM_ADC_MUX&t;&t;0x1b&t;/* input MUX */
DECL|macro|WM_OUT_MUX1
mdefine_line|#define WM_OUT_MUX1&t;&t;0x1c&t;/* output MUX */
DECL|macro|WM_OUT_MUX2
mdefine_line|#define WM_OUT_MUX2&t;&t;0x1e&t;/* output MUX */
DECL|macro|WM_RESET
mdefine_line|#define WM_RESET&t;&t;0x1f&t;/* software reset */
macro_line|#endif /* __SOUND_PRODIGY_H */
eof
