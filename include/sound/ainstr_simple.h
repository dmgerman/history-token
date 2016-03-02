multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *&n; *  Simple (MOD player) Instrument Format&n; *  Copyright (c) 1994-99 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_AINSTR_SIMPLE_H
DECL|macro|__SOUND_AINSTR_SIMPLE_H
mdefine_line|#define __SOUND_AINSTR_SIMPLE_H
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  share types (share ID 1)&n; */
DECL|macro|SIMPLE_SHARE_FILE
mdefine_line|#define SIMPLE_SHARE_FILE&t;&t;0
multiline_comment|/*&n; *  wave formats&n; */
DECL|macro|SIMPLE_WAVE_16BIT
mdefine_line|#define SIMPLE_WAVE_16BIT&t;&t;0x0001  /* 16-bit wave */
DECL|macro|SIMPLE_WAVE_UNSIGNED
mdefine_line|#define SIMPLE_WAVE_UNSIGNED&t;&t;0x0002  /* unsigned wave */
DECL|macro|SIMPLE_WAVE_INVERT
mdefine_line|#define SIMPLE_WAVE_INVERT&t;&t;0x0002  /* same as unsigned wave */
DECL|macro|SIMPLE_WAVE_BACKWARD
mdefine_line|#define SIMPLE_WAVE_BACKWARD&t;&t;0x0004  /* backward mode (maybe used for reverb or ping-ping loop) */
DECL|macro|SIMPLE_WAVE_LOOP
mdefine_line|#define SIMPLE_WAVE_LOOP&t;&t;0x0008  /* loop mode */
DECL|macro|SIMPLE_WAVE_BIDIR
mdefine_line|#define SIMPLE_WAVE_BIDIR&t;&t;0x0010  /* bidirectional mode */
DECL|macro|SIMPLE_WAVE_STEREO
mdefine_line|#define SIMPLE_WAVE_STEREO&t;&t;0x0100&t;/* stereo wave */
DECL|macro|SIMPLE_WAVE_ULAW
mdefine_line|#define SIMPLE_WAVE_ULAW&t;&t;0x0200&t;/* uLaw compression mode */
multiline_comment|/*&n; *  instrument effects&n; */
DECL|macro|SIMPLE_EFFECT_NONE
mdefine_line|#define SIMPLE_EFFECT_NONE&t;&t;0
DECL|macro|SIMPLE_EFFECT_REVERB
mdefine_line|#define SIMPLE_EFFECT_REVERB&t;&t;1
DECL|macro|SIMPLE_EFFECT_CHORUS
mdefine_line|#define SIMPLE_EFFECT_CHORUS&t;&t;2
DECL|macro|SIMPLE_EFFECT_ECHO
mdefine_line|#define SIMPLE_EFFECT_ECHO&t;&t;3
multiline_comment|/*&n; *  instrument info&n; */
DECL|struct|simple_instrument_info
r_typedef
r_struct
id|simple_instrument_info
(brace
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* supported format bits */
DECL|member|effects
r_int
r_int
id|effects
suffix:semicolon
multiline_comment|/* supported effects (1 &lt;&lt; SIMPLE_EFFECT_*) */
DECL|member|max8_len
r_int
r_int
id|max8_len
suffix:semicolon
multiline_comment|/* maximum 8-bit wave length */
DECL|member|max16_len
r_int
r_int
id|max16_len
suffix:semicolon
multiline_comment|/* maximum 16-bit wave length */
DECL|typedef|simple_instrument_info_t
)brace
id|simple_instrument_info_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
r_typedef
r_struct
(brace
DECL|member|share_id
r_int
r_int
id|share_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* share id - zero = no sharing */
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* wave format */
r_struct
(brace
DECL|member|number
r_int
r_int
id|number
suffix:semicolon
multiline_comment|/* some other ID for this instrument */
DECL|member|memory
r_int
r_int
id|memory
suffix:semicolon
multiline_comment|/* begin of waveform in onboard memory */
DECL|member|ptr
r_int
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* pointer to waveform in system memory */
DECL|member|address
)brace
id|address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of waveform in samples */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_start
r_int
r_int
id|loop_start
suffix:semicolon
multiline_comment|/* loop start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_end
r_int
r_int
id|loop_end
suffix:semicolon
multiline_comment|/* loop end offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_repeat
r_int
r_int
id|loop_repeat
suffix:semicolon
multiline_comment|/* loop repeat - 0 = forever */
DECL|member|effect1
r_int
r_char
id|effect1
suffix:semicolon
multiline_comment|/* effect 1 */
DECL|member|effect1_depth
r_int
r_char
id|effect1_depth
suffix:semicolon
multiline_comment|/* 0-127 */
DECL|member|effect2
r_int
r_char
id|effect2
suffix:semicolon
multiline_comment|/* effect 2 */
DECL|member|effect2_depth
r_int
r_char
id|effect2_depth
suffix:semicolon
multiline_comment|/* 0-127 */
DECL|typedef|simple_instrument_t
)brace
id|simple_instrument_t
suffix:semicolon
multiline_comment|/*&n; *&n; *    Kernel &lt;-&gt; user space&n; *    Hardware (CPU) independent section&n; *&n; *    * = zero or more&n; *    + = one or more&n; *&n; *    simple_xinstrument&t;SIMPLE_STRU_INSTR&n; *&n; */
DECL|macro|SIMPLE_STRU_INSTR
mdefine_line|#define SIMPLE_STRU_INSTR&t;__cpu_to_be32((&squot;I&squot;&lt;&lt;24)|(&squot;N&squot;&lt;&lt;16)|(&squot;S&squot;&lt;&lt;8)|&squot;T&squot;)
multiline_comment|/*&n; *  Instrument&n; */
DECL|struct|simple_xinstrument
r_typedef
r_struct
id|simple_xinstrument
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
DECL|member|share_id
id|__u32
id|share_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* share id - zero = no sharing */
DECL|member|format
id|__u32
id|format
suffix:semicolon
multiline_comment|/* wave format */
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/* size of waveform in samples */
DECL|member|start
id|__u32
id|start
suffix:semicolon
multiline_comment|/* start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_start
id|__u32
id|loop_start
suffix:semicolon
multiline_comment|/* bits loop start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_end
id|__u32
id|loop_end
suffix:semicolon
multiline_comment|/* loop start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_repeat
id|__u16
id|loop_repeat
suffix:semicolon
multiline_comment|/* loop repeat - 0 = forever */
DECL|member|effect1
id|__u8
id|effect1
suffix:semicolon
multiline_comment|/* effect 1 */
DECL|member|effect1_depth
id|__u8
id|effect1_depth
suffix:semicolon
multiline_comment|/* 0-127 */
DECL|member|effect2
id|__u8
id|effect2
suffix:semicolon
multiline_comment|/* effect 2 */
DECL|member|effect2_depth
id|__u8
id|effect2_depth
suffix:semicolon
multiline_comment|/* 0-127 */
DECL|typedef|simple_xinstrument_t
)brace
id|simple_xinstrument_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;seq_instr.h&quot;
r_extern
r_char
op_star
id|snd_seq_simple_id
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|info
r_int
(paren
op_star
id|info
)paren
(paren
r_void
op_star
id|private_data
comma
id|simple_instrument_info_t
op_star
id|info
)paren
suffix:semicolon
DECL|member|put_sample
r_int
(paren
op_star
id|put_sample
)paren
(paren
r_void
op_star
id|private_data
comma
id|simple_instrument_t
op_star
id|instr
comma
r_char
id|__user
op_star
id|data
comma
r_int
id|len
comma
r_int
id|atomic
)paren
suffix:semicolon
DECL|member|get_sample
r_int
(paren
op_star
id|get_sample
)paren
(paren
r_void
op_star
id|private_data
comma
id|simple_instrument_t
op_star
id|instr
comma
r_char
id|__user
op_star
id|data
comma
r_int
id|len
comma
r_int
id|atomic
)paren
suffix:semicolon
DECL|member|remove_sample
r_int
(paren
op_star
id|remove_sample
)paren
(paren
r_void
op_star
id|private_data
comma
id|simple_instrument_t
op_star
id|instr
comma
r_int
id|atomic
)paren
suffix:semicolon
DECL|member|notify
r_void
(paren
op_star
id|notify
)paren
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_int
id|what
)paren
suffix:semicolon
DECL|member|kops
id|snd_seq_kinstr_ops_t
id|kops
suffix:semicolon
DECL|typedef|snd_simple_ops_t
)brace
id|snd_simple_ops_t
suffix:semicolon
r_int
id|snd_seq_simple_init
c_func
(paren
id|snd_simple_ops_t
op_star
id|ops
comma
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_ops_t
op_star
id|next
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_AINSTR_SIMPLE_H */
eof
