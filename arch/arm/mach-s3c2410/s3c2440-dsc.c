multiline_comment|/* linux/arch/arm/mach-s3c2410/s3c2440-dsc.c&n; *&n; * Copyright (c) 2004-2005 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Samsung S3C2440 Drive Strength Control support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     29-Aug-2004 BJD  Start of drive-strength control&n; *     09-Nov-2004 BJD  Added symbol export&n; *     11-Jan-2005 BJD  Include fix&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
macro_line|#include &lt;asm/arch/regs-dsc.h&gt;
macro_line|#include &quot;cpu.h&quot;
macro_line|#include &quot;s3c2440.h&quot;
DECL|function|s3c2440_set_dsc
r_int
id|s3c2440_set_dsc
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|value
)paren
(brace
r_int
r_int
id|base
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
id|base
op_assign
(paren
id|pin
op_amp
id|S3C2440_SELECT_DSC1
)paren
ques
c_cond
id|S3C2440_DSC1
suffix:colon
id|S3C2440_DSC0
suffix:semicolon
id|mask
op_assign
l_int|3
op_lshift
id|S3C2440_DSC_GETSHIFT
c_func
(paren
id|pin
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|__raw_readl
c_func
(paren
id|base
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|mask
suffix:semicolon
id|val
op_or_assign
id|value
op_amp
id|mask
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|base
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|s3c2440_set_dsc
id|EXPORT_SYMBOL
c_func
(paren
id|s3c2440_set_dsc
)paren
suffix:semicolon
eof
