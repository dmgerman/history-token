multiline_comment|/*&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU Library General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
multiline_comment|/*&n; * Vortex PCM ALSA driver.&n; *&n; * Supports ADB and WT DMA. Unfortunately, WT channels do not run yet.&n; * It remains stuck,and DMA transfers do not happen. &n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/pcm_params.h&gt;
macro_line|#include &quot;au88x0.h&quot;
DECL|macro|VORTEX_PCM_TYPE
mdefine_line|#define VORTEX_PCM_TYPE(x) (x-&gt;name[40])
multiline_comment|/* hardware definition */
DECL|variable|snd_vortex_playback_hw_adb
r_static
id|snd_pcm_hardware_t
id|snd_vortex_playback_hw_adb
op_assign
(brace
dot
id|info
op_assign
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_RESUME
op_or
id|SNDRV_PCM_INFO_PAUSE
op_or
id|SNDRV_PCM_INFO_INTERLEAVED
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
op_or
id|SNDRV_PCM_FMTBIT_U8
op_or
id|SNDRV_PCM_FMTBIT_MU_LAW
op_or
id|SNDRV_PCM_FMTBIT_A_LAW
comma
dot
id|rates
op_assign
id|SNDRV_PCM_RATE_CONTINUOUS
comma
dot
id|rate_min
op_assign
l_int|5000
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
macro_line|#ifdef CHIP_AU8830
dot
id|channels_max
op_assign
l_int|4
comma
macro_line|#else
dot
id|channels_max
op_assign
l_int|2
comma
macro_line|#endif
dot
id|buffer_bytes_max
op_assign
l_int|0x10000
comma
dot
id|period_bytes_min
op_assign
l_int|0x1
comma
dot
id|period_bytes_max
op_assign
l_int|0x1000
comma
dot
id|periods_min
op_assign
l_int|2
comma
dot
id|periods_max
op_assign
l_int|32
comma
)brace
suffix:semicolon
macro_line|#ifndef CHIP_AU8820
DECL|variable|snd_vortex_playback_hw_a3d
r_static
id|snd_pcm_hardware_t
id|snd_vortex_playback_hw_a3d
op_assign
(brace
dot
id|info
op_assign
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_RESUME
op_or
id|SNDRV_PCM_INFO_PAUSE
op_or
id|SNDRV_PCM_INFO_INTERLEAVED
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
op_or
id|SNDRV_PCM_FMTBIT_U8
op_or
id|SNDRV_PCM_FMTBIT_MU_LAW
op_or
id|SNDRV_PCM_FMTBIT_A_LAW
comma
dot
id|rates
op_assign
id|SNDRV_PCM_RATE_CONTINUOUS
comma
dot
id|rate_min
op_assign
l_int|5000
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
l_int|1
comma
dot
id|buffer_bytes_max
op_assign
l_int|0x10000
comma
dot
id|period_bytes_min
op_assign
l_int|0x100
comma
dot
id|period_bytes_max
op_assign
l_int|0x1000
comma
dot
id|periods_min
op_assign
l_int|2
comma
dot
id|periods_max
op_assign
l_int|64
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|snd_vortex_playback_hw_spdif
r_static
id|snd_pcm_hardware_t
id|snd_vortex_playback_hw_spdif
op_assign
(brace
dot
id|info
op_assign
(paren
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_RESUME
op_or
id|SNDRV_PCM_INFO_PAUSE
op_or
id|SNDRV_PCM_INFO_INTERLEAVED
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
op_or
id|SNDRV_PCM_FMTBIT_U8
op_or
id|SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE
op_or
id|SNDRV_PCM_FMTBIT_MU_LAW
op_or
id|SNDRV_PCM_FMTBIT_A_LAW
comma
dot
id|rates
op_assign
id|SNDRV_PCM_RATE_32000
op_or
id|SNDRV_PCM_RATE_44100
op_or
id|SNDRV_PCM_RATE_48000
comma
dot
id|rate_min
op_assign
l_int|32000
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
l_int|0x10000
comma
dot
id|period_bytes_min
op_assign
l_int|0x100
comma
dot
id|period_bytes_max
op_assign
l_int|0x1000
comma
dot
id|periods_min
op_assign
l_int|2
comma
dot
id|periods_max
op_assign
l_int|64
comma
)brace
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
DECL|variable|snd_vortex_playback_hw_wt
r_static
id|snd_pcm_hardware_t
id|snd_vortex_playback_hw_wt
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
id|SNDRV_PCM_INFO_BLOCK_TRANSFER
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
comma
dot
id|rates
op_assign
id|SNDRV_PCM_RATE_8000_48000
op_or
id|SNDRV_PCM_RATE_CONTINUOUS
comma
singleline_comment|// SNDRV_PCM_RATE_48000,
dot
id|rate_min
op_assign
l_int|8000
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
l_int|0x10000
comma
dot
id|period_bytes_min
op_assign
l_int|0x0400
comma
dot
id|period_bytes_max
op_assign
l_int|0x1000
comma
dot
id|periods_min
op_assign
l_int|2
comma
dot
id|periods_max
op_assign
l_int|64
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* open callback */
DECL|function|snd_vortex_pcm_open
r_static
r_int
id|snd_vortex_pcm_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|vortex_t
op_star
id|vortex
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
id|err
suffix:semicolon
multiline_comment|/* Force equal size periods */
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
multiline_comment|/* Avoid PAGE_SIZE boundary to fall inside of a period. */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pcm_hw_constraint_pow2
c_func
(paren
id|runtime
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_PERIOD_BYTES
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
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
(brace
macro_line|#ifndef CHIP_AU8820
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_eq
id|VORTEX_PCM_A3D
)paren
(brace
id|runtime-&gt;hw
op_assign
id|snd_vortex_playback_hw_a3d
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_eq
id|VORTEX_PCM_SPDIF
)paren
(brace
id|runtime-&gt;hw
op_assign
id|snd_vortex_playback_hw_spdif
suffix:semicolon
r_switch
c_cond
(paren
id|vortex-&gt;spdif_sr
)paren
(brace
r_case
l_int|32000
suffix:colon
id|runtime-&gt;hw.rates
op_assign
id|SNDRV_PCM_RATE_32000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|44100
suffix:colon
id|runtime-&gt;hw.rates
op_assign
id|SNDRV_PCM_RATE_44100
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48000
suffix:colon
id|runtime-&gt;hw.rates
op_assign
id|SNDRV_PCM_RATE_48000
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_eq
id|VORTEX_PCM_ADB
op_logical_or
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_eq
id|VORTEX_PCM_I2S
)paren
id|runtime-&gt;hw
op_assign
id|snd_vortex_playback_hw_adb
suffix:semicolon
id|substream-&gt;runtime-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifndef CHIP_AU8810
r_else
(brace
id|runtime-&gt;hw
op_assign
id|snd_vortex_playback_hw_wt
suffix:semicolon
id|substream-&gt;runtime-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* close callback */
DECL|function|snd_vortex_pcm_close
r_static
r_int
id|snd_vortex_pcm_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
singleline_comment|//vortex_t *chip = snd_pcm_substream_chip(substream);
id|stream_t
op_star
id|stream
op_assign
(paren
id|stream_t
op_star
)paren
id|substream-&gt;runtime-&gt;private_data
suffix:semicolon
singleline_comment|// the hardware-specific codes will be here
r_if
c_cond
(paren
id|stream
op_ne
l_int|NULL
)paren
(brace
id|stream-&gt;substream
op_assign
l_int|NULL
suffix:semicolon
id|stream-&gt;nr_ch
op_assign
l_int|0
suffix:semicolon
)brace
id|substream-&gt;runtime-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* hw_params callback */
r_static
r_int
DECL|function|snd_vortex_pcm_hw_params
id|snd_vortex_pcm_hw_params
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
id|vortex_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|stream_t
op_star
id|stream
op_assign
(paren
id|stream_t
op_star
)paren
(paren
id|substream-&gt;runtime-&gt;private_data
)paren
suffix:semicolon
id|snd_pcm_sgbuf_t
op_star
id|sgbuf
suffix:semicolon
r_int
id|err
suffix:semicolon
singleline_comment|// Alloc buffer memory.
id|err
op_assign
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
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Vortex: pcm page alloc failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
singleline_comment|//sgbuf = (snd_pcm_sgbuf_t *) substream-&gt;runtime-&gt;dma_private;
id|sgbuf
op_assign
id|snd_pcm_substream_sgbuf
c_func
(paren
id|substream
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   printk(KERN_INFO &quot;Vortex: periods %d, period_bytes %d, channels = %d&bslash;n&quot;, params_periods(hw_params),&n;&t;   params_period_bytes(hw_params), params_channels(hw_params));&n;&t; */
singleline_comment|// Make audio routes and config buffer DMA.
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
(brace
r_int
id|dma
comma
id|type
op_assign
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
suffix:semicolon
multiline_comment|/* Dealloc any routes. */
r_if
c_cond
(paren
id|stream
op_ne
l_int|NULL
)paren
id|vortex_adb_allocroute
c_func
(paren
id|chip
comma
id|stream-&gt;dma
comma
id|stream-&gt;nr_ch
comma
id|stream-&gt;dir
comma
id|stream-&gt;type
)paren
suffix:semicolon
multiline_comment|/* Alloc routes. */
id|dma
op_assign
id|vortex_adb_allocroute
c_func
(paren
id|chip
comma
op_minus
l_int|1
comma
id|params_channels
c_func
(paren
id|hw_params
)paren
comma
id|substream-&gt;stream
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma
OL
l_int|0
)paren
r_return
id|dma
suffix:semicolon
id|stream
op_assign
id|substream-&gt;runtime-&gt;private_data
op_assign
op_amp
id|chip-&gt;dma_adb
(braket
id|dma
)braket
suffix:semicolon
id|stream-&gt;substream
op_assign
id|substream
suffix:semicolon
multiline_comment|/* Setup Buffers. */
id|vortex_adbdma_setbuffers
c_func
(paren
id|chip
comma
id|dma
comma
id|sgbuf
comma
id|params_period_bytes
c_func
(paren
id|hw_params
)paren
comma
id|params_periods
c_func
(paren
id|hw_params
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CHIP_AU8810
r_else
(brace
multiline_comment|/* if (stream != NULL)&n;&t;&t;   vortex_wt_allocroute(chip, substream-&gt;number, 0); */
id|vortex_wt_allocroute
c_func
(paren
id|chip
comma
id|substream-&gt;number
comma
id|params_channels
c_func
(paren
id|hw_params
)paren
)paren
suffix:semicolon
id|stream
op_assign
id|substream-&gt;runtime-&gt;private_data
op_assign
op_amp
id|chip-&gt;dma_wt
(braket
id|substream-&gt;number
)braket
suffix:semicolon
id|stream-&gt;dma
op_assign
id|substream-&gt;number
suffix:semicolon
id|stream-&gt;substream
op_assign
id|substream
suffix:semicolon
id|vortex_wtdma_setbuffers
c_func
(paren
id|chip
comma
id|substream-&gt;number
comma
id|sgbuf
comma
id|params_period_bytes
c_func
(paren
id|hw_params
)paren
comma
id|params_periods
c_func
(paren
id|hw_params
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* hw_free callback */
DECL|function|snd_vortex_pcm_hw_free
r_static
r_int
id|snd_vortex_pcm_hw_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|vortex_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|stream_t
op_star
id|stream
op_assign
(paren
id|stream_t
op_star
)paren
(paren
id|substream-&gt;runtime-&gt;private_data
)paren
suffix:semicolon
singleline_comment|// Delete audio routes.
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
(brace
r_if
c_cond
(paren
id|stream
op_ne
l_int|NULL
)paren
id|vortex_adb_allocroute
c_func
(paren
id|chip
comma
id|stream-&gt;dma
comma
id|stream-&gt;nr_ch
comma
id|stream-&gt;dir
comma
id|stream-&gt;type
)paren
suffix:semicolon
)brace
macro_line|#ifndef CHIP_AU8810
r_else
(brace
r_if
c_cond
(paren
id|stream
op_ne
l_int|NULL
)paren
id|vortex_wt_allocroute
c_func
(paren
id|chip
comma
id|stream-&gt;dma
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
id|substream-&gt;runtime-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
id|snd_pcm_lib_free_pages
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
multiline_comment|/* prepare callback */
DECL|function|snd_vortex_pcm_prepare
r_static
r_int
id|snd_vortex_pcm_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|vortex_t
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
id|stream_t
op_star
id|stream
op_assign
(paren
id|stream_t
op_star
)paren
id|substream-&gt;runtime-&gt;private_data
suffix:semicolon
r_int
id|dma
op_assign
id|stream-&gt;dma
comma
id|fmt
comma
id|dir
suffix:semicolon
singleline_comment|// set up the hardware with the current configuration.
r_if
c_cond
(paren
id|substream-&gt;stream
op_eq
id|SNDRV_PCM_STREAM_PLAYBACK
)paren
id|dir
op_assign
l_int|1
suffix:semicolon
r_else
id|dir
op_assign
l_int|0
suffix:semicolon
id|fmt
op_assign
id|vortex_alsafmt_aspfmt
c_func
(paren
id|runtime-&gt;format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
(brace
id|vortex_adbdma_setmode
c_func
(paren
id|chip
comma
id|dma
comma
l_int|1
comma
id|dir
comma
id|fmt
comma
l_int|0
multiline_comment|/*? */
comma
l_int|0
)paren
suffix:semicolon
id|vortex_adbdma_setstartbuffer
c_func
(paren
id|chip
comma
id|dma
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_SPDIF
)paren
id|vortex_adb_setsrc
c_func
(paren
id|chip
comma
id|dma
comma
id|runtime-&gt;rate
comma
id|dir
)paren
suffix:semicolon
)brace
macro_line|#ifndef CHIP_AU8810
r_else
(brace
id|vortex_wtdma_setmode
c_func
(paren
id|chip
comma
id|dma
comma
l_int|1
comma
id|fmt
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// FIXME: Set rate (i guess using vortex_wt_writereg() somehow).
id|vortex_wtdma_setstartbuffer
c_func
(paren
id|chip
comma
id|dma
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* trigger callback */
DECL|function|snd_vortex_pcm_trigger
r_static
r_int
id|snd_vortex_pcm_trigger
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
id|vortex_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|stream_t
op_star
id|stream
op_assign
(paren
id|stream_t
op_star
)paren
id|substream-&gt;runtime-&gt;private_data
suffix:semicolon
r_int
id|dma
op_assign
id|stream-&gt;dma
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
singleline_comment|// do something to start the PCM engine
singleline_comment|//printk(KERN_INFO &quot;vortex: start %d&bslash;n&quot;, dma);
id|stream-&gt;fifo_enabled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
(brace
id|vortex_adbdma_resetup
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
id|vortex_adbdma_startfifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
)brace
macro_line|#ifndef CHIP_AU8810
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vortex: wt start %d&bslash;n&quot;
comma
id|dma
)paren
suffix:semicolon
id|vortex_wtdma_startfifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
)brace
macro_line|#endif
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_STOP
suffix:colon
singleline_comment|// do something to stop the PCM engine
singleline_comment|//printk(KERN_INFO &quot;vortex: stop %d&bslash;n&quot;, dma);
id|stream-&gt;fifo_enabled
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
id|vortex_adbdma_pausefifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
singleline_comment|//vortex_adbdma_stopfifo(chip, dma);
macro_line|#ifndef CHIP_AU8810
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vortex: wt stop %d&bslash;n&quot;
comma
id|dma
)paren
suffix:semicolon
id|vortex_wtdma_stopfifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
)brace
macro_line|#endif
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_PAUSE_PUSH
suffix:colon
singleline_comment|//printk(KERN_INFO &quot;vortex: pause %d&bslash;n&quot;, dma);
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
id|vortex_adbdma_pausefifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
r_else
id|vortex_wtdma_pausefifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_PAUSE_RELEASE
suffix:colon
singleline_comment|//printk(KERN_INFO &quot;vortex: resume %d&bslash;n&quot;, dma);
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
id|vortex_adbdma_resumefifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
r_else
id|vortex_wtdma_resumefifo
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* pointer callback */
DECL|function|snd_vortex_pcm_pointer
r_static
id|snd_pcm_uframes_t
id|snd_vortex_pcm_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|vortex_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|substream
)paren
suffix:semicolon
id|stream_t
op_star
id|stream
op_assign
(paren
id|stream_t
op_star
)paren
id|substream-&gt;runtime-&gt;private_data
suffix:semicolon
r_int
id|dma
op_assign
id|stream-&gt;dma
suffix:semicolon
id|snd_pcm_uframes_t
id|current_ptr
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|substream-&gt;pcm
)paren
op_ne
id|VORTEX_PCM_WT
)paren
id|current_ptr
op_assign
id|vortex_adbdma_getlinearpos
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
r_else
id|current_ptr
op_assign
id|vortex_wtdma_getlinearpos
c_func
(paren
id|chip
comma
id|dma
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|//printk(KERN_INFO &quot;vortex: pointer = 0x%x&bslash;n&quot;, current_ptr);
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;lock
)paren
suffix:semicolon
r_return
(paren
id|bytes_to_frames
c_func
(paren
id|substream-&gt;runtime
comma
id|current_ptr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Page callback. */
multiline_comment|/*&n;static struct page *snd_pcm_sgbuf_ops_page(snd_pcm_substream_t *substream, unsigned long offset) {&n;&t;&n;&t;&n;}&n;*/
multiline_comment|/* operators */
DECL|variable|snd_vortex_playback_ops
r_static
id|snd_pcm_ops_t
id|snd_vortex_playback_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_vortex_pcm_open
comma
dot
id|close
op_assign
id|snd_vortex_pcm_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_vortex_pcm_hw_params
comma
dot
id|hw_free
op_assign
id|snd_vortex_pcm_hw_free
comma
dot
id|prepare
op_assign
id|snd_vortex_pcm_prepare
comma
dot
id|trigger
op_assign
id|snd_vortex_pcm_trigger
comma
dot
id|pointer
op_assign
id|snd_vortex_pcm_pointer
comma
dot
id|page
op_assign
id|snd_pcm_sgbuf_ops_page
comma
)brace
suffix:semicolon
multiline_comment|/*&n;*  definitions of capture are omitted here...&n;*/
DECL|variable|vortex_pcm_prettyname
r_static
r_char
op_star
id|vortex_pcm_prettyname
(braket
id|VORTEX_PCM_LAST
)braket
op_assign
(brace
l_string|&quot;AU88x0 ADB&quot;
comma
l_string|&quot;AU88x0 SPDIF&quot;
comma
l_string|&quot;AU88x0 A3D&quot;
comma
l_string|&quot;AU88x0 WT&quot;
comma
l_string|&quot;AU88x0 I2S&quot;
comma
)brace
suffix:semicolon
DECL|variable|vortex_pcm_name
r_static
r_char
op_star
id|vortex_pcm_name
(braket
id|VORTEX_PCM_LAST
)braket
op_assign
(brace
l_string|&quot;adb&quot;
comma
l_string|&quot;spdif&quot;
comma
l_string|&quot;a3d&quot;
comma
l_string|&quot;wt&quot;
comma
l_string|&quot;i2s&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* SPDIF kcontrol */
r_static
r_int
DECL|function|snd_vortex_spdif_info
id|snd_vortex_spdif_info
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
r_static
r_char
op_star
id|texts
(braket
)braket
op_assign
(brace
l_string|&quot;32000&quot;
comma
l_string|&quot;44100&quot;
comma
l_string|&quot;48000&quot;
)brace
suffix:semicolon
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_ENUMERATED
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
id|uinfo-&gt;value.enumerated.items
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|uinfo-&gt;value.enumerated.item
op_ge
id|uinfo-&gt;value.enumerated.items
)paren
id|uinfo-&gt;value.enumerated.item
op_assign
id|uinfo-&gt;value.enumerated.items
op_minus
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|uinfo-&gt;value.enumerated.name
comma
id|texts
(braket
id|uinfo-&gt;value.enumerated.item
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_vortex_spdif_get
id|snd_vortex_spdif_get
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
id|vortex_t
op_star
id|vortex
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vortex-&gt;spdif_sr
op_eq
l_int|32000
)paren
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vortex-&gt;spdif_sr
op_eq
l_int|44100
)paren
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|vortex-&gt;spdif_sr
op_eq
l_int|48000
)paren
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_vortex_spdif_put
id|snd_vortex_spdif_put
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
id|vortex_t
op_star
id|vortex
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_static
r_int
r_int
id|sr
(braket
l_int|3
)braket
op_assign
(brace
l_int|32000
comma
l_int|44100
comma
l_int|48000
)brace
suffix:semicolon
singleline_comment|//printk(&quot;vortex: spdif sr = %d&bslash;n&quot;, ucontrol-&gt;value.enumerated.item[0]);
id|vortex-&gt;spdif_sr
op_assign
id|sr
(braket
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_mod
l_int|3
)braket
suffix:semicolon
id|vortex_spdif_init
c_func
(paren
id|vortex
comma
id|sr
(braket
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_mod
l_int|3
)braket
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
id|snd_kcontrol_new_t
id|vortex_spdif_kcontrol
id|__devinitdata
op_assign
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;SPDIF SR&quot;
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READWRITE
comma
dot
id|private_value
op_assign
l_int|0
comma
dot
id|info
op_assign
id|snd_vortex_spdif_info
comma
dot
id|get
op_assign
id|snd_vortex_spdif_get
comma
dot
id|put
op_assign
id|snd_vortex_spdif_put
)brace
suffix:semicolon
multiline_comment|/* create a pcm device */
DECL|function|snd_vortex_new_pcm
r_static
r_int
id|__devinit
id|snd_vortex_new_pcm
c_func
(paren
id|vortex_t
op_star
id|chip
comma
r_int
id|idx
comma
r_int
id|nr
)paren
(brace
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
r_int
id|err
comma
id|nr_capt
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chip
op_eq
l_int|0
)paren
op_logical_or
(paren
id|idx
OL
l_int|0
)paren
op_logical_or
(paren
id|idx
OG
id|VORTEX_PCM_LAST
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* idx indicates which kind of PCM device. ADB, SPDIF, I2S and A3D share the &n;&t; * same dma engine. WT uses it own separate dma engine whcih cant capture. */
r_if
c_cond
(paren
id|idx
op_eq
id|VORTEX_PCM_ADB
)paren
id|nr_capt
op_assign
id|nr
suffix:semicolon
r_else
id|nr_capt
op_assign
l_int|0
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
id|chip-&gt;card
comma
id|vortex_pcm_prettyname
(braket
id|idx
)braket
comma
id|idx
comma
id|nr
comma
id|nr_capt
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
id|strcpy
c_func
(paren
id|pcm-&gt;name
comma
id|vortex_pcm_name
(braket
id|idx
)braket
)paren
suffix:semicolon
id|chip-&gt;pcm
(braket
id|idx
)braket
op_assign
id|pcm
suffix:semicolon
singleline_comment|// This is an evil hack, but it saves a lot of duplicated code.
id|VORTEX_PCM_TYPE
c_func
(paren
id|pcm
)paren
op_assign
id|idx
suffix:semicolon
id|pcm-&gt;private_data
op_assign
id|chip
suffix:semicolon
multiline_comment|/* set operators */
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_PLAYBACK
comma
op_amp
id|snd_vortex_playback_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_eq
id|VORTEX_PCM_ADB
)paren
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_CAPTURE
comma
op_amp
id|snd_vortex_playback_ops
)paren
suffix:semicolon
multiline_comment|/* pre-allocation of Scatter-Gather buffers */
id|snd_pcm_lib_preallocate_pages_for_all
c_func
(paren
id|pcm
comma
id|SNDRV_DMA_TYPE_DEV_SG
comma
id|snd_dma_pci_data
c_func
(paren
id|chip-&gt;pci_dev
)paren
comma
l_int|0x10000
comma
l_int|0x10000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VORTEX_PCM_TYPE
c_func
(paren
id|pcm
)paren
op_eq
id|VORTEX_PCM_SPDIF
)paren
(brace
id|snd_kcontrol_t
op_star
id|kcontrol
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kcontrol
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|vortex_spdif_kcontrol
comma
id|chip
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|kcontrol
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
eof
