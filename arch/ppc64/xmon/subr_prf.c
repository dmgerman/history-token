multiline_comment|/*&n; * Written by Cort Dougan to replace the version originally used&n; * by Paul Mackerras, which came from NetBSD and thus had copyright&n; * conflicts with Linux.&n; *&n; * This file makes liberal use of the standard linux utility&n; * routines to reduce the size of the binary.  We assume we can&n; * trust some parts of Linux inside the debugger.&n; *   -- Cort (cort@cs.nmt.edu)&n; *&n; * Copyright (C) 1999 Cort Dougan.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;nonstdio.h&quot;
r_extern
r_int
id|xmon_write
c_func
(paren
r_void
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
DECL|function|xmon_vfprintf
id|xmon_vfprintf
c_func
(paren
r_void
op_star
id|f
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|ap
)paren
(brace
r_static
r_char
id|xmon_buf
(braket
l_int|2048
)braket
suffix:semicolon
r_int
id|n
suffix:semicolon
id|n
op_assign
id|vsprintf
c_func
(paren
id|xmon_buf
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|xmon_write
c_func
(paren
id|f
comma
id|xmon_buf
comma
id|n
)paren
suffix:semicolon
)brace
r_void
DECL|function|xmon_printf
id|xmon_printf
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
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|xmon_vfprintf
c_func
(paren
id|stdout
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
r_void
DECL|function|xmon_fprintf
id|xmon_fprintf
c_func
(paren
r_void
op_star
id|f
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
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|xmon_vfprintf
c_func
(paren
id|f
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
eof