multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_defs.h&gt;
multiline_comment|/*&n; * functions&n; */
r_int
id|pcibr_ate_alloc
c_func
(paren
id|pcibr_soft_t
comma
r_int
comma
r_struct
id|resource
op_star
)paren
suffix:semicolon
r_void
id|pcibr_ate_free
c_func
(paren
id|pcibr_soft_t
comma
r_int
comma
r_int
comma
r_struct
id|resource
op_star
)paren
suffix:semicolon
id|bridge_ate_t
id|pcibr_flags_to_ate
c_func
(paren
id|pcibr_soft_t
comma
r_int
)paren
suffix:semicolon
id|bridge_ate_p
id|pcibr_ate_addr
c_func
(paren
id|pcibr_soft_t
comma
r_int
)paren
suffix:semicolon
r_void
id|ate_write
c_func
(paren
id|pcibr_soft_t
comma
r_int
comma
r_int
comma
id|bridge_ate_t
)paren
suffix:semicolon
DECL|variable|pcibr_invalidate_ate
r_int
id|pcibr_invalidate_ate
suffix:semicolon
multiline_comment|/* by default don&squot;t invalidate ATE on free */
multiline_comment|/*&n; * Allocate &quot;count&quot; contiguous Bridge Address Translation Entries&n; * on the specified bridge to be used for PCI to XTALK mappings.&n; * Indices in rm map range from 1..num_entries.  Indicies returned&n; * to caller range from 0..num_entries-1.&n; *&n; * Return the start index on success, -1 on failure.&n; */
r_int
DECL|function|pcibr_ate_alloc
id|pcibr_ate_alloc
c_func
(paren
id|pcibr_soft_t
id|pcibr_soft
comma
r_int
id|count
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flag
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
id|flag
op_assign
id|pcibr_lock
c_func
(paren
id|pcibr_soft
)paren
suffix:semicolon
id|status
op_assign
id|allocate_resource
c_func
(paren
op_amp
id|pcibr_soft-&gt;bs_int_ate_resource
comma
id|res
comma
id|count
comma
id|pcibr_soft-&gt;bs_int_ate_resource.start
comma
id|pcibr_soft-&gt;bs_int_ate_resource.end
comma
l_int|1
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* Failed to allocate */
id|pcibr_unlock
c_func
(paren
id|pcibr_soft
comma
id|flag
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Save the resource for freeing */
id|pcibr_unlock
c_func
(paren
id|pcibr_soft
comma
id|flag
)paren
suffix:semicolon
r_return
id|res-&gt;start
suffix:semicolon
)brace
r_void
DECL|function|pcibr_ate_free
id|pcibr_ate_free
c_func
(paren
id|pcibr_soft_t
id|pcibr_soft
comma
r_int
id|index
comma
r_int
id|count
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
id|bridge_ate_t
id|ate
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|pcibr_invalidate_ate
)paren
(brace
multiline_comment|/* For debugging purposes, clear the valid bit in the ATE */
id|ate
op_assign
op_star
id|pcibr_ate_addr
c_func
(paren
id|pcibr_soft
comma
id|index
)paren
suffix:semicolon
id|ate_write
c_func
(paren
id|pcibr_soft
comma
id|index
comma
id|count
comma
(paren
id|ate
op_amp
op_complement
id|ATE_V
)paren
)paren
suffix:semicolon
)brace
id|flags
op_assign
id|pcibr_lock
c_func
(paren
id|pcibr_soft
)paren
suffix:semicolon
id|status
op_assign
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
id|pcibr_unlock
c_func
(paren
id|pcibr_soft
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ouch .. */
)brace
multiline_comment|/*&n; * Convert PCI-generic software flags and Bridge-specific software flags&n; * into Bridge-specific Address Translation Entry attribute bits.&n; */
id|bridge_ate_t
DECL|function|pcibr_flags_to_ate
id|pcibr_flags_to_ate
c_func
(paren
id|pcibr_soft_t
id|pcibr_soft
comma
r_int
id|flags
)paren
(brace
id|bridge_ate_t
id|attributes
suffix:semicolon
multiline_comment|/* default if nothing specified:&n;     * NOBARRIER&n;     * NOPREFETCH&n;     * NOPRECISE&n;     * COHERENT&n;     * Plus the valid bit&n;     */
id|attributes
op_assign
id|ATE_CO
op_or
id|ATE_V
suffix:semicolon
multiline_comment|/* Generic macro flags&n;     */
r_if
c_cond
(paren
id|flags
op_amp
id|PCIIO_DMA_DATA
)paren
(brace
multiline_comment|/* standard data channel */
id|attributes
op_and_assign
op_complement
id|ATE_BAR
suffix:semicolon
multiline_comment|/* no barrier */
id|attributes
op_or_assign
id|ATE_PREF
suffix:semicolon
multiline_comment|/* prefetch on */
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|PCIIO_DMA_CMD
)paren
(brace
multiline_comment|/* standard command channel */
id|attributes
op_or_assign
id|ATE_BAR
suffix:semicolon
multiline_comment|/* barrier bit on */
id|attributes
op_and_assign
op_complement
id|ATE_PREF
suffix:semicolon
multiline_comment|/* disable prefetch */
)brace
multiline_comment|/* Generic detail flags&n;     */
r_if
c_cond
(paren
id|flags
op_amp
id|PCIIO_PREFETCH
)paren
id|attributes
op_or_assign
id|ATE_PREF
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCIIO_NOPREFETCH
)paren
id|attributes
op_and_assign
op_complement
id|ATE_PREF
suffix:semicolon
multiline_comment|/* Provider-specific flags&n;     */
r_if
c_cond
(paren
id|flags
op_amp
id|PCIBR_BARRIER
)paren
id|attributes
op_or_assign
id|ATE_BAR
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCIBR_NOBARRIER
)paren
id|attributes
op_and_assign
op_complement
id|ATE_BAR
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCIBR_PREFETCH
)paren
id|attributes
op_or_assign
id|ATE_PREF
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCIBR_NOPREFETCH
)paren
id|attributes
op_and_assign
op_complement
id|ATE_PREF
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCIBR_PRECISE
)paren
id|attributes
op_or_assign
id|ATE_PREC
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCIBR_NOPRECISE
)paren
id|attributes
op_and_assign
op_complement
id|ATE_PREC
suffix:semicolon
multiline_comment|/* In PCI-X mode, Prefetch &amp; Precise not supported */
r_if
c_cond
(paren
id|IS_PCIX
c_func
(paren
id|pcibr_soft
)paren
)paren
(brace
id|attributes
op_and_assign
op_complement
(paren
id|ATE_PREC
op_or
id|ATE_PREF
)paren
suffix:semicolon
)brace
r_return
(paren
id|attributes
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup an Address Translation Entry as specified.  Use either the Bridge&n; * internal maps or the external map RAM, as appropriate.&n; */
id|bridge_ate_p
DECL|function|pcibr_ate_addr
id|pcibr_ate_addr
c_func
(paren
id|pcibr_soft_t
id|pcibr_soft
comma
r_int
id|ate_index
)paren
(brace
r_if
c_cond
(paren
id|ate_index
OL
id|pcibr_soft-&gt;bs_int_ate_size
)paren
(brace
r_return
(paren
id|pcireg_int_ate_addr
c_func
(paren
id|pcibr_soft
comma
id|ate_index
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;pcibr_ate_addr(): INVALID ate_index 0x%x&quot;
comma
id|ate_index
)paren
suffix:semicolon
r_return
(paren
id|bridge_ate_p
)paren
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write the ATE.&n; */
r_void
DECL|function|ate_write
id|ate_write
c_func
(paren
id|pcibr_soft_t
id|pcibr_soft
comma
r_int
id|ate_index
comma
r_int
id|count
comma
id|bridge_ate_t
id|ate
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ate_index
OL
id|pcibr_soft-&gt;bs_int_ate_size
)paren
(brace
id|pcireg_int_ate_set
c_func
(paren
id|pcibr_soft
comma
id|ate_index
comma
id|ate
)paren
suffix:semicolon
id|PCIBR_DEBUG
c_func
(paren
(paren
id|PCIBR_DEBUG_DMAMAP
comma
id|pcibr_soft-&gt;bs_vhdl
comma
l_string|&quot;ate_write(): ate_index=0x%x, ate=0x%lx&bslash;n&quot;
comma
id|ate_index
comma
(paren
r_uint64
)paren
id|ate
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ate_write(): INVALID ate_index 0x%x&quot;
comma
id|ate_index
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ate_index
op_increment
suffix:semicolon
id|ate
op_add_assign
id|IOPGSIZE
suffix:semicolon
)brace
id|pcireg_tflush_get
c_func
(paren
id|pcibr_soft
)paren
suffix:semicolon
multiline_comment|/* wait until Bridge PIO complete */
)brace
eof
