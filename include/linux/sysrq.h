multiline_comment|/* -*- linux-c -*-&n; *&n; *&t;$Id: sysrq.h,v 1.3 1997/07/17 11:54:33 mj Exp $&n; *&n; *&t;Linux Magic System Request Key Hacks&n; *&n; *&t;(c) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|kbd_struct
suffix:semicolon
r_struct
id|tty_struct
suffix:semicolon
multiline_comment|/* Generic SysRq interface -- you may call it from any device driver, supplying&n; * ASCII code of the key, pointer to registers and kbd/tty structs (if they&n; * are available -- else NULL&squot;s).&n; */
r_void
id|handle_sysrq
c_func
(paren
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|kbd_struct
op_star
comma
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Deferred actions */
r_extern
r_int
id|emergency_sync_scheduled
suffix:semicolon
DECL|macro|EMERG_SYNC
mdefine_line|#define EMERG_SYNC 1
DECL|macro|EMERG_REMOUNT
mdefine_line|#define EMERG_REMOUNT 2
r_void
id|do_emergency_sync
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|macro|CHECK_EMERGENCY_SYNC
mdefine_line|#define CHECK_EMERGENCY_SYNC&t;&t;&t;&bslash;&n;&t;if (emergency_sync_scheduled)&t;&t;&bslash;&n;&t;&t;do_emergency_sync();
macro_line|#else
DECL|macro|CHECK_EMERGENCY_SYNC
mdefine_line|#define CHECK_EMERGENCY_SYNC
macro_line|#endif
eof
