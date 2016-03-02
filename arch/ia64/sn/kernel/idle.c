multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2003 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/leds.h&gt;
macro_line|#include &lt;asm/sn/simulator.h&gt;
DECL|function|snidle
r_void
id|snidle
c_func
(paren
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
r_if
c_cond
(paren
id|pda-&gt;idle_flag
op_eq
l_int|0
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * Turn the activity LED off.&n;&t;&t;&t; */
id|set_led_bits
c_func
(paren
l_int|0
comma
id|LED_CPU_ACTIVITY
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IA64_SGI_SN_SIM
r_if
c_cond
(paren
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
id|SIMULATOR_SLEEP
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|pda-&gt;idle_flag
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* &n;&t;&t; * Turn the activity LED on.&n;&t;&t; */
id|set_led_bits
c_func
(paren
id|LED_CPU_ACTIVITY
comma
id|LED_CPU_ACTIVITY
)paren
suffix:semicolon
id|pda-&gt;idle_flag
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
