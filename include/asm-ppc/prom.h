multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Definitions for talking to the Open Firmware PROM on&n; * Power Macintosh computers.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_PROM_H
DECL|macro|_PPC_PROM_H
mdefine_line|#define _PPC_PROM_H
macro_line|#include &lt;linux/config.h&gt;
DECL|typedef|phandle
r_typedef
r_void
op_star
id|phandle
suffix:semicolon
DECL|typedef|ihandle
r_typedef
r_void
op_star
id|ihandle
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
multiline_comment|/*&n; * Note: don&squot;t change this structure for now or you&squot;ll break BootX !&n; */
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
r_struct
id|prom_args
suffix:semicolon
DECL|typedef|prom_entry
r_typedef
r_void
(paren
op_star
id|prom_entry
)paren
(paren
r_struct
id|prom_args
op_star
)paren
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
comma
r_int
comma
id|prom_entry
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
r_extern
r_void
id|prom_get_irq_senses
c_func
(paren
r_int
r_char
op_star
comma
r_int
comma
r_int
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
r_struct
id|resource
op_star
id|request_OF_resource
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|index
comma
r_const
r_char
op_star
id|name_postfix
)paren
suffix:semicolon
r_extern
r_int
id|release_OF_resource
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|index
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
id|call_rtas
c_func
(paren
r_const
r_char
op_star
id|service
comma
r_int
id|nargs
comma
r_int
id|nret
comma
r_int
r_int
op_star
id|outputs
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/*&n; * When we call back to the Open Firmware client interface, we usually&n; * have to do that before the kernel is relocated to its final location&n; * (this is because we can&squot;t use OF after we have overwritten the&n; * exception vectors with our exception handlers).  These macros assist&n; * in performing the address calculations that we need to do to access&n; * data when the kernel is running at an address that is different from&n; * the address that the kernel is linked at.  The reloc_offset() function&n; * returns the difference between these two addresses and the macros&n; * simplify the process of adding or subtracting this offset to/from&n; * pointer values.  See arch/ppc/kernel/prom.c for how these are used.&n; */
r_extern
r_int
r_int
id|reloc_offset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|add_reloc_offset
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sub_reloc_offset
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|PTRRELOC
mdefine_line|#define PTRRELOC(x)&t;((typeof(x))add_reloc_offset((unsigned long)(x)))
DECL|macro|PTRUNRELOC
mdefine_line|#define PTRUNRELOC(x)&t;((typeof(x))sub_reloc_offset((unsigned long)(x)))
macro_line|#endif /* _PPC_PROM_H */
macro_line|#endif /* __KERNEL__ */
eof
