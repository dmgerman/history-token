multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; * Copyright (C) Leigh Brown 2002.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;of1275.h&quot;
r_void
DECL|function|exit
m_exit
(paren
r_void
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
)brace
id|args
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|args.service
op_assign
l_string|&quot;exit&quot;
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
)brace
)brace
eof
