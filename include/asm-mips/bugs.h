multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
macro_line|#ifndef _ASM_BUGS_H
DECL|macro|_ASM_BUGS_H
mdefine_line|#define _ASM_BUGS_H
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_void
id|check_bugs32
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|check_bugs64
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|check_bugs
r_static
r_inline
r_void
id|check_bugs
c_func
(paren
r_void
)paren
(brace
id|check_bugs32
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS64
id|check_bugs64
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* _ASM_BUGS_H */
eof
