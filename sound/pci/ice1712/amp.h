macro_line|#ifndef __SOUND_AMP_H
DECL|macro|__SOUND_AMP_H
mdefine_line|#define __SOUND_AMP_H
multiline_comment|/*&n; *   ALSA driver for VIA VT1724 (Envy24HT)&n; *&n; *   Lowlevel functions for Advanced Micro Peripherals Ltd AUDIO2000&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|AMP_AUDIO2000_DEVICE_DESC
mdefine_line|#define  AMP_AUDIO2000_DEVICE_DESC &t;       &quot;{AMP Ltd AUDIO2000},&quot;
DECL|macro|VT1724_SUBDEVICE_AUDIO2000
mdefine_line|#define VT1724_SUBDEVICE_AUDIO2000&t;0x12142417&t;/* Advanced Micro Peripherals Ltd AUDIO2000 */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_amp_cards
(braket
)braket
suffix:semicolon
macro_line|#endif /* __SOUND_AMP_H */
eof
