macro_line|#ifndef _LINUX_HIGHMEM_H
DECL|macro|_LINUX_HIGHMEM_H
mdefine_line|#define _LINUX_HIGHMEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#ifdef CONFIG_HIGHMEM
macro_line|#include &lt;asm/highmem.h&gt;
multiline_comment|/* declarations for linux/mm/highmem.c */
r_int
r_int
id|nr_free_highpages
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* CONFIG_HIGHMEM */
DECL|function|nr_free_highpages
r_static
r_inline
r_int
r_int
id|nr_free_highpages
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kmap
r_static
r_inline
r_void
op_star
id|kmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|macro|kunmap
mdefine_line|#define kunmap(page) do { (void) (page); } while (0)
DECL|macro|kmap_atomic
mdefine_line|#define kmap_atomic(page, idx)&t;&t;page_address(page)
DECL|macro|kunmap_atomic
mdefine_line|#define kunmap_atomic(addr, idx)&t;do { } while (0)
DECL|macro|kmap_atomic_to_page
mdefine_line|#define kmap_atomic_to_page(ptr)&t;virt_to_page(ptr)
macro_line|#endif /* CONFIG_HIGHMEM */
multiline_comment|/* when CONFIG_HIGHMEM is not set these will be plain clear/copy_page */
DECL|function|clear_user_highpage
r_static
r_inline
r_void
id|clear_user_highpage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|vaddr
)paren
(brace
r_void
op_star
id|addr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|clear_user_page
c_func
(paren
id|addr
comma
id|vaddr
comma
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|addr
comma
id|KM_USER0
)paren
suffix:semicolon
multiline_comment|/* Make sure this page is cleared on other CPU&squot;s too before using it */
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
r_static
r_inline
r_struct
id|page
op_star
DECL|function|alloc_zeroed_user_highpage
id|alloc_zeroed_user_highpage
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|alloc_page_vma
c_func
(paren
id|GFP_HIGHUSER
comma
id|vma
comma
id|vaddr
)paren
suffix:semicolon
id|clear_user_highpage
c_func
(paren
id|page
comma
id|vaddr
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
macro_line|#endif
DECL|function|clear_highpage
r_static
r_inline
r_void
id|clear_highpage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_void
op_star
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|clear_page
c_func
(paren
id|kaddr
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Same but also flushes aliased cache contents to RAM.&n; */
DECL|function|memclear_highpage_flush
r_static
r_inline
r_void
id|memclear_highpage_flush
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|kaddr
suffix:semicolon
id|BUG_ON
c_func
(paren
id|offset
op_plus
id|size
OG
id|PAGE_SIZE
)paren
suffix:semicolon
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|kaddr
op_plus
id|offset
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
)brace
DECL|function|copy_user_highpage
r_static
r_inline
r_void
id|copy_user_highpage
c_func
(paren
r_struct
id|page
op_star
id|to
comma
r_struct
id|page
op_star
id|from
comma
r_int
r_int
id|vaddr
)paren
(brace
r_char
op_star
id|vfrom
comma
op_star
id|vto
suffix:semicolon
id|vfrom
op_assign
id|kmap_atomic
c_func
(paren
id|from
comma
id|KM_USER0
)paren
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
id|to
comma
id|KM_USER1
)paren
suffix:semicolon
id|copy_user_page
c_func
(paren
id|vto
comma
id|vfrom
comma
id|vaddr
comma
id|to
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vfrom
comma
id|KM_USER0
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vto
comma
id|KM_USER1
)paren
suffix:semicolon
multiline_comment|/* Make sure this page is cleared on other CPU&squot;s too before using it */
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|copy_highpage
r_static
r_inline
r_void
id|copy_highpage
c_func
(paren
r_struct
id|page
op_star
id|to
comma
r_struct
id|page
op_star
id|from
)paren
(brace
r_char
op_star
id|vfrom
comma
op_star
id|vto
suffix:semicolon
id|vfrom
op_assign
id|kmap_atomic
c_func
(paren
id|from
comma
id|KM_USER0
)paren
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
id|to
comma
id|KM_USER1
)paren
suffix:semicolon
id|copy_page
c_func
(paren
id|vto
comma
id|vfrom
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vfrom
comma
id|KM_USER0
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vto
comma
id|KM_USER1
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_HIGHMEM_H */
eof
