multiline_comment|/*&n; * AMD K7 AGPGART routines.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/page-flags.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|macro|AMD_MMBASE
mdefine_line|#define AMD_MMBASE&t;0x14
DECL|macro|AMD_APSIZE
mdefine_line|#define AMD_APSIZE&t;0xac
DECL|macro|AMD_MODECNTL
mdefine_line|#define AMD_MODECNTL&t;0xb0
DECL|macro|AMD_MODECNTL2
mdefine_line|#define AMD_MODECNTL2&t;0xb2
DECL|macro|AMD_GARTENABLE
mdefine_line|#define AMD_GARTENABLE&t;0x02&t;/* In mmio region (16-bit register) */
DECL|macro|AMD_ATTBASE
mdefine_line|#define AMD_ATTBASE&t;0x04&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_TLBFLUSH
mdefine_line|#define AMD_TLBFLUSH&t;0x0c&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_CACHEENTRY
mdefine_line|#define AMD_CACHEENTRY&t;0x10&t;/* In mmio region (32-bit register) */
DECL|variable|agp_amdk7_pci_table
r_static
r_struct
id|pci_device_id
id|agp_amdk7_pci_table
(braket
)braket
suffix:semicolon
DECL|struct|amd_page_map
r_struct
id|amd_page_map
(brace
DECL|member|real
r_int
r_int
op_star
id|real
suffix:semicolon
DECL|member|remapped
r_int
r_int
id|__iomem
op_star
id|remapped
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_amd_irongate_private
r_static
r_struct
id|_amd_irongate_private
(brace
DECL|member|registers
r_volatile
id|u8
id|__iomem
op_star
id|registers
suffix:semicolon
DECL|member|gatt_pages
r_struct
id|amd_page_map
op_star
op_star
id|gatt_pages
suffix:semicolon
DECL|member|num_tables
r_int
id|num_tables
suffix:semicolon
DECL|variable|amd_irongate_private
)brace
id|amd_irongate_private
suffix:semicolon
DECL|function|amd_create_page_map
r_static
r_int
id|amd_create_page_map
c_func
(paren
r_struct
id|amd_page_map
op_star
id|page_map
)paren
(brace
r_int
id|i
suffix:semicolon
id|page_map-&gt;real
op_assign
(paren
r_int
r_int
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_map-&gt;real
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page_map-&gt;real
)paren
)paren
suffix:semicolon
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
id|page_map-&gt;remapped
op_assign
id|ioremap_nocache
c_func
(paren
id|virt_to_phys
c_func
(paren
id|page_map-&gt;real
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_map-&gt;remapped
op_eq
l_int|NULL
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page_map-&gt;real
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page_map-&gt;real
)paren
suffix:semicolon
id|page_map-&gt;real
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|global_cache_flush
c_func
(paren
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
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
id|page_map-&gt;remapped
op_plus
id|i
)paren
suffix:semicolon
id|readl
c_func
(paren
id|page_map-&gt;remapped
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_free_page_map
r_static
r_void
id|amd_free_page_map
c_func
(paren
r_struct
id|amd_page_map
op_star
id|page_map
)paren
(brace
id|iounmap
c_func
(paren
id|page_map-&gt;remapped
)paren
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page_map-&gt;real
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page_map-&gt;real
)paren
suffix:semicolon
)brace
DECL|function|amd_free_gatt_pages
r_static
r_void
id|amd_free_gatt_pages
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|amd_page_map
op_star
op_star
id|tables
suffix:semicolon
r_struct
id|amd_page_map
op_star
id|entry
suffix:semicolon
id|tables
op_assign
id|amd_irongate_private.gatt_pages
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
id|amd_irongate_private.num_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|tables
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;real
op_ne
l_int|NULL
)paren
id|amd_free_page_map
c_func
(paren
id|entry
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|tables
)paren
suffix:semicolon
id|amd_irongate_private.gatt_pages
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|amd_create_gatt_pages
r_static
r_int
id|amd_create_gatt_pages
c_func
(paren
r_int
id|nr_tables
)paren
(brace
r_struct
id|amd_page_map
op_star
op_star
id|tables
suffix:semicolon
r_struct
id|amd_page_map
op_star
id|entry
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|tables
op_assign
id|kmalloc
c_func
(paren
(paren
id|nr_tables
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|amd_page_map
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tables
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
(paren
id|tables
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|amd_page_map
op_star
)paren
op_star
(paren
id|nr_tables
op_plus
l_int|1
)paren
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
id|nr_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|amd_page_map
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memset
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|amd_page_map
)paren
)paren
suffix:semicolon
id|tables
(braket
id|i
)braket
op_assign
id|entry
suffix:semicolon
id|retval
op_assign
id|amd_create_page_map
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|amd_irongate_private.num_tables
op_assign
id|nr_tables
suffix:semicolon
id|amd_irongate_private.gatt_pages
op_assign
id|tables
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
id|amd_free_gatt_pages
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Since we don&squot;t need contigious memory we just try&n; * to get the gatt table once&n; */
DECL|macro|GET_PAGE_DIR_OFF
mdefine_line|#define GET_PAGE_DIR_OFF(addr) (addr &gt;&gt; 22)
DECL|macro|GET_PAGE_DIR_IDX
mdefine_line|#define GET_PAGE_DIR_IDX(addr) (GET_PAGE_DIR_OFF(addr) - &bslash;&n;&t;GET_PAGE_DIR_OFF(agp_bridge-&gt;gart_bus_addr))
DECL|macro|GET_GATT_OFF
mdefine_line|#define GET_GATT_OFF(addr) ((addr &amp; 0x003ff000) &gt;&gt; 12)
DECL|macro|GET_GATT
mdefine_line|#define GET_GATT(addr) (amd_irongate_private.gatt_pages[&bslash;&n;&t;GET_PAGE_DIR_IDX(addr)]-&gt;remapped)
DECL|function|amd_create_gatt_table
r_static
r_int
id|amd_create_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_lvl2
op_star
id|value
suffix:semicolon
r_struct
id|amd_page_map
id|page_dir
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|value
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
id|retval
op_assign
id|amd_create_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|retval
op_assign
id|amd_create_gatt_pages
c_func
(paren
id|value-&gt;num_entries
op_div
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|amd_free_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|agp_bridge-&gt;gatt_table_real
op_assign
(paren
id|u32
op_star
)paren
id|page_dir.real
suffix:semicolon
id|agp_bridge-&gt;gatt_table
op_assign
(paren
id|u32
id|__iomem
op_star
)paren
id|page_dir.remapped
suffix:semicolon
id|agp_bridge-&gt;gatt_bus_addr
op_assign
id|virt_to_phys
c_func
(paren
id|page_dir.real
)paren
suffix:semicolon
multiline_comment|/* Get the address for the gart region.&n;&t; * This is a bus address even on the alpha, b/c its&n;&t; * used to program the agp master not the cpu&n;&t; */
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
id|addr
op_assign
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
id|agp_bridge-&gt;gart_bus_addr
op_assign
id|addr
suffix:semicolon
multiline_comment|/* Calculate the agp offset */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|value-&gt;num_entries
op_div
l_int|1024
suffix:semicolon
id|i
op_increment
comma
id|addr
op_add_assign
l_int|0x00400000
)paren
(brace
id|writel
c_func
(paren
id|virt_to_phys
c_func
(paren
id|amd_irongate_private.gatt_pages
(braket
id|i
)braket
op_member_access_from_pointer
id|real
)paren
op_or
l_int|1
comma
id|page_dir.remapped
op_plus
id|GET_PAGE_DIR_OFF
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|page_dir.remapped
op_plus
id|GET_PAGE_DIR_OFF
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_free_gatt_table
r_static
r_int
id|amd_free_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|amd_page_map
id|page_dir
suffix:semicolon
id|page_dir.real
op_assign
(paren
r_int
r_int
op_star
)paren
id|agp_bridge-&gt;gatt_table_real
suffix:semicolon
id|page_dir.remapped
op_assign
(paren
r_int
r_int
id|__iomem
op_star
)paren
id|agp_bridge-&gt;gatt_table
suffix:semicolon
id|amd_free_gatt_pages
c_func
(paren
)paren
suffix:semicolon
id|amd_free_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_irongate_fetch_size
r_static
r_int
id|amd_irongate_fetch_size
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
id|aper_size_info_lvl2
op_star
id|values
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_amp
l_int|0x0000000e
)paren
suffix:semicolon
id|values
op_assign
id|A_SIZE_LVL2
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
DECL|function|amd_irongate_configure
r_static
r_int
id|amd_irongate_configure
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_lvl2
op_star
id|current_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|u16
id|enable_reg
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
multiline_comment|/* Get the memory mapped registers */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_MMBASE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
id|amd_irongate_private.registers
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
l_int|4096
)paren
suffix:semicolon
multiline_comment|/* Write out the address of the gatt table */
id|writel
c_func
(paren
id|agp_bridge-&gt;gatt_bus_addr
comma
id|amd_irongate_private.registers
op_plus
id|AMD_ATTBASE
)paren
suffix:semicolon
id|readl
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_ATTBASE
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
multiline_comment|/* Write the Sync register */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_MODECNTL
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Set indexing mode */
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_MODECNTL2
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Write the enable register */
id|enable_reg
op_assign
id|readw
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_GARTENABLE
)paren
suffix:semicolon
id|enable_reg
op_assign
(paren
id|enable_reg
op_or
l_int|0x0004
)paren
suffix:semicolon
id|writew
c_func
(paren
id|enable_reg
comma
id|amd_irongate_private.registers
op_plus
id|AMD_GARTENABLE
)paren
suffix:semicolon
id|readw
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_GARTENABLE
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
multiline_comment|/* Write out the size register */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_APSIZE
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
op_complement
(paren
l_int|0x0000000e
)paren
)paren
op_or
id|current_size-&gt;size_value
)paren
op_or
l_int|1
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_APSIZE
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* Flush the tlb */
id|writel
c_func
(paren
l_int|1
comma
id|amd_irongate_private.registers
op_plus
id|AMD_TLBFLUSH
)paren
suffix:semicolon
id|readl
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_TLBFLUSH
)paren
suffix:semicolon
multiline_comment|/* PCI Posting.*/
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_irongate_cleanup
r_static
r_void
id|amd_irongate_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_lvl2
op_star
id|previous_size
suffix:semicolon
id|u32
id|temp
suffix:semicolon
id|u16
id|enable_reg
suffix:semicolon
id|previous_size
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge-&gt;previous_size
)paren
suffix:semicolon
id|enable_reg
op_assign
id|readw
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_GARTENABLE
)paren
suffix:semicolon
id|enable_reg
op_assign
(paren
id|enable_reg
op_amp
op_complement
(paren
l_int|0x0004
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
id|enable_reg
comma
id|amd_irongate_private.registers
op_plus
id|AMD_GARTENABLE
)paren
suffix:semicolon
id|readw
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_GARTENABLE
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
multiline_comment|/* Write back the previous size and disable gart translation */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
(paren
id|temp
op_amp
op_complement
(paren
l_int|0x0000000f
)paren
)paren
op_or
id|previous_size-&gt;size_value
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|AMD_APSIZE
comma
id|temp
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
id|__iomem
op_star
)paren
id|amd_irongate_private.registers
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine could be implemented by taking the addresses&n; * written to the GATT, and flushing them individually.  However&n; * currently it just flushes the whole table.  Which is probably&n; * more efficent, since agp_memory blocks can be a large number of&n; * entries.&n; */
DECL|function|amd_irongate_tlbflush
r_static
r_void
id|amd_irongate_tlbflush
c_func
(paren
r_struct
id|agp_memory
op_star
id|temp
)paren
(brace
id|writel
c_func
(paren
l_int|1
comma
id|amd_irongate_private.registers
op_plus
id|AMD_TLBFLUSH
)paren
suffix:semicolon
id|readl
c_func
(paren
id|amd_irongate_private.registers
op_plus
id|AMD_TLBFLUSH
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
DECL|function|amd_insert_memory
r_static
r_int
id|amd_insert_memory
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
r_int
r_int
id|__iomem
op_star
id|cur_gatt
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
l_int|0
op_logical_or
id|mem-&gt;type
op_ne
l_int|0
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
id|num_entries
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|j
op_assign
id|pg_start
suffix:semicolon
r_while
c_loop
(paren
id|j
OL
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
)paren
)paren
(brace
id|addr
op_assign
(paren
id|j
op_star
id|PAGE_SIZE
)paren
op_plus
id|agp_bridge-&gt;gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PGE_EMPTY
c_func
(paren
id|agp_bridge
comma
id|readl
c_func
(paren
id|cur_gatt
op_plus
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)paren
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|j
op_increment
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
(brace
id|addr
op_assign
(paren
id|j
op_star
id|PAGE_SIZE
)paren
op_plus
id|agp_bridge-&gt;gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
id|writel
c_func
(paren
id|agp_generic_mask_memory
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
id|cur_gatt
op_plus
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|cur_gatt
op_plus
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
id|amd_irongate_tlbflush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_remove_memory
r_static
r_int
id|amd_remove_memory
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
r_int
r_int
id|__iomem
op_star
id|cur_gatt
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
l_int|0
op_logical_or
id|mem-&gt;type
op_ne
l_int|0
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
id|addr
op_assign
(paren
id|i
op_star
id|PAGE_SIZE
)paren
op_plus
id|agp_bridge-&gt;gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
id|writel
c_func
(paren
id|agp_bridge-&gt;scratch_page
comma
id|cur_gatt
op_plus
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|cur_gatt
op_plus
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
id|amd_irongate_tlbflush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|amd_irongate_sizes
r_static
r_struct
id|aper_size_info_lvl2
id|amd_irongate_sizes
(braket
l_int|7
)braket
op_assign
(brace
(brace
l_int|2048
comma
l_int|524288
comma
l_int|0x0000000c
)brace
comma
(brace
l_int|1024
comma
l_int|262144
comma
l_int|0x0000000a
)brace
comma
(brace
l_int|512
comma
l_int|131072
comma
l_int|0x00000008
)brace
comma
(brace
l_int|256
comma
l_int|65536
comma
l_int|0x00000006
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|0x00000004
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|0x00000002
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|0x00000000
)brace
)brace
suffix:semicolon
DECL|variable|amd_irongate_masks
r_static
r_struct
id|gatt_mask
id|amd_irongate_masks
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
DECL|variable|amd_irongate_driver
r_struct
id|agp_bridge_driver
id|amd_irongate_driver
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
id|amd_irongate_sizes
comma
dot
id|size_type
op_assign
id|LVL2_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|7
comma
dot
id|configure
op_assign
id|amd_irongate_configure
comma
dot
id|fetch_size
op_assign
id|amd_irongate_fetch_size
comma
dot
id|cleanup
op_assign
id|amd_irongate_cleanup
comma
dot
id|tlb_flush
op_assign
id|amd_irongate_tlbflush
comma
dot
id|mask_memory
op_assign
id|agp_generic_mask_memory
comma
dot
id|masks
op_assign
id|amd_irongate_masks
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
id|amd_create_gatt_table
comma
dot
id|free_gatt_table
op_assign
id|amd_free_gatt_table
comma
dot
id|insert_memory
op_assign
id|amd_insert_memory
comma
dot
id|remove_memory
op_assign
id|amd_remove_memory
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
id|amd_agp_device_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AMD_FE_GATE_7006
comma
dot
id|chipset_name
op_assign
l_string|&quot;Irongate&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AMD_FE_GATE_700E
comma
dot
id|chipset_name
op_assign
l_string|&quot;761&quot;
comma
)brace
comma
(brace
dot
id|device_id
op_assign
id|PCI_DEVICE_ID_AMD_FE_GATE_700C
comma
dot
id|chipset_name
op_assign
l_string|&quot;760MP&quot;
comma
)brace
comma
(brace
)brace
comma
multiline_comment|/* dummy final entry, always present */
)brace
suffix:semicolon
DECL|function|agp_amdk7_probe
r_static
r_int
id|__devinit
id|agp_amdk7_probe
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
id|j
op_assign
id|ent
op_minus
id|agp_amdk7_pci_table
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected AMD %s chipset&bslash;n&quot;
comma
id|amd_agp_device_ids
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
id|bridge-&gt;driver
op_assign
op_amp
id|amd_irongate_driver
suffix:semicolon
id|bridge-&gt;dev_private_data
op_assign
op_amp
id|amd_irongate_private
comma
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* 751 Errata (22564_B-1.PDF)&n;&t;   erratum 20: strobe glitch with Nvidia NV10 GeForce cards.&n;&t;   system controller may experience noise due to strong drive strengths&n;&t; */
r_if
c_cond
(paren
id|agp_bridge-&gt;dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AMD_FE_GATE_7006
)paren
(brace
id|u8
id|cap_ptr
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|gfxcard
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cap_ptr
)paren
(brace
id|gfxcard
op_assign
id|pci_get_class
c_func
(paren
id|PCI_CLASS_DISPLAY_VGA
op_lshift
l_int|8
comma
id|gfxcard
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gfxcard
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Couldn&squot;t find an AGP VGA controller.&bslash;n&quot;
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
id|gfxcard
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
(brace
id|pci_dev_put
c_func
(paren
id|gfxcard
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/* With so many variants of NVidia cards, it&squot;s simpler just&n;&t;&t;   to blacklist them all, and then whitelist them as needed&n;&t;&t;   (if necessary at all). */
r_if
c_cond
(paren
id|gfxcard-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NVIDIA
)paren
(brace
id|agp_bridge-&gt;flags
op_or_assign
id|AGP_ERRATA_1X
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;AMD 751 chipset with NVidia GeForce detected. Forcing to 1X due to errata.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pci_dev_put
c_func
(paren
id|gfxcard
)paren
suffix:semicolon
)brace
multiline_comment|/* 761 Errata (23613_F.pdf)&n;&t; * Revisions B0/B1 were a disaster.&n;&t; * erratum 44: SYSCLK/AGPCLK skew causes 2X failures -- Force mode to 1X&n;&t; * erratum 45: Timing problem prevents fast writes -- Disable fast write.&n;&t; * erratum 46: Setup violation on AGP SBA pins - Disable side band addressing.&n;&t; * With this lot disabled, we should prevent lockups. */
r_if
c_cond
(paren
id|agp_bridge-&gt;dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AMD_FE_GATE_700E
)paren
(brace
id|u8
id|revision
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|PCI_REVISION_ID
comma
op_amp
id|revision
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
l_int|0x10
op_logical_or
id|revision
op_eq
l_int|0x11
)paren
(brace
id|agp_bridge-&gt;flags
op_assign
id|AGP_ERRATA_FASTWRITES
suffix:semicolon
id|agp_bridge-&gt;flags
op_or_assign
id|AGP_ERRATA_SBA
suffix:semicolon
id|agp_bridge-&gt;flags
op_or_assign
id|AGP_ERRATA_1X
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;AMD 761 chipset with errata detected - disabling AGP fast writes &amp; SBA and forcing to 1X.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
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
DECL|function|agp_amdk7_remove
r_static
r_void
id|__devexit
id|agp_amdk7_remove
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
multiline_comment|/* must be the same order as name table above */
DECL|variable|agp_amdk7_pci_table
r_static
r_struct
id|pci_device_id
id|agp_amdk7_pci_table
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
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_FE_GATE_7006
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
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_FE_GATE_700E
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
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_FE_GATE_700C
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
id|agp_amdk7_pci_table
)paren
suffix:semicolon
DECL|variable|agp_amdk7_pci_driver
r_static
r_struct
id|pci_driver
id|agp_amdk7_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-amdk7&quot;
comma
dot
id|id_table
op_assign
id|agp_amdk7_pci_table
comma
dot
id|probe
op_assign
id|agp_amdk7_probe
comma
dot
id|remove
op_assign
id|agp_amdk7_remove
comma
)brace
suffix:semicolon
DECL|function|agp_amdk7_init
r_static
r_int
id|__init
id|agp_amdk7_init
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
id|agp_amdk7_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|agp_amdk7_cleanup
r_static
r_void
id|__exit
id|agp_amdk7_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_amdk7_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_amdk7_init
id|module_init
c_func
(paren
id|agp_amdk7_init
)paren
suffix:semicolon
DECL|variable|agp_amdk7_cleanup
id|module_exit
c_func
(paren
id|agp_amdk7_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
