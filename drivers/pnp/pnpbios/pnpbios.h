multiline_comment|/*&n; * pnpbios.h - contains definitions for functions used only locally.&n; */
r_extern
r_int
id|pnpbios_parse_data_stream
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_bios_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_int
id|pnpbios_read_resources_from_node
c_func
(paren
r_struct
id|pnp_resource_table
op_star
id|res
comma
r_struct
id|pnp_bios_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_int
id|pnpbios_write_resources_to_node
c_func
(paren
r_struct
id|pnp_resource_table
op_star
id|res
comma
r_struct
id|pnp_bios_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_void
id|pnpid32_to_pnpid
c_func
(paren
id|u32
id|id
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|pnpbios_print_status
c_func
(paren
r_const
r_char
op_star
id|module
comma
id|u16
id|status
)paren
suffix:semicolon
r_extern
r_int
id|pnpbios_probe_installation
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|pnpbios_interface_attach_device
c_func
(paren
r_struct
id|pnp_bios_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_int
id|pnpbios_proc_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pnpbios_proc_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|pnpbios_interface_attach_device
r_static
r_inline
r_int
id|pnpbios_interface_attach_device
c_func
(paren
r_struct
id|pnp_bios_node
op_star
id|node
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpbios_proc_init
r_static
r_inline
r_int
id|pnpbios_proc_init
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpbios_proc_exit
r_static
r_inline
r_void
id|pnpbios_proc_exit
(paren
r_void
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC */
eof
