multiline_comment|/*&n; * include/asm-sh/freq.h&n; *&n; * Copyright (C) 2002, 2003 Paul Mundt&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASM_SH_FREQ_H
DECL|macro|__ASM_SH_FREQ_H
mdefine_line|#define __ASM_SH_FREQ_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/cpu/freq.h&gt;
multiline_comment|/* arch/sh/kernel/time.c */
r_extern
r_void
id|get_current_frequency_divisors
c_func
(paren
r_int
r_int
op_star
id|ifc
comma
r_int
r_int
op_star
id|pfc
comma
r_int
r_int
op_star
id|bfc
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_ifc_divisor
c_func
(paren
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_ifc_divisor
c_func
(paren
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_ifc_divisor
c_func
(paren
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_ifc_value
c_func
(paren
r_int
r_int
id|divisor
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_pfc_value
c_func
(paren
r_int
r_int
id|divisor
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_bfc_value
c_func
(paren
r_int
r_int
id|divisor
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_FREQ_H */
eof
