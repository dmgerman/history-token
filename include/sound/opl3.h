macro_line|#ifndef __SOUND_OPL3_H
DECL|macro|__SOUND_OPL3_H
mdefine_line|#define __SOUND_OPL3_H
multiline_comment|/*&n; * Definitions of the OPL-3 registers.&n; *&n; * Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *                  Hannu Savolainen 1993-1996&n; *&n; *&n; *      The OPL-3 mode is switched on by writing 0x01, to the offset 5&n; *      of the right side.&n; *&n; *      Another special register at the right side is at offset 4. It contains&n; *      a bit mask defining which voices are used as 4 OP voices.&n; *&n; *      The percussive mode is implemented in the left side only.&n; *&n; *      With the above exceptions the both sides can be operated independently.&n; *      &n; *      A 4 OP voice can be created by setting the corresponding&n; *      bit at offset 4 of the right side.&n; *&n; *      For example setting the rightmost bit (0x01) changes the&n; *      first voice on the right side to the 4 OP mode. The fourth&n; *      voice is made inaccessible.&n; *&n; *      If a voice is set to the 2 OP mode, it works like 2 OP modes&n; *      of the original YM3812 (AdLib). In addition the voice can &n; *      be connected the left, right or both stereo channels. It can&n; *      even be left unconnected. This works with 4 OP voices also.&n; *&n; *      The stereo connection bits are located in the FEEDBACK_CONNECTION&n; *      register of the voice (0xC0-0xC8). In 4 OP voices these bits are&n; *      in the second half of the voice.&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;driver.h&quot;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &quot;core.h&quot;
macro_line|#include &quot;hwdep.h&quot;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &quot;seq_midi_emul.h&quot;
macro_line|#ifdef CONFIG_SND_SEQUENCER_OSS
macro_line|#include &quot;seq_oss.h&quot;
macro_line|#include &quot;seq_oss_legacy.h&quot;
macro_line|#endif
macro_line|#include &quot;seq_device.h&quot;
macro_line|#include &quot;ainstr_fm.h&quot;
multiline_comment|/*&n; *    Register numbers for the global registers&n; */
DECL|macro|OPL3_REG_TEST
mdefine_line|#define OPL3_REG_TEST&t;&t;&t;0x01
DECL|macro|OPL3_ENABLE_WAVE_SELECT
mdefine_line|#define   OPL3_ENABLE_WAVE_SELECT&t;0x20
DECL|macro|OPL3_REG_TIMER1
mdefine_line|#define OPL3_REG_TIMER1&t;&t;&t;0x02
DECL|macro|OPL3_REG_TIMER2
mdefine_line|#define OPL3_REG_TIMER2&t;&t;&t;0x03
DECL|macro|OPL3_REG_TIMER_CONTROL
mdefine_line|#define OPL3_REG_TIMER_CONTROL&t;&t;0x04&t;/* Left side */
DECL|macro|OPL3_IRQ_RESET
mdefine_line|#define   OPL3_IRQ_RESET&t;&t;0x80
DECL|macro|OPL3_TIMER1_MASK
mdefine_line|#define   OPL3_TIMER1_MASK&t;&t;0x40
DECL|macro|OPL3_TIMER2_MASK
mdefine_line|#define   OPL3_TIMER2_MASK&t;&t;0x20
DECL|macro|OPL3_TIMER1_START
mdefine_line|#define   OPL3_TIMER1_START&t;&t;0x01
DECL|macro|OPL3_TIMER2_START
mdefine_line|#define   OPL3_TIMER2_START&t;&t;0x02
DECL|macro|OPL3_REG_CONNECTION_SELECT
mdefine_line|#define OPL3_REG_CONNECTION_SELECT&t;0x04&t;/* Right side */
DECL|macro|OPL3_LEFT_4OP_0
mdefine_line|#define   OPL3_LEFT_4OP_0&t;&t;0x01
DECL|macro|OPL3_LEFT_4OP_1
mdefine_line|#define   OPL3_LEFT_4OP_1&t;&t;0x02
DECL|macro|OPL3_LEFT_4OP_2
mdefine_line|#define   OPL3_LEFT_4OP_2&t;&t;0x04
DECL|macro|OPL3_RIGHT_4OP_0
mdefine_line|#define   OPL3_RIGHT_4OP_0&t;&t;0x08
DECL|macro|OPL3_RIGHT_4OP_1
mdefine_line|#define   OPL3_RIGHT_4OP_1&t;&t;0x10
DECL|macro|OPL3_RIGHT_4OP_2
mdefine_line|#define   OPL3_RIGHT_4OP_2&t;&t;0x20
DECL|macro|OPL3_REG_MODE
mdefine_line|#define OPL3_REG_MODE&t;&t;&t;0x05&t;/* Right side */
DECL|macro|OPL3_OPL3_ENABLE
mdefine_line|#define   OPL3_OPL3_ENABLE&t;&t;0x01&t;/* OPL3 mode */
DECL|macro|OPL3_OPL4_ENABLE
mdefine_line|#define   OPL3_OPL4_ENABLE&t;&t;0x02&t;/* OPL4 mode */
DECL|macro|OPL3_REG_KBD_SPLIT
mdefine_line|#define OPL3_REG_KBD_SPLIT&t;&t;0x08&t;/* Left side */
DECL|macro|OPL3_COMPOSITE_SINE_WAVE_MODE
mdefine_line|#define   OPL3_COMPOSITE_SINE_WAVE_MODE&t;0x80&t;/* Don&squot;t use with OPL-3? */
DECL|macro|OPL3_KEYBOARD_SPLIT
mdefine_line|#define   OPL3_KEYBOARD_SPLIT&t;&t;0x40
DECL|macro|OPL3_REG_PERCUSSION
mdefine_line|#define OPL3_REG_PERCUSSION&t;&t;0xbd&t;/* Left side only */
DECL|macro|OPL3_TREMOLO_DEPTH
mdefine_line|#define   OPL3_TREMOLO_DEPTH&t;&t;0x80
DECL|macro|OPL3_VIBRATO_DEPTH
mdefine_line|#define   OPL3_VIBRATO_DEPTH&t;&t;0x40
DECL|macro|OPL3_PERCUSSION_ENABLE
mdefine_line|#define&t;  OPL3_PERCUSSION_ENABLE&t;0x20
DECL|macro|OPL3_BASSDRUM_ON
mdefine_line|#define   OPL3_BASSDRUM_ON&t;&t;0x10
DECL|macro|OPL3_SNAREDRUM_ON
mdefine_line|#define   OPL3_SNAREDRUM_ON&t;&t;0x08
DECL|macro|OPL3_TOMTOM_ON
mdefine_line|#define   OPL3_TOMTOM_ON&t;&t;0x04
DECL|macro|OPL3_CYMBAL_ON
mdefine_line|#define   OPL3_CYMBAL_ON&t;&t;0x02
DECL|macro|OPL3_HIHAT_ON
mdefine_line|#define   OPL3_HIHAT_ON&t;&t;&t;0x01
multiline_comment|/*&n; *    Offsets to the register banks for operators. To get the&n; *      register number just add the operator offset to the bank offset&n; *&n; *      AM/VIB/EG/KSR/Multiple (0x20 to 0x35)&n; */
DECL|macro|OPL3_REG_AM_VIB
mdefine_line|#define OPL3_REG_AM_VIB&t;&t;&t;0x20
DECL|macro|OPL3_TREMOLO_ON
mdefine_line|#define   OPL3_TREMOLO_ON&t;&t;0x80
DECL|macro|OPL3_VIBRATO_ON
mdefine_line|#define   OPL3_VIBRATO_ON&t;&t;0x40
DECL|macro|OPL3_SUSTAIN_ON
mdefine_line|#define   OPL3_SUSTAIN_ON&t;&t;0x20
DECL|macro|OPL3_KSR
mdefine_line|#define   OPL3_KSR&t;&t;&t;0x10&t;/* Key scaling rate */
DECL|macro|OPL3_MULTIPLE_MASK
mdefine_line|#define   OPL3_MULTIPLE_MASK&t;&t;0x0f&t;/* Frequency multiplier */
multiline_comment|/*&n;  *   KSL/Total level (0x40 to 0x55)&n;  */
DECL|macro|OPL3_REG_KSL_LEVEL
mdefine_line|#define OPL3_REG_KSL_LEVEL&t;&t;0x40
DECL|macro|OPL3_KSL_MASK
mdefine_line|#define   OPL3_KSL_MASK&t;&t;&t;0xc0&t;/* Envelope scaling bits */
DECL|macro|OPL3_TOTAL_LEVEL_MASK
mdefine_line|#define   OPL3_TOTAL_LEVEL_MASK&t;&t;0x3f&t;/* Strength (volume) of OP */
multiline_comment|/*&n; *    Attack / Decay rate (0x60 to 0x75)&n; */
DECL|macro|OPL3_REG_ATTACK_DECAY
mdefine_line|#define OPL3_REG_ATTACK_DECAY&t;&t;0x60
DECL|macro|OPL3_ATTACK_MASK
mdefine_line|#define   OPL3_ATTACK_MASK&t;&t;0xf0
DECL|macro|OPL3_DECAY_MASK
mdefine_line|#define   OPL3_DECAY_MASK&t;&t;0x0f
multiline_comment|/*&n; * Sustain level / Release rate (0x80 to 0x95)&n; */
DECL|macro|OPL3_REG_SUSTAIN_RELEASE
mdefine_line|#define OPL3_REG_SUSTAIN_RELEASE&t;0x80
DECL|macro|OPL3_SUSTAIN_MASK
mdefine_line|#define   OPL3_SUSTAIN_MASK&t;&t;0xf0
DECL|macro|OPL3_RELEASE_MASK
mdefine_line|#define   OPL3_RELEASE_MASK&t;&t;0x0f
multiline_comment|/*&n; * Wave select (0xE0 to 0xF5)&n; */
DECL|macro|OPL3_REG_WAVE_SELECT
mdefine_line|#define OPL3_REG_WAVE_SELECT&t;&t;0xe0
DECL|macro|OPL3_WAVE_SELECT_MASK
mdefine_line|#define   OPL3_WAVE_SELECT_MASK&t;&t;0x07
multiline_comment|/*&n; *    Offsets to the register banks for voices. Just add to the&n; *      voice number to get the register number.&n; *&n; *      F-Number low bits (0xA0 to 0xA8).&n; */
DECL|macro|OPL3_REG_FNUM_LOW
mdefine_line|#define OPL3_REG_FNUM_LOW&t;&t;0xa0
multiline_comment|/*&n; *    F-number high bits / Key on / Block (octave) (0xB0 to 0xB8)&n; */
DECL|macro|OPL3_REG_KEYON_BLOCK
mdefine_line|#define OPL3_REG_KEYON_BLOCK&t;&t;0xb0
DECL|macro|OPL3_KEYON_BIT
mdefine_line|#define&t;  OPL3_KEYON_BIT&t;&t;0x20
DECL|macro|OPL3_BLOCKNUM_MASK
mdefine_line|#define&t;  OPL3_BLOCKNUM_MASK&t;&t;0x1c
DECL|macro|OPL3_FNUM_HIGH_MASK
mdefine_line|#define   OPL3_FNUM_HIGH_MASK&t;&t;0x03
multiline_comment|/*&n; *    Feedback / Connection (0xc0 to 0xc8)&n; *&n; *      These registers have two new bits when the OPL-3 mode&n; *      is selected. These bits controls connecting the voice&n; *      to the stereo channels. For 4 OP voices this bit is&n; *      defined in the second half of the voice (add 3 to the&n; *      register offset).&n; *&n; *      For 4 OP voices the connection bit is used in the&n; *      both halves (gives 4 ways to connect the operators).&n; */
DECL|macro|OPL3_REG_FEEDBACK_CONNECTION
mdefine_line|#define OPL3_REG_FEEDBACK_CONNECTION&t;0xc0
DECL|macro|OPL3_FEEDBACK_MASK
mdefine_line|#define   OPL3_FEEDBACK_MASK&t;&t;0x0e&t;/* Valid just for 1st OP of a voice */
DECL|macro|OPL3_CONNECTION_BIT
mdefine_line|#define   OPL3_CONNECTION_BIT&t;&t;0x01
multiline_comment|/*&n; *    In the 4 OP mode there is four possible configurations how the&n; *      operators can be connected together (in 2 OP modes there is just&n; *      AM or FM). The 4 OP connection mode is defined by the rightmost&n; *      bit of the FEEDBACK_CONNECTION (0xC0-0xC8) on the both halves.&n; *&n; *      First half      Second half     Mode&n; *&n; *                                       +---+&n; *                                       v   |&n; *      0               0               &gt;+-1-+--2--3--4--&gt;&n; *&n; *&n; *                                      &n; *                                       +---+&n; *                                       |   |&n; *      0               1               &gt;+-1-+--2-+&n; *                                                |-&gt;&n; *                                      &gt;--3----4-+&n; *                                      &n; *                                       +---+&n; *                                       |   |&n; *      1               0               &gt;+-1-+-----+&n; *                                                 |-&gt;&n; *                                      &gt;--2--3--4-+&n; *&n; *                                       +---+&n; *                                       |   |&n; *      1               1               &gt;+-1-+--+&n; *                                              |&n; *                                      &gt;--2--3-+-&gt;&n; *                                              |&n; *                                      &gt;--4----+&n; */
DECL|macro|OPL3_STEREO_BITS
mdefine_line|#define   OPL3_STEREO_BITS&t;&t;0x30&t;/* OPL-3 only */
DECL|macro|OPL3_VOICE_TO_LEFT
mdefine_line|#define     OPL3_VOICE_TO_LEFT&t;&t;0x10
DECL|macro|OPL3_VOICE_TO_RIGHT
mdefine_line|#define     OPL3_VOICE_TO_RIGHT&t;&t;0x20
multiline_comment|/*&n;&n; */
DECL|macro|OPL3_LEFT
mdefine_line|#define OPL3_LEFT&t;&t;0x0000
DECL|macro|OPL3_RIGHT
mdefine_line|#define OPL3_RIGHT&t;&t;0x0100
DECL|macro|OPL3_HW_AUTO
mdefine_line|#define OPL3_HW_AUTO&t;&t;0x0000
DECL|macro|OPL3_HW_OPL2
mdefine_line|#define OPL3_HW_OPL2&t;&t;0x0200
DECL|macro|OPL3_HW_OPL3
mdefine_line|#define OPL3_HW_OPL3&t;&t;0x0300
DECL|macro|OPL3_HW_OPL3_SV
mdefine_line|#define OPL3_HW_OPL3_SV&t;&t;0x0301&t;/* S3 SonicVibes */
DECL|macro|OPL3_HW_OPL3_CS
mdefine_line|#define OPL3_HW_OPL3_CS&t;&t;0x0302&t;/* CS4232/CS4236+ */
DECL|macro|OPL3_HW_OPL3_FM801
mdefine_line|#define OPL3_HW_OPL3_FM801&t;0x0303&t;/* FM801 */
DECL|macro|OPL3_HW_OPL3_CS4281
mdefine_line|#define OPL3_HW_OPL3_CS4281&t;0x0304&t;/* CS4281 */
DECL|macro|OPL3_HW_OPL4
mdefine_line|#define OPL3_HW_OPL4&t;&t;0x0400
DECL|macro|OPL3_HW_MASK
mdefine_line|#define OPL3_HW_MASK&t;&t;0xff00
DECL|macro|MAX_OPL2_VOICES
mdefine_line|#define MAX_OPL2_VOICES&t;&t;9
DECL|macro|MAX_OPL3_VOICES
mdefine_line|#define MAX_OPL3_VOICES&t;&t;18
DECL|typedef|opl3_t
r_typedef
r_struct
id|snd_opl3
id|opl3_t
suffix:semicolon
multiline_comment|/*&n; * A structure to keep track of each hardware voice&n; */
DECL|struct|snd_opl3_voice
r_typedef
r_struct
id|snd_opl3_voice
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* status */
DECL|macro|SNDRV_OPL3_ST_OFF
mdefine_line|#define SNDRV_OPL3_ST_OFF&t;&t;0&t;/* Not playing */
DECL|macro|SNDRV_OPL3_ST_ON_2OP
mdefine_line|#define SNDRV_OPL3_ST_ON_2OP&t;1&t;/* 2op voice is allocated */
DECL|macro|SNDRV_OPL3_ST_ON_4OP
mdefine_line|#define SNDRV_OPL3_ST_ON_4OP&t;2&t;/* 4op voice is allocated */
DECL|macro|SNDRV_OPL3_ST_NOT_AVAIL
mdefine_line|#define SNDRV_OPL3_ST_NOT_AVAIL&t;-1&t;/* voice is not available */
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
DECL|member|note_off
r_int
r_int
id|note_off
suffix:semicolon
multiline_comment|/* note-off time */
DECL|member|note_off_check
r_int
id|note_off_check
suffix:semicolon
multiline_comment|/* check note-off time */
DECL|member|keyon_reg
r_int
r_char
id|keyon_reg
suffix:semicolon
multiline_comment|/* KON register shadow */
DECL|member|chan
id|snd_midi_channel_t
op_star
id|chan
suffix:semicolon
multiline_comment|/* Midi channel for this note */
DECL|typedef|snd_opl3_voice_t
)brace
id|snd_opl3_voice_t
suffix:semicolon
DECL|struct|snd_opl3
r_struct
id|snd_opl3
(brace
DECL|member|l_port
r_int
r_int
id|l_port
suffix:semicolon
DECL|member|r_port
r_int
r_int
id|r_port
suffix:semicolon
DECL|member|res_l_port
r_struct
id|resource
op_star
id|res_l_port
suffix:semicolon
DECL|member|res_r_port
r_struct
id|resource
op_star
id|res_r_port
suffix:semicolon
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
multiline_comment|/* hardware access */
DECL|member|command
r_void
(paren
op_star
id|command
)paren
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
r_int
id|cmd
comma
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|member|timer_enable
r_int
r_int
id|timer_enable
suffix:semicolon
DECL|member|seq_dev_num
r_int
id|seq_dev_num
suffix:semicolon
multiline_comment|/* sequencer device number */
DECL|member|timer1
id|snd_timer_t
op_star
id|timer1
suffix:semicolon
DECL|member|timer2
id|snd_timer_t
op_star
id|timer2
suffix:semicolon
DECL|member|timer_lock
id|spinlock_t
id|timer_lock
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
multiline_comment|/* The card that this belongs to */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* usage flag - exclusive */
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
DECL|member|max_voices
r_int
r_char
id|max_voices
suffix:semicolon
multiline_comment|/* max number of voices */
macro_line|#if defined(CONFIG_SND_SEQUENCER) || defined(CONFIG_SND_SEQUENCER_MODULE)
DECL|macro|SNDRV_OPL3_MODE_SYNTH
mdefine_line|#define SNDRV_OPL3_MODE_SYNTH 0&t;&t;/* OSS - voices allocated by application */
DECL|macro|SNDRV_OPL3_MODE_SEQ
mdefine_line|#define SNDRV_OPL3_MODE_SEQ 1&t;&t;/* ALSA - driver handles voice allocation */
DECL|member|synth_mode
r_int
id|synth_mode
suffix:semicolon
multiline_comment|/* synth mode */
DECL|member|seq_client
r_int
id|seq_client
suffix:semicolon
DECL|member|seq_dev
id|snd_seq_device_t
op_star
id|seq_dev
suffix:semicolon
multiline_comment|/* sequencer device */
DECL|member|chset
id|snd_midi_channel_set_t
op_star
id|chset
suffix:semicolon
macro_line|#ifdef CONFIG_SND_SEQUENCER_OSS
DECL|member|oss_seq_dev
id|snd_seq_device_t
op_star
id|oss_seq_dev
suffix:semicolon
multiline_comment|/* OSS sequencer device, WIP */
DECL|member|oss_chset
id|snd_midi_channel_set_t
op_star
id|oss_chset
suffix:semicolon
macro_line|#endif
DECL|member|fm_ops
id|snd_seq_kinstr_ops_t
id|fm_ops
suffix:semicolon
DECL|member|ilist
id|snd_seq_kinstr_list_t
op_star
id|ilist
suffix:semicolon
DECL|member|voices
id|snd_opl3_voice_t
id|voices
(braket
id|MAX_OPL3_VOICES
)braket
suffix:semicolon
multiline_comment|/* Voices (OPL3 &squot;channel&squot;) */
DECL|member|use_time
r_int
id|use_time
suffix:semicolon
multiline_comment|/* allocation counter */
DECL|member|connection_reg
r_int
r_int
id|connection_reg
suffix:semicolon
multiline_comment|/* connection reg shadow */
DECL|member|drum_reg
r_int
r_char
id|drum_reg
suffix:semicolon
multiline_comment|/* percussion reg shadow */
DECL|member|voice_lock
id|spinlock_t
id|voice_lock
suffix:semicolon
multiline_comment|/* Lock for voice access */
DECL|member|tlist
r_struct
id|timer_list
id|tlist
suffix:semicolon
multiline_comment|/* timer for note-offs and effects */
DECL|member|sys_timer_status
r_int
id|sys_timer_status
suffix:semicolon
multiline_comment|/* system timer run status */
DECL|member|sys_timer_lock
id|spinlock_t
id|sys_timer_lock
suffix:semicolon
multiline_comment|/* Lock for system timer access */
macro_line|#endif
DECL|member|access_mutex
r_struct
id|semaphore
id|access_mutex
suffix:semicolon
multiline_comment|/* locking */
)brace
suffix:semicolon
multiline_comment|/* opl3.c */
r_void
id|snd_opl3_interrupt
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
)paren
suffix:semicolon
r_int
id|snd_opl3_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|l_port
comma
r_int
r_int
id|r_port
comma
r_int
r_int
id|hardware
comma
r_int
id|integrated
comma
id|opl3_t
op_star
op_star
id|opl3
)paren
suffix:semicolon
r_int
id|snd_opl3_timer_new
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
id|timer1_dev
comma
r_int
id|timer2_dev
)paren
suffix:semicolon
r_int
id|snd_opl3_hwdep_new
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_int
id|device
comma
r_int
id|seq_device
comma
id|snd_hwdep_t
op_star
op_star
id|rhwdep
)paren
suffix:semicolon
multiline_comment|/* opl3_synth */
r_int
id|snd_opl3_open
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_int
id|snd_opl3_ioctl
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|snd_opl3_release
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_void
id|snd_opl3_reset
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_OPL3_H */
eof
