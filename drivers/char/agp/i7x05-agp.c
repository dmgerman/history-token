macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|function|intel_7505_fetch_size
r_static
r_int
id|intel_7505_fetch_size
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u16
id|tmp
suffix:semicolon
r_struct
id|aper_size_info_16
op_star
id|values
suffix:semicolon
multiline_comment|/* &n;&t; * For AGP 3.0 APSIZE is now 16 bits&n;&t; */
id|pci_read_config_word
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I7505_APSIZE
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_amp
l_int|0xfff
)paren
suffix:semicolon
id|values
op_assign
id|A_SIZE_16
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
id|tmp
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
DECL|function|intel_7505_tlbflush
r_static
r_void
id|intel_7505_tlbflush
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
id|INTEL_I7505_AGPCTRL
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
id|INTEL_I7505_AGPCTRL
comma
id|temp
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I7505_AGPCTRL
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
id|INTEL_I7505_AGPCTRL
comma
id|temp
op_or
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|intel_7505_cleanup
r_static
r_void
id|intel_7505_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_16
op_star
id|previous_size
suffix:semicolon
id|previous_size
op_assign
id|A_SIZE_16
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
id|INTEL_I7505_APSIZE
comma
id|previous_size-&gt;size_value
)paren
suffix:semicolon
)brace
DECL|function|intel_7505_configure
r_static
r_int
id|intel_7505_configure
c_func
(paren
r_void
)paren
(brace
id|u32
id|temp
suffix:semicolon
r_struct
id|aper_size_info_16
op_star
id|current_size
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_16
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
multiline_comment|/* aperture size */
id|pci_write_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I7505_APSIZE
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
id|INTEL_I7505_NAPBASELO
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
multiline_comment|/* attbase */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I7505_ATTBASE
comma
id|agp_bridge-&gt;gatt_bus_addr
)paren
suffix:semicolon
multiline_comment|/* agpctrl */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I7505_AGPCTRL
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* clear error registers */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I7505_ERRSTS
comma
l_int|0xff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|intel_7505_sizes
r_static
r_struct
id|aper_size_info_16
id|intel_7505_sizes
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
l_int|0xf00
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
comma
l_int|0xf20
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|0xf30
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
comma
l_int|0xf38
)brace
comma
(brace
l_int|16
comma
l_int|4096
comma
l_int|2
comma
l_int|0xf3c
)brace
comma
(brace
l_int|8
comma
l_int|2048
comma
l_int|1
comma
l_int|0xf3e
)brace
comma
(brace
l_int|4
comma
l_int|1024
comma
l_int|0
comma
l_int|0xf3f
)brace
)brace
suffix:semicolon
DECL|function|i7x05_mask_memory
r_static
r_int
r_int
id|i7x05_mask_memory
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
DECL|variable|i7x05_generic_masks
r_static
r_struct
id|gatt_mask
id|i7x05_generic_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
l_int|0x00000017
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|intel_7505_setup
r_static
r_int
id|__init
id|intel_7505_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|agp_bridge-&gt;masks
op_assign
id|i7x05_generic_masks
suffix:semicolon
id|agp_bridge-&gt;aperture_sizes
op_assign
(paren
r_void
op_star
)paren
id|intel_7505_sizes
suffix:semicolon
id|agp_bridge-&gt;size_type
op_assign
id|U16_APER_SIZE
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
id|intel_7505_configure
suffix:semicolon
id|agp_bridge-&gt;fetch_size
op_assign
id|intel_7505_fetch_size
suffix:semicolon
id|agp_bridge-&gt;cleanup
op_assign
id|intel_7505_cleanup
suffix:semicolon
id|agp_bridge-&gt;tlb_flush
op_assign
id|intel_7505_tlbflush
suffix:semicolon
id|agp_bridge-&gt;mask_memory
op_assign
id|i7x05_mask_memory
suffix:semicolon
id|agp_bridge-&gt;agp_enable
op_assign
id|agp_generic_enable
suffix:semicolon
id|agp_bridge-&gt;cache_flush
op_assign
id|global_cache_flush
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
id|agp_generic_alloc_page
suffix:semicolon
id|agp_bridge-&gt;agp_destroy_page
op_assign
id|agp_generic_destroy_page
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
id|i7x05_agp_device_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_INTEL_7505_0
comma
dot
id|chipset
op_assign
id|INTEL_I7505
comma
dot
id|chipset_name
op_assign
l_string|&quot;i7505&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_INTEL_7205_0
comma
dot
id|chipset
op_assign
id|INTEL_I7505
comma
dot
id|chipset_name
op_assign
l_string|&quot;i7205&quot;
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
id|i7x05_agp_device_ids
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
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected Intel %s chipset&bslash;n&quot;
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
id|intel_7505_setup
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
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unsupported Intel chipset (device id: %04x),&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|i7x05_agp_driver
r_static
r_struct
id|agp_driver
id|i7x05_agp_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|agp_i7x05_probe
r_static
r_int
id|__init
id|agp_i7x05_probe
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
id|i7x05_agp_driver.dev
op_assign
id|dev
suffix:semicolon
id|agp_register_driver
c_func
(paren
op_amp
id|i7x05_agp_driver
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
id|agp_i7x05_pci_table
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
id|PCI_VENDOR_ID_INTEL
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
id|agp_i7x05_pci_table
)paren
suffix:semicolon
DECL|variable|agp_i7x05_pci_driver
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_i7x05_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-i7x05&quot;
comma
dot
id|id_table
op_assign
id|agp_i7x05_pci_table
comma
dot
id|probe
op_assign
id|agp_i7x05_probe
comma
)brace
suffix:semicolon
DECL|function|agp_i7x05_init
r_int
id|__init
id|agp_i7x05_init
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
id|agp_i7x05_pci_driver
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
DECL|function|agp_i7x05_cleanup
r_static
r_void
id|__exit
id|agp_i7x05_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_unregister_driver
c_func
(paren
op_amp
id|i7x05_agp_driver
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_i7x05_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_i7x05_init
id|module_init
c_func
(paren
id|agp_i7x05_init
)paren
suffix:semicolon
DECL|variable|agp_i7x05_cleanup
id|module_exit
c_func
(paren
id|agp_i7x05_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Matthew E Tolentino &lt;matthew.e.tolentino@intel.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
