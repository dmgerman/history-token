multiline_comment|/*&n; * AGPGART module version 1.0&n; * Copyright (C) 2002 Dave Jones.&n; * Copyright (C) 1999 Jeff Hartmann.&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * TODO: &n; * - Allocate more than order 0 pages to avoid too much linear map splitting.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|variable|agp_gatt_table
id|__u32
op_star
id|agp_gatt_table
suffix:semicolon
DECL|variable|agp_memory_reserved
r_int
id|agp_memory_reserved
suffix:semicolon
multiline_comment|/* &n; * Generic routines for handling agp_memory structures -&n; * They use the basic page allocation routines to do the&n; * brunt of the work.&n; */
DECL|function|agp_free_key
r_void
id|agp_free_key
c_func
(paren
r_int
id|key
)paren
(brace
r_if
c_cond
(paren
id|key
OL
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|key
OL
id|MAXKEY
)paren
id|clear_bit
c_func
(paren
id|key
comma
id|agp_bridge.key_list
)paren
suffix:semicolon
)brace
DECL|function|agp_get_key
r_static
r_int
id|agp_get_key
c_func
(paren
r_void
)paren
(brace
r_int
id|bit
suffix:semicolon
id|bit
op_assign
id|find_first_zero_bit
c_func
(paren
id|agp_bridge.key_list
comma
id|MAXKEY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
id|MAXKEY
)paren
(brace
id|set_bit
c_func
(paren
id|bit
comma
id|agp_bridge.key_list
)paren
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|agp_create_memory
id|agp_memory
op_star
id|agp_create_memory
c_func
(paren
r_int
id|scratch_pages
)paren
(brace
id|agp_memory
op_star
r_new
suffix:semicolon
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|agp_memory
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
id|agp_memory
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|key
op_assign
id|agp_get_key
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|key
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|memory
op_assign
id|vmalloc
c_func
(paren
id|PAGE_SIZE
op_star
id|scratch_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|memory
op_eq
l_int|NULL
)paren
(brace
id|agp_free_key
c_func
(paren
r_new
op_member_access_from_pointer
id|key
)paren
suffix:semicolon
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|num_scratch_pages
op_assign
id|scratch_pages
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
DECL|function|agp_free_memory
r_void
id|agp_free_memory
c_func
(paren
id|agp_memory
op_star
id|curr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|agp_bridge.type
op_eq
id|NOT_SUPPORTED
)paren
op_logical_or
(paren
id|curr
op_eq
l_int|NULL
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|curr-&gt;is_bound
op_eq
id|TRUE
)paren
id|agp_unbind_memory
c_func
(paren
id|curr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr-&gt;type
op_ne
l_int|0
)paren
(brace
id|agp_bridge
dot
id|free_by_type
c_func
(paren
id|curr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|curr-&gt;page_count
op_ne
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|curr-&gt;page_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|curr-&gt;memory
(braket
id|i
)braket
op_and_assign
op_complement
(paren
l_int|0x00000fff
)paren
suffix:semicolon
id|agp_bridge
dot
id|agp_destroy_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|curr-&gt;memory
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
)brace
id|agp_free_key
c_func
(paren
id|curr-&gt;key
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|curr-&gt;memory
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|curr
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|macro|ENTRIES_PER_PAGE
mdefine_line|#define ENTRIES_PER_PAGE&t;&t;(PAGE_SIZE / sizeof(unsigned long))
DECL|function|agp_allocate_memory
id|agp_memory
op_star
id|agp_allocate_memory
c_func
(paren
r_int
id|page_count
comma
id|u32
id|type
)paren
(brace
r_int
id|scratch_pages
suffix:semicolon
id|agp_memory
op_star
r_new
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.type
op_eq
id|NOT_SUPPORTED
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|agp_bridge.current_memory_agp
)paren
op_plus
id|page_count
)paren
OG
id|agp_bridge.max_memory_agp
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
l_int|0
)paren
(brace
r_new
op_assign
id|agp_bridge
dot
id|alloc_by_type
c_func
(paren
id|page_count
comma
id|type
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
multiline_comment|/* We always increase the module count, since free auto-decrements it */
id|MOD_INC_USE_COUNT
suffix:semicolon
id|scratch_pages
op_assign
(paren
id|page_count
op_plus
id|ENTRIES_PER_PAGE
op_minus
l_int|1
)paren
op_div
id|ENTRIES_PER_PAGE
suffix:semicolon
r_new
op_assign
id|agp_create_memory
c_func
(paren
id|scratch_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|page_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_void
op_star
id|addr
op_assign
id|agp_bridge
dot
id|agp_alloc_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
l_int|NULL
)paren
(brace
id|agp_free_memory
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|memory
(braket
id|i
)braket
op_assign
id|agp_bridge
dot
id|mask_memory
c_func
(paren
id|virt_to_phys
c_func
(paren
id|addr
)paren
comma
id|type
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|page_count
op_increment
suffix:semicolon
)brace
id|flush_agp_mappings
c_func
(paren
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
multiline_comment|/* End - Generic routines for handling agp_memory structures */
DECL|function|agp_return_size
r_static
r_int
id|agp_return_size
c_func
(paren
r_void
)paren
(brace
r_int
id|current_size
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
id|temp
op_assign
id|agp_bridge.current_size
suffix:semicolon
r_switch
c_cond
(paren
id|agp_bridge.size_type
)paren
(brace
r_case
id|U8_APER_SIZE
suffix:colon
id|current_size
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U16_APER_SIZE
suffix:colon
id|current_size
op_assign
id|A_SIZE_16
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U32_APER_SIZE
suffix:colon
id|current_size
op_assign
id|A_SIZE_32
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL2_APER_SIZE
suffix:colon
id|current_size
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIXED_APER_SIZE
suffix:colon
id|current_size
op_assign
id|A_SIZE_FIX
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|current_size
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|current_size
op_sub_assign
(paren
id|agp_memory_reserved
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_size
OL
l_int|0
)paren
id|current_size
op_assign
l_int|0
suffix:semicolon
r_return
id|current_size
suffix:semicolon
)brace
multiline_comment|/* Routine to copy over information structure */
DECL|function|agp_copy_info
r_int
id|agp_copy_info
c_func
(paren
id|agp_kern_info
op_star
id|info
)paren
(brace
r_int
r_int
id|page_mask
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|agp_kern_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.type
op_eq
id|NOT_SUPPORTED
)paren
(brace
id|info-&gt;chipset
op_assign
id|agp_bridge.type
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|info-&gt;version.major
op_assign
id|agp_bridge.version-&gt;major
suffix:semicolon
id|info-&gt;version.minor
op_assign
id|agp_bridge.version-&gt;minor
suffix:semicolon
id|info-&gt;device
op_assign
id|agp_bridge.dev
suffix:semicolon
id|info-&gt;chipset
op_assign
id|agp_bridge.type
suffix:semicolon
id|info-&gt;mode
op_assign
id|agp_bridge.mode
suffix:semicolon
id|info-&gt;aper_base
op_assign
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|info-&gt;aper_size
op_assign
id|agp_return_size
c_func
(paren
)paren
suffix:semicolon
id|info-&gt;max_memory
op_assign
id|agp_bridge.max_memory_agp
suffix:semicolon
id|info-&gt;current_memory
op_assign
id|atomic_read
c_func
(paren
op_amp
id|agp_bridge.current_memory_agp
)paren
suffix:semicolon
id|info-&gt;cant_use_aperture
op_assign
id|agp_bridge.cant_use_aperture
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
id|agp_bridge.num_of_masks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page_mask
op_or_assign
id|agp_bridge
dot
id|mask_memory
c_func
(paren
id|page_mask
comma
id|i
)paren
suffix:semicolon
)brace
id|info-&gt;page_mask
op_assign
op_complement
id|page_mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* End - Routine to copy over information structure */
multiline_comment|/*&n; * Routines for handling swapping of agp_memory into the GATT -&n; * These routines take agp_memory and insert them into the GATT.&n; * They call device specific routines to actually write to the GATT.&n; */
DECL|function|agp_bind_memory
r_int
id|agp_bind_memory
c_func
(paren
id|agp_memory
op_star
id|curr
comma
id|off_t
id|pg_start
)paren
(brace
r_int
id|ret_val
suffix:semicolon
r_if
c_cond
(paren
(paren
id|agp_bridge.type
op_eq
id|NOT_SUPPORTED
)paren
op_logical_or
(paren
id|curr
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|curr-&gt;is_bound
op_eq
id|TRUE
)paren
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
id|curr-&gt;is_flushed
op_eq
id|FALSE
)paren
(brace
id|CACHE_FLUSH
c_func
(paren
)paren
suffix:semicolon
id|curr-&gt;is_flushed
op_assign
id|TRUE
suffix:semicolon
)brace
id|ret_val
op_assign
id|agp_bridge
dot
id|insert_memory
c_func
(paren
id|curr
comma
id|pg_start
comma
id|curr-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
op_ne
l_int|0
)paren
r_return
id|ret_val
suffix:semicolon
id|curr-&gt;is_bound
op_assign
id|TRUE
suffix:semicolon
id|curr-&gt;pg_start
op_assign
id|pg_start
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_unbind_memory
r_int
id|agp_unbind_memory
c_func
(paren
id|agp_memory
op_star
id|curr
)paren
(brace
r_int
id|ret_val
suffix:semicolon
r_if
c_cond
(paren
(paren
id|agp_bridge.type
op_eq
id|NOT_SUPPORTED
)paren
op_logical_or
(paren
id|curr
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|curr-&gt;is_bound
op_ne
id|TRUE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret_val
op_assign
id|agp_bridge
dot
id|remove_memory
c_func
(paren
id|curr
comma
id|curr-&gt;pg_start
comma
id|curr-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
op_ne
l_int|0
)paren
r_return
id|ret_val
suffix:semicolon
id|curr-&gt;is_bound
op_assign
id|FALSE
suffix:semicolon
id|curr-&gt;pg_start
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* End - Routines for handling swapping of agp_memory into the GATT */
multiline_comment|/* Generic Agp routines - Start */
DECL|function|agp_generic_agp_enable
r_void
id|agp_generic_agp_enable
c_func
(paren
id|u32
id|mode
)paren
(brace
r_struct
id|pci_dev
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|command
comma
id|scratch
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|agp_bridge.capndx
op_plus
l_int|4
comma
op_amp
id|command
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * PASS1: go through all devices that claim to be&n;&t; *        AGP devices and collect their data.&n;&t; */
id|pci_for_each_dev
c_func
(paren
id|device
)paren
(brace
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|device
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap_ptr
op_ne
l_int|0x00
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Ok, here we have a AGP device. Disable impossible &n;&t;&t;&t; * settings, and adjust the readqueue to the minimum.&n;&t;&t;&t; */
id|pci_read_config_dword
c_func
(paren
id|device
comma
id|cap_ptr
op_plus
l_int|4
comma
op_amp
id|scratch
)paren
suffix:semicolon
multiline_comment|/* adjust RQ depth */
id|command
op_assign
(paren
(paren
id|command
op_amp
op_complement
l_int|0xff000000
)paren
op_or
id|min_t
c_func
(paren
id|u32
comma
(paren
id|mode
op_amp
l_int|0xff000000
)paren
comma
id|min_t
c_func
(paren
id|u32
comma
(paren
id|command
op_amp
l_int|0xff000000
)paren
comma
(paren
id|scratch
op_amp
l_int|0xff000000
)paren
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* disable SBA if it&squot;s not supported */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|0x00000200
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|0x00000200
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|0x00000200
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000200
suffix:semicolon
multiline_comment|/* disable FW if it&squot;s not supported */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|0x00000010
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|0x00000010
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|0x00000010
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000010
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|4
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|4
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|4
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000004
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|2
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|2
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|2
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000002
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|1
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|1
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|1
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000001
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * PASS2: Figure out the 4X/2X/1X setting and enable the&n;&t; *        target (our motherboard chipset).&n;&t; */
r_if
c_cond
(paren
id|command
op_amp
l_int|4
)paren
id|command
op_and_assign
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* 4X */
r_if
c_cond
(paren
id|command
op_amp
l_int|2
)paren
id|command
op_and_assign
op_complement
l_int|5
suffix:semicolon
multiline_comment|/* 2X */
r_if
c_cond
(paren
id|command
op_amp
l_int|1
)paren
id|command
op_and_assign
op_complement
l_int|6
suffix:semicolon
multiline_comment|/* 1X */
id|command
op_or_assign
l_int|0x00000100
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|agp_bridge.capndx
op_plus
l_int|8
comma
id|command
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * PASS3: Go throu all AGP devices and update the&n;&t; *        command registers.&n;&t; */
id|pci_for_each_dev
c_func
(paren
id|device
)paren
(brace
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|device
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap_ptr
op_ne
l_int|0x00
)paren
id|pci_write_config_dword
c_func
(paren
id|device
comma
id|cap_ptr
op_plus
l_int|8
comma
id|command
)paren
suffix:semicolon
)brace
)brace
DECL|function|agp_generic_create_gatt_table
r_int
id|agp_generic_create_gatt_table
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|table
suffix:semicolon
r_char
op_star
id|table_end
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|page_order
suffix:semicolon
r_int
id|num_entries
suffix:semicolon
r_int
id|i
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/* The generic routines can&squot;t handle 2 level gatt&squot;s */
r_if
c_cond
(paren
id|agp_bridge.size_type
op_eq
id|LVL2_APER_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|table
op_assign
l_int|NULL
suffix:semicolon
id|i
op_assign
id|agp_bridge.aperture_size_idx
suffix:semicolon
id|temp
op_assign
id|agp_bridge.current_size
suffix:semicolon
id|size
op_assign
id|page_order
op_assign
id|num_entries
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.size_type
op_ne
id|FIXED_APER_SIZE
)paren
(brace
r_do
(brace
r_switch
c_cond
(paren
id|agp_bridge.size_type
)paren
(brace
r_case
id|U8_APER_SIZE
suffix:colon
id|size
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
id|page_order
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U16_APER_SIZE
suffix:colon
id|size
op_assign
id|A_SIZE_16
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
id|page_order
op_assign
id|A_SIZE_16
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_16
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U32_APER_SIZE
suffix:colon
id|size
op_assign
id|A_SIZE_32
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
id|page_order
op_assign
id|A_SIZE_32
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_32
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* This case will never really happen. */
r_case
id|FIXED_APER_SIZE
suffix:colon
r_case
id|LVL2_APER_SIZE
suffix:colon
r_default
suffix:colon
id|size
op_assign
id|page_order
op_assign
id|num_entries
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|table
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|page_order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|table
op_eq
l_int|NULL
)paren
(brace
id|i
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|agp_bridge.size_type
)paren
(brace
r_case
id|U8_APER_SIZE
suffix:colon
id|agp_bridge.current_size
op_assign
id|A_IDX8
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U16_APER_SIZE
suffix:colon
id|agp_bridge.current_size
op_assign
id|A_IDX16
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U32_APER_SIZE
suffix:colon
id|agp_bridge.current_size
op_assign
id|A_IDX32
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* This case will never really &n;&t;&t;&t;&t;&t; * happen. &n;&t;&t;&t;&t;&t; */
r_case
id|FIXED_APER_SIZE
suffix:colon
r_case
id|LVL2_APER_SIZE
suffix:colon
r_default
suffix:colon
id|agp_bridge.current_size
op_assign
id|agp_bridge.current_size
suffix:semicolon
r_break
suffix:semicolon
)brace
id|temp
op_assign
id|agp_bridge.current_size
suffix:semicolon
)brace
r_else
(brace
id|agp_bridge.aperture_size_idx
op_assign
id|i
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|table
op_eq
l_int|NULL
)paren
op_logical_and
(paren
id|i
OL
id|agp_bridge.num_aperture_sizes
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|size
op_assign
(paren
(paren
r_struct
id|aper_size_info_fixed
op_star
)paren
id|temp
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
id|page_order
op_assign
(paren
(paren
r_struct
id|aper_size_info_fixed
op_star
)paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
id|num_entries
op_assign
(paren
(paren
r_struct
id|aper_size_info_fixed
op_star
)paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
id|table
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|page_order
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|table
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|table_end
op_assign
id|table
op_plus
(paren
(paren
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|page_order
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|virt_to_page
c_func
(paren
id|table
)paren
suffix:semicolon
id|page
op_le
id|virt_to_page
c_func
(paren
id|table_end
)paren
suffix:semicolon
id|page
op_increment
)paren
id|SetPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|agp_bridge.gatt_table_real
op_assign
(paren
id|u32
op_star
)paren
id|table
suffix:semicolon
id|agp_gatt_table
op_assign
(paren
r_void
op_star
)paren
id|table
suffix:semicolon
id|CACHE_FLUSH
c_func
(paren
)paren
suffix:semicolon
id|agp_bridge.gatt_table
op_assign
id|ioremap_nocache
c_func
(paren
id|virt_to_phys
c_func
(paren
id|table
)paren
comma
(paren
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|page_order
)paren
)paren
)paren
suffix:semicolon
id|CACHE_FLUSH
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.gatt_table
op_eq
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|page
op_assign
id|virt_to_page
c_func
(paren
id|table
)paren
suffix:semicolon
id|page
op_le
id|virt_to_page
c_func
(paren
id|table_end
)paren
suffix:semicolon
id|page
op_increment
)paren
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|table
comma
id|page_order
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|agp_bridge.gatt_bus_addr
op_assign
id|virt_to_phys
c_func
(paren
id|agp_bridge.gatt_table_real
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
id|num_entries
suffix:semicolon
id|i
op_increment
)paren
id|agp_bridge.gatt_table
(braket
id|i
)braket
op_assign
(paren
r_int
r_int
)paren
id|agp_bridge.scratch_page
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_generic_suspend
r_int
id|agp_generic_suspend
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_generic_resume
r_void
id|agp_generic_resume
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|agp_generic_free_gatt_table
r_int
id|agp_generic_free_gatt_table
c_func
(paren
r_void
)paren
(brace
r_int
id|page_order
suffix:semicolon
r_char
op_star
id|table
comma
op_star
id|table_end
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|temp
op_assign
id|agp_bridge.current_size
suffix:semicolon
r_switch
c_cond
(paren
id|agp_bridge.size_type
)paren
(brace
r_case
id|U8_APER_SIZE
suffix:colon
id|page_order
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U16_APER_SIZE
suffix:colon
id|page_order
op_assign
id|A_SIZE_16
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U32_APER_SIZE
suffix:colon
id|page_order
op_assign
id|A_SIZE_32
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIXED_APER_SIZE
suffix:colon
id|page_order
op_assign
id|A_SIZE_FIX
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL2_APER_SIZE
suffix:colon
multiline_comment|/* The generic routines can&squot;t deal with 2 level gatt&squot;s */
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|page_order
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Do not worry about freeing memory, because if this is&n;&t; * called, then all agp memory is deallocated and removed&n;&t; * from the table.&n;&t; */
id|iounmap
c_func
(paren
id|agp_bridge.gatt_table
)paren
suffix:semicolon
id|table
op_assign
(paren
r_char
op_star
)paren
id|agp_bridge.gatt_table_real
suffix:semicolon
id|table_end
op_assign
id|table
op_plus
(paren
(paren
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|page_order
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|virt_to_page
c_func
(paren
id|table
)paren
suffix:semicolon
id|page
op_le
id|virt_to_page
c_func
(paren
id|table_end
)paren
suffix:semicolon
id|page
op_increment
)paren
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|agp_bridge.gatt_table_real
comma
id|page_order
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_generic_insert_memory
r_int
id|agp_generic_insert_memory
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
r_void
op_star
id|temp
suffix:semicolon
id|temp
op_assign
id|agp_bridge.current_size
suffix:semicolon
r_switch
c_cond
(paren
id|agp_bridge.size_type
)paren
(brace
r_case
id|U8_APER_SIZE
suffix:colon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U16_APER_SIZE
suffix:colon
id|num_entries
op_assign
id|A_SIZE_16
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
r_case
id|U32_APER_SIZE
suffix:colon
id|num_entries
op_assign
id|A_SIZE_32
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIXED_APER_SIZE
suffix:colon
id|num_entries
op_assign
id|A_SIZE_FIX
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL2_APER_SIZE
suffix:colon
multiline_comment|/* The generic routines can&squot;t deal with 2 level gatt&squot;s */
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|num_entries
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|num_entries
op_sub_assign
id|agp_memory_reserved
op_div
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|num_entries
OL
l_int|0
)paren
id|num_entries
op_assign
l_int|0
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
multiline_comment|/* The generic routines know nothing of memory types */
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
r_return
op_minus
id|EINVAL
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|PGE_EMPTY
c_func
(paren
id|agp_bridge.gatt_table
(braket
id|j
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
id|agp_bridge.gatt_table
(braket
id|j
)braket
op_assign
id|mem-&gt;memory
(braket
id|i
)braket
suffix:semicolon
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
DECL|function|agp_generic_remove_memory
r_int
id|agp_generic_remove_memory
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
multiline_comment|/* The generic routines know nothing of memory types */
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
id|agp_bridge.gatt_table
(braket
id|i
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
DECL|function|agp_generic_alloc_by_type
id|agp_memory
op_star
id|agp_generic_alloc_by_type
c_func
(paren
r_int
id|page_count
comma
r_int
id|type
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|agp_generic_free_by_type
r_void
id|agp_generic_free_by_type
c_func
(paren
id|agp_memory
op_star
id|curr
)paren
(brace
r_if
c_cond
(paren
id|curr-&gt;memory
op_ne
l_int|NULL
)paren
id|vfree
c_func
(paren
id|curr-&gt;memory
)paren
suffix:semicolon
id|agp_free_key
c_func
(paren
id|curr-&gt;key
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|curr
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Basic Page Allocation Routines -&n; * These routines handle page allocation&n; * and by default they reserve the allocated &n; * memory.  They also handle incrementing the&n; * current_memory_agp value, Which is checked&n; * against a maximum value.&n; */
DECL|function|agp_generic_alloc_page
r_void
op_star
id|agp_generic_alloc_page
c_func
(paren
r_void
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|map_page_into_agp
c_func
(paren
id|page
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageLocked
c_func
(paren
id|page
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|agp_bridge.current_memory_agp
)paren
suffix:semicolon
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|agp_generic_destroy_page
r_void
id|agp_generic_destroy_page
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|unmap_page_from_agp
c_func
(paren
id|page
)paren
suffix:semicolon
id|put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|agp_bridge.current_memory_agp
)paren
suffix:semicolon
)brace
multiline_comment|/* End Basic Page Allocation Routines */
DECL|function|agp_enable
r_void
id|agp_enable
c_func
(paren
id|u32
id|mode
)paren
(brace
r_if
c_cond
(paren
id|agp_bridge.type
op_eq
id|NOT_SUPPORTED
)paren
r_return
suffix:semicolon
id|agp_bridge
dot
id|agp_enable
c_func
(paren
id|mode
)paren
suffix:semicolon
)brace
DECL|variable|agp_free_memory
id|EXPORT_SYMBOL
c_func
(paren
id|agp_free_memory
)paren
suffix:semicolon
DECL|variable|agp_allocate_memory
id|EXPORT_SYMBOL
c_func
(paren
id|agp_allocate_memory
)paren
suffix:semicolon
DECL|variable|agp_copy_info
id|EXPORT_SYMBOL
c_func
(paren
id|agp_copy_info
)paren
suffix:semicolon
DECL|variable|agp_bind_memory
id|EXPORT_SYMBOL
c_func
(paren
id|agp_bind_memory
)paren
suffix:semicolon
DECL|variable|agp_unbind_memory
id|EXPORT_SYMBOL
c_func
(paren
id|agp_unbind_memory
)paren
suffix:semicolon
DECL|variable|agp_enable
id|EXPORT_SYMBOL
c_func
(paren
id|agp_enable
)paren
suffix:semicolon
eof
