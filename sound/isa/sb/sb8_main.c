multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *&n; *  Routines for control of 8-bit SoundBlaster cards and clones&n; *  Please note: I don&squot;t have access to old SB8 soundcards.&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; * --&n; *&n; * Thu Apr 29 20:36:17 BST 1999 George David Morrison &lt;gdm@gedamo.demon.co.uk&gt;&n; *   DSP can&squot;t respond to commands whilst in &quot;high speed&quot; mode. Caused &n; *   glitching during playback. Fixed.&n; *&n; * Wed Jul 12 22:02:55 CEST 2000 Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *   Cleaned up and rewrote lowlevel routines.&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/sb.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;, Uros Bizjak &lt;uros@kss-loka.si&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Routines for control of 8-bit SoundBlaster cards and clones&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|chip_t
mdefine_line|#define chip_t sb_t
DECL|macro|SB8_CLOCK
mdefine_line|#define SB8_CLOCK&t;1000000
DECL|macro|SB8_DEN
mdefine_line|#define SB8_DEN(v)&t;((SB8_CLOCK + (v) / 2) / (v))
DECL|macro|SB8_RATE
mdefine_line|#define SB8_RATE(v)&t;(SB8_CLOCK / SB8_DEN(v))
DECL|variable|clock
r_static
id|ratnum_t
id|clock
op_assign
(brace
dot
id|num
op_assign
id|SB8_CLOCK
comma
dot
id|den_min
op_assign
l_int|1
comma
dot
id|den_max
op_assign
l_int|256
comma
dot
id|den_step
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|hw_constraints_clock
r_static
id|snd_pcm_hw_constraint_ratnums_t
id|hw_constraints_clock
op_assign
(brace
dot
id|nrats
op_assign
l_int|1
comma
dot
id|rats
op_assign
op_amp
id|clock
comma
)brace
suffix:semicolon
DECL|variable|stereo_clocks
r_static
id|ratnum_t
id|stereo_clocks
(braket
)braket
op_assign
(brace
(brace
dot
id|num
op_assign
id|SB8_CLOCK
comma
dot
id|den_min
op_assign
id|SB8_DEN
c_func
(paren
l_int|22050
)paren
comma
dot
id|den_max
op_assign
id|SB8_DEN
c_func
(paren
l_int|22050
)paren
comma
dot
id|den_step
op_assign
l_int|1
comma
)brace
comma
(brace
dot
id|num
op_assign
id|SB8_CLOCK
comma
dot
id|den_min
op_assign
id|SB8_DEN
c_func
(paren
l_int|11025
)paren
comma
dot
id|den_max
op_assign
id|SB8_DEN
c_func
(paren
l_int|11025
)paren
comma
dot
id|den_step
op_assign
l_int|1
comma
)brace
)brace
suffix:semicolon
DECL|function|snd_sb8_hw_constraint_rate_channels
r_static
r_int
id|snd_sb8_hw_constraint_rate_channels
c_func
(paren
id|snd_pcm_hw_params_t
op_star
id|params
comma
id|snd_pcm_hw_rule_t
op_star
id|rule
)paren
(brace
id|snd_interval_t
op_star
id|c
op_assign
id|hw_param_interval
c_func
(paren
id|params
comma
id|SNDRV_PCM_HW_PARAM_CHANNELS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;min
OG
l_int|1
)paren
(brace
r_int
r_int
id|num
op_assign
l_int|0
comma
id|den
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
id|snd_interval_ratnum
c_func
(paren
id|hw_param_interval
c_func
(paren
id|params
comma
id|SNDRV_PCM_HW_PARAM_RATE
)paren
comma
l_int|2
comma
id|stereo_clocks
comma
op_amp
id|num
comma
op_amp
id|den
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
op_logical_and
id|den
)paren
(brace
id|params-&gt;rate_num
op_assign
id|num
suffix:semicolon
id|params-&gt;rate_den
op_assign
id|den
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_hw_constraint_channels_rate
r_static
r_int
id|snd_sb8_hw_constraint_channels_rate
c_func
(paren
id|snd_pcm_hw_params_t
op_star
id|params
comma
id|snd_pcm_hw_rule_t
op_star
id|rule
)paren
(brace
id|snd_interval_t
op_star
id|r
op_assign
id|hw_param_interval
c_func
(paren
id|params
comma
id|SNDRV_PCM_HW_PARAM_RATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;min
OG
id|SB8_RATE
c_func
(paren
l_int|22050
)paren
op_logical_or
id|r-&gt;max
op_le
id|SB8_RATE
c_func
(paren
l_int|11025
)paren
)paren
(brace
id|snd_interval_t
id|t
op_assign
(brace
dot
id|min
op_assign
l_int|1
comma
dot
id|max
op_assign
l_int|1
)brace
suffix:semicolon
r_return
id|snd_interval_refine
c_func
(paren
id|hw_param_interval
c_func
(paren
id|params
comma
id|SNDRV_PCM_HW_PARAM_CHANNELS
)paren
comma
op_amp
id|t
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_playback_prepare
r_static
r_int
id|snd_sb8_playback_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_int
r_int
id|mixreg
comma
id|rate
comma
id|size
comma
id|count
suffix:semicolon
id|rate
op_assign
id|runtime-&gt;rate
suffix:semicolon
r_switch
c_cond
(paren
id|chip-&gt;hardware
)paren
(brace
r_case
id|SB_HW_PRO
suffix:colon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
id|snd_assert
c_func
(paren
id|rate
op_eq
id|SB8_RATE
c_func
(paren
l_int|11025
)paren
op_logical_or
id|rate
op_eq
id|SB8_RATE
c_func
(paren
l_int|22050
)paren
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|chip-&gt;playback_format
op_assign
id|SB_DSP_HI_OUTPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthru */
r_case
id|SB_HW_201
suffix:colon
r_if
c_cond
(paren
id|rate
OG
l_int|23000
)paren
(brace
id|chip-&gt;playback_format
op_assign
id|SB_DSP_HI_OUTPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthru */
r_case
id|SB_HW_20
suffix:colon
id|chip-&gt;playback_format
op_assign
id|SB_DSP_LO_OUTPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_HW_10
suffix:colon
id|chip-&gt;playback_format
op_assign
id|SB_DSP_OUTPUT
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
id|size
op_assign
id|chip-&gt;p_dma_size
op_assign
id|snd_pcm_lib_buffer_bytes
c_func
(paren
id|substream
)paren
suffix:semicolon
id|count
op_assign
id|chip-&gt;p_period_size
op_assign
id|snd_pcm_lib_period_bytes
c_func
(paren
id|substream
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_SPEAKER_ON
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
multiline_comment|/* set playback stereo mode */
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
id|mixreg
op_assign
id|snd_sbmixer_read
c_func
(paren
id|chip
comma
id|SB_DSP_STEREO_SW
)paren
suffix:semicolon
id|snd_sbmixer_write
c_func
(paren
id|chip
comma
id|SB_DSP_STEREO_SW
comma
id|mixreg
op_or
l_int|0x02
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* Soundblaster hardware programming reference guide, 3-23 */
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_DMA8_EXIT
)paren
suffix:semicolon
id|runtime-&gt;dma_area
(braket
l_int|0
)braket
op_assign
l_int|0x80
suffix:semicolon
id|snd_dma_program
c_func
(paren
id|chip-&gt;dma8
comma
id|runtime-&gt;dma_addr
comma
l_int|1
comma
id|DMA_MODE_WRITE
)paren
suffix:semicolon
multiline_comment|/* force interrupt */
id|chip-&gt;mode
op_assign
id|SB_MODE_HALT
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_OUTPUT
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
)brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_SAMPLE_RATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
l_int|256
op_minus
id|runtime-&gt;rate_den
op_div
l_int|2
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* save output filter status and turn it off */
id|mixreg
op_assign
id|snd_sbmixer_read
c_func
(paren
id|chip
comma
id|SB_DSP_PLAYBACK_FILT
)paren
suffix:semicolon
id|snd_sbmixer_write
c_func
(paren
id|chip
comma
id|SB_DSP_PLAYBACK_FILT
comma
id|mixreg
op_or
l_int|0x20
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* just use force_mode16 for temporary storate... */
id|chip-&gt;force_mode16
op_assign
id|mixreg
suffix:semicolon
)brace
r_else
(brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
l_int|256
op_minus
id|runtime-&gt;rate_den
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;playback_format
op_ne
id|SB_DSP_OUTPUT
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_BLOCK_SIZE
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_amp
l_int|0xff
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_dma_program
c_func
(paren
id|chip-&gt;dma8
comma
id|runtime-&gt;dma_addr
comma
id|size
comma
id|DMA_MODE_WRITE
op_or
id|DMA_AUTOINIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_playback_trigger
r_static
r_int
id|snd_sb8_playback_trigger
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|cmd
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
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
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|chip-&gt;playback_format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;playback_format
op_eq
id|SB_DSP_OUTPUT
)paren
(brace
id|count
op_assign
id|chip-&gt;p_period_size
op_minus
l_int|1
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_amp
l_int|0xff
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_STOP
suffix:colon
r_if
c_cond
(paren
id|chip-&gt;playback_format
op_eq
id|SB_DSP_HI_OUTPUT_AUTO
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_sbdsp_reset
c_func
(paren
id|chip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* restore output filter and set hardware to mono mode */
id|snd_sbmixer_write
c_func
(paren
id|chip
comma
id|SB_DSP_STEREO_SW
comma
id|chip-&gt;force_mode16
op_amp
op_complement
l_int|0x02
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_DMA8_OFF
)paren
suffix:semicolon
)brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_SPEAKER_OFF
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|chip-&gt;mode
op_assign
(paren
id|cmd
op_eq
id|SNDRV_PCM_TRIGGER_START
)paren
ques
c_cond
id|SB_MODE_PLAYBACK_8
suffix:colon
id|SB_MODE_HALT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_hw_params
r_static
r_int
id|snd_sb8_hw_params
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
id|snd_pcm_hw_params_t
op_star
id|hw_params
)paren
(brace
r_return
id|snd_pcm_lib_malloc_pages
c_func
(paren
id|substream
comma
id|params_buffer_bytes
c_func
(paren
id|hw_params
)paren
)paren
suffix:semicolon
)brace
DECL|function|snd_sb8_hw_free
r_static
r_int
id|snd_sb8_hw_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_lib_free_pages
c_func
(paren
id|substream
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_capture_prepare
r_static
r_int
id|snd_sb8_capture_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_int
r_int
id|mixreg
comma
id|rate
comma
id|size
comma
id|count
suffix:semicolon
id|rate
op_assign
id|runtime-&gt;rate
suffix:semicolon
r_switch
c_cond
(paren
id|chip-&gt;hardware
)paren
(brace
r_case
id|SB_HW_PRO
suffix:colon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
id|snd_assert
c_func
(paren
id|rate
op_eq
id|SB8_RATE
c_func
(paren
l_int|11025
)paren
op_logical_or
id|rate
op_eq
id|SB8_RATE
c_func
(paren
l_int|22050
)paren
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|chip-&gt;capture_format
op_assign
id|SB_DSP_HI_INPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|chip-&gt;capture_format
op_assign
(paren
id|rate
OG
l_int|23000
)paren
ques
c_cond
id|SB_DSP_HI_INPUT_AUTO
suffix:colon
id|SB_DSP_LO_INPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_HW_201
suffix:colon
r_if
c_cond
(paren
id|rate
OG
l_int|13000
)paren
(brace
id|chip-&gt;capture_format
op_assign
id|SB_DSP_HI_INPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthru */
r_case
id|SB_HW_20
suffix:colon
id|chip-&gt;capture_format
op_assign
id|SB_DSP_LO_INPUT_AUTO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_HW_10
suffix:colon
id|chip-&gt;capture_format
op_assign
id|SB_DSP_INPUT
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
id|size
op_assign
id|chip-&gt;c_dma_size
op_assign
id|snd_pcm_lib_buffer_bytes
c_func
(paren
id|substream
)paren
suffix:semicolon
id|count
op_assign
id|chip-&gt;c_period_size
op_assign
id|snd_pcm_lib_period_bytes
c_func
(paren
id|substream
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_SPEAKER_OFF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_STEREO_8BIT
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_SAMPLE_RATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
l_int|256
op_minus
id|runtime-&gt;rate_den
op_div
l_int|2
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* save input filter status and turn it off */
id|mixreg
op_assign
id|snd_sbmixer_read
c_func
(paren
id|chip
comma
id|SB_DSP_CAPTURE_FILT
)paren
suffix:semicolon
id|snd_sbmixer_write
c_func
(paren
id|chip
comma
id|SB_DSP_CAPTURE_FILT
comma
id|mixreg
op_or
l_int|0x20
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* just use force_mode16 for temporary storate... */
id|chip-&gt;force_mode16
op_assign
id|mixreg
suffix:semicolon
)brace
r_else
(brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
l_int|256
op_minus
id|runtime-&gt;rate_den
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;capture_format
op_ne
id|SB_DSP_OUTPUT
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_BLOCK_SIZE
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_amp
l_int|0xff
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_dma_program
c_func
(paren
id|chip-&gt;dma8
comma
id|runtime-&gt;dma_addr
comma
id|size
comma
id|DMA_MODE_READ
op_or
id|DMA_AUTOINIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_capture_trigger
r_static
r_int
id|snd_sb8_capture_trigger
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|cmd
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
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
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|chip-&gt;capture_format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;capture_format
op_eq
id|SB_DSP_INPUT
)paren
(brace
id|count
op_assign
id|chip-&gt;c_period_size
op_minus
l_int|1
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_amp
l_int|0xff
)paren
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|count
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_STOP
suffix:colon
r_if
c_cond
(paren
id|chip-&gt;capture_format
op_eq
id|SB_DSP_HI_INPUT_AUTO
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_sbdsp_reset
c_func
(paren
id|chip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
OG
l_int|1
)paren
(brace
multiline_comment|/* restore input filter status */
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
id|snd_sbmixer_write
c_func
(paren
id|chip
comma
id|SB_DSP_CAPTURE_FILT
comma
id|chip-&gt;force_mode16
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
multiline_comment|/* set hardware to mono mode */
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_MONO_8BIT
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_DMA8_OFF
)paren
suffix:semicolon
)brace
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_SPEAKER_OFF
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|chip-&gt;mode
op_assign
(paren
id|cmd
op_eq
id|SNDRV_PCM_TRIGGER_START
)paren
ques
c_cond
id|SB_MODE_CAPTURE_8
suffix:colon
id|SB_MODE_HALT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8dsp_interrupt
r_void
id|snd_sb8dsp_interrupt
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
suffix:semicolon
macro_line|#if 0
id|snd_printk
c_func
(paren
l_string|&quot;sb8: interrupt&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|snd_sb_ack_8bit
c_func
(paren
id|chip
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|chip-&gt;mode
)paren
(brace
r_case
id|SB_MODE_PLAYBACK_8
suffix:colon
multiline_comment|/* ok.. playback is active */
id|substream
op_assign
id|chip-&gt;playback_substream
suffix:semicolon
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;playback_format
op_eq
id|SB_DSP_OUTPUT
)paren
id|snd_sb8_playback_trigger
c_func
(paren
id|substream
comma
id|SNDRV_PCM_TRIGGER_START
)paren
suffix:semicolon
id|snd_pcm_period_elapsed
c_func
(paren
id|substream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_MODE_CAPTURE_8
suffix:colon
id|substream
op_assign
id|chip-&gt;capture_substream
suffix:semicolon
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;capture_format
op_eq
id|SB_DSP_INPUT
)paren
id|snd_sb8_capture_trigger
c_func
(paren
id|substream
comma
id|SNDRV_PCM_TRIGGER_START
)paren
suffix:semicolon
id|snd_pcm_period_elapsed
c_func
(paren
id|substream
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|snd_sb8_playback_pointer
r_static
id|snd_pcm_uframes_t
id|snd_sb8_playback_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
r_int
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;mode
op_ne
id|SB_MODE_PLAYBACK_8
)paren
r_return
l_int|0
suffix:semicolon
id|ptr
op_assign
id|snd_dma_pointer
c_func
(paren
id|chip-&gt;dma8
comma
id|chip-&gt;p_dma_size
)paren
suffix:semicolon
r_return
id|bytes_to_frames
c_func
(paren
id|substream-&gt;runtime
comma
id|ptr
)paren
suffix:semicolon
)brace
DECL|function|snd_sb8_capture_pointer
r_static
id|snd_pcm_uframes_t
id|snd_sb8_capture_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
r_int
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;mode
op_ne
id|SB_MODE_CAPTURE_8
)paren
r_return
l_int|0
suffix:semicolon
id|ptr
op_assign
id|snd_dma_pointer
c_func
(paren
id|chip-&gt;dma8
comma
id|chip-&gt;c_dma_size
)paren
suffix:semicolon
r_return
id|bytes_to_frames
c_func
(paren
id|substream-&gt;runtime
comma
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&n; */
DECL|variable|snd_sb8_playback
r_static
id|snd_pcm_hardware_t
id|snd_sb8_playback
op_assign
(brace
dot
id|info
op_assign
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_INTERLEAVED
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_U8
comma
dot
id|rates
op_assign
(paren
id|SNDRV_PCM_RATE_CONTINUOUS
op_or
id|SNDRV_PCM_RATE_8000
op_or
id|SNDRV_PCM_RATE_11025
op_or
id|SNDRV_PCM_RATE_22050
)paren
comma
dot
id|rate_min
op_assign
l_int|4000
comma
dot
id|rate_max
op_assign
l_int|23000
comma
dot
id|channels_min
op_assign
l_int|1
comma
dot
id|channels_max
op_assign
l_int|1
comma
dot
id|buffer_bytes_max
op_assign
l_int|65536
comma
dot
id|period_bytes_min
op_assign
l_int|64
comma
dot
id|period_bytes_max
op_assign
l_int|65536
comma
dot
id|periods_min
op_assign
l_int|1
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
DECL|variable|snd_sb8_capture
r_static
id|snd_pcm_hardware_t
id|snd_sb8_capture
op_assign
(brace
dot
id|info
op_assign
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_INTERLEAVED
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_U8
comma
dot
id|rates
op_assign
(paren
id|SNDRV_PCM_RATE_CONTINUOUS
op_or
id|SNDRV_PCM_RATE_8000
op_or
id|SNDRV_PCM_RATE_11025
)paren
comma
dot
id|rate_min
op_assign
l_int|4000
comma
dot
id|rate_max
op_assign
l_int|13000
comma
dot
id|channels_min
op_assign
l_int|1
comma
dot
id|channels_max
op_assign
l_int|1
comma
dot
id|buffer_bytes_max
op_assign
l_int|65536
comma
dot
id|period_bytes_min
op_assign
l_int|64
comma
dot
id|period_bytes_max
op_assign
l_int|65536
comma
dot
id|periods_min
op_assign
l_int|1
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
multiline_comment|/*&n; *&n; */
DECL|function|snd_sb8_open
r_int
id|snd_sb8_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;open
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|chip-&gt;open
op_or_assign
id|SB_OPEN_PCM
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;stream
op_eq
id|SNDRV_PCM_STREAM_PLAYBACK
)paren
(brace
id|chip-&gt;playback_substream
op_assign
id|substream
suffix:semicolon
id|runtime-&gt;hw
op_assign
id|snd_sb8_playback
suffix:semicolon
)brace
r_else
(brace
id|chip-&gt;capture_substream
op_assign
id|substream
suffix:semicolon
id|runtime-&gt;hw
op_assign
id|snd_sb8_capture
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|chip-&gt;hardware
)paren
(brace
r_case
id|SB_HW_PRO
suffix:colon
id|runtime-&gt;hw.rate_max
op_assign
l_int|44100
suffix:semicolon
id|runtime-&gt;hw.channels_max
op_assign
l_int|2
suffix:semicolon
id|snd_pcm_hw_rule_add
c_func
(paren
id|runtime
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_RATE
comma
id|snd_sb8_hw_constraint_rate_channels
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_CHANNELS
comma
id|SNDRV_PCM_HW_PARAM_RATE
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|snd_pcm_hw_rule_add
c_func
(paren
id|runtime
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_CHANNELS
comma
id|snd_sb8_hw_constraint_channels_rate
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_RATE
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_HW_201
suffix:colon
r_if
c_cond
(paren
id|substream-&gt;stream
op_eq
id|SNDRV_PCM_STREAM_PLAYBACK
)paren
(brace
id|runtime-&gt;hw.rate_max
op_assign
l_int|44100
suffix:semicolon
)brace
r_else
(brace
id|runtime-&gt;hw.rate_max
op_assign
l_int|15000
suffix:semicolon
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|snd_pcm_hw_constraint_ratnums
c_func
(paren
id|runtime
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_RATE
comma
op_amp
id|hw_constraints_clock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sb8_close
r_int
id|snd_sb8_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|sb_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|chip-&gt;playback_substream
op_assign
l_int|NULL
suffix:semicolon
id|chip-&gt;capture_substream
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|chip-&gt;open
op_and_assign
op_complement
id|SB_OPEN_PCM
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialization part&n; */
DECL|variable|snd_sb8_playback_ops
r_static
id|snd_pcm_ops_t
id|snd_sb8_playback_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_sb8_open
comma
dot
id|close
op_assign
id|snd_sb8_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_sb8_hw_params
comma
dot
id|hw_free
op_assign
id|snd_sb8_hw_free
comma
dot
id|prepare
op_assign
id|snd_sb8_playback_prepare
comma
dot
id|trigger
op_assign
id|snd_sb8_playback_trigger
comma
dot
id|pointer
op_assign
id|snd_sb8_playback_pointer
comma
)brace
suffix:semicolon
DECL|variable|snd_sb8_capture_ops
r_static
id|snd_pcm_ops_t
id|snd_sb8_capture_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_sb8_open
comma
dot
id|close
op_assign
id|snd_sb8_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_sb8_hw_params
comma
dot
id|hw_free
op_assign
id|snd_sb8_hw_free
comma
dot
id|prepare
op_assign
id|snd_sb8_capture_prepare
comma
dot
id|trigger
op_assign
id|snd_sb8_capture_trigger
comma
dot
id|pointer
op_assign
id|snd_sb8_capture_pointer
comma
)brace
suffix:semicolon
DECL|function|snd_sb8dsp_pcm_free
r_static
r_void
id|snd_sb8dsp_pcm_free
c_func
(paren
id|snd_pcm_t
op_star
id|pcm
)paren
(brace
id|snd_pcm_lib_preallocate_free_for_all
c_func
(paren
id|pcm
)paren
suffix:semicolon
)brace
DECL|function|snd_sb8dsp_pcm
r_int
id|snd_sb8dsp_pcm
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
(brace
id|snd_card_t
op_star
id|card
op_assign
id|chip-&gt;card
suffix:semicolon
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
id|rpcm
)paren
op_star
id|rpcm
op_assign
l_int|NULL
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
l_string|&quot;SB8 DSP&quot;
comma
id|device
comma
l_int|1
comma
l_int|1
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
id|sprintf
c_func
(paren
id|pcm-&gt;name
comma
l_string|&quot;DSP v%i.%i&quot;
comma
id|chip-&gt;version
op_rshift
l_int|8
comma
id|chip-&gt;version
op_amp
l_int|0xff
)paren
suffix:semicolon
id|pcm-&gt;info_flags
op_assign
id|SNDRV_PCM_INFO_HALF_DUPLEX
suffix:semicolon
id|pcm-&gt;private_data
op_assign
id|chip
suffix:semicolon
id|pcm-&gt;private_free
op_assign
id|snd_sb8dsp_pcm_free
suffix:semicolon
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_PLAYBACK
comma
op_amp
id|snd_sb8_playback_ops
)paren
suffix:semicolon
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_CAPTURE
comma
op_amp
id|snd_sb8_capture_ops
)paren
suffix:semicolon
id|snd_pcm_lib_preallocate_isa_pages_for_all
c_func
(paren
id|pcm
comma
l_int|64
op_star
l_int|1024
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rpcm
)paren
op_star
id|rpcm
op_assign
id|pcm
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_sb8dsp_pcm
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sb8dsp_pcm
)paren
suffix:semicolon
DECL|variable|snd_sb8dsp_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sb8dsp_interrupt
)paren
suffix:semicolon
multiline_comment|/* sb8_midi.c */
DECL|variable|snd_sb8dsp_midi_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sb8dsp_midi_interrupt
)paren
suffix:semicolon
DECL|variable|snd_sb8dsp_midi
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sb8dsp_midi
)paren
suffix:semicolon
multiline_comment|/*&n; *  INIT part&n; */
DECL|function|alsa_sb8_init
r_static
r_int
id|__init
id|alsa_sb8_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_sb8_exit
r_static
r_void
id|__exit
id|alsa_sb8_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_sb8_init
)paren
id|module_exit
c_func
(paren
id|alsa_sb8_exit
)paren
eof
