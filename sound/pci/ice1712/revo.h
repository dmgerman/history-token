macro_line|#ifndef __SOUND_REVO_H
DECL|macro|__SOUND_REVO_H
mdefine_line|#define __SOUND_REVO_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   Lowlevel functions for M-Audio Revolution 7.1&n; *&n; *&t;Copyright (c) 2003 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|REVO_DEVICE_DESC
mdefine_line|#define REVO_DEVICE_DESC &bslash;&n;&t;&t;&quot;{MidiMan M Audio,Revolution 7.1},&quot;
DECL|macro|VT1724_SUBDEVICE_REVOLUTION71
mdefine_line|#define VT1724_SUBDEVICE_REVOLUTION71&t;0x12143036
multiline_comment|/* entry point */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_revo_cards
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; *  MidiMan M-Audio Revolution GPIO definitions&n; */
DECL|macro|VT1724_REVO_CCLK
mdefine_line|#define VT1724_REVO_CCLK&t;0x02
DECL|macro|VT1724_REVO_CDIN
mdefine_line|#define VT1724_REVO_CDIN&t;0x04&t;/* not used */
DECL|macro|VT1724_REVO_CDOUT
mdefine_line|#define VT1724_REVO_CDOUT&t;0x08
DECL|macro|VT1724_REVO_CS0
mdefine_line|#define VT1724_REVO_CS0&t;&t;0x10&t;/* not used */
DECL|macro|VT1724_REVO_CS1
mdefine_line|#define VT1724_REVO_CS1&t;&t;0x20&t;/* front AKM4381 chipselect */
DECL|macro|VT1724_REVO_CS2
mdefine_line|#define VT1724_REVO_CS2&t;&t;0x40&t;/* surround AKM4355 chipselect */
DECL|macro|VT1724_REVO_MUTE
mdefine_line|#define VT1724_REVO_MUTE&t;(1&lt;&lt;22)&t;/* 0 = all mute, 1 = normal operation */
macro_line|#endif /* __SOUND_REVO_H */
eof
