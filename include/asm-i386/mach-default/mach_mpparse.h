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
id|Dprintk
c_func
(paren
l_string|&quot;Bus #%d is %s&bslash;n&quot;
comma
id|m-&gt;mpc_busid
comma
id|name
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
)brace
DECL|function|mps_oem_check
r_static
r_inline
r_void
id|mps_oem_check
c_func
(paren
r_struct
id|mp_config_table
op_star
id|mpc
comma
r_char
op_star
id|oem
comma
r_char
op_star
id|productid
)paren
(brace
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
