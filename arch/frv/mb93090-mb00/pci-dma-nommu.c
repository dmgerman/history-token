multiline_comment|/* pci-dma-nommu.c: Dynamic DMA mapping support for the FRV&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Woodhouse (dwmw2@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if 1
DECL|macro|DMA_SRAM_START
mdefine_line|#define DMA_SRAM_START&t;dma_coherent_mem_start
DECL|macro|DMA_SRAM_END
mdefine_line|#define DMA_SRAM_END&t;dma_coherent_mem_end
macro_line|#else 
singleline_comment|// Use video RAM on Matrox
DECL|macro|DMA_SRAM_START
mdefine_line|#define DMA_SRAM_START&t;0xe8900000
DECL|macro|DMA_SRAM_END
mdefine_line|#define DMA_SRAM_END&t;0xe8a00000
macro_line|#endif
DECL|struct|dma_alloc_record
r_struct
id|dma_alloc_record
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|ofs
r_int
r_int
id|ofs
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|dma_alloc_lock
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|dma_alloc_list
)paren
suffix:semicolon
DECL|function|dma_alloc_coherent
r_void
op_star
id|dma_alloc_coherent
c_func
(paren
r_struct
id|device
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
comma
r_int
id|gfp
)paren
(brace
r_struct
id|dma_alloc_record
op_star
r_new
suffix:semicolon
r_struct
id|list_head
op_star
id|this
op_assign
op_amp
id|dma_alloc_list
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|start
op_assign
id|DMA_SRAM_START
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DMA_SRAM_START
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s called without any DMA area reserved!&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Round up to a reasonable alignment */
r_new
op_member_access_from_pointer
id|len
op_assign
(paren
id|size
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dma_alloc_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
(paren
id|this
comma
op_amp
id|dma_alloc_list
)paren
(brace
r_struct
id|dma_alloc_record
op_star
id|this_r
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|dma_alloc_record
comma
id|list
)paren
suffix:semicolon
id|end
op_assign
id|this_r-&gt;ofs
suffix:semicolon
r_if
c_cond
(paren
id|end
op_minus
id|start
op_ge
id|size
)paren
r_goto
id|gotone
suffix:semicolon
id|start
op_assign
id|this_r-&gt;ofs
op_plus
id|this_r-&gt;len
suffix:semicolon
)brace
multiline_comment|/* Reached end of list. */
id|end
op_assign
id|DMA_SRAM_END
suffix:semicolon
id|this
op_assign
op_amp
id|dma_alloc_list
suffix:semicolon
r_if
c_cond
(paren
id|end
op_minus
id|start
op_ge
id|size
)paren
(brace
id|gotone
suffix:colon
r_new
op_member_access_from_pointer
id|ofs
op_assign
id|start
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
id|this
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_alloc_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
id|start
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|start
suffix:semicolon
)brace
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_alloc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dma_free_coherent
r_void
id|dma_free_coherent
c_func
(paren
r_struct
id|device
op_star
id|hwdev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
r_struct
id|dma_alloc_record
op_star
id|rec
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dma_alloc_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|rec
comma
op_amp
id|dma_alloc_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|rec-&gt;ofs
op_eq
id|dma_handle
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|rec-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rec
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_alloc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_alloc_lock
comma
id|flags
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Map a single buffer of the indicated size for DMA in streaming mode.&n; * The 32-bit bus address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_dma_sync_single is performed.&n; */
DECL|function|dma_map_single
id|dma_addr_t
id|dma_map_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|frv_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|ptr
comma
(paren
r_int
r_int
)paren
id|ptr
op_plus
id|size
)paren
suffix:semicolon
r_return
id|virt_to_bus
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Map a set of buffers described by scatterlist in streaming&n; * mode for DMA.  This is the scather-gather version of the&n; * above pci_map_single interface.  Here the scatter gather list&n; * elements are each tagged with the appropriate dma address&n; * and length.  They are obtained via sg_dma_{address,length}(SG).&n; *&n; * NOTE: An implementation may be able to use a smaller number of&n; *       DMA address/length pairs than there are SG table elements.&n; *       (for example via virtual mapping capabilities)&n; *       The routine returns the number of addr/length pairs actually&n; *       used, at most nents.&n; *&n; * Device ownership issues as mentioned above for pci_map_single are&n; * the same here.&n; */
DECL|function|dma_map_sg
r_int
id|dma_map_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
)paren
id|frv_cache_wback_inv
c_func
(paren
id|sg_dma_address
c_func
(paren
op_amp
id|sg
(braket
id|i
)braket
)paren
comma
id|sg_dma_address
c_func
(paren
op_amp
id|sg
(braket
id|i
)braket
)paren
op_plus
id|sg_dma_len
c_func
(paren
op_amp
id|sg
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|nents
suffix:semicolon
)brace
eof
