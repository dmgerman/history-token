multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *&n; *  GF1 (GUS) Patch Instrument Format&n; *  Copyright (c) 1994-99 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_AINSTR_GF1_H
DECL|macro|__SOUND_AINSTR_GF1_H
mdefine_line|#define __SOUND_AINSTR_GF1_H
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  share types (share ID 1)&n; */
DECL|macro|GF1_SHARE_FILE
mdefine_line|#define GF1_SHARE_FILE&t;&t;&t;0
multiline_comment|/*&n; *  wave formats&n; */
DECL|macro|GF1_WAVE_16BIT
mdefine_line|#define GF1_WAVE_16BIT&t;&t;&t;0x0001  /* 16-bit wave */
DECL|macro|GF1_WAVE_UNSIGNED
mdefine_line|#define GF1_WAVE_UNSIGNED&t;&t;0x0002  /* unsigned wave */
DECL|macro|GF1_WAVE_INVERT
mdefine_line|#define GF1_WAVE_INVERT&t;&t;&t;0x0002  /* same as unsigned wave */
DECL|macro|GF1_WAVE_BACKWARD
mdefine_line|#define GF1_WAVE_BACKWARD&t;&t;0x0004  /* backward mode (maybe used for reverb or ping-ping loop) */
DECL|macro|GF1_WAVE_LOOP
mdefine_line|#define GF1_WAVE_LOOP&t;&t;&t;0x0008  /* loop mode */
DECL|macro|GF1_WAVE_BIDIR
mdefine_line|#define GF1_WAVE_BIDIR&t;&t;&t;0x0010  /* bidirectional mode */
DECL|macro|GF1_WAVE_STEREO
mdefine_line|#define GF1_WAVE_STEREO&t;&t;&t;0x0100&t;/* stereo mode */
DECL|macro|GF1_WAVE_ULAW
mdefine_line|#define GF1_WAVE_ULAW&t;&t;&t;0x0200&t;/* uLaw compression mode */
multiline_comment|/*&n; *  Wavetable definitions&n; */
DECL|struct|gf1_wave
r_typedef
r_struct
id|gf1_wave
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
multiline_comment|/* bits loop start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_end
r_int
r_int
id|loop_end
suffix:semicolon
multiline_comment|/* loop start offset in samples * 16 (lowest 4 bits - fraction) */
DECL|member|loop_repeat
r_int
r_int
id|loop_repeat
suffix:semicolon
multiline_comment|/* loop repeat - 0 = forever */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* GF1 patch flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|sample_rate
r_int
r_int
id|sample_rate
suffix:semicolon
multiline_comment|/* sample rate in Hz */
DECL|member|low_frequency
r_int
r_int
id|low_frequency
suffix:semicolon
multiline_comment|/* low frequency range */
DECL|member|high_frequency
r_int
r_int
id|high_frequency
suffix:semicolon
multiline_comment|/* high frequency range */
DECL|member|root_frequency
r_int
r_int
id|root_frequency
suffix:semicolon
multiline_comment|/* root frequency range */
DECL|member|tune
r_int
r_int
id|tune
suffix:semicolon
DECL|member|balance
r_int
r_char
id|balance
suffix:semicolon
DECL|member|envelope_rate
r_int
r_char
id|envelope_rate
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|envelope_offset
r_int
r_char
id|envelope_offset
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|tremolo_sweep
r_int
r_char
id|tremolo_sweep
suffix:semicolon
DECL|member|tremolo_rate
r_int
r_char
id|tremolo_rate
suffix:semicolon
DECL|member|tremolo_depth
r_int
r_char
id|tremolo_depth
suffix:semicolon
DECL|member|vibrato_sweep
r_int
r_char
id|vibrato_sweep
suffix:semicolon
DECL|member|vibrato_rate
r_int
r_char
id|vibrato_rate
suffix:semicolon
DECL|member|vibrato_depth
r_int
r_char
id|vibrato_depth
suffix:semicolon
DECL|member|scale_frequency
r_int
r_int
id|scale_frequency
suffix:semicolon
DECL|member|scale_factor
r_int
r_int
id|scale_factor
suffix:semicolon
multiline_comment|/* 0-2048 or 0-2 */
DECL|member|next
r_struct
id|gf1_wave
op_star
id|next
suffix:semicolon
DECL|typedef|gf1_wave_t
)brace
id|gf1_wave_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
DECL|macro|IWFFFF_EXCLUDE_NONE
mdefine_line|#define IWFFFF_EXCLUDE_NONE&t;&t;0x0000&t;/* exclusion mode - none */
DECL|macro|IWFFFF_EXCLUDE_SINGLE
mdefine_line|#define IWFFFF_EXCLUDE_SINGLE&t;&t;0x0001&t;/* exclude single - single note from the instrument group */
DECL|macro|IWFFFF_EXCLUDE_MULTIPLE
mdefine_line|#define IWFFFF_EXCLUDE_MULTIPLE&t;&t;0x0002&t;/* exclude multiple - stop only same note from this instrument */
DECL|macro|IWFFFF_EFFECT_NONE
mdefine_line|#define IWFFFF_EFFECT_NONE&t;&t;0
DECL|macro|IWFFFF_EFFECT_REVERB
mdefine_line|#define IWFFFF_EFFECT_REVERB&t;&t;1
DECL|macro|IWFFFF_EFFECT_CHORUS
mdefine_line|#define IWFFFF_EFFECT_CHORUS&t;&t;2
DECL|macro|IWFFFF_EFFECT_ECHO
mdefine_line|#define IWFFFF_EFFECT_ECHO&t;&t;3
r_typedef
r_struct
(brace
DECL|member|exclusion
r_int
r_int
id|exclusion
suffix:semicolon
DECL|member|exclusion_group
r_int
r_int
id|exclusion_group
suffix:semicolon
multiline_comment|/* 0 - none, 1-65535 */
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
DECL|member|wave
id|gf1_wave_t
op_star
id|wave
suffix:semicolon
multiline_comment|/* first waveform */
DECL|typedef|gf1_instrument_t
)brace
id|gf1_instrument_t
suffix:semicolon
multiline_comment|/*&n; *&n; *    Kernel &lt;-&gt; user space&n; *    Hardware (CPU) independent section&n; *&n; *    * = zero or more&n; *    + = one or more&n; *&n; *    gf1_xinstrument&t;&t;IWFFFF_STRU_INSTR&n; *      +gf1_xwave&t;&t;IWFFFF_STRU_WAVE&n; *&n; */
DECL|macro|GF1_STRU_WAVE
mdefine_line|#define GF1_STRU_WAVE&t;&t;__cpu_to_be32((&squot;W&squot;&lt;&lt;24)|(&squot;A&squot;&lt;&lt;16)|(&squot;V&squot;&lt;&lt;8)|&squot;E&squot;)
DECL|macro|GF1_STRU_INSTR
mdefine_line|#define GF1_STRU_INSTR&t;&t;__cpu_to_be32((&squot;I&squot;&lt;&lt;24)|(&squot;N&squot;&lt;&lt;16)|(&squot;S&squot;&lt;&lt;8)|&squot;T&squot;)
multiline_comment|/*&n; *  Wavetable definitions&n; */
DECL|struct|gf1_xwave
r_typedef
r_struct
id|gf1_xwave
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
multiline_comment|/* structure type */
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
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
multiline_comment|/* GF1 patch flags */
DECL|member|pad
id|__u8
id|pad
suffix:semicolon
DECL|member|sample_rate
id|__u32
id|sample_rate
suffix:semicolon
multiline_comment|/* sample rate in Hz */
DECL|member|low_frequency
id|__u32
id|low_frequency
suffix:semicolon
multiline_comment|/* low frequency range */
DECL|member|high_frequency
id|__u32
id|high_frequency
suffix:semicolon
multiline_comment|/* high frequency range */
DECL|member|root_frequency
id|__u32
id|root_frequency
suffix:semicolon
multiline_comment|/* root frequency range */
DECL|member|tune
id|__s16
id|tune
suffix:semicolon
DECL|member|balance
id|__u8
id|balance
suffix:semicolon
DECL|member|envelope_rate
id|__u8
id|envelope_rate
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|envelope_offset
id|__u8
id|envelope_offset
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|tremolo_sweep
id|__u8
id|tremolo_sweep
suffix:semicolon
DECL|member|tremolo_rate
id|__u8
id|tremolo_rate
suffix:semicolon
DECL|member|tremolo_depth
id|__u8
id|tremolo_depth
suffix:semicolon
DECL|member|vibrato_sweep
id|__u8
id|vibrato_sweep
suffix:semicolon
DECL|member|vibrato_rate
id|__u8
id|vibrato_rate
suffix:semicolon
DECL|member|vibrato_depth
id|__u8
id|vibrato_depth
suffix:semicolon
DECL|member|scale_frequency
id|__u16
id|scale_frequency
suffix:semicolon
DECL|member|scale_factor
id|__u16
id|scale_factor
suffix:semicolon
multiline_comment|/* 0-2048 or 0-2 */
DECL|typedef|gf1_xwave_t
)brace
id|gf1_xwave_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
DECL|struct|gf1_xinstrument
r_typedef
r_struct
id|gf1_xinstrument
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
DECL|member|exclusion
id|__u16
id|exclusion
suffix:semicolon
DECL|member|exclusion_group
id|__u16
id|exclusion_group
suffix:semicolon
multiline_comment|/* 0 - none, 1-65535 */
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
DECL|typedef|gf1_xinstrument_t
)brace
id|gf1_xinstrument_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument info&n; */
DECL|macro|GF1_INFO_ENVELOPE
mdefine_line|#define GF1_INFO_ENVELOPE&t;&t;(1&lt;&lt;0)
DECL|macro|GF1_INFO_TREMOLO
mdefine_line|#define GF1_INFO_TREMOLO&t;&t;(1&lt;&lt;1)
DECL|macro|GF1_INFO_VIBRATO
mdefine_line|#define GF1_INFO_VIBRATO&t;&t;(1&lt;&lt;2)
DECL|struct|gf1_info
r_typedef
r_struct
id|gf1_info
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* supported wave flags */
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
multiline_comment|/* supported features */
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
DECL|typedef|gf1_info_t
)brace
id|gf1_info_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;seq_instr.h&quot;
r_extern
r_char
op_star
id|snd_seq_gf1_id
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
id|gf1_info_t
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
id|gf1_wave_t
op_star
id|wave
comma
r_char
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
id|gf1_wave_t
op_star
id|wave
comma
r_char
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
id|gf1_wave_t
op_star
id|wave
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
DECL|typedef|snd_gf1_ops_t
)brace
id|snd_gf1_ops_t
suffix:semicolon
r_int
id|snd_seq_gf1_init
c_func
(paren
id|snd_gf1_ops_t
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
macro_line|#endif /* __SOUND_AINSTR_GF1_H */
eof
