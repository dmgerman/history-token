macro_line|#ifndef __LINUX_GFP_H
DECL|macro|__LINUX_GFP_H
mdefine_line|#define __LINUX_GFP_H
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/config.h&gt;
r_struct
id|vm_area_struct
suffix:semicolon
multiline_comment|/*&n; * GFP bitmasks..&n; */
multiline_comment|/* Zone modifiers in GFP_ZONEMASK (see linux/mmzone.h - low two bits) */
DECL|macro|__GFP_DMA
mdefine_line|#define __GFP_DMA&t;0x01
DECL|macro|__GFP_HIGHMEM
mdefine_line|#define __GFP_HIGHMEM&t;0x02
multiline_comment|/*&n; * Action modifiers - doesn&squot;t change the zoning&n; *&n; * __GFP_REPEAT: Try hard to allocate the memory, but the allocation attempt&n; * _might_ fail.  This depends upon the particular VM implementation.&n; *&n; * __GFP_NOFAIL: The VM implementation _must_ retry infinitely: the caller&n; * cannot handle allocation failures.&n; *&n; * __GFP_NORETRY: The VM implementation must not retry indefinitely.&n; */
DECL|macro|__GFP_WAIT
mdefine_line|#define __GFP_WAIT&t;0x10&t;/* Can wait and reschedule? */
DECL|macro|__GFP_HIGH
mdefine_line|#define __GFP_HIGH&t;0x20&t;/* Should access emergency pools? */
DECL|macro|__GFP_IO
mdefine_line|#define __GFP_IO&t;0x40&t;/* Can start physical IO? */
DECL|macro|__GFP_FS
mdefine_line|#define __GFP_FS&t;0x80&t;/* Can call down to low-level FS? */
DECL|macro|__GFP_COLD
mdefine_line|#define __GFP_COLD&t;0x100&t;/* Cache-cold page required */
DECL|macro|__GFP_NOWARN
mdefine_line|#define __GFP_NOWARN&t;0x200&t;/* Suppress page allocation failure warning */
DECL|macro|__GFP_REPEAT
mdefine_line|#define __GFP_REPEAT&t;0x400&t;/* Retry the allocation.  Might fail */
DECL|macro|__GFP_NOFAIL
mdefine_line|#define __GFP_NOFAIL&t;0x800&t;/* Retry for ever.  Cannot fail */
DECL|macro|__GFP_NORETRY
mdefine_line|#define __GFP_NORETRY&t;0x1000&t;/* Do not retry.  Might fail */
DECL|macro|__GFP_NO_GROW
mdefine_line|#define __GFP_NO_GROW&t;0x2000&t;/* Slab internal usage */
DECL|macro|__GFP_COMP
mdefine_line|#define __GFP_COMP&t;0x4000&t;/* Add compound page metadata */
DECL|macro|__GFP_ZERO
mdefine_line|#define __GFP_ZERO&t;0x8000&t;/* Return zeroed page on success */
DECL|macro|__GFP_BITS_SHIFT
mdefine_line|#define __GFP_BITS_SHIFT 16&t;/* Room for 16 __GFP_FOO bits */
DECL|macro|__GFP_BITS_MASK
mdefine_line|#define __GFP_BITS_MASK ((1 &lt;&lt; __GFP_BITS_SHIFT) - 1)
multiline_comment|/* if you forget to add the bitmask here kernel will crash, period */
DECL|macro|GFP_LEVEL_MASK
mdefine_line|#define GFP_LEVEL_MASK (__GFP_WAIT|__GFP_HIGH|__GFP_IO|__GFP_FS| &bslash;&n;&t;&t;&t;__GFP_COLD|__GFP_NOWARN|__GFP_REPEAT| &bslash;&n;&t;&t;&t;__GFP_NOFAIL|__GFP_NORETRY|__GFP_NO_GROW|__GFP_COMP)
DECL|macro|GFP_ATOMIC
mdefine_line|#define GFP_ATOMIC&t;(__GFP_HIGH)
DECL|macro|GFP_NOIO
mdefine_line|#define GFP_NOIO&t;(__GFP_WAIT)
DECL|macro|GFP_NOFS
mdefine_line|#define GFP_NOFS&t;(__GFP_WAIT | __GFP_IO)
DECL|macro|GFP_KERNEL
mdefine_line|#define GFP_KERNEL&t;(__GFP_WAIT | __GFP_IO | __GFP_FS)
DECL|macro|GFP_USER
mdefine_line|#define GFP_USER&t;(__GFP_WAIT | __GFP_IO | __GFP_FS)
DECL|macro|GFP_HIGHUSER
mdefine_line|#define GFP_HIGHUSER&t;(__GFP_WAIT | __GFP_IO | __GFP_FS | __GFP_HIGHMEM)
DECL|macro|GFP_HIGHZERO
mdefine_line|#define GFP_HIGHZERO&t;(__GFP_WAIT | __GFP_IO | __GFP_FS | __GFP_HIGHMEM | __GFP_ZERO)
multiline_comment|/* Flag - indicates that the buffer will be suitable for DMA.  Ignored on some&n;   platforms, used as appropriate on others */
DECL|macro|GFP_DMA
mdefine_line|#define GFP_DMA&t;&t;__GFP_DMA
multiline_comment|/*&n; * There is only one page-allocator function, and two main namespaces to&n; * it. The alloc_page*() variants return &squot;struct page *&squot; and as such&n; * can allocate highmem pages, the *get*page*() variants return&n; * virtual kernel addresses to the allocated page(s).&n; */
multiline_comment|/*&n; * We get the zone list from the current node and the gfp_mask.&n; * This zone list contains a maximum of MAXNODES*MAX_NR_ZONES zones.&n; *&n; * For the normal case of non-DISCONTIGMEM systems the NODE_DATA() gets&n; * optimized to &amp;contig_page_data at compile-time.&n; */
macro_line|#ifndef HAVE_ARCH_FREE_PAGE
DECL|function|arch_free_page
r_static
r_inline
r_void
id|arch_free_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|order
)paren
(brace
)brace
macro_line|#endif
r_extern
r_struct
id|page
op_star
id|FASTCALL
c_func
(paren
id|__alloc_pages
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|zonelist
op_star
)paren
)paren
suffix:semicolon
DECL|function|alloc_pages_node
r_static
r_inline
r_struct
id|page
op_star
id|alloc_pages_node
c_func
(paren
r_int
id|nid
comma
r_int
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|order
op_ge
id|MAX_ORDER
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|__alloc_pages
c_func
(paren
id|gfp_mask
comma
id|order
comma
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_zonelists
op_plus
(paren
id|gfp_mask
op_amp
id|GFP_ZONEMASK
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NUMA
r_extern
r_struct
id|page
op_star
id|alloc_pages_current
c_func
(paren
r_int
id|gfp_mask
comma
r_int
id|order
)paren
suffix:semicolon
r_static
r_inline
r_struct
id|page
op_star
DECL|function|alloc_pages
id|alloc_pages
c_func
(paren
r_int
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|order
op_ge
id|MAX_ORDER
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|alloc_pages_current
c_func
(paren
id|gfp_mask
comma
id|order
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|page
op_star
id|alloc_page_vma
c_func
(paren
r_int
id|gfp_mask
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#else
DECL|macro|alloc_pages
mdefine_line|#define alloc_pages(gfp_mask, order) &bslash;&n;&t;&t;alloc_pages_node(numa_node_id(), gfp_mask, order)
DECL|macro|alloc_page_vma
mdefine_line|#define alloc_page_vma(gfp_mask, vma, addr) alloc_pages(gfp_mask, 0)
macro_line|#endif
DECL|macro|alloc_page
mdefine_line|#define alloc_page(gfp_mask) alloc_pages(gfp_mask, 0)
r_extern
r_int
r_int
id|FASTCALL
c_func
(paren
id|__get_free_pages
c_func
(paren
r_int
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
)paren
suffix:semicolon
r_extern
r_int
r_int
id|FASTCALL
c_func
(paren
id|get_zeroed_page
c_func
(paren
r_int
r_int
id|gfp_mask
)paren
)paren
suffix:semicolon
DECL|macro|__get_free_page
mdefine_line|#define __get_free_page(gfp_mask) &bslash;&n;&t;&t;__get_free_pages((gfp_mask),0)
DECL|macro|__get_dma_pages
mdefine_line|#define __get_dma_pages(gfp_mask, order) &bslash;&n;&t;&t;__get_free_pages((gfp_mask) | GFP_DMA,(order))
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__free_pages
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|order
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|free_pages
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|order
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|free_hot_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|free_cold_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
)paren
suffix:semicolon
DECL|macro|__free_page
mdefine_line|#define __free_page(page) __free_pages((page), 0)
DECL|macro|free_page
mdefine_line|#define free_page(addr) free_pages((addr),0)
r_void
id|page_alloc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_GFP_H */
eof
