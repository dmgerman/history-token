macro_line|#ifndef __LINUX_GFP_H
DECL|macro|__LINUX_GFP_H
mdefine_line|#define __LINUX_GFP_H
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * GFP bitmasks..&n; */
multiline_comment|/* Zone modifiers in GFP_ZONEMASK (see linux/mmzone.h - low four bits) */
DECL|macro|__GFP_DMA
mdefine_line|#define __GFP_DMA&t;0x01
DECL|macro|__GFP_HIGHMEM
mdefine_line|#define __GFP_HIGHMEM&t;0x02
multiline_comment|/* Action modifiers - doesn&squot;t change the zoning */
DECL|macro|__GFP_WAIT
mdefine_line|#define __GFP_WAIT&t;0x10&t;/* Can wait and reschedule? */
DECL|macro|__GFP_HIGH
mdefine_line|#define __GFP_HIGH&t;0x20&t;/* Should access emergency pools? */
DECL|macro|__GFP_IO
mdefine_line|#define __GFP_IO&t;0x40&t;/* Can start low memory physical IO? */
DECL|macro|__GFP_HIGHIO
mdefine_line|#define __GFP_HIGHIO&t;0x80&t;/* Can start high mem physical IO? */
DECL|macro|__GFP_FS
mdefine_line|#define __GFP_FS&t;0x100&t;/* Can call down to low-level FS? */
DECL|macro|GFP_NOHIGHIO
mdefine_line|#define GFP_NOHIGHIO&t;(__GFP_HIGH | __GFP_WAIT | __GFP_IO)
DECL|macro|GFP_NOIO
mdefine_line|#define GFP_NOIO&t;(__GFP_HIGH | __GFP_WAIT)
DECL|macro|GFP_NOFS
mdefine_line|#define GFP_NOFS&t;(__GFP_HIGH | __GFP_WAIT | __GFP_IO | __GFP_HIGHIO)
DECL|macro|GFP_ATOMIC
mdefine_line|#define GFP_ATOMIC&t;(__GFP_HIGH)
DECL|macro|GFP_USER
mdefine_line|#define GFP_USER&t;(             __GFP_WAIT | __GFP_IO | __GFP_HIGHIO | __GFP_FS)
DECL|macro|GFP_HIGHUSER
mdefine_line|#define GFP_HIGHUSER&t;(             __GFP_WAIT | __GFP_IO | __GFP_HIGHIO | __GFP_FS | __GFP_HIGHMEM)
DECL|macro|GFP_KERNEL
mdefine_line|#define GFP_KERNEL&t;(__GFP_HIGH | __GFP_WAIT | __GFP_IO | __GFP_HIGHIO | __GFP_FS)
DECL|macro|GFP_NFS
mdefine_line|#define GFP_NFS&t;&t;(__GFP_HIGH | __GFP_WAIT | __GFP_IO | __GFP_HIGHIO | __GFP_FS)
DECL|macro|GFP_KSWAPD
mdefine_line|#define GFP_KSWAPD&t;(             __GFP_WAIT | __GFP_IO | __GFP_HIGHIO | __GFP_FS)
multiline_comment|/* Flag - indicates that the buffer will be suitable for DMA.  Ignored on some&n;   platforms, used as appropriate on others */
DECL|macro|GFP_DMA
mdefine_line|#define GFP_DMA&t;&t;__GFP_DMA
multiline_comment|/*&n; * There is only one page-allocator function, and two main namespaces to&n; * it. The alloc_page*() variants return &squot;struct page *&squot; and as such&n; * can allocate highmem pages, the *get*page*() variants return&n; * virtual kernel addresses to the allocated page(s).&n; */
r_extern
r_struct
id|page
op_star
id|FASTCALL
c_func
(paren
id|_alloc_pages
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
id|gfp_mask
comma
r_int
r_int
id|order
comma
id|zonelist_t
op_star
id|zonelist
)paren
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
DECL|function|alloc_pages
r_static
r_inline
r_struct
id|page
op_star
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
multiline_comment|/*&n;&t; * Gets optimized away by the compiler.&n;&t; */
r_if
c_cond
(paren
id|order
op_ge
id|MAX_ORDER
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|_alloc_pages
c_func
(paren
id|gfp_mask
comma
id|order
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; * The old interface name will be removed in 2.5:&n; */
DECL|macro|get_free_page
mdefine_line|#define get_free_page get_zeroed_page
multiline_comment|/*&n; * There is only one &squot;core&squot; page-freeing function.&n; */
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
DECL|macro|__free_page
mdefine_line|#define __free_page(page) __free_pages((page), 0)
DECL|macro|free_page
mdefine_line|#define free_page(addr) free_pages((addr),0)
macro_line|#endif /* __LINUX_GFP_H */
eof
