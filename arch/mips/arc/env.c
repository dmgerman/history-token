multiline_comment|/*&n; * env.c: ARCS environment variable routines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * $Id: env.c,v 1.2 1999/10/09 00:00:57 ralf Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
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
id|romvec
op_member_access_from_pointer
id|get_evar
c_func
(paren
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
id|romvec
op_member_access_from_pointer
id|set_evar
c_func
(paren
id|name
comma
id|value
)paren
suffix:semicolon
)brace
eof
