multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_DMAMAP_H
DECL|macro|_ASM_IA64_SN_DMAMAP_H
mdefine_line|#define _ASM_IA64_SN_DMAMAP_H
macro_line|#include &lt;asm/sn/types.h&gt;
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
r_int
r_int
id|dma_virtaddr
suffix:semicolon
multiline_comment|/* Beginning virtual address that is mapped */
DECL|typedef|dmamap_t
)brace
id|dmamap_t
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
macro_line|#endif /* _ASM_IA64_SN_DMAMAP_H */
eof
