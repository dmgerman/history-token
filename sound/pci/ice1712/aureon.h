macro_line|#ifndef __SOUND_AUREON_H
DECL|macro|__SOUND_AUREON_H
mdefine_line|#define __SOUND_AUREON_H
multiline_comment|/*&n; *   ALSA driver for VIA VT1724 (Envy24HT)&n; *&n; *   Lowlevel functions for Terratec Aureon cards&n; *&n; *&t;Copyright (c) 2003 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|AUREON_DEVICE_DESC
mdefine_line|#define  AUREON_DEVICE_DESC &t;       &quot;{Terratec,Aureon 5.1 Sky},&quot;&bslash;&n;&t;&t;&t;&t;       &quot;{Terratec,Aureon 7.1 Space},&quot;&bslash;&n;&t;&t;&t;&t;       &quot;{Terratec,Aureon 7.1 Universe},&quot; &bslash;&n;&t;&t;&t;&t;&t;&quot;{AudioTrak,Prodigy 7.1},&quot;
DECL|macro|VT1724_SUBDEVICE_AUREON51_SKY
mdefine_line|#define VT1724_SUBDEVICE_AUREON51_SKY&t;0x3b154711&t;/* Aureon 5.1 Sky */
DECL|macro|VT1724_SUBDEVICE_AUREON71_SPACE
mdefine_line|#define VT1724_SUBDEVICE_AUREON71_SPACE&t;0x3b154511&t;/* Aureon 7.1 Space */
DECL|macro|VT1724_SUBDEVICE_AUREON71_UNIVERSE
mdefine_line|#define VT1724_SUBDEVICE_AUREON71_UNIVERSE&t;0x3b155311&t;/* Aureon 7.1 Universe */
DECL|macro|VT1724_SUBDEVICE_PRODIGY71
mdefine_line|#define VT1724_SUBDEVICE_PRODIGY71&t;0x33495345&t;/* PRODIGY 7.1 */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_aureon_cards
(braket
)braket
suffix:semicolon
multiline_comment|/* GPIO bits */
DECL|macro|AUREON_CS8415_CS
mdefine_line|#define AUREON_CS8415_CS&t;(1 &lt;&lt; 22)
DECL|macro|AUREON_SPI_MISO
mdefine_line|#define AUREON_SPI_MISO&t;&t;(1 &lt;&lt; 21)
DECL|macro|AUREON_WM_RESET
mdefine_line|#define AUREON_WM_RESET&t;&t;(1 &lt;&lt; 20)
DECL|macro|AUREON_SPI_CLK
mdefine_line|#define AUREON_SPI_CLK&t;&t;(1 &lt;&lt; 19)
DECL|macro|AUREON_SPI_MOSI
mdefine_line|#define AUREON_SPI_MOSI&t;&t;(1 &lt;&lt; 18)
DECL|macro|AUREON_WM_RW
mdefine_line|#define AUREON_WM_RW&t;&t;(1 &lt;&lt; 17)
DECL|macro|AUREON_AC97_RESET
mdefine_line|#define AUREON_AC97_RESET&t;(1 &lt;&lt; 16)
DECL|macro|AUREON_DIGITAL_SEL1
mdefine_line|#define AUREON_DIGITAL_SEL1&t;(1 &lt;&lt; 15)
DECL|macro|AUREON_HP_SEL
mdefine_line|#define AUREON_HP_SEL&t;&t;(1 &lt;&lt; 14)
DECL|macro|AUREON_WM_CS
mdefine_line|#define AUREON_WM_CS&t;&t;(1 &lt;&lt; 12)
DECL|macro|AUREON_AC97_COMMIT
mdefine_line|#define AUREON_AC97_COMMIT&t;(1 &lt;&lt; 11)
DECL|macro|AUREON_AC97_ADDR
mdefine_line|#define AUREON_AC97_ADDR&t;(1 &lt;&lt; 10)
DECL|macro|AUREON_AC97_DATA_LOW
mdefine_line|#define AUREON_AC97_DATA_LOW&t;(1 &lt;&lt; 9)
DECL|macro|AUREON_AC97_DATA_HIGH
mdefine_line|#define AUREON_AC97_DATA_HIGH&t;(1 &lt;&lt; 8)
DECL|macro|AUREON_AC97_DATA_MASK
mdefine_line|#define AUREON_AC97_DATA_MASK&t;0xFF
macro_line|#endif /* __SOUND_AUREON_H */
eof
