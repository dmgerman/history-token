multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __PTRACE_USER_H__
DECL|macro|__PTRACE_USER_H__
mdefine_line|#define __PTRACE_USER_H__
macro_line|#include &quot;sysdep/ptrace_user.h&quot;
r_extern
r_int
id|ptrace_getregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs_out
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_setregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs_in
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_getfpregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs_out
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_setfpregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|arch_enter_kernel
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|arch_leave_kernel
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|ptrace_pokeuser
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/* syscall emulation path in ptrace */
macro_line|#ifndef PTRACE_SYSEMU
DECL|macro|PTRACE_SYSEMU
mdefine_line|#define PTRACE_SYSEMU 31
macro_line|#endif
macro_line|#ifndef PTRACE_SYSEMU_SINGLESTEP
DECL|macro|PTRACE_SYSEMU_SINGLESTEP
mdefine_line|#define PTRACE_SYSEMU_SINGLESTEP 32
macro_line|#endif
multiline_comment|/* On architectures, that started to support PTRACE_O_TRACESYSGOOD&n; * in linux 2.4, there are two different definitions of&n; * PTRACE_SETOPTIONS: linux 2.4 uses 21 while linux 2.6 uses 0x4200.&n; * For binary compatibility, 2.6 also supports the old &quot;21&quot;, named&n; * PTRACE_OLDSETOPTION. On these architectures, UML always must use&n; * &quot;21&quot;, to ensure the kernel runs on 2.4 and 2.6 host without&n; * recompilation. So, we use PTRACE_OLDSETOPTIONS in UML.&n; * We also want to be able to build the kernel on 2.4, which doesn&squot;t&n; * have PTRACE_OLDSETOPTIONS. So, if it is missing, we declare&n; * PTRACE_OLDSETOPTIONS to to be the same as PTRACE_SETOPTIONS.&n; *&n; * On architectures, that start to support PTRACE_O_TRACESYSGOOD on&n; * linux 2.6, PTRACE_OLDSETOPTIONS never is defined, and also isn&squot;t&n; * supported by the host kernel. In that case, our trick lets us use&n; * the new 0x4200 with the name PTRACE_OLDSETOPTIONS.&n; */
macro_line|#ifndef PTRACE_OLDSETOPTIONS
DECL|macro|PTRACE_OLDSETOPTIONS
mdefine_line|#define PTRACE_OLDSETOPTIONS PTRACE_SETOPTIONS
macro_line|#endif
r_void
id|set_using_sysemu
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
r_int
id|get_using_sysemu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sysemu_supported
suffix:semicolon
DECL|macro|SELECT_PTRACE_OPERATION
mdefine_line|#define SELECT_PTRACE_OPERATION(sysemu_mode, singlestep_mode) &bslash;&n;&t;(((int[3][3] ) { &bslash;&n;&t;&t;{ PTRACE_SYSCALL, PTRACE_SYSCALL, PTRACE_SINGLESTEP }, &bslash;&n;&t;&t;{ PTRACE_SYSEMU, PTRACE_SYSEMU, PTRACE_SINGLESTEP }, &bslash;&n;&t;&t;{ PTRACE_SYSEMU, PTRACE_SYSEMU_SINGLESTEP, PTRACE_SYSEMU_SINGLESTEP }}) &bslash;&n;&t;&t;[sysemu_mode][singlestep_mode])
macro_line|#endif
eof
