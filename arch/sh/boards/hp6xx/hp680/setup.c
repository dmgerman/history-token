multiline_comment|/*&n; * linux/arch/sh/boards/hp6xx/hp680/setup.c&n; *&n; * Copyright (C) 2002 Andriy Skulysh&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Setup code for an HP680  (internal peripherials only)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hd64461/hd64461.h&gt;
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
l_string|&quot;HP680&quot;
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
id|__set_io_port_base
c_func
(paren
id|CONFIG_HD64461_IOBASE
op_minus
id|HD64461_STBCR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
