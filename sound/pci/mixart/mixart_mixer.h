multiline_comment|/*&n; * Driver for Digigram miXart soundcards&n; *&n; * include file for mixer&n; *&n; * Copyright (c) 2003 by Digigram &lt;alsa@digigram.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __SOUND_MIXART_MIXER_H
DECL|macro|__SOUND_MIXART_MIXER_H
mdefine_line|#define __SOUND_MIXART_MIXER_H
multiline_comment|/* exported */
r_int
id|mixart_update_playback_stream_level
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|is_aes
comma
r_int
id|idx
)paren
suffix:semicolon
r_int
id|mixart_update_capture_stream_level
c_func
(paren
id|mixart_t
op_star
id|chip
comma
r_int
id|is_aes
)paren
suffix:semicolon
r_int
id|snd_mixart_create_mixer
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_MIXART_MIXER_H */
eof
