macro_line|#ifndef __SOUND_ASOUND_FM_H
DECL|macro|__SOUND_ASOUND_FM_H
mdefine_line|#define __SOUND_ASOUND_FM_H
multiline_comment|/*&n; *  Advanced Linux Sound Architecture - ALSA&n; *&n; *  Interface file between ALSA driver &amp; user space&n; *  Copyright (c) 1994-98 by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *                           4Front Technologies&n; *&n; *  Direct FM control&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|SNDRV_DM_FM_MODE_OPL2
mdefine_line|#define SNDRV_DM_FM_MODE_OPL2&t;0x00
DECL|macro|SNDRV_DM_FM_MODE_OPL3
mdefine_line|#define SNDRV_DM_FM_MODE_OPL3&t;0x01
DECL|struct|snd_dm_fm_info
r_typedef
r_struct
id|snd_dm_fm_info
(brace
DECL|member|fm_mode
r_int
r_char
id|fm_mode
suffix:semicolon
multiline_comment|/* OPL mode, see SNDRV_DM_FM_MODE_XXX */
DECL|member|rhythm
r_int
r_char
id|rhythm
suffix:semicolon
multiline_comment|/* percussion mode flag */
DECL|typedef|snd_dm_fm_info_t
)brace
id|snd_dm_fm_info_t
suffix:semicolon
multiline_comment|/*&n; *  Data structure composing an FM &quot;note&quot; or sound event.&n; */
DECL|struct|snd_dm_fm_voice
r_typedef
r_struct
id|snd_dm_fm_voice
(brace
DECL|member|op
r_int
r_char
id|op
suffix:semicolon
multiline_comment|/* operator cell (0 or 1) */
DECL|member|voice
r_int
r_char
id|voice
suffix:semicolon
multiline_comment|/* FM voice (0 to 17) */
DECL|member|am
r_int
r_char
id|am
suffix:semicolon
multiline_comment|/* amplitude modulation */
DECL|member|vibrato
r_int
r_char
id|vibrato
suffix:semicolon
multiline_comment|/* vibrato effect */
DECL|member|do_sustain
r_int
r_char
id|do_sustain
suffix:semicolon
multiline_comment|/* sustain phase */
DECL|member|kbd_scale
r_int
r_char
id|kbd_scale
suffix:semicolon
multiline_comment|/* keyboard scaling */
DECL|member|harmonic
r_int
r_char
id|harmonic
suffix:semicolon
multiline_comment|/* 4 bits: harmonic and multiplier */
DECL|member|scale_level
r_int
r_char
id|scale_level
suffix:semicolon
multiline_comment|/* 2 bits: decrease output freq rises */
DECL|member|volume
r_int
r_char
id|volume
suffix:semicolon
multiline_comment|/* 6 bits: volume */
DECL|member|attack
r_int
r_char
id|attack
suffix:semicolon
multiline_comment|/* 4 bits: attack rate */
DECL|member|decay
r_int
r_char
id|decay
suffix:semicolon
multiline_comment|/* 4 bits: decay rate */
DECL|member|sustain
r_int
r_char
id|sustain
suffix:semicolon
multiline_comment|/* 4 bits: sustain level */
DECL|member|release
r_int
r_char
id|release
suffix:semicolon
multiline_comment|/* 4 bits: release rate */
DECL|member|feedback
r_int
r_char
id|feedback
suffix:semicolon
multiline_comment|/* 3 bits: feedback for op0 */
DECL|member|connection
r_int
r_char
id|connection
suffix:semicolon
multiline_comment|/* 0 for serial, 1 for parallel */
DECL|member|left
r_int
r_char
id|left
suffix:semicolon
multiline_comment|/* stereo left */
DECL|member|right
r_int
r_char
id|right
suffix:semicolon
multiline_comment|/* stereo right */
DECL|member|waveform
r_int
r_char
id|waveform
suffix:semicolon
multiline_comment|/* 3 bits: waveform shape */
DECL|typedef|snd_dm_fm_voice_t
)brace
id|snd_dm_fm_voice_t
suffix:semicolon
multiline_comment|/*&n; *  This describes an FM note by its voice, octave, frequency number (10bit)&n; *  and key on/off.&n; */
DECL|struct|snd_dm_fm_note
r_typedef
r_struct
id|snd_dm_fm_note
(brace
DECL|member|voice
r_int
r_char
id|voice
suffix:semicolon
multiline_comment|/* 0-17 voice channel */
DECL|member|octave
r_int
r_char
id|octave
suffix:semicolon
multiline_comment|/* 3 bits: what octave to play */
DECL|member|fnum
r_int
r_int
id|fnum
suffix:semicolon
multiline_comment|/* 10 bits: frequency number */
DECL|member|key_on
r_int
r_char
id|key_on
suffix:semicolon
multiline_comment|/* set for active, clear for silent */
DECL|typedef|snd_dm_fm_note_t
)brace
id|snd_dm_fm_note_t
suffix:semicolon
multiline_comment|/*&n; *  FM parameters that apply globally to all voices, and thus are not &quot;notes&quot;&n; */
DECL|struct|snd_dm_fm_params
r_typedef
r_struct
id|snd_dm_fm_params
(brace
DECL|member|am_depth
r_int
r_char
id|am_depth
suffix:semicolon
multiline_comment|/* amplitude modulation depth (1=hi) */
DECL|member|vib_depth
r_int
r_char
id|vib_depth
suffix:semicolon
multiline_comment|/* vibrato depth (1=hi) */
DECL|member|kbd_split
r_int
r_char
id|kbd_split
suffix:semicolon
multiline_comment|/* keyboard split */
DECL|member|rhythm
r_int
r_char
id|rhythm
suffix:semicolon
multiline_comment|/* percussion mode select */
multiline_comment|/* This block is the percussion instrument data */
DECL|member|bass
r_int
r_char
id|bass
suffix:semicolon
DECL|member|snare
r_int
r_char
id|snare
suffix:semicolon
DECL|member|tomtom
r_int
r_char
id|tomtom
suffix:semicolon
DECL|member|cymbal
r_int
r_char
id|cymbal
suffix:semicolon
DECL|member|hihat
r_int
r_char
id|hihat
suffix:semicolon
DECL|typedef|snd_dm_fm_params_t
)brace
id|snd_dm_fm_params_t
suffix:semicolon
multiline_comment|/*&n; *  FM mode ioctl settings&n; */
DECL|macro|SNDRV_DM_FM_IOCTL_INFO
mdefine_line|#define SNDRV_DM_FM_IOCTL_INFO&t;&t;_IOR(&squot;H&squot;, 0x20, snd_dm_fm_info_t)
DECL|macro|SNDRV_DM_FM_IOCTL_RESET
mdefine_line|#define SNDRV_DM_FM_IOCTL_RESET&t;&t;_IO (&squot;H&squot;, 0x21)
DECL|macro|SNDRV_DM_FM_IOCTL_PLAY_NOTE
mdefine_line|#define SNDRV_DM_FM_IOCTL_PLAY_NOTE&t;_IOW(&squot;H&squot;, 0x22, snd_dm_fm_note_t)
DECL|macro|SNDRV_DM_FM_IOCTL_SET_VOICE
mdefine_line|#define SNDRV_DM_FM_IOCTL_SET_VOICE&t;_IOW(&squot;H&squot;, 0x23, snd_dm_fm_voice_t)
DECL|macro|SNDRV_DM_FM_IOCTL_SET_PARAMS
mdefine_line|#define SNDRV_DM_FM_IOCTL_SET_PARAMS&t;_IOW(&squot;H&squot;, 0x24, snd_dm_fm_params_t)
DECL|macro|SNDRV_DM_FM_IOCTL_SET_MODE
mdefine_line|#define SNDRV_DM_FM_IOCTL_SET_MODE&t;_IOW(&squot;H&squot;, 0x25, int)
multiline_comment|/* for OPL3 only */
DECL|macro|SNDRV_DM_FM_IOCTL_SET_CONNECTION
mdefine_line|#define SNDRV_DM_FM_IOCTL_SET_CONNECTION&t;_IOW(&squot;H&squot;, 0x26, int)
macro_line|#ifdef __SND_OSS_COMPAT__
DECL|macro|SNDRV_DM_FM_OSS_IOCTL_RESET
mdefine_line|#define SNDRV_DM_FM_OSS_IOCTL_RESET&t;&t;0x20
DECL|macro|SNDRV_DM_FM_OSS_IOCTL_PLAY_NOTE
mdefine_line|#define SNDRV_DM_FM_OSS_IOCTL_PLAY_NOTE&t;&t;0x21
DECL|macro|SNDRV_DM_FM_OSS_IOCTL_SET_VOICE
mdefine_line|#define SNDRV_DM_FM_OSS_IOCTL_SET_VOICE&t;&t;0x22
DECL|macro|SNDRV_DM_FM_OSS_IOCTL_SET_PARAMS
mdefine_line|#define SNDRV_DM_FM_OSS_IOCTL_SET_PARAMS&t;0x23
DECL|macro|SNDRV_DM_FM_OSS_IOCTL_SET_MODE
mdefine_line|#define SNDRV_DM_FM_OSS_IOCTL_SET_MODE&t;&t;0x24
DECL|macro|SNDRV_DM_FM_OSS_IOCTL_SET_OPL
mdefine_line|#define SNDRV_DM_FM_OSS_IOCTL_SET_OPL&t;&t;0x25
macro_line|#endif
macro_line|#endif /* __SOUND_ASOUND_FM_H */
eof
