macro_line|#ifndef _ASM_RTC_H
DECL|macro|_ASM_RTC_H
mdefine_line|#define _ASM_RTC_H
macro_line|#include &lt;asm/machvec.h&gt;
DECL|macro|rtc_gettimeofday
mdefine_line|#define rtc_gettimeofday sh_mv.mv_rtc_gettimeofday
DECL|macro|rtc_settimeofday
mdefine_line|#define rtc_settimeofday sh_mv.mv_rtc_settimeofday
r_extern
r_void
id|sh_rtc_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_int
id|sh_rtc_settimeofday
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
macro_line|#endif /* _ASM_RTC_H */
eof
