macro_line|#ifndef _PPC64_PROM_H
DECL|macro|_PPC64_PROM_H
mdefine_line|#define _PPC64_PROM_H
multiline_comment|/*&n; * Definitions for talking to the Open Firmware PROM on&n; * Power Macintosh computers.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; * Updates for PPC64 by Peter Bergner &amp; David Engebretsen, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|PTRRELOC
mdefine_line|#define PTRRELOC(x)     ((typeof(x))((unsigned long)(x) - offset))
DECL|macro|PTRUNRELOC
mdefine_line|#define PTRUNRELOC(x)   ((typeof(x))((unsigned long)(x) + offset))
DECL|macro|RELOC
mdefine_line|#define RELOC(x)        (*PTRRELOC(&amp;(x)))
DECL|macro|LONG_LSW
mdefine_line|#define LONG_LSW(X) (((unsigned long)X) &amp; 0xffffffff)
DECL|macro|LONG_MSW
mdefine_line|#define LONG_MSW(X) (((unsigned long)X) &gt;&gt; 32)
DECL|typedef|phandle
r_typedef
id|u32
id|phandle
suffix:semicolon
DECL|typedef|ihandle
r_typedef
r_void
op_star
id|ihandle
suffix:semicolon
DECL|typedef|phandle32
r_typedef
id|u32
id|phandle32
suffix:semicolon
DECL|typedef|ihandle32
r_typedef
id|u32
id|ihandle32
suffix:semicolon
r_extern
r_char
op_star
id|prom_display_paths
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|prom_num_displays
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
DECL|struct|pci_range32
r_struct
id|pci_range32
(brace
DECL|member|child_addr
r_struct
id|pci_address
id|child_addr
suffix:semicolon
DECL|member|parent_addr
r_int
r_int
id|parent_addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_range64
r_struct
id|pci_range64
(brace
DECL|member|child_addr
r_struct
id|pci_address
id|child_addr
suffix:semicolon
DECL|member|parent_addr
r_int
r_int
id|parent_addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|union|pci_range
r_union
id|pci_range
(brace
r_struct
(brace
DECL|member|addr
r_struct
id|pci_address
id|addr
suffix:semicolon
DECL|member|phys
id|u32
id|phys
suffix:semicolon
DECL|member|size_hi
id|u32
id|size_hi
suffix:semicolon
DECL|member|pci32
)brace
id|pci32
suffix:semicolon
r_struct
(brace
DECL|member|addr
r_struct
id|pci_address
id|addr
suffix:semicolon
DECL|member|phys_hi
id|u32
id|phys_hi
suffix:semicolon
DECL|member|phys_lo
id|u32
id|phys_lo
suffix:semicolon
DECL|member|size_hi
id|u32
id|size_hi
suffix:semicolon
DECL|member|size_lo
id|u32
id|size_lo
suffix:semicolon
DECL|member|pci64
)brace
id|pci64
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_of_tce_table
r_struct
id|_of_tce_table
(brace
DECL|member|node
id|phandle
id|node
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
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
DECL|struct|translation_property
r_struct
id|translation_property
(brace
DECL|member|virt
r_int
r_int
id|virt
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
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
id|TceTable
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
DECL|member|busno
r_int
id|busno
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|devfn
r_int
id|devfn
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|phb
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
multiline_comment|/* for pci devices */
DECL|member|tce_table
r_struct
id|TceTable
op_star
id|tce_table
suffix:semicolon
multiline_comment|/* for phb&squot;s or bridges */
DECL|macro|DN_STATUS_BIST_FAILED
mdefine_line|#define DN_STATUS_BIST_FAILED (1&lt;&lt;0)
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
)brace
suffix:semicolon
DECL|typedef|prom_arg_t
r_typedef
id|u32
id|prom_arg_t
suffix:semicolon
DECL|struct|prom_args
r_struct
id|prom_args
(brace
DECL|member|service
id|u32
id|service
suffix:semicolon
DECL|member|nargs
id|u32
id|nargs
suffix:semicolon
DECL|member|nret
id|u32
id|nret
suffix:semicolon
DECL|member|args
id|prom_arg_t
id|args
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|rets
id|prom_arg_t
op_star
id|rets
suffix:semicolon
multiline_comment|/* Pointer to return values in args[16]. */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|printf
id|u32
id|printf
suffix:semicolon
multiline_comment|/* void (*printf)(char *, ...); */
DECL|member|memdump
id|u32
id|memdump
suffix:semicolon
multiline_comment|/* void (*memdump)(unsigned char *, unsigned long); */
DECL|member|dummy
id|u32
id|dummy
suffix:semicolon
multiline_comment|/* void (*dummy)(void); */
DECL|typedef|yaboot_debug_t
)brace
id|yaboot_debug_t
suffix:semicolon
DECL|struct|prom_t
r_struct
id|prom_t
(brace
DECL|member|entry
r_int
r_int
id|entry
suffix:semicolon
DECL|member|chosen
id|ihandle
id|chosen
suffix:semicolon
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
DECL|member|stdout
id|ihandle
id|stdout
suffix:semicolon
DECL|member|disp_node
id|ihandle
id|disp_node
suffix:semicolon
DECL|member|args
r_struct
id|prom_args
id|args
suffix:semicolon
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|encode_phys_size
r_int
r_int
id|encode_phys_size
suffix:semicolon
DECL|member|bi_recs
r_struct
id|bi_record
op_star
id|bi_recs
suffix:semicolon
macro_line|#ifdef DEBUG_YABOOT
DECL|member|yaboot
id|yaboot_debug_t
op_star
id|yaboot
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_extern
r_struct
id|prom_t
id|prom
suffix:semicolon
multiline_comment|/* Prototypes */
r_extern
r_void
m_abort
(paren
r_void
)paren
suffix:semicolon
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
comma
id|yaboot_debug_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|prom_print
c_func
(paren
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
r_extern
r_void
id|relocate_nodes
c_func
(paren
r_void
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
id|find_pci_device_OFnode
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
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
macro_line|#endif /* _PPC64_PROM_H */
eof
