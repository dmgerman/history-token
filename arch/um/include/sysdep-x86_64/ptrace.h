multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_X86_64_PTRACE_H
DECL|macro|__SYSDEP_X86_64_PTRACE_H
mdefine_line|#define __SYSDEP_X86_64_PTRACE_H
macro_line|#include &quot;uml-config.h&quot;
macro_line|#ifdef UML_CONFIG_MODE_TT
macro_line|#include &quot;sysdep/sc.h&quot;
macro_line|#endif
macro_line|#ifdef UML_CONFIG_MODE_SKAS
macro_line|#include &quot;skas_ptregs.h&quot;
DECL|macro|REGS_IP
mdefine_line|#define REGS_IP(r) ((r)[HOST_IP])
DECL|macro|REGS_SP
mdefine_line|#define REGS_SP(r) ((r)[HOST_SP])
DECL|macro|REGS_RBX
mdefine_line|#define REGS_RBX(r) ((r)[HOST_RBX])
DECL|macro|REGS_RCX
mdefine_line|#define REGS_RCX(r) ((r)[HOST_RCX])
DECL|macro|REGS_RDX
mdefine_line|#define REGS_RDX(r) ((r)[HOST_RDX])
DECL|macro|REGS_RSI
mdefine_line|#define REGS_RSI(r) ((r)[HOST_RSI])
DECL|macro|REGS_RDI
mdefine_line|#define REGS_RDI(r) ((r)[HOST_RDI])
DECL|macro|REGS_RBP
mdefine_line|#define REGS_RBP(r) ((r)[HOST_RBP])
DECL|macro|REGS_RAX
mdefine_line|#define REGS_RAX(r) ((r)[HOST_RAX])
DECL|macro|REGS_R8
mdefine_line|#define REGS_R8(r) ((r)[HOST_R8])
DECL|macro|REGS_R9
mdefine_line|#define REGS_R9(r) ((r)[HOST_R9])
DECL|macro|REGS_R10
mdefine_line|#define REGS_R10(r) ((r)[HOST_R10])
DECL|macro|REGS_R11
mdefine_line|#define REGS_R11(r) ((r)[HOST_R11])
DECL|macro|REGS_R12
mdefine_line|#define REGS_R12(r) ((r)[HOST_R12])
DECL|macro|REGS_R13
mdefine_line|#define REGS_R13(r) ((r)[HOST_R13])
DECL|macro|REGS_R14
mdefine_line|#define REGS_R14(r) ((r)[HOST_R14])
DECL|macro|REGS_R15
mdefine_line|#define REGS_R15(r) ((r)[HOST_R15])
DECL|macro|REGS_CS
mdefine_line|#define REGS_CS(r) ((r)[HOST_CS])
DECL|macro|REGS_EFLAGS
mdefine_line|#define REGS_EFLAGS(r) ((r)[HOST_EFLAGS])
DECL|macro|REGS_SS
mdefine_line|#define REGS_SS(r) ((r)[HOST_SS])
DECL|macro|HOST_FS_BASE
mdefine_line|#define HOST_FS_BASE 21
DECL|macro|HOST_GS_BASE
mdefine_line|#define HOST_GS_BASE 22
DECL|macro|HOST_DS
mdefine_line|#define HOST_DS 23
DECL|macro|HOST_ES
mdefine_line|#define HOST_ES 24
DECL|macro|HOST_FS
mdefine_line|#define HOST_FS 25
DECL|macro|HOST_GS
mdefine_line|#define HOST_GS 26
DECL|macro|REGS_FS_BASE
mdefine_line|#define REGS_FS_BASE(r) ((r)[HOST_FS_BASE])
DECL|macro|REGS_GS_BASE
mdefine_line|#define REGS_GS_BASE(r) ((r)[HOST_GS_BASE])
DECL|macro|REGS_DS
mdefine_line|#define REGS_DS(r) ((r)[HOST_DS])
DECL|macro|REGS_ES
mdefine_line|#define REGS_ES(r) ((r)[HOST_ES])
DECL|macro|REGS_FS
mdefine_line|#define REGS_FS(r) ((r)[HOST_FS])
DECL|macro|REGS_GS
mdefine_line|#define REGS_GS(r) ((r)[HOST_GS])
DECL|macro|REGS_ORIG_RAX
mdefine_line|#define REGS_ORIG_RAX(r) ((r)[HOST_ORIG_RAX])
DECL|macro|REGS_SET_SYSCALL_RETURN
mdefine_line|#define REGS_SET_SYSCALL_RETURN(r, res) REGS_RAX(r) = (res)
DECL|macro|REGS_RESTART_SYSCALL
mdefine_line|#define REGS_RESTART_SYSCALL(r) IP_RESTART_SYSCALL(REGS_IP(r))
DECL|macro|REGS_SEGV_IS_FIXABLE
mdefine_line|#define REGS_SEGV_IS_FIXABLE(r) SEGV_IS_FIXABLE((r)-&gt;trap_type)
DECL|macro|REGS_FAULT_ADDR
mdefine_line|#define REGS_FAULT_ADDR(r) ((r)-&gt;fault_addr)
DECL|macro|REGS_FAULT_WRITE
mdefine_line|#define REGS_FAULT_WRITE(r) FAULT_WRITE((r)-&gt;fault_type)
DECL|macro|REGS_TRAP
mdefine_line|#define REGS_TRAP(r) ((r)-&gt;trap_type)
DECL|macro|REGS_ERR
mdefine_line|#define REGS_ERR(r) ((r)-&gt;fault_type)
macro_line|#endif
macro_line|#include &quot;choose-mode.h&quot;
multiline_comment|/* XXX */
DECL|union|uml_pt_regs
r_union
id|uml_pt_regs
(brace
macro_line|#ifdef UML_CONFIG_MODE_TT
DECL|struct|tt_regs
r_struct
id|tt_regs
(brace
DECL|member|syscall
r_int
id|syscall
suffix:semicolon
DECL|member|orig_rax
r_int
r_int
id|orig_rax
suffix:semicolon
DECL|member|sc
r_void
op_star
id|sc
suffix:semicolon
DECL|member|tt
)brace
id|tt
suffix:semicolon
macro_line|#endif
macro_line|#ifdef UML_CONFIG_MODE_SKAS
DECL|struct|skas_regs
r_struct
id|skas_regs
(brace
multiline_comment|/* XXX */
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|27
)braket
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
(braket
l_int|65
)braket
suffix:semicolon
DECL|member|fault_addr
r_int
r_int
id|fault_addr
suffix:semicolon
DECL|member|fault_type
r_int
r_int
id|fault_type
suffix:semicolon
DECL|member|trap_type
r_int
r_int
id|trap_type
suffix:semicolon
DECL|member|syscall
r_int
id|syscall
suffix:semicolon
DECL|member|is_user
r_int
id|is_user
suffix:semicolon
DECL|member|skas
)brace
id|skas
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|EMPTY_UML_PT_REGS
mdefine_line|#define EMPTY_UML_PT_REGS { }
multiline_comment|/* XXX */
r_extern
r_int
id|mode_tt
suffix:semicolon
DECL|macro|UPT_RBX
mdefine_line|#define UPT_RBX(r) CHOOSE_MODE(SC_RBX(UPT_SC(r)), REGS_RBX((r)-&gt;skas.regs))
DECL|macro|UPT_RCX
mdefine_line|#define UPT_RCX(r) CHOOSE_MODE(SC_RCX(UPT_SC(r)), REGS_RCX((r)-&gt;skas.regs))
DECL|macro|UPT_RDX
mdefine_line|#define UPT_RDX(r) CHOOSE_MODE(SC_RDX(UPT_SC(r)), REGS_RDX((r)-&gt;skas.regs))
DECL|macro|UPT_RSI
mdefine_line|#define UPT_RSI(r) CHOOSE_MODE(SC_RSI(UPT_SC(r)), REGS_RSI((r)-&gt;skas.regs))
DECL|macro|UPT_RDI
mdefine_line|#define UPT_RDI(r) CHOOSE_MODE(SC_RDI(UPT_SC(r)), REGS_RDI((r)-&gt;skas.regs))
DECL|macro|UPT_RBP
mdefine_line|#define UPT_RBP(r) CHOOSE_MODE(SC_RBP(UPT_SC(r)), REGS_RBP((r)-&gt;skas.regs))
DECL|macro|UPT_RAX
mdefine_line|#define UPT_RAX(r) CHOOSE_MODE(SC_RAX(UPT_SC(r)), REGS_RAX((r)-&gt;skas.regs))
DECL|macro|UPT_R8
mdefine_line|#define UPT_R8(r) CHOOSE_MODE(SC_R8(UPT_SC(r)), REGS_R8((r)-&gt;skas.regs))
DECL|macro|UPT_R9
mdefine_line|#define UPT_R9(r) CHOOSE_MODE(SC_R9(UPT_SC(r)), REGS_R9((r)-&gt;skas.regs))
DECL|macro|UPT_R10
mdefine_line|#define UPT_R10(r) CHOOSE_MODE(SC_R10(UPT_SC(r)), REGS_R10((r)-&gt;skas.regs))
DECL|macro|UPT_R11
mdefine_line|#define UPT_R11(r) CHOOSE_MODE(SC_R11(UPT_SC(r)), REGS_R11((r)-&gt;skas.regs))
DECL|macro|UPT_R12
mdefine_line|#define UPT_R12(r) CHOOSE_MODE(SC_R12(UPT_SC(r)), REGS_R12((r)-&gt;skas.regs))
DECL|macro|UPT_R13
mdefine_line|#define UPT_R13(r) CHOOSE_MODE(SC_R13(UPT_SC(r)), REGS_R13((r)-&gt;skas.regs))
DECL|macro|UPT_R14
mdefine_line|#define UPT_R14(r) CHOOSE_MODE(SC_R14(UPT_SC(r)), REGS_R14((r)-&gt;skas.regs))
DECL|macro|UPT_R15
mdefine_line|#define UPT_R15(r) CHOOSE_MODE(SC_R15(UPT_SC(r)), REGS_R15((r)-&gt;skas.regs))
DECL|macro|UPT_CS
mdefine_line|#define UPT_CS(r) CHOOSE_MODE(SC_CS(UPT_SC(r)), REGS_CS((r)-&gt;skas.regs))
DECL|macro|UPT_FS
mdefine_line|#define UPT_FS(r) CHOOSE_MODE(SC_FS(UPT_SC(r)), REGS_FS((r)-&gt;skas.regs))
DECL|macro|UPT_GS
mdefine_line|#define UPT_GS(r) CHOOSE_MODE(SC_GS(UPT_SC(r)), REGS_GS((r)-&gt;skas.regs))
DECL|macro|UPT_DS
mdefine_line|#define UPT_DS(r) CHOOSE_MODE(SC_DS(UPT_SC(r)), REGS_DS((r)-&gt;skas.regs))
DECL|macro|UPT_ES
mdefine_line|#define UPT_ES(r) CHOOSE_MODE(SC_ES(UPT_SC(r)), REGS_ES((r)-&gt;skas.regs))
DECL|macro|UPT_CS
mdefine_line|#define UPT_CS(r) CHOOSE_MODE(SC_CS(UPT_SC(r)), REGS_CS((r)-&gt;skas.regs))
DECL|macro|UPT_ORIG_RAX
mdefine_line|#define UPT_ORIG_RAX(r) &bslash;&n;&t;CHOOSE_MODE((r)-&gt;tt.orig_rax, REGS_ORIG_RAX((r)-&gt;skas.regs))
DECL|macro|UPT_IP
mdefine_line|#define UPT_IP(r) CHOOSE_MODE(SC_IP(UPT_SC(r)), REGS_IP((r)-&gt;skas.regs))
DECL|macro|UPT_SP
mdefine_line|#define UPT_SP(r) CHOOSE_MODE(SC_SP(UPT_SC(r)), REGS_SP((r)-&gt;skas.regs))
DECL|macro|UPT_EFLAGS
mdefine_line|#define UPT_EFLAGS(r) &bslash;&n;&t;CHOOSE_MODE(SC_EFLAGS(UPT_SC(r)), REGS_EFLAGS((r)-&gt;skas.regs))
DECL|macro|UPT_SC
mdefine_line|#define UPT_SC(r) ((r)-&gt;tt.sc)
DECL|macro|UPT_SYSCALL_NR
mdefine_line|#define UPT_SYSCALL_NR(r) CHOOSE_MODE((r)-&gt;tt.syscall, (r)-&gt;skas.syscall)
r_extern
r_int
id|user_context
c_func
(paren
r_int
r_int
id|sp
)paren
suffix:semicolon
DECL|macro|UPT_IS_USER
mdefine_line|#define UPT_IS_USER(r) &bslash;&n;&t;CHOOSE_MODE(user_context(UPT_SP(r)), (r)-&gt;skas.is_user)
DECL|macro|UPT_SYSCALL_ARG1
mdefine_line|#define UPT_SYSCALL_ARG1(r) UPT_RDI(r)
DECL|macro|UPT_SYSCALL_ARG2
mdefine_line|#define UPT_SYSCALL_ARG2(r) UPT_RSI(r)
DECL|macro|UPT_SYSCALL_ARG3
mdefine_line|#define UPT_SYSCALL_ARG3(r) UPT_RDX(r)
DECL|macro|UPT_SYSCALL_ARG4
mdefine_line|#define UPT_SYSCALL_ARG4(r) UPT_R10(r)
DECL|macro|UPT_SYSCALL_ARG5
mdefine_line|#define UPT_SYSCALL_ARG5(r) UPT_R8(r)
DECL|macro|UPT_SYSCALL_ARG6
mdefine_line|#define UPT_SYSCALL_ARG6(r) UPT_R9(r)
DECL|struct|syscall_args
r_struct
id|syscall_args
(brace
DECL|member|args
r_int
r_int
id|args
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SYSCALL_ARGS
mdefine_line|#define SYSCALL_ARGS(r) ((struct syscall_args) &bslash;&n;                        { .args = { UPT_SYSCALL_ARG1(r), &bslash;&n;                                    UPT_SYSCALL_ARG2(r), &bslash;&n; &t;&t;&t;            UPT_SYSCALL_ARG3(r), &bslash;&n;                                    UPT_SYSCALL_ARG4(r), &bslash;&n;&t;&t;                    UPT_SYSCALL_ARG5(r), &bslash;&n;                                    UPT_SYSCALL_ARG6(r) } } )
DECL|macro|UPT_REG
mdefine_line|#define UPT_REG(regs, reg) &bslash;&n;        ({      unsigned long val; &bslash;&n;                switch(reg){ &bslash;&n;&t;&t;case R8: val = UPT_R8(regs); break; &bslash;&n;&t;&t;case R9: val = UPT_R9(regs); break; &bslash;&n;&t;&t;case R10: val = UPT_R10(regs); break; &bslash;&n;&t;&t;case R11: val = UPT_R11(regs); break; &bslash;&n;&t;&t;case R12: val = UPT_R12(regs); break; &bslash;&n;&t;&t;case R13: val = UPT_R13(regs); break; &bslash;&n;&t;&t;case R14: val = UPT_R14(regs); break; &bslash;&n;&t;&t;case R15: val = UPT_R15(regs); break; &bslash;&n;                case RIP: val = UPT_IP(regs); break; &bslash;&n;                case RSP: val = UPT_SP(regs); break; &bslash;&n;                case RAX: val = UPT_RAX(regs); break; &bslash;&n;                case RBX: val = UPT_RBX(regs); break; &bslash;&n;                case RCX: val = UPT_RCX(regs); break; &bslash;&n;                case RDX: val = UPT_RDX(regs); break; &bslash;&n;                case RSI: val = UPT_RSI(regs); break; &bslash;&n;                case RDI: val = UPT_RDI(regs); break; &bslash;&n;                case RBP: val = UPT_RBP(regs); break; &bslash;&n;                case ORIG_RAX: val = UPT_ORIG_RAX(regs); break; &bslash;&n;                case CS: val = UPT_CS(regs); break; &bslash;&n;                case DS: val = UPT_DS(regs); break; &bslash;&n;                case ES: val = UPT_ES(regs); break; &bslash;&n;                case FS: val = UPT_FS(regs); break; &bslash;&n;                case GS: val = UPT_GS(regs); break; &bslash;&n;                case EFLAGS: val = UPT_EFLAGS(regs); break; &bslash;&n;                default :  &bslash;&n;                        panic(&quot;Bad register in UPT_REG : %d&bslash;n&quot;, reg);  &bslash;&n;                        val = -1; &bslash;&n;                } &bslash;&n;                val; &bslash;&n;        })
DECL|macro|UPT_SET
mdefine_line|#define UPT_SET(regs, reg, val) &bslash;&n;        ({      unsigned long val; &bslash;&n;                switch(reg){ &bslash;&n;&t;&t;case R8: UPT_R8(regs) = val; break; &bslash;&n;&t;&t;case R9: UPT_R9(regs) = val; break; &bslash;&n;&t;&t;case R10: UPT_R10(regs) = val; break; &bslash;&n;&t;&t;case R11: UPT_R11(regs) = val; break; &bslash;&n;&t;&t;case R12: UPT_R12(regs) = val; break; &bslash;&n;&t;&t;case R13: UPT_R13(regs) = val; break; &bslash;&n;&t;&t;case R14: UPT_R14(regs) = val; break; &bslash;&n;&t;&t;case R15: UPT_R15(regs) = val; break; &bslash;&n;                case RIP: UPT_IP(regs) = val; break; &bslash;&n;                case RSP: UPT_SP(regs) = val; break; &bslash;&n;                case RAX: UPT_RAX(regs) = val; break; &bslash;&n;                case RBX: UPT_RBX(regs) = val; break; &bslash;&n;                case RCX: UPT_RCX(regs) = val; break; &bslash;&n;                case RDX: UPT_RDX(regs) = val; break; &bslash;&n;                case RSI: UPT_RSI(regs) = val; break; &bslash;&n;                case RDI: UPT_RDI(regs) = val; break; &bslash;&n;                case RBP: UPT_RBP(regs) = val; break; &bslash;&n;                case ORIG_RAX: UPT_ORIG_RAX(regs) = val; break; &bslash;&n;                case CS: UPT_CS(regs) = val; break; &bslash;&n;                case DS: UPT_DS(regs) = val; break; &bslash;&n;                case ES: UPT_ES(regs) = val; break; &bslash;&n;                case FS: UPT_FS(regs) = val; break; &bslash;&n;                case GS: UPT_GS(regs) = val; break; &bslash;&n;                case EFLAGS: UPT_EFLAGS(regs) = val; break; &bslash;&n;                default :  &bslash;&n;                        panic(&quot;Bad register in UPT_SET : %d&bslash;n&quot;, reg);  &bslash;&n;&t;&t;&t;break; &bslash;&n;                } &bslash;&n;                val; &bslash;&n;        })
DECL|macro|UPT_SET_SYSCALL_RETURN
mdefine_line|#define UPT_SET_SYSCALL_RETURN(r, res) &bslash;&n;&t;CHOOSE_MODE(SC_SET_SYSCALL_RETURN(UPT_SC(r), (res)), &bslash;&n;                    REGS_SET_SYSCALL_RETURN((r)-&gt;skas.regs, (res)))
DECL|macro|UPT_RESTART_SYSCALL
mdefine_line|#define UPT_RESTART_SYSCALL(r) &bslash;&n;&t;CHOOSE_MODE(SC_RESTART_SYSCALL(UPT_SC(r)), &bslash;&n;&t;&t;    REGS_RESTART_SYSCALL((r)-&gt;skas.regs))
DECL|macro|UPT_SEGV_IS_FIXABLE
mdefine_line|#define UPT_SEGV_IS_FIXABLE(r) &bslash;&n;&t;CHOOSE_MODE(SC_SEGV_IS_FIXABLE(UPT_SC(r)), &bslash;&n;                    REGS_SEGV_IS_FIXABLE(&amp;r-&gt;skas))
DECL|macro|UPT_FAULT_ADDR
mdefine_line|#define UPT_FAULT_ADDR(r) &bslash;&n;&t;CHOOSE_MODE(SC_FAULT_ADDR(UPT_SC(r)), REGS_FAULT_ADDR(&amp;r-&gt;skas))
DECL|macro|UPT_FAULT_WRITE
mdefine_line|#define UPT_FAULT_WRITE(r) &bslash;&n;&t;CHOOSE_MODE(SC_FAULT_WRITE(UPT_SC(r)), REGS_FAULT_WRITE(&amp;r-&gt;skas))
DECL|macro|UPT_TRAP
mdefine_line|#define UPT_TRAP(r) CHOOSE_MODE(SC_TRAP_TYPE(UPT_SC(r)), REGS_TRAP(&amp;r-&gt;skas))
DECL|macro|UPT_ERR
mdefine_line|#define UPT_ERR(r) CHOOSE_MODE(SC_FAULT_TYPE(UPT_SC(r)), REGS_ERR(&amp;r-&gt;skas))
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
