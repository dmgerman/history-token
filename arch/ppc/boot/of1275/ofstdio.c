multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; * Copyright (C) Leigh Brown 2002.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;of1275.h&quot;
r_int
DECL|function|ofstdio
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
(brace
id|ihandle
id|in
comma
id|out
suffix:semicolon
id|phandle
id|chosen
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
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen
comma
l_string|&quot;stdout&quot;
comma
op_amp
id|out
comma
r_sizeof
(paren
id|out
)paren
)paren
op_ne
l_int|4
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|in
comma
r_sizeof
(paren
id|in
)paren
)paren
op_ne
l_int|4
)paren
r_goto
id|err
suffix:semicolon
op_star
id|stdin
op_assign
id|in
suffix:semicolon
op_star
id|stdout
op_assign
id|out
suffix:semicolon
op_star
id|stderr
op_assign
id|out
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof
