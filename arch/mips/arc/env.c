multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * env.c: ARCS environment variable routines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/arc/types.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
id|PCHAR
id|__init
DECL|function|ArcGetEnvironmentVariable
id|ArcGetEnvironmentVariable
c_func
(paren
id|CHAR
op_star
id|name
)paren
(brace
r_return
(paren
id|CHAR
op_star
)paren
id|ARC_CALL1
c_func
(paren
id|get_evar
comma
id|name
)paren
suffix:semicolon
)brace
id|LONG
id|__init
DECL|function|ArcSetEnvironmentVariable
id|ArcSetEnvironmentVariable
c_func
(paren
id|PCHAR
id|name
comma
id|PCHAR
id|value
)paren
(brace
r_return
id|ARC_CALL2
c_func
(paren
id|set_evar
comma
id|name
comma
id|value
)paren
suffix:semicolon
)brace
eof
