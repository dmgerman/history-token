multiline_comment|/*&n; * Local definitions for the OPL4 driver&n; *&n; * Copyright (c) 2003 by Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed and/or modified under the&n; * terms of the GNU General Public License as published by the Free Software&n; * Foundation; either version 2 of the License, or (at your option) any later&n; * version.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef __OPL4_LOCAL_H
DECL|macro|__OPL4_LOCAL_H
mdefine_line|#define __OPL4_LOCAL_H
macro_line|#include &lt;sound/opl4.h&gt;
multiline_comment|/*&n; * Register numbers&n; */
DECL|macro|OPL4_REG_TEST0
mdefine_line|#define OPL4_REG_TEST0&t;&t;&t;0x00
DECL|macro|OPL4_REG_TEST1
mdefine_line|#define OPL4_REG_TEST1&t;&t;&t;0x01
DECL|macro|OPL4_REG_MEMORY_CONFIGURATION
mdefine_line|#define OPL4_REG_MEMORY_CONFIGURATION&t;0x02
DECL|macro|OPL4_MODE_BIT
mdefine_line|#define   OPL4_MODE_BIT&t;&t;&t;0x01
DECL|macro|OPL4_MTYPE_BIT
mdefine_line|#define   OPL4_MTYPE_BIT&t;&t;0x02
DECL|macro|OPL4_TONE_HEADER_MASK
mdefine_line|#define   OPL4_TONE_HEADER_MASK&t;&t;0x1c
DECL|macro|OPL4_DEVICE_ID_MASK
mdefine_line|#define   OPL4_DEVICE_ID_MASK&t;&t;0xe0
DECL|macro|OPL4_REG_MEMORY_ADDRESS_HIGH
mdefine_line|#define OPL4_REG_MEMORY_ADDRESS_HIGH&t;0x03
DECL|macro|OPL4_REG_MEMORY_ADDRESS_MID
mdefine_line|#define OPL4_REG_MEMORY_ADDRESS_MID&t;0x04
DECL|macro|OPL4_REG_MEMORY_ADDRESS_LOW
mdefine_line|#define OPL4_REG_MEMORY_ADDRESS_LOW&t;0x05
DECL|macro|OPL4_REG_MEMORY_DATA
mdefine_line|#define OPL4_REG_MEMORY_DATA&t;&t;0x06
multiline_comment|/*&n; * Offsets to the register banks for voices. To get the&n; * register number just add the voice number to the bank offset.&n; *&n; * Wave Table Number low bits (0x08 to 0x1F)&n; */
DECL|macro|OPL4_REG_TONE_NUMBER
mdefine_line|#define OPL4_REG_TONE_NUMBER&t;&t;0x08
multiline_comment|/* Wave Table Number high bit, F-Number low bits (0x20 to 0x37) */
DECL|macro|OPL4_REG_F_NUMBER
mdefine_line|#define OPL4_REG_F_NUMBER&t;&t;0x20
DECL|macro|OPL4_TONE_NUMBER_BIT8
mdefine_line|#define   OPL4_TONE_NUMBER_BIT8&t;&t;0x01
DECL|macro|OPL4_F_NUMBER_LOW_MASK
mdefine_line|#define   OPL4_F_NUMBER_LOW_MASK&t;0xfe
multiline_comment|/* F-Number high bits, Octave, Pseudo-Reverb (0x38 to 0x4F) */
DECL|macro|OPL4_REG_OCTAVE
mdefine_line|#define OPL4_REG_OCTAVE&t;&t;&t;0x38
DECL|macro|OPL4_F_NUMBER_HIGH_MASK
mdefine_line|#define   OPL4_F_NUMBER_HIGH_MASK&t;0x07
DECL|macro|OPL4_BLOCK_MASK
mdefine_line|#define   OPL4_BLOCK_MASK&t;&t;0xf0
DECL|macro|OPL4_PSEUDO_REVERB_BIT
mdefine_line|#define   OPL4_PSEUDO_REVERB_BIT&t;0x08
multiline_comment|/* Total Level, Level Direct (0x50 to 0x67) */
DECL|macro|OPL4_REG_LEVEL
mdefine_line|#define OPL4_REG_LEVEL&t;&t;&t;0x50
DECL|macro|OPL4_TOTAL_LEVEL_MASK
mdefine_line|#define   OPL4_TOTAL_LEVEL_MASK&t;&t;0xfe
DECL|macro|OPL4_LEVEL_DIRECT_BIT
mdefine_line|#define   OPL4_LEVEL_DIRECT_BIT&t;&t;0x01
multiline_comment|/* Key On, Damp, LFO RST, CH, Panpot (0x68 to 0x7F) */
DECL|macro|OPL4_REG_MISC
mdefine_line|#define OPL4_REG_MISC&t;&t;&t;0x68
DECL|macro|OPL4_KEY_ON_BIT
mdefine_line|#define   OPL4_KEY_ON_BIT&t;&t;0x80
DECL|macro|OPL4_DAMP_BIT
mdefine_line|#define   OPL4_DAMP_BIT&t;&t;&t;0x40
DECL|macro|OPL4_LFO_RESET_BIT
mdefine_line|#define   OPL4_LFO_RESET_BIT&t;&t;0x20
DECL|macro|OPL4_OUTPUT_CHANNEL_BIT
mdefine_line|#define   OPL4_OUTPUT_CHANNEL_BIT&t;0x10
DECL|macro|OPL4_PAN_POT_MASK
mdefine_line|#define   OPL4_PAN_POT_MASK&t;&t;0x0f
multiline_comment|/* LFO, VIB (0x80 to 0x97) */
DECL|macro|OPL4_REG_LFO_VIBRATO
mdefine_line|#define OPL4_REG_LFO_VIBRATO&t;&t;0x80
DECL|macro|OPL4_LFO_FREQUENCY_MASK
mdefine_line|#define   OPL4_LFO_FREQUENCY_MASK&t;0x38
DECL|macro|OPL4_VIBRATO_DEPTH_MASK
mdefine_line|#define   OPL4_VIBRATO_DEPTH_MASK&t;0x07
DECL|macro|OPL4_CHORUS_SEND_MASK
mdefine_line|#define   OPL4_CHORUS_SEND_MASK&t;&t;0xc0 /* ML only */
multiline_comment|/* Attack / Decay 1 rate (0x98 to 0xAF) */
DECL|macro|OPL4_REG_ATTACK_DECAY1
mdefine_line|#define OPL4_REG_ATTACK_DECAY1&t;&t;0x98
DECL|macro|OPL4_ATTACK_RATE_MASK
mdefine_line|#define   OPL4_ATTACK_RATE_MASK&t;&t;0xf0
DECL|macro|OPL4_DECAY1_RATE_MASK
mdefine_line|#define   OPL4_DECAY1_RATE_MASK&t;&t;0x0f
multiline_comment|/* Decay level / 2 rate (0xB0 to 0xC7) */
DECL|macro|OPL4_REG_LEVEL_DECAY2
mdefine_line|#define OPL4_REG_LEVEL_DECAY2&t;&t;0xb0
DECL|macro|OPL4_DECAY_LEVEL_MASK
mdefine_line|#define   OPL4_DECAY_LEVEL_MASK&t;&t;0xf0
DECL|macro|OPL4_DECAY2_RATE_MASK
mdefine_line|#define   OPL4_DECAY2_RATE_MASK&t;&t;0x0f
multiline_comment|/* Release rate / Rate correction (0xC8 to 0xDF) */
DECL|macro|OPL4_REG_RELEASE_CORRECTION
mdefine_line|#define OPL4_REG_RELEASE_CORRECTION&t;0xc8
DECL|macro|OPL4_RELEASE_RATE_MASK
mdefine_line|#define   OPL4_RELEASE_RATE_MASK&t;0x0f
DECL|macro|OPL4_RATE_INTERPOLATION_MASK
mdefine_line|#define   OPL4_RATE_INTERPOLATION_MASK&t;0xf0
multiline_comment|/* AM (0xE0 to 0xF7) */
DECL|macro|OPL4_REG_TREMOLO
mdefine_line|#define OPL4_REG_TREMOLO&t;&t;0xe0
DECL|macro|OPL4_TREMOLO_DEPTH_MASK
mdefine_line|#define   OPL4_TREMOLO_DEPTH_MASK&t;0x07
DECL|macro|OPL4_REVERB_SEND_MASK
mdefine_line|#define   OPL4_REVERB_SEND_MASK&t;&t;0xe0 /* ML only */
multiline_comment|/* Mixer */
DECL|macro|OPL4_REG_MIX_CONTROL_FM
mdefine_line|#define OPL4_REG_MIX_CONTROL_FM&t;&t;0xf8
DECL|macro|OPL4_REG_MIX_CONTROL_PCM
mdefine_line|#define OPL4_REG_MIX_CONTROL_PCM&t;0xf9
DECL|macro|OPL4_MIX_LEFT_MASK
mdefine_line|#define   OPL4_MIX_LEFT_MASK&t;&t;0x07
DECL|macro|OPL4_MIX_RIGHT_MASK
mdefine_line|#define   OPL4_MIX_RIGHT_MASK&t;&t;0x38
DECL|macro|OPL4_REG_ATC
mdefine_line|#define OPL4_REG_ATC&t;&t;&t;0xfa
DECL|macro|OPL4_ATC_BIT
mdefine_line|#define   OPL4_ATC_BIT&t;&t;&t;0x01 /* ???, ML only */
multiline_comment|/* bits in the OPL3 Status register */
DECL|macro|OPL4_STATUS_BUSY
mdefine_line|#define OPL4_STATUS_BUSY&t;&t;0x01
DECL|macro|OPL4_STATUS_LOAD
mdefine_line|#define OPL4_STATUS_LOAD&t;&t;0x02
DECL|macro|OPL4_MAX_VOICES
mdefine_line|#define OPL4_MAX_VOICES 24
DECL|macro|SNDRV_SEQ_DEV_ID_OPL4
mdefine_line|#define SNDRV_SEQ_DEV_ID_OPL4 &quot;opl4-synth&quot;
DECL|struct|opl4_sound
r_typedef
r_struct
id|opl4_sound
(brace
DECL|member|tone
id|u16
id|tone
suffix:semicolon
DECL|member|pitch_offset
id|s16
id|pitch_offset
suffix:semicolon
DECL|member|key_scaling
id|u8
id|key_scaling
suffix:semicolon
DECL|member|panpot
id|s8
id|panpot
suffix:semicolon
DECL|member|vibrato
id|u8
id|vibrato
suffix:semicolon
DECL|member|tone_attenuate
id|u8
id|tone_attenuate
suffix:semicolon
DECL|member|volume_factor
id|u8
id|volume_factor
suffix:semicolon
DECL|member|reg_lfo_vibrato
id|u8
id|reg_lfo_vibrato
suffix:semicolon
DECL|member|reg_attack_decay1
id|u8
id|reg_attack_decay1
suffix:semicolon
DECL|member|reg_level_decay2
id|u8
id|reg_level_decay2
suffix:semicolon
DECL|member|reg_release_correction
id|u8
id|reg_release_correction
suffix:semicolon
DECL|member|reg_tremolo
id|u8
id|reg_tremolo
suffix:semicolon
DECL|typedef|opl4_sound_t
)brace
id|opl4_sound_t
suffix:semicolon
DECL|struct|opl4_region
r_typedef
r_struct
id|opl4_region
(brace
DECL|member|key_min
DECL|member|key_max
id|u8
id|key_min
comma
id|key_max
suffix:semicolon
DECL|member|sound
id|opl4_sound_t
id|sound
suffix:semicolon
DECL|typedef|opl4_region_t
)brace
id|opl4_region_t
suffix:semicolon
DECL|struct|opl4_region_ptr
r_typedef
r_struct
id|opl4_region_ptr
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|regions
r_const
id|opl4_region_t
op_star
id|regions
suffix:semicolon
DECL|typedef|opl4_region_ptr_t
)brace
id|opl4_region_ptr_t
suffix:semicolon
DECL|struct|opl4_voice
r_typedef
r_struct
id|opl4_voice
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|chan
id|snd_midi_channel_t
op_star
id|chan
suffix:semicolon
DECL|member|note
r_int
id|note
suffix:semicolon
DECL|member|velocity
r_int
id|velocity
suffix:semicolon
DECL|member|sound
r_const
id|opl4_sound_t
op_star
id|sound
suffix:semicolon
DECL|member|reg_f_number
id|u8
id|reg_f_number
suffix:semicolon
DECL|member|reg_misc
id|u8
id|reg_misc
suffix:semicolon
DECL|typedef|opl4_voice_t
)brace
id|opl4_voice_t
suffix:semicolon
DECL|struct|opl4
r_struct
id|opl4
(brace
DECL|member|fm_port
r_int
r_int
id|fm_port
suffix:semicolon
DECL|member|pcm_port
r_int
r_int
id|pcm_port
suffix:semicolon
DECL|member|res_fm_port
r_struct
id|resource
op_star
id|res_fm_port
suffix:semicolon
DECL|member|res_pcm_port
r_struct
id|resource
op_star
id|res_pcm_port
suffix:semicolon
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
DECL|member|memory_access
r_int
id|memory_access
suffix:semicolon
macro_line|#endif
DECL|member|access_mutex
r_struct
id|semaphore
id|access_mutex
suffix:semicolon
macro_line|#if defined(CONFIG_SND_SEQUENCER) || defined(CONFIG_SND_SEQUENCER_MODULE)
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|seq_dev_num
r_int
id|seq_dev_num
suffix:semicolon
DECL|member|seq_client
r_int
id|seq_client
suffix:semicolon
DECL|member|seq_dev
id|snd_seq_device_t
op_star
id|seq_dev
suffix:semicolon
DECL|member|chset
id|snd_midi_channel_set_t
op_star
id|chset
suffix:semicolon
DECL|member|voices
id|opl4_voice_t
id|voices
(braket
id|OPL4_MAX_VOICES
)braket
suffix:semicolon
DECL|member|off_voices
r_struct
id|list_head
id|off_voices
suffix:semicolon
DECL|member|on_voices
r_struct
id|list_head
id|on_voices
suffix:semicolon
DECL|member|voices_lock
id|spinlock_t
id|voices_lock
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* opl4_lib.c */
r_void
id|snd_opl4_write
c_func
(paren
id|opl4_t
op_star
id|opl4
comma
id|u8
id|reg
comma
id|u8
id|value
)paren
suffix:semicolon
id|u8
id|snd_opl4_read
c_func
(paren
id|opl4_t
op_star
id|opl4
comma
id|u8
id|reg
)paren
suffix:semicolon
r_void
id|snd_opl4_read_memory
c_func
(paren
id|opl4_t
op_star
id|opl4
comma
r_char
op_star
id|buf
comma
r_int
id|offset
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|snd_opl4_write_memory
c_func
(paren
id|opl4_t
op_star
id|opl4
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|offset
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* opl4_mixer.c */
r_int
id|snd_opl4_create_mixer
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* opl4_proc.c */
r_int
id|snd_opl4_create_proc
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
suffix:semicolon
r_void
id|snd_opl4_free_proc
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* opl4_seq.c */
r_extern
r_int
id|volume_boost
suffix:semicolon
multiline_comment|/* opl4_synth.c */
r_void
id|snd_opl4_synth_reset
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
suffix:semicolon
r_void
id|snd_opl4_synth_shutdown
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
suffix:semicolon
r_void
id|snd_opl4_note_on
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|note
comma
r_int
id|vel
comma
id|snd_midi_channel_t
op_star
id|chan
)paren
suffix:semicolon
r_void
id|snd_opl4_note_off
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|note
comma
r_int
id|vel
comma
id|snd_midi_channel_t
op_star
id|chan
)paren
suffix:semicolon
r_void
id|snd_opl4_terminate_note
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|note
comma
id|snd_midi_channel_t
op_star
id|chan
)paren
suffix:semicolon
r_void
id|snd_opl4_control
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|type
comma
id|snd_midi_channel_t
op_star
id|chan
)paren
suffix:semicolon
r_void
id|snd_opl4_sysex
c_func
(paren
r_void
op_star
id|p
comma
r_int
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
multiline_comment|/* yrw801.c */
r_int
id|snd_yrw801_detect
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
suffix:semicolon
r_extern
r_const
id|opl4_region_ptr_t
id|snd_yrw801_regions
(braket
)braket
suffix:semicolon
macro_line|#endif /* __OPL4_LOCAL_H */
eof
