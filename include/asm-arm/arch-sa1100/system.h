multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/system.h&n; *&n; * Copyright (c) 1999 Nicolas Pitre &lt;nico@cam.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|function|arch_idle
r_static
r_inline
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|current-&gt;need_resched
op_logical_and
op_logical_neg
id|hlt_counter
)paren
id|cpu_do_idle
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SA1100_VICTOR
multiline_comment|/* power off unconditionally */
DECL|macro|arch_reset
mdefine_line|#define arch_reset(x) machine_power_off()
macro_line|#else
DECL|function|arch_reset
r_extern
r_inline
r_void
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
multiline_comment|/* Jump into ROM at address 0 */
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Activate SA1100 watchdog and wait for the trigger... */
id|OSMR3
op_assign
id|OSCR
op_plus
l_int|3686400
op_div
l_int|2
suffix:semicolon
multiline_comment|/* in 1/2 sec */
id|OWER
op_or_assign
id|OWER_WME
suffix:semicolon
id|OIER
op_or_assign
id|OIER_E3
suffix:semicolon
)brace
)brace
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()&t;do { } while (0)
macro_line|#endif
eof
