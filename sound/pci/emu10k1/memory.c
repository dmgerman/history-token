multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *  EMU10K1 memory page allocation (PTB area)&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
multiline_comment|/* page arguments of these two macros are Emu page (4096 bytes), not like&n; * aligned pages in others&n; */
DECL|macro|__set_ptb_entry
mdefine_line|#define __set_ptb_entry(emu,page,addr) &bslash;&n;&t;(((u32 *)(emu)-&gt;ptb_pages.area)[page] = cpu_to_le32(((addr) &lt;&lt; 1) | (page)))
DECL|macro|UNIT_PAGES
mdefine_line|#define UNIT_PAGES&t;&t;(PAGE_SIZE / EMUPAGESIZE)
DECL|macro|MAX_ALIGN_PAGES
mdefine_line|#define MAX_ALIGN_PAGES&t;&t;(MAXPAGES / UNIT_PAGES)
multiline_comment|/* get aligned page from offset address */
DECL|macro|get_aligned_page
mdefine_line|#define get_aligned_page(offset)&t;((offset) &gt;&gt; PAGE_SHIFT)
multiline_comment|/* get offset address from aligned page */
DECL|macro|aligned_page_offset
mdefine_line|#define aligned_page_offset(page)&t;((page) &lt;&lt; PAGE_SHIFT)
macro_line|#if PAGE_SIZE == 4096
multiline_comment|/* page size == EMUPAGESIZE */
multiline_comment|/* fill PTB entrie(s) corresponding to page with addr */
DECL|macro|set_ptb_entry
mdefine_line|#define set_ptb_entry(emu,page,addr)&t;__set_ptb_entry(emu,page,addr)
multiline_comment|/* fill PTB entrie(s) corresponding to page with silence pointer */
DECL|macro|set_silent_ptb
mdefine_line|#define set_silent_ptb(emu,page)&t;__set_ptb_entry(emu,page,emu-&gt;silent_page.addr)
macro_line|#else
multiline_comment|/* fill PTB entries -- we need to fill UNIT_PAGES entries */
DECL|function|set_ptb_entry
r_static
r_inline
r_void
id|set_ptb_entry
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|page
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
id|__set_ptb_entry
c_func
(paren
id|emu
comma
id|page
comma
id|addr
)paren
suffix:semicolon
id|addr
op_add_assign
id|EMUPAGESIZE
suffix:semicolon
)brace
)brace
DECL|function|set_silent_ptb
r_static
r_inline
r_void
id|set_silent_ptb
c_func
(paren
id|emu10k1_t
op_star
id|emu
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
multiline_comment|/* do not increment ptr */
id|__set_ptb_entry
c_func
(paren
id|emu
comma
id|page
comma
id|emu-&gt;silent_page_dmaaddr
)paren
suffix:semicolon
)brace
macro_line|#endif /* PAGE_SIZE */
multiline_comment|/*&n; */
r_static
r_int
id|synth_alloc_pages
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|emu10k1_memblk_t
op_star
id|blk
)paren
suffix:semicolon
r_static
r_int
id|synth_free_pages
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
id|emu10k1_memblk_t
op_star
id|blk
)paren
suffix:semicolon
DECL|macro|get_emu10k1_memblk
mdefine_line|#define get_emu10k1_memblk(l,member)&t;list_entry(l, emu10k1_memblk_t, member)
multiline_comment|/* initialize emu10k1 part */
DECL|function|emu10k1_memblk_init
r_static
r_void
id|emu10k1_memblk_init
c_func
(paren
id|emu10k1_memblk_t
op_star
id|blk
)paren
(brace
id|blk-&gt;mapped_page
op_assign
op_minus
l_int|1
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|blk-&gt;mapped_link
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|blk-&gt;mapped_order_link
)paren
suffix:semicolon
id|blk-&gt;map_locked
op_assign
l_int|0
suffix:semicolon
id|blk-&gt;first_page
op_assign
id|get_aligned_page
c_func
(paren
id|blk-&gt;mem.offset
)paren
suffix:semicolon
id|blk-&gt;last_page
op_assign
id|get_aligned_page
c_func
(paren
id|blk-&gt;mem.offset
op_plus
id|blk-&gt;mem.size
op_minus
l_int|1
)paren
suffix:semicolon
id|blk-&gt;pages
op_assign
id|blk-&gt;last_page
op_minus
id|blk-&gt;first_page
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * search empty region on PTB with the given size&n; *&n; * if an empty region is found, return the page and store the next mapped block&n; * in nextp&n; * if not found, return a negative error code.&n; */
DECL|function|search_empty_map_area
r_static
r_int
id|search_empty_map_area
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|npages
comma
r_struct
id|list_head
op_star
op_star
id|nextp
)paren
(brace
r_int
id|page
op_assign
l_int|0
comma
id|found_page
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_int
id|max_size
op_assign
id|npages
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|list_head
op_star
id|candidate
op_assign
op_amp
id|emu-&gt;mapped_link_head
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|list_for_each
(paren
id|pos
comma
op_amp
id|emu-&gt;mapped_link_head
)paren
(brace
id|emu10k1_memblk_t
op_star
id|blk
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|pos
comma
id|mapped_link
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|blk-&gt;mapped_page
op_ge
l_int|0
comma
r_continue
)paren
suffix:semicolon
id|size
op_assign
id|blk-&gt;mapped_page
op_minus
id|page
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
id|npages
)paren
(brace
op_star
id|nextp
op_assign
id|pos
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|size
OG
id|max_size
)paren
(brace
multiline_comment|/* we look for the maximum empty hole */
id|max_size
op_assign
id|size
suffix:semicolon
id|candidate
op_assign
id|pos
suffix:semicolon
id|found_page
op_assign
id|page
suffix:semicolon
)brace
id|page
op_assign
id|blk-&gt;mapped_page
op_plus
id|blk-&gt;pages
suffix:semicolon
)brace
id|size
op_assign
id|MAX_ALIGN_PAGES
op_minus
id|page
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
id|max_size
)paren
(brace
op_star
id|nextp
op_assign
id|pos
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
op_star
id|nextp
op_assign
id|candidate
suffix:semicolon
r_return
id|found_page
suffix:semicolon
)brace
multiline_comment|/*&n; * map a memory block onto emu10k1&squot;s PTB&n; *&n; * call with memblk_lock held&n; */
DECL|function|map_memblk
r_static
r_int
id|map_memblk
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_memblk_t
op_star
id|blk
)paren
(brace
r_int
id|page
comma
id|pg
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
id|page
op_assign
id|search_empty_map_area
c_func
(paren
id|emu
comma
id|blk-&gt;pages
comma
op_amp
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
OL
l_int|0
)paren
multiline_comment|/* not found */
r_return
id|page
suffix:semicolon
multiline_comment|/* insert this block in the proper position of mapped list */
id|list_add_tail
c_func
(paren
op_amp
id|blk-&gt;mapped_link
comma
id|next
)paren
suffix:semicolon
multiline_comment|/* append this as a newest block in order list */
id|list_add_tail
c_func
(paren
op_amp
id|blk-&gt;mapped_order_link
comma
op_amp
id|emu-&gt;mapped_order_link_head
)paren
suffix:semicolon
id|blk-&gt;mapped_page
op_assign
id|page
suffix:semicolon
multiline_comment|/* fill PTB */
r_for
c_loop
(paren
id|pg
op_assign
id|blk-&gt;first_page
suffix:semicolon
id|pg
op_le
id|blk-&gt;last_page
suffix:semicolon
id|pg
op_increment
)paren
(brace
id|set_ptb_entry
c_func
(paren
id|emu
comma
id|page
comma
id|emu-&gt;page_addr_table
(braket
id|pg
)braket
)paren
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * unmap the block&n; * return the size of resultant empty pages&n; *&n; * call with memblk_lock held&n; */
DECL|function|unmap_memblk
r_static
r_int
id|unmap_memblk
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_memblk_t
op_star
id|blk
)paren
(brace
r_int
id|start_page
comma
id|end_page
comma
id|mpage
comma
id|pg
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|q
suffix:semicolon
multiline_comment|/* calculate the expected size of empty region */
r_if
c_cond
(paren
(paren
id|p
op_assign
id|blk-&gt;mapped_link.prev
)paren
op_ne
op_amp
id|emu-&gt;mapped_link_head
)paren
(brace
id|q
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|p
comma
id|mapped_link
)paren
suffix:semicolon
id|start_page
op_assign
id|q-&gt;mapped_page
op_plus
id|q-&gt;pages
suffix:semicolon
)brace
r_else
id|start_page
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|blk-&gt;mapped_link.next
)paren
op_ne
op_amp
id|emu-&gt;mapped_link_head
)paren
(brace
id|q
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|p
comma
id|mapped_link
)paren
suffix:semicolon
id|end_page
op_assign
id|q-&gt;mapped_page
suffix:semicolon
)brace
r_else
id|end_page
op_assign
id|MAX_ALIGN_PAGES
suffix:semicolon
multiline_comment|/* remove links */
id|list_del
c_func
(paren
op_amp
id|blk-&gt;mapped_link
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|blk-&gt;mapped_order_link
)paren
suffix:semicolon
multiline_comment|/* clear PTB */
id|mpage
op_assign
id|blk-&gt;mapped_page
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
id|blk-&gt;first_page
suffix:semicolon
id|pg
op_le
id|blk-&gt;last_page
suffix:semicolon
id|pg
op_increment
)paren
(brace
id|set_silent_ptb
c_func
(paren
id|emu
comma
id|mpage
)paren
suffix:semicolon
id|mpage
op_increment
suffix:semicolon
)brace
id|blk-&gt;mapped_page
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|end_page
op_minus
id|start_page
suffix:semicolon
multiline_comment|/* return the new empty size */
)brace
multiline_comment|/*&n; * search empty pages with the given size, and create a memory block&n; *&n; * unlike synth_alloc the memory block is aligned to the page start&n; */
r_static
id|emu10k1_memblk_t
op_star
DECL|function|search_empty
id|search_empty
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|size
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|blk
suffix:semicolon
r_int
id|page
comma
id|psize
suffix:semicolon
id|psize
op_assign
id|get_aligned_page
c_func
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
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
id|emu-&gt;memhdr-&gt;block
)paren
(brace
id|blk
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|p
comma
id|mem.list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_plus
id|psize
op_le
id|blk-&gt;first_page
)paren
r_goto
id|__found_pages
suffix:semicolon
id|page
op_assign
id|blk-&gt;last_page
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
id|emu-&gt;max_cache_pages
)paren
r_return
l_int|NULL
suffix:semicolon
id|__found_pages
suffix:colon
multiline_comment|/* create a new memory block */
id|blk
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|__snd_util_memblk_new
c_func
(paren
id|emu-&gt;memhdr
comma
id|psize
op_lshift
id|PAGE_SHIFT
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
id|blk-&gt;mem.offset
op_assign
id|aligned_page_offset
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* set aligned offset */
id|emu10k1_memblk_init
c_func
(paren
id|blk
)paren
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
id|emu10k1_t
op_star
id|emu
comma
id|dma_addr_t
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|emu-&gt;dma_mask
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;max memory size is 0x%lx (addr = 0x%lx)!!&bslash;n&quot;
comma
id|emu-&gt;dma_mask
comma
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_amp
(paren
id|EMUPAGESIZE
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
multiline_comment|/*&n; * map the given memory block on PTB.&n; * if the block is already mapped, update the link order.&n; * if no empty pages are found, tries to release unsed memory blocks&n; * and retry the mapping.&n; */
DECL|function|snd_emu10k1_memblk_map
r_int
id|snd_emu10k1_memblk_map
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_memblk_t
op_star
id|blk
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|nextp
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|deleted
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;memblk_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk-&gt;mapped_page
op_ge
l_int|0
)paren
(brace
multiline_comment|/* update order link */
id|list_del
c_func
(paren
op_amp
id|blk-&gt;mapped_order_link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|blk-&gt;mapped_order_link
comma
op_amp
id|emu-&gt;mapped_order_link_head
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;memblk_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|map_memblk
c_func
(paren
id|emu
comma
id|blk
)paren
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* no enough page - try to unmap some blocks */
multiline_comment|/* starting from the oldest block */
id|p
op_assign
id|emu-&gt;mapped_order_link_head.next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|p
op_ne
op_amp
id|emu-&gt;mapped_order_link_head
suffix:semicolon
id|p
op_assign
id|nextp
)paren
(brace
id|nextp
op_assign
id|p-&gt;next
suffix:semicolon
id|deleted
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|p
comma
id|mapped_order_link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deleted-&gt;map_locked
)paren
r_continue
suffix:semicolon
id|size
op_assign
id|unmap_memblk
c_func
(paren
id|emu
comma
id|deleted
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
id|blk-&gt;pages
)paren
(brace
multiline_comment|/* ok the empty region is enough large */
id|err
op_assign
id|map_memblk
c_func
(paren
id|emu
comma
id|blk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;memblk_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * page allocation for DMA&n; */
id|snd_util_memblk_t
op_star
DECL|function|snd_emu10k1_alloc_pages
id|snd_emu10k1_alloc_pages
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_struct
id|snd_sg_buf
op_star
id|sgbuf
op_assign
id|runtime-&gt;dma_private
suffix:semicolon
id|snd_util_memhdr_t
op_star
id|hdr
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|blk
suffix:semicolon
r_int
id|page
comma
id|err
comma
id|idx
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|substream-&gt;dma_device.type
op_eq
id|SNDRV_DMA_TYPE_PCI_SG
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|runtime-&gt;dma_bytes
OG
l_int|0
op_logical_and
id|runtime-&gt;dma_bytes
OL
id|MAXPAGES
op_star
id|EMUPAGESIZE
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|hdr
op_assign
id|emu-&gt;memhdr
suffix:semicolon
id|snd_assert
c_func
(paren
id|hdr
comma
r_return
l_int|NULL
)paren
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
id|emu
comma
id|runtime-&gt;dma_bytes
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
multiline_comment|/* fill buffer addresses but pointers are not stored so that&n;&t; * snd_free_pci_page() is not called in in synth_free()&n;&t; */
id|idx
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|blk-&gt;first_page
suffix:semicolon
id|page
op_le
id|blk-&gt;last_page
suffix:semicolon
id|page
op_increment
comma
id|idx
op_increment
)paren
(brace
id|dma_addr_t
id|addr
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
r_if
c_cond
(paren
id|idx
op_ge
id|sgbuf-&gt;pages
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;emu: pages overflow! (%d-%d) for %d&bslash;n&quot;
comma
id|blk-&gt;first_page
comma
id|blk-&gt;last_page
comma
id|sgbuf-&gt;pages
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
macro_line|#endif
id|addr
op_assign
id|sgbuf-&gt;table
(braket
id|idx
)braket
dot
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_valid_page
c_func
(paren
id|emu
comma
id|addr
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;emu: failure page = %d&bslash;n&quot;
comma
id|idx
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
id|emu-&gt;page_addr_table
(braket
id|page
)braket
op_assign
id|addr
suffix:semicolon
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* set PTB entries */
id|blk-&gt;map_locked
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* do not unmap this block! */
id|err
op_assign
id|snd_emu10k1_memblk_map
c_func
(paren
id|emu
comma
id|blk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|__snd_util_mem_free
c_func
(paren
id|hdr
comma
(paren
id|snd_util_memblk_t
op_star
)paren
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
(paren
id|snd_util_memblk_t
op_star
)paren
id|blk
suffix:semicolon
)brace
multiline_comment|/*&n; * release DMA buffer from page table&n; */
DECL|function|snd_emu10k1_free_pages
r_int
id|snd_emu10k1_free_pages
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
(brace
id|snd_assert
c_func
(paren
id|emu
op_logical_and
id|blk
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_return
id|snd_emu10k1_synth_free
c_func
(paren
id|emu
comma
id|blk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * memory allocation using multiple pages (for synth)&n; * Unlike the DMA allocation above, non-contiguous pages are assined.&n; */
multiline_comment|/*&n; * allocate a synth sample area&n; */
id|snd_util_memblk_t
op_star
DECL|function|snd_emu10k1_synth_alloc
id|snd_emu10k1_synth_alloc
c_func
(paren
id|emu10k1_t
op_star
id|hw
comma
r_int
r_int
id|size
)paren
(brace
id|emu10k1_memblk_t
op_star
id|blk
suffix:semicolon
id|snd_util_memhdr_t
op_star
id|hdr
op_assign
id|hw-&gt;memhdr
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
(paren
id|emu10k1_memblk_t
op_star
)paren
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
(paren
id|snd_util_memblk_t
op_star
)paren
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
id|snd_emu10k1_memblk_map
c_func
(paren
id|hw
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
(paren
id|snd_util_memblk_t
op_star
)paren
id|blk
suffix:semicolon
)brace
multiline_comment|/*&n; * free a synth sample area&n; */
r_int
DECL|function|snd_emu10k1_synth_free
id|snd_emu10k1_synth_free
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_util_memblk_t
op_star
id|memblk
)paren
(brace
id|snd_util_memhdr_t
op_star
id|hdr
op_assign
id|emu-&gt;memhdr
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|blk
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|memblk
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hdr-&gt;block_mutex
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;memblk_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk-&gt;mapped_page
op_ge
l_int|0
)paren
id|unmap_memblk
c_func
(paren
id|emu
comma
id|blk
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;memblk_lock
comma
id|flags
)paren
suffix:semicolon
id|synth_free_pages
c_func
(paren
id|emu
comma
id|blk
)paren
suffix:semicolon
id|__snd_util_mem_free
c_func
(paren
id|hdr
comma
id|memblk
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
id|emu10k1_memblk_t
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
id|emu10k1_memblk_t
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
id|blk-&gt;first_page
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|blk-&gt;mem.list.prev
)paren
op_ne
op_amp
id|hdr-&gt;block
)paren
(brace
id|q
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|p
comma
id|mem.list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;last_page
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
id|blk-&gt;last_page
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|blk-&gt;mem.list.next
)paren
op_ne
op_amp
id|hdr-&gt;block
)paren
(brace
id|q
op_assign
id|get_emu10k1_memblk
c_func
(paren
id|p
comma
id|mem.list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;first_page
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
multiline_comment|/*&n; * allocate kernel pages&n; */
DECL|function|synth_alloc_pages
r_static
r_int
id|synth_alloc_pages
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_memblk_t
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
r_struct
id|snd_dma_buffer
id|dmab
suffix:semicolon
id|emu10k1_memblk_init
c_func
(paren
id|blk
)paren
suffix:semicolon
id|get_single_page_range
c_func
(paren
id|emu-&gt;memhdr
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
multiline_comment|/* allocate kernel pages */
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
r_if
c_cond
(paren
id|snd_dma_alloc_pages
c_func
(paren
op_amp
id|emu-&gt;dma_dev
comma
id|PAGE_SIZE
comma
op_amp
id|dmab
)paren
OL
l_int|0
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
id|emu
comma
id|dmab.addr
)paren
)paren
(brace
id|snd_dma_free_pages
c_func
(paren
op_amp
id|emu-&gt;dma_dev
comma
op_amp
id|dmab
)paren
suffix:semicolon
r_goto
id|__fail
suffix:semicolon
)brace
id|emu-&gt;page_addr_table
(braket
id|page
)braket
op_assign
id|dmab.addr
suffix:semicolon
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
op_assign
id|dmab.area
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
(brace
id|dmab.area
op_assign
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
suffix:semicolon
id|dmab.addr
op_assign
id|emu-&gt;page_addr_table
(braket
id|page
)braket
suffix:semicolon
id|dmab.bytes
op_assign
id|PAGE_SIZE
suffix:semicolon
id|snd_dma_free_pages
c_func
(paren
op_amp
id|emu-&gt;dma_dev
comma
op_amp
id|dmab
)paren
suffix:semicolon
id|emu-&gt;page_addr_table
(braket
id|page
)braket
op_assign
l_int|0
suffix:semicolon
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
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
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_memblk_t
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
r_struct
id|snd_dma_buffer
id|dmab
suffix:semicolon
id|get_single_page_range
c_func
(paren
id|emu-&gt;memhdr
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
(brace
r_if
c_cond
(paren
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|dmab.area
op_assign
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
suffix:semicolon
id|dmab.addr
op_assign
id|emu-&gt;page_addr_table
(braket
id|page
)braket
suffix:semicolon
id|dmab.bytes
op_assign
id|PAGE_SIZE
suffix:semicolon
id|snd_dma_free_pages
c_func
(paren
op_amp
id|emu-&gt;dma_dev
comma
op_amp
id|dmab
)paren
suffix:semicolon
id|emu-&gt;page_addr_table
(braket
id|page
)braket
op_assign
l_int|0
suffix:semicolon
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* calculate buffer pointer from offset address */
DECL|function|offset_ptr
r_inline
r_static
r_void
op_star
id|offset_ptr
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|page
comma
r_int
id|offset
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
id|snd_assert
c_func
(paren
id|page
op_ge
l_int|0
op_logical_and
id|page
OL
id|emu-&gt;max_cache_pages
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|ptr
op_assign
id|emu-&gt;page_ptr_table
(braket
id|page
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;emu10k1: access to NULL ptr: page = %d&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ptr
op_add_assign
id|offset
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ptr
suffix:semicolon
)brace
multiline_comment|/*&n; * bzero(blk + offset, size)&n; */
DECL|function|snd_emu10k1_synth_bzero
r_int
id|snd_emu10k1_synth_bzero
c_func
(paren
id|emu10k1_t
op_star
id|emu
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
r_void
op_star
id|ptr
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|p
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|blk
suffix:semicolon
id|offset
op_add_assign
id|blk-&gt;offset
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
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
suffix:semicolon
r_do
(brace
id|nextofs
op_assign
id|aligned_page_offset
c_func
(paren
id|page
op_plus
l_int|1
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
id|ptr
op_assign
id|offset_ptr
c_func
(paren
id|emu
comma
id|page
op_plus
id|p-&gt;first_page
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|memset
c_func
(paren
id|ptr
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
DECL|function|snd_emu10k1_synth_copy_from_user
r_int
id|snd_emu10k1_synth_copy_from_user
c_func
(paren
id|emu10k1_t
op_star
id|emu
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
id|__user
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
r_void
op_star
id|ptr
suffix:semicolon
id|emu10k1_memblk_t
op_star
id|p
op_assign
(paren
id|emu10k1_memblk_t
op_star
)paren
id|blk
suffix:semicolon
id|offset
op_add_assign
id|blk-&gt;offset
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
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
suffix:semicolon
r_do
(brace
id|nextofs
op_assign
id|aligned_page_offset
c_func
(paren
id|page
op_plus
l_int|1
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
id|ptr
op_assign
id|offset_ptr
c_func
(paren
id|emu
comma
id|page
op_plus
id|p-&gt;first_page
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_logical_and
id|copy_from_user
c_func
(paren
id|ptr
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
