macro_line|#ifndef __SOUND_HOONTECH_H
DECL|macro|__SOUND_HOONTECH_H
mdefine_line|#define __SOUND_HOONTECH_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   Lowlevel functions for Hoontech STDSP24&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|HOONTECH_DEVICE_DESC
mdefine_line|#define  HOONTECH_DEVICE_DESC &bslash;&n;&t;&quot;{Hoontech SoundTrack DSP 24},&quot; &bslash;&n;&t;&quot;{Hoontech SoundTrack DSP 24 Value},&quot; &bslash;&n;&t;&quot;{Hoontech SoundTrack DSP 24 Media 7.1},&quot; &bslash;&n;
DECL|macro|ICE1712_SUBDEVICE_STDSP24
mdefine_line|#define ICE1712_SUBDEVICE_STDSP24&t;&t;0x12141217&t;/* Hoontech SoundTrack Audio DSP 24 */
DECL|macro|ICE1712_SUBDEVICE_STDSP24_MEDIA7_1
mdefine_line|#define ICE1712_SUBDEVICE_STDSP24_MEDIA7_1&t;0x16141217&t;/* Hoontech ST Audio DSP24 Media 7.1 */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_ice1712_hoontech_cards
(braket
)braket
suffix:semicolon
multiline_comment|/* Hoontech SoundTrack Audio DSP 24 GPIO definitions */
DECL|macro|ICE1712_STDSP24_0_BOX
mdefine_line|#define ICE1712_STDSP24_0_BOX(r, x)&t;r[0] = ((r[0] &amp; ~3) | ((x)&amp;3))
DECL|macro|ICE1712_STDSP24_0_DAREAR
mdefine_line|#define ICE1712_STDSP24_0_DAREAR(r, x)&t;r[0] = ((r[0] &amp; ~4) | (((x)&amp;1)&lt;&lt;2))
DECL|macro|ICE1712_STDSP24_1_CHN1
mdefine_line|#define ICE1712_STDSP24_1_CHN1(r, x)&t;r[1] = ((r[1] &amp; ~1) | ((x)&amp;1))
DECL|macro|ICE1712_STDSP24_1_CHN2
mdefine_line|#define ICE1712_STDSP24_1_CHN2(r, x)&t;r[1] = ((r[1] &amp; ~2) | (((x)&amp;1)&lt;&lt;1))
DECL|macro|ICE1712_STDSP24_1_CHN3
mdefine_line|#define ICE1712_STDSP24_1_CHN3(r, x)&t;r[1] = ((r[1] &amp; ~4) | (((x)&amp;1)&lt;&lt;2))
DECL|macro|ICE1712_STDSP24_2_CHN4
mdefine_line|#define ICE1712_STDSP24_2_CHN4(r, x)&t;r[2] = ((r[2] &amp; ~1) | ((x)&amp;1))
DECL|macro|ICE1712_STDSP24_2_MIDIIN
mdefine_line|#define ICE1712_STDSP24_2_MIDIIN(r, x)&t;r[2] = ((r[2] &amp; ~2) | (((x)&amp;1)&lt;&lt;1))
DECL|macro|ICE1712_STDSP24_2_MIDI1
mdefine_line|#define ICE1712_STDSP24_2_MIDI1(r, x)&t;r[2] = ((r[2] &amp; ~4) | (((x)&amp;1)&lt;&lt;2))
DECL|macro|ICE1712_STDSP24_3_MIDI2
mdefine_line|#define ICE1712_STDSP24_3_MIDI2(r, x)&t;r[3] = ((r[3] &amp; ~1) | ((x)&amp;1))
DECL|macro|ICE1712_STDSP24_3_MUTE
mdefine_line|#define ICE1712_STDSP24_3_MUTE(r, x)&t;r[3] = ((r[3] &amp; ~2) | (((x)&amp;1)&lt;&lt;1))
DECL|macro|ICE1712_STDSP24_3_INSEL
mdefine_line|#define ICE1712_STDSP24_3_INSEL(r, x)&t;r[3] = ((r[3] &amp; ~4) | (((x)&amp;1)&lt;&lt;2))
DECL|macro|ICE1712_STDSP24_SET_ADDR
mdefine_line|#define ICE1712_STDSP24_SET_ADDR(r, a)&t;r[a&amp;3] = ((r[a&amp;3] &amp; ~0x18) | (((a)&amp;3)&lt;&lt;3))
DECL|macro|ICE1712_STDSP24_CLOCK
mdefine_line|#define ICE1712_STDSP24_CLOCK(r, a, c)&t;r[a&amp;3] = ((r[a&amp;3] &amp; ~0x20) | (((c)&amp;1)&lt;&lt;5))
DECL|macro|ICE1712_STDSP24_CLOCK_BIT
mdefine_line|#define ICE1712_STDSP24_CLOCK_BIT&t;(1&lt;&lt;5)
multiline_comment|/* Hoontech SoundTrack Audio DSP 24 box configuration definitions */
DECL|macro|ICE1712_STDSP24_DAREAR
mdefine_line|#define ICE1712_STDSP24_DAREAR&t;&t;(1&lt;&lt;0)
DECL|macro|ICE1712_STDSP24_MUTE
mdefine_line|#define ICE1712_STDSP24_MUTE&t;&t;(1&lt;&lt;1)
DECL|macro|ICE1712_STDSP24_INSEL
mdefine_line|#define ICE1712_STDSP24_INSEL&t;&t;(1&lt;&lt;2)
DECL|macro|ICE1712_STDSP24_BOX_CHN1
mdefine_line|#define ICE1712_STDSP24_BOX_CHN1&t;(1&lt;&lt;0)&t;/* input channel 1 */
DECL|macro|ICE1712_STDSP24_BOX_CHN2
mdefine_line|#define ICE1712_STDSP24_BOX_CHN2&t;(1&lt;&lt;1)&t;/* input channel 2 */
DECL|macro|ICE1712_STDSP24_BOX_CHN3
mdefine_line|#define ICE1712_STDSP24_BOX_CHN3&t;(1&lt;&lt;2)&t;/* input channel 3 */
DECL|macro|ICE1712_STDSP24_BOX_CHN4
mdefine_line|#define ICE1712_STDSP24_BOX_CHN4&t;(1&lt;&lt;3)&t;/* input channel 4 */
DECL|macro|ICE1712_STDSP24_BOX_MIDI1
mdefine_line|#define ICE1712_STDSP24_BOX_MIDI1&t;(1&lt;&lt;8)
DECL|macro|ICE1712_STDSP24_BOX_MIDI2
mdefine_line|#define ICE1712_STDSP24_BOX_MIDI2&t;(1&lt;&lt;9)
macro_line|#endif /* __SOUND_HOONTECH_H */
eof
