multiline_comment|/*&n; * IP32 basic setup&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/ip32/crime.h&gt;
macro_line|#include &lt;asm/ip32/mace.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
r_extern
r_struct
id|rtc_ops
id|ip32_rtc_ops
suffix:semicolon
r_extern
id|u32
id|cc_interval
suffix:semicolon
DECL|function|ip32_init
r_void
id|__init
id|ip32_init
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
id|arc_meminit
(paren
)paren
suffix:semicolon
)brace
DECL|function|ip32_setup
r_void
id|__init
id|ip32_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SERIAL_CONSOLE
r_char
op_star
id|ctype
suffix:semicolon
macro_line|#endif
id|TLBMISS_HANDLER_SETUP
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_CONSOLE
id|ctype
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;console&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ctype
op_eq
l_char|&squot;d&squot;
)paren
(brace
r_if
c_cond
(paren
id|ctype
(braket
l_int|1
)braket
op_eq
l_char|&squot;2&squot;
)paren
id|console_setup
(paren
l_string|&quot;ttyS1&quot;
)paren
suffix:semicolon
r_else
id|console_setup
(paren
l_string|&quot;ttyS0&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_VT
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|rtc_ops
op_assign
op_amp
id|ip32_rtc_ops
suffix:semicolon
id|crime_init
(paren
)paren
suffix:semicolon
)brace
DECL|function|page_is_ram
r_int
id|__init
id|page_is_ram
(paren
r_int
r_int
id|pagenr
)paren
(brace
multiline_comment|/* XXX: to do? */
r_return
l_int|1
suffix:semicolon
)brace
eof
