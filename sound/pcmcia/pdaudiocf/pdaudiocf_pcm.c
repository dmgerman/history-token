multiline_comment|/*&n; * Driver for Sound Core PDAudioCF soundcards&n; *&n; * PCM part&n; *&n; * Copyright (c) 2003 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/asoundef.h&gt;
macro_line|#include &quot;pdaudiocf.h&quot;
DECL|macro|chip_t
mdefine_line|#define chip_t&t;pdacf_t
multiline_comment|/*&n; * we use a vmalloc&squot;ed (sg-)buffer&n; */
multiline_comment|/* get the physical page pointer on the given offset */
DECL|function|snd_pcm_get_vmalloc_page
r_static
r_struct
id|page
op_star
id|snd_pcm_get_vmalloc_page
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
r_int
id|offset
)paren
(brace
r_void
op_star
id|pageptr
op_assign
id|subs-&gt;runtime-&gt;dma_area
op_plus
id|offset
suffix:semicolon
r_return
id|vmalloc_to_page
c_func
(paren
id|pageptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hw_params callback&n; * NOTE: this may be called not only once per pcm open!&n; */
DECL|function|snd_pcm_alloc_vmalloc_buffer
r_static
r_int
id|snd_pcm_alloc_vmalloc_buffer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
comma
r_int
id|size
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|subs-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;dma_area
)paren
(brace
r_if
c_cond
(paren
id|runtime-&gt;dma_bytes
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* already enough large */
id|vfree_nocheck
c_func
(paren
id|runtime-&gt;dma_area
)paren
suffix:semicolon
)brace
id|runtime-&gt;dma_area
op_assign
id|vmalloc_nocheck
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|runtime-&gt;dma_area
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|runtime-&gt;dma_bytes
op_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hw_free callback&n; * NOTE: this may be called not only once per pcm open!&n; */
DECL|function|snd_pcm_free_vmalloc_buffer
r_static
r_int
id|snd_pcm_free_vmalloc_buffer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|subs-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;dma_area
)paren
(brace
id|vfree_nocheck
c_func
(paren
id|runtime-&gt;dma_area
)paren
suffix:semicolon
id|runtime-&gt;dma_area
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * clear the SRAM contents&n; */
DECL|function|pdacf_pcm_clear_sram
r_static
r_int
id|pdacf_pcm_clear_sram
c_func
(paren
id|pdacf_t
op_star
id|chip
)paren
(brace
r_int
id|max_loop
op_assign
l_int|64
op_star
l_int|1024
suffix:semicolon
r_while
c_loop
(paren
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_RDP
)paren
op_ne
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_WDP
)paren
)paren
(brace
r_if
c_cond
(paren
id|max_loop
op_decrement
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_MD
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pdacf_pcm_trigger - trigger callback for capture&n; */
DECL|function|pdacf_pcm_trigger
r_static
r_int
id|pdacf_pcm_trigger
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
id|pdacf_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|subs
)paren
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|subs-&gt;runtime
suffix:semicolon
r_int
id|inc
comma
id|ret
op_assign
l_int|0
comma
id|rate
suffix:semicolon
r_int
r_int
id|mask
comma
id|val
comma
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|PDAUDIOCF_STAT_IS_STALE
)paren
r_return
op_minus
id|EBUSY
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
id|chip-&gt;pcm_hwptr
op_assign
l_int|0
suffix:semicolon
id|chip-&gt;pcm_tdone
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fall thru */
r_case
id|SNDRV_PCM_TRIGGER_PAUSE_RELEASE
suffix:colon
r_case
id|SNDRV_PCM_TRIGGER_RESUME
suffix:colon
id|mask
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
id|PDAUDIOCF_RECORD
suffix:semicolon
id|inc
op_assign
l_int|1
suffix:semicolon
id|rate
op_assign
id|snd_ak4117_check_rate_and_errors
c_func
(paren
id|chip-&gt;ak4117
comma
id|AK4117_CHECK_NO_STAT
op_or
id|AK4117_CHECK_NO_RATE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_STOP
suffix:colon
r_case
id|SNDRV_PCM_TRIGGER_PAUSE_PUSH
suffix:colon
r_case
id|SNDRV_PCM_TRIGGER_SUSPEND
suffix:colon
id|mask
op_assign
id|PDAUDIOCF_RECORD
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
id|inc
op_assign
op_minus
l_int|1
suffix:semicolon
id|rate
op_assign
l_int|0
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
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
id|chip-&gt;pcm_running
op_add_assign
id|inc
suffix:semicolon
id|tmp
op_assign
id|pdacf_reg_read
c_func
(paren
id|chip
comma
id|PDAUDIOCF_REG_SCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;pcm_running
)paren
(brace
r_if
c_cond
(paren
(paren
id|chip-&gt;ak4117-&gt;rcs0
op_amp
id|AK4117_UNLCK
)paren
op_logical_or
id|runtime-&gt;rate
op_ne
id|rate
)paren
(brace
id|chip-&gt;pcm_running
op_sub_assign
id|inc
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|__end
suffix:semicolon
)brace
)brace
id|tmp
op_and_assign
op_complement
id|mask
suffix:semicolon
id|tmp
op_or_assign
id|val
suffix:semicolon
id|pdacf_reg_write
c_func
(paren
id|chip
comma
id|PDAUDIOCF_REG_SCR
comma
id|tmp
)paren
suffix:semicolon
id|__end
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
id|snd_ak4117_check_rate_and_errors
c_func
(paren
id|chip-&gt;ak4117
comma
id|AK4117_CHECK_NO_RATE
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * pdacf_pcm_hw_params - hw_params callback for playback and capture&n; */
DECL|function|pdacf_pcm_hw_params
r_static
r_int
id|pdacf_pcm_hw_params
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
r_return
id|snd_pcm_alloc_vmalloc_buffer
c_func
(paren
id|subs
comma
id|params_buffer_bytes
c_func
(paren
id|hw_params
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * pdacf_pcm_hw_free - hw_free callback for playback and capture&n; */
DECL|function|pdacf_pcm_hw_free
r_static
r_int
id|pdacf_pcm_hw_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
r_return
id|snd_pcm_free_vmalloc_buffer
c_func
(paren
id|subs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * pdacf_pcm_prepare - prepare callback for playback and capture&n; */
DECL|function|pdacf_pcm_prepare
r_static
r_int
id|pdacf_pcm_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|subs
)paren
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|subs-&gt;runtime
suffix:semicolon
id|u16
id|val
comma
id|nval
comma
id|aval
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|PDAUDIOCF_STAT_IS_STALE
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|chip-&gt;pcm_channels
op_assign
id|runtime-&gt;channels
suffix:semicolon
id|chip-&gt;pcm_little
op_assign
id|snd_pcm_format_little_endian
c_func
(paren
id|runtime-&gt;format
)paren
OG
l_int|0
suffix:semicolon
macro_line|#ifdef SNDRV_LITTLE_ENDIAN
id|chip-&gt;pcm_swab
op_assign
id|snd_pcm_format_big_endian
c_func
(paren
id|runtime-&gt;format
)paren
OG
l_int|0
suffix:semicolon
macro_line|#else
id|chip-&gt;pcm_swab
op_assign
id|chip-&gt;pcm_little
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|snd_pcm_format_unsigned
c_func
(paren
id|runtime-&gt;format
)paren
)paren
id|chip-&gt;pcm_xor
op_assign
l_int|0x80008000
suffix:semicolon
r_if
c_cond
(paren
id|pdacf_pcm_clear_sram
c_func
(paren
id|chip
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|val
op_assign
id|nval
op_assign
id|pdacf_reg_read
c_func
(paren
id|chip
comma
id|PDAUDIOCF_REG_SCR
)paren
suffix:semicolon
id|nval
op_and_assign
op_complement
(paren
id|PDAUDIOCF_DATAFMT0
op_or
id|PDAUDIOCF_DATAFMT1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|runtime-&gt;format
)paren
(brace
r_case
id|SNDRV_PCM_FORMAT_S16_LE
suffix:colon
r_case
id|SNDRV_PCM_FORMAT_S16_BE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* 24-bit */
id|nval
op_or_assign
id|PDAUDIOCF_DATAFMT0
op_or
id|PDAUDIOCF_DATAFMT1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|aval
op_assign
l_int|0
suffix:semicolon
id|chip-&gt;pcm_sample
op_assign
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|runtime-&gt;format
)paren
(brace
r_case
id|SNDRV_PCM_FORMAT_S16_LE
suffix:colon
r_case
id|SNDRV_PCM_FORMAT_S16_BE
suffix:colon
id|aval
op_assign
id|AK4117_DIF_16R
suffix:semicolon
id|chip-&gt;pcm_frame
op_assign
l_int|2
suffix:semicolon
id|chip-&gt;pcm_sample
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_FORMAT_S24_3LE
suffix:colon
r_case
id|SNDRV_PCM_FORMAT_S24_3BE
suffix:colon
id|chip-&gt;pcm_sample
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* fall trough */
r_default
suffix:colon
multiline_comment|/* 24-bit */
id|aval
op_assign
id|AK4117_DIF_24R
suffix:semicolon
id|chip-&gt;pcm_frame
op_assign
l_int|3
suffix:semicolon
id|chip-&gt;pcm_xor
op_and_assign
l_int|0xffff0000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_ne
id|nval
)paren
(brace
id|snd_ak4117_reg_write
c_func
(paren
id|chip-&gt;ak4117
comma
id|AK4117_REG_IO
comma
id|AK4117_DIF2
op_or
id|AK4117_DIF1
op_or
id|AK4117_DIF0
comma
id|aval
)paren
suffix:semicolon
id|pdacf_reg_write
c_func
(paren
id|chip
comma
id|PDAUDIOCF_REG_SCR
comma
id|nval
)paren
suffix:semicolon
)brace
id|val
op_assign
id|pdacf_reg_read
c_func
(paren
id|chip
comma
id|PDAUDIOCF_REG_IER
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
id|PDAUDIOCF_IRQLVLEN1
)paren
suffix:semicolon
id|val
op_or_assign
id|PDAUDIOCF_IRQLVLEN0
suffix:semicolon
id|pdacf_reg_write
c_func
(paren
id|chip
comma
id|PDAUDIOCF_REG_IER
comma
id|val
)paren
suffix:semicolon
id|chip-&gt;pcm_size
op_assign
id|runtime-&gt;buffer_size
suffix:semicolon
id|chip-&gt;pcm_period
op_assign
id|runtime-&gt;period_size
suffix:semicolon
id|chip-&gt;pcm_area
op_assign
id|runtime-&gt;dma_area
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * capture hw information&n; */
DECL|variable|pdacf_pcm_capture_hw
r_static
id|snd_pcm_hardware_t
id|pdacf_pcm_capture_hw
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
id|SNDRV_PCM_INFO_PAUSE
op_or
id|SNDRV_PCM_INFO_RESUME
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
op_or
id|SNDRV_PCM_FMTBIT_S16_BE
op_or
id|SNDRV_PCM_FMTBIT_S24_3LE
op_or
id|SNDRV_PCM_FMTBIT_S24_3BE
op_or
id|SNDRV_PCM_FMTBIT_S32_LE
op_or
id|SNDRV_PCM_FMTBIT_S32_BE
comma
dot
id|rates
op_assign
id|SNDRV_PCM_RATE_32000
op_or
id|SNDRV_PCM_RATE_44100
op_or
id|SNDRV_PCM_RATE_48000
op_or
id|SNDRV_PCM_RATE_88200
op_or
id|SNDRV_PCM_RATE_96000
op_or
id|SNDRV_PCM_RATE_176400
op_or
id|SNDRV_PCM_RATE_192000
comma
dot
id|rate_min
op_assign
l_int|32000
comma
dot
id|rate_max
op_assign
l_int|192000
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
l_int|512
op_star
l_int|1024
)paren
comma
dot
id|period_bytes_min
op_assign
l_int|8
op_star
l_int|1024
comma
dot
id|period_bytes_max
op_assign
(paren
l_int|64
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
l_int|128
comma
dot
id|fifo_size
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * pdacf_pcm_capture_open - open callback for capture&n; */
DECL|function|pdacf_pcm_capture_open
r_static
r_int
id|pdacf_pcm_capture_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|subs-&gt;runtime
suffix:semicolon
id|pdacf_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|subs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|PDAUDIOCF_STAT_IS_STALE
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|runtime-&gt;hw
op_assign
id|pdacf_pcm_capture_hw
suffix:semicolon
id|runtime-&gt;private_data
op_assign
id|chip
suffix:semicolon
id|chip-&gt;pcm_substream
op_assign
id|subs
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pdacf_pcm_capture_close - close callback for capture&n; */
DECL|function|pdacf_pcm_capture_close
r_static
r_int
id|pdacf_pcm_capture_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|subs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chip
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pdacf_reinit
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
id|chip-&gt;pcm_substream
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pdacf_pcm_capture_pointer - pointer callback for capture&n; */
DECL|function|pdacf_pcm_capture_pointer
r_static
id|snd_pcm_uframes_t
id|pdacf_pcm_capture_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|snd_pcm_substream_chip
c_func
(paren
id|subs
)paren
suffix:semicolon
r_return
id|chip-&gt;pcm_hwptr
suffix:semicolon
)brace
multiline_comment|/*&n; * operators for PCM capture&n; */
DECL|variable|pdacf_pcm_capture_ops
r_static
id|snd_pcm_ops_t
id|pdacf_pcm_capture_ops
op_assign
(brace
dot
id|open
op_assign
id|pdacf_pcm_capture_open
comma
dot
id|close
op_assign
id|pdacf_pcm_capture_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|pdacf_pcm_hw_params
comma
dot
id|hw_free
op_assign
id|pdacf_pcm_hw_free
comma
dot
id|prepare
op_assign
id|pdacf_pcm_prepare
comma
dot
id|trigger
op_assign
id|pdacf_pcm_trigger
comma
dot
id|pointer
op_assign
id|pdacf_pcm_capture_pointer
comma
dot
id|page
op_assign
id|snd_pcm_get_vmalloc_page
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * free callback for pcm&n; */
DECL|function|snd_pdacf_pcm_free
r_static
r_void
id|snd_pdacf_pcm_free
c_func
(paren
id|snd_pcm_t
op_star
id|pcm
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|pdacf_t
comma
id|pcm-&gt;private_data
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;pcm
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * snd_pdacf_pcm_new - create and initialize a pcm&n; */
DECL|function|snd_pdacf_pcm_new
r_int
id|snd_pdacf_pcm_new
c_func
(paren
id|pdacf_t
op_star
id|chip
)paren
(brace
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|snd_pcm_new
c_func
(paren
id|chip-&gt;card
comma
l_string|&quot;PDAudioCF&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
op_amp
id|pcm
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
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_CAPTURE
comma
op_amp
id|pdacf_pcm_capture_ops
)paren
suffix:semicolon
id|pcm-&gt;private_data
op_assign
id|chip
suffix:semicolon
id|pcm-&gt;private_free
op_assign
id|snd_pdacf_pcm_free
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
id|chip-&gt;card-&gt;shortname
)paren
suffix:semicolon
id|chip-&gt;pcm
op_assign
id|pcm
suffix:semicolon
id|err
op_assign
id|snd_ak4117_build
c_func
(paren
id|chip-&gt;ak4117
comma
id|pcm-&gt;streams
(braket
id|SNDRV_PCM_STREAM_CAPTURE
)braket
dot
id|substream
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
l_int|0
suffix:semicolon
)brace
eof
