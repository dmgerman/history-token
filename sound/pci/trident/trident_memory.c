multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *  Copyright (c) by Scott McNab &lt;sdm@fractalgraphics.com.au&gt;&n; *&n; *  Trident 4DWave-NX memory page allocation (TLB area)&n; *  Trident chip can handle only 16MByte of the memory at the same time.&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/trident.h&gt;
multiline_comment|/* page arguments of these two macros are Trident page (4096 bytes), not like&n; * aligned pages in others&n; */
DECL|macro|__set_tlb_bus
mdefine_line|#define __set_tlb_bus(trident,page,ptr,addr) &bslash;&n;&t;do { (trident)-&gt;tlb.entries[page] = cpu_to_le32((addr) &amp; ~(SNDRV_TRIDENT_PAGE_SIZE-1)); &bslash;&n;&t;     (trident)-&gt;tlb.shadow_entries[page] = (ptr); } while (0)
DECL|macro|__tlb_to_ptr
mdefine_line|#define __tlb_to_ptr(trident,page) &bslash;&n;&t;(void*)((trident)-&gt;tlb.shadow_entries[page])
DECL|macro|__tlb_to_addr
mdefine_line|#define __tlb_to_addr(trident,page) &bslash;&n;&t;(dma_addr_t)le32_to_cpu((trident-&gt;tlb.entries[page]) &amp; ~(SNDRV_TRIDENT_PAGE_SIZE - 1))
macro_line|#if PAGE_SIZE == 4096
multiline_comment|/* page size == SNDRV_TRIDENT_PAGE_SIZE */
DECL|macro|ALIGN_PAGE_SIZE
mdefine_line|#define ALIGN_PAGE_SIZE&t;&t;PAGE_SIZE&t;/* minimum page size for allocation */
DECL|macro|MAX_ALIGN_PAGES
mdefine_line|#define MAX_ALIGN_PAGES&t;&t;SNDRV_TRIDENT_MAX_PAGES&t;/* maxmium aligned pages */
multiline_comment|/* fill TLB entrie(s) corresponding to page with ptr */
DECL|macro|set_tlb_bus
mdefine_line|#define set_tlb_bus(trident,page,ptr,addr) __set_tlb_bus(trident,page,ptr,addr)
multiline_comment|/* fill TLB entrie(s) corresponding to page with silence pointer */
DECL|macro|set_silent_tlb
mdefine_line|#define set_silent_tlb(trident,page)&t;__set_tlb_bus(trident, page, (unsigned long)trident-&gt;tlb.silent_page, trident-&gt;tlb.silent_page_dmaaddr)
multiline_comment|/* get aligned page from offset address */
DECL|macro|get_aligned_page
mdefine_line|#define get_aligned_page(offset)&t;((offset) &gt;&gt; 12)
multiline_comment|/* get offset address from aligned page */
DECL|macro|aligned_page_offset
mdefine_line|#define aligned_page_offset(page)&t;((page) &lt;&lt; 12)
multiline_comment|/* get buffer address from aligned page */
DECL|macro|page_to_ptr
mdefine_line|#define page_to_ptr(trident,page)&t;__tlb_to_ptr(trident, page)
multiline_comment|/* get PCI physical address from aligned page */
DECL|macro|page_to_addr
mdefine_line|#define page_to_addr(trident,page)&t;__tlb_to_addr(trident, page)
macro_line|#elif PAGE_SIZE == 8192
multiline_comment|/* page size == SNDRV_TRIDENT_PAGE_SIZE x 2*/
DECL|macro|ALIGN_PAGE_SIZE
mdefine_line|#define ALIGN_PAGE_SIZE&t;&t;PAGE_SIZE
DECL|macro|MAX_ALIGN_PAGES
mdefine_line|#define MAX_ALIGN_PAGES&t;&t;(SNDRV_TRIDENT_MAX_PAGES / 2)
DECL|macro|get_aligned_page
mdefine_line|#define get_aligned_page(offset)&t;((offset) &gt;&gt; 13)
DECL|macro|aligned_page_offset
mdefine_line|#define aligned_page_offset(page)&t;((page) &lt;&lt; 13)
DECL|macro|page_to_ptr
mdefine_line|#define page_to_ptr(trident,page)&t;__tlb_to_ptr(trident, (page) &lt;&lt; 1)
DECL|macro|page_to_addr
mdefine_line|#define page_to_addr(trident,page)&t;__tlb_to_addr(trident, (page) &lt;&lt; 1)
multiline_comment|/* fill TLB entries -- we need to fill two entries */
DECL|function|set_tlb_bus
r_static
r_inline
r_void
id|set_tlb_bus
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|page
comma
r_int
r_int
id|ptr
comma
id|dma_addr_t
id|addr
)paren
(brace
id|page
op_lshift_assign
l_int|1
suffix:semicolon
id|__set_tlb_bus
c_func
(paren
id|trident
comma
id|page
comma
id|ptr
comma
id|addr
)paren
suffix:semicolon
id|__set_tlb_bus
c_func
(paren
id|trident
comma
id|page
op_plus
l_int|1
comma
id|ptr
op_plus
id|SNDRV_TRIDENT_PAGE_SIZE
comma
id|addr
op_plus
id|SNDRV_TRIDENT_PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|set_silent_tlb
r_static
r_inline
r_void
id|set_silent_tlb
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|page
)paren
(brace
id|page
op_lshift_assign
l_int|1
suffix:semicolon
id|__set_tlb_bus
c_func
(paren
id|trident
comma
id|page
comma
(paren
r_int
r_int
)paren
id|trident-&gt;tlb.silent_page
comma
id|trident-&gt;tlb.silent_page_dmaaddr
)paren
suffix:semicolon
id|__set_tlb_bus
c_func
(paren
id|trident
comma
id|page
op_plus
l_int|1
comma
(paren
r_int
r_int
)paren
id|trident-&gt;tlb.silent_page
comma
id|trident-&gt;tlb.silent_page_dmaaddr
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* arbitrary size */
DECL|macro|UNIT_PAGES
mdefine_line|#define UNIT_PAGES&t;&t;(PAGE_SIZE / SNDRV_TRIDENT_PAGE_SIZE)
DECL|macro|ALIGN_PAGE_SIZE
mdefine_line|#define ALIGN_PAGE_SIZE&t;&t;(SNDRV_TRIDENT_PAGE_SIZE * UNIT_PAGES)
DECL|macro|MAX_ALIGN_PAGES
mdefine_line|#define MAX_ALIGN_PAGES&t;&t;(SNDRV_TRIDENT_MAX_PAGES / UNIT_PAGES)
multiline_comment|/* Note: if alignment doesn&squot;t match to the maximum size, the last few blocks&n; * become unusable.  To use such blocks, you&squot;ll need to check the validity&n; * of accessing page in set_tlb_bus and set_silent_tlb.  search_empty()&n; * should also check it, too.&n; */
DECL|macro|get_aligned_page
mdefine_line|#define get_aligned_page(offset)&t;((offset) / ALIGN_PAGE_SIZE)
DECL|macro|aligned_page_offset
mdefine_line|#define aligned_page_offset(page)&t;((page) * ALIGN_PAGE_SIZE)
DECL|macro|page_to_ptr
mdefine_line|#define page_to_ptr(trident,page)&t;__tlb_to_ptr(trident, (page) * UNIT_PAGES)
DECL|macro|page_to_addr
mdefine_line|#define page_to_addr(trident,page)&t;__tlb_to_addr(trident, (page) * UNIT_PAGES)
multiline_comment|/* fill TLB entries -- UNIT_PAGES entries must be filled */
DECL|function|set_tlb_bus
r_static
r_inline
r_void
id|set_tlb_bus
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|page
comma
r_int
r_int
id|ptr
comma
id|dma_addr_t
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
id|page
op_mul_assign
id|UNIT_PAGES
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
id|UNIT_PAGES
suffix:semicolon
id|i
op_increment
comma
id|page
op_increment
)paren
(brace
id|__set_tlb_bus
c_func
(paren
id|trident
comma
id|page
comma
id|ptr
comma
id|addr
)paren
suffix:semicolon
id|ptr
op_add_assign
id|SNDRV_TRIDENT_PAGE_SIZE
suffix:semicolon
id|addr
op_add_assign
id|SNDRV_TRIDENT_PAGE_SIZE
suffix:semicolon
)brace
)brace
DECL|function|set_silent_tlb
r_static
r_inline
r_void
id|set_silent_tlb
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|page
)paren
(brace
r_int
id|i
suffix:semicolon
id|page
op_mul_assign
id|UNIT_PAGES
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
id|UNIT_PAGES
suffix:semicolon
id|i
op_increment
comma
id|page
op_increment
)paren
id|__set_tlb_bus
c_func
(paren
id|trident
comma
id|page
comma
(paren
r_int
r_int
)paren
id|trident-&gt;tlb.silent_page
comma
id|trident-&gt;tlb.silent_page_dmaaddr
)paren
suffix:semicolon
)brace
macro_line|#endif /* PAGE_SIZE */
multiline_comment|/* calculate buffer pointer from offset address */
DECL|function|offset_ptr
r_inline
r_static
r_void
op_star
id|offset_ptr
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|offset
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|page_to_ptr
c_func
(paren
id|trident
comma
id|get_aligned_page
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
id|ptr
op_add_assign
id|offset
op_mod
id|ALIGN_PAGE_SIZE
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ptr
suffix:semicolon
)brace
multiline_comment|/* first and last (aligned) pages of memory block */
DECL|macro|firstpg
mdefine_line|#define firstpg(blk)&t;(((snd_trident_memblk_arg_t*)snd_util_memblk_argptr(blk))-&gt;first_page)
DECL|macro|lastpg
mdefine_line|#define lastpg(blk)&t;(((snd_trident_memblk_arg_t*)snd_util_memblk_argptr(blk))-&gt;last_page)
multiline_comment|/*&n; * search empty pages which may contain given size&n; */
r_static
id|snd_util_memblk_t
op_star
DECL|function|search_empty
id|search_empty
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_int
id|size
)paren
(brace
id|snd_util_memblk_t
op_star
id|blk
comma
op_star
id|prev
suffix:semicolon
r_int
id|page
comma
id|psize
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|psize
op_assign
id|get_aligned_page
c_func
(paren
id|size
op_plus
id|ALIGN_PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|page
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|hdr-&gt;block
)paren
(brace
id|blk
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|snd_util_memblk_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_plus
id|psize
op_le
id|firstpg
c_func
(paren
id|blk
)paren
)paren
r_goto
id|__found_pages
suffix:semicolon
id|page
op_assign
id|lastpg
c_func
(paren
id|blk
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
op_plus
id|psize
OG
id|MAX_ALIGN_PAGES
)paren
r_return
l_int|NULL
suffix:semicolon
id|__found_pages
suffix:colon
multiline_comment|/* create a new memory block */
id|blk
op_assign
id|__snd_util_memblk_new
c_func
(paren
id|hdr
comma
id|psize
op_star
id|ALIGN_PAGE_SIZE
comma
id|p-&gt;prev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|blk-&gt;offset
op_assign
id|aligned_page_offset
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* set aligned offset */
id|firstpg
c_func
(paren
id|blk
)paren
op_assign
id|page
suffix:semicolon
id|lastpg
c_func
(paren
id|blk
)paren
op_assign
id|page
op_plus
id|psize
op_minus
l_int|1
suffix:semicolon
r_return
id|blk
suffix:semicolon
)brace
multiline_comment|/*&n; * check if the given pointer is valid for pages&n; */
DECL|function|is_valid_page
r_static
r_int
id|is_valid_page
c_func
(paren
r_void
op_star
id|pages
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
id|virt_to_phys
c_func
(paren
id|pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_amp
op_complement
l_int|0x3fffffffUL
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;max memory size is 1GB!!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptr
op_amp
(paren
id|SNDRV_TRIDENT_PAGE_SIZE
op_minus
l_int|1
)paren
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;page is not aligned&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * page allocation for DMA&n; */
id|snd_util_memblk_t
op_star
DECL|function|snd_trident_alloc_pages
id|snd_trident_alloc_pages
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_void
op_star
id|pages
comma
id|dma_addr_t
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|ptr
suffix:semicolon
id|snd_util_memhdr_t
op_star
id|hdr
suffix:semicolon
id|snd_util_memblk_t
op_star
id|blk
suffix:semicolon
r_int
id|page
suffix:semicolon
id|snd_assert
c_func
(paren
id|trident
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
OG
l_int|0
op_logical_and
id|size
OL
id|SNDRV_TRIDENT_MAX_PAGES
op_star
id|SNDRV_TRIDENT_PAGE_SIZE
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|hdr
op_assign
id|trident-&gt;tlb.memhdr
suffix:semicolon
id|snd_assert
c_func
(paren
id|hdr
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_valid_page
c_func
(paren
id|pages
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
id|blk
op_assign
id|search_empty
c_func
(paren
id|hdr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* set TLB entries */
id|ptr
op_assign
(paren
r_int
r_int
)paren
id|pages
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|firstpg
c_func
(paren
id|blk
)paren
suffix:semicolon
id|page
op_le
id|lastpg
c_func
(paren
id|blk
)paren
suffix:semicolon
id|page
op_increment
)paren
(brace
id|set_tlb_bus
c_func
(paren
id|trident
comma
id|page
comma
id|ptr
comma
id|addr
)paren
suffix:semicolon
id|ptr
op_add_assign
id|ALIGN_PAGE_SIZE
suffix:semicolon
id|addr
op_add_assign
id|ALIGN_PAGE_SIZE
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
id|blk
suffix:semicolon
)brace
multiline_comment|/*&n; * release DMA buffer from page table&n; */
DECL|function|snd_trident_free_pages
r_int
id|snd_trident_free_pages
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
(brace
id|snd_util_memhdr_t
op_star
id|hdr
suffix:semicolon
r_int
id|page
suffix:semicolon
id|snd_assert
c_func
(paren
id|trident
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|blk
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|hdr
op_assign
id|trident-&gt;tlb.memhdr
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
multiline_comment|/* reset TLB entries */
r_for
c_loop
(paren
id|page
op_assign
id|firstpg
c_func
(paren
id|blk
)paren
suffix:semicolon
id|page
op_le
id|lastpg
c_func
(paren
id|blk
)paren
suffix:semicolon
id|page
op_increment
)paren
id|set_silent_tlb
c_func
(paren
id|trident
comma
id|page
)paren
suffix:semicolon
multiline_comment|/* free memory block */
id|__snd_util_mem_free
c_func
(paren
id|hdr
comma
id|blk
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------&n; * memory allocation using multiple pages (for synth)&n; *----------------------------------------------------------------&n; * Unlike the DMA allocation above, non-contiguous pages are&n; * assigned to TLB.&n; *----------------------------------------------------------------*/
multiline_comment|/*&n; */
r_static
r_int
id|synth_alloc_pages
c_func
(paren
id|trident_t
op_star
id|hw
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
r_static
r_int
id|synth_free_pages
c_func
(paren
id|trident_t
op_star
id|hw
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
multiline_comment|/*&n; * allocate a synth sample area&n; */
id|snd_util_memblk_t
op_star
DECL|function|snd_trident_synth_alloc
id|snd_trident_synth_alloc
c_func
(paren
id|trident_t
op_star
id|hw
comma
r_int
r_int
id|size
)paren
(brace
id|snd_util_memblk_t
op_star
id|blk
suffix:semicolon
id|snd_util_memhdr_t
op_star
id|hdr
op_assign
id|hw-&gt;tlb.memhdr
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
id|blk
op_assign
id|__snd_util_mem_alloc
c_func
(paren
id|hdr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|synth_alloc_pages
c_func
(paren
id|hw
comma
id|blk
)paren
)paren
(brace
id|__snd_util_mem_free
c_func
(paren
id|hdr
comma
id|blk
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
id|blk
suffix:semicolon
)brace
multiline_comment|/*&n; * free a synth sample area&n; */
r_int
DECL|function|snd_trident_synth_free
id|snd_trident_synth_free
c_func
(paren
id|trident_t
op_star
id|hw
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
(brace
id|snd_util_memhdr_t
op_star
id|hdr
op_assign
id|hw-&gt;tlb.memhdr
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
id|synth_free_pages
c_func
(paren
id|hw
comma
id|blk
)paren
suffix:semicolon
id|__snd_util_mem_free
c_func
(paren
id|hdr
comma
id|blk
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * reset TLB entry and free kernel page&n; */
DECL|function|clear_tlb
r_static
r_void
id|clear_tlb
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|page
)paren
(brace
r_void
op_star
id|ptr
op_assign
id|page_to_ptr
c_func
(paren
id|trident
comma
id|page
)paren
suffix:semicolon
id|dma_addr_t
id|addr
op_assign
id|page_to_addr
c_func
(paren
id|trident
comma
id|page
)paren
suffix:semicolon
id|set_silent_tlb
c_func
(paren
id|trident
comma
id|page
)paren
suffix:semicolon
id|snd_free_pci_pages
c_func
(paren
id|trident-&gt;pci
comma
id|ALIGN_PAGE_SIZE
comma
id|ptr
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* check new allocation range */
DECL|function|get_single_page_range
r_static
r_void
id|get_single_page_range
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
op_star
id|first_page_ret
comma
r_int
op_star
id|last_page_ret
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|snd_util_memblk_t
op_star
id|q
suffix:semicolon
r_int
id|first_page
comma
id|last_page
suffix:semicolon
id|first_page
op_assign
id|firstpg
c_func
(paren
id|blk
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|blk-&gt;list.prev
)paren
op_ne
op_amp
id|hdr-&gt;block
)paren
(brace
id|q
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|snd_util_memblk_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lastpg
c_func
(paren
id|q
)paren
op_eq
id|first_page
)paren
id|first_page
op_increment
suffix:semicolon
multiline_comment|/* first page was already allocated */
)brace
id|last_page
op_assign
id|lastpg
c_func
(paren
id|blk
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|blk-&gt;list.next
)paren
op_ne
op_amp
id|hdr-&gt;block
)paren
(brace
id|q
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|snd_util_memblk_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|firstpg
c_func
(paren
id|q
)paren
op_eq
id|last_page
)paren
id|last_page
op_decrement
suffix:semicolon
multiline_comment|/* last page was already allocated */
)brace
op_star
id|first_page_ret
op_assign
id|first_page
suffix:semicolon
op_star
id|last_page_ret
op_assign
id|last_page
suffix:semicolon
)brace
multiline_comment|/*&n; * allocate kernel pages and assign them to TLB&n; */
DECL|function|synth_alloc_pages
r_static
r_int
id|synth_alloc_pages
c_func
(paren
id|trident_t
op_star
id|hw
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
(brace
r_int
id|page
comma
id|first_page
comma
id|last_page
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
id|dma_addr_t
id|addr
suffix:semicolon
id|firstpg
c_func
(paren
id|blk
)paren
op_assign
id|get_aligned_page
c_func
(paren
id|blk-&gt;offset
)paren
suffix:semicolon
id|lastpg
c_func
(paren
id|blk
)paren
op_assign
id|get_aligned_page
c_func
(paren
id|blk-&gt;offset
op_plus
id|blk-&gt;size
op_minus
l_int|1
)paren
suffix:semicolon
id|get_single_page_range
c_func
(paren
id|hw-&gt;tlb.memhdr
comma
id|blk
comma
op_amp
id|first_page
comma
op_amp
id|last_page
)paren
suffix:semicolon
multiline_comment|/* allocate a kernel page for each Trident page -&n;&t; * fortunately Trident page size and kernel PAGE_SIZE is identical!&n;&t; */
r_for
c_loop
(paren
id|page
op_assign
id|first_page
suffix:semicolon
id|page
op_le
id|last_page
suffix:semicolon
id|page
op_increment
)paren
(brace
id|ptr
op_assign
id|snd_malloc_pci_pages
c_func
(paren
id|hw-&gt;pci
comma
id|ALIGN_PAGE_SIZE
comma
op_amp
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
r_goto
id|__fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_valid_page
c_func
(paren
id|ptr
)paren
)paren
(brace
id|snd_free_pci_pages
c_func
(paren
id|hw-&gt;pci
comma
id|ALIGN_PAGE_SIZE
comma
id|ptr
comma
id|addr
)paren
suffix:semicolon
r_goto
id|__fail
suffix:semicolon
)brace
id|set_tlb_bus
c_func
(paren
id|hw
comma
id|page
comma
(paren
r_int
r_int
)paren
id|ptr
comma
id|addr
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|__fail
suffix:colon
multiline_comment|/* release allocated pages */
id|last_page
op_assign
id|page
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|first_page
suffix:semicolon
id|page
op_le
id|last_page
suffix:semicolon
id|page
op_increment
)paren
id|clear_tlb
c_func
(paren
id|hw
comma
id|page
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n; * free pages&n; */
DECL|function|synth_free_pages
r_static
r_int
id|synth_free_pages
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
(brace
r_int
id|page
comma
id|first_page
comma
id|last_page
suffix:semicolon
id|get_single_page_range
c_func
(paren
id|trident-&gt;tlb.memhdr
comma
id|blk
comma
op_amp
id|first_page
comma
op_amp
id|last_page
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|first_page
suffix:semicolon
id|page
op_le
id|last_page
suffix:semicolon
id|page
op_increment
)paren
id|clear_tlb
c_func
(paren
id|trident
comma
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * bzero(blk + offset, size)&n; */
DECL|function|snd_trident_synth_bzero
r_int
id|snd_trident_synth_bzero
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
id|offset
comma
r_int
id|size
)paren
(brace
r_int
id|page
comma
id|nextofs
comma
id|end_offset
comma
id|temp
comma
id|temp1
suffix:semicolon
id|offset
op_add_assign
id|blk-&gt;offset
suffix:semicolon
id|end_offset
op_assign
id|offset
op_plus
id|size
suffix:semicolon
id|page
op_assign
id|get_aligned_page
c_func
(paren
id|offset
)paren
op_plus
l_int|1
suffix:semicolon
r_do
(brace
id|nextofs
op_assign
id|aligned_page_offset
c_func
(paren
id|page
)paren
suffix:semicolon
id|temp
op_assign
id|nextofs
op_minus
id|offset
suffix:semicolon
id|temp1
op_assign
id|end_offset
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|temp1
OL
id|temp
)paren
id|temp
op_assign
id|temp1
suffix:semicolon
id|memset
c_func
(paren
id|offset_ptr
c_func
(paren
id|trident
comma
id|offset
)paren
comma
l_int|0
comma
id|temp
)paren
suffix:semicolon
id|offset
op_assign
id|nextofs
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
id|end_offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * copy_from_user(blk + offset, data, size)&n; */
DECL|function|snd_trident_synth_copy_from_user
r_int
id|snd_trident_synth_copy_from_user
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_int
id|page
comma
id|nextofs
comma
id|end_offset
comma
id|temp
comma
id|temp1
suffix:semicolon
id|offset
op_add_assign
id|blk-&gt;offset
suffix:semicolon
id|end_offset
op_assign
id|offset
op_plus
id|size
suffix:semicolon
id|page
op_assign
id|get_aligned_page
c_func
(paren
id|offset
)paren
op_plus
l_int|1
suffix:semicolon
r_do
(brace
id|nextofs
op_assign
id|aligned_page_offset
c_func
(paren
id|page
)paren
suffix:semicolon
id|temp
op_assign
id|nextofs
op_minus
id|offset
suffix:semicolon
id|temp1
op_assign
id|end_offset
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|temp1
OL
id|temp
)paren
id|temp
op_assign
id|temp1
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|offset_ptr
c_func
(paren
id|trident
comma
id|offset
)paren
comma
id|data
comma
id|temp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|offset
op_assign
id|nextofs
suffix:semicolon
id|data
op_add_assign
id|temp
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
id|end_offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
