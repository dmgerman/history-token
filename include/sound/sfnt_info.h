macro_line|#ifndef __SOUND_SFNT_INFO_H
DECL|macro|__SOUND_SFNT_INFO_H
mdefine_line|#define __SOUND_SFNT_INFO_H
multiline_comment|/*&n; *  Patch record compatible with AWE driver on OSS&n; *&n; *  Copyright (C) 1999-2000 Takashi Iwai&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;seq_oss_legacy.h&quot;
multiline_comment|/*&n; * patch information record&n; */
multiline_comment|/* patch interface header: 16 bytes */
DECL|struct|soundfont_patch_info_t
r_typedef
r_struct
id|soundfont_patch_info_t
(brace
DECL|member|key
r_int
r_int
id|key
suffix:semicolon
multiline_comment|/* use the key below */
DECL|macro|SNDRV_OSS_SOUNDFONT_PATCH
mdefine_line|#define SNDRV_OSS_SOUNDFONT_PATCH&t;&t;_PATCHKEY(0x07)
DECL|member|device_no
r_int
id|device_no
suffix:semicolon
multiline_comment|/* synthesizer number */
DECL|member|sf_id
r_int
r_int
id|sf_id
suffix:semicolon
multiline_comment|/* file id (should be zero) */
DECL|member|optarg
r_int
id|optarg
suffix:semicolon
multiline_comment|/* optional argument */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* data length (without this header) */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* patch operation type */
DECL|macro|SNDRV_SFNT_LOAD_INFO
mdefine_line|#define SNDRV_SFNT_LOAD_INFO&t;&t;0&t;/* awe_voice_rec */
DECL|macro|SNDRV_SFNT_LOAD_DATA
mdefine_line|#define SNDRV_SFNT_LOAD_DATA&t;&t;1&t;/* awe_sample_info */
DECL|macro|SNDRV_SFNT_OPEN_PATCH
mdefine_line|#define SNDRV_SFNT_OPEN_PATCH&t;2&t;/* awe_open_parm */
DECL|macro|SNDRV_SFNT_CLOSE_PATCH
mdefine_line|#define SNDRV_SFNT_CLOSE_PATCH&t;3&t;/* none */
multiline_comment|/* 4 is obsolete */
DECL|macro|SNDRV_SFNT_REPLACE_DATA
mdefine_line|#define SNDRV_SFNT_REPLACE_DATA&t;5&t;/* awe_sample_info (optarg=#channels)*/
DECL|macro|SNDRV_SFNT_MAP_PRESET
mdefine_line|#define SNDRV_SFNT_MAP_PRESET&t;6&t;/* awe_voice_map */
multiline_comment|/* 7 is not used */
DECL|macro|SNDRV_SFNT_PROBE_DATA
mdefine_line|#define SNDRV_SFNT_PROBE_DATA&t;&t;8&t;/* optarg=sample */
DECL|macro|SNDRV_SFNT_REMOVE_INFO
mdefine_line|#define SNDRV_SFNT_REMOVE_INFO&t;&t;9&t;/* optarg=(bank&lt;&lt;8)|instr */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* word alignment data */
multiline_comment|/* the actual patch data begins after this */
DECL|typedef|soundfont_patch_info_t
)brace
id|soundfont_patch_info_t
suffix:semicolon
multiline_comment|/*&n; * open patch&n; */
DECL|macro|SNDRV_SFNT_PATCH_NAME_LEN
mdefine_line|#define SNDRV_SFNT_PATCH_NAME_LEN&t;32
DECL|struct|soundfont_open_parm_t
r_typedef
r_struct
id|soundfont_open_parm_t
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* sample type */
DECL|macro|SNDRV_SFNT_PAT_TYPE_MISC
mdefine_line|#define SNDRV_SFNT_PAT_TYPE_MISC&t;0
DECL|macro|SNDRV_SFNT_PAT_TYPE_GUS
mdefine_line|#define SNDRV_SFNT_PAT_TYPE_GUS&t;6
DECL|macro|SNDRV_SFNT_PAT_TYPE_MAP
mdefine_line|#define SNDRV_SFNT_PAT_TYPE_MAP&t;7
DECL|macro|SNDRV_SFNT_PAT_LOCKED
mdefine_line|#define SNDRV_SFNT_PAT_LOCKED&t;0x100&t;/* lock the samples */
DECL|macro|SNDRV_SFNT_PAT_SHARED
mdefine_line|#define SNDRV_SFNT_PAT_SHARED&t;0x200&t;/* sample is shared */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|SNDRV_SFNT_PATCH_NAME_LEN
)braket
suffix:semicolon
DECL|typedef|soundfont_open_parm_t
)brace
id|soundfont_open_parm_t
suffix:semicolon
multiline_comment|/*&n; * raw voice information record&n; */
multiline_comment|/* wave table envelope &amp; effect parameters to control EMU8000 */
DECL|struct|soundfont_voice_parm_t
r_typedef
r_struct
id|soundfont_voice_parm_t
(brace
DECL|member|moddelay
r_int
r_int
id|moddelay
suffix:semicolon
multiline_comment|/* modulation delay (0x8000) */
DECL|member|modatkhld
r_int
r_int
id|modatkhld
suffix:semicolon
multiline_comment|/* modulation attack &amp; hold time (0x7f7f) */
DECL|member|moddcysus
r_int
r_int
id|moddcysus
suffix:semicolon
multiline_comment|/* modulation decay &amp; sustain (0x7f7f) */
DECL|member|modrelease
r_int
r_int
id|modrelease
suffix:semicolon
multiline_comment|/* modulation release time (0x807f) */
DECL|member|modkeyhold
DECL|member|modkeydecay
r_int
id|modkeyhold
comma
id|modkeydecay
suffix:semicolon
multiline_comment|/* envelope change per key (not used) */
DECL|member|voldelay
r_int
r_int
id|voldelay
suffix:semicolon
multiline_comment|/* volume delay (0x8000) */
DECL|member|volatkhld
r_int
r_int
id|volatkhld
suffix:semicolon
multiline_comment|/* volume attack &amp; hold time (0x7f7f) */
DECL|member|voldcysus
r_int
r_int
id|voldcysus
suffix:semicolon
multiline_comment|/* volume decay &amp; sustain (0x7f7f) */
DECL|member|volrelease
r_int
r_int
id|volrelease
suffix:semicolon
multiline_comment|/* volume release time (0x807f) */
DECL|member|volkeyhold
DECL|member|volkeydecay
r_int
id|volkeyhold
comma
id|volkeydecay
suffix:semicolon
multiline_comment|/* envelope change per key (not used) */
DECL|member|lfo1delay
r_int
r_int
id|lfo1delay
suffix:semicolon
multiline_comment|/* LFO1 delay (0x8000) */
DECL|member|lfo2delay
r_int
r_int
id|lfo2delay
suffix:semicolon
multiline_comment|/* LFO2 delay (0x8000) */
DECL|member|pefe
r_int
r_int
id|pefe
suffix:semicolon
multiline_comment|/* modulation pitch &amp; cutoff (0x0000) */
DECL|member|fmmod
r_int
r_int
id|fmmod
suffix:semicolon
multiline_comment|/* LFO1 pitch &amp; cutoff (0x0000) */
DECL|member|tremfrq
r_int
r_int
id|tremfrq
suffix:semicolon
multiline_comment|/* LFO1 volume &amp; freq (0x0000) */
DECL|member|fm2frq2
r_int
r_int
id|fm2frq2
suffix:semicolon
multiline_comment|/* LFO2 pitch &amp; freq (0x0000) */
DECL|member|cutoff
r_int
r_char
id|cutoff
suffix:semicolon
multiline_comment|/* initial cutoff (0xff) */
DECL|member|filterQ
r_int
r_char
id|filterQ
suffix:semicolon
multiline_comment|/* initial filter Q [0-15] (0x0) */
DECL|member|chorus
r_int
r_char
id|chorus
suffix:semicolon
multiline_comment|/* chorus send (0x00) */
DECL|member|reverb
r_int
r_char
id|reverb
suffix:semicolon
multiline_comment|/* reverb send (0x00) */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* not used */
DECL|typedef|soundfont_voice_parm_t
)brace
id|soundfont_voice_parm_t
suffix:semicolon
multiline_comment|/* wave table parameters: 92 bytes */
DECL|struct|soundfont_voice_info_t
r_typedef
r_struct
id|soundfont_voice_info_t
(brace
DECL|member|sf_id
r_int
r_int
id|sf_id
suffix:semicolon
multiline_comment|/* file id (should be zero) */
DECL|member|sample
r_int
r_int
id|sample
suffix:semicolon
multiline_comment|/* sample id */
DECL|member|start
DECL|member|end
r_int
id|start
comma
id|end
suffix:semicolon
multiline_comment|/* sample offset correction */
DECL|member|loopstart
DECL|member|loopend
r_int
id|loopstart
comma
id|loopend
suffix:semicolon
multiline_comment|/* loop offset correction */
DECL|member|rate_offset
r_int
id|rate_offset
suffix:semicolon
multiline_comment|/* sample rate pitch offset */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* sample mode */
DECL|macro|SNDRV_SFNT_MODE_ROMSOUND
mdefine_line|#define SNDRV_SFNT_MODE_ROMSOUND&t;&t;0x8000
DECL|macro|SNDRV_SFNT_MODE_STEREO
mdefine_line|#define SNDRV_SFNT_MODE_STEREO&t;&t;1
DECL|macro|SNDRV_SFNT_MODE_LOOPING
mdefine_line|#define SNDRV_SFNT_MODE_LOOPING&t;&t;2
DECL|macro|SNDRV_SFNT_MODE_NORELEASE
mdefine_line|#define SNDRV_SFNT_MODE_NORELEASE&t;&t;4&t;/* obsolete */
DECL|macro|SNDRV_SFNT_MODE_INIT_PARM
mdefine_line|#define SNDRV_SFNT_MODE_INIT_PARM&t;&t;8
DECL|member|root
r_int
id|root
suffix:semicolon
multiline_comment|/* midi root key */
DECL|member|tune
r_int
id|tune
suffix:semicolon
multiline_comment|/* pitch tuning (in cents) */
DECL|member|low
DECL|member|high
r_int
r_char
id|low
comma
id|high
suffix:semicolon
multiline_comment|/* key note range */
DECL|member|vellow
DECL|member|velhigh
r_int
r_char
id|vellow
comma
id|velhigh
suffix:semicolon
multiline_comment|/* velocity range */
DECL|member|fixkey
DECL|member|fixvel
r_int
r_char
id|fixkey
comma
id|fixvel
suffix:semicolon
multiline_comment|/* fixed key, velocity */
DECL|member|pan
DECL|member|fixpan
r_int
r_char
id|pan
comma
id|fixpan
suffix:semicolon
multiline_comment|/* panning, fixed panning */
DECL|member|exclusiveClass
r_int
id|exclusiveClass
suffix:semicolon
multiline_comment|/* exclusive class (0 = none) */
DECL|member|amplitude
r_int
r_char
id|amplitude
suffix:semicolon
multiline_comment|/* sample volume (127 max) */
DECL|member|attenuation
r_int
r_char
id|attenuation
suffix:semicolon
multiline_comment|/* attenuation (0.375dB) */
DECL|member|scaleTuning
r_int
id|scaleTuning
suffix:semicolon
multiline_comment|/* pitch scale tuning(%), normally 100 */
DECL|member|parm
id|soundfont_voice_parm_t
id|parm
suffix:semicolon
multiline_comment|/* voice envelope parameters */
DECL|member|sample_mode
r_int
r_int
id|sample_mode
suffix:semicolon
multiline_comment|/* sample mode_flag (set by driver) */
DECL|typedef|soundfont_voice_info_t
)brace
id|soundfont_voice_info_t
suffix:semicolon
multiline_comment|/* instrument info header: 4 bytes */
DECL|struct|soundfont_voice_rec_hdr_t
r_typedef
r_struct
id|soundfont_voice_rec_hdr_t
(brace
DECL|member|bank
r_int
r_char
id|bank
suffix:semicolon
multiline_comment|/* midi bank number */
DECL|member|instr
r_int
r_char
id|instr
suffix:semicolon
multiline_comment|/* midi preset number */
DECL|member|nvoices
r_char
id|nvoices
suffix:semicolon
multiline_comment|/* number of voices */
DECL|member|write_mode
r_char
id|write_mode
suffix:semicolon
multiline_comment|/* write mode; normally 0 */
DECL|macro|SNDRV_SFNT_WR_APPEND
mdefine_line|#define SNDRV_SFNT_WR_APPEND&t;&t;0&t;/* append anyway */
DECL|macro|SNDRV_SFNT_WR_EXCLUSIVE
mdefine_line|#define SNDRV_SFNT_WR_EXCLUSIVE&t;&t;1&t;/* skip if already exists */
DECL|macro|SNDRV_SFNT_WR_REPLACE
mdefine_line|#define SNDRV_SFNT_WR_REPLACE&t;&t;2&t;/* replace if already exists */
DECL|typedef|soundfont_voice_rec_hdr_t
)brace
id|soundfont_voice_rec_hdr_t
suffix:semicolon
multiline_comment|/*&n; * sample wave information&n; */
multiline_comment|/* wave table sample header: 32 bytes */
DECL|struct|soundfont_sample_info_t
r_typedef
r_struct
id|soundfont_sample_info_t
(brace
DECL|member|sf_id
r_int
r_int
id|sf_id
suffix:semicolon
multiline_comment|/* file id (should be zero) */
DECL|member|sample
r_int
r_int
id|sample
suffix:semicolon
multiline_comment|/* sample id */
DECL|member|start
DECL|member|end
r_int
id|start
comma
id|end
suffix:semicolon
multiline_comment|/* start &amp; end offset */
DECL|member|loopstart
DECL|member|loopend
r_int
id|loopstart
comma
id|loopend
suffix:semicolon
multiline_comment|/* loop start &amp; end offset */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size (0 = ROM) */
DECL|member|dummy
r_int
id|dummy
suffix:semicolon
multiline_comment|/* not used */
DECL|member|mode_flags
r_int
r_int
id|mode_flags
suffix:semicolon
multiline_comment|/* mode flags */
DECL|macro|SNDRV_SFNT_SAMPLE_8BITS
mdefine_line|#define SNDRV_SFNT_SAMPLE_8BITS&t;&t;1&t;/* wave data is 8bits */
DECL|macro|SNDRV_SFNT_SAMPLE_UNSIGNED
mdefine_line|#define SNDRV_SFNT_SAMPLE_UNSIGNED&t;2&t;/* wave data is unsigned */
DECL|macro|SNDRV_SFNT_SAMPLE_NO_BLANK
mdefine_line|#define SNDRV_SFNT_SAMPLE_NO_BLANK&t;4&t;/* no blank loop is attached */
DECL|macro|SNDRV_SFNT_SAMPLE_SINGLESHOT
mdefine_line|#define SNDRV_SFNT_SAMPLE_SINGLESHOT&t;8&t;/* single-shot w/o loop */
DECL|macro|SNDRV_SFNT_SAMPLE_BIDIR_LOOP
mdefine_line|#define SNDRV_SFNT_SAMPLE_BIDIR_LOOP&t;16&t;/* bidirectional looping */
DECL|macro|SNDRV_SFNT_SAMPLE_STEREO_LEFT
mdefine_line|#define SNDRV_SFNT_SAMPLE_STEREO_LEFT&t;32&t;/* stereo left sound */
DECL|macro|SNDRV_SFNT_SAMPLE_STEREO_RIGHT
mdefine_line|#define SNDRV_SFNT_SAMPLE_STEREO_RIGHT&t;64&t;/* stereo right sound */
DECL|macro|SNDRV_SFNT_SAMPLE_REVERSE_LOOP
mdefine_line|#define SNDRV_SFNT_SAMPLE_REVERSE_LOOP&t;128&t;/* reverse looping */
DECL|member|truesize
r_int
r_int
id|truesize
suffix:semicolon
multiline_comment|/* used memory size (set by driver) */
DECL|typedef|soundfont_sample_info_t
)brace
id|soundfont_sample_info_t
suffix:semicolon
multiline_comment|/*&n; * voice preset mapping (aliasing)&n; */
DECL|struct|soundfont_voice_map_t
r_typedef
r_struct
id|soundfont_voice_map_t
(brace
DECL|member|map_bank
DECL|member|map_instr
DECL|member|map_key
r_int
id|map_bank
comma
id|map_instr
comma
id|map_key
suffix:semicolon
multiline_comment|/* key = -1 means all keys */
DECL|member|src_bank
DECL|member|src_instr
DECL|member|src_key
r_int
id|src_bank
comma
id|src_instr
comma
id|src_key
suffix:semicolon
DECL|typedef|soundfont_voice_map_t
)brace
id|soundfont_voice_map_t
suffix:semicolon
macro_line|#endif /* __SOUND_SFNT_INFO_H */
eof
