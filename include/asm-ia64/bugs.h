multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; *&n; * Based on &lt;asm-alpha/bugs.h&gt;.&n; *&n; * Modified 1998, 1999, 2003&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;,  Hewlett-Packard Co.&n; */
macro_line|#ifndef _ASM_IA64_BUGS_H
DECL|macro|_ASM_IA64_BUGS_H
mdefine_line|#define _ASM_IA64_BUGS_H
macro_line|#include &lt;asm/processor.h&gt;
r_extern
r_void
id|check_bugs
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_BUGS_H */
eof
