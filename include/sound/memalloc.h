multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Takashi Iwai &lt;tiwai@suse.de&gt;&n; * &n; *  Generic memory allocators&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_MEMALLOC_H
DECL|macro|__SOUND_MEMALLOC_H
mdefine_line|#define __SOUND_MEMALLOC_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#ifdef CONFIG_SBUS
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#endif
multiline_comment|/*&n; * buffer device info&n; */
DECL|struct|snd_dma_device
r_struct
id|snd_dma_device
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* SNDRV_MEM_TYPE_XXX */
r_union
(brace
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
multiline_comment|/* for PCI and PCI-SG types */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* GFP_XXX for continous and ISA types */
macro_line|#ifdef CONFIG_SBUS
DECL|member|sbus
r_struct
id|sbus_dev
op_star
id|sbus
suffix:semicolon
multiline_comment|/* for SBUS type */
macro_line|#endif
DECL|member|dev
)brace
id|dev
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* a unique ID */
)brace
suffix:semicolon
multiline_comment|/*&n; * buffer types&n; */
DECL|macro|SNDRV_DMA_TYPE_UNKNOWN
mdefine_line|#define SNDRV_DMA_TYPE_UNKNOWN&t;&t;0&t;/* not defined */
DECL|macro|SNDRV_DMA_TYPE_CONTINUOUS
mdefine_line|#define SNDRV_DMA_TYPE_CONTINUOUS&t;1&t;/* continuous no-DMA memory */
DECL|macro|SNDRV_DMA_TYPE_ISA
mdefine_line|#define SNDRV_DMA_TYPE_ISA&t;&t;2&t;/* ISA continuous */
DECL|macro|SNDRV_DMA_TYPE_PCI
mdefine_line|#define SNDRV_DMA_TYPE_PCI&t;&t;3&t;/* PCI continuous */
DECL|macro|SNDRV_DMA_TYPE_SBUS
mdefine_line|#define SNDRV_DMA_TYPE_SBUS&t;&t;4&t;/* SBUS continuous */
DECL|macro|SNDRV_DMA_TYPE_PCI_SG
mdefine_line|#define SNDRV_DMA_TYPE_PCI_SG&t;&t;5&t;/* PCI SG-buffer */
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n; * compose a snd_dma_device struct for the PCI device&n; */
DECL|function|snd_dma_device_pci
r_static
r_inline
r_void
id|snd_dma_device_pci
c_func
(paren
r_struct
id|snd_dma_device
op_star
id|dev
comma
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|id
)paren
(brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;type
op_assign
id|SNDRV_DMA_TYPE_PCI
suffix:semicolon
id|dev-&gt;dev.pci
op_assign
id|pci
suffix:semicolon
id|dev-&gt;id
op_assign
id|id
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * info for buffer allocation&n; */
DECL|struct|snd_dma_buffer
r_struct
id|snd_dma_buffer
(brace
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
multiline_comment|/* allocate/release a buffer */
r_int
id|snd_dma_alloc_pages
c_func
(paren
r_const
r_struct
id|snd_dma_device
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
r_const
r_struct
id|snd_dma_device
op_star
id|dev
comma
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
suffix:semicolon
multiline_comment|/* buffer-preservation managements */
r_int
id|snd_dma_get_reserved
c_func
(paren
r_const
r_struct
id|snd_dma_device
op_star
id|dev
comma
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
suffix:semicolon
r_int
id|snd_dma_free_reserved
c_func
(paren
r_const
r_struct
id|snd_dma_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|snd_dma_set_reserved
c_func
(paren
r_const
r_struct
id|snd_dma_device
op_star
id|dev
comma
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
suffix:semicolon
multiline_comment|/*&n; * Generic memory allocators&n; */
multiline_comment|/*&n; * continuous pages&n; */
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
op_star
id|snd_malloc_pages_fallback
c_func
(paren
r_int
id|size
comma
r_int
r_int
id|gfp_flags
comma
r_int
op_star
id|res_size
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
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n; * PCI continuous pages&n; */
r_void
op_star
id|snd_malloc_pci_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_pci_pages_fallback
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
op_star
id|res_size
)paren
suffix:semicolon
r_void
id|snd_free_pci_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
multiline_comment|/* one page allocation */
r_void
op_star
id|snd_malloc_pci_page
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
suffix:semicolon
DECL|macro|snd_free_pci_page
mdefine_line|#define snd_free_pci_page(pci,ptr,addr) snd_free_pci_pages(pci,PAGE_SIZE,ptr,addr)
macro_line|#endif
macro_line|#ifdef CONFIG_SBUS
multiline_comment|/*&n; * SBUS continuous pages&n; */
r_void
op_star
id|snd_malloc_sbus_pages
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_sbus_pages_fallback
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
op_star
id|res_size
)paren
suffix:semicolon
r_void
id|snd_free_sbus_pages
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISA
multiline_comment|/*&n; * ISA continuous pages&n; */
r_void
op_star
id|snd_malloc_isa_pages
c_func
(paren
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_isa_pages_fallback
c_func
(paren
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
op_star
id|res_size
)paren
suffix:semicolon
r_void
id|snd_free_isa_pages
c_func
(paren
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|addr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|macro|snd_malloc_isa_pages
mdefine_line|#define snd_malloc_isa_pages(size, dma_addr) snd_malloc_pci_pages(NULL, size, dma_addr)
DECL|macro|snd_malloc_isa_pages_fallback
mdefine_line|#define snd_malloc_isa_pages_fallback(size, dma_addr, res_size) snd_malloc_pci_pages_fallback(NULL, size, dma_addr, res_size)
DECL|macro|snd_free_isa_pages
mdefine_line|#define snd_free_isa_pages(size, ptr, dma_addr) snd_free_pci_pages(NULL, size, ptr, dma_addr)
macro_line|#else /* !CONFIG_PCI */
DECL|macro|snd_free_isa_pages
mdefine_line|#define snd_free_isa_pages(size, ptr, dma_addr) snd_free_pages(ptr, size)
macro_line|#endif /* CONFIG_PCI */
macro_line|#endif /* CONFIG_ISA */
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n; * Scatter-Gather PCI pages&n; */
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
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
)brace
suffix:semicolon
r_void
op_star
id|snd_malloc_sgbuf_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
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
id|snd_free_sgbuf_pages
c_func
(paren
r_struct
id|snd_dma_buffer
op_star
id|dmab
)paren
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
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/*&n; * wrappers&n; */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2, 4, 0)
macro_line|#ifdef CONFIG_PCI
macro_line|#if defined(__i386__) || defined(__ppc__) || defined(__x86_64__)
DECL|macro|HACK_PCI_ALLOC_CONSISTENT
mdefine_line|#define HACK_PCI_ALLOC_CONSISTENT
multiline_comment|/* a hack for 2.4/5 kernels for better allocation of large buffers */
r_void
op_star
id|snd_pci_hack_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
suffix:semicolon
macro_line|#endif /* arch */
macro_line|#endif /* CONFIG_PCI */
macro_line|#endif /* LINUX &gt;= 2.4.0 */
macro_line|#endif /* __SOUND_MEMALLOC_H */
eof
