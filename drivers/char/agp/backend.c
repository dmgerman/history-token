multiline_comment|/*&n; * AGPGART module version 1.0&n; * Copyright (C) 2002 Dave Jones.&n; * Copyright (C) 1999 Jeff Hartmann.&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, DAVE JONES, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * TODO: &n; * - Allocate more than order 0 pages to avoid too much linear map splitting.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/* Due to XFree86 brain-damage, we can&squot;t go to 1.0 until they&n; * fix some real stupidity. It&squot;s only by chance we can bump&n; * past 0.99 at all due to some boolean logic error. */
DECL|macro|AGPGART_VERSION_MAJOR
mdefine_line|#define AGPGART_VERSION_MAJOR 0
DECL|macro|AGPGART_VERSION_MINOR
mdefine_line|#define AGPGART_VERSION_MINOR 100
DECL|variable|agp_bridge
r_struct
id|agp_bridge_data
id|agp_bridge
op_assign
(brace
dot
id|type
op_assign
id|NOT_SUPPORTED
)brace
suffix:semicolon
DECL|function|agp_backend_acquire
r_int
id|agp_backend_acquire
c_func
(paren
r_void
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
op_minus
id|EINVAL
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|agp_bridge.agp_in_use
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|agp_bridge.agp_in_use
)paren
op_ne
l_int|1
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|agp_bridge.agp_in_use
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_backend_release
r_void
id|agp_backend_release
c_func
(paren
r_void
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
id|atomic_dec
c_func
(paren
op_amp
id|agp_bridge.agp_in_use
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|struct|agp_max_table
r_struct
id|agp_max_table
(brace
DECL|member|mem
r_int
id|mem
suffix:semicolon
DECL|member|agp
r_int
id|agp
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|agp_max_table
id|maxes_table
(braket
l_int|9
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|32
comma
l_int|4
)brace
comma
(brace
l_int|64
comma
l_int|28
)brace
comma
(brace
l_int|128
comma
l_int|96
)brace
comma
(brace
l_int|256
comma
l_int|204
)brace
comma
(brace
l_int|512
comma
l_int|440
)brace
comma
(brace
l_int|1024
comma
l_int|942
)brace
comma
(brace
l_int|2048
comma
l_int|1920
)brace
comma
(brace
l_int|4096
comma
l_int|3932
)brace
)brace
suffix:semicolon
DECL|function|agp_find_max
r_static
r_int
id|__init
id|agp_find_max
(paren
r_void
)paren
(brace
r_int
id|memory
comma
id|index
comma
id|result
suffix:semicolon
id|memory
op_assign
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
op_rshift
l_int|20
suffix:semicolon
id|index
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|memory
OG
id|maxes_table
(braket
id|index
)braket
dot
id|mem
)paren
op_logical_and
(paren
id|index
OL
l_int|8
)paren
)paren
id|index
op_increment
suffix:semicolon
id|result
op_assign
id|maxes_table
(braket
id|index
op_minus
l_int|1
)braket
dot
id|agp
op_plus
(paren
(paren
id|memory
op_minus
id|maxes_table
(braket
id|index
op_minus
l_int|1
)braket
dot
id|mem
)paren
op_star
(paren
id|maxes_table
(braket
id|index
)braket
dot
id|agp
op_minus
id|maxes_table
(braket
id|index
op_minus
l_int|1
)braket
dot
id|agp
)paren
)paren
op_div
(paren
id|maxes_table
(braket
id|index
)braket
dot
id|mem
op_minus
id|maxes_table
(braket
id|index
op_minus
l_int|1
)braket
dot
id|mem
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Maximum main memory to use for agp memory: %ldM&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|result
op_assign
id|result
op_lshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|agp_current_version
r_static
r_struct
id|agp_version
id|agp_current_version
op_assign
(brace
dot
id|major
op_assign
id|AGPGART_VERSION_MAJOR
comma
dot
id|minor
op_assign
id|AGPGART_VERSION_MINOR
comma
)brace
suffix:semicolon
DECL|function|agp_backend_initialize
r_static
r_int
id|__init
id|agp_backend_initialize
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|size_value
comma
id|rc
comma
id|got_gatt
op_assign
l_int|0
comma
id|got_keylist
op_assign
l_int|0
suffix:semicolon
id|u8
id|cap_ptr
op_assign
l_int|0
suffix:semicolon
id|agp_bridge.max_memory_agp
op_assign
id|agp_find_max
c_func
(paren
)paren
suffix:semicolon
id|agp_bridge.version
op_assign
op_amp
id|agp_current_version
suffix:semicolon
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap_ptr
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|agp_bridge.capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* Fill in the mode register */
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
id|agp_bridge.mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.needs_scratch_page
op_eq
id|TRUE
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
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
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;unable to get memory for scratch page.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|agp_bridge.scratch_page
op_assign
id|virt_to_phys
c_func
(paren
id|addr
)paren
suffix:semicolon
id|agp_bridge.scratch_page
op_assign
id|agp_bridge
dot
id|mask_memory
c_func
(paren
id|agp_bridge.scratch_page
comma
l_int|0
)paren
suffix:semicolon
)brace
id|size_value
op_assign
id|agp_bridge
dot
id|fetch_size
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size_value
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;unable to determine aperture size.&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|agp_bridge
dot
id|create_gatt_table
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;unable to get memory for graphics translation table.&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|got_gatt
op_assign
l_int|1
suffix:semicolon
id|agp_bridge.key_list
op_assign
id|vmalloc
c_func
(paren
id|PAGE_SIZE
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.key_list
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;error allocating memory for key lists.&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|got_keylist
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* FIXME vmalloc&squot;d memory not guaranteed contiguous */
id|memset
c_func
(paren
id|agp_bridge.key_list
comma
l_int|0
comma
id|PAGE_SIZE
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge
dot
id|configure
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;error configuring host chipset.&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;AGP aperture is %dM @ 0x%lx&bslash;n&quot;
comma
id|size_value
comma
id|agp_bridge.gart_bus_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out
suffix:colon
r_if
c_cond
(paren
id|agp_bridge.needs_scratch_page
op_eq
id|TRUE
)paren
(brace
id|agp_bridge.scratch_page
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
id|agp_bridge.scratch_page
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|got_gatt
)paren
id|agp_bridge
dot
id|free_gatt_table
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|got_keylist
)paren
id|vfree
c_func
(paren
id|agp_bridge.key_list
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* cannot be __exit b/c as it could be called from __init code */
DECL|function|agp_backend_cleanup
r_static
r_void
id|agp_backend_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_bridge
dot
id|cleanup
c_func
(paren
)paren
suffix:semicolon
id|agp_bridge
dot
id|free_gatt_table
c_func
(paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|agp_bridge.key_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge.needs_scratch_page
op_eq
id|TRUE
)paren
(brace
id|agp_bridge.scratch_page
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
id|agp_bridge.scratch_page
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|agp_power
r_static
r_int
id|agp_power
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rq
comma
r_void
op_star
id|data
)paren
(brace
r_switch
c_cond
(paren
id|rq
)paren
(brace
r_case
id|PM_SUSPEND
suffix:colon
r_return
id|agp_bridge
dot
id|suspend
c_func
(paren
)paren
suffix:semicolon
r_case
id|PM_RESUME
suffix:colon
id|agp_bridge
dot
id|resume
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|agp_frontend_initialize
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|agp_frontend_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|drm_agp
r_static
r_const
id|drm_agp_t
id|drm_agp
op_assign
(brace
op_amp
id|agp_free_memory
comma
op_amp
id|agp_allocate_memory
comma
op_amp
id|agp_bind_memory
comma
op_amp
id|agp_unbind_memory
comma
op_amp
id|agp_enable
comma
op_amp
id|agp_backend_acquire
comma
op_amp
id|agp_backend_release
comma
op_amp
id|agp_copy_info
)brace
suffix:semicolon
DECL|variable|agp_count
r_static
r_int
id|agp_count
op_assign
l_int|0
suffix:semicolon
DECL|function|agp_register_driver
r_int
id|agp_register_driver
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|ret_val
suffix:semicolon
r_if
c_cond
(paren
id|agp_count
op_eq
l_int|1
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;Only one agpgart device currently supported.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ret_val
op_assign
id|agp_backend_initialize
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
)paren
(brace
id|agp_bridge.type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
id|ret_val
op_assign
id|agp_frontend_initialize
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
)paren
(brace
id|agp_bridge.type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
id|agp_backend_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
id|inter_module_register
c_func
(paren
l_string|&quot;drm_agp&quot;
comma
id|THIS_MODULE
comma
op_amp
id|drm_agp
)paren
suffix:semicolon
id|pm_register
c_func
(paren
id|PM_PCI_DEV
comma
id|PM_PCI_ID
c_func
(paren
id|agp_bridge.dev
)paren
comma
id|agp_power
)paren
suffix:semicolon
id|agp_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_unregister_driver
r_int
id|agp_unregister_driver
c_func
(paren
r_void
)paren
(brace
id|agp_bridge.type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
id|pm_unregister_all
c_func
(paren
id|agp_power
)paren
suffix:semicolon
id|agp_frontend_cleanup
c_func
(paren
)paren
suffix:semicolon
id|agp_backend_cleanup
c_func
(paren
)paren
suffix:semicolon
id|inter_module_unregister
c_func
(paren
l_string|&quot;drm_agp&quot;
)paren
suffix:semicolon
id|agp_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_exit
r_int
id|__exit
id|agp_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|agp_count
op_eq
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_init
r_int
id|__init
id|agp_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|already_initialised
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|already_initialised
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|already_initialised
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|agp_bridge
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|agp_bridge_data
)paren
)paren
suffix:semicolon
id|agp_bridge.type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux agpgart interface v%d.%d (c) Dave Jones&bslash;n&quot;
comma
id|AGPGART_VERSION_MAJOR
comma
id|AGPGART_VERSION_MINOR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_GART_IOMMU
DECL|variable|agp_init
id|module_init
c_func
(paren
id|agp_init
)paren
suffix:semicolon
DECL|variable|agp_exit
id|module_exit
c_func
(paren
id|agp_exit
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|agp_backend_acquire
id|EXPORT_SYMBOL
c_func
(paren
id|agp_backend_acquire
)paren
suffix:semicolon
DECL|variable|agp_backend_release
id|EXPORT_SYMBOL
c_func
(paren
id|agp_backend_release
)paren
suffix:semicolon
DECL|variable|agp_register_driver
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|agp_register_driver
)paren
suffix:semicolon
DECL|variable|agp_unregister_driver
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|agp_unregister_driver
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
