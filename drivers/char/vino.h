multiline_comment|/* $Id: vino.h,v 1.2 1999/02/09 23:03:53 ulfc Exp $&n; * drivers/sgi/vino.h&n; *&n; * Copyright (C) 1999 Ulf Carlsson (ulfc@bun.falkenberg.se)&n; */
DECL|macro|VINO_BASE
mdefine_line|#define VINO_BASE&t;&t;0x0008000
DECL|macro|VINO_REVID
mdefine_line|#define VINO_REVID&t;&t;0x0000
DECL|macro|VINO_CTRL
mdefine_line|#define VINO_CTRL&t;&t;0x0008
DECL|macro|VINO_INTSTAT
mdefine_line|#define VINO_INTSTAT&t;&t;0x0010&t;/* Interrupt status */
DECL|macro|VINO_I2C_CTRL
mdefine_line|#define VINO_I2C_CTRL&t;&t;0x0018
DECL|macro|VINO_I2C_DATA
mdefine_line|#define VINO_I2C_DATA&t;&t;0x0020
DECL|macro|VINO_A_ALPHA
mdefine_line|#define VINO_A_ALPHA&t;&t;0x0028&t;/* Channel A ... */
DECL|macro|VINO_A_CLIPS
mdefine_line|#define VINO_A_CLIPS&t;&t;0x0030&t;/* Clipping start */
DECL|macro|VINO_A_CLIPE
mdefine_line|#define VINO_A_CLIPE&t;&t;0x0038&t;/* Clipping end */
DECL|macro|VINO_A_FRAMERT
mdefine_line|#define VINO_A_FRAMERT&t;&t;0x0040&t;/* Framerate */
DECL|macro|VINO_A_FLDCNT
mdefine_line|#define VINO_A_FLDCNT&t;&t;0x0048&t;/* Field counter */
DECL|macro|VINO_A_LNSZ
mdefine_line|#define VINO_A_LNSZ&t;&t;0x0050
DECL|macro|VINO_A_LNCNT
mdefine_line|#define VINO_A_LNCNT&t;&t;0x0058
DECL|macro|VINO_A_PGIX
mdefine_line|#define VINO_A_PGIX&t;&t;0x0060&t;/* Page index */
DECL|macro|VINO_A_DESC_PTR
mdefine_line|#define VINO_A_DESC_PTR&t;&t;0x0068&t;/* Ptr to next four descriptors */
DECL|macro|VINO_A_DESC_TLB_PTR
mdefine_line|#define VINO_A_DESC_TLB_PTR&t;0x0070&t;/* Ptr to start of descriptor table */
DECL|macro|VINO_A_DESC_DATA0
mdefine_line|#define VINO_A_DESC_DATA0&t;0x0078&t;/* Descriptor data 0 */
DECL|macro|VINO_A_DESC_DATA1
mdefine_line|#define VINO_A_DESC_DATA1&t;0x0080&t;/* ... */
DECL|macro|VINO_A_DESC_DATA2
mdefine_line|#define VINO_A_DESC_DATA2&t;0x0088
DECL|macro|VINO_A_DESC_DATA3
mdefine_line|#define VINO_A_DESC_DATA3&t;0x0090
DECL|macro|VINO_A_FIFO_THRESHOLD
mdefine_line|#define VINO_A_FIFO_THRESHOLD&t;0x0098&t;/* FIFO threshold */
DECL|macro|VINO_A_FIFO_RP
mdefine_line|#define VINO_A_FIFO_RP&t;&t;0x00a0
DECL|macro|VINO_A_FIFO_WP
mdefine_line|#define VINO_A_FIFO_WP&t;&t;0x00a8
DECL|macro|VINO_B_ALPHA
mdefine_line|#define VINO_B_ALPHA&t;&t;0x00b0&t;/* Channel B ... */
DECL|macro|VINO_B_CLIPS
mdefine_line|#define VINO_B_CLIPS&t;&t;0x00b8
DECL|macro|VINO_B_CLIPE
mdefine_line|#define VINO_B_CLIPE&t;&t;0x00c0
DECL|macro|VINO_B_FRAMERT
mdefine_line|#define VINO_B_FRAMERT&t;&t;0x00c8
DECL|macro|VINO_B_FLDCNT
mdefine_line|#define VINO_B_FLDCNT&t;&t;0x00d0
DECL|macro|VINO_B_LNSZ
mdefine_line|#define VINO_B_LNSZ&t;&t;0x00d8
DECL|macro|VINO_B_LNCNT
mdefine_line|#define VINO_B_LNCNT&t;&t;0x00e0
DECL|macro|VINO_B_PGIX
mdefine_line|#define VINO_B_PGIX&t;&t;0x00e8
DECL|macro|VINO_B_DESC_PTR
mdefine_line|#define VINO_B_DESC_PTR&t;&t;0x00f0
DECL|macro|VINO_B_DESC_TLB_PTR
mdefine_line|#define VINO_B_DESC_TLB_PTR&t;0x00f8
DECL|macro|VINO_B_DESC_DATA0
mdefine_line|#define VINO_B_DESC_DATA0&t;0x0100
DECL|macro|VINO_B_DESC_DATA1
mdefine_line|#define VINO_B_DESC_DATA1&t;0x0108
DECL|macro|VINO_B_DESC_DATA2
mdefine_line|#define VINO_B_DESC_DATA2&t;0x0110
DECL|macro|VINO_B_DESC_DATA3
mdefine_line|#define VINO_B_DESC_DATA3&t;0x0118
DECL|macro|VINO_B_FIFO_THRESHOLD
mdefine_line|#define VINO_B_FIFO_THRESHOLD&t;0x0120
DECL|macro|VINO_B_FIFO_RP
mdefine_line|#define VINO_B_FIFO_RP&t;&t;0x0128
DECL|macro|VINO_B_FIFO_WP
mdefine_line|#define VINO_B_FIFO_WP&t;&t;0x0130
multiline_comment|/* Bits in the VINO_REVID register */
DECL|macro|VINO_REVID_REV_MASK
mdefine_line|#define VINO_REVID_REV_MASK&t;&t;0x000f&t;/* bits 0:3 */
DECL|macro|VINO_REVID_ID_MASK
mdefine_line|#define VINO_REVID_ID_MASK&t;&t;0x00f0&t;/* bits 4:7 */
multiline_comment|/* Bits in the VINO_CTRL register */
DECL|macro|VINO_CTRL_LITTLE_ENDIAN
mdefine_line|#define VINO_CTRL_LITTLE_ENDIAN&t;&t;(1&lt;&lt;0)
DECL|macro|VINO_CTRL_A_FIELD_TRANS_INT
mdefine_line|#define VINO_CTRL_A_FIELD_TRANS_INT&t;(1&lt;&lt;1)&t;/* Field transferred int */
DECL|macro|VINO_CTRL_A_FIFO_OF_INT
mdefine_line|#define VINO_CTRL_A_FIFO_OF_INT&t;&t;(1&lt;&lt;2)&t;/* FIFO overflow int */
DECL|macro|VINO_CTRL_A_END_DESC_TBL_INT
mdefine_line|#define VINO_CTRL_A_END_DESC_TBL_INT&t;(1&lt;&lt;3)&t;/* End of desc table int */
DECL|macro|VINO_CTRL_B_FIELD_TRANS_INT
mdefine_line|#define VINO_CTRL_B_FIELD_TRANS_INT&t;(1&lt;&lt;4)&t;/* Field transferred int */
DECL|macro|VINO_CTRL_B_FIFO_OF_INT
mdefine_line|#define VINO_CTRL_B_FIFO_OF_INT&t;&t;(1&lt;&lt;5)&t;/* FIFO overflow int */
DECL|macro|VINO_CTRL_B_END_DESC_TLB_INT
mdefine_line|#define VINO_CTRL_B_END_DESC_TLB_INT&t;(1&lt;&lt;6)&t;/* End of desc table int */
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
mdefine_line|#define VINO_CTRL_B_RGB&t;&t;&t;(1&lt;&lt;22)&t;/* 1=RGB 0=YUV */
DECL|macro|VINO_CTRL_B_LUMA_ONLY
mdefine_line|#define VINO_CTRL_B_LUMA_ONLY&t;&t;(1&lt;&lt;23)
DECL|macro|VINO_CTRL_B_DEC_ENBL
mdefine_line|#define VINO_CTRL_B_DEC_ENBL&t;&t;(1&lt;&lt;24)&t;/* Decimation */
DECL|macro|VINO_CTRL_B_DEC_SCALE_MASK
mdefine_line|#define VINO_CTRL_B_DEC_SCALE_MASK&t;0x1c000000&t;/* bits 25:28 */
DECL|macro|VINO_CTRL_B_DEC_HOR_ONLY
mdefine_line|#define VINO_CTRL_B_DEC_HOR_ONLY&t;(1&lt;&lt;29)&t;/* Decimation horizontal only */
DECL|macro|VINO_CTRL_B_DITHER
mdefine_line|#define VINO_CTRL_B_DITHER&t;&t;(1&lt;&lt;30)&t;/* ChanB 24 -&gt; 8 bit dither */
multiline_comment|/* Bits in the Interrupt and Status register */
DECL|macro|VINO_INTSTAT_A_FIELD_TRANS
mdefine_line|#define VINO_INTSTAT_A_FIELD_TRANS&t;(1&lt;&lt;0)&t;/* Field transferred int */
DECL|macro|VINO_INTSTAT_A_FIFO_OF
mdefine_line|#define VINO_INTSTAT_A_FIFO_OF&t;&t;(1&lt;&lt;1)&t;/* FIFO overflow int */
DECL|macro|VINO_INTSTAT_A_END_DESC_TBL
mdefine_line|#define VINO_INTSTAT_A_END_DESC_TBL&t;(1&lt;&lt;2)&t;/* End of desc table int */
DECL|macro|VINO_INTSTAT_B_FIELD_TRANS
mdefine_line|#define VINO_INTSTAT_B_FIELD_TRANS&t;(1&lt;&lt;3)&t;/* Field transferred int */
DECL|macro|VINO_INTSTAT_B_FIFO_OF
mdefine_line|#define VINO_INTSTAT_B_FIFO_OF&t;&t;(1&lt;&lt;4)&t;/* FIFO overflow int */
DECL|macro|VINO_INTSTAT_B_END_DESC_TBL
mdefine_line|#define VINO_INTSTAT_B_END_DESC_TBL&t;(1&lt;&lt;5)&t;/* End of desc table int */
multiline_comment|/* Bits in the Clipping Start register */
DECL|macro|VINO_CLIPS_START
mdefine_line|#define VINO_CLIPS_START&t;&t;0x3ff&t;&t;/* bits 0:9 */
DECL|macro|VINO_CLIPS_ODD_MASK
mdefine_line|#define VINO_CLIPS_ODD_MASK&t;&t;0x7fc00&t;&t;/* bits 10:18 */
DECL|macro|VINO_CLIPS_EVEN_MASK
mdefine_line|#define VINO_CLIPS_EVEN_MASK&t;&t;0xff80000&t;/* bits 19:27 */
multiline_comment|/* Bits in the Clipping End register */
DECL|macro|VINO_CLIPE_END
mdefine_line|#define VINO_CLIPE_END&t;&t;&t;0x3ff&t;&t;/* bits 0:9 */
DECL|macro|VINO_CLIPE_ODD_MASK
mdefine_line|#define VINO_CLIPE_ODD_MASK&t;&t;0x7fc00&t;&t;/* bits 10:18 */
DECL|macro|VINO_CLIPE_EVEN_MASK
mdefine_line|#define VINO_CLIPE_EVEN_MASK&t;&t;0xff80000&t;/* bits 19:27 */
multiline_comment|/* Bits in the Frame Rate register */
DECL|macro|VINO_FRAMERT_PAL
mdefine_line|#define VINO_FRAMERT_PAL&t;&t;(1&lt;&lt;0)&t;/* 0=NTSC 1=PAL */
DECL|macro|VINO_FRAMERT_RT_MASK
mdefine_line|#define VINO_FRAMERT_RT_MASK&t;&t;0x1ffe&t;&t;/* bits 1:12 */
multiline_comment|/* Bits in the VINO_I2C_CTRL */
DECL|macro|VINO_CTRL_I2C_IDLE
mdefine_line|#define VINO_CTRL_I2C_IDLE&t;&t;(1&lt;&lt;0)&t;/* write: 0=force idle&n;&t;&t;&t;&t;&t;&t; * read: 0=idle 1=not idle */
DECL|macro|VINO_CTRL_I2C_DIR
mdefine_line|#define VINO_CTRL_I2C_DIR&t;&t;(1&lt;&lt;1)&t;/* 0=read 1=write */
DECL|macro|VINO_CTRL_I2C_MORE_BYTES
mdefine_line|#define VINO_CTRL_I2C_MORE_BYTES&t;(1&lt;&lt;2)&t;/* 0=last byte 1=more bytes */
DECL|macro|VINO_CTRL_I2C_TRANS_BUSY
mdefine_line|#define VINO_CTRL_I2C_TRANS_BUSY&t;(1&lt;&lt;4)&t;/* 0=trans done 1=trans busy */
DECL|macro|VINO_CTRL_I2C_ACK
mdefine_line|#define VINO_CTRL_I2C_ACK&t;&t;(1&lt;&lt;5)&t;/* 0=ack received 1=ack not */
DECL|macro|VINO_CTRL_I2C_BUS_ERROR
mdefine_line|#define VINO_CTRL_I2C_BUS_ERROR&t;&t;(1&lt;&lt;7)&t;/* 0=no bus err 1=bus err */
eof
