macro_line|#ifndef __SOUND_EMUX_SYNTH_H
DECL|macro|__SOUND_EMUX_SYNTH_H
mdefine_line|#define __SOUND_EMUX_SYNTH_H
multiline_comment|/*&n; *  Defines for the Emu-series WaveTable chip&n; *&n; *  Copyright (C) 2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;driver.h&quot;
macro_line|#include &quot;core.h&quot;
macro_line|#include &quot;seq_kernel.h&quot;
macro_line|#include &quot;seq_device.h&quot;
macro_line|#include &quot;soundfont.h&quot;
macro_line|#include &quot;seq_midi_emul.h&quot;
macro_line|#ifdef CONFIG_SND_OSSEMUL
macro_line|#include &quot;seq_oss.h&quot;
macro_line|#endif
macro_line|#include &quot;emux_legacy.h&quot;
macro_line|#include &quot;seq_virmidi.h&quot;
multiline_comment|/*&n; * compile flags&n; */
DECL|macro|SNDRV_EMUX_USE_RAW_EFFECT
mdefine_line|#define SNDRV_EMUX_USE_RAW_EFFECT
multiline_comment|/*&n; * typedefs&n; */
DECL|typedef|snd_emux_effect_table_t
r_typedef
r_struct
id|snd_emux_effect_table
id|snd_emux_effect_table_t
suffix:semicolon
DECL|typedef|snd_emux_port_t
r_typedef
r_struct
id|snd_emux_port
id|snd_emux_port_t
suffix:semicolon
DECL|typedef|snd_emux_voice_t
r_typedef
r_struct
id|snd_emux_voice
id|snd_emux_voice_t
suffix:semicolon
DECL|typedef|snd_emux_t
r_typedef
r_struct
id|snd_emux
id|snd_emux_t
suffix:semicolon
multiline_comment|/*&n; * operators&n; */
DECL|struct|snd_emux_operators
r_typedef
r_struct
id|snd_emux_operators
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|get_voice
id|snd_emux_voice_t
op_star
(paren
op_star
id|get_voice
)paren
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
)paren
suffix:semicolon
DECL|member|prepare
r_int
(paren
op_star
id|prepare
)paren
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
DECL|member|trigger
r_void
(paren
op_star
id|trigger
)paren
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
DECL|member|update
r_void
(paren
op_star
id|update
)paren
(paren
id|snd_emux_voice_t
op_star
id|vp
comma
r_int
id|update
)paren
suffix:semicolon
DECL|member|terminate
r_void
(paren
op_star
id|terminate
)paren
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
DECL|member|free_voice
r_void
(paren
op_star
id|free_voice
)paren
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
id|snd_emux_t
op_star
id|emu
comma
r_int
id|ch
)paren
suffix:semicolon
multiline_comment|/* the first parameters are snd_emux_t */
DECL|member|sample_new
r_int
(paren
op_star
id|sample_new
)paren
(paren
id|snd_emux_t
op_star
id|emu
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
id|data
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|sample_free
r_int
(paren
op_star
id|sample_free
)paren
(paren
id|snd_emux_t
op_star
id|emu
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
DECL|member|sample_reset
r_void
(paren
op_star
id|sample_reset
)paren
(paren
id|snd_emux_t
op_star
id|emu
)paren
suffix:semicolon
DECL|member|load_fx
r_int
(paren
op_star
id|load_fx
)paren
(paren
id|snd_emux_t
op_star
id|emu
comma
r_int
id|type
comma
r_int
id|arg
comma
r_const
r_void
op_star
id|data
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|sysex
r_void
(paren
op_star
id|sysex
)paren
(paren
id|snd_emux_t
op_star
id|emu
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|parsed
comma
id|snd_midi_channel_set_t
op_star
id|chset
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|member|oss_ioctl
r_int
(paren
op_star
id|oss_ioctl
)paren
(paren
id|snd_emux_t
op_star
id|emu
comma
r_int
id|cmd
comma
r_int
id|p1
comma
r_int
id|p2
)paren
suffix:semicolon
macro_line|#endif
DECL|typedef|snd_emux_operators_t
)brace
id|snd_emux_operators_t
suffix:semicolon
multiline_comment|/*&n; * constant values&n; */
DECL|macro|SNDRV_EMUX_MAX_PORTS
mdefine_line|#define SNDRV_EMUX_MAX_PORTS&t;&t;32&t;/* max # of sequencer ports */
DECL|macro|SNDRV_EMUX_MAX_VOICES
mdefine_line|#define SNDRV_EMUX_MAX_VOICES&t;&t;64&t;/* max # of voices */
DECL|macro|SNDRV_EMUX_MAX_MULTI_VOICES
mdefine_line|#define SNDRV_EMUX_MAX_MULTI_VOICES&t;16&t;/* max # of playable voices&n;&t;&t;&t;&t;&t;&t; * simultineously&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * flags&n; */
DECL|macro|SNDRV_EMUX_ACCEPT_ROM
mdefine_line|#define SNDRV_EMUX_ACCEPT_ROM&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * emuX wavetable&n; */
DECL|struct|snd_emux
r_struct
id|snd_emux
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* assigned card */
multiline_comment|/* following should be initialized before registration */
DECL|member|max_voices
r_int
id|max_voices
suffix:semicolon
multiline_comment|/* Number of voices */
DECL|member|mem_size
r_int
id|mem_size
suffix:semicolon
multiline_comment|/* memory size (in byte) */
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
multiline_comment|/* number of ports to be created */
DECL|member|pitch_shift
r_int
id|pitch_shift
suffix:semicolon
multiline_comment|/* pitch shift value (for Emu10k1) */
DECL|member|ops
id|snd_emux_operators_t
id|ops
suffix:semicolon
multiline_comment|/* operators */
DECL|member|hw
r_void
op_star
id|hw
suffix:semicolon
multiline_comment|/* hardware */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* other conditions */
DECL|member|midi_ports
r_int
id|midi_ports
suffix:semicolon
multiline_comment|/* number of virtual midi devices */
DECL|member|midi_devidx
r_int
id|midi_devidx
suffix:semicolon
multiline_comment|/* device offset of virtual midi */
multiline_comment|/* private */
DECL|member|num_voices
r_int
id|num_voices
suffix:semicolon
multiline_comment|/* current number of voices */
DECL|member|sflist
id|snd_sf_list_t
op_star
id|sflist
suffix:semicolon
multiline_comment|/* root of SoundFont list */
DECL|member|voices
id|snd_emux_voice_t
op_star
id|voices
suffix:semicolon
multiline_comment|/* Voices (EMU &squot;channel&squot;) */
DECL|member|use_time
r_int
id|use_time
suffix:semicolon
multiline_comment|/* allocation counter */
DECL|member|voice_lock
id|spinlock_t
id|voice_lock
suffix:semicolon
multiline_comment|/* Lock for voice access */
DECL|member|register_mutex
r_struct
id|semaphore
id|register_mutex
suffix:semicolon
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* For the sequencer client */
DECL|member|ports
r_int
id|ports
(braket
id|SNDRV_EMUX_MAX_PORTS
)braket
suffix:semicolon
multiline_comment|/* The ports for this device */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* use counter */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of the device (internal) */
DECL|member|vmidi
id|snd_rawmidi_t
op_star
op_star
id|vmidi
suffix:semicolon
DECL|member|tlist
r_struct
id|timer_list
id|tlist
suffix:semicolon
multiline_comment|/* for pending note-offs */
DECL|member|timer_active
r_int
id|timer_active
suffix:semicolon
DECL|member|memhdr
id|snd_util_memhdr_t
op_star
id|memhdr
suffix:semicolon
multiline_comment|/* memory chunk information */
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|proc
id|snd_info_entry_t
op_star
id|proc
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|member|oss_synth
id|snd_seq_device_t
op_star
id|oss_synth
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * sequencer port information&n; */
DECL|struct|snd_emux_port
r_struct
id|snd_emux_port
(brace
DECL|member|chset
id|snd_midi_channel_set_t
id|chset
suffix:semicolon
DECL|member|emu
id|snd_emux_t
op_star
id|emu
suffix:semicolon
DECL|member|port_mode
r_char
id|port_mode
suffix:semicolon
multiline_comment|/* operation mode */
DECL|member|volume_atten
r_int
id|volume_atten
suffix:semicolon
multiline_comment|/* emuX raw attenuation */
DECL|member|drum_flags
r_int
r_int
id|drum_flags
suffix:semicolon
multiline_comment|/* drum bitmaps */
DECL|member|ctrls
r_int
id|ctrls
(braket
id|EMUX_MD_END
)braket
suffix:semicolon
multiline_comment|/* control parameters */
macro_line|#ifdef SNDRV_EMUX_USE_RAW_EFFECT
DECL|member|effect
id|snd_emux_effect_table_t
op_star
id|effect
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|member|oss_arg
id|snd_seq_oss_arg_t
op_star
id|oss_arg
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* port_mode */
DECL|macro|SNDRV_EMUX_PORT_MODE_MIDI
mdefine_line|#define SNDRV_EMUX_PORT_MODE_MIDI&t;&t;0&t;/* normal MIDI port */
DECL|macro|SNDRV_EMUX_PORT_MODE_OSS_SYNTH
mdefine_line|#define SNDRV_EMUX_PORT_MODE_OSS_SYNTH&t;1&t;/* OSS synth port */
DECL|macro|SNDRV_EMUX_PORT_MODE_OSS_MIDI
mdefine_line|#define SNDRV_EMUX_PORT_MODE_OSS_MIDI&t;2&t;/* OSS multi channel synth port */
multiline_comment|/*&n; * A structure to keep track of each hardware voice&n; */
DECL|struct|snd_emux_voice
r_struct
id|snd_emux_voice
(brace
DECL|member|ch
r_int
id|ch
suffix:semicolon
multiline_comment|/* Hardware channel number */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* status */
DECL|macro|SNDRV_EMUX_ST_OFF
mdefine_line|#define SNDRV_EMUX_ST_OFF&t;&t;0x00&t;/* Not playing, and inactive */
DECL|macro|SNDRV_EMUX_ST_ON
mdefine_line|#define SNDRV_EMUX_ST_ON&t;&t;0x01&t;/* Note on */
DECL|macro|SNDRV_EMUX_ST_RELEASED
mdefine_line|#define SNDRV_EMUX_ST_RELEASED &t;(0x02|SNDRV_EMUX_ST_ON)&t;/* Note released */
DECL|macro|SNDRV_EMUX_ST_SUSTAINED
mdefine_line|#define SNDRV_EMUX_ST_SUSTAINED&t;(0x04|SNDRV_EMUX_ST_ON)&t;/* Note sustained */
DECL|macro|SNDRV_EMUX_ST_STANDBY
mdefine_line|#define SNDRV_EMUX_ST_STANDBY&t;(0x08|SNDRV_EMUX_ST_ON)&t;/* Waiting to be triggered */
DECL|macro|SNDRV_EMUX_ST_PENDING
mdefine_line|#define SNDRV_EMUX_ST_PENDING &t;(0x10|SNDRV_EMUX_ST_ON)&t;/* Note will be released */
DECL|macro|SNDRV_EMUX_ST_LOCKED
mdefine_line|#define SNDRV_EMUX_ST_LOCKED&t;&t;0x100&t;/* Not accessible */
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
multiline_comment|/* An allocation time */
DECL|member|note
r_int
r_char
id|note
suffix:semicolon
multiline_comment|/* Note currently assigned to this voice */
DECL|member|key
r_int
r_char
id|key
suffix:semicolon
DECL|member|velocity
r_int
r_char
id|velocity
suffix:semicolon
multiline_comment|/* Velocity of current note */
DECL|member|zone
id|snd_sf_zone_t
op_star
id|zone
suffix:semicolon
multiline_comment|/* Zone assigned to this note */
DECL|member|block
r_void
op_star
id|block
suffix:semicolon
multiline_comment|/* sample block pointer (optional) */
DECL|member|chan
id|snd_midi_channel_t
op_star
id|chan
suffix:semicolon
multiline_comment|/* Midi channel for this note */
DECL|member|port
id|snd_emux_port_t
op_star
id|port
suffix:semicolon
multiline_comment|/* associated port */
DECL|member|emu
id|snd_emux_t
op_star
id|emu
suffix:semicolon
multiline_comment|/* assigned root info */
DECL|member|hw
r_void
op_star
id|hw
suffix:semicolon
multiline_comment|/* hardware pointer (emu8000_t or emu10k1_t) */
DECL|member|ontime
r_int
r_int
id|ontime
suffix:semicolon
multiline_comment|/* jiffies at note triggered */
multiline_comment|/* Emu8k/Emu10k1 registers */
DECL|member|reg
id|soundfont_voice_info_t
id|reg
suffix:semicolon
multiline_comment|/* additional registers */
DECL|member|avol
r_int
id|avol
suffix:semicolon
multiline_comment|/* volume attenuation */
DECL|member|acutoff
r_int
id|acutoff
suffix:semicolon
multiline_comment|/* cutoff target */
DECL|member|apitch
r_int
id|apitch
suffix:semicolon
multiline_comment|/* pitch offset */
DECL|member|apan
r_int
id|apan
suffix:semicolon
multiline_comment|/* pan/aux pair */
DECL|member|aaux
r_int
id|aaux
suffix:semicolon
DECL|member|ptarget
r_int
id|ptarget
suffix:semicolon
multiline_comment|/* pitch target */
DECL|member|vtarget
r_int
id|vtarget
suffix:semicolon
multiline_comment|/* volume target */
DECL|member|ftarget
r_int
id|ftarget
suffix:semicolon
multiline_comment|/* filter target */
)brace
suffix:semicolon
multiline_comment|/*&n; * update flags (can be combined)&n; */
DECL|macro|SNDRV_EMUX_UPDATE_VOLUME
mdefine_line|#define SNDRV_EMUX_UPDATE_VOLUME&t;&t;(1&lt;&lt;0)
DECL|macro|SNDRV_EMUX_UPDATE_PITCH
mdefine_line|#define SNDRV_EMUX_UPDATE_PITCH&t;&t;(1&lt;&lt;1)
DECL|macro|SNDRV_EMUX_UPDATE_PAN
mdefine_line|#define SNDRV_EMUX_UPDATE_PAN&t;&t;(1&lt;&lt;2)
DECL|macro|SNDRV_EMUX_UPDATE_FMMOD
mdefine_line|#define SNDRV_EMUX_UPDATE_FMMOD&t;&t;(1&lt;&lt;3)
DECL|macro|SNDRV_EMUX_UPDATE_TREMFREQ
mdefine_line|#define SNDRV_EMUX_UPDATE_TREMFREQ&t;(1&lt;&lt;4)
DECL|macro|SNDRV_EMUX_UPDATE_FM2FRQ2
mdefine_line|#define SNDRV_EMUX_UPDATE_FM2FRQ2&t;&t;(1&lt;&lt;5)
DECL|macro|SNDRV_EMUX_UPDATE_Q
mdefine_line|#define SNDRV_EMUX_UPDATE_Q&t;&t;(1&lt;&lt;6)
macro_line|#ifdef SNDRV_EMUX_USE_RAW_EFFECT
multiline_comment|/*&n; * effect table&n; */
DECL|struct|snd_emux_effect_table
r_struct
id|snd_emux_effect_table
(brace
multiline_comment|/* Emu8000 specific effects */
DECL|member|val
r_int
id|val
(braket
id|EMUX_NUM_EFFECTS
)braket
suffix:semicolon
DECL|member|flag
r_int
r_char
id|flag
(braket
id|EMUX_NUM_EFFECTS
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* SNDRV_EMUX_USE_RAW_EFFECT */
multiline_comment|/*&n; * prototypes - interface to Emu10k1 and Emu8k routines&n; */
r_int
id|snd_emux_new
c_func
(paren
id|snd_emux_t
op_star
op_star
id|remu
)paren
suffix:semicolon
r_int
id|snd_emux_register
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|index
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|snd_emux_free
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
suffix:semicolon
multiline_comment|/*&n; * exported functions&n; */
r_void
id|snd_emux_terminate_all
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
suffix:semicolon
r_void
id|snd_emux_lock_voice
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
r_int
id|voice
)paren
suffix:semicolon
r_void
id|snd_emux_unlock_voice
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
r_int
id|voice
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_EMUX_SYNTH_H */
eof
