macro_line|#ifndef __SOUND_PHASE_H
DECL|macro|__SOUND_PHASE_H
mdefine_line|#define __SOUND_PHASE_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   Lowlevel functions for Terratec PHASE 22&n; *&n; *&t;Copyright (c) 2005 Misha Zhilin &lt;misha@epiphan.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|PHASE_DEVICE_DESC
mdefine_line|#define PHASE_DEVICE_DESC &quot;{Terratec,Phase 22},&quot;
DECL|macro|VT1724_SUBDEVICE_PHASE22
mdefine_line|#define VT1724_SUBDEVICE_PHASE22&t;0x3b155011
multiline_comment|/* entry point */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_phase_cards
(braket
)braket
suffix:semicolon
macro_line|#endif /* __SOUND_PHASE */
eof
