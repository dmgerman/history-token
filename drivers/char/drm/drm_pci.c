multiline_comment|/* drm_pci.h -- PCI DMA memory management wrappers for DRM -*- linux-c -*- */
multiline_comment|/**&n; * &bslash;file drm_pci.c&n; * &bslash;brief Functions and ioctls to manage PCI memory&n; *&n; * &bslash;warning These interfaces aren&squot;t stable yet.&n; *&n; * &bslash;todo Implement the remaining ioctl&squot;s for the PCI pools.&n; * &bslash;todo The wrappers here are so thin that they would be better off inlined..&n; *&n; * &bslash;author Jose Fonseca &lt;jrfonseca@tungstengraphics.com&gt;&n; * &bslash;author Leif Delgass &lt;ldelgass@retinalburn.net&gt;&n; */
multiline_comment|/*&n; * Copyright 2003 Jos&#xfffd;Fonseca.&n; * Copyright 2003 Leif Delgass.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE&n; * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION&n; * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;drmP.h&quot;
multiline_comment|/**********************************************************************/
multiline_comment|/** &bslash;name PCI memory */
multiline_comment|/*@{*/
multiline_comment|/**&n; * &bslash;brief Allocate a PCI consistent memory block, for DMA.&n; */
DECL|function|drm_pci_alloc
r_void
op_star
id|drm_pci_alloc
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|size
comma
r_int
id|align
comma
id|dma_addr_t
id|maxaddr
comma
id|dma_addr_t
op_star
id|busaddr
)paren
(brace
r_void
op_star
id|address
suffix:semicolon
macro_line|#if DRM_DEBUG_MEMORY
r_int
id|area
op_assign
id|DRM_MEM_DMA
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drm_ram_used
op_rshift
id|PAGE_SHIFT
)paren
OG
(paren
id|DRM_RAM_PERCENT
op_star
id|drm_ram_available
)paren
op_div
l_int|100
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* pci_alloc_consistent only guarantees alignment to the smallest&n;&t; * PAGE_SIZE order which is greater than or equal to the requested size.&n;&t; * Return NULL here for now to make sure nobody tries for larger alignment&n;&t; */
r_if
c_cond
(paren
id|align
OG
id|size
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pci_set_dma_mask
c_func
(paren
id|dev-&gt;pdev
comma
id|maxaddr
)paren
op_ne
l_int|0
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Setting pci dma mask failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|address
op_assign
id|pci_alloc_consistent
c_func
(paren
id|dev-&gt;pdev
comma
id|size
comma
id|busaddr
)paren
suffix:semicolon
macro_line|#if DRM_DEBUG_MEMORY
r_if
c_cond
(paren
id|address
op_eq
l_int|NULL
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
op_increment
id|drm_mem_stats
(braket
id|area
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
op_increment
id|drm_mem_stats
(braket
id|area
)braket
dot
id|succeed_count
suffix:semicolon
id|drm_mem_stats
(braket
id|area
)braket
dot
id|bytes_allocated
op_add_assign
id|size
suffix:semicolon
id|drm_ram_used
op_add_assign
id|size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|address
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
id|memset
c_func
(paren
id|address
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|address
suffix:semicolon
)brace
DECL|variable|drm_pci_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|drm_pci_alloc
)paren
suffix:semicolon
multiline_comment|/**&n; * &bslash;brief Free a PCI consistent memory block.&n; */
r_void
DECL|function|drm_pci_free
id|drm_pci_free
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|busaddr
)paren
(brace
macro_line|#if DRM_DEBUG_MEMORY
r_int
id|area
op_assign
id|DRM_MEM_DMA
suffix:semicolon
r_int
id|alloc_count
suffix:semicolon
r_int
id|free_count
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|vaddr
)paren
(brace
macro_line|#if DRM_DEBUG_MEMORY
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Attempt to free address 0&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|pci_free_consistent
c_func
(paren
id|dev-&gt;pdev
comma
id|size
comma
id|vaddr
comma
id|busaddr
)paren
suffix:semicolon
)brace
macro_line|#if DRM_DEBUG_MEMORY
id|spin_lock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
id|free_count
op_assign
op_increment
id|drm_mem_stats
(braket
id|area
)braket
dot
id|free_count
suffix:semicolon
id|alloc_count
op_assign
id|drm_mem_stats
(braket
id|area
)braket
dot
id|succeed_count
suffix:semicolon
id|drm_mem_stats
(braket
id|area
)braket
dot
id|bytes_freed
op_add_assign
id|size
suffix:semicolon
id|drm_ram_used
op_sub_assign
id|size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|drm_mem_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
OG
id|alloc_count
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Excess frees: %d frees, %d allocs&bslash;n&quot;
comma
id|free_count
comma
id|alloc_count
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|variable|drm_pci_free
id|EXPORT_SYMBOL
c_func
(paren
id|drm_pci_free
)paren
suffix:semicolon
multiline_comment|/*@}*/
eof
