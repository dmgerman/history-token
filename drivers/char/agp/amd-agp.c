multiline_comment|/*&n; * AGPGART module version 0.99&n; * Copyright (C) 1999 Jeff Hartmann&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * TODO: &n; * - Allocate more than order 0 pages to avoid too much linear map splitting.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|struct|amd_page_map
r_struct
id|amd_page_map
(brace
DECL|member|real
r_int
r_int
op_star
id|real
suffix:semicolon
DECL|member|remapped
r_int
r_int
op_star
id|remapped
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_amd_irongate_private
r_static
r_struct
id|_amd_irongate_private
(brace
DECL|member|registers
r_volatile
id|u8
op_star
id|registers
suffix:semicolon
DECL|member|gatt_pages
r_struct
id|amd_page_map
op_star
op_star
id|gatt_pages
suffix:semicolon
DECL|member|num_tables
r_int
id|num_tables
suffix:semicolon
DECL|variable|amd_irongate_private
)brace
id|amd_irongate_private
suffix:semicolon
DECL|function|amd_create_page_map
r_static
r_int
id|amd_create_page_map
c_func
(paren
r_struct
id|amd_page_map
op_star
id|page_map
)paren
(brace
r_int
id|i
suffix:semicolon
id|page_map-&gt;real
op_assign
(paren
r_int
r_int
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_map-&gt;real
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page_map-&gt;real
)paren
)paren
suffix:semicolon
id|CACHE_FLUSH
c_func
(paren
)paren
suffix:semicolon
id|page_map-&gt;remapped
op_assign
id|ioremap_nocache
c_func
(paren
id|virt_to_phys
c_func
(paren
id|page_map-&gt;real
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_map-&gt;remapped
op_eq
l_int|NULL
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page_map-&gt;real
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page_map-&gt;real
)paren
suffix:semicolon
id|page_map-&gt;real
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|CACHE_FLUSH
c_func
(paren
)paren
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page_map-&gt;remapped
(braket
id|i
)braket
op_assign
id|agp_bridge.scratch_page
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_free_page_map
r_static
r_void
id|amd_free_page_map
c_func
(paren
r_struct
id|amd_page_map
op_star
id|page_map
)paren
(brace
id|iounmap
c_func
(paren
id|page_map-&gt;remapped
)paren
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page_map-&gt;real
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page_map-&gt;real
)paren
suffix:semicolon
)brace
DECL|function|amd_free_gatt_pages
r_static
r_void
id|amd_free_gatt_pages
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|amd_page_map
op_star
op_star
id|tables
suffix:semicolon
r_struct
id|amd_page_map
op_star
id|entry
suffix:semicolon
id|tables
op_assign
id|amd_irongate_private.gatt_pages
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
id|amd_irongate_private.num_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|tables
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;real
op_ne
l_int|NULL
)paren
(brace
id|amd_free_page_map
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|tables
)paren
suffix:semicolon
)brace
DECL|function|amd_create_gatt_pages
r_static
r_int
id|amd_create_gatt_pages
c_func
(paren
r_int
id|nr_tables
)paren
(brace
r_struct
id|amd_page_map
op_star
op_star
id|tables
suffix:semicolon
r_struct
id|amd_page_map
op_star
id|entry
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|tables
op_assign
id|kmalloc
c_func
(paren
(paren
id|nr_tables
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|amd_page_map
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tables
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|tables
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|amd_page_map
op_star
)paren
op_star
(paren
id|nr_tables
op_plus
l_int|1
)paren
)paren
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
id|nr_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|amd_page_map
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|amd_page_map
)paren
)paren
suffix:semicolon
id|tables
(braket
id|i
)braket
op_assign
id|entry
suffix:semicolon
id|retval
op_assign
id|amd_create_page_map
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|amd_irongate_private.num_tables
op_assign
id|nr_tables
suffix:semicolon
id|amd_irongate_private.gatt_pages
op_assign
id|tables
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
id|amd_free_gatt_pages
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Since we don&squot;t need contigious memory we just try&n; * to get the gatt table once&n; */
DECL|macro|GET_PAGE_DIR_OFF
mdefine_line|#define GET_PAGE_DIR_OFF(addr) (addr &gt;&gt; 22)
DECL|macro|GET_PAGE_DIR_IDX
mdefine_line|#define GET_PAGE_DIR_IDX(addr) (GET_PAGE_DIR_OFF(addr) - &bslash;&n;&t;GET_PAGE_DIR_OFF(agp_bridge.gart_bus_addr))
DECL|macro|GET_GATT_OFF
mdefine_line|#define GET_GATT_OFF(addr) ((addr &amp; 0x003ff000) &gt;&gt; 12) 
DECL|macro|GET_GATT
mdefine_line|#define GET_GATT(addr) (amd_irongate_private.gatt_pages[&bslash;&n;&t;GET_PAGE_DIR_IDX(addr)]-&gt;remapped)
DECL|function|amd_create_gatt_table
r_static
r_int
id|amd_create_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_lvl2
op_star
id|value
suffix:semicolon
r_struct
id|amd_page_map
id|page_dir
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|value
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.current_size
)paren
suffix:semicolon
id|retval
op_assign
id|amd_create_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
r_return
id|retval
suffix:semicolon
)brace
id|retval
op_assign
id|amd_create_gatt_pages
c_func
(paren
id|value-&gt;num_entries
op_div
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|amd_free_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|agp_bridge.gatt_table_real
op_assign
id|page_dir.real
suffix:semicolon
id|agp_bridge.gatt_table
op_assign
id|page_dir.remapped
suffix:semicolon
id|agp_bridge.gatt_bus_addr
op_assign
id|virt_to_phys
c_func
(paren
id|page_dir.real
)paren
suffix:semicolon
multiline_comment|/* Get the address for the gart region.&n;&t; * This is a bus address even on the alpha, b/c its&n;&t; * used to program the agp master not the cpu&n;&t; */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_APBASE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
id|agp_bridge.gart_bus_addr
op_assign
id|addr
suffix:semicolon
multiline_comment|/* Calculate the agp offset */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|value-&gt;num_entries
op_div
l_int|1024
suffix:semicolon
id|i
op_increment
comma
id|addr
op_add_assign
l_int|0x00400000
)paren
(brace
id|page_dir.remapped
(braket
id|GET_PAGE_DIR_OFF
c_func
(paren
id|addr
)paren
)braket
op_assign
id|virt_to_phys
c_func
(paren
id|amd_irongate_private.gatt_pages
(braket
id|i
)braket
op_member_access_from_pointer
id|real
)paren
suffix:semicolon
id|page_dir.remapped
(braket
id|GET_PAGE_DIR_OFF
c_func
(paren
id|addr
)paren
)braket
op_or_assign
l_int|0x00000001
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_free_gatt_table
r_static
r_int
id|amd_free_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|amd_page_map
id|page_dir
suffix:semicolon
id|page_dir.real
op_assign
id|agp_bridge.gatt_table_real
suffix:semicolon
id|page_dir.remapped
op_assign
id|agp_bridge.gatt_table
suffix:semicolon
id|amd_free_gatt_pages
c_func
(paren
)paren
suffix:semicolon
id|amd_free_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_irongate_fetch_size
r_static
r_int
id|amd_irongate_fetch_size
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_struct
id|aper_size_info_lvl2
op_star
id|values
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_amp
l_int|0x0000000e
)paren
suffix:semicolon
id|values
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.aperture_sizes
)paren
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
id|agp_bridge.num_aperture_sizes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|temp
op_eq
id|values
(braket
id|i
)braket
dot
id|size_value
)paren
(brace
id|agp_bridge.previous_size
op_assign
id|agp_bridge.current_size
op_assign
(paren
r_void
op_star
)paren
(paren
id|values
op_plus
id|i
)paren
suffix:semicolon
id|agp_bridge.aperture_size_idx
op_assign
id|i
suffix:semicolon
r_return
id|values
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_irongate_configure
r_static
r_int
id|amd_irongate_configure
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_lvl2
op_star
id|current_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|u16
id|enable_reg
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.current_size
)paren
suffix:semicolon
multiline_comment|/* Get the memory mapped registers */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_MMBASE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
id|amd_irongate_private.registers
op_assign
(paren
r_volatile
id|u8
op_star
)paren
id|ioremap
c_func
(paren
id|temp
comma
l_int|4096
)paren
suffix:semicolon
multiline_comment|/* Write out the address of the gatt table */
id|OUTREG32
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_ATTBASE
comma
id|agp_bridge.gatt_bus_addr
)paren
suffix:semicolon
multiline_comment|/* Write the Sync register */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_MODECNTL
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Set indexing mode */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_MODECNTL2
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Write the enable register */
id|enable_reg
op_assign
id|INREG16
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_GARTENABLE
)paren
suffix:semicolon
id|enable_reg
op_assign
(paren
id|enable_reg
op_or
l_int|0x0004
)paren
suffix:semicolon
id|OUTREG16
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_GARTENABLE
comma
id|enable_reg
)paren
suffix:semicolon
multiline_comment|/* Write out the size register */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
(paren
(paren
id|temp
op_amp
op_complement
(paren
l_int|0x0000000e
)paren
)paren
op_or
id|current_size-&gt;size_value
)paren
op_or
l_int|0x00000001
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_APSIZE
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* Flush the tlb */
id|OUTREG32
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_TLBFLUSH
comma
l_int|0x00000001
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_irongate_cleanup
r_static
r_void
id|amd_irongate_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_lvl2
op_star
id|previous_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|u16
id|enable_reg
suffix:semicolon
id|previous_size
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.previous_size
)paren
suffix:semicolon
id|enable_reg
op_assign
id|INREG16
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_GARTENABLE
)paren
suffix:semicolon
id|enable_reg
op_assign
(paren
id|enable_reg
op_amp
op_complement
(paren
l_int|0x0004
)paren
)paren
suffix:semicolon
id|OUTREG16
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_GARTENABLE
comma
id|enable_reg
)paren
suffix:semicolon
multiline_comment|/* Write back the previous size and disable gart translation */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
(paren
id|temp
op_amp
op_complement
(paren
l_int|0x0000000f
)paren
)paren
op_or
id|previous_size-&gt;size_value
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|AMD_APSIZE
comma
id|temp
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|amd_irongate_private.registers
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine could be implemented by taking the addresses&n; * written to the GATT, and flushing them individually.  However&n; * currently it just flushes the whole table.  Which is probably&n; * more efficent, since agp_memory blocks can be a large number of&n; * entries.&n; */
DECL|function|amd_irongate_tlbflush
r_static
r_void
id|amd_irongate_tlbflush
c_func
(paren
id|agp_memory
op_star
id|temp
)paren
(brace
id|OUTREG32
c_func
(paren
id|amd_irongate_private.registers
comma
id|AMD_TLBFLUSH
comma
l_int|0x00000001
)paren
suffix:semicolon
)brace
DECL|function|amd_irongate_mask_memory
r_static
r_int
r_int
id|amd_irongate_mask_memory
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|type
)paren
(brace
multiline_comment|/* Only type 0 is supported by the irongate */
r_return
id|addr
op_or
id|agp_bridge.masks
(braket
l_int|0
)braket
dot
id|mask
suffix:semicolon
)brace
DECL|function|amd_insert_memory
r_static
r_int
id|amd_insert_memory
c_func
(paren
id|agp_memory
op_star
id|mem
comma
id|off_t
id|pg_start
comma
r_int
id|type
)paren
(brace
r_int
id|i
comma
id|j
comma
id|num_entries
suffix:semicolon
r_int
r_int
op_star
id|cur_gatt
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.current_size
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
l_int|0
op_logical_or
id|mem-&gt;type
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
)paren
OG
id|num_entries
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|j
op_assign
id|pg_start
suffix:semicolon
r_while
c_loop
(paren
id|j
OL
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
)paren
)paren
(brace
id|addr
op_assign
(paren
id|j
op_star
id|PAGE_SIZE
)paren
op_plus
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PGE_EMPTY
c_func
(paren
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)braket
)paren
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mem-&gt;is_flushed
op_eq
id|FALSE
)paren
(brace
id|CACHE_FLUSH
c_func
(paren
)paren
suffix:semicolon
id|mem-&gt;is_flushed
op_assign
id|TRUE
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
id|pg_start
suffix:semicolon
id|i
OL
id|mem-&gt;page_count
suffix:semicolon
id|i
op_increment
comma
id|j
op_increment
)paren
(brace
id|addr
op_assign
(paren
id|j
op_star
id|PAGE_SIZE
)paren
op_plus
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)braket
op_assign
id|mem-&gt;memory
(braket
id|i
)braket
suffix:semicolon
)brace
id|agp_bridge
dot
id|tlb_flush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_remove_memory
r_static
r_int
id|amd_remove_memory
c_func
(paren
id|agp_memory
op_star
id|mem
comma
id|off_t
id|pg_start
comma
r_int
id|type
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|cur_gatt
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
l_int|0
op_logical_or
id|mem-&gt;type
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|pg_start
suffix:semicolon
id|i
OL
(paren
id|mem-&gt;page_count
op_plus
id|pg_start
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|addr
op_assign
(paren
id|i
op_star
id|PAGE_SIZE
)paren
op_plus
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)braket
op_assign
(paren
r_int
r_int
)paren
id|agp_bridge.scratch_page
suffix:semicolon
)brace
id|agp_bridge
dot
id|tlb_flush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|amd_irongate_sizes
r_static
r_struct
id|aper_size_info_lvl2
id|amd_irongate_sizes
(braket
l_int|7
)braket
op_assign
(brace
(brace
l_int|2048
comma
l_int|524288
comma
l_int|0x0000000c
)brace
comma
(brace
l_int|1024
comma
l_int|262144
comma
l_int|0x0000000a
)brace
comma
(brace
l_int|512
comma
l_int|131072
comma
l_int|0x00000008
)brace
comma
(brace
l_int|256
comma
l_int|65536
comma
l_int|0x00000006
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|0x00000004
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|0x00000002
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|0x00000000
)brace
)brace
suffix:semicolon
DECL|variable|amd_irongate_masks
r_static
r_struct
id|gatt_mask
id|amd_irongate_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
l_int|0x00000001
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|amd_irongate_setup
r_int
id|__init
id|amd_irongate_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|agp_bridge.masks
op_assign
id|amd_irongate_masks
suffix:semicolon
id|agp_bridge.num_of_masks
op_assign
l_int|1
suffix:semicolon
id|agp_bridge.aperture_sizes
op_assign
(paren
r_void
op_star
)paren
id|amd_irongate_sizes
suffix:semicolon
id|agp_bridge.size_type
op_assign
id|LVL2_APER_SIZE
suffix:semicolon
id|agp_bridge.num_aperture_sizes
op_assign
l_int|7
suffix:semicolon
id|agp_bridge.dev_private_data
op_assign
(paren
r_void
op_star
)paren
op_amp
id|amd_irongate_private
suffix:semicolon
id|agp_bridge.needs_scratch_page
op_assign
id|FALSE
suffix:semicolon
id|agp_bridge.configure
op_assign
id|amd_irongate_configure
suffix:semicolon
id|agp_bridge.fetch_size
op_assign
id|amd_irongate_fetch_size
suffix:semicolon
id|agp_bridge.cleanup
op_assign
id|amd_irongate_cleanup
suffix:semicolon
id|agp_bridge.tlb_flush
op_assign
id|amd_irongate_tlbflush
suffix:semicolon
id|agp_bridge.mask_memory
op_assign
id|amd_irongate_mask_memory
suffix:semicolon
id|agp_bridge.agp_enable
op_assign
id|agp_generic_agp_enable
suffix:semicolon
id|agp_bridge.cache_flush
op_assign
id|global_cache_flush
suffix:semicolon
id|agp_bridge.create_gatt_table
op_assign
id|amd_create_gatt_table
suffix:semicolon
id|agp_bridge.free_gatt_table
op_assign
id|amd_free_gatt_table
suffix:semicolon
id|agp_bridge.insert_memory
op_assign
id|amd_insert_memory
suffix:semicolon
id|agp_bridge.remove_memory
op_assign
id|amd_remove_memory
suffix:semicolon
id|agp_bridge.alloc_by_type
op_assign
id|agp_generic_alloc_by_type
suffix:semicolon
id|agp_bridge.free_by_type
op_assign
id|agp_generic_free_by_type
suffix:semicolon
id|agp_bridge.agp_alloc_page
op_assign
id|agp_generic_alloc_page
suffix:semicolon
id|agp_bridge.agp_destroy_page
op_assign
id|agp_generic_destroy_page
suffix:semicolon
id|agp_bridge.suspend
op_assign
id|agp_generic_suspend
suffix:semicolon
id|agp_bridge.resume
op_assign
id|agp_generic_resume
suffix:semicolon
id|agp_bridge.cant_use_aperture
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
(paren
r_void
)paren
id|pdev
suffix:semicolon
multiline_comment|/* unused */
)brace
eof
