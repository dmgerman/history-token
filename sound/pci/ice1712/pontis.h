macro_line|#ifndef __SOUND_PONTIS_H
DECL|macro|__SOUND_PONTIS_H
mdefine_line|#define __SOUND_PONTIS_H
multiline_comment|/*&n; *   ALSA driver for VIA VT1724 (Envy24HT)&n; *&n; *   Lowlevel functions for Pontis MS300 boards&n; *&n; *&t;Copyright (c) 2004 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|PONTIS_DEVICE_DESC
mdefine_line|#define PONTIS_DEVICE_DESC &t;       &quot;{Pontis,MS300},&quot;
DECL|macro|VT1720_SUBDEVICE_PONTIS_MS300
mdefine_line|#define VT1720_SUBDEVICE_PONTIS_MS300&t;0x00020002&t;/* a dummy id for MS300 */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1720_pontis_cards
(braket
)braket
suffix:semicolon
macro_line|#endif /* __SOUND_PONTIS_H */
eof
