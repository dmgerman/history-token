macro_line|#ifndef __EMU10K1_SYNTH_H
DECL|macro|__EMU10K1_SYNTH_H
mdefine_line|#define __EMU10K1_SYNTH_H
multiline_comment|/*&n; *  Defines for the Emu10k1 WaveTable synth&n; *&n; *  Copyright (C) 2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;emu10k1.h&quot;
macro_line|#include &quot;emux_synth.h&quot;
multiline_comment|/* sequencer device id */
DECL|macro|SNDRV_SEQ_DEV_ID_EMU10K1_SYNTH
mdefine_line|#define SNDRV_SEQ_DEV_ID_EMU10K1_SYNTH&t;&quot;emu10k1-synth&quot;
multiline_comment|/* argument for snd_seq_device_new */
DECL|struct|snd_emu10k1_synth_arg
r_typedef
r_struct
id|snd_emu10k1_synth_arg
(brace
DECL|member|hwptr
id|emu10k1_t
op_star
id|hwptr
suffix:semicolon
multiline_comment|/* chip */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* sequencer client index */
DECL|member|seq_ports
r_int
id|seq_ports
suffix:semicolon
multiline_comment|/* number of sequencer ports to be created */
DECL|member|max_voices
r_int
id|max_voices
suffix:semicolon
multiline_comment|/* maximum number of voices for wavetable */
DECL|typedef|snd_emu10k1_synth_arg_t
)brace
id|snd_emu10k1_synth_arg_t
suffix:semicolon
DECL|macro|EMU10K1_MAX_MEMSIZE
mdefine_line|#define EMU10K1_MAX_MEMSIZE&t;(32 * 1024 * 1024) /* 32MB */
macro_line|#endif
eof
