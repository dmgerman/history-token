multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_DMAMAP_H
DECL|macro|_ASM_SN_DMAMAP_H
mdefine_line|#define _ASM_SN_DMAMAP_H
macro_line|#include &lt;asm/sn/sv.h&gt;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*&n; * Definitions for allocating, freeing, and using DMA maps&n; */
multiline_comment|/*&n; * DMA map types&n; */
DECL|macro|DMA_SCSI
mdefine_line|#define&t;DMA_SCSI&t;0
DECL|macro|DMA_A24VME
mdefine_line|#define&t;DMA_A24VME&t;1&t;&t;/* Challenge/Onyx only &t;*/
DECL|macro|DMA_A32VME
mdefine_line|#define&t;DMA_A32VME&t;2&t;&t;/* Challenge/Onyx only &t;*/
DECL|macro|DMA_A64VME
mdefine_line|#define&t;DMA_A64VME&t;3&t;&t;/* SN0/Racer */
DECL|macro|DMA_EISA
mdefine_line|#define&t;DMA_EISA&t;4
DECL|macro|DMA_PCI32
mdefine_line|#define&t;DMA_PCI32&t;5&t;&t;/* SN0/Racer &t;*/
DECL|macro|DMA_PCI64
mdefine_line|#define&t;DMA_PCI64&t;6&t;&t;/* SN0/Racer &t;*/
multiline_comment|/*&n; * DMA map structure as returned by dma_mapalloc()&n; */
DECL|struct|dmamap
r_typedef
r_struct
id|dmamap
(brace
DECL|member|dma_type
r_int
id|dma_type
suffix:semicolon
multiline_comment|/* Map type (see above) */
DECL|member|dma_adap
r_int
id|dma_adap
suffix:semicolon
multiline_comment|/* I/O adapter */
DECL|member|dma_index
r_int
id|dma_index
suffix:semicolon
multiline_comment|/* Beginning map register to use */
DECL|member|dma_size
r_int
id|dma_size
suffix:semicolon
multiline_comment|/* Number of map registers to use */
DECL|member|dma_addr
id|paddr_t
id|dma_addr
suffix:semicolon
multiline_comment|/* Corresponding bus addr for A24/A32 */
DECL|member|dma_virtaddr
id|caddr_t
id|dma_virtaddr
suffix:semicolon
multiline_comment|/* Beginning virtual address that is mapped */
DECL|typedef|dmamap_t
)brace
id|dmamap_t
suffix:semicolon
r_struct
id|alenlist_s
suffix:semicolon
multiline_comment|/*&n; * Prototypes of exported functions&n; */
r_extern
id|dmamap_t
op_star
id|dma_mapalloc
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|dma_mapfree
c_func
(paren
id|dmamap_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dma_map
c_func
(paren
id|dmamap_t
op_star
comma
id|caddr_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|dma_map2
c_func
(paren
id|dmamap_t
op_star
comma
id|caddr_t
comma
id|caddr_t
comma
r_int
)paren
suffix:semicolon
r_extern
id|paddr_t
id|dma_mapaddr
c_func
(paren
id|dmamap_t
op_star
comma
id|caddr_t
)paren
suffix:semicolon
macro_line|#ifdef LATER
r_extern
r_int
id|dma_mapbp
c_func
(paren
id|dmamap_t
op_star
comma
id|buf_t
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|dma_map_alenlist
c_func
(paren
id|dmamap_t
op_star
comma
r_struct
id|alenlist_s
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|uint
id|ev_kvtoiopnum
c_func
(paren
id|caddr_t
)paren
suffix:semicolon
multiline_comment|/*&n; * These variables are defined in master.d/kernel&n; */
r_extern
r_struct
id|map
op_star
id|a24map
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|map
op_star
id|a32map
(braket
)braket
suffix:semicolon
r_extern
r_int
id|a24_mapsize
suffix:semicolon
r_extern
r_int
id|a32_mapsize
suffix:semicolon
r_extern
id|lock_t
id|dmamaplock
suffix:semicolon
r_extern
id|sv_t
id|dmamapout
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
multiline_comment|/* standard flags values for pio_map routines,&n; * including {xtalk,pciio}_dmamap calls.&n; * NOTE: try to keep these in step with PIOMAP flags.&n; */
DECL|macro|DMAMAP_FIXED
mdefine_line|#define DMAMAP_FIXED&t;0x1
DECL|macro|DMAMAP_NOSLEEP
mdefine_line|#define DMAMAP_NOSLEEP&t;0x2
DECL|macro|DMAMAP_INPLACE
mdefine_line|#define&t;DMAMAP_INPLACE&t;0x4
DECL|macro|DMAMAP_FLAGS
mdefine_line|#define&t;DMAMAP_FLAGS&t;0x7
macro_line|#endif /* _ASM_SN_DMAMAP_H */
eof
