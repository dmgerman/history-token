multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *&n; *  InterWave FFFF Instrument Format&n; *  Copyright (c) 1994-99 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_AINSTR_IW_H
DECL|macro|__SOUND_AINSTR_IW_H
mdefine_line|#define __SOUND_AINSTR_IW_H
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  share types (share ID 1)&n; */
DECL|macro|IWFFFF_SHARE_FILE
mdefine_line|#define IWFFFF_SHARE_FILE&t;&t;0
multiline_comment|/*&n; *  wave formats&n; */
DECL|macro|IWFFFF_WAVE_16BIT
mdefine_line|#define IWFFFF_WAVE_16BIT&t;&t;0x0001  /* 16-bit wave */
DECL|macro|IWFFFF_WAVE_UNSIGNED
mdefine_line|#define IWFFFF_WAVE_UNSIGNED&t;&t;0x0002  /* unsigned wave */
DECL|macro|IWFFFF_WAVE_INVERT
mdefine_line|#define IWFFFF_WAVE_INVERT&t;&t;0x0002  /* same as unsigned wave */
DECL|macro|IWFFFF_WAVE_BACKWARD
mdefine_line|#define IWFFFF_WAVE_BACKWARD&t;&t;0x0004  /* backward mode (maybe used for reverb or ping-ping loop) */
DECL|macro|IWFFFF_WAVE_LOOP
mdefine_line|#define IWFFFF_WAVE_LOOP&t;&t;0x0008  /* loop mode */
DECL|macro|IWFFFF_WAVE_BIDIR
mdefine_line|#define IWFFFF_WAVE_BIDIR&t;&t;0x0010  /* bidirectional mode */
DECL|macro|IWFFFF_WAVE_ULAW
mdefine_line|#define IWFFFF_WAVE_ULAW&t;&t;0x0020  /* uLaw compressed wave */
DECL|macro|IWFFFF_WAVE_RAM
mdefine_line|#define IWFFFF_WAVE_RAM&t;&t;&t;0x0040  /* wave is _preloaded_ in RAM (it is used for ROM simulation) */
DECL|macro|IWFFFF_WAVE_ROM
mdefine_line|#define IWFFFF_WAVE_ROM&t;&t;&t;0x0080  /* wave is in ROM */
DECL|macro|IWFFFF_WAVE_STEREO
mdefine_line|#define IWFFFF_WAVE_STEREO&t;&t;0x0100&t;/* wave is stereo */
multiline_comment|/*&n; *  Wavetable definitions&n; */
DECL|struct|iwffff_wave
r_typedef
r_struct
id|iwffff_wave
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
multiline_comment|/* some other ID for this wave */
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
DECL|member|sample_ratio
r_int
r_int
id|sample_ratio
suffix:semicolon
multiline_comment|/* sample ratio (44100 * 1024 / rate) */
DECL|member|attenuation
r_int
r_char
id|attenuation
suffix:semicolon
multiline_comment|/* 0 - 127 (no corresponding midi controller) */
DECL|member|low_note
r_int
r_char
id|low_note
suffix:semicolon
multiline_comment|/* lower frequency range for this waveform */
DECL|member|high_note
r_int
r_char
id|high_note
suffix:semicolon
multiline_comment|/* higher frequency range for this waveform */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|next
r_struct
id|iwffff_wave
op_star
id|next
suffix:semicolon
DECL|typedef|iwffff_wave_t
)brace
id|iwffff_wave_t
suffix:semicolon
multiline_comment|/*&n; *  Layer&n; */
DECL|macro|IWFFFF_LFO_SHAPE_TRIANGLE
mdefine_line|#define IWFFFF_LFO_SHAPE_TRIANGLE&t;0
DECL|macro|IWFFFF_LFO_SHAPE_POSTRIANGLE
mdefine_line|#define IWFFFF_LFO_SHAPE_POSTRIANGLE&t;1
DECL|struct|iwffff_lfo
r_typedef
r_struct
id|iwffff_lfo
(brace
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* (0-2047) 0.01Hz - 21.5Hz */
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
multiline_comment|/* volume +- (0-255) 0.48675dB/step */
DECL|member|sweep
r_int
r_int
id|sweep
suffix:semicolon
multiline_comment|/* 0 - 950 deciseconds */
DECL|member|shape
r_int
r_char
id|shape
suffix:semicolon
multiline_comment|/* see to IWFFFF_LFO_SHAPE_XXXX */
DECL|member|delay
r_int
r_char
id|delay
suffix:semicolon
multiline_comment|/* 0 - 255 deciseconds */
DECL|typedef|iwffff_lfo_t
)brace
id|iwffff_lfo_t
suffix:semicolon
DECL|macro|IWFFFF_ENV_FLAG_RETRIGGER
mdefine_line|#define IWFFFF_ENV_FLAG_RETRIGGER&t;0x0001&t;/* flag - retrigger */
DECL|macro|IWFFFF_ENV_MODE_ONE_SHOT
mdefine_line|#define IWFFFF_ENV_MODE_ONE_SHOT&t;0x0001&t;/* mode - one shot */
DECL|macro|IWFFFF_ENV_MODE_SUSTAIN
mdefine_line|#define IWFFFF_ENV_MODE_SUSTAIN&t;&t;0x0002&t;/* mode - sustain */
DECL|macro|IWFFFF_ENV_MODE_NO_SUSTAIN
mdefine_line|#define IWFFFF_ENV_MODE_NO_SUSTAIN&t;0x0003&t;/* mode - no sustain */
DECL|macro|IWFFFF_ENV_INDEX_VELOCITY
mdefine_line|#define IWFFFF_ENV_INDEX_VELOCITY&t;0x0001&t;/* index - velocity */
DECL|macro|IWFFFF_ENV_INDEX_FREQUENCY
mdefine_line|#define IWFFFF_ENV_INDEX_FREQUENCY&t;0x0002&t;/* index - frequency */
DECL|struct|iwffff_env_point
r_typedef
r_struct
id|iwffff_env_point
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
DECL|typedef|iwffff_env_point_t
)brace
id|iwffff_env_point_t
suffix:semicolon
DECL|struct|iwffff_env_record
r_typedef
r_struct
id|iwffff_env_record
(brace
DECL|member|nattack
r_int
r_int
id|nattack
suffix:semicolon
DECL|member|nrelease
r_int
r_int
id|nrelease
suffix:semicolon
DECL|member|sustain_offset
r_int
r_int
id|sustain_offset
suffix:semicolon
DECL|member|sustain_rate
r_int
r_int
id|sustain_rate
suffix:semicolon
DECL|member|release_rate
r_int
r_int
id|release_rate
suffix:semicolon
DECL|member|hirange
r_int
r_char
id|hirange
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|next
r_struct
id|iwffff_env_record
op_star
id|next
suffix:semicolon
multiline_comment|/* points are stored here */
multiline_comment|/* count of points = nattack + nrelease */
DECL|typedef|iwffff_env_record_t
)brace
id|iwffff_env_record_t
suffix:semicolon
DECL|struct|iwffff_env
r_typedef
r_struct
id|iwffff_env
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
DECL|member|index
r_int
r_char
id|index
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|record
r_struct
id|iwffff_env_record
op_star
id|record
suffix:semicolon
DECL|typedef|iwffff_env_t
)brace
id|iwffff_env_t
suffix:semicolon
DECL|macro|IWFFFF_LAYER_FLAG_RETRIGGER
mdefine_line|#define IWFFFF_LAYER_FLAG_RETRIGGER&t;0x0001&t;/* retrigger */
DECL|macro|IWFFFF_LAYER_VELOCITY_TIME
mdefine_line|#define IWFFFF_LAYER_VELOCITY_TIME&t;0x0000&t;/* velocity mode = time */
DECL|macro|IWFFFF_LAYER_VELOCITY_RATE
mdefine_line|#define IWFFFF_LAYER_VELOCITY_RATE&t;0x0001&t;/* velocity mode = rate */
DECL|macro|IWFFFF_LAYER_EVENT_KUP
mdefine_line|#define IWFFFF_LAYER_EVENT_KUP&t;&t;0x0000&t;/* layer event - key up */
DECL|macro|IWFFFF_LAYER_EVENT_KDOWN
mdefine_line|#define IWFFFF_LAYER_EVENT_KDOWN&t;0x0001&t;/* layer event - key down */
DECL|macro|IWFFFF_LAYER_EVENT_RETRIG
mdefine_line|#define IWFFFF_LAYER_EVENT_RETRIG&t;0x0002&t;/* layer event - retrigger */
DECL|macro|IWFFFF_LAYER_EVENT_LEGATO
mdefine_line|#define IWFFFF_LAYER_EVENT_LEGATO&t;0x0003&t;/* layer event - legato */
DECL|struct|iwffff_layer
r_typedef
r_struct
id|iwffff_layer
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|velocity_mode
r_int
r_char
id|velocity_mode
suffix:semicolon
DECL|member|layer_event
r_int
r_char
id|layer_event
suffix:semicolon
DECL|member|low_range
r_int
r_char
id|low_range
suffix:semicolon
multiline_comment|/* range for layer based */
DECL|member|high_range
r_int
r_char
id|high_range
suffix:semicolon
multiline_comment|/* on either velocity or frequency */
DECL|member|pan
r_int
r_char
id|pan
suffix:semicolon
multiline_comment|/* pan offset from CC1 (0 left - 127 right) */
DECL|member|pan_freq_scale
r_int
r_char
id|pan_freq_scale
suffix:semicolon
multiline_comment|/* position based on frequency (0-127) */
DECL|member|attenuation
r_int
r_char
id|attenuation
suffix:semicolon
multiline_comment|/* 0-127 (no corresponding midi controller) */
DECL|member|tremolo
id|iwffff_lfo_t
id|tremolo
suffix:semicolon
multiline_comment|/* tremolo effect */
DECL|member|vibrato
id|iwffff_lfo_t
id|vibrato
suffix:semicolon
multiline_comment|/* vibrato effect */
DECL|member|freq_scale
r_int
r_int
id|freq_scale
suffix:semicolon
multiline_comment|/* 0-2048, 1024 is equal to semitone scaling */
DECL|member|freq_center
r_int
r_char
id|freq_center
suffix:semicolon
multiline_comment|/* center for keyboard frequency scaling */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|penv
id|iwffff_env_t
id|penv
suffix:semicolon
multiline_comment|/* pitch envelope */
DECL|member|venv
id|iwffff_env_t
id|venv
suffix:semicolon
multiline_comment|/* volume envelope */
DECL|member|wave
id|iwffff_wave_t
op_star
id|wave
suffix:semicolon
DECL|member|next
r_struct
id|iwffff_layer
op_star
id|next
suffix:semicolon
DECL|typedef|iwffff_layer_t
)brace
id|iwffff_layer_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
DECL|macro|IWFFFF_EXCLUDE_NONE
mdefine_line|#define IWFFFF_EXCLUDE_NONE&t;&t;0x0000&t;/* exclusion mode - none */
DECL|macro|IWFFFF_EXCLUDE_SINGLE
mdefine_line|#define IWFFFF_EXCLUDE_SINGLE&t;&t;0x0001&t;/* exclude single - single note from the instrument group */
DECL|macro|IWFFFF_EXCLUDE_MULTIPLE
mdefine_line|#define IWFFFF_EXCLUDE_MULTIPLE&t;&t;0x0002&t;/* exclude multiple - stop only same note from this instrument */
DECL|macro|IWFFFF_LAYER_NONE
mdefine_line|#define IWFFFF_LAYER_NONE&t;&t;0x0000&t;/* not layered */
DECL|macro|IWFFFF_LAYER_ON
mdefine_line|#define IWFFFF_LAYER_ON&t;&t;&t;0x0001&t;/* layered */
DECL|macro|IWFFFF_LAYER_VELOCITY
mdefine_line|#define IWFFFF_LAYER_VELOCITY&t;&t;0x0002&t;/* layered by velocity */
DECL|macro|IWFFFF_LAYER_FREQUENCY
mdefine_line|#define IWFFFF_LAYER_FREQUENCY&t;&t;0x0003&t;/* layered by frequency */
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
DECL|member|layer_type
r_int
r_int
id|layer_type
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
DECL|member|layer
id|iwffff_layer_t
op_star
id|layer
suffix:semicolon
multiline_comment|/* first layer */
DECL|typedef|iwffff_instrument_t
)brace
id|iwffff_instrument_t
suffix:semicolon
multiline_comment|/*&n; *&n; *    Kernel &lt;-&gt; user space&n; *    Hardware (CPU) independent section&n; *&n; *    * = zero or more&n; *    + = one or more&n; *&n; *    iwffff_xinstrument&t;&t;IWFFFF_STRU_INSTR&n; *      +iwffff_xlayer&t;&t;&t;IWFFFF_STRU_LAYER&n; *        *iwffff_xenv_record&t;&t;IWFFFF_STRU_ENV_RECT (tremolo)&n; *        *iwffff_xenv_record&t;&t;IWFFFF_STRU_EVN_RECT (vibrato)&n; *          +iwffff_xwave&t;&t;IWFFFF_STRU_WAVE&n; *&n; */
DECL|macro|IWFFFF_STRU_WAVE
mdefine_line|#define IWFFFF_STRU_WAVE&t;__cpu_to_be32((&squot;W&squot;&lt;&lt;24)|(&squot;A&squot;&lt;&lt;16)|(&squot;V&squot;&lt;&lt;8)|&squot;E&squot;)
DECL|macro|IWFFFF_STRU_ENV_RECP
mdefine_line|#define IWFFFF_STRU_ENV_RECP&t;__cpu_to_be32((&squot;E&squot;&lt;&lt;24)|(&squot;N&squot;&lt;&lt;16)|(&squot;R&squot;&lt;&lt;8)|&squot;P&squot;)
DECL|macro|IWFFFF_STRU_ENV_RECV
mdefine_line|#define IWFFFF_STRU_ENV_RECV&t;__cpu_to_be32((&squot;E&squot;&lt;&lt;24)|(&squot;N&squot;&lt;&lt;16)|(&squot;R&squot;&lt;&lt;8)|&squot;V&squot;)
DECL|macro|IWFFFF_STRU_LAYER
mdefine_line|#define IWFFFF_STRU_LAYER &t;__cpu_to_be32((&squot;L&squot;&lt;&lt;24)|(&squot;A&squot;&lt;&lt;16)|(&squot;Y&squot;&lt;&lt;8)|&squot;R&squot;)
DECL|macro|IWFFFF_STRU_INSTR
mdefine_line|#define IWFFFF_STRU_INSTR &t;__cpu_to_be32((&squot;I&squot;&lt;&lt;24)|(&squot;N&squot;&lt;&lt;16)|(&squot;S&squot;&lt;&lt;8)|&squot;T&squot;)
multiline_comment|/*&n; *  Wavetable definitions&n; */
DECL|struct|iwffff_xwave
r_typedef
r_struct
id|iwffff_xwave
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
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* offset to ROM (address) */
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
DECL|member|sample_ratio
id|__u32
id|sample_ratio
suffix:semicolon
multiline_comment|/* sample ratio (44100 * 1024 / rate) */
DECL|member|attenuation
id|__u8
id|attenuation
suffix:semicolon
multiline_comment|/* 0 - 127 (no corresponding midi controller) */
DECL|member|low_note
id|__u8
id|low_note
suffix:semicolon
multiline_comment|/* lower frequency range for this waveform */
DECL|member|high_note
id|__u8
id|high_note
suffix:semicolon
multiline_comment|/* higher frequency range for this waveform */
DECL|member|pad
id|__u8
id|pad
suffix:semicolon
DECL|typedef|iwffff_xwave_t
)brace
id|iwffff_xwave_t
suffix:semicolon
multiline_comment|/*&n; *  Layer&n; */
DECL|struct|iwffff_xlfo
r_typedef
r_struct
id|iwffff_xlfo
(brace
DECL|member|freq
id|__u16
id|freq
suffix:semicolon
multiline_comment|/* (0-2047) 0.01Hz - 21.5Hz */
DECL|member|depth
id|__s16
id|depth
suffix:semicolon
multiline_comment|/* volume +- (0-255) 0.48675dB/step */
DECL|member|sweep
id|__s16
id|sweep
suffix:semicolon
multiline_comment|/* 0 - 950 deciseconds */
DECL|member|shape
id|__u8
id|shape
suffix:semicolon
multiline_comment|/* see to ULTRA_IW_LFO_SHAPE_XXXX */
DECL|member|delay
id|__u8
id|delay
suffix:semicolon
multiline_comment|/* 0 - 255 deciseconds */
DECL|typedef|iwffff_xlfo_t
)brace
id|iwffff_xlfo_t
suffix:semicolon
DECL|struct|iwffff_xenv_point
r_typedef
r_struct
id|iwffff_xenv_point
(brace
DECL|member|offset
id|__u16
id|offset
suffix:semicolon
DECL|member|rate
id|__u16
id|rate
suffix:semicolon
DECL|typedef|iwffff_xenv_point_t
)brace
id|iwffff_xenv_point_t
suffix:semicolon
DECL|struct|iwffff_xenv_record
r_typedef
r_struct
id|iwffff_xenv_record
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
DECL|member|nattack
id|__u16
id|nattack
suffix:semicolon
DECL|member|nrelease
id|__u16
id|nrelease
suffix:semicolon
DECL|member|sustain_offset
id|__u16
id|sustain_offset
suffix:semicolon
DECL|member|sustain_rate
id|__u16
id|sustain_rate
suffix:semicolon
DECL|member|release_rate
id|__u16
id|release_rate
suffix:semicolon
DECL|member|hirange
id|__u8
id|hirange
suffix:semicolon
DECL|member|pad
id|__u8
id|pad
suffix:semicolon
multiline_comment|/* points are stored here.. */
multiline_comment|/* count of points = nattack + nrelease */
DECL|typedef|iwffff_xenv_record_t
)brace
id|iwffff_xenv_record_t
suffix:semicolon
DECL|struct|iwffff_xenv
r_typedef
r_struct
id|iwffff_xenv
(brace
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|mode
id|__u8
id|mode
suffix:semicolon
DECL|member|index
id|__u8
id|index
suffix:semicolon
DECL|member|pad
id|__u8
id|pad
suffix:semicolon
DECL|typedef|iwffff_xenv_t
)brace
id|iwffff_xenv_t
suffix:semicolon
DECL|struct|iwffff_xlayer
r_typedef
r_struct
id|iwffff_xlayer
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|velocity_mode
id|__u8
id|velocity_mode
suffix:semicolon
DECL|member|layer_event
id|__u8
id|layer_event
suffix:semicolon
DECL|member|low_range
id|__u8
id|low_range
suffix:semicolon
multiline_comment|/* range for layer based */
DECL|member|high_range
id|__u8
id|high_range
suffix:semicolon
multiline_comment|/* on either velocity or frequency */
DECL|member|pan
id|__u8
id|pan
suffix:semicolon
multiline_comment|/* pan offset from CC1 (0 left - 127 right) */
DECL|member|pan_freq_scale
id|__u8
id|pan_freq_scale
suffix:semicolon
multiline_comment|/* position based on frequency (0-127) */
DECL|member|attenuation
id|__u8
id|attenuation
suffix:semicolon
multiline_comment|/* 0-127 (no corresponding midi controller) */
DECL|member|tremolo
id|iwffff_xlfo_t
id|tremolo
suffix:semicolon
multiline_comment|/* tremolo effect */
DECL|member|vibrato
id|iwffff_xlfo_t
id|vibrato
suffix:semicolon
multiline_comment|/* vibrato effect */
DECL|member|freq_scale
id|__u16
id|freq_scale
suffix:semicolon
multiline_comment|/* 0-2048, 1024 is equal to semitone scaling */
DECL|member|freq_center
id|__u8
id|freq_center
suffix:semicolon
multiline_comment|/* center for keyboard frequency scaling */
DECL|member|pad
id|__u8
id|pad
suffix:semicolon
DECL|member|penv
id|iwffff_xenv_t
id|penv
suffix:semicolon
multiline_comment|/* pitch envelope */
DECL|member|venv
id|iwffff_xenv_t
id|venv
suffix:semicolon
multiline_comment|/* volume envelope */
DECL|typedef|iwffff_xlayer_t
)brace
id|iwffff_xlayer_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
DECL|struct|iwffff_xinstrument
r_typedef
r_struct
id|iwffff_xinstrument
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
DECL|member|exclusion
id|__u16
id|exclusion
suffix:semicolon
DECL|member|layer_type
id|__u16
id|layer_type
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
DECL|typedef|iwffff_xinstrument_t
)brace
id|iwffff_xinstrument_t
suffix:semicolon
multiline_comment|/*&n; *  ROM support&n; *    InterWave ROMs are Little-Endian (x86)&n; */
DECL|macro|IWFFFF_ROM_HDR_SIZE
mdefine_line|#define IWFFFF_ROM_HDR_SIZE&t;512
r_typedef
r_struct
(brace
DECL|member|iwave
id|__u8
id|iwave
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|revision
id|__u8
id|revision
suffix:semicolon
DECL|member|series_number
id|__u8
id|series_number
suffix:semicolon
DECL|member|series_name
id|__u8
id|series_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|date
id|__u8
id|date
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|vendor_revision_major
id|__u16
id|vendor_revision_major
suffix:semicolon
DECL|member|vendor_revision_minor
id|__u16
id|vendor_revision_minor
suffix:semicolon
DECL|member|rom_size
id|__u32
id|rom_size
suffix:semicolon
DECL|member|copyright
id|__u8
id|copyright
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|vendor_name
id|__u8
id|vendor_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|description
id|__u8
id|description
(braket
l_int|128
)braket
suffix:semicolon
DECL|typedef|iwffff_rom_header_t
)brace
id|iwffff_rom_header_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument info&n; */
DECL|macro|IWFFFF_INFO_LFO_VIBRATO
mdefine_line|#define IWFFFF_INFO_LFO_VIBRATO&t;&t;(1&lt;&lt;0)
DECL|macro|IWFFFF_INFO_LFO_VIBRATO_SHAPE
mdefine_line|#define IWFFFF_INFO_LFO_VIBRATO_SHAPE&t;(1&lt;&lt;1)
DECL|macro|IWFFFF_INFO_LFO_TREMOLO
mdefine_line|#define IWFFFF_INFO_LFO_TREMOLO&t;&t;(1&lt;&lt;2)
DECL|macro|IWFFFF_INFO_LFO_TREMOLO_SHAPE
mdefine_line|#define IWFFFF_INFO_LFO_TREMOLO_SHAPE&t;(1&lt;&lt;3)
DECL|struct|iwffff_info
r_typedef
r_struct
id|iwffff_info
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
multiline_comment|/* supported effects (1 &lt;&lt; IWFFFF_EFFECT*) */
DECL|member|lfos
r_int
r_int
id|lfos
suffix:semicolon
multiline_comment|/* LFO effects */
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
DECL|typedef|iwffff_info_t
)brace
id|iwffff_info_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;seq_instr.h&quot;
r_extern
r_char
op_star
id|snd_seq_iwffff_id
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
id|iwffff_info_t
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
id|iwffff_wave_t
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
id|iwffff_wave_t
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
id|iwffff_wave_t
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
DECL|typedef|snd_iwffff_ops_t
)brace
id|snd_iwffff_ops_t
suffix:semicolon
r_int
id|snd_seq_iwffff_init
c_func
(paren
id|snd_iwffff_ops_t
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
macro_line|#endif /* __SOUND_AINSTR_IW_H */
eof
