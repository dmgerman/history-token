multiline_comment|/*&n; * Platform dependent support for HP simulator.&n; *&n; * Copyright (C) 1998, 1999, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &quot;hpsim_ssc.h&quot;
r_void
DECL|function|ia64_ssc_connect_irq
id|ia64_ssc_connect_irq
(paren
r_int
id|intr
comma
r_int
id|irq
)paren
(brace
id|ia64_ssc
c_func
(paren
id|intr
comma
id|irq
comma
l_int|0
comma
l_int|0
comma
id|SSC_CONNECT_INTERRUPT
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_ctl_trace
id|ia64_ctl_trace
(paren
r_int
id|on
)paren
(brace
id|ia64_ssc
c_func
(paren
id|on
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_CTL_TRACE
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|hpsim_setup
id|hpsim_setup
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
id|ROOT_DEV
op_assign
id|Root_SDA1
suffix:semicolon
multiline_comment|/* default to first SCSI drive */
macro_line|#ifdef CONFIG_HP_SIMSERIAL_CONSOLE
(brace
r_extern
r_struct
id|console
id|hpsim_cons
suffix:semicolon
r_if
c_cond
(paren
id|ia64_platform_is
c_func
(paren
l_string|&quot;hpsim&quot;
)paren
)paren
id|register_console
c_func
(paren
op_amp
id|hpsim_cons
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
