macro_line|#ifndef __ASM_X8664_BUG_H
DECL|macro|__ASM_X8664_BUG_H
mdefine_line|#define __ASM_X8664_BUG_H 1
macro_line|#include &lt;linux/stringify.h&gt;
multiline_comment|/*&n; * Tell the user there is some problem.  The exception handler decodes &n; * this frame.&n; */
DECL|struct|bug_frame
r_struct
id|bug_frame
(brace
DECL|member|ud2
r_int
r_char
id|ud2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* should use 32bit offset instead, but the assembler doesn&squot;t &n;&t;   like it */
DECL|member|filename
r_char
op_star
id|filename
suffix:semicolon
DECL|member|line
r_int
r_int
id|line
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG() &bslash;&n;&t;asm volatile(&quot;ud2 ; .quad %c1 ; .short %c0&quot; :: &bslash;&n;&t;&t;     &quot;i&quot;(__LINE__), &quot;i&quot; (__stringify(KBUILD_BASENAME)))
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) BUG()
r_void
id|out_of_line_bug
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
