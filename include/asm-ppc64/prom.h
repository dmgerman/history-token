macro_line|#ifndef _PPC64_PROM_H
DECL|macro|_PPC64_PROM_H
mdefine_line|#define _PPC64_PROM_H
multiline_comment|/*&n; * Definitions for talking to the Open Firmware PROM on&n; * Power Macintosh computers.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; * Updates for PPC64 by Peter Bergner &amp; David Engebretsen, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|PTRRELOC
mdefine_line|#define PTRRELOC(x)     ((typeof(x))((unsigned long)(x) - offset))
DECL|macro|PTRUNRELOC
mdefine_line|#define PTRUNRELOC(x)   ((typeof(x))((unsigned long)(x) + offset))
DECL|macro|RELOC
mdefine_line|#define RELOC(x)        (*PTRRELOC(&amp;(x)))
multiline_comment|/* Definitions used by the flattened device tree */
DECL|macro|OF_DT_HEADER
mdefine_line|#define OF_DT_HEADER&t;&t;0xd00dfeed&t;/* 4: version, 4: total size */
DECL|macro|OF_DT_BEGIN_NODE
mdefine_line|#define OF_DT_BEGIN_NODE&t;0x1&t;&t;/* Start node: full name */
DECL|macro|OF_DT_END_NODE
mdefine_line|#define OF_DT_END_NODE&t;&t;0x2&t;&t;/* End node */
DECL|macro|OF_DT_PROP
mdefine_line|#define OF_DT_PROP&t;&t;0x3&t;&t;/* Property: name off, size, content */
DECL|macro|OF_DT_END
mdefine_line|#define OF_DT_END&t;&t;0x9
DECL|macro|OF_DT_VERSION
mdefine_line|#define OF_DT_VERSION&t;&t;1
multiline_comment|/*&n; * This is what gets passed to the kernel by prom_init or kexec&n; *&n; * The dt struct contains the device tree structure, full pathes and&n; * property contents. The dt strings contain a separate block with just&n; * the strings for the property names, and is fully page aligned and&n; * self contained in a page, so that it can be kept around by the kernel,&n; * each property name appears only once in this page (cheap compression)&n; *&n; * the mem_rsvmap contains a map of reserved ranges of physical memory,&n; * passing it here instead of in the device-tree itself greatly simplifies&n; * the job of everybody. It&squot;s just a list of u64 pairs (base/size) that&n; * ends when size is 0&n; */
DECL|struct|boot_param_header
r_struct
id|boot_param_header
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* magic word OF_DT_HEADER */
DECL|member|totalsize
id|u32
id|totalsize
suffix:semicolon
multiline_comment|/* total size of DT block */
DECL|member|off_dt_struct
id|u32
id|off_dt_struct
suffix:semicolon
multiline_comment|/* offset to structure */
DECL|member|off_dt_strings
id|u32
id|off_dt_strings
suffix:semicolon
multiline_comment|/* offset to strings */
DECL|member|off_mem_rsvmap
id|u32
id|off_mem_rsvmap
suffix:semicolon
multiline_comment|/* offset to memory reserve map */
DECL|member|version
id|u32
id|version
suffix:semicolon
multiline_comment|/* format version */
DECL|member|last_comp_version
id|u32
id|last_comp_version
suffix:semicolon
multiline_comment|/* last compatible version */
multiline_comment|/* version 2 fields below */
DECL|member|boot_cpuid_phys
id|u32
id|boot_cpuid_phys
suffix:semicolon
multiline_comment|/* Which physical CPU id we&squot;re booting on */
)brace
suffix:semicolon
DECL|typedef|phandle
r_typedef
id|u32
id|phandle
suffix:semicolon
DECL|typedef|ihandle
r_typedef
id|u32
id|ihandle
suffix:semicolon
DECL|struct|address_range
r_struct
id|address_range
(brace
DECL|member|space
r_int
r_int
id|space
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|interrupt_info
r_struct
id|interrupt_info
(brace
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|sense
r_int
id|sense
suffix:semicolon
multiline_comment|/* +ve/-ve logic, edge or level, etc. */
)brace
suffix:semicolon
DECL|struct|pci_address
r_struct
id|pci_address
(brace
DECL|member|a_hi
id|u32
id|a_hi
suffix:semicolon
DECL|member|a_mid
id|u32
id|a_mid
suffix:semicolon
DECL|member|a_lo
id|u32
id|a_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|isa_address
r_struct
id|isa_address
(brace
DECL|member|a_hi
id|u32
id|a_hi
suffix:semicolon
DECL|member|a_lo
id|u32
id|a_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|isa_range
r_struct
id|isa_range
(brace
DECL|member|isa_addr
r_struct
id|isa_address
id|isa_addr
suffix:semicolon
DECL|member|pci_addr
r_struct
id|pci_address
id|pci_addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|reg_property
r_struct
id|reg_property
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|reg_property32
r_struct
id|reg_property32
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|reg_property64
r_struct
id|reg_property64
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|property
r_struct
id|property
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|value
r_int
r_char
op_star
id|value
suffix:semicolon
DECL|member|next
r_struct
id|property
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* NOTE: the device_node contains PCI specific info for pci devices.&n; * This perhaps could be hung off the device_node with another struct,&n; * but for now it is directly in the node.  The phb ptr is a good&n; * indication of a real PCI node.  Other nodes leave these fields zeroed.&n; */
r_struct
id|pci_controller
suffix:semicolon
r_struct
id|iommu_table
suffix:semicolon
DECL|struct|device_node
r_struct
id|device_node
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
DECL|member|node
id|phandle
id|node
suffix:semicolon
DECL|member|linux_phandle
id|phandle
id|linux_phandle
suffix:semicolon
DECL|member|n_addrs
r_int
id|n_addrs
suffix:semicolon
DECL|member|addrs
r_struct
id|address_range
op_star
id|addrs
suffix:semicolon
DECL|member|n_intrs
r_int
id|n_intrs
suffix:semicolon
DECL|member|intrs
r_struct
id|interrupt_info
op_star
id|intrs
suffix:semicolon
DECL|member|full_name
r_char
op_star
id|full_name
suffix:semicolon
multiline_comment|/* PCI stuff probably doesn&squot;t belong here */
DECL|member|busno
r_int
id|busno
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|bussubno
r_int
id|bussubno
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|devfn
r_int
id|devfn
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|eeh_mode
r_int
id|eeh_mode
suffix:semicolon
multiline_comment|/* See eeh.h for possible EEH_MODEs */
DECL|member|eeh_config_addr
r_int
id|eeh_config_addr
suffix:semicolon
DECL|member|pci_ext_config_space
r_int
id|pci_ext_config_space
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|phb
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|iommu_table
r_struct
id|iommu_table
op_star
id|iommu_table
suffix:semicolon
multiline_comment|/* for phb&squot;s or bridges */
DECL|member|properties
r_struct
id|property
op_star
id|properties
suffix:semicolon
DECL|member|parent
r_struct
id|device_node
op_star
id|parent
suffix:semicolon
DECL|member|child
r_struct
id|device_node
op_star
id|child
suffix:semicolon
DECL|member|sibling
r_struct
id|device_node
op_star
id|sibling
suffix:semicolon
DECL|member|next
r_struct
id|device_node
op_star
id|next
suffix:semicolon
multiline_comment|/* next device of same type */
DECL|member|allnext
r_struct
id|device_node
op_star
id|allnext
suffix:semicolon
multiline_comment|/* next in list of all nodes */
DECL|member|pde
r_struct
id|proc_dir_entry
op_star
id|pde
suffix:semicolon
multiline_comment|/* this node&squot;s proc directory */
DECL|member|name_link
r_struct
id|proc_dir_entry
op_star
id|name_link
suffix:semicolon
multiline_comment|/* name symlink */
DECL|member|addr_link
r_struct
id|proc_dir_entry
op_star
id|addr_link
suffix:semicolon
multiline_comment|/* addr symlink */
DECL|member|kref
r_struct
id|kref
id|kref
suffix:semicolon
DECL|member|_flags
r_int
r_int
id|_flags
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_chosen
suffix:semicolon
multiline_comment|/* flag descriptions */
DECL|macro|OF_DYNAMIC
mdefine_line|#define OF_DYNAMIC 1 /* node and properties were allocated via kmalloc */
DECL|macro|OF_IS_DYNAMIC
mdefine_line|#define OF_IS_DYNAMIC(x) test_bit(OF_DYNAMIC, &amp;x-&gt;_flags)
DECL|macro|OF_MARK_DYNAMIC
mdefine_line|#define OF_MARK_DYNAMIC(x) set_bit(OF_DYNAMIC, &amp;x-&gt;_flags)
multiline_comment|/*&n; * Until 32-bit ppc can add proc_dir_entries to its device_node&n; * definition, we cannot refer to pde, name_link, and addr_link&n; * in arch-independent code.&n; */
DECL|macro|HAVE_ARCH_DEVTREE_FIXUPS
mdefine_line|#define HAVE_ARCH_DEVTREE_FIXUPS
DECL|function|set_node_proc_entry
r_static
r_inline
r_void
id|set_node_proc_entry
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
id|dn-&gt;pde
op_assign
id|de
suffix:semicolon
)brace
DECL|function|set_node_name_link
r_static
r_void
r_inline
id|set_node_name_link
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
id|dn-&gt;name_link
op_assign
id|de
suffix:semicolon
)brace
DECL|function|set_node_addr_link
r_static
r_void
r_inline
id|set_node_addr_link
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
id|dn-&gt;addr_link
op_assign
id|de
suffix:semicolon
)brace
multiline_comment|/* OBSOLETE: Old stlye node lookup */
r_extern
r_struct
id|device_node
op_star
id|find_devices
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|find_type_devices
c_func
(paren
r_const
r_char
op_star
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|find_path_device
c_func
(paren
r_const
r_char
op_star
id|path
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|find_compatible_devices
c_func
(paren
r_const
r_char
op_star
id|type
comma
r_const
r_char
op_star
id|compat
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|find_all_nodes
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* New style node lookup */
r_extern
r_struct
id|device_node
op_star
id|of_find_node_by_name
c_func
(paren
r_struct
id|device_node
op_star
id|from
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_find_node_by_type
c_func
(paren
r_struct
id|device_node
op_star
id|from
comma
r_const
r_char
op_star
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_find_compatible_node
c_func
(paren
r_struct
id|device_node
op_star
id|from
comma
r_const
r_char
op_star
id|type
comma
r_const
r_char
op_star
id|compat
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_find_node_by_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_find_node_by_phandle
c_func
(paren
id|phandle
id|handle
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_find_all_nodes
c_func
(paren
r_struct
id|device_node
op_star
id|prev
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_get_parent
c_func
(paren
r_const
r_struct
id|device_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_get_next_child
c_func
(paren
r_const
r_struct
id|device_node
op_star
id|node
comma
r_struct
id|device_node
op_star
id|prev
)paren
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|of_node_get
c_func
(paren
r_struct
id|device_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_void
id|of_node_put
c_func
(paren
r_struct
id|device_node
op_star
id|node
)paren
suffix:semicolon
multiline_comment|/* For updating the device tree at runtime */
r_extern
r_void
id|of_attach_node
c_func
(paren
r_struct
id|device_node
op_star
)paren
suffix:semicolon
r_extern
r_void
id|of_detach_node
c_func
(paren
r_const
r_struct
id|device_node
op_star
)paren
suffix:semicolon
multiline_comment|/* Other Prototypes */
r_extern
r_int
r_int
id|prom_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|finish_device_tree
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|device_is_compatible
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|machine_is_compatible
c_func
(paren
r_const
r_char
op_star
id|compat
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|get_property
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|lenp
)paren
suffix:semicolon
r_extern
r_void
id|print_properties
c_func
(paren
r_struct
id|device_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_int
id|prom_n_addr_cells
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
suffix:semicolon
r_extern
r_int
id|prom_n_size_cells
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
suffix:semicolon
r_extern
r_int
id|prom_n_intr_cells
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
suffix:semicolon
r_extern
r_void
id|prom_get_irq_senses
c_func
(paren
r_int
r_char
op_star
id|senses
comma
r_int
id|off
comma
r_int
id|max
)paren
suffix:semicolon
r_extern
r_void
id|prom_add_property
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
r_struct
id|property
op_star
id|prop
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_PROM_H */
eof
