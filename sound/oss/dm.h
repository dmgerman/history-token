macro_line|#ifndef _DRIVERS_SOUND_DM_H
DECL|macro|_DRIVERS_SOUND_DM_H
mdefine_line|#define _DRIVERS_SOUND_DM_H
multiline_comment|/*&n; *&t;Definitions of the &squot;direct midi sound&squot; interface used&n; *&t;by the newer commercial OSS package. We should export&n; *&t;this to userland somewhere in glibc later.&n; */
multiline_comment|/*&n; * Data structure composing an FM &quot;note&quot; or sound event.&n; */
DECL|struct|dm_fm_voice
r_struct
id|dm_fm_voice
(brace
DECL|member|op
id|u8
id|op
suffix:semicolon
DECL|member|voice
id|u8
id|voice
suffix:semicolon
DECL|member|am
id|u8
id|am
suffix:semicolon
DECL|member|vibrato
id|u8
id|vibrato
suffix:semicolon
DECL|member|do_sustain
id|u8
id|do_sustain
suffix:semicolon
DECL|member|kbd_scale
id|u8
id|kbd_scale
suffix:semicolon
DECL|member|harmonic
id|u8
id|harmonic
suffix:semicolon
DECL|member|scale_level
id|u8
id|scale_level
suffix:semicolon
DECL|member|volume
id|u8
id|volume
suffix:semicolon
DECL|member|attack
id|u8
id|attack
suffix:semicolon
DECL|member|decay
id|u8
id|decay
suffix:semicolon
DECL|member|sustain
id|u8
id|sustain
suffix:semicolon
DECL|member|release
id|u8
id|release
suffix:semicolon
DECL|member|feedback
id|u8
id|feedback
suffix:semicolon
DECL|member|connection
id|u8
id|connection
suffix:semicolon
DECL|member|left
id|u8
id|left
suffix:semicolon
DECL|member|right
id|u8
id|right
suffix:semicolon
DECL|member|waveform
id|u8
id|waveform
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;This describes an FM note by its voice, octave, frequency number (10bit)&n; *&t;and key on/off.&n; */
DECL|struct|dm_fm_note
r_struct
id|dm_fm_note
(brace
DECL|member|voice
id|u8
id|voice
suffix:semicolon
DECL|member|octave
id|u8
id|octave
suffix:semicolon
DECL|member|fnum
id|u32
id|fnum
suffix:semicolon
DECL|member|key_on
id|u8
id|key_on
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * FM parameters that apply globally to all voices, and thus are not &quot;notes&quot;&n; */
DECL|struct|dm_fm_params
r_struct
id|dm_fm_params
(brace
DECL|member|am_depth
id|u8
id|am_depth
suffix:semicolon
DECL|member|vib_depth
id|u8
id|vib_depth
suffix:semicolon
DECL|member|kbd_split
id|u8
id|kbd_split
suffix:semicolon
DECL|member|rhythm
id|u8
id|rhythm
suffix:semicolon
multiline_comment|/* This block is the percussion instrument data */
DECL|member|bass
id|u8
id|bass
suffix:semicolon
DECL|member|snare
id|u8
id|snare
suffix:semicolon
DECL|member|tomtom
id|u8
id|tomtom
suffix:semicolon
DECL|member|cymbal
id|u8
id|cymbal
suffix:semicolon
DECL|member|hihat
id|u8
id|hihat
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;FM mode ioctl settings&n; */
DECL|macro|FM_IOCTL_RESET
mdefine_line|#define FM_IOCTL_RESET        0x20
DECL|macro|FM_IOCTL_PLAY_NOTE
mdefine_line|#define FM_IOCTL_PLAY_NOTE    0x21
DECL|macro|FM_IOCTL_SET_VOICE
mdefine_line|#define FM_IOCTL_SET_VOICE    0x22
DECL|macro|FM_IOCTL_SET_PARAMS
mdefine_line|#define FM_IOCTL_SET_PARAMS   0x23
DECL|macro|FM_IOCTL_SET_MODE
mdefine_line|#define FM_IOCTL_SET_MODE     0x24
DECL|macro|FM_IOCTL_SET_OPL
mdefine_line|#define FM_IOCTL_SET_OPL      0x25
macro_line|#endif
eof