multiline_comment|/*&n; * AGPGART module version 0.99&n; * Copyright (C) 1999 Jeff Hartmann&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * TODO: &n; * - Allocate more than order 0 pages to avoid too much linear map splitting.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
macro_line|#include &quot;via.h&quot;
DECL|function|via_fetch_size
r_static
r_int
id|via_fetch_size
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u8
id|temp
suffix:semicolon
r_struct
id|aper_size_info_8
op_star
id|values
suffix:semicolon
id|values
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge.aperture_sizes
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_APSIZE
comma
op_amp
id|temp
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
DECL|function|via_configure
r_static
r_int
id|via_configure
c_func
(paren
r_void
)paren
(brace
id|u32
id|temp
suffix:semicolon
r_struct
id|aper_size_info_8
op_star
id|current_size
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge.current_size
)paren
suffix:semicolon
multiline_comment|/* aperture size */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_APSIZE
comma
id|current_size-&gt;size_value
)paren
suffix:semicolon
multiline_comment|/* address to map too */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_APBASE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|agp_bridge.gart_bus_addr
op_assign
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
multiline_comment|/* GART control register */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_GARTCTRL
comma
l_int|0x0000000f
)paren
suffix:semicolon
multiline_comment|/* attbase - aperture GATT base */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_ATTBASE
comma
(paren
id|agp_bridge.gatt_bus_addr
op_amp
l_int|0xfffff000
)paren
op_or
l_int|3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|via_cleanup
r_static
r_void
id|via_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_8
op_star
id|previous_size
suffix:semicolon
id|previous_size
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge.previous_size
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_APSIZE
comma
id|previous_size-&gt;size_value
)paren
suffix:semicolon
multiline_comment|/* Do not disable by writing 0 to VIA_ATTBASE, it screws things up&n;&t; * during reinitialization.&n;&t; */
)brace
DECL|function|via_tlbflush
r_static
r_void
id|via_tlbflush
c_func
(paren
id|agp_memory
op_star
id|mem
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_GARTCTRL
comma
l_int|0x0000008f
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|VIA_GARTCTRL
comma
l_int|0x0000000f
)paren
suffix:semicolon
)brace
DECL|function|via_mask_memory
r_static
r_int
r_int
id|via_mask_memory
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
multiline_comment|/* Memory type is ignored */
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
DECL|variable|via_generic_sizes
r_static
r_struct
id|aper_size_info_8
id|via_generic_sizes
(braket
l_int|7
)braket
op_assign
(brace
(brace
l_int|256
comma
l_int|65536
comma
l_int|6
comma
l_int|0
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
comma
l_int|128
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|192
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
comma
l_int|224
)brace
comma
(brace
l_int|16
comma
l_int|4096
comma
l_int|2
comma
l_int|240
)brace
comma
(brace
l_int|8
comma
l_int|2048
comma
l_int|1
comma
l_int|248
)brace
comma
(brace
l_int|4
comma
l_int|1024
comma
l_int|0
comma
l_int|252
)brace
)brace
suffix:semicolon
DECL|variable|via_generic_masks
r_static
r_struct
id|gatt_mask
id|via_generic_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
l_int|0x00000000
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|via_generic_setup
r_int
id|__init
id|via_generic_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|agp_bridge.masks
op_assign
id|via_generic_masks
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
id|via_generic_sizes
suffix:semicolon
id|agp_bridge.size_type
op_assign
id|U8_APER_SIZE
suffix:semicolon
id|agp_bridge.num_aperture_sizes
op_assign
l_int|7
suffix:semicolon
id|agp_bridge.dev_private_data
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge.needs_scratch_page
op_assign
id|FALSE
suffix:semicolon
id|agp_bridge.configure
op_assign
id|via_configure
suffix:semicolon
id|agp_bridge.fetch_size
op_assign
id|via_fetch_size
suffix:semicolon
id|agp_bridge.cleanup
op_assign
id|via_cleanup
suffix:semicolon
id|agp_bridge.tlb_flush
op_assign
id|via_tlbflush
suffix:semicolon
id|agp_bridge.mask_memory
op_assign
id|via_mask_memory
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
id|agp_generic_create_gatt_table
suffix:semicolon
id|agp_bridge.free_gatt_table
op_assign
id|agp_generic_free_gatt_table
suffix:semicolon
id|agp_bridge.insert_memory
op_assign
id|agp_generic_insert_memory
suffix:semicolon
id|agp_bridge.remove_memory
op_assign
id|agp_generic_remove_memory
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
