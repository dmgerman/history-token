multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Extracting time information from ARCS prom.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/arc/types.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
r_struct
id|linux_tinfo
op_star
id|__init
DECL|function|ArcGetTime
id|ArcGetTime
c_func
(paren
id|VOID
)paren
(brace
r_return
(paren
r_struct
id|linux_tinfo
op_star
)paren
id|ARC_CALL0
c_func
(paren
id|get_tinfo
)paren
suffix:semicolon
)brace
id|ULONG
id|__init
DECL|function|ArcGetRelativeTime
id|ArcGetRelativeTime
c_func
(paren
id|VOID
)paren
(brace
r_return
id|ARC_CALL0
c_func
(paren
id|get_rtime
)paren
suffix:semicolon
)brace
eof
