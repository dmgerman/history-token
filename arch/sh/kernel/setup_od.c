multiline_comment|/* $Id: setup_od.c,v 1.1 2000/06/14 09:35:59 stuart_menefy Exp $&n; *&n; * arch/sh/kernel/setup_od.c&n; *&n; * Copyright (C) 2000  Stuart Menefy&n; *&n; * STMicroelectronics Overdrive Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|setup_od
r_int
id|__init
id|setup_od
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Enable RS232 receive buffers */
r_volatile
r_int
op_star
id|p
op_assign
(paren
r_volatile
r_int
op_star
)paren
l_int|0xa3000000
suffix:semicolon
macro_line|#if defined(CONFIG_SH_ORION)
op_star
id|p
op_assign
l_int|1
suffix:semicolon
macro_line|#elif defined(CONFIG_SH_OVERDRIVE)
op_star
id|p
op_assign
l_int|0x1e
suffix:semicolon
macro_line|#else
macro_line|#error Illegal configuration
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;STMicroelectronics Overdrive Setup...done&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_od
id|module_init
c_func
(paren
id|setup_od
)paren
suffix:semicolon
eof
