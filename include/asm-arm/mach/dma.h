multiline_comment|/*&n; *  linux/include/asm-arm/mach/dma.h&n; *&n; *  Copyright (C) 1998-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This header file describes the interface between the generic DMA handler&n; *  (dma.c) and the architecture-specific DMA backends (dma-*.c)&n; */
r_struct
id|dma_struct
suffix:semicolon
DECL|typedef|dma_t
r_typedef
r_struct
id|dma_struct
id|dma_t
suffix:semicolon
DECL|struct|dma_ops
r_struct
id|dma_ops
(brace
DECL|member|request
r_int
(paren
op_star
id|request
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|enable
r_void
(paren
op_star
id|enable
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* mandatory */
DECL|member|disable
r_void
(paren
op_star
id|disable
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* mandatory */
DECL|member|residue
r_int
(paren
op_star
id|residue
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|setspeed
r_int
(paren
op_star
id|setspeed
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dma_struct
r_struct
id|dma_struct
(brace
DECL|member|buf
r_struct
id|scatterlist
id|buf
suffix:semicolon
multiline_comment|/* single DMA&t;&t;&t;*/
DECL|member|sgcount
r_int
id|sgcount
suffix:semicolon
multiline_comment|/* number of DMA SG&t;&t;*/
DECL|member|sg
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
multiline_comment|/* DMA Scatter-Gather List&t;*/
DECL|member|active
r_int
r_int
id|active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transfer active&t;&t;*/
DECL|member|invalid
r_int
r_int
id|invalid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Address/Count changed&t;*/
DECL|member|using_sg
r_int
r_int
id|using_sg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using scatter list?&t;&t;*/
DECL|member|dma_mode
id|dmamode_t
id|dma_mode
suffix:semicolon
multiline_comment|/* DMA mode&t;&t;&t;*/
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* DMA speed&t;&t;&t;*/
DECL|member|lock
r_int
r_int
id|lock
suffix:semicolon
multiline_comment|/* Device is allocated&t;&t;*/
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
multiline_comment|/* Device name&t;&t;&t;*/
DECL|member|dma_base
r_int
r_int
id|dma_base
suffix:semicolon
multiline_comment|/* Controller base address&t;*/
DECL|member|dma_irq
r_int
id|dma_irq
suffix:semicolon
multiline_comment|/* Controller IRQ&t;&t;*/
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Controller state&t;&t;*/
DECL|member|cur_sg
r_struct
id|scatterlist
id|cur_sg
suffix:semicolon
multiline_comment|/* Current controller buffer&t;*/
DECL|member|d_ops
r_struct
id|dma_ops
op_star
id|d_ops
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Prototype: void arch_dma_init(dma)&n; * Purpose  : Initialise architecture specific DMA&n; * Params   : dma - pointer to array of DMA structures&n; */
r_extern
r_void
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
r_extern
r_void
id|isa_init_dma
c_func
(paren
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
eof
