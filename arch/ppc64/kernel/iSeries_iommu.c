multiline_comment|/*&n; * arch/ppc64/kernel/iSeries_iommu.c&n; *&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen, IBM Corporation&n; * &n; * Rewrite, cleanup: &n; *&n; * Copyright (C) 2004 Olof Johansson &lt;olof@austin.ibm.com&gt;, IBM Corporation&n; *&n; * Dynamic DMA mapping support, iSeries-specific parts.&n; *&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallXm.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#include &lt;asm/iSeries/vio.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|variable|veth_iommu_table
r_static
r_struct
id|iommu_table
id|veth_iommu_table
suffix:semicolon
multiline_comment|/* Tce table for virtual ethernet */
DECL|variable|vio_iommu_table
r_static
r_struct
id|iommu_table
id|vio_iommu_table
suffix:semicolon
multiline_comment|/* Tce table for virtual I/O */
DECL|variable|veth_dev_node
r_static
r_struct
id|iSeries_Device_Node
id|veth_dev_node
op_assign
(brace
dot
id|LogicalSlot
op_assign
l_int|0xFF
comma
dot
id|iommu_table
op_assign
op_amp
id|veth_iommu_table
)brace
suffix:semicolon
DECL|variable|vio_dev_node
r_static
r_struct
id|iSeries_Device_Node
id|vio_dev_node
op_assign
(brace
dot
id|LogicalSlot
op_assign
l_int|0xFF
comma
dot
id|iommu_table
op_assign
op_amp
id|vio_iommu_table
)brace
suffix:semicolon
DECL|variable|_veth_dev
r_static
r_struct
id|pci_dev
id|_veth_dev
op_assign
(brace
dot
id|sysdata
op_assign
op_amp
id|veth_dev_node
)brace
suffix:semicolon
DECL|variable|_vio_dev
r_static
r_struct
id|pci_dev
id|_vio_dev
op_assign
(brace
dot
id|sysdata
op_assign
op_amp
id|vio_dev_node
comma
dot
id|dev.bus
op_assign
op_amp
id|pci_bus_type
)brace
suffix:semicolon
DECL|variable|iSeries_veth_dev
r_struct
id|pci_dev
op_star
id|iSeries_veth_dev
op_assign
op_amp
id|_veth_dev
suffix:semicolon
DECL|variable|iSeries_vio_dev
r_struct
id|device
op_star
id|iSeries_vio_dev
op_assign
op_amp
id|_vio_dev.dev
suffix:semicolon
DECL|variable|iSeries_veth_dev
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_veth_dev
)paren
suffix:semicolon
DECL|variable|iSeries_vio_dev
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_vio_dev
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|iSeries_Global_Device_List
suffix:semicolon
DECL|function|tce_build_iSeries
r_static
r_void
id|tce_build_iSeries
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
r_int
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
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
id|tce.te_bits.tb_rpn
op_assign
id|virt_to_abs
c_func
(paren
id|uaddr
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|tbl-&gt;it_type
op_eq
id|TCE_VB
)paren
(brace
multiline_comment|/* Virtual Bus */
id|tce.te_bits.tb_valid
op_assign
l_int|1
suffix:semicolon
id|tce.te_bits.tb_allio
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
id|tce.te_bits.tb_rdwr
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* PCI Bus */
id|tce.te_bits.tb_rdwr
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Read allowed */
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
id|tce.te_bits.tb_pciwr
op_assign
l_int|1
suffix:semicolon
)brace
id|rc
op_assign
id|HvCallXm_setTce
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
id|index
comma
id|tce.te_word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|panic
c_func
(paren
l_string|&quot;PCI_DMA: HvCallXm_setTce failed, Rc: 0x%lx&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|index
op_increment
suffix:semicolon
id|uaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
DECL|function|tce_free_iSeries
r_static
r_void
id|tce_free_iSeries
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
id|u64
id|rc
suffix:semicolon
r_union
id|tce_entry
id|tce
suffix:semicolon
r_while
c_loop
(paren
id|npages
op_decrement
)paren
(brace
id|tce.te_word
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|HvCallXm_setTce
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
id|index
comma
id|tce.te_word
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|panic
c_func
(paren
l_string|&quot;PCI_DMA: HvCallXm_setTce failed, Rc: 0x%lx&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|index
op_increment
suffix:semicolon
)brace
)brace
DECL|function|iommu_vio_init
r_void
id|__init
id|iommu_vio_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|iommu_table
op_star
id|t
suffix:semicolon
r_struct
id|iommu_table_cb
id|cb
suffix:semicolon
r_int
r_int
id|cbp
suffix:semicolon
id|cb.itc_busno
op_assign
l_int|255
suffix:semicolon
multiline_comment|/* Bus 255 is the virtual bus */
id|cb.itc_virtbus
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Ask for virtual bus */
id|cbp
op_assign
id|virt_to_abs
c_func
(paren
op_amp
id|cb
)paren
suffix:semicolon
id|HvCallXm_getTceTableParms
c_func
(paren
id|cbp
)paren
suffix:semicolon
id|veth_iommu_table.it_size
op_assign
id|cb.itc_size
op_div
l_int|2
suffix:semicolon
id|veth_iommu_table.it_busno
op_assign
id|cb.itc_busno
suffix:semicolon
id|veth_iommu_table.it_offset
op_assign
id|cb.itc_offset
suffix:semicolon
id|veth_iommu_table.it_index
op_assign
id|cb.itc_index
suffix:semicolon
id|veth_iommu_table.it_type
op_assign
id|TCE_VB
suffix:semicolon
id|veth_iommu_table.it_entrysize
op_assign
r_sizeof
(paren
r_union
id|tce_entry
)paren
suffix:semicolon
id|veth_iommu_table.it_blocksize
op_assign
l_int|1
suffix:semicolon
id|t
op_assign
id|iommu_init_table
c_func
(paren
op_amp
id|veth_iommu_table
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
id|printk
c_func
(paren
l_string|&quot;Virtual Bus VETH TCE table failed.&bslash;n&quot;
)paren
suffix:semicolon
id|vio_iommu_table.it_size
op_assign
id|cb.itc_size
op_minus
id|veth_iommu_table.it_size
suffix:semicolon
id|vio_iommu_table.it_busno
op_assign
id|cb.itc_busno
suffix:semicolon
id|vio_iommu_table.it_offset
op_assign
id|cb.itc_offset
op_plus
id|veth_iommu_table.it_size
op_star
(paren
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_union
id|tce_entry
)paren
)paren
suffix:semicolon
id|vio_iommu_table.it_index
op_assign
id|cb.itc_index
suffix:semicolon
id|vio_iommu_table.it_type
op_assign
id|TCE_VB
suffix:semicolon
id|vio_iommu_table.it_entrysize
op_assign
r_sizeof
(paren
r_union
id|tce_entry
)paren
suffix:semicolon
id|vio_iommu_table.it_blocksize
op_assign
l_int|1
suffix:semicolon
id|t
op_assign
id|iommu_init_table
c_func
(paren
op_amp
id|vio_iommu_table
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
id|printk
c_func
(paren
l_string|&quot;Virtual Bus VIO TCE table failed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function compares the known tables to find an iommu_table&n; * that has already been built for hardware TCEs.                          &n; */
DECL|function|iommu_table_find
r_static
r_struct
id|iommu_table
op_star
id|iommu_table_find
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
)paren
(brace
r_struct
id|iSeries_Device_Node
op_star
id|dp
suffix:semicolon
r_for
c_loop
(paren
id|dp
op_assign
(paren
r_struct
id|iSeries_Device_Node
op_star
)paren
id|iSeries_Global_Device_List.next
suffix:semicolon
id|dp
op_ne
(paren
r_struct
id|iSeries_Device_Node
op_star
)paren
op_amp
id|iSeries_Global_Device_List
suffix:semicolon
id|dp
op_assign
(paren
r_struct
id|iSeries_Device_Node
op_star
)paren
id|dp-&gt;Device_List.next
)paren
r_if
c_cond
(paren
id|dp-&gt;iommu_table
op_ne
l_int|NULL
op_logical_and
id|dp-&gt;iommu_table-&gt;it_type
op_eq
id|TCE_PCI
op_logical_and
id|dp-&gt;iommu_table-&gt;it_offset
op_eq
id|tbl-&gt;it_offset
op_logical_and
id|dp-&gt;iommu_table-&gt;it_index
op_eq
id|tbl-&gt;it_index
op_logical_and
id|dp-&gt;iommu_table-&gt;it_size
op_eq
id|tbl-&gt;it_size
)paren
r_return
id|dp-&gt;iommu_table
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Call Hv with the architected data structure to get TCE table info.&n; * info. Put the returned data into the Linux representation of the   &n; * TCE table data.                                                     &n; * The Hardware Tce table comes in three flavors.                     &n; * 1. TCE table shared between Buses.                                  &n; * 2. TCE table per Bus.                                               &n; * 3. TCE Table per IOA.                                               &n; */
DECL|function|iommu_table_getparms
r_static
r_void
id|iommu_table_getparms
c_func
(paren
r_struct
id|iSeries_Device_Node
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
id|iommu_table_cb
op_star
id|parms
suffix:semicolon
id|parms
op_assign
(paren
r_struct
id|iommu_table_cb
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|parms
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parms
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;PCI_DMA: TCE Table Allocation failed.&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|parms
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|parms
)paren
)paren
suffix:semicolon
id|parms-&gt;itc_busno
op_assign
id|ISERIES_BUS
c_func
(paren
id|dn
)paren
suffix:semicolon
id|parms-&gt;itc_slotno
op_assign
id|dn-&gt;LogicalSlot
suffix:semicolon
id|parms-&gt;itc_virtbus
op_assign
l_int|0
suffix:semicolon
id|HvCallXm_getTceTableParms
c_func
(paren
id|ISERIES_HV_ADDR
c_func
(paren
id|parms
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parms-&gt;itc_size
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;PCI_DMA: parms-&gt;size is zero, parms is 0x%p&quot;
comma
id|parms
)paren
suffix:semicolon
id|tbl-&gt;it_size
op_assign
id|parms-&gt;itc_size
suffix:semicolon
id|tbl-&gt;it_busno
op_assign
id|parms-&gt;itc_busno
suffix:semicolon
id|tbl-&gt;it_offset
op_assign
id|parms-&gt;itc_offset
suffix:semicolon
id|tbl-&gt;it_index
op_assign
id|parms-&gt;itc_index
suffix:semicolon
id|tbl-&gt;it_entrysize
op_assign
r_sizeof
(paren
r_union
id|tce_entry
)paren
suffix:semicolon
id|tbl-&gt;it_blocksize
op_assign
l_int|1
suffix:semicolon
id|tbl-&gt;it_type
op_assign
id|TCE_PCI
suffix:semicolon
id|kfree
c_func
(paren
id|parms
)paren
suffix:semicolon
)brace
DECL|function|iommu_devnode_init
r_void
id|iommu_devnode_init
c_func
(paren
r_struct
id|iSeries_Device_Node
op_star
id|dn
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
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
id|iommu_table_getparms
c_func
(paren
id|dn
comma
id|tbl
)paren
suffix:semicolon
multiline_comment|/* Look for existing tce table */
id|dn-&gt;iommu_table
op_assign
id|iommu_table_find
c_func
(paren
id|tbl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn-&gt;iommu_table
op_eq
l_int|NULL
)paren
id|dn-&gt;iommu_table
op_assign
id|iommu_init_table
c_func
(paren
id|tbl
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|tbl
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tce_init_iSeries
r_void
id|tce_init_iSeries
c_func
(paren
r_void
)paren
(brace
id|ppc_md.tce_build
op_assign
id|tce_build_iSeries
suffix:semicolon
id|ppc_md.tce_free
op_assign
id|tce_free_iSeries
suffix:semicolon
id|pci_iommu_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
