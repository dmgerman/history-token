macro_line|#ifndef _PARISC_MACHDEP_H
DECL|macro|_PARISC_MACHDEP_H
mdefine_line|#define _PARISC_MACHDEP_H
macro_line|#include &lt;linux/notifier.h&gt;
DECL|macro|MACH_RESTART
mdefine_line|#define&t;MACH_RESTART&t;1
DECL|macro|MACH_HALT
mdefine_line|#define&t;MACH_HALT&t;2
DECL|macro|MACH_POWER_ON
mdefine_line|#define MACH_POWER_ON&t;3
DECL|macro|MACH_POWER_OFF
mdefine_line|#define&t;MACH_POWER_OFF&t;4
r_extern
r_struct
id|notifier_block
op_star
id|mach_notifier
suffix:semicolon
r_extern
r_void
id|pa7300lc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|cpu_lpmc
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
