multiline_comment|/*&n; * arch/ppc64/kernel/pSeries_iommu.c&n; *&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen, IBM Corporation&n; *&n; * Rewrite, cleanup: &n; *&n; * Copyright (C) 2004 Olof Johansson &lt;olof@austin.ibm.com&gt;, IBM Corporation&n; *&n; * Dynamic DMA mapping support, pSeries-specific parts, both SMP and LPAR.&n; *&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/plpar_wrappers.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
r_extern
r_int
id|is_python
c_func
(paren
r_struct
id|device_node
op_star
)paren
suffix:semicolon
DECL|function|tce_build_pSeries
r_static
r_void
id|tce_build_pSeries
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
r_union
id|tce_entry
id|t
suffix:semicolon
r_union
id|tce_entry
op_star
id|tp
suffix:semicolon
id|t.te_word
op_assign
l_int|0
suffix:semicolon
id|t.te_rdwr
op_assign
l_int|1
suffix:semicolon
singleline_comment|// Read allowed 
r_if
c_cond
(paren
id|direction
op_ne
id|DMA_TO_DEVICE
)paren
id|t.te_pciwr
op_assign
l_int|1
suffix:semicolon
id|tp
op_assign
(paren
(paren
r_union
id|tce_entry
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
(brace
multiline_comment|/* can&squot;t move this out since we might cross LMB boundary */
id|t.te_rpn
op_assign
(paren
id|virt_to_abs
c_func
(paren
id|uaddr
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tp-&gt;te_word
op_assign
id|t.te_word
suffix:semicolon
id|uaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|tp
op_increment
suffix:semicolon
)brace
)brace
DECL|function|tce_free_pSeries
r_static
r_void
id|tce_free_pSeries
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
r_union
id|tce_entry
id|t
suffix:semicolon
r_union
id|tce_entry
op_star
id|tp
suffix:semicolon
id|t.te_word
op_assign
l_int|0
suffix:semicolon
id|tp
op_assign
(paren
(paren
r_union
id|tce_entry
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
(brace
id|tp-&gt;te_word
op_assign
id|t.te_word
suffix:semicolon
id|tp
op_increment
suffix:semicolon
)brace
)brace
DECL|function|tce_build_pSeriesLP
r_static
r_void
id|tce_build_pSeriesLP
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|tcenum
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
id|u64
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
suffix:semicolon
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
id|tce.te_rpn
op_assign
(paren
id|virt_to_abs
c_func
(paren
id|uaddr
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tce.te_rdwr
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|DMA_TO_DEVICE
)paren
id|tce.te_pciwr
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|rc
op_assign
id|plpar_tce_put
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;it_index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.te_word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_build_pSeriesLP: plpar_tce_put failed. rc=%ld&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tindex   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttcenum  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tcenum
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttce val = 0x%lx&bslash;n&quot;
comma
id|tce.te_word
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|tcenum
op_increment
suffix:semicolon
id|tce.te_rpn
op_increment
suffix:semicolon
)brace
)brace
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_void
op_star
comma
id|tce_page
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|function|tce_buildmulti_pSeriesLP
r_static
r_void
id|tce_buildmulti_pSeriesLP
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|tcenum
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
id|u64
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
comma
op_star
id|tcep
suffix:semicolon
r_int
id|l
comma
id|limit
suffix:semicolon
r_if
c_cond
(paren
id|npages
op_eq
l_int|1
)paren
r_return
id|tce_build_pSeriesLP
c_func
(paren
id|tbl
comma
id|tcenum
comma
id|npages
comma
id|uaddr
comma
id|direction
)paren
suffix:semicolon
id|tcep
op_assign
id|__get_cpu_var
c_func
(paren
id|tce_page
)paren
suffix:semicolon
multiline_comment|/* This is safe to do since interrupts are off when we&squot;re called&n;&t; * from iommu_alloc{,_sg}()&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|tcep
)paren
(brace
id|tcep
op_assign
(paren
r_void
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* If allocation fails, fall back to the loop implementation */
r_if
c_cond
(paren
op_logical_neg
id|tcep
)paren
r_return
id|tce_build_pSeriesLP
c_func
(paren
id|tbl
comma
id|tcenum
comma
id|npages
comma
id|uaddr
comma
id|direction
)paren
suffix:semicolon
id|__get_cpu_var
c_func
(paren
id|tce_page
)paren
op_assign
id|tcep
suffix:semicolon
)brace
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
id|tce.te_rpn
op_assign
(paren
id|virt_to_abs
c_func
(paren
id|uaddr
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tce.te_rdwr
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|DMA_TO_DEVICE
)paren
id|tce.te_pciwr
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We can map max one pageful of TCEs at a time */
r_do
(brace
multiline_comment|/*&n;&t;&t; * Set up the page with TCE data, looping through and setting&n;&t;&t; * the values.&n;&t;&t; */
id|limit
op_assign
id|min_t
c_func
(paren
r_int
comma
id|npages
comma
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_union
id|tce_entry
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|0
suffix:semicolon
id|l
OL
id|limit
suffix:semicolon
id|l
op_increment
)paren
(brace
id|tcep
(braket
id|l
)braket
op_assign
id|tce
suffix:semicolon
id|tce.te_rpn
op_increment
suffix:semicolon
)brace
id|rc
op_assign
id|plpar_tce_put_indirect
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;it_index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
(paren
id|u64
)paren
id|virt_to_abs
c_func
(paren
id|tcep
)paren
comma
id|limit
)paren
suffix:semicolon
id|npages
op_sub_assign
id|limit
suffix:semicolon
id|tcenum
op_add_assign
id|limit
suffix:semicolon
)brace
r_while
c_loop
(paren
id|npages
OG
l_int|0
op_logical_and
op_logical_neg
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_buildmulti_pSeriesLP: plpar_tce_put failed. rc=%ld&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tindex   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tnpages  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|npages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttce[0] val = 0x%lx&bslash;n&quot;
comma
id|tcep
(braket
l_int|0
)braket
dot
id|te_word
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|tce_free_pSeriesLP
r_static
r_void
id|tce_free_pSeriesLP
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|tcenum
comma
r_int
id|npages
)paren
(brace
id|u64
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
suffix:semicolon
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|rc
op_assign
id|plpar_tce_put
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;it_index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.te_word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_free_pSeriesLP: plpar_tce_put failed. rc=%ld&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tindex   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttcenum  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tcenum
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttce val = 0x%lx&bslash;n&quot;
comma
id|tce.te_word
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|tcenum
op_increment
suffix:semicolon
)brace
)brace
DECL|function|tce_freemulti_pSeriesLP
r_static
r_void
id|tce_freemulti_pSeriesLP
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|tcenum
comma
r_int
id|npages
)paren
(brace
id|u64
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
suffix:semicolon
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|plpar_tce_stuff
c_func
(paren
(paren
id|u64
)paren
id|tbl-&gt;it_index
comma
(paren
id|u64
)paren
id|tcenum
op_lshift
l_int|12
comma
id|tce.te_word
comma
id|npages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_and
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tce_freemulti_pSeriesLP: plpar_tce_stuff failed&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;trc      = %ld&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tindex   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tnpages  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|npages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;ttce val = 0x%lx&bslash;n&quot;
comma
id|tce.te_word
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|iommu_table_setparms
r_static
r_void
id|iommu_table_setparms
c_func
(paren
r_struct
id|pci_controller
op_star
id|phb
comma
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|iommu_table
op_star
id|tbl
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
r_int
op_star
id|basep
suffix:semicolon
r_int
r_int
op_star
id|sizep
suffix:semicolon
id|node
op_assign
(paren
r_struct
id|device_node
op_star
)paren
id|phb-&gt;arch_data
suffix:semicolon
id|basep
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;linux,tce-base&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|sizep
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;linux,tce-size&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|basep
op_eq
l_int|NULL
op_logical_or
id|sizep
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI_DMA: iommu_table_setparms: %s has &quot;
l_string|&quot;missing tce entries !&bslash;n&quot;
comma
id|dn-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tbl-&gt;it_base
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
op_star
id|basep
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|tbl-&gt;it_base
comma
l_int|0
comma
op_star
id|sizep
)paren
suffix:semicolon
id|tbl-&gt;it_busno
op_assign
id|phb-&gt;bus-&gt;number
suffix:semicolon
multiline_comment|/* Units of tce entries */
id|tbl-&gt;it_offset
op_assign
id|phb-&gt;dma_window_base_cur
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Test if we are going over 2GB of DMA space */
r_if
c_cond
(paren
id|phb-&gt;dma_window_base_cur
op_plus
id|phb-&gt;dma_window_size
OG
(paren
l_int|1L
op_lshift
l_int|31
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;PCI_DMA: Unexpected number of IOAs under this PHB.&bslash;n&quot;
)paren
suffix:semicolon
id|phb-&gt;dma_window_base_cur
op_add_assign
id|phb-&gt;dma_window_size
suffix:semicolon
multiline_comment|/* Set the tce table size - measured in entries */
id|tbl-&gt;it_size
op_assign
id|phb-&gt;dma_window_size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tbl-&gt;it_index
op_assign
l_int|0
suffix:semicolon
id|tbl-&gt;it_blocksize
op_assign
l_int|16
suffix:semicolon
id|tbl-&gt;it_type
op_assign
id|TCE_PCI
suffix:semicolon
)brace
multiline_comment|/*&n; * iommu_table_setparms_lpar&n; *&n; * Function: On pSeries LPAR systems, return TCE table info, given a pci bus.&n; *&n; * ToDo: properly interpret the ibm,dma-window property.  The definition is:&n; *&t;logical-bus-number&t;(1 word)&n; *&t;phys-address&t;&t;(#address-cells words)&n; *&t;size&t;&t;&t;(#cell-size words)&n; *&n; * Currently we hard code these sizes (more or less).&n; */
DECL|function|iommu_table_setparms_lpar
r_static
r_void
id|iommu_table_setparms_lpar
c_func
(paren
r_struct
id|pci_controller
op_star
id|phb
comma
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
r_int
op_star
id|dma_window
)paren
(brace
id|tbl-&gt;it_busno
op_assign
id|dn-&gt;bussubno
suffix:semicolon
multiline_comment|/* TODO: Parse field size properties properly. */
id|tbl-&gt;it_size
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|dma_window
(braket
l_int|4
)braket
op_lshift
l_int|32
)paren
op_or
(paren
r_int
r_int
)paren
id|dma_window
(braket
l_int|5
)braket
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tbl-&gt;it_offset
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|dma_window
(braket
l_int|2
)braket
op_lshift
l_int|32
)paren
op_or
(paren
r_int
r_int
)paren
id|dma_window
(braket
l_int|3
)braket
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|tbl-&gt;it_base
op_assign
l_int|0
suffix:semicolon
id|tbl-&gt;it_index
op_assign
id|dma_window
(braket
l_int|0
)braket
suffix:semicolon
id|tbl-&gt;it_blocksize
op_assign
l_int|16
suffix:semicolon
id|tbl-&gt;it_type
op_assign
id|TCE_PCI
suffix:semicolon
)brace
DECL|function|iommu_bus_setup_pSeries
r_static
r_void
id|iommu_bus_setup_pSeries
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|device_node
op_star
id|dn
comma
op_star
id|pdn
suffix:semicolon
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;iommu_bus_setup_pSeries, bus %p, bus-&gt;self %p&bslash;n&quot;
comma
id|bus
comma
id|bus-&gt;self
)paren
suffix:semicolon
multiline_comment|/* For each (root) bus, we carve up the available DMA space in 256MB&n;&t; * pieces. Since each piece is used by one (sub) bus/device, that would&n;&t; * give a maximum of 7 devices per PHB. In most cases, this is plenty.&n;&t; *&n;&t; * The exception is on Python PHBs (pre-POWER4). Here we don&squot;t have EADS&n;&t; * bridges below the PHB to allocate the sectioned tables to, so instead&n;&t; * we allocate a 1GB table at the PHB level.&n;&t; */
id|dn
op_assign
id|pci_bus_to_OF_node
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;self
)paren
(brace
multiline_comment|/* Root bus */
r_if
c_cond
(paren
id|is_python
c_func
(paren
id|dn
)paren
)paren
(brace
r_int
r_int
op_star
id|iohole
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Python root bus %s&bslash;n&quot;
comma
id|bus-&gt;name
)paren
suffix:semicolon
id|iohole
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;io-hole&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iohole
)paren
(brace
multiline_comment|/* On first bus we need to leave room for the&n;&t;&t;&t;&t; * ISA address space. Just skip the first 256MB&n;&t;&t;&t;&t; * alltogether. This leaves 768MB for the window.&n;&t;&t;&t;&t; */
id|DBG
c_func
(paren
l_string|&quot;PHB has io-hole, reserving 256MB&bslash;n&quot;
)paren
suffix:semicolon
id|dn-&gt;phb-&gt;dma_window_size
op_assign
l_int|3
op_lshift
l_int|28
suffix:semicolon
id|dn-&gt;phb-&gt;dma_window_base_cur
op_assign
l_int|1
op_lshift
l_int|28
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 1GB window by default */
id|dn-&gt;phb-&gt;dma_window_size
op_assign
l_int|1
op_lshift
l_int|30
suffix:semicolon
id|dn-&gt;phb-&gt;dma_window_base_cur
op_assign
l_int|0
suffix:semicolon
)brace
id|tbl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iommu_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|iommu_table_setparms
c_func
(paren
id|dn-&gt;phb
comma
id|dn
comma
id|tbl
)paren
suffix:semicolon
id|dn-&gt;iommu_table
op_assign
id|iommu_init_table
c_func
(paren
id|tbl
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Do a 128MB table at root. This is used for the IDE&n;&t;&t;&t; * controller on some SMP-mode POWER4 machines. It&n;&t;&t;&t; * doesn&squot;t hurt to allocate it on other machines&n;&t;&t;&t; * -- it&squot;ll just be unused since new tables are&n;&t;&t;&t; * allocated on the EADS level.&n;&t;&t;&t; *&n;&t;&t;&t; * Allocate at offset 128MB to avoid having to deal&n;&t;&t;&t; * with ISA holes; 128MB table for IDE is plenty.&n;&t;&t;&t; */
id|dn-&gt;phb-&gt;dma_window_size
op_assign
l_int|1
op_lshift
l_int|27
suffix:semicolon
id|dn-&gt;phb-&gt;dma_window_base_cur
op_assign
l_int|1
op_lshift
l_int|27
suffix:semicolon
id|tbl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iommu_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|iommu_table_setparms
c_func
(paren
id|dn-&gt;phb
comma
id|dn
comma
id|tbl
)paren
suffix:semicolon
id|dn-&gt;iommu_table
op_assign
id|iommu_init_table
c_func
(paren
id|tbl
)paren
suffix:semicolon
multiline_comment|/* All child buses have 256MB tables */
id|dn-&gt;phb-&gt;dma_window_size
op_assign
l_int|1
op_lshift
l_int|28
suffix:semicolon
)brace
)brace
r_else
(brace
id|pdn
op_assign
id|pci_bus_to_OF_node
c_func
(paren
id|bus-&gt;parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;parent-&gt;self
op_logical_and
op_logical_neg
id|is_python
c_func
(paren
id|pdn
)paren
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
multiline_comment|/* First child and not python means this is the EADS&n;&t;&t;&t; * level. Allocate new table for this slot with 256MB&n;&t;&t;&t; * window.&n;&t;&t;&t; */
id|tbl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iommu_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|iommu_table_setparms
c_func
(paren
id|dn-&gt;phb
comma
id|dn
comma
id|tbl
)paren
suffix:semicolon
id|dn-&gt;iommu_table
op_assign
id|iommu_init_table
c_func
(paren
id|tbl
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Lower than first child or under python, use parent table */
id|dn-&gt;iommu_table
op_assign
id|pdn-&gt;iommu_table
suffix:semicolon
)brace
)brace
)brace
DECL|function|iommu_bus_setup_pSeriesLP
r_static
r_void
id|iommu_bus_setup_pSeriesLP
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
r_struct
id|device_node
op_star
id|dn
comma
op_star
id|pdn
suffix:semicolon
r_int
r_int
op_star
id|dma_window
op_assign
l_int|NULL
suffix:semicolon
id|dn
op_assign
id|pci_bus_to_OF_node
c_func
(paren
id|bus
)paren
suffix:semicolon
multiline_comment|/* Find nearest ibm,dma-window, walking up the device tree */
r_for
c_loop
(paren
id|pdn
op_assign
id|dn
suffix:semicolon
id|pdn
op_ne
l_int|NULL
suffix:semicolon
id|pdn
op_assign
id|pdn-&gt;parent
)paren
(brace
id|dma_window
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|pdn
comma
l_string|&quot;ibm,dma-window&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_window
op_ne
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma_window
op_eq
l_int|NULL
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;iommu_bus_setup_pSeriesLP: bus %s seems to have no ibm,dma-window property&bslash;n&quot;
comma
id|dn-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pdn-&gt;iommu_table
)paren
(brace
multiline_comment|/* Bussubno hasn&squot;t been copied yet.&n;&t;&t; * Do it now because iommu_table_setparms_lpar needs it.&n;&t;&t; */
id|pdn-&gt;bussubno
op_assign
id|bus-&gt;number
suffix:semicolon
id|tbl
op_assign
(paren
r_struct
id|iommu_table
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iommu_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|iommu_table_setparms_lpar
c_func
(paren
id|pdn-&gt;phb
comma
id|pdn
comma
id|tbl
comma
id|dma_window
)paren
suffix:semicolon
id|pdn-&gt;iommu_table
op_assign
id|iommu_init_table
c_func
(paren
id|tbl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdn
op_ne
id|dn
)paren
id|dn-&gt;iommu_table
op_assign
id|pdn-&gt;iommu_table
suffix:semicolon
)brace
DECL|function|iommu_dev_setup_pSeries
r_static
r_void
id|iommu_dev_setup_pSeries
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|device_node
op_star
id|dn
comma
op_star
id|mydn
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;iommu_dev_setup_pSeries, dev %p (%s)&bslash;n&quot;
comma
id|dev
comma
id|dev-&gt;pretty_name
)paren
suffix:semicolon
multiline_comment|/* Now copy the iommu_table ptr from the bus device down to the&n;&t; * pci device_node.  This means get_iommu_table() won&squot;t need to search&n;&t; * up the device tree to find it.&n;&t; */
id|mydn
op_assign
id|dn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dn
op_logical_and
id|dn-&gt;iommu_table
op_eq
l_int|NULL
)paren
id|dn
op_assign
id|dn-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
id|dn
)paren
(brace
id|mydn-&gt;iommu_table
op_assign
id|dn-&gt;iommu_table
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_string|&quot;iommu_dev_setup_pSeries, dev %p (%s) has no iommu table&bslash;n&quot;
comma
id|dev
comma
id|dev-&gt;pretty_name
)paren
suffix:semicolon
)brace
)brace
DECL|function|iommu_bus_setup_null
r_static
r_void
id|iommu_bus_setup_null
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
)brace
DECL|function|iommu_dev_setup_null
r_static
r_void
id|iommu_dev_setup_null
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
)brace
multiline_comment|/* These are called very early. */
DECL|function|iommu_init_early_pSeries
r_void
id|iommu_init_early_pSeries
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|of_chosen
op_logical_and
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,iommu-off&quot;
comma
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* Direct I/O, IOMMU off */
id|ppc_md.iommu_dev_setup
op_assign
id|iommu_dev_setup_null
suffix:semicolon
id|ppc_md.iommu_bus_setup
op_assign
id|iommu_bus_setup_null
suffix:semicolon
id|pci_direct_iommu_init
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_LPAR
)paren
(brace
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_MULTITCE
)paren
(brace
id|ppc_md.tce_build
op_assign
id|tce_buildmulti_pSeriesLP
suffix:semicolon
id|ppc_md.tce_free
op_assign
id|tce_freemulti_pSeriesLP
suffix:semicolon
)brace
r_else
(brace
id|ppc_md.tce_build
op_assign
id|tce_build_pSeriesLP
suffix:semicolon
id|ppc_md.tce_free
op_assign
id|tce_free_pSeriesLP
suffix:semicolon
)brace
id|ppc_md.iommu_bus_setup
op_assign
id|iommu_bus_setup_pSeriesLP
suffix:semicolon
)brace
r_else
(brace
id|ppc_md.tce_build
op_assign
id|tce_build_pSeries
suffix:semicolon
id|ppc_md.tce_free
op_assign
id|tce_free_pSeries
suffix:semicolon
id|ppc_md.iommu_bus_setup
op_assign
id|iommu_bus_setup_pSeries
suffix:semicolon
)brace
id|ppc_md.iommu_dev_setup
op_assign
id|iommu_dev_setup_pSeries
suffix:semicolon
id|pci_iommu_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
