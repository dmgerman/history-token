multiline_comment|/*&n; * arch/ppc/platforms/rpx8260.c&n; *&n; * RPC EP8260 platform support&n; *&n; * Author: Dan Malek &lt;dan@embeddededge.com&gt;&n; * Derived from: pq2ads_setup.c by Kumar&n; *&n; * Copyright 2004 Embedded Edge, LLC&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|variable|callback_setup_arch
r_static
r_void
(paren
op_star
id|callback_setup_arch
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|m8260_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|ep8260_setup_arch
id|ep8260_setup_arch
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC EP8260 Port&bslash;n&quot;
)paren
suffix:semicolon
id|callback_setup_arch
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
multiline_comment|/* Generic 8260 platform initialization */
id|m8260_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
multiline_comment|/* Anything special for this platform */
id|callback_setup_arch
op_assign
id|ppc_md.setup_arch
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|ep8260_setup_arch
suffix:semicolon
)brace
eof
