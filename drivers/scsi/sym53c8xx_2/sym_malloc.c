multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifdef __FreeBSD__
macro_line|#include &lt;dev/sym/sym_glue.h&gt;
macro_line|#else
macro_line|#include &quot;sym_glue.h&quot;
macro_line|#endif
multiline_comment|/*&n; *  Simple power of two buddy-like generic allocator.&n; *  Provides naturally aligned memory chunks.&n; *&n; *  This simple code is not intended to be fast, but to &n; *  provide power of 2 aligned memory allocations.&n; *  Since the SCRIPTS processor only supplies 8 bit arithmetic, &n; *  this allocator allows simple and fast address calculations  &n; *  from the SCRIPTS code. In addition, cache line alignment &n; *  is guaranteed for power of 2 cache line size.&n; *&n; *  This allocator has been developped for the Linux sym53c8xx  &n; *  driver, since this O/S does not provide naturally aligned &n; *  allocations.&n; *  It has the advantage of allowing the driver to use private &n; *  pages of memory that will be useful if we ever need to deal &n; *  with IO MMUs for PCI.&n; */
DECL|function|___sym_malloc
r_static
r_void
op_star
id|___sym_malloc
c_func
(paren
id|m_pool_p
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
id|SYM_MEM_SHIFT
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
id|m_addr_t
id|a
suffix:semicolon
id|m_link_p
id|h
op_assign
id|mp-&gt;h
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|SYM_MEM_CLUSTER_SIZE
)paren
r_return
l_int|0
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
id|SYM_MEM_CLUSTER_SIZE
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
id|m_link_p
)paren
id|M_GET_MEM_CLUSTER
c_func
(paren
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
l_int|0
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
id|m_link_p
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
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printf
c_func
(paren
l_string|&quot;___sym_malloc(%d) = %p&bslash;n&quot;
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
multiline_comment|/*&n; *  Counter-part of the generic allocator.&n; */
DECL|function|___sym_mfree
r_static
r_void
id|___sym_mfree
c_func
(paren
id|m_pool_p
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
id|SYM_MEM_SHIFT
)paren
suffix:semicolon
id|m_link_p
id|q
suffix:semicolon
id|m_addr_t
id|a
comma
id|b
suffix:semicolon
id|m_link_p
id|h
op_assign
id|mp-&gt;h
suffix:semicolon
macro_line|#ifdef DEBUG
id|printf
c_func
(paren
l_string|&quot;___sym_mfree(%p, %d)&bslash;n&quot;
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
id|SYM_MEM_CLUSTER_SIZE
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
r_if
c_cond
(paren
id|s
op_eq
id|SYM_MEM_CLUSTER_SIZE
)paren
(brace
macro_line|#ifdef SYM_MEM_FREE_UNUSED
id|M_FREE_MEM_CLUSTER
c_func
(paren
id|a
)paren
suffix:semicolon
macro_line|#else
(paren
(paren
id|m_link_p
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
id|m_link_p
)paren
id|a
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
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
id|m_link_p
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
id|m_link_p
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
id|m_link_p
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
multiline_comment|/*&n; *  Verbose and zeroing allocator that wrapps to the generic allocator.&n; */
DECL|function|__sym_calloc2
r_static
r_void
op_star
id|__sym_calloc2
c_func
(paren
id|m_pool_p
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
id|___sym_malloc
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
(brace
id|printf
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
)brace
r_if
c_cond
(paren
id|p
)paren
id|bzero
c_func
(paren
id|p
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
id|SYM_MEM_WARN
)paren
id|printf
(paren
l_string|&quot;__sym_calloc2: failed to allocate %s[%d]&bslash;n&quot;
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
DECL|macro|__sym_calloc
mdefine_line|#define __sym_calloc(mp, s, n)&t;__sym_calloc2(mp, s, n, SYM_MEM_WARN)
multiline_comment|/*&n; *  Its counter-part.&n; */
DECL|function|__sym_mfree
r_static
r_void
id|__sym_mfree
c_func
(paren
id|m_pool_p
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
id|printf
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
id|___sym_mfree
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
multiline_comment|/*&n; *  Default memory pool we donnot need to involve in DMA.&n; *&n; *  If DMA abtraction is not needed, the generic allocator &n; *  calls directly some kernel allocator.&n; *&n; *  With DMA abstraction, we use functions (methods), to &n; *  distinguish between non DMAable memory and DMAable memory.&n; */
macro_line|#ifndef&t;SYM_OPT_BUS_DMA_ABSTRACTION
DECL|variable|mp0
r_static
r_struct
id|sym_m_pool
id|mp0
suffix:semicolon
macro_line|#else
DECL|function|___mp0_get_mem_cluster
r_static
id|m_addr_t
id|___mp0_get_mem_cluster
c_func
(paren
id|m_pool_p
id|mp
)paren
(brace
id|m_addr_t
id|m
op_assign
(paren
id|m_addr_t
)paren
id|sym_get_mem_cluster
c_func
(paren
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
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
DECL|function|___mp0_free_mem_cluster
r_static
r_void
id|___mp0_free_mem_cluster
c_func
(paren
id|m_pool_p
id|mp
comma
id|m_addr_t
id|m
)paren
(brace
id|sym_free_mem_cluster
c_func
(paren
id|m
)paren
suffix:semicolon
op_decrement
id|mp-&gt;nump
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
DECL|variable|mp0
r_static
r_struct
id|sym_m_pool
id|mp0
op_assign
(brace
l_int|0
comma
id|___mp0_get_mem_cluster
comma
id|___mp0_free_mem_cluster
)brace
suffix:semicolon
macro_line|#else
DECL|variable|mp0
r_static
r_struct
id|sym_m_pool
id|mp0
op_assign
(brace
l_int|0
comma
id|___mp0_get_mem_cluster
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* SYM_OPT_BUS_DMA_ABSTRACTION */
multiline_comment|/*&n; * Actual memory allocation routine for non-DMAed memory.&n; */
DECL|function|sym_calloc_unlocked
r_void
op_star
id|sym_calloc_unlocked
c_func
(paren
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
r_void
op_star
id|m
suffix:semicolon
id|m
op_assign
id|__sym_calloc
c_func
(paren
op_amp
id|mp0
comma
id|size
comma
id|name
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
multiline_comment|/*&n; *  Its counter-part.&n; */
DECL|function|sym_mfree_unlocked
r_void
id|sym_mfree_unlocked
c_func
(paren
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
id|__sym_mfree
c_func
(paren
op_amp
id|mp0
comma
id|ptr
comma
id|size
comma
id|name
)paren
suffix:semicolon
)brace
macro_line|#ifdef&t;SYM_OPT_BUS_DMA_ABSTRACTION
multiline_comment|/*&n; *  Methods that maintains DMAable pools according to user allocations.&n; *  New pools are created on the fly when a new pool id is provided.&n; *  They are deleted on the fly when they get emptied.&n; */
multiline_comment|/* Get a memory cluster that matches the DMA contraints of a given pool */
DECL|function|___get_dma_mem_cluster
r_static
id|m_addr_t
id|___get_dma_mem_cluster
c_func
(paren
id|m_pool_p
id|mp
)paren
(brace
id|m_vtob_p
id|vbp
suffix:semicolon
id|m_addr_t
id|vaddr
suffix:semicolon
id|vbp
op_assign
id|__sym_calloc
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
op_logical_neg
id|vbp
)paren
r_goto
id|out_err
suffix:semicolon
id|vaddr
op_assign
id|sym_m_get_dma_mem_cluster
c_func
(paren
id|mp
comma
id|vbp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vaddr
)paren
(brace
r_int
id|hc
op_assign
id|VTOB_HASH_CODE
c_func
(paren
id|vaddr
)paren
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
(paren
id|m_addr_t
)paren
id|vaddr
suffix:semicolon
)brace
r_return
id|vaddr
suffix:semicolon
id|out_err
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
multiline_comment|/* Free a memory cluster and associated resources for DMA */
DECL|function|___free_dma_mem_cluster
r_static
r_void
id|___free_dma_mem_cluster
c_func
(paren
id|m_pool_p
id|mp
comma
id|m_addr_t
id|m
)paren
(brace
id|m_vtob_p
op_star
id|vbpp
comma
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
id|sym_m_free_dma_mem_cluster
c_func
(paren
id|mp
comma
id|vbp
)paren
suffix:semicolon
id|__sym_mfree
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
macro_line|#endif
multiline_comment|/* Fetch the memory pool for a given pool id (i.e. DMA constraints) */
DECL|function|___get_dma_pool
r_static
id|__inline
id|m_pool_p
id|___get_dma_pool
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
)paren
(brace
id|m_pool_p
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
op_logical_neg
id|sym_m_pool_match
c_func
(paren
id|mp-&gt;dev_dmat
comma
id|dev_dmat
)paren
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
multiline_comment|/* Create a new memory DMAable pool (when fetch failed) */
DECL|function|___cre_dma_pool
r_static
id|m_pool_p
id|___cre_dma_pool
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
)paren
(brace
id|m_pool_p
id|mp
op_assign
l_int|0
suffix:semicolon
id|mp
op_assign
id|__sym_calloc
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
id|mp-&gt;dev_dmat
op_assign
id|dev_dmat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym_m_create_dma_mem_tag
c_func
(paren
id|mp
)paren
)paren
(brace
id|mp-&gt;get_mem_cluster
op_assign
id|___get_dma_mem_cluster
suffix:semicolon
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
id|mp-&gt;free_mem_cluster
op_assign
id|___free_dma_mem_cluster
suffix:semicolon
macro_line|#endif
id|mp-&gt;next
op_assign
id|mp0.next
suffix:semicolon
id|mp0.next
op_assign
id|mp
suffix:semicolon
r_return
id|mp
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mp
)paren
id|__sym_mfree
c_func
(paren
op_amp
id|mp0
comma
id|mp
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
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
multiline_comment|/* Destroy a DMAable memory pool (when got emptied) */
DECL|function|___del_dma_pool
r_static
r_void
id|___del_dma_pool
c_func
(paren
id|m_pool_p
id|p
)paren
(brace
id|m_pool_p
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
id|sym_m_delete_dma_mem_tag
c_func
(paren
id|p
)paren
suffix:semicolon
id|__sym_mfree
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
macro_line|#endif
multiline_comment|/*&n; *  Actual allocator for DMAable memory.&n; */
DECL|function|__sym_calloc_dma_unlocked
r_void
op_star
id|__sym_calloc_dma_unlocked
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
id|m_pool_p
id|mp
suffix:semicolon
r_void
op_star
id|m
op_assign
l_int|0
suffix:semicolon
id|mp
op_assign
id|___get_dma_pool
c_func
(paren
id|dev_dmat
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
id|dev_dmat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
id|m
op_assign
id|__sym_calloc
c_func
(paren
id|mp
comma
id|size
comma
id|name
)paren
suffix:semicolon
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
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
macro_line|#endif
r_return
id|m
suffix:semicolon
)brace
multiline_comment|/*&n; *  Its counter-part.&n; */
r_void
DECL|function|__sym_mfree_dma_unlocked
id|__sym_mfree_dma_unlocked
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
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
id|m_pool_p
id|mp
suffix:semicolon
id|mp
op_assign
id|___get_dma_pool
c_func
(paren
id|dev_dmat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
id|__sym_mfree
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
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
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
macro_line|#endif
)brace
multiline_comment|/*&n; *  Actual virtual to bus physical address translator &n; *  for 32 bit addressable DMAable memory.&n; */
DECL|function|__vtobus_unlocked
id|u32
id|__vtobus_unlocked
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_void
op_star
id|m
)paren
(brace
id|m_pool_p
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
id|m_vtob_p
id|vp
op_assign
l_int|0
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
id|SYM_MEM_CLUSTER_MASK
suffix:semicolon
id|mp
op_assign
id|___get_dma_pool
c_func
(paren
id|dev_dmat
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
r_if
c_cond
(paren
op_logical_neg
id|vp
)paren
id|panic
c_func
(paren
l_string|&quot;sym: VTOBUS FAILED!&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|u32
)paren
(paren
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
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* SYM_OPT_BUS_DMA_ABSTRACTION */
eof
