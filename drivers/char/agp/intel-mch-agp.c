multiline_comment|/*&n; * Intel MCH AGPGART routines.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|macro|AGP_DCACHE_MEMORY
mdefine_line|#define AGP_DCACHE_MEMORY&t;1
DECL|macro|AGP_PHYS_MEMORY
mdefine_line|#define AGP_PHYS_MEMORY&t;&t;2
DECL|variable|intel_i810_masks
r_static
r_struct
id|gatt_mask
id|intel_i810_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
id|I810_PTE_VALID
comma
dot
id|type
op_assign
l_int|0
)brace
comma
(brace
dot
id|mask
op_assign
(paren
id|I810_PTE_VALID
op_or
id|I810_PTE_LOCAL
)paren
comma
dot
id|type
op_assign
id|AGP_DCACHE_MEMORY
)brace
comma
(brace
dot
id|mask
op_assign
id|I810_PTE_VALID
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|intel_i810_tlbflush
r_static
r_void
id|intel_i810_tlbflush
c_func
(paren
r_struct
id|agp_memory
op_star
id|mem
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|intel_i810_agp_enable
r_static
r_void
id|intel_i810_agp_enable
c_func
(paren
id|u32
id|mode
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * The i810/i830 requires a physical address to program its mouse&n; * pointer into hardware.&n; * However the Xserver still writes to it through the agp aperture.&n; */
DECL|function|alloc_agpphysmem_i8xx
r_static
r_struct
id|agp_memory
op_star
id|alloc_agpphysmem_i8xx
c_func
(paren
r_int
id|pg_count
comma
r_int
id|type
)paren
(brace
r_struct
id|agp_memory
op_star
r_new
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|pg_count
op_ne
l_int|1
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|agp_bridge-&gt;driver
op_member_access_from_pointer
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
r_return
l_int|NULL
suffix:semicolon
r_new
op_assign
id|agp_create_memory
c_func
(paren
l_int|1
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
r_new
op_member_access_from_pointer
id|memory
(braket
l_int|0
)braket
op_assign
id|agp_bridge-&gt;driver
op_member_access_from_pointer
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
op_assign
l_int|1
suffix:semicolon
r_new
op_member_access_from_pointer
id|num_scratch_pages
op_assign
l_int|1
suffix:semicolon
r_new
op_member_access_from_pointer
id|type
op_assign
id|AGP_PHYS_MEMORY
suffix:semicolon
r_new
op_member_access_from_pointer
id|physical
op_assign
r_new
op_member_access_from_pointer
id|memory
(braket
l_int|0
)braket
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
DECL|function|intel_i810_free_by_type
r_static
r_void
id|intel_i810_free_by_type
c_func
(paren
r_struct
id|agp_memory
op_star
id|curr
)paren
(brace
id|agp_free_key
c_func
(paren
id|curr-&gt;key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr-&gt;type
op_eq
id|AGP_PHYS_MEMORY
)paren
(brace
id|agp_bridge-&gt;driver
op_member_access_from_pointer
id|agp_destroy_page
c_func
(paren
id|phys_to_virt
c_func
(paren
id|curr-&gt;memory
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|curr-&gt;memory
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|curr
)paren
suffix:semicolon
)brace
DECL|function|intel_i810_mask_memory
r_static
r_int
r_int
id|intel_i810_mask_memory
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
multiline_comment|/* Type checking must be done elsewhere */
r_return
id|addr
op_or
id|agp_bridge-&gt;driver-&gt;masks
(braket
id|type
)braket
dot
id|mask
suffix:semicolon
)brace
DECL|variable|intel_i830_sizes
r_static
r_struct
id|aper_size_info_fixed
id|intel_i830_sizes
(braket
)braket
op_assign
(brace
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
)brace
comma
multiline_comment|/* The 64M mode still requires a 128k gatt */
(brace
l_int|64
comma
l_int|16384
comma
l_int|5
)brace
)brace
suffix:semicolon
DECL|struct|_intel_i830_private
r_static
r_struct
id|_intel_i830_private
(brace
DECL|member|i830_dev
r_struct
id|pci_dev
op_star
id|i830_dev
suffix:semicolon
multiline_comment|/* device one */
DECL|member|registers
r_volatile
id|u8
id|__iomem
op_star
id|registers
suffix:semicolon
DECL|member|gtt_entries
r_int
id|gtt_entries
suffix:semicolon
DECL|variable|intel_i830_private
)brace
id|intel_i830_private
suffix:semicolon
DECL|function|intel_i830_init_gtt_entries
r_static
r_void
id|intel_i830_init_gtt_entries
c_func
(paren
r_void
)paren
(brace
id|u16
id|gmch_ctrl
suffix:semicolon
r_int
id|gtt_entries
suffix:semicolon
id|u8
id|rdct
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
r_static
r_const
r_int
id|ddt
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|16
comma
l_int|32
comma
l_int|64
)brace
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|I830_GMCH_CTRL
comma
op_amp
id|gmch_ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge-&gt;dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82830_HB
op_logical_or
id|agp_bridge-&gt;dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82845G_HB
)paren
(brace
r_switch
c_cond
(paren
id|gmch_ctrl
op_amp
id|I830_GMCH_GMS_MASK
)paren
(brace
r_case
id|I830_GMCH_GMS_STOLEN_512
suffix:colon
id|gtt_entries
op_assign
id|KB
c_func
(paren
l_int|512
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I830_GMCH_GMS_STOLEN_1024
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|1
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I830_GMCH_GMS_STOLEN_8192
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|8
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I830_GMCH_GMS_LOCAL
suffix:colon
id|rdct
op_assign
id|readb
c_func
(paren
id|intel_i830_private.registers
op_plus
id|I830_RDRAM_CHANNEL_TYPE
)paren
suffix:semicolon
id|gtt_entries
op_assign
(paren
id|I830_RDRAM_ND
c_func
(paren
id|rdct
)paren
op_plus
l_int|1
)paren
op_star
id|MB
c_func
(paren
id|ddt
(braket
id|I830_RDRAM_DDT
c_func
(paren
id|rdct
)paren
)braket
)paren
suffix:semicolon
id|local
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|gtt_entries
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|gmch_ctrl
op_amp
id|I830_GMCH_GMS_MASK
)paren
(brace
r_case
id|I855_GMCH_GMS_STOLEN_1M
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|1
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I855_GMCH_GMS_STOLEN_4M
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|4
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I855_GMCH_GMS_STOLEN_8M
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|8
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I855_GMCH_GMS_STOLEN_16M
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|16
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I855_GMCH_GMS_STOLEN_32M
suffix:colon
id|gtt_entries
op_assign
id|MB
c_func
(paren
l_int|32
)paren
op_minus
id|KB
c_func
(paren
l_int|132
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|gtt_entries
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|gtt_entries
OG
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected %dK %s memory.&bslash;n&quot;
comma
id|gtt_entries
op_div
id|KB
c_func
(paren
l_int|1
)paren
comma
id|local
ques
c_cond
l_string|&quot;local&quot;
suffix:colon
l_string|&quot;stolen&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;No pre-allocated video memory detected.&bslash;n&quot;
)paren
suffix:semicolon
id|gtt_entries
op_div_assign
id|KB
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|intel_i830_private.gtt_entries
op_assign
id|gtt_entries
suffix:semicolon
)brace
multiline_comment|/* The intel i830 automatically initializes the agp aperture during POST.&n; * Use the memory already set aside for in the GTT.&n; */
DECL|function|intel_i830_create_gatt_table
r_static
r_int
id|intel_i830_create_gatt_table
c_func
(paren
r_void
)paren
(brace
r_int
id|page_order
suffix:semicolon
r_struct
id|aper_size_info_fixed
op_star
id|size
suffix:semicolon
r_int
id|num_entries
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|size
op_assign
id|agp_bridge-&gt;current_size
suffix:semicolon
id|page_order
op_assign
id|size-&gt;page_order
suffix:semicolon
id|num_entries
op_assign
id|size-&gt;num_entries
suffix:semicolon
id|agp_bridge-&gt;gatt_table_real
op_assign
l_int|NULL
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|intel_i830_private.i830_dev
comma
id|I810_MMADDR
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
l_int|0xfff80000
suffix:semicolon
id|intel_i830_private.registers
op_assign
(paren
r_volatile
id|u8
id|__iomem
op_star
)paren
id|ioremap
c_func
(paren
id|temp
comma
l_int|128
op_star
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|intel_i830_private.registers
)paren
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|temp
op_assign
id|readl
c_func
(paren
id|intel_i830_private.registers
op_plus
id|I810_PGETBL_CTL
)paren
op_amp
l_int|0xfffff000
suffix:semicolon
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: ?? */
multiline_comment|/* we have to call this as early as possible after the MMIO base address is known */
id|intel_i830_init_gtt_entries
c_func
(paren
)paren
suffix:semicolon
id|agp_bridge-&gt;gatt_table
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge-&gt;gatt_bus_addr
op_assign
id|temp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return the gatt table to a sane state. Use the top of stolen&n; * memory for the GTT.&n; */
DECL|function|intel_i830_free_gatt_table
r_static
r_int
id|intel_i830_free_gatt_table
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|intel_i830_fetch_size
r_static
r_int
id|intel_i830_fetch_size
c_func
(paren
r_void
)paren
(brace
id|u16
id|gmch_ctrl
suffix:semicolon
r_struct
id|aper_size_info_fixed
op_star
id|values
suffix:semicolon
id|values
op_assign
id|A_SIZE_FIX
c_func
(paren
id|agp_bridge-&gt;driver-&gt;aperture_sizes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|agp_bridge-&gt;dev-&gt;device
op_ne
id|PCI_DEVICE_ID_INTEL_82830_HB
op_logical_and
id|agp_bridge-&gt;dev-&gt;device
op_ne
id|PCI_DEVICE_ID_INTEL_82845G_HB
)paren
(brace
multiline_comment|/* 855GM/852GM/865G has 128MB aperture size */
id|agp_bridge-&gt;previous_size
op_assign
id|agp_bridge-&gt;current_size
op_assign
(paren
r_void
op_star
)paren
id|values
suffix:semicolon
id|agp_bridge-&gt;aperture_size_idx
op_assign
l_int|0
suffix:semicolon
r_return
id|values
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
)brace
id|pci_read_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|I830_GMCH_CTRL
comma
op_amp
id|gmch_ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gmch_ctrl
op_amp
id|I830_GMCH_MEM_MASK
)paren
op_eq
id|I830_GMCH_MEM_128M
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
id|values
suffix:semicolon
id|agp_bridge-&gt;aperture_size_idx
op_assign
l_int|0
suffix:semicolon
r_return
id|values
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
)brace
r_else
(brace
id|agp_bridge-&gt;previous_size
op_assign
id|agp_bridge-&gt;current_size
op_assign
(paren
r_void
op_star
)paren
id|values
suffix:semicolon
id|agp_bridge-&gt;aperture_size_idx
op_assign
l_int|1
suffix:semicolon
r_return
id|values
(braket
l_int|1
)braket
dot
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|intel_i830_configure
r_static
r_int
id|intel_i830_configure
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_fixed
op_star
id|current_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|u16
id|gmch_ctrl
suffix:semicolon
r_int
id|i
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_FIX
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|intel_i830_private.i830_dev
comma
id|I810_GMADDR
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
id|pci_read_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|I830_GMCH_CTRL
comma
op_amp
id|gmch_ctrl
)paren
suffix:semicolon
id|gmch_ctrl
op_or_assign
id|I830_GMCH_ENABLED
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|I830_GMCH_CTRL
comma
id|gmch_ctrl
)paren
suffix:semicolon
id|writel
c_func
(paren
id|agp_bridge-&gt;gatt_bus_addr
op_or
id|I810_PGETBL_ENABLED
comma
id|intel_i830_private.registers
op_plus
id|I810_PGETBL_CTL
)paren
suffix:semicolon
id|readl
c_func
(paren
id|intel_i830_private.registers
op_plus
id|I810_PGETBL_CTL
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
r_if
c_cond
(paren
id|agp_bridge-&gt;driver-&gt;needs_scratch_page
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|intel_i830_private.gtt_entries
suffix:semicolon
id|i
OL
id|current_size-&gt;num_entries
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writel
c_func
(paren
id|agp_bridge-&gt;scratch_page
comma
id|intel_i830_private.registers
op_plus
id|I810_PTE_BASE
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|intel_i830_private.registers
op_plus
id|I810_PTE_BASE
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
)brace
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|intel_i830_cleanup
r_static
r_void
id|intel_i830_cleanup
c_func
(paren
r_void
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
id|__iomem
op_star
)paren
id|intel_i830_private.registers
)paren
suffix:semicolon
)brace
DECL|function|intel_i830_insert_entries
r_static
r_int
id|intel_i830_insert_entries
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
comma
id|num_entries
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
id|pg_start
OL
id|intel_i830_private.gtt_entries
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;pg_start == 0x%.8lx,intel_i830_private.gtt_entries == 0x%.8x&bslash;n&quot;
comma
id|pg_start
comma
id|intel_i830_private.gtt_entries
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Trying to insert into local/stolen memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
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
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* The i830 can&squot;t check the GTT for entries since its read only,&n;&t; * depend on the caller to make the correct offset decisions.&n;&t; */
r_if
c_cond
(paren
(paren
id|type
op_ne
l_int|0
op_logical_and
id|type
op_ne
id|AGP_PHYS_MEMORY
)paren
op_logical_or
(paren
id|mem-&gt;type
op_ne
l_int|0
op_logical_and
id|mem-&gt;type
op_ne
id|AGP_PHYS_MEMORY
)paren
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: ?? */
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
(brace
id|writel
c_func
(paren
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
comma
id|intel_i830_private.registers
op_plus
id|I810_PTE_BASE
op_plus
(paren
id|j
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|intel_i830_private.registers
op_plus
id|I810_PTE_BASE
op_plus
(paren
id|j
op_star
l_int|4
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
id|global_cache_flush
c_func
(paren
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
DECL|function|intel_i830_remove_entries
r_static
r_int
id|intel_i830_remove_entries
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
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pg_start
OL
id|intel_i830_private.gtt_entries
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Trying to disable local/stolen memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EINVAL
)paren
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
id|writel
c_func
(paren
id|agp_bridge-&gt;scratch_page
comma
id|intel_i830_private.registers
op_plus
id|I810_PTE_BASE
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|intel_i830_private.registers
op_plus
id|I810_PTE_BASE
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
id|global_cache_flush
c_func
(paren
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
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|intel_i830_alloc_by_type
r_static
r_struct
id|agp_memory
op_star
id|intel_i830_alloc_by_type
c_func
(paren
r_int
id|pg_count
comma
r_int
id|type
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|AGP_PHYS_MEMORY
)paren
r_return
id|alloc_agpphysmem_i8xx
c_func
(paren
id|pg_count
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* always return NULL for other allocation types for now */
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|intel_8xx_fetch_size
r_static
r_int
id|intel_8xx_fetch_size
c_func
(paren
r_void
)paren
(brace
id|u8
id|temp
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
id|INTEL_APSIZE
comma
op_amp
id|temp
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
DECL|function|intel_8xx_tlbflush
r_static
r_void
id|intel_8xx_tlbflush
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
id|INTEL_AGPCTRL
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
id|INTEL_AGPCTRL
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
id|INTEL_AGPCTRL
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
id|INTEL_AGPCTRL
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
DECL|function|intel_8xx_cleanup
r_static
r_void
id|intel_8xx_cleanup
c_func
(paren
r_void
)paren
(brace
id|u16
id|temp
suffix:semicolon
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
id|pci_read_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_NBXCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_NBXCFG
comma
id|temp
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|9
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_APSIZE
comma
id|previous_size-&gt;size_value
)paren
suffix:semicolon
)brace
DECL|function|intel_845_configure
r_static
r_int
id|intel_845_configure
c_func
(paren
r_void
)paren
(brace
id|u32
id|temp
suffix:semicolon
id|u8
id|temp2
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
id|INTEL_APSIZE
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
multiline_comment|/* attbase - aperture base */
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_ATTBASE
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
id|INTEL_AGPCTRL
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* agpm */
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I845_AGPM
comma
op_amp
id|temp2
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I845_AGPM
comma
id|temp2
op_or
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* clear any possible error conditions */
id|pci_write_config_word
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I845_ERRSTS
comma
l_int|0x001c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Setup function */
DECL|variable|intel_generic_masks
r_static
r_struct
id|gatt_mask
id|intel_generic_masks
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
DECL|variable|intel_8xx_sizes
r_static
r_struct
id|aper_size_info_8
id|intel_8xx_sizes
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
l_int|32
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|48
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
comma
l_int|56
)brace
comma
(brace
l_int|16
comma
l_int|4096
comma
l_int|2
comma
l_int|60
)brace
comma
(brace
l_int|8
comma
l_int|2048
comma
l_int|1
comma
l_int|62
)brace
comma
(brace
l_int|4
comma
l_int|1024
comma
l_int|0
comma
l_int|63
)brace
)brace
suffix:semicolon
DECL|variable|intel_830_driver
r_static
r_struct
id|agp_bridge_driver
id|intel_830_driver
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
id|intel_i830_sizes
comma
dot
id|size_type
op_assign
id|FIXED_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|2
comma
dot
id|needs_scratch_page
op_assign
id|TRUE
comma
dot
id|configure
op_assign
id|intel_i830_configure
comma
dot
id|fetch_size
op_assign
id|intel_i830_fetch_size
comma
dot
id|cleanup
op_assign
id|intel_i830_cleanup
comma
dot
id|tlb_flush
op_assign
id|intel_i810_tlbflush
comma
dot
id|mask_memory
op_assign
id|intel_i810_mask_memory
comma
dot
id|masks
op_assign
id|intel_i810_masks
comma
dot
id|agp_enable
op_assign
id|intel_i810_agp_enable
comma
dot
id|cache_flush
op_assign
id|global_cache_flush
comma
dot
id|create_gatt_table
op_assign
id|intel_i830_create_gatt_table
comma
dot
id|free_gatt_table
op_assign
id|intel_i830_free_gatt_table
comma
dot
id|insert_memory
op_assign
id|intel_i830_insert_entries
comma
dot
id|remove_memory
op_assign
id|intel_i830_remove_entries
comma
dot
id|alloc_by_type
op_assign
id|intel_i830_alloc_by_type
comma
dot
id|free_by_type
op_assign
id|intel_i810_free_by_type
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
DECL|variable|intel_845_driver
r_static
r_struct
id|agp_bridge_driver
id|intel_845_driver
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
id|intel_8xx_sizes
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
id|intel_845_configure
comma
dot
id|fetch_size
op_assign
id|intel_8xx_fetch_size
comma
dot
id|cleanup
op_assign
id|intel_8xx_cleanup
comma
dot
id|tlb_flush
op_assign
id|intel_8xx_tlbflush
comma
dot
id|mask_memory
op_assign
id|agp_generic_mask_memory
comma
dot
id|masks
op_assign
id|intel_generic_masks
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
DECL|function|find_i830
r_static
r_int
id|find_i830
c_func
(paren
id|u16
id|device
)paren
(brace
r_struct
id|pci_dev
op_star
id|i830_dev
suffix:semicolon
id|i830_dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|device
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i830_dev
op_logical_and
id|PCI_FUNC
c_func
(paren
id|i830_dev-&gt;devfn
)paren
op_ne
l_int|0
)paren
(brace
id|i830_dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|device
comma
id|i830_dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|i830_dev
)paren
r_return
l_int|0
suffix:semicolon
id|intel_i830_private.i830_dev
op_assign
id|i830_dev
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|agp_intelmch_probe
r_static
r_int
id|__devinit
id|agp_intelmch_probe
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
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_char
op_star
id|name
op_assign
l_string|&quot;(unknown)&quot;
suffix:semicolon
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
r_switch
c_cond
(paren
id|pdev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_INTEL_82865_HB
suffix:colon
r_if
c_cond
(paren
id|find_i830
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82865_IG
)paren
)paren
(brace
id|bridge-&gt;driver
op_assign
op_amp
id|intel_830_driver
suffix:semicolon
)brace
r_else
(brace
id|bridge-&gt;driver
op_assign
op_amp
id|intel_845_driver
suffix:semicolon
)brace
id|name
op_assign
l_string|&quot;865&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_INTEL_82875_HB
suffix:colon
id|bridge-&gt;driver
op_assign
op_amp
id|intel_845_driver
suffix:semicolon
id|name
op_assign
l_string|&quot;i875&quot;
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
l_string|&quot;Unsupported Intel chipset (device id: %04x)&bslash;n&quot;
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
suffix:semicolon
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;driver
op_eq
op_amp
id|intel_830_driver
)paren
id|bridge-&gt;dev_private_data
op_assign
op_amp
id|intel_i830_private
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected an Intel %s Chipset.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;&t;* The following fixes the case where the BIOS has &quot;forgotten&quot; to&n;&t;* provide an address range for the GART.&n;&t;* 20030610 - hamish@zot.org&n;&t;*/
id|r
op_assign
op_amp
id|pdev-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
r_if
c_cond
(paren
id|pci_assign_resource
c_func
(paren
id|pdev
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;could not assign resource 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;* If the device has not been properly setup, the following will catch&n;&t;* the problem and should stop the system from crashing.&n;&t;* 20030610 - hamish@zot.org&n;&t;*/
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unable to Enable PCI device&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
multiline_comment|/* Fill in the mode register */
r_if
c_cond
(paren
id|cap_ptr
)paren
(brace
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
)brace
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
DECL|function|agp_intelmch_remove
r_static
r_void
id|__devexit
id|agp_intelmch_remove
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
id|pci_dev_put
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
DECL|function|agp_intelmch_resume
r_static
r_int
id|agp_intelmch_resume
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
id|intel_845_driver
)paren
id|intel_845_configure
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|agp_intelmch_pci_table
r_static
r_struct
id|pci_device_id
id|agp_intelmch_pci_table
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
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82865_HB
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
id|PCI_DEVICE_ID_INTEL_82875_HB
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
id|agp_intelmch_pci_table
)paren
suffix:semicolon
DECL|variable|agp_intelmch_pci_driver
r_static
r_struct
id|pci_driver
id|agp_intelmch_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-intel-mch&quot;
comma
dot
id|id_table
op_assign
id|agp_intelmch_pci_table
comma
dot
id|probe
op_assign
id|agp_intelmch_probe
comma
dot
id|remove
op_assign
id|agp_intelmch_remove
comma
dot
id|resume
op_assign
id|agp_intelmch_resume
comma
)brace
suffix:semicolon
multiline_comment|/* intel_agp_init() must not be declared static for explicit&n;   early initialization to work (ie i810fb) */
DECL|function|agp_intelmch_init
r_int
id|__init
id|agp_intelmch_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|agp_initialised
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|agp_initialised
op_eq
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|agp_initialised
op_assign
l_int|1
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|agp_intelmch_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|agp_intelmch_cleanup
r_static
r_void
id|__exit
id|agp_intelmch_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_intelmch_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_intelmch_init
id|module_init
c_func
(paren
id|agp_intelmch_init
)paren
suffix:semicolon
DECL|variable|agp_intelmch_cleanup
id|module_exit
c_func
(paren
id|agp_intelmch_cleanup
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
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
