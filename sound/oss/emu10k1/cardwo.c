multiline_comment|/*&n; **********************************************************************&n; *     cardwo.c - PCM output HAL for emu10k1 driver&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;8010.h&quot;
macro_line|#include &quot;voicemgr.h&quot;
macro_line|#include &quot;cardwo.h&quot;
macro_line|#include &quot;audio.h&quot;
DECL|function|samplerate_to_linearpitch
r_static
id|u32
id|samplerate_to_linearpitch
c_func
(paren
id|u32
id|samplingrate
)paren
(brace
id|samplingrate
op_assign
(paren
id|samplingrate
op_lshift
l_int|8
)paren
op_div
l_int|375
suffix:semicolon
r_return
(paren
id|samplingrate
op_rshift
l_int|1
)paren
op_plus
(paren
id|samplingrate
op_amp
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|query_format
r_static
r_void
id|query_format
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
comma
r_struct
id|wave_format
op_star
id|wave_fmt
)paren
(brace
r_int
id|i
comma
id|j
comma
id|do_passthrough
op_assign
l_int|0
comma
id|is_ac3
op_assign
l_int|0
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wave_fmt-&gt;channels
OG
l_int|2
)paren
op_logical_and
(paren
id|wave_fmt-&gt;id
op_ne
id|AFMT_S16_LE
)paren
op_logical_and
(paren
id|wave_fmt-&gt;id
op_ne
id|AFMT_U8
)paren
)paren
id|wave_fmt-&gt;channels
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wave_fmt-&gt;channels
OL
l_int|1
)paren
op_logical_or
(paren
id|wave_fmt-&gt;channels
OG
id|WAVEOUT_MAXVOICES
)paren
)paren
id|wave_fmt-&gt;channels
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|wave_fmt-&gt;channels
op_eq
l_int|2
)paren
id|woinst-&gt;num_voices
op_assign
l_int|1
suffix:semicolon
r_else
id|woinst-&gt;num_voices
op_assign
id|wave_fmt-&gt;channels
suffix:semicolon
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
l_int|0x2ee00
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x2ee00
suffix:semicolon
id|wave_fmt-&gt;passthrough
op_assign
l_int|0
suffix:semicolon
id|do_passthrough
op_assign
id|is_ac3
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;pt.selected
)paren
id|do_passthrough
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|wave_fmt-&gt;id
)paren
(brace
r_case
id|AFMT_S16_LE
suffix:colon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFMT_U8
suffix:colon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFMT_AC3
suffix:colon
id|do_passthrough
op_assign
l_int|1
suffix:semicolon
id|is_ac3
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|wave_fmt-&gt;id
op_assign
id|AFMT_S16_LE
suffix:semicolon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_passthrough
)paren
(brace
multiline_comment|/* currently only one waveout instance may use pass-through */
r_if
c_cond
(paren
id|woinst-&gt;state
op_ne
id|WAVE_STATE_CLOSED
op_logical_or
id|card-&gt;pt.state
op_ne
id|PT_STATE_INACTIVE
op_logical_or
(paren
id|wave_fmt-&gt;samplingrate
op_ne
l_int|48000
op_logical_and
op_logical_neg
id|is_ac3
)paren
)paren
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;unable to set pass-through mode&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|USE_PT_METHOD1
)paren
(brace
id|i
op_assign
id|emu10k1_find_control_gpr
c_func
(paren
op_amp
id|card-&gt;mgr
comma
id|card-&gt;pt.patch_name
comma
id|card-&gt;pt.intr_gpr_name
)paren
suffix:semicolon
id|j
op_assign
id|emu10k1_find_control_gpr
c_func
(paren
op_amp
id|card-&gt;mgr
comma
id|card-&gt;pt.patch_name
comma
id|card-&gt;pt.enable_gpr_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_or
id|j
OL
l_int|0
)paren
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;unable to set pass-through mode&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|wave_fmt-&gt;samplingrate
op_assign
l_int|48000
suffix:semicolon
id|wave_fmt-&gt;channels
op_assign
l_int|2
suffix:semicolon
id|card-&gt;pt.pos_gpr
op_assign
id|emu10k1_find_control_gpr
c_func
(paren
op_amp
id|card-&gt;mgr
comma
id|card-&gt;pt.patch_name
comma
id|card-&gt;pt.pos_gpr_name
)paren
suffix:semicolon
id|wave_fmt-&gt;passthrough
op_assign
l_int|1
suffix:semicolon
id|card-&gt;pt.intr_gpr
op_assign
id|i
suffix:semicolon
id|card-&gt;pt.enable_gpr
op_assign
id|j
suffix:semicolon
id|card-&gt;pt.state
op_assign
id|PT_STATE_INACTIVE
suffix:semicolon
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;is_ac3 is %d&bslash;n&quot;
comma
id|is_ac3
)paren
suffix:semicolon
id|card-&gt;pt.ac3data
op_assign
id|is_ac3
suffix:semicolon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|16
suffix:semicolon
)brace
)brace
r_else
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;Using Passthrough Method 2&bslash;n&quot;
)paren
suffix:semicolon
id|card-&gt;pt.enable_gpr
op_assign
id|emu10k1_find_control_gpr
c_func
(paren
op_amp
id|card-&gt;mgr
comma
id|card-&gt;pt.patch_name
comma
id|card-&gt;pt.enable_gpr_name
)paren
suffix:semicolon
id|wave_fmt-&gt;passthrough
op_assign
l_int|2
suffix:semicolon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|16
suffix:semicolon
)brace
)brace
id|wave_fmt-&gt;bytesperchannel
op_assign
id|wave_fmt-&gt;bitsperchannel
op_rshift
l_int|3
suffix:semicolon
id|wave_fmt-&gt;bytespersample
op_assign
id|wave_fmt-&gt;channels
op_star
id|wave_fmt-&gt;bytesperchannel
suffix:semicolon
id|wave_fmt-&gt;bytespersec
op_assign
id|wave_fmt-&gt;bytespersample
op_star
id|wave_fmt-&gt;samplingrate
suffix:semicolon
r_if
c_cond
(paren
id|wave_fmt-&gt;channels
op_eq
l_int|2
)paren
id|wave_fmt-&gt;bytespervoicesample
op_assign
id|wave_fmt-&gt;channels
op_star
id|wave_fmt-&gt;bytesperchannel
suffix:semicolon
r_else
id|wave_fmt-&gt;bytespervoicesample
op_assign
id|wave_fmt-&gt;bytesperchannel
suffix:semicolon
)brace
DECL|function|get_voice
r_static
r_int
id|get_voice
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|woinst
op_star
id|woinst
comma
r_int
r_int
id|voicenum
)paren
(brace
r_struct
id|emu_voice
op_star
id|voice
op_assign
op_amp
id|woinst-&gt;voice
(braket
id|voicenum
)braket
suffix:semicolon
multiline_comment|/* Allocate voices here, if no voices available, return error. */
id|voice-&gt;usage
op_assign
id|VOICE_USAGE_PLAYBACK
suffix:semicolon
id|voice-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;format.channels
op_eq
l_int|2
)paren
id|voice-&gt;flags
op_or_assign
id|VOICE_FLAGS_STEREO
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;format.bitsperchannel
op_eq
l_int|16
)paren
id|voice-&gt;flags
op_or_assign
id|VOICE_FLAGS_16BIT
suffix:semicolon
r_if
c_cond
(paren
id|emu10k1_voice_alloc
c_func
(paren
id|card
comma
id|voice
)paren
OL
l_int|0
)paren
(brace
id|voice-&gt;usage
op_assign
id|VOICE_USAGE_FREE
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Calculate pitch */
id|voice-&gt;initial_pitch
op_assign
(paren
id|u16
)paren
(paren
id|srToPitch
c_func
(paren
id|woinst-&gt;format.samplingrate
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|voice-&gt;pitch_target
op_assign
id|samplerate_to_linearpitch
c_func
(paren
id|woinst-&gt;format.samplingrate
)paren
suffix:semicolon
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;Initial pitch --&gt; %#x&bslash;n&quot;
comma
id|voice-&gt;initial_pitch
)paren
suffix:semicolon
id|voice-&gt;startloop
op_assign
(paren
id|voice-&gt;mem.emupageindex
op_lshift
l_int|12
)paren
op_div
id|woinst-&gt;format.bytespervoicesample
suffix:semicolon
id|voice-&gt;endloop
op_assign
id|voice-&gt;startloop
op_plus
id|woinst-&gt;buffer.size
op_div
id|woinst-&gt;format.bytespervoicesample
suffix:semicolon
id|voice-&gt;start
op_assign
id|voice-&gt;startloop
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|volume_target
op_assign
l_int|0xffff
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|initial_fc
op_assign
l_int|0xff
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|initial_attn
op_assign
l_int|0x00
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|byampl_env_sustain
op_assign
l_int|0x7f
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|byampl_env_decay
op_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|voice-&gt;flags
op_amp
id|VOICE_FLAGS_STEREO
)paren
(brace
r_if
c_cond
(paren
id|woinst-&gt;format.passthrough
op_eq
l_int|2
)paren
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_routing
op_assign
id|card-&gt;waveout.send_routing
(braket
id|ROUTE_PT
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing2
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_routing2
op_assign
id|card-&gt;waveout.send_routing2
(braket
id|ROUTE_PT
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_dcba
op_assign
l_int|0xff
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_dcba
op_assign
l_int|0xff00
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_hgfe
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_hgfe
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_dcba
op_assign
id|card-&gt;waveout.send_dcba
(braket
id|SEND_LEFT
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_hgfe
op_assign
id|card-&gt;waveout.send_hgfe
(braket
id|SEND_LEFT
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_dcba
op_assign
id|card-&gt;waveout.send_dcba
(braket
id|SEND_RIGHT
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_hgfe
op_assign
id|card-&gt;waveout.send_hgfe
(braket
id|SEND_RIGHT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;device
)paren
(brace
singleline_comment|// /dev/dps1
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_routing
op_assign
id|card-&gt;waveout.send_routing
(braket
id|ROUTE_PCM1
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing2
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_routing2
op_assign
id|card-&gt;waveout.send_routing2
(braket
id|ROUTE_PCM1
)braket
suffix:semicolon
)brace
r_else
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_routing
op_assign
id|card-&gt;waveout.send_routing
(braket
id|ROUTE_PCM
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing2
op_assign
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|send_routing2
op_assign
id|card-&gt;waveout.send_routing2
(braket
id|ROUTE_PCM
)braket
suffix:semicolon
)brace
)brace
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|volume_target
op_assign
l_int|0xffff
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|initial_fc
op_assign
l_int|0xff
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|initial_attn
op_assign
l_int|0x00
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|byampl_env_sustain
op_assign
l_int|0x7f
suffix:semicolon
id|voice-&gt;params
(braket
l_int|1
)braket
dot
id|byampl_env_decay
op_assign
l_int|0x7f
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|woinst-&gt;num_voices
OG
l_int|1
)paren
(brace
singleline_comment|// Multichannel pcm
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_dcba
op_assign
l_int|0xff
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_hgfe
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;is_audigy
)paren
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
l_int|0x3f3f3f00
op_plus
id|card-&gt;mchannel_fx
op_plus
id|voicenum
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing2
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
)brace
r_else
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
l_int|0xfff0
op_plus
id|card-&gt;mchannel_fx
op_plus
id|voicenum
suffix:semicolon
)brace
)brace
r_else
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_dcba
op_assign
id|card-&gt;waveout.send_dcba
(braket
id|SEND_MONO
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_hgfe
op_assign
id|card-&gt;waveout.send_hgfe
(braket
id|SEND_MONO
)braket
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;device
)paren
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
id|card-&gt;waveout.send_routing
(braket
id|ROUTE_PCM1
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing2
op_assign
id|card-&gt;waveout.send_routing2
(braket
id|ROUTE_PCM1
)braket
suffix:semicolon
)brace
r_else
(brace
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing
op_assign
id|card-&gt;waveout.send_routing
(braket
id|ROUTE_PCM
)braket
suffix:semicolon
id|voice-&gt;params
(braket
l_int|0
)braket
dot
id|send_routing2
op_assign
id|card-&gt;waveout.send_routing2
(braket
id|ROUTE_PCM
)braket
suffix:semicolon
)brace
)brace
)brace
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;voice: startloop=%#x, endloop=%#x&bslash;n&quot;
comma
id|voice-&gt;startloop
comma
id|voice-&gt;endloop
)paren
suffix:semicolon
id|emu10k1_voice_playback_setup
c_func
(paren
id|voice
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_waveout_open
r_int
id|emu10k1_waveout_open
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_struct
id|waveout_buffer
op_star
id|buffer
op_assign
op_amp
id|woinst-&gt;buffer
suffix:semicolon
r_int
r_int
id|voicenum
suffix:semicolon
id|u16
id|delay
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_waveout_open()&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voicenum
op_assign
l_int|0
suffix:semicolon
id|voicenum
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voicenum
op_increment
)paren
(brace
r_if
c_cond
(paren
id|emu10k1_voice_alloc_buffer
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;voice
(braket
id|voicenum
)braket
dot
id|mem
comma
id|woinst-&gt;buffer.pages
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|emu10k1_waveout_close
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_voice
c_func
(paren
id|card
comma
id|woinst
comma
id|voicenum
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|emu10k1_waveout_close
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|buffer-&gt;fill_silence
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;silence_bytes
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;silence_pos
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;hw_pos
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;free_bytes
op_assign
id|woinst-&gt;buffer.size
suffix:semicolon
id|delay
op_assign
(paren
l_int|48000
op_star
id|woinst-&gt;buffer.fragment_size
)paren
op_div
(paren
id|woinst-&gt;format.samplingrate
op_star
id|woinst-&gt;format.bytespervoicesample
)paren
suffix:semicolon
id|emu10k1_timer_install
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;timer
comma
id|delay
)paren
suffix:semicolon
id|woinst-&gt;state
op_assign
id|WAVE_STATE_OPEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_waveout_close
r_void
id|emu10k1_waveout_close
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_int
r_int
id|voicenum
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_waveout_close()&bslash;n&quot;
)paren
suffix:semicolon
id|emu10k1_waveout_stop
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
id|emu10k1_timer_uninstall
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;timer
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voicenum
op_assign
l_int|0
suffix:semicolon
id|voicenum
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voicenum
op_increment
)paren
(brace
id|emu10k1_voice_free
c_func
(paren
op_amp
id|woinst-&gt;voice
(braket
id|voicenum
)braket
)paren
suffix:semicolon
id|emu10k1_voice_free_buffer
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;voice
(braket
id|voicenum
)braket
dot
id|mem
)paren
suffix:semicolon
)brace
id|woinst-&gt;state
op_assign
id|WAVE_STATE_CLOSED
suffix:semicolon
)brace
DECL|function|emu10k1_waveout_start
r_void
id|emu10k1_waveout_start
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|card-&gt;pt
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_waveout_start()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;format.passthrough
op_eq
l_int|2
)paren
(brace
id|emu10k1_pt_setup
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
(paren
id|card-&gt;is_audigy
ques
c_cond
id|A_GPR_BASE
suffix:colon
id|GPR_BASE
)paren
op_plus
id|pt-&gt;enable_gpr
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|pt-&gt;state
op_assign
id|PT_STATE_PLAYING
suffix:semicolon
)brace
multiline_comment|/* Actual start */
id|emu10k1_voices_start
c_func
(paren
id|woinst-&gt;voice
comma
id|woinst-&gt;num_voices
comma
id|woinst-&gt;total_played
)paren
suffix:semicolon
id|emu10k1_timer_enable
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;timer
)paren
suffix:semicolon
id|woinst-&gt;state
op_or_assign
id|WAVE_STATE_STARTED
suffix:semicolon
)brace
DECL|function|emu10k1_waveout_setformat
r_int
id|emu10k1_waveout_setformat
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
comma
r_struct
id|wave_format
op_star
id|format
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_int
r_int
id|voicenum
suffix:semicolon
id|u16
id|delay
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_waveout_setformat()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;state
op_amp
id|WAVE_STATE_STARTED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|query_format
c_func
(paren
id|wave_dev
comma
id|format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;format.samplingrate
op_ne
id|format-&gt;samplingrate
op_logical_or
id|woinst-&gt;format.channels
op_ne
id|format-&gt;channels
op_logical_or
id|woinst-&gt;format.bitsperchannel
op_ne
id|format-&gt;bitsperchannel
)paren
(brace
id|woinst-&gt;format
op_assign
op_star
id|format
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;state
op_eq
id|WAVE_STATE_CLOSED
)paren
r_return
l_int|0
suffix:semicolon
id|emu10k1_timer_uninstall
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;timer
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voicenum
op_assign
l_int|0
suffix:semicolon
id|voicenum
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voicenum
op_increment
)paren
(brace
id|emu10k1_voice_free
c_func
(paren
op_amp
id|woinst-&gt;voice
(braket
id|voicenum
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_voice
c_func
(paren
id|card
comma
id|woinst
comma
id|voicenum
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|emu10k1_waveout_close
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|delay
op_assign
(paren
l_int|48000
op_star
id|woinst-&gt;buffer.fragment_size
)paren
op_div
(paren
id|woinst-&gt;format.samplingrate
op_star
id|woinst-&gt;format.bytespervoicesample
)paren
suffix:semicolon
id|emu10k1_timer_install
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;timer
comma
id|delay
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_waveout_stop
r_void
id|emu10k1_waveout_stop
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_waveout_stop()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|woinst-&gt;state
op_amp
id|WAVE_STATE_STARTED
)paren
)paren
r_return
suffix:semicolon
id|emu10k1_timer_disable
c_func
(paren
id|card
comma
op_amp
id|woinst-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* Stop actual voices */
id|emu10k1_voices_stop
c_func
(paren
id|woinst-&gt;voice
comma
id|woinst-&gt;num_voices
)paren
suffix:semicolon
id|emu10k1_waveout_update
c_func
(paren
id|woinst
)paren
suffix:semicolon
id|woinst-&gt;state
op_and_assign
op_complement
id|WAVE_STATE_STARTED
suffix:semicolon
)brace
multiline_comment|/**&n; * emu10k1_waveout_getxfersize -&n; *&n; * gives the total free bytes on the voice buffer, including silence bytes&n; * (basically: total_free_bytes = free_bytes + silence_bytes).&n; *&n; */
DECL|function|emu10k1_waveout_getxfersize
r_void
id|emu10k1_waveout_getxfersize
c_func
(paren
r_struct
id|woinst
op_star
id|woinst
comma
id|u32
op_star
id|total_free_bytes
)paren
(brace
r_struct
id|waveout_buffer
op_star
id|buffer
op_assign
op_amp
id|woinst-&gt;buffer
suffix:semicolon
r_int
id|pending_bytes
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;mmapped
)paren
(brace
op_star
id|total_free_bytes
op_assign
id|buffer-&gt;free_bytes
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pending_bytes
op_assign
id|buffer-&gt;size
op_minus
id|buffer-&gt;free_bytes
suffix:semicolon
id|buffer-&gt;fill_silence
op_assign
(paren
id|pending_bytes
OL
(paren
r_int
)paren
id|buffer-&gt;fragment_size
op_star
l_int|2
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pending_bytes
OG
(paren
r_int
)paren
id|buffer-&gt;silence_bytes
)paren
(brace
op_star
id|total_free_bytes
op_assign
(paren
id|buffer-&gt;free_bytes
op_plus
id|buffer-&gt;silence_bytes
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|total_free_bytes
op_assign
id|buffer-&gt;size
suffix:semicolon
id|buffer-&gt;silence_bytes
op_assign
id|pending_bytes
suffix:semicolon
r_if
c_cond
(paren
id|pending_bytes
OL
l_int|0
)paren
(brace
id|buffer-&gt;silence_pos
op_assign
id|buffer-&gt;hw_pos
suffix:semicolon
id|buffer-&gt;silence_bytes
op_assign
l_int|0
suffix:semicolon
id|buffer-&gt;free_bytes
op_assign
id|buffer-&gt;size
suffix:semicolon
id|DPF
c_func
(paren
l_int|1
comma
l_string|&quot;buffer underrun&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * copy_block -&n; *&n; * copies a block of pcm data to a voice buffer.&n; * Notice that the voice buffer is actually a set of disjointed memory pages.&n; *&n; */
DECL|function|copy_block
r_static
r_void
id|copy_block
c_func
(paren
r_void
op_star
op_star
id|dst
comma
id|u32
id|str
comma
id|u8
op_star
id|src
comma
id|u32
id|len
)paren
(brace
r_int
r_int
id|pg
suffix:semicolon
r_int
r_int
id|pgoff
suffix:semicolon
r_int
r_int
id|k
suffix:semicolon
id|pg
op_assign
id|str
op_div
id|PAGE_SIZE
suffix:semicolon
id|pgoff
op_assign
id|str
op_mod
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|PAGE_SIZE
op_minus
id|pgoff
)paren
(brace
id|k
op_assign
id|PAGE_SIZE
op_minus
id|pgoff
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
(paren
id|u8
op_star
)paren
id|dst
(braket
id|pg
)braket
op_plus
id|pgoff
comma
id|src
comma
id|k
)paren
)paren
r_return
suffix:semicolon
id|len
op_sub_assign
id|k
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|dst
(braket
op_increment
id|pg
)braket
comma
id|src
op_plus
id|k
comma
id|PAGE_SIZE
)paren
)paren
r_return
suffix:semicolon
id|k
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|len
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|dst
(braket
op_increment
id|pg
)braket
comma
id|src
op_plus
id|k
comma
id|len
)paren
)paren
r_return
suffix:semicolon
)brace
r_else
id|__copy_from_user
c_func
(paren
(paren
id|u8
op_star
)paren
id|dst
(braket
id|pg
)braket
op_plus
id|pgoff
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * copy_ilv_block -&n; *&n; * copies a block of pcm data containing n interleaved channels to n mono voice buffers.&n; * Notice that the voice buffer is actually a set of disjointed memory pages.&n; *&n; */
DECL|function|copy_ilv_block
r_static
r_void
id|copy_ilv_block
c_func
(paren
r_struct
id|woinst
op_star
id|woinst
comma
id|u32
id|str
comma
id|u8
op_star
id|src
comma
id|u32
id|len
)paren
(brace
r_int
r_int
id|pg
suffix:semicolon
r_int
r_int
id|pgoff
suffix:semicolon
r_int
r_int
id|voice_num
suffix:semicolon
r_struct
id|emu_voice
op_star
id|voice
op_assign
id|woinst-&gt;voice
suffix:semicolon
id|pg
op_assign
id|str
op_div
id|PAGE_SIZE
suffix:semicolon
id|pgoff
op_assign
id|str
op_mod
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_for
c_loop
(paren
id|voice_num
op_assign
l_int|0
suffix:semicolon
id|voice_num
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voice_num
op_increment
)paren
(brace
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|voice
(braket
id|voice_num
)braket
dot
id|mem.addr
(braket
id|pg
)braket
)paren
op_plus
id|pgoff
comma
id|src
comma
id|woinst-&gt;format.bytespervoicesample
)paren
)paren
r_return
suffix:semicolon
id|src
op_add_assign
id|woinst-&gt;format.bytespervoicesample
suffix:semicolon
)brace
id|len
op_sub_assign
id|woinst-&gt;format.bytespervoicesample
suffix:semicolon
id|pgoff
op_add_assign
id|woinst-&gt;format.bytespervoicesample
suffix:semicolon
r_if
c_cond
(paren
id|pgoff
op_ge
id|PAGE_SIZE
)paren
(brace
id|pgoff
op_assign
l_int|0
suffix:semicolon
id|pg
op_increment
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * fill_block -&n; *&n; * fills a set voice buffers with a block of a given sample.&n; *&n; */
DECL|function|fill_block
r_static
r_void
id|fill_block
c_func
(paren
r_struct
id|woinst
op_star
id|woinst
comma
id|u32
id|str
comma
id|u8
id|data
comma
id|u32
id|len
)paren
(brace
r_int
r_int
id|pg
suffix:semicolon
r_int
r_int
id|pgoff
suffix:semicolon
r_int
r_int
id|voice_num
suffix:semicolon
r_struct
id|emu_voice
op_star
id|voice
op_assign
id|woinst-&gt;voice
suffix:semicolon
r_int
r_int
id|k
suffix:semicolon
id|pg
op_assign
id|str
op_div
id|PAGE_SIZE
suffix:semicolon
id|pgoff
op_assign
id|str
op_mod
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|PAGE_SIZE
op_minus
id|pgoff
)paren
(brace
id|k
op_assign
id|PAGE_SIZE
op_minus
id|pgoff
suffix:semicolon
r_for
c_loop
(paren
id|voice_num
op_assign
l_int|0
suffix:semicolon
id|voice_num
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voice_num
op_increment
)paren
id|memset
c_func
(paren
(paren
id|u8
op_star
)paren
id|voice
(braket
id|voice_num
)braket
dot
id|mem.addr
(braket
id|pg
)braket
op_plus
id|pgoff
comma
id|data
comma
id|k
)paren
suffix:semicolon
id|len
op_sub_assign
id|k
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
id|PAGE_SIZE
)paren
(brace
id|pg
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|voice_num
op_assign
l_int|0
suffix:semicolon
id|voice_num
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voice_num
op_increment
)paren
id|memset
c_func
(paren
id|voice
(braket
id|voice_num
)braket
dot
id|mem.addr
(braket
id|pg
)braket
comma
id|data
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|len
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|pg
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|voice_num
op_assign
l_int|0
suffix:semicolon
id|voice_num
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voice_num
op_increment
)paren
id|memset
c_func
(paren
id|voice
(braket
id|voice_num
)braket
dot
id|mem.addr
(braket
id|pg
)braket
comma
id|data
comma
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|voice_num
op_assign
l_int|0
suffix:semicolon
id|voice_num
OL
id|woinst-&gt;num_voices
suffix:semicolon
id|voice_num
op_increment
)paren
id|memset
c_func
(paren
(paren
id|u8
op_star
)paren
id|voice
(braket
id|voice_num
)braket
dot
id|mem.addr
(braket
id|pg
)braket
op_plus
id|pgoff
comma
id|data
comma
id|len
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * emu10k1_waveout_xferdata -&n; *&n; * copies pcm data to the voice buffer. Silence samples&n; * previously added to the buffer are overwritten.&n; *&n; */
DECL|function|emu10k1_waveout_xferdata
r_void
id|emu10k1_waveout_xferdata
c_func
(paren
r_struct
id|woinst
op_star
id|woinst
comma
id|u8
op_star
id|data
comma
id|u32
op_star
id|size
)paren
(brace
r_struct
id|waveout_buffer
op_star
id|buffer
op_assign
op_amp
id|woinst-&gt;buffer
suffix:semicolon
r_struct
id|voice_mem
op_star
id|mem
op_assign
op_amp
id|woinst-&gt;voice
(braket
l_int|0
)braket
dot
id|mem
suffix:semicolon
id|u32
id|sizetocopy
comma
id|sizetocopy_now
comma
id|start
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|sizetocopy
op_assign
id|min_t
c_func
(paren
id|u32
comma
id|buffer-&gt;size
comma
op_star
id|size
)paren
suffix:semicolon
op_star
id|size
op_assign
id|sizetocopy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sizetocopy
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|woinst-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|start
op_assign
(paren
id|buffer-&gt;size
op_plus
id|buffer-&gt;silence_pos
op_minus
id|buffer-&gt;silence_bytes
)paren
op_mod
id|buffer-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|sizetocopy
OG
id|buffer-&gt;silence_bytes
)paren
(brace
id|buffer-&gt;silence_pos
op_add_assign
id|sizetocopy
op_minus
id|buffer-&gt;silence_bytes
suffix:semicolon
id|buffer-&gt;free_bytes
op_sub_assign
id|sizetocopy
op_minus
id|buffer-&gt;silence_bytes
suffix:semicolon
id|buffer-&gt;silence_bytes
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|buffer-&gt;silence_bytes
op_sub_assign
id|sizetocopy
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|woinst-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|sizetocopy_now
op_assign
id|buffer-&gt;size
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
id|sizetocopy
OG
id|sizetocopy_now
)paren
(brace
id|sizetocopy
op_sub_assign
id|sizetocopy_now
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;num_voices
OG
l_int|1
)paren
(brace
id|copy_ilv_block
c_func
(paren
id|woinst
comma
id|start
comma
id|data
comma
id|sizetocopy_now
)paren
suffix:semicolon
id|copy_ilv_block
c_func
(paren
id|woinst
comma
l_int|0
comma
id|data
op_plus
id|sizetocopy_now
op_star
id|woinst-&gt;num_voices
comma
id|sizetocopy
)paren
suffix:semicolon
)brace
r_else
(brace
id|copy_block
c_func
(paren
id|mem-&gt;addr
comma
id|start
comma
id|data
comma
id|sizetocopy_now
)paren
suffix:semicolon
id|copy_block
c_func
(paren
id|mem-&gt;addr
comma
l_int|0
comma
id|data
op_plus
id|sizetocopy_now
comma
id|sizetocopy
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|woinst-&gt;num_voices
OG
l_int|1
)paren
id|copy_ilv_block
c_func
(paren
id|woinst
comma
id|start
comma
id|data
comma
id|sizetocopy
)paren
suffix:semicolon
r_else
id|copy_block
c_func
(paren
id|mem-&gt;addr
comma
id|start
comma
id|data
comma
id|sizetocopy
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * emu10k1_waveout_fillsilence -&n; *&n; * adds samples of silence to the voice buffer so that we&n; * don&squot;t loop over stale pcm data.&n; *&n; */
DECL|function|emu10k1_waveout_fillsilence
r_void
id|emu10k1_waveout_fillsilence
c_func
(paren
r_struct
id|woinst
op_star
id|woinst
)paren
(brace
r_struct
id|waveout_buffer
op_star
id|buffer
op_assign
op_amp
id|woinst-&gt;buffer
suffix:semicolon
id|u32
id|sizetocopy
comma
id|sizetocopy_now
comma
id|start
suffix:semicolon
id|u8
id|filldata
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|sizetocopy
op_assign
id|buffer-&gt;fragment_size
suffix:semicolon
r_if
c_cond
(paren
id|woinst-&gt;format.bitsperchannel
op_eq
l_int|16
)paren
id|filldata
op_assign
l_int|0x00
suffix:semicolon
r_else
id|filldata
op_assign
l_int|0x80
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|woinst-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|buffer-&gt;silence_bytes
op_add_assign
id|sizetocopy
suffix:semicolon
id|buffer-&gt;free_bytes
op_sub_assign
id|sizetocopy
suffix:semicolon
id|buffer-&gt;silence_pos
op_mod_assign
id|buffer-&gt;size
suffix:semicolon
id|start
op_assign
id|buffer-&gt;silence_pos
suffix:semicolon
id|buffer-&gt;silence_pos
op_add_assign
id|sizetocopy
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|woinst-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|sizetocopy_now
op_assign
id|buffer-&gt;size
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
id|sizetocopy
OG
id|sizetocopy_now
)paren
(brace
id|sizetocopy
op_sub_assign
id|sizetocopy_now
suffix:semicolon
id|fill_block
c_func
(paren
id|woinst
comma
id|start
comma
id|filldata
comma
id|sizetocopy_now
)paren
suffix:semicolon
id|fill_block
c_func
(paren
id|woinst
comma
l_int|0
comma
id|filldata
comma
id|sizetocopy
)paren
suffix:semicolon
)brace
r_else
(brace
id|fill_block
c_func
(paren
id|woinst
comma
id|start
comma
id|filldata
comma
id|sizetocopy
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * emu10k1_waveout_update -&n; *&n; * updates the position of the voice buffer hardware pointer (hw_pos)&n; * and the number of free bytes on the buffer (free_bytes).&n; * The free bytes _don&squot;t_ include silence bytes that may have been&n; * added to the buffer.&n; *&n; */
DECL|function|emu10k1_waveout_update
r_void
id|emu10k1_waveout_update
c_func
(paren
r_struct
id|woinst
op_star
id|woinst
)paren
(brace
id|u32
id|hw_pos
suffix:semicolon
id|u32
id|diff
suffix:semicolon
multiline_comment|/* There is no actual start yet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|woinst-&gt;state
op_amp
id|WAVE_STATE_STARTED
)paren
)paren
(brace
id|hw_pos
op_assign
id|woinst-&gt;buffer.hw_pos
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* hw_pos in sample units */
id|hw_pos
op_assign
id|sblive_readptr
c_func
(paren
id|woinst-&gt;voice
(braket
l_int|0
)braket
dot
id|card
comma
id|CCCA_CURRADDR
comma
id|woinst-&gt;voice
(braket
l_int|0
)braket
dot
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_pos
OL
id|woinst-&gt;voice
(braket
l_int|0
)braket
dot
id|start
)paren
(brace
id|hw_pos
op_add_assign
id|woinst-&gt;buffer.size
op_div
id|woinst-&gt;format.bytespervoicesample
op_minus
id|woinst-&gt;voice
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
)brace
r_else
id|hw_pos
op_sub_assign
id|woinst-&gt;voice
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|hw_pos
op_mul_assign
id|woinst-&gt;format.bytespervoicesample
suffix:semicolon
)brace
id|diff
op_assign
(paren
id|woinst-&gt;buffer.size
op_plus
id|hw_pos
op_minus
id|woinst-&gt;buffer.hw_pos
)paren
op_mod
id|woinst-&gt;buffer.size
suffix:semicolon
id|woinst-&gt;total_played
op_add_assign
id|diff
suffix:semicolon
id|woinst-&gt;buffer.free_bytes
op_add_assign
id|diff
suffix:semicolon
id|woinst-&gt;buffer.hw_pos
op_assign
id|hw_pos
suffix:semicolon
)brace
eof
