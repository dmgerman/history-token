macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/agp_backend.h&gt;
macro_line|#include &quot;../../../arch/alpha/kernel/pci_impl.h&quot;
macro_line|#include &quot;agp.h&quot;
DECL|function|alpha_core_agp_vm_nopage
r_static
r_struct
id|page
op_star
id|alpha_core_agp_vm_nopage
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|write_access
)paren
(brace
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
r_int
r_int
id|pa
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|dma_addr
op_assign
id|address
op_minus
id|vma-&gt;vm_start
op_plus
id|agp-&gt;aperture.bus_base
suffix:semicolon
id|pa
op_assign
id|agp-&gt;ops
op_member_access_from_pointer
id|translate
c_func
(paren
id|agp
comma
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pa
op_eq
(paren
r_int
r_int
)paren
op_minus
id|EINVAL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* no translation */
multiline_comment|/*&n;&t; * Get the page, inc the use count, and return it&n;&t; */
id|page
op_assign
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|pa
)paren
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|variable|alpha_core_agp_sizes
r_static
r_struct
id|aper_size_info_fixed
id|alpha_core_agp_sizes
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* filled in by alpha_core_agp_setup */
)brace
suffix:semicolon
DECL|variable|alpha_core_agp_vm_ops
r_struct
id|vm_operations_struct
id|alpha_core_agp_vm_ops
op_assign
(brace
dot
id|nopage
op_assign
id|alpha_core_agp_vm_nopage
comma
)brace
suffix:semicolon
DECL|function|alpha_core_agp_nop
r_static
r_int
id|alpha_core_agp_nop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* just return success */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alpha_core_agp_fetch_size
r_static
r_int
id|alpha_core_agp_fetch_size
c_func
(paren
r_void
)paren
(brace
r_return
id|alpha_core_agp_sizes
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
)brace
DECL|function|alpha_core_agp_configure
r_static
r_int
id|alpha_core_agp_configure
c_func
(paren
r_void
)paren
(brace
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
id|agp_bridge-&gt;gart_bus_addr
op_assign
id|agp-&gt;aperture.bus_base
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alpha_core_agp_cleanup
r_static
r_void
id|alpha_core_agp_cleanup
c_func
(paren
r_void
)paren
(brace
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
id|agp-&gt;ops
op_member_access_from_pointer
id|cleanup
c_func
(paren
id|agp
)paren
suffix:semicolon
)brace
DECL|function|alpha_core_agp_tlbflush
r_static
r_void
id|alpha_core_agp_tlbflush
c_func
(paren
id|agp_memory
op_star
id|mem
)paren
(brace
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
id|alpha_mv
dot
id|mv_pci_tbi
c_func
(paren
id|agp-&gt;hose
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|alpha_core_agp_enable
r_static
r_void
id|alpha_core_agp_enable
c_func
(paren
id|u32
id|mode
)paren
(brace
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
id|agp-&gt;mode.lw
op_assign
id|agp_collect_device_status
c_func
(paren
id|mode
comma
id|agp-&gt;capability.lw
)paren
suffix:semicolon
id|agp-&gt;mode.bits.enable
op_assign
l_int|1
suffix:semicolon
id|agp-&gt;ops
op_member_access_from_pointer
id|configure
c_func
(paren
id|agp
)paren
suffix:semicolon
id|agp_device_command
c_func
(paren
id|agp-&gt;mode.lw
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|alpha_core_agp_insert_memory
r_static
r_int
id|alpha_core_agp_insert_memory
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
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
r_int
id|num_entries
comma
id|status
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
id|temp
op_assign
id|agp_bridge-&gt;current_size
suffix:semicolon
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
id|status
op_assign
id|agp-&gt;ops
op_member_access_from_pointer
id|bind
c_func
(paren
id|agp
comma
id|pg_start
comma
id|mem
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|alpha_core_agp_tlbflush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|alpha_core_agp_remove_memory
r_static
r_int
id|alpha_core_agp_remove_memory
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
id|alpha_agp_info
op_star
id|agp
op_assign
id|agp_bridge-&gt;dev_private_data
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|agp-&gt;ops
op_member_access_from_pointer
id|unbind
c_func
(paren
id|agp
comma
id|pg_start
comma
id|mem
)paren
suffix:semicolon
id|alpha_core_agp_tlbflush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|variable|alpha_core_agp_driver
r_struct
id|agp_bridge_driver
id|alpha_core_agp_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|aperture_sizes
op_assign
id|aper_size
comma
dot
id|current_size
op_assign
id|aper_size
comma
multiline_comment|/* only one entry */
dot
id|size_type
op_assign
id|FIXED_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|1
comma
dot
id|configure
op_assign
id|alpha_core_agp_configure
comma
dot
id|fetch_size
op_assign
id|alpha_core_agp_fetch_size
comma
dot
id|cleanup
op_assign
id|alpha_core_agp_cleanup
comma
dot
id|tlb_flush
op_assign
id|alpha_core_agp_tlbflush
comma
dot
id|mask_memory
op_assign
id|agp_generic_mask_memory
comma
dot
id|masks
op_assign
l_int|NULL
comma
dot
id|agp_enable
op_assign
id|alpha_core_agp_enable
comma
dot
id|cache_flush
op_assign
id|global_cache_flush
comma
dot
id|create_gatt_table
op_assign
id|alpha_core_agp_nop
comma
dot
id|free_gatt_table
op_assign
id|alpha_core_agp_nop
comma
dot
id|insert_memory
op_assign
id|alpha_core_agp_insert_memory
comma
dot
id|remove_memory
op_assign
id|alpha_core_agp_remove_memory
comma
dot
id|alloc_by_type
op_assign
id|agp_generic_alloc_by_type
comma
dot
id|free_by_type
op_assign
id|agp_generic_free_by_type
comma
dot
id|agp_alloc_page
op_assign
id|agp_generic_alloc_page
comma
dot
id|agp_destroy_page
op_assign
id|agp_generic_destroy_page
comma
dot
id|mode
op_assign
id|agp-&gt;capability.lw
comma
dot
id|cant_use_aperture
op_assign
l_int|1
comma
dot
id|vm_ops
op_assign
op_amp
id|alpha_core_agp_vm_ops
comma
)brace
suffix:semicolon
DECL|variable|alpha_bridge
r_struct
id|agp_bridge_data
op_star
id|alpha_bridge
suffix:semicolon
r_int
id|__init
DECL|function|alpha_core_agp_setup
id|alpha_core_agp_setup
c_func
(paren
r_void
)paren
(brace
id|alpha_agp_info
op_star
id|agp
op_assign
id|alpha_mv
dot
id|agp_info
c_func
(paren
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* faked */
r_struct
id|aper_size_info_fixed
op_star
id|aper_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|agp
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|agp-&gt;ops
op_member_access_from_pointer
id|setup
c_func
(paren
id|agp
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Build the aperture size descriptor&n;&t; */
id|aper_size
op_assign
id|alpha_core_agp_sizes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aper_size
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|aper_size-&gt;size
op_assign
id|agp-&gt;aperture.size
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|aper_size-&gt;num_entries
op_assign
id|agp-&gt;aperture.size
op_div
id|PAGE_SIZE
suffix:semicolon
id|aper_size-&gt;page_order
op_assign
id|ffs
c_func
(paren
id|aper_size-&gt;num_entries
op_div
l_int|1024
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Build a fake pci_dev struct&n;&t; */
id|pdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pdev-&gt;vendor
op_assign
l_int|0xffff
suffix:semicolon
id|pdev-&gt;device
op_assign
l_int|0xffff
suffix:semicolon
id|pdev-&gt;sysdata
op_assign
id|agp-&gt;hose
suffix:semicolon
id|alpha_bridge
op_assign
id|agp_alloc_bridge
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alpha_bridge
)paren
r_goto
id|fail
suffix:semicolon
id|alpha_bridge-&gt;driver
op_assign
op_amp
id|alpha_core_agp_driver
suffix:semicolon
id|alpha_bridge-&gt;dev_private_data
op_assign
id|agp
suffix:semicolon
id|alpha_bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Detected AGP on hose %d&bslash;n&quot;
comma
id|agp-&gt;hose-&gt;index
)paren
suffix:semicolon
r_return
id|agp_add_bridge
c_func
(paren
id|alpha_bridge
)paren
suffix:semicolon
id|fail
suffix:colon
id|kfree
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|agp_alpha_core_init
r_static
r_int
id|__init
id|agp_alpha_core_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|alpha_mv.agp_info
)paren
r_return
id|alpha_core_agp_setup
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|agp_alpha_core_cleanup
r_static
r_void
id|__exit
id|agp_alpha_core_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_remove_bridge
c_func
(paren
id|alpha_bridge
)paren
suffix:semicolon
id|agp_put_bridge
c_func
(paren
id|alpha_bridge
)paren
suffix:semicolon
)brace
DECL|variable|agp_alpha_core_init
id|module_init
c_func
(paren
id|agp_alpha_core_init
)paren
suffix:semicolon
DECL|variable|agp_alpha_core_cleanup
id|module_exit
c_func
(paren
id|agp_alpha_core_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jeff Wiedemeier &lt;Jeff.Wiedemeier@hp.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
