multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
r_extern
r_void
id|snd_gf1_timers_init
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
suffix:semicolon
r_extern
r_void
id|snd_gf1_timers_done
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
suffix:semicolon
r_extern
r_int
id|snd_gf1_synth_init
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
suffix:semicolon
r_extern
r_void
id|snd_gf1_synth_done
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
suffix:semicolon
multiline_comment|/*&n; *  ok.. default interrupt handlers...&n; */
DECL|function|snd_gf1_default_interrupt_handler_midi_out
r_static
r_void
id|snd_gf1_default_interrupt_handler_midi_out
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_and_assign
op_complement
l_int|0x20
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_default_interrupt_handler_midi_in
r_static
r_void
id|snd_gf1_default_interrupt_handler_midi_in
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_and_assign
op_complement
l_int|0x80
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_default_interrupt_handler_timer1
r_static
r_void
id|snd_gf1_default_interrupt_handler_timer1
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_SOUND_BLASTER_CONTROL
comma
id|gus-&gt;gf1.timer_enabled
op_and_assign
op_complement
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_default_interrupt_handler_timer2
r_static
r_void
id|snd_gf1_default_interrupt_handler_timer2
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_SOUND_BLASTER_CONTROL
comma
id|gus-&gt;gf1.timer_enabled
op_and_assign
op_complement
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_default_interrupt_handler_wave_and_volume
r_static
r_void
id|snd_gf1_default_interrupt_handler_wave_and_volume
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
id|snd_gus_voice_t
op_star
id|voice
)paren
(brace
id|snd_gf1_i_ctrl_stop
c_func
(paren
id|gus
comma
l_int|0x00
)paren
suffix:semicolon
id|snd_gf1_i_ctrl_stop
c_func
(paren
id|gus
comma
l_int|0x0d
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_default_interrupt_handler_dma_write
r_static
r_void
id|snd_gf1_default_interrupt_handler_dma_write
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
l_int|0x41
comma
l_int|0x00
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_default_interrupt_handler_dma_read
r_static
r_void
id|snd_gf1_default_interrupt_handler_dma_read
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
l_int|0x49
comma
l_int|0x00
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_set_default_handlers
r_void
id|snd_gf1_set_default_handlers
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
r_int
id|what
)paren
(brace
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_MIDI_OUT
)paren
id|gus-&gt;gf1.interrupt_handler_midi_out
op_assign
id|snd_gf1_default_interrupt_handler_midi_out
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_MIDI_IN
)paren
id|gus-&gt;gf1.interrupt_handler_midi_in
op_assign
id|snd_gf1_default_interrupt_handler_midi_in
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_TIMER1
)paren
id|gus-&gt;gf1.interrupt_handler_timer1
op_assign
id|snd_gf1_default_interrupt_handler_timer1
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_TIMER2
)paren
id|gus-&gt;gf1.interrupt_handler_timer2
op_assign
id|snd_gf1_default_interrupt_handler_timer2
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_VOICE
)paren
(brace
id|snd_gus_voice_t
op_star
id|voice
suffix:semicolon
id|voice
op_assign
op_amp
id|gus-&gt;gf1.voices
(braket
id|what
op_amp
l_int|0xffff
)braket
suffix:semicolon
id|voice-&gt;handler_wave
op_assign
id|voice-&gt;handler_volume
op_assign
id|snd_gf1_default_interrupt_handler_wave_and_volume
suffix:semicolon
id|voice-&gt;handler_effect
op_assign
l_int|NULL
suffix:semicolon
id|voice-&gt;volume_change
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_DMA_WRITE
)paren
id|gus-&gt;gf1.interrupt_handler_dma_write
op_assign
id|snd_gf1_default_interrupt_handler_dma_write
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|SNDRV_GF1_HANDLER_DMA_READ
)paren
id|gus-&gt;gf1.interrupt_handler_dma_read
op_assign
id|snd_gf1_default_interrupt_handler_dma_read
suffix:semicolon
)brace
multiline_comment|/*&n;&n; */
DECL|function|snd_gf1_clear_regs
r_static
r_void
id|snd_gf1_clear_regs
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
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
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|inb
c_func
(paren
id|GUSP
c_func
(paren
id|gus
comma
id|IRQSTAT
)paren
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
l_int|0x41
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* DRAM DMA Control Register */
id|snd_gf1_write8
c_func
(paren
id|gus
comma
l_int|0x45
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Timer Control */
id|snd_gf1_write8
c_func
(paren
id|gus
comma
l_int|0x49
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Sampling Control Register */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_look_regs
r_static
r_void
id|snd_gf1_look_regs
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
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
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_look8
c_func
(paren
id|gus
comma
l_int|0x41
)paren
suffix:semicolon
multiline_comment|/* DRAM DMA Control Register */
id|snd_gf1_look8
c_func
(paren
id|gus
comma
l_int|0x49
)paren
suffix:semicolon
multiline_comment|/* Sampling Control Register */
id|inb
c_func
(paren
id|GUSP
c_func
(paren
id|gus
comma
id|IRQSTAT
)paren
)paren
suffix:semicolon
id|snd_gf1_read8
c_func
(paren
id|gus
comma
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* IRQ Source Register */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  put selected GF1 voices to initial stage...&n; */
DECL|function|snd_gf1_smart_stop_voice
r_void
id|snd_gf1_smart_stop_voice
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
r_int
id|voice
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
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_select_voice
c_func
(paren
id|gus
comma
id|voice
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot; -%i- smart stop voice - volume = 0x%x&bslash;n&quot;
comma
id|voice
comma
id|snd_gf1_i_read16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VW_VOLUME
)paren
)paren
suffix:semicolon
macro_line|#endif
id|snd_gf1_ctrl_stop
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_ADDRESS_CONTROL
)paren
suffix:semicolon
id|snd_gf1_ctrl_stop
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_CONTROL
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_stop_voice
r_void
id|snd_gf1_stop_voice
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
r_int
id|voice
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
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_select_voice
c_func
(paren
id|gus
comma
id|voice
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot; -%i- stop voice - volume = 0x%x&bslash;n&quot;
comma
id|voice
comma
id|snd_gf1_i_read16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VW_VOLUME
)paren
)paren
suffix:semicolon
macro_line|#endif
id|snd_gf1_ctrl_stop
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_ADDRESS_CONTROL
)paren
suffix:semicolon
id|snd_gf1_ctrl_stop
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_ACCUMULATOR
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#if 0
id|snd_gf1_lfo_shutdown
c_func
(paren
id|gus
comma
id|voice
comma
id|ULTRA_LFO_VIBRATO
)paren
suffix:semicolon
id|snd_gf1_lfo_shutdown
c_func
(paren
id|gus
comma
id|voice
comma
id|ULTRA_LFO_TREMOLO
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|snd_gf1_clear_voices
r_void
id|snd_gf1_clear_voices
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
r_int
id|v_min
comma
r_int
r_int
id|v_max
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|daddr
suffix:semicolon
r_int
r_int
id|i
comma
id|w_16
suffix:semicolon
id|daddr
op_assign
id|gus-&gt;gf1.default_voice_address
op_lshift
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|v_min
suffix:semicolon
id|i
op_le
id|v_max
suffix:semicolon
id|i
op_increment
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|gus-&gt;gf1.syn_voices
)paren
id|gus-&gt;gf1.syn_voices
(braket
id|i
)braket
dot
id|flags
op_assign
op_complement
id|VFLG_DYNAMIC
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_select_voice
c_func
(paren
id|gus
comma
id|i
)paren
suffix:semicolon
id|snd_gf1_ctrl_stop
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_ADDRESS_CONTROL
)paren
suffix:semicolon
multiline_comment|/* Voice Control Register = voice stop */
id|snd_gf1_ctrl_stop
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_CONTROL
)paren
suffix:semicolon
multiline_comment|/* Volume Ramp Control Register = ramp off */
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_MODE
comma
id|gus-&gt;gf1.memory
ques
c_cond
l_int|0x02
suffix:colon
l_int|0x82
)paren
suffix:semicolon
multiline_comment|/* Deactivate voice */
id|w_16
op_assign
id|snd_gf1_read8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_ADDRESS_CONTROL
)paren
op_amp
l_int|0x04
suffix:semicolon
id|snd_gf1_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VW_FREQUENCY
comma
l_int|0x400
)paren
suffix:semicolon
id|snd_gf1_write_addr
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VA_START
comma
id|daddr
comma
id|w_16
)paren
suffix:semicolon
id|snd_gf1_write_addr
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VA_END
comma
id|daddr
comma
id|w_16
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_START
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_END
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_RATE
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VW_VOLUME
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_write_addr
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VA_CURRENT
comma
id|daddr
comma
id|w_16
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_PAN
comma
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
(brace
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_ACCUMULATOR
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VW_EFFECT_VOLUME
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VW_EFFECT_VOLUME_FINAL
comma
l_int|0
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#if 0
id|snd_gf1_lfo_shutdown
c_func
(paren
id|gus
comma
id|i
comma
id|ULTRA_LFO_VIBRATO
)paren
suffix:semicolon
id|snd_gf1_lfo_shutdown
c_func
(paren
id|gus
comma
id|i
comma
id|ULTRA_LFO_TREMOLO
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|snd_gf1_stop_voices
r_void
id|snd_gf1_stop_voices
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
r_int
id|v_min
comma
r_int
r_int
id|v_max
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
comma
id|ramp_ok
suffix:semicolon
r_int
r_int
id|ramp_end
suffix:semicolon
r_int
id|time
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* this can&squot;t be done in interrupt */
r_for
c_loop
(paren
id|i
op_assign
id|v_min
comma
id|ramp_ok
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|v_max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_select_voice
c_func
(paren
id|gus
comma
id|i
)paren
suffix:semicolon
id|ramp_end
op_assign
id|snd_gf1_read16
c_func
(paren
id|gus
comma
l_int|9
)paren
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|ramp_end
OG
id|SNDRV_GF1_MIN_OFFSET
)paren
(brace
id|ramp_ok
op_increment
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_RATE
comma
l_int|20
)paren
suffix:semicolon
multiline_comment|/* ramp rate */
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_START
comma
id|SNDRV_GF1_MIN_OFFSET
)paren
suffix:semicolon
multiline_comment|/* ramp start */
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_END
comma
id|ramp_end
)paren
suffix:semicolon
multiline_comment|/* ramp end */
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_CONTROL
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* ramp down */
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
(brace
id|snd_gf1_delay
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VB_VOLUME_CONTROL
comma
l_int|0x40
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|time
op_assign
id|HZ
op_div
l_int|20
suffix:semicolon
r_while
c_loop
(paren
id|time
OG
l_int|0
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|time
op_assign
id|schedule_timeout
c_func
(paren
id|time
)paren
suffix:semicolon
)brace
)brace
id|snd_gf1_clear_voices
c_func
(paren
id|gus
comma
id|v_min
comma
id|v_max
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_alloc_voice_use
r_static
r_void
id|snd_gf1_alloc_voice_use
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
id|snd_gus_voice_t
op_star
id|pvoice
comma
r_int
id|type
comma
r_int
id|client
comma
r_int
id|port
)paren
(brace
id|pvoice-&gt;use
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
id|SNDRV_GF1_VOICE_TYPE_PCM
suffix:colon
id|gus-&gt;gf1.pcm_alloc_voices
op_increment
suffix:semicolon
id|pvoice-&gt;pcm
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_GF1_VOICE_TYPE_SYNTH
suffix:colon
id|pvoice-&gt;synth
op_assign
l_int|1
suffix:semicolon
id|pvoice-&gt;client
op_assign
id|client
suffix:semicolon
id|pvoice-&gt;port
op_assign
id|port
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_GF1_VOICE_TYPE_MIDI
suffix:colon
id|pvoice-&gt;midi
op_assign
l_int|1
suffix:semicolon
id|pvoice-&gt;client
op_assign
id|client
suffix:semicolon
id|pvoice-&gt;port
op_assign
id|port
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|snd_gf1_alloc_voice
id|snd_gus_voice_t
op_star
id|snd_gf1_alloc_voice
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
id|type
comma
r_int
id|client
comma
r_int
id|port
)paren
(brace
id|snd_gus_voice_t
op_star
id|pvoice
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|SNDRV_GF1_VOICE_TYPE_PCM
)paren
(brace
r_if
c_cond
(paren
id|gus-&gt;gf1.pcm_alloc_voices
op_ge
id|gus-&gt;gf1.pcm_channels
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|32
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|pvoice
op_assign
op_amp
id|gus-&gt;gf1.voices
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pvoice-&gt;use
)paren
(brace
id|snd_gf1_alloc_voice_use
c_func
(paren
id|gus
comma
id|pvoice
comma
id|type
comma
id|client
comma
id|port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
r_return
id|pvoice
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|32
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|pvoice
op_assign
op_amp
id|gus-&gt;gf1.voices
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pvoice-&gt;midi
op_logical_and
op_logical_neg
id|pvoice-&gt;client
)paren
(brace
id|snd_gf1_clear_voices
c_func
(paren
id|gus
comma
id|pvoice-&gt;number
comma
id|pvoice-&gt;number
)paren
suffix:semicolon
id|snd_gf1_alloc_voice_use
c_func
(paren
id|gus
comma
id|pvoice
comma
id|type
comma
id|client
comma
id|port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
r_return
id|pvoice
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_gf1_free_voice
r_void
id|snd_gf1_free_voice
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
id|snd_gus_voice_t
op_star
id|voice
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_gus_voice_t
op_star
id|voice
)paren
suffix:semicolon
r_void
op_star
id|private_data
suffix:semicolon
r_if
c_cond
(paren
id|voice
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|voice-&gt;use
)paren
r_return
suffix:semicolon
id|snd_gf1_set_default_handlers
c_func
(paren
id|gus
comma
id|SNDRV_GF1_HANDLER_VOICE
op_or
id|voice-&gt;number
)paren
suffix:semicolon
id|snd_gf1_clear_voices
c_func
(paren
id|gus
comma
id|voice-&gt;number
comma
id|voice-&gt;number
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
id|private_free
op_assign
id|voice-&gt;private_free
suffix:semicolon
id|private_data
op_assign
id|voice-&gt;private_data
suffix:semicolon
id|voice-&gt;private_free
op_assign
l_int|NULL
suffix:semicolon
id|voice-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|voice-&gt;pcm
)paren
id|gus-&gt;gf1.pcm_alloc_voices
op_decrement
suffix:semicolon
id|voice-&gt;use
op_assign
id|voice-&gt;pcm
op_assign
l_int|0
suffix:semicolon
id|voice-&gt;sample_ops
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;voice_alloc
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|private_free
)paren
id|private_free
c_func
(paren
id|voice
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  call this function only by start of driver&n; */
DECL|function|snd_gf1_start
r_int
id|snd_gf1_start
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* reset GF1 */
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* disable IRQ &amp; DAC */
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_JOYSTICK_DAC_LEVEL
comma
id|gus-&gt;joystick_dac
)paren
suffix:semicolon
id|snd_gf1_set_default_handlers
c_func
(paren
id|gus
comma
id|SNDRV_GF1_HANDLER_ALL
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gus-&gt;gf1.voices
(braket
id|i
)braket
dot
id|number
op_assign
id|i
suffix:semicolon
id|snd_gf1_set_default_handlers
c_func
(paren
id|gus
comma
id|SNDRV_GF1_HANDLER_VOICE
op_or
id|i
)paren
suffix:semicolon
)brace
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* huh.. this cleanup took me some time... */
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
(brace
multiline_comment|/* enhanced mode !!!! */
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_GLOBAL_MODE
comma
id|snd_gf1_i_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_GLOBAL_MODE
)paren
op_or
l_int|0x01
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_MEMORY_CONTROL
comma
l_int|0x01
)paren
suffix:semicolon
)brace
id|snd_gf1_clear_regs
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_select_active_voices
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_delay
c_func
(paren
id|gus
)paren
suffix:semicolon
id|gus-&gt;gf1.default_voice_address
op_assign
id|gus-&gt;gf1.memory
OG
l_int|0
ques
c_cond
l_int|0
suffix:colon
l_int|512
op_minus
l_int|8
suffix:semicolon
multiline_comment|/* initialize LFOs &amp; clear LFOs memory */
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
op_logical_and
id|gus-&gt;gf1.memory
)paren
(brace
id|gus-&gt;gf1.hw_lfo
op_assign
l_int|1
suffix:semicolon
id|gus-&gt;gf1.default_voice_address
op_add_assign
l_int|1024
suffix:semicolon
)brace
r_else
(brace
id|gus-&gt;gf1.sw_lfo
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#if 0
id|snd_gf1_lfo_init
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|gus-&gt;gf1.memory
OG
l_int|0
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|snd_gf1_poke
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.default_voice_address
op_plus
id|i
comma
l_int|0
)paren
suffix:semicolon
id|snd_gf1_clear_regs
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_clear_voices
c_func
(paren
id|gus
comma
l_int|0
comma
l_int|31
)paren
suffix:semicolon
id|snd_gf1_look_regs
c_func
(paren
id|gus
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Reset Register = IRQ enable, DAC enable */
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Reset Register = IRQ enable, DAC enable */
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
(brace
multiline_comment|/* enhanced mode !!!! */
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_GLOBAL_MODE
comma
id|snd_gf1_i_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_GLOBAL_MODE
)paren
op_or
l_int|0x01
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_MEMORY_CONTROL
comma
l_int|0x01
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|snd_gf1_i_read8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_VOICES_IRQ
)paren
op_amp
l_int|0xc0
)paren
op_ne
l_int|0xc0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|gus-&gt;gf1.active_voice
op_assign
l_int|0
comma
id|GUSP
c_func
(paren
id|gus
comma
id|GF1PAGE
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|gus-&gt;mix_cntrl_reg
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXCNTRLREG
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_timers_init
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_look_regs
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_mem_init
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_mem_proc_init
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
id|snd_gus_irq_profile_init
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
r_if
c_cond
(paren
id|gus-&gt;pnp_flag
)paren
(brace
r_if
c_cond
(paren
id|gus-&gt;chip.playback_fifo_size
OG
l_int|0
)paren
id|snd_gf1_i_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GW_FIFO_RECORD_BASE_ADDR
comma
id|gus-&gt;chip.playback_fifo_block-&gt;ptr
op_rshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;chip.record_fifo_size
OG
l_int|0
)paren
id|snd_gf1_i_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GW_FIFO_PLAY_BASE_ADDR
comma
id|gus-&gt;chip.record_fifo_block-&gt;ptr
op_rshift
l_int|8
)paren
suffix:semicolon
id|snd_gf1_i_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GW_FIFO_SIZE
comma
id|gus-&gt;chip.interwave_fifo_reg
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  call this function only by shutdown of driver&n; */
DECL|function|snd_gf1_stop
r_int
id|snd_gf1_stop
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_SOUND_BLASTER_CONTROL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* stop all timers */
id|snd_gf1_stop_voices
c_func
(paren
id|gus
comma
l_int|0
comma
l_int|31
)paren
suffix:semicolon
multiline_comment|/* stop all voices */
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* disable IRQ &amp; DAC */
id|snd_gf1_timers_done
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
id|snd_gus_irq_profile_done
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#endif
id|snd_gf1_mem_proc_done
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_gf1_mem_done
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#if 0
id|snd_gf1_lfo_done
c_func
(paren
id|gus
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof