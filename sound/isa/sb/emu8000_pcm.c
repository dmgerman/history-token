multiline_comment|/*&n; * pcm emulation on emu8000 wavetable&n; *&n; *  Copyright (C) 2002 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;emu8000_local.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t emu8000_t
multiline_comment|/*&n; * define the following if you want to use this pcm with non-interleaved mode&n; */
multiline_comment|/* #define USE_NONINTERLEAVE */
multiline_comment|/* NOTE: for using the non-interleaved mode with alsa-lib, you have to set&n; * mmap_emulation flag to 1 in your .asoundrc, such like&n; *&n; *&t;pcm.emu8k {&n; *&t;&t;type plug&n; *&t;&t;slave.pcm {&n; *&t;&t;&t;type hw&n; *&t;&t;&t;card 0&n; *&t;&t;&t;device 1&n; *&t;&t;&t;mmap_emulation 1&n; *&t;&t;}&n; *&t;}&n; *&n; * besides, for the time being, the non-interleaved mode doesn&squot;t work well on&n; * alsa-lib...&n; */
DECL|typedef|emu8k_pcm_t
r_typedef
r_struct
id|snd_emu8k_pcm
id|emu8k_pcm_t
suffix:semicolon
DECL|struct|snd_emu8k_pcm
r_struct
id|snd_emu8k_pcm
(brace
DECL|member|emu
id|emu8000_t
op_star
id|emu
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|allocated_bytes
r_int
r_int
id|allocated_bytes
suffix:semicolon
DECL|member|block
id|snd_util_memblk_t
op_star
id|block
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
DECL|member|period_size
r_int
r_int
id|period_size
suffix:semicolon
DECL|member|loop_start
r_int
r_int
id|loop_start
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pitch
r_int
r_int
id|pitch
suffix:semicolon
DECL|member|panning
r_int
id|panning
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|last_ptr
r_int
id|last_ptr
suffix:semicolon
DECL|member|period_pos
r_int
id|period_pos
suffix:semicolon
DECL|member|voices
r_int
id|voices
suffix:semicolon
DECL|member|dram_opened
r_int
r_int
id|dram_opened
suffix:colon
l_int|1
suffix:semicolon
DECL|member|running
r_int
r_int
id|running
suffix:colon
l_int|1
suffix:semicolon
DECL|member|timer_running
r_int
r_int
id|timer_running
suffix:colon
l_int|1
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|timer_lock
id|spinlock_t
id|timer_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LOOP_BLANK_SIZE
mdefine_line|#define LOOP_BLANK_SIZE&t;&t;8
multiline_comment|/*&n; * open up channels for the simultaneous data transfer and playback&n; */
r_static
r_int
DECL|function|emu8k_open_dram_for_pcm
id|emu8k_open_dram_for_pcm
c_func
(paren
id|emu8000_t
op_star
id|emu
comma
r_int
id|channels
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* reserve up to 2 voices for playback */
id|snd_emux_lock_voice
c_func
(paren
id|emu-&gt;emu
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channels
OG
l_int|1
)paren
id|snd_emux_lock_voice
c_func
(paren
id|emu-&gt;emu
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* reserve 28 voices for loading */
r_for
c_loop
(paren
id|i
op_assign
id|channels
op_plus
l_int|1
suffix:semicolon
id|i
OL
id|EMU8000_DRAM_VOICES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|mode
op_assign
id|EMU8000_RAM_WRITE
suffix:semicolon
id|snd_emux_lock_voice
c_func
(paren
id|emu-&gt;emu
comma
id|i
)paren
suffix:semicolon
macro_line|#ifndef USE_NONINTERLEAVE
r_if
c_cond
(paren
id|channels
OG
l_int|1
op_logical_and
(paren
id|i
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
id|mode
op_or_assign
id|EMU8000_RAM_RIGHT
suffix:semicolon
macro_line|#endif
id|snd_emu8000_dma_chan
c_func
(paren
id|emu
comma
id|i
comma
id|mode
)paren
suffix:semicolon
)brace
multiline_comment|/* assign voice 31 and 32 to ROM */
id|EMU8000_VTFT_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0
)paren
suffix:semicolon
id|EMU8000_PSST_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0x1d8
)paren
suffix:semicolon
id|EMU8000_CSL_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0x1e0
)paren
suffix:semicolon
id|EMU8000_CCCA_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0x1d8
)paren
suffix:semicolon
id|EMU8000_VTFT_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0
)paren
suffix:semicolon
id|EMU8000_PSST_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0x1d8
)paren
suffix:semicolon
id|EMU8000_CSL_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0x1e0
)paren
suffix:semicolon
id|EMU8000_CCCA_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0x1d8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; */
r_static
r_void
DECL|function|snd_emu8000_write_wait
id|snd_emu8000_write_wait
c_func
(paren
id|emu8000_t
op_star
id|emu
)paren
(brace
r_while
c_loop
(paren
(paren
id|EMU8000_SMALW_READ
c_func
(paren
id|emu
)paren
op_amp
l_int|0x80000000
)paren
op_ne
l_int|0
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * close all channels&n; */
r_static
r_void
DECL|function|emu8k_close_dram
id|emu8k_close_dram
c_func
(paren
id|emu8000_t
op_star
id|emu
)paren
(brace
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|snd_emux_unlock_voice
c_func
(paren
id|emu-&gt;emu
comma
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|EMU8000_DRAM_VOICES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_emu8000_dma_chan
c_func
(paren
id|emu
comma
id|i
comma
id|EMU8000_RAM_CLOSE
)paren
suffix:semicolon
id|snd_emux_unlock_voice
c_func
(paren
id|emu-&gt;emu
comma
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * convert Hz to AWE32 rate offset (see emux/soundfont.c)&n; */
DECL|macro|OFFSET_SAMPLERATE
mdefine_line|#define OFFSET_SAMPLERATE&t;1011119&t;&t;/* base = 44100 */
DECL|macro|SAMPLERATE_RATIO
mdefine_line|#define SAMPLERATE_RATIO&t;4096
DECL|function|calc_rate_offset
r_static
r_int
id|calc_rate_offset
c_func
(paren
r_int
id|hz
)paren
(brace
r_return
id|snd_sf_linear_to_log
c_func
(paren
id|hz
comma
id|OFFSET_SAMPLERATE
comma
id|SAMPLERATE_RATIO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|variable|emu8k_pcm_hw
r_static
id|snd_pcm_hardware_t
id|emu8k_pcm_hw
op_assign
(brace
macro_line|#ifdef USE_NONINTERLEAVE
dot
id|info
op_assign
id|SNDRV_PCM_INFO_NONINTERLEAVED
comma
macro_line|#else
dot
id|info
op_assign
id|SNDRV_PCM_INFO_INTERLEAVED
comma
macro_line|#endif
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
comma
dot
id|rates
op_assign
id|SNDRV_PCM_RATE_CONTINUOUS
op_or
id|SNDRV_PCM_RATE_8000_48000
comma
dot
id|rate_min
op_assign
l_int|4000
comma
dot
id|rate_max
op_assign
l_int|48000
comma
dot
id|channels_min
op_assign
l_int|1
comma
dot
id|channels_max
op_assign
l_int|2
comma
dot
id|buffer_bytes_max
op_assign
(paren
l_int|128
op_star
l_int|1024
)paren
comma
dot
id|period_bytes_min
op_assign
l_int|1024
comma
dot
id|period_bytes_max
op_assign
(paren
l_int|128
op_star
l_int|1024
)paren
comma
dot
id|periods_min
op_assign
l_int|2
comma
dot
id|periods_max
op_assign
l_int|1024
comma
dot
id|fifo_size
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * get the current position at the given channel from CCCA register&n; */
DECL|function|emu8k_get_curpos
r_static
r_inline
r_int
id|emu8k_get_curpos
c_func
(paren
id|emu8k_pcm_t
op_star
id|rec
comma
r_int
id|ch
)paren
(brace
r_int
id|val
op_assign
id|EMU8000_CCCA_READ
c_func
(paren
id|rec-&gt;emu
comma
id|ch
)paren
op_amp
l_int|0xfffffff
suffix:semicolon
id|val
op_sub_assign
id|rec-&gt;loop_start
(braket
id|ch
)braket
op_minus
l_int|1
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * timer interrupt handler&n; * check the current position and update the period if necessary.&n; */
DECL|function|emu8k_pcm_timer_func
r_static
r_void
id|emu8k_pcm_timer_func
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
(paren
id|emu8k_pcm_t
op_star
)paren
id|data
suffix:semicolon
r_int
id|ptr
comma
id|delta
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rec-&gt;timer_lock
)paren
suffix:semicolon
multiline_comment|/* update the current pointer */
id|ptr
op_assign
id|emu8k_get_curpos
c_func
(paren
id|rec
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
OL
id|rec-&gt;last_ptr
)paren
id|delta
op_assign
id|ptr
op_plus
id|rec-&gt;buf_size
op_minus
id|rec-&gt;last_ptr
suffix:semicolon
r_else
id|delta
op_assign
id|ptr
op_minus
id|rec-&gt;last_ptr
suffix:semicolon
id|rec-&gt;period_pos
op_add_assign
id|delta
suffix:semicolon
id|rec-&gt;last_ptr
op_assign
id|ptr
suffix:semicolon
multiline_comment|/* reprogram timer */
id|rec-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rec-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* update period */
r_if
c_cond
(paren
id|rec-&gt;period_pos
op_ge
id|rec-&gt;period_size
)paren
(brace
id|rec-&gt;period_pos
op_mod_assign
id|rec-&gt;period_size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rec-&gt;timer_lock
)paren
suffix:semicolon
id|snd_pcm_period_elapsed
c_func
(paren
id|rec-&gt;substream
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|rec-&gt;timer_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * open pcm&n; * creating an instance here&n; */
DECL|function|emu8k_pcm_open
r_static
r_int
id|emu8k_pcm_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|emu8000_t
op_star
id|emu
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|subs
)paren
suffix:semicolon
id|emu8k_pcm_t
op_star
id|rec
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|subs-&gt;runtime
suffix:semicolon
id|rec
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rec
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rec
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rec-&gt;emu
op_assign
id|emu
suffix:semicolon
id|rec-&gt;substream
op_assign
id|subs
suffix:semicolon
id|runtime-&gt;private_data
op_assign
id|rec
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|rec-&gt;timer_lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|rec-&gt;timer
)paren
suffix:semicolon
id|rec-&gt;timer.function
op_assign
id|emu8k_pcm_timer_func
suffix:semicolon
id|rec-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|rec
suffix:semicolon
id|runtime-&gt;hw
op_assign
id|emu8k_pcm_hw
suffix:semicolon
id|runtime-&gt;hw.buffer_bytes_max
op_assign
id|emu-&gt;mem_size
op_minus
id|LOOP_BLANK_SIZE
op_star
l_int|3
suffix:semicolon
id|runtime-&gt;hw.period_bytes_max
op_assign
id|runtime-&gt;hw.buffer_bytes_max
op_div
l_int|2
suffix:semicolon
multiline_comment|/* use timer to update periods.. (specified in msec) */
id|snd_pcm_hw_constraint_minmax
c_func
(paren
id|runtime
comma
id|SNDRV_PCM_HW_PARAM_PERIOD_TIME
comma
(paren
l_int|1000000
op_plus
id|HZ
op_minus
l_int|1
)paren
op_div
id|HZ
comma
id|UINT_MAX
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu8k_pcm_close
r_static
r_int
id|emu8k_pcm_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|rec
)paren
id|kfree
c_func
(paren
id|rec
)paren
suffix:semicolon
id|subs-&gt;runtime-&gt;private_data
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * calculate pitch target&n; */
DECL|function|calc_pitch_target
r_static
r_int
id|calc_pitch_target
c_func
(paren
r_int
id|pitch
)paren
(brace
r_int
id|ptarget
op_assign
l_int|1
op_lshift
(paren
id|pitch
op_rshift
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pitch
op_amp
l_int|0x800
)paren
id|ptarget
op_add_assign
(paren
id|ptarget
op_star
l_int|0x102e
)paren
op_div
l_int|0x2710
suffix:semicolon
r_if
c_cond
(paren
id|pitch
op_amp
l_int|0x400
)paren
id|ptarget
op_add_assign
(paren
id|ptarget
op_star
l_int|0x764
)paren
op_div
l_int|0x2710
suffix:semicolon
r_if
c_cond
(paren
id|pitch
op_amp
l_int|0x200
)paren
id|ptarget
op_add_assign
(paren
id|ptarget
op_star
l_int|0x389
)paren
op_div
l_int|0x2710
suffix:semicolon
id|ptarget
op_add_assign
(paren
id|ptarget
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptarget
OG
l_int|0xffff
)paren
id|ptarget
op_assign
l_int|0xffff
suffix:semicolon
r_return
id|ptarget
suffix:semicolon
)brace
multiline_comment|/*&n; * set up the voice&n; */
DECL|function|setup_voice
r_static
r_void
id|setup_voice
c_func
(paren
id|emu8k_pcm_t
op_star
id|rec
comma
r_int
id|ch
)paren
(brace
id|emu8000_t
op_star
id|hw
op_assign
id|rec-&gt;emu
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
multiline_comment|/* channel to be silent and idle */
id|EMU8000_DCYSUSV_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x0080
)paren
suffix:semicolon
id|EMU8000_VTFT_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x0000FFFF
)paren
suffix:semicolon
id|EMU8000_CVCF_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x0000FFFF
)paren
suffix:semicolon
id|EMU8000_PTRX_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
id|EMU8000_CPF_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* pitch offset */
id|EMU8000_IP_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
id|rec-&gt;pitch
)paren
suffix:semicolon
multiline_comment|/* set envelope parameters */
id|EMU8000_ENVVAL_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x8000
)paren
suffix:semicolon
id|EMU8000_ATKHLD_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x7f7f
)paren
suffix:semicolon
id|EMU8000_DCYSUS_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x7f7f
)paren
suffix:semicolon
id|EMU8000_ENVVOL_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x8000
)paren
suffix:semicolon
id|EMU8000_ATKHLDV_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x7f7f
)paren
suffix:semicolon
multiline_comment|/* decay/sustain parameter for volume envelope is used&n;&t;   for triggerg the voice */
multiline_comment|/* modulation envelope heights */
id|EMU8000_PEFE_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* lfo1/2 delay */
id|EMU8000_LFO1VAL_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x8000
)paren
suffix:semicolon
id|EMU8000_LFO2VAL_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x8000
)paren
suffix:semicolon
multiline_comment|/* lfo1 pitch &amp; cutoff shift */
id|EMU8000_FMMOD_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* lfo1 volume &amp; freq */
id|EMU8000_TREMFRQ_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* lfo2 pitch &amp; freq */
id|EMU8000_FM2FRQ2_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* pan &amp; loop start */
id|temp
op_assign
id|rec-&gt;panning
(braket
id|ch
)braket
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_lshift
l_int|24
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|rec-&gt;loop_start
(braket
id|ch
)braket
op_minus
l_int|1
)paren
suffix:semicolon
id|EMU8000_PSST_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* chorus &amp; loop end (chorus 8bit, MSB) */
id|temp
op_assign
l_int|0
suffix:semicolon
singleline_comment|// chorus
id|temp
op_assign
(paren
id|temp
op_lshift
l_int|24
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|rec-&gt;loop_start
(braket
id|ch
)braket
op_plus
id|rec-&gt;buf_size
op_minus
l_int|1
)paren
suffix:semicolon
id|EMU8000_CSL_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* Q &amp; current address (Q 4bit value, MSB) */
id|temp
op_assign
l_int|0
suffix:semicolon
singleline_comment|// filterQ
id|temp
op_assign
(paren
id|temp
op_lshift
l_int|28
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|rec-&gt;loop_start
(braket
id|ch
)braket
op_minus
l_int|1
)paren
suffix:semicolon
id|EMU8000_CCCA_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* clear unknown registers */
id|EMU8000_00A0_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
id|EMU8000_0080_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * trigger the voice&n; */
DECL|function|start_voice
r_static
r_void
id|start_voice
c_func
(paren
id|emu8k_pcm_t
op_star
id|rec
comma
r_int
id|ch
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu8000_t
op_star
id|hw
op_assign
id|rec-&gt;emu
suffix:semicolon
r_int
r_int
id|temp
comma
id|aux
suffix:semicolon
r_int
id|pt
op_assign
id|calc_pitch_target
c_func
(paren
id|rec-&gt;pitch
)paren
suffix:semicolon
multiline_comment|/* cutoff and volume */
id|EMU8000_IFATN_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0xff00
)paren
suffix:semicolon
id|EMU8000_VTFT_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0xffff
)paren
suffix:semicolon
id|EMU8000_CVCF_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* trigger envelope */
id|EMU8000_DCYSUSV_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x7f7f
)paren
suffix:semicolon
multiline_comment|/* set reverb and pitch target */
id|temp
op_assign
l_int|0
suffix:semicolon
singleline_comment|// reverb
r_if
c_cond
(paren
id|rec-&gt;panning
(braket
id|ch
)braket
op_eq
l_int|0
)paren
id|aux
op_assign
l_int|0xff
suffix:semicolon
r_else
id|aux
op_assign
(paren
op_minus
id|rec-&gt;panning
(braket
id|ch
)braket
)paren
op_amp
l_int|0xff
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_lshift
l_int|8
)paren
op_or
(paren
id|pt
op_lshift
l_int|16
)paren
op_or
id|aux
suffix:semicolon
id|EMU8000_PTRX_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
id|temp
)paren
suffix:semicolon
id|EMU8000_CPF_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
id|pt
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* start timer */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rec-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rec-&gt;timer_running
)paren
(brace
id|rec-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rec-&gt;timer
)paren
suffix:semicolon
id|rec-&gt;timer_running
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rec-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * stop the voice immediately&n; */
DECL|function|stop_voice
r_static
r_void
id|stop_voice
c_func
(paren
id|emu8k_pcm_t
op_star
id|rec
comma
r_int
id|ch
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|emu8000_t
op_star
id|hw
op_assign
id|rec-&gt;emu
suffix:semicolon
id|EMU8000_DCYSUSV_WRITE
c_func
(paren
id|hw
comma
id|ch
comma
l_int|0x807F
)paren
suffix:semicolon
multiline_comment|/* stop timer */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rec-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;timer_running
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|rec-&gt;timer
)paren
suffix:semicolon
id|rec-&gt;timer_running
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rec-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|emu8k_pcm_trigger
r_static
r_int
id|emu8k_pcm_trigger
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
id|cmd
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_PCM_TRIGGER_START
suffix:colon
r_for
c_loop
(paren
id|ch
op_assign
l_int|0
suffix:semicolon
id|ch
OL
id|rec-&gt;voices
suffix:semicolon
id|ch
op_increment
)paren
id|start_voice
c_func
(paren
id|rec
comma
id|ch
)paren
suffix:semicolon
id|rec-&gt;running
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_STOP
suffix:colon
id|rec-&gt;running
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ch
op_assign
l_int|0
suffix:semicolon
id|ch
OL
id|rec-&gt;voices
suffix:semicolon
id|ch
op_increment
)paren
id|stop_voice
c_func
(paren
id|rec
comma
id|ch
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * copy / silence ops&n; */
multiline_comment|/*&n; * this macro should be inserted in the copy/silence loops&n; * to reduce the latency.  without this, the system will hang up&n; * during the whole loop.&n; */
DECL|macro|CHECK_SCHEDULER
mdefine_line|#define CHECK_SCHEDULER() &bslash;&n;do { &bslash;&n;&t;if (need_resched()) {&bslash;&n;&t;&t;if (current-&gt;state != TASK_RUNNING)&bslash;&n;&t;&t;&t;set_current_state(TASK_RUNNING);&bslash;&n;&t;&t;schedule();&bslash;&n;&t;&t;if (signal_pending(current))&bslash;&n;&t;&t;&t;return -EAGAIN;&bslash;&n;&t;}&bslash;&n;} while (0)
macro_line|#ifdef USE_NONINTERLEAVE
multiline_comment|/* copy one channel block */
DECL|function|emu8k_transfer_block
r_static
r_int
id|emu8k_transfer_block
c_func
(paren
id|emu8000_t
op_star
id|emu
comma
r_int
id|offset
comma
r_int
r_int
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|EMU8000_SMALW_WRITE
c_func
(paren
id|emu
comma
id|offset
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
r_int
id|sval
suffix:semicolon
id|CHECK_SCHEDULER
c_func
(paren
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|sval
comma
id|buf
)paren
suffix:semicolon
id|EMU8000_SMLD_WRITE
c_func
(paren
id|emu
comma
id|sval
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu8k_pcm_copy
r_static
r_int
id|emu8k_pcm_copy
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
id|voice
comma
id|snd_pcm_uframes_t
id|pos
comma
r_void
op_star
id|src
comma
id|snd_pcm_uframes_t
id|count
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
id|emu8000_t
op_star
id|emu
op_assign
id|rec-&gt;emu
suffix:semicolon
id|snd_emu8000_write_wait
c_func
(paren
id|emu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|voice
op_eq
op_minus
l_int|1
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|src
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
id|count
op_div_assign
id|rec-&gt;voices
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
id|rec-&gt;voices
suffix:semicolon
id|i
op_increment
)paren
(brace
id|err
op_assign
id|emu8k_transfer_block
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
id|i
)braket
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|buf
op_add_assign
id|count
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
id|emu8k_transfer_block
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
id|voice
)braket
comma
id|src
comma
id|count
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* make a channel block silence */
DECL|function|emu8k_silence_block
r_static
r_int
id|emu8k_silence_block
c_func
(paren
id|emu8000_t
op_star
id|emu
comma
r_int
id|offset
comma
r_int
id|count
)paren
(brace
id|EMU8000_SMALW_WRITE
c_func
(paren
id|emu
comma
id|offset
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|CHECK_SCHEDULER
c_func
(paren
)paren
suffix:semicolon
id|EMU8000_SMLD_WRITE
c_func
(paren
id|emu
comma
l_int|0
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu8k_pcm_silence
r_static
r_int
id|emu8k_pcm_silence
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
id|voice
comma
id|snd_pcm_uframes_t
id|pos
comma
id|snd_pcm_uframes_t
id|count
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
id|emu8000_t
op_star
id|emu
op_assign
id|rec-&gt;emu
suffix:semicolon
id|snd_emu8000_write_wait
c_func
(paren
id|emu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|voice
op_eq
op_minus
l_int|1
op_logical_and
id|rec-&gt;voices
op_eq
l_int|1
)paren
id|voice
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|voice
op_eq
op_minus
l_int|1
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|emu8k_silence_block
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
l_int|0
)braket
comma
id|count
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|emu8k_silence_block
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
l_int|1
)braket
comma
id|count
op_div
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|emu8k_silence_block
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
id|voice
)braket
comma
id|count
)paren
suffix:semicolon
)brace
)brace
macro_line|#else /* interleave */
multiline_comment|/*&n; * copy the interleaved data can be done easily by using&n; * DMA &quot;left&quot; and &quot;right&quot; channels on emu8k engine.&n; */
DECL|function|emu8k_pcm_copy
r_static
r_int
id|emu8k_pcm_copy
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
id|voice
comma
id|snd_pcm_uframes_t
id|pos
comma
r_void
op_star
id|src
comma
id|snd_pcm_uframes_t
id|count
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
id|emu8000_t
op_star
id|emu
op_assign
id|rec-&gt;emu
suffix:semicolon
r_int
r_int
op_star
id|buf
op_assign
id|src
suffix:semicolon
id|snd_emu8000_write_wait
c_func
(paren
id|emu
)paren
suffix:semicolon
id|EMU8000_SMALW_WRITE
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
id|EMU8000_SMARW_WRITE
c_func
(paren
id|emu
comma
id|pos
op_plus
id|rec-&gt;loop_start
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
r_int
r_int
id|sval
suffix:semicolon
id|CHECK_SCHEDULER
c_func
(paren
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|sval
comma
id|buf
)paren
suffix:semicolon
id|EMU8000_SMLD_WRITE
c_func
(paren
id|emu
comma
id|sval
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
(brace
id|CHECK_SCHEDULER
c_func
(paren
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|sval
comma
id|buf
)paren
suffix:semicolon
id|EMU8000_SMRD_WRITE
c_func
(paren
id|emu
comma
id|sval
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu8k_pcm_silence
r_static
r_int
id|emu8k_pcm_silence
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
id|voice
comma
id|snd_pcm_uframes_t
id|pos
comma
id|snd_pcm_uframes_t
id|count
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
id|emu8000_t
op_star
id|emu
op_assign
id|rec-&gt;emu
suffix:semicolon
id|snd_emu8000_write_wait
c_func
(paren
id|emu
)paren
suffix:semicolon
id|EMU8000_SMALW_WRITE
c_func
(paren
id|emu
comma
id|rec-&gt;loop_start
(braket
l_int|0
)braket
op_plus
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
id|EMU8000_SMARW_WRITE
c_func
(paren
id|emu
comma
id|rec-&gt;loop_start
(braket
l_int|1
)braket
op_plus
id|pos
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
id|CHECK_SCHEDULER
c_func
(paren
)paren
suffix:semicolon
id|EMU8000_SMLD_WRITE
c_func
(paren
id|emu
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
(brace
id|CHECK_SCHEDULER
c_func
(paren
)paren
suffix:semicolon
id|EMU8000_SMRD_WRITE
c_func
(paren
id|emu
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * allocate a memory block&n; */
DECL|function|emu8k_pcm_hw_params
r_static
r_int
id|emu8k_pcm_hw_params
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
id|snd_pcm_hw_params_t
op_star
id|hw_params
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;block
)paren
(brace
multiline_comment|/* reallocation - release the old block */
id|snd_util_mem_free
c_func
(paren
id|rec-&gt;emu-&gt;memhdr
comma
id|rec-&gt;block
)paren
suffix:semicolon
id|rec-&gt;block
op_assign
l_int|NULL
suffix:semicolon
)brace
id|rec-&gt;allocated_bytes
op_assign
id|params_buffer_bytes
c_func
(paren
id|hw_params
)paren
op_plus
id|LOOP_BLANK_SIZE
op_star
l_int|4
suffix:semicolon
id|rec-&gt;block
op_assign
id|snd_util_mem_alloc
c_func
(paren
id|rec-&gt;emu-&gt;memhdr
comma
id|rec-&gt;allocated_bytes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rec-&gt;block
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rec-&gt;offset
op_assign
id|EMU8000_DRAM_OFFSET
op_plus
(paren
id|rec-&gt;block-&gt;offset
op_rshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* in word */
multiline_comment|/* at least dma_bytes must be set for non-interleaved mode */
id|subs-&gt;dma_bytes
op_assign
id|params_buffer_bytes
c_func
(paren
id|hw_params
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * free the memory block&n; */
DECL|function|emu8k_pcm_hw_free
r_static
r_int
id|emu8k_pcm_hw_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;block
)paren
(brace
r_int
id|ch
suffix:semicolon
r_for
c_loop
(paren
id|ch
op_assign
l_int|0
suffix:semicolon
id|ch
OL
id|rec-&gt;voices
suffix:semicolon
id|ch
op_increment
)paren
id|stop_voice
c_func
(paren
id|rec
comma
id|ch
)paren
suffix:semicolon
singleline_comment|// to be sure
r_if
c_cond
(paren
id|rec-&gt;dram_opened
)paren
id|emu8k_close_dram
c_func
(paren
id|rec-&gt;emu
)paren
suffix:semicolon
id|snd_util_mem_free
c_func
(paren
id|rec-&gt;emu-&gt;memhdr
comma
id|rec-&gt;block
)paren
suffix:semicolon
id|rec-&gt;block
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|emu8k_pcm_prepare
r_static
r_int
id|emu8k_pcm_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
id|rec-&gt;pitch
op_assign
l_int|0xe000
op_plus
id|calc_rate_offset
c_func
(paren
id|subs-&gt;runtime-&gt;rate
)paren
suffix:semicolon
id|rec-&gt;last_ptr
op_assign
l_int|0
suffix:semicolon
id|rec-&gt;period_pos
op_assign
l_int|0
suffix:semicolon
id|rec-&gt;buf_size
op_assign
id|subs-&gt;runtime-&gt;buffer_size
suffix:semicolon
id|rec-&gt;period_size
op_assign
id|subs-&gt;runtime-&gt;period_size
suffix:semicolon
id|rec-&gt;voices
op_assign
id|subs-&gt;runtime-&gt;channels
suffix:semicolon
id|rec-&gt;loop_start
(braket
l_int|0
)braket
op_assign
id|rec-&gt;offset
op_plus
id|LOOP_BLANK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
id|rec-&gt;loop_start
(braket
l_int|1
)braket
op_assign
id|rec-&gt;loop_start
(braket
l_int|0
)braket
op_plus
id|rec-&gt;buf_size
op_plus
id|LOOP_BLANK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
(brace
id|rec-&gt;panning
(braket
l_int|0
)braket
op_assign
l_int|0xff
suffix:semicolon
id|rec-&gt;panning
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
)brace
r_else
id|rec-&gt;panning
(braket
l_int|0
)braket
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rec-&gt;dram_opened
)paren
(brace
r_int
id|err
comma
id|i
comma
id|ch
suffix:semicolon
id|snd_emux_terminate_all
c_func
(paren
id|rec-&gt;emu-&gt;emu
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|emu8k_open_dram_for_pcm
c_func
(paren
id|rec-&gt;emu
comma
id|rec-&gt;voices
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|rec-&gt;dram_opened
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* clear loop blanks */
id|snd_emu8000_write_wait
c_func
(paren
id|rec-&gt;emu
)paren
suffix:semicolon
id|EMU8000_SMALW_WRITE
c_func
(paren
id|rec-&gt;emu
comma
id|rec-&gt;offset
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
id|LOOP_BLANK_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|EMU8000_SMLD_WRITE
c_func
(paren
id|rec-&gt;emu
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ch
op_assign
l_int|0
suffix:semicolon
id|ch
OL
id|rec-&gt;voices
suffix:semicolon
id|ch
op_increment
)paren
(brace
id|EMU8000_SMALW_WRITE
c_func
(paren
id|rec-&gt;emu
comma
id|rec-&gt;loop_start
(braket
id|ch
)braket
op_plus
id|rec-&gt;buf_size
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
id|LOOP_BLANK_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|EMU8000_SMLD_WRITE
c_func
(paren
id|rec-&gt;emu
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|setup_voice
c_func
(paren
id|rec
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;voices
OG
l_int|1
)paren
id|setup_voice
c_func
(paren
id|rec
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu8k_pcm_pointer
r_static
id|snd_pcm_uframes_t
id|emu8k_pcm_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|emu8k_pcm_t
op_star
id|rec
op_assign
id|subs-&gt;runtime-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;running
)paren
r_return
id|emu8k_get_curpos
c_func
(paren
id|rec
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|emu8k_pcm_ops
r_static
id|snd_pcm_ops_t
id|emu8k_pcm_ops
op_assign
(brace
dot
id|open
op_assign
id|emu8k_pcm_open
comma
dot
id|close
op_assign
id|emu8k_pcm_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|emu8k_pcm_hw_params
comma
dot
id|hw_free
op_assign
id|emu8k_pcm_hw_free
comma
dot
id|prepare
op_assign
id|emu8k_pcm_prepare
comma
dot
id|trigger
op_assign
id|emu8k_pcm_trigger
comma
dot
id|pointer
op_assign
id|emu8k_pcm_pointer
comma
dot
id|copy
op_assign
id|emu8k_pcm_copy
comma
dot
id|silence
op_assign
id|emu8k_pcm_silence
comma
)brace
suffix:semicolon
DECL|function|snd_emu8000_pcm_free
r_static
r_void
id|snd_emu8000_pcm_free
c_func
(paren
id|snd_pcm_t
op_star
id|pcm
)paren
(brace
id|emu8000_t
op_star
id|emu
op_assign
id|pcm-&gt;private_data
suffix:semicolon
id|emu-&gt;pcm
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_emu8000_pcm_new
r_int
id|snd_emu8000_pcm_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|emu8000_t
op_star
id|emu
comma
r_int
id|index
)paren
(brace
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pcm_new
c_func
(paren
id|card
comma
l_string|&quot;Emu8000 PCM&quot;
comma
id|index
comma
l_int|1
comma
l_int|0
comma
op_amp
id|pcm
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|pcm-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|pcm-&gt;private_free
op_assign
id|snd_emu8000_pcm_free
suffix:semicolon
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_PLAYBACK
comma
op_amp
id|emu8k_pcm_ops
)paren
suffix:semicolon
id|emu-&gt;pcm
op_assign
id|pcm
suffix:semicolon
id|snd_device_register
c_func
(paren
id|card
comma
id|pcm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
