multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; * Copyright (C) Leigh Brown 2002.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;of1275.h&quot;
macro_line|#include &quot;nonstdio.h&quot;
r_extern
id|ihandle
id|of_prom_mmu
suffix:semicolon
r_int
DECL|function|map
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
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|nret
suffix:semicolon
r_char
op_star
id|method
suffix:semicolon
id|ihandle
id|mmu_ihandle
suffix:semicolon
r_int
id|misc
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|virt
suffix:semicolon
r_int
r_int
id|phys
suffix:semicolon
r_int
id|ret0
suffix:semicolon
)brace
id|args
suffix:semicolon
r_if
c_cond
(paren
id|of_prom_mmu
op_eq
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;map() called, no MMU found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|args.service
op_assign
l_string|&quot;call-method&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|6
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.method
op_assign
l_string|&quot;map&quot;
suffix:semicolon
id|args.mmu_ihandle
op_assign
id|of_prom_mmu
suffix:semicolon
id|args.misc
op_assign
l_int|0
suffix:semicolon
id|args.phys
op_assign
id|phys
suffix:semicolon
id|args.virt
op_assign
id|virt
suffix:semicolon
id|args.size
op_assign
id|size
suffix:semicolon
(paren
op_star
id|of_prom_entry
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|args.ret0
suffix:semicolon
)brace
eof
