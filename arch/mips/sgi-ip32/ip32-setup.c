multiline_comment|/*&n; * IP32 basic setup&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/ip32/crime.h&gt;
macro_line|#include &lt;asm/ip32/mace.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
r_extern
r_struct
id|rtc_ops
id|ip32_rtc_ops
suffix:semicolon
r_extern
id|u32
id|cc_interval
suffix:semicolon
macro_line|#ifdef CONFIG_SGI_O2MACE_ETH
multiline_comment|/*&n; * This is taken care of in here &squot;cause they say using Arc later on is&n; * problematic&n; */
r_extern
r_char
id|o2meth_eaddr
(braket
l_int|8
)braket
suffix:semicolon
DECL|function|str2hexnum
r_static
r_inline
r_int
r_char
id|str2hexnum
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
r_return
id|c
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;f&squot;
)paren
r_return
id|c
op_minus
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* foo */
)brace
DECL|function|str2eaddr
r_static
r_inline
r_void
id|str2eaddr
c_func
(paren
r_int
r_char
op_star
id|ea
comma
r_int
r_char
op_star
id|str
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|num
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|str
op_increment
suffix:semicolon
)brace
id|num
op_assign
id|str2hexnum
c_func
(paren
op_star
id|str
op_increment
)paren
op_lshift
l_int|4
suffix:semicolon
id|num
op_or_assign
(paren
id|str2hexnum
c_func
(paren
op_star
id|str
op_increment
)paren
)paren
suffix:semicolon
id|ea
(braket
id|i
)braket
op_assign
id|num
suffix:semicolon
)brace
)brace
macro_line|#endif
r_extern
r_void
id|ip32_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip32_reboot_setup
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|mips_io_port_base
op_assign
id|UNCACHEDADDR
c_func
(paren
id|MACEPCI_HI_IO
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_SGI_O2MACE_ETH
(brace
r_char
op_star
id|mac
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;eaddr&quot;
)paren
suffix:semicolon
id|str2eaddr
c_func
(paren
id|o2meth_eaddr
comma
id|mac
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
id|board_be_init
op_assign
id|ip32_be_init
suffix:semicolon
id|board_time_init
op_assign
id|ip32_time_init
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
