multiline_comment|/* &n; * audio.h&n; *&n; * Copyright (C) 2000 Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                  &amp; Marcus Metzler &lt;marcus@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Lesser Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVBAUDIO_H_
DECL|macro|_DVBAUDIO_H_
mdefine_line|#define _DVBAUDIO_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#else
macro_line|#include &lt;stdint.h&gt;
macro_line|#endif
r_typedef
r_enum
(brace
DECL|enumerator|AUDIO_SOURCE_DEMUX
id|AUDIO_SOURCE_DEMUX
comma
multiline_comment|/* Select the demux as the main source */
DECL|enumerator|AUDIO_SOURCE_MEMORY
id|AUDIO_SOURCE_MEMORY
multiline_comment|/* Select internal memory as the main source */
DECL|typedef|audio_stream_source_t
)brace
id|audio_stream_source_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AUDIO_STOPPED
id|AUDIO_STOPPED
comma
multiline_comment|/* Device is stopped */
DECL|enumerator|AUDIO_PLAYING
id|AUDIO_PLAYING
comma
multiline_comment|/* Device is currently playing */
DECL|enumerator|AUDIO_PAUSED
id|AUDIO_PAUSED
multiline_comment|/* Device is paused */
DECL|typedef|audio_play_state_t
)brace
id|audio_play_state_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AUDIO_STEREO
id|AUDIO_STEREO
comma
DECL|enumerator|AUDIO_MONO_LEFT
id|AUDIO_MONO_LEFT
comma
DECL|enumerator|AUDIO_MONO_RIGHT
id|AUDIO_MONO_RIGHT
DECL|typedef|audio_channel_select_t
)brace
id|audio_channel_select_t
suffix:semicolon
DECL|struct|audio_mixer
r_typedef
r_struct
id|audio_mixer
(brace
DECL|member|volume_left
r_int
r_int
id|volume_left
suffix:semicolon
DECL|member|volume_right
r_int
r_int
id|volume_right
suffix:semicolon
singleline_comment|// what else do we need? bass, pass-through, ...
DECL|typedef|audio_mixer_t
)brace
id|audio_mixer_t
suffix:semicolon
DECL|struct|audio_status
r_typedef
r_struct
id|audio_status
(brace
DECL|member|AV_sync_state
r_int
id|AV_sync_state
suffix:semicolon
multiline_comment|/* sync audio and video? */
DECL|member|mute_state
r_int
id|mute_state
suffix:semicolon
multiline_comment|/* audio is muted */
DECL|member|play_state
id|audio_play_state_t
id|play_state
suffix:semicolon
multiline_comment|/* current playback state */
DECL|member|stream_source
id|audio_stream_source_t
id|stream_source
suffix:semicolon
multiline_comment|/* current stream source */
DECL|member|channel_select
id|audio_channel_select_t
id|channel_select
suffix:semicolon
multiline_comment|/* currently selected channel */
DECL|member|bypass_mode
r_int
id|bypass_mode
suffix:semicolon
multiline_comment|/* pass on audio data to */
DECL|member|mixer_state
id|audio_mixer_t
id|mixer_state
suffix:semicolon
multiline_comment|/* current mixer state */
DECL|typedef|audio_status_t
)brace
id|audio_status_t
suffix:semicolon
multiline_comment|/* separate decoder hardware */
r_typedef
DECL|struct|audio_karaoke
r_struct
id|audio_karaoke
(brace
multiline_comment|/* if Vocal1 or Vocal2 are non-zero, they get mixed  */
DECL|member|vocal1
r_int
id|vocal1
suffix:semicolon
multiline_comment|/* into left and right t at 70% each */
DECL|member|vocal2
r_int
id|vocal2
suffix:semicolon
multiline_comment|/* if both, Vocal1 and Vocal2 are non-zero, Vocal1 gets*/
DECL|member|melody
r_int
id|melody
suffix:semicolon
multiline_comment|/* mixed into the left channel and */
multiline_comment|/* Vocal2 into the right channel at 100% each. */
multiline_comment|/* if Melody is non-zero, the melody channel gets mixed*/
DECL|typedef|audio_karaoke_t
)brace
id|audio_karaoke_t
suffix:semicolon
multiline_comment|/* into left and right  */
DECL|typedef|audio_attributes_t
r_typedef
r_uint16
id|audio_attributes_t
suffix:semicolon
multiline_comment|/*   bits: descr. */
multiline_comment|/*   15-13 audio coding mode (0=ac3, 2=mpeg1, 3=mpeg2ext, 4=LPCM, 6=DTS, */
multiline_comment|/*   12    multichannel extension */
multiline_comment|/*   11-10 audio type (0=not spec, 1=language included) */
multiline_comment|/*    9- 8 audio application mode (0=not spec, 1=karaoke, 2=surround) */
multiline_comment|/*    7- 6 Quantization / DRC (mpeg audio: 1=DRC exists)(lpcm: 0=16bit,  */
multiline_comment|/*    5- 4 Sample frequency fs (0=48kHz, 1=96kHz) */
multiline_comment|/*    2- 0 number of audio channels (n+1 channels) */
multiline_comment|/* for GET_CAPABILITIES and SET_FORMAT, the latter should only set one bit */
DECL|macro|AUDIO_CAP_DTS
mdefine_line|#define AUDIO_CAP_DTS    1
DECL|macro|AUDIO_CAP_LPCM
mdefine_line|#define AUDIO_CAP_LPCM   2
DECL|macro|AUDIO_CAP_MP1
mdefine_line|#define AUDIO_CAP_MP1    4
DECL|macro|AUDIO_CAP_MP2
mdefine_line|#define AUDIO_CAP_MP2    8
DECL|macro|AUDIO_CAP_MP3
mdefine_line|#define AUDIO_CAP_MP3   16
DECL|macro|AUDIO_CAP_AAC
mdefine_line|#define AUDIO_CAP_AAC   32
DECL|macro|AUDIO_CAP_OGG
mdefine_line|#define AUDIO_CAP_OGG   64
DECL|macro|AUDIO_CAP_SDDS
mdefine_line|#define AUDIO_CAP_SDDS 128
DECL|macro|AUDIO_CAP_AC3
mdefine_line|#define AUDIO_CAP_AC3  256
DECL|macro|AUDIO_STOP
mdefine_line|#define AUDIO_STOP                 _IO(&squot;o&squot;, 1) 
DECL|macro|AUDIO_PLAY
mdefine_line|#define AUDIO_PLAY                 _IO(&squot;o&squot;, 2)
DECL|macro|AUDIO_PAUSE
mdefine_line|#define AUDIO_PAUSE                _IO(&squot;o&squot;, 3)
DECL|macro|AUDIO_CONTINUE
mdefine_line|#define AUDIO_CONTINUE             _IO(&squot;o&squot;, 4)
DECL|macro|AUDIO_SELECT_SOURCE
mdefine_line|#define AUDIO_SELECT_SOURCE        _IO(&squot;o&squot;, 5)
DECL|macro|AUDIO_SET_MUTE
mdefine_line|#define AUDIO_SET_MUTE             _IO(&squot;o&squot;, 6)
DECL|macro|AUDIO_SET_AV_SYNC
mdefine_line|#define AUDIO_SET_AV_SYNC          _IO(&squot;o&squot;, 7)
DECL|macro|AUDIO_SET_BYPASS_MODE
mdefine_line|#define AUDIO_SET_BYPASS_MODE      _IO(&squot;o&squot;, 8)
DECL|macro|AUDIO_CHANNEL_SELECT
mdefine_line|#define AUDIO_CHANNEL_SELECT       _IO(&squot;o&squot;, 9)
DECL|macro|AUDIO_GET_STATUS
mdefine_line|#define AUDIO_GET_STATUS           _IOR(&squot;o&squot;, 10, audio_status_t)
DECL|macro|AUDIO_GET_CAPABILITIES
mdefine_line|#define AUDIO_GET_CAPABILITIES     _IOR(&squot;o&squot;, 11, unsigned int)
DECL|macro|AUDIO_CLEAR_BUFFER
mdefine_line|#define AUDIO_CLEAR_BUFFER         _IO(&squot;o&squot;,  12)
DECL|macro|AUDIO_SET_ID
mdefine_line|#define AUDIO_SET_ID               _IO(&squot;o&squot;, 13)
DECL|macro|AUDIO_SET_MIXER
mdefine_line|#define AUDIO_SET_MIXER            _IOW(&squot;o&squot;, 14, audio_mixer_t)
DECL|macro|AUDIO_SET_STREAMTYPE
mdefine_line|#define AUDIO_SET_STREAMTYPE       _IO(&squot;o&squot;, 15)
DECL|macro|AUDIO_SET_EXT_ID
mdefine_line|#define AUDIO_SET_EXT_ID           _IO(&squot;o&squot;, 16)
DECL|macro|AUDIO_SET_ATTRIBUTES
mdefine_line|#define AUDIO_SET_ATTRIBUTES       _IOW(&squot;o&squot;, 17, audio_attributes_t)
DECL|macro|AUDIO_SET_KARAOKE
mdefine_line|#define AUDIO_SET_KARAOKE          _IOW(&squot;o&squot;, 18, audio_karaoke_t)
macro_line|#endif /* _DVBAUDIO_H_ */
eof
