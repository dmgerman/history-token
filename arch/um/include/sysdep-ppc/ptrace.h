multiline_comment|/* &n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYS_PTRACE_PPC_H
DECL|macro|__SYS_PTRACE_PPC_H
mdefine_line|#define __SYS_PTRACE_PPC_H
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/types.h&quot;
multiline_comment|/* the following taken from &lt;asm-ppc/ptrace.h&gt; */
macro_line|#ifdef CONFIG_PPC64
DECL|macro|PPC_REG
mdefine_line|#define PPC_REG unsigned long /*long*/
macro_line|#else
DECL|macro|PPC_REG
mdefine_line|#define PPC_REG unsigned long
macro_line|#endif
DECL|struct|sys_pt_regs_s
r_struct
id|sys_pt_regs_s
(brace
DECL|member|gpr
id|PPC_REG
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|nip
id|PPC_REG
id|nip
suffix:semicolon
DECL|member|msr
id|PPC_REG
id|msr
suffix:semicolon
DECL|member|orig_gpr3
id|PPC_REG
id|orig_gpr3
suffix:semicolon
multiline_comment|/* Used for restarting system calls */
DECL|member|ctr
id|PPC_REG
id|ctr
suffix:semicolon
DECL|member|link
id|PPC_REG
id|link
suffix:semicolon
DECL|member|xer
id|PPC_REG
id|xer
suffix:semicolon
DECL|member|ccr
id|PPC_REG
id|ccr
suffix:semicolon
DECL|member|mq
id|PPC_REG
id|mq
suffix:semicolon
multiline_comment|/* 601 only (not used at present) */
multiline_comment|/* Used on APUS to hold IPL value. */
DECL|member|trap
id|PPC_REG
id|trap
suffix:semicolon
multiline_comment|/* Reason for being here */
DECL|member|dar
id|PPC_REG
id|dar
suffix:semicolon
multiline_comment|/* Fault registers */
DECL|member|dsisr
id|PPC_REG
id|dsisr
suffix:semicolon
DECL|member|result
id|PPC_REG
id|result
suffix:semicolon
multiline_comment|/* Result of a system call */
)brace
suffix:semicolon
DECL|macro|NUM_REGS
mdefine_line|#define NUM_REGS (sizeof(struct sys_pt_regs_s) / sizeof(PPC_REG))
DECL|struct|sys_pt_regs
r_struct
id|sys_pt_regs
(brace
DECL|member|regs
id|PPC_REG
id|regs
(braket
r_sizeof
(paren
r_struct
id|sys_pt_regs_s
)paren
op_div
r_sizeof
(paren
id|PPC_REG
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UM_MAX_REG
mdefine_line|#define UM_MAX_REG (PT_FPR0)
DECL|macro|UM_MAX_REG_OFFSET
mdefine_line|#define UM_MAX_REG_OFFSET (UM_MAX_REG * sizeof(PPC_REG))
DECL|macro|EMPTY_REGS
mdefine_line|#define EMPTY_REGS { { [ 0 ... NUM_REGS - 1] = 0 } }
DECL|macro|UM_REG
mdefine_line|#define UM_REG(r, n) ((r)-&gt;regs[n])
DECL|macro|UM_SYSCALL_RET
mdefine_line|#define UM_SYSCALL_RET(r) UM_REG(r, PT_R3)
DECL|macro|UM_SP
mdefine_line|#define UM_SP(r) UM_REG(r, PT_R1)
DECL|macro|UM_IP
mdefine_line|#define UM_IP(r) UM_REG(r, PT_NIP)
DECL|macro|UM_ELF_ZERO
mdefine_line|#define UM_ELF_ZERO(r) UM_REG(r, PT_FPSCR)
DECL|macro|UM_SYSCALL_NR
mdefine_line|#define UM_SYSCALL_NR(r) UM_REG(r, PT_R0)
DECL|macro|UM_SYSCALL_ARG1
mdefine_line|#define UM_SYSCALL_ARG1(r) UM_REG(r, PT_ORIG_R3)
DECL|macro|UM_SYSCALL_ARG2
mdefine_line|#define UM_SYSCALL_ARG2(r) UM_REG(r, PT_R4)
DECL|macro|UM_SYSCALL_ARG3
mdefine_line|#define UM_SYSCALL_ARG3(r) UM_REG(r, PT_R5)
DECL|macro|UM_SYSCALL_ARG4
mdefine_line|#define UM_SYSCALL_ARG4(r) UM_REG(r, PT_R6)
DECL|macro|UM_SYSCALL_ARG5
mdefine_line|#define UM_SYSCALL_ARG5(r) UM_REG(r, PT_R7)
DECL|macro|UM_SYSCALL_ARG6
mdefine_line|#define UM_SYSCALL_ARG6(r) UM_REG(r, PT_R8)
DECL|macro|UM_SYSCALL_NR_OFFSET
mdefine_line|#define UM_SYSCALL_NR_OFFSET (PT_R0 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_RET_OFFSET
mdefine_line|#define UM_SYSCALL_RET_OFFSET (PT_R3 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_ARG1_OFFSET
mdefine_line|#define UM_SYSCALL_ARG1_OFFSET (PT_R3 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_ARG2_OFFSET
mdefine_line|#define UM_SYSCALL_ARG2_OFFSET (PT_R4 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_ARG3_OFFSET
mdefine_line|#define UM_SYSCALL_ARG3_OFFSET (PT_R5 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_ARG4_OFFSET
mdefine_line|#define UM_SYSCALL_ARG4_OFFSET (PT_R6 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_ARG5_OFFSET
mdefine_line|#define UM_SYSCALL_ARG5_OFFSET (PT_R7 * sizeof(PPC_REG))
DECL|macro|UM_SYSCALL_ARG6_OFFSET
mdefine_line|#define UM_SYSCALL_ARG6_OFFSET (PT_R8 * sizeof(PPC_REG))
DECL|macro|UM_SP_OFFSET
mdefine_line|#define UM_SP_OFFSET (PT_R1 * sizeof(PPC_REG))
DECL|macro|UM_IP_OFFSET
mdefine_line|#define UM_IP_OFFSET (PT_NIP * sizeof(PPC_REG))
DECL|macro|UM_ELF_ZERO_OFFSET
mdefine_line|#define UM_ELF_ZERO_OFFSET (PT_R3 * sizeof(PPC_REG))
DECL|macro|UM_SET_SYSCALL_RETURN
mdefine_line|#define UM_SET_SYSCALL_RETURN(_regs, result)&t;        &bslash;&n;do {                                                    &bslash;&n;        if (result &lt; 0) {&t;&t;&t;&t;&bslash;&n;&t;&t;(_regs)-&gt;regs[PT_CCR] |= 0x10000000;&t;&bslash;&n;&t;&t;UM_SYSCALL_RET((_regs)) = -result;&t;&bslash;&n;        } else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;UM_SYSCALL_RET((_regs)) = result;&t;&bslash;&n;        }                                               &bslash;&n;} while(0)
r_extern
r_void
id|shove_aux_table
c_func
(paren
r_int
r_int
id|sp
)paren
suffix:semicolon
DECL|macro|UM_FIX_EXEC_STACK
mdefine_line|#define UM_FIX_EXEC_STACK(sp) shove_aux_table(sp);
multiline_comment|/* These aren&squot;t actually defined.  The undefs are just to make sure&n; * everyone&squot;s clear on the concept.&n; */
DECL|macro|UML_HAVE_GETREGS
macro_line|#undef UML_HAVE_GETREGS
DECL|macro|UML_HAVE_GETFPREGS
macro_line|#undef UML_HAVE_GETFPREGS
DECL|macro|UML_HAVE_SETREGS
macro_line|#undef UML_HAVE_SETREGS
DECL|macro|UML_HAVE_SETFPREGS
macro_line|#undef UML_HAVE_SETFPREGS
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
