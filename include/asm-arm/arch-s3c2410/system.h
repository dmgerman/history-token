multiline_comment|/* linux/include/asm-arm/arch-s3c2410/system.h&n; *&n; * (c) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - System function defines and includes&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  12-May-2003 BJD  Created file&n; *  14-May-2003 BJD  Removed idle to aid debugging&n; *  12-Jun-2003 BJD  Added reset via watchdog&n; *  04-Sep-2003 BJD  Moved to v2.6&n; */
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/map.h&gt;
macro_line|#include &lt;asm/arch/regs-watchdog.h&gt;
macro_line|#include &lt;asm/arch/regs-clock.h&gt;
r_extern
r_void
id|printascii
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_void
DECL|function|arch_idle
id|arch_idle
c_func
(paren
r_void
)paren
(brace
singleline_comment|//unsigned long reg = S3C2410_CLKCON;
singleline_comment|//printascii(&quot;arch_idle:&bslash;n&quot;);
multiline_comment|/* idle the system by using the idle mode which will wait for an&n;&t; * interrupt to happen before restarting the system.&n;&t; */
multiline_comment|/* going into idle state upsets the jtag, so don&squot;t do it&n;&t; * at the moment */
macro_line|#if 0
id|__raw_writel
c_func
(paren
id|__raw_readl
c_func
(paren
id|reg
)paren
op_or
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* the samsung port seems to do a loop and then unset idle.. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|50
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|__raw_readl
c_func
(paren
id|reg
)paren
suffix:semicolon
multiline_comment|/* ensure loop not optimised out */
)brace
singleline_comment|//printascii(&quot;arch_idle: done&bslash;n&quot;);
id|__raw_writel
c_func
(paren
id|__raw_readl
c_func
(paren
id|reg
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
id|reg
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
DECL|function|arch_reset
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
l_char|&squot;s&squot;
)paren
(brace
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;arch_reset: attempting watchdog reset&bslash;n&quot;
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0
comma
id|S3C2410_WTCON
)paren
suffix:semicolon
multiline_comment|/* disable watchdog, to be safe  */
multiline_comment|/* put initial values into count and data */
id|__raw_writel
c_func
(paren
l_int|0x100
comma
id|S3C2410_WTCNT
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0x100
comma
id|S3C2410_WTDAT
)paren
suffix:semicolon
multiline_comment|/* set the watchdog to go and reset... */
id|__raw_writel
c_func
(paren
id|S3C2410_WTCON_ENABLE
op_or
id|S3C2410_WTCON_DIV16
op_or
id|S3C2410_WTCON_RSTEN
op_or
id|S3C2410_WTCON_PRESCALE
c_func
(paren
l_int|0x80
)paren
comma
id|S3C2410_WTCON
)paren
suffix:semicolon
multiline_comment|/* wait for reset to assert... */
id|mdelay
c_func
(paren
l_int|5000
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Watchdog reset failed to assert reset&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* we&squot;ll take a jump through zero as a poor second */
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
