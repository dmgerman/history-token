multiline_comment|/*&n; * ALi AGPGART routines.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|variable|__initdata
r_static
r_int
id|agp_try_unsupported
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|function|ali_fetch_size
r_static
r_int
id|ali_fetch_size
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
id|aper_size_info_32
op_star
id|values
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_ATTBASE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
(paren
l_int|0xfffffff0
)paren
suffix:semicolon
id|values
op_assign
id|A_SIZE_32
c_func
(paren
id|agp_bridge-&gt;aperture_sizes
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
id|agp_bridge-&gt;num_aperture_sizes
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
DECL|function|ali_tlbflush
r_static
r_void
id|ali_tlbflush
c_func
(paren
id|agp_memory
op_star
id|mem
)paren
(brace
id|u32
id|temp
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TLBCTRL
comma
op_amp
id|temp
)paren
suffix:semicolon
singleline_comment|// clear tag
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TAGCTRL
comma
(paren
(paren
id|temp
op_amp
l_int|0xfffffff0
)paren
op_or
l_int|0x00000001
op_or
l_int|0x00000002
)paren
)paren
suffix:semicolon
)brace
DECL|function|ali_cleanup
r_static
r_void
id|ali_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_32
op_star
id|previous_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|previous_size
op_assign
id|A_SIZE_32
c_func
(paren
id|agp_bridge-&gt;previous_size
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TLBCTRL
comma
op_amp
id|temp
)paren
suffix:semicolon
singleline_comment|// clear tag
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TAGCTRL
comma
(paren
(paren
id|temp
op_amp
l_int|0xffffff00
)paren
op_or
l_int|0x00000001
op_or
l_int|0x00000002
)paren
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_ATTBASE
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
id|ALI_ATTBASE
comma
(paren
(paren
id|temp
op_amp
l_int|0x00000ff0
)paren
op_or
id|previous_size-&gt;size_value
)paren
)paren
suffix:semicolon
)brace
DECL|function|ali_configure
r_static
r_int
id|ali_configure
c_func
(paren
r_void
)paren
(brace
id|u32
id|temp
suffix:semicolon
r_struct
id|aper_size_info_32
op_star
id|current_size
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_32
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
multiline_comment|/* aperture size and gatt addr */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_ATTBASE
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
l_int|0x00000ff0
)paren
op_or
(paren
id|agp_bridge-&gt;gatt_bus_addr
op_amp
l_int|0xfffff000
)paren
)paren
op_or
(paren
id|current_size-&gt;size_value
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_ATTBASE
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* tlb control */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TLBCTRL
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
id|ALI_TLBCTRL
comma
(paren
(paren
id|temp
op_amp
l_int|0xffffff00
)paren
op_or
l_int|0x00000010
)paren
)paren
suffix:semicolon
multiline_comment|/* address to map to */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_APBASE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|agp_bridge-&gt;gart_bus_addr
op_assign
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|agp_bridge-&gt;type
op_eq
id|ALI_M1541
)paren
(brace
id|u32
id|nlvm_addr
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|current_size-&gt;size_value
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|nlvm_addr
op_assign
l_int|0x100000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|nlvm_addr
op_assign
l_int|0x200000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|nlvm_addr
op_assign
l_int|0x400000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|nlvm_addr
op_assign
l_int|0x800000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|nlvm_addr
op_assign
l_int|0x1000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|nlvm_addr
op_assign
l_int|0x2000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|nlvm_addr
op_assign
l_int|0x4000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|nlvm_addr
op_assign
l_int|0x8000000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|nlvm_addr
op_assign
l_int|0x10000000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|nlvm_addr
op_decrement
suffix:semicolon
id|nlvm_addr
op_and_assign
l_int|0xfff00000
suffix:semicolon
id|nlvm_addr
op_add_assign
id|agp_bridge-&gt;gart_bus_addr
suffix:semicolon
id|nlvm_addr
op_or_assign
(paren
id|agp_bridge-&gt;gart_bus_addr
op_rshift
l_int|12
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;nlvm top &amp;base = %8x&bslash;n&quot;
comma
id|nlvm_addr
)paren
suffix:semicolon
)brace
macro_line|#endif
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TLBCTRL
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
l_int|0xffffff7f
suffix:semicolon
singleline_comment|//enable TLB
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_TLBCTRL
comma
id|temp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ali_mask_memory
r_static
r_int
r_int
id|ali_mask_memory
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
id|agp_bridge-&gt;masks
(braket
l_int|0
)braket
dot
id|mask
suffix:semicolon
)brace
DECL|function|ali_cache_flush
r_static
r_void
id|ali_cache_flush
c_func
(paren
r_void
)paren
(brace
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge-&gt;type
op_eq
id|ALI_M1541
)paren
(brace
r_int
id|i
comma
id|page_count
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|page_count
op_assign
l_int|1
op_lshift
id|A_SIZE_32
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
op_member_access_from_pointer
id|page_order
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
op_star
id|page_count
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_CACHE_FLUSH_CTRL
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
id|ALI_CACHE_FLUSH_CTRL
comma
(paren
(paren
(paren
id|temp
op_amp
id|ALI_CACHE_FLUSH_ADDR_MASK
)paren
op_or
(paren
id|agp_bridge-&gt;gatt_bus_addr
op_plus
id|i
)paren
)paren
op_or
id|ALI_CACHE_FLUSH_EN
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|ali_alloc_page
r_static
r_void
op_star
id|ali_alloc_page
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|adr
op_assign
id|agp_generic_alloc_page
c_func
(paren
)paren
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|adr
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge-&gt;type
op_eq
id|ALI_M1541
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_CACHE_FLUSH_CTRL
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
id|ALI_CACHE_FLUSH_CTRL
comma
(paren
(paren
(paren
id|temp
op_amp
id|ALI_CACHE_FLUSH_ADDR_MASK
)paren
op_or
id|virt_to_phys
c_func
(paren
id|adr
)paren
)paren
op_or
id|ALI_CACHE_FLUSH_EN
)paren
)paren
suffix:semicolon
)brace
r_return
id|adr
suffix:semicolon
)brace
DECL|function|ali_destroy_page
r_static
r_void
id|ali_destroy_page
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|u32
id|temp
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
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge-&gt;type
op_eq
id|ALI_M1541
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|ALI_CACHE_FLUSH_CTRL
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
id|ALI_CACHE_FLUSH_CTRL
comma
(paren
(paren
(paren
id|temp
op_amp
id|ALI_CACHE_FLUSH_ADDR_MASK
)paren
op_or
id|virt_to_phys
c_func
(paren
id|addr
)paren
)paren
op_or
id|ALI_CACHE_FLUSH_EN
)paren
)paren
suffix:semicolon
)brace
id|agp_generic_destroy_page
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup function */
DECL|variable|ali_generic_masks
r_static
r_struct
id|gatt_mask
id|ali_generic_masks
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
DECL|variable|ali_generic_sizes
r_static
r_struct
id|aper_size_info_32
id|ali_generic_sizes
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
l_int|10
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
comma
l_int|9
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|8
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
comma
l_int|7
)brace
comma
(brace
l_int|16
comma
l_int|4096
comma
l_int|2
comma
l_int|6
)brace
comma
(brace
l_int|8
comma
l_int|2048
comma
l_int|1
comma
l_int|4
)brace
comma
(brace
l_int|4
comma
l_int|1024
comma
l_int|0
comma
l_int|3
)brace
)brace
suffix:semicolon
DECL|function|ali_generic_setup
r_static
r_int
id|__init
id|ali_generic_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|agp_bridge-&gt;masks
op_assign
id|ali_generic_masks
suffix:semicolon
id|agp_bridge-&gt;aperture_sizes
op_assign
(paren
r_void
op_star
)paren
id|ali_generic_sizes
suffix:semicolon
id|agp_bridge-&gt;size_type
op_assign
id|U32_APER_SIZE
suffix:semicolon
id|agp_bridge-&gt;num_aperture_sizes
op_assign
l_int|7
suffix:semicolon
id|agp_bridge-&gt;dev_private_data
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge-&gt;needs_scratch_page
op_assign
id|FALSE
suffix:semicolon
id|agp_bridge-&gt;configure
op_assign
id|ali_configure
suffix:semicolon
id|agp_bridge-&gt;fetch_size
op_assign
id|ali_fetch_size
suffix:semicolon
id|agp_bridge-&gt;cleanup
op_assign
id|ali_cleanup
suffix:semicolon
id|agp_bridge-&gt;tlb_flush
op_assign
id|ali_tlbflush
suffix:semicolon
id|agp_bridge-&gt;mask_memory
op_assign
id|ali_mask_memory
suffix:semicolon
id|agp_bridge-&gt;agp_enable
op_assign
id|agp_generic_agp_enable
suffix:semicolon
id|agp_bridge-&gt;cache_flush
op_assign
id|ali_cache_flush
suffix:semicolon
id|agp_bridge-&gt;create_gatt_table
op_assign
id|agp_generic_create_gatt_table
suffix:semicolon
id|agp_bridge-&gt;free_gatt_table
op_assign
id|agp_generic_free_gatt_table
suffix:semicolon
id|agp_bridge-&gt;insert_memory
op_assign
id|agp_generic_insert_memory
suffix:semicolon
id|agp_bridge-&gt;remove_memory
op_assign
id|agp_generic_remove_memory
suffix:semicolon
id|agp_bridge-&gt;alloc_by_type
op_assign
id|agp_generic_alloc_by_type
suffix:semicolon
id|agp_bridge-&gt;free_by_type
op_assign
id|agp_generic_free_by_type
suffix:semicolon
id|agp_bridge-&gt;agp_alloc_page
op_assign
id|ali_alloc_page
suffix:semicolon
id|agp_bridge-&gt;agp_destroy_page
op_assign
id|ali_destroy_page
suffix:semicolon
id|agp_bridge-&gt;suspend
op_assign
id|agp_generic_suspend
suffix:semicolon
id|agp_bridge-&gt;resume
op_assign
id|agp_generic_resume
suffix:semicolon
id|agp_bridge-&gt;cant_use_aperture
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_struct
id|agp_device_ids
id|ali_agp_device_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1541
comma
dot
id|chipset
op_assign
id|ALI_M1541
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1541&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1621
comma
dot
id|chipset
op_assign
id|ALI_M1621
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1621&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1631
comma
dot
id|chipset
op_assign
id|ALI_M1631
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1631&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1632
comma
dot
id|chipset
op_assign
id|ALI_M1632
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1632&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1641
comma
dot
id|chipset
op_assign
id|ALI_M1641
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1641&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1644
comma
dot
id|chipset
op_assign
id|ALI_M1644
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1644&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1647
comma
dot
id|chipset
op_assign
id|ALI_M1647
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1647&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1651
comma
dot
id|chipset
op_assign
id|ALI_M1651
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1651&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AL_M1671
comma
dot
id|chipset
op_assign
id|ALI_M1671
comma
dot
id|chipset_name
op_assign
l_string|&quot;M1671&quot;
comma
)brace
comma
(brace
)brace
comma
multiline_comment|/* dummy final entry, always present */
)brace
suffix:semicolon
multiline_comment|/* scan table above for supported devices */
DECL|function|agp_lookup_host_bridge
r_static
r_int
id|__init
id|agp_lookup_host_bridge
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
r_struct
id|agp_device_ids
op_star
id|devs
suffix:semicolon
id|devs
op_assign
id|ali_agp_device_ids
suffix:semicolon
r_while
c_loop
(paren
id|devs
(braket
id|j
)braket
dot
id|chipset_name
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|pdev-&gt;device
op_eq
id|devs
(braket
id|j
)braket
dot
id|device_id
)paren
(brace
r_if
c_cond
(paren
id|pdev-&gt;device
op_eq
id|PCI_DEVICE_ID_AL_M1621
)paren
(brace
id|u8
id|hidden_1621_id
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
l_int|0xFB
comma
op_amp
id|hidden_1621_id
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|hidden_1621_id
)paren
(brace
r_case
l_int|0x31
suffix:colon
id|devs
(braket
id|j
)braket
dot
id|chipset_name
op_assign
l_string|&quot;M1631&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x32
suffix:colon
id|devs
(braket
id|j
)braket
dot
id|chipset_name
op_assign
l_string|&quot;M1632&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x41
suffix:colon
id|devs
(braket
id|j
)braket
dot
id|chipset_name
op_assign
l_string|&quot;M1641&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x43
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0x47
suffix:colon
id|devs
(braket
id|j
)braket
dot
id|chipset_name
op_assign
l_string|&quot;M1647&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x51
suffix:colon
id|devs
(braket
id|j
)braket
dot
id|chipset_name
op_assign
l_string|&quot;M1651&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected ALi %s chipset&bslash;n&quot;
comma
id|devs
(braket
id|j
)braket
dot
id|chipset_name
)paren
suffix:semicolon
id|agp_bridge-&gt;type
op_assign
id|devs
(braket
id|j
)braket
dot
id|chipset
suffix:semicolon
r_if
c_cond
(paren
id|devs
(braket
id|j
)braket
dot
id|chipset_setup
op_ne
l_int|NULL
)paren
r_return
id|devs
(braket
id|j
)braket
dot
id|chipset_setup
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_else
r_return
id|ali_generic_setup
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
id|j
op_increment
suffix:semicolon
)brace
multiline_comment|/* try init anyway, if user requests it */
r_if
c_cond
(paren
id|agp_try_unsupported
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;Trying generic ALi routines&quot;
l_string|&quot; for device id: %04x&bslash;n&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
id|agp_bridge-&gt;type
op_assign
id|ALI_GENERIC
suffix:semicolon
r_return
id|ali_generic_setup
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unsupported ALi chipset (device id: %04x),&quot;
l_string|&quot; you might want to try agp_try_unsupported=1.&bslash;n&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|ali_agp_driver
r_static
r_struct
id|agp_driver
id|ali_agp_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|agp_ali_probe
r_static
r_int
id|__init
id|agp_ali_probe
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
id|u8
id|cap_ptr
op_assign
l_int|0
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
multiline_comment|/* probe for known chipsets */
r_if
c_cond
(paren
id|agp_lookup_host_bridge
c_func
(paren
id|dev
)paren
op_ne
op_minus
id|ENODEV
)paren
(brace
id|agp_bridge-&gt;dev
op_assign
id|dev
suffix:semicolon
id|agp_bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* Fill in the mode register */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|agp_bridge-&gt;capndx
op_plus
id|PCI_AGP_STATUS
comma
op_amp
id|agp_bridge-&gt;mode
)paren
suffix:semicolon
id|ali_agp_driver.dev
op_assign
id|dev
suffix:semicolon
id|agp_register_driver
c_func
(paren
op_amp
id|ali_agp_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|agp_ali_pci_table
(braket
)braket
id|__initdata
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
id|PCI_VENDOR_ID_AL
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
id|agp_ali_pci_table
)paren
suffix:semicolon
DECL|variable|agp_ali_pci_driver
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_ali_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-ali&quot;
comma
dot
id|id_table
op_assign
id|agp_ali_pci_table
comma
dot
id|probe
op_assign
id|agp_ali_probe
comma
)brace
suffix:semicolon
DECL|function|agp_ali_init
r_static
r_int
id|__init
id|agp_ali_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret_val
suffix:semicolon
id|ret_val
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|agp_ali_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
)paren
id|agp_bridge-&gt;type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
DECL|function|agp_ali_cleanup
r_static
r_void
id|__exit
id|agp_ali_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_unregister_driver
c_func
(paren
op_amp
id|ali_agp_driver
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_ali_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_ali_init
id|module_init
c_func
(paren
id|agp_ali_init
)paren
suffix:semicolon
DECL|variable|agp_ali_cleanup
id|module_exit
c_func
(paren
id|agp_ali_cleanup
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|agp_try_unsupported
comma
l_string|&quot;1i&quot;
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
