multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Creative Labs, Inc.&n; *                   Lee Revell &lt;rlrevell@joe-job.com&gt;&n; *  Routines for control of EMU10K1 chips - voice manager&n; *&n; *  Rewrote voice allocator for multichannel support - rlrevell 12/2004&n; * &n; *  BUGS:&n; *    --&n; *&n; *  TODO:&n; *    --&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
multiline_comment|/* Previously the voice allocator started at 0 every time.  The new voice &n; * allocator uses a round robin scheme.  The next free voice is tracked in &n; * the card record and each allocation begins where the last left off.  The &n; * hardware requires stereo interleaved voices be aligned to an even/odd &n; * boundary.  For multichannel voice allocation we ensure than the block of &n; * voices does not cross the 32 voice boundary.  This simplifies the &n; * multichannel support and ensures we can use a single write to the &n; * (set|clear)_loop_stop registers.  Otherwise (for example) the voices would &n; * get out of sync when pausing/resuming a stream.&n; *&t;&t;&t;&t;&t;&t;&t;--rlrevell&n; */
DECL|function|voice_alloc
r_static
r_int
id|voice_alloc
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_voice_type_t
id|type
comma
r_int
id|number
comma
id|emu10k1_voice_t
op_star
op_star
id|rvoice
)paren
(brace
id|emu10k1_voice_t
op_star
id|voice
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|first_voice
comma
id|last_voice
comma
id|skip
suffix:semicolon
op_star
id|rvoice
op_assign
l_int|NULL
suffix:semicolon
id|first_voice
op_assign
id|last_voice
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|emu-&gt;next_free_voice
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NUM_G
suffix:semicolon
id|i
op_add_assign
id|number
comma
id|j
op_add_assign
id|number
)paren
(brace
singleline_comment|// printk(&quot;i %d j %d next free %d!&bslash;n&quot;, i, j, emu-&gt;next_free_voice);
id|i
op_mod_assign
id|NUM_G
suffix:semicolon
multiline_comment|/* stereo voices must be even/odd */
r_if
c_cond
(paren
(paren
id|number
op_eq
l_int|2
)paren
op_logical_and
(paren
id|i
op_mod
l_int|2
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|skip
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|number
suffix:semicolon
id|k
op_increment
)paren
(brace
id|voice
op_assign
op_amp
id|emu-&gt;voices
(braket
(paren
id|i
op_plus
id|k
)paren
op_mod
id|NUM_G
)braket
suffix:semicolon
r_if
c_cond
(paren
id|voice-&gt;use
)paren
(brace
id|skip
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|skip
)paren
(brace
singleline_comment|// printk(&quot;allocated voice %d&bslash;n&quot;, i);
id|first_voice
op_assign
id|i
suffix:semicolon
id|last_voice
op_assign
(paren
id|i
op_plus
id|number
)paren
op_mod
id|NUM_G
suffix:semicolon
id|emu-&gt;next_free_voice
op_assign
id|last_voice
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|first_voice
op_eq
id|last_voice
)paren
r_return
op_minus
id|ENOMEM
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
id|number
suffix:semicolon
id|i
op_increment
)paren
(brace
id|voice
op_assign
op_amp
id|emu-&gt;voices
(braket
(paren
id|first_voice
op_plus
id|i
)paren
op_mod
id|NUM_G
)braket
suffix:semicolon
singleline_comment|// printk(&quot;voice alloc - %i, %i of %i&bslash;n&quot;, voice-&gt;number, idx-first_voice+1, number);
id|voice-&gt;use
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EMU10K1_PCM
suffix:colon
id|voice-&gt;pcm
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EMU10K1_SYNTH
suffix:colon
id|voice-&gt;synth
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EMU10K1_MIDI
suffix:colon
id|voice-&gt;midi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EMU10K1_EFX
suffix:colon
id|voice-&gt;efx
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
op_star
id|rvoice
op_assign
op_amp
id|emu-&gt;voices
(braket
id|first_voice
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_alloc
r_int
id|snd_emu10k1_voice_alloc
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_voice_type_t
id|type
comma
r_int
id|number
comma
id|emu10k1_voice_t
op_star
op_star
id|rvoice
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|result
suffix:semicolon
id|snd_assert
c_func
(paren
id|rvoice
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|number
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|result
op_assign
id|voice_alloc
c_func
(paren
id|emu
comma
id|type
comma
id|number
comma
id|rvoice
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
op_logical_or
id|type
op_eq
id|EMU10K1_SYNTH
op_logical_or
id|type
op_eq
id|EMU10K1_MIDI
)paren
r_break
suffix:semicolon
multiline_comment|/* free a voice from synth */
r_if
c_cond
(paren
id|emu-&gt;get_synth_voice
)paren
(brace
id|result
op_assign
id|emu
op_member_access_from_pointer
id|get_synth_voice
c_func
(paren
id|emu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|emu10k1_voice_t
op_star
id|pvoice
op_assign
op_amp
id|emu-&gt;voices
(braket
id|result
)braket
suffix:semicolon
id|pvoice-&gt;interrupt
op_assign
l_int|NULL
suffix:semicolon
id|pvoice-&gt;use
op_assign
id|pvoice-&gt;pcm
op_assign
id|pvoice-&gt;synth
op_assign
id|pvoice-&gt;midi
op_assign
id|pvoice-&gt;efx
op_assign
l_int|0
suffix:semicolon
id|pvoice-&gt;epcm
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_break
suffix:semicolon
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
r_return
id|result
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_free
r_int
id|snd_emu10k1_voice_free
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_voice_t
op_star
id|pvoice
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_assert
c_func
(paren
id|pvoice
op_ne
l_int|NULL
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
id|pvoice-&gt;interrupt
op_assign
l_int|NULL
suffix:semicolon
id|pvoice-&gt;use
op_assign
id|pvoice-&gt;pcm
op_assign
id|pvoice-&gt;synth
op_assign
id|pvoice-&gt;midi
op_assign
id|pvoice-&gt;efx
op_assign
l_int|0
suffix:semicolon
id|pvoice-&gt;epcm
op_assign
l_int|NULL
suffix:semicolon
id|snd_emu10k1_voice_init
c_func
(paren
id|emu
comma
id|pvoice-&gt;number
)paren
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
l_int|0
suffix:semicolon
)brace
eof
