multiline_comment|/*&n; * arch/ppc64/kernel/u3_iommu.c&n; *&n; * Copyright (C) 2004 Olof Johansson &lt;olof@austin.ibm.com&gt;, IBM Corporation&n; *&n; * Based on pSeries_iommu.c:&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen, IBM Corporation&n; * Copyright (C) 2004 Olof Johansson &lt;olof@austin.ibm.com&gt;, IBM Corporation&n; *&n; * Dynamic DMA mapping support, Apple U3 &amp; IBM CPC925 &quot;DART&quot; iommu.&n; *&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &quot;pci.h&quot;
r_extern
r_int
id|iommu_force_on
suffix:semicolon
multiline_comment|/* physical base of DART registers */
DECL|macro|DART_BASE
mdefine_line|#define DART_BASE        0xf8033000UL
multiline_comment|/* Offset from base to control register */
DECL|macro|DARTCNTL
mdefine_line|#define DARTCNTL   0
multiline_comment|/* Offset from base to exception register */
DECL|macro|DARTEXCP
mdefine_line|#define DARTEXCP   0x10
multiline_comment|/* Offset from base to TLB tag registers */
DECL|macro|DARTTAG
mdefine_line|#define DARTTAG    0x1000
multiline_comment|/* Control Register fields */
multiline_comment|/* base address of table (pfn) */
DECL|macro|DARTCNTL_BASE_MASK
mdefine_line|#define DARTCNTL_BASE_MASK    0xfffff
DECL|macro|DARTCNTL_BASE_SHIFT
mdefine_line|#define DARTCNTL_BASE_SHIFT   12
DECL|macro|DARTCNTL_FLUSHTLB
mdefine_line|#define DARTCNTL_FLUSHTLB     0x400
DECL|macro|DARTCNTL_ENABLE
mdefine_line|#define DARTCNTL_ENABLE       0x200
multiline_comment|/* size of table in pages */
DECL|macro|DARTCNTL_SIZE_MASK
mdefine_line|#define DARTCNTL_SIZE_MASK    0x1ff
DECL|macro|DARTCNTL_SIZE_SHIFT
mdefine_line|#define DARTCNTL_SIZE_SHIFT   0
multiline_comment|/* DART table fields */
DECL|macro|DARTMAP_VALID
mdefine_line|#define DARTMAP_VALID   0x80000000
DECL|macro|DARTMAP_RPNMASK
mdefine_line|#define DARTMAP_RPNMASK 0x00ffffff
multiline_comment|/* Physical base address and size of the DART table */
DECL|variable|dart_tablebase
r_int
r_int
id|dart_tablebase
suffix:semicolon
multiline_comment|/* exported to htab_initialize */
DECL|variable|dart_tablesize
r_static
r_int
r_int
id|dart_tablesize
suffix:semicolon
multiline_comment|/* Virtual base address of the DART table */
DECL|variable|dart_vbase
r_static
id|u32
op_star
id|dart_vbase
suffix:semicolon
multiline_comment|/* Mapped base address for the dart */
DECL|variable|dart
r_static
r_int
r_int
op_star
id|dart
suffix:semicolon
multiline_comment|/* Dummy val that entries are set to when unused */
DECL|variable|dart_emptyval
r_static
r_int
r_int
id|dart_emptyval
suffix:semicolon
DECL|variable|iommu_table_u3
r_static
r_struct
id|iommu_table
id|iommu_table_u3
suffix:semicolon
DECL|variable|dart_dirty
r_static
r_int
id|dart_dirty
suffix:semicolon
DECL|macro|DBG
mdefine_line|#define DBG(...)
DECL|function|dart_tlb_invalidate_all
r_static
r_inline
r_void
id|dart_tlb_invalidate_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|l
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
r_int
r_int
id|limit
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;dart: flush&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* To invalidate the DART, set the DARTCNTL_FLUSHTLB bit in the&n;&t; * control register and wait for it to clear.&n;&t; *&n;&t; * Gotcha: Sometimes, the DART won&squot;t detect that the bit gets&n;&t; * set. If so, clear it and set it again.&n;&t; */
id|limit
op_assign
l_int|0
suffix:semicolon
id|retry
suffix:colon
id|reg
op_assign
id|in_be32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|dart
op_plus
id|DARTCNTL
)paren
suffix:semicolon
id|reg
op_or_assign
id|DARTCNTL_FLUSHTLB
suffix:semicolon
id|out_be32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|dart
op_plus
id|DARTCNTL
comma
id|reg
)paren
suffix:semicolon
id|l
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|in_be32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|dart
op_plus
id|DARTCNTL
)paren
op_amp
id|DARTCNTL_FLUSHTLB
)paren
op_logical_and
id|l
OL
(paren
l_int|1L
op_lshift
id|limit
)paren
)paren
(brace
id|l
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|l
op_eq
(paren
l_int|1L
op_lshift
id|limit
)paren
)paren
(brace
r_if
c_cond
(paren
id|limit
OL
l_int|4
)paren
(brace
id|limit
op_increment
suffix:semicolon
id|reg
op_assign
id|in_be32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|dart
op_plus
id|DARTCNTL
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
id|DARTCNTL_FLUSHTLB
suffix:semicolon
id|out_be32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|dart
op_plus
id|DARTCNTL
comma
id|reg
)paren
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
r_else
id|panic
c_func
(paren
l_string|&quot;U3-DART: TLB did not flush after waiting a long &quot;
l_string|&quot;time. Buggy U3 ?&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|dart_flush
r_static
r_void
id|dart_flush
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
)paren
(brace
r_if
c_cond
(paren
id|dart_dirty
)paren
id|dart_tlb_invalidate_all
c_func
(paren
)paren
suffix:semicolon
id|dart_dirty
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|dart_build
r_static
r_void
id|dart_build
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|index
comma
r_int
id|npages
comma
r_int
r_int
id|uaddr
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
r_int
op_star
id|dp
suffix:semicolon
r_int
r_int
id|rpn
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;dart: build at: %lx, %lx, addr: %x&bslash;n&quot;
comma
id|index
comma
id|npages
comma
id|uaddr
)paren
suffix:semicolon
id|dp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|tbl-&gt;it_base
)paren
op_plus
id|index
suffix:semicolon
multiline_comment|/* On U3, all memory is contigous, so we can move this&n;&t; * out of the loop.&n;&t; */
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|rpn
op_assign
id|virt_to_abs
c_func
(paren
id|uaddr
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
op_star
(paren
id|dp
op_increment
)paren
op_assign
id|DARTMAP_VALID
op_or
(paren
id|rpn
op_amp
id|DARTMAP_RPNMASK
)paren
suffix:semicolon
id|rpn
op_increment
suffix:semicolon
id|uaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|dart_dirty
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|dart_free
r_static
r_void
id|dart_free
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|index
comma
r_int
id|npages
)paren
(brace
r_int
r_int
op_star
id|dp
suffix:semicolon
multiline_comment|/* We don&squot;t worry about flushing the TLB cache. The only drawback of&n;&t; * not doing it is that we won&squot;t catch buggy device drivers doing&n;&t; * bad DMAs, but then no 32-bit architecture ever does either.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;dart: free at: %lx, %lx&bslash;n&quot;
comma
id|index
comma
id|npages
)paren
suffix:semicolon
id|dp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|tbl-&gt;it_base
)paren
op_plus
id|index
suffix:semicolon
r_while
c_loop
(paren
id|npages
op_decrement
)paren
op_star
(paren
id|dp
op_increment
)paren
op_assign
id|dart_emptyval
suffix:semicolon
)brace
DECL|function|dart_init
r_static
r_int
id|dart_init
c_func
(paren
r_struct
id|device_node
op_star
id|dart_node
)paren
(brace
r_int
r_int
id|regword
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_struct
id|page
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|dart_tablebase
op_eq
l_int|0
op_logical_or
id|dart_tablesize
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;U3-DART: table not allocated, using direct DMA&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Make sure nothing from the DART range remains in the CPU cache&n;&t; * from a previous mapping that existed before the kernel took&n;&t; * over&n;&t; */
id|flush_dcache_phys_range
c_func
(paren
id|dart_tablebase
comma
id|dart_tablebase
op_plus
id|dart_tablesize
)paren
suffix:semicolon
multiline_comment|/* Allocate a spare page to map all invalid DART pages. We need to do&n;&t; * that to work around what looks like a problem with the HT bridge&n;&t; * prefetching into invalid pages and corrupting data&n;&t; */
id|tmp
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;U3-DART: Cannot allocate spare page !&quot;
)paren
suffix:semicolon
id|dart_emptyval
op_assign
id|DARTMAP_VALID
op_or
(paren
(paren
id|virt_to_abs
c_func
(paren
id|tmp
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_amp
id|DARTMAP_RPNMASK
)paren
suffix:semicolon
multiline_comment|/* Map in DART registers. FIXME: Use device node to get base address */
id|dart
op_assign
id|ioremap
c_func
(paren
id|DART_BASE
comma
l_int|0x7000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dart
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;U3-DART: Cannot map registers !&quot;
)paren
suffix:semicolon
multiline_comment|/* Set initial control register contents: table base, &n;&t; * table size and enable bit&n;&t; */
id|regword
op_assign
id|DARTCNTL_ENABLE
op_or
(paren
(paren
id|dart_tablebase
op_rshift
id|PAGE_SHIFT
)paren
op_lshift
id|DARTCNTL_BASE_SHIFT
)paren
op_or
(paren
(paren
(paren
id|dart_tablesize
op_rshift
id|PAGE_SHIFT
)paren
op_amp
id|DARTCNTL_SIZE_MASK
)paren
op_lshift
id|DARTCNTL_SIZE_SHIFT
)paren
suffix:semicolon
id|p
op_assign
id|virt_to_page
c_func
(paren
id|dart_tablebase
)paren
suffix:semicolon
id|dart_vbase
op_assign
id|ioremap
c_func
(paren
id|virt_to_abs
c_func
(paren
id|dart_tablebase
)paren
comma
id|dart_tablesize
)paren
suffix:semicolon
multiline_comment|/* Fill initial table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dart_tablesize
op_div
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|dart_vbase
(braket
id|i
)braket
op_assign
id|dart_emptyval
suffix:semicolon
multiline_comment|/* Initialize DART with table base and enable it. */
id|out_be32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|dart
comma
id|regword
)paren
suffix:semicolon
multiline_comment|/* Invalidate DART to get rid of possible stale TLBs */
id|dart_tlb_invalidate_all
c_func
(paren
)paren
suffix:semicolon
id|iommu_table_u3.it_busno
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Units of tce entries */
id|iommu_table_u3.it_offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set the tce table size - measured in pages */
id|iommu_table_u3.it_size
op_assign
id|dart_tablesize
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Initialize the common IOMMU code */
id|iommu_table_u3.it_base
op_assign
(paren
r_int
r_int
)paren
id|dart_vbase
suffix:semicolon
id|iommu_table_u3.it_index
op_assign
l_int|0
suffix:semicolon
id|iommu_table_u3.it_blocksize
op_assign
l_int|1
suffix:semicolon
id|iommu_table_u3.it_entrysize
op_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
id|iommu_init_table
c_func
(paren
op_amp
id|iommu_table_u3
)paren
suffix:semicolon
multiline_comment|/* Reserve the last page of the DART to avoid possible prefetch&n;&t; * past the DART mapped area&n;&t; */
id|set_bit
c_func
(paren
id|iommu_table_u3.it_mapsize
op_minus
l_int|1
comma
id|iommu_table_u3.it_map
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;U3/CPC925 DART IOMMU initialized&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iommu_setup_u3
r_void
id|iommu_setup_u3
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|phb
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
multiline_comment|/* Find the DART in the device-tree */
id|dn
op_assign
id|of_find_compatible_node
c_func
(paren
l_int|NULL
comma
l_string|&quot;dart&quot;
comma
l_string|&quot;u3-dart&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Setup low level TCE operations for the core IOMMU code */
id|ppc_md.tce_build
op_assign
id|dart_build
suffix:semicolon
id|ppc_md.tce_free
op_assign
id|dart_free
suffix:semicolon
id|ppc_md.tce_flush
op_assign
id|dart_flush
suffix:semicolon
multiline_comment|/* Initialize the DART HW */
r_if
c_cond
(paren
id|dart_init
c_func
(paren
id|dn
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Setup pci_dma ops */
id|pci_iommu_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We only have one iommu table on the mac for now, which makes&n;&t; * things simple. Setup all PCI devices to point to this table&n;&t; */
id|for_each_pci_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/* We must use pci_device_to_OF_node() to make sure that&n;&t;&t; * we get the real &quot;final&quot; pointer to the device in the&n;&t;&t; * pci_dev sysdata and not the temporary PHB one&n;&t;&t; */
r_struct
id|device_node
op_star
id|dn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
)paren
id|dn-&gt;iommu_table
op_assign
op_amp
id|iommu_table_u3
suffix:semicolon
)brace
multiline_comment|/* We also make sure we set all PHBs ... */
id|list_for_each_entry_safe
c_func
(paren
id|phb
comma
id|tmp
comma
op_amp
id|hose_list
comma
id|list_node
)paren
(brace
id|dn
op_assign
(paren
r_struct
id|device_node
op_star
)paren
id|phb-&gt;arch_data
suffix:semicolon
id|dn-&gt;iommu_table
op_assign
op_amp
id|iommu_table_u3
suffix:semicolon
)brace
)brace
DECL|function|alloc_u3_dart_table
r_void
id|__init
id|alloc_u3_dart_table
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Only reserve DART space if machine has more than 2GB of RAM&n;&t; * or if requested with iommu=on on cmdline.&n;&t; */
r_if
c_cond
(paren
id|lmb_end_of_DRAM
c_func
(paren
)paren
op_le
l_int|0x80000000ull
op_logical_and
op_logical_neg
id|iommu_force_on
)paren
r_return
suffix:semicolon
multiline_comment|/* 512 pages (2MB) is max DART tablesize. */
id|dart_tablesize
op_assign
l_int|1UL
op_lshift
l_int|21
suffix:semicolon
multiline_comment|/* 16MB (1 &lt;&lt; 24) alignment. We allocate a full 16Mb chuck since we&n;&t; * will blow up an entire large page anyway in the kernel mapping&n;&t; */
id|dart_tablebase
op_assign
(paren
r_int
r_int
)paren
id|abs_to_virt
c_func
(paren
id|lmb_alloc_base
c_func
(paren
l_int|1UL
op_lshift
l_int|24
comma
l_int|1UL
op_lshift
l_int|24
comma
l_int|0x80000000L
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;U3-DART allocated at: %lx&bslash;n&quot;
comma
id|dart_tablebase
)paren
suffix:semicolon
)brace
eof
