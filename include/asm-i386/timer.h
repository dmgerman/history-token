macro_line|#ifndef _ASMi386_TIMER_H
DECL|macro|_ASMi386_TIMER_H
mdefine_line|#define _ASMi386_TIMER_H
DECL|struct|timer_opts
r_struct
id|timer_opts
(brace
multiline_comment|/* probes and initializes timer. returns 1 on sucess, 0 on failure */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* called by the timer interrupt */
DECL|member|mark_offset
r_void
(paren
op_star
id|mark_offset
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* called by gettimeofday. returns # ms since the last timer interrupt */
DECL|member|get_offset
r_int
r_int
(paren
op_star
id|get_offset
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE (tick_nsec / 1000)
r_struct
id|timer_opts
op_star
id|select_timer
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
