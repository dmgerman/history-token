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
id|cpu_do_idle
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SA1100_VICTOR
multiline_comment|/* power off unconditionally */
DECL|macro|arch_reset
mdefine_line|#define arch_reset(x) machine_power_off()
macro_line|#else
DECL|function|arch_reset
r_static
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
multiline_comment|/* Use on-chip reset capability */
id|RSRR
op_assign
id|RSRR_SWR
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
