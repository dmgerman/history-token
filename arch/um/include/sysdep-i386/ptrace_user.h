multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_I386_PTRACE_USER_H__
DECL|macro|__SYSDEP_I386_PTRACE_USER_H__
mdefine_line|#define __SYSDEP_I386_PTRACE_USER_H__
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|PT_OFFSET
mdefine_line|#define PT_OFFSET(r) ((r) * sizeof(long))
DECL|macro|PT_SYSCALL_NR
mdefine_line|#define PT_SYSCALL_NR(regs) ((regs)[ORIG_EAX])
DECL|macro|PT_SYSCALL_NR_OFFSET
mdefine_line|#define PT_SYSCALL_NR_OFFSET PT_OFFSET(ORIG_EAX)
DECL|macro|PT_SYSCALL_ARG1_OFFSET
mdefine_line|#define PT_SYSCALL_ARG1_OFFSET PT_OFFSET(EBX)
DECL|macro|PT_SYSCALL_ARG2_OFFSET
mdefine_line|#define PT_SYSCALL_ARG2_OFFSET PT_OFFSET(ECX)
DECL|macro|PT_SYSCALL_ARG3_OFFSET
mdefine_line|#define PT_SYSCALL_ARG3_OFFSET PT_OFFSET(EDX)
DECL|macro|PT_SYSCALL_ARG4_OFFSET
mdefine_line|#define PT_SYSCALL_ARG4_OFFSET PT_OFFSET(ESI)
DECL|macro|PT_SYSCALL_ARG5_OFFSET
mdefine_line|#define PT_SYSCALL_ARG5_OFFSET PT_OFFSET(EDI)
DECL|macro|PT_SYSCALL_RET_OFFSET
mdefine_line|#define PT_SYSCALL_RET_OFFSET PT_OFFSET(EAX)
DECL|macro|PT_IP_OFFSET
mdefine_line|#define PT_IP_OFFSET PT_OFFSET(EIP)
DECL|macro|PT_IP
mdefine_line|#define PT_IP(regs) ((regs)[EIP])
DECL|macro|PT_SP
mdefine_line|#define PT_SP(regs) ((regs)[UESP])
macro_line|#ifndef FRAME_SIZE
DECL|macro|FRAME_SIZE
mdefine_line|#define FRAME_SIZE (17)
macro_line|#endif
DECL|macro|FRAME_SIZE_OFFSET
mdefine_line|#define FRAME_SIZE_OFFSET (FRAME_SIZE * sizeof(unsigned long))
DECL|macro|FP_FRAME_SIZE
mdefine_line|#define FP_FRAME_SIZE (27)
DECL|macro|FPX_FRAME_SIZE
mdefine_line|#define FPX_FRAME_SIZE (128)
DECL|macro|MAX_REG_OFFSET
mdefine_line|#define MAX_REG_OFFSET (FRAME_SIZE_OFFSET)
DECL|macro|MAX_REG_NR
mdefine_line|#define MAX_REG_NR (FRAME_SIZE)
macro_line|#ifdef PTRACE_GETREGS
DECL|macro|UM_HAVE_GETREGS
mdefine_line|#define UM_HAVE_GETREGS
macro_line|#endif
macro_line|#ifdef PTRACE_SETREGS
DECL|macro|UM_HAVE_SETREGS
mdefine_line|#define UM_HAVE_SETREGS
macro_line|#endif
macro_line|#ifdef PTRACE_GETFPREGS
DECL|macro|UM_HAVE_GETFPREGS
mdefine_line|#define UM_HAVE_GETFPREGS
macro_line|#endif
macro_line|#ifdef PTRACE_SETFPREGS
DECL|macro|UM_HAVE_SETFPREGS
mdefine_line|#define UM_HAVE_SETFPREGS
macro_line|#endif
macro_line|#ifdef PTRACE_GETFPXREGS
DECL|macro|UM_HAVE_GETFPXREGS
mdefine_line|#define UM_HAVE_GETFPXREGS
macro_line|#endif
macro_line|#ifdef PTRACE_SETFPXREGS
DECL|macro|UM_HAVE_SETFPXREGS
mdefine_line|#define UM_HAVE_SETFPXREGS
macro_line|#endif
r_extern
r_void
id|update_debugregs
c_func
(paren
r_int
id|seq
)paren
suffix:semicolon
macro_line|#endif
eof
