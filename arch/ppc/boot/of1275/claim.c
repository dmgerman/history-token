multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; * Copyright (C) Leigh Brown 2002.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;of1275.h&quot;
r_void
op_star
DECL|function|claim
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
r_int
r_int
id|virt
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|align
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;claim&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|3
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.virt
op_assign
id|virt
suffix:semicolon
id|args.size
op_assign
id|size
suffix:semicolon
id|args.align
op_assign
id|align
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
id|args.ret
suffix:semicolon
)brace
eof
