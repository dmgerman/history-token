multiline_comment|/*&n; * DMA region bookkeeping routines&n; *&n; * Copyright (C) 2002 Maas Digital LLC&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#ifndef IEEE1394_DMA_H
DECL|macro|IEEE1394_DMA_H
mdefine_line|#define IEEE1394_DMA_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* struct dma_prog_region&n;   &n;   a small, physically-contiguous DMA buffer with random-access,&n;   synchronous usage characteristics&n;*/
DECL|struct|dma_prog_region
r_struct
id|dma_prog_region
(brace
DECL|member|kvirt
r_int
r_char
op_star
id|kvirt
suffix:semicolon
multiline_comment|/* kernel virtual address */
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* PCI device */
DECL|member|n_pages
r_int
r_int
id|n_pages
suffix:semicolon
multiline_comment|/* # of kernel pages */
DECL|member|bus_addr
id|dma_addr_t
id|bus_addr
suffix:semicolon
multiline_comment|/* base bus address */
)brace
suffix:semicolon
multiline_comment|/* clear out all fields but do not allocate any memory */
r_void
id|dma_prog_region_init
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
)paren
suffix:semicolon
r_int
id|dma_prog_region_alloc
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
comma
r_int
r_int
id|n_bytes
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|dma_prog_region_free
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
)paren
suffix:semicolon
DECL|function|dma_prog_region_offset_to_bus
r_static
r_inline
id|dma_addr_t
id|dma_prog_region_offset_to_bus
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
comma
r_int
r_int
id|offset
)paren
(brace
r_return
id|prog-&gt;bus_addr
op_plus
id|offset
suffix:semicolon
)brace
multiline_comment|/* struct dma_region&n;   &n;   a large, non-physically-contiguous DMA buffer with streaming,&n;   asynchronous usage characteristics&n;*/
DECL|struct|dma_region
r_struct
id|dma_region
(brace
DECL|member|kvirt
r_int
r_char
op_star
id|kvirt
suffix:semicolon
multiline_comment|/* kernel virtual address */
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* PCI device */
DECL|member|n_pages
r_int
r_int
id|n_pages
suffix:semicolon
multiline_comment|/* # of kernel pages */
DECL|member|n_dma_pages
r_int
r_int
id|n_dma_pages
suffix:semicolon
multiline_comment|/* # of IOMMU pages */
DECL|member|sglist
r_struct
id|scatterlist
op_star
id|sglist
suffix:semicolon
multiline_comment|/* IOMMU mapping */
DECL|member|direction
r_int
id|direction
suffix:semicolon
multiline_comment|/* PCI_DMA_TODEVICE, etc */
)brace
suffix:semicolon
multiline_comment|/* clear out all fields but do not allocate anything */
r_void
id|dma_region_init
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* allocate the buffer and map it to the IOMMU */
r_int
id|dma_region_alloc
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|n_bytes
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|direction
)paren
suffix:semicolon
multiline_comment|/* unmap and free the buffer */
r_void
id|dma_region_free
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* sync the IO bus&squot; view of the buffer with the CPU&squot;s view */
r_void
id|dma_region_sync
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* map the buffer into a user space process */
r_int
id|dma_region_mmap
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
multiline_comment|/* macro to index into a DMA region (or dma_prog_region) */
DECL|macro|dma_region_i
mdefine_line|#define dma_region_i(_dma, _type, _index) ( ((_type*) ((_dma)-&gt;kvirt)) + (_index) )
multiline_comment|/* return the DMA bus address of the byte with the given offset&n;   relative to the beginning of the dma_region */
id|dma_addr_t
id|dma_region_offset_to_bus
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/* round up a number of bytes to be a multiple of the PAGE_SIZE */
DECL|function|round_up_to_page
r_static
r_inline
r_int
r_int
id|round_up_to_page
c_func
(paren
r_int
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_mod
id|PAGE_SIZE
)paren
id|len
op_add_assign
id|PAGE_SIZE
op_minus
(paren
id|len
op_mod
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif /* IEEE1394_DMA_H */
eof
