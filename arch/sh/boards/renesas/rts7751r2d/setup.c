multiline_comment|/*&n; * linux/arch/sh/kernel/setup_rts7751r2d.c&n; *&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * Renesas Technology Sales RTS7751R2D Support.&n; *&n; * Modified for RTS7751R2D by&n; * Atom Create Engineering Co., Ltd. 2002.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rts7751r2d/rts7751r2d.h&gt;
DECL|variable|debug_counter
r_int
r_int
id|debug_counter
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;RTS7751R2D&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|platform_setup
r_void
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Renesas Technology Sales RTS7751R2D support.&bslash;n&quot;
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0x0000
comma
id|PA_OUTPORT
)paren
suffix:semicolon
id|debug_counter
op_assign
l_int|0
suffix:semicolon
)brace
eof
