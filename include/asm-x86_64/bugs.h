multiline_comment|/*&n; *  include/asm-x86_64/bugs.h&n; *&n; *  Copyright (C) 1994  Linus Torvalds&n; *  Copyright (C) 2000  SuSE&n; *&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
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
id|identify_cpu
c_func
(paren
op_amp
id|boot_cpu_data
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_SMP)
id|printk
c_func
(paren
l_string|&quot;CPU: &quot;
)paren
suffix:semicolon
id|print_cpu_info
c_func
(paren
op_amp
id|boot_cpu_data
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
