macro_line|#ifndef _ASM_IA64_SN_IDLE_H
DECL|macro|_ASM_IA64_SN_IDLE_H
mdefine_line|#define _ASM_IA64_SN_IDLE_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/leds.h&gt;
macro_line|#include &lt;asm/sn/simulator.h&gt;
r_static
id|__inline__
r_void
DECL|function|snidle
id|snidle
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
macro_line|#ifdef CONFIG_IA64_SGI_AUTOTEST
(brace
r_extern
r_int
id|autotest_enabled
suffix:semicolon
r_if
c_cond
(paren
id|autotest_enabled
)paren
(brace
r_extern
r_void
id|llsc_main
c_func
(paren
r_int
)paren
suffix:semicolon
id|llsc_main
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|pda.idle_flag
op_eq
l_int|0
)paren
(brace
multiline_comment|/* &n;&t;&t; * Turn the activity LED off.&n;&t;&t; */
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
id|pda.idle_flag
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_static
id|__inline__
r_void
DECL|function|snidleoff
id|snidleoff
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
multiline_comment|/* &n;&t; * Turn the activity LED on.&n;&t; */
id|set_led_bits
c_func
(paren
id|LED_CPU_ACTIVITY
comma
id|LED_CPU_ACTIVITY
)paren
suffix:semicolon
id|pda.idle_flag
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* _ASM_IA64_SN_IDLE_H */
eof
