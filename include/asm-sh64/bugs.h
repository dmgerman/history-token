macro_line|#ifndef __ASM_SH64_BUGS_H
DECL|macro|__ASM_SH64_BUGS_H
mdefine_line|#define __ASM_SH64_BUGS_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/bugs.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; *&n; */
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
multiline_comment|/*&n; * I don&squot;t know of any Super-H bugs yet.&n; */
macro_line|#include &lt;asm/processor.h&gt;
DECL|function|check_bugs
r_static
r_void
id|__init
id|check_bugs
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
op_star
id|get_cpu_subtype
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
id|cpu_data-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU: %s&bslash;n&quot;
comma
id|get_cpu_subtype
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SH64_BUGS_H */
eof
