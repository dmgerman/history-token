multiline_comment|/* -*- linux-c -*-&n; *&n; *&t;$Id: sysrq.h,v 1.3 1997/07/17 11:54:33 mj Exp $&n; *&n; *&t;Linux Magic System Request Key Hacks&n; *&n; *&t;(c) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; *&n; *&t;(c) 2000 Crutcher Dunnavant &lt;crutcher+kernel@datastacks.com&gt;&n; *&t;overhauled to use key registration&n; *&t;based upon discusions in irc://irc.openprojects.net/#kernelnewbies&n; */
macro_line|#include &lt;linux/config.h&gt;
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|tty_struct
suffix:semicolon
multiline_comment|/* Possible values of bitmask for enabling sysrq functions */
multiline_comment|/* 0x0001 is reserved for enable everything */
DECL|macro|SYSRQ_ENABLE_LOG
mdefine_line|#define SYSRQ_ENABLE_LOG&t;0x0002
DECL|macro|SYSRQ_ENABLE_KEYBOARD
mdefine_line|#define SYSRQ_ENABLE_KEYBOARD&t;0x0004
DECL|macro|SYSRQ_ENABLE_DUMP
mdefine_line|#define SYSRQ_ENABLE_DUMP&t;0x0008
DECL|macro|SYSRQ_ENABLE_SYNC
mdefine_line|#define SYSRQ_ENABLE_SYNC&t;0x0010
DECL|macro|SYSRQ_ENABLE_REMOUNT
mdefine_line|#define SYSRQ_ENABLE_REMOUNT&t;0x0020
DECL|macro|SYSRQ_ENABLE_SIGNAL
mdefine_line|#define SYSRQ_ENABLE_SIGNAL&t;0x0040
DECL|macro|SYSRQ_ENABLE_BOOT
mdefine_line|#define SYSRQ_ENABLE_BOOT&t;0x0080
DECL|macro|SYSRQ_ENABLE_RTNICE
mdefine_line|#define SYSRQ_ENABLE_RTNICE&t;0x0100
DECL|struct|sysrq_key_op
r_struct
id|sysrq_key_op
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
DECL|member|help_msg
r_char
op_star
id|help_msg
suffix:semicolon
DECL|member|action_msg
r_char
op_star
id|action_msg
suffix:semicolon
DECL|member|enable_mask
r_int
id|enable_mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
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
id|tty_struct
op_star
)paren
suffix:semicolon
r_void
id|__handle_sysrq
c_func
(paren
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|tty_struct
op_star
comma
r_int
id|check_mask
)paren
suffix:semicolon
r_int
id|register_sysrq_key
c_func
(paren
r_int
comma
r_struct
id|sysrq_key_op
op_star
)paren
suffix:semicolon
r_int
id|unregister_sysrq_key
c_func
(paren
r_int
comma
r_struct
id|sysrq_key_op
op_star
)paren
suffix:semicolon
r_struct
id|sysrq_key_op
op_star
id|__sysrq_get_key_op
c_func
(paren
r_int
id|key
)paren
suffix:semicolon
macro_line|#else
DECL|function|__reterr
r_static
r_inline
r_int
id|__reterr
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|macro|register_sysrq_key
mdefine_line|#define register_sysrq_key(ig,nore) __reterr()
DECL|macro|unregister_sysrq_key
mdefine_line|#define unregister_sysrq_key(ig,nore) __reterr()
macro_line|#endif
eof
