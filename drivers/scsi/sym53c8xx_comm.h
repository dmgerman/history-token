multiline_comment|/******************************************************************************&n;**  High Performance device driver for the Symbios 53C896 controller.&n;**&n;**  Copyright (C) 1998-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n;**&n;**  This driver also supports all the Symbios 53C8XX controller family, &n;**  except 53C810 revisions &lt; 16, 53C825 revisions &lt; 16 and all &n;**  revisions of 53C815 controllers.&n;**&n;**  This driver is based on the Linux port of the FreeBSD ncr driver.&n;** &n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**  &n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  The Linux port of the FreeBSD ncr driver has been achieved in &n;**  november 1995 by:&n;**&n;**          Gerard Roudier              &lt;groudier@free.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  Major contributions:&n;**  --------------------&n;**&n;**  NVRAM detection and reading.&n;**    Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n;**&n;*******************************************************************************&n;*/
multiline_comment|/*==========================================================&n;**&n;**&t;Debugging tags&n;**&n;**==========================================================&n;*/
DECL|macro|DEBUG_ALLOC
mdefine_line|#define DEBUG_ALLOC    (0x0001)
DECL|macro|DEBUG_PHASE
mdefine_line|#define DEBUG_PHASE    (0x0002)
DECL|macro|DEBUG_QUEUE
mdefine_line|#define DEBUG_QUEUE    (0x0008)
DECL|macro|DEBUG_RESULT
mdefine_line|#define DEBUG_RESULT   (0x0010)
DECL|macro|DEBUG_POINTER
mdefine_line|#define DEBUG_POINTER  (0x0020)
DECL|macro|DEBUG_SCRIPT
mdefine_line|#define DEBUG_SCRIPT   (0x0040)
DECL|macro|DEBUG_TINY
mdefine_line|#define DEBUG_TINY     (0x0080)
DECL|macro|DEBUG_TIMING
mdefine_line|#define DEBUG_TIMING   (0x0100)
DECL|macro|DEBUG_NEGO
mdefine_line|#define DEBUG_NEGO     (0x0200)
DECL|macro|DEBUG_TAGS
mdefine_line|#define DEBUG_TAGS     (0x0400)
DECL|macro|DEBUG_SCATTER
mdefine_line|#define DEBUG_SCATTER  (0x0800)
DECL|macro|DEBUG_IC
mdefine_line|#define DEBUG_IC        (0x1000)
multiline_comment|/*&n;**    Enable/Disable debug messages.&n;**    Can be changed at runtime too.&n;*/
macro_line|#ifdef SCSI_NCR_DEBUG_INFO_SUPPORT
DECL|variable|ncr_debug
r_static
r_int
id|ncr_debug
op_assign
id|SCSI_NCR_DEBUG_FLAGS
suffix:semicolon
DECL|macro|DEBUG_FLAGS
mdefine_line|#define DEBUG_FLAGS ncr_debug
macro_line|#else
DECL|macro|DEBUG_FLAGS
mdefine_line|#define DEBUG_FLAGS&t;SCSI_NCR_DEBUG_FLAGS
macro_line|#endif
DECL|function|ncr_list_pop
r_static
r_inline
r_struct
id|list_head
op_star
id|ncr_list_pop
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|head
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|elem
op_assign
id|head-&gt;next
suffix:semicolon
id|list_del
c_func
(paren
id|elem
)paren
suffix:semicolon
r_return
id|elem
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef __sparc__
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#endif
multiline_comment|/*==========================================================&n;**&n;**&t;Simple power of two buddy-like allocator.&n;**&n;**&t;This simple code is not intended to be fast, but to &n;**&t;provide power of 2 aligned memory allocations.&n;**&t;Since the SCRIPTS processor only supplies 8 bit &n;**&t;arithmetic, this allocator allows simple and fast &n;**&t;address calculations  from the SCRIPTS code.&n;**&t;In addition, cache line alignment is guaranteed for &n;**&t;power of 2 cache line size.&n;**&t;Enhanced in linux-2.3.44 to provide a memory pool &n;**&t;per pcidev to support dynamic dma mapping. (I would &n;**&t;have preferred a real bus astraction, btw).&n;**&n;**==========================================================&n;*/
DECL|macro|MEMO_SHIFT
mdefine_line|#define MEMO_SHIFT&t;4&t;/* 16 bytes minimum memory chunk */
macro_line|#if PAGE_SIZE &gt;= 8192
DECL|macro|MEMO_PAGE_ORDER
mdefine_line|#define MEMO_PAGE_ORDER&t;0&t;/* 1 PAGE  maximum */
macro_line|#else
DECL|macro|MEMO_PAGE_ORDER
mdefine_line|#define MEMO_PAGE_ORDER&t;1&t;/* 2 PAGES maximum */
macro_line|#endif
DECL|macro|MEMO_FREE_UNUSED
mdefine_line|#define MEMO_FREE_UNUSED&t;/* Free unused pages immediately */
DECL|macro|MEMO_WARN
mdefine_line|#define MEMO_WARN&t;1
DECL|macro|MEMO_GFP_FLAGS
mdefine_line|#define MEMO_GFP_FLAGS&t;GFP_ATOMIC
DECL|macro|MEMO_CLUSTER_SHIFT
mdefine_line|#define MEMO_CLUSTER_SHIFT&t;(PAGE_SHIFT+MEMO_PAGE_ORDER)
DECL|macro|MEMO_CLUSTER_SIZE
mdefine_line|#define MEMO_CLUSTER_SIZE&t;(1UL &lt;&lt; MEMO_CLUSTER_SHIFT)
DECL|macro|MEMO_CLUSTER_MASK
mdefine_line|#define MEMO_CLUSTER_MASK&t;(MEMO_CLUSTER_SIZE-1)
DECL|typedef|m_addr_t
r_typedef
id|u_long
id|m_addr_t
suffix:semicolon
multiline_comment|/* Enough bits to bit-hack addresses */
DECL|typedef|m_bush_t
r_typedef
r_struct
id|device
op_star
id|m_bush_t
suffix:semicolon
multiline_comment|/* Something that addresses DMAable */
DECL|struct|m_link
r_typedef
r_struct
id|m_link
(brace
multiline_comment|/* Link between free memory chunks */
DECL|member|next
r_struct
id|m_link
op_star
id|next
suffix:semicolon
DECL|typedef|m_link_s
)brace
id|m_link_s
suffix:semicolon
DECL|struct|m_vtob
r_typedef
r_struct
id|m_vtob
(brace
multiline_comment|/* Virtual to Bus address translation */
DECL|member|next
r_struct
id|m_vtob
op_star
id|next
suffix:semicolon
DECL|member|vaddr
id|m_addr_t
id|vaddr
suffix:semicolon
DECL|member|baddr
id|m_addr_t
id|baddr
suffix:semicolon
DECL|typedef|m_vtob_s
)brace
id|m_vtob_s
suffix:semicolon
DECL|macro|VTOB_HASH_SHIFT
mdefine_line|#define VTOB_HASH_SHIFT&t;&t;5
DECL|macro|VTOB_HASH_SIZE
mdefine_line|#define VTOB_HASH_SIZE&t;&t;(1UL &lt;&lt; VTOB_HASH_SHIFT)
DECL|macro|VTOB_HASH_MASK
mdefine_line|#define VTOB_HASH_MASK&t;&t;(VTOB_HASH_SIZE-1)
DECL|macro|VTOB_HASH_CODE
mdefine_line|#define VTOB_HASH_CODE(m)&t;&bslash;&n;&t;((((m_addr_t) (m)) &gt;&gt; MEMO_CLUSTER_SHIFT) &amp; VTOB_HASH_MASK)
DECL|struct|m_pool
r_typedef
r_struct
id|m_pool
(brace
multiline_comment|/* Memory pool of a given kind */
DECL|member|bush
id|m_bush_t
id|bush
suffix:semicolon
DECL|member|getp
id|m_addr_t
(paren
op_star
id|getp
)paren
(paren
r_struct
id|m_pool
op_star
)paren
suffix:semicolon
DECL|member|freep
r_void
(paren
op_star
id|freep
)paren
(paren
r_struct
id|m_pool
op_star
comma
id|m_addr_t
)paren
suffix:semicolon
DECL|member|nump
r_int
id|nump
suffix:semicolon
DECL|member|vtob
id|m_vtob_s
op_star
(paren
id|vtob
(braket
id|VTOB_HASH_SIZE
)braket
)paren
suffix:semicolon
DECL|member|next
r_struct
id|m_pool
op_star
id|next
suffix:semicolon
DECL|member|h
r_struct
id|m_link
id|h
(braket
id|PAGE_SHIFT
op_minus
id|MEMO_SHIFT
op_plus
id|MEMO_PAGE_ORDER
op_plus
l_int|1
)braket
suffix:semicolon
DECL|typedef|m_pool_s
)brace
id|m_pool_s
suffix:semicolon
DECL|function|___m_alloc
r_static
r_void
op_star
id|___m_alloc
c_func
(paren
id|m_pool_s
op_star
id|mp
comma
r_int
id|size
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|s
op_assign
(paren
l_int|1
op_lshift
id|MEMO_SHIFT
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
id|m_addr_t
id|a
suffix:semicolon
id|m_link_s
op_star
id|h
op_assign
id|mp-&gt;h
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|PAGE_SIZE
op_lshift
id|MEMO_PAGE_ORDER
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
id|s
)paren
(brace
id|s
op_lshift_assign
l_int|1
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
id|j
op_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|h
(braket
id|j
)braket
dot
id|next
)paren
(brace
r_if
c_cond
(paren
id|s
op_eq
(paren
id|PAGE_SIZE
op_lshift
id|MEMO_PAGE_ORDER
)paren
)paren
(brace
id|h
(braket
id|j
)braket
dot
id|next
op_assign
(paren
id|m_link_s
op_star
)paren
id|mp
op_member_access_from_pointer
id|getp
c_func
(paren
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h
(braket
id|j
)braket
dot
id|next
)paren
id|h
(braket
id|j
)braket
dot
id|next-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
op_increment
id|j
suffix:semicolon
id|s
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|a
op_assign
(paren
id|m_addr_t
)paren
id|h
(braket
id|j
)braket
dot
id|next
suffix:semicolon
r_if
c_cond
(paren
id|a
)paren
(brace
id|h
(braket
id|j
)braket
dot
id|next
op_assign
id|h
(braket
id|j
)braket
dot
id|next-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|j
OG
id|i
)paren
(brace
id|j
op_sub_assign
l_int|1
suffix:semicolon
id|s
op_rshift_assign
l_int|1
suffix:semicolon
id|h
(braket
id|j
)braket
dot
id|next
op_assign
(paren
id|m_link_s
op_star
)paren
(paren
id|a
op_plus
id|s
)paren
suffix:semicolon
id|h
(braket
id|j
)braket
dot
id|next-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;___m_alloc(%d) = %p&bslash;n&quot;
comma
id|size
comma
(paren
r_void
op_star
)paren
id|a
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
r_void
op_star
)paren
id|a
suffix:semicolon
)brace
DECL|function|___m_free
r_static
r_void
id|___m_free
c_func
(paren
id|m_pool_s
op_star
id|mp
comma
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|s
op_assign
(paren
l_int|1
op_lshift
id|MEMO_SHIFT
)paren
suffix:semicolon
id|m_link_s
op_star
id|q
suffix:semicolon
id|m_addr_t
id|a
comma
id|b
suffix:semicolon
id|m_link_s
op_star
id|h
op_assign
id|mp-&gt;h
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;___m_free(%p, %d)&bslash;n&quot;
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|size
OG
(paren
id|PAGE_SIZE
op_lshift
id|MEMO_PAGE_ORDER
)paren
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
id|s
)paren
(brace
id|s
op_lshift_assign
l_int|1
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
id|a
op_assign
(paren
id|m_addr_t
)paren
id|ptr
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
macro_line|#ifdef MEMO_FREE_UNUSED
r_if
c_cond
(paren
id|s
op_eq
(paren
id|PAGE_SIZE
op_lshift
id|MEMO_PAGE_ORDER
)paren
)paren
(brace
id|mp
op_member_access_from_pointer
id|freep
c_func
(paren
id|mp
comma
id|a
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
id|b
op_assign
id|a
op_xor
id|s
suffix:semicolon
id|q
op_assign
op_amp
id|h
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|q-&gt;next
op_logical_and
id|q-&gt;next
op_ne
(paren
id|m_link_s
op_star
)paren
id|b
)paren
(brace
id|q
op_assign
id|q-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;next
)paren
(brace
(paren
(paren
id|m_link_s
op_star
)paren
id|a
)paren
op_member_access_from_pointer
id|next
op_assign
id|h
(braket
id|i
)braket
dot
id|next
suffix:semicolon
id|h
(braket
id|i
)braket
dot
id|next
op_assign
(paren
id|m_link_s
op_star
)paren
id|a
suffix:semicolon
r_break
suffix:semicolon
)brace
id|q-&gt;next
op_assign
id|q-&gt;next-&gt;next
suffix:semicolon
id|a
op_assign
id|a
op_amp
id|b
suffix:semicolon
id|s
op_lshift_assign
l_int|1
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
)brace
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|ncr53c8xx_lock
)paren
suffix:semicolon
DECL|function|__m_calloc2
r_static
r_void
op_star
id|__m_calloc2
c_func
(paren
id|m_pool_s
op_star
id|mp
comma
r_int
id|size
comma
r_char
op_star
id|name
comma
r_int
id|uflags
)paren
(brace
r_void
op_star
id|p
suffix:semicolon
id|p
op_assign
id|___m_alloc
c_func
(paren
id|mp
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_FLAGS
op_amp
id|DEBUG_ALLOC
)paren
id|printk
(paren
l_string|&quot;new %-10s[%4d] @%p.&bslash;n&quot;
comma
id|name
comma
id|size
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|uflags
op_amp
id|MEMO_WARN
)paren
id|printk
(paren
id|NAME53C8XX
l_string|&quot;: failed to allocate %s[%d]&bslash;n&quot;
comma
id|name
comma
id|size
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|macro|__m_calloc
mdefine_line|#define __m_calloc(mp, s, n)&t;__m_calloc2(mp, s, n, MEMO_WARN)
DECL|function|__m_free
r_static
r_void
id|__m_free
c_func
(paren
id|m_pool_s
op_star
id|mp
comma
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|DEBUG_FLAGS
op_amp
id|DEBUG_ALLOC
)paren
id|printk
(paren
l_string|&quot;freeing %-10s[%4d] @%p.&bslash;n&quot;
comma
id|name
comma
id|size
comma
id|ptr
)paren
suffix:semicolon
id|___m_free
c_func
(paren
id|mp
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * With pci bus iommu support, we use a default pool of unmapped memory &n; * for memory we donnot need to DMA from/to and one pool per pcidev for &n; * memory accessed by the PCI chip. `mp0&squot; is the default not DMAable pool.&n; */
DECL|function|___mp0_getp
r_static
id|m_addr_t
id|___mp0_getp
c_func
(paren
id|m_pool_s
op_star
id|mp
)paren
(brace
id|m_addr_t
id|m
op_assign
id|__get_free_pages
c_func
(paren
id|MEMO_GFP_FLAGS
comma
id|MEMO_PAGE_ORDER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
)paren
op_increment
id|mp-&gt;nump
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
DECL|function|___mp0_freep
r_static
r_void
id|___mp0_freep
c_func
(paren
id|m_pool_s
op_star
id|mp
comma
id|m_addr_t
id|m
)paren
(brace
id|free_pages
c_func
(paren
id|m
comma
id|MEMO_PAGE_ORDER
)paren
suffix:semicolon
op_decrement
id|mp-&gt;nump
suffix:semicolon
)brace
DECL|variable|mp0
r_static
id|m_pool_s
id|mp0
op_assign
(brace
l_int|NULL
comma
id|___mp0_getp
comma
id|___mp0_freep
)brace
suffix:semicolon
multiline_comment|/*&n; * DMAable pools.&n; */
multiline_comment|/*&n; * With pci bus iommu support, we maintain one pool per pcidev and a &n; * hashed reverse table for virtual to bus physical address translations.&n; */
DECL|function|___dma_getp
r_static
id|m_addr_t
id|___dma_getp
c_func
(paren
id|m_pool_s
op_star
id|mp
)paren
(brace
id|m_addr_t
id|vp
suffix:semicolon
id|m_vtob_s
op_star
id|vbp
suffix:semicolon
id|vbp
op_assign
id|__m_calloc
c_func
(paren
op_amp
id|mp0
comma
r_sizeof
(paren
op_star
id|vbp
)paren
comma
l_string|&quot;VTOB&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vbp
)paren
(brace
id|dma_addr_t
id|daddr
suffix:semicolon
id|vp
op_assign
(paren
id|m_addr_t
)paren
id|dma_alloc_coherent
c_func
(paren
id|mp-&gt;bush
comma
id|PAGE_SIZE
op_lshift
id|MEMO_PAGE_ORDER
comma
op_amp
id|daddr
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vp
)paren
(brace
r_int
id|hc
op_assign
id|VTOB_HASH_CODE
c_func
(paren
id|vp
)paren
suffix:semicolon
id|vbp-&gt;vaddr
op_assign
id|vp
suffix:semicolon
id|vbp-&gt;baddr
op_assign
id|daddr
suffix:semicolon
id|vbp-&gt;next
op_assign
id|mp-&gt;vtob
(braket
id|hc
)braket
suffix:semicolon
id|mp-&gt;vtob
(braket
id|hc
)braket
op_assign
id|vbp
suffix:semicolon
op_increment
id|mp-&gt;nump
suffix:semicolon
r_return
id|vp
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|vbp
)paren
id|__m_free
c_func
(paren
op_amp
id|mp0
comma
id|vbp
comma
r_sizeof
(paren
op_star
id|vbp
)paren
comma
l_string|&quot;VTOB&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|___dma_freep
r_static
r_void
id|___dma_freep
c_func
(paren
id|m_pool_s
op_star
id|mp
comma
id|m_addr_t
id|m
)paren
(brace
id|m_vtob_s
op_star
op_star
id|vbpp
comma
op_star
id|vbp
suffix:semicolon
r_int
id|hc
op_assign
id|VTOB_HASH_CODE
c_func
(paren
id|m
)paren
suffix:semicolon
id|vbpp
op_assign
op_amp
id|mp-&gt;vtob
(braket
id|hc
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|vbpp
op_logical_and
(paren
op_star
id|vbpp
)paren
op_member_access_from_pointer
id|vaddr
op_ne
id|m
)paren
id|vbpp
op_assign
op_amp
(paren
op_star
id|vbpp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
op_star
id|vbpp
)paren
(brace
id|vbp
op_assign
op_star
id|vbpp
suffix:semicolon
op_star
id|vbpp
op_assign
(paren
op_star
id|vbpp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|dma_free_coherent
c_func
(paren
id|mp-&gt;bush
comma
id|PAGE_SIZE
op_lshift
id|MEMO_PAGE_ORDER
comma
(paren
r_void
op_star
)paren
id|vbp-&gt;vaddr
comma
(paren
id|dma_addr_t
)paren
id|vbp-&gt;baddr
)paren
suffix:semicolon
id|__m_free
c_func
(paren
op_amp
id|mp0
comma
id|vbp
comma
r_sizeof
(paren
op_star
id|vbp
)paren
comma
l_string|&quot;VTOB&quot;
)paren
suffix:semicolon
op_decrement
id|mp-&gt;nump
suffix:semicolon
)brace
)brace
DECL|function|___get_dma_pool
r_static
r_inline
id|m_pool_s
op_star
id|___get_dma_pool
c_func
(paren
id|m_bush_t
id|bush
)paren
(brace
id|m_pool_s
op_star
id|mp
suffix:semicolon
r_for
c_loop
(paren
id|mp
op_assign
id|mp0.next
suffix:semicolon
id|mp
op_logical_and
id|mp-&gt;bush
op_ne
id|bush
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
suffix:semicolon
r_return
id|mp
suffix:semicolon
)brace
DECL|function|___cre_dma_pool
r_static
id|m_pool_s
op_star
id|___cre_dma_pool
c_func
(paren
id|m_bush_t
id|bush
)paren
(brace
id|m_pool_s
op_star
id|mp
suffix:semicolon
id|mp
op_assign
id|__m_calloc
c_func
(paren
op_amp
id|mp0
comma
r_sizeof
(paren
op_star
id|mp
)paren
comma
l_string|&quot;MPOOL&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
(brace
id|memset
c_func
(paren
id|mp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mp
)paren
)paren
suffix:semicolon
id|mp-&gt;bush
op_assign
id|bush
suffix:semicolon
id|mp-&gt;getp
op_assign
id|___dma_getp
suffix:semicolon
id|mp-&gt;freep
op_assign
id|___dma_freep
suffix:semicolon
id|mp-&gt;next
op_assign
id|mp0.next
suffix:semicolon
id|mp0.next
op_assign
id|mp
suffix:semicolon
)brace
r_return
id|mp
suffix:semicolon
)brace
DECL|function|___del_dma_pool
r_static
r_void
id|___del_dma_pool
c_func
(paren
id|m_pool_s
op_star
id|p
)paren
(brace
r_struct
id|m_pool
op_star
op_star
id|pp
op_assign
op_amp
id|mp0.next
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pp
op_logical_and
op_star
id|pp
op_ne
id|p
)paren
id|pp
op_assign
op_amp
(paren
op_star
id|pp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pp
)paren
(brace
op_star
id|pp
op_assign
(paren
op_star
id|pp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|__m_free
c_func
(paren
op_amp
id|mp0
comma
id|p
comma
r_sizeof
(paren
op_star
id|p
)paren
comma
l_string|&quot;MPOOL&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|__m_calloc_dma
r_static
r_void
op_star
id|__m_calloc_dma
c_func
(paren
id|m_bush_t
id|bush
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
id|u_long
id|flags
suffix:semicolon
r_struct
id|m_pool
op_star
id|mp
suffix:semicolon
r_void
op_star
id|m
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ncr53c8xx_lock
comma
id|flags
)paren
suffix:semicolon
id|mp
op_assign
id|___get_dma_pool
c_func
(paren
id|bush
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mp
)paren
id|mp
op_assign
id|___cre_dma_pool
c_func
(paren
id|bush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
id|m
op_assign
id|__m_calloc
c_func
(paren
id|mp
comma
id|size
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
op_logical_and
op_logical_neg
id|mp-&gt;nump
)paren
id|___del_dma_pool
c_func
(paren
id|mp
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ncr53c8xx_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
DECL|function|__m_free_dma
r_static
r_void
id|__m_free_dma
c_func
(paren
id|m_bush_t
id|bush
comma
r_void
op_star
id|m
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
id|u_long
id|flags
suffix:semicolon
r_struct
id|m_pool
op_star
id|mp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ncr53c8xx_lock
comma
id|flags
)paren
suffix:semicolon
id|mp
op_assign
id|___get_dma_pool
c_func
(paren
id|bush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
id|__m_free
c_func
(paren
id|mp
comma
id|m
comma
id|size
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
op_logical_and
op_logical_neg
id|mp-&gt;nump
)paren
id|___del_dma_pool
c_func
(paren
id|mp
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ncr53c8xx_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__vtobus
r_static
id|m_addr_t
id|__vtobus
c_func
(paren
id|m_bush_t
id|bush
comma
r_void
op_star
id|m
)paren
(brace
id|u_long
id|flags
suffix:semicolon
id|m_pool_s
op_star
id|mp
suffix:semicolon
r_int
id|hc
op_assign
id|VTOB_HASH_CODE
c_func
(paren
id|m
)paren
suffix:semicolon
id|m_vtob_s
op_star
id|vp
op_assign
l_int|NULL
suffix:semicolon
id|m_addr_t
id|a
op_assign
(paren
(paren
id|m_addr_t
)paren
id|m
)paren
op_amp
op_complement
id|MEMO_CLUSTER_MASK
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ncr53c8xx_lock
comma
id|flags
)paren
suffix:semicolon
id|mp
op_assign
id|___get_dma_pool
c_func
(paren
id|bush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
(brace
id|vp
op_assign
id|mp-&gt;vtob
(braket
id|hc
)braket
suffix:semicolon
r_while
c_loop
(paren
id|vp
op_logical_and
(paren
id|m_addr_t
)paren
id|vp-&gt;vaddr
op_ne
id|a
)paren
id|vp
op_assign
id|vp-&gt;next
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ncr53c8xx_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|vp
ques
c_cond
id|vp-&gt;baddr
op_plus
(paren
(paren
(paren
id|m_addr_t
)paren
id|m
)paren
op_minus
id|a
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|macro|_m_calloc_dma
mdefine_line|#define _m_calloc_dma(np, s, n)&t;&t;__m_calloc_dma(np-&gt;dev, s, n)
DECL|macro|_m_free_dma
mdefine_line|#define _m_free_dma(np, p, s, n)&t;__m_free_dma(np-&gt;dev, p, s, n)
DECL|macro|m_calloc_dma
mdefine_line|#define m_calloc_dma(s, n)&t;&t;_m_calloc_dma(np, s, n)
DECL|macro|m_free_dma
mdefine_line|#define m_free_dma(p, s, n)&t;&t;_m_free_dma(np, p, s, n)
DECL|macro|_vtobus
mdefine_line|#define _vtobus(np, p)&t;&t;&t;__vtobus(np-&gt;dev, p)
DECL|macro|vtobus
mdefine_line|#define vtobus(p)&t;&t;&t;_vtobus(np, p)
multiline_comment|/*&n; *  Deal with DMA mapping/unmapping.&n; */
multiline_comment|/* To keep track of the dma mapping (sg/single) that has been set */
DECL|macro|__data_mapped
mdefine_line|#define __data_mapped&t;SCp.phase
DECL|macro|__data_mapping
mdefine_line|#define __data_mapping&t;SCp.have_data_in
DECL|function|__unmap_scsi_data
r_static
r_void
id|__unmap_scsi_data
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_switch
c_cond
(paren
id|cmd-&gt;__data_mapped
)paren
(brace
r_case
l_int|2
suffix:colon
id|dma_unmap_sg
c_func
(paren
id|dev
comma
id|cmd-&gt;buffer
comma
id|cmd-&gt;use_sg
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|dma_unmap_single
c_func
(paren
id|dev
comma
id|cmd-&gt;__data_mapping
comma
id|cmd-&gt;request_bufflen
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cmd-&gt;__data_mapped
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|__map_scsi_single_data
r_static
id|u_long
id|__map_scsi_single_data
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
id|dma_addr_t
id|mapping
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;request_bufflen
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|mapping
op_assign
id|dma_map_single
c_func
(paren
id|dev
comma
id|cmd-&gt;request_buffer
comma
id|cmd-&gt;request_bufflen
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
id|cmd-&gt;__data_mapped
op_assign
l_int|1
suffix:semicolon
id|cmd-&gt;__data_mapping
op_assign
id|mapping
suffix:semicolon
r_return
id|mapping
suffix:semicolon
)brace
DECL|function|__map_scsi_sg_data
r_static
r_int
id|__map_scsi_sg_data
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_int
id|use_sg
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;use_sg
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|use_sg
op_assign
id|dma_map_sg
c_func
(paren
id|dev
comma
id|cmd-&gt;buffer
comma
id|cmd-&gt;use_sg
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
id|cmd-&gt;__data_mapped
op_assign
l_int|2
suffix:semicolon
id|cmd-&gt;__data_mapping
op_assign
id|use_sg
suffix:semicolon
r_return
id|use_sg
suffix:semicolon
)brace
DECL|macro|unmap_scsi_data
mdefine_line|#define unmap_scsi_data(np, cmd)&t;__unmap_scsi_data(np-&gt;dev, cmd)
DECL|macro|map_scsi_single_data
mdefine_line|#define map_scsi_single_data(np, cmd)&t;__map_scsi_single_data(np-&gt;dev, cmd)
DECL|macro|map_scsi_sg_data
mdefine_line|#define map_scsi_sg_data(np, cmd)&t;__map_scsi_sg_data(np-&gt;dev, cmd)
multiline_comment|/*==========================================================&n;**&n;**&t;Driver setup.&n;**&n;**&t;This structure is initialized from linux config &n;**&t;options. It can be overridden at boot-up by the boot &n;**&t;command line.&n;**&n;**==========================================================&n;*/
r_static
r_struct
id|ncr_driver_setup
DECL|variable|driver_setup
id|driver_setup
op_assign
id|SCSI_NCR_DRIVER_SETUP
suffix:semicolon
macro_line|#ifdef&t;SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
r_static
r_struct
id|ncr_driver_setup
DECL|variable|__initdata
id|driver_safe_setup
id|__initdata
op_assign
id|SCSI_NCR_DRIVER_SAFE_SETUP
suffix:semicolon
macro_line|#endif
DECL|macro|initverbose
mdefine_line|#define initverbose (driver_setup.verbose)
DECL|macro|bootverbose
mdefine_line|#define bootverbose (np-&gt;verbose)
multiline_comment|/*===================================================================&n;**&n;**&t;Driver setup from the boot command line&n;**&n;**===================================================================&n;*/
macro_line|#ifdef MODULE
DECL|macro|ARG_SEP
mdefine_line|#define&t;ARG_SEP&t;&squot; &squot;
macro_line|#else
DECL|macro|ARG_SEP
mdefine_line|#define&t;ARG_SEP&t;&squot;,&squot;
macro_line|#endif
DECL|macro|OPT_TAGS
mdefine_line|#define OPT_TAGS&t;&t;1
DECL|macro|OPT_MASTER_PARITY
mdefine_line|#define OPT_MASTER_PARITY&t;2
DECL|macro|OPT_SCSI_PARITY
mdefine_line|#define OPT_SCSI_PARITY&t;&t;3
DECL|macro|OPT_DISCONNECTION
mdefine_line|#define OPT_DISCONNECTION&t;4
DECL|macro|OPT_SPECIAL_FEATURES
mdefine_line|#define OPT_SPECIAL_FEATURES&t;5
DECL|macro|OPT_UNUSED_1
mdefine_line|#define OPT_UNUSED_1&t;&t;6
DECL|macro|OPT_FORCE_SYNC_NEGO
mdefine_line|#define OPT_FORCE_SYNC_NEGO&t;7
DECL|macro|OPT_REVERSE_PROBE
mdefine_line|#define OPT_REVERSE_PROBE&t;8
DECL|macro|OPT_DEFAULT_SYNC
mdefine_line|#define OPT_DEFAULT_SYNC&t;9
DECL|macro|OPT_VERBOSE
mdefine_line|#define OPT_VERBOSE&t;&t;10
DECL|macro|OPT_DEBUG
mdefine_line|#define OPT_DEBUG&t;&t;11
DECL|macro|OPT_BURST_MAX
mdefine_line|#define OPT_BURST_MAX&t;&t;12
DECL|macro|OPT_LED_PIN
mdefine_line|#define OPT_LED_PIN&t;&t;13
DECL|macro|OPT_MAX_WIDE
mdefine_line|#define OPT_MAX_WIDE&t;&t;14
DECL|macro|OPT_SETTLE_DELAY
mdefine_line|#define OPT_SETTLE_DELAY&t;15
DECL|macro|OPT_DIFF_SUPPORT
mdefine_line|#define OPT_DIFF_SUPPORT&t;16
DECL|macro|OPT_IRQM
mdefine_line|#define OPT_IRQM&t;&t;17
DECL|macro|OPT_PCI_FIX_UP
mdefine_line|#define OPT_PCI_FIX_UP&t;&t;18
DECL|macro|OPT_BUS_CHECK
mdefine_line|#define OPT_BUS_CHECK&t;&t;19
DECL|macro|OPT_OPTIMIZE
mdefine_line|#define OPT_OPTIMIZE&t;&t;20
DECL|macro|OPT_RECOVERY
mdefine_line|#define OPT_RECOVERY&t;&t;21
DECL|macro|OPT_SAFE_SETUP
mdefine_line|#define OPT_SAFE_SETUP&t;&t;22
DECL|macro|OPT_USE_NVRAM
mdefine_line|#define OPT_USE_NVRAM&t;&t;23
DECL|macro|OPT_EXCLUDE
mdefine_line|#define OPT_EXCLUDE&t;&t;24
DECL|macro|OPT_HOST_ID
mdefine_line|#define OPT_HOST_ID&t;&t;25
macro_line|#ifdef SCSI_NCR_IARB_SUPPORT
DECL|macro|OPT_IARB
mdefine_line|#define OPT_IARB&t;&t;26
macro_line|#endif
DECL|variable|__initdata
r_static
r_char
id|setup_token
(braket
)braket
id|__initdata
op_assign
l_string|&quot;tags:&quot;
l_string|&quot;mpar:&quot;
l_string|&quot;spar:&quot;
l_string|&quot;disc:&quot;
l_string|&quot;specf:&quot;
l_string|&quot;ultra:&quot;
l_string|&quot;fsn:&quot;
l_string|&quot;revprob:&quot;
l_string|&quot;sync:&quot;
l_string|&quot;verb:&quot;
l_string|&quot;debug:&quot;
l_string|&quot;burst:&quot;
l_string|&quot;led:&quot;
l_string|&quot;wide:&quot;
l_string|&quot;settle:&quot;
l_string|&quot;diff:&quot;
l_string|&quot;irqm:&quot;
l_string|&quot;pcifix:&quot;
l_string|&quot;buschk:&quot;
l_string|&quot;optim:&quot;
l_string|&quot;recovery:&quot;
l_string|&quot;safe:&quot;
l_string|&quot;nvram:&quot;
l_string|&quot;excl:&quot;
l_string|&quot;hostid:&quot;
macro_line|#ifdef SCSI_NCR_IARB_SUPPORT
l_string|&quot;iarb:&quot;
macro_line|#endif
suffix:semicolon
multiline_comment|/* DONNOT REMOVE THIS &squot;;&squot; */
macro_line|#ifdef MODULE
DECL|macro|ARG_SEP
mdefine_line|#define&t;ARG_SEP&t;&squot; &squot;
macro_line|#else
DECL|macro|ARG_SEP
mdefine_line|#define&t;ARG_SEP&t;&squot;,&squot;
macro_line|#endif
DECL|function|get_setup_token
r_static
r_int
id|__init
id|get_setup_token
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_char
op_star
id|cur
op_assign
id|setup_token
suffix:semicolon
r_char
op_star
id|pc
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
op_logical_and
(paren
id|pc
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
op_increment
id|pc
suffix:semicolon
op_increment
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p
comma
id|cur
comma
id|pc
op_minus
id|cur
)paren
)paren
r_return
id|i
suffix:semicolon
id|cur
op_assign
id|pc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sym53c8xx__setup
r_static
r_int
id|__init
id|sym53c8xx__setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
macro_line|#ifdef SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
r_char
op_star
id|cur
op_assign
id|str
suffix:semicolon
r_char
op_star
id|pc
comma
op_star
id|pv
suffix:semicolon
r_int
id|i
comma
id|val
comma
id|c
suffix:semicolon
r_int
id|xi
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
op_logical_and
(paren
id|pc
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;:&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|pe
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
id|pv
op_assign
id|pc
suffix:semicolon
id|c
op_assign
op_star
op_increment
id|pv
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;n&squot;
)paren
id|val
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;y&squot;
)paren
id|val
op_assign
l_int|1
suffix:semicolon
r_else
id|val
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|pv
comma
op_amp
id|pe
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|get_setup_token
c_func
(paren
id|cur
)paren
)paren
(brace
r_case
id|OPT_TAGS
suffix:colon
id|driver_setup.default_tags
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
id|pe
op_logical_and
op_star
id|pe
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pe
op_logical_and
op_star
id|pe
op_ne
id|ARG_SEP
op_logical_and
id|i
OL
r_sizeof
(paren
id|driver_setup.tag_ctrl
)paren
op_minus
l_int|1
)paren
(brace
id|driver_setup.tag_ctrl
(braket
id|i
op_increment
)braket
op_assign
op_star
id|pe
op_increment
suffix:semicolon
)brace
id|driver_setup.tag_ctrl
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|OPT_MASTER_PARITY
suffix:colon
id|driver_setup.master_parity
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_SCSI_PARITY
suffix:colon
id|driver_setup.scsi_parity
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_DISCONNECTION
suffix:colon
id|driver_setup.disconnection
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_SPECIAL_FEATURES
suffix:colon
id|driver_setup.special_features
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_FORCE_SYNC_NEGO
suffix:colon
id|driver_setup.force_sync_nego
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_REVERSE_PROBE
suffix:colon
id|driver_setup.reverse_probe
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_DEFAULT_SYNC
suffix:colon
id|driver_setup.default_sync
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_VERBOSE
suffix:colon
id|driver_setup.verbose
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_DEBUG
suffix:colon
id|driver_setup.debug
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_BURST_MAX
suffix:colon
id|driver_setup.burst_max
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_LED_PIN
suffix:colon
id|driver_setup.led_pin
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_MAX_WIDE
suffix:colon
id|driver_setup.max_wide
op_assign
id|val
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_SETTLE_DELAY
suffix:colon
id|driver_setup.settle_delay
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_DIFF_SUPPORT
suffix:colon
id|driver_setup.diff_support
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_IRQM
suffix:colon
id|driver_setup.irqm
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_PCI_FIX_UP
suffix:colon
id|driver_setup.pci_fix_up
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_BUS_CHECK
suffix:colon
id|driver_setup.bus_check
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_OPTIMIZE
suffix:colon
id|driver_setup.optimize
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_RECOVERY
suffix:colon
id|driver_setup.recovery
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_USE_NVRAM
suffix:colon
id|driver_setup.use_nvram
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_SAFE_SETUP
suffix:colon
id|memcpy
c_func
(paren
op_amp
id|driver_setup
comma
op_amp
id|driver_safe_setup
comma
r_sizeof
(paren
id|driver_setup
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_EXCLUDE
suffix:colon
r_if
c_cond
(paren
id|xi
OL
id|SCSI_NCR_MAX_EXCLUDES
)paren
id|driver_setup.excludes
(braket
id|xi
op_increment
)braket
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPT_HOST_ID
suffix:colon
id|driver_setup.host_id
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef SCSI_NCR_IARB_SUPPORT
r_case
id|OPT_IARB
suffix:colon
id|driver_setup.iarb
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;sym53c8xx_setup: unexpected boot option &squot;%.*s&squot; ignored&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|pc
op_minus
id|cur
op_plus
l_int|1
)paren
comma
id|cur
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cur
op_assign
id|strchr
c_func
(paren
id|cur
comma
id|ARG_SEP
)paren
)paren
op_ne
l_int|NULL
)paren
op_increment
id|cur
suffix:semicolon
)brace
macro_line|#endif /* SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*===================================================================&n;**&n;**&t;Get device queue depth from boot command line.&n;**&n;**===================================================================&n;*/
DECL|macro|DEF_DEPTH
mdefine_line|#define DEF_DEPTH&t;(driver_setup.default_tags)
DECL|macro|ALL_TARGETS
mdefine_line|#define ALL_TARGETS&t;-2
DECL|macro|NO_TARGET
mdefine_line|#define NO_TARGET&t;-1
DECL|macro|ALL_LUNS
mdefine_line|#define ALL_LUNS&t;-2
DECL|macro|NO_LUN
mdefine_line|#define NO_LUN&t;&t;-1
DECL|function|device_queue_depth
r_static
r_int
id|device_queue_depth
c_func
(paren
r_int
id|unit
comma
r_int
id|target
comma
r_int
id|lun
)paren
(brace
r_int
id|c
comma
id|h
comma
id|t
comma
id|u
comma
id|v
suffix:semicolon
r_char
op_star
id|p
op_assign
id|driver_setup.tag_ctrl
suffix:semicolon
r_char
op_star
id|ep
suffix:semicolon
id|h
op_assign
op_minus
l_int|1
suffix:semicolon
id|t
op_assign
id|NO_TARGET
suffix:semicolon
id|u
op_assign
id|NO_LUN
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_int|0
)paren
(brace
id|v
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|ep
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;/&squot;
suffix:colon
op_increment
id|h
suffix:semicolon
id|t
op_assign
id|ALL_TARGETS
suffix:semicolon
id|u
op_assign
id|ALL_LUNS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
r_if
c_cond
(paren
id|t
op_ne
id|target
)paren
id|t
op_assign
(paren
id|target
op_eq
id|v
)paren
ques
c_cond
id|v
suffix:colon
id|NO_TARGET
suffix:semicolon
id|u
op_assign
id|ALL_LUNS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;u&squot;
suffix:colon
r_if
c_cond
(paren
id|u
op_ne
id|lun
)paren
id|u
op_assign
(paren
id|lun
op_eq
id|v
)paren
ques
c_cond
id|v
suffix:colon
id|NO_LUN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;q&squot;
suffix:colon
r_if
c_cond
(paren
id|h
op_eq
id|unit
op_logical_and
(paren
id|t
op_eq
id|ALL_TARGETS
op_logical_or
id|t
op_eq
id|target
)paren
op_logical_and
(paren
id|u
op_eq
id|ALL_LUNS
op_logical_or
id|u
op_eq
id|lun
)paren
)paren
r_return
id|v
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
id|t
op_assign
id|ALL_TARGETS
suffix:semicolon
id|u
op_assign
id|ALL_LUNS
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|p
op_assign
id|ep
suffix:semicolon
)brace
r_return
id|DEF_DEPTH
suffix:semicolon
)brace
eof
