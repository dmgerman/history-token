macro_line|#ifndef __UDBG_HDR
DECL|macro|__UDBG_HDR
mdefine_line|#define __UDBG_HDR
multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_void
id|udbg_init_uart
c_func
(paren
r_void
op_star
id|comport
)paren
suffix:semicolon
r_void
id|udbg_putc
c_func
(paren
r_int
r_char
id|c
)paren
suffix:semicolon
r_int
r_char
id|udbg_getc
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|udbg_getc_poll
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|udbg_puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_int
id|udbg_write
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
suffix:semicolon
r_int
id|udbg_read
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_struct
id|console
suffix:semicolon
r_void
id|udbg_console_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|n
)paren
suffix:semicolon
r_void
id|udbg_printf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|udbg_ppcdbg
c_func
(paren
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
r_int
id|udbg_ifdebug
c_func
(paren
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif
eof
