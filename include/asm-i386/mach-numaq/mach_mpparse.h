macro_line|#ifndef __ASM_MACH_MPPARSE_H
DECL|macro|__ASM_MACH_MPPARSE_H
mdefine_line|#define __ASM_MACH_MPPARSE_H
DECL|function|mpc_oem_bus_info
r_static
r_inline
r_void
id|mpc_oem_bus_info
c_func
(paren
r_struct
id|mpc_config_bus
op_star
id|m
comma
r_char
op_star
id|name
comma
r_struct
id|mpc_config_translation
op_star
id|translation
)paren
(brace
r_int
id|quad
op_assign
id|translation-&gt;trans_quad
suffix:semicolon
r_int
id|local
op_assign
id|translation-&gt;trans_local
suffix:semicolon
id|mp_bus_id_to_node
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|quad
suffix:semicolon
id|mp_bus_id_to_local
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|local
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bus #%d is %s (node %d)&bslash;n&quot;
comma
id|m-&gt;mpc_busid
comma
id|name
comma
id|quad
)paren
suffix:semicolon
)brace
DECL|function|mpc_oem_pci_bus
r_static
r_inline
r_void
id|mpc_oem_pci_bus
c_func
(paren
r_struct
id|mpc_config_bus
op_star
id|m
comma
r_struct
id|mpc_config_translation
op_star
id|translation
)paren
(brace
r_int
id|quad
op_assign
id|translation-&gt;trans_quad
suffix:semicolon
r_int
id|local
op_assign
id|translation-&gt;trans_local
suffix:semicolon
id|quad_local_to_mp_bus_id
(braket
id|quad
)braket
(braket
id|local
)braket
op_assign
id|m-&gt;mpc_busid
suffix:semicolon
)brace
multiline_comment|/* Hook from generic ACPI tables.c */
DECL|function|acpi_madt_oem_check
r_static
r_inline
r_void
id|acpi_madt_oem_check
c_func
(paren
r_char
op_star
id|oem_id
comma
r_char
op_star
id|oem_table_id
)paren
(brace
)brace
macro_line|#endif /* __ASM_MACH_MPPARSE_H */
eof
