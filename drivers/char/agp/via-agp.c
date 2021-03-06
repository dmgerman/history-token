multiline_comment|/*&n; * VIA AGPGART routines.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|variable|agp_via_pci_table
r_static
r_struct
id|pci_device_id
id|agp_via_pci_table
(braket
)braket
suffix:semicolon
DECL|macro|VIA_GARTCTRL
mdefine_line|#define VIA_GARTCTRL&t;0x80
DECL|macro|VIA_APSIZE
mdefine_line|#define VIA_APSIZE&t;0x84
DECL|macro|VIA_ATTBASE
mdefine_line|#define VIA_ATTBASE&t;0x88
DECL|macro|VIA_AGP3_GARTCTRL
mdefine_line|#define VIA_AGP3_GARTCTRL&t;0x90
DECL|macro|VIA_AGP3_APSIZE
mdefine_line|#define VIA_AGP3_APSIZE&t;&t;0x94
DECL|macro|VIA_AGP3_ATTBASE
mdefine_line|#define VIA_AGP3_ATTBASE&t;0x98
DECL|macro|VIA_AGPSEL
mdefine_line|#define VIA_AGPSEL&t;&t;0xfd
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
id|agp_bridge-&gt;driver-&gt;aperture_sizes
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
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
id|agp_bridge-&gt;driver-&gt;num_aperture_sizes
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
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unknown aperture size from AGP bridge (0x%x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
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
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
multiline_comment|/* aperture size */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
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
multiline_comment|/* GART control register */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
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
id|agp_bridge-&gt;dev
comma
id|VIA_ATTBASE
comma
(paren
id|agp_bridge-&gt;gatt_bus_addr
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
id|agp_bridge-&gt;previous_size
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
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
r_struct
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
id|VIA_GARTCTRL
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_or_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|VIA_GARTCTRL
comma
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|VIA_GARTCTRL
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|variable|via_generic_sizes
r_static
r_struct
id|aper_size_info_8
id|via_generic_sizes
(braket
l_int|9
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
comma
(brace
l_int|2
comma
l_int|512
comma
l_int|0
comma
l_int|254
)brace
comma
(brace
l_int|1
comma
l_int|256
comma
l_int|0
comma
l_int|255
)brace
)brace
suffix:semicolon
DECL|function|via_fetch_size_agp3
r_static
r_int
id|via_fetch_size_agp3
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u16
id|temp
suffix:semicolon
r_struct
id|aper_size_info_16
op_star
id|values
suffix:semicolon
id|values
op_assign
id|A_SIZE_16
c_func
(paren
id|agp_bridge-&gt;driver-&gt;aperture_sizes
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|VIA_AGP3_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
l_int|0xfff
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
DECL|function|via_configure_agp3
r_static
r_int
id|via_configure_agp3
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
multiline_comment|/* address to map too */
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
multiline_comment|/* attbase - aperture GATT base */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|VIA_AGP3_ATTBASE
comma
id|agp_bridge-&gt;gatt_bus_addr
op_amp
l_int|0xfffff000
)paren
suffix:semicolon
multiline_comment|/* 1. Enable GTLB in RX90&lt;7&gt;, all AGP aperture access needs to fetch&n;&t; *    translation table first.&n;&t; * 2. Enable AGP aperture in RX91&lt;0&gt;. This bit controls the enabling of the&n;&t; *    graphics AGP aperture for the AGP3.0 port.&n;&t; */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|VIA_AGP3_GARTCTRL
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
id|VIA_AGP3_GARTCTRL
comma
id|temp
op_or
(paren
l_int|3
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|via_cleanup_agp3
r_static
r_void
id|via_cleanup_agp3
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
id|VIA_APSIZE
comma
id|previous_size-&gt;size_value
)paren
suffix:semicolon
)brace
DECL|function|via_tlbflush_agp3
r_static
r_void
id|via_tlbflush_agp3
c_func
(paren
r_struct
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
id|VIA_AGP3_GARTCTRL
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
id|VIA_AGP3_GARTCTRL
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
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|VIA_AGP3_GARTCTRL
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|variable|via_agp3_driver
r_struct
id|agp_bridge_driver
id|via_agp3_driver
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
id|agp3_generic_sizes
comma
dot
id|size_type
op_assign
id|U8_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|10
comma
dot
id|configure
op_assign
id|via_configure_agp3
comma
dot
id|fetch_size
op_assign
id|via_fetch_size_agp3
comma
dot
id|cleanup
op_assign
id|via_cleanup_agp3
comma
dot
id|tlb_flush
op_assign
id|via_tlbflush_agp3
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
DECL|variable|via_driver
r_struct
id|agp_bridge_driver
id|via_driver
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
id|via_generic_sizes
comma
dot
id|size_type
op_assign
id|U8_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|9
comma
dot
id|configure
op_assign
id|via_configure
comma
dot
id|fetch_size
op_assign
id|via_fetch_size
comma
dot
id|cleanup
op_assign
id|via_cleanup
comma
dot
id|tlb_flush
op_assign
id|via_tlbflush
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
id|via_agp_device_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_82C597_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo VP3&quot;
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
id|chipset_name
op_assign
l_string|&quot;Apollo MVP3&quot;
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
id|chipset_name
op_assign
l_string|&quot;Apollo MVP4&quot;
comma
)brace
comma
multiline_comment|/* VT8601 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8601_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo ProMedia/PLE133Ta&quot;
comma
)brace
comma
multiline_comment|/* VT82C693A / VT28C694T */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_82C691_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro 133&quot;
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
id|chipset_name
op_assign
l_string|&quot;KX133&quot;
comma
)brace
comma
multiline_comment|/* VT8633 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8633_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;Pro 266&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_XN266
comma
dot
id|chipset_name
op_assign
l_string|&quot;Apollo Pro266&quot;
comma
)brace
comma
multiline_comment|/* VT8361 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8361
comma
dot
id|chipset_name
op_assign
l_string|&quot;KLE133&quot;
comma
)brace
comma
multiline_comment|/* VT8365 / VT8362 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8363_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;Twister-K/KT133x/KM133&quot;
comma
)brace
comma
multiline_comment|/* VT8753A */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8753_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;P4X266&quot;
comma
)brace
comma
multiline_comment|/* VT8366 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8367_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;KT266/KY266x/KT333&quot;
comma
)brace
comma
multiline_comment|/* VT8633 (for CuMine/ Celeron) */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8653_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;Pro266T&quot;
comma
)brace
comma
multiline_comment|/* KM266 / PM266 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_XM266
comma
dot
id|chipset_name
op_assign
l_string|&quot;PM266/KM266&quot;
comma
)brace
comma
multiline_comment|/* CLE266 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_862X_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;CLE266&quot;
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
id|chipset_name
op_assign
l_string|&quot;KT400/KT400A/KT600&quot;
comma
)brace
comma
multiline_comment|/* VT8604 / VT8605 / VT8603&n;&t; * (Apollo Pro133A chipset with S3 Savage4) */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8605_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;ProSavage PM133/PL133/PN133&quot;
)brace
comma
multiline_comment|/* P4M266x/P4N266 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8703_51_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;P4M266x/P4N266&quot;
comma
)brace
comma
multiline_comment|/* VT8754 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8754C_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;PT800&quot;
comma
)brace
comma
multiline_comment|/* P4X600 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8763_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;P4X600&quot;
)brace
comma
multiline_comment|/* KM400 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8378_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;KM400/KM400A&quot;
comma
)brace
comma
multiline_comment|/* PT880 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_PT880
comma
dot
id|chipset_name
op_assign
l_string|&quot;PT880&quot;
comma
)brace
comma
multiline_comment|/* PT890 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_8783_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;PT890&quot;
comma
)brace
comma
multiline_comment|/* PM800/PN800/PM880/PN880 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_PX8X0_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;PM800/PN800/PM880/PN880&quot;
comma
)brace
comma
multiline_comment|/* KT880 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_3269_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;KT880&quot;
comma
)brace
comma
multiline_comment|/* KTxxx/Px8xx */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_83_87XX_1
comma
dot
id|chipset_name
op_assign
l_string|&quot;VT83xx/VT87xx/KTxxx/Px8xx&quot;
comma
)brace
comma
multiline_comment|/* P4M800 */
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_VIA_3296_0
comma
dot
id|chipset_name
op_assign
l_string|&quot;P4M800&quot;
comma
)brace
comma
(brace
)brace
comma
multiline_comment|/* dummy final entry, always present */
)brace
suffix:semicolon
multiline_comment|/*&n; * VIA&squot;s AGP3 chipsets do magick to put the AGP bridge compliant&n; * with the same standards version as the graphics card.&n; */
DECL|function|check_via_agp3
r_static
r_void
id|check_via_agp3
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
(brace
id|u8
id|reg
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bridge-&gt;dev
comma
id|VIA_AGPSEL
comma
op_amp
id|reg
)paren
suffix:semicolon
multiline_comment|/* Check AGP 2.0 compatibility mode. */
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
l_int|0
)paren
id|bridge-&gt;driver
op_assign
op_amp
id|via_agp3_driver
suffix:semicolon
)brace
DECL|function|agp_via_probe
r_static
r_int
id|__devinit
id|agp_via_probe
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
id|via_agp_device_ids
suffix:semicolon
r_struct
id|agp_bridge_data
op_star
id|bridge
suffix:semicolon
r_int
id|j
op_assign
l_int|0
suffix:semicolon
id|u8
id|cap_ptr
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
id|j
op_assign
id|ent
op_minus
id|agp_via_pci_table
suffix:semicolon
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
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
id|bridge-&gt;driver
op_assign
op_amp
id|via_driver
suffix:semicolon
multiline_comment|/*&n;&t; * Garg, there are KT400s with KT266 IDs.&n;&t; */
r_if
c_cond
(paren
id|pdev-&gt;device
op_eq
id|PCI_DEVICE_ID_VIA_8367_0
)paren
(brace
multiline_comment|/* Is there a KT400 subsystem ? */
r_if
c_cond
(paren
id|pdev-&gt;subsystem_device
op_eq
id|PCI_DEVICE_ID_VIA_8377_0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Found KT400 in disguise as a KT266.&bslash;n&quot;
)paren
suffix:semicolon
id|check_via_agp3
c_func
(paren
id|bridge
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* If this is an AGP3 bridge, check which mode its in and adjust. */
id|get_agp_version
c_func
(paren
id|bridge
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;major_version
op_ge
l_int|3
)paren
id|check_via_agp3
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
DECL|function|agp_via_remove
r_static
r_void
id|__devexit
id|agp_via_remove
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
macro_line|#ifdef CONFIG_PM
DECL|function|agp_via_suspend
r_static
r_int
id|agp_via_suspend
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|pm_message_t
id|state
)paren
(brace
id|pci_save_state
(paren
id|pdev
)paren
suffix:semicolon
id|pci_set_power_state
(paren
id|pdev
comma
id|PCI_D3hot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_via_resume
r_static
r_int
id|agp_via_resume
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
id|pci_set_power_state
(paren
id|pdev
comma
id|PCI_D0
)paren
suffix:semicolon
id|pci_restore_state
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;driver
op_eq
op_amp
id|via_agp3_driver
)paren
r_return
id|via_configure_agp3
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bridge-&gt;driver
op_eq
op_amp
id|via_driver
)paren
r_return
id|via_configure
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PM */
multiline_comment|/* must be the same order as name table above */
DECL|variable|agp_via_pci_table
r_static
r_struct
id|pci_device_id
id|agp_via_pci_table
(braket
)braket
op_assign
(brace
DECL|macro|ID
mdefine_line|#define ID(x) &bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.class&t;&t;= (PCI_CLASS_BRIDGE_HOST &lt;&lt; 8),&t;&bslash;&n;&t;.class_mask&t;= ~0,&t;&t;&t;&t;&bslash;&n;&t;.vendor&t;&t;= PCI_VENDOR_ID_VIA,&t;&t;&bslash;&n;&t;.device&t;&t;= x,&t;&t;&t;&t;&bslash;&n;&t;.subvendor&t;= PCI_ANY_ID,&t;&t;&t;&bslash;&n;&t;.subdevice&t;= PCI_ANY_ID,&t;&t;&t;&bslash;&n;&t;}
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_82C597_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_82C598_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8501_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8601_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_82C691_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8371_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8633_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_XN266
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8361
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8363_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8753_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8367_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8653_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_XM266
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_862X_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8377_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8605_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8703_51_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8754C_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8763_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8378_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_PT880
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_8783_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_PX8X0_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_3269_0
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_83_87XX_1
)paren
comma
id|ID
c_func
(paren
id|PCI_DEVICE_ID_VIA_3296_0
)paren
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
dot
id|remove
op_assign
id|agp_via_remove
comma
macro_line|#ifdef CONFIG_PM
dot
id|suspend
op_assign
id|agp_via_suspend
comma
dot
id|resume
op_assign
id|agp_via_resume
comma
macro_line|#endif
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
r_if
c_cond
(paren
id|agp_off
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|agp_via_pci_driver
)paren
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;&quot;
)paren
suffix:semicolon
eof
