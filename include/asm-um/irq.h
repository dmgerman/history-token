macro_line|#ifndef __UM_IRQ_H
DECL|macro|__UM_IRQ_H
mdefine_line|#define __UM_IRQ_H
multiline_comment|/* The i386 irq.h has a struct task_struct in a prototype without including&n; * sched.h.  This forward declaration kills the resulting warning.&n; */
r_struct
id|task_struct
suffix:semicolon
macro_line|#include &quot;asm/ptrace.h&quot;
DECL|macro|NR_IRQS
macro_line|#undef NR_IRQS
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;&t;0
DECL|macro|UMN_IRQ
mdefine_line|#define UMN_IRQ&t;&t;&t;1
DECL|macro|CONSOLE_IRQ
mdefine_line|#define CONSOLE_IRQ&t;&t;2
DECL|macro|CONSOLE_WRITE_IRQ
mdefine_line|#define CONSOLE_WRITE_IRQ&t;3
DECL|macro|UBD_IRQ
mdefine_line|#define UBD_IRQ&t;&t;&t;4
DECL|macro|UM_ETH_IRQ
mdefine_line|#define UM_ETH_IRQ&t;&t;5
DECL|macro|SSL_IRQ
mdefine_line|#define SSL_IRQ&t;&t;&t;6
DECL|macro|SSL_WRITE_IRQ
mdefine_line|#define SSL_WRITE_IRQ&t;&t;7
DECL|macro|ACCEPT_IRQ
mdefine_line|#define ACCEPT_IRQ&t;&t;8
DECL|macro|MCONSOLE_IRQ
mdefine_line|#define MCONSOLE_IRQ&t;&t;9
DECL|macro|WINCH_IRQ
mdefine_line|#define WINCH_IRQ&t;&t;10
DECL|macro|SIGIO_WRITE_IRQ
mdefine_line|#define SIGIO_WRITE_IRQ &t;11
DECL|macro|TELNETD_IRQ
mdefine_line|#define TELNETD_IRQ &t;&t;12
DECL|macro|LAST_IRQ
mdefine_line|#define LAST_IRQ TELNETD_IRQ
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (LAST_IRQ + 1)
r_extern
r_int
id|um_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
id|fd
comma
r_int
id|type
comma
r_void
(paren
op_star
id|handler
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
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
macro_line|#endif
eof
