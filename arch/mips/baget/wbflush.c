multiline_comment|/*&n; * Setup the right wbflush routine for Baget/MIPS.&n; *&n; * Copyright (C) 1999 Gleb Raiko &amp; Vladimir Roganov&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|variable|__wbflush
r_void
(paren
op_star
id|__wbflush
)paren
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|wbflush_baget
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|wbflush_setup
r_void
id|__init
id|wbflush_setup
c_func
(paren
r_void
)paren
(brace
id|__wbflush
op_assign
id|wbflush_baget
suffix:semicolon
)brace
multiline_comment|/*&n; * Baget/MIPS doesnt need to write back the WB.&n; */
DECL|function|wbflush_baget
r_static
r_void
id|wbflush_baget
c_func
(paren
r_void
)paren
(brace
)brace
eof
