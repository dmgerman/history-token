macro_line|#ifndef _LINUX_HIGHMEM_H
DECL|macro|_LINUX_HIGHMEM_H
mdefine_line|#define _LINUX_HIGHMEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#ifdef CONFIG_HIGHMEM
r_extern
r_struct
id|page
op_star
id|highmem_start_page
suffix:semicolon
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
r_extern
r_void
id|create_bounce
c_func
(paren
r_int
r_int
id|pfn
comma
r_int
id|gfp
comma
r_struct
id|bio
op_star
op_star
id|bio_orig
)paren
suffix:semicolon
r_extern
r_void
id|check_highmem_ptes
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|bh_kmap
r_static
r_inline
r_char
op_star
id|bh_kmap
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|kmap
c_func
(paren
id|bh-&gt;b_page
)paren
op_plus
id|bh_offset
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|bh_kunmap
r_static
r_inline
r_void
id|bh_kunmap
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|kunmap
c_func
(paren
id|bh-&gt;b_page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remember to add offset! and never ever reenable interrupts between a&n; * bio_kmap_irq and bio_kunmap_irq!!&n; */
DECL|function|bio_kmap_irq
r_static
r_inline
r_char
op_star
id|bio_kmap_irq
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|__save_flags
c_func
(paren
op_star
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * could be low&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|bio_page
c_func
(paren
id|bio
)paren
)paren
)paren
r_return
id|bio_data
c_func
(paren
id|bio
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * it&squot;s a highmem page&n;&t; */
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|kmap_atomic
c_func
(paren
id|bio_page
c_func
(paren
id|bio
)paren
comma
id|KM_BIO_IRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|addr
op_plus
id|bio_offset
c_func
(paren
id|bio
)paren
suffix:semicolon
)brace
DECL|function|bio_kunmap_irq
r_static
r_inline
r_void
id|bio_kunmap_irq
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_int
r_int
id|ptr
op_assign
(paren
r_int
r_int
)paren
id|buffer
op_amp
id|PAGE_MASK
suffix:semicolon
id|kunmap_atomic
c_func
(paren
(paren
r_void
op_star
)paren
id|ptr
comma
id|KM_BIO_IRQ
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
op_star
id|flags
)paren
suffix:semicolon
)brace
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
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|macro|kunmap
mdefine_line|#define kunmap(page) do { } while (0)
DECL|macro|kmap_atomic
mdefine_line|#define kmap_atomic(page,idx)&t;&t;kmap(page)
DECL|macro|kunmap_atomic
mdefine_line|#define kunmap_atomic(page,idx)&t;&t;kunmap(page)
DECL|macro|bh_kmap
mdefine_line|#define bh_kmap(bh)&t;((bh)-&gt;b_data)
DECL|macro|bh_kunmap
mdefine_line|#define bh_kunmap(bh)&t;do { } while (0)
DECL|macro|bio_kmap_irq
mdefine_line|#define bio_kmap_irq(bio, flags)&t;(bio_data(bio))
DECL|macro|bio_kunmap_irq
mdefine_line|#define bio_kunmap_irq(buf, flags)&t;do { *(flags) = 0; } while (0)
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
)brace
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
r_if
c_cond
(paren
id|offset
op_plus
id|size
OG
id|PAGE_SIZE
)paren
id|BUG
c_func
(paren
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
id|flush_page_to_ram
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
