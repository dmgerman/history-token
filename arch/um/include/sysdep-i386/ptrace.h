multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_I386_PTRACE_H
DECL|macro|__SYSDEP_I386_PTRACE_H
mdefine_line|#define __SYSDEP_I386_PTRACE_H
macro_line|#include &quot;uml-config.h&quot;
macro_line|#include &quot;ptrace-tt.h&quot;
macro_line|#include &quot;ptrace-skas.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
DECL|struct|uml_pt_regs
r_struct
id|uml_pt_regs
(brace
DECL|member|args
r_int
r_int
id|args
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|syscall
r_int
id|syscall
suffix:semicolon
DECL|member|is_user
r_int
id|is_user
suffix:semicolon
r_union
(brace
macro_line|#ifdef CONFIG_MODE_TT
DECL|member|tt
r_void
op_star
id|tt
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_SKAS
r_struct
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
id|HOST_FRAME_SIZE
)braket
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
(braket
id|HOST_FP_SIZE
)braket
suffix:semicolon
DECL|member|xfp
r_int
r_int
id|xfp
(braket
id|HOST_XFP_SIZE
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
DECL|member|skas
)brace
id|skas
suffix:semicolon
macro_line|#endif
DECL|member|mode
)brace
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EMPTY_UML_PT_REGS
mdefine_line|#define EMPTY_UML_PT_REGS { &bslash;&n;&t;syscall : &t;-1, &bslash;&n;&t;args : &t;&t;{ [0 ... 5] = 0 }, &bslash;&n;&t;is_user :&t;0 }
r_extern
r_int
id|mode_tt
suffix:semicolon
DECL|macro|UPT_IP
mdefine_line|#define UPT_IP(r) &bslash;&n;&t;CHOOSE_MODE(SC_IP((r)-&gt;mode.tt), REGS_IP((r)-&gt;mode.skas.regs))
DECL|macro|UPT_SP
mdefine_line|#define UPT_SP(r) &bslash;&n;&t;CHOOSE_MODE(SC_SP((r)-&gt;mode.tt), REGS_SP((r)-&gt;mode.skas.regs))
DECL|macro|UPT_EFLAGS
mdefine_line|#define UPT_EFLAGS(r) &bslash;&n;&t;CHOOSE_MODE(SC_EFLAGS((r)-&gt;mode.tt), REGS_EFLAGS((r)-&gt;mode.skas.regs))
DECL|macro|UPT_EAX
mdefine_line|#define UPT_EAX(r) &bslash;&n;&t;CHOOSE_MODE(SC_EAX((r)-&gt;mode.tt), REGS_EAX((r)-&gt;mode.skas.regs))
DECL|macro|UPT_EBX
mdefine_line|#define UPT_EBX(r) &bslash;&n;&t;CHOOSE_MODE(SC_EBX((r)-&gt;mode.tt), REGS_EBX((r)-&gt;mode.skas.regs))
DECL|macro|UPT_ECX
mdefine_line|#define UPT_ECX(r) &bslash;&n;&t;CHOOSE_MODE(SC_ECX((r)-&gt;mode.tt), REGS_ECX((r)-&gt;mode.skas.regs))
DECL|macro|UPT_EDX
mdefine_line|#define UPT_EDX(r) &bslash;&n;&t;CHOOSE_MODE(SC_EDX((r)-&gt;mode.tt), REGS_EDX((r)-&gt;mode.skas.regs))
DECL|macro|UPT_ESI
mdefine_line|#define UPT_ESI(r) &bslash;&n;&t;CHOOSE_MODE(SC_ESI((r)-&gt;mode.tt), REGS_ESI((r)-&gt;mode.skas.regs))
DECL|macro|UPT_EDI
mdefine_line|#define UPT_EDI(r) &bslash;&n;&t;CHOOSE_MODE(SC_EDI((r)-&gt;mode.tt), REGS_EDI((r)-&gt;mode.skas.regs))
DECL|macro|UPT_EBP
mdefine_line|#define UPT_EBP(r) &bslash;&n;&t;CHOOSE_MODE(SC_EBP((r)-&gt;mode.tt), REGS_EBP((r)-&gt;mode.skas.regs))
DECL|macro|UPT_ORIG_EAX
mdefine_line|#define UPT_ORIG_EAX(r) ((r)-&gt;syscall)
DECL|macro|UPT_CS
mdefine_line|#define UPT_CS(r) &bslash;&n;&t;CHOOSE_MODE(SC_CS((r)-&gt;mode.tt), REGS_CS((r)-&gt;mode.skas.regs))
DECL|macro|UPT_SS
mdefine_line|#define UPT_SS(r) &bslash;&n;&t;CHOOSE_MODE(SC_SS((r)-&gt;mode.tt), REGS_SS((r)-&gt;mode.skas.regs))
DECL|macro|UPT_DS
mdefine_line|#define UPT_DS(r) &bslash;&n;&t;CHOOSE_MODE(SC_DS((r)-&gt;mode.tt), REGS_DS((r)-&gt;mode.skas.regs))
DECL|macro|UPT_ES
mdefine_line|#define UPT_ES(r) &bslash;&n;&t;CHOOSE_MODE(SC_ES((r)-&gt;mode.tt), REGS_ES((r)-&gt;mode.skas.regs))
DECL|macro|UPT_FS
mdefine_line|#define UPT_FS(r) &bslash;&n;&t;CHOOSE_MODE(SC_FS((r)-&gt;mode.tt), REGS_FS((r)-&gt;mode.skas.regs))
DECL|macro|UPT_GS
mdefine_line|#define UPT_GS(r) &bslash;&n;&t;CHOOSE_MODE(SC_GS((r)-&gt;mode.tt), REGS_GS((r)-&gt;mode.skas.regs))
DECL|macro|UPT_SC
mdefine_line|#define UPT_SC(r) ((r)-&gt;mode.tt)
DECL|macro|UPT_REG
mdefine_line|#define UPT_REG(regs, reg) &bslash;&n;&t;({&t;unsigned long val; &bslash;&n;&t;&t;switch(reg){ &bslash;&n;&t;&t;case EIP: val = UPT_IP(regs); break; &bslash;&n;&t;&t;case UESP: val = UPT_SP(regs); break; &bslash;&n;&t;&t;case EAX: val = UPT_EAX(regs); break; &bslash;&n;&t;&t;case EBX: val = UPT_EBX(regs); break; &bslash;&n;&t;&t;case ECX: val = UPT_ECX(regs); break; &bslash;&n;&t;&t;case EDX: val = UPT_EDX(regs); break; &bslash;&n;&t;&t;case ESI: val = UPT_ESI(regs); break; &bslash;&n;&t;&t;case EDI: val = UPT_EDI(regs); break; &bslash;&n;&t;&t;case EBP: val = UPT_EBP(regs); break; &bslash;&n;&t;&t;case ORIG_EAX: val = UPT_ORIG_EAX(regs); break; &bslash;&n;&t;&t;case CS: val = UPT_CS(regs); break; &bslash;&n;&t;&t;case SS: val = UPT_SS(regs); break; &bslash;&n;&t;&t;case DS: val = UPT_DS(regs); break; &bslash;&n;&t;&t;case ES: val = UPT_ES(regs); break; &bslash;&n;&t;&t;case FS: val = UPT_FS(regs); break; &bslash;&n;&t;&t;case GS: val = UPT_GS(regs); break; &bslash;&n;&t;&t;case EFL: val = UPT_EFLAGS(regs); break; &bslash;&n;&t;&t;default :  &bslash;&n;&t;&t;&t;panic(&quot;Bad register in UPT_REG : %d&bslash;n&quot;, reg);  &bslash;&n;&t;&t;&t;val = -1; &bslash;&n;&t;&t;} &bslash;&n;&t;        val; &bslash;&n;&t;})
DECL|macro|UPT_SET
mdefine_line|#define UPT_SET(regs, reg, val) &bslash;&n;&t;do { &bslash;&n;&t;&t;switch(reg){ &bslash;&n;&t;&t;case EIP: UPT_IP(regs) = val; break; &bslash;&n;&t;&t;case UESP: UPT_SP(regs) = val; break; &bslash;&n;&t;&t;case EAX: UPT_EAX(regs) = val; break; &bslash;&n;&t;&t;case EBX: UPT_EBX(regs) = val; break; &bslash;&n;&t;&t;case ECX: UPT_ECX(regs) = val; break; &bslash;&n;&t;&t;case EDX: UPT_EDX(regs) = val; break; &bslash;&n;&t;&t;case ESI: UPT_ESI(regs) = val; break; &bslash;&n;&t;&t;case EDI: UPT_EDI(regs) = val; break; &bslash;&n;&t;&t;case EBP: UPT_EBP(regs) = val; break; &bslash;&n;&t;&t;case ORIG_EAX: UPT_ORIG_EAX(regs) = val; break; &bslash;&n;&t;&t;case CS: UPT_CS(regs) = val; break; &bslash;&n;&t;&t;case SS: UPT_SS(regs) = val; break; &bslash;&n;&t;&t;case DS: UPT_DS(regs) = val; break; &bslash;&n;&t;&t;case ES: UPT_ES(regs) = val; break; &bslash;&n;&t;&t;case FS: UPT_FS(regs) = val; break; &bslash;&n;&t;&t;case GS: UPT_GS(regs) = val; break; &bslash;&n;&t;&t;case EFL: UPT_EFLAGS(regs) = val; break; &bslash;&n;&t;&t;default :  &bslash;&n;&t;&t;&t;panic(&quot;Bad register in UPT_SET : %d&bslash;n&quot;, reg);  &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
DECL|macro|UPT_SET_SYSCALL_RETURN
mdefine_line|#define UPT_SET_SYSCALL_RETURN(r, res) &bslash;&n;&t;CHOOSE_MODE(SC_SET_SYSCALL_RETURN((r)-&gt;mode.tt, (res)), &bslash;&n;                    REGS_SET_SYSCALL_RETURN((r)-&gt;mode.skas.regs, (res)))
DECL|macro|UPT_RESTART_SYSCALL
mdefine_line|#define UPT_RESTART_SYSCALL(r) &bslash;&n;&t;CHOOSE_MODE(SC_RESTART_SYSCALL((r)-&gt;mode.tt), &bslash;&n;&t;&t;    REGS_RESTART_SYSCALL((r)-&gt;mode.skas.regs))
DECL|macro|UPT_ORIG_SYSCALL
mdefine_line|#define UPT_ORIG_SYSCALL(r) UPT_EAX(r)
DECL|macro|UPT_SYSCALL_NR
mdefine_line|#define UPT_SYSCALL_NR(r) ((r)-&gt;syscall)
DECL|macro|UPT_SYSCALL_RET
mdefine_line|#define UPT_SYSCALL_RET(r) UPT_EAX(r)
DECL|macro|UPT_SEGV_IS_FIXABLE
mdefine_line|#define UPT_SEGV_IS_FIXABLE(r) &bslash;&n;&t;CHOOSE_MODE(SC_SEGV_IS_FIXABLE(r-&gt;mode.tt), &bslash;&n;&t;&t;    REGS_SEGV_IS_FIXABLE(&amp;r-&gt;mode.skas))
DECL|macro|UPT_FAULT_ADDR
mdefine_line|#define UPT_FAULT_ADDR(r) &bslash;&n;&t;CHOOSE_MODE(SC_FAULT_ADDR(r-&gt;mode.tt), &bslash;&n;&t;&t;    REGS_FAULT_ADDR(&amp;r-&gt;mode.skas))
DECL|macro|UPT_FAULT_WRITE
mdefine_line|#define UPT_FAULT_WRITE(r) &bslash;&n;&t;CHOOSE_MODE(SC_FAULT_WRITE(r-&gt;mode.tt), &bslash;&n;&t;&t;    REGS_FAULT_WRITE(&amp;r-&gt;mode.skas))
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
