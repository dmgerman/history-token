multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSDEP_I386_PTRACE_H
DECL|macro|__SYSDEP_I386_PTRACE_H
mdefine_line|#define __SYSDEP_I386_PTRACE_H
macro_line|#include &quot;sysdep/sc.h&quot;
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
DECL|member|sc
r_void
op_star
id|sc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EMPTY_UML_PT_REGS
mdefine_line|#define EMPTY_UML_PT_REGS { &bslash;&n;&t;syscall : &t;-1, &bslash;&n;&t;args : &t;&t;{ [0 ... 5] = 0 }, &bslash;&n;&t;is_user :&t;0, &bslash;&n;&t;sc : &t;&t;NULL }
DECL|macro|UPT_IP
mdefine_line|#define UPT_IP(regs) SC_IP((regs)-&gt;sc)
DECL|macro|UPT_SP
mdefine_line|#define UPT_SP(regs) SC_SP((regs)-&gt;sc)
DECL|macro|UPT_EFLAGS
mdefine_line|#define UPT_EFLAGS(regs) SC_EFLAGS((regs)-&gt;sc)
DECL|macro|UPT_EAX
mdefine_line|#define UPT_EAX(regs) SC_EAX((regs)-&gt;sc)
DECL|macro|UPT_EBX
mdefine_line|#define UPT_EBX(regs) SC_EBX((regs)-&gt;sc)
DECL|macro|UPT_ECX
mdefine_line|#define UPT_ECX(regs) SC_ECX((regs)-&gt;sc)
DECL|macro|UPT_EDX
mdefine_line|#define UPT_EDX(regs) SC_EDX((regs)-&gt;sc)
DECL|macro|UPT_ESI
mdefine_line|#define UPT_ESI(regs) SC_ESI((regs)-&gt;sc)
DECL|macro|UPT_EDI
mdefine_line|#define UPT_EDI(regs) SC_EDI((regs)-&gt;sc)
DECL|macro|UPT_EBP
mdefine_line|#define UPT_EBP(regs) SC_EBP((regs)-&gt;sc)
DECL|macro|UPT_ORIG_EAX
mdefine_line|#define UPT_ORIG_EAX(regs) ((regs)-&gt;syscall)
DECL|macro|UPT_CS
mdefine_line|#define UPT_CS(regs) SC_CS((regs)-&gt;sc)
DECL|macro|UPT_SS
mdefine_line|#define UPT_SS(regs) SC_SS((regs)-&gt;sc)
DECL|macro|UPT_DS
mdefine_line|#define UPT_DS(regs) SC_DS((regs)-&gt;sc)
DECL|macro|UPT_ES
mdefine_line|#define UPT_ES(regs) SC_ES((regs)-&gt;sc)
DECL|macro|UPT_FS
mdefine_line|#define UPT_FS(regs) SC_FS((regs)-&gt;sc)
DECL|macro|UPT_GS
mdefine_line|#define UPT_GS(regs) SC_GS((regs)-&gt;sc)
DECL|macro|UPT_SC
mdefine_line|#define UPT_SC(regs) ((regs)-&gt;sc)
DECL|macro|UPT_REG
mdefine_line|#define UPT_REG(regs, reg) &bslash;&n;&t;({&t;unsigned long val; &bslash;&n;&t;&t;switch(reg){ &bslash;&n;&t;&t;case EIP: val = UPT_IP(regs); break; &bslash;&n;&t;&t;case UESP: val = UPT_SP(regs); break; &bslash;&n;&t;&t;case EAX: val = UPT_EAX(regs); break; &bslash;&n;&t;&t;case EBX: val = UPT_EBX(regs); break; &bslash;&n;&t;&t;case ECX: val = UPT_ECX(regs); break; &bslash;&n;&t;&t;case EDX: val = UPT_EDX(regs); break; &bslash;&n;&t;&t;case ESI: val = UPT_ESI(regs); break; &bslash;&n;&t;&t;case EDI: val = UPT_EDI(regs); break; &bslash;&n;&t;&t;case EBP: val = UPT_EBP(regs); break; &bslash;&n;&t;&t;case ORIG_EAX: val = UPT_ORIG_EAX(regs); break; &bslash;&n;&t;&t;case CS: val = UPT_CS(regs); break; &bslash;&n;&t;&t;case SS: val = UPT_SS(regs); break; &bslash;&n;&t;&t;case DS: val = UPT_DS(regs); break; &bslash;&n;&t;&t;case ES: val = UPT_ES(regs); break; &bslash;&n;&t;&t;case FS: val = UPT_FS(regs); break; &bslash;&n;&t;&t;case GS: val = UPT_GS(regs); break; &bslash;&n;&t;&t;case EFL: val = UPT_EFLAGS(regs); break; &bslash;&n;&t;&t;default :  &bslash;&n;&t;&t;&t;panic(&quot;Bad register in UPT_REG : %d&bslash;n&quot;, reg);  &bslash;&n;&t;&t;&t;val = -1; &bslash;&n;&t;&t;} &bslash;&n;&t;        val; &bslash;&n;&t;})
DECL|macro|UPT_SET
mdefine_line|#define UPT_SET(regs, reg, val) &bslash;&n;&t;do { &bslash;&n;&t;&t;switch(reg){ &bslash;&n;&t;&t;case EIP: UPT_IP(regs) = val; break; &bslash;&n;&t;&t;case UESP: UPT_SP(regs) = val; break; &bslash;&n;&t;&t;case EAX: UPT_EAX(regs) = val; break; &bslash;&n;&t;&t;case EBX: UPT_EBX(regs) = val; break; &bslash;&n;&t;&t;case ECX: UPT_ECX(regs) = val; break; &bslash;&n;&t;&t;case EDX: UPT_EDX(regs) = val; break; &bslash;&n;&t;&t;case ESI: UPT_ESI(regs) = val; break; &bslash;&n;&t;&t;case EDI: UPT_EDI(regs) = val; break; &bslash;&n;&t;&t;case EBP: UPT_EBP(regs) = val; break; &bslash;&n;&t;&t;case ORIG_EAX: UPT_ORIG_EAX(regs) = val; break; &bslash;&n;&t;&t;case CS: UPT_CS(regs) = val; break; &bslash;&n;&t;&t;case SS: UPT_SS(regs) = val; break; &bslash;&n;&t;&t;case DS: UPT_DS(regs) = val; break; &bslash;&n;&t;&t;case ES: UPT_ES(regs) = val; break; &bslash;&n;&t;&t;case FS: UPT_FS(regs) = val; break; &bslash;&n;&t;&t;case GS: UPT_GS(regs) = val; break; &bslash;&n;&t;&t;case EFL: UPT_EFLAGS(regs) = val; break; &bslash;&n;&t;&t;default :  &bslash;&n;&t;&t;&t;panic(&quot;Bad register in UPT_SET : %d&bslash;n&quot;, reg);  &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
DECL|macro|UPT_SET_SYSCALL_RETURN
mdefine_line|#define UPT_SET_SYSCALL_RETURN(regs, res) &bslash;&n;&t;SC_SET_SYSCALL_RETURN((regs)-&gt;sc, (res))
DECL|macro|UPT_RESTART_SYSCALL
mdefine_line|#define UPT_RESTART_SYSCALL(regs) SC_RESTART_SYSCALL((regs)-&gt;sc)
DECL|macro|UPT_ORIG_SYSCALL
mdefine_line|#define UPT_ORIG_SYSCALL(regs) UPT_EAX(regs)
DECL|macro|UPT_SYSCALL_NR
mdefine_line|#define UPT_SYSCALL_NR(regs) ((regs)-&gt;syscall)
DECL|macro|UPT_SYSCALL_RET
mdefine_line|#define UPT_SYSCALL_RET(regs) UPT_EAX(regs)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
