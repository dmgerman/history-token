multiline_comment|/** &n; * &bslash;file drm_memory.h &n; * Memory management wrappers for DRM&n; *&n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/* &n; * Created: Thu Feb  4 14:00:34 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &quot;drmP.h&quot;
multiline_comment|/**&n; * Cut down version of drm_memory_debug.h, which used to be called&n; * drm_memory.h.  &n; */
macro_line|#if __OS_HAS_AGP
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#ifdef HAVE_PAGE_AGP
macro_line|#include &lt;asm/agp.h&gt;
macro_line|#else
macro_line|# ifdef __powerpc__
DECL|macro|PAGE_AGP
macro_line|#  define PAGE_AGP&t;__pgprot(_PAGE_KERNEL | _PAGE_NO_CACHE)
macro_line|# else
DECL|macro|PAGE_AGP
macro_line|#  define PAGE_AGP&t;PAGE_KERNEL
macro_line|# endif
macro_line|#endif
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * Find the drm_map that covers the range [offset, offset+size).&n; */
r_static
r_inline
id|drm_map_t
op_star
DECL|function|drm_lookup_map
id|drm_lookup_map
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|dev-&gt;maplist-&gt;head
)paren
(brace
id|r_list
op_assign
(paren
id|drm_map_list_t
op_star
)paren
id|list
suffix:semicolon
id|map
op_assign
id|r_list-&gt;map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;offset
op_le
id|offset
op_logical_and
(paren
id|offset
op_plus
id|size
)paren
op_le
(paren
id|map-&gt;offset
op_plus
id|map-&gt;size
)paren
)paren
r_return
id|map
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|agp_remap
id|agp_remap
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
r_int
op_star
id|phys_addr_map
comma
id|i
comma
id|num_pages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_struct
id|drm_agp_mem
op_star
id|agpmem
suffix:semicolon
r_struct
id|page
op_star
op_star
id|page_map
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
macro_line|#ifdef __alpha__
id|offset
op_sub_assign
id|dev-&gt;hose-&gt;mem_space-&gt;start
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|agpmem
op_assign
id|dev-&gt;agp-&gt;memory
suffix:semicolon
id|agpmem
suffix:semicolon
id|agpmem
op_assign
id|agpmem-&gt;next
)paren
r_if
c_cond
(paren
id|agpmem-&gt;bound
op_le
id|offset
op_logical_and
(paren
id|agpmem-&gt;bound
op_plus
(paren
id|agpmem-&gt;pages
op_lshift
id|PAGE_SHIFT
)paren
)paren
op_ge
(paren
id|offset
op_plus
id|size
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|agpmem
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * OK, we&squot;re mapping AGP space on a chipset/platform on which memory accesses by&n;&t; * the CPU do not get remapped by the GART.  We fix this by using the kernel&squot;s&n;&t; * page-table instead (that&squot;s probably faster anyhow...).&n;&t; */
multiline_comment|/* note: use vmalloc() because num_pages could be large... */
id|page_map
op_assign
id|vmalloc
c_func
(paren
id|num_pages
op_star
r_sizeof
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_map
)paren
r_return
l_int|NULL
suffix:semicolon
id|phys_addr_map
op_assign
id|agpmem-&gt;memory-&gt;memory
op_plus
(paren
id|offset
op_minus
id|agpmem-&gt;bound
)paren
op_div
id|PAGE_SIZE
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
id|num_pages
suffix:semicolon
op_increment
id|i
)paren
id|page_map
(braket
id|i
)braket
op_assign
id|pfn_to_page
c_func
(paren
id|phys_addr_map
(braket
id|i
)braket
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|addr
op_assign
id|vmap
c_func
(paren
id|page_map
comma
id|num_pages
comma
id|VM_IOREMAP
comma
id|PAGE_AGP
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|page_map
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|drm_follow_page
id|drm_follow_page
(paren
r_void
op_star
id|vaddr
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
id|pte_t
op_star
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
r_return
id|pte_pfn
c_func
(paren
op_star
id|ptep
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
)brace
macro_line|#else /* __OS_HAS_AGP */
DECL|function|drm_lookup_map
r_static
r_inline
id|drm_map_t
op_star
id|drm_lookup_map
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|agp_remap
r_static
r_inline
r_void
op_star
id|agp_remap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|drm_follow_page
r_static
r_inline
r_int
r_int
id|drm_follow_page
(paren
r_void
op_star
id|vaddr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|drm_ioremap
r_static
r_inline
r_void
op_star
id|drm_ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;agp
op_logical_and
id|dev-&gt;agp-&gt;cant_use_aperture
)paren
(brace
id|drm_map_t
op_star
id|map
op_assign
id|drm_lookup_map
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_logical_and
id|map-&gt;type
op_eq
id|_DRM_AGP
)paren
r_return
id|agp_remap
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
id|ioremap
c_func
(paren
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|drm_ioremap_nocache
r_static
r_inline
r_void
op_star
id|drm_ioremap_nocache
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;agp
op_logical_and
id|dev-&gt;agp-&gt;cant_use_aperture
)paren
(brace
id|drm_map_t
op_star
id|map
op_assign
id|drm_lookup_map
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_logical_and
id|map-&gt;type
op_eq
id|_DRM_AGP
)paren
r_return
id|agp_remap
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
id|ioremap_nocache
c_func
(paren
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|drm_ioremapfree
r_static
r_inline
r_void
id|drm_ioremapfree
c_func
(paren
r_void
op_star
id|pt
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * This is a bit ugly.  It would be much cleaner if the DRM API would use separate&n;&t; * routines for handling mappings in the AGP space.  Hopefully this can be done in&n;&t; * a future revision of the interface...&n;&t; */
r_if
c_cond
(paren
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;agp
op_logical_and
id|dev-&gt;agp-&gt;cant_use_aperture
op_logical_and
(paren
(paren
r_int
r_int
)paren
id|pt
op_ge
id|VMALLOC_START
op_logical_and
(paren
r_int
r_int
)paren
id|pt
OL
id|VMALLOC_END
)paren
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
id|offset
op_assign
id|drm_follow_page
c_func
(paren
id|pt
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|pt
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|map
op_assign
id|drm_lookup_map
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_logical_and
id|map-&gt;type
op_eq
id|_DRM_AGP
)paren
(brace
id|vunmap
c_func
(paren
id|pt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|iounmap
c_func
(paren
id|pt
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_MEMORY
macro_line|#include &quot;drm_memory_debug.h&quot;
macro_line|#else
multiline_comment|/** No-op. */
DECL|function|mem_init
r_void
id|DRM
c_func
(paren
id|mem_init
)paren
(paren
r_void
)paren
(brace
)brace
multiline_comment|/**&n; * Called when &quot;/proc/dri/%dev%/mem&quot; is read.&n; * &n; * &bslash;param buf output buffer.&n; * &bslash;param start start of output data.&n; * &bslash;param offset requested start offset.&n; * &bslash;param len requested number of bytes.&n; * &bslash;param eof whether there is no more data to return.&n; * &bslash;param data private data.&n; * &bslash;return number of written bytes.&n; *&n; * No-op. &n; */
DECL|function|mem_info
r_int
id|DRM
c_func
(paren
id|mem_info
)paren
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** Wrapper around kmalloc() */
DECL|function|calloc
r_void
op_star
id|DRM
c_func
(paren
id|calloc
)paren
(paren
r_int
id|nmemb
comma
r_int
id|size
comma
r_int
id|area
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
id|addr
op_assign
id|kmalloc
c_func
(paren
id|size
op_star
id|nmemb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ne
l_int|NULL
)paren
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
l_int|0
comma
id|size
op_star
id|nmemb
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/** Wrapper around kmalloc() and kfree() */
DECL|function|realloc
r_void
op_star
id|DRM
c_func
(paren
id|realloc
)paren
(paren
r_void
op_star
id|oldpt
comma
r_int
id|oldsize
comma
r_int
id|size
comma
r_int
id|area
)paren
(brace
r_void
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|oldpt
op_logical_and
id|oldsize
)paren
(brace
id|memcpy
c_func
(paren
id|pt
comma
id|oldpt
comma
id|oldsize
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|oldpt
)paren
suffix:semicolon
)brace
r_return
id|pt
suffix:semicolon
)brace
multiline_comment|/**&n; * Allocate pages.&n; *&n; * &bslash;param order size order.&n; * &bslash;param area memory area. (Not used.)&n; * &bslash;return page address on success, or zero on failure.&n; *&n; * Allocate and reserve free pages.&n; */
DECL|function|alloc_pages
r_int
r_int
id|DRM
c_func
(paren
id|alloc_pages
)paren
(paren
r_int
id|order
comma
r_int
id|area
)paren
(brace
r_int
r_int
id|address
suffix:semicolon
r_int
r_int
id|bytes
op_assign
id|PAGE_SIZE
op_lshift
id|order
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
id|address
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Zero */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|address
comma
l_int|0
comma
id|bytes
)paren
suffix:semicolon
multiline_comment|/* Reserve */
r_for
c_loop
(paren
id|addr
op_assign
id|address
comma
id|sz
op_assign
id|bytes
suffix:semicolon
id|sz
OG
l_int|0
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|sz
op_sub_assign
id|PAGE_SIZE
)paren
(brace
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
r_return
id|address
suffix:semicolon
)brace
multiline_comment|/**&n; * Free pages.&n; * &n; * &bslash;param address address of the pages to free.&n; * &bslash;param order size order.&n; * &bslash;param area memory area. (Not used.)&n; *&n; * Unreserve and free pages allocated by alloc_pages().&n; */
DECL|function|free_pages
r_void
id|DRM
c_func
(paren
id|free_pages
)paren
(paren
r_int
r_int
id|address
comma
r_int
id|order
comma
r_int
id|area
)paren
(brace
r_int
r_int
id|bytes
op_assign
id|PAGE_SIZE
op_lshift
id|order
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
r_return
suffix:semicolon
multiline_comment|/* Unreserve */
r_for
c_loop
(paren
id|addr
op_assign
id|address
comma
id|sz
op_assign
id|bytes
suffix:semicolon
id|sz
OG
l_int|0
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|sz
op_sub_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
id|free_pages
c_func
(paren
id|address
comma
id|order
)paren
suffix:semicolon
)brace
multiline_comment|/** Wrapper around drm_ioremap() */
DECL|function|ioremap
r_void
op_star
id|DRM
c_func
(paren
id|ioremap
)paren
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_return
id|drm_ioremap
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/** Wrapper around drm_ioremap_nocache() */
DECL|function|ioremap_nocache
r_void
op_star
id|DRM
c_func
(paren
id|ioremap_nocache
)paren
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_return
id|drm_ioremap_nocache
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/** Wrapper around drm_iounmap() */
DECL|function|ioremapfree
r_void
id|DRM
c_func
(paren
id|ioremapfree
)paren
(paren
r_void
op_star
id|pt
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_ioremapfree
c_func
(paren
id|pt
comma
id|size
comma
id|dev
)paren
suffix:semicolon
)brace
macro_line|#if __OS_HAS_AGP
multiline_comment|/** Wrapper around agp_allocate_memory() */
DECL|function|alloc_agp
id|DRM_AGP_MEM
op_star
id|DRM
c_func
(paren
id|alloc_agp
)paren
(paren
r_int
id|pages
comma
id|u32
id|type
)paren
(brace
r_return
id|DRM
c_func
(paren
id|agp_allocate_memory
)paren
(paren
id|pages
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/** Wrapper around agp_free_memory() */
DECL|function|free_agp
r_int
id|DRM
c_func
(paren
id|free_agp
)paren
(paren
id|DRM_AGP_MEM
op_star
id|handle
comma
r_int
id|pages
)paren
(brace
r_return
id|DRM
c_func
(paren
id|agp_free_memory
)paren
(paren
id|handle
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/** Wrapper around agp_bind_memory() */
DECL|function|bind_agp
r_int
id|DRM
c_func
(paren
id|bind_agp
)paren
(paren
id|DRM_AGP_MEM
op_star
id|handle
comma
r_int
r_int
id|start
)paren
(brace
r_return
id|DRM
c_func
(paren
id|agp_bind_memory
)paren
(paren
id|handle
comma
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/** Wrapper around agp_unbind_memory() */
DECL|function|unbind_agp
r_int
id|DRM
c_func
(paren
id|unbind_agp
)paren
(paren
id|DRM_AGP_MEM
op_star
id|handle
)paren
(brace
r_return
id|DRM
c_func
(paren
id|agp_unbind_memory
)paren
(paren
id|handle
)paren
suffix:semicolon
)brace
macro_line|#endif /* agp */
macro_line|#endif /* debug_memory */
eof
