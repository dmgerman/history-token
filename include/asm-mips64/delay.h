multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf Electronics&n; * Copyright (C) 1995 - 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_DELAY_H
DECL|macro|_ASM_DELAY_H
mdefine_line|#define _ASM_DELAY_H
macro_line|#include &lt;linux/config.h&gt;
r_extern
id|__inline__
r_void
DECL|function|__delay
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;1:&bslash;tbnez&bslash;t%0,1b&bslash;n&bslash;t&quot;
l_string|&quot;dsubu&bslash;t%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Division by multiplication: you don&squot;t have to worry about&n; * loss of precision.&n; *&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
DECL|function|__udelay
r_extern
id|__inline__
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
comma
r_int
r_int
id|lps
)paren
(brace
r_int
r_int
id|lo
suffix:semicolon
id|usecs
op_mul_assign
l_int|0x000010c6f7a0b5edUL
suffix:semicolon
multiline_comment|/* 2**64 / 1000000 */
id|__asm__
c_func
(paren
l_string|&quot;dmultu&bslash;t%2,%3&quot;
suffix:colon
l_string|&quot;=h&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;=l&quot;
(paren
id|lo
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;r&quot;
(paren
id|lps
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|usecs
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val cpu_data[smp_processor_id()].udelay_val
macro_line|#else
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val loops_per_sec
macro_line|#endif
DECL|macro|udelay
mdefine_line|#define udelay(usecs) __udelay((usecs),__udelay_val)
macro_line|#endif /* _ASM_DELAY_H */
eof
