multiline_comment|/*&n; *  synth callback routines for Emu10k1&n; *&n; *  Copyright (C) 2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;emu10k1_synth_local.h&quot;
macro_line|#include &lt;sound/asoundef.h&gt;
multiline_comment|/* voice status */
r_enum
(brace
DECL|enumerator|V_FREE
DECL|enumerator|V_OFF
DECL|enumerator|V_RELEASED
DECL|enumerator|V_PLAYING
DECL|enumerator|V_END
id|V_FREE
op_assign
l_int|0
comma
id|V_OFF
comma
id|V_RELEASED
comma
id|V_PLAYING
comma
id|V_END
)brace
suffix:semicolon
multiline_comment|/* Keeps track of what we are finding */
DECL|struct|best_voice
r_typedef
r_struct
id|best_voice
(brace
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
DECL|member|voice
r_int
id|voice
suffix:semicolon
DECL|typedef|best_voice_t
)brace
id|best_voice_t
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
r_void
id|lookup_voices
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|emu10k1_t
op_star
id|hw
comma
id|best_voice_t
op_star
id|best
comma
r_int
id|active_only
)paren
suffix:semicolon
r_static
id|snd_emux_voice_t
op_star
id|get_voice
c_func
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
r_static
r_int
id|start_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|trigger_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|release_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|update_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
comma
r_int
id|update
)paren
suffix:semicolon
r_static
r_void
id|terminate_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|free_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|set_fmmod
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|set_fm2frq2
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
r_static
r_void
id|set_filterQ
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|snd_emux_voice_t
op_star
id|vp
)paren
suffix:semicolon
multiline_comment|/*&n; * Ensure a value is between two points&n; * macro evaluates its args more than once, so changed to upper-case.&n; */
DECL|macro|LIMITVALUE
mdefine_line|#define LIMITVALUE(x, a, b) do { if ((x) &lt; (a)) (x) = (a); else if ((x) &gt; (b)) (x) = (b); } while (0)
DECL|macro|LIMITMAX
mdefine_line|#define LIMITMAX(x, a) do {if ((x) &gt; (a)) (x) = (a); } while (0)
multiline_comment|/*&n; * set up operators&n; */
DECL|variable|emu10k1_ops
r_static
id|snd_emux_operators_t
id|emu10k1_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|get_voice
op_assign
id|get_voice
comma
dot
id|prepare
op_assign
id|start_voice
comma
dot
id|trigger
op_assign
id|trigger_voice
comma
dot
id|release
op_assign
id|release_voice
comma
dot
id|update
op_assign
id|update_voice
comma
dot
id|terminate
op_assign
id|terminate_voice
comma
dot
id|free_voice
op_assign
id|free_voice
comma
dot
id|sample_new
op_assign
id|snd_emu10k1_sample_new
comma
dot
id|sample_free
op_assign
id|snd_emu10k1_sample_free
comma
)brace
suffix:semicolon
r_void
DECL|function|snd_emu10k1_ops_setup
id|snd_emu10k1_ops_setup
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
(brace
id|emu-&gt;ops
op_assign
id|emu10k1_ops
suffix:semicolon
)brace
multiline_comment|/*&n; * get more voice for pcm&n; *&n; * terminate most inactive voice and give it as a pcm voice.&n; */
r_int
DECL|function|snd_emu10k1_synth_get_voice
id|snd_emu10k1_synth_get_voice
c_func
(paren
id|emu10k1_t
op_star
id|hw
)paren
(brace
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|snd_emux_voice_t
op_star
id|vp
suffix:semicolon
id|best_voice_t
id|best
(braket
id|V_END
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_t
comma
id|hw-&gt;synth
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;voice_lock
comma
id|flags
)paren
suffix:semicolon
id|lookup_voices
c_func
(paren
id|emu
comma
id|hw
comma
id|best
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* no OFF voices */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|V_END
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|best
(braket
id|i
)braket
dot
id|voice
op_ge
l_int|0
)paren
(brace
r_int
id|ch
suffix:semicolon
id|vp
op_assign
op_amp
id|emu-&gt;voices
(braket
id|best
(braket
id|i
)braket
dot
id|voice
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ch
op_assign
id|vp-&gt;ch
)paren
OL
l_int|0
)paren
(brace
singleline_comment|//printk(&quot;synth_get_voice: ch &lt; 0 (%d) ??&quot;, i);
r_continue
suffix:semicolon
)brace
id|vp-&gt;emu-&gt;num_voices
op_decrement
suffix:semicolon
id|vp-&gt;ch
op_assign
op_minus
l_int|1
suffix:semicolon
id|vp-&gt;state
op_assign
id|SNDRV_EMUX_ST_OFF
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;voice_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;voice_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* not found */
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n; * turn off the voice (not terminated)&n; */
r_static
r_void
DECL|function|release_voice
id|release_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
r_int
id|dcysusv
suffix:semicolon
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|vp-&gt;hw
comma
r_return
)paren
suffix:semicolon
id|dcysusv
op_assign
l_int|0x8000
op_or
(paren
r_int
r_char
)paren
id|vp-&gt;reg.parm.modrelease
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSM
comma
id|vp-&gt;ch
comma
id|dcysusv
)paren
suffix:semicolon
id|dcysusv
op_assign
l_int|0x8000
op_or
(paren
r_int
r_char
)paren
id|vp-&gt;reg.parm.volrelease
op_or
id|DCYSUSV_CHANNELENABLE_MASK
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSV
comma
id|vp-&gt;ch
comma
id|dcysusv
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * terminate the voice&n; */
r_static
r_void
DECL|function|terminate_voice
id|terminate_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|snd_assert
c_func
(paren
id|vp
comma
r_return
)paren
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|vp-&gt;hw
comma
r_return
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSV
comma
id|vp-&gt;ch
comma
l_int|0x807f
op_or
id|DCYSUSV_CHANNELENABLE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;block
)paren
(brace
id|emu10k1_memblk_t
op_star
id|emem
suffix:semicolon
id|emem
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|vp-&gt;block
suffix:semicolon
r_if
c_cond
(paren
id|emem-&gt;map_locked
OG
l_int|0
)paren
id|emem-&gt;map_locked
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * release the voice to system&n; */
r_static
r_void
DECL|function|free_voice
id|free_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|vp-&gt;hw
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;ch
op_ge
l_int|0
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|IFATN
comma
id|vp-&gt;ch
comma
l_int|0xff00
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSV
comma
id|vp-&gt;ch
comma
l_int|0x807f
op_or
id|DCYSUSV_CHANNELENABLE_MASK
)paren
suffix:semicolon
singleline_comment|// snd_emu10k1_ptr_write(hw, DCYSUSV, vp-&gt;ch, 0);
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|VTFT
comma
id|vp-&gt;ch
comma
l_int|0xffff
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CVCF
comma
id|vp-&gt;ch
comma
l_int|0xffff
)paren
suffix:semicolon
id|snd_emu10k1_voice_free
c_func
(paren
id|hw
comma
op_amp
id|hw-&gt;voices
(braket
id|vp-&gt;ch
)braket
)paren
suffix:semicolon
id|vp-&gt;emu-&gt;num_voices
op_decrement
suffix:semicolon
id|vp-&gt;ch
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * update registers&n; */
r_static
r_void
DECL|function|update_voice
id|update_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
comma
r_int
id|update
)paren
(brace
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|vp-&gt;hw
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_VOLUME
)paren
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|IFATN_ATTENUATION
comma
id|vp-&gt;ch
comma
id|vp-&gt;avol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_PITCH
)paren
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|IP
comma
id|vp-&gt;ch
comma
id|vp-&gt;apitch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_PAN
)paren
(brace
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|PTRX_FXSENDAMOUNT_A
comma
id|vp-&gt;ch
comma
id|vp-&gt;apan
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|PTRX_FXSENDAMOUNT_B
comma
id|vp-&gt;ch
comma
id|vp-&gt;aaux
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_FMMOD
)paren
id|set_fmmod
c_func
(paren
id|hw
comma
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_TREMFREQ
)paren
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|TREMFRQ
comma
id|vp-&gt;ch
comma
id|vp-&gt;reg.parm.tremfrq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_FM2FRQ2
)paren
id|set_fm2frq2
c_func
(paren
id|hw
comma
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update
op_amp
id|SNDRV_EMUX_UPDATE_Q
)paren
id|set_filterQ
c_func
(paren
id|hw
comma
id|vp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * look up voice table - get the best voice in order of preference&n; */
multiline_comment|/* spinlock held! */
r_static
r_void
DECL|function|lookup_voices
id|lookup_voices
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|emu10k1_t
op_star
id|hw
comma
id|best_voice_t
op_star
id|best
comma
r_int
id|active_only
)paren
(brace
id|snd_emux_voice_t
op_star
id|vp
suffix:semicolon
id|best_voice_t
op_star
id|bp
suffix:semicolon
r_int
id|i
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
id|V_END
suffix:semicolon
id|i
op_increment
)paren
(brace
id|best
(braket
id|i
)braket
dot
id|time
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* XXX MAX_?INT really */
suffix:semicolon
id|best
(braket
id|i
)braket
dot
id|voice
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Go through them all and get a best one to use.&n;&t; * NOTE: could also look at volume and pick the quietest one.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|emu-&gt;max_voices
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|state
comma
id|val
suffix:semicolon
id|vp
op_assign
op_amp
id|emu-&gt;voices
(braket
id|i
)braket
suffix:semicolon
id|state
op_assign
id|vp-&gt;state
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
id|SNDRV_EMUX_ST_OFF
)paren
(brace
r_if
c_cond
(paren
id|vp-&gt;ch
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|active_only
)paren
r_continue
suffix:semicolon
id|bp
op_assign
id|best
op_plus
id|V_FREE
suffix:semicolon
)brace
r_else
id|bp
op_assign
id|best
op_plus
id|V_OFF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|SNDRV_EMUX_ST_RELEASED
op_logical_or
id|state
op_eq
id|SNDRV_EMUX_ST_PENDING
)paren
(brace
id|bp
op_assign
id|best
op_plus
id|V_RELEASED
suffix:semicolon
macro_line|#if 0
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|hw
comma
id|CVCF_CURRENTVOL
comma
id|vp-&gt;ch
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|bp
op_assign
id|best
op_plus
id|V_OFF
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|SNDRV_EMUX_ST_STANDBY
)paren
r_continue
suffix:semicolon
r_else
r_if
c_cond
(paren
id|state
op_amp
id|SNDRV_EMUX_ST_ON
)paren
id|bp
op_assign
id|best
op_plus
id|V_PLAYING
suffix:semicolon
r_else
r_continue
suffix:semicolon
multiline_comment|/* check if sample is finished playing (non-looping only) */
r_if
c_cond
(paren
id|bp
op_ne
id|best
op_plus
id|V_OFF
op_logical_and
id|bp
op_ne
id|best
op_plus
id|V_FREE
op_logical_and
(paren
id|vp-&gt;reg.sample_mode
op_amp
id|SNDRV_SFNT_SAMPLE_SINGLESHOT
)paren
)paren
(brace
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|hw
comma
id|CCCA_CURRADDR
comma
id|vp-&gt;ch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ge
id|vp-&gt;reg.loopstart
)paren
id|bp
op_assign
id|best
op_plus
id|V_OFF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vp-&gt;time
OL
id|bp-&gt;time
)paren
(brace
id|bp-&gt;time
op_assign
id|vp-&gt;time
suffix:semicolon
id|bp-&gt;voice
op_assign
id|i
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * get an empty voice&n; *&n; * emu-&gt;voice_lock is already held.&n; */
r_static
id|snd_emux_voice_t
op_star
DECL|function|get_voice
id|get_voice
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
)paren
(brace
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|snd_emux_voice_t
op_star
id|vp
suffix:semicolon
id|best_voice_t
id|best
(braket
id|V_END
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|emu-&gt;hw
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|lookup_voices
c_func
(paren
id|emu
comma
id|hw
comma
id|best
comma
l_int|0
)paren
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
id|V_END
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|best
(braket
id|i
)braket
dot
id|voice
op_ge
l_int|0
)paren
(brace
id|vp
op_assign
op_amp
id|emu-&gt;voices
(braket
id|best
(braket
id|i
)braket
dot
id|voice
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;ch
OL
l_int|0
)paren
(brace
multiline_comment|/* allocate a voice */
id|emu10k1_voice_t
op_star
id|hwvoice
suffix:semicolon
r_if
c_cond
(paren
id|snd_emu10k1_voice_alloc
c_func
(paren
id|hw
comma
id|EMU10K1_SYNTH
comma
l_int|0
comma
op_amp
id|hwvoice
)paren
OL
l_int|0
op_logical_or
id|hwvoice
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|vp-&gt;ch
op_assign
id|hwvoice-&gt;number
suffix:semicolon
id|emu-&gt;num_voices
op_increment
suffix:semicolon
)brace
r_return
id|vp
suffix:semicolon
)brace
)brace
multiline_comment|/* not found */
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * prepare envelopes and LFOs&n; */
r_static
r_int
DECL|function|start_voice
id|start_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_int
r_int
id|addr
comma
id|mapped_offset
suffix:semicolon
id|snd_midi_channel_t
op_star
id|chan
suffix:semicolon
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|emem
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|vp-&gt;hw
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|ch
op_assign
id|vp-&gt;ch
suffix:semicolon
id|snd_assert
c_func
(paren
id|ch
op_ge
l_int|0
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|chan
op_assign
id|vp-&gt;chan
suffix:semicolon
id|emem
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|vp-&gt;block
suffix:semicolon
r_if
c_cond
(paren
id|emem
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|emem-&gt;map_locked
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|snd_emu10k1_memblk_map
c_func
(paren
id|hw
comma
id|emem
)paren
OL
l_int|0
)paren
(brace
singleline_comment|// printk(&quot;emu: cannot map!&bslash;n&quot;);
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|mapped_offset
op_assign
id|snd_emu10k1_memblk_offset
c_func
(paren
id|emem
)paren
op_rshift
l_int|1
suffix:semicolon
id|vp-&gt;reg.start
op_add_assign
id|mapped_offset
suffix:semicolon
id|vp-&gt;reg.end
op_add_assign
id|mapped_offset
suffix:semicolon
id|vp-&gt;reg.loopstart
op_add_assign
id|mapped_offset
suffix:semicolon
id|vp-&gt;reg.loopend
op_add_assign
id|mapped_offset
suffix:semicolon
multiline_comment|/* set channel routing */
multiline_comment|/* A = left(0), B = right(1), C = reverb(c), D = chorus(d) */
r_if
c_cond
(paren
id|hw-&gt;audigy
)paren
(brace
id|temp
op_assign
id|FXBUS_MIDI_LEFT
op_or
(paren
id|FXBUS_MIDI_RIGHT
op_lshift
l_int|8
)paren
op_or
(paren
id|FXBUS_MIDI_REVERB
op_lshift
l_int|16
)paren
op_or
(paren
id|FXBUS_MIDI_CHORUS
op_lshift
l_int|24
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|A_FXRT1
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp
op_assign
(paren
id|FXBUS_MIDI_LEFT
op_lshift
l_int|16
)paren
op_or
(paren
id|FXBUS_MIDI_RIGHT
op_lshift
l_int|20
)paren
op_or
(paren
id|FXBUS_MIDI_REVERB
op_lshift
l_int|24
)paren
op_or
(paren
id|FXBUS_MIDI_CHORUS
op_lshift
l_int|28
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|FXRT
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
)brace
multiline_comment|/* channel to be silent and idle */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSV
comma
id|ch
comma
l_int|0x0080
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|VTFT
comma
id|ch
comma
l_int|0x0000FFFF
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CVCF
comma
id|ch
comma
l_int|0x0000FFFF
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|PTRX
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CPF
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set pitch offset */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|IP
comma
id|vp-&gt;ch
comma
id|vp-&gt;apitch
)paren
suffix:semicolon
multiline_comment|/* set envelope parameters */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|ENVVAL
comma
id|ch
comma
id|vp-&gt;reg.parm.moddelay
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|ATKHLDM
comma
id|ch
comma
id|vp-&gt;reg.parm.modatkhld
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSM
comma
id|ch
comma
id|vp-&gt;reg.parm.moddcysus
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|ENVVOL
comma
id|ch
comma
id|vp-&gt;reg.parm.voldelay
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|ATKHLDV
comma
id|ch
comma
id|vp-&gt;reg.parm.volatkhld
)paren
suffix:semicolon
multiline_comment|/* decay/sustain parameter for volume envelope is used&n;&t;   for triggerg the voice */
multiline_comment|/* cutoff and volume */
id|temp
op_assign
(paren
r_int
r_int
)paren
id|vp-&gt;acutoff
op_lshift
l_int|8
op_or
(paren
r_int
r_char
)paren
id|vp-&gt;avol
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|IFATN
comma
id|vp-&gt;ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* modulation envelope heights */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|PEFE
comma
id|ch
comma
id|vp-&gt;reg.parm.pefe
)paren
suffix:semicolon
multiline_comment|/* lfo1/2 delay */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|LFOVAL1
comma
id|ch
comma
id|vp-&gt;reg.parm.lfo1delay
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|LFOVAL2
comma
id|ch
comma
id|vp-&gt;reg.parm.lfo2delay
)paren
suffix:semicolon
multiline_comment|/* lfo1 pitch &amp; cutoff shift */
id|set_fmmod
c_func
(paren
id|hw
comma
id|vp
)paren
suffix:semicolon
multiline_comment|/* lfo1 volume &amp; freq */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|TREMFRQ
comma
id|vp-&gt;ch
comma
id|vp-&gt;reg.parm.tremfrq
)paren
suffix:semicolon
multiline_comment|/* lfo2 pitch &amp; freq */
id|set_fm2frq2
c_func
(paren
id|hw
comma
id|vp
)paren
suffix:semicolon
multiline_comment|/* reverb and loop start (reverb 8bit, MSB) */
id|temp
op_assign
id|vp-&gt;reg.parm.reverb
suffix:semicolon
id|temp
op_add_assign
(paren
r_int
)paren
id|vp-&gt;chan-&gt;control
(braket
id|MIDI_CTL_E1_REVERB_DEPTH
)braket
op_star
l_int|9
op_div
l_int|10
suffix:semicolon
id|LIMITMAX
c_func
(paren
id|temp
comma
l_int|255
)paren
suffix:semicolon
id|addr
op_assign
id|vp-&gt;reg.loopstart
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|PSST
comma
id|vp-&gt;ch
comma
(paren
id|temp
op_lshift
l_int|24
)paren
op_or
id|addr
)paren
suffix:semicolon
multiline_comment|/* chorus &amp; loop end (chorus 8bit, MSB) */
id|addr
op_assign
id|vp-&gt;reg.loopend
suffix:semicolon
id|temp
op_assign
id|vp-&gt;reg.parm.chorus
suffix:semicolon
id|temp
op_add_assign
(paren
r_int
)paren
id|chan-&gt;control
(braket
id|MIDI_CTL_E3_CHORUS_DEPTH
)braket
op_star
l_int|9
op_div
l_int|10
suffix:semicolon
id|LIMITMAX
c_func
(paren
id|temp
comma
l_int|255
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_lshift
l_int|24
)paren
op_or
id|addr
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DSL
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* clear filter delay memory */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|Z1
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|Z2
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* invalidate maps */
id|temp
op_assign
(paren
id|hw-&gt;silent_page.addr
op_lshift
l_int|1
)paren
op_or
id|MAP_PTI_MASK
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|MAPA
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|MAPB
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* cache */
(brace
r_int
r_int
id|val
comma
id|sample
suffix:semicolon
id|val
op_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;reg.sample_mode
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
id|sample
op_assign
l_int|0x80808080
suffix:semicolon
r_else
(brace
id|sample
op_assign
l_int|0
suffix:semicolon
id|val
op_mul_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* cache */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CCR
comma
id|ch
comma
l_int|0x1c
op_lshift
l_int|16
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CDE
comma
id|ch
comma
id|sample
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CDF
comma
id|ch
comma
id|sample
)paren
suffix:semicolon
multiline_comment|/* invalidate maps */
id|temp
op_assign
(paren
(paren
r_int
r_int
)paren
id|hw-&gt;silent_page_dmaaddr
op_lshift
l_int|1
)paren
op_or
id|MAP_PTI_MASK
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|MAPA
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|MAPB
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* fill cache */
id|val
op_sub_assign
l_int|4
suffix:semicolon
id|val
op_lshift_assign
l_int|25
suffix:semicolon
id|val
op_or_assign
l_int|0x1c
op_lshift
l_int|16
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CCR
comma
id|ch
comma
id|val
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Q &amp; current address (Q 4bit value, MSB) */
id|addr
op_assign
id|vp-&gt;reg.start
suffix:semicolon
id|temp
op_assign
id|vp-&gt;reg.parm.filterQ
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_lshift
l_int|28
)paren
op_or
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|vp-&gt;apitch
OL
l_int|0xe400
)paren
id|temp
op_or_assign
id|CCCA_INTERPROM_0
suffix:semicolon
r_else
(brace
r_int
r_int
id|shift
op_assign
(paren
id|vp-&gt;apitch
op_minus
l_int|0xe000
)paren
op_rshift
l_int|10
suffix:semicolon
id|temp
op_or_assign
id|shift
op_lshift
l_int|25
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vp-&gt;reg.sample_mode
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
id|temp
op_or_assign
id|CCCA_8BITSELECT
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CCCA
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* reset volume */
id|temp
op_assign
(paren
r_int
r_int
)paren
id|vp-&gt;vtarget
op_lshift
l_int|16
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|VTFT
comma
id|ch
comma
id|temp
op_or
id|vp-&gt;ftarget
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CVCF
comma
id|ch
comma
id|temp
op_or
l_int|0xff00
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Start envelope&n; */
r_static
r_void
DECL|function|trigger_voice
id|trigger_voice
c_func
(paren
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
r_int
r_int
id|temp
comma
id|ptarget
suffix:semicolon
id|emu10k1_t
op_star
id|hw
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|emem
suffix:semicolon
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|vp-&gt;hw
comma
r_return
)paren
suffix:semicolon
id|emem
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|vp-&gt;block
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|emem
op_logical_or
id|emem-&gt;mapped_page
OL
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* not mapped */
macro_line|#if 0
id|ptarget
op_assign
(paren
r_int
r_int
)paren
id|vp-&gt;ptarget
op_lshift
l_int|16
suffix:semicolon
macro_line|#else
id|ptarget
op_assign
id|IP_TO_CP
c_func
(paren
id|vp-&gt;apitch
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* set pitch target and pan (volume) */
id|temp
op_assign
id|ptarget
op_or
(paren
id|vp-&gt;apan
op_lshift
l_int|8
)paren
op_or
id|vp-&gt;aaux
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|PTRX
comma
id|vp-&gt;ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* pitch target */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CPF
comma
id|vp-&gt;ch
comma
id|ptarget
)paren
suffix:semicolon
multiline_comment|/* trigger voice */
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|DCYSUSV
comma
id|vp-&gt;ch
comma
id|vp-&gt;reg.parm.voldcysus
op_or
id|DCYSUSV_CHANNELENABLE_MASK
)paren
suffix:semicolon
)brace
DECL|macro|MOD_SENSE
mdefine_line|#define MOD_SENSE 18
multiline_comment|/* set lfo1 modulation height and cutoff */
r_static
r_void
DECL|function|set_fmmod
id|set_fmmod
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
r_int
r_int
id|fmmod
suffix:semicolon
r_int
id|pitch
suffix:semicolon
r_int
r_char
id|cutoff
suffix:semicolon
r_int
id|modulation
suffix:semicolon
id|pitch
op_assign
(paren
r_char
)paren
(paren
id|vp-&gt;reg.parm.fmmod
op_rshift
l_int|8
)paren
suffix:semicolon
id|cutoff
op_assign
(paren
id|vp-&gt;reg.parm.fmmod
op_amp
l_int|0xff
)paren
suffix:semicolon
id|modulation
op_assign
id|vp-&gt;chan-&gt;gm_modulation
op_plus
id|vp-&gt;chan-&gt;midi_pressure
suffix:semicolon
id|pitch
op_add_assign
(paren
id|MOD_SENSE
op_star
id|modulation
)paren
op_div
l_int|1200
suffix:semicolon
id|LIMITVALUE
c_func
(paren
id|pitch
comma
op_minus
l_int|128
comma
l_int|127
)paren
suffix:semicolon
id|fmmod
op_assign
(paren
(paren
r_int
r_char
)paren
id|pitch
op_lshift
l_int|8
)paren
op_or
id|cutoff
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|FMMOD
comma
id|vp-&gt;ch
comma
id|fmmod
)paren
suffix:semicolon
)brace
multiline_comment|/* set lfo2 pitch &amp; frequency */
r_static
r_void
DECL|function|set_fm2frq2
id|set_fm2frq2
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
r_int
r_int
id|fm2frq2
suffix:semicolon
r_int
id|pitch
suffix:semicolon
r_int
r_char
id|freq
suffix:semicolon
r_int
id|modulation
suffix:semicolon
id|pitch
op_assign
(paren
r_char
)paren
(paren
id|vp-&gt;reg.parm.fm2frq2
op_rshift
l_int|8
)paren
suffix:semicolon
id|freq
op_assign
id|vp-&gt;reg.parm.fm2frq2
op_amp
l_int|0xff
suffix:semicolon
id|modulation
op_assign
id|vp-&gt;chan-&gt;gm_modulation
op_plus
id|vp-&gt;chan-&gt;midi_pressure
suffix:semicolon
id|pitch
op_add_assign
(paren
id|MOD_SENSE
op_star
id|modulation
)paren
op_div
l_int|1200
suffix:semicolon
id|LIMITVALUE
c_func
(paren
id|pitch
comma
op_minus
l_int|128
comma
l_int|127
)paren
suffix:semicolon
id|fm2frq2
op_assign
(paren
(paren
r_int
r_char
)paren
id|pitch
op_lshift
l_int|8
)paren
op_or
id|freq
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|FM2FRQ2
comma
id|vp-&gt;ch
comma
id|fm2frq2
)paren
suffix:semicolon
)brace
multiline_comment|/* set filterQ */
r_static
r_void
DECL|function|set_filterQ
id|set_filterQ
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|snd_emux_voice_t
op_star
id|vp
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|hw
comma
id|CCCA
comma
id|vp-&gt;ch
)paren
op_amp
op_complement
id|CCCA_RESONANCE
suffix:semicolon
id|val
op_or_assign
(paren
id|vp-&gt;reg.parm.filterQ
op_lshift
l_int|28
)paren
suffix:semicolon
id|snd_emu10k1_ptr_write
c_func
(paren
id|hw
comma
id|CCCA
comma
id|vp-&gt;ch
comma
id|val
)paren
suffix:semicolon
)brace
eof
