multiline_comment|/*&n; * Definitions shared between dma-sa1100.c and dma-sa1111.c&n; * (C) 2000 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * DMA buffer structure&n; */
DECL|struct|dma_buf_s
r_typedef
r_struct
id|dma_buf_s
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* buffer size */
DECL|member|dma_start
id|dma_addr_t
id|dma_start
suffix:semicolon
multiline_comment|/* starting DMA address */
DECL|member|dma_ptr
id|dma_addr_t
id|dma_ptr
suffix:semicolon
multiline_comment|/* next DMA pointer to use */
DECL|member|ref
r_int
id|ref
suffix:semicolon
multiline_comment|/* number of DMA references */
DECL|member|id
r_void
op_star
id|id
suffix:semicolon
multiline_comment|/* to identify buffer from outside */
DECL|member|next
r_struct
id|dma_buf_s
op_star
id|next
suffix:semicolon
multiline_comment|/* next buffer to process */
DECL|typedef|dma_buf_t
)brace
id|dma_buf_t
suffix:semicolon
multiline_comment|/*&n; * DMA channel structure.&n; */
r_typedef
r_struct
(brace
DECL|member|in_use
r_int
r_int
id|in_use
suffix:semicolon
multiline_comment|/* Device is allocated */
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
multiline_comment|/* Device name */
DECL|member|device
id|dma_device_t
id|device
suffix:semicolon
multiline_comment|/* ... to which this channel is attached */
DECL|member|head
id|dma_buf_t
op_star
id|head
suffix:semicolon
multiline_comment|/* where to insert buffers */
DECL|member|tail
id|dma_buf_t
op_star
id|tail
suffix:semicolon
multiline_comment|/* where to remove buffers */
DECL|member|curr
id|dma_buf_t
op_star
id|curr
suffix:semicolon
multiline_comment|/* buffer currently DMA&squot;ed */
DECL|member|stopped
r_int
id|stopped
suffix:semicolon
multiline_comment|/* 1 if DMA is stalled */
DECL|member|regs
id|dma_regs_t
op_star
id|regs
suffix:semicolon
multiline_comment|/* points to appropriate DMA registers */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ used by the channel */
DECL|member|callback
id|dma_callback_t
id|callback
suffix:semicolon
multiline_comment|/* ... to call when buffers are done */
DECL|member|spin_size
r_int
id|spin_size
suffix:semicolon
multiline_comment|/* &gt; 0 when DMA should spin when no more buffer */
DECL|member|spin_addr
id|dma_addr_t
id|spin_addr
suffix:semicolon
multiline_comment|/* DMA address to spin onto */
DECL|member|spin_ref
r_int
id|spin_ref
suffix:semicolon
multiline_comment|/* number of spinning references */
macro_line|#ifdef CONFIG_SA1111
DECL|member|dma_a
DECL|member|dma_b
DECL|member|last_dma
r_int
id|dma_a
comma
id|dma_b
comma
id|last_dma
suffix:semicolon
multiline_comment|/* SA-1111 specific */
macro_line|#endif
DECL|typedef|sa1100_dma_t
)brace
id|sa1100_dma_t
suffix:semicolon
r_extern
id|sa1100_dma_t
id|dma_chan
(braket
id|MAX_SA1100_DMA_CHANNELS
)braket
suffix:semicolon
r_int
id|start_sa1111_sac_dma
c_func
(paren
id|sa1100_dma_t
op_star
id|dma
comma
id|dma_addr_t
id|dma_ptr
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|sa1111_dma_get_current
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
op_star
id|buf_id
comma
id|dma_addr_t
op_star
id|addr
)paren
suffix:semicolon
r_int
id|sa1111_dma_stop
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_int
id|sa1111_dma_resume
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_void
id|sa1111_reset_sac_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_void
id|sa1111_cleanup_sac_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
r_void
id|sa1100_dma_done
(paren
id|sa1100_dma_t
op_star
id|dma
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SA1111
DECL|macro|channel_is_sa1111_sac
mdefine_line|#define channel_is_sa1111_sac(ch) &bslash;&n;&t;((ch) &gt;= SA1111_SAC_DMA_BASE &amp;&amp; &bslash;&n;&t; (ch) &lt;  SA1111_SAC_DMA_BASE + SA1111_SAC_DMA_CHANNELS)
macro_line|#else
DECL|macro|channel_is_sa1111_sac
mdefine_line|#define channel_is_sa1111_sac(ch) (0)
macro_line|#endif
eof
