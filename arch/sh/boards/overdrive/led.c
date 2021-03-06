multiline_comment|/*&n; * linux/arch/sh/overdrive/led.c&n; *&n; * Copyright (C) 1999 Stuart Menefy &lt;stuart.menefy@st.com&gt;&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * This file contains an Overdrive specific LED feature.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/overdrive/overdrive.h&gt;
DECL|function|mach_led
r_static
r_void
id|mach_led
c_func
(paren
r_int
id|position
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|reg
op_assign
id|readl
c_func
(paren
id|OVERDRIVE_CTRL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|reg
op_or_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
id|reg
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
id|writel
c_func
(paren
id|reg
comma
id|OVERDRIVE_CTRL
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HEARTBEAT
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* acts like an actual heart beat -- ie thump-thump-pause... */
DECL|function|heartbeat_od
r_void
id|heartbeat_od
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|cnt
op_assign
l_int|0
comma
id|period
op_assign
l_int|0
comma
id|dist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
l_int|0
op_logical_or
id|cnt
op_eq
id|dist
)paren
id|mach_led
c_func
(paren
op_minus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cnt
op_eq
l_int|7
op_logical_or
id|cnt
op_eq
id|dist
op_plus
l_int|7
)paren
id|mach_led
c_func
(paren
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
OG
id|period
)paren
(brace
id|cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The hyperbolic function below modifies the heartbeat period&n;&t;&t; * length in dependency of the current (5min) load. It goes&n;&t;&t; * through the points f(0)=126, f(1)=86, f(5)=51,&n;&t;&t; * f(inf)-&gt;30. */
id|period
op_assign
(paren
(paren
l_int|672
op_lshift
id|FSHIFT
)paren
op_div
(paren
l_int|5
op_star
id|avenrun
(braket
l_int|0
)braket
op_plus
(paren
l_int|7
op_lshift
id|FSHIFT
)paren
)paren
)paren
op_plus
l_int|30
suffix:semicolon
id|dist
op_assign
id|period
op_div
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_HEARTBEAT */
eof
