multiline_comment|/*&n; *  NRPN / SYSEX callbacks for Emu8k/Emu10k1&n; *&n; *  Copyright (c) 1999-2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;emux_voice.h&quot;
macro_line|#include &lt;sound/asoundef.h&gt;
DECL|macro|NELEM
mdefine_line|#define NELEM(arr) (sizeof(arr)/sizeof((arr)[0]))
multiline_comment|/*&n; * conversion from NRPN/control parameters to Emu8000 raw parameters&n; */
multiline_comment|/* NRPN / CC -&gt; Emu8000 parameter converter */
r_typedef
r_struct
(brace
DECL|member|control
r_int
id|control
suffix:semicolon
DECL|member|effect
r_int
id|effect
suffix:semicolon
DECL|member|convert
r_int
(paren
op_star
id|convert
)paren
(paren
r_int
id|val
)paren
suffix:semicolon
DECL|typedef|nrpn_conv_table
)brace
id|nrpn_conv_table
suffix:semicolon
multiline_comment|/* effect sensitivity */
DECL|macro|FX_CUTOFF
mdefine_line|#define FX_CUTOFF&t;0
DECL|macro|FX_RESONANCE
mdefine_line|#define FX_RESONANCE&t;1
DECL|macro|FX_ATTACK
mdefine_line|#define FX_ATTACK&t;2
DECL|macro|FX_RELEASE
mdefine_line|#define FX_RELEASE&t;3
DECL|macro|FX_VIBRATE
mdefine_line|#define FX_VIBRATE&t;4
DECL|macro|FX_VIBDEPTH
mdefine_line|#define FX_VIBDEPTH&t;5
DECL|macro|FX_VIBDELAY
mdefine_line|#define FX_VIBDELAY&t;6
DECL|macro|FX_NUMS
mdefine_line|#define FX_NUMS&t;&t;7
multiline_comment|/*&n; * convert NRPN/control values&n; */
DECL|function|send_converted_effect
r_static
r_int
id|send_converted_effect
c_func
(paren
id|nrpn_conv_table
op_star
id|table
comma
r_int
id|num_tables
comma
id|snd_emux_port_t
op_star
id|port
comma
id|snd_midi_channel_t
op_star
id|chan
comma
r_int
id|type
comma
r_int
id|val
comma
r_int
id|mode
)paren
(brace
r_int
id|i
comma
id|cval
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|table
(braket
id|i
)braket
dot
id|control
op_eq
id|type
)paren
(brace
id|cval
op_assign
id|table
(braket
id|i
)braket
dot
id|convert
c_func
(paren
id|val
)paren
suffix:semicolon
id|snd_emux_send_effect
c_func
(paren
id|port
comma
id|chan
comma
id|table
(braket
id|i
)braket
dot
id|effect
comma
id|cval
comma
id|mode
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DEF_FX_CUTOFF
mdefine_line|#define DEF_FX_CUTOFF&t;&t;170
DECL|macro|DEF_FX_RESONANCE
mdefine_line|#define DEF_FX_RESONANCE&t;6
DECL|macro|DEF_FX_ATTACK
mdefine_line|#define DEF_FX_ATTACK&t;&t;50
DECL|macro|DEF_FX_RELEASE
mdefine_line|#define DEF_FX_RELEASE&t;&t;50
DECL|macro|DEF_FX_VIBRATE
mdefine_line|#define DEF_FX_VIBRATE&t;&t;30
DECL|macro|DEF_FX_VIBDEPTH
mdefine_line|#define DEF_FX_VIBDEPTH&t;&t;4
DECL|macro|DEF_FX_VIBDELAY
mdefine_line|#define DEF_FX_VIBDELAY&t;&t;1500
multiline_comment|/* effect sensitivities for GS NRPN:&n; *  adjusted for chaos 8MB soundfonts&n; */
DECL|variable|gs_sense
r_static
r_int
id|gs_sense
(braket
)braket
op_assign
(brace
id|DEF_FX_CUTOFF
comma
id|DEF_FX_RESONANCE
comma
id|DEF_FX_ATTACK
comma
id|DEF_FX_RELEASE
comma
id|DEF_FX_VIBRATE
comma
id|DEF_FX_VIBDEPTH
comma
id|DEF_FX_VIBDELAY
)brace
suffix:semicolon
multiline_comment|/* effect sensitivies for XG controls:&n; * adjusted for chaos 8MB soundfonts&n; */
DECL|variable|xg_sense
r_static
r_int
id|xg_sense
(braket
)braket
op_assign
(brace
id|DEF_FX_CUTOFF
comma
id|DEF_FX_RESONANCE
comma
id|DEF_FX_ATTACK
comma
id|DEF_FX_RELEASE
comma
id|DEF_FX_VIBRATE
comma
id|DEF_FX_VIBDEPTH
comma
id|DEF_FX_VIBDELAY
)brace
suffix:semicolon
multiline_comment|/*&n; * AWE32 NRPN effects&n; */
r_static
r_int
id|fx_delay
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_attack
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_hold
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_decay
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_the_value
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_twice_value
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_conv_pitch
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_static
r_int
id|fx_conv_Q
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
multiline_comment|/* function for each NRPN */
multiline_comment|/* [range]  units */
DECL|macro|fx_env1_delay
mdefine_line|#define fx_env1_delay&t;fx_delay&t;/* [0,5900] 4msec */
DECL|macro|fx_env1_attack
mdefine_line|#define fx_env1_attack&t;fx_attack&t;/* [0,5940] 1msec */
DECL|macro|fx_env1_hold
mdefine_line|#define fx_env1_hold&t;fx_hold&t;&t;/* [0,8191] 1msec */
DECL|macro|fx_env1_decay
mdefine_line|#define fx_env1_decay&t;fx_decay&t;/* [0,5940] 4msec */
DECL|macro|fx_env1_release
mdefine_line|#define fx_env1_release&t;fx_decay&t;/* [0,5940] 4msec */
DECL|macro|fx_env1_sustain
mdefine_line|#define fx_env1_sustain&t;fx_the_value&t;/* [0,127] 0.75dB */
DECL|macro|fx_env1_pitch
mdefine_line|#define fx_env1_pitch&t;fx_the_value&t;/* [-127,127] 9.375cents */
DECL|macro|fx_env1_cutoff
mdefine_line|#define fx_env1_cutoff&t;fx_the_value&t;/* [-127,127] 56.25cents */
DECL|macro|fx_env2_delay
mdefine_line|#define fx_env2_delay&t;fx_delay&t;/* [0,5900] 4msec */
DECL|macro|fx_env2_attack
mdefine_line|#define fx_env2_attack&t;fx_attack&t;/* [0,5940] 1msec */
DECL|macro|fx_env2_hold
mdefine_line|#define fx_env2_hold&t;fx_hold&t;&t;/* [0,8191] 1msec */
DECL|macro|fx_env2_decay
mdefine_line|#define fx_env2_decay&t;fx_decay&t;/* [0,5940] 4msec */
DECL|macro|fx_env2_release
mdefine_line|#define fx_env2_release&t;fx_decay&t;/* [0,5940] 4msec */
DECL|macro|fx_env2_sustain
mdefine_line|#define fx_env2_sustain&t;fx_the_value&t;/* [0,127] 0.75dB */
DECL|macro|fx_lfo1_delay
mdefine_line|#define fx_lfo1_delay&t;fx_delay&t;/* [0,5900] 4msec */
DECL|macro|fx_lfo1_freq
mdefine_line|#define fx_lfo1_freq&t;fx_twice_value&t;/* [0,127] 84mHz */
DECL|macro|fx_lfo1_volume
mdefine_line|#define fx_lfo1_volume&t;fx_twice_value&t;/* [0,127] 0.1875dB */
DECL|macro|fx_lfo1_pitch
mdefine_line|#define fx_lfo1_pitch&t;fx_the_value&t;/* [-127,127] 9.375cents */
DECL|macro|fx_lfo1_cutoff
mdefine_line|#define fx_lfo1_cutoff&t;fx_twice_value&t;/* [-64,63] 56.25cents */
DECL|macro|fx_lfo2_delay
mdefine_line|#define fx_lfo2_delay&t;fx_delay&t;/* [0,5900] 4msec */
DECL|macro|fx_lfo2_freq
mdefine_line|#define fx_lfo2_freq&t;fx_twice_value&t;/* [0,127] 84mHz */
DECL|macro|fx_lfo2_pitch
mdefine_line|#define fx_lfo2_pitch&t;fx_the_value&t;/* [-127,127] 9.375cents */
DECL|macro|fx_init_pitch
mdefine_line|#define fx_init_pitch&t;fx_conv_pitch&t;/* [-8192,8192] cents */
DECL|macro|fx_chorus
mdefine_line|#define fx_chorus&t;fx_the_value&t;/* [0,255] -- */
DECL|macro|fx_reverb
mdefine_line|#define fx_reverb&t;fx_the_value&t;/* [0,255] -- */
DECL|macro|fx_cutoff
mdefine_line|#define fx_cutoff&t;fx_twice_value&t;/* [0,127] 62Hz */
DECL|macro|fx_filterQ
mdefine_line|#define fx_filterQ&t;fx_conv_Q&t;/* [0,127] -- */
DECL|function|fx_delay
r_static
r_int
id|fx_delay
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|snd_sf_calc_parm_delay
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|fx_attack
r_static
r_int
id|fx_attack
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|snd_sf_calc_parm_attack
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|fx_hold
r_static
r_int
id|fx_hold
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|snd_sf_calc_parm_hold
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|fx_decay
r_static
r_int
id|fx_decay
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|snd_sf_calc_parm_decay
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|fx_the_value
r_static
r_int
id|fx_the_value
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
id|val
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|fx_twice_value
r_static
r_int
id|fx_twice_value
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
(paren
id|val
op_star
l_int|2
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|fx_conv_pitch
r_static
r_int
id|fx_conv_pitch
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
)paren
(paren
id|val
op_star
l_int|4096
op_div
l_int|1200
)paren
suffix:semicolon
)brace
DECL|function|fx_conv_Q
r_static
r_int
id|fx_conv_Q
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
r_int
r_int
)paren
(paren
(paren
id|val
op_div
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|variable|awe_effects
r_static
id|nrpn_conv_table
id|awe_effects
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
id|EMUX_FX_LFO1_DELAY
comma
id|fx_lfo1_delay
)brace
comma
(brace
l_int|1
comma
id|EMUX_FX_LFO1_FREQ
comma
id|fx_lfo1_freq
)brace
comma
(brace
l_int|2
comma
id|EMUX_FX_LFO2_DELAY
comma
id|fx_lfo2_delay
)brace
comma
(brace
l_int|3
comma
id|EMUX_FX_LFO2_FREQ
comma
id|fx_lfo2_freq
)brace
comma
(brace
l_int|4
comma
id|EMUX_FX_ENV1_DELAY
comma
id|fx_env1_delay
)brace
comma
(brace
l_int|5
comma
id|EMUX_FX_ENV1_ATTACK
comma
id|fx_env1_attack
)brace
comma
(brace
l_int|6
comma
id|EMUX_FX_ENV1_HOLD
comma
id|fx_env1_hold
)brace
comma
(brace
l_int|7
comma
id|EMUX_FX_ENV1_DECAY
comma
id|fx_env1_decay
)brace
comma
(brace
l_int|8
comma
id|EMUX_FX_ENV1_SUSTAIN
comma
id|fx_env1_sustain
)brace
comma
(brace
l_int|9
comma
id|EMUX_FX_ENV1_RELEASE
comma
id|fx_env1_release
)brace
comma
(brace
l_int|10
comma
id|EMUX_FX_ENV2_DELAY
comma
id|fx_env2_delay
)brace
comma
(brace
l_int|11
comma
id|EMUX_FX_ENV2_ATTACK
comma
id|fx_env2_attack
)brace
comma
(brace
l_int|12
comma
id|EMUX_FX_ENV2_HOLD
comma
id|fx_env2_hold
)brace
comma
(brace
l_int|13
comma
id|EMUX_FX_ENV2_DECAY
comma
id|fx_env2_decay
)brace
comma
(brace
l_int|14
comma
id|EMUX_FX_ENV2_SUSTAIN
comma
id|fx_env2_sustain
)brace
comma
(brace
l_int|15
comma
id|EMUX_FX_ENV2_RELEASE
comma
id|fx_env2_release
)brace
comma
(brace
l_int|16
comma
id|EMUX_FX_INIT_PITCH
comma
id|fx_init_pitch
)brace
comma
(brace
l_int|17
comma
id|EMUX_FX_LFO1_PITCH
comma
id|fx_lfo1_pitch
)brace
comma
(brace
l_int|18
comma
id|EMUX_FX_LFO2_PITCH
comma
id|fx_lfo2_pitch
)brace
comma
(brace
l_int|19
comma
id|EMUX_FX_ENV1_PITCH
comma
id|fx_env1_pitch
)brace
comma
(brace
l_int|20
comma
id|EMUX_FX_LFO1_VOLUME
comma
id|fx_lfo1_volume
)brace
comma
(brace
l_int|21
comma
id|EMUX_FX_CUTOFF
comma
id|fx_cutoff
)brace
comma
(brace
l_int|22
comma
id|EMUX_FX_FILTERQ
comma
id|fx_filterQ
)brace
comma
(brace
l_int|23
comma
id|EMUX_FX_LFO1_CUTOFF
comma
id|fx_lfo1_cutoff
)brace
comma
(brace
l_int|24
comma
id|EMUX_FX_ENV1_CUTOFF
comma
id|fx_env1_cutoff
)brace
comma
(brace
l_int|25
comma
id|EMUX_FX_CHORUS
comma
id|fx_chorus
)brace
comma
(brace
l_int|26
comma
id|EMUX_FX_REVERB
comma
id|fx_reverb
)brace
comma
)brace
suffix:semicolon
DECL|variable|num_awe_effects
r_static
r_int
id|num_awe_effects
op_assign
id|NELEM
c_func
(paren
id|awe_effects
)paren
suffix:semicolon
multiline_comment|/*&n; * GS(SC88) NRPN effects; still experimental&n; */
multiline_comment|/* cutoff: quarter semitone step, max=255 */
DECL|function|gs_cutoff
r_static
r_int
id|gs_cutoff
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_CUTOFF
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* resonance: 0 to 15(max) */
DECL|function|gs_filterQ
r_static
r_int
id|gs_filterQ
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_RESONANCE
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* attack: */
DECL|function|gs_attack
r_static
r_int
id|gs_attack
c_func
(paren
r_int
id|val
)paren
(brace
r_return
op_minus
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_ATTACK
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* decay: */
DECL|function|gs_decay
r_static
r_int
id|gs_decay
c_func
(paren
r_int
id|val
)paren
(brace
r_return
op_minus
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_RELEASE
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* release: */
DECL|function|gs_release
r_static
r_int
id|gs_release
c_func
(paren
r_int
id|val
)paren
(brace
r_return
op_minus
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_RELEASE
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* vibrato freq: 0.042Hz step, max=255 */
DECL|function|gs_vib_rate
r_static
r_int
id|gs_vib_rate
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_VIBRATE
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* vibrato depth: max=127, 1 octave */
DECL|function|gs_vib_depth
r_static
r_int
id|gs_vib_depth
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_VIBDEPTH
)braket
op_div
l_int|50
suffix:semicolon
)brace
multiline_comment|/* vibrato delay: -0.725msec step */
DECL|function|gs_vib_delay
r_static
r_int
id|gs_vib_delay
c_func
(paren
r_int
id|val
)paren
(brace
r_return
op_minus
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|gs_sense
(braket
id|FX_VIBDELAY
)braket
op_div
l_int|50
suffix:semicolon
)brace
DECL|variable|gs_effects
r_static
id|nrpn_conv_table
id|gs_effects
(braket
)braket
op_assign
(brace
(brace
l_int|32
comma
id|EMUX_FX_CUTOFF
comma
id|gs_cutoff
)brace
comma
(brace
l_int|33
comma
id|EMUX_FX_FILTERQ
comma
id|gs_filterQ
)brace
comma
(brace
l_int|99
comma
id|EMUX_FX_ENV2_ATTACK
comma
id|gs_attack
)brace
comma
(brace
l_int|100
comma
id|EMUX_FX_ENV2_DECAY
comma
id|gs_decay
)brace
comma
(brace
l_int|102
comma
id|EMUX_FX_ENV2_RELEASE
comma
id|gs_release
)brace
comma
(brace
l_int|8
comma
id|EMUX_FX_LFO1_FREQ
comma
id|gs_vib_rate
)brace
comma
(brace
l_int|9
comma
id|EMUX_FX_LFO1_VOLUME
comma
id|gs_vib_depth
)brace
comma
(brace
l_int|10
comma
id|EMUX_FX_LFO1_DELAY
comma
id|gs_vib_delay
)brace
comma
)brace
suffix:semicolon
DECL|variable|num_gs_effects
r_static
r_int
id|num_gs_effects
op_assign
id|NELEM
c_func
(paren
id|gs_effects
)paren
suffix:semicolon
multiline_comment|/*&n; * NRPN events&n; */
r_void
DECL|function|snd_emux_nrpn
id|snd_emux_nrpn
c_func
(paren
r_void
op_star
id|p
comma
id|snd_midi_channel_t
op_star
id|chan
comma
id|snd_midi_channel_set_t
op_star
id|chset
)paren
(brace
id|snd_emux_port_t
op_star
id|port
suffix:semicolon
id|port
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|p
comma
r_return
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|port
op_ne
l_int|NULL
comma
r_return
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|chan
op_ne
l_int|NULL
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;control
(braket
id|MIDI_CTL_NONREG_PARM_NUM_MSB
)braket
op_eq
l_int|127
op_logical_and
id|chan-&gt;control
(braket
id|MIDI_CTL_NONREG_PARM_NUM_LSB
)braket
op_le
l_int|26
)paren
(brace
r_int
id|val
suffix:semicolon
multiline_comment|/* Win/DOS AWE32 specific NRPNs */
multiline_comment|/* both MSB/LSB necessary */
id|val
op_assign
(paren
id|chan-&gt;control
(braket
id|MIDI_CTL_MSB_DATA_ENTRY
)braket
op_lshift
l_int|7
)paren
op_or
id|chan-&gt;control
(braket
id|MIDI_CTL_LSB_DATA_ENTRY
)braket
suffix:semicolon
id|val
op_sub_assign
l_int|8192
suffix:semicolon
id|send_converted_effect
(paren
id|awe_effects
comma
id|num_awe_effects
comma
id|port
comma
id|chan
comma
id|chan-&gt;control
(braket
id|MIDI_CTL_NONREG_PARM_NUM_LSB
)braket
comma
id|val
comma
id|EMUX_FX_FLAG_SET
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;chset.midi_mode
op_eq
id|SNDRV_MIDI_MODE_GS
op_logical_and
id|chan-&gt;control
(braket
id|MIDI_CTL_NONREG_PARM_NUM_MSB
)braket
op_eq
l_int|1
)paren
(brace
r_int
id|val
suffix:semicolon
multiline_comment|/* GS specific NRPNs */
multiline_comment|/* only MSB is valid */
id|val
op_assign
id|chan-&gt;control
(braket
id|MIDI_CTL_MSB_DATA_ENTRY
)braket
suffix:semicolon
id|send_converted_effect
(paren
id|gs_effects
comma
id|num_gs_effects
comma
id|port
comma
id|chan
comma
id|chan-&gt;control
(braket
id|MIDI_CTL_NONREG_PARM_NUM_LSB
)braket
comma
id|val
comma
id|EMUX_FX_FLAG_ADD
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * XG control effects; still experimental&n; */
multiline_comment|/* cutoff: quarter semitone step, max=255 */
DECL|function|xg_cutoff
r_static
r_int
id|xg_cutoff
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|xg_sense
(braket
id|FX_CUTOFF
)braket
op_div
l_int|64
suffix:semicolon
)brace
multiline_comment|/* resonance: 0(open) to 15(most nasal) */
DECL|function|xg_filterQ
r_static
r_int
id|xg_filterQ
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|xg_sense
(braket
id|FX_RESONANCE
)braket
op_div
l_int|64
suffix:semicolon
)brace
multiline_comment|/* attack: */
DECL|function|xg_attack
r_static
r_int
id|xg_attack
c_func
(paren
r_int
id|val
)paren
(brace
r_return
op_minus
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|xg_sense
(braket
id|FX_ATTACK
)braket
op_div
l_int|64
suffix:semicolon
)brace
multiline_comment|/* release: */
DECL|function|xg_release
r_static
r_int
id|xg_release
c_func
(paren
r_int
id|val
)paren
(brace
r_return
op_minus
(paren
id|val
op_minus
l_int|64
)paren
op_star
id|xg_sense
(braket
id|FX_RELEASE
)braket
op_div
l_int|64
suffix:semicolon
)brace
DECL|variable|xg_effects
r_static
id|nrpn_conv_table
id|xg_effects
(braket
)braket
op_assign
(brace
(brace
l_int|71
comma
id|EMUX_FX_CUTOFF
comma
id|xg_cutoff
)brace
comma
(brace
l_int|74
comma
id|EMUX_FX_FILTERQ
comma
id|xg_filterQ
)brace
comma
(brace
l_int|72
comma
id|EMUX_FX_ENV2_RELEASE
comma
id|xg_release
)brace
comma
(brace
l_int|73
comma
id|EMUX_FX_ENV2_ATTACK
comma
id|xg_attack
)brace
comma
)brace
suffix:semicolon
DECL|variable|num_xg_effects
r_static
r_int
id|num_xg_effects
op_assign
id|NELEM
c_func
(paren
id|xg_effects
)paren
suffix:semicolon
r_int
DECL|function|snd_emux_xg_control
id|snd_emux_xg_control
c_func
(paren
id|snd_emux_port_t
op_star
id|port
comma
id|snd_midi_channel_t
op_star
id|chan
comma
r_int
id|param
)paren
(brace
r_return
id|send_converted_effect
c_func
(paren
id|xg_effects
comma
id|num_xg_effects
comma
id|port
comma
id|chan
comma
id|param
comma
id|chan-&gt;control
(braket
id|param
)braket
comma
id|EMUX_FX_FLAG_ADD
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * receive sysex&n; */
r_void
DECL|function|snd_emux_sysex
id|snd_emux_sysex
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
(brace
id|snd_emux_port_t
op_star
id|port
suffix:semicolon
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|port
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|p
comma
r_return
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|port
op_ne
l_int|NULL
comma
r_return
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|chset
op_ne
l_int|NULL
comma
r_return
)paren
suffix:semicolon
id|emu
op_assign
id|port-&gt;emu
suffix:semicolon
r_switch
c_cond
(paren
id|parsed
)paren
(brace
r_case
id|SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME
suffix:colon
id|snd_emux_update_port
c_func
(paren
id|port
comma
id|SNDRV_EMUX_UPDATE_VOLUME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|emu-&gt;ops.sysex
)paren
id|emu-&gt;ops
dot
id|sysex
c_func
(paren
id|emu
comma
id|buf
comma
id|len
comma
id|parsed
comma
id|chset
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
eof