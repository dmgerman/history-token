multiline_comment|/*&n; *  linux/arch/arm/kernel/arthur.c&n; *&n; *  Copyright (C) 1998, 1999, 2000, 2001 Philip Blundell&n; *&n; * Arthur personality&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/* Arthur doesn&squot;t have many signals, and a lot of those that it does&n;   have don&squot;t map easily to any Linux equivalent.  Never mind.  */
DECL|macro|ARTHUR_SIGABRT
mdefine_line|#define ARTHUR_SIGABRT&t;&t;1
DECL|macro|ARTHUR_SIGFPE
mdefine_line|#define ARTHUR_SIGFPE&t;&t;2
DECL|macro|ARTHUR_SIGILL
mdefine_line|#define ARTHUR_SIGILL&t;&t;3
DECL|macro|ARTHUR_SIGINT
mdefine_line|#define ARTHUR_SIGINT&t;&t;4
DECL|macro|ARTHUR_SIGSEGV
mdefine_line|#define ARTHUR_SIGSEGV&t;&t;5
DECL|macro|ARTHUR_SIGTERM
mdefine_line|#define ARTHUR_SIGTERM&t;&t;6
DECL|macro|ARTHUR_SIGSTAK
mdefine_line|#define ARTHUR_SIGSTAK&t;&t;7
DECL|macro|ARTHUR_SIGUSR1
mdefine_line|#define ARTHUR_SIGUSR1&t;&t;8
DECL|macro|ARTHUR_SIGUSR2
mdefine_line|#define ARTHUR_SIGUSR2&t;&t;9
DECL|macro|ARTHUR_SIGOSERROR
mdefine_line|#define ARTHUR_SIGOSERROR&t;10
DECL|variable|arthur_to_linux_signals
r_static
r_int
r_int
id|arthur_to_linux_signals
(braket
l_int|32
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|variable|linux_to_arthur_signals
r_static
r_int
r_int
id|linux_to_arthur_signals
(braket
l_int|32
)braket
op_assign
(brace
l_int|0
comma
op_minus
l_int|1
comma
id|ARTHUR_SIGINT
comma
op_minus
l_int|1
comma
id|ARTHUR_SIGILL
comma
l_int|5
comma
id|ARTHUR_SIGABRT
comma
l_int|7
comma
id|ARTHUR_SIGFPE
comma
l_int|9
comma
id|ARTHUR_SIGUSR1
comma
id|ARTHUR_SIGSEGV
comma
id|ARTHUR_SIGUSR2
comma
l_int|13
comma
l_int|14
comma
id|ARTHUR_SIGTERM
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|function|arthur_lcall7
r_static
r_void
id|arthur_lcall7
c_func
(paren
r_int
id|nr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|siginfo
id|info
suffix:semicolon
id|info.si_signo
op_assign
id|SIGSWI
suffix:semicolon
id|info.si_errno
op_assign
id|nr
suffix:semicolon
multiline_comment|/* Bounce it to the emulator */
id|send_sig_info
c_func
(paren
id|SIGSWI
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|variable|arthur_exec_domain
r_static
r_struct
id|exec_domain
id|arthur_exec_domain
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Arthur&quot;
comma
dot
id|handler
op_assign
id|arthur_lcall7
comma
dot
id|pers_low
op_assign
id|PER_RISCOS
comma
dot
id|pers_high
op_assign
id|PER_RISCOS
comma
dot
id|signal_map
op_assign
id|arthur_to_linux_signals
comma
dot
id|signal_invmap
op_assign
id|linux_to_arthur_signals
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * We could do with some locking to stop Arthur being removed while&n; * processes are using it.&n; */
DECL|function|arthur_init
r_static
r_int
id|__init
id|arthur_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_exec_domain
c_func
(paren
op_amp
id|arthur_exec_domain
)paren
suffix:semicolon
)brace
DECL|function|arthur_exit
r_static
r_void
id|__exit
id|arthur_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_exec_domain
c_func
(paren
op_amp
id|arthur_exec_domain
)paren
suffix:semicolon
)brace
DECL|variable|arthur_init
id|module_init
c_func
(paren
id|arthur_init
)paren
suffix:semicolon
DECL|variable|arthur_exit
id|module_exit
c_func
(paren
id|arthur_exit
)paren
suffix:semicolon
eof
