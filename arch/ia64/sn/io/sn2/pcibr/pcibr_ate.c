multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_defs.h&gt;
macro_line|#include &lt;asm/sn/prio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/ioc3.h&gt;
macro_line|#include &lt;asm/sn/eeprom.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#ifdef __ia64
r_uint64
id|atealloc
c_func
(paren
r_struct
id|map
op_star
id|mp
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|atefree
c_func
(paren
r_struct
id|map
op_star
id|mp
comma
r_int
id|size
comma
r_uint64
id|a
)paren
suffix:semicolon
r_void
id|atemapfree
c_func
(paren
r_struct
id|map
op_star
id|mp
)paren
suffix:semicolon
r_struct
id|map
op_star
id|atemapalloc
c_func
(paren
r_uint64
id|mapsiz
)paren
suffix:semicolon
DECL|macro|rmallocmap
mdefine_line|#define rmallocmap atemapalloc
DECL|macro|rmfreemap
mdefine_line|#define rmfreemap atemapfree
DECL|macro|rmfree
mdefine_line|#define rmfree atefree
DECL|macro|rmalloc
mdefine_line|#define rmalloc atealloc
macro_line|#endif
macro_line|#ifdef LATER
macro_line|#if (PCIBR_FREEZE_TIME) || PCIBR_ATE_DEBUG
DECL|variable|ate_bits
id|LOCAL
r_struct
id|reg_desc
id|ate_bits
(braket
)braket
op_assign
(brace
(brace
l_int|0xFFFF000000000000ull
comma
op_minus
l_int|48
comma
l_string|&quot;RMF&quot;
comma
l_string|&quot;%x&quot;
)brace
comma
(brace
op_complement
(paren
id|IOPGSIZE
op_minus
l_int|1
)paren
op_amp
multiline_comment|/* may trim off some low bits */
l_int|0x0000FFFFFFFFF000ull
comma
l_int|0
comma
l_string|&quot;XIO&quot;
comma
l_string|&quot;%x&quot;
)brace
comma
(brace
l_int|0x0000000000000F00ull
comma
op_minus
l_int|8
comma
l_string|&quot;port&quot;
comma
l_string|&quot;%x&quot;
)brace
comma
(brace
l_int|0x0000000000000010ull
comma
l_int|0
comma
l_string|&quot;Barrier&quot;
)brace
comma
(brace
l_int|0x0000000000000008ull
comma
l_int|0
comma
l_string|&quot;Prefetch&quot;
)brace
comma
(brace
l_int|0x0000000000000004ull
comma
l_int|0
comma
l_string|&quot;Precise&quot;
)brace
comma
(brace
l_int|0x0000000000000002ull
comma
l_int|0
comma
l_string|&quot;Coherent&quot;
)brace
comma
(brace
l_int|0x0000000000000001ull
comma
l_int|0
comma
l_string|&quot;Valid&quot;
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* LATER */
macro_line|#ifndef LOCAL
DECL|macro|LOCAL
mdefine_line|#define LOCAL           static
macro_line|#endif
multiline_comment|/*&n; * functions&n; */
r_int
id|pcibr_init_ext_ate_ram
c_func
(paren
id|bridge_t
op_star
)paren
suffix:semicolon
r_int
id|pcibr_ate_alloc
c_func
(paren
id|pcibr_soft_t
comma
r_int
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
)paren
suffix:semicolon
id|bridge_ate_t
id|pcibr_flags_to_ate
c_func
(paren
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
r_int
id|ate_freeze
c_func
(paren
id|pcibr_dmamap_t
id|pcibr_dmamap
comma
macro_line|#if PCIBR_FREEZE_TIME
r_int
op_star
id|freeze_time_ptr
comma
macro_line|#endif
r_int
op_star
id|cmd_regs
)paren
suffix:semicolon
r_void
id|ate_write
c_func
(paren
id|bridge_ate_p
id|ate_ptr
comma
r_int
id|ate_count
comma
id|bridge_ate_t
id|ate
)paren
suffix:semicolon
r_void
id|ate_thaw
c_func
(paren
id|pcibr_dmamap_t
id|pcibr_dmamap
comma
r_int
id|ate_index
comma
macro_line|#if PCIBR_FREEZE_TIME
id|bridge_ate_t
id|ate
comma
r_int
id|ate_total
comma
r_int
id|freeze_time_start
comma
macro_line|#endif
r_int
op_star
id|cmd_regs
comma
r_int
id|s
)paren
suffix:semicolon
multiline_comment|/* Convert from ssram_bits in control register to number of SSRAM entries */
DECL|macro|ATE_NUM_ENTRIES
mdefine_line|#define ATE_NUM_ENTRIES(n) _ate_info[n]
multiline_comment|/* Possible choices for number of ATE entries in Bridge&squot;s SSRAM */
DECL|variable|_ate_info
id|LOCAL
r_int
id|_ate_info
(braket
)braket
op_assign
(brace
l_int|0
comma
multiline_comment|/* 0 entries */
l_int|8
op_star
l_int|1024
comma
multiline_comment|/* 8K entries */
l_int|16
op_star
l_int|1024
comma
multiline_comment|/* 16K entries */
l_int|64
op_star
l_int|1024
multiline_comment|/* 64K entries */
)brace
suffix:semicolon
DECL|macro|ATE_NUM_SIZES
mdefine_line|#define ATE_NUM_SIZES (sizeof(_ate_info) / sizeof(int))
DECL|macro|ATE_PROBE_VALUE
mdefine_line|#define ATE_PROBE_VALUE 0x0123456789abcdefULL
multiline_comment|/*&n; * Determine the size of this bridge&squot;s external mapping SSRAM, and set&n; * the control register appropriately to reflect this size, and initialize&n; * the external SSRAM.&n; */
r_int
DECL|function|pcibr_init_ext_ate_ram
id|pcibr_init_ext_ate_ram
c_func
(paren
id|bridge_t
op_star
id|bridge
)paren
(brace
r_int
id|largest_working_size
op_assign
l_int|0
suffix:semicolon
r_int
id|num_entries
comma
id|entry
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|bridgereg_t
id|old_enable
comma
id|new_enable
suffix:semicolon
r_int
id|s
suffix:semicolon
multiline_comment|/* Probe SSRAM to determine its size. */
id|old_enable
op_assign
id|bridge-&gt;b_int_enable
suffix:semicolon
id|new_enable
op_assign
id|old_enable
op_amp
op_complement
id|BRIDGE_IMR_PCI_MST_TIMEOUT
suffix:semicolon
id|bridge-&gt;b_int_enable
op_assign
id|new_enable
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ATE_NUM_SIZES
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Try writing a value */
id|bridge-&gt;b_ext_ate_ram
(braket
id|ATE_NUM_ENTRIES
c_func
(paren
id|i
)paren
op_minus
l_int|1
)braket
op_assign
id|ATE_PROBE_VALUE
suffix:semicolon
multiline_comment|/* Guard against wrap */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
id|bridge-&gt;b_ext_ate_ram
(braket
id|ATE_NUM_ENTRIES
c_func
(paren
id|j
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* See if value was written */
r_if
c_cond
(paren
id|bridge-&gt;b_ext_ate_ram
(braket
id|ATE_NUM_ENTRIES
c_func
(paren
id|i
)paren
op_minus
l_int|1
)braket
op_eq
id|ATE_PROBE_VALUE
)paren
id|largest_working_size
op_assign
id|i
suffix:semicolon
)brace
id|bridge-&gt;b_int_enable
op_assign
id|old_enable
suffix:semicolon
id|bridge-&gt;b_wid_tflush
suffix:semicolon
multiline_comment|/* wait until Bridge PIO complete */
multiline_comment|/*&n;     * ensure that we write and read without any interruption.&n;     * The read following the write is required for the Bridge war&n;     */
id|s
op_assign
id|splhi
c_func
(paren
)paren
suffix:semicolon
id|bridge-&gt;b_wid_control
op_assign
(paren
id|bridge-&gt;b_wid_control
op_amp
op_complement
id|BRIDGE_CTRL_SSRAM_SIZE_MASK
)paren
op_or
id|BRIDGE_CTRL_SSRAM_SIZE
c_func
(paren
id|largest_working_size
)paren
suffix:semicolon
id|bridge-&gt;b_wid_control
suffix:semicolon
multiline_comment|/* inval addr bug war */
id|splx
c_func
(paren
id|s
)paren
suffix:semicolon
id|num_entries
op_assign
id|ATE_NUM_ENTRIES
c_func
(paren
id|largest_working_size
)paren
suffix:semicolon
macro_line|#if PCIBR_ATE_DEBUG
r_if
c_cond
(paren
id|num_entries
)paren
id|printk
c_func
(paren
l_string|&quot;bridge at 0x%x: clearing %d external ATEs&bslash;n&quot;
comma
id|bridge
comma
id|num_entries
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;bridge at 0x%x: no external ATE RAM found&bslash;n&quot;
comma
id|bridge
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Initialize external mapping entries */
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|num_entries
suffix:semicolon
id|entry
op_increment
)paren
id|bridge-&gt;b_ext_ate_ram
(braket
id|entry
)braket
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|num_entries
)paren
suffix:semicolon
)brace
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
)paren
(brace
r_int
id|index
op_assign
l_int|0
suffix:semicolon
id|index
op_assign
(paren
r_int
)paren
id|rmalloc
c_func
(paren
id|pcibr_soft-&gt;bs_int_ate_map
comma
(paren
r_int
)paren
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|index
op_logical_and
id|pcibr_soft-&gt;bs_ext_ate_map
)paren
id|index
op_assign
(paren
r_int
)paren
id|rmalloc
c_func
(paren
id|pcibr_soft-&gt;bs_ext_ate_map
comma
(paren
r_int
)paren
id|count
)paren
suffix:semicolon
multiline_comment|/* rmalloc manages resources in the 1..n&n;     * range, with 0 being failure.&n;     * pcibr_ate_alloc manages resources&n;     * in the 0..n-1 range, with -1 being failure.&n;     */
r_return
id|index
op_minus
l_int|1
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
)paren
multiline_comment|/* Who says there&squot;s no such thing as a free meal? :-) */
(brace
multiline_comment|/* note the &quot;+1&quot; since rmalloc handles 1..n but&n;     * we start counting ATEs at zero.&n;     */
id|rmfree
c_func
(paren
(paren
id|index
OL
id|pcibr_soft-&gt;bs_int_ate_size
)paren
ques
c_cond
id|pcibr_soft-&gt;bs_int_ate_map
suffix:colon
id|pcibr_soft-&gt;bs_ext_ate_map
comma
id|count
comma
id|index
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert PCI-generic software flags and Bridge-specific software flags&n; * into Bridge-specific Address Translation Entry attribute bits.&n; */
id|bridge_ate_t
DECL|function|pcibr_flags_to_ate
id|pcibr_flags_to_ate
c_func
(paren
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
id|bridge_t
op_star
id|bridge
op_assign
id|pcibr_soft-&gt;bs_base
suffix:semicolon
r_return
(paren
id|ate_index
OL
id|pcibr_soft-&gt;bs_int_ate_size
)paren
ques
c_cond
op_amp
(paren
id|bridge-&gt;b_int_ate_ram
(braket
id|ate_index
)braket
dot
id|wr
)paren
suffix:colon
op_amp
(paren
id|bridge-&gt;b_ext_ate_ram
(braket
id|ate_index
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* We are starting to get more complexity&n; * surrounding writing ATEs, so pull&n; * the writing code into this new function.&n; */
macro_line|#if PCIBR_FREEZE_TIME
DECL|macro|ATE_FREEZE
mdefine_line|#define&t;ATE_FREEZE()&t;s = ate_freeze(pcibr_dmamap, &amp;freeze_time, cmd_regs)
macro_line|#else
DECL|macro|ATE_FREEZE
mdefine_line|#define&t;ATE_FREEZE()&t;s = ate_freeze(pcibr_dmamap, cmd_regs)
macro_line|#endif
r_int
DECL|function|ate_freeze
id|ate_freeze
c_func
(paren
id|pcibr_dmamap_t
id|pcibr_dmamap
comma
macro_line|#if PCIBR_FREEZE_TIME
r_int
op_star
id|freeze_time_ptr
comma
macro_line|#endif
r_int
op_star
id|cmd_regs
)paren
(brace
id|pcibr_soft_t
id|pcibr_soft
op_assign
id|pcibr_dmamap-&gt;bd_soft
suffix:semicolon
macro_line|#ifdef LATER
r_int
id|dma_slot
op_assign
id|pcibr_dmamap-&gt;bd_slot
suffix:semicolon
macro_line|#endif
r_int
id|ext_ates
op_assign
id|pcibr_dmamap-&gt;bd_flags
op_amp
id|PCIBR_DMAMAP_SSRAM
suffix:semicolon
r_int
id|slot
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
r_int
id|cmd_reg
suffix:semicolon
r_volatile
r_int
op_star
id|cmd_lwa
suffix:semicolon
r_int
id|cmd_lwd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ext_ates
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Bridge Hardware Bug WAR #484930:&n;     * Bridge can&squot;t handle updating External ATEs&n;     * while DMA is occuring that uses External ATEs,&n;     * even if the particular ATEs involved are disjoint.&n;     */
multiline_comment|/* need to prevent anyone else from&n;     * unfreezing the grant while we&n;     * are working; also need to prevent&n;     * this thread from being interrupted&n;     * to keep PCI grant freeze time&n;     * at an absolute minimum.&n;     */
id|s
op_assign
id|pcibr_lock
c_func
(paren
id|pcibr_soft
)paren
suffix:semicolon
macro_line|#ifdef LATER
multiline_comment|/* just in case pcibr_dmamap_done was not called */
r_if
c_cond
(paren
id|pcibr_dmamap-&gt;bd_flags
op_amp
id|PCIBR_DMAMAP_BUSY
)paren
(brace
id|pcibr_dmamap-&gt;bd_flags
op_and_assign
op_complement
id|PCIBR_DMAMAP_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|pcibr_dmamap-&gt;bd_flags
op_amp
id|PCIBR_DMAMAP_SSRAM
)paren
id|atomic_dec
c_func
(paren
op_amp
(paren
id|pcibr_soft-&gt;bs_slot
(braket
id|dma_slot
)braket
dot
id|bss_ext_ates_active
)paren
)paren
suffix:semicolon
id|xtalk_dmamap_done
c_func
(paren
id|pcibr_dmamap-&gt;bd_xtalk
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* LATER */
macro_line|#if PCIBR_FREEZE_TIME
op_star
id|freeze_time_ptr
op_assign
id|get_timestamp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|cmd_lwa
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
l_int|8
suffix:semicolon
op_increment
id|slot
)paren
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|pcibr_soft-&gt;bs_slot
(braket
id|slot
)braket
dot
id|bss_ext_ates_active
)paren
)paren
(brace
id|cmd_reg
op_assign
id|pcibr_soft
op_member_access_from_pointer
id|bs_slot
(braket
id|slot
)braket
dot
id|bss_cmd_shadow
suffix:semicolon
r_if
c_cond
(paren
id|cmd_reg
op_amp
id|PCI_CMD_BUS_MASTER
)paren
(brace
id|cmd_lwa
op_assign
id|pcibr_soft
op_member_access_from_pointer
id|bs_slot
(braket
id|slot
)braket
dot
id|bss_cmd_pointer
suffix:semicolon
id|cmd_lwd
op_assign
id|cmd_reg
op_xor
id|PCI_CMD_BUS_MASTER
suffix:semicolon
id|cmd_lwa
(braket
l_int|0
)braket
op_assign
id|cmd_lwd
suffix:semicolon
)brace
id|cmd_regs
(braket
id|slot
)braket
op_assign
id|cmd_reg
suffix:semicolon
)brace
r_else
id|cmd_regs
(braket
id|slot
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmd_lwa
)paren
(brace
id|bridge_t
op_star
id|bridge
op_assign
id|pcibr_soft-&gt;bs_base
suffix:semicolon
multiline_comment|/* Read the last master bit that has been cleared. This PIO read&n;&t;     * on the PCI bus is to ensure the completion of any DMAs that&n;&t;     * are due to bus requests issued by PCI devices before the&n;&t;     * clearing of master bits.&n;&t;     */
id|cmd_lwa
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Flush all the write buffers in the bridge */
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
l_int|8
suffix:semicolon
op_increment
id|slot
)paren
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|pcibr_soft-&gt;bs_slot
(braket
id|slot
)braket
dot
id|bss_ext_ates_active
)paren
)paren
(brace
multiline_comment|/* Flush the write buffer associated with this&n;&t;&t;&t;     * PCI device which might be using dma map RAM.&n;&t;&t;&t;     */
id|bridge-&gt;b_wr_req_buf
(braket
id|slot
)braket
dot
id|reg
suffix:semicolon
)brace
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|macro|ATE_WRITE
mdefine_line|#define&t;ATE_WRITE()    ate_write(ate_ptr, ate_count, ate)
r_void
DECL|function|ate_write
id|ate_write
c_func
(paren
id|bridge_ate_p
id|ate_ptr
comma
r_int
id|ate_count
comma
id|bridge_ate_t
id|ate
)paren
(brace
r_while
c_loop
(paren
id|ate_count
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|ate_ptr
op_increment
op_assign
id|ate
suffix:semicolon
id|ate
op_add_assign
id|IOPGSIZE
suffix:semicolon
)brace
)brace
macro_line|#if PCIBR_FREEZE_TIME
DECL|macro|ATE_THAW
mdefine_line|#define&t;ATE_THAW()&t;ate_thaw(pcibr_dmamap, ate_index, ate, ate_total, freeze_time, cmd_regs, s)
macro_line|#else
DECL|macro|ATE_THAW
mdefine_line|#define&t;ATE_THAW()&t;ate_thaw(pcibr_dmamap, ate_index, cmd_regs, s)
macro_line|#endif
r_void
DECL|function|ate_thaw
id|ate_thaw
c_func
(paren
id|pcibr_dmamap_t
id|pcibr_dmamap
comma
r_int
id|ate_index
comma
macro_line|#if PCIBR_FREEZE_TIME
id|bridge_ate_t
id|ate
comma
r_int
id|ate_total
comma
r_int
id|freeze_time_start
comma
macro_line|#endif
r_int
op_star
id|cmd_regs
comma
r_int
id|s
)paren
(brace
id|pcibr_soft_t
id|pcibr_soft
op_assign
id|pcibr_dmamap-&gt;bd_soft
suffix:semicolon
r_int
id|dma_slot
op_assign
id|pcibr_dmamap-&gt;bd_slot
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|bridge_t
op_star
id|bridge
op_assign
id|pcibr_soft-&gt;bs_base
suffix:semicolon
r_int
id|ext_ates
op_assign
id|pcibr_dmamap-&gt;bd_flags
op_amp
id|PCIBR_DMAMAP_SSRAM
suffix:semicolon
r_int
id|cmd_reg
suffix:semicolon
macro_line|#if PCIBR_FREEZE_TIME
r_int
id|freeze_time
suffix:semicolon
r_static
r_int
id|max_freeze_time
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|max_ate_total
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ext_ates
)paren
r_return
suffix:semicolon
multiline_comment|/* restore cmd regs */
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
l_int|8
suffix:semicolon
op_increment
id|slot
)paren
r_if
c_cond
(paren
(paren
id|cmd_reg
op_assign
id|cmd_regs
(braket
id|slot
)braket
)paren
op_amp
id|PCI_CMD_BUS_MASTER
)paren
id|bridge-&gt;b_type0_cfg_dev
(braket
id|slot
)braket
dot
id|l
(braket
id|PCI_CFG_COMMAND
op_div
l_int|4
)braket
op_assign
id|cmd_reg
suffix:semicolon
id|pcibr_dmamap-&gt;bd_flags
op_or_assign
id|PCIBR_DMAMAP_BUSY
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
(paren
id|pcibr_soft-&gt;bs_slot
(braket
id|dma_slot
)braket
dot
id|bss_ext_ates_active
)paren
)paren
suffix:semicolon
macro_line|#if PCIBR_FREEZE_TIME
id|freeze_time
op_assign
id|get_timestamp
c_func
(paren
)paren
op_minus
id|freeze_time_start
suffix:semicolon
r_if
c_cond
(paren
(paren
id|max_freeze_time
OL
id|freeze_time
)paren
op_logical_or
(paren
id|max_ate_total
OL
id|ate_total
)paren
)paren
(brace
r_if
c_cond
(paren
id|max_freeze_time
OL
id|freeze_time
)paren
id|max_freeze_time
op_assign
id|freeze_time
suffix:semicolon
r_if
c_cond
(paren
id|max_ate_total
OL
id|ate_total
)paren
id|max_ate_total
op_assign
id|ate_total
suffix:semicolon
id|pcibr_unlock
c_func
(paren
id|pcibr_soft
comma
id|s
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: pci freeze time %d usec for %d ATEs&bslash;n&quot;
l_string|&quot;&bslash;tfirst ate: %R&bslash;n&quot;
comma
id|pcibr_soft-&gt;bs_name
comma
id|freeze_time
op_star
l_int|1000
op_div
l_int|1250
comma
id|ate_total
comma
id|ate
comma
id|ate_bits
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|pcibr_unlock
c_func
(paren
id|pcibr_soft
comma
id|s
)paren
suffix:semicolon
)brace
eof
