multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Creative Labs, Inc.&n; *  Routines for control of EMU10K1 chips&n; *&n; *  BUGS:&n; *    --&n; *&n; *  TODO:&n; *    --&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
DECL|function|snd_emu10k1_ptr_read
r_int
r_int
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|chn
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|regptr
comma
id|val
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
id|emu-&gt;audigy
ques
c_cond
id|A_PTR_ADDRESS_MASK
suffix:colon
id|PTR_ADDRESS_MASK
suffix:semicolon
id|regptr
op_assign
(paren
(paren
id|reg
op_lshift
l_int|16
)paren
op_amp
id|mask
)paren
op_or
(paren
id|chn
op_amp
id|PTR_CHANNELNUM_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
r_int
r_char
id|size
comma
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|val
op_amp
id|mask
)paren
op_rshift
id|offset
suffix:semicolon
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
)brace
DECL|function|snd_emu10k1_ptr_write
r_void
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|chn
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|regptr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
id|emu-&gt;audigy
ques
c_cond
id|A_PTR_ADDRESS_MASK
suffix:colon
id|PTR_ADDRESS_MASK
suffix:semicolon
id|regptr
op_assign
(paren
(paren
id|reg
op_lshift
l_int|16
)paren
op_amp
id|mask
)paren
op_or
(paren
id|chn
op_amp
id|PTR_CHANNELNUM_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
r_int
r_char
id|size
comma
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
suffix:semicolon
id|data
op_assign
(paren
id|data
op_lshift
id|offset
)paren
op_amp
id|mask
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|data
op_or_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
op_amp
op_complement
id|mask
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_emu10k1_intr_enable
r_void
id|snd_emu10k1_intr_enable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|intrenb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|enable
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|enable
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|INTE
)paren
op_or
id|intrenb
suffix:semicolon
id|outl
c_func
(paren
id|enable
comma
id|emu-&gt;port
op_plus
id|INTE
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_intr_disable
r_void
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|intrenb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|enable
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|enable
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|INTE
)paren
op_amp
op_complement
id|intrenb
suffix:semicolon
id|outl
c_func
(paren
id|enable
comma
id|emu-&gt;port
op_plus
id|INTE
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_intr_enable
r_void
id|snd_emu10k1_voice_intr_enable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
(brace
id|outl
c_func
(paren
id|CLIEH
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|val
op_or_assign
l_int|1
op_lshift
(paren
id|voicenum
op_minus
l_int|32
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
c_func
(paren
id|CLIEL
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|val
op_or_assign
l_int|1
op_lshift
id|voicenum
suffix:semicolon
)brace
id|outl
c_func
(paren
id|val
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_intr_disable
r_void
id|snd_emu10k1_voice_intr_disable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
(brace
id|outl
c_func
(paren
id|CLIEH
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|voicenum
op_minus
l_int|32
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
c_func
(paren
id|CLIEL
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|voicenum
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
id|val
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_intr_ack
r_void
id|snd_emu10k1_voice_intr_ack
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
(brace
id|outl
c_func
(paren
id|CLIPH
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|voicenum
op_assign
l_int|1
op_lshift
(paren
id|voicenum
op_minus
l_int|32
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
c_func
(paren
id|CLIPL
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|voicenum
op_assign
l_int|1
op_lshift
id|voicenum
suffix:semicolon
)brace
id|outl
c_func
(paren
id|voicenum
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_set_loop_stop
r_void
id|snd_emu10k1_voice_set_loop_stop
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|sol
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
(brace
id|outl
c_func
(paren
id|SOLEH
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|sol
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|sol
op_or_assign
l_int|1
op_lshift
(paren
id|voicenum
op_minus
l_int|32
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
c_func
(paren
id|SOLEL
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|sol
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|sol
op_or_assign
l_int|1
op_lshift
id|voicenum
suffix:semicolon
)brace
id|outl
c_func
(paren
id|sol
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_voice_clear_loop_stop
r_void
id|snd_emu10k1_voice_clear_loop_stop
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|sol
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
(brace
id|outl
c_func
(paren
id|SOLEH
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|sol
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|sol
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|voicenum
op_minus
l_int|32
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
c_func
(paren
id|SOLEL
op_lshift
l_int|16
comma
id|emu-&gt;port
op_plus
id|PTR
)paren
suffix:semicolon
id|sol
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|sol
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|voicenum
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
id|sol
comma
id|emu-&gt;port
op_plus
id|DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_wait
r_void
id|snd_emu10k1_wait
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|wait
)paren
(brace
r_volatile
r_int
id|count
suffix:semicolon
r_int
r_int
id|newtime
op_assign
l_int|0
comma
id|curtime
suffix:semicolon
id|curtime
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|WC
)paren
op_rshift
l_int|6
suffix:semicolon
r_while
c_loop
(paren
id|wait
op_decrement
OG
l_int|0
)paren
(brace
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16384
)paren
(brace
id|newtime
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|WC
)paren
op_rshift
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|newtime
op_ne
id|curtime
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_ge
l_int|16384
)paren
r_break
suffix:semicolon
id|curtime
op_assign
id|newtime
suffix:semicolon
)brace
)brace
DECL|function|snd_emu10k1_ac97_read
r_int
r_int
id|snd_emu10k1_ac97_read
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|ac97-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|emu-&gt;port
op_plus
id|AC97ADDRESS
)paren
suffix:semicolon
id|val
op_assign
id|inw
c_func
(paren
id|emu-&gt;port
op_plus
id|AC97DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|snd_emu10k1_ac97_write
r_void
id|snd_emu10k1_ac97_write
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|data
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|ac97-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|emu-&gt;port
op_plus
id|AC97ADDRESS
)paren
suffix:semicolon
id|outw
c_func
(paren
id|data
comma
id|emu-&gt;port
op_plus
id|AC97DATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;emu_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  convert rate to pitch&n; */
DECL|function|snd_emu10k1_rate_to_pitch
r_int
r_int
id|snd_emu10k1_rate_to_pitch
c_func
(paren
r_int
r_int
id|rate
)paren
(brace
r_static
id|u32
id|logMagTable
(braket
l_int|128
)braket
op_assign
(brace
l_int|0x00000
comma
l_int|0x02dfc
comma
l_int|0x05b9e
comma
l_int|0x088e6
comma
l_int|0x0b5d6
comma
l_int|0x0e26f
comma
l_int|0x10eb3
comma
l_int|0x13aa2
comma
l_int|0x1663f
comma
l_int|0x1918a
comma
l_int|0x1bc84
comma
l_int|0x1e72e
comma
l_int|0x2118b
comma
l_int|0x23b9a
comma
l_int|0x2655d
comma
l_int|0x28ed5
comma
l_int|0x2b803
comma
l_int|0x2e0e8
comma
l_int|0x30985
comma
l_int|0x331db
comma
l_int|0x359eb
comma
l_int|0x381b6
comma
l_int|0x3a93d
comma
l_int|0x3d081
comma
l_int|0x3f782
comma
l_int|0x41e42
comma
l_int|0x444c1
comma
l_int|0x46b01
comma
l_int|0x49101
comma
l_int|0x4b6c4
comma
l_int|0x4dc49
comma
l_int|0x50191
comma
l_int|0x5269e
comma
l_int|0x54b6f
comma
l_int|0x57006
comma
l_int|0x59463
comma
l_int|0x5b888
comma
l_int|0x5dc74
comma
l_int|0x60029
comma
l_int|0x623a7
comma
l_int|0x646ee
comma
l_int|0x66a00
comma
l_int|0x68cdd
comma
l_int|0x6af86
comma
l_int|0x6d1fa
comma
l_int|0x6f43c
comma
l_int|0x7164b
comma
l_int|0x73829
comma
l_int|0x759d4
comma
l_int|0x77b4f
comma
l_int|0x79c9a
comma
l_int|0x7bdb5
comma
l_int|0x7dea1
comma
l_int|0x7ff5e
comma
l_int|0x81fed
comma
l_int|0x8404e
comma
l_int|0x86082
comma
l_int|0x88089
comma
l_int|0x8a064
comma
l_int|0x8c014
comma
l_int|0x8df98
comma
l_int|0x8fef1
comma
l_int|0x91e20
comma
l_int|0x93d26
comma
l_int|0x95c01
comma
l_int|0x97ab4
comma
l_int|0x9993e
comma
l_int|0x9b79f
comma
l_int|0x9d5d9
comma
l_int|0x9f3ec
comma
l_int|0xa11d8
comma
l_int|0xa2f9d
comma
l_int|0xa4d3c
comma
l_int|0xa6ab5
comma
l_int|0xa8808
comma
l_int|0xaa537
comma
l_int|0xac241
comma
l_int|0xadf26
comma
l_int|0xafbe7
comma
l_int|0xb1885
comma
l_int|0xb3500
comma
l_int|0xb5157
comma
l_int|0xb6d8c
comma
l_int|0xb899f
comma
l_int|0xba58f
comma
l_int|0xbc15e
comma
l_int|0xbdd0c
comma
l_int|0xbf899
comma
l_int|0xc1404
comma
l_int|0xc2f50
comma
l_int|0xc4a7b
comma
l_int|0xc6587
comma
l_int|0xc8073
comma
l_int|0xc9b3f
comma
l_int|0xcb5ed
comma
l_int|0xcd07c
comma
l_int|0xceaec
comma
l_int|0xd053f
comma
l_int|0xd1f73
comma
l_int|0xd398a
comma
l_int|0xd5384
comma
l_int|0xd6d60
comma
l_int|0xd8720
comma
l_int|0xda0c3
comma
l_int|0xdba4a
comma
l_int|0xdd3b4
comma
l_int|0xded03
comma
l_int|0xe0636
comma
l_int|0xe1f4e
comma
l_int|0xe384a
comma
l_int|0xe512c
comma
l_int|0xe69f3
comma
l_int|0xe829f
comma
l_int|0xe9b31
comma
l_int|0xeb3a9
comma
l_int|0xecc08
comma
l_int|0xee44c
comma
l_int|0xefc78
comma
l_int|0xf148a
comma
l_int|0xf2c83
comma
l_int|0xf4463
comma
l_int|0xf5c2a
comma
l_int|0xf73da
comma
l_int|0xf8b71
comma
l_int|0xfa2f0
comma
l_int|0xfba57
comma
l_int|0xfd1a7
comma
l_int|0xfe8df
)brace
suffix:semicolon
r_static
r_char
id|logSlopeTable
(braket
l_int|128
)braket
op_assign
(brace
l_int|0x5c
comma
l_int|0x5c
comma
l_int|0x5b
comma
l_int|0x5a
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x58
comma
l_int|0x58
comma
l_int|0x57
comma
l_int|0x56
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x55
comma
l_int|0x54
comma
l_int|0x53
comma
l_int|0x53
comma
l_int|0x52
comma
l_int|0x52
comma
l_int|0x51
comma
l_int|0x51
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x4f
comma
l_int|0x4f
comma
l_int|0x4e
comma
l_int|0x4d
comma
l_int|0x4d
comma
l_int|0x4d
comma
l_int|0x4c
comma
l_int|0x4c
comma
l_int|0x4b
comma
l_int|0x4b
comma
l_int|0x4a
comma
l_int|0x4a
comma
l_int|0x49
comma
l_int|0x49
comma
l_int|0x48
comma
l_int|0x48
comma
l_int|0x47
comma
l_int|0x47
comma
l_int|0x47
comma
l_int|0x46
comma
l_int|0x46
comma
l_int|0x45
comma
l_int|0x45
comma
l_int|0x45
comma
l_int|0x44
comma
l_int|0x44
comma
l_int|0x43
comma
l_int|0x43
comma
l_int|0x43
comma
l_int|0x42
comma
l_int|0x42
comma
l_int|0x42
comma
l_int|0x41
comma
l_int|0x41
comma
l_int|0x41
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x3f
comma
l_int|0x3f
comma
l_int|0x3f
comma
l_int|0x3e
comma
l_int|0x3e
comma
l_int|0x3e
comma
l_int|0x3d
comma
l_int|0x3d
comma
l_int|0x3d
comma
l_int|0x3c
comma
l_int|0x3c
comma
l_int|0x3c
comma
l_int|0x3b
comma
l_int|0x3b
comma
l_int|0x3b
comma
l_int|0x3b
comma
l_int|0x3a
comma
l_int|0x3a
comma
l_int|0x3a
comma
l_int|0x39
comma
l_int|0x39
comma
l_int|0x39
comma
l_int|0x39
comma
l_int|0x38
comma
l_int|0x38
comma
l_int|0x38
comma
l_int|0x38
comma
l_int|0x37
comma
l_int|0x37
comma
l_int|0x37
comma
l_int|0x37
comma
l_int|0x36
comma
l_int|0x36
comma
l_int|0x36
comma
l_int|0x36
comma
l_int|0x35
comma
l_int|0x35
comma
l_int|0x35
comma
l_int|0x35
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x2f
comma
l_int|0x2f
comma
l_int|0x2f
comma
l_int|0x2f
comma
l_int|0x2f
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|rate
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Bail out if no leading &quot;1&quot; */
id|rate
op_mul_assign
l_int|11185
suffix:semicolon
multiline_comment|/* Scale 48000 to 0x20002380 */
r_for
c_loop
(paren
id|i
op_assign
l_int|31
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|rate
op_amp
l_int|0x80000000
)paren
(brace
multiline_comment|/* Detect leading &quot;1&quot; */
r_return
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|i
op_minus
l_int|15
)paren
op_lshift
l_int|20
)paren
op_plus
id|logMagTable
(braket
l_int|0x7f
op_amp
(paren
id|rate
op_rshift
l_int|24
)paren
)braket
op_plus
(paren
l_int|0x7f
op_amp
(paren
id|rate
op_rshift
l_int|17
)paren
)paren
op_star
id|logSlopeTable
(braket
l_int|0x7f
op_amp
(paren
id|rate
op_rshift
l_int|24
)paren
)braket
)paren
suffix:semicolon
)brace
id|rate
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Should never reach this point */
)brace
eof
