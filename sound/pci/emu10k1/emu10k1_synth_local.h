macro_line|#ifndef __EMU10K1_SYNTH_LOCAL_H
DECL|macro|__EMU10K1_SYNTH_LOCAL_H
mdefine_line|#define __EMU10K1_SYNTH_LOCAL_H
multiline_comment|/*&n; *  Local defininitons for Emu10k1 wavetable&n; *&n; *  Copyright (C) 2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1_synth.h&gt;
multiline_comment|/* emu10k1_patch.c */
r_int
id|snd_emu10k1_sample_new
c_func
(paren
id|snd_emux_t
op_star
id|private_data
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_const
r_void
op_star
id|_data
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_emu10k1_sample_free
c_func
(paren
id|snd_emux_t
op_star
id|private_data
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
)paren
suffix:semicolon
r_int
id|snd_emu10k1_memhdr_init
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
suffix:semicolon
multiline_comment|/* emu10k1_callback.c */
r_void
id|snd_emu10k1_ops_setup
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
suffix:semicolon
r_int
id|snd_emu10k1_synth_get_voice
c_func
(paren
id|emu10k1_t
op_star
id|hw
)paren
suffix:semicolon
macro_line|#endif&t;/* __EMU10K1_SYNTH_LOCAL_H */
eof
