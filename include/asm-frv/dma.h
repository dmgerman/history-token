multiline_comment|/* dma.h: FRV DMA controller management&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
singleline_comment|//#define DMA_DEBUG 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|macro|MAX_DMA_CHANNELS
macro_line|#undef MAX_DMA_CHANNELS&t;&t;/* don&squot;t use kernel/dma.c */
multiline_comment|/* under 2.4 this is actually needed by the new bootmem allocator */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;PAGE_OFFSET
multiline_comment|/*&n; * FRV DMA controller management&n; */
r_struct
id|pt_regs
suffix:semicolon
DECL|typedef|dma_irq_handler_t
r_typedef
id|irqreturn_t
(paren
op_star
id|dma_irq_handler_t
)paren
(paren
r_int
id|dmachan
comma
r_int
r_int
id|cstr
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|frv_dma_open
c_func
(paren
r_const
r_char
op_star
id|devname
comma
r_int
r_int
id|dmamask
comma
r_int
id|dmacap
comma
id|dma_irq_handler_t
id|handler
comma
r_int
r_int
id|irq_flags
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* channels required */
DECL|macro|FRV_DMA_MASK_ANY
mdefine_line|#define FRV_DMA_MASK_ANY&t;ULONG_MAX&t;/* any channel */
multiline_comment|/* capabilities required */
DECL|macro|FRV_DMA_CAP_DREQ
mdefine_line|#define FRV_DMA_CAP_DREQ&t;0x01&t;&t;/* DMA request pin */
DECL|macro|FRV_DMA_CAP_DACK
mdefine_line|#define FRV_DMA_CAP_DACK&t;0x02&t;&t;/* DMA ACK pin */
DECL|macro|FRV_DMA_CAP_DONE
mdefine_line|#define FRV_DMA_CAP_DONE&t;0x04&t;&t;/* DMA done pin */
r_extern
r_void
id|frv_dma_close
c_func
(paren
r_int
id|dma
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_config
c_func
(paren
r_int
id|dma
comma
r_int
r_int
id|ccfr
comma
r_int
r_int
id|cctr
comma
r_int
r_int
id|apr
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_start
c_func
(paren
r_int
id|dma
comma
r_int
r_int
id|sba
comma
r_int
r_int
id|dba
comma
r_int
r_int
id|pix
comma
r_int
r_int
id|six
comma
r_int
r_int
id|bcl
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_restart_circular
c_func
(paren
r_int
id|dma
comma
r_int
r_int
id|six
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_stop
c_func
(paren
r_int
id|dma
)paren
suffix:semicolon
r_extern
r_int
id|is_frv_dma_interrupting
c_func
(paren
r_int
id|dma
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_dump
c_func
(paren
r_int
id|dma
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_status_clear
c_func
(paren
r_int
id|dma
)paren
suffix:semicolon
DECL|macro|FRV_DMA_NCHANS
mdefine_line|#define FRV_DMA_NCHANS&t;8
DECL|macro|FRV_DMA_4CHANS
mdefine_line|#define FRV_DMA_4CHANS&t;4
DECL|macro|FRV_DMA_8CHANS
mdefine_line|#define FRV_DMA_8CHANS&t;8
DECL|macro|DMAC_CCFRx
mdefine_line|#define DMAC_CCFRx&t;&t;0x00&t;/* channel configuration reg */
DECL|macro|DMAC_CCFRx_CM_SHIFT
mdefine_line|#define DMAC_CCFRx_CM_SHIFT&t;16
DECL|macro|DMAC_CCFRx_CM_DA
mdefine_line|#define DMAC_CCFRx_CM_DA&t;0x00000000
DECL|macro|DMAC_CCFRx_CM_SCA
mdefine_line|#define DMAC_CCFRx_CM_SCA&t;0x00010000
DECL|macro|DMAC_CCFRx_CM_DCA
mdefine_line|#define DMAC_CCFRx_CM_DCA&t;0x00020000
DECL|macro|DMAC_CCFRx_CM_2D
mdefine_line|#define DMAC_CCFRx_CM_2D&t;0x00030000
DECL|macro|DMAC_CCFRx_ATS_SHIFT
mdefine_line|#define DMAC_CCFRx_ATS_SHIFT&t;8
DECL|macro|DMAC_CCFRx_RS_INTERN
mdefine_line|#define DMAC_CCFRx_RS_INTERN&t;0x00000000
DECL|macro|DMAC_CCFRx_RS_EXTERN
mdefine_line|#define DMAC_CCFRx_RS_EXTERN&t;0x00000001
DECL|macro|DMAC_CCFRx_RS_SHIFT
mdefine_line|#define DMAC_CCFRx_RS_SHIFT&t;0
DECL|macro|DMAC_CSTRx
mdefine_line|#define DMAC_CSTRx&t;&t;0x08&t;/* channel status reg */
DECL|macro|DMAC_CSTRx_FS
mdefine_line|#define DMAC_CSTRx_FS&t;&t;0x0000003f
DECL|macro|DMAC_CSTRx_NE
mdefine_line|#define DMAC_CSTRx_NE&t;&t;0x00000100
DECL|macro|DMAC_CSTRx_FED
mdefine_line|#define DMAC_CSTRx_FED&t;&t;0x00000200
DECL|macro|DMAC_CSTRx_WER
mdefine_line|#define DMAC_CSTRx_WER&t;&t;0x00000800
DECL|macro|DMAC_CSTRx_RER
mdefine_line|#define DMAC_CSTRx_RER&t;&t;0x00001000
DECL|macro|DMAC_CSTRx_CE
mdefine_line|#define DMAC_CSTRx_CE&t;&t;0x00002000
DECL|macro|DMAC_CSTRx_INT
mdefine_line|#define DMAC_CSTRx_INT&t;&t;0x00800000
DECL|macro|DMAC_CSTRx_BUSY
mdefine_line|#define DMAC_CSTRx_BUSY&t;&t;0x80000000
DECL|macro|DMAC_CCTRx
mdefine_line|#define DMAC_CCTRx&t;&t;0x10&t;/* channel control reg */
DECL|macro|DMAC_CCTRx_DSIZ_1
mdefine_line|#define DMAC_CCTRx_DSIZ_1&t;0x00000000
DECL|macro|DMAC_CCTRx_DSIZ_2
mdefine_line|#define DMAC_CCTRx_DSIZ_2&t;0x00000001
DECL|macro|DMAC_CCTRx_DSIZ_4
mdefine_line|#define DMAC_CCTRx_DSIZ_4&t;0x00000002
DECL|macro|DMAC_CCTRx_DSIZ_32
mdefine_line|#define DMAC_CCTRx_DSIZ_32&t;0x00000005
DECL|macro|DMAC_CCTRx_DAU_HOLD
mdefine_line|#define DMAC_CCTRx_DAU_HOLD&t;0x00000000
DECL|macro|DMAC_CCTRx_DAU_INC
mdefine_line|#define DMAC_CCTRx_DAU_INC&t;0x00000010
DECL|macro|DMAC_CCTRx_DAU_DEC
mdefine_line|#define DMAC_CCTRx_DAU_DEC&t;0x00000020
DECL|macro|DMAC_CCTRx_SSIZ_1
mdefine_line|#define DMAC_CCTRx_SSIZ_1&t;0x00000000
DECL|macro|DMAC_CCTRx_SSIZ_2
mdefine_line|#define DMAC_CCTRx_SSIZ_2&t;0x00000100
DECL|macro|DMAC_CCTRx_SSIZ_4
mdefine_line|#define DMAC_CCTRx_SSIZ_4&t;0x00000200
DECL|macro|DMAC_CCTRx_SSIZ_32
mdefine_line|#define DMAC_CCTRx_SSIZ_32&t;0x00000500
DECL|macro|DMAC_CCTRx_SAU_HOLD
mdefine_line|#define DMAC_CCTRx_SAU_HOLD&t;0x00000000
DECL|macro|DMAC_CCTRx_SAU_INC
mdefine_line|#define DMAC_CCTRx_SAU_INC&t;0x00001000
DECL|macro|DMAC_CCTRx_SAU_DEC
mdefine_line|#define DMAC_CCTRx_SAU_DEC&t;0x00002000
DECL|macro|DMAC_CCTRx_FC
mdefine_line|#define DMAC_CCTRx_FC&t;&t;0x08000000
DECL|macro|DMAC_CCTRx_ICE
mdefine_line|#define DMAC_CCTRx_ICE&t;&t;0x10000000
DECL|macro|DMAC_CCTRx_IE
mdefine_line|#define DMAC_CCTRx_IE&t;&t;0x40000000
DECL|macro|DMAC_CCTRx_ACT
mdefine_line|#define DMAC_CCTRx_ACT&t;&t;0x80000000
DECL|macro|DMAC_SBAx
mdefine_line|#define DMAC_SBAx&t;&t;0x18&t;/* source base address reg */
DECL|macro|DMAC_DBAx
mdefine_line|#define DMAC_DBAx&t;&t;0x20&t;/* data base address reg */
DECL|macro|DMAC_PIXx
mdefine_line|#define DMAC_PIXx&t;&t;0x28&t;/* primary index reg */
DECL|macro|DMAC_SIXx
mdefine_line|#define DMAC_SIXx&t;&t;0x30&t;/* secondary index reg */
DECL|macro|DMAC_BCLx
mdefine_line|#define DMAC_BCLx&t;&t;0x38&t;/* byte count limit reg */
DECL|macro|DMAC_APRx
mdefine_line|#define DMAC_APRx&t;&t;0x40&t;/* alternate pointer reg */
multiline_comment|/*&n; * required for PCI + MODULES&n; */
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* _ASM_DMA_H */
eof
