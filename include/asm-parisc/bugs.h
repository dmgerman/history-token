multiline_comment|/*&n; *  include/asm-parisc/bugs.h&n; *&n; *  Copyright (C) 1999&t;Mike Shaver&n; */
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
macro_line|#include &lt;asm/processor.h&gt;
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
singleline_comment|//&t;identify_cpu(&amp;boot_cpu_data);
)brace
eof
