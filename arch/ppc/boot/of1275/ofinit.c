multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; * Copyright (C) Leigh Brown 2002.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;of1275.h&quot;
DECL|variable|of_prom_entry
id|prom_entry
id|of_prom_entry
suffix:semicolon
DECL|variable|of_prom_mmu
id|ihandle
id|of_prom_mmu
suffix:semicolon
r_void
DECL|function|ofinit
id|ofinit
c_func
(paren
id|prom_entry
id|prom_ptr
)paren
(brace
id|phandle
id|chosen
suffix:semicolon
id|of_prom_entry
op_assign
id|prom_ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chosen
op_assign
id|finddevice
c_func
(paren
l_string|&quot;/chosen&quot;
)paren
)paren
op_eq
id|OF_INVALID_HANDLE
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen
comma
l_string|&quot;mmu&quot;
comma
op_amp
id|of_prom_mmu
comma
r_sizeof
(paren
id|ihandle
)paren
)paren
op_ne
l_int|4
)paren
r_return
suffix:semicolon
)brace
eof
