multiline_comment|/*&n; * Serverworks AGPGART routines.&n; */
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
DECL|struct|serverworks_page_map
r_struct
id|serverworks_page_map
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
op_star
id|remapped
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_serverworks_private
r_static
r_struct
id|_serverworks_private
(brace
DECL|member|svrwrks_dev
r_struct
id|pci_dev
op_star
id|svrwrks_dev
suffix:semicolon
multiline_comment|/* device one */
DECL|member|registers
r_volatile
id|u8
op_star
id|registers
suffix:semicolon
DECL|member|gatt_pages
r_struct
id|serverworks_page_map
op_star
op_star
id|gatt_pages
suffix:semicolon
DECL|member|num_tables
r_int
id|num_tables
suffix:semicolon
DECL|member|scratch_dir
r_struct
id|serverworks_page_map
id|scratch_dir
suffix:semicolon
DECL|member|gart_addr_ofs
r_int
id|gart_addr_ofs
suffix:semicolon
DECL|member|mm_addr_ofs
r_int
id|mm_addr_ofs
suffix:semicolon
DECL|variable|serverworks_private
)brace
id|serverworks_private
suffix:semicolon
DECL|function|serverworks_create_page_map
r_static
r_int
id|serverworks_create_page_map
c_func
(paren
r_struct
id|serverworks_page_map
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
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
id|CACHE_FLUSH
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
id|CACHE_FLUSH
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
id|page_map-&gt;remapped
(braket
id|i
)braket
op_assign
id|agp_bridge.scratch_page
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serverworks_free_page_map
r_static
r_void
id|serverworks_free_page_map
c_func
(paren
r_struct
id|serverworks_page_map
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
DECL|function|serverworks_free_gatt_pages
r_static
r_void
id|serverworks_free_gatt_pages
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|serverworks_page_map
op_star
op_star
id|tables
suffix:semicolon
r_struct
id|serverworks_page_map
op_star
id|entry
suffix:semicolon
id|tables
op_assign
id|serverworks_private.gatt_pages
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
id|serverworks_private.num_tables
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
(brace
id|serverworks_free_page_map
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
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
)brace
DECL|function|serverworks_create_gatt_pages
r_static
r_int
id|serverworks_create_gatt_pages
c_func
(paren
r_int
id|nr_tables
)paren
(brace
r_struct
id|serverworks_page_map
op_star
op_star
id|tables
suffix:semicolon
r_struct
id|serverworks_page_map
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
id|serverworks_page_map
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
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|tables
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serverworks_page_map
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
id|serverworks_page_map
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
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serverworks_page_map
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
id|serverworks_create_page_map
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
id|serverworks_private.num_tables
op_assign
id|nr_tables
suffix:semicolon
id|serverworks_private.gatt_pages
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
id|serverworks_free_gatt_pages
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|SVRWRKS_GET_GATT
mdefine_line|#define SVRWRKS_GET_GATT(addr) (serverworks_private.gatt_pages[&bslash;&n;&t;GET_PAGE_DIR_IDX(addr)]-&gt;remapped)
macro_line|#ifndef GET_PAGE_DIR_OFF
DECL|macro|GET_PAGE_DIR_OFF
mdefine_line|#define GET_PAGE_DIR_OFF(addr) (addr &gt;&gt; 22)
macro_line|#endif
macro_line|#ifndef GET_PAGE_DIR_IDX
DECL|macro|GET_PAGE_DIR_IDX
mdefine_line|#define GET_PAGE_DIR_IDX(addr) (GET_PAGE_DIR_OFF(addr) - &bslash;&n;&t;GET_PAGE_DIR_OFF(agp_bridge.gart_bus_addr))
macro_line|#endif
macro_line|#ifndef GET_GATT_OFF
DECL|macro|GET_GATT_OFF
mdefine_line|#define GET_GATT_OFF(addr) ((addr &amp; 0x003ff000) &gt;&gt; 12)
macro_line|#endif
DECL|function|serverworks_create_gatt_table
r_static
r_int
id|serverworks_create_gatt_table
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
id|serverworks_page_map
id|page_dir
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
id|agp_bridge.current_size
)paren
suffix:semicolon
id|retval
op_assign
id|serverworks_create_page_map
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
(brace
r_return
id|retval
suffix:semicolon
)brace
id|retval
op_assign
id|serverworks_create_page_map
c_func
(paren
op_amp
id|serverworks_private.scratch_dir
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
id|serverworks_free_page_map
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
multiline_comment|/* Create a fake scratch directory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1024
suffix:semicolon
id|i
op_increment
)paren
(brace
id|serverworks_private.scratch_dir.remapped
(braket
id|i
)braket
op_assign
(paren
r_int
r_int
)paren
id|agp_bridge.scratch_page
suffix:semicolon
id|page_dir.remapped
(braket
id|i
)braket
op_assign
id|virt_to_phys
c_func
(paren
id|serverworks_private.scratch_dir.real
)paren
suffix:semicolon
id|page_dir.remapped
(braket
id|i
)braket
op_or_assign
l_int|0x00000001
suffix:semicolon
)brace
id|retval
op_assign
id|serverworks_create_gatt_pages
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
id|serverworks_free_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
id|serverworks_free_page_map
c_func
(paren
op_amp
id|serverworks_private.scratch_dir
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|agp_bridge.gatt_table_real
op_assign
(paren
id|u32
op_star
)paren
id|page_dir.real
suffix:semicolon
id|agp_bridge.gatt_table
op_assign
(paren
id|u32
op_star
)paren
id|page_dir.remapped
suffix:semicolon
id|agp_bridge.gatt_bus_addr
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
id|agp_bridge.dev
comma
id|serverworks_private.gart_addr_ofs
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
)paren
(brace
id|page_dir.remapped
(braket
id|i
)braket
op_assign
id|virt_to_phys
c_func
(paren
id|serverworks_private.gatt_pages
(braket
id|i
)braket
op_member_access_from_pointer
id|real
)paren
suffix:semicolon
id|page_dir.remapped
(braket
id|i
)braket
op_or_assign
l_int|0x00000001
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serverworks_free_gatt_table
r_static
r_int
id|serverworks_free_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|serverworks_page_map
id|page_dir
suffix:semicolon
id|page_dir.real
op_assign
(paren
r_int
r_int
op_star
)paren
id|agp_bridge.gatt_table_real
suffix:semicolon
id|page_dir.remapped
op_assign
(paren
r_int
r_int
op_star
)paren
id|agp_bridge.gatt_table
suffix:semicolon
id|serverworks_free_gatt_pages
c_func
(paren
)paren
suffix:semicolon
id|serverworks_free_page_map
c_func
(paren
op_amp
id|page_dir
)paren
suffix:semicolon
id|serverworks_free_page_map
c_func
(paren
op_amp
id|serverworks_private.scratch_dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serverworks_fetch_size
r_static
r_int
id|serverworks_fetch_size
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
id|u32
id|temp2
suffix:semicolon
r_struct
id|aper_size_info_lvl2
op_star
id|values
suffix:semicolon
id|values
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.aperture_sizes
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.gart_addr_ofs
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.gart_addr_ofs
comma
id|SVWRKS_SIZE_MASK
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.gart_addr_ofs
comma
op_amp
id|temp2
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.gart_addr_ofs
comma
id|temp
)paren
suffix:semicolon
id|temp2
op_and_assign
id|SVWRKS_SIZE_MASK
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
id|temp2
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
DECL|function|serverworks_configure
r_static
r_int
id|serverworks_configure
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
id|u8
id|enable_reg
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
id|u32
id|cap_id
suffix:semicolon
id|u16
id|cap_reg
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_LVL2
c_func
(paren
id|agp_bridge.current_size
)paren
suffix:semicolon
multiline_comment|/* Get the memory mapped registers */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.mm_addr_ofs
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
id|serverworks_private.registers
op_assign
(paren
r_volatile
id|u8
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
id|OUTREG8
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_GART_CACHE
comma
l_int|0x0a
)paren
suffix:semicolon
id|OUTREG32
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_GATTBASE
comma
id|agp_bridge.gatt_bus_addr
)paren
suffix:semicolon
id|cap_reg
op_assign
id|INREG16
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_COMMAND
)paren
suffix:semicolon
id|cap_reg
op_and_assign
op_complement
l_int|0x0007
suffix:semicolon
id|cap_reg
op_or_assign
l_int|0x4
suffix:semicolon
id|OUTREG16
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_COMMAND
comma
id|cap_reg
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
id|SVWRKS_AGP_ENABLE
comma
op_amp
id|enable_reg
)paren
suffix:semicolon
id|enable_reg
op_or_assign
l_int|0x1
suffix:semicolon
multiline_comment|/* Agp Enable bit */
id|pci_write_config_byte
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
id|SVWRKS_AGP_ENABLE
comma
id|enable_reg
)paren
suffix:semicolon
id|agp_bridge
dot
id|tlb_flush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
l_int|0x34
comma
op_amp
id|cap_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap_ptr
op_ne
l_int|0
)paren
(brace
r_do
(brace
id|pci_read_config_dword
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
id|cap_ptr
comma
op_amp
id|cap_id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cap_id
op_amp
l_int|0xff
)paren
op_ne
l_int|0x02
)paren
id|cap_ptr
op_assign
(paren
id|cap_id
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|cap_id
op_amp
l_int|0xff
)paren
op_ne
l_int|0x02
)paren
op_logical_and
(paren
id|cap_ptr
op_ne
l_int|0
)paren
)paren
suffix:semicolon
)brace
id|agp_bridge.capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* Fill in the mode register */
id|pci_read_config_dword
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
id|agp_bridge.capndx
op_plus
l_int|4
comma
op_amp
id|agp_bridge.mode
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|SVWRKS_CACHING
comma
op_amp
id|enable_reg
)paren
suffix:semicolon
id|enable_reg
op_and_assign
op_complement
l_int|0x3
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|SVWRKS_CACHING
comma
id|enable_reg
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|SVWRKS_FEATURE
comma
op_amp
id|enable_reg
)paren
suffix:semicolon
id|enable_reg
op_or_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge.dev
comma
id|SVWRKS_FEATURE
comma
id|enable_reg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serverworks_cleanup
r_static
r_void
id|serverworks_cleanup
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
op_star
)paren
id|serverworks_private.registers
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine could be implemented by taking the addresses&n; * written to the GATT, and flushing them individually.  However&n; * currently it just flushes the whole table.  Which is probably&n; * more efficent, since agp_memory blocks can be a large number of&n; * entries.&n; */
DECL|function|serverworks_tlbflush
r_static
r_void
id|serverworks_tlbflush
c_func
(paren
id|agp_memory
op_star
id|temp
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|OUTREG8
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_POSTFLUSH
comma
l_int|0x01
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
r_while
c_loop
(paren
id|INREG8
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_POSTFLUSH
)paren
op_eq
l_int|0x01
)paren
(brace
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
l_string|&quot;Posted write buffer flush took more&quot;
l_string|&quot;then 3 seconds&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|OUTREG32
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_DIRFLUSH
comma
l_int|0x00000001
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
r_while
c_loop
(paren
id|INREG32
c_func
(paren
id|serverworks_private.registers
comma
id|SVWRKS_DIRFLUSH
)paren
op_eq
l_int|0x00000001
)paren
(brace
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
l_string|&quot;TLB flush took more&quot;
l_string|&quot;then 3 seconds&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|serverworks_mask_memory
r_static
r_int
r_int
id|serverworks_mask_memory
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
multiline_comment|/* Only type 0 is supported by the serverworks chipsets */
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
DECL|function|serverworks_insert_memory
r_static
r_int
id|serverworks_insert_memory
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
r_int
id|i
comma
id|j
comma
id|num_entries
suffix:semicolon
r_int
r_int
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
id|agp_bridge.current_size
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
(brace
r_return
op_minus
id|EINVAL
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|SVRWRKS_GET_GATT
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
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)braket
)paren
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
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
id|CACHE_FLUSH
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
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|SVRWRKS_GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)braket
op_assign
id|agp_bridge
dot
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
)brace
id|agp_bridge
dot
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
DECL|function|serverworks_remove_memory
r_static
r_int
id|serverworks_remove_memory
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
r_int
id|i
suffix:semicolon
r_int
r_int
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|CACHE_FLUSH
c_func
(paren
)paren
suffix:semicolon
id|agp_bridge
dot
id|tlb_flush
c_func
(paren
id|mem
)paren
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
id|agp_bridge.gart_bus_addr
suffix:semicolon
id|cur_gatt
op_assign
id|SVRWRKS_GET_GATT
c_func
(paren
id|addr
)paren
suffix:semicolon
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|addr
)paren
)braket
op_assign
(paren
r_int
r_int
)paren
id|agp_bridge.scratch_page
suffix:semicolon
)brace
id|agp_bridge
dot
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
DECL|variable|serverworks_masks
r_static
r_struct
id|gatt_mask
id|serverworks_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
l_int|0x00000001
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|serverworks_sizes
r_static
r_struct
id|aper_size_info_lvl2
id|serverworks_sizes
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
l_int|0x80000000
)brace
comma
(brace
l_int|1024
comma
l_int|262144
comma
l_int|0xc0000000
)brace
comma
(brace
l_int|512
comma
l_int|131072
comma
l_int|0xe0000000
)brace
comma
(brace
l_int|256
comma
l_int|65536
comma
l_int|0xf0000000
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|0xf8000000
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|0xfc000000
)brace
comma
(brace
l_int|32
comma
l_int|8192
comma
l_int|0xfe000000
)brace
)brace
suffix:semicolon
DECL|function|serverworks_agp_enable
r_static
r_void
id|serverworks_agp_enable
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
comma
id|scratch
comma
id|cap_id
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
id|agp_bridge.capndx
op_plus
l_int|4
comma
op_amp
id|command
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * PASS1: go throu all devices that claim to be&n;&t; *        AGP devices and collect their data.&n;&t; */
id|pci_for_each_dev
c_func
(paren
id|device
)paren
(brace
id|cap_ptr
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
id|cap_ptr
op_ne
l_int|0x00
)paren
(brace
r_do
(brace
id|pci_read_config_dword
c_func
(paren
id|device
comma
id|cap_ptr
comma
op_amp
id|cap_id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cap_id
op_amp
l_int|0xff
)paren
op_ne
l_int|0x02
)paren
id|cap_ptr
op_assign
(paren
id|cap_id
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|cap_id
op_amp
l_int|0xff
)paren
op_ne
l_int|0x02
)paren
op_logical_and
(paren
id|cap_ptr
op_ne
l_int|0x00
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cap_ptr
op_ne
l_int|0x00
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Ok, here we have a AGP device. Disable impossible &n;&t;&t;&t; * settings, and adjust the readqueue to the minimum.&n;&t;&t;&t; */
id|pci_read_config_dword
c_func
(paren
id|device
comma
id|cap_ptr
op_plus
l_int|4
comma
op_amp
id|scratch
)paren
suffix:semicolon
multiline_comment|/* adjust RQ depth */
id|command
op_assign
(paren
(paren
id|command
op_amp
op_complement
l_int|0xff000000
)paren
op_or
id|min_t
c_func
(paren
id|u32
comma
(paren
id|mode
op_amp
l_int|0xff000000
)paren
comma
id|min_t
c_func
(paren
id|u32
comma
(paren
id|command
op_amp
l_int|0xff000000
)paren
comma
(paren
id|scratch
op_amp
l_int|0xff000000
)paren
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* disable SBA if it&squot;s not supported */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|0x00000200
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|0x00000200
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|0x00000200
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000200
suffix:semicolon
multiline_comment|/* disable FW */
id|command
op_and_assign
op_complement
l_int|0x00000010
suffix:semicolon
id|command
op_and_assign
op_complement
l_int|0x00000008
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|4
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|4
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|4
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000004
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|2
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|2
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|2
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000002
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|command
op_amp
l_int|1
)paren
op_logical_and
(paren
id|scratch
op_amp
l_int|1
)paren
op_logical_and
(paren
id|mode
op_amp
l_int|1
)paren
)paren
)paren
id|command
op_and_assign
op_complement
l_int|0x00000001
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * PASS2: Figure out the 4X/2X/1X setting and enable the&n;&t; *        target (our motherboard chipset).&n;&t; */
r_if
c_cond
(paren
id|command
op_amp
l_int|4
)paren
(brace
id|command
op_and_assign
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* 4X */
)brace
r_if
c_cond
(paren
id|command
op_amp
l_int|2
)paren
(brace
id|command
op_and_assign
op_complement
l_int|5
suffix:semicolon
multiline_comment|/* 2X */
)brace
r_if
c_cond
(paren
id|command
op_amp
l_int|1
)paren
(brace
id|command
op_and_assign
op_complement
l_int|6
suffix:semicolon
multiline_comment|/* 1X */
)brace
id|command
op_or_assign
l_int|0x00000100
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|serverworks_private.svrwrks_dev
comma
id|agp_bridge.capndx
op_plus
l_int|8
comma
id|command
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * PASS3: Go throu all AGP devices and update the&n;&t; *        command registers.&n;&t; */
id|pci_for_each_dev
c_func
(paren
id|device
)paren
(brace
id|cap_ptr
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
id|cap_ptr
op_ne
l_int|0x00
)paren
id|pci_write_config_dword
c_func
(paren
id|device
comma
id|cap_ptr
op_plus
l_int|8
comma
id|command
)paren
suffix:semicolon
)brace
)brace
DECL|function|serverworks_setup
r_static
r_int
id|__init
id|serverworks_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|u32
id|temp
suffix:semicolon
id|u32
id|temp2
suffix:semicolon
id|serverworks_private.svrwrks_dev
op_assign
id|pdev
suffix:semicolon
id|agp_bridge.masks
op_assign
id|serverworks_masks
suffix:semicolon
id|agp_bridge.aperture_sizes
op_assign
(paren
r_void
op_star
)paren
id|serverworks_sizes
suffix:semicolon
id|agp_bridge.size_type
op_assign
id|LVL2_APER_SIZE
suffix:semicolon
id|agp_bridge.num_aperture_sizes
op_assign
l_int|7
suffix:semicolon
id|agp_bridge.dev_private_data
op_assign
(paren
r_void
op_star
)paren
op_amp
id|serverworks_private
suffix:semicolon
id|agp_bridge.needs_scratch_page
op_assign
id|TRUE
suffix:semicolon
id|agp_bridge.configure
op_assign
id|serverworks_configure
suffix:semicolon
id|agp_bridge.fetch_size
op_assign
id|serverworks_fetch_size
suffix:semicolon
id|agp_bridge.cleanup
op_assign
id|serverworks_cleanup
suffix:semicolon
id|agp_bridge.tlb_flush
op_assign
id|serverworks_tlbflush
suffix:semicolon
id|agp_bridge.mask_memory
op_assign
id|serverworks_mask_memory
suffix:semicolon
id|agp_bridge.agp_enable
op_assign
id|serverworks_agp_enable
suffix:semicolon
id|agp_bridge.cache_flush
op_assign
id|global_cache_flush
suffix:semicolon
id|agp_bridge.create_gatt_table
op_assign
id|serverworks_create_gatt_table
suffix:semicolon
id|agp_bridge.free_gatt_table
op_assign
id|serverworks_free_gatt_table
suffix:semicolon
id|agp_bridge.insert_memory
op_assign
id|serverworks_insert_memory
suffix:semicolon
id|agp_bridge.remove_memory
op_assign
id|serverworks_remove_memory
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
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|SVWRKS_APSIZE
comma
op_amp
id|temp
)paren
suffix:semicolon
id|serverworks_private.gart_addr_ofs
op_assign
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|SVWRKS_APSIZE
op_plus
l_int|4
comma
op_amp
id|temp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp2
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Detected 64 bit aperture address, but top &quot;
l_string|&quot;bits are not zero.  Disabling agp&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|serverworks_private.mm_addr_ofs
op_assign
l_int|0x18
suffix:semicolon
)brace
r_else
(brace
id|serverworks_private.mm_addr_ofs
op_assign
l_int|0x14
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.mm_addr_ofs
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|serverworks_private.mm_addr_ofs
op_plus
l_int|4
comma
op_amp
id|temp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp2
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Detected 64 bit MMIO address, but top &quot;
l_string|&quot;bits are not zero.  Disabling agp&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_find_supported_device
r_static
r_int
id|__init
id|agp_find_supported_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge_dev
suffix:semicolon
multiline_comment|/* Everything is on func 1 here so we are hardcoding function one */
id|bridge_dev
op_assign
id|pci_find_slot
(paren
(paren
r_int
r_int
)paren
id|dev-&gt;bus-&gt;number
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
r_if
c_cond
(paren
id|bridge_dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;agpgart: Detected a Serverworks &quot;
l_string|&quot;Chipset, but could not find the secondary &quot;
l_string|&quot;device.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|agp_bridge.dev
op_assign
id|dev
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_SERVERWORKS_HE
suffix:colon
id|agp_bridge.type
op_assign
id|SVWRKS_HE
suffix:semicolon
r_return
id|serverworks_setup
c_func
(paren
id|bridge_dev
)paren
suffix:semicolon
r_case
id|PCI_DEVICE_ID_SERVERWORKS_LE
suffix:colon
r_case
l_int|0x0007
suffix:colon
id|agp_bridge.type
op_assign
id|SVWRKS_LE
suffix:semicolon
r_return
id|serverworks_setup
c_func
(paren
id|bridge_dev
)paren
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|agp_try_unsupported
)paren
(brace
id|agp_bridge.type
op_assign
id|SVWRKS_GENERIC
suffix:semicolon
r_return
id|serverworks_setup
c_func
(paren
id|bridge_dev
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|agp_serverworks_probe
r_static
r_int
id|__init
id|agp_serverworks_probe
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
r_if
c_cond
(paren
id|agp_find_supported_device
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
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
id|agp_serverworks_pci_table
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
id|PCI_VENDOR_ID_SERVERWORKS
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
id|agp_serverworks_pci_table
)paren
suffix:semicolon
DECL|variable|agp_serverworks_pci_driver
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_serverworks_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-serverworks&quot;
comma
dot
id|id_table
op_assign
id|agp_serverworks_pci_table
comma
dot
id|probe
op_assign
id|agp_serverworks_probe
comma
)brace
suffix:semicolon
DECL|function|agp_serverworks_init
r_static
r_int
id|__init
id|agp_serverworks_init
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
id|agp_serverworks_pci_driver
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
DECL|function|agp_serverworks_cleanup
r_static
r_void
id|__exit
id|agp_serverworks_cleanup
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
id|agp_serverworks_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_serverworks_init
id|module_init
c_func
(paren
id|agp_serverworks_init
)paren
suffix:semicolon
DECL|variable|agp_serverworks_cleanup
id|module_exit
c_func
(paren
id|agp_serverworks_cleanup
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
