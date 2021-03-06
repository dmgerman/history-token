multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; * Copyright (C) Leigh Brown 2002.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|typedef|prom_handle
r_typedef
r_void
op_star
id|prom_handle
suffix:semicolon
DECL|typedef|ihandle
r_typedef
r_void
op_star
id|ihandle
suffix:semicolon
DECL|typedef|phandle
r_typedef
r_void
op_star
id|phandle
suffix:semicolon
DECL|typedef|prom_entry
r_typedef
r_int
(paren
op_star
id|prom_entry
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|macro|OF_INVALID_HANDLE
mdefine_line|#define OF_INVALID_HANDLE&t;((prom_handle)-1UL)
r_extern
id|prom_entry
id|of_prom_entry
suffix:semicolon
multiline_comment|/* function declarations */
r_void
op_star
id|claim
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
suffix:semicolon
r_int
id|map
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_int
id|virt
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_void
id|enter
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
m_exit
(paren
r_void
)paren
suffix:semicolon
id|phandle
id|finddevice
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|getprop
c_func
(paren
id|phandle
id|node
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_void
id|ofinit
c_func
(paren
id|prom_entry
id|entry
)paren
suffix:semicolon
r_int
id|ofstdio
c_func
(paren
id|ihandle
op_star
id|stdin
comma
id|ihandle
op_star
id|stdout
comma
id|ihandle
op_star
id|stderr
)paren
suffix:semicolon
r_int
id|read
c_func
(paren
id|ihandle
id|instance
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_void
id|release
c_func
(paren
r_void
op_star
id|virt
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|write
c_func
(paren
id|ihandle
id|instance
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
multiline_comment|/* inlines */
DECL|function|pause
r_extern
r_inline
r_void
id|pause
c_func
(paren
r_void
)paren
(brace
id|enter
c_func
(paren
)paren
suffix:semicolon
)brace
eof
