macro_line|#ifndef SUN3X_TIME_H
DECL|macro|SUN3X_TIME_H
mdefine_line|#define SUN3X_TIME_H
r_extern
r_int
id|sun3x_hwclk
c_func
(paren
r_int
id|set
comma
r_struct
id|rtc_time
op_star
id|t
)paren
suffix:semicolon
r_int
r_int
id|sun3x_gettimeoffset
(paren
r_void
)paren
suffix:semicolon
r_void
id|sun3x_sched_init
c_func
(paren
r_void
(paren
op_star
id|vector
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
DECL|struct|mostek_dt
r_struct
id|mostek_dt
(brace
DECL|member|csr
r_volatile
r_int
r_char
id|csr
suffix:semicolon
DECL|member|sec
r_volatile
r_int
r_char
id|sec
suffix:semicolon
DECL|member|min
r_volatile
r_int
r_char
id|min
suffix:semicolon
DECL|member|hour
r_volatile
r_int
r_char
id|hour
suffix:semicolon
DECL|member|wday
r_volatile
r_int
r_char
id|wday
suffix:semicolon
DECL|member|mday
r_volatile
r_int
r_char
id|mday
suffix:semicolon
DECL|member|month
r_volatile
r_int
r_char
id|month
suffix:semicolon
DECL|member|year
r_volatile
r_int
r_char
id|year
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
