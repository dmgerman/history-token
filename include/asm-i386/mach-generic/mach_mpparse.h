macro_line|#ifndef _MACH_MPPARSE_H
DECL|macro|_MACH_MPPARSE_H
mdefine_line|#define _MACH_MPPARSE_H 1
macro_line|#include &lt;asm/genapic.h&gt;
DECL|macro|mpc_oem_bus_info
mdefine_line|#define mpc_oem_bus_info (genapic-&gt;mpc_oem_bus_info)
DECL|macro|mpc_oem_pci_bus
mdefine_line|#define mpc_oem_pci_bus (genapic-&gt;mpc_oem_pci_bus)
r_int
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
suffix:semicolon
r_int
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
suffix:semicolon
macro_line|#endif
eof
