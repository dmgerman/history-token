macro_line|#ifndef __UM_IRQ_H
DECL|macro|__UM_IRQ_H
mdefine_line|#define __UM_IRQ_H
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
DECL|macro|XTERM_IRQ
mdefine_line|#define XTERM_IRQ &t;&t;13
DECL|macro|LAST_IRQ
mdefine_line|#define LAST_IRQ XTERM_IRQ
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (LAST_IRQ + 1)
macro_line|#endif
eof
