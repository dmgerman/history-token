multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __PTRACE_SKAS_H
DECL|macro|__PTRACE_SKAS_H
mdefine_line|#define __PTRACE_SKAS_H
macro_line|#include &quot;uml-config.h&quot;
macro_line|#ifdef UML_CONFIG_MODE_SKAS
macro_line|#include &quot;skas_ptregs.h&quot;
DECL|macro|HOST_FRAME_SIZE
mdefine_line|#define HOST_FRAME_SIZE 17
DECL|macro|REGS_IP
mdefine_line|#define REGS_IP(r) ((r)[HOST_IP])
DECL|macro|REGS_SP
mdefine_line|#define REGS_SP(r) ((r)[HOST_SP])
DECL|macro|REGS_EFLAGS
mdefine_line|#define REGS_EFLAGS(r) ((r)[HOST_EFLAGS])
DECL|macro|REGS_EAX
mdefine_line|#define REGS_EAX(r) ((r)[HOST_EAX])
DECL|macro|REGS_EBX
mdefine_line|#define REGS_EBX(r) ((r)[HOST_EBX])
DECL|macro|REGS_ECX
mdefine_line|#define REGS_ECX(r) ((r)[HOST_ECX])
DECL|macro|REGS_EDX
mdefine_line|#define REGS_EDX(r) ((r)[HOST_EDX])
DECL|macro|REGS_ESI
mdefine_line|#define REGS_ESI(r) ((r)[HOST_ESI])
DECL|macro|REGS_EDI
mdefine_line|#define REGS_EDI(r) ((r)[HOST_EDI])
DECL|macro|REGS_EBP
mdefine_line|#define REGS_EBP(r) ((r)[HOST_EBP])
DECL|macro|REGS_CS
mdefine_line|#define REGS_CS(r) ((r)[HOST_CS])
DECL|macro|REGS_SS
mdefine_line|#define REGS_SS(r) ((r)[HOST_SS])
DECL|macro|REGS_DS
mdefine_line|#define REGS_DS(r) ((r)[HOST_DS])
DECL|macro|REGS_ES
mdefine_line|#define REGS_ES(r) ((r)[HOST_ES])
DECL|macro|REGS_FS
mdefine_line|#define REGS_FS(r) ((r)[HOST_FS])
DECL|macro|REGS_GS
mdefine_line|#define REGS_GS(r) ((r)[HOST_GS])
DECL|macro|REGS_SET_SYSCALL_RETURN
mdefine_line|#define REGS_SET_SYSCALL_RETURN(r, res) REGS_EAX(r) = (res)
DECL|macro|REGS_RESTART_SYSCALL
mdefine_line|#define REGS_RESTART_SYSCALL(r) IP_RESTART_SYSCALL(REGS_IP(r))
DECL|macro|REGS_SEGV_IS_FIXABLE
mdefine_line|#define REGS_SEGV_IS_FIXABLE(r) SEGV_IS_FIXABLE((r)-&gt;trap_type)
DECL|macro|REGS_FAULT_ADDR
mdefine_line|#define REGS_FAULT_ADDR(r) ((r)-&gt;fault_addr)
DECL|macro|REGS_FAULT_WRITE
mdefine_line|#define REGS_FAULT_WRITE(r) FAULT_WRITE((r)-&gt;fault_type)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
