multiline_comment|/*&n; * Copyright (C) 1999 Ulf Karlsson &lt;ulfc@bun.falkenberg.se&gt;&n; * Copyright (C) 2003 Ladislav Michl &lt;ladis@linux-mips.org&gt;&n; */
macro_line|#ifndef VINO_H
DECL|macro|VINO_H
mdefine_line|#define VINO_H
DECL|macro|VINO_BASE
mdefine_line|#define VINO_BASE&t;0x00080000&t;/* Vino is in the EISA address space,&n;&t;&t;&t;&t;&t; * but it is not an EISA bus card */
DECL|struct|sgi_vino_channel
r_struct
id|sgi_vino_channel
(brace
DECL|member|_pad_alpha
id|u32
id|_pad_alpha
suffix:semicolon
DECL|member|alpha
r_volatile
id|u32
id|alpha
suffix:semicolon
DECL|macro|VINO_CLIP_X
mdefine_line|#define VINO_CLIP_X(x)&t;&t;((x) &amp; 0x3ff)&t;&t;/* bits 0:9 */
DECL|macro|VINO_CLIP_ODD
mdefine_line|#define VINO_CLIP_ODD(x)&t;(((x) &amp; 0x1ff) &lt;&lt; 10)&t;/* bits 10:18 */
DECL|macro|VINO_CLIP_EVEN
mdefine_line|#define VINO_CLIP_EVEN(x)&t;(((x) &amp; 0x1ff) &lt;&lt; 19)&t;/* bits 19:27 */
DECL|member|_pad_clip_start
id|u32
id|_pad_clip_start
suffix:semicolon
DECL|member|clip_start
r_volatile
id|u32
id|clip_start
suffix:semicolon
DECL|member|_pad_clip_end
id|u32
id|_pad_clip_end
suffix:semicolon
DECL|member|clip_end
r_volatile
id|u32
id|clip_end
suffix:semicolon
DECL|macro|VINO_FRAMERT_PAL
mdefine_line|#define VINO_FRAMERT_PAL&t;(1&lt;&lt;0)&t;&t;&t;/* 0=NTSC 1=PAL */
DECL|macro|VINO_FRAMERT_RT
mdefine_line|#define VINO_FRAMERT_RT(x)&t;(((x) &amp; 0x1fff) &lt;&lt; 1)&t;/* bits 1:12 */
DECL|member|_pad_frame_rate
id|u32
id|_pad_frame_rate
suffix:semicolon
DECL|member|frame_rate
r_volatile
id|u32
id|frame_rate
suffix:semicolon
DECL|member|_pad_field_counter
id|u32
id|_pad_field_counter
suffix:semicolon
DECL|member|field_counter
r_volatile
id|u32
id|field_counter
suffix:semicolon
DECL|member|_pad_line_size
id|u32
id|_pad_line_size
suffix:semicolon
DECL|member|line_size
r_volatile
id|u32
id|line_size
suffix:semicolon
DECL|member|_pad_line_count
id|u32
id|_pad_line_count
suffix:semicolon
DECL|member|line_count
r_volatile
id|u32
id|line_count
suffix:semicolon
DECL|member|_pad_page_index
id|u32
id|_pad_page_index
suffix:semicolon
DECL|member|page_index
r_volatile
id|u32
id|page_index
suffix:semicolon
DECL|member|_pad_next_4_desc
id|u32
id|_pad_next_4_desc
suffix:semicolon
DECL|member|next_4_desc
r_volatile
id|u32
id|next_4_desc
suffix:semicolon
DECL|member|_pad_start_desc_tbl
id|u32
id|_pad_start_desc_tbl
suffix:semicolon
DECL|member|start_desc_tbl
r_volatile
id|u32
id|start_desc_tbl
suffix:semicolon
DECL|macro|VINO_DESC_JUMP
mdefine_line|#define VINO_DESC_JUMP&t;&t;(1&lt;&lt;30)
DECL|macro|VINO_DESC_STOP
mdefine_line|#define VINO_DESC_STOP&t;&t;(1&lt;&lt;31)
DECL|macro|VINO_DESC_VALID
mdefine_line|#define VINO_DESC_VALID&t;&t;(1&lt;&lt;32)
DECL|member|_pad_desc_0
id|u32
id|_pad_desc_0
suffix:semicolon
DECL|member|desc_0
r_volatile
id|u32
id|desc_0
suffix:semicolon
DECL|member|_pad_desc_1
id|u32
id|_pad_desc_1
suffix:semicolon
DECL|member|desc_1
r_volatile
id|u32
id|desc_1
suffix:semicolon
DECL|member|_pad_desc_2
id|u32
id|_pad_desc_2
suffix:semicolon
DECL|member|desc_2
r_volatile
id|u32
id|desc_2
suffix:semicolon
DECL|member|_pad_Bdesc_3
id|u32
id|_pad_Bdesc_3
suffix:semicolon
DECL|member|desc_3
r_volatile
id|u32
id|desc_3
suffix:semicolon
DECL|member|_pad_fifo_thres
id|u32
id|_pad_fifo_thres
suffix:semicolon
DECL|member|fifo_thres
r_volatile
id|u32
id|fifo_thres
suffix:semicolon
DECL|member|_pad_fifo_read
id|u32
id|_pad_fifo_read
suffix:semicolon
DECL|member|fifo_read
r_volatile
id|u32
id|fifo_read
suffix:semicolon
DECL|member|_pad_fifo_write
id|u32
id|_pad_fifo_write
suffix:semicolon
DECL|member|fifo_write
r_volatile
id|u32
id|fifo_write
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgi_vino
r_struct
id|sgi_vino
(brace
DECL|macro|VINO_CHIP_ID
mdefine_line|#define VINO_CHIP_ID&t;&t;0xb
DECL|macro|VINO_REV_NUM
mdefine_line|#define VINO_REV_NUM(x)&t;&t;((x) &amp; 0x0f)
DECL|macro|VINO_ID_VALUE
mdefine_line|#define VINO_ID_VALUE(x)&t;(((x) &amp; 0xf0) &gt;&gt; 4)
DECL|member|_pad_rev_id
id|u32
id|_pad_rev_id
suffix:semicolon
DECL|member|rev_id
r_volatile
id|u32
id|rev_id
suffix:semicolon
DECL|macro|VINO_CTRL_LITTLE_ENDIAN
mdefine_line|#define VINO_CTRL_LITTLE_ENDIAN&t;&t;(1&lt;&lt;0)
DECL|macro|VINO_CTRL_A_FIELD_TRANS_INT
mdefine_line|#define VINO_CTRL_A_FIELD_TRANS_INT&t;(1&lt;&lt;1)&t;/* Field transferred int */
DECL|macro|VINO_CTRL_A_FIFO_OF_INT
mdefine_line|#define VINO_CTRL_A_FIFO_OF_INT&t;&t;(1&lt;&lt;2)&t;/* FIFO overflow int */
DECL|macro|VINO_CTRL_A_END_DESC_TBL_INT
mdefine_line|#define VINO_CTRL_A_END_DESC_TBL_INT&t;(1&lt;&lt;3)&t;/* End of desc table int */
DECL|macro|VINO_CTRL_A_INT
mdefine_line|#define VINO_CTRL_A_INT&t;&t;&t;(VINO_CTRL_A_FIELD_TRANS_INT | &bslash;&n;&t;&t;&t;&t;&t; VINO_CTRL_A_FIFO_OF_INT | &bslash;&n;&t;&t;&t;&t;&t; VINO_CTRL_A_END_DESC_TBL_INT)
DECL|macro|VINO_CTRL_B_FIELD_TRANS_INT
mdefine_line|#define VINO_CTRL_B_FIELD_TRANS_INT&t;(1&lt;&lt;4)&t;/* Field transferred int */
DECL|macro|VINO_CTRL_B_FIFO_OF_INT
mdefine_line|#define VINO_CTRL_B_FIFO_OF_INT&t;&t;(1&lt;&lt;5)&t;/* FIFO overflow int */
DECL|macro|VINO_CTRL_B_END_DESC_TBL_INT
mdefine_line|#define VINO_CTRL_B_END_DESC_TBL_INT&t;(1&lt;&lt;6)&t;/* End of desc table int */
DECL|macro|VINO_CTRL_B_INT
mdefine_line|#define VINO_CTRL_B_INT&t;&t;&t;(VINO_CTRL_B_FIELD_TRANS_INT | &bslash;&n;&t;&t;&t;&t;&t; VINO_CTRL_B_FIFO_OF_INT | &bslash;&n;&t;&t;&t;&t;&t; VINO_CTRL_B_END_DESC_TBL_INT)
DECL|macro|VINO_CTRL_A_DMA_ENBL
mdefine_line|#define VINO_CTRL_A_DMA_ENBL&t;&t;(1&lt;&lt;7)
DECL|macro|VINO_CTRL_A_INTERLEAVE_ENBL
mdefine_line|#define VINO_CTRL_A_INTERLEAVE_ENBL&t;(1&lt;&lt;8)
DECL|macro|VINO_CTRL_A_SYNC_ENBL
mdefine_line|#define VINO_CTRL_A_SYNC_ENBL&t;&t;(1&lt;&lt;9)
DECL|macro|VINO_CTRL_A_SELECT
mdefine_line|#define VINO_CTRL_A_SELECT&t;&t;(1&lt;&lt;10)&t;/* 1=D1 0=Philips */
DECL|macro|VINO_CTRL_A_RGB
mdefine_line|#define VINO_CTRL_A_RGB&t;&t;&t;(1&lt;&lt;11)&t;/* 1=RGB 0=YUV */
DECL|macro|VINO_CTRL_A_LUMA_ONLY
mdefine_line|#define VINO_CTRL_A_LUMA_ONLY&t;&t;(1&lt;&lt;12)
DECL|macro|VINO_CTRL_A_DEC_ENBL
mdefine_line|#define VINO_CTRL_A_DEC_ENBL&t;&t;(1&lt;&lt;13)&t;/* Decimation */
DECL|macro|VINO_CTRL_A_DEC_SCALE_MASK
mdefine_line|#define VINO_CTRL_A_DEC_SCALE_MASK&t;0x1c000&t;/* bits 14:17 */
DECL|macro|VINO_CTRL_A_DEC_SCALE_SHIFT
mdefine_line|#define VINO_CTRL_A_DEC_SCALE_SHIFT&t;(14)
DECL|macro|VINO_CTRL_A_DEC_HOR_ONLY
mdefine_line|#define VINO_CTRL_A_DEC_HOR_ONLY&t;(1&lt;&lt;17)&t;/* Horizontal only */
DECL|macro|VINO_CTRL_A_DITHER
mdefine_line|#define VINO_CTRL_A_DITHER&t;&t;(1&lt;&lt;18)&t;/* 24 -&gt; 8 bit dither */
DECL|macro|VINO_CTRL_B_DMA_ENBL
mdefine_line|#define VINO_CTRL_B_DMA_ENBL&t;&t;(1&lt;&lt;19)
DECL|macro|VINO_CTRL_B_INTERLEAVE_ENBL
mdefine_line|#define VINO_CTRL_B_INTERLEAVE_ENBL&t;(1&lt;&lt;20)
DECL|macro|VINO_CTRL_B_SYNC_ENBL
mdefine_line|#define VINO_CTRL_B_SYNC_ENBL&t;&t;(1&lt;&lt;21)
DECL|macro|VINO_CTRL_B_SELECT
mdefine_line|#define VINO_CTRL_B_SELECT&t;&t;(1&lt;&lt;22)&t;/* 1=D1 0=Philips */
DECL|macro|VINO_CTRL_B_RGB
mdefine_line|#define VINO_CTRL_B_RGB&t;&t;&t;(1&lt;&lt;23)&t;/* 1=RGB 0=YUV */
DECL|macro|VINO_CTRL_B_LUMA_ONLY
mdefine_line|#define VINO_CTRL_B_LUMA_ONLY&t;&t;(1&lt;&lt;24)
DECL|macro|VINO_CTRL_B_DEC_ENBL
mdefine_line|#define VINO_CTRL_B_DEC_ENBL&t;&t;(1&lt;&lt;25)&t;/* Decimation */
DECL|macro|VINO_CTRL_B_DEC_SCALE_MASK
mdefine_line|#define VINO_CTRL_B_DEC_SCALE_MASK&t;0x1c000000&t;/* bits 26:28 */
DECL|macro|VINO_CTRL_B_DEC_SCALE_SHIFT
mdefine_line|#define VINO_CTRL_B_DEC_SCALE_SHIFT&t;(26)
DECL|macro|VINO_CTRL_B_DEC_HOR_ONLY
mdefine_line|#define VINO_CTRL_B_DEC_HOR_ONLY&t;(1&lt;&lt;29)&t;/* Decimation horizontal only */
DECL|macro|VINO_CTRL_B_DITHER
mdefine_line|#define VINO_CTRL_B_DITHER&t;&t;(1&lt;&lt;30)&t;/* ChanB 24 -&gt; 8 bit dither */
DECL|member|_pad_control
id|u32
id|_pad_control
suffix:semicolon
DECL|member|control
r_volatile
id|u32
id|control
suffix:semicolon
DECL|macro|VINO_INTSTAT_A_FIELD_TRANS
mdefine_line|#define VINO_INTSTAT_A_FIELD_TRANS&t;(1&lt;&lt;0)&t;/* Field transferred int */
DECL|macro|VINO_INTSTAT_A_FIFO_OF
mdefine_line|#define VINO_INTSTAT_A_FIFO_OF&t;&t;(1&lt;&lt;1)&t;/* FIFO overflow int */
DECL|macro|VINO_INTSTAT_A_END_DESC_TBL
mdefine_line|#define VINO_INTSTAT_A_END_DESC_TBL&t;(1&lt;&lt;2)&t;/* End of desc table int */
DECL|macro|VINO_INTSTAT_A
mdefine_line|#define VINO_INTSTAT_A&t;&t;&t;(VINO_INTSTAT_A_FIELD_TRANS | &bslash;&n;&t;&t;&t;&t;&t; VINO_INTSTAT_A_FIFO_OF | &bslash;&n;&t;&t;&t;&t;&t; VINO_INTSTAT_A_END_DESC_TBL)
DECL|macro|VINO_INTSTAT_B_FIELD_TRANS
mdefine_line|#define VINO_INTSTAT_B_FIELD_TRANS&t;(1&lt;&lt;3)&t;/* Field transferred int */
DECL|macro|VINO_INTSTAT_B_FIFO_OF
mdefine_line|#define VINO_INTSTAT_B_FIFO_OF&t;&t;(1&lt;&lt;4)&t;/* FIFO overflow int */
DECL|macro|VINO_INTSTAT_B_END_DESC_TBL
mdefine_line|#define VINO_INTSTAT_B_END_DESC_TBL&t;(1&lt;&lt;5)&t;/* End of desc table int */
DECL|macro|VINO_INTSTAT_B
mdefine_line|#define VINO_INTSTAT_B&t;&t;&t;(VINO_INTSTAT_B_FIELD_TRANS | &bslash;&n;&t;&t;&t;&t;&t; VINO_INTSTAT_B_FIFO_OF | &bslash;&n;&t;&t;&t;&t;&t; VINO_INTSTAT_B_END_DESC_TBL)
DECL|member|_pad_intr_status
id|u32
id|_pad_intr_status
suffix:semicolon
DECL|member|intr_status
r_volatile
id|u32
id|intr_status
suffix:semicolon
DECL|member|_pad_i2c_control
id|u32
id|_pad_i2c_control
suffix:semicolon
DECL|member|i2c_control
r_volatile
id|u32
id|i2c_control
suffix:semicolon
DECL|member|_pad_i2c_data
id|u32
id|_pad_i2c_data
suffix:semicolon
DECL|member|i2c_data
r_volatile
id|u32
id|i2c_data
suffix:semicolon
DECL|member|a
r_struct
id|sgi_vino_channel
id|a
suffix:semicolon
DECL|member|b
r_struct
id|sgi_vino_channel
id|b
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
