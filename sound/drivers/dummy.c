multiline_comment|/*&n; *  Dummy soundcard&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/rawmidi.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Dummy soundcard (/dev/null)&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;{{ALSA,Dummy soundcard}}&quot;
)paren
suffix:semicolon
DECL|macro|MAX_PCM_DEVICES
mdefine_line|#define MAX_PCM_DEVICES&t;&t;4
DECL|macro|MAX_PCM_SUBSTREAMS
mdefine_line|#define MAX_PCM_SUBSTREAMS&t;16
DECL|macro|MAX_MIDI_DEVICES
mdefine_line|#define MAX_MIDI_DEVICES&t;2
macro_line|#if 0 /* emu10k1 emulation */
mdefine_line|#define MAX_BUFFER_SIZE&t;&t;(128 * 1024)
r_static
r_int
id|emu10k1_playback_constraints
c_func
(paren
id|snd_pcm_runtime_t
op_star
id|runtime
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pcm_hw_constraint_integer
c_func
(paren
id|runtime
comma
id|SNDRV_PCM_HW_PARAM_PERIODS
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pcm_hw_constraint_minmax
c_func
(paren
id|runtime
comma
id|SNDRV_PCM_HW_PARAM_BUFFER_BYTES
comma
l_int|256
comma
id|UINT_MAX
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
mdefine_line|#define add_playback_constraints emu10k1_playback_constraints
macro_line|#endif
macro_line|#if 0 /* RME9652 emulation */
mdefine_line|#define MAX_BUFFER_SIZE&t;&t;(26 * 64 * 1024)
mdefine_line|#define USE_FORMATS&t;&t;SNDRV_PCM_FMTBIT_S32_LE
mdefine_line|#define USE_CHANNELS_MIN&t;26
mdefine_line|#define USE_CHANNELS_MAX&t;26
mdefine_line|#define USE_PERIODS_MIN&t;&t;2
mdefine_line|#define USE_PERIODS_MAX&t;&t;2
macro_line|#endif
macro_line|#if 0 /* ICE1712 emulation */
mdefine_line|#define MAX_BUFFER_SIZE&t;&t;(256 * 1024)
mdefine_line|#define USE_FORMATS&t;&t;SNDRV_PCM_FMTBIT_S32_LE
mdefine_line|#define USE_CHANNELS_MIN&t;10
mdefine_line|#define USE_CHANNELS_MAX&t;10
mdefine_line|#define USE_PERIODS_MIN&t;&t;1
mdefine_line|#define USE_PERIODS_MAX&t;&t;1024
macro_line|#endif
macro_line|#if 0 /* UDA1341 emulation */
mdefine_line|#define MAX_BUFFER_SIZE&t;&t;(16380)
mdefine_line|#define USE_FORMATS&t;&t;SNDRV_PCM_FMTBIT_S16_LE
mdefine_line|#define USE_CHANNELS_MIN&t;2
mdefine_line|#define USE_CHANNELS_MAX&t;2
mdefine_line|#define USE_PERIODS_MIN&t;&t;2
mdefine_line|#define USE_PERIODS_MAX&t;&t;255
macro_line|#endif
macro_line|#if 0 /* simple AC97 bridge (intel8x0) with 48kHz AC97 only codec */
mdefine_line|#define USE_FORMATS&t;&t;SNDRV_PCM_FMTBIT_S16_LE
mdefine_line|#define USE_CHANNELS_MIN&t;2
mdefine_line|#define USE_CHANNELS_MAX&t;2
mdefine_line|#define USE_RATE&t;&t;SNDRV_PCM_RATE_48000
mdefine_line|#define USE_RATE_MIN&t;&t;48000
mdefine_line|#define USE_RATE_MAX&t;&t;48000
macro_line|#endif
multiline_comment|/* defaults */
macro_line|#ifndef MAX_BUFFER_SIZE
DECL|macro|MAX_BUFFER_SIZE
mdefine_line|#define MAX_BUFFER_SIZE&t;&t;(64*1024)
macro_line|#endif
macro_line|#ifndef USE_FORMATS
DECL|macro|USE_FORMATS
mdefine_line|#define USE_FORMATS &t;&t;(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE)
macro_line|#endif
macro_line|#ifndef USE_RATE
DECL|macro|USE_RATE
mdefine_line|#define USE_RATE&t;&t;SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000
DECL|macro|USE_RATE_MIN
mdefine_line|#define USE_RATE_MIN&t;&t;5500
DECL|macro|USE_RATE_MAX
mdefine_line|#define USE_RATE_MAX&t;&t;48000
macro_line|#endif
macro_line|#ifndef USE_CHANNELS_MIN
DECL|macro|USE_CHANNELS_MIN
mdefine_line|#define USE_CHANNELS_MIN &t;1
macro_line|#endif
macro_line|#ifndef USE_CHANNELS_MAX
DECL|macro|USE_CHANNELS_MAX
mdefine_line|#define USE_CHANNELS_MAX &t;2
macro_line|#endif
macro_line|#ifndef USE_PERIODS_MIN
DECL|macro|USE_PERIODS_MIN
mdefine_line|#define USE_PERIODS_MIN &t;1
macro_line|#endif
macro_line|#ifndef USE_PERIODS_MAX
DECL|macro|USE_PERIODS_MAX
mdefine_line|#define USE_PERIODS_MAX &t;1024
macro_line|#endif
macro_line|#ifndef add_playback_constraints
DECL|macro|add_playback_constraints
mdefine_line|#define add_playback_constraints(x) 0
macro_line|#endif
macro_line|#ifndef add_capture_constraints
DECL|macro|add_capture_constraints
mdefine_line|#define add_capture_constraints(x) 0
macro_line|#endif
DECL|variable|index
r_static
r_int
id|index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|id
r_static
r_char
op_star
id|id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|enable
r_static
r_int
id|enable
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
l_int|1
comma
(braket
l_int|1
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|pcm_devs
r_static
r_int
id|pcm_devs
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|1
)brace
suffix:semicolon
DECL|variable|pcm_substreams
r_static
r_int
id|pcm_substreams
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|8
)brace
suffix:semicolon
singleline_comment|//static int midi_devs[SNDRV_CARDS] = {[0 ... (SNDRV_CARDS - 1)] = 2};
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for dummy soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for dummy soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable this dummy soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|pcm_devs
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|pcm_devs
comma
l_string|&quot;PCM devices # (0-4) for dummy driver.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|pcm_substreams
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|pcm_substreams
comma
l_string|&quot;PCM substreams # (1-16) for dummy driver.&quot;
)paren
suffix:semicolon
singleline_comment|//module_param_array(midi_devs, int, NULL, 0444);
singleline_comment|//MODULE_PARM_DESC(midi_devs, &quot;MIDI devices # (0-2) for dummy driver.&quot;);
DECL|macro|MIXER_ADDR_MASTER
mdefine_line|#define MIXER_ADDR_MASTER&t;0
DECL|macro|MIXER_ADDR_LINE
mdefine_line|#define MIXER_ADDR_LINE&t;&t;1
DECL|macro|MIXER_ADDR_MIC
mdefine_line|#define MIXER_ADDR_MIC&t;&t;2
DECL|macro|MIXER_ADDR_SYNTH
mdefine_line|#define MIXER_ADDR_SYNTH&t;3
DECL|macro|MIXER_ADDR_CD
mdefine_line|#define MIXER_ADDR_CD&t;&t;4
DECL|macro|MIXER_ADDR_LAST
mdefine_line|#define MIXER_ADDR_LAST&t;&t;4
DECL|struct|snd_card_dummy
r_typedef
r_struct
id|snd_card_dummy
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|mixer_lock
id|spinlock_t
id|mixer_lock
suffix:semicolon
DECL|member|mixer_volume
r_int
id|mixer_volume
(braket
id|MIXER_ADDR_LAST
op_plus
l_int|1
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|capture_source
r_int
id|capture_source
(braket
id|MIXER_ADDR_LAST
op_plus
l_int|1
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|snd_card_dummy_t
)brace
id|snd_card_dummy_t
suffix:semicolon
DECL|struct|snd_card_dummy_pcm
r_typedef
r_struct
id|snd_card_dummy_pcm
(brace
DECL|member|dummy
id|snd_card_dummy_t
op_star
id|dummy
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|pcm_size
r_int
r_int
id|pcm_size
suffix:semicolon
DECL|member|pcm_count
r_int
r_int
id|pcm_count
suffix:semicolon
DECL|member|pcm_bps
r_int
r_int
id|pcm_bps
suffix:semicolon
multiline_comment|/* bytes per second */
DECL|member|pcm_jiffie
r_int
r_int
id|pcm_jiffie
suffix:semicolon
multiline_comment|/* bytes per one jiffie */
DECL|member|pcm_irq_pos
r_int
r_int
id|pcm_irq_pos
suffix:semicolon
multiline_comment|/* IRQ position */
DECL|member|pcm_buf_pos
r_int
r_int
id|pcm_buf_pos
suffix:semicolon
multiline_comment|/* position in buffer */
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|typedef|snd_card_dummy_pcm_t
)brace
id|snd_card_dummy_pcm_t
suffix:semicolon
DECL|variable|snd_dummy_cards
r_static
id|snd_card_t
op_star
id|snd_dummy_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|function|snd_card_dummy_pcm_timer_start
r_static
r_void
id|snd_card_dummy_pcm_timer_start
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
id|runtime-&gt;private_data
suffix:semicolon
id|dpcm-&gt;timer.expires
op_assign
l_int|1
op_plus
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|dpcm-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_pcm_timer_stop
r_static
r_void
id|snd_card_dummy_pcm_timer_stop
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
id|runtime-&gt;private_data
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|dpcm-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_playback_trigger
r_static
r_int
id|snd_card_dummy_playback_trigger
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
r_if
c_cond
(paren
id|cmd
op_eq
id|SNDRV_PCM_TRIGGER_START
)paren
(brace
id|snd_card_dummy_pcm_timer_start
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd
op_eq
id|SNDRV_PCM_TRIGGER_STOP
)paren
(brace
id|snd_card_dummy_pcm_timer_stop
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_capture_trigger
r_static
r_int
id|snd_card_dummy_capture_trigger
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
r_if
c_cond
(paren
id|cmd
op_eq
id|SNDRV_PCM_TRIGGER_START
)paren
(brace
id|snd_card_dummy_pcm_timer_start
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd
op_eq
id|SNDRV_PCM_TRIGGER_STOP
)paren
(brace
id|snd_card_dummy_pcm_timer_stop
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_pcm_prepare
r_static
r_int
id|snd_card_dummy_pcm_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
id|runtime-&gt;private_data
suffix:semicolon
r_int
r_int
id|bps
suffix:semicolon
id|bps
op_assign
id|runtime-&gt;rate
op_star
id|runtime-&gt;channels
suffix:semicolon
id|bps
op_mul_assign
id|snd_pcm_format_width
c_func
(paren
id|runtime-&gt;format
)paren
suffix:semicolon
id|bps
op_div_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|bps
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dpcm-&gt;pcm_bps
op_assign
id|bps
suffix:semicolon
id|dpcm-&gt;pcm_jiffie
op_assign
id|bps
op_div
id|HZ
suffix:semicolon
id|dpcm-&gt;pcm_size
op_assign
id|snd_pcm_lib_buffer_bytes
c_func
(paren
id|substream
)paren
suffix:semicolon
id|dpcm-&gt;pcm_count
op_assign
id|snd_pcm_lib_period_bytes
c_func
(paren
id|substream
)paren
suffix:semicolon
id|dpcm-&gt;pcm_irq_pos
op_assign
l_int|0
suffix:semicolon
id|dpcm-&gt;pcm_buf_pos
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_playback_prepare
r_static
r_int
id|snd_card_dummy_playback_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_return
id|snd_card_dummy_pcm_prepare
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_capture_prepare
r_static
r_int
id|snd_card_dummy_capture_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_return
id|snd_card_dummy_pcm_prepare
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_pcm_timer_function
r_static
r_void
id|snd_card_dummy_pcm_timer_function
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
(paren
id|snd_card_dummy_pcm_t
op_star
)paren
id|data
suffix:semicolon
id|dpcm-&gt;timer.expires
op_assign
l_int|1
op_plus
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|dpcm-&gt;timer
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|dpcm-&gt;lock
)paren
suffix:semicolon
id|dpcm-&gt;pcm_irq_pos
op_add_assign
id|dpcm-&gt;pcm_jiffie
suffix:semicolon
id|dpcm-&gt;pcm_buf_pos
op_add_assign
id|dpcm-&gt;pcm_jiffie
suffix:semicolon
id|dpcm-&gt;pcm_buf_pos
op_mod_assign
id|dpcm-&gt;pcm_size
suffix:semicolon
r_if
c_cond
(paren
id|dpcm-&gt;pcm_irq_pos
op_ge
id|dpcm-&gt;pcm_count
)paren
(brace
id|dpcm-&gt;pcm_irq_pos
op_mod_assign
id|dpcm-&gt;pcm_count
suffix:semicolon
id|snd_pcm_period_elapsed
c_func
(paren
id|dpcm-&gt;substream
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|dpcm-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_playback_pointer
r_static
id|snd_pcm_uframes_t
id|snd_card_dummy_playback_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
id|runtime-&gt;private_data
suffix:semicolon
r_return
id|bytes_to_frames
c_func
(paren
id|runtime
comma
id|dpcm-&gt;pcm_buf_pos
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_capture_pointer
r_static
id|snd_pcm_uframes_t
id|snd_card_dummy_capture_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
id|runtime-&gt;private_data
suffix:semicolon
r_return
id|bytes_to_frames
c_func
(paren
id|runtime
comma
id|dpcm-&gt;pcm_buf_pos
)paren
suffix:semicolon
)brace
DECL|variable|snd_card_dummy_playback
r_static
id|snd_pcm_hardware_t
id|snd_card_dummy_playback
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
id|USE_FORMATS
comma
dot
id|rates
op_assign
id|USE_RATE
comma
dot
id|rate_min
op_assign
id|USE_RATE_MIN
comma
dot
id|rate_max
op_assign
id|USE_RATE_MAX
comma
dot
id|channels_min
op_assign
id|USE_CHANNELS_MIN
comma
dot
id|channels_max
op_assign
id|USE_CHANNELS_MAX
comma
dot
id|buffer_bytes_max
op_assign
id|MAX_BUFFER_SIZE
comma
dot
id|period_bytes_min
op_assign
l_int|64
comma
dot
id|period_bytes_max
op_assign
id|MAX_BUFFER_SIZE
comma
dot
id|periods_min
op_assign
id|USE_PERIODS_MIN
comma
dot
id|periods_max
op_assign
id|USE_PERIODS_MAX
comma
dot
id|fifo_size
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|snd_card_dummy_capture
r_static
id|snd_pcm_hardware_t
id|snd_card_dummy_capture
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
id|USE_FORMATS
comma
dot
id|rates
op_assign
id|USE_RATE
comma
dot
id|rate_min
op_assign
id|USE_RATE_MIN
comma
dot
id|rate_max
op_assign
id|USE_RATE_MAX
comma
dot
id|channels_min
op_assign
id|USE_CHANNELS_MIN
comma
dot
id|channels_max
op_assign
id|USE_CHANNELS_MAX
comma
dot
id|buffer_bytes_max
op_assign
id|MAX_BUFFER_SIZE
comma
dot
id|period_bytes_min
op_assign
l_int|64
comma
dot
id|period_bytes_max
op_assign
id|MAX_BUFFER_SIZE
comma
dot
id|periods_min
op_assign
id|USE_PERIODS_MIN
comma
dot
id|periods_max
op_assign
id|USE_PERIODS_MAX
comma
dot
id|fifo_size
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|function|snd_card_dummy_runtime_free
r_static
r_void
id|snd_card_dummy_runtime_free
c_func
(paren
id|snd_pcm_runtime_t
op_star
id|runtime
)paren
(brace
id|snd_card_dummy_pcm_t
op_star
id|dpcm
op_assign
id|runtime-&gt;private_data
suffix:semicolon
id|kfree
c_func
(paren
id|dpcm
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_hw_params
r_static
r_int
id|snd_card_dummy_hw_params
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
DECL|function|snd_card_dummy_hw_free
r_static
r_int
id|snd_card_dummy_hw_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_return
id|snd_pcm_lib_free_pages
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
DECL|function|snd_card_dummy_playback_open
r_static
r_int
id|snd_card_dummy_playback_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dpcm
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dpcm
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dpcm
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dpcm-&gt;timer
)paren
suffix:semicolon
id|dpcm-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|dpcm
suffix:semicolon
id|dpcm-&gt;timer.function
op_assign
id|snd_card_dummy_pcm_timer_function
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dpcm-&gt;lock
)paren
suffix:semicolon
id|dpcm-&gt;substream
op_assign
id|substream
suffix:semicolon
id|runtime-&gt;private_data
op_assign
id|dpcm
suffix:semicolon
id|runtime-&gt;private_free
op_assign
id|snd_card_dummy_runtime_free
suffix:semicolon
id|runtime-&gt;hw
op_assign
id|snd_card_dummy_playback
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;pcm-&gt;device
op_amp
l_int|1
)paren
(brace
id|runtime-&gt;hw.info
op_and_assign
op_complement
id|SNDRV_PCM_INFO_INTERLEAVED
suffix:semicolon
id|runtime-&gt;hw.info
op_or_assign
id|SNDRV_PCM_INFO_NONINTERLEAVED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|substream-&gt;pcm-&gt;device
op_amp
l_int|2
)paren
id|runtime-&gt;hw.info
op_and_assign
op_complement
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|add_playback_constraints
c_func
(paren
id|runtime
)paren
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dpcm
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_capture_open
r_static
r_int
id|snd_card_dummy_capture_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_card_dummy_pcm_t
op_star
id|dpcm
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dpcm
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dpcm
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dpcm
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dpcm-&gt;timer
)paren
suffix:semicolon
id|dpcm-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|dpcm
suffix:semicolon
id|dpcm-&gt;timer.function
op_assign
id|snd_card_dummy_pcm_timer_function
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dpcm-&gt;lock
)paren
suffix:semicolon
id|dpcm-&gt;substream
op_assign
id|substream
suffix:semicolon
id|runtime-&gt;private_data
op_assign
id|dpcm
suffix:semicolon
id|runtime-&gt;private_free
op_assign
id|snd_card_dummy_runtime_free
suffix:semicolon
id|runtime-&gt;hw
op_assign
id|snd_card_dummy_capture
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;pcm-&gt;device
op_eq
l_int|1
)paren
(brace
id|runtime-&gt;hw.info
op_and_assign
op_complement
id|SNDRV_PCM_INFO_INTERLEAVED
suffix:semicolon
id|runtime-&gt;hw.info
op_or_assign
id|SNDRV_PCM_INFO_NONINTERLEAVED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|substream-&gt;pcm-&gt;device
op_amp
l_int|2
)paren
id|runtime-&gt;hw.info
op_and_assign
op_complement
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|add_capture_constraints
c_func
(paren
id|runtime
)paren
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dpcm
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_playback_close
r_static
r_int
id|snd_card_dummy_playback_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_capture_close
r_static
r_int
id|snd_card_dummy_capture_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_card_dummy_playback_ops
r_static
id|snd_pcm_ops_t
id|snd_card_dummy_playback_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_card_dummy_playback_open
comma
dot
id|close
op_assign
id|snd_card_dummy_playback_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_card_dummy_hw_params
comma
dot
id|hw_free
op_assign
id|snd_card_dummy_hw_free
comma
dot
id|prepare
op_assign
id|snd_card_dummy_playback_prepare
comma
dot
id|trigger
op_assign
id|snd_card_dummy_playback_trigger
comma
dot
id|pointer
op_assign
id|snd_card_dummy_playback_pointer
comma
)brace
suffix:semicolon
DECL|variable|snd_card_dummy_capture_ops
r_static
id|snd_pcm_ops_t
id|snd_card_dummy_capture_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_card_dummy_capture_open
comma
dot
id|close
op_assign
id|snd_card_dummy_capture_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_card_dummy_hw_params
comma
dot
id|hw_free
op_assign
id|snd_card_dummy_hw_free
comma
dot
id|prepare
op_assign
id|snd_card_dummy_capture_prepare
comma
dot
id|trigger
op_assign
id|snd_card_dummy_capture_trigger
comma
dot
id|pointer
op_assign
id|snd_card_dummy_capture_pointer
comma
)brace
suffix:semicolon
DECL|function|snd_card_dummy_pcm
r_static
r_int
id|__init
id|snd_card_dummy_pcm
c_func
(paren
id|snd_card_dummy_t
op_star
id|dummy
comma
r_int
id|device
comma
r_int
id|substreams
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
id|dummy-&gt;card
comma
l_string|&quot;Dummy PCM&quot;
comma
id|device
comma
id|substreams
comma
id|substreams
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
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_PLAYBACK
comma
op_amp
id|snd_card_dummy_playback_ops
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
id|snd_card_dummy_capture_ops
)paren
suffix:semicolon
id|pcm-&gt;private_data
op_assign
id|dummy
suffix:semicolon
id|pcm-&gt;info_flags
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|pcm-&gt;name
comma
l_string|&quot;Dummy PCM&quot;
)paren
suffix:semicolon
id|snd_pcm_lib_preallocate_pages_for_all
c_func
(paren
id|pcm
comma
id|SNDRV_DMA_TYPE_CONTINUOUS
comma
id|snd_dma_continuous_data
c_func
(paren
id|GFP_KERNEL
)paren
comma
l_int|0
comma
l_int|64
op_star
l_int|1024
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DUMMY_VOLUME
mdefine_line|#define DUMMY_VOLUME(xname, xindex, addr) &bslash;&n;{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, &bslash;&n;  .info = snd_dummy_volume_info, &bslash;&n;  .get = snd_dummy_volume_get, .put = snd_dummy_volume_put, &bslash;&n;  .private_value = addr }
DECL|function|snd_dummy_volume_info
r_static
r_int
id|snd_dummy_volume_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|2
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
op_minus
l_int|50
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|100
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_dummy_volume_get
r_static
r_int
id|snd_dummy_volume_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_card_dummy_t
op_star
id|dummy
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|addr
op_assign
id|kcontrol-&gt;private_value
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|dummy-&gt;mixer_volume
(braket
id|addr
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|dummy-&gt;mixer_volume
(braket
id|addr
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_dummy_volume_put
r_static
r_int
id|snd_dummy_volume_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_card_dummy_t
op_star
id|dummy
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|change
comma
id|addr
op_assign
id|kcontrol-&gt;private_value
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
id|left
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|left
OL
op_minus
l_int|50
)paren
id|left
op_assign
op_minus
l_int|50
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
l_int|100
)paren
id|left
op_assign
l_int|100
suffix:semicolon
id|right
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|right
OL
op_minus
l_int|50
)paren
id|right
op_assign
op_minus
l_int|50
suffix:semicolon
r_if
c_cond
(paren
id|right
OG
l_int|100
)paren
id|right
op_assign
l_int|100
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
id|change
op_assign
id|dummy-&gt;mixer_volume
(braket
id|addr
)braket
(braket
l_int|0
)braket
op_ne
id|left
op_logical_or
id|dummy-&gt;mixer_volume
(braket
id|addr
)braket
(braket
l_int|1
)braket
op_ne
id|right
suffix:semicolon
id|dummy-&gt;mixer_volume
(braket
id|addr
)braket
(braket
l_int|0
)braket
op_assign
id|left
suffix:semicolon
id|dummy-&gt;mixer_volume
(braket
id|addr
)braket
(braket
l_int|1
)braket
op_assign
id|right
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|macro|DUMMY_CAPSRC
mdefine_line|#define DUMMY_CAPSRC(xname, xindex, addr) &bslash;&n;{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, &bslash;&n;  .info = snd_dummy_capsrc_info, &bslash;&n;  .get = snd_dummy_capsrc_get, .put = snd_dummy_capsrc_put, &bslash;&n;  .private_value = addr }
DECL|function|snd_dummy_capsrc_info
r_static
r_int
id|snd_dummy_capsrc_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|2
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_dummy_capsrc_get
r_static
r_int
id|snd_dummy_capsrc_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_card_dummy_t
op_star
id|dummy
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|addr
op_assign
id|kcontrol-&gt;private_value
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|dummy-&gt;capture_source
(braket
id|addr
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|dummy-&gt;capture_source
(braket
id|addr
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_dummy_capsrc_put
r_static
r_int
id|snd_dummy_capsrc_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_card_dummy_t
op_star
id|dummy
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|change
comma
id|addr
op_assign
id|kcontrol-&gt;private_value
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
id|left
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_amp
l_int|1
suffix:semicolon
id|right
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_amp
l_int|1
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
id|change
op_assign
id|dummy-&gt;capture_source
(braket
id|addr
)braket
(braket
l_int|0
)braket
op_ne
id|left
op_logical_and
id|dummy-&gt;capture_source
(braket
id|addr
)braket
(braket
l_int|1
)braket
op_ne
id|right
suffix:semicolon
id|dummy-&gt;capture_source
(braket
id|addr
)braket
(braket
l_int|0
)braket
op_assign
id|left
suffix:semicolon
id|dummy-&gt;capture_source
(braket
id|addr
)braket
(braket
l_int|1
)braket
op_assign
id|right
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|variable|snd_dummy_controls
r_static
id|snd_kcontrol_new_t
id|snd_dummy_controls
(braket
)braket
op_assign
(brace
id|DUMMY_VOLUME
c_func
(paren
l_string|&quot;Master Volume&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MASTER
)paren
comma
id|DUMMY_CAPSRC
c_func
(paren
l_string|&quot;Master Capture Switch&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MASTER
)paren
comma
id|DUMMY_VOLUME
c_func
(paren
l_string|&quot;Synth Volume&quot;
comma
l_int|0
comma
id|MIXER_ADDR_SYNTH
)paren
comma
id|DUMMY_CAPSRC
c_func
(paren
l_string|&quot;Synth Capture Switch&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MASTER
)paren
comma
id|DUMMY_VOLUME
c_func
(paren
l_string|&quot;Line Volume&quot;
comma
l_int|0
comma
id|MIXER_ADDR_LINE
)paren
comma
id|DUMMY_CAPSRC
c_func
(paren
l_string|&quot;Line Capture Switch&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MASTER
)paren
comma
id|DUMMY_VOLUME
c_func
(paren
l_string|&quot;Mic Volume&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MIC
)paren
comma
id|DUMMY_CAPSRC
c_func
(paren
l_string|&quot;Mic Capture Switch&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MASTER
)paren
comma
id|DUMMY_VOLUME
c_func
(paren
l_string|&quot;CD Volume&quot;
comma
l_int|0
comma
id|MIXER_ADDR_CD
)paren
comma
id|DUMMY_CAPSRC
c_func
(paren
l_string|&quot;CD Capture Switch&quot;
comma
l_int|0
comma
id|MIXER_ADDR_MASTER
)paren
)brace
suffix:semicolon
DECL|function|snd_card_dummy_new_mixer
r_static
r_int
id|__init
id|snd_card_dummy_new_mixer
c_func
(paren
id|snd_card_dummy_t
op_star
id|dummy
)paren
(brace
id|snd_card_t
op_star
id|card
op_assign
id|dummy-&gt;card
suffix:semicolon
r_int
r_int
id|idx
suffix:semicolon
r_int
id|err
suffix:semicolon
id|snd_assert
c_func
(paren
id|dummy
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dummy-&gt;mixer_lock
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;mixername
comma
l_string|&quot;Dummy Mixer&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|ARRAY_SIZE
c_func
(paren
id|snd_dummy_controls
)paren
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_dummy_controls
(braket
id|idx
)braket
comma
id|dummy
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_dummy_probe
r_static
r_int
id|__init
id|snd_card_dummy_probe
c_func
(paren
r_int
id|dev
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_card_dummy
op_star
id|dummy
suffix:semicolon
r_int
id|idx
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|dev
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|card
op_assign
id|snd_card_new
c_func
(paren
id|index
(braket
id|dev
)braket
comma
id|id
(braket
id|dev
)braket
comma
id|THIS_MODULE
comma
r_sizeof
(paren
r_struct
id|snd_card_dummy
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dummy
op_assign
(paren
r_struct
id|snd_card_dummy
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|dummy-&gt;card
op_assign
id|card
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|MAX_PCM_DEVICES
op_logical_and
id|idx
OL
id|pcm_devs
(braket
id|dev
)braket
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pcm_substreams
(braket
id|dev
)braket
OL
l_int|1
)paren
id|pcm_substreams
(braket
id|dev
)braket
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pcm_substreams
(braket
id|dev
)braket
OG
id|MAX_PCM_SUBSTREAMS
)paren
id|pcm_substreams
(braket
id|dev
)braket
op_assign
id|MAX_PCM_SUBSTREAMS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_dummy_pcm
c_func
(paren
id|dummy
comma
id|idx
comma
id|pcm_substreams
(braket
id|dev
)braket
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__nodev
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_dummy_new_mixer
c_func
(paren
id|dummy
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__nodev
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;Dummy&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Dummy&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;Dummy %i&quot;
comma
id|dev
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|card
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|snd_dummy_cards
(braket
id|dev
)braket
op_assign
id|card
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__nodev
suffix:colon
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|alsa_card_dummy_init
r_static
r_int
id|__init
id|alsa_card_dummy_init
c_func
(paren
r_void
)paren
(brace
r_int
id|dev
comma
id|cards
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|cards
op_assign
l_int|0
suffix:semicolon
id|dev
OL
id|SNDRV_CARDS
op_logical_and
id|enable
(braket
id|dev
)braket
suffix:semicolon
id|dev
op_increment
)paren
(brace
r_if
c_cond
(paren
id|snd_card_dummy_probe
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Dummy soundcard #%i not found or device busy&bslash;n&quot;
comma
id|dev
op_plus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
id|cards
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Dummy soundcard not found or device busy&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_card_dummy_exit
r_static
r_void
id|__exit
id|alsa_card_dummy_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_CARDS
suffix:semicolon
id|idx
op_increment
)paren
id|snd_card_free
c_func
(paren
id|snd_dummy_cards
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_dummy_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_dummy_exit
)paren
eof
