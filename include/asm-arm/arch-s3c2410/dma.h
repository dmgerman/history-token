multiline_comment|/* linux/include/asm-arm/arch-bast/dma.h&n; *&n; * Copyright (C) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Samsung S3C2410X DMA support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  ??-May-2003 BJD   Created file&n; *  ??-Jun-2003 BJD   Added more dma functionality to go with arch&n;*/
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;hardware.h&quot;
multiline_comment|/*&n; * This is the maximum DMA address(physical address) that can be DMAd to.&n; *&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0x20000000
DECL|macro|MAX_DMA_TRANSFER_SIZE
mdefine_line|#define MAX_DMA_TRANSFER_SIZE&t;0x100000 /* Data Unit is half word  */
multiline_comment|/* according to the samsung port, we cannot use the regular&n; * dma channels... we must therefore provide our own interface&n; * for DMA, and allow our drivers to use that.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
multiline_comment|/* we have 4 dma channels */
DECL|macro|S3C2410_DMA_CHANNELS
mdefine_line|#define S3C2410_DMA_CHANNELS&t;    (4)
multiline_comment|/* dma buffer */
DECL|typedef|s3c2410_dma_buf_t
r_typedef
r_struct
id|s3c2410_dma_buf_s
id|s3c2410_dma_buf_t
suffix:semicolon
DECL|struct|s3c2410_dma_buf_s
r_struct
id|s3c2410_dma_buf_s
(brace
DECL|member|next
id|s3c2410_dma_buf_t
op_star
id|next
suffix:semicolon
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* buffer size in bytes */
DECL|member|data
id|dma_addr_t
id|data
suffix:semicolon
multiline_comment|/* start of DMA data */
DECL|member|ptr
id|dma_addr_t
id|ptr
suffix:semicolon
multiline_comment|/* where the DMA got to [1] */
DECL|member|ref
r_int
id|ref
suffix:semicolon
DECL|member|id
r_void
op_star
id|id
suffix:semicolon
multiline_comment|/* client&squot;s id */
DECL|member|no_callback
r_int
r_char
id|no_callback
suffix:semicolon
multiline_comment|/* disable callback for buffer */
)brace
suffix:semicolon
multiline_comment|/* [1] is this updated for both recv/send modes? */
DECL|typedef|s3c2410_dma_chan_t
r_typedef
r_struct
id|s3c2410_dma_chan_s
id|s3c2410_dma_chan_t
suffix:semicolon
DECL|typedef|s3c2410_dma_cbfn_t
r_typedef
r_void
(paren
op_star
id|s3c2410_dma_cbfn_t
)paren
(paren
id|s3c2410_dma_chan_t
op_star
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
DECL|typedef|s3c2410_dma_enfn_t
r_typedef
r_void
(paren
op_star
id|s3c2410_dma_enfn_t
)paren
(paren
id|s3c2410_dma_chan_t
op_star
comma
r_int
id|on
)paren
suffix:semicolon
DECL|typedef|s3c2410_dma_pausefn_t
r_typedef
r_void
(paren
op_star
id|s3c2410_dma_pausefn_t
)paren
(paren
id|s3c2410_dma_chan_t
op_star
comma
r_int
id|on
)paren
suffix:semicolon
DECL|struct|s3c2410_dma_chan_s
r_struct
id|s3c2410_dma_chan_s
(brace
multiline_comment|/* channel state flags */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* number of this dma channel */
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
multiline_comment|/* channel allocated */
DECL|member|started
r_int
r_char
id|started
suffix:semicolon
multiline_comment|/* channel has been started */
DECL|member|stopped
r_int
r_char
id|stopped
suffix:semicolon
multiline_comment|/* channel stopped */
DECL|member|sleeping
r_int
r_char
id|sleeping
suffix:semicolon
DECL|member|xfer_unit
r_int
r_char
id|xfer_unit
suffix:semicolon
multiline_comment|/* size of an transfer */
DECL|member|irq_claimed
r_int
r_char
id|irq_claimed
suffix:semicolon
multiline_comment|/* channel&squot;s hardware position and configuration */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* channels registers */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* channel irq */
DECL|member|addr_reg
r_int
r_int
id|addr_reg
suffix:semicolon
multiline_comment|/* data address register for buffs */
DECL|member|dcon
r_int
r_int
id|dcon
suffix:semicolon
multiline_comment|/* default value of DCON */
multiline_comment|/* driver handlers for channel */
DECL|member|callback_fn
id|s3c2410_dma_cbfn_t
id|callback_fn
suffix:semicolon
multiline_comment|/* callback function for buf-done */
DECL|member|enable_fn
id|s3c2410_dma_enfn_t
id|enable_fn
suffix:semicolon
multiline_comment|/* channel enable function */
DECL|member|pause_fn
id|s3c2410_dma_pausefn_t
id|pause_fn
suffix:semicolon
multiline_comment|/* channel pause function */
multiline_comment|/* buffer list and information */
DECL|member|curr
id|s3c2410_dma_buf_t
op_star
id|curr
suffix:semicolon
multiline_comment|/* current dma buffer */
DECL|member|next
id|s3c2410_dma_buf_t
op_star
id|next
suffix:semicolon
multiline_comment|/* next buffer to load */
DECL|member|end
id|s3c2410_dma_buf_t
op_star
id|end
suffix:semicolon
multiline_comment|/* end of queue */
DECL|member|queue_count
r_int
id|queue_count
suffix:semicolon
multiline_comment|/* number of items in queue */
DECL|member|loaded_count
r_int
id|loaded_count
suffix:semicolon
multiline_comment|/* number of loaded buffers */
)brace
suffix:semicolon
multiline_comment|/* note, we don&squot;t really use dma_deivce_t at the moment */
DECL|typedef|dma_device_t
r_typedef
r_int
r_int
id|dma_device_t
suffix:semicolon
DECL|typedef|s3c2410_dmasrc_t
r_typedef
r_enum
id|s3c2410_dmasrc_e
id|s3c2410_dmasrc_t
suffix:semicolon
multiline_comment|/* these two defines control the source for the dma channel,&n; * wether it is from memory or an device&n;*/
DECL|enum|s3c2410_dmasrc_e
r_enum
id|s3c2410_dmasrc_e
(brace
DECL|enumerator|S3C2410_DMASRC_HW
id|S3C2410_DMASRC_HW
comma
multiline_comment|/* source is memory */
DECL|enumerator|S3C2410_DMASRC_MEM
id|S3C2410_DMASRC_MEM
multiline_comment|/* source is hardware */
)brace
suffix:semicolon
multiline_comment|/* dma control routines */
r_extern
r_int
id|s3c2410_request_dma
c_func
(paren
id|dmach_t
id|channel
comma
r_const
r_char
op_star
id|devid
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_free_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_flush_all
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_stop
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_resume
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_queue
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
id|id
comma
id|dma_addr_t
id|data
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|s3c2410_dma_queue_buffer
mdefine_line|#define s3c2410_dma_queue_buffer s3c2410_dma_queue
multiline_comment|/* channel configuration */
r_extern
r_int
id|s3c2410_dma_config
c_func
(paren
id|dmach_t
id|channel
comma
r_int
id|xferunit
comma
r_int
id|dcon
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_devconfig
c_func
(paren
r_int
id|channel
comma
id|s3c2410_dmasrc_t
id|source
comma
r_int
id|hwcfg
comma
r_int
r_int
id|devaddr
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_set_enablefn
c_func
(paren
id|dmach_t
comma
id|s3c2410_dma_enfn_t
id|rtn
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_set_pausefn
c_func
(paren
id|dmach_t
comma
id|s3c2410_dma_pausefn_t
id|rtn
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_set_callbackfn
c_func
(paren
id|dmach_t
comma
id|s3c2410_dma_cbfn_t
id|rtn
)paren
suffix:semicolon
DECL|macro|s3c2410_dma_set_callback
mdefine_line|#define s3c2410_dma_set_callback s3c2410_dma_set_callbackfn
DECL|macro|S3C2410_DMA_DISRC
mdefine_line|#define S3C2410_DMA_DISRC&t;(0x00)
DECL|macro|S3C2410_DMA_DISRCC
mdefine_line|#define S3C2410_DMA_DISRCC&t;(0x04)
DECL|macro|S3C2410_DMA_DIDST
mdefine_line|#define S3C2410_DMA_DIDST&t;(0x08)
DECL|macro|S3C2410_DMA_DIDSTC
mdefine_line|#define S3C2410_DMA_DIDSTC&t;(0x0C)
DECL|macro|S3C2410_DMA_DCON
mdefine_line|#define S3C2410_DMA_DCON&t;(0x10)
DECL|macro|S3C2410_DMA_DSTAT
mdefine_line|#define S3C2410_DMA_DSTAT&t;(0x14)
DECL|macro|S3C2410_DMA_DCSRC
mdefine_line|#define S3C2410_DMA_DCSRC&t;(0x18)
DECL|macro|S3C2410_DMA_DCDST
mdefine_line|#define S3C2410_DMA_DCDST&t;(0x1C)
DECL|macro|S3C2410_DMA_DMASKTRIG
mdefine_line|#define S3C2410_DMA_DMASKTRIG&t;(0x20)
DECL|macro|S3C2410_DMASKTRIG_STOP
mdefine_line|#define S3C2410_DMASKTRIG_STOP&t; (1&lt;&lt;2)
DECL|macro|S3C2410_DMASKTRIG_ON
mdefine_line|#define S3C2410_DMASKTRIG_ON&t; (1&lt;&lt;1)
DECL|macro|S3C2410_DMASKTRIG_SWTRIG
mdefine_line|#define S3C2410_DMASKTRIG_SWTRIG (1&lt;&lt;0)
DECL|macro|S3C2410_DCOM_DEMAND
mdefine_line|#define S3C2410_DCOM_DEMAND&t;(0&lt;&lt;31)
DECL|macro|S3C2410_DCON_HANDSHAKE
mdefine_line|#define S3C2410_DCON_HANDSHAKE  (1&lt;&lt;31)
DECL|macro|S3C2410_DCON_SYNC_PCLK
mdefine_line|#define S3C2410_DCON_SYNC_PCLK  (0&lt;&lt;30)
DECL|macro|S3C2410_DCON_SYNC_HCLK
mdefine_line|#define S3C2410_DCON_SYNC_HCLK  (1&lt;&lt;30)
DECL|macro|S3C2410_DCON_INTREQ
mdefine_line|#define S3C2410_DCON_INTREQ&t;(1&lt;&lt;29)
DECL|macro|S3C2410_DCON_SRCSHIFT
mdefine_line|#define S3C2410_DCON_SRCSHIFT&t;(24)
DECL|macro|S3C2410_DCON_BYTE
mdefine_line|#define S3C2410_DCON_BYTE&t;(0&lt;&lt;20)
DECL|macro|S3C2410_DCON_HALFWORD
mdefine_line|#define S3C2410_DCON_HALFWORD&t;(1&lt;&lt;20)
DECL|macro|S3C2410_DCON_WORD
mdefine_line|#define S3C2410_DCON_WORD&t;(2&lt;&lt;20)
DECL|macro|S3C2410_DCON_AUTORELOAD
mdefine_line|#define S3C2410_DCON_AUTORELOAD (0&lt;&lt;22)
DECL|macro|S3C2410_DCON_HWTRIG
mdefine_line|#define S3C2410_DCON_HWTRIG&t;(1&lt;&lt;23)
macro_line|#endif /* __ASM_ARCH_DMA_H */
eof
