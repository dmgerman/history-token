multiline_comment|/*&n; * sound/awe_voice.h&n; *&n; * Voice information definitions for the low level driver for the &n; * AWE32/SB32/AWE64 wave table synth.&n; *   version 0.4.4; Jan. 4, 2000&n; *&n; * Copyright (C) 1996-2000 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_VOICE_H
DECL|macro|AWE_VOICE_H
mdefine_line|#define AWE_VOICE_H
macro_line|#ifndef SAMPLE_TYPE_AWE32
DECL|macro|SAMPLE_TYPE_AWE32
mdefine_line|#define SAMPLE_TYPE_AWE32&t;0x20
macro_line|#endif
macro_line|#ifndef _PATCHKEY
DECL|macro|_PATCHKEY
mdefine_line|#define _PATCHKEY(id) ((id&lt;&lt;8)|0xfd)
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------&n; * patch information record&n; *----------------------------------------------------------------*/
multiline_comment|/* patch interface header: 16 bytes */
DECL|struct|awe_patch_info
r_typedef
r_struct
id|awe_patch_info
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* use AWE_PATCH here */
DECL|macro|AWE_PATCH
mdefine_line|#define AWE_PATCH&t;_PATCHKEY(0x07)
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
DECL|macro|AWE_LOAD_INFO
mdefine_line|#define AWE_LOAD_INFO&t;&t;0&t;/* awe_voice_rec */
DECL|macro|AWE_LOAD_DATA
mdefine_line|#define AWE_LOAD_DATA&t;&t;1&t;/* awe_sample_info */
DECL|macro|AWE_OPEN_PATCH
mdefine_line|#define AWE_OPEN_PATCH&t;&t;2&t;/* awe_open_parm */
DECL|macro|AWE_CLOSE_PATCH
mdefine_line|#define AWE_CLOSE_PATCH&t;&t;3&t;/* none */
DECL|macro|AWE_UNLOAD_PATCH
mdefine_line|#define AWE_UNLOAD_PATCH&t;4&t;/* none */
DECL|macro|AWE_REPLACE_DATA
mdefine_line|#define AWE_REPLACE_DATA&t;5&t;/* awe_sample_info (optarg=#channels)*/
DECL|macro|AWE_MAP_PRESET
mdefine_line|#define AWE_MAP_PRESET&t;&t;6&t;/* awe_voice_map */
multiline_comment|/*#define AWE_PROBE_INFO&t;7*/
multiline_comment|/* awe_voice_map (pat only) */
DECL|macro|AWE_PROBE_DATA
mdefine_line|#define AWE_PROBE_DATA&t;&t;8&t;/* optarg=sample */
DECL|macro|AWE_REMOVE_INFO
mdefine_line|#define AWE_REMOVE_INFO&t;&t;9&t;/* optarg=(bank&lt;&lt;8)|instr */
DECL|macro|AWE_LOAD_CHORUS_FX
mdefine_line|#define AWE_LOAD_CHORUS_FX&t;0x10&t;/* awe_chorus_fx_rec (optarg=mode) */
DECL|macro|AWE_LOAD_REVERB_FX
mdefine_line|#define AWE_LOAD_REVERB_FX&t;0x11&t;/* awe_reverb_fx_rec (optarg=mode) */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* word alignment data */
multiline_comment|/* the actual patch data begins after this */
macro_line|#if defined(AWE_COMPAT_030) &amp;&amp; AWE_COMPAT_030
DECL|member|data
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|awe_patch_info
)brace
id|awe_patch_info
suffix:semicolon
multiline_comment|/*#define AWE_PATCH_INFO_SIZE&t;16*/
DECL|macro|AWE_PATCH_INFO_SIZE
mdefine_line|#define AWE_PATCH_INFO_SIZE&t;sizeof(awe_patch_info)
multiline_comment|/*----------------------------------------------------------------&n; * open patch&n; *----------------------------------------------------------------*/
DECL|macro|AWE_PATCH_NAME_LEN
mdefine_line|#define AWE_PATCH_NAME_LEN&t;32
DECL|struct|_awe_open_parm
r_typedef
r_struct
id|_awe_open_parm
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* sample type */
DECL|macro|AWE_PAT_TYPE_MISC
mdefine_line|#define AWE_PAT_TYPE_MISC&t;0
DECL|macro|AWE_PAT_TYPE_GM
mdefine_line|#define AWE_PAT_TYPE_GM&t;&t;1
DECL|macro|AWE_PAT_TYPE_GS
mdefine_line|#define AWE_PAT_TYPE_GS&t;&t;2
DECL|macro|AWE_PAT_TYPE_MT32
mdefine_line|#define AWE_PAT_TYPE_MT32&t;3
DECL|macro|AWE_PAT_TYPE_XG
mdefine_line|#define AWE_PAT_TYPE_XG&t;&t;4
DECL|macro|AWE_PAT_TYPE_SFX
mdefine_line|#define AWE_PAT_TYPE_SFX&t;5
DECL|macro|AWE_PAT_TYPE_GUS
mdefine_line|#define AWE_PAT_TYPE_GUS&t;6
DECL|macro|AWE_PAT_TYPE_MAP
mdefine_line|#define AWE_PAT_TYPE_MAP&t;7
DECL|macro|AWE_PAT_LOCKED
mdefine_line|#define AWE_PAT_LOCKED&t;&t;0x100&t;/* lock the samples */
DECL|macro|AWE_PAT_SHARED
mdefine_line|#define AWE_PAT_SHARED&t;&t;0x200&t;/* sample is shared */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|AWE_PATCH_NAME_LEN
)braket
suffix:semicolon
DECL|typedef|awe_open_parm
)brace
id|awe_open_parm
suffix:semicolon
multiline_comment|/*#define AWE_OPEN_PARM_SIZE&t;28*/
DECL|macro|AWE_OPEN_PARM_SIZE
mdefine_line|#define AWE_OPEN_PARM_SIZE&t;sizeof(awe_open_parm)
multiline_comment|/*----------------------------------------------------------------&n; * raw voice information record&n; *----------------------------------------------------------------*/
multiline_comment|/* wave table envelope &amp; effect parameters to control EMU8000 */
DECL|struct|_awe_voice_parm
r_typedef
r_struct
id|_awe_voice_parm
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
DECL|typedef|awe_voice_parm
)brace
id|awe_voice_parm
suffix:semicolon
DECL|struct|_awe_voice_parm_block
r_typedef
r_struct
id|_awe_voice_parm_block
(brace
DECL|member|moddelay
r_int
r_int
id|moddelay
suffix:semicolon
multiline_comment|/* modulation delay (0x8000) */
DECL|member|modatk
DECL|member|modhld
r_int
r_char
id|modatk
comma
id|modhld
suffix:semicolon
DECL|member|moddcy
DECL|member|modsus
r_int
r_char
id|moddcy
comma
id|modsus
suffix:semicolon
DECL|member|modrel
DECL|member|moddummy
r_int
r_char
id|modrel
comma
id|moddummy
suffix:semicolon
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
DECL|member|volatk
DECL|member|volhld
r_int
r_char
id|volatk
comma
id|volhld
suffix:semicolon
DECL|member|voldcy
DECL|member|volsus
r_int
r_char
id|voldcy
comma
id|volsus
suffix:semicolon
DECL|member|volrel
DECL|member|voldummy
r_int
r_char
id|volrel
comma
id|voldummy
suffix:semicolon
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
DECL|member|env1fc
DECL|member|env1pit
r_int
r_char
id|env1fc
comma
id|env1pit
suffix:semicolon
DECL|member|lfo1fc
DECL|member|lfo1pit
r_int
r_char
id|lfo1fc
comma
id|lfo1pit
suffix:semicolon
DECL|member|lfo1freq
DECL|member|lfo1vol
r_int
r_char
id|lfo1freq
comma
id|lfo1vol
suffix:semicolon
DECL|member|lfo2freq
DECL|member|lfo2pit
r_int
r_char
id|lfo2freq
comma
id|lfo2pit
suffix:semicolon
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
DECL|typedef|awe_voice_parm_block
)brace
id|awe_voice_parm_block
suffix:semicolon
DECL|macro|AWE_VOICE_PARM_SIZE
mdefine_line|#define AWE_VOICE_PARM_SIZE&t;48
multiline_comment|/* wave table parameters: 92 bytes */
DECL|struct|_awe_voice_info
r_typedef
r_struct
id|_awe_voice_info
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
DECL|macro|AWE_MODE_ROMSOUND
mdefine_line|#define AWE_MODE_ROMSOUND&t;&t;0x8000
DECL|macro|AWE_MODE_STEREO
mdefine_line|#define AWE_MODE_STEREO&t;&t;&t;1
DECL|macro|AWE_MODE_LOOPING
mdefine_line|#define AWE_MODE_LOOPING&t;&t;2
DECL|macro|AWE_MODE_NORELEASE
mdefine_line|#define AWE_MODE_NORELEASE&t;&t;4&t;/* obsolete */
DECL|macro|AWE_MODE_INIT_PARM
mdefine_line|#define AWE_MODE_INIT_PARM&t;&t;8
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
id|awe_voice_parm
id|parm
suffix:semicolon
multiline_comment|/* voice envelope parameters */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* internal index (set by driver) */
DECL|typedef|awe_voice_info
)brace
id|awe_voice_info
suffix:semicolon
multiline_comment|/*#define AWE_VOICE_INFO_SIZE&t;92*/
DECL|macro|AWE_VOICE_INFO_SIZE
mdefine_line|#define AWE_VOICE_INFO_SIZE&t;sizeof(awe_voice_info)
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* The info entry of awe_voice_rec is changed from 0 to 1&n; * for some compilers refusing zero size array.&n; * Due to this change, sizeof(awe_voice_rec) becomes different&n; * from older versions.&n; * Use AWE_VOICE_REC_SIZE instead.&n; */
multiline_comment|/* instrument info header: 4 bytes */
DECL|struct|_awe_voice_rec_hdr
r_typedef
r_struct
id|_awe_voice_rec_hdr
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
DECL|macro|AWE_WR_APPEND
mdefine_line|#define AWE_WR_APPEND&t;&t;0&t;/* append anyway */
DECL|macro|AWE_WR_EXCLUSIVE
mdefine_line|#define AWE_WR_EXCLUSIVE&t;1&t;/* skip if already exists */
DECL|macro|AWE_WR_REPLACE
mdefine_line|#define AWE_WR_REPLACE&t;&t;2&t;/* replace if already exists */
DECL|typedef|awe_voice_rec_hdr
)brace
id|awe_voice_rec_hdr
suffix:semicolon
multiline_comment|/*#define AWE_VOICE_REC_SIZE&t;4*/
DECL|macro|AWE_VOICE_REC_SIZE
mdefine_line|#define AWE_VOICE_REC_SIZE&t;sizeof(awe_voice_rec_hdr)
multiline_comment|/* the standard patch structure for one sample */
DECL|struct|_awe_voice_rec_patch
r_typedef
r_struct
id|_awe_voice_rec_patch
(brace
DECL|member|patch
id|awe_patch_info
id|patch
suffix:semicolon
DECL|member|hdr
id|awe_voice_rec_hdr
id|hdr
suffix:semicolon
DECL|member|info
id|awe_voice_info
id|info
suffix:semicolon
DECL|typedef|awe_voice_rec_patch
)brace
id|awe_voice_rec_patch
suffix:semicolon
multiline_comment|/* obsolete data type */
macro_line|#if defined(AWE_COMPAT_030) &amp;&amp; AWE_COMPAT_030
DECL|macro|AWE_INFOARRAY_SIZE
mdefine_line|#define AWE_INFOARRAY_SIZE&t;0
macro_line|#else
DECL|macro|AWE_INFOARRAY_SIZE
mdefine_line|#define AWE_INFOARRAY_SIZE&t;1
macro_line|#endif
DECL|struct|_awe_voice_rec
r_typedef
r_struct
id|_awe_voice_rec
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
r_int
id|nvoices
suffix:semicolon
multiline_comment|/* number of voices */
multiline_comment|/* voice information follows here */
DECL|member|info
id|awe_voice_info
id|info
(braket
id|AWE_INFOARRAY_SIZE
)braket
suffix:semicolon
DECL|typedef|awe_voice_rec
)brace
id|awe_voice_rec
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------&n; * sample wave information&n; *----------------------------------------------------------------*/
multiline_comment|/* wave table sample header: 32 bytes */
DECL|struct|awe_sample_info
r_typedef
r_struct
id|awe_sample_info
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
DECL|member|checksum_flag
r_int
id|checksum_flag
suffix:semicolon
multiline_comment|/* use check sum = 1 */
DECL|member|mode_flags
r_int
r_int
id|mode_flags
suffix:semicolon
multiline_comment|/* mode flags */
DECL|macro|AWE_SAMPLE_8BITS
mdefine_line|#define AWE_SAMPLE_8BITS&t;1&t;/* wave data is 8bits */
DECL|macro|AWE_SAMPLE_UNSIGNED
mdefine_line|#define AWE_SAMPLE_UNSIGNED&t;2&t;/* wave data is unsigned */
DECL|macro|AWE_SAMPLE_NO_BLANK
mdefine_line|#define AWE_SAMPLE_NO_BLANK&t;4&t;/* no blank loop is attached */
DECL|macro|AWE_SAMPLE_SINGLESHOT
mdefine_line|#define AWE_SAMPLE_SINGLESHOT&t;8&t;/* single-shot w/o loop */
DECL|macro|AWE_SAMPLE_BIDIR_LOOP
mdefine_line|#define AWE_SAMPLE_BIDIR_LOOP&t;16&t;/* bidirectional looping */
DECL|macro|AWE_SAMPLE_STEREO_LEFT
mdefine_line|#define AWE_SAMPLE_STEREO_LEFT&t;32&t;/* stereo left sound */
DECL|macro|AWE_SAMPLE_STEREO_RIGHT
mdefine_line|#define AWE_SAMPLE_STEREO_RIGHT&t;64&t;/* stereo right sound */
DECL|macro|AWE_SAMPLE_REVERSE_LOOP
mdefine_line|#define AWE_SAMPLE_REVERSE_LOOP 128&t;/* reverse looping */
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
multiline_comment|/* check sum */
macro_line|#if defined(AWE_COMPAT_030) &amp;&amp; AWE_COMPAT_030
DECL|member|data
r_int
r_int
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* sample data follows here */
macro_line|#endif
DECL|typedef|awe_sample_info
)brace
id|awe_sample_info
suffix:semicolon
multiline_comment|/*#define AWE_SAMPLE_INFO_SIZE&t;32*/
DECL|macro|AWE_SAMPLE_INFO_SIZE
mdefine_line|#define AWE_SAMPLE_INFO_SIZE&t;sizeof(awe_sample_info)
multiline_comment|/*----------------------------------------------------------------&n; * voice preset mapping&n; *----------------------------------------------------------------*/
DECL|struct|awe_voice_map
r_typedef
r_struct
id|awe_voice_map
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
DECL|typedef|awe_voice_map
)brace
id|awe_voice_map
suffix:semicolon
DECL|macro|AWE_VOICE_MAP_SIZE
mdefine_line|#define AWE_VOICE_MAP_SIZE&t;sizeof(awe_voice_map)
multiline_comment|/*----------------------------------------------------------------&n; * awe hardware controls&n; *----------------------------------------------------------------*/
DECL|macro|_AWE_DEBUG_MODE
mdefine_line|#define _AWE_DEBUG_MODE&t;&t;&t;0x00
DECL|macro|_AWE_REVERB_MODE
mdefine_line|#define _AWE_REVERB_MODE&t;&t;0x01
DECL|macro|_AWE_CHORUS_MODE
mdefine_line|#define _AWE_CHORUS_MODE&t;&t;0x02
DECL|macro|_AWE_REMOVE_LAST_SAMPLES
mdefine_line|#define _AWE_REMOVE_LAST_SAMPLES&t;0x03
DECL|macro|_AWE_INITIALIZE_CHIP
mdefine_line|#define _AWE_INITIALIZE_CHIP&t;&t;0x04
DECL|macro|_AWE_SEND_EFFECT
mdefine_line|#define _AWE_SEND_EFFECT&t;&t;0x05
DECL|macro|_AWE_TERMINATE_CHANNEL
mdefine_line|#define _AWE_TERMINATE_CHANNEL&t;&t;0x06
DECL|macro|_AWE_TERMINATE_ALL
mdefine_line|#define _AWE_TERMINATE_ALL&t;&t;0x07
DECL|macro|_AWE_INITIAL_VOLUME
mdefine_line|#define _AWE_INITIAL_VOLUME&t;&t;0x08
DECL|macro|_AWE_INITIAL_ATTEN
mdefine_line|#define _AWE_INITIAL_ATTEN&t;_AWE_INITIAL_VOLUME
DECL|macro|_AWE_RESET_CHANNEL
mdefine_line|#define _AWE_RESET_CHANNEL&t;&t;0x09
DECL|macro|_AWE_CHANNEL_MODE
mdefine_line|#define _AWE_CHANNEL_MODE&t;&t;0x0a
DECL|macro|_AWE_DRUM_CHANNELS
mdefine_line|#define _AWE_DRUM_CHANNELS&t;&t;0x0b
DECL|macro|_AWE_MISC_MODE
mdefine_line|#define _AWE_MISC_MODE&t;&t;&t;0x0c
DECL|macro|_AWE_RELEASE_ALL
mdefine_line|#define _AWE_RELEASE_ALL&t;&t;0x0d
DECL|macro|_AWE_NOTEOFF_ALL
mdefine_line|#define _AWE_NOTEOFF_ALL&t;&t;0x0e
DECL|macro|_AWE_CHN_PRESSURE
mdefine_line|#define _AWE_CHN_PRESSURE&t;&t;0x0f
multiline_comment|/*#define _AWE_GET_CURRENT_MODE&t;&t;0x10*/
DECL|macro|_AWE_EQUALIZER
mdefine_line|#define _AWE_EQUALIZER&t;&t;&t;0x11
multiline_comment|/*#define _AWE_GET_MISC_MODE&t;&t;0x12*/
multiline_comment|/*#define _AWE_GET_FONTINFO&t;&t;0x13*/
DECL|macro|_AWE_MODE_FLAG
mdefine_line|#define _AWE_MODE_FLAG&t;&t;&t;0x80
DECL|macro|_AWE_COOKED_FLAG
mdefine_line|#define _AWE_COOKED_FLAG&t;&t;0x40&t;/* not supported */
DECL|macro|_AWE_MODE_VALUE_MASK
mdefine_line|#define _AWE_MODE_VALUE_MASK&t;&t;0x3F
multiline_comment|/*----------------------------------------------------------------*/
DECL|macro|_AWE_SET_CMD
mdefine_line|#define _AWE_SET_CMD(p,dev,voice,cmd,p1,p2) &bslash;&n;{((char*)(p))[0] = SEQ_PRIVATE;&bslash;&n; ((char*)(p))[1] = dev;&bslash;&n; ((char*)(p))[2] = _AWE_MODE_FLAG|(cmd);&bslash;&n; ((char*)(p))[3] = voice;&bslash;&n; ((unsigned short*)(p))[2] = p1;&bslash;&n; ((unsigned short*)(p))[3] = p2;}
multiline_comment|/* buffered access */
DECL|macro|_AWE_CMD
mdefine_line|#define _AWE_CMD(dev, voice, cmd, p1, p2) &bslash;&n;{_SEQ_NEEDBUF(8);&bslash;&n; _AWE_SET_CMD(_seqbuf + _seqbufptr, dev, voice, cmd, p1, p2);&bslash;&n; _SEQ_ADVBUF(8);}
multiline_comment|/* direct access */
DECL|macro|_AWE_CMD_NOW
mdefine_line|#define _AWE_CMD_NOW(seqfd,dev,voice,cmd,p1,p2) &bslash;&n;{struct seq_event_rec tmp;&bslash;&n; _AWE_SET_CMD(&amp;tmp, dev, voice, cmd, p1, p2);&bslash;&n; ioctl(seqfd, SNDCTL_SEQ_OUTOFBAND, &amp;tmp);}
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* set debugging mode */
DECL|macro|AWE_DEBUG_MODE
mdefine_line|#define AWE_DEBUG_MODE(dev,p1)&t;_AWE_CMD(dev, 0, _AWE_DEBUG_MODE, p1, 0)
multiline_comment|/* set reverb mode; from 0 to 7 */
DECL|macro|AWE_REVERB_MODE
mdefine_line|#define AWE_REVERB_MODE(dev,p1)&t;_AWE_CMD(dev, 0, _AWE_REVERB_MODE, p1, 0)
multiline_comment|/* set chorus mode; from 0 to 7 */
DECL|macro|AWE_CHORUS_MODE
mdefine_line|#define AWE_CHORUS_MODE(dev,p1)&t;_AWE_CMD(dev, 0, _AWE_CHORUS_MODE, p1, 0)
multiline_comment|/* reset channel */
DECL|macro|AWE_RESET_CHANNEL
mdefine_line|#define AWE_RESET_CHANNEL(dev,ch) _AWE_CMD(dev, ch, _AWE_RESET_CHANNEL, 0, 0)
DECL|macro|AWE_RESET_CONTROL
mdefine_line|#define AWE_RESET_CONTROL(dev,ch) _AWE_CMD(dev, ch, _AWE_RESET_CHANNEL, 1, 0)
multiline_comment|/* send an effect to all layers */
DECL|macro|AWE_SEND_EFFECT
mdefine_line|#define AWE_SEND_EFFECT(dev,voice,type,value) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,type,value)
DECL|macro|AWE_ADD_EFFECT
mdefine_line|#define AWE_ADD_EFFECT(dev,voice,type,value) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,((type)|0x80),value)
DECL|macro|AWE_UNSET_EFFECT
mdefine_line|#define AWE_UNSET_EFFECT(dev,voice,type) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,((type)|0x40),0)
multiline_comment|/* send an effect to a layer */
DECL|macro|AWE_SEND_LAYER_EFFECT
mdefine_line|#define AWE_SEND_LAYER_EFFECT(dev,voice,layer,type,value) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,((layer+1)&lt;&lt;8|(type)),value)
DECL|macro|AWE_ADD_LAYER_EFFECT
mdefine_line|#define AWE_ADD_LAYER_EFFECT(dev,voice,layer,type,value) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,((layer+1)&lt;&lt;8|(type)|0x80),value)
DECL|macro|AWE_UNSET_LAYER_EFFECT
mdefine_line|#define AWE_UNSET_LAYER_EFFECT(dev,voice,layer,type) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,((layer+1)&lt;&lt;8|(type)|0x40),0)
multiline_comment|/* terminate sound on the channel/voice */
DECL|macro|AWE_TERMINATE_CHANNEL
mdefine_line|#define AWE_TERMINATE_CHANNEL(dev,voice) _AWE_CMD(dev,voice,_AWE_TERMINATE_CHANNEL,0,0)
multiline_comment|/* terminate all sounds */
DECL|macro|AWE_TERMINATE_ALL
mdefine_line|#define AWE_TERMINATE_ALL(dev) _AWE_CMD(dev, 0, _AWE_TERMINATE_ALL, 0, 0)
multiline_comment|/* release all sounds (w/o sustain effect) */
DECL|macro|AWE_RELEASE_ALL
mdefine_line|#define AWE_RELEASE_ALL(dev) _AWE_CMD(dev, 0, _AWE_RELEASE_ALL, 0, 0)
multiline_comment|/* note off all sounds (w sustain effect) */
DECL|macro|AWE_NOTEOFF_ALL
mdefine_line|#define AWE_NOTEOFF_ALL(dev) _AWE_CMD(dev, 0, _AWE_NOTEOFF_ALL, 0, 0)
multiline_comment|/* set initial attenuation */
DECL|macro|AWE_INITIAL_VOLUME
mdefine_line|#define AWE_INITIAL_VOLUME(dev,atten) _AWE_CMD(dev, 0, _AWE_INITIAL_VOLUME, atten, 0)
DECL|macro|AWE_INITIAL_ATTEN
mdefine_line|#define AWE_INITIAL_ATTEN  AWE_INITIAL_VOLUME
multiline_comment|/* relative attenuation */
DECL|macro|AWE_SET_ATTEN
mdefine_line|#define AWE_SET_ATTEN(dev,atten)  _AWE_CMD(dev, 0, _AWE_INITIAL_VOLUME, atten, 1)
multiline_comment|/* set channel playing mode; mode=0/1/2 */
DECL|macro|AWE_SET_CHANNEL_MODE
mdefine_line|#define AWE_SET_CHANNEL_MODE(dev,mode) _AWE_CMD(dev, 0, _AWE_CHANNEL_MODE, mode, 0)
DECL|macro|AWE_PLAY_INDIRECT
mdefine_line|#define AWE_PLAY_INDIRECT&t;0&t;/* indirect voice mode (default) */
DECL|macro|AWE_PLAY_MULTI
mdefine_line|#define AWE_PLAY_MULTI&t;&t;1&t;/* multi note voice mode */
DECL|macro|AWE_PLAY_DIRECT
mdefine_line|#define AWE_PLAY_DIRECT&t;&t;2&t;/* direct single voice mode */
DECL|macro|AWE_PLAY_MULTI2
mdefine_line|#define AWE_PLAY_MULTI2&t;&t;3&t;/* sequencer2 mode; used internally */
multiline_comment|/* set drum channel mask; channels is 32bit long value */
DECL|macro|AWE_DRUM_CHANNELS
mdefine_line|#define AWE_DRUM_CHANNELS(dev,channels) _AWE_CMD(dev, 0, _AWE_DRUM_CHANNELS, ((channels) &amp; 0xffff), ((channels) &gt;&gt; 16))
multiline_comment|/* set bass and treble control; values are from 0 to 11 */
DECL|macro|AWE_EQUALIZER
mdefine_line|#define AWE_EQUALIZER(dev,bass,treble) _AWE_CMD(dev, 0, _AWE_EQUALIZER, bass, treble)
multiline_comment|/* remove last loaded samples */
DECL|macro|AWE_REMOVE_LAST_SAMPLES
mdefine_line|#define AWE_REMOVE_LAST_SAMPLES(seqfd,dev) _AWE_CMD_NOW(seqfd, dev, 0, _AWE_REMOVE_LAST_SAMPLES, 0, 0)
multiline_comment|/* initialize emu8000 chip */
DECL|macro|AWE_INITIALIZE_CHIP
mdefine_line|#define AWE_INITIALIZE_CHIP(seqfd,dev) _AWE_CMD_NOW(seqfd, dev, 0, _AWE_INITIALIZE_CHIP, 0, 0)
multiline_comment|/* set miscellaneous modes; meta command */
DECL|macro|AWE_MISC_MODE
mdefine_line|#define AWE_MISC_MODE(dev,mode,value) _AWE_CMD(dev, 0, _AWE_MISC_MODE, mode, value)
multiline_comment|/* exclusive sound off; 1=off */
DECL|macro|AWE_EXCLUSIVE_SOUND
mdefine_line|#define AWE_EXCLUSIVE_SOUND(dev,mode) AWE_MISC_MODE(dev,AWE_MD_EXCLUSIVE_SOUND,mode)
multiline_comment|/* default GUS bank number */
DECL|macro|AWE_SET_GUS_BANK
mdefine_line|#define AWE_SET_GUS_BANK(dev,bank) AWE_MISC_MODE(dev,AWE_MD_GUS_BANK,bank)
multiline_comment|/* change panning position in realtime; 0=don&squot;t 1=do */
DECL|macro|AWE_REALTIME_PAN
mdefine_line|#define AWE_REALTIME_PAN(dev,mode) AWE_MISC_MODE(dev,AWE_MD_REALTIME_PAN,mode)
multiline_comment|/* extended pressure controls; not portable with other sound drivers */
DECL|macro|AWE_KEY_PRESSURE
mdefine_line|#define AWE_KEY_PRESSURE(dev,ch,note,vel) SEQ_START_NOTE(dev,ch,(note)+128,vel)
DECL|macro|AWE_CHN_PRESSURE
mdefine_line|#define AWE_CHN_PRESSURE(dev,ch,vel) _AWE_CMD(dev,ch,_AWE_CHN_PRESSURE,vel,0)
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* reverb mode parameters */
DECL|macro|AWE_REVERB_ROOM1
mdefine_line|#define&t;AWE_REVERB_ROOM1&t;0
DECL|macro|AWE_REVERB_ROOM2
mdefine_line|#define AWE_REVERB_ROOM2&t;1
DECL|macro|AWE_REVERB_ROOM3
mdefine_line|#define&t;AWE_REVERB_ROOM3&t;2
DECL|macro|AWE_REVERB_HALL1
mdefine_line|#define&t;AWE_REVERB_HALL1&t;3
DECL|macro|AWE_REVERB_HALL2
mdefine_line|#define&t;AWE_REVERB_HALL2&t;4
DECL|macro|AWE_REVERB_PLATE
mdefine_line|#define&t;AWE_REVERB_PLATE&t;5
DECL|macro|AWE_REVERB_DELAY
mdefine_line|#define&t;AWE_REVERB_DELAY&t;6
DECL|macro|AWE_REVERB_PANNINGDELAY
mdefine_line|#define&t;AWE_REVERB_PANNINGDELAY 7
DECL|macro|AWE_REVERB_PREDEFINED
mdefine_line|#define AWE_REVERB_PREDEFINED&t;8
multiline_comment|/* user can define reverb modes up to 32 */
DECL|macro|AWE_REVERB_NUMBERS
mdefine_line|#define AWE_REVERB_NUMBERS&t;32
DECL|struct|awe_reverb_fx_rec
r_typedef
r_struct
id|awe_reverb_fx_rec
(brace
DECL|member|parms
r_int
r_int
id|parms
(braket
l_int|28
)braket
suffix:semicolon
DECL|typedef|awe_reverb_fx_rec
)brace
id|awe_reverb_fx_rec
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* chorus mode parameters */
DECL|macro|AWE_CHORUS_1
mdefine_line|#define AWE_CHORUS_1&t;&t;0
DECL|macro|AWE_CHORUS_2
mdefine_line|#define&t;AWE_CHORUS_2&t;&t;1
DECL|macro|AWE_CHORUS_3
mdefine_line|#define&t;AWE_CHORUS_3&t;&t;2
DECL|macro|AWE_CHORUS_4
mdefine_line|#define&t;AWE_CHORUS_4&t;&t;3
DECL|macro|AWE_CHORUS_FEEDBACK
mdefine_line|#define&t;AWE_CHORUS_FEEDBACK&t;4
DECL|macro|AWE_CHORUS_FLANGER
mdefine_line|#define&t;AWE_CHORUS_FLANGER&t;5
DECL|macro|AWE_CHORUS_SHORTDELAY
mdefine_line|#define&t;AWE_CHORUS_SHORTDELAY&t;6
DECL|macro|AWE_CHORUS_SHORTDELAY2
mdefine_line|#define&t;AWE_CHORUS_SHORTDELAY2&t;7
DECL|macro|AWE_CHORUS_PREDEFINED
mdefine_line|#define AWE_CHORUS_PREDEFINED&t;8
multiline_comment|/* user can define chorus modes up to 32 */
DECL|macro|AWE_CHORUS_NUMBERS
mdefine_line|#define AWE_CHORUS_NUMBERS&t;32
DECL|struct|awe_chorus_fx_rec
r_typedef
r_struct
id|awe_chorus_fx_rec
(brace
DECL|member|feedback
r_int
r_int
id|feedback
suffix:semicolon
multiline_comment|/* feedback level (0xE600-0xE6FF) */
DECL|member|delay_offset
r_int
r_int
id|delay_offset
suffix:semicolon
multiline_comment|/* delay (0-0x0DA3) [1/44100 sec] */
DECL|member|lfo_depth
r_int
r_int
id|lfo_depth
suffix:semicolon
multiline_comment|/* LFO depth (0xBC00-0xBCFF) */
DECL|member|delay
r_int
r_int
id|delay
suffix:semicolon
multiline_comment|/* right delay (0-0xFFFFFFFF) [1/256/44100 sec] */
DECL|member|lfo_freq
r_int
r_int
id|lfo_freq
suffix:semicolon
multiline_comment|/* LFO freq LFO freq (0-0xFFFFFFFF) */
DECL|typedef|awe_chorus_fx_rec
)brace
id|awe_chorus_fx_rec
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* misc mode types */
r_enum
(brace
DECL|enumerator|AWE_MD_EXCLUSIVE_OFF
multiline_comment|/* 0*/
id|AWE_MD_EXCLUSIVE_OFF
comma
multiline_comment|/* obsolete */
DECL|enumerator|AWE_MD_EXCLUSIVE_ON
multiline_comment|/* 1*/
id|AWE_MD_EXCLUSIVE_ON
comma
multiline_comment|/* obsolete */
DECL|enumerator|AWE_MD_VERSION
multiline_comment|/* 2*/
id|AWE_MD_VERSION
comma
multiline_comment|/* read only */
DECL|enumerator|AWE_MD_EXCLUSIVE_SOUND
multiline_comment|/* 3*/
id|AWE_MD_EXCLUSIVE_SOUND
comma
multiline_comment|/* 0/1: exclusive note on (default=1) */
DECL|enumerator|AWE_MD_REALTIME_PAN
multiline_comment|/* 4*/
id|AWE_MD_REALTIME_PAN
comma
multiline_comment|/* 0/1: do realtime pan change (default=1) */
DECL|enumerator|AWE_MD_GUS_BANK
multiline_comment|/* 5*/
id|AWE_MD_GUS_BANK
comma
multiline_comment|/* bank number for GUS patches (default=0) */
DECL|enumerator|AWE_MD_KEEP_EFFECT
multiline_comment|/* 6*/
id|AWE_MD_KEEP_EFFECT
comma
multiline_comment|/* 0/1: keep effect values, (default=0) */
DECL|enumerator|AWE_MD_ZERO_ATTEN
multiline_comment|/* 7*/
id|AWE_MD_ZERO_ATTEN
comma
multiline_comment|/* attenuation of max volume (default=32) */
DECL|enumerator|AWE_MD_CHN_PRIOR
multiline_comment|/* 8*/
id|AWE_MD_CHN_PRIOR
comma
multiline_comment|/* 0/1: set MIDI channel priority mode (default=1) */
DECL|enumerator|AWE_MD_MOD_SENSE
multiline_comment|/* 9*/
id|AWE_MD_MOD_SENSE
comma
multiline_comment|/* integer: modwheel sensitivity (def=18) */
DECL|enumerator|AWE_MD_DEF_PRESET
multiline_comment|/*10*/
id|AWE_MD_DEF_PRESET
comma
multiline_comment|/* integer: default preset number (def=0) */
DECL|enumerator|AWE_MD_DEF_BANK
multiline_comment|/*11*/
id|AWE_MD_DEF_BANK
comma
multiline_comment|/* integer: default bank number (def=0) */
DECL|enumerator|AWE_MD_DEF_DRUM
multiline_comment|/*12*/
id|AWE_MD_DEF_DRUM
comma
multiline_comment|/* integer: default drumset number (def=0) */
DECL|enumerator|AWE_MD_TOGGLE_DRUM_BANK
multiline_comment|/*13*/
id|AWE_MD_TOGGLE_DRUM_BANK
comma
multiline_comment|/* 0/1: toggle drum flag with bank# (def=0) */
DECL|enumerator|AWE_MD_NEW_VOLUME_CALC
multiline_comment|/*14*/
id|AWE_MD_NEW_VOLUME_CALC
comma
multiline_comment|/* 0/1: volume calculation mode (def=1) */
DECL|enumerator|AWE_MD_CHORUS_MODE
multiline_comment|/*15*/
id|AWE_MD_CHORUS_MODE
comma
multiline_comment|/* integer: chorus mode (def=2) */
DECL|enumerator|AWE_MD_REVERB_MODE
multiline_comment|/*16*/
id|AWE_MD_REVERB_MODE
comma
multiline_comment|/* integer: chorus mode (def=4) */
DECL|enumerator|AWE_MD_BASS_LEVEL
multiline_comment|/*17*/
id|AWE_MD_BASS_LEVEL
comma
multiline_comment|/* integer: bass level (def=5) */
DECL|enumerator|AWE_MD_TREBLE_LEVEL
multiline_comment|/*18*/
id|AWE_MD_TREBLE_LEVEL
comma
multiline_comment|/* integer: treble level (def=9) */
DECL|enumerator|AWE_MD_DEBUG_MODE
multiline_comment|/*19*/
id|AWE_MD_DEBUG_MODE
comma
multiline_comment|/* integer: debug level (def=0) */
DECL|enumerator|AWE_MD_PAN_EXCHANGE
multiline_comment|/*20*/
id|AWE_MD_PAN_EXCHANGE
comma
multiline_comment|/* 0/1: exchange panning direction (def=0) */
DECL|enumerator|AWE_MD_END
id|AWE_MD_END
comma
)brace
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* effect parameters */
r_enum
(brace
multiline_comment|/* modulation envelope parameters */
DECL|enumerator|AWE_FX_ENV1_DELAY
multiline_comment|/* 0*/
id|AWE_FX_ENV1_DELAY
comma
multiline_comment|/* WORD: ENVVAL */
DECL|enumerator|AWE_FX_ENV1_ATTACK
multiline_comment|/* 1*/
id|AWE_FX_ENV1_ATTACK
comma
multiline_comment|/* BYTE: up ATKHLD */
DECL|enumerator|AWE_FX_ENV1_HOLD
multiline_comment|/* 2*/
id|AWE_FX_ENV1_HOLD
comma
multiline_comment|/* BYTE: lw ATKHLD */
DECL|enumerator|AWE_FX_ENV1_DECAY
multiline_comment|/* 3*/
id|AWE_FX_ENV1_DECAY
comma
multiline_comment|/* BYTE: lw DCYSUS */
DECL|enumerator|AWE_FX_ENV1_RELEASE
multiline_comment|/* 4*/
id|AWE_FX_ENV1_RELEASE
comma
multiline_comment|/* BYTE: lw DCYSUS */
DECL|enumerator|AWE_FX_ENV1_SUSTAIN
multiline_comment|/* 5*/
id|AWE_FX_ENV1_SUSTAIN
comma
multiline_comment|/* BYTE: up DCYSUS */
DECL|enumerator|AWE_FX_ENV1_PITCH
multiline_comment|/* 6*/
id|AWE_FX_ENV1_PITCH
comma
multiline_comment|/* BYTE: up PEFE */
DECL|enumerator|AWE_FX_ENV1_CUTOFF
multiline_comment|/* 7*/
id|AWE_FX_ENV1_CUTOFF
comma
multiline_comment|/* BYTE: lw PEFE */
multiline_comment|/* volume envelope parameters */
DECL|enumerator|AWE_FX_ENV2_DELAY
multiline_comment|/* 8*/
id|AWE_FX_ENV2_DELAY
comma
multiline_comment|/* WORD: ENVVOL */
DECL|enumerator|AWE_FX_ENV2_ATTACK
multiline_comment|/* 9*/
id|AWE_FX_ENV2_ATTACK
comma
multiline_comment|/* BYTE: up ATKHLDV */
DECL|enumerator|AWE_FX_ENV2_HOLD
multiline_comment|/*10*/
id|AWE_FX_ENV2_HOLD
comma
multiline_comment|/* BYTE: lw ATKHLDV */
DECL|enumerator|AWE_FX_ENV2_DECAY
multiline_comment|/*11*/
id|AWE_FX_ENV2_DECAY
comma
multiline_comment|/* BYTE: lw DCYSUSV */
DECL|enumerator|AWE_FX_ENV2_RELEASE
multiline_comment|/*12*/
id|AWE_FX_ENV2_RELEASE
comma
multiline_comment|/* BYTE: lw DCYSUSV */
DECL|enumerator|AWE_FX_ENV2_SUSTAIN
multiline_comment|/*13*/
id|AWE_FX_ENV2_SUSTAIN
comma
multiline_comment|/* BYTE: up DCYSUSV */
multiline_comment|/* LFO1 (tremolo &amp; vibrato) parameters */
DECL|enumerator|AWE_FX_LFO1_DELAY
multiline_comment|/*14*/
id|AWE_FX_LFO1_DELAY
comma
multiline_comment|/* WORD: LFO1VAL */
DECL|enumerator|AWE_FX_LFO1_FREQ
multiline_comment|/*15*/
id|AWE_FX_LFO1_FREQ
comma
multiline_comment|/* BYTE: lo TREMFRQ */
DECL|enumerator|AWE_FX_LFO1_VOLUME
multiline_comment|/*16*/
id|AWE_FX_LFO1_VOLUME
comma
multiline_comment|/* BYTE: up TREMFRQ */
DECL|enumerator|AWE_FX_LFO1_PITCH
multiline_comment|/*17*/
id|AWE_FX_LFO1_PITCH
comma
multiline_comment|/* BYTE: up FMMOD */
DECL|enumerator|AWE_FX_LFO1_CUTOFF
multiline_comment|/*18*/
id|AWE_FX_LFO1_CUTOFF
comma
multiline_comment|/* BYTE: lo FMMOD */
multiline_comment|/* LFO2 (vibrato) parameters */
DECL|enumerator|AWE_FX_LFO2_DELAY
multiline_comment|/*19*/
id|AWE_FX_LFO2_DELAY
comma
multiline_comment|/* WORD: LFO2VAL */
DECL|enumerator|AWE_FX_LFO2_FREQ
multiline_comment|/*20*/
id|AWE_FX_LFO2_FREQ
comma
multiline_comment|/* BYTE: lo FM2FRQ2 */
DECL|enumerator|AWE_FX_LFO2_PITCH
multiline_comment|/*21*/
id|AWE_FX_LFO2_PITCH
comma
multiline_comment|/* BYTE: up FM2FRQ2 */
multiline_comment|/* Other overall effect parameters */
DECL|enumerator|AWE_FX_INIT_PITCH
multiline_comment|/*22*/
id|AWE_FX_INIT_PITCH
comma
multiline_comment|/* SHORT: pitch offset */
DECL|enumerator|AWE_FX_CHORUS
multiline_comment|/*23*/
id|AWE_FX_CHORUS
comma
multiline_comment|/* BYTE: chorus effects send (0-255) */
DECL|enumerator|AWE_FX_REVERB
multiline_comment|/*24*/
id|AWE_FX_REVERB
comma
multiline_comment|/* BYTE: reverb effects send (0-255) */
DECL|enumerator|AWE_FX_CUTOFF
multiline_comment|/*25*/
id|AWE_FX_CUTOFF
comma
multiline_comment|/* BYTE: up IFATN */
DECL|enumerator|AWE_FX_FILTERQ
multiline_comment|/*26*/
id|AWE_FX_FILTERQ
comma
multiline_comment|/* BYTE: up CCCA */
multiline_comment|/* Sample / loop offset changes */
DECL|enumerator|AWE_FX_SAMPLE_START
multiline_comment|/*27*/
id|AWE_FX_SAMPLE_START
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|AWE_FX_LOOP_START
multiline_comment|/*28*/
id|AWE_FX_LOOP_START
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|AWE_FX_LOOP_END
multiline_comment|/*29*/
id|AWE_FX_LOOP_END
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|AWE_FX_COARSE_SAMPLE_START
multiline_comment|/*30*/
id|AWE_FX_COARSE_SAMPLE_START
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|AWE_FX_COARSE_LOOP_START
multiline_comment|/*31*/
id|AWE_FX_COARSE_LOOP_START
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|AWE_FX_COARSE_LOOP_END
multiline_comment|/*32*/
id|AWE_FX_COARSE_LOOP_END
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|AWE_FX_ATTEN
multiline_comment|/*33*/
id|AWE_FX_ATTEN
comma
multiline_comment|/* BYTE: lo IFATN */
DECL|enumerator|AWE_FX_END
id|AWE_FX_END
comma
)brace
suffix:semicolon
macro_line|#endif /* AWE_VOICE_H */
eof
