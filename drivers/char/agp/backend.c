multiline_comment|/*&n; * AGPGART driver backend routines.&n; * Copyright (C) 2002-2003 Dave Jones.&n; * Copyright (C) 1999 Jeff Hartmann.&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, DAVE JONES, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * TODO: &n; * - Allocate more than order 0 pages to avoid too much linear map splitting.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/agpgart.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/* Due to XFree86 brain-damage, we can&squot;t go to 1.0 until they&n; * fix some real stupidity. It&squot;s only by chance we can bump&n; * past 0.99 at all due to some boolean logic error. */
DECL|macro|AGPGART_VERSION_MAJOR
mdefine_line|#define AGPGART_VERSION_MAJOR 0
DECL|macro|AGPGART_VERSION_MINOR
mdefine_line|#define AGPGART_VERSION_MINOR 100
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
DECL|variable|agp_count
r_static
r_int
id|agp_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|agp_bridge_dummy
r_struct
id|agp_bridge_data
id|agp_bridge_dummy
op_assign
(brace
dot
id|type
op_assign
id|NOT_SUPPORTED
)brace
suffix:semicolon
DECL|variable|agp_bridge
r_struct
id|agp_bridge_data
op_star
id|agp_bridge
op_assign
op_amp
id|agp_bridge_dummy
suffix:semicolon
DECL|variable|agp_bridge
id|EXPORT_SYMBOL
c_func
(paren
id|agp_bridge
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;agp_backend_acquire  -  attempt to acquire the agp backend.&n; *&n; *&t;returns -EBUSY if agp is in use,&n; *&t;returns 0 if the caller owns the agp backend&n; */
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
id|agp_bridge-&gt;type
op_eq
id|NOT_SUPPORTED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|agp_bridge-&gt;agp_in_use
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|agp_bridge-&gt;agp_in_use
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|agp_backend_acquire
id|EXPORT_SYMBOL
c_func
(paren
id|agp_backend_acquire
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;agp_backend_release  -  release the lock on the agp backend.&n; *&n; *&t;The caller must insure that the graphics aperture translation table&n; *&t;is read for use by another entity.&n; *&n; *&t;(Ensure that all memory it bound is unbound.)&n; */
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
id|agp_bridge-&gt;type
op_ne
id|NOT_SUPPORTED
)paren
id|atomic_dec
c_func
(paren
op_amp
id|agp_bridge-&gt;agp_in_use
)paren
suffix:semicolon
)brace
DECL|variable|agp_backend_release
id|EXPORT_SYMBOL
c_func
(paren
id|agp_backend_release
)paren
suffix:semicolon
DECL|member|mem
DECL|member|agp
DECL|variable|maxes_table
r_struct
(brace
r_int
id|mem
comma
id|agp
suffix:semicolon
)brace
id|maxes_table
(braket
)braket
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
id|agp_find_max
c_func
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
macro_line|#if PAGE_SHIFT &lt; 20
id|memory
op_assign
id|num_physpages
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
macro_line|#else
id|memory
op_assign
id|num_physpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|20
)paren
suffix:semicolon
macro_line|#endif
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
DECL|function|agp_backend_initialize
r_static
r_int
id|agp_backend_initialize
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
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
id|bridge-&gt;max_memory_agp
op_assign
id|agp_find_max
c_func
(paren
)paren
suffix:semicolon
id|bridge-&gt;version
op_assign
op_amp
id|agp_current_version
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;driver-&gt;needs_scratch_page
)paren
(brace
r_void
op_star
id|addr
op_assign
id|bridge-&gt;driver
op_member_access_from_pointer
id|agp_alloc_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
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
id|bridge-&gt;scratch_page_real
op_assign
id|virt_to_phys
c_func
(paren
id|addr
)paren
suffix:semicolon
id|bridge-&gt;scratch_page
op_assign
id|bridge-&gt;driver
op_member_access_from_pointer
id|mask_memory
c_func
(paren
id|bridge-&gt;scratch_page_real
comma
l_int|0
)paren
suffix:semicolon
)brace
id|size_value
op_assign
id|bridge-&gt;driver
op_member_access_from_pointer
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
id|bridge-&gt;driver
op_member_access_from_pointer
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
id|bridge-&gt;key_list
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
id|bridge-&gt;key_list
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
id|bridge-&gt;key_list
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
id|bridge-&gt;driver
op_member_access_from_pointer
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
id|bridge-&gt;gart_bus_addr
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
id|bridge-&gt;driver-&gt;needs_scratch_page
)paren
id|bridge-&gt;driver
op_member_access_from_pointer
id|agp_destroy_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|bridge-&gt;scratch_page_real
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|got_gatt
)paren
id|bridge-&gt;driver
op_member_access_from_pointer
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
(brace
id|vfree
c_func
(paren
id|bridge-&gt;key_list
)paren
suffix:semicolon
id|bridge-&gt;key_list
op_assign
l_int|NULL
suffix:semicolon
)brace
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
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
r_if
c_cond
(paren
id|bridge-&gt;driver-&gt;cleanup
)paren
id|bridge-&gt;driver
op_member_access_from_pointer
id|cleanup
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;driver-&gt;free_gatt_table
)paren
id|bridge-&gt;driver
op_member_access_from_pointer
id|free_gatt_table
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;key_list
)paren
(brace
id|vfree
c_func
(paren
id|bridge-&gt;key_list
)paren
suffix:semicolon
id|bridge-&gt;key_list
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bridge-&gt;driver-&gt;agp_destroy_page
op_logical_and
id|bridge-&gt;driver-&gt;needs_scratch_page
)paren
id|bridge-&gt;driver
op_member_access_from_pointer
id|agp_destroy_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|bridge-&gt;scratch_page_real
)paren
)paren
suffix:semicolon
)brace
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
multiline_comment|/* XXX Kludge alert: agpgart isn&squot;t ready for multiple bridges yet */
DECL|function|agp_alloc_bridge
r_struct
id|agp_bridge_data
op_star
id|agp_alloc_bridge
c_func
(paren
r_void
)paren
(brace
r_return
id|agp_bridge
suffix:semicolon
)brace
DECL|variable|agp_alloc_bridge
id|EXPORT_SYMBOL
c_func
(paren
id|agp_alloc_bridge
)paren
suffix:semicolon
DECL|function|agp_put_bridge
r_void
id|agp_put_bridge
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
)brace
DECL|variable|agp_put_bridge
id|EXPORT_SYMBOL
c_func
(paren
id|agp_put_bridge
)paren
suffix:semicolon
DECL|function|agp_add_bridge
r_int
id|agp_add_bridge
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge-&gt;dev
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;Erk, registering with no pci_dev!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|agp_count
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Only one agpgart device currently supported.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Grab reference on the chipset driver. */
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|bridge-&gt;driver-&gt;owner
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Couldn&squot;t lock chipset driver.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bridge-&gt;type
op_assign
id|SUPPORTED
suffix:semicolon
id|error
op_assign
id|agp_backend_initialize
c_func
(paren
id|agp_bridge
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;agp_backend_initialize() failed.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|error
op_assign
id|agp_frontend_initialize
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;agp_frontend_initialize() failed.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|frontend_err
suffix:semicolon
)brace
multiline_comment|/* FIXME: What to do with this? */
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
id|agp_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|frontend_err
suffix:colon
id|agp_backend_cleanup
c_func
(paren
id|agp_bridge
)paren
suffix:semicolon
id|err_out
suffix:colon
id|bridge-&gt;type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
id|module_put
c_func
(paren
id|bridge-&gt;driver-&gt;owner
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|agp_add_bridge
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|agp_add_bridge
)paren
suffix:semicolon
DECL|function|agp_remove_bridge
r_void
id|agp_remove_bridge
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
id|bridge-&gt;type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
id|agp_frontend_cleanup
c_func
(paren
)paren
suffix:semicolon
id|agp_backend_cleanup
c_func
(paren
id|bridge
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
id|module_put
c_func
(paren
id|bridge-&gt;driver-&gt;owner
)paren
suffix:semicolon
)brace
DECL|variable|agp_remove_bridge
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|agp_remove_bridge
)paren
suffix:semicolon
DECL|variable|agp_off
r_int
id|agp_off
suffix:semicolon
DECL|variable|agp_try_unsupported_boot
r_int
id|agp_try_unsupported_boot
suffix:semicolon
DECL|variable|agp_off
id|EXPORT_SYMBOL
c_func
(paren
id|agp_off
)paren
suffix:semicolon
DECL|variable|agp_try_unsupported_boot
id|EXPORT_SYMBOL
c_func
(paren
id|agp_try_unsupported_boot
)paren
suffix:semicolon
DECL|function|agp_init
r_static
r_int
id|__init
id|agp_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|agp_off
)paren
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
DECL|function|agp_exit
r_void
id|__exit
id|agp_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#ifndef MODULE
DECL|function|agp_setup
r_static
id|__init
r_int
id|agp_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
l_string|&quot;off&quot;
)paren
)paren
id|agp_off
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
l_string|&quot;try_unsupported&quot;
)paren
)paren
id|agp_try_unsupported_boot
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;agp=&quot;
comma
id|agp_setup
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AGP GART driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
DECL|variable|AGPGART_MINOR
id|MODULE_ALIAS_MISCDEV
c_func
(paren
id|AGPGART_MINOR
)paren
suffix:semicolon
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
eof
