multiline_comment|/* &n; * Handle the memory map.&n; * The functions here do the job until bootmem takes over.&n; * $Id: e820.c,v 1.4 2002/09/19 19:25:32 ak Exp $&n;&n; * AK: some of these functions are not used in 2.5 yet but they will be when&n; * NUMA is completely merged.&n;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/bootsetup.h&gt;
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
multiline_comment|/* &n; * PFN of last memory page.&n; */
DECL|variable|end_pfn
r_int
r_int
id|end_pfn
suffix:semicolon
multiline_comment|/* &n; * end_pfn only includes RAM, while end_pfn_map includes all e820 entries.&n; * The direct mapping extends to end_pfn_map, so that we can directly access&n; * apertures, ACPI and other tables without having to play with fixmaps.&n; */
DECL|variable|end_pfn_map
r_int
r_int
id|end_pfn_map
suffix:semicolon
multiline_comment|/* &n; * Last pfn which the user wants to use.&n; */
DECL|variable|end_user_pfn
r_int
r_int
id|end_user_pfn
op_assign
id|MAXMEM
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_extern
r_struct
id|resource
id|code_resource
comma
id|data_resource
comma
id|vram_resource
suffix:semicolon
multiline_comment|/* Check for some hardcoded bad areas that early boot is not allowed to touch */
DECL|function|bad_addr
r_static
r_inline
r_int
id|bad_addr
c_func
(paren
r_int
r_int
op_star
id|addrp
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|addr
op_assign
op_star
id|addrp
comma
id|last
op_assign
id|addr
op_plus
id|size
suffix:semicolon
multiline_comment|/* various gunk below that needed for SMP startup */
r_if
c_cond
(paren
id|addr
OL
l_int|0x8000
)paren
(brace
op_star
id|addrp
op_assign
l_int|0x8000
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* direct mapping tables of the kernel */
r_if
c_cond
(paren
id|last
op_ge
id|table_start
op_lshift
id|PAGE_SHIFT
op_logical_and
id|addr
OL
id|table_end
op_lshift
id|PAGE_SHIFT
)paren
(brace
op_star
id|addrp
op_assign
id|table_end
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* initrd */
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|LOADER_TYPE
op_logical_and
id|INITRD_START
op_logical_and
id|last
op_ge
id|INITRD_START
op_logical_and
id|addr
OL
id|INITRD_START
op_plus
id|INITRD_SIZE
)paren
(brace
op_star
id|addrp
op_assign
id|INITRD_START
op_plus
id|INITRD_SIZE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* kernel code + 640k memory hole (later should not be needed, but &n;&t;   be paranoid for now) */
r_if
c_cond
(paren
id|last
op_ge
l_int|640
op_star
l_int|1024
op_logical_and
id|addr
OL
id|__pa_symbol
c_func
(paren
op_amp
id|_end
)paren
)paren
(brace
op_star
id|addrp
op_assign
id|__pa_symbol
c_func
(paren
op_amp
id|_end
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* XXX ramdisk image here? */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|e820_mapped
r_int
id|__init
id|e820_mapped
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|type
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
id|i
OL
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|e820entry
op_star
id|ei
op_assign
op_amp
id|e820.map
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|type
op_logical_and
id|ei-&gt;type
op_ne
id|type
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ei-&gt;addr
op_ge
id|end
op_logical_or
id|ei-&gt;addr
op_plus
id|ei-&gt;size
OL
id|start
)paren
r_continue
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Find a free area in a specific range. &n; */
DECL|function|find_e820_area
r_int
r_int
id|__init
id|find_e820_area
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|size
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
id|i
OL
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|e820entry
op_star
id|ei
op_assign
op_amp
id|e820.map
(braket
id|i
)braket
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|ei-&gt;addr
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
id|ei-&gt;type
op_ne
id|E820_RAM
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|start
)paren
id|addr
op_assign
id|start
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|ei-&gt;addr
op_plus
id|ei-&gt;size
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|bad_addr
c_func
(paren
op_amp
id|addr
comma
id|size
)paren
op_logical_and
id|addr
op_plus
id|size
OL
id|ei-&gt;addr
op_plus
id|ei-&gt;size
)paren
suffix:semicolon
id|last
op_assign
id|addr
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|last
OG
id|ei-&gt;addr
op_plus
id|ei-&gt;size
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|last
OG
id|end
)paren
r_continue
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
r_return
op_minus
l_int|1UL
suffix:semicolon
)brace
multiline_comment|/* &n; * Free bootmem based on the e820 table for a node.&n; */
DECL|function|e820_bootmem_free
r_void
id|__init
id|e820_bootmem_free
c_func
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
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
id|i
OL
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|e820entry
op_star
id|ei
op_assign
op_amp
id|e820.map
(braket
id|i
)braket
suffix:semicolon
r_int
r_int
id|last
comma
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|ei-&gt;type
op_ne
id|E820_RAM
op_logical_or
id|ei-&gt;addr
op_plus
id|ei-&gt;size
op_le
id|start
op_logical_or
id|ei-&gt;addr
OG
id|end
)paren
r_continue
suffix:semicolon
id|addr
op_assign
id|round_up
c_func
(paren
id|ei-&gt;addr
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|start
)paren
id|addr
op_assign
id|start
suffix:semicolon
id|last
op_assign
id|round_down
c_func
(paren
id|ei-&gt;addr
op_plus
id|ei-&gt;size
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last
op_ge
id|end
)paren
id|last
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
id|last
OG
id|addr
op_logical_and
id|last
op_minus
id|addr
op_ge
id|PAGE_SIZE
)paren
id|free_bootmem_node
c_func
(paren
id|pgdat
comma
id|addr
comma
id|last
op_minus
id|addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Find the highest page frame number we have available&n; */
DECL|function|e820_end_of_ram
r_int
r_int
id|__init
id|e820_end_of_ram
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|end_pfn
op_assign
l_int|0
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
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|e820entry
op_star
id|ei
op_assign
op_amp
id|e820.map
(braket
id|i
)braket
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
id|start
op_assign
id|round_up
c_func
(paren
id|ei-&gt;addr
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|end
op_assign
id|round_down
c_func
(paren
id|ei-&gt;addr
op_plus
id|ei-&gt;size
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ei-&gt;type
op_eq
id|E820_RAM
)paren
(brace
r_if
c_cond
(paren
id|end
OG
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
id|end_pfn
op_assign
id|end
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|end
OG
id|end_pfn_map
op_lshift
id|PAGE_SHIFT
)paren
id|end_pfn_map
op_assign
id|end
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|end_pfn
OG
id|end_pfn_map
)paren
id|end_pfn_map
op_assign
id|end_pfn
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn_map
OG
id|MAXMEM
op_rshift
id|PAGE_SHIFT
)paren
id|end_pfn_map
op_assign
id|MAXMEM
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
OG
id|end_user_pfn
)paren
id|end_pfn
op_assign
id|end_user_pfn
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
OG
id|end_pfn_map
)paren
id|end_pfn
op_assign
id|end_pfn_map
suffix:semicolon
r_return
id|end_pfn
suffix:semicolon
)brace
multiline_comment|/* &n; * Mark e820 reserved areas as busy for the resource manager.&n; */
DECL|function|e820_reserve_resources
r_void
id|__init
id|e820_reserve_resources
c_func
(paren
r_void
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
id|i
OL
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|e820.map
(braket
id|i
)braket
dot
id|size
OG
l_int|0x100000000ULL
)paren
r_continue
suffix:semicolon
id|res
op_assign
id|alloc_bootmem_low
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
)paren
(brace
r_case
id|E820_RAM
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;System RAM&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E820_ACPI
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;ACPI Tables&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E820_NVS
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;ACPI Non-volatile Storage&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
)brace
id|res-&gt;start
op_assign
id|e820.map
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|res-&gt;end
op_assign
id|res-&gt;start
op_plus
id|e820.map
(braket
id|i
)braket
dot
id|size
op_minus
l_int|1
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
op_eq
id|E820_RAM
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *  We dont&squot;t know which RAM region contains kernel data,&n;&t;&t;&t; *  so we try it repeatedly and let the resource manager&n;&t;&t;&t; *  test it.&n;&t;&t;&t; */
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|code_resource
)paren
suffix:semicolon
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|data_resource
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* &n; * Add a memory region to the kernel e820 map.&n; */
DECL|function|add_memory_region
r_void
id|__init
id|add_memory_region
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
comma
r_int
id|type
)paren
(brace
r_int
id|x
op_assign
id|e820.nr_map
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
id|E820MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Ooops! Too many entries in the memory map!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|e820.map
(braket
id|x
)braket
dot
id|addr
op_assign
id|start
suffix:semicolon
id|e820.map
(braket
id|x
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|e820.map
(braket
id|x
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|e820.nr_map
op_increment
suffix:semicolon
)brace
DECL|function|e820_print_map
r_void
id|__init
id|e820_print_map
c_func
(paren
r_char
op_star
id|who
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
id|i
OL
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %s: %016Lx - %016Lx &quot;
comma
id|who
comma
(paren
r_int
r_int
r_int
)paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
comma
(paren
r_int
r_int
r_int
)paren
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|e820.map
(braket
id|i
)braket
dot
id|size
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
)paren
(brace
r_case
id|E820_RAM
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(usable)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E820_RESERVED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(reserved)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E820_ACPI
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(ACPI data)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|E820_NVS
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(ACPI NVS)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;type %u&bslash;n&quot;
comma
id|e820.map
(braket
id|i
)braket
dot
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Sanitize the BIOS e820 map.&n; *&n; * Some e820 responses include overlapping entries.  The following &n; * replaces the original e820 map with a new one, removing overlaps.&n; *&n; */
DECL|function|sanitize_e820_map
r_static
r_int
id|__init
id|sanitize_e820_map
c_func
(paren
r_struct
id|e820entry
op_star
id|biosmap
comma
r_char
op_star
id|pnr_map
)paren
(brace
r_struct
id|change_member
(brace
r_struct
id|e820entry
op_star
id|pbios
suffix:semicolon
multiline_comment|/* pointer to original bios entry */
r_int
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* address for this change point */
)brace
suffix:semicolon
r_static
r_struct
id|change_member
id|change_point_list
(braket
l_int|2
op_star
id|E820MAX
)braket
id|__initdata
suffix:semicolon
r_static
r_struct
id|change_member
op_star
id|change_point
(braket
l_int|2
op_star
id|E820MAX
)braket
id|__initdata
suffix:semicolon
r_static
r_struct
id|e820entry
op_star
id|overlap_list
(braket
id|E820MAX
)braket
id|__initdata
suffix:semicolon
r_static
r_struct
id|e820entry
id|new_bios
(braket
id|E820MAX
)braket
id|__initdata
suffix:semicolon
r_struct
id|change_member
op_star
id|change_tmp
suffix:semicolon
r_int
r_int
id|current_type
comma
id|last_type
suffix:semicolon
r_int
r_int
r_int
id|last_addr
suffix:semicolon
r_int
id|chgidx
comma
id|still_changing
suffix:semicolon
r_int
id|overlap_entries
suffix:semicolon
r_int
id|new_bios_entry
suffix:semicolon
r_int
id|old_nr
comma
id|new_nr
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t;Visually we&squot;re performing the following (1,2,3,4 = memory types)...&n;&n;&t;&t;Sample memory map (w/overlaps):&n;&t;&t;   ____22__________________&n;&t;&t;   ______________________4_&n;&t;&t;   ____1111________________&n;&t;&t;   _44_____________________&n;&t;&t;   11111111________________&n;&t;&t;   ____________________33__&n;&t;&t;   ___________44___________&n;&t;&t;   __________33333_________&n;&t;&t;   ______________22________&n;&t;&t;   ___________________2222_&n;&t;&t;   _________111111111______&n;&t;&t;   _____________________11_&n;&t;&t;   _________________4______&n;&n;&t;&t;Sanitized equivalent (no overlap):&n;&t;&t;   1_______________________&n;&t;&t;   _44_____________________&n;&t;&t;   ___1____________________&n;&t;&t;   ____22__________________&n;&t;&t;   ______11________________&n;&t;&t;   _________1______________&n;&t;&t;   __________3_____________&n;&t;&t;   ___________44___________&n;&t;&t;   _____________33_________&n;&t;&t;   _______________2________&n;&t;&t;   ________________1_______&n;&t;&t;   _________________4______&n;&t;&t;   ___________________2____&n;&t;&t;   ____________________33__&n;&t;&t;   ______________________4_&n;&t;*/
multiline_comment|/* if there&squot;s only one memory region, don&squot;t bother */
r_if
c_cond
(paren
op_star
id|pnr_map
OL
l_int|2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|old_nr
op_assign
op_star
id|pnr_map
suffix:semicolon
multiline_comment|/* bail out if we find any unreasonable addresses in bios map */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|old_nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|biosmap
(braket
id|i
)braket
dot
id|addr
op_plus
id|biosmap
(braket
id|i
)braket
dot
id|size
OL
id|biosmap
(braket
id|i
)braket
dot
id|addr
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* create pointers for initial change-point information (for sorting) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
op_star
id|old_nr
suffix:semicolon
id|i
op_increment
)paren
id|change_point
(braket
id|i
)braket
op_assign
op_amp
id|change_point_list
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* record all known change-points (starting and ending addresses) */
id|chgidx
op_assign
l_int|0
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
id|old_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|addr
op_assign
id|biosmap
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|change_point
(braket
id|chgidx
op_increment
)braket
op_member_access_from_pointer
id|pbios
op_assign
op_amp
id|biosmap
(braket
id|i
)braket
suffix:semicolon
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|addr
op_assign
id|biosmap
(braket
id|i
)braket
dot
id|addr
op_plus
id|biosmap
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|change_point
(braket
id|chgidx
op_increment
)braket
op_member_access_from_pointer
id|pbios
op_assign
op_amp
id|biosmap
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* sort change-point list by memory addresses (low -&gt; high) */
id|still_changing
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|still_changing
)paren
(brace
id|still_changing
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|2
op_star
id|old_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* if &lt;current_addr&gt; &gt; &lt;last_addr&gt;, swap */
multiline_comment|/* or, if current=&lt;start_addr&gt; &amp; last=&lt;end_addr&gt;, swap */
r_if
c_cond
(paren
(paren
id|change_point
(braket
id|i
)braket
op_member_access_from_pointer
id|addr
OL
id|change_point
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|addr
)paren
op_logical_or
(paren
(paren
id|change_point
(braket
id|i
)braket
op_member_access_from_pointer
id|addr
op_eq
id|change_point
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|addr
)paren
op_logical_and
(paren
id|change_point
(braket
id|i
)braket
op_member_access_from_pointer
id|addr
op_eq
id|change_point
(braket
id|i
)braket
op_member_access_from_pointer
id|pbios-&gt;addr
)paren
op_logical_and
(paren
id|change_point
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|addr
op_ne
id|change_point
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|pbios-&gt;addr
)paren
)paren
)paren
(brace
id|change_tmp
op_assign
id|change_point
(braket
id|i
)braket
suffix:semicolon
id|change_point
(braket
id|i
)braket
op_assign
id|change_point
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|change_point
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|change_tmp
suffix:semicolon
id|still_changing
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* create a new bios memory map, removing overlaps */
id|overlap_entries
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of entries in the overlap table */
id|new_bios_entry
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* index for creating new bios map entries */
id|last_type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* start with undefined memory type */
id|last_addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* start with 0 as last starting address */
multiline_comment|/* loop through change-points, determining affect on the new bios map */
r_for
c_loop
(paren
id|chgidx
op_assign
l_int|0
suffix:semicolon
id|chgidx
OL
l_int|2
op_star
id|old_nr
suffix:semicolon
id|chgidx
op_increment
)paren
(brace
multiline_comment|/* keep track of all overlapping bios entries */
r_if
c_cond
(paren
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|addr
op_eq
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|pbios-&gt;addr
)paren
(brace
multiline_comment|/* add map entry to overlap list (&gt; 1 entry implies an overlap) */
id|overlap_list
(braket
id|overlap_entries
op_increment
)braket
op_assign
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|pbios
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* remove entry from list (order independent, so swap with last) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|overlap_entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|overlap_list
(braket
id|i
)braket
op_eq
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|pbios
)paren
id|overlap_list
(braket
id|i
)braket
op_assign
id|overlap_list
(braket
id|overlap_entries
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|overlap_entries
op_decrement
suffix:semicolon
)brace
multiline_comment|/* if there are overlapping entries, decide which &quot;type&quot; to use */
multiline_comment|/* (larger value takes precedence -- 1=usable, 2,3,4,4+=unusable) */
id|current_type
op_assign
l_int|0
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
id|overlap_entries
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|overlap_list
(braket
id|i
)braket
op_member_access_from_pointer
id|type
OG
id|current_type
)paren
id|current_type
op_assign
id|overlap_list
(braket
id|i
)braket
op_member_access_from_pointer
id|type
suffix:semicolon
multiline_comment|/* continue building up new bios map based on this information */
r_if
c_cond
(paren
id|current_type
op_ne
id|last_type
)paren
(brace
r_if
c_cond
(paren
id|last_type
op_ne
l_int|0
)paren
(brace
id|new_bios
(braket
id|new_bios_entry
)braket
dot
id|size
op_assign
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|addr
op_minus
id|last_addr
suffix:semicolon
multiline_comment|/* move forward only if the new size was non-zero */
r_if
c_cond
(paren
id|new_bios
(braket
id|new_bios_entry
)braket
dot
id|size
op_ne
l_int|0
)paren
r_if
c_cond
(paren
op_increment
id|new_bios_entry
op_ge
id|E820MAX
)paren
r_break
suffix:semicolon
multiline_comment|/* no more space left for new bios entries */
)brace
r_if
c_cond
(paren
id|current_type
op_ne
l_int|0
)paren
(brace
id|new_bios
(braket
id|new_bios_entry
)braket
dot
id|addr
op_assign
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|addr
suffix:semicolon
id|new_bios
(braket
id|new_bios_entry
)braket
dot
id|type
op_assign
id|current_type
suffix:semicolon
id|last_addr
op_assign
id|change_point
(braket
id|chgidx
)braket
op_member_access_from_pointer
id|addr
suffix:semicolon
)brace
id|last_type
op_assign
id|current_type
suffix:semicolon
)brace
)brace
id|new_nr
op_assign
id|new_bios_entry
suffix:semicolon
multiline_comment|/* retain count for new bios entries */
multiline_comment|/* copy new bios mapping into original location */
id|memcpy
c_func
(paren
id|biosmap
comma
id|new_bios
comma
id|new_nr
op_star
r_sizeof
(paren
r_struct
id|e820entry
)paren
)paren
suffix:semicolon
op_star
id|pnr_map
op_assign
id|new_nr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy the BIOS e820 map into a safe place.&n; *&n; * Sanity-check it while we&squot;re at it..&n; *&n; * If we&squot;re lucky and live on a modern system, the setup code&n; * will have given us a memory map that we can use to properly&n; * set up memory.  If we aren&squot;t, we&squot;ll fake a memory map.&n; *&n; * We check to see that the memory map contains at least 2 elements&n; * before we&squot;ll use it, because the detection code in setup.S may&n; * not be perfect and most every PC known to man has two memory&n; * regions: one from 0 to 640k, and one from 1mb up.  (The IBM&n; * thinkpad 560x, for example, does not cooperate with the memory&n; * detection code.)&n; */
DECL|function|copy_e820_map
r_static
r_int
id|__init
id|copy_e820_map
c_func
(paren
r_struct
id|e820entry
op_star
id|biosmap
comma
r_int
id|nr_map
)paren
(brace
multiline_comment|/* Only one memory region (or negative)? Ignore it */
r_if
c_cond
(paren
id|nr_map
OL
l_int|2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_do
(brace
r_int
r_int
id|start
op_assign
id|biosmap-&gt;addr
suffix:semicolon
r_int
r_int
id|size
op_assign
id|biosmap-&gt;size
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|size
suffix:semicolon
r_int
r_int
id|type
op_assign
id|biosmap-&gt;type
suffix:semicolon
multiline_comment|/* Overflow in 64 bits? Ignore the memory map. */
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Some BIOSes claim RAM in the 640k - 1M region.&n;&t;&t; * Not right. Fix it up.&n;&t;&t; * &n;&t;&t; * This should be removed on Hammer which is supposed to not&n;&t;&t; * have non e820 covered ISA mappings there, but I had some strange&n;&t;&t; * problems so it stays for now.  -AK&n;&t;&t; */
r_if
c_cond
(paren
id|type
op_eq
id|E820_RAM
)paren
(brace
r_if
c_cond
(paren
id|start
template_param
l_int|0xA0000ULL
)paren
(brace
r_if
c_cond
(paren
id|start
OL
l_int|0xA0000ULL
)paren
id|add_memory_region
c_func
(paren
id|start
comma
l_int|0xA0000ULL
op_minus
id|start
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
l_int|0x100000ULL
)paren
r_continue
suffix:semicolon
id|start
op_assign
l_int|0x100000ULL
suffix:semicolon
id|size
op_assign
id|end
op_minus
id|start
suffix:semicolon
)brace
)brace
id|add_memory_region
c_func
(paren
id|start
comma
id|size
comma
id|type
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|biosmap
op_increment
comma
op_decrement
id|nr_map
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_memory_region
r_void
id|__init
id|setup_memory_region
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|who
op_assign
l_string|&quot;BIOS-e820&quot;
suffix:semicolon
multiline_comment|/*&n;&t; * Try to copy the BIOS-supplied E820-map.&n;&t; *&n;&t; * Otherwise fake a memory map; one section from 0k-&gt;640k,&n;&t; * the next section from 1mb-&gt;appropriate_mem_k&n;&t; */
id|sanitize_e820_map
c_func
(paren
id|E820_MAP
comma
op_amp
id|E820_MAP_NR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_e820_map
c_func
(paren
id|E820_MAP
comma
id|E820_MAP_NR
)paren
OL
l_int|0
)paren
(brace
r_int
r_int
id|mem_size
suffix:semicolon
multiline_comment|/* compare results from other methods and take the greater */
r_if
c_cond
(paren
id|ALT_MEM_K
OL
id|EXT_MEM_K
)paren
(brace
id|mem_size
op_assign
id|EXT_MEM_K
suffix:semicolon
id|who
op_assign
l_string|&quot;BIOS-88&quot;
suffix:semicolon
)brace
r_else
(brace
id|mem_size
op_assign
id|ALT_MEM_K
suffix:semicolon
id|who
op_assign
l_string|&quot;BIOS-e801&quot;
suffix:semicolon
)brace
id|e820.nr_map
op_assign
l_int|0
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
id|LOWMEMSIZE
c_func
(paren
)paren
comma
id|E820_RAM
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
id|HIGH_MEMORY
comma
id|mem_size
op_lshift
l_int|10
comma
id|E820_RAM
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;BIOS-provided physical RAM map:&bslash;n&quot;
)paren
suffix:semicolon
id|e820_print_map
c_func
(paren
id|who
)paren
suffix:semicolon
)brace
DECL|function|parse_memopt
r_void
id|__init
id|parse_memopt
c_func
(paren
r_char
op_star
id|p
comma
r_char
op_star
op_star
id|from
)paren
(brace
multiline_comment|/*&n;&t; * mem=XXX[kKmM] limits kernel memory to XXX+1MB&n;&t; *&n;&t; * It would be more logical to count from 0 instead of from&n;&t; * HIGH_MEMORY, but we keep that for now for i386 compatibility. &n;&t; *&t;&n;&t; * No support for custom mapping like i386.  The reason is&n;&t; * that we need to read the e820 map anyways to handle the&n;&t; * ACPI mappings in the direct map.  Also on x86-64 there&n;&t; * should be always a good e820 map. This is only an upper&n;&t; * limit, you cannot force usage of memory not in e820.&n;&t; *&n;&t; * -AK&n;&t;&t;&t; */
id|end_user_pfn
op_assign
id|memparse
c_func
(paren
id|p
comma
id|from
)paren
op_plus
id|HIGH_MEMORY
suffix:semicolon
id|end_user_pfn
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
)brace
eof
