multiline_comment|/* &n; * arch/sh/boards/saturn/setup.c&n; *&n; * Hardware support for the Sega Saturn.&n; *&n; * Copyright (c) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
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
l_string|&quot;Sega Saturn&quot;
suffix:semicolon
)brace
DECL|function|platform_setup
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
