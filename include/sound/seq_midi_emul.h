macro_line|#ifndef __SOUND_SEQ_MIDI_EMUL_H
DECL|macro|__SOUND_SEQ_MIDI_EMUL_H
mdefine_line|#define __SOUND_SEQ_MIDI_EMUL_H
multiline_comment|/*&n; *  Midi channel definition for optional channel management.&n; *&n; *  Copyright (C) 1999 Steve Ratcliffe&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;seq_kernel.h&quot;
multiline_comment|/*&n; * This structure is used to keep track of the current state on each&n; * channel.  All drivers for hardware that does not understand midi&n; * directly will probably need to use this structure.&n; */
DECL|struct|snd_midi_channel
r_typedef
r_struct
id|snd_midi_channel
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* A back pointer to driver data */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* The channel number */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* The client associated with this channel */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* The port associated with this channel */
DECL|member|midi_mode
r_int
r_char
id|midi_mode
suffix:semicolon
multiline_comment|/* GM, GS, XG etc */
r_int
r_int
DECL|member|drum_channel
id|drum_channel
suffix:colon
l_int|1
comma
multiline_comment|/* Drum channel */
DECL|member|param_type
id|param_type
suffix:colon
l_int|1
multiline_comment|/* RPN/NRPN */
suffix:semicolon
DECL|member|midi_aftertouch
r_int
r_char
id|midi_aftertouch
suffix:semicolon
multiline_comment|/* Aftertouch (key pressure) */
DECL|member|midi_pressure
r_int
r_char
id|midi_pressure
suffix:semicolon
multiline_comment|/* Channel pressure */
DECL|member|midi_program
r_int
r_char
id|midi_program
suffix:semicolon
multiline_comment|/* Instrument number */
DECL|member|midi_pitchbend
r_int
id|midi_pitchbend
suffix:semicolon
multiline_comment|/* Pitch bend amount */
DECL|member|control
r_int
r_char
id|control
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Current value of all controls */
DECL|member|note
r_int
r_char
id|note
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Current status for all notes */
DECL|member|gm_rpn_pitch_bend_range
r_int
id|gm_rpn_pitch_bend_range
suffix:semicolon
multiline_comment|/* Pitch bend range */
DECL|member|gm_rpn_fine_tuning
r_int
id|gm_rpn_fine_tuning
suffix:semicolon
multiline_comment|/* Master fine tuning */
DECL|member|gm_rpn_coarse_tuning
r_int
id|gm_rpn_coarse_tuning
suffix:semicolon
multiline_comment|/* Master coarse tuning */
DECL|typedef|snd_midi_channel_t
)brace
id|snd_midi_channel_t
suffix:semicolon
multiline_comment|/*&n; * A structure that represets a set of channels bound to a port.  There&n; * would usually be 16 channels per port.  But fewer could be used for&n; * particular cases.&n; * The channel set consists of information describing the client and&n; * port for this midi synth and an array of snd_midi_channel_t structures.&n; * A driver that had no need for snd_midi_channel_t could still use the&n; * channel set type if it wished with the channel array null.&n; */
DECL|struct|snd_midi_channel_set
r_typedef
r_struct
id|snd_midi_channel_set
(brace
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* Driver data */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* Client for this port */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* The port number */
DECL|member|max_channels
r_int
id|max_channels
suffix:semicolon
multiline_comment|/* Size of the channels array */
DECL|member|channels
id|snd_midi_channel_t
op_star
id|channels
suffix:semicolon
DECL|member|midi_mode
r_int
r_char
id|midi_mode
suffix:semicolon
multiline_comment|/* MIDI operating mode */
DECL|member|gs_master_volume
r_int
r_char
id|gs_master_volume
suffix:semicolon
multiline_comment|/* SYSEX master volume: 0-127 */
DECL|member|gs_chorus_mode
r_int
r_char
id|gs_chorus_mode
suffix:semicolon
DECL|member|gs_reverb_mode
r_int
r_char
id|gs_reverb_mode
suffix:semicolon
DECL|typedef|snd_midi_channel_set_t
)brace
id|snd_midi_channel_set_t
suffix:semicolon
DECL|struct|snd_seq_midi_op
r_typedef
r_struct
id|snd_seq_midi_op
(brace
DECL|member|note_on
r_void
(paren
op_star
id|note_on
)paren
(paren
r_void
op_star
id|private_data
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
DECL|member|note_off
r_void
(paren
op_star
id|note_off
)paren
(paren
r_void
op_star
id|private_data
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
multiline_comment|/* release note */
DECL|member|key_press
r_void
(paren
op_star
id|key_press
)paren
(paren
r_void
op_star
id|private_data
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
DECL|member|note_terminate
r_void
(paren
op_star
id|note_terminate
)paren
(paren
r_void
op_star
id|private_data
comma
r_int
id|note
comma
id|snd_midi_channel_t
op_star
id|chan
)paren
suffix:semicolon
multiline_comment|/* terminate note immediately */
DECL|member|control
r_void
(paren
op_star
id|control
)paren
(paren
r_void
op_star
id|private_data
comma
r_int
id|type
comma
id|snd_midi_channel_t
op_star
id|chan
)paren
suffix:semicolon
DECL|member|nrpn
r_void
(paren
op_star
id|nrpn
)paren
(paren
r_void
op_star
id|private_data
comma
id|snd_midi_channel_t
op_star
id|chan
comma
id|snd_midi_channel_set_t
op_star
id|chset
)paren
suffix:semicolon
DECL|member|sysex
r_void
(paren
op_star
id|sysex
)paren
(paren
r_void
op_star
id|private_data
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
DECL|typedef|snd_midi_op_t
)brace
id|snd_midi_op_t
suffix:semicolon
multiline_comment|/*&n; * These defines are used so that pitchbend, aftertouch etc, can be&n; * distinguished from controller values.&n; */
multiline_comment|/* 0-127 controller values */
DECL|macro|MIDI_CTL_PITCHBEND
mdefine_line|#define MIDI_CTL_PITCHBEND&t;0x80
DECL|macro|MIDI_CTL_AFTERTOUCH
mdefine_line|#define MIDI_CTL_AFTERTOUCH&t;0x81
DECL|macro|MIDI_CTL_CHAN_PRESSURE
mdefine_line|#define MIDI_CTL_CHAN_PRESSURE&t;0x82
multiline_comment|/*&n; * These names exist to allow symbolic access to the controls array.&n; * The usage is eg: chan-&gt;gm_bank_select.  Another implementation would&n; * be really have these members in the struct, and not the array.&n; */
DECL|macro|gm_bank_select
mdefine_line|#define gm_bank_select&t;&t;control[0]
DECL|macro|gm_modulation
mdefine_line|#define gm_modulation&t;&t;control[1]
DECL|macro|gm_breath
mdefine_line|#define gm_breath&t;&t;control[2]
DECL|macro|gm_foot_pedal
mdefine_line|#define gm_foot_pedal&t;&t;control[4]
DECL|macro|gm_portamento_time
mdefine_line|#define gm_portamento_time&t;control[5]
DECL|macro|gm_data_entry
mdefine_line|#define gm_data_entry&t;&t;control[6]
DECL|macro|gm_volume
mdefine_line|#define gm_volume&t;&t;control[7]
DECL|macro|gm_balance
mdefine_line|#define gm_balance&t;&t;control[8]
DECL|macro|gm_pan
mdefine_line|#define gm_pan&t;&t;&t;control[10]
DECL|macro|gm_expression
mdefine_line|#define gm_expression&t;&t;control[11]
DECL|macro|gm_effect_control1
mdefine_line|#define gm_effect_control1&t;control[12]
DECL|macro|gm_effect_control2
mdefine_line|#define gm_effect_control2&t;control[13]
DECL|macro|gm_slider1
mdefine_line|#define gm_slider1&t;&t;control[16]
DECL|macro|gm_slider2
mdefine_line|#define gm_slider2&t;&t;control[17]
DECL|macro|gm_slider3
mdefine_line|#define gm_slider3&t;&t;control[18]
DECL|macro|gm_slider4
mdefine_line|#define gm_slider4&t;&t;control[19]
DECL|macro|gm_bank_select_lsb
mdefine_line|#define gm_bank_select_lsb&t;control[32]
DECL|macro|gm_modulation_wheel_lsb
mdefine_line|#define gm_modulation_wheel_lsb&t;control[33]
DECL|macro|gm_breath_lsb
mdefine_line|#define gm_breath_lsb&t;&t;control[34]
DECL|macro|gm_foot_pedal_lsb
mdefine_line|#define gm_foot_pedal_lsb&t;control[36]
DECL|macro|gm_portamento_time_lsb
mdefine_line|#define gm_portamento_time_lsb&t;control[37]
DECL|macro|gm_data_entry_lsb
mdefine_line|#define gm_data_entry_lsb&t;control[38]
DECL|macro|gm_volume_lsb
mdefine_line|#define gm_volume_lsb&t;&t;control[39]
DECL|macro|gm_balance_lsb
mdefine_line|#define gm_balance_lsb&t;&t;control[40]
DECL|macro|gm_pan_lsb
mdefine_line|#define gm_pan_lsb&t;&t;control[42]
DECL|macro|gm_expression_lsb
mdefine_line|#define gm_expression_lsb&t;control[43]
DECL|macro|gm_effect_control1_lsb
mdefine_line|#define gm_effect_control1_lsb&t;control[44]
DECL|macro|gm_effect_control2_lsb
mdefine_line|#define gm_effect_control2_lsb&t;control[45]
DECL|macro|gm_sustain
mdefine_line|#define gm_sustain&t; &t;control[MIDI_CTL_SUSTAIN]
DECL|macro|gm_hold
mdefine_line|#define gm_hold&t;&t;&t;gm_sustain
DECL|macro|gm_portamento
mdefine_line|#define gm_portamento&t;&t;control[MIDI_CTL_PORTAMENTO]
DECL|macro|gm_sustenuto
mdefine_line|#define gm_sustenuto&t;&t;control[MIDI_CTL_SUSTENUTO]
multiline_comment|/*&n; * These macros give the complete value of the controls that consist&n; * of coarse and fine pairs.  Of course the fine controls are seldom used&n; * but there is no harm in being complete.&n; */
DECL|macro|SNDRV_GM_BANK_SELECT
mdefine_line|#define SNDRV_GM_BANK_SELECT(cp)&t;&t;(((cp)-&gt;control[0]&lt;&lt;7)|((cp)-&gt;control[32]))
DECL|macro|SNDRV_GM_MODULATION_WHEEL
mdefine_line|#define SNDRV_GM_MODULATION_WHEEL(cp)&t;(((cp)-&gt;control[1]&lt;&lt;7)|((cp)-&gt;control[33]))
DECL|macro|SNDRV_GM_BREATH
mdefine_line|#define SNDRV_GM_BREATH(cp)&t;&t;(((cp)-&gt;control[2]&lt;&lt;7)|((cp)-&gt;control[34]))
DECL|macro|SNDRV_GM_FOOT_PEDAL
mdefine_line|#define SNDRV_GM_FOOT_PEDAL(cp)&t;&t;(((cp)-&gt;control[4]&lt;&lt;7)|((cp)-&gt;control[36]))
DECL|macro|SNDRV_GM_PORTAMENTO_TIME
mdefine_line|#define SNDRV_GM_PORTAMENTO_TIME(cp)&t;(((cp)-&gt;control[5]&lt;&lt;7)|((cp)-&gt;control[37]))
DECL|macro|SNDRV_GM_DATA_ENTRY
mdefine_line|#define SNDRV_GM_DATA_ENTRY(cp)&t;&t;(((cp)-&gt;control[6]&lt;&lt;7)|((cp)-&gt;control[38]))
DECL|macro|SNDRV_GM_VOLUME
mdefine_line|#define SNDRV_GM_VOLUME(cp)&t;&t;(((cp)-&gt;control[7]&lt;&lt;7)|((cp)-&gt;control[39]))
DECL|macro|SNDRV_GM_BALANCE
mdefine_line|#define SNDRV_GM_BALANCE(cp)&t;&t;(((cp)-&gt;control[8]&lt;&lt;7)|((cp)-&gt;control[40]))
DECL|macro|SNDRV_GM_PAN
mdefine_line|#define SNDRV_GM_PAN(cp)&t;&t;&t;(((cp)-&gt;control[10]&lt;&lt;7)|((cp)-&gt;control[42]))
DECL|macro|SNDRV_GM_EXPRESSION
mdefine_line|#define SNDRV_GM_EXPRESSION(cp)&t;&t;(((cp)-&gt;control[11]&lt;&lt;7)|((cp)-&gt;control[43]))
multiline_comment|/* MIDI mode */
DECL|macro|SNDRV_MIDI_MODE_NONE
mdefine_line|#define SNDRV_MIDI_MODE_NONE&t;0&t;/* Generic midi */
DECL|macro|SNDRV_MIDI_MODE_GM
mdefine_line|#define SNDRV_MIDI_MODE_GM&t;1
DECL|macro|SNDRV_MIDI_MODE_GS
mdefine_line|#define SNDRV_MIDI_MODE_GS&t;2
DECL|macro|SNDRV_MIDI_MODE_XG
mdefine_line|#define SNDRV_MIDI_MODE_XG&t;3
DECL|macro|SNDRV_MIDI_MODE_MT32
mdefine_line|#define SNDRV_MIDI_MODE_MT32&t;4
multiline_comment|/* MIDI note state */
DECL|macro|SNDRV_MIDI_NOTE_OFF
mdefine_line|#define SNDRV_MIDI_NOTE_OFF&t;&t;0x00
DECL|macro|SNDRV_MIDI_NOTE_ON
mdefine_line|#define SNDRV_MIDI_NOTE_ON&t;&t;0x01
DECL|macro|SNDRV_MIDI_NOTE_RELEASED
mdefine_line|#define SNDRV_MIDI_NOTE_RELEASED&t;&t;0x02
DECL|macro|SNDRV_MIDI_NOTE_SUSTENUTO
mdefine_line|#define SNDRV_MIDI_NOTE_SUSTENUTO&t;&t;0x04
DECL|macro|SNDRV_MIDI_PARAM_TYPE_REGISTERED
mdefine_line|#define SNDRV_MIDI_PARAM_TYPE_REGISTERED&t;&t;0
DECL|macro|SNDRV_MIDI_PARAM_TYPE_NONREGISTERED
mdefine_line|#define SNDRV_MIDI_PARAM_TYPE_NONREGISTERED&t;1
multiline_comment|/* SYSEX parse flag */
r_enum
(brace
DECL|enumerator|SNDRV_MIDI_SYSEX_NOT_PARSED
id|SNDRV_MIDI_SYSEX_NOT_PARSED
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GM_ON
id|SNDRV_MIDI_SYSEX_GM_ON
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_ON
id|SNDRV_MIDI_SYSEX_GS_ON
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_RESET
id|SNDRV_MIDI_SYSEX_GS_RESET
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_CHORUS_MODE
id|SNDRV_MIDI_SYSEX_GS_CHORUS_MODE
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_REVERB_MODE
id|SNDRV_MIDI_SYSEX_GS_REVERB_MODE
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME
id|SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_PROGRAM
id|SNDRV_MIDI_SYSEX_GS_PROGRAM
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_GS_DRUM_CHANNEL
id|SNDRV_MIDI_SYSEX_GS_DRUM_CHANNEL
comma
DECL|enumerator|SNDRV_MIDI_SYSEX_XG_ON
id|SNDRV_MIDI_SYSEX_XG_ON
comma
)brace
suffix:semicolon
multiline_comment|/* Prototypes for midi_process.c */
r_void
id|snd_midi_process_event
c_func
(paren
id|snd_midi_op_t
op_star
id|ops
comma
id|snd_seq_event_t
op_star
id|ev
comma
id|snd_midi_channel_set_t
op_star
id|chanset
)paren
suffix:semicolon
r_void
id|snd_midi_channel_set_clear
c_func
(paren
id|snd_midi_channel_set_t
op_star
id|chset
)paren
suffix:semicolon
r_void
id|snd_midi_channel_init
c_func
(paren
id|snd_midi_channel_t
op_star
id|p
comma
r_int
id|n
)paren
suffix:semicolon
id|snd_midi_channel_t
op_star
id|snd_midi_channel_init_set
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
id|snd_midi_channel_set_t
op_star
id|snd_midi_channel_alloc_set
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
r_void
id|snd_midi_channel_free_set
c_func
(paren
id|snd_midi_channel_set_t
op_star
id|chset
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_SEQ_MIDI_EMUL_H */
eof
