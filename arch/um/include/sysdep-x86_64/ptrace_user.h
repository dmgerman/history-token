multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_X86_64_PTRACE_USER_H__
DECL|macro|__SYSDEP_X86_64_PTRACE_USER_H__
mdefine_line|#define __SYSDEP_X86_64_PTRACE_USER_H__
DECL|macro|__FRAME_OFFSETS
mdefine_line|#define __FRAME_OFFSETS
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|__FRAME_OFFSETS
macro_line|#undef __FRAME_OFFSETS
DECL|macro|PT_INDEX
mdefine_line|#define PT_INDEX(off) ((off) / sizeof(unsigned long))
DECL|macro|PT_SYSCALL_NR
mdefine_line|#define PT_SYSCALL_NR(regs) ((regs)[PT_INDEX(ORIG_RAX)])
DECL|macro|PT_SYSCALL_NR_OFFSET
mdefine_line|#define PT_SYSCALL_NR_OFFSET (ORIG_RAX)
DECL|macro|PT_SYSCALL_ARG1
mdefine_line|#define PT_SYSCALL_ARG1(regs) (((unsigned long *) (regs))[PT_INDEX(RDI)])
DECL|macro|PT_SYSCALL_ARG1_OFFSET
mdefine_line|#define PT_SYSCALL_ARG1_OFFSET (RDI)
DECL|macro|PT_SYSCALL_ARG2
mdefine_line|#define PT_SYSCALL_ARG2(regs) (((unsigned long *) (regs))[PT_INDEX(RSI)])
DECL|macro|PT_SYSCALL_ARG2_OFFSET
mdefine_line|#define PT_SYSCALL_ARG2_OFFSET (RSI)
DECL|macro|PT_SYSCALL_ARG3
mdefine_line|#define PT_SYSCALL_ARG3(regs) (((unsigned long *) (regs))[PT_INDEX(RDX)])
DECL|macro|PT_SYSCALL_ARG3_OFFSET
mdefine_line|#define PT_SYSCALL_ARG3_OFFSET (RDX)
DECL|macro|PT_SYSCALL_ARG4
mdefine_line|#define PT_SYSCALL_ARG4(regs) (((unsigned long *) (regs))[PT_INDEX(RCX)])
DECL|macro|PT_SYSCALL_ARG4_OFFSET
mdefine_line|#define PT_SYSCALL_ARG4_OFFSET (RCX)
DECL|macro|PT_SYSCALL_ARG5
mdefine_line|#define PT_SYSCALL_ARG5(regs) (((unsigned long *) (regs))[PT_INDEX(R8)])
DECL|macro|PT_SYSCALL_ARG5_OFFSET
mdefine_line|#define PT_SYSCALL_ARG5_OFFSET (R8)
DECL|macro|PT_SYSCALL_ARG6
mdefine_line|#define PT_SYSCALL_ARG6(regs) (((unsigned long *) (regs))[PT_INDEX(R9)])
DECL|macro|PT_SYSCALL_ARG6_OFFSET
mdefine_line|#define PT_SYSCALL_ARG6_OFFSET (R9)
DECL|macro|PT_SYSCALL_RET_OFFSET
mdefine_line|#define PT_SYSCALL_RET_OFFSET (RAX)
DECL|macro|PT_IP_OFFSET
mdefine_line|#define PT_IP_OFFSET (RIP)
DECL|macro|PT_IP
mdefine_line|#define PT_IP(regs) ((regs)[PT_INDEX(RIP)])
DECL|macro|PT_SP_OFFSET
mdefine_line|#define PT_SP_OFFSET (RSP)
DECL|macro|PT_SP
mdefine_line|#define PT_SP(regs) ((regs)[PT_INDEX(RSP)])
DECL|macro|PT_ORIG_RAX_OFFSET
mdefine_line|#define PT_ORIG_RAX_OFFSET (ORIG_RAX)
DECL|macro|PT_ORIG_RAX
mdefine_line|#define PT_ORIG_RAX(regs) ((regs)[PT_INDEX(ORIG_RAX)])
DECL|macro|MAX_REG_OFFSET
mdefine_line|#define MAX_REG_OFFSET (FRAME_SIZE)
DECL|macro|MAX_REG_NR
mdefine_line|#define MAX_REG_NR ((MAX_REG_OFFSET) / sizeof(unsigned long))
multiline_comment|/* x86_64 FC3 doesn&squot;t define this in /usr/include/linux/ptrace.h even though&n; * it&squot;s defined in the kernel&squot;s include/linux/ptrace.h&n; */
macro_line|#ifndef PTRACE_SETOPTIONS
DECL|macro|PTRACE_SETOPTIONS
mdefine_line|#define PTRACE_SETOPTIONS 0x4200
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
