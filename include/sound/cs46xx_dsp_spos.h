multiline_comment|/*&n; *  The driver for the Cirrus Logic&squot;s Sound Fusion CS46XX based soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __CS46XX_DSP_SPOS_H__
DECL|macro|__CS46XX_DSP_SPOS_H__
mdefine_line|#define __CS46XX_DSP_SPOS_H__
macro_line|#include &quot;cs46xx_dsp_scb_types.h&quot;
macro_line|#include &quot;cs46xx_dsp_task_types.h&quot;
DECL|macro|SYMBOL_CONSTANT
mdefine_line|#define SYMBOL_CONSTANT  0x0
DECL|macro|SYMBOL_SAMPLE
mdefine_line|#define SYMBOL_SAMPLE    0x1
DECL|macro|SYMBOL_PARAMETER
mdefine_line|#define SYMBOL_PARAMETER 0x2
DECL|macro|SYMBOL_CODE
mdefine_line|#define SYMBOL_CODE      0x3
DECL|macro|SEGTYPE_SP_PROGRAM
mdefine_line|#define SEGTYPE_SP_PROGRAM              0x00000001
DECL|macro|SEGTYPE_SP_PARAMETER
mdefine_line|#define SEGTYPE_SP_PARAMETER            0x00000002
DECL|macro|SEGTYPE_SP_SAMPLE
mdefine_line|#define SEGTYPE_SP_SAMPLE               0x00000003
DECL|macro|SEGTYPE_SP_COEFFICIENT
mdefine_line|#define SEGTYPE_SP_COEFFICIENT          0x00000004
DECL|macro|DSP_SPOS_UU
mdefine_line|#define DSP_SPOS_UU      0x0deadul     /* unused */
DECL|macro|DSP_SPOS_DC
mdefine_line|#define DSP_SPOS_DC      0x0badul      /* dont care */
DECL|macro|DSP_SPOS_DC_DC
mdefine_line|#define DSP_SPOS_DC_DC   0x0bad0badul  /* dont care */
DECL|macro|DSP_SPOS_UUUU
mdefine_line|#define DSP_SPOS_UUUU    0xdeadc0edul  /* unused */
DECL|macro|DSP_SPOS_UUHI
mdefine_line|#define DSP_SPOS_UUHI    0xdeadul
DECL|macro|DSP_SPOS_UULO
mdefine_line|#define DSP_SPOS_UULO    0xc0edul
DECL|macro|DSP_SPOS_DCDC
mdefine_line|#define DSP_SPOS_DCDC    0x0badf1d0ul  /* dont care */
DECL|macro|DSP_SPOS_DCDCHI
mdefine_line|#define DSP_SPOS_DCDCHI  0x0badul
DECL|macro|DSP_SPOS_DCDCLO
mdefine_line|#define DSP_SPOS_DCDCLO  0xf1d0ul
DECL|macro|DSP_MAX_TASK_NAME
mdefine_line|#define DSP_MAX_TASK_NAME   60
DECL|macro|DSP_MAX_SYMBOL_NAME
mdefine_line|#define DSP_MAX_SYMBOL_NAME 100
DECL|macro|DSP_MAX_SCB_NAME
mdefine_line|#define DSP_MAX_SCB_NAME    60
DECL|macro|DSP_MAX_SCB_DESC
mdefine_line|#define DSP_MAX_SCB_DESC    200
DECL|macro|DSP_MAX_TASK_DESC
mdefine_line|#define DSP_MAX_TASK_DESC   50
DECL|macro|DSP_MAX_PCM_CHANNELS
mdefine_line|#define DSP_MAX_PCM_CHANNELS 32
DECL|macro|DSP_MAX_SRC_NR
mdefine_line|#define DSP_MAX_SRC_NR       6
DECL|macro|DSP_PCM_MAIN_CHANNEL
mdefine_line|#define DSP_PCM_MAIN_CHANNEL    1
DECL|macro|DSP_PCM_REAR_CHANNEL
mdefine_line|#define DSP_PCM_REAR_CHANNEL    2
DECL|macro|DSP_PCM_CENTER_CHANNEL
mdefine_line|#define DSP_PCM_CENTER_CHANNEL  3
DECL|macro|DSP_PCM_LFE_CHANNEL
mdefine_line|#define DSP_PCM_LFE_CHANNEL     4
DECL|macro|DSP_IEC958_CHANNEL
mdefine_line|#define DSP_IEC958_CHANNEL      5
DECL|macro|DSP_SPDIF_STATUS_OUTPUT_ENABLED
mdefine_line|#define DSP_SPDIF_STATUS_OUTPUT_ENABLED 1
DECL|macro|DSP_SPDIF_STATUS_PLAYBACK_OPEN
mdefine_line|#define DSP_SPDIF_STATUS_PLAYBACK_OPEN  2
DECL|macro|DSP_SPDIF_STATUS_HW_ENABLED
mdefine_line|#define DSP_SPDIF_STATUS_HW_ENABLED     4
r_struct
id|_dsp_module_desc_t
suffix:semicolon
DECL|struct|_symbol_entry_t
r_typedef
r_struct
id|_symbol_entry_t
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|symbol_name
r_char
id|symbol_name
(braket
id|DSP_MAX_SYMBOL_NAME
)braket
suffix:semicolon
DECL|member|symbol_type
r_int
id|symbol_type
suffix:semicolon
multiline_comment|/* initialized by driver */
DECL|member|module
r_struct
id|_dsp_module_desc_t
op_star
id|module
suffix:semicolon
DECL|member|deleted
r_int
id|deleted
suffix:semicolon
DECL|typedef|symbol_entry_t
)brace
id|symbol_entry_t
suffix:semicolon
DECL|struct|_symbol_desc_t
r_typedef
r_struct
id|_symbol_desc_t
(brace
DECL|member|nsymbols
r_int
id|nsymbols
suffix:semicolon
DECL|member|symbols
id|symbol_entry_t
op_star
id|symbols
suffix:semicolon
multiline_comment|/* initialized by driver */
DECL|member|highest_frag_index
r_int
id|highest_frag_index
suffix:semicolon
DECL|typedef|symbol_desc_t
)brace
id|symbol_desc_t
suffix:semicolon
DECL|struct|_segment_desc_t
r_typedef
r_struct
id|_segment_desc_t
(brace
DECL|member|segment_type
r_int
id|segment_type
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|data
id|u32
op_star
id|data
suffix:semicolon
DECL|typedef|segment_desc_t
)brace
id|segment_desc_t
suffix:semicolon
DECL|struct|_dsp_module_desc_t
r_typedef
r_struct
id|_dsp_module_desc_t
(brace
DECL|member|module_name
r_char
op_star
id|module_name
suffix:semicolon
DECL|member|symbol_table
id|symbol_desc_t
id|symbol_table
suffix:semicolon
DECL|member|nsegments
r_int
id|nsegments
suffix:semicolon
DECL|member|segments
id|segment_desc_t
op_star
id|segments
suffix:semicolon
multiline_comment|/* initialized by driver */
DECL|member|overlay_begin_address
id|u32
id|overlay_begin_address
suffix:semicolon
DECL|member|load_address
id|u32
id|load_address
suffix:semicolon
DECL|member|nfixups
r_int
id|nfixups
suffix:semicolon
DECL|typedef|dsp_module_desc_t
)brace
id|dsp_module_desc_t
suffix:semicolon
DECL|struct|_dsp_scb_descriptor_t
r_typedef
r_struct
id|_dsp_scb_descriptor_t
(brace
DECL|member|scb_name
r_char
id|scb_name
(braket
id|DSP_MAX_SCB_NAME
)braket
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|sub_list_ptr
r_struct
id|_dsp_scb_descriptor_t
op_star
id|sub_list_ptr
suffix:semicolon
DECL|member|next_scb_ptr
r_struct
id|_dsp_scb_descriptor_t
op_star
id|next_scb_ptr
suffix:semicolon
DECL|member|parent_scb_ptr
r_struct
id|_dsp_scb_descriptor_t
op_star
id|parent_scb_ptr
suffix:semicolon
DECL|member|task_entry
id|symbol_entry_t
op_star
id|task_entry
suffix:semicolon
DECL|member|scb_symbol
id|symbol_entry_t
op_star
id|scb_symbol
suffix:semicolon
DECL|member|proc_info
id|snd_info_entry_t
op_star
id|proc_info
suffix:semicolon
DECL|member|ref_count
r_int
id|ref_count
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|deleted
r_int
id|deleted
suffix:semicolon
DECL|typedef|dsp_scb_descriptor_t
)brace
id|dsp_scb_descriptor_t
suffix:semicolon
DECL|struct|_dsp_task_descriptor_t
r_typedef
r_struct
id|_dsp_task_descriptor_t
(brace
DECL|member|task_name
r_char
id|task_name
(braket
id|DSP_MAX_TASK_NAME
)braket
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|typedef|dsp_task_descriptor_t
)brace
id|dsp_task_descriptor_t
suffix:semicolon
DECL|struct|_pcm_channel_descriptor_t
r_typedef
r_struct
id|_pcm_channel_descriptor_t
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|src_slot
r_int
id|src_slot
suffix:semicolon
DECL|member|pcm_slot
r_int
id|pcm_slot
suffix:semicolon
DECL|member|sample_rate
id|u32
id|sample_rate
suffix:semicolon
DECL|member|unlinked
id|u32
id|unlinked
suffix:semicolon
DECL|member|pcm_reader_scb
id|dsp_scb_descriptor_t
op_star
id|pcm_reader_scb
suffix:semicolon
DECL|member|src_scb
id|dsp_scb_descriptor_t
op_star
id|src_scb
suffix:semicolon
DECL|member|mixer_scb
id|dsp_scb_descriptor_t
op_star
id|mixer_scb
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|typedef|pcm_channel_descriptor_t
)brace
id|pcm_channel_descriptor_t
suffix:semicolon
DECL|struct|_dsp_spos_instance_t
r_typedef
r_struct
id|_dsp_spos_instance_t
(brace
DECL|member|symbol_table
id|symbol_desc_t
id|symbol_table
suffix:semicolon
multiline_comment|/* currently availble loaded symbols in SP */
DECL|member|nmodules
r_int
id|nmodules
suffix:semicolon
DECL|member|modules
id|dsp_module_desc_t
op_star
id|modules
suffix:semicolon
multiline_comment|/* modules loaded into SP */
DECL|member|code
id|segment_desc_t
id|code
suffix:semicolon
multiline_comment|/* Main PCM playback mixer */
DECL|member|master_mix_scb
id|dsp_scb_descriptor_t
op_star
id|master_mix_scb
suffix:semicolon
DECL|member|dac_volume_right
id|u16
id|dac_volume_right
suffix:semicolon
DECL|member|dac_volume_left
id|u16
id|dac_volume_left
suffix:semicolon
multiline_comment|/* Rear PCM playback mixer */
DECL|member|rear_mix_scb
id|dsp_scb_descriptor_t
op_star
id|rear_mix_scb
suffix:semicolon
DECL|member|npcm_channels
r_int
id|npcm_channels
suffix:semicolon
DECL|member|nsrc_scb
r_int
id|nsrc_scb
suffix:semicolon
DECL|member|pcm_channels
id|pcm_channel_descriptor_t
id|pcm_channels
(braket
id|DSP_MAX_PCM_CHANNELS
)braket
suffix:semicolon
DECL|member|src_scb_slots
r_int
id|src_scb_slots
(braket
id|DSP_MAX_SRC_NR
)braket
suffix:semicolon
multiline_comment|/* cache this symbols */
DECL|member|null_algorithm
id|symbol_entry_t
op_star
id|null_algorithm
suffix:semicolon
multiline_comment|/* used by PCMreaderSCB&squot;s */
DECL|member|s16_up
id|symbol_entry_t
op_star
id|s16_up
suffix:semicolon
multiline_comment|/* used by SRCtaskSCB&squot;s */
multiline_comment|/* proc fs */
DECL|member|snd_card
id|snd_card_t
op_star
id|snd_card
suffix:semicolon
DECL|member|proc_dsp_dir
id|snd_info_entry_t
op_star
id|proc_dsp_dir
suffix:semicolon
DECL|member|proc_sym_info_entry
id|snd_info_entry_t
op_star
id|proc_sym_info_entry
suffix:semicolon
DECL|member|proc_modules_info_entry
id|snd_info_entry_t
op_star
id|proc_modules_info_entry
suffix:semicolon
DECL|member|proc_parameter_dump_info_entry
id|snd_info_entry_t
op_star
id|proc_parameter_dump_info_entry
suffix:semicolon
DECL|member|proc_sample_dump_info_entry
id|snd_info_entry_t
op_star
id|proc_sample_dump_info_entry
suffix:semicolon
multiline_comment|/* SCB&squot;s descriptors */
DECL|member|nscb
r_int
id|nscb
suffix:semicolon
DECL|member|scb_highest_frag_index
r_int
id|scb_highest_frag_index
suffix:semicolon
DECL|member|scbs
id|dsp_scb_descriptor_t
id|scbs
(braket
id|DSP_MAX_SCB_DESC
)braket
suffix:semicolon
DECL|member|proc_scb_info_entry
id|snd_info_entry_t
op_star
id|proc_scb_info_entry
suffix:semicolon
DECL|member|the_null_scb
id|dsp_scb_descriptor_t
op_star
id|the_null_scb
suffix:semicolon
multiline_comment|/* Task&squot;s descriptors */
DECL|member|ntask
r_int
id|ntask
suffix:semicolon
DECL|member|tasks
id|dsp_task_descriptor_t
id|tasks
(braket
id|DSP_MAX_TASK_DESC
)braket
suffix:semicolon
DECL|member|proc_task_info_entry
id|snd_info_entry_t
op_star
id|proc_task_info_entry
suffix:semicolon
multiline_comment|/* SPDIF status */
DECL|member|spdif_status_out
r_int
id|spdif_status_out
suffix:semicolon
DECL|member|spdif_status_in
r_int
id|spdif_status_in
suffix:semicolon
DECL|member|spdif_input_volume_right
id|u16
id|spdif_input_volume_right
suffix:semicolon
DECL|member|spdif_input_volume_left
id|u16
id|spdif_input_volume_left
suffix:semicolon
multiline_comment|/* spdif channel status,&n;&t;   left right and user validity bits */
DECL|member|spdif_csuv_default
r_int
id|spdif_csuv_default
suffix:semicolon
DECL|member|spdif_csuv_stream
r_int
id|spdif_csuv_stream
suffix:semicolon
multiline_comment|/* SPDIF input sample rate converter */
DECL|member|spdif_in_src
id|dsp_scb_descriptor_t
op_star
id|spdif_in_src
suffix:semicolon
multiline_comment|/* SPDIF input asynch. receiver */
DECL|member|asynch_rx_scb
id|dsp_scb_descriptor_t
op_star
id|asynch_rx_scb
suffix:semicolon
multiline_comment|/* Capture record mixer SCB */
DECL|member|record_mixer_scb
id|dsp_scb_descriptor_t
op_star
id|record_mixer_scb
suffix:semicolon
multiline_comment|/* CODEC input SCB */
DECL|member|codec_in_scb
id|dsp_scb_descriptor_t
op_star
id|codec_in_scb
suffix:semicolon
multiline_comment|/* reference snooper */
DECL|member|ref_snoop_scb
id|dsp_scb_descriptor_t
op_star
id|ref_snoop_scb
suffix:semicolon
multiline_comment|/* SPDIF output  PCM reference  */
DECL|member|spdif_pcm_input_scb
id|dsp_scb_descriptor_t
op_star
id|spdif_pcm_input_scb
suffix:semicolon
multiline_comment|/* asynch TX task */
DECL|member|asynch_tx_scb
id|dsp_scb_descriptor_t
op_star
id|asynch_tx_scb
suffix:semicolon
multiline_comment|/* record sources */
DECL|member|pcm_input
id|dsp_scb_descriptor_t
op_star
id|pcm_input
suffix:semicolon
DECL|member|adc_input
id|dsp_scb_descriptor_t
op_star
id|adc_input
suffix:semicolon
DECL|member|spdif_in_sample_rate
r_int
id|spdif_in_sample_rate
suffix:semicolon
DECL|typedef|dsp_spos_instance_t
)brace
id|dsp_spos_instance_t
suffix:semicolon
macro_line|#endif /* __DSP_SPOS_H__ */
eof
