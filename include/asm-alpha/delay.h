macro_line|#ifndef __ALPHA_DELAY_H
DECL|macro|__ALPHA_DELAY_H
mdefine_line|#define __ALPHA_DELAY_H
r_extern
r_void
id|__delay
c_func
(paren
r_int
id|loops
)paren
suffix:semicolon
r_extern
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|ndelay
c_func
(paren
r_int
r_int
id|nsecs
)paren
suffix:semicolon
DECL|macro|ndelay
mdefine_line|#define ndelay ndelay
macro_line|#endif /* defined(__ALPHA_DELAY_H) */
eof
