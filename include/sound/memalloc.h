multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Takashi Iwai &lt;tiwai@suse.de&gt;&n; * &n; *  Generic memory allocators&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_MEMALLOC_H
DECL|macro|__SOUND_MEMALLOC_H
mdefine_line|#define __SOUND_MEMALLOC_H
r_struct
id|device
suffix:semicolon
multiline_comment|/*&n; * buffer device info&n; */
DECL|struct|snd_dma_device
r_struct
id|snd_dma_device
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* SNDRV_DMA_TYPE_XXX */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* generic device */
)brace
suffix:semicolon
macro_line|#ifndef snd_dma_pci_data
DECL|macro|snd_dma_pci_data
mdefine_line|#define snd_dma_pci_data(pci)&t;(&amp;(pci)-&gt;dev)
DECL|macro|snd_dma_isa_data
mdefine_line|#define snd_dma_isa_data()&t;NULL
DECL|macro|snd_dma_sbus_data
mdefine_line|#define snd_dma_sbus_data(sbus)&t;((struct device *)(sbus))
DECL|macro|snd_dma_continuous_data
mdefine_line|#define snd_dma_continuous_data(x)&t;((struct device *)(unsigned long)(x))
macro_line|#endif
multiline_comment|/*&n; * buffer types&n; */
DECL|macro|SNDRV_DMA_TYPE_UNKNOWN
mdefine_line|#define SNDRV_DMA_TYPE_UNKNOWN&t;&t;0&t;/* not defined */
DECL|macro|SNDRV_DMA_TYPE_CONTINUOUS
mdefine_line|#define SNDRV_DMA_TYPE_CONTINUOUS&t;1&t;/* continuous no-DMA memory */
DECL|macro|SNDRV_DMA_TYPE_DEV
mdefine_line|#define SNDRV_DMA_TYPE_DEV&t;&t;2&t;/* generic device continuous */
DECL|macro|SNDRV_DMA_TYPE_DEV_SG
mdefine_line|#define SNDRV_DMA_TYPE_DEV_SG&t;&t;3&t;/* generic device SG-buffer */
DECL|macro|SNDRV_DMA_TYPE_SBUS
mdefine_line|#define SNDRV_DMA_TYPE_SBUS&t;&t;4&t;/* SBUS continuous */
multiline_comment|/*&n; * info for buffer allocation&n; */
DECL|struct|snd_dma_buffer
r_struct
id|snd_dma_buffer
(brace
DECL|member|dev
r_struct
id|snd_dma_device
id|dev
suffix:semicolon
multiline_comment|/* device type */
DECL|member|area
r_int
r_char
op_star
id|area
suffix:semicolon
multiline_comment|/* virtual pointer */
DECL|member|addr
id|dma_addr_t
id|addr
suffix:semicolon
multiline_comment|/* physical address */
DECL|member|bytes
r_int
id|bytes
suffix:semicolon
multiline_comment|/* buffer size in bytes */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* private for allocator; don&squot;t touch */
)brace
suffix:semicolon
multiline_comment|/*&n; * Scatter-Gather generic device pages&n; */
DECL|struct|snd_sg_page
r_struct
id|snd_sg_page
(brace
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
DECL|member|addr
id|dma_addr_t
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_sg_buf
r_struct
id|snd_sg_buf
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* allocated byte size */
DECL|member|pages
r_int
id|pages
suffix:semicolon
multiline_comment|/* allocated pages */
DECL|member|tblsize
r_int
id|tblsize
suffix:semicolon
multiline_comment|/* allocated table size */
DECL|member|table
r_struct
id|snd_sg_page
op_star
id|table
suffix:semicolon
multiline_comment|/* address table */
DECL|member|page_table
r_struct
id|page
op_star
op_star
id|page_table
suffix:semicolon
multiline_comment|/* page table (for vmap/vunmap) */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * return the pages matching with the given byte size&n; */
DECL|function|snd_sgbuf_aligned_pages
r_static
r_inline
r_int
r_int
id|snd_sgbuf_aligned_pages
c_func
(paren
r_int
id|size
)paren
(brace
r_return
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
multiline_comment|/*&n; * return the physical address at the corresponding offset&n; */
DECL|function|snd_sgbuf_get_addr
r_static
r_inline
id|dma_addr_t
id|snd_sgbuf_get_addr
c_func
(paren
r_struct
id|snd_sg_buf
op_star
id|sgbuf
comma
r_int
id|offset
)paren
(brace
r_return
id|sgbuf-&gt;table
(braket
id|offset
op_rshift
id|PAGE_SHIFT
)braket
dot
id|addr
op_plus
id|offset
op_mod
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/* allocate/release a buffer */
r_int
id|snd_dma_alloc_pages
c_func
(paren
r_int
id|type
comma
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
suffix:semicolon
r_int
id|snd_dma_alloc_pages_fallback
c_func
(paren
r_int
id|type
comma
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
suffix:semicolon
r_void
id|snd_dma_free_pages
c_func
(paren
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
suffix:semicolon
multiline_comment|/* buffer-preservation managements */
DECL|macro|snd_dma_pci_buf_id
mdefine_line|#define snd_dma_pci_buf_id(pci)&t;(((unsigned int)(pci)-&gt;vendor &lt;&lt; 16) | (pci)-&gt;device)
r_int
id|snd_dma_get_reserved_buf
c_func
(paren
r_struct
id|snd_dma_buffer
op_star
id|dmab
comma
r_int
r_int
id|id
)paren
suffix:semicolon
r_int
id|snd_dma_reserve_buf
c_func
(paren
r_struct
id|snd_dma_buffer
op_star
id|dmab
comma
r_int
r_int
id|id
)paren
suffix:semicolon
multiline_comment|/* basic memory allocation functions */
r_void
op_star
id|snd_malloc_pages
c_func
(paren
r_int
id|size
comma
r_int
r_int
id|gfp_flags
)paren
suffix:semicolon
r_void
id|snd_free_pages
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_MEMALLOC_H */
eof
