multiline_comment|/* eCos HAL interface header */
macro_line|#ifndef SH_BIOS_H
DECL|macro|SH_BIOS_H
mdefine_line|#define SH_BIOS_H
DECL|macro|HAL_IF_VECTOR_TABLE
mdefine_line|#define HAL_IF_VECTOR_TABLE 0xfffe20
DECL|macro|CALL_IF_SET_CONSOLE_COMM
mdefine_line|#define CALL_IF_SET_CONSOLE_COMM  13
DECL|macro|QUERY_CURRENT
mdefine_line|#define QUERY_CURRENT -1
DECL|macro|MANGLER
mdefine_line|#define MANGLER       -3
multiline_comment|/* Checking for GDB stub active */
multiline_comment|/* suggestion Jonathan Larmour */
DECL|function|sh_bios_in_gdb_mode
r_static
r_int
id|sh_bios_in_gdb_mode
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|gdb_active
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|gdb_active
op_eq
op_minus
l_int|1
)paren
(brace
r_int
(paren
op_star
id|set_console_comm
)paren
(paren
r_int
)paren
suffix:semicolon
id|set_console_comm
op_assign
(paren
(paren
r_void
op_star
op_star
)paren
id|HAL_IF_VECTOR_TABLE
)paren
(braket
id|CALL_IF_SET_CONSOLE_COMM
)braket
suffix:semicolon
id|gdb_active
op_assign
(paren
id|set_console_comm
c_func
(paren
id|QUERY_CURRENT
)paren
op_eq
id|MANGLER
)paren
suffix:semicolon
)brace
r_return
id|gdb_active
suffix:semicolon
)brace
DECL|function|sh_bios_gdb_detach
r_static
r_void
id|sh_bios_gdb_detach
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
