multiline_comment|/*&n; * SiS AGPGART routines. &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|macro|SIS_ATTBASE
mdefine_line|#define SIS_ATTBASE&t;0x90
DECL|macro|SIS_APSIZE
mdefine_line|#define SIS_APSIZE&t;0x94
DECL|macro|SIS_TLBCNTRL
mdefine_line|#define SIS_TLBCNTRL&t;0x97
DECL|macro|SIS_TLBFLUSH
mdefine_line|#define SIS_TLBFLUSH&t;0x98
DECL|variable|agp_sis_force_delay
r_static
r_int
id|__devinitdata
id|agp_sis_force_delay
op_assign
l_int|0
suffix:semicolon
DECL|variable|agp_sis_agp_spec
r_static
r_int
id|__devinitdata
id|agp_sis_agp_spec
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|sis_fetch_size
r_static
r_int
id|sis_fetch_size
c_func
(paren
r_void
)paren
(brace
id|u8
id|temp_size
suffix:semicolon
r_int
id|i
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
id|SIS_APSIZE
comma
op_amp
id|temp_size
)paren
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
(paren
id|temp_size
op_eq
id|values
(braket
id|i
)braket
dot
id|size_value
)paren
op_logical_or
(paren
(paren
id|temp_size
op_amp
op_complement
(paren
l_int|0x03
)paren
)paren
op_eq
(paren
id|values
(braket
id|i
)braket
dot
id|size_value
op_amp
op_complement
(paren
l_int|0x03
)paren
)paren
)paren
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
DECL|function|sis_tlbflush
r_static
r_void
id|sis_tlbflush
c_func
(paren
r_struct
id|agp_memory
op_star
id|mem
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|SIS_TLBFLUSH
comma
l_int|0x02
)paren
suffix:semicolon
)brace
DECL|function|sis_configure
r_static
r_int
id|sis_configure
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
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|SIS_TLBCNTRL
comma
l_int|0x05
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AGP_APBASE
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
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|SIS_ATTBASE
comma
id|agp_bridge-&gt;gatt_bus_addr
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|SIS_APSIZE
comma
id|current_size-&gt;size_value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis_cleanup
r_static
r_void
id|sis_cleanup
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
id|agp_bridge-&gt;previous_size
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|SIS_APSIZE
comma
(paren
id|previous_size-&gt;size_value
op_amp
op_complement
(paren
l_int|0x03
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|sis_delayed_enable
r_static
r_void
id|sis_delayed_enable
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
suffix:semicolon
r_int
id|rate
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Found an AGP %d.%d compliant device at %s.&bslash;n&quot;
comma
id|agp_bridge-&gt;major_version
comma
id|agp_bridge-&gt;minor_version
comma
id|agp_bridge-&gt;dev-&gt;slot_name
)paren
suffix:semicolon
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
id|command
)paren
suffix:semicolon
id|command
op_assign
id|agp_collect_device_status
c_func
(paren
id|mode
comma
id|command
)paren
suffix:semicolon
id|command
op_or_assign
id|AGPSTAT_AGP_ENABLE
suffix:semicolon
id|rate
op_assign
(paren
id|command
op_amp
l_int|0x7
)paren
op_lshift
l_int|2
suffix:semicolon
r_while
c_loop
(paren
(paren
id|device
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|device
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|u8
id|agp
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
op_logical_neg
id|agp
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Putting AGP V3 device at %s into %dx mode&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|device
)paren
comma
id|rate
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|device
comma
id|agp
op_plus
id|PCI_AGP_COMMAND
comma
id|command
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Weird: on some sis chipsets any rate change in the target&n;&t;&t; * command register triggers a 5ms screwup during which the master&n;&t;&t; * cannot be configured&t;&t; &n;&t;&t; */
r_if
c_cond
(paren
id|device-&gt;device
op_eq
id|agp_bridge-&gt;dev-&gt;device
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;SiS delay workaround: giving bridge time to recover.&bslash;n&quot;
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
(paren
l_int|1
op_plus
(paren
id|HZ
op_star
l_int|10
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|sis_generic_sizes
r_static
r_struct
id|aper_size_info_8
id|sis_generic_sizes
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
l_int|99
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
comma
l_int|83
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|67
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
comma
l_int|51
)brace
comma
(brace
l_int|16
comma
l_int|4096
comma
l_int|2
comma
l_int|35
)brace
comma
(brace
l_int|8
comma
l_int|2048
comma
l_int|1
comma
l_int|19
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
DECL|variable|sis_driver
r_struct
id|agp_bridge_driver
id|sis_driver
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
id|sis_generic_sizes
comma
dot
id|size_type
op_assign
id|U8_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|7
comma
dot
id|configure
op_assign
id|sis_configure
comma
dot
id|fetch_size
op_assign
id|sis_fetch_size
comma
dot
id|cleanup
op_assign
id|sis_cleanup
comma
dot
id|tlb_flush
op_assign
id|sis_tlbflush
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
id|agp_generic_insert_memory
comma
dot
id|remove_memory
op_assign
id|agp_generic_remove_memory
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
DECL|variable|__devinitdata
r_static
r_struct
id|agp_device_ids
id|sis_agp_device_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_5591_AGP
comma
dot
id|chipset_name
op_assign
l_string|&quot;5591&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_530
comma
dot
id|chipset_name
op_assign
l_string|&quot;530&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_540
comma
dot
id|chipset_name
op_assign
l_string|&quot;540&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_550
comma
dot
id|chipset_name
op_assign
l_string|&quot;550&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_620
comma
dot
id|chipset_name
op_assign
l_string|&quot;620&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_630
comma
dot
id|chipset_name
op_assign
l_string|&quot;630&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_635
comma
dot
id|chipset_name
op_assign
l_string|&quot;635&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_645
comma
dot
id|chipset_name
op_assign
l_string|&quot;645&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_646
comma
dot
id|chipset_name
op_assign
l_string|&quot;646&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_648
comma
dot
id|chipset_name
op_assign
l_string|&quot;648&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_650
comma
dot
id|chipset_name
op_assign
l_string|&quot;650&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_651
comma
dot
id|chipset_name
op_assign
l_string|&quot;651&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_655
comma
dot
id|chipset_name
op_assign
l_string|&quot;655&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_661
comma
dot
id|chipset_name
op_assign
l_string|&quot;661&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_730
comma
dot
id|chipset_name
op_assign
l_string|&quot;730&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_735
comma
dot
id|chipset_name
op_assign
l_string|&quot;735&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_740
comma
dot
id|chipset_name
op_assign
l_string|&quot;740&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_741
comma
dot
id|chipset_name
op_assign
l_string|&quot;741&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_745
comma
dot
id|chipset_name
op_assign
l_string|&quot;745&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_746
comma
dot
id|chipset_name
op_assign
l_string|&quot;746&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_SI_760
comma
dot
id|chipset_name
op_assign
l_string|&quot;760&quot;
comma
)brace
comma
(brace
)brace
comma
multiline_comment|/* dummy final entry, always present */
)brace
suffix:semicolon
singleline_comment|// chipsets that require the &squot;delay hack&squot;
DECL|variable|__devinitdata
r_static
r_int
id|sis_broken_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
id|PCI_DEVICE_ID_SI_648
comma
id|PCI_DEVICE_ID_SI_746
comma
l_int|0
singleline_comment|// terminator
)brace
suffix:semicolon
DECL|function|sis_get_driver
r_static
r_void
id|__devinit
id|sis_get_driver
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sis_broken_chipsets
(braket
id|i
)braket
op_ne
l_int|0
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|bridge-&gt;dev-&gt;device
op_eq
id|sis_broken_chipsets
(braket
id|i
)braket
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sis_broken_chipsets
(braket
id|i
)braket
op_logical_or
id|agp_sis_force_delay
)paren
(brace
id|sis_driver.agp_enable
op_assign
id|sis_delayed_enable
suffix:semicolon
)brace
singleline_comment|// sis chipsets that indicate less than agp3.5
singleline_comment|// are not actually fully agp3 compliant
r_if
c_cond
(paren
(paren
id|agp_bridge-&gt;major_version
op_eq
l_int|3
op_logical_and
id|agp_bridge-&gt;minor_version
op_ge
l_int|5
op_logical_and
id|agp_sis_agp_spec
op_ne
l_int|0
)paren
op_logical_or
id|agp_sis_agp_spec
op_eq
l_int|1
)paren
(brace
id|sis_driver.aperture_sizes
op_assign
id|agp3_generic_sizes
suffix:semicolon
id|sis_driver.size_type
op_assign
id|U16_APER_SIZE
suffix:semicolon
id|sis_driver.num_aperture_sizes
op_assign
id|AGP_GENERIC_SIZES_ENTRIES
suffix:semicolon
id|sis_driver.configure
op_assign
id|agp3_generic_configure
suffix:semicolon
id|sis_driver.fetch_size
op_assign
id|agp3_generic_fetch_size
suffix:semicolon
id|sis_driver.cleanup
op_assign
id|agp3_generic_cleanup
suffix:semicolon
id|sis_driver.tlb_flush
op_assign
id|agp3_generic_tlbflush
suffix:semicolon
)brace
)brace
DECL|function|agp_sis_probe
r_static
r_int
id|__devinit
id|agp_sis_probe
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
id|agp_device_ids
op_star
id|devs
op_assign
id|sis_agp_device_ids
suffix:semicolon
r_struct
id|agp_bridge_data
op_star
id|bridge
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
r_int
id|j
suffix:semicolon
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
multiline_comment|/* probe for known chipsets */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|devs
(braket
id|j
)braket
dot
id|chipset_name
suffix:semicolon
id|j
op_increment
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
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected SiS %s chipset&bslash;n&quot;
comma
id|devs
(braket
id|j
)braket
dot
id|chipset_name
)paren
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unsupported SiS chipset (device id: %04x)&bslash;n&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
id|found
suffix:colon
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
id|sis_driver
suffix:semicolon
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
id|get_agp_version
c_func
(paren
id|bridge
)paren
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
id|sis_get_driver
c_func
(paren
id|bridge
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
DECL|function|agp_sis_remove
r_static
r_void
id|__devexit
id|agp_sis_remove
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
DECL|variable|agp_sis_pci_table
r_static
r_struct
id|pci_device_id
id|agp_sis_pci_table
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
id|PCI_VENDOR_ID_SI
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
id|agp_sis_pci_table
)paren
suffix:semicolon
DECL|variable|agp_sis_pci_driver
r_static
r_struct
id|pci_driver
id|agp_sis_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-sis&quot;
comma
dot
id|id_table
op_assign
id|agp_sis_pci_table
comma
dot
id|probe
op_assign
id|agp_sis_probe
comma
dot
id|remove
op_assign
id|agp_sis_remove
comma
)brace
suffix:semicolon
DECL|function|agp_sis_init
r_static
r_int
id|__init
id|agp_sis_init
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
id|agp_sis_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|agp_sis_cleanup
r_static
r_void
id|__exit
id|agp_sis_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_sis_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_sis_init
id|module_init
c_func
(paren
id|agp_sis_init
)paren
suffix:semicolon
DECL|variable|agp_sis_cleanup
id|module_exit
c_func
(paren
id|agp_sis_cleanup
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|agp_sis_force_delay
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|agp_sis_force_delay
comma
l_string|&quot;forces sis delay hack&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|agp_sis_agp_spec
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|agp_sis_agp_spec
comma
l_string|&quot;0=force sis init, 1=force generic agp3 init, default: autodetect&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
