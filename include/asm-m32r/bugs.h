macro_line|#ifndef _ASM_M32R_BUGS_H
DECL|macro|_ASM_M32R_BUGS_H
mdefine_line|#define _ASM_M32R_BUGS_H
multiline_comment|/* $Id$ */
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *     void check_bugs(void);&n; */
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
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
id|current_cpu_data.loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
)brace
macro_line|#endif  /* _ASM_M32R_BUGS_H */
eof
