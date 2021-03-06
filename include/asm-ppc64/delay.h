macro_line|#ifndef _PPC64_DELAY_H
DECL|macro|_PPC64_DELAY_H
mdefine_line|#define _PPC64_DELAY_H
multiline_comment|/*&n; * Copyright 1996, Paul Mackerras.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * PPC64 Support added by Dave Engebretsen, Todd Inglett, Mike Corrigan,&n; * Anton Blanchard.&n; */
r_extern
r_int
r_int
id|tb_ticks_per_usec
suffix:semicolon
multiline_comment|/* define these here to prevent circular dependencies */
DECL|macro|__HMT_low
mdefine_line|#define __HMT_low()&t;asm volatile(&quot;or 1,1,1&quot;)
DECL|macro|__HMT_medium
mdefine_line|#define __HMT_medium()&t;asm volatile(&quot;or 2,2,2&quot;)
DECL|macro|__barrier
mdefine_line|#define __barrier()&t;asm volatile(&quot;&quot;:::&quot;memory&quot;)
DECL|function|__get_tb
r_static
r_inline
r_int
r_int
id|__get_tb
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|rval
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mftb %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|rval
)paren
)paren
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
DECL|function|__delay
r_static
r_inline
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
r_int
r_int
id|start
op_assign
id|__get_tb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|__get_tb
c_func
(paren
)paren
op_minus
id|start
)paren
OL
id|loops
)paren
(brace
id|__HMT_low
c_func
(paren
)paren
suffix:semicolon
)brace
id|__HMT_medium
c_func
(paren
)paren
suffix:semicolon
id|__barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|udelay
r_static
r_inline
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
r_int
r_int
id|loops
op_assign
id|tb_ticks_per_usec
op_star
id|usecs
suffix:semicolon
id|__delay
c_func
(paren
id|loops
)paren
suffix:semicolon
)brace
macro_line|#endif /* _PPC64_DELAY_H */
eof
