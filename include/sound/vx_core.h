multiline_comment|/*&n; * Driver for Digigram VX soundcards&n; *&n; * Hardware core part&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __SOUND_VX_COMMON_H
DECL|macro|__SOUND_VX_COMMON_H
mdefine_line|#define __SOUND_VX_COMMON_H
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/hwdep.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#if defined(CONFIG_FW_LOADER) || defined(CONFIG_FW_LOADER_MODULE)
macro_line|#if !defined(CONFIG_USE_VXLOADER) &amp;&amp; !defined(CONFIG_SND_VX_LIB) /* built-in kernel */
DECL|macro|SND_VX_FW_LOADER
mdefine_line|#define SND_VX_FW_LOADER&t;/* use the standard firmware loader */
macro_line|#endif
macro_line|#endif
r_struct
id|firmware
suffix:semicolon
r_struct
id|device
suffix:semicolon
DECL|typedef|vx_core_t
r_typedef
r_struct
id|snd_vx_core
id|vx_core_t
suffix:semicolon
DECL|typedef|vx_pipe_t
r_typedef
r_struct
id|vx_pipe
id|vx_pipe_t
suffix:semicolon
DECL|macro|VX_DRIVER_VERSION
mdefine_line|#define VX_DRIVER_VERSION&t;0x010000&t;/* 1.0.0 */
multiline_comment|/*&n; */
DECL|macro|SIZE_MAX_CMD
mdefine_line|#define SIZE_MAX_CMD    0x10
DECL|macro|SIZE_MAX_STATUS
mdefine_line|#define SIZE_MAX_STATUS 0x10
DECL|struct|vx_rmh
r_struct
id|vx_rmh
(brace
DECL|member|LgCmd
id|u16
id|LgCmd
suffix:semicolon
multiline_comment|/* length of the command to send (WORDs) */
DECL|member|LgStat
id|u16
id|LgStat
suffix:semicolon
multiline_comment|/* length of the status received (WORDs) */
DECL|member|Cmd
id|u32
id|Cmd
(braket
id|SIZE_MAX_CMD
)braket
suffix:semicolon
DECL|member|Stat
id|u32
id|Stat
(braket
id|SIZE_MAX_STATUS
)braket
suffix:semicolon
DECL|member|DspStat
id|u16
id|DspStat
suffix:semicolon
multiline_comment|/* status type, RMP_SSIZE_XXX */
)brace
suffix:semicolon
DECL|typedef|pcx_time_t
r_typedef
id|u64
id|pcx_time_t
suffix:semicolon
DECL|macro|VX_MAX_PIPES
mdefine_line|#define VX_MAX_PIPES&t;16
DECL|macro|VX_MAX_PERIODS
mdefine_line|#define VX_MAX_PERIODS&t;32
DECL|macro|VX_MAX_CODECS
mdefine_line|#define VX_MAX_CODECS&t;2
DECL|struct|vx_ibl_info
r_struct
id|vx_ibl_info
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* the current IBL size (0 = query) in bytes */
DECL|member|max_size
r_int
id|max_size
suffix:semicolon
multiline_comment|/* max. IBL size in bytes */
DECL|member|min_size
r_int
id|min_size
suffix:semicolon
multiline_comment|/* min. IBL size in bytes */
DECL|member|granularity
r_int
id|granularity
suffix:semicolon
multiline_comment|/* granularity */
)brace
suffix:semicolon
DECL|struct|vx_pipe
r_struct
id|vx_pipe
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|is_capture
r_int
r_int
id|is_capture
suffix:colon
l_int|1
suffix:semicolon
DECL|member|data_mode
r_int
r_int
id|data_mode
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
DECL|member|prepared
r_int
r_int
id|prepared
suffix:colon
l_int|1
suffix:semicolon
DECL|member|channels
r_int
id|channels
suffix:semicolon
DECL|member|differed_type
r_int
r_int
id|differed_type
suffix:semicolon
DECL|member|pcx_time
id|pcx_time_t
id|pcx_time
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|hbuf_size
r_int
id|hbuf_size
suffix:semicolon
multiline_comment|/* H-buffer size in bytes */
DECL|member|buffer_bytes
r_int
id|buffer_bytes
suffix:semicolon
multiline_comment|/* the ALSA pcm buffer size in bytes */
DECL|member|period_bytes
r_int
id|period_bytes
suffix:semicolon
multiline_comment|/* the ALSA pcm period size in bytes */
DECL|member|hw_ptr
r_int
id|hw_ptr
suffix:semicolon
multiline_comment|/* the current hardware pointer in bytes */
DECL|member|position
r_int
id|position
suffix:semicolon
multiline_comment|/* the current position in frames (playback only) */
DECL|member|transferred
r_int
id|transferred
suffix:semicolon
multiline_comment|/* the transferred size (per period) in frames */
DECL|member|align
r_int
id|align
suffix:semicolon
multiline_comment|/* size of alignment */
DECL|member|cur_count
id|u64
id|cur_count
suffix:semicolon
multiline_comment|/* current sample position (for playback) */
DECL|member|references
r_int
r_int
id|references
suffix:semicolon
multiline_comment|/* an output pipe may be used for monitoring and/or playback */
DECL|member|monitoring_pipe
id|vx_pipe_t
op_star
id|monitoring_pipe
suffix:semicolon
multiline_comment|/* pointer to the monitoring pipe (capture pipe only)*/
DECL|member|start_tq
r_struct
id|tasklet_struct
id|start_tq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_vx_ops
r_struct
id|snd_vx_ops
(brace
multiline_comment|/* low-level i/o */
DECL|member|in8
r_int
r_char
(paren
op_star
id|in8
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
)paren
suffix:semicolon
DECL|member|in32
r_int
r_int
(paren
op_star
id|in32
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
)paren
suffix:semicolon
DECL|member|out8
r_void
(paren
op_star
id|out8
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
comma
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|member|out32
r_void
(paren
op_star
id|out32
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
multiline_comment|/* irq */
DECL|member|test_and_ack
r_int
(paren
op_star
id|test_and_ack
)paren
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
DECL|member|validate_irq
r_void
(paren
op_star
id|validate_irq
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|enable
)paren
suffix:semicolon
multiline_comment|/* codec */
DECL|member|write_codec
r_void
(paren
op_star
id|write_codec
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|codec
comma
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|member|akm_write
r_void
(paren
op_star
id|akm_write
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
comma
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|member|reset_codec
r_void
(paren
op_star
id|reset_codec
)paren
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
DECL|member|change_audio_source
r_void
(paren
op_star
id|change_audio_source
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|src
)paren
suffix:semicolon
DECL|member|set_clock_source
r_void
(paren
op_star
id|set_clock_source
)paren
(paren
id|vx_core_t
op_star
id|chp
comma
r_int
id|src
)paren
suffix:semicolon
multiline_comment|/* chip init */
DECL|member|load_dsp
r_int
(paren
op_star
id|load_dsp
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|idx
comma
r_const
r_struct
id|firmware
op_star
id|fw
)paren
suffix:semicolon
DECL|member|reset_dsp
r_void
(paren
op_star
id|reset_dsp
)paren
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
DECL|member|reset_board
r_void
(paren
op_star
id|reset_board
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|cold_reset
)paren
suffix:semicolon
DECL|member|add_controls
r_int
(paren
op_star
id|add_controls
)paren
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/* pcm */
DECL|member|dma_write
r_void
(paren
op_star
id|dma_write
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
id|snd_pcm_runtime_t
op_star
id|runtime
comma
id|vx_pipe_t
op_star
id|pipe
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|dma_read
r_void
(paren
op_star
id|dma_read
)paren
(paren
id|vx_core_t
op_star
id|chip
comma
id|snd_pcm_runtime_t
op_star
id|runtime
comma
id|vx_pipe_t
op_star
id|pipe
comma
r_int
id|count
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_vx_hardware
r_struct
id|snd_vx_hardware
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* VX_TYPE_XXX */
multiline_comment|/* hardware specs */
DECL|member|num_codecs
r_int
r_int
id|num_codecs
suffix:semicolon
DECL|member|num_ins
r_int
r_int
id|num_ins
suffix:semicolon
DECL|member|num_outs
r_int
r_int
id|num_outs
suffix:semicolon
DECL|member|output_level_max
r_int
r_int
id|output_level_max
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hwdep id string */
DECL|macro|SND_VX_HWDEP_ID
mdefine_line|#define SND_VX_HWDEP_ID&t;&t;&quot;VX Loader&quot;
multiline_comment|/* hardware type */
r_enum
(brace
multiline_comment|/* VX222 PCI */
DECL|enumerator|VX_TYPE_BOARD
id|VX_TYPE_BOARD
comma
multiline_comment|/* old VX222 PCI */
DECL|enumerator|VX_TYPE_V2
id|VX_TYPE_V2
comma
multiline_comment|/* VX222 V2 PCI */
DECL|enumerator|VX_TYPE_MIC
id|VX_TYPE_MIC
comma
multiline_comment|/* VX222 Mic PCI */
multiline_comment|/* VX-pocket */
DECL|enumerator|VX_TYPE_VXPOCKET
id|VX_TYPE_VXPOCKET
comma
multiline_comment|/* VXpocket V2 */
DECL|enumerator|VX_TYPE_VXP440
id|VX_TYPE_VXP440
comma
multiline_comment|/* VXpocket 440 */
DECL|enumerator|VX_TYPE_NUMS
id|VX_TYPE_NUMS
)brace
suffix:semicolon
multiline_comment|/* chip status */
r_enum
(brace
DECL|enumerator|VX_STAT_XILINX_LOADED
id|VX_STAT_XILINX_LOADED
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* devices are registered */
DECL|enumerator|VX_STAT_DEVICE_INIT
id|VX_STAT_DEVICE_INIT
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* devices are registered */
DECL|enumerator|VX_STAT_CHIP_INIT
id|VX_STAT_CHIP_INIT
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* all operational */
DECL|enumerator|VX_STAT_IN_SUSPEND
id|VX_STAT_IN_SUSPEND
op_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
multiline_comment|/* in suspend phase */
DECL|enumerator|VX_STAT_IS_STALE
id|VX_STAT_IS_STALE
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
multiline_comment|/* device is stale */
)brace
suffix:semicolon
multiline_comment|/* min/max values for analog output for old codecs */
DECL|macro|VX_ANALOG_OUT_LEVEL_MAX
mdefine_line|#define VX_ANALOG_OUT_LEVEL_MAX&t;&t;0xe3
DECL|struct|snd_vx_core
r_struct
id|snd_vx_core
(brace
multiline_comment|/* ALSA stuff */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
(braket
id|VX_MAX_CODECS
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* VX_TYPE_XXX */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* ports are defined externally */
multiline_comment|/* low-level functions */
DECL|member|hw
r_struct
id|snd_vx_hardware
op_star
id|hw
suffix:semicolon
DECL|member|ops
r_struct
id|snd_vx_ops
op_star
id|ops
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|irq_lock
id|spinlock_t
id|irq_lock
suffix:semicolon
DECL|member|tq
r_struct
id|tasklet_struct
id|tq
suffix:semicolon
DECL|member|chip_status
r_int
r_int
id|chip_status
suffix:semicolon
DECL|member|pcm_running
r_int
r_int
id|pcm_running
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|hwdep
id|snd_hwdep_t
op_star
id|hwdep
suffix:semicolon
DECL|member|irq_rmh
r_struct
id|vx_rmh
id|irq_rmh
suffix:semicolon
multiline_comment|/* RMH used in interrupts */
DECL|member|audio_info
r_int
r_int
id|audio_info
suffix:semicolon
multiline_comment|/* see VX_AUDIO_INFO */
DECL|member|audio_ins
r_int
r_int
id|audio_ins
suffix:semicolon
DECL|member|audio_outs
r_int
r_int
id|audio_outs
suffix:semicolon
DECL|member|playback_pipes
r_struct
id|vx_pipe
op_star
op_star
id|playback_pipes
suffix:semicolon
DECL|member|capture_pipes
r_struct
id|vx_pipe
op_star
op_star
id|capture_pipes
suffix:semicolon
multiline_comment|/* clock and audio sources */
DECL|member|audio_source
r_int
r_int
id|audio_source
suffix:semicolon
multiline_comment|/* current audio input source */
DECL|member|audio_source_target
r_int
r_int
id|audio_source_target
suffix:semicolon
DECL|member|clock_mode
r_int
r_int
id|clock_mode
suffix:semicolon
multiline_comment|/* clock mode (VX_CLOCK_MODE_XXX) */
DECL|member|clock_source
r_int
r_int
id|clock_source
suffix:semicolon
multiline_comment|/* current clock source (INTERNAL_QUARTZ or UER_SYNC) */
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* current frequency */
DECL|member|freq_detected
r_int
r_int
id|freq_detected
suffix:semicolon
multiline_comment|/* detected frequency from digital in */
DECL|member|uer_detected
r_int
r_int
id|uer_detected
suffix:semicolon
multiline_comment|/* VX_UER_MODE_XXX */
DECL|member|uer_bits
r_int
r_int
id|uer_bits
suffix:semicolon
multiline_comment|/* IEC958 status bits */
DECL|member|ibl
r_struct
id|vx_ibl_info
id|ibl
suffix:semicolon
multiline_comment|/* IBL information */
multiline_comment|/* mixer setting */
DECL|member|output_level
r_int
id|output_level
(braket
id|VX_MAX_CODECS
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* analog output level */
DECL|member|audio_gain
r_int
id|audio_gain
(braket
l_int|2
)braket
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* digital audio level (playback/capture) */
DECL|member|audio_active
r_int
r_char
id|audio_active
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* mute/unmute on digital playback */
DECL|member|audio_monitor
r_int
id|audio_monitor
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* playback hw-monitor level */
DECL|member|audio_monitor_active
r_int
r_char
id|audio_monitor_active
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* playback hw-monitor mute/unmute */
DECL|member|mixer_mutex
r_struct
id|semaphore
id|mixer_mutex
suffix:semicolon
DECL|member|firmware
r_const
r_struct
id|firmware
op_star
id|firmware
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* loaded firmware data */
)brace
suffix:semicolon
multiline_comment|/*&n; * constructor&n; */
id|vx_core_t
op_star
id|snd_vx_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|snd_vx_hardware
op_star
id|hw
comma
r_struct
id|snd_vx_ops
op_star
id|ops
comma
r_int
id|extra_size
)paren
suffix:semicolon
r_int
id|snd_vx_setup_firmware
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_vx_load_boot_image
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_const
r_struct
id|firmware
op_star
id|dsp
)paren
suffix:semicolon
r_int
id|snd_vx_dsp_boot
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_const
r_struct
id|firmware
op_star
id|dsp
)paren
suffix:semicolon
r_int
id|snd_vx_dsp_load
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_const
r_struct
id|firmware
op_star
id|dsp
)paren
suffix:semicolon
r_void
id|snd_vx_free_firmware
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/*&n; * interrupt handler; exported for pcmcia&n; */
id|irqreturn_t
id|snd_vx_irq_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * lowlevel functions&n; */
DECL|function|vx_test_and_ack
r_inline
r_static
r_int
id|vx_test_and_ack
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;test_and_ack
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_return
id|chip-&gt;ops
op_member_access_from_pointer
id|test_and_ack
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
DECL|function|vx_validate_irq
r_inline
r_static
r_void
id|vx_validate_irq
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|enable
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;validate_irq
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|validate_irq
c_func
(paren
id|chip
comma
id|enable
)paren
suffix:semicolon
)brace
DECL|function|snd_vx_inb
r_inline
r_static
r_int
r_char
id|snd_vx_inb
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;in8
comma
r_return
l_int|0
)paren
suffix:semicolon
r_return
id|chip-&gt;ops
op_member_access_from_pointer
id|in8
c_func
(paren
id|chip
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|function|snd_vx_inl
r_inline
r_static
r_int
r_int
id|snd_vx_inl
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;in32
comma
r_return
l_int|0
)paren
suffix:semicolon
r_return
id|chip-&gt;ops
op_member_access_from_pointer
id|in32
c_func
(paren
id|chip
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|function|snd_vx_outb
r_inline
r_static
r_void
id|snd_vx_outb
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;out8
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|out8
c_func
(paren
id|chip
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|snd_vx_outl
r_inline
r_static
r_void
id|snd_vx_outl
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
comma
r_int
r_int
id|val
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;out32
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|out32
c_func
(paren
id|chip
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
DECL|macro|vx_inb
mdefine_line|#define vx_inb(chip,reg)&t;snd_vx_inb(chip, VX_##reg)
DECL|macro|vx_outb
mdefine_line|#define vx_outb(chip,reg,val)&t;snd_vx_outb(chip, VX_##reg,val)
DECL|macro|vx_inl
mdefine_line|#define vx_inl(chip,reg)&t;snd_vx_inl(chip, VX_##reg)
DECL|macro|vx_outl
mdefine_line|#define vx_outl(chip,reg,val)&t;snd_vx_outl(chip, VX_##reg,val)
r_void
id|snd_vx_delay
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|msec
)paren
suffix:semicolon
DECL|function|vx_reset_dsp
r_static
r_inline
r_void
id|vx_reset_dsp
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;reset_dsp
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|reset_dsp
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
r_int
id|vx_send_msg
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_struct
id|vx_rmh
op_star
id|rmh
)paren
suffix:semicolon
r_int
id|vx_send_msg_nolock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_struct
id|vx_rmh
op_star
id|rmh
)paren
suffix:semicolon
r_int
id|vx_send_rih
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|cmd
)paren
suffix:semicolon
r_int
id|vx_send_rih_nolock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|cmd
)paren
suffix:semicolon
r_void
id|vx_reset_codec
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|cold_reset
)paren
suffix:semicolon
multiline_comment|/*&n; * check the bit on the specified register&n; * returns zero if a bit matches, or a negative error code.&n; * exported for vxpocket driver&n; */
r_int
id|snd_vx_check_reg_bit
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|reg
comma
r_int
id|mask
comma
r_int
id|bit
comma
r_int
id|time
)paren
suffix:semicolon
DECL|macro|vx_check_isr
mdefine_line|#define vx_check_isr(chip,mask,bit,time) snd_vx_check_reg_bit(chip, VX_ISR, mask, bit, time)
DECL|macro|vx_wait_isr_bit
mdefine_line|#define vx_wait_isr_bit(chip,bit) vx_check_isr(chip, bit, bit, 200)
DECL|macro|vx_wait_for_rx_full
mdefine_line|#define vx_wait_for_rx_full(chip) vx_wait_isr_bit(chip, ISR_RX_FULL)
multiline_comment|/*&n; * pseudo-DMA transfer&n; */
DECL|function|vx_pseudo_dma_write
r_inline
r_static
r_void
id|vx_pseudo_dma_write
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
id|snd_pcm_runtime_t
op_star
id|runtime
comma
id|vx_pipe_t
op_star
id|pipe
comma
r_int
id|count
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;dma_write
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|dma_write
c_func
(paren
id|chip
comma
id|runtime
comma
id|pipe
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|vx_pseudo_dma_read
r_inline
r_static
r_void
id|vx_pseudo_dma_read
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
id|snd_pcm_runtime_t
op_star
id|runtime
comma
id|vx_pipe_t
op_star
id|pipe
comma
r_int
id|count
)paren
(brace
id|snd_assert
c_func
(paren
id|chip-&gt;ops-&gt;dma_read
comma
r_return
)paren
suffix:semicolon
id|chip-&gt;ops
op_member_access_from_pointer
id|dma_read
c_func
(paren
id|chip
comma
id|runtime
comma
id|pipe
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* error with hardware code,&n; * the return value is -(VX_ERR_MASK | actual-hw-error-code)&n; */
DECL|macro|VX_ERR_MASK
mdefine_line|#define VX_ERR_MASK&t;0x1000000
DECL|macro|vx_get_error
mdefine_line|#define vx_get_error(err)&t;(-(err) &amp; ~VX_ERR_MASK)
multiline_comment|/*&n; * pcm stuff&n; */
r_int
id|snd_vx_pcm_new
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|vx_pcm_update_intr
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|events
)paren
suffix:semicolon
multiline_comment|/*&n; * mixer stuff&n; */
r_int
id|snd_vx_mixer_new
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|vx_toggle_dac_mute
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|mute
)paren
suffix:semicolon
r_int
id|vx_sync_audio_source
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|vx_set_monitor_level
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|audio
comma
r_int
id|level
comma
r_int
id|active
)paren
suffix:semicolon
multiline_comment|/*&n; * IEC958 &amp; clock stuff&n; */
r_void
id|vx_set_iec958_status
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|bits
)paren
suffix:semicolon
r_int
id|vx_set_clock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|freq
)paren
suffix:semicolon
r_void
id|vx_set_internal_clock
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
r_int
id|freq
)paren
suffix:semicolon
r_int
id|vx_change_frequency
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/*&n; * hardware constants&n; */
DECL|macro|vx_has_new_dsp
mdefine_line|#define vx_has_new_dsp(chip)&t;((chip)-&gt;type != VX_TYPE_BOARD)
DECL|macro|vx_is_pcmcia
mdefine_line|#define vx_is_pcmcia(chip)&t;((chip)-&gt;type &gt;= VX_TYPE_VXPOCKET)
multiline_comment|/* audio input source */
r_enum
(brace
DECL|enumerator|VX_AUDIO_SRC_DIGITAL
id|VX_AUDIO_SRC_DIGITAL
comma
DECL|enumerator|VX_AUDIO_SRC_LINE
id|VX_AUDIO_SRC_LINE
comma
DECL|enumerator|VX_AUDIO_SRC_MIC
id|VX_AUDIO_SRC_MIC
)brace
suffix:semicolon
multiline_comment|/* clock source */
r_enum
(brace
DECL|enumerator|INTERNAL_QUARTZ
id|INTERNAL_QUARTZ
comma
DECL|enumerator|UER_SYNC
id|UER_SYNC
)brace
suffix:semicolon
multiline_comment|/* clock mode */
r_enum
(brace
DECL|enumerator|VX_CLOCK_MODE_AUTO
id|VX_CLOCK_MODE_AUTO
comma
multiline_comment|/* depending on the current audio source */
DECL|enumerator|VX_CLOCK_MODE_INTERNAL
id|VX_CLOCK_MODE_INTERNAL
comma
multiline_comment|/* fixed to internal quartz */
DECL|enumerator|VX_CLOCK_MODE_EXTERNAL
id|VX_CLOCK_MODE_EXTERNAL
multiline_comment|/* fixed to UER sync */
)brace
suffix:semicolon
multiline_comment|/* SPDIF/UER type */
r_enum
(brace
DECL|enumerator|VX_UER_MODE_CONSUMER
id|VX_UER_MODE_CONSUMER
comma
DECL|enumerator|VX_UER_MODE_PROFESSIONAL
id|VX_UER_MODE_PROFESSIONAL
comma
DECL|enumerator|VX_UER_MODE_NOT_PRESENT
id|VX_UER_MODE_NOT_PRESENT
comma
)brace
suffix:semicolon
multiline_comment|/* register indices */
r_enum
(brace
DECL|enumerator|VX_ICR
id|VX_ICR
comma
DECL|enumerator|VX_CVR
id|VX_CVR
comma
DECL|enumerator|VX_ISR
id|VX_ISR
comma
DECL|enumerator|VX_IVR
id|VX_IVR
comma
DECL|enumerator|VX_RXH
id|VX_RXH
comma
DECL|enumerator|VX_TXH
id|VX_TXH
op_assign
id|VX_RXH
comma
DECL|enumerator|VX_RXM
id|VX_RXM
comma
DECL|enumerator|VX_TXM
id|VX_TXM
op_assign
id|VX_RXM
comma
DECL|enumerator|VX_RXL
id|VX_RXL
comma
DECL|enumerator|VX_TXL
id|VX_TXL
op_assign
id|VX_RXL
comma
DECL|enumerator|VX_DMA
id|VX_DMA
comma
DECL|enumerator|VX_CDSP
id|VX_CDSP
comma
DECL|enumerator|VX_RFREQ
id|VX_RFREQ
comma
DECL|enumerator|VX_RUER_V2
id|VX_RUER_V2
comma
DECL|enumerator|VX_GAIN
id|VX_GAIN
comma
DECL|enumerator|VX_DATA
id|VX_DATA
op_assign
id|VX_GAIN
comma
DECL|enumerator|VX_MEMIRQ
id|VX_MEMIRQ
comma
DECL|enumerator|VX_ACQ
id|VX_ACQ
comma
DECL|enumerator|VX_BIT0
id|VX_BIT0
comma
DECL|enumerator|VX_BIT1
id|VX_BIT1
comma
DECL|enumerator|VX_MIC0
id|VX_MIC0
comma
DECL|enumerator|VX_MIC1
id|VX_MIC1
comma
DECL|enumerator|VX_MIC2
id|VX_MIC2
comma
DECL|enumerator|VX_MIC3
id|VX_MIC3
comma
DECL|enumerator|VX_PLX0
id|VX_PLX0
comma
DECL|enumerator|VX_PLX1
id|VX_PLX1
comma
DECL|enumerator|VX_PLX2
id|VX_PLX2
comma
DECL|enumerator|VX_LOFREQ
id|VX_LOFREQ
comma
singleline_comment|// V2: ACQ, VP: RFREQ
DECL|enumerator|VX_HIFREQ
id|VX_HIFREQ
comma
singleline_comment|// V2: BIT0, VP: RUER_V2
DECL|enumerator|VX_CSUER
id|VX_CSUER
comma
singleline_comment|// V2: BIT1, VP: BIT0
DECL|enumerator|VX_RUER
id|VX_RUER
comma
singleline_comment|// V2: RUER_V2, VP: BIT1
DECL|enumerator|VX_REG_MAX
id|VX_REG_MAX
comma
multiline_comment|/* aliases for VX board */
DECL|enumerator|VX_RESET_DMA
id|VX_RESET_DMA
op_assign
id|VX_ISR
comma
DECL|enumerator|VX_CFG
id|VX_CFG
op_assign
id|VX_RFREQ
comma
DECL|enumerator|VX_STATUS
id|VX_STATUS
op_assign
id|VX_MEMIRQ
comma
DECL|enumerator|VX_SELMIC
id|VX_SELMIC
op_assign
id|VX_MIC0
comma
DECL|enumerator|VX_COMPOT
id|VX_COMPOT
op_assign
id|VX_MIC1
comma
DECL|enumerator|VX_SCOMPR
id|VX_SCOMPR
op_assign
id|VX_MIC2
comma
DECL|enumerator|VX_GLIMIT
id|VX_GLIMIT
op_assign
id|VX_MIC3
comma
DECL|enumerator|VX_INTCSR
id|VX_INTCSR
op_assign
id|VX_PLX0
comma
DECL|enumerator|VX_CNTRL
id|VX_CNTRL
op_assign
id|VX_PLX1
comma
DECL|enumerator|VX_GPIOC
id|VX_GPIOC
op_assign
id|VX_PLX2
comma
multiline_comment|/* aliases for VXPOCKET board */
DECL|enumerator|VX_MICRO
id|VX_MICRO
op_assign
id|VX_MEMIRQ
comma
DECL|enumerator|VX_CODEC2
id|VX_CODEC2
op_assign
id|VX_MEMIRQ
comma
DECL|enumerator|VX_DIALOG
id|VX_DIALOG
op_assign
id|VX_ACQ
comma
)brace
suffix:semicolon
multiline_comment|/* RMH status type */
r_enum
(brace
DECL|enumerator|RMH_SSIZE_FIXED
id|RMH_SSIZE_FIXED
op_assign
l_int|0
comma
multiline_comment|/* status size given by the driver (in LgStat) */
DECL|enumerator|RMH_SSIZE_ARG
id|RMH_SSIZE_ARG
op_assign
l_int|1
comma
multiline_comment|/* status size given in the LSB byte */
DECL|enumerator|RMH_SSIZE_MASK
id|RMH_SSIZE_MASK
op_assign
l_int|2
comma
multiline_comment|/* status size given in bitmask */
)brace
suffix:semicolon
multiline_comment|/* bits for ICR register */
DECL|macro|ICR_HF1
mdefine_line|#define ICR_HF1&t;&t;0x10
DECL|macro|ICR_HF0
mdefine_line|#define ICR_HF0&t;&t;0x08
DECL|macro|ICR_TREQ
mdefine_line|#define ICR_TREQ&t;0x02&t;/* Interrupt mode + HREQ set on for transfer (-&gt;DSP) request */
DECL|macro|ICR_RREQ
mdefine_line|#define ICR_RREQ&t;0x01&t;/* Interrupt mode + RREQ set on for transfer (-&gt;PC) request */
multiline_comment|/* bits for CVR register */
DECL|macro|CVR_HC
mdefine_line|#define CVR_HC&t;&t;0x80
multiline_comment|/* bits for ISR register */
DECL|macro|ISR_HF3
mdefine_line|#define ISR_HF3&t;&t;0x10
DECL|macro|ISR_HF2
mdefine_line|#define ISR_HF2&t;&t;0x08
DECL|macro|ISR_CHK
mdefine_line|#define ISR_CHK&t;&t;0x10
DECL|macro|ISR_ERR
mdefine_line|#define ISR_ERR&t;&t;0x08
DECL|macro|ISR_TX_READY
mdefine_line|#define ISR_TX_READY&t;0x04
DECL|macro|ISR_TX_EMPTY
mdefine_line|#define ISR_TX_EMPTY&t;0x02
DECL|macro|ISR_RX_FULL
mdefine_line|#define ISR_RX_FULL&t;0x01
multiline_comment|/* Constants used to access the DATA register */
DECL|macro|VX_DATA_CODEC_MASK
mdefine_line|#define VX_DATA_CODEC_MASK&t;0x80
DECL|macro|VX_DATA_XICOR_MASK
mdefine_line|#define VX_DATA_XICOR_MASK&t;0x80
multiline_comment|/* Constants used to access the CSUER register (both for VX2 and VXP) */
DECL|macro|VX_SUER_FREQ_MASK
mdefine_line|#define VX_SUER_FREQ_MASK&t;&t;0x0c
DECL|macro|VX_SUER_FREQ_32KHz_MASK
mdefine_line|#define VX_SUER_FREQ_32KHz_MASK&t;&t;0x0c
DECL|macro|VX_SUER_FREQ_44KHz_MASK
mdefine_line|#define VX_SUER_FREQ_44KHz_MASK&t;&t;0x00
DECL|macro|VX_SUER_FREQ_48KHz_MASK
mdefine_line|#define VX_SUER_FREQ_48KHz_MASK&t;&t;0x04
DECL|macro|VX_SUER_DATA_PRESENT_MASK
mdefine_line|#define VX_SUER_DATA_PRESENT_MASK&t;0x02
DECL|macro|VX_SUER_CLOCK_PRESENT_MASK
mdefine_line|#define VX_SUER_CLOCK_PRESENT_MASK&t;0x01
DECL|macro|VX_CUER_HH_BITC_SEL_MASK
mdefine_line|#define VX_CUER_HH_BITC_SEL_MASK&t;0x08
DECL|macro|VX_CUER_MH_BITC_SEL_MASK
mdefine_line|#define VX_CUER_MH_BITC_SEL_MASK&t;0x04
DECL|macro|VX_CUER_ML_BITC_SEL_MASK
mdefine_line|#define VX_CUER_ML_BITC_SEL_MASK&t;0x02
DECL|macro|VX_CUER_LL_BITC_SEL_MASK
mdefine_line|#define VX_CUER_LL_BITC_SEL_MASK&t;0x01
DECL|macro|XX_UER_CBITS_OFFSET_MASK
mdefine_line|#define XX_UER_CBITS_OFFSET_MASK&t;0x1f
multiline_comment|/* bits for audio_info */
DECL|macro|VX_AUDIO_INFO_REAL_TIME
mdefine_line|#define VX_AUDIO_INFO_REAL_TIME&t;(1&lt;&lt;0)&t;/* real-time processing available */
DECL|macro|VX_AUDIO_INFO_OFFLINE
mdefine_line|#define VX_AUDIO_INFO_OFFLINE&t;(1&lt;&lt;1)&t;/* offline processing available */
DECL|macro|VX_AUDIO_INFO_MPEG1
mdefine_line|#define VX_AUDIO_INFO_MPEG1&t;(1&lt;&lt;5)
DECL|macro|VX_AUDIO_INFO_MPEG2
mdefine_line|#define VX_AUDIO_INFO_MPEG2&t;(1&lt;&lt;6)
DECL|macro|VX_AUDIO_INFO_LINEAR_8
mdefine_line|#define VX_AUDIO_INFO_LINEAR_8&t;(1&lt;&lt;7)
DECL|macro|VX_AUDIO_INFO_LINEAR_16
mdefine_line|#define VX_AUDIO_INFO_LINEAR_16&t;(1&lt;&lt;8)
DECL|macro|VX_AUDIO_INFO_LINEAR_24
mdefine_line|#define VX_AUDIO_INFO_LINEAR_24&t;(1&lt;&lt;9)
multiline_comment|/* DSP Interrupt Request values */
DECL|macro|VXP_IRQ_OFFSET
mdefine_line|#define VXP_IRQ_OFFSET&t;&t;0x40 /* add 0x40 offset for vxpocket and vx222/v2 */
multiline_comment|/* call with vx_send_irq_dsp() */
DECL|macro|IRQ_MESS_WRITE_END
mdefine_line|#define IRQ_MESS_WRITE_END          0x30
DECL|macro|IRQ_MESS_WRITE_NEXT
mdefine_line|#define IRQ_MESS_WRITE_NEXT         0x32
DECL|macro|IRQ_MESS_READ_NEXT
mdefine_line|#define IRQ_MESS_READ_NEXT          0x34
DECL|macro|IRQ_MESS_READ_END
mdefine_line|#define IRQ_MESS_READ_END           0x36
DECL|macro|IRQ_MESSAGE
mdefine_line|#define IRQ_MESSAGE                 0x38
DECL|macro|IRQ_RESET_CHK
mdefine_line|#define IRQ_RESET_CHK               0x3A
DECL|macro|IRQ_CONNECT_STREAM_NEXT
mdefine_line|#define IRQ_CONNECT_STREAM_NEXT     0x26
DECL|macro|IRQ_CONNECT_STREAM_END
mdefine_line|#define IRQ_CONNECT_STREAM_END      0x28
DECL|macro|IRQ_PAUSE_START_CONNECT
mdefine_line|#define IRQ_PAUSE_START_CONNECT     0x2A
DECL|macro|IRQ_END_CONNECTION
mdefine_line|#define IRQ_END_CONNECTION          0x2C
multiline_comment|/* Is there async. events pending ( IT Source Test ) */
DECL|macro|ASYNC_EVENTS_PENDING
mdefine_line|#define ASYNC_EVENTS_PENDING            0x008000
DECL|macro|HBUFFER_EVENTS_PENDING
mdefine_line|#define HBUFFER_EVENTS_PENDING          0x004000   
singleline_comment|// Not always accurate
DECL|macro|NOTIF_EVENTS_PENDING
mdefine_line|#define NOTIF_EVENTS_PENDING            0x002000
DECL|macro|TIME_CODE_EVENT_PENDING
mdefine_line|#define TIME_CODE_EVENT_PENDING         0x001000
DECL|macro|FREQUENCY_CHANGE_EVENT_PENDING
mdefine_line|#define FREQUENCY_CHANGE_EVENT_PENDING  0x000800
DECL|macro|END_OF_BUFFER_EVENTS_PENDING
mdefine_line|#define END_OF_BUFFER_EVENTS_PENDING    0x000400
DECL|macro|FATAL_DSP_ERROR
mdefine_line|#define FATAL_DSP_ERROR                 0xff0000
multiline_comment|/* Stream Format Header Defines */
DECL|macro|HEADER_FMT_BASE
mdefine_line|#define HEADER_FMT_BASE&t;&t;&t;0xFED00000
DECL|macro|HEADER_FMT_MONO
mdefine_line|#define HEADER_FMT_MONO&t;&t;&t;0x000000C0
DECL|macro|HEADER_FMT_INTEL
mdefine_line|#define HEADER_FMT_INTEL&t;&t;0x00008000
DECL|macro|HEADER_FMT_16BITS
mdefine_line|#define HEADER_FMT_16BITS&t;&t;0x00002000
DECL|macro|HEADER_FMT_24BITS
mdefine_line|#define HEADER_FMT_24BITS&t;&t;0x00004000
DECL|macro|HEADER_FMT_UPTO11
mdefine_line|#define HEADER_FMT_UPTO11&t;&t;0x00000200&t;/* frequency is less or equ. to 11k.*/
DECL|macro|HEADER_FMT_UPTO32
mdefine_line|#define HEADER_FMT_UPTO32&t;&t;0x00000100&t;/* frequency is over 11k and less then 32k.*/
multiline_comment|/* Constants used to access the Codec */
DECL|macro|XX_CODEC_SELECTOR
mdefine_line|#define XX_CODEC_SELECTOR               0x20
multiline_comment|/* codec commands */
DECL|macro|XX_CODEC_ADC_CONTROL_REGISTER
mdefine_line|#define XX_CODEC_ADC_CONTROL_REGISTER   0x01
DECL|macro|XX_CODEC_DAC_CONTROL_REGISTER
mdefine_line|#define XX_CODEC_DAC_CONTROL_REGISTER   0x02
DECL|macro|XX_CODEC_LEVEL_LEFT_REGISTER
mdefine_line|#define XX_CODEC_LEVEL_LEFT_REGISTER    0x03
DECL|macro|XX_CODEC_LEVEL_RIGHT_REGISTER
mdefine_line|#define XX_CODEC_LEVEL_RIGHT_REGISTER   0x04
DECL|macro|XX_CODEC_PORT_MODE_REGISTER
mdefine_line|#define XX_CODEC_PORT_MODE_REGISTER     0x05
DECL|macro|XX_CODEC_STATUS_REPORT_REGISTER
mdefine_line|#define XX_CODEC_STATUS_REPORT_REGISTER 0x06
DECL|macro|XX_CODEC_CLOCK_CONTROL_REGISTER
mdefine_line|#define XX_CODEC_CLOCK_CONTROL_REGISTER 0x07
multiline_comment|/*&n; * Audio-level control values&n; */
DECL|macro|CVAL_M110DB
mdefine_line|#define CVAL_M110DB&t;&t;0x000&t;/* -110dB */
DECL|macro|CVAL_M99DB
mdefine_line|#define CVAL_M99DB&t;&t;0x02C
DECL|macro|CVAL_M21DB
mdefine_line|#define CVAL_M21DB&t;&t;0x163
DECL|macro|CVAL_M18DB
mdefine_line|#define CVAL_M18DB&t;&t;0x16F
DECL|macro|CVAL_M10DB
mdefine_line|#define CVAL_M10DB&t;&t;0x18F
DECL|macro|CVAL_0DB
mdefine_line|#define CVAL_0DB&t;&t;0x1B7
DECL|macro|CVAL_18DB
mdefine_line|#define CVAL_18DB&t;&t;0x1FF&t;/* +18dB */
DECL|macro|CVAL_MAX
mdefine_line|#define CVAL_MAX&t;&t;0x1FF
DECL|macro|AUDIO_IO_HAS_MUTE_LEVEL
mdefine_line|#define AUDIO_IO_HAS_MUTE_LEVEL&t;&t;&t;0x400000
DECL|macro|AUDIO_IO_HAS_MUTE_MONITORING_1
mdefine_line|#define AUDIO_IO_HAS_MUTE_MONITORING_1&t;&t;0x200000
DECL|macro|AUDIO_IO_HAS_MUTE_MONITORING_2
mdefine_line|#define AUDIO_IO_HAS_MUTE_MONITORING_2&t;&t;0x100000
DECL|macro|VALID_AUDIO_IO_DIGITAL_LEVEL
mdefine_line|#define VALID_AUDIO_IO_DIGITAL_LEVEL&t;&t;0x01
DECL|macro|VALID_AUDIO_IO_MONITORING_LEVEL
mdefine_line|#define VALID_AUDIO_IO_MONITORING_LEVEL&t;&t;0x02
DECL|macro|VALID_AUDIO_IO_MUTE_LEVEL
mdefine_line|#define VALID_AUDIO_IO_MUTE_LEVEL&t;&t;0x04
DECL|macro|VALID_AUDIO_IO_MUTE_MONITORING_1
mdefine_line|#define VALID_AUDIO_IO_MUTE_MONITORING_1&t;0x08
DECL|macro|VALID_AUDIO_IO_MUTE_MONITORING_2
mdefine_line|#define VALID_AUDIO_IO_MUTE_MONITORING_2&t;0x10
macro_line|#endif /* __SOUND_VX_COMMON_H */
eof
