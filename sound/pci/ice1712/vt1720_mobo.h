macro_line|#ifndef __SOUND_VT1720_MOBO_H
DECL|macro|__SOUND_VT1720_MOBO_H
mdefine_line|#define __SOUND_VT1720_MOBO_H
multiline_comment|/*&n; *   ALSA driver for VT1720/VT1724 (Envy24PT/Envy24HT)&n; *&n; *   Lowlevel functions for VT1720-based motherboards&n; *&n; *&t;Copyright (c) 2004 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|VT1720_MOBO_DEVICE_DESC
mdefine_line|#define VT1720_MOBO_DEVICE_DESC        &quot;{Albatron,K8X800 Pro II},&quot;&bslash;&n;&t;&t;&t;&t;       &quot;{Chaintech,ZNF3-150},&quot;&bslash;&n;&t;&t;&t;&t;       &quot;{Chaintech,ZNF3-250},&quot;&bslash;&n;&t;&t;&t;&t;       &quot;{Chaintech,9CJS},&quot;
DECL|macro|VT1720_SUBDEVICE_K8X800
mdefine_line|#define VT1720_SUBDEVICE_K8X800&t;&t;0xf217052c
DECL|macro|VT1720_SUBDEVICE_ZNF3_150
mdefine_line|#define VT1720_SUBDEVICE_ZNF3_150&t;0x0f2741f6
DECL|macro|VT1720_SUBDEVICE_ZNF3_250
mdefine_line|#define VT1720_SUBDEVICE_ZNF3_250&t;0x0f2745f6
DECL|macro|VT1720_SUBDEVICE_9CJS
mdefine_line|#define VT1720_SUBDEVICE_9CJS&t;&t;0x0f272327
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1720_mobo_cards
(braket
)braket
suffix:semicolon
macro_line|#endif /* __SOUND_VT1720_MOBO_H */
eof
