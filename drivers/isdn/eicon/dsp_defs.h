multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.0  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef DSP_DEFS_H_
DECL|macro|DSP_DEFS_H_
mdefine_line|#define DSP_DEFS_H_
macro_line|#ifndef DSPDIDS_H_
macro_line|#include &quot;dspdids.h&quot;
macro_line|#endif
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*---------------------------------------------------------------------------*/
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE (0 == 0)
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE (0 != 0)
macro_line|#endif
multiline_comment|/*---------------------------------------------------------------------------*/
DECL|macro|DSP_MEMORY_TYPE_EXTERNAL_DM
mdefine_line|#define DSP_MEMORY_TYPE_EXTERNAL_DM         0
DECL|macro|DSP_MEMORY_TYPE_EXTERNAL_PM
mdefine_line|#define DSP_MEMORY_TYPE_EXTERNAL_PM         1
DECL|macro|DSP_MEMORY_TYPE_INTERNAL_DM
mdefine_line|#define DSP_MEMORY_TYPE_INTERNAL_DM         2
DECL|macro|DSP_MEMORY_TYPE_INTERNAL_PM
mdefine_line|#define DSP_MEMORY_TYPE_INTERNAL_PM         3
DECL|macro|DSP_DOWNLOAD_FLAG_BOOTABLE
mdefine_line|#define DSP_DOWNLOAD_FLAG_BOOTABLE          0x0001
DECL|macro|DSP_DOWNLOAD_FLAG_2181
mdefine_line|#define DSP_DOWNLOAD_FLAG_2181              0x0002
DECL|macro|DSP_DOWNLOAD_FLAG_TIMECRITICAL
mdefine_line|#define DSP_DOWNLOAD_FLAG_TIMECRITICAL      0x0004
DECL|macro|DSP_DOWNLOAD_FLAG_COMPAND
mdefine_line|#define DSP_DOWNLOAD_FLAG_COMPAND           0x0008
DECL|macro|DSP_MEMORY_BLOCK_COUNT
mdefine_line|#define DSP_MEMORY_BLOCK_COUNT              16
DECL|macro|DSP_SEGMENT_PM_FLAG
mdefine_line|#define DSP_SEGMENT_PM_FLAG                 0x0001
DECL|macro|DSP_SEGMENT_SHARED_FLAG
mdefine_line|#define DSP_SEGMENT_SHARED_FLAG             0x0002
DECL|macro|DSP_SEGMENT_EXTERNAL_DM
mdefine_line|#define DSP_SEGMENT_EXTERNAL_DM             DSP_MEMORY_TYPE_EXTERNAL_DM
DECL|macro|DSP_SEGMENT_EXTERNAL_PM
mdefine_line|#define DSP_SEGMENT_EXTERNAL_PM             DSP_MEMORY_TYPE_EXTERNAL_PM
DECL|macro|DSP_SEGMENT_INTERNAL_DM
mdefine_line|#define DSP_SEGMENT_INTERNAL_DM             DSP_MEMORY_TYPE_INTERNAL_DM
DECL|macro|DSP_SEGMENT_INTERNAL_PM
mdefine_line|#define DSP_SEGMENT_INTERNAL_PM             DSP_MEMORY_TYPE_INTERNAL_PM
DECL|macro|DSP_SEGMENT_FIRST_RELOCATABLE
mdefine_line|#define DSP_SEGMENT_FIRST_RELOCATABLE       4
DECL|macro|DSP_DATA_BLOCK_PM_FLAG
mdefine_line|#define DSP_DATA_BLOCK_PM_FLAG              0x0001
DECL|macro|DSP_DATA_BLOCK_DWORD_FLAG
mdefine_line|#define DSP_DATA_BLOCK_DWORD_FLAG           0x0002
DECL|macro|DSP_DATA_BLOCK_RESOLVE_FLAG
mdefine_line|#define DSP_DATA_BLOCK_RESOLVE_FLAG         0x0004
DECL|macro|DSP_RELOC_NONE
mdefine_line|#define DSP_RELOC_NONE                      0x00
DECL|macro|DSP_RELOC_SEGMENT_MASK
mdefine_line|#define DSP_RELOC_SEGMENT_MASK              0x3f
DECL|macro|DSP_RELOC_TYPE_MASK
mdefine_line|#define DSP_RELOC_TYPE_MASK                 0xc0
DECL|macro|DSP_RELOC_TYPE_0
mdefine_line|#define DSP_RELOC_TYPE_0                    0x00  /* relocation of address in DM word / high part of PM word */
DECL|macro|DSP_RELOC_TYPE_1
mdefine_line|#define DSP_RELOC_TYPE_1                    0x40  /* relocation of address in low part of PM data word */
DECL|macro|DSP_RELOC_TYPE_2
mdefine_line|#define DSP_RELOC_TYPE_2                    0x80  /* relocation of address in standard command */
DECL|macro|DSP_RELOC_TYPE_3
mdefine_line|#define DSP_RELOC_TYPE_3                    0xc0  /* relocation of address in call/jump on flag in */
DECL|macro|DSP_COMBIFILE_FORMAT_IDENTIFICATION_SIZE
mdefine_line|#define DSP_COMBIFILE_FORMAT_IDENTIFICATION_SIZE 48
DECL|macro|DSP_COMBIFILE_FORMAT_VERSION_BCD
mdefine_line|#define DSP_COMBIFILE_FORMAT_VERSION_BCD    0x0100
DECL|macro|DSP_FILE_FORMAT_IDENTIFICATION_SIZE
mdefine_line|#define DSP_FILE_FORMAT_IDENTIFICATION_SIZE 48
DECL|macro|DSP_FILE_FORMAT_VERSION_BCD
mdefine_line|#define DSP_FILE_FORMAT_VERSION_BCD         0x0100
DECL|struct|tag_dsp_combifile_header
r_typedef
r_struct
id|tag_dsp_combifile_header
(brace
DECL|member|format_identification
r_char
id|format_identification
(braket
id|DSP_COMBIFILE_FORMAT_IDENTIFICATION_SIZE
)braket
suffix:semicolon
DECL|member|format_version_bcd
id|word
id|format_version_bcd
suffix:semicolon
DECL|member|header_size
id|word
id|header_size
suffix:semicolon
DECL|member|combifile_description_size
id|word
id|combifile_description_size
suffix:semicolon
DECL|member|directory_entries
id|word
id|directory_entries
suffix:semicolon
DECL|member|directory_size
id|word
id|directory_size
suffix:semicolon
DECL|member|download_count
id|word
id|download_count
suffix:semicolon
DECL|member|usage_mask_size
id|word
id|usage_mask_size
suffix:semicolon
DECL|typedef|t_dsp_combifile_header
)brace
id|t_dsp_combifile_header
suffix:semicolon
DECL|struct|tag_dsp_combifile_directory_entry
r_typedef
r_struct
id|tag_dsp_combifile_directory_entry
(brace
DECL|member|card_type_number
id|word
id|card_type_number
suffix:semicolon
DECL|member|file_set_number
id|word
id|file_set_number
suffix:semicolon
DECL|typedef|t_dsp_combifile_directory_entry
)brace
id|t_dsp_combifile_directory_entry
suffix:semicolon
DECL|struct|tag_dsp_file_header
r_typedef
r_struct
id|tag_dsp_file_header
(brace
DECL|member|format_identification
r_char
id|format_identification
(braket
id|DSP_FILE_FORMAT_IDENTIFICATION_SIZE
)braket
suffix:semicolon
DECL|member|format_version_bcd
id|word
id|format_version_bcd
suffix:semicolon
DECL|member|download_id
id|word
id|download_id
suffix:semicolon
DECL|member|download_flags
id|word
id|download_flags
suffix:semicolon
DECL|member|required_processing_power
id|word
id|required_processing_power
suffix:semicolon
DECL|member|interface_channel_count
id|word
id|interface_channel_count
suffix:semicolon
DECL|member|header_size
id|word
id|header_size
suffix:semicolon
DECL|member|download_description_size
id|word
id|download_description_size
suffix:semicolon
DECL|member|memory_block_table_size
id|word
id|memory_block_table_size
suffix:semicolon
DECL|member|memory_block_count
id|word
id|memory_block_count
suffix:semicolon
DECL|member|segment_table_size
id|word
id|segment_table_size
suffix:semicolon
DECL|member|segment_count
id|word
id|segment_count
suffix:semicolon
DECL|member|symbol_table_size
id|word
id|symbol_table_size
suffix:semicolon
DECL|member|symbol_count
id|word
id|symbol_count
suffix:semicolon
DECL|member|total_data_size_dm
id|word
id|total_data_size_dm
suffix:semicolon
DECL|member|data_block_count_dm
id|word
id|data_block_count_dm
suffix:semicolon
DECL|member|total_data_size_pm
id|word
id|total_data_size_pm
suffix:semicolon
DECL|member|data_block_count_pm
id|word
id|data_block_count_pm
suffix:semicolon
DECL|typedef|t_dsp_file_header
)brace
id|t_dsp_file_header
suffix:semicolon
DECL|struct|tag_dsp_memory_block_desc
r_typedef
r_struct
id|tag_dsp_memory_block_desc
(brace
DECL|member|alias_memory_block
id|word
id|alias_memory_block
suffix:semicolon
DECL|member|memory_type
id|word
id|memory_type
suffix:semicolon
DECL|member|address
id|word
id|address
suffix:semicolon
DECL|member|size
id|word
id|size
suffix:semicolon
multiline_comment|/* DSP words */
DECL|typedef|t_dsp_memory_block_desc
)brace
id|t_dsp_memory_block_desc
suffix:semicolon
DECL|struct|tag_dsp_segment_desc
r_typedef
r_struct
id|tag_dsp_segment_desc
(brace
DECL|member|memory_block
id|word
id|memory_block
suffix:semicolon
DECL|member|attributes
id|word
id|attributes
suffix:semicolon
DECL|member|base
id|word
id|base
suffix:semicolon
DECL|member|size
id|word
id|size
suffix:semicolon
DECL|member|alignment
id|word
id|alignment
suffix:semicolon
multiline_comment|/* ==0 -&gt; no other legal start address than base */
DECL|typedef|t_dsp_segment_desc
)brace
id|t_dsp_segment_desc
suffix:semicolon
DECL|struct|tag_dsp_symbol_desc
r_typedef
r_struct
id|tag_dsp_symbol_desc
(brace
DECL|member|symbol_id
id|word
id|symbol_id
suffix:semicolon
DECL|member|segment
id|word
id|segment
suffix:semicolon
DECL|member|offset
id|word
id|offset
suffix:semicolon
DECL|member|size
id|word
id|size
suffix:semicolon
multiline_comment|/* DSP words */
DECL|typedef|t_dsp_symbol_desc
)brace
id|t_dsp_symbol_desc
suffix:semicolon
DECL|struct|tag_dsp_data_block_header
r_typedef
r_struct
id|tag_dsp_data_block_header
(brace
DECL|member|attributes
id|word
id|attributes
suffix:semicolon
DECL|member|segment
id|word
id|segment
suffix:semicolon
DECL|member|offset
id|word
id|offset
suffix:semicolon
DECL|member|size
id|word
id|size
suffix:semicolon
multiline_comment|/* DSP words */
DECL|typedef|t_dsp_data_block_header
)brace
id|t_dsp_data_block_header
suffix:semicolon
DECL|struct|tag_dsp_download_desc
r_typedef
r_struct
id|tag_dsp_download_desc
multiline_comment|/* be sure to keep native alignment for MAESTRA&squot;s */
(brace
DECL|member|download_id
id|word
id|download_id
suffix:semicolon
DECL|member|download_flags
id|word
id|download_flags
suffix:semicolon
DECL|member|required_processing_power
id|word
id|required_processing_power
suffix:semicolon
DECL|member|interface_channel_count
id|word
id|interface_channel_count
suffix:semicolon
DECL|member|excess_header_size
id|word
id|excess_header_size
suffix:semicolon
DECL|member|memory_block_count
id|word
id|memory_block_count
suffix:semicolon
DECL|member|segment_count
id|word
id|segment_count
suffix:semicolon
DECL|member|symbol_count
id|word
id|symbol_count
suffix:semicolon
DECL|member|data_block_count_dm
id|word
id|data_block_count_dm
suffix:semicolon
DECL|member|data_block_count_pm
id|word
id|data_block_count_pm
suffix:semicolon
DECL|member|p_excess_header_data
id|byte
op_star
id|p_excess_header_data
suffix:semicolon
DECL|member|p_download_description
r_char
op_star
id|p_download_description
suffix:semicolon
DECL|member|p_memory_block_table
id|t_dsp_memory_block_desc
op_star
id|p_memory_block_table
suffix:semicolon
DECL|member|p_segment_table
id|t_dsp_segment_desc
op_star
id|p_segment_table
suffix:semicolon
DECL|member|p_symbol_table
id|t_dsp_symbol_desc
op_star
id|p_symbol_table
suffix:semicolon
DECL|member|p_data_blocks_dm
id|word
op_star
id|p_data_blocks_dm
suffix:semicolon
DECL|member|p_data_blocks_pm
id|word
op_star
id|p_data_blocks_pm
suffix:semicolon
DECL|typedef|t_dsp_download_desc
)brace
id|t_dsp_download_desc
suffix:semicolon
DECL|macro|DSP_DOWNLOAD_INDEX_KERNEL
mdefine_line|#define DSP_DOWNLOAD_INDEX_KERNEL               0
DECL|macro|DSP30TX_DOWNLOAD_INDEX_KERNEL
mdefine_line|#define DSP30TX_DOWNLOAD_INDEX_KERNEL           1
DECL|macro|DSP30RX_DOWNLOAD_INDEX_KERNEL
mdefine_line|#define DSP30RX_DOWNLOAD_INDEX_KERNEL           2
DECL|macro|DSP_MAX_DOWNLOAD_COUNT
mdefine_line|#define DSP_MAX_DOWNLOAD_COUNT                  35
DECL|macro|DSP_DOWNLOAD_MAX_SEGMENTS
mdefine_line|#define DSP_DOWNLOAD_MAX_SEGMENTS         16
DECL|macro|DSP_UDATA_REQUEST_RECONFIGURE
mdefine_line|#define DSP_UDATA_REQUEST_RECONFIGURE     0
multiline_comment|/*&n;parameters:&n;  &lt;word&gt; reconfigure delay (in 8kHz samples)&n;  &lt;word&gt; reconfigure code&n;  &lt;byte&gt; reconfigure hdlc preamble flags&n;*/
DECL|macro|DSP_RECONFIGURE_TX_FLAG
mdefine_line|#define DSP_RECONFIGURE_TX_FLAG           0x8000
DECL|macro|DSP_RECONFIGURE_SHORT_TRAIN_FLAG
mdefine_line|#define DSP_RECONFIGURE_SHORT_TRAIN_FLAG  0x4000
DECL|macro|DSP_RECONFIGURE_ECHO_PROTECT_FLAG
mdefine_line|#define DSP_RECONFIGURE_ECHO_PROTECT_FLAG 0x2000
DECL|macro|DSP_RECONFIGURE_HDLC_FLAG
mdefine_line|#define DSP_RECONFIGURE_HDLC_FLAG         0x1000
DECL|macro|DSP_RECONFIGURE_SYNC_FLAG
mdefine_line|#define DSP_RECONFIGURE_SYNC_FLAG         0x0800
DECL|macro|DSP_RECONFIGURE_PROTOCOL_MASK
mdefine_line|#define DSP_RECONFIGURE_PROTOCOL_MASK     0x00ff
DECL|macro|DSP_RECONFIGURE_IDLE
mdefine_line|#define DSP_RECONFIGURE_IDLE              0
DECL|macro|DSP_RECONFIGURE_V25
mdefine_line|#define DSP_RECONFIGURE_V25               1
DECL|macro|DSP_RECONFIGURE_V21_CH2
mdefine_line|#define DSP_RECONFIGURE_V21_CH2           2
DECL|macro|DSP_RECONFIGURE_V27_2400
mdefine_line|#define DSP_RECONFIGURE_V27_2400          3
DECL|macro|DSP_RECONFIGURE_V27_4800
mdefine_line|#define DSP_RECONFIGURE_V27_4800          4
DECL|macro|DSP_RECONFIGURE_V29_7200
mdefine_line|#define DSP_RECONFIGURE_V29_7200          5
DECL|macro|DSP_RECONFIGURE_V29_9600
mdefine_line|#define DSP_RECONFIGURE_V29_9600          6
DECL|macro|DSP_RECONFIGURE_V33_12000
mdefine_line|#define DSP_RECONFIGURE_V33_12000         7
DECL|macro|DSP_RECONFIGURE_V33_14400
mdefine_line|#define DSP_RECONFIGURE_V33_14400         8
DECL|macro|DSP_RECONFIGURE_V17_7200
mdefine_line|#define DSP_RECONFIGURE_V17_7200          9
DECL|macro|DSP_RECONFIGURE_V17_9600
mdefine_line|#define DSP_RECONFIGURE_V17_9600          10
DECL|macro|DSP_RECONFIGURE_V17_12000
mdefine_line|#define DSP_RECONFIGURE_V17_12000         11
DECL|macro|DSP_RECONFIGURE_V17_14400
mdefine_line|#define DSP_RECONFIGURE_V17_14400         12
multiline_comment|/*&n;data indications if transparent framer&n;  &lt;byte&gt; data 0&n;  &lt;byte&gt; data 1&n;  ...&n;&n;data indications if HDLC framer&n;  &lt;byte&gt; data 0&n;  &lt;byte&gt; data 1&n;  ...&n;  &lt;byte&gt; CRC 0&n;  &lt;byte&gt; CRC 1&n;  &lt;byte&gt; preamble flags&n;*/
DECL|macro|DSP_UDATA_INDICATION_SYNC
mdefine_line|#define DSP_UDATA_INDICATION_SYNC         0
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of sync (sampled from counter at 8kHz)&n;*/
DECL|macro|DSP_UDATA_INDICATION_DCD_OFF
mdefine_line|#define DSP_UDATA_INDICATION_DCD_OFF      1
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of DCD off (sampled from counter at 8kHz)&n;*/
DECL|macro|DSP_UDATA_INDICATION_DCD_ON
mdefine_line|#define DSP_UDATA_INDICATION_DCD_ON       2
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of DCD on (sampled from counter at 8kHz)&n;  &lt;byte&gt; connected norm&n;  &lt;word&gt; connected options&n;  &lt;dword&gt; connected speed (bit/s)&n;*/
DECL|macro|DSP_UDATA_INDICATION_CTS_OFF
mdefine_line|#define DSP_UDATA_INDICATION_CTS_OFF      3
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of CTS off (sampled from counter at 8kHz)&n;*/
DECL|macro|DSP_UDATA_INDICATION_CTS_ON
mdefine_line|#define DSP_UDATA_INDICATION_CTS_ON       4
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of CTS on (sampled from counter at 8kHz)&n;  &lt;byte&gt; connected norm&n;  &lt;word&gt; connected options&n;  &lt;dword&gt; connected speed (bit/s)&n;*/
DECL|macro|DSP_CONNECTED_NORM_UNSPECIFIED
mdefine_line|#define DSP_CONNECTED_NORM_UNSPECIFIED      0
DECL|macro|DSP_CONNECTED_NORM_V21
mdefine_line|#define DSP_CONNECTED_NORM_V21              1
DECL|macro|DSP_CONNECTED_NORM_V23
mdefine_line|#define DSP_CONNECTED_NORM_V23              2
DECL|macro|DSP_CONNECTED_NORM_V22
mdefine_line|#define DSP_CONNECTED_NORM_V22              3
DECL|macro|DSP_CONNECTED_NORM_V22_BIS
mdefine_line|#define DSP_CONNECTED_NORM_V22_BIS          4
DECL|macro|DSP_CONNECTED_NORM_V32_BIS
mdefine_line|#define DSP_CONNECTED_NORM_V32_BIS          5
DECL|macro|DSP_CONNECTED_NORM_V34
mdefine_line|#define DSP_CONNECTED_NORM_V34              6
DECL|macro|DSP_CONNECTED_NORM_V8
mdefine_line|#define DSP_CONNECTED_NORM_V8               7
DECL|macro|DSP_CONNECTED_NORM_BELL_212A
mdefine_line|#define DSP_CONNECTED_NORM_BELL_212A        8
DECL|macro|DSP_CONNECTED_NORM_BELL_103
mdefine_line|#define DSP_CONNECTED_NORM_BELL_103         9
DECL|macro|DSP_CONNECTED_NORM_V29_LEASED_LINE
mdefine_line|#define DSP_CONNECTED_NORM_V29_LEASED_LINE  10
DECL|macro|DSP_CONNECTED_NORM_V33_LEASED_LINE
mdefine_line|#define DSP_CONNECTED_NORM_V33_LEASED_LINE  11
DECL|macro|DSP_CONNECTED_NORM_TFAST
mdefine_line|#define DSP_CONNECTED_NORM_TFAST            12
DECL|macro|DSP_CONNECTED_NORM_V21_CH2
mdefine_line|#define DSP_CONNECTED_NORM_V21_CH2          13
DECL|macro|DSP_CONNECTED_NORM_V27_TER
mdefine_line|#define DSP_CONNECTED_NORM_V27_TER          14
DECL|macro|DSP_CONNECTED_NORM_V29
mdefine_line|#define DSP_CONNECTED_NORM_V29              15
DECL|macro|DSP_CONNECTED_NORM_V33
mdefine_line|#define DSP_CONNECTED_NORM_V33              16
DECL|macro|DSP_CONNECTED_NORM_V17
mdefine_line|#define DSP_CONNECTED_NORM_V17              17
DECL|macro|DSP_CONNECTED_OPTION_TRELLIS
mdefine_line|#define DSP_CONNECTED_OPTION_TRELLIS        0x0001
multiline_comment|/*---------------------------------------------------------------------------*/
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/*---------------------------------------------------------------------------*/
eof
