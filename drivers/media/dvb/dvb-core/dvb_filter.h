macro_line|#ifndef _DVB_FILTER_H_
DECL|macro|_DVB_FILTER_H_
mdefine_line|#define _DVB_FILTER_H_
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;demux.h&quot;
DECL|typedef|dvb_filter_pes2ts_cb_t
r_typedef
r_int
(paren
id|dvb_filter_pes2ts_cb_t
)paren
(paren
r_void
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|struct|dvb_filter_pes2ts
r_struct
id|dvb_filter_pes2ts
(brace
DECL|member|buf
r_int
r_char
id|buf
(braket
l_int|188
)braket
suffix:semicolon
DECL|member|cc
r_int
r_char
id|cc
suffix:semicolon
DECL|member|cb
id|dvb_filter_pes2ts_cb_t
op_star
id|cb
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
)brace
suffix:semicolon
r_void
id|dvb_filter_pes2ts_init
c_func
(paren
r_struct
id|dvb_filter_pes2ts
op_star
id|p2ts
comma
r_int
r_int
id|pid
comma
id|dvb_filter_pes2ts_cb_t
op_star
id|cb
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_int
id|dvb_filter_pes2ts
c_func
(paren
r_struct
id|dvb_filter_pes2ts
op_star
id|p2ts
comma
r_int
r_char
op_star
id|pes
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|PROG_STREAM_MAP
mdefine_line|#define PROG_STREAM_MAP  0xBC
DECL|macro|PRIVATE_STREAM1
mdefine_line|#define PRIVATE_STREAM1  0xBD
DECL|macro|PADDING_STREAM
mdefine_line|#define PADDING_STREAM   0xBE
DECL|macro|PRIVATE_STREAM2
mdefine_line|#define PRIVATE_STREAM2  0xBF
DECL|macro|AUDIO_STREAM_S
mdefine_line|#define AUDIO_STREAM_S   0xC0
DECL|macro|AUDIO_STREAM_E
mdefine_line|#define AUDIO_STREAM_E   0xDF
DECL|macro|VIDEO_STREAM_S
mdefine_line|#define VIDEO_STREAM_S   0xE0
DECL|macro|VIDEO_STREAM_E
mdefine_line|#define VIDEO_STREAM_E   0xEF
DECL|macro|ECM_STREAM
mdefine_line|#define ECM_STREAM       0xF0
DECL|macro|EMM_STREAM
mdefine_line|#define EMM_STREAM       0xF1
DECL|macro|DSM_CC_STREAM
mdefine_line|#define DSM_CC_STREAM    0xF2
DECL|macro|ISO13522_STREAM
mdefine_line|#define ISO13522_STREAM  0xF3
DECL|macro|PROG_STREAM_DIR
mdefine_line|#define PROG_STREAM_DIR  0xFF
DECL|macro|DVB_PICTURE_START
mdefine_line|#define DVB_PICTURE_START    0x00
DECL|macro|DVB_USER_START
mdefine_line|#define DVB_USER_START       0xb2
DECL|macro|DVB_SEQUENCE_HEADER
mdefine_line|#define DVB_SEQUENCE_HEADER  0xb3
DECL|macro|DVB_SEQUENCE_ERROR
mdefine_line|#define DVB_SEQUENCE_ERROR   0xb4
DECL|macro|DVB_EXTENSION_START
mdefine_line|#define DVB_EXTENSION_START  0xb5
DECL|macro|DVB_SEQUENCE_END
mdefine_line|#define DVB_SEQUENCE_END     0xb7
DECL|macro|DVB_GOP_START
mdefine_line|#define DVB_GOP_START        0xb8
DECL|macro|DVB_EXCEPT_SLICE
mdefine_line|#define DVB_EXCEPT_SLICE     0xb0
DECL|macro|SEQUENCE_EXTENSION
mdefine_line|#define SEQUENCE_EXTENSION           0x01
DECL|macro|SEQUENCE_DISPLAY_EXTENSION
mdefine_line|#define SEQUENCE_DISPLAY_EXTENSION   0x02
DECL|macro|PICTURE_CODING_EXTENSION
mdefine_line|#define PICTURE_CODING_EXTENSION     0x08
DECL|macro|QUANT_MATRIX_EXTENSION
mdefine_line|#define QUANT_MATRIX_EXTENSION       0x03
DECL|macro|PICTURE_DISPLAY_EXTENSION
mdefine_line|#define PICTURE_DISPLAY_EXTENSION    0x07
DECL|macro|I_FRAME
mdefine_line|#define I_FRAME 0x01 
DECL|macro|B_FRAME
mdefine_line|#define B_FRAME 0x02 
DECL|macro|P_FRAME
mdefine_line|#define P_FRAME 0x03
multiline_comment|/* Initialize sequence_data */
DECL|macro|INIT_HORIZONTAL_SIZE
mdefine_line|#define INIT_HORIZONTAL_SIZE        720
DECL|macro|INIT_VERTICAL_SIZE
mdefine_line|#define INIT_VERTICAL_SIZE          576
DECL|macro|INIT_ASPECT_RATIO
mdefine_line|#define INIT_ASPECT_RATIO          0x02
DECL|macro|INIT_FRAME_RATE
mdefine_line|#define INIT_FRAME_RATE            0x03
DECL|macro|INIT_DISP_HORIZONTAL_SIZE
mdefine_line|#define INIT_DISP_HORIZONTAL_SIZE   540
DECL|macro|INIT_DISP_VERTICAL_SIZE
mdefine_line|#define INIT_DISP_VERTICAL_SIZE     576
singleline_comment|//flags2
DECL|macro|PTS_DTS_FLAGS
mdefine_line|#define PTS_DTS_FLAGS    0xC0
DECL|macro|ESCR_FLAG
mdefine_line|#define ESCR_FLAG        0x20
DECL|macro|ES_RATE_FLAG
mdefine_line|#define ES_RATE_FLAG     0x10
DECL|macro|DSM_TRICK_FLAG
mdefine_line|#define DSM_TRICK_FLAG   0x08
DECL|macro|ADD_CPY_FLAG
mdefine_line|#define ADD_CPY_FLAG     0x04
DECL|macro|PES_CRC_FLAG
mdefine_line|#define PES_CRC_FLAG     0x02
DECL|macro|PES_EXT_FLAG
mdefine_line|#define PES_EXT_FLAG     0x01
singleline_comment|//pts_dts flags 
DECL|macro|PTS_ONLY
mdefine_line|#define PTS_ONLY         0x80
DECL|macro|PTS_DTS
mdefine_line|#define PTS_DTS          0xC0
DECL|macro|TS_SIZE
mdefine_line|#define TS_SIZE        188
DECL|macro|TRANS_ERROR
mdefine_line|#define TRANS_ERROR    0x80
DECL|macro|PAY_START
mdefine_line|#define PAY_START      0x40
DECL|macro|TRANS_PRIO
mdefine_line|#define TRANS_PRIO     0x20
DECL|macro|PID_MASK_HI
mdefine_line|#define PID_MASK_HI    0x1F
singleline_comment|//flags
DECL|macro|TRANS_SCRMBL1
mdefine_line|#define TRANS_SCRMBL1  0x80
DECL|macro|TRANS_SCRMBL2
mdefine_line|#define TRANS_SCRMBL2  0x40
DECL|macro|ADAPT_FIELD
mdefine_line|#define ADAPT_FIELD    0x20
DECL|macro|PAYLOAD
mdefine_line|#define PAYLOAD        0x10
DECL|macro|COUNT_MASK
mdefine_line|#define COUNT_MASK     0x0F
singleline_comment|// adaptation flags
DECL|macro|DISCON_IND
mdefine_line|#define DISCON_IND     0x80
DECL|macro|RAND_ACC_IND
mdefine_line|#define RAND_ACC_IND   0x40
DECL|macro|ES_PRI_IND
mdefine_line|#define ES_PRI_IND     0x20
DECL|macro|PCR_FLAG
mdefine_line|#define PCR_FLAG       0x10
DECL|macro|OPCR_FLAG
mdefine_line|#define OPCR_FLAG      0x08
DECL|macro|SPLICE_FLAG
mdefine_line|#define SPLICE_FLAG    0x04
DECL|macro|TRANS_PRIV
mdefine_line|#define TRANS_PRIV     0x02
DECL|macro|ADAP_EXT_FLAG
mdefine_line|#define ADAP_EXT_FLAG  0x01
singleline_comment|// adaptation extension flags
DECL|macro|LTW_FLAG
mdefine_line|#define LTW_FLAG       0x80
DECL|macro|PIECE_RATE
mdefine_line|#define PIECE_RATE     0x40
DECL|macro|SEAM_SPLICE
mdefine_line|#define SEAM_SPLICE    0x20
DECL|macro|MAX_PLENGTH
mdefine_line|#define MAX_PLENGTH 0xFFFF
DECL|macro|MMAX_PLENGTH
mdefine_line|#define MMAX_PLENGTH (256*MAX_PLENGTH)
macro_line|#ifndef IPACKS
DECL|macro|IPACKS
mdefine_line|#define IPACKS 2048
macro_line|#endif
DECL|struct|ipack
r_struct
id|ipack
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|found
r_int
id|found
suffix:semicolon
DECL|member|buf
id|u8
op_star
id|buf
suffix:semicolon
DECL|member|cid
id|u8
id|cid
suffix:semicolon
DECL|member|plength
id|u32
id|plength
suffix:semicolon
DECL|member|plen
id|u8
id|plen
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|flag1
id|u8
id|flag1
suffix:semicolon
DECL|member|flag2
id|u8
id|flag2
suffix:semicolon
DECL|member|hlength
id|u8
id|hlength
suffix:semicolon
DECL|member|pts
id|u8
id|pts
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|pid
id|u16
op_star
id|pid
suffix:semicolon
DECL|member|mpeg
r_int
id|mpeg
suffix:semicolon
DECL|member|check
id|u8
id|check
suffix:semicolon
DECL|member|which
r_int
id|which
suffix:semicolon
DECL|member|done
r_int
id|done
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
id|u8
op_star
id|buf
comma
r_int
id|size
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|repack_subids
r_int
id|repack_subids
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvb_video_info
r_struct
id|dvb_video_info
(brace
DECL|member|horizontal_size
id|u32
id|horizontal_size
suffix:semicolon
DECL|member|vertical_size
id|u32
id|vertical_size
suffix:semicolon
DECL|member|aspect_ratio
id|u32
id|aspect_ratio
suffix:semicolon
DECL|member|framerate
id|u32
id|framerate
suffix:semicolon
DECL|member|video_format
id|u32
id|video_format
suffix:semicolon
DECL|member|bit_rate
id|u32
id|bit_rate
suffix:semicolon
DECL|member|comp_bit_rate
id|u32
id|comp_bit_rate
suffix:semicolon
DECL|member|vbv_buffer_size
id|u32
id|vbv_buffer_size
suffix:semicolon
DECL|member|vbv_delay
id|s16
id|vbv_delay
suffix:semicolon
DECL|member|CSPF
id|u32
id|CSPF
suffix:semicolon
DECL|member|off
id|u32
id|off
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OFF_SIZE
mdefine_line|#define OFF_SIZE 4
DECL|macro|FIRST_FIELD
mdefine_line|#define FIRST_FIELD 0
DECL|macro|SECOND_FIELD
mdefine_line|#define SECOND_FIELD 1
DECL|macro|VIDEO_FRAME_PICTURE
mdefine_line|#define VIDEO_FRAME_PICTURE 0x03
DECL|struct|mpg_picture
r_struct
id|mpg_picture
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|vinfo
r_struct
id|dvb_video_info
id|vinfo
suffix:semicolon
DECL|member|sequence_gop_header
id|u32
op_star
id|sequence_gop_header
suffix:semicolon
DECL|member|picture_header
id|u32
op_star
id|picture_header
suffix:semicolon
DECL|member|time_code
id|s32
id|time_code
suffix:semicolon
DECL|member|low_delay
r_int
id|low_delay
suffix:semicolon
DECL|member|closed_gop
r_int
id|closed_gop
suffix:semicolon
DECL|member|broken_link
r_int
id|broken_link
suffix:semicolon
DECL|member|sequence_header_flag
r_int
id|sequence_header_flag
suffix:semicolon
DECL|member|gop_flag
r_int
id|gop_flag
suffix:semicolon
DECL|member|sequence_end_flag
r_int
id|sequence_end_flag
suffix:semicolon
DECL|member|profile_and_level
id|u8
id|profile_and_level
suffix:semicolon
DECL|member|picture_coding_parameter
id|s32
id|picture_coding_parameter
suffix:semicolon
DECL|member|matrix
id|u32
id|matrix
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|matrix_change_flag
id|s8
id|matrix_change_flag
suffix:semicolon
DECL|member|picture_header_parameter
id|u8
id|picture_header_parameter
suffix:semicolon
multiline_comment|/* bit 0 - 2: bwd f code&n;     bit 3    : fpb vector&n;     bit 4 - 6: fwd f code&n;     bit 7    : fpf vector */
DECL|member|mpeg1_flag
r_int
id|mpeg1_flag
suffix:semicolon
DECL|member|progressive_sequence
r_int
id|progressive_sequence
suffix:semicolon
DECL|member|sequence_display_extension_flag
r_int
id|sequence_display_extension_flag
suffix:semicolon
DECL|member|sequence_header_data
id|u32
id|sequence_header_data
suffix:semicolon
DECL|member|last_frame_centre_horizontal_offset
id|s16
id|last_frame_centre_horizontal_offset
suffix:semicolon
DECL|member|last_frame_centre_vertical_offset
id|s16
id|last_frame_centre_vertical_offset
suffix:semicolon
DECL|member|pts
id|u32
id|pts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] 1st field, [1] 2nd field */
DECL|member|top_field_first
r_int
id|top_field_first
suffix:semicolon
DECL|member|repeat_first_field
r_int
id|repeat_first_field
suffix:semicolon
DECL|member|progressive_frame
r_int
id|progressive_frame
suffix:semicolon
DECL|member|bank
r_int
id|bank
suffix:semicolon
DECL|member|forward_bank
r_int
id|forward_bank
suffix:semicolon
DECL|member|backward_bank
r_int
id|backward_bank
suffix:semicolon
DECL|member|compress
r_int
id|compress
suffix:semicolon
DECL|member|frame_centre_horizontal_offset
id|s16
id|frame_centre_horizontal_offset
(braket
id|OFF_SIZE
)braket
suffix:semicolon
multiline_comment|/* [0-2] 1st field, [3] 2nd field */
DECL|member|frame_centre_vertical_offset
id|s16
id|frame_centre_vertical_offset
(braket
id|OFF_SIZE
)braket
suffix:semicolon
multiline_comment|/* [0-2] 1st field, [3] 2nd field */
DECL|member|temporal_reference
id|s16
id|temporal_reference
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] 1st field, [1] 2nd field */
DECL|member|picture_coding_type
id|s8
id|picture_coding_type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] 1st field, [1] 2nd field */
DECL|member|picture_structure
id|s8
id|picture_structure
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] 1st field, [1] 2nd field */
DECL|member|picture_display_extension_flag
id|s8
id|picture_display_extension_flag
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] 1st field, [1] 2nd field */
multiline_comment|/* picture_display_extenion() 0:no 1:exit*/
DECL|member|pts_flag
id|s8
id|pts_flag
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0] 1st field, [1] 2nd field */
)brace
suffix:semicolon
DECL|struct|dvb_audio_info
r_struct
id|dvb_audio_info
(brace
DECL|member|layer
r_int
id|layer
suffix:semicolon
DECL|member|bit_rate
id|u32
id|bit_rate
suffix:semicolon
DECL|member|frequency
id|u32
id|frequency
suffix:semicolon
DECL|member|mode
id|u32
id|mode
suffix:semicolon
DECL|member|mode_extension
id|u32
id|mode_extension
suffix:semicolon
DECL|member|emphasis
id|u32
id|emphasis
suffix:semicolon
DECL|member|framesize
id|u32
id|framesize
suffix:semicolon
DECL|member|off
id|u32
id|off
suffix:semicolon
)brace
suffix:semicolon
r_int
id|dvb_filter_get_ac3info
c_func
(paren
id|u8
op_star
id|mbuf
comma
r_int
id|count
comma
r_struct
id|dvb_audio_info
op_star
id|ai
comma
r_int
id|pr
)paren
suffix:semicolon
macro_line|#endif
eof
