multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Creative Labs, Inc.&n; *  Routines for IRQ control of EMU10K1 chips&n; *&n; *  BUGS:&n; *    --&n; *&n; *  TODO:&n; *    --&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
DECL|function|snd_emu10k1_interrupt
id|irqreturn_t
id|snd_emu10k1_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|emu10k1_t
op_star
id|emu
op_assign
id|dev_id
suffix:semicolon
r_int
r_int
id|status
comma
id|status2
comma
id|orig_status
comma
id|orig_status2
suffix:semicolon
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|status
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|IPR
)paren
)paren
op_ne
l_int|0
)paren
(brace
singleline_comment|// printk(&quot;irq - status = 0x%x&bslash;n&quot;, status);
id|orig_status
op_assign
id|status
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IPR_PCIERROR
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;interrupt: PCI error&bslash;n&quot;
)paren
suffix:semicolon
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_PCIERRORENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
id|IPR_PCIERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_VOLINCR
op_or
id|IPR_VOLDECR
op_or
id|IPR_MUTE
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;hwvol_interrupt
)paren
id|emu
op_member_access_from_pointer
id|hwvol_interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_VOLINCRENABLE
op_or
id|INTE_VOLDECRENABLE
op_or
id|INTE_MUTEENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_VOLINCR
op_or
id|IPR_VOLDECR
op_or
id|IPR_MUTE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|IPR_CHANNELLOOP
)paren
(brace
r_int
id|voice
suffix:semicolon
r_int
id|voice_max
op_assign
id|status
op_amp
id|IPR_CHANNELNUMBERMASK
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|emu10k1_voice_t
op_star
id|pvoice
op_assign
id|emu-&gt;voices
suffix:semicolon
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|CLIPL
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voice
op_assign
l_int|0
suffix:semicolon
id|voice
op_le
id|voice_max
suffix:semicolon
id|voice
op_increment
)paren
(brace
r_if
c_cond
(paren
id|voice
op_eq
l_int|0x20
)paren
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|CLIPH
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|pvoice-&gt;use
op_logical_and
id|pvoice-&gt;interrupt
op_ne
l_int|NULL
)paren
(brace
id|pvoice
op_member_access_from_pointer
id|interrupt
c_func
(paren
id|emu
comma
id|pvoice
)paren
suffix:semicolon
id|snd_emu10k1_voice_intr_ack
c_func
(paren
id|emu
comma
id|voice
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_emu10k1_voice_intr_disable
c_func
(paren
id|emu
comma
id|voice
)paren
suffix:semicolon
)brace
)brace
id|val
op_rshift_assign
l_int|1
suffix:semicolon
id|pvoice
op_increment
suffix:semicolon
)brace
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|HLIPL
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|voice
op_assign
l_int|0
suffix:semicolon
id|voice
op_le
id|voice_max
suffix:semicolon
id|voice
op_increment
)paren
(brace
r_if
c_cond
(paren
id|voice
op_eq
l_int|0x20
)paren
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|HLIPH
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|pvoice-&gt;use
op_logical_and
id|pvoice-&gt;interrupt
op_ne
l_int|NULL
)paren
(brace
id|pvoice
op_member_access_from_pointer
id|interrupt
c_func
(paren
id|emu
comma
id|pvoice
)paren
suffix:semicolon
id|snd_emu10k1_voice_half_loop_intr_ack
c_func
(paren
id|emu
comma
id|voice
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_emu10k1_voice_half_loop_intr_disable
c_func
(paren
id|emu
comma
id|voice
)paren
suffix:semicolon
)brace
)brace
id|val
op_rshift_assign
l_int|1
suffix:semicolon
id|pvoice
op_increment
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
id|IPR_CHANNELLOOP
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
id|IPR_CHANNELNUMBERMASK
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_ADCBUFFULL
op_or
id|IPR_ADCBUFHALFFULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;capture_interrupt
)paren
id|emu
op_member_access_from_pointer
id|capture_interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_ADCBUFENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_ADCBUFFULL
op_or
id|IPR_ADCBUFHALFFULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_MICBUFFULL
op_or
id|IPR_MICBUFHALFFULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;capture_mic_interrupt
)paren
id|emu
op_member_access_from_pointer
id|capture_mic_interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_MICBUFENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_MICBUFFULL
op_or
id|IPR_MICBUFHALFFULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_EFXBUFFULL
op_or
id|IPR_EFXBUFHALFFULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;capture_efx_interrupt
)paren
id|emu
op_member_access_from_pointer
id|capture_efx_interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_EFXBUFENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_EFXBUFFULL
op_or
id|IPR_EFXBUFHALFFULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_MIDITRANSBUFEMPTY
op_or
id|IPR_MIDIRECVBUFEMPTY
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;midi.interrupt
)paren
id|emu-&gt;midi
dot
id|interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_MIDITXENABLE
op_or
id|INTE_MIDIRXENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_MIDITRANSBUFEMPTY
op_or
id|IPR_MIDIRECVBUFEMPTY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_A_MIDITRANSBUFEMPTY2
op_or
id|IPR_A_MIDIRECVBUFEMPTY2
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;midi2.interrupt
)paren
id|emu-&gt;midi2
dot
id|interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_A_MIDITXENABLE2
op_or
id|INTE_A_MIDIRXENABLE2
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_A_MIDITRANSBUFEMPTY2
op_or
id|IPR_A_MIDIRECVBUFEMPTY2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|IPR_INTERVALTIMER
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;timer
)paren
id|snd_timer_interrupt
c_func
(paren
id|emu-&gt;timer
comma
id|emu-&gt;timer-&gt;sticks
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_INTERVALTIMERENB
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
id|IPR_INTERVALTIMER
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|IPR_GPSPDIFSTATUSCHANGE
op_or
id|IPR_CDROMSTATUSCHANGE
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;spdif_interrupt
)paren
id|emu
op_member_access_from_pointer
id|spdif_interrupt
c_func
(paren
id|emu
comma
id|status
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_GPSPDIFENABLE
op_or
id|INTE_CDSPDIFENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|IPR_GPSPDIFSTATUSCHANGE
op_or
id|IPR_CDROMSTATUSCHANGE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|IPR_FXDSP
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;dsp_interrupt
)paren
id|emu
op_member_access_from_pointer
id|dsp_interrupt
c_func
(paren
id|emu
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_FXDSPENABLE
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
id|IPR_FXDSP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
)paren
(brace
r_int
r_int
id|bits
suffix:semicolon
singleline_comment|//snd_printk(KERN_ERR &quot;emu10k1: unhandled interrupt: 0x%08x&bslash;n&quot;, status);
singleline_comment|//make sure any interrupts we don&squot;t handle are disabled:
id|bits
op_assign
id|INTE_FXDSPENABLE
op_or
id|INTE_PCIERRORENABLE
op_or
id|INTE_VOLINCRENABLE
op_or
id|INTE_VOLDECRENABLE
op_or
id|INTE_MUTEENABLE
op_or
id|INTE_MICBUFENABLE
op_or
id|INTE_ADCBUFENABLE
op_or
id|INTE_EFXBUFENABLE
op_or
id|INTE_GPSPDIFENABLE
op_or
id|INTE_CDSPDIFENABLE
op_or
id|INTE_INTERVALTIMERENB
op_or
id|INTE_MIDITXENABLE
op_or
id|INTE_MIDIRXENABLE
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
id|bits
op_or_assign
id|INTE_A_MIDITXENABLE2
op_or
id|INTE_A_MIDIRXENABLE2
suffix:semicolon
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|bits
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
id|orig_status
comma
id|emu-&gt;port
op_plus
id|IPR
)paren
suffix:semicolon
multiline_comment|/* ack all */
)brace
r_while
c_loop
(paren
(paren
id|status2
op_assign
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|IPR2
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|u32
id|mask
op_assign
id|INTE2_PLAYBACK_CH_0_LOOP
suffix:semicolon
multiline_comment|/* Full Loop */
id|emu10k1_voice_t
op_star
id|pvoice
op_assign
op_amp
(paren
id|emu-&gt;p16v_voices
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|orig_status2
op_assign
id|status2
suffix:semicolon
r_if
c_cond
(paren
id|status2
op_amp
id|mask
)paren
(brace
r_if
c_cond
(paren
id|pvoice-&gt;use
)paren
(brace
id|snd_pcm_period_elapsed
c_func
(paren
id|pvoice-&gt;epcm-&gt;substream
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;p16v: status: 0x%08x, mask=0x%08x, pvoice=%p, use=%d&bslash;n&quot;
comma
id|status2
comma
id|mask
comma
id|pvoice
comma
id|pvoice-&gt;use
)paren
suffix:semicolon
)brace
)brace
id|outl
c_func
(paren
id|orig_status2
comma
id|emu-&gt;port
op_plus
id|IPR2
)paren
suffix:semicolon
multiline_comment|/* ack all */
)brace
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
)brace
eof
