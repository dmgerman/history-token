multiline_comment|/*&n; * Driver for PowerMac onboard soundchips&n; * Copyright (c) 2001 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *   based on dmasound.c.&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __PMAC_H
DECL|macro|__PMAC_H
mdefine_line|#define __PMAC_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &quot;awacs.h&quot;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#ifdef CONFIG_ADB_CUDA
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ADB_PMU
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;asm/dbdma.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* maximum number of fragments */
DECL|macro|PMAC_MAX_FRAGS
mdefine_line|#define PMAC_MAX_FRAGS&t;&t;32
DECL|macro|PMAC_SUPPORT_AUTOMUTE
mdefine_line|#define PMAC_SUPPORT_AUTOMUTE
multiline_comment|/*&n; * typedefs&n; */
DECL|typedef|pmac_t
r_typedef
r_struct
id|snd_pmac
id|pmac_t
suffix:semicolon
DECL|typedef|pmac_stream_t
r_typedef
r_struct
id|snd_pmac_stream
id|pmac_stream_t
suffix:semicolon
DECL|typedef|pmac_beep_t
r_typedef
r_struct
id|snd_pmac_beep
id|pmac_beep_t
suffix:semicolon
DECL|typedef|pmac_dbdma_t
r_typedef
r_struct
id|snd_pmac_dbdma
id|pmac_dbdma_t
suffix:semicolon
multiline_comment|/*&n; * DBDMA space&n; */
DECL|struct|snd_pmac_dbdma
r_struct
id|snd_pmac_dbdma
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|cmds
r_struct
id|dbdma_cmd
id|__iomem
op_star
id|cmds
suffix:semicolon
DECL|member|space
r_void
op_star
id|space
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * playback/capture stream&n; */
DECL|struct|snd_pmac_stream
r_struct
id|snd_pmac_stream
(brace
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* boolean */
DECL|member|stream
r_int
id|stream
suffix:semicolon
multiline_comment|/* PLAYBACK/CAPTURE */
DECL|member|dma_size
r_int
id|dma_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|period_size
r_int
id|period_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* in kbytes */
DECL|member|nperiods
DECL|member|cur_period
r_int
id|nperiods
comma
id|cur_period
suffix:semicolon
DECL|member|cmd
id|pmac_dbdma_t
id|cmd
suffix:semicolon
DECL|member|dma
r_volatile
r_struct
id|dbdma_regs
id|__iomem
op_star
id|dma
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|cur_freqs
r_int
r_int
id|cur_freqs
suffix:semicolon
multiline_comment|/* currently available frequencies */
DECL|member|cur_formats
r_int
r_int
id|cur_formats
suffix:semicolon
multiline_comment|/* currently available formats */
)brace
suffix:semicolon
multiline_comment|/*&n; */
DECL|enum|snd_pmac_model
r_enum
id|snd_pmac_model
(brace
DECL|enumerator|PMAC_AWACS
DECL|enumerator|PMAC_SCREAMER
DECL|enumerator|PMAC_BURGUNDY
DECL|enumerator|PMAC_DACA
DECL|enumerator|PMAC_TUMBLER
DECL|enumerator|PMAC_SNAPPER
id|PMAC_AWACS
comma
id|PMAC_SCREAMER
comma
id|PMAC_BURGUNDY
comma
id|PMAC_DACA
comma
id|PMAC_TUMBLER
comma
id|PMAC_SNAPPER
)brace
suffix:semicolon
DECL|struct|snd_pmac
r_struct
id|snd_pmac
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* h/w info */
DECL|member|node
r_struct
id|device_node
op_star
id|node
suffix:semicolon
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
DECL|member|manufacturer
r_int
r_int
id|manufacturer
suffix:semicolon
DECL|member|subframe
r_int
r_int
id|subframe
suffix:semicolon
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
DECL|member|model
r_enum
id|snd_pmac_model
id|model
suffix:semicolon
DECL|member|has_iic
r_int
r_int
id|has_iic
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_pbook_3400
r_int
r_int
id|is_pbook_3400
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_pbook_G3
r_int
r_int
id|is_pbook_G3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|can_byte_swap
r_int
r_int
id|can_byte_swap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|can_duplex
r_int
r_int
id|can_duplex
suffix:colon
l_int|1
suffix:semicolon
DECL|member|can_capture
r_int
r_int
id|can_capture
suffix:colon
l_int|1
suffix:semicolon
DECL|member|auto_mute
r_int
r_int
id|auto_mute
suffix:colon
l_int|1
suffix:semicolon
DECL|member|initialized
r_int
r_int
id|initialized
suffix:colon
l_int|1
suffix:semicolon
DECL|member|feature_is_set
r_int
r_int
id|feature_is_set
suffix:colon
l_int|1
suffix:semicolon
DECL|member|of_requested
r_int
r_int
id|of_requested
suffix:semicolon
DECL|member|num_freqs
r_int
id|num_freqs
suffix:semicolon
DECL|member|freq_table
r_int
op_star
id|freq_table
suffix:semicolon
DECL|member|freqs_ok
r_int
r_int
id|freqs_ok
suffix:semicolon
multiline_comment|/* bit flags */
DECL|member|formats_ok
r_int
r_int
id|formats_ok
suffix:semicolon
multiline_comment|/* pcm hwinfo */
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|rate_index
r_int
id|rate_index
suffix:semicolon
DECL|member|format
r_int
id|format
suffix:semicolon
multiline_comment|/* current format */
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|awacs
r_volatile
r_struct
id|awacs_regs
id|__iomem
op_star
id|awacs
suffix:semicolon
DECL|member|awacs_reg
r_int
id|awacs_reg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* register cache */
DECL|member|hp_stat_mask
r_int
r_int
id|hp_stat_mask
suffix:semicolon
DECL|member|latch_base
r_int
r_char
id|__iomem
op_star
id|latch_base
suffix:semicolon
DECL|member|macio_base
r_int
r_char
id|__iomem
op_star
id|macio_base
suffix:semicolon
DECL|member|playback
id|pmac_stream_t
id|playback
suffix:semicolon
DECL|member|capture
id|pmac_stream_t
id|capture
suffix:semicolon
DECL|member|extra_dma
id|pmac_dbdma_t
id|extra_dma
suffix:semicolon
DECL|member|irq
DECL|member|tx_irq
DECL|member|rx_irq
r_int
id|irq
comma
id|tx_irq
comma
id|rx_irq
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|beep
id|pmac_beep_t
op_star
id|beep
suffix:semicolon
DECL|member|control_mask
r_int
r_int
id|control_mask
suffix:semicolon
multiline_comment|/* control mask */
multiline_comment|/* mixer stuffs */
DECL|member|mixer_data
r_void
op_star
id|mixer_data
suffix:semicolon
DECL|member|mixer_free
r_void
(paren
op_star
id|mixer_free
)paren
(paren
id|pmac_t
op_star
)paren
suffix:semicolon
DECL|member|master_sw_ctl
id|snd_kcontrol_t
op_star
id|master_sw_ctl
suffix:semicolon
DECL|member|speaker_sw_ctl
id|snd_kcontrol_t
op_star
id|speaker_sw_ctl
suffix:semicolon
DECL|member|drc_sw_ctl
id|snd_kcontrol_t
op_star
id|drc_sw_ctl
suffix:semicolon
multiline_comment|/* only used for tumbler -ReneR */
DECL|member|hp_detect_ctl
id|snd_kcontrol_t
op_star
id|hp_detect_ctl
suffix:semicolon
multiline_comment|/* lowlevel callbacks */
DECL|member|set_format
r_void
(paren
op_star
id|set_format
)paren
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
DECL|member|update_automute
r_void
(paren
op_star
id|update_automute
)paren
(paren
id|pmac_t
op_star
id|chip
comma
r_int
id|do_notify
)paren
suffix:semicolon
DECL|member|detect_headphone
r_int
(paren
op_star
id|detect_headphone
)paren
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
DECL|member|suspend
r_void
(paren
op_star
id|suspend
)paren
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* exported functions */
r_int
id|snd_pmac_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|pmac_t
op_star
op_star
id|chip_return
)paren
suffix:semicolon
r_int
id|snd_pmac_pcm_new
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_pmac_attach_beep
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|snd_pmac_detach_beep
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|snd_pmac_beep_stop
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_int
r_int
id|snd_pmac_rate_index
c_func
(paren
id|pmac_t
op_star
id|chip
comma
id|pmac_stream_t
op_star
id|rec
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
r_void
id|snd_pmac_beep_dma_start
c_func
(paren
id|pmac_t
op_star
id|chip
comma
r_int
id|bytes
comma
r_int
r_int
id|addr
comma
r_int
id|speed
)paren
suffix:semicolon
r_void
id|snd_pmac_beep_dma_stop
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/* initialize mixer */
r_int
id|snd_pmac_awacs_init
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_pmac_burgundy_init
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_pmac_daca_init
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_pmac_tumbler_init
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_pmac_tumbler_post_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* i2c functions */
DECL|struct|snd_pmac_keywest
r_typedef
r_struct
id|snd_pmac_keywest
(brace
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|client
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|init_client
r_int
(paren
op_star
id|init_client
)paren
(paren
r_struct
id|snd_pmac_keywest
op_star
id|i2c
)paren
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|typedef|pmac_keywest_t
)brace
id|pmac_keywest_t
suffix:semicolon
r_int
id|snd_pmac_keywest_init
c_func
(paren
id|pmac_keywest_t
op_star
id|i2c
)paren
suffix:semicolon
r_void
id|snd_pmac_keywest_cleanup
c_func
(paren
id|pmac_keywest_t
op_star
id|i2c
)paren
suffix:semicolon
multiline_comment|/* misc */
r_int
id|snd_pmac_boolean_stereo_info
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
suffix:semicolon
r_int
id|snd_pmac_boolean_mono_info
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
suffix:semicolon
r_int
id|snd_pmac_add_automute
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
suffix:semicolon
DECL|macro|big_mdelay
mdefine_line|#define big_mdelay(msec) do {&bslash;&n;&t;set_current_state(TASK_UNINTERRUPTIBLE);&bslash;&n;&t;schedule_timeout(((msec) * HZ + 999) / 1000);&bslash;&n;} while (0)
macro_line|#endif /* __PMAC_H */
eof
