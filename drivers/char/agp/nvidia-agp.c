multiline_comment|/*&n; * Nvidia AGPGART routines.&n; * Based upon a 2.4 agpgart diff by the folks from NVIDIA, and hacked up&n; * to work in 2.5 by Dave Jones &lt;davej@codemonkey.org.uk&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/page-flags.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/* registers */
DECL|macro|NVIDIA_0_APBASE
mdefine_line|#define NVIDIA_0_APBASE&t;&t;0x10
DECL|macro|NVIDIA_0_APSIZE
mdefine_line|#define NVIDIA_0_APSIZE&t;&t;0x80
DECL|macro|NVIDIA_1_WBC
mdefine_line|#define NVIDIA_1_WBC&t;&t;0xf0
DECL|macro|NVIDIA_2_GARTCTRL
mdefine_line|#define NVIDIA_2_GARTCTRL&t;0xd0
DECL|macro|NVIDIA_2_APBASE
mdefine_line|#define NVIDIA_2_APBASE&t;&t;0xd8
DECL|macro|NVIDIA_2_APLIMIT
mdefine_line|#define NVIDIA_2_APLIMIT&t;0xdc
DECL|macro|NVIDIA_2_ATTBASE
mdefine_line|#define NVIDIA_2_ATTBASE(i)&t;(0xe0 + (i) * 4)
DECL|macro|NVIDIA_3_APBASE
mdefine_line|#define NVIDIA_3_APBASE&t;&t;0x50
DECL|macro|NVIDIA_3_APLIMIT
mdefine_line|#define NVIDIA_3_APLIMIT&t;0x54
DECL|struct|_nvidia_private
r_static
r_struct
id|_nvidia_private
(brace
DECL|member|dev_1
r_struct
id|pci_dev
op_star
id|dev_1
suffix:semicolon
DECL|member|dev_2
r_struct
id|pci_dev
op_star
id|dev_2
suffix:semicolon
DECL|member|dev_3
r_struct
id|pci_dev
op_star
id|dev_3
suffix:semicolon
DECL|member|aperture
r_volatile
id|u32
op_star
id|aperture
suffix:semicolon
DECL|member|num_active_entries
r_int
id|num_active_entries
suffix:semicolon
DECL|member|pg_offset
id|off_t
id|pg_offset
suffix:semicolon
DECL|member|wbc_mask
id|u32
id|wbc_mask
suffix:semicolon
DECL|variable|nvidia_private
)brace
id|nvidia_private
suffix:semicolon
DECL|function|nvidia_fetch_size
r_static
r_int
id|nvidia_fetch_size
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u8
id|size_value
suffix:semicolon
r_struct
id|aper_size_info_8
op_star
id|values
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
op_amp
id|size_value
)paren
suffix:semicolon
id|size_value
op_and_assign
l_int|0x0f
suffix:semicolon
id|values
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge-&gt;driver-&gt;aperture_sizes
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
id|agp_bridge-&gt;driver-&gt;num_aperture_sizes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|size_value
op_eq
id|values
(braket
id|i
)braket
dot
id|size_value
)paren
(brace
id|agp_bridge-&gt;previous_size
op_assign
id|agp_bridge-&gt;current_size
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
id|agp_bridge-&gt;aperture_size_idx
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
DECL|function|nvidia_configure
r_static
r_int
id|nvidia_configure
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|num_dirs
suffix:semicolon
id|u32
id|apbase
comma
id|aplimit
suffix:semicolon
r_struct
id|aper_size_info_8
op_star
id|current_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
multiline_comment|/* aperture size */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
id|current_size-&gt;size_value
)paren
suffix:semicolon
multiline_comment|/* address to map to */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APBASE
comma
op_amp
id|apbase
)paren
suffix:semicolon
id|apbase
op_and_assign
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|agp_bridge-&gt;gart_bus_addr
op_assign
id|apbase
suffix:semicolon
id|aplimit
op_assign
id|apbase
op_plus
(paren
id|current_size-&gt;size
op_star
l_int|1024
op_star
l_int|1024
)paren
op_minus
l_int|1
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_APBASE
comma
id|apbase
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_APLIMIT
comma
id|aplimit
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_3
comma
id|NVIDIA_3_APBASE
comma
id|apbase
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_3
comma
id|NVIDIA_3_APLIMIT
comma
id|aplimit
)paren
suffix:semicolon
multiline_comment|/* directory size is 64k */
id|num_dirs
op_assign
id|current_size-&gt;size
op_div
l_int|64
suffix:semicolon
id|nvidia_private.num_active_entries
op_assign
id|current_size-&gt;num_entries
suffix:semicolon
id|nvidia_private.pg_offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num_dirs
op_eq
l_int|0
)paren
(brace
id|num_dirs
op_assign
l_int|1
suffix:semicolon
id|nvidia_private.num_active_entries
op_div_assign
(paren
l_int|64
op_div
id|current_size-&gt;size
)paren
suffix:semicolon
id|nvidia_private.pg_offset
op_assign
(paren
id|apbase
op_amp
(paren
l_int|64
op_star
l_int|1024
op_star
l_int|1024
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|current_size-&gt;size
op_star
l_int|1024
op_star
l_int|1024
op_minus
l_int|1
)paren
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/* attbase */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_ATTBASE
c_func
(paren
id|i
)paren
comma
(paren
id|agp_bridge-&gt;gatt_bus_addr
op_plus
(paren
id|i
op_mod
id|num_dirs
)paren
op_star
l_int|64
op_star
l_int|1024
)paren
op_or
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* gtlb control */
id|pci_read_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_GARTCTRL
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_GARTCTRL
comma
id|temp
op_or
l_int|0x11
)paren
suffix:semicolon
multiline_comment|/* gart control */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
id|temp
op_or
l_int|0x100
)paren
suffix:semicolon
multiline_comment|/* map aperture */
id|nvidia_private.aperture
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ioremap
c_func
(paren
id|apbase
comma
l_int|33
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nvidia_cleanup
r_static
r_void
id|nvidia_cleanup
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
id|u32
id|temp
suffix:semicolon
multiline_comment|/* gart control */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
id|temp
op_amp
op_complement
(paren
l_int|0x100
)paren
)paren
suffix:semicolon
multiline_comment|/* gtlb control */
id|pci_read_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_GARTCTRL
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_2
comma
id|NVIDIA_2_GARTCTRL
comma
id|temp
op_amp
op_complement
(paren
l_int|0x11
)paren
)paren
suffix:semicolon
multiline_comment|/* unmap aperture */
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|nvidia_private.aperture
)paren
suffix:semicolon
multiline_comment|/* restore previous aperture size */
id|previous_size
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge-&gt;previous_size
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|NVIDIA_0_APSIZE
comma
id|previous_size-&gt;size_value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note we can&squot;t use the generic routines, even though they are 99% the same.&n; * Aperture sizes &lt;64M still requires a full 64k GART directory, but&n; * only use the portion of the TLB entries that correspond to the apertures&n; * alignment inside the surrounding 64M block.&n; */
r_extern
r_int
id|agp_memory_reserved
suffix:semicolon
DECL|function|nvidia_insert_memory
r_static
r_int
id|nvidia_insert_memory
c_func
(paren
r_struct
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
suffix:semicolon
r_if
c_cond
(paren
(paren
id|type
op_ne
l_int|0
)paren
op_logical_or
(paren
id|mem-&gt;type
op_ne
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
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
(paren
id|nvidia_private.num_active_entries
op_minus
id|agp_memory_reserved
op_div
id|PAGE_SIZE
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|pg_start
suffix:semicolon
id|j
OL
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PGE_EMPTY
c_func
(paren
id|agp_bridge
comma
id|agp_bridge-&gt;gatt_table
(braket
id|nvidia_private.pg_offset
op_plus
id|j
)braket
)paren
)paren
r_return
op_minus
id|EBUSY
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
id|global_cache_flush
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
id|agp_bridge-&gt;gatt_table
(braket
id|nvidia_private.pg_offset
op_plus
id|j
)braket
op_assign
id|agp_bridge-&gt;driver
op_member_access_from_pointer
id|mask_memory
c_func
(paren
id|mem-&gt;memory
(braket
id|i
)braket
comma
id|mem-&gt;type
)paren
suffix:semicolon
id|agp_bridge-&gt;driver
op_member_access_from_pointer
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
DECL|function|nvidia_remove_memory
r_static
r_int
id|nvidia_remove_memory
c_func
(paren
r_struct
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
(paren
id|type
op_ne
l_int|0
)paren
op_logical_or
(paren
id|mem-&gt;type
op_ne
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
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
id|agp_bridge-&gt;gatt_table
(braket
id|nvidia_private.pg_offset
op_plus
id|i
)braket
op_assign
(paren
r_int
r_int
)paren
id|agp_bridge-&gt;scratch_page
suffix:semicolon
)brace
id|agp_bridge-&gt;driver
op_member_access_from_pointer
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
DECL|function|nvidia_tlbflush
r_static
r_void
id|nvidia_tlbflush
c_func
(paren
r_struct
id|agp_memory
op_star
id|mem
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|u32
id|wbc_reg
comma
id|temp
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* flush chipset */
r_if
c_cond
(paren
id|nvidia_private.wbc_mask
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|nvidia_private.dev_1
comma
id|NVIDIA_1_WBC
comma
op_amp
id|wbc_reg
)paren
suffix:semicolon
id|wbc_reg
op_or_assign
id|nvidia_private.wbc_mask
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nvidia_private.dev_1
comma
id|NVIDIA_1_WBC
comma
id|wbc_reg
)paren
suffix:semicolon
id|end
op_assign
id|jiffies
op_plus
l_int|3
op_star
id|HZ
suffix:semicolon
r_do
(brace
id|pci_read_config_dword
c_func
(paren
id|nvidia_private.dev_1
comma
id|NVIDIA_1_WBC
comma
op_amp
id|wbc_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|end
op_minus
id|jiffies
)paren
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;TLB flush took more than 3 seconds.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|wbc_reg
op_amp
id|nvidia_private.wbc_mask
)paren
suffix:semicolon
)brace
multiline_comment|/* flush TLB entries */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
op_assign
id|nvidia_private.aperture
(braket
id|i
op_star
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|u32
)paren
)braket
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
l_int|32
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
op_assign
id|nvidia_private.aperture
(braket
id|i
op_star
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
)brace
)brace
DECL|variable|nvidia_generic_sizes
r_static
r_struct
id|aper_size_info_8
id|nvidia_generic_sizes
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|512
comma
l_int|131072
comma
l_int|7
comma
l_int|0
)brace
comma
(brace
l_int|256
comma
l_int|65536
comma
l_int|6
comma
l_int|8
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
comma
l_int|12
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|14
)brace
comma
multiline_comment|/* The 32M mode still requires a 64k gatt */
(brace
l_int|32
comma
l_int|16384
comma
l_int|4
comma
l_int|15
)brace
)brace
suffix:semicolon
DECL|variable|nvidia_generic_masks
r_static
r_struct
id|gatt_mask
id|nvidia_generic_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
l_int|1
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|nvidia_driver
r_struct
id|agp_bridge_driver
id|nvidia_driver
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
id|nvidia_generic_sizes
comma
dot
id|size_type
op_assign
id|U8_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|5
comma
dot
id|configure
op_assign
id|nvidia_configure
comma
dot
id|fetch_size
op_assign
id|nvidia_fetch_size
comma
dot
id|cleanup
op_assign
id|nvidia_cleanup
comma
dot
id|tlb_flush
op_assign
id|nvidia_tlbflush
comma
dot
id|mask_memory
op_assign
id|agp_generic_mask_memory
comma
dot
id|masks
op_assign
id|nvidia_generic_masks
comma
dot
id|agp_enable
op_assign
id|agp_generic_enable
comma
dot
id|cache_flush
op_assign
id|global_cache_flush
comma
dot
id|create_gatt_table
op_assign
id|agp_generic_create_gatt_table
comma
dot
id|free_gatt_table
op_assign
id|agp_generic_free_gatt_table
comma
dot
id|insert_memory
op_assign
id|nvidia_insert_memory
comma
dot
id|remove_memory
op_assign
id|nvidia_remove_memory
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
)brace
suffix:semicolon
DECL|function|agp_nvidia_probe
r_static
r_int
id|__init
id|agp_nvidia_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_struct
id|agp_bridge_data
op_star
id|bridge
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
id|nvidia_private.dev_1
op_assign
id|pci_find_slot
c_func
(paren
(paren
r_int
r_int
)paren
id|pdev-&gt;bus-&gt;number
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|1
)paren
)paren
suffix:semicolon
id|nvidia_private.dev_2
op_assign
id|pci_find_slot
c_func
(paren
(paren
r_int
r_int
)paren
id|pdev-&gt;bus-&gt;number
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|2
)paren
)paren
suffix:semicolon
id|nvidia_private.dev_3
op_assign
id|pci_find_slot
c_func
(paren
(paren
r_int
r_int
)paren
id|pdev-&gt;bus-&gt;number
comma
id|PCI_DEVFN
c_func
(paren
l_int|30
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nvidia_private.dev_1
op_logical_or
op_logical_neg
id|nvidia_private.dev_2
op_logical_or
op_logical_neg
id|nvidia_private.dev_3
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected an NVIDIA nForce/nForce2 &quot;
l_string|&quot;chipset, but could not find the secondary devices.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|pdev
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cap_ptr
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|pdev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_NVIDIA_NFORCE
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected NVIDIA nForce chipset&bslash;n&quot;
)paren
suffix:semicolon
id|nvidia_private.wbc_mask
op_assign
l_int|0x00010000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_NVIDIA_NFORCE2
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected NVIDIA nForce2 chipset&bslash;n&quot;
)paren
suffix:semicolon
id|nvidia_private.wbc_mask
op_assign
l_int|0x80000000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unsupported NVIDIA chipset (device id: %04x)&bslash;n&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|bridge
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
id|bridge
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|bridge-&gt;driver
op_assign
op_amp
id|nvidia_driver
suffix:semicolon
id|bridge-&gt;dev_private_data
op_assign
op_amp
id|nvidia_private
comma
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* Fill in the mode register */
id|pci_read_config_dword
c_func
(paren
id|pdev
comma
id|bridge-&gt;capndx
op_plus
id|PCI_AGP_STATUS
comma
op_amp
id|bridge-&gt;mode
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|bridge
)paren
suffix:semicolon
r_return
id|agp_add_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
)brace
DECL|function|agp_nvidia_remove
r_static
r_void
id|__devexit
id|agp_nvidia_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|agp_bridge_data
op_star
id|bridge
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|agp_remove_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
id|agp_put_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
)brace
DECL|variable|agp_nvidia_pci_table
r_static
r_struct
id|pci_device_id
id|agp_nvidia_pci_table
(braket
)braket
op_assign
(brace
(brace
dot
r_class
op_assign
(paren
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
)paren
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_ANY_ID
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|agp_nvidia_pci_table
)paren
suffix:semicolon
DECL|variable|agp_nvidia_pci_driver
r_static
r_struct
id|pci_driver
id|agp_nvidia_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-nvidia&quot;
comma
dot
id|id_table
op_assign
id|agp_nvidia_pci_table
comma
dot
id|probe
op_assign
id|agp_nvidia_probe
comma
dot
id|remove
op_assign
id|agp_nvidia_remove
comma
)brace
suffix:semicolon
DECL|function|agp_nvidia_init
r_static
r_int
id|__init
id|agp_nvidia_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|agp_nvidia_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|agp_nvidia_cleanup
r_static
r_void
id|__exit
id|agp_nvidia_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_nvidia_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_nvidia_init
id|module_init
c_func
(paren
id|agp_nvidia_init
)paren
suffix:semicolon
DECL|variable|agp_nvidia_cleanup
id|module_exit
c_func
(paren
id|agp_nvidia_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;NVIDIA Corporation&quot;
)paren
suffix:semicolon
eof
