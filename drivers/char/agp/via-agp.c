multiline_comment|/*&n; * VIA AGPGART routines. &n; */
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
r_static
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
)brace
multiline_comment|/*&n; * The KT400 does magick to put the AGP bridge compliant with the same&n; * standards version as the graphics card. If we haven&squot;t fallen into&n; * 2.0 compatability mode, we abort, as this gets picked up by&n; * via-agp3.o&n; */
DECL|function|via_kt400_setup
r_static
r_int
id|__init
id|via_kt400_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|u8
id|reg
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|VIA_AGPSEL
comma
op_amp
id|reg
)paren
suffix:semicolon
multiline_comment|/* Check AGP 2.0 compatability mode. */
r_if
c_cond
(paren
(paren
id|reg
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
op_eq
l_int|1
)paren
(brace
id|via_generic_setup
c_func
(paren
id|pdev
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
id|agp_device_ids
id|via_agp_device_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_82C597_0
comma
dot
id|chipset
op_assign
id|VIA_VP3
comma
dot
id|chipset_name
op_assign
l_string|&quot;VP3&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_82C598_0
comma
dot
id|chipset
op_assign
id|VIA_MVP3
comma
dot
id|chipset_name
op_assign
l_string|&quot;MVP3&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8501_0
comma
dot
id|chipset
op_assign
id|VIA_MVP4
comma
dot
id|chipset_name
op_assign
l_string|&quot;MVP4&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_82C691
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_PRO
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8371_0
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_KX133
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro KX133&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8633_0
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_PRO_266
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro 266&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8363_0
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_KT133
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro KT133&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8367_0
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_KT133
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro KT266&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8653_0
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_PRO
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro 266T&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8377_0
comma
dot
id|chipset
op_assign
id|VIA_APOLLO_KT400
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro KT400&quot;
comma
dot
id|chipset_setup
op_assign
id|via_kt400_setup
comma
)brace
comma
(brace
multiline_comment|/* VIA ProSavage PM133 (Apollo Pro133A chipset with S3 Savage4) */
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_82C694X_0
comma
dot
id|chipset
op_assign
id|VIA_VT8605
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo ProSavage PM133&quot;
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8754
comma
dot
id|chipset
op_assign
id|VIA_P4X
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo P4X333/P4X400&quot;
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
id|via_agp_device_ids
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
l_string|&quot;Detected VIA %s chipset&bslash;n&quot;
comma
id|devs
(braket
id|j
)braket
dot
id|chipset_name
)paren
suffix:semicolon
id|agp_bridge.type
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
id|via_generic_setup
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
l_string|&quot;Trying generic VIA routines&quot;
l_string|&quot; for device id: %04x&bslash;n&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
id|agp_bridge.type
op_assign
id|VIA_GENERIC
suffix:semicolon
r_return
id|via_generic_setup
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
l_string|&quot;Unsupported VIA chipset (device id: %04x),&quot;
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
DECL|function|agp_via_probe
r_static
r_int
id|__init
id|agp_via_probe
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
(paren
id|dev
)paren
op_ne
op_minus
id|ENODEV
)paren
(brace
id|agp_bridge.dev
op_assign
id|dev
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
id|agp_register_driver
c_func
(paren
id|dev
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
id|agp_via_pci_table
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
id|PCI_VENDOR_ID_VIA
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
id|agp_via_pci_table
)paren
suffix:semicolon
DECL|variable|agp_via_pci_driver
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_via_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-via&quot;
comma
dot
id|id_table
op_assign
id|agp_via_pci_table
comma
dot
id|probe
op_assign
id|agp_via_probe
comma
)brace
suffix:semicolon
DECL|function|agp_via_init
r_static
r_int
id|__init
id|agp_via_init
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
id|agp_via_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
)paren
id|agp_bridge.type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
DECL|function|agp_via_cleanup
r_static
r_void
id|__exit
id|agp_via_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_unregister_driver
c_func
(paren
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_via_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_via_init
id|module_init
c_func
(paren
id|agp_via_init
)paren
suffix:semicolon
DECL|variable|agp_via_cleanup
id|module_exit
c_func
(paren
id|agp_via_cleanup
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
