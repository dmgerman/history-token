multiline_comment|/*&n; * arch/sh/drivers/dma/dma-sh.h&n; *&n; * Copyright (C) 2000  Takashi YOSHII&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __DMA_SH_H
DECL|macro|__DMA_SH_H
mdefine_line|#define __DMA_SH_H
multiline_comment|/* Definitions for the SuperH DMAC */
DECL|macro|REQ_L
mdefine_line|#define REQ_L&t;0x00000000
DECL|macro|REQ_E
mdefine_line|#define REQ_E&t;0x00080000
DECL|macro|RACK_H
mdefine_line|#define RACK_H&t;0x00000000
DECL|macro|RACK_L
mdefine_line|#define RACK_L&t;0x00040000
DECL|macro|ACK_R
mdefine_line|#define ACK_R&t;0x00000000
DECL|macro|ACK_W
mdefine_line|#define ACK_W&t;0x00020000
DECL|macro|ACK_H
mdefine_line|#define ACK_H&t;0x00000000
DECL|macro|ACK_L
mdefine_line|#define ACK_L&t;0x00010000
DECL|macro|DM_INC
mdefine_line|#define DM_INC&t;0x00004000
DECL|macro|DM_DEC
mdefine_line|#define DM_DEC&t;0x00008000
DECL|macro|SM_INC
mdefine_line|#define SM_INC&t;0x00001000
DECL|macro|SM_DEC
mdefine_line|#define SM_DEC&t;0x00002000
DECL|macro|RS_DUAL
mdefine_line|#define RS_DUAL&t;0x00000000
DECL|macro|RS_IN
mdefine_line|#define RS_IN&t;0x00000200
DECL|macro|RS_OUT
mdefine_line|#define RS_OUT&t;0x00000300
DECL|macro|TM_BURST
mdefine_line|#define TM_BURST 0x0000080
DECL|macro|TS_8
mdefine_line|#define TS_8&t;0x00000010
DECL|macro|TS_16
mdefine_line|#define TS_16&t;0x00000020
DECL|macro|TS_32
mdefine_line|#define TS_32&t;0x00000030
DECL|macro|TS_64
mdefine_line|#define TS_64&t;0x00000000
DECL|macro|TS_BLK
mdefine_line|#define TS_BLK&t;0x00000040
DECL|macro|CHCR_DE
mdefine_line|#define CHCR_DE 0x00000001
DECL|macro|CHCR_TE
mdefine_line|#define CHCR_TE 0x00000002
DECL|macro|CHCR_IE
mdefine_line|#define CHCR_IE 0x00000004
DECL|macro|DMAOR_COD
mdefine_line|#define DMAOR_COD&t;0x00000008
DECL|macro|DMAOR_AE
mdefine_line|#define DMAOR_AE&t;0x00000004
DECL|macro|DMAOR_NMIF
mdefine_line|#define DMAOR_NMIF&t;0x00000002
DECL|macro|DMAOR_DME
mdefine_line|#define DMAOR_DME&t;0x00000001
DECL|macro|MAX_DMAC_CHANNELS
mdefine_line|#define MAX_DMAC_CHANNELS&t;(CONFIG_NR_ONCHIP_DMA_CHANNELS)
macro_line|#endif /* __DMA_SH_H */
eof
