multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/pxa27x.c&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Nov 05, 2002&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * Code specific to PXA27x aka Bulverde.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/* Crystal clock: 13MHz */
DECL|macro|BASE_CLK
mdefine_line|#define BASE_CLK&t;13000000
multiline_comment|/*&n; * Get the clock frequency as reflected by CCSR and the turbo flag.&n; * We assume these values have been applied via a fcs.&n; * If info is not 0 we also display the current settings.&n; */
DECL|function|get_clk_frequency_khz
r_int
r_int
id|get_clk_frequency_khz
c_func
(paren
r_int
id|info
)paren
(brace
r_int
r_int
id|ccsr
comma
id|clkcfg
suffix:semicolon
r_int
r_int
id|l
comma
id|L
comma
id|m
comma
id|M
comma
id|n2
comma
id|N
comma
id|S
suffix:semicolon
r_int
id|cccr_a
comma
id|t
comma
id|ht
comma
id|b
suffix:semicolon
id|ccsr
op_assign
id|CCSR
suffix:semicolon
id|cccr_a
op_assign
id|CCCR
op_amp
(paren
l_int|1
op_lshift
l_int|25
)paren
suffix:semicolon
multiline_comment|/* Read clkcfg register: it has turbo, b, half-turbo (and f) */
id|asm
c_func
(paren
l_string|&quot;mrc&bslash;tp14, 0, %0, c6, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|clkcfg
)paren
)paren
suffix:semicolon
id|t
op_assign
id|clkcfg
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
suffix:semicolon
id|ht
op_assign
id|clkcfg
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
id|b
op_assign
id|clkcfg
op_amp
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
id|l
op_assign
id|ccsr
op_amp
l_int|0x1f
suffix:semicolon
id|n2
op_assign
(paren
id|ccsr
op_rshift
l_int|7
)paren
op_amp
l_int|0xf
suffix:semicolon
id|m
op_assign
(paren
id|l
op_le
l_int|10
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|l
op_le
l_int|20
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
suffix:semicolon
id|L
op_assign
id|l
op_star
id|BASE_CLK
suffix:semicolon
id|N
op_assign
(paren
id|L
op_star
id|n2
)paren
op_div
l_int|2
suffix:semicolon
id|M
op_assign
(paren
op_logical_neg
id|cccr_a
)paren
ques
c_cond
(paren
id|L
op_div
id|m
)paren
suffix:colon
(paren
(paren
id|b
)paren
ques
c_cond
id|L
suffix:colon
(paren
id|L
op_div
l_int|2
)paren
)paren
suffix:semicolon
id|S
op_assign
(paren
id|b
)paren
ques
c_cond
id|L
suffix:colon
(paren
id|L
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Run Mode clock: %d.%02dMHz (*%d)&bslash;n&quot;
comma
id|L
op_div
l_int|1000000
comma
(paren
id|L
op_mod
l_int|1000000
)paren
op_div
l_int|10000
comma
id|l
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Turbo Mode clock: %d.%02dMHz (*%d.%d, %sactive)&bslash;n&quot;
comma
id|N
op_div
l_int|1000000
comma
(paren
id|N
op_mod
l_int|1000000
)paren
op_div
l_int|10000
comma
id|n2
op_div
l_int|2
comma
(paren
id|n2
op_mod
l_int|2
)paren
op_star
l_int|5
comma
(paren
id|t
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;in&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory clock: %d.%02dMHz (/%d)&bslash;n&quot;
comma
id|M
op_div
l_int|1000000
comma
(paren
id|M
op_mod
l_int|1000000
)paren
op_div
l_int|10000
comma
id|m
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;System bus clock: %d.%02dMHz &bslash;n&quot;
comma
id|S
op_div
l_int|1000000
comma
(paren
id|S
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
)brace
r_return
(paren
id|t
)paren
ques
c_cond
(paren
id|N
op_div
l_int|1000
)paren
suffix:colon
(paren
id|L
op_div
l_int|1000
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the current mem clock frequency in units of 10kHz as&n; * reflected by CCCR[A], B, and L&n; */
DECL|function|get_memclk_frequency_10khz
r_int
r_int
id|get_memclk_frequency_10khz
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ccsr
comma
id|clkcfg
suffix:semicolon
r_int
r_int
id|l
comma
id|L
comma
id|m
comma
id|M
suffix:semicolon
r_int
id|cccr_a
comma
id|b
suffix:semicolon
id|ccsr
op_assign
id|CCSR
suffix:semicolon
id|cccr_a
op_assign
id|CCCR
op_amp
(paren
l_int|1
op_lshift
l_int|25
)paren
suffix:semicolon
multiline_comment|/* Read clkcfg register: it has turbo, b, half-turbo (and f) */
id|asm
c_func
(paren
l_string|&quot;mrc&bslash;tp14, 0, %0, c6, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|clkcfg
)paren
)paren
suffix:semicolon
id|b
op_assign
id|clkcfg
op_amp
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
id|l
op_assign
id|ccsr
op_amp
l_int|0x1f
suffix:semicolon
id|m
op_assign
(paren
id|l
op_le
l_int|10
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|l
op_le
l_int|20
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
suffix:semicolon
id|L
op_assign
id|l
op_star
id|BASE_CLK
suffix:semicolon
id|M
op_assign
(paren
op_logical_neg
id|cccr_a
)paren
ques
c_cond
(paren
id|L
op_div
id|m
)paren
suffix:colon
(paren
(paren
id|b
)paren
ques
c_cond
id|L
suffix:colon
(paren
id|L
op_div
l_int|2
)paren
)paren
suffix:semicolon
r_return
(paren
id|M
op_div
l_int|10000
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the current LCD clock frequency in units of 10kHz as&n; */
DECL|function|get_lcdclk_frequency_10khz
r_int
r_int
id|get_lcdclk_frequency_10khz
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ccsr
suffix:semicolon
r_int
r_int
id|l
comma
id|L
comma
id|k
comma
id|K
suffix:semicolon
id|ccsr
op_assign
id|CCSR
suffix:semicolon
id|l
op_assign
id|ccsr
op_amp
l_int|0x1f
suffix:semicolon
id|k
op_assign
(paren
id|l
op_le
l_int|7
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|l
op_le
l_int|16
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
suffix:semicolon
id|L
op_assign
id|l
op_star
id|BASE_CLK
suffix:semicolon
id|K
op_assign
id|L
op_div
id|k
suffix:semicolon
r_return
(paren
id|K
op_div
l_int|10000
)paren
suffix:semicolon
)brace
DECL|variable|get_clk_frequency_khz
id|EXPORT_SYMBOL
c_func
(paren
id|get_clk_frequency_khz
)paren
suffix:semicolon
DECL|variable|get_memclk_frequency_10khz
id|EXPORT_SYMBOL
c_func
(paren
id|get_memclk_frequency_10khz
)paren
suffix:semicolon
DECL|variable|get_lcdclk_frequency_10khz
id|EXPORT_SYMBOL
c_func
(paren
id|get_lcdclk_frequency_10khz
)paren
suffix:semicolon
eof
