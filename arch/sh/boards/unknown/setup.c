multiline_comment|/*&n; * linux/arch/sh/boards/unknown/setup.c&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Setup code for an unknown machine (internal peripherials only)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;Unknown&quot;
suffix:semicolon
)brace
DECL|function|platform_setup
r_void
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
)brace
eof
