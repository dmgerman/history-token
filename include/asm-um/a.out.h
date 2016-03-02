macro_line|#ifndef __UM_A_OUT_H
DECL|macro|__UM_A_OUT_H
mdefine_line|#define __UM_A_OUT_H
macro_line|#include &quot;asm/arch/a.out.h&quot;
DECL|macro|STACK_TOP
macro_line|#undef STACK_TOP
r_extern
r_int
r_int
id|stacksizelim
suffix:semicolon
r_extern
r_int
r_int
id|host_task_size
suffix:semicolon
r_extern
r_int
id|honeypot
suffix:semicolon
DECL|macro|STACK_ROOM
mdefine_line|#define STACK_ROOM (stacksizelim)
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP (honeypot ? host_task_size : task_size)
macro_line|#endif
eof
