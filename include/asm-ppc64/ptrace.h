macro_line|#ifndef _PPC64_PTRACE_H
DECL|macro|_PPC64_PTRACE_H
mdefine_line|#define _PPC64_PTRACE_H
multiline_comment|/*&n; * Copyright (C) 2001 PPC64 Team, IBM Corp&n; *&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; *&n; * this should only contain volatile regs&n; * since we can keep non-volatile in the thread_struct&n; * should set this up when only volatiles are saved&n; * by intr code.&n; *&n; * Since this is going on the stack, *CARE MUST BE TAKEN* to insure&n; * that the overall structure is a multiple of 16 bytes in length.&n; *&n; * Note that the offsets of the fields in this struct correspond with&n; * the PT_* values below.  This simplifies arch/ppc64/kernel/ptrace.c.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PPC_REG
mdefine_line|#define PPC_REG unsigned long
DECL|struct|pt_regs
r_struct
id|pt_regs
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
DECL|member|softe
id|PPC_REG
id|softe
suffix:semicolon
multiline_comment|/* Soft enabled/disabled */
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
DECL|macro|PPC_REG_32
mdefine_line|#define PPC_REG_32 unsigned int
DECL|struct|pt_regs32
r_struct
id|pt_regs32
(brace
DECL|member|gpr
id|PPC_REG_32
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|nip
id|PPC_REG_32
id|nip
suffix:semicolon
DECL|member|msr
id|PPC_REG_32
id|msr
suffix:semicolon
DECL|member|orig_gpr3
id|PPC_REG_32
id|orig_gpr3
suffix:semicolon
multiline_comment|/* Used for restarting system calls */
DECL|member|ctr
id|PPC_REG_32
id|ctr
suffix:semicolon
DECL|member|link
id|PPC_REG_32
id|link
suffix:semicolon
DECL|member|xer
id|PPC_REG_32
id|xer
suffix:semicolon
DECL|member|ccr
id|PPC_REG_32
id|ccr
suffix:semicolon
DECL|member|mq
id|PPC_REG_32
id|mq
suffix:semicolon
multiline_comment|/* 601 only (not used at present) */
multiline_comment|/* Used on APUS to hold IPL value. */
DECL|member|trap
id|PPC_REG_32
id|trap
suffix:semicolon
multiline_comment|/* Reason for being here */
DECL|member|dar
id|PPC_REG_32
id|dar
suffix:semicolon
multiline_comment|/* Fault registers */
DECL|member|dsisr
id|PPC_REG_32
id|dsisr
suffix:semicolon
DECL|member|result
id|PPC_REG_32
id|result
suffix:semicolon
multiline_comment|/* Result of a system call */
)brace
suffix:semicolon
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;nip)
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
r_int
id|profile_pc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
DECL|macro|profile_pc
mdefine_line|#define profile_pc(regs) instruction_pointer(regs)
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|STACK_FRAME_OVERHEAD
mdefine_line|#define STACK_FRAME_OVERHEAD&t;112&t;/* size of minimum stack frame */
multiline_comment|/* Size of dummy stack frame allocated when calling signal handler. */
DECL|macro|__SIGNAL_FRAMESIZE
mdefine_line|#define __SIGNAL_FRAMESIZE&t;128
DECL|macro|__SIGNAL_FRAMESIZE32
mdefine_line|#define __SIGNAL_FRAMESIZE32&t;64
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((((regs)-&gt;msr) &gt;&gt; MSR_PR_LG) &amp; 0x1)
DECL|macro|force_successful_syscall_return
mdefine_line|#define force_successful_syscall_return()   &bslash;&n;&t;&t;(current_thread_info()-&gt;syscall_noerror = 1)
multiline_comment|/*&n; * We use the least-significant bit of the trap field to indicate&n; * whether we have saved the full set of registers, or only a&n; * partial set.  A 1 there means the partial set.&n; */
DECL|macro|FULL_REGS
mdefine_line|#define FULL_REGS(regs)&t;&t;(((regs)-&gt;trap &amp; 1) == 0)
DECL|macro|TRAP
mdefine_line|#define TRAP(regs)&t;&t;((regs)-&gt;trap &amp; ~0xF)
DECL|macro|CHECK_FULL_REGS
mdefine_line|#define CHECK_FULL_REGS(regs)&t;BUG_ON(regs-&gt;trap &amp; 1)
multiline_comment|/*&n; * Offsets used by &squot;ptrace&squot; system call interface.&n; */
DECL|macro|PT_R0
mdefine_line|#define PT_R0&t;0
DECL|macro|PT_R1
mdefine_line|#define PT_R1&t;1
DECL|macro|PT_R2
mdefine_line|#define PT_R2&t;2
DECL|macro|PT_R3
mdefine_line|#define PT_R3&t;3
DECL|macro|PT_R4
mdefine_line|#define PT_R4&t;4
DECL|macro|PT_R5
mdefine_line|#define PT_R5&t;5
DECL|macro|PT_R6
mdefine_line|#define PT_R6&t;6
DECL|macro|PT_R7
mdefine_line|#define PT_R7&t;7
DECL|macro|PT_R8
mdefine_line|#define PT_R8&t;8
DECL|macro|PT_R9
mdefine_line|#define PT_R9&t;9
DECL|macro|PT_R10
mdefine_line|#define PT_R10&t;10
DECL|macro|PT_R11
mdefine_line|#define PT_R11&t;11
DECL|macro|PT_R12
mdefine_line|#define PT_R12&t;12
DECL|macro|PT_R13
mdefine_line|#define PT_R13&t;13
DECL|macro|PT_R14
mdefine_line|#define PT_R14&t;14
DECL|macro|PT_R15
mdefine_line|#define PT_R15&t;15
DECL|macro|PT_R16
mdefine_line|#define PT_R16&t;16
DECL|macro|PT_R17
mdefine_line|#define PT_R17&t;17
DECL|macro|PT_R18
mdefine_line|#define PT_R18&t;18
DECL|macro|PT_R19
mdefine_line|#define PT_R19&t;19
DECL|macro|PT_R20
mdefine_line|#define PT_R20&t;20
DECL|macro|PT_R21
mdefine_line|#define PT_R21&t;21
DECL|macro|PT_R22
mdefine_line|#define PT_R22&t;22
DECL|macro|PT_R23
mdefine_line|#define PT_R23&t;23
DECL|macro|PT_R24
mdefine_line|#define PT_R24&t;24
DECL|macro|PT_R25
mdefine_line|#define PT_R25&t;25
DECL|macro|PT_R26
mdefine_line|#define PT_R26&t;26
DECL|macro|PT_R27
mdefine_line|#define PT_R27&t;27
DECL|macro|PT_R28
mdefine_line|#define PT_R28&t;28
DECL|macro|PT_R29
mdefine_line|#define PT_R29&t;29
DECL|macro|PT_R30
mdefine_line|#define PT_R30&t;30
DECL|macro|PT_R31
mdefine_line|#define PT_R31&t;31
DECL|macro|PT_NIP
mdefine_line|#define PT_NIP&t;32
DECL|macro|PT_MSR
mdefine_line|#define PT_MSR&t;33
macro_line|#ifdef __KERNEL__
DECL|macro|PT_ORIG_R3
mdefine_line|#define PT_ORIG_R3 34
macro_line|#endif
DECL|macro|PT_CTR
mdefine_line|#define PT_CTR&t;35
DECL|macro|PT_LNK
mdefine_line|#define PT_LNK&t;36
DECL|macro|PT_XER
mdefine_line|#define PT_XER&t;37
DECL|macro|PT_CCR
mdefine_line|#define PT_CCR&t;38
DECL|macro|PT_SOFTE
mdefine_line|#define PT_SOFTE 39
DECL|macro|PT_RESULT
mdefine_line|#define PT_RESULT 43
DECL|macro|PT_FPR0
mdefine_line|#define PT_FPR0&t;48
multiline_comment|/* Kernel and userspace will both use this PT_FPSCR value.  32-bit apps will have&n; * visibility to the asm-ppc/ptrace.h header instead of this one.&n; */
DECL|macro|PT_FPSCR
mdefine_line|#define PT_FPSCR (PT_FPR0 + 32)&t;  /* each FP reg occupies 1 slot in 64-bit space */
macro_line|#ifdef __KERNEL__
DECL|macro|PT_FPSCR32
mdefine_line|#define PT_FPSCR32 (PT_FPR0 + 2*32 + 1)&t;  /* each FP reg occupies 2 32-bit userspace slots */
macro_line|#endif
DECL|macro|PT_VR0
mdefine_line|#define PT_VR0 82&t;/* each Vector reg occupies 2 slots in 64-bit */
DECL|macro|PT_VSCR
mdefine_line|#define PT_VSCR (PT_VR0 + 32*2 + 1)
DECL|macro|PT_VRSAVE
mdefine_line|#define PT_VRSAVE (PT_VR0 + 33*2)
macro_line|#ifdef __KERNEL__
DECL|macro|PT_VR0_32
mdefine_line|#define PT_VR0_32 164&t;/* each Vector reg occupies 4 slots in 32-bit */
DECL|macro|PT_VSCR_32
mdefine_line|#define PT_VSCR_32 (PT_VR0 + 32*4 + 3)
DECL|macro|PT_VRSAVE_32
mdefine_line|#define PT_VRSAVE_32 (PT_VR0 + 33*4)
macro_line|#endif
multiline_comment|/*&n; * Get/set all the altivec registers vr0..vr31, vscr, vrsave, in one go. &n; * The transfer totals 34 quadword.  Quadwords 0-31 contain the &n; * corresponding vector registers.  Quadword 32 contains the vscr as the &n; * last word (offset 12) within that quadword.  Quadword 33 contains the &n; * vrsave as the first word (offset 0) within the quadword.&n; *&n; * This definition of the VMX state is compatible with the current PPC32 &n; * ptrace interface.  This allows signal handling and ptrace to use the same &n; * structures.  This also simplifies the implementation of a bi-arch &n; * (combined (32- and 64-bit) gdb.&n; */
DECL|macro|PTRACE_GETVRREGS
mdefine_line|#define PTRACE_GETVRREGS&t;18
DECL|macro|PTRACE_SETVRREGS
mdefine_line|#define PTRACE_SETVRREGS&t;19
multiline_comment|/* Additional PTRACE requests implemented on PowerPC. */
DECL|macro|PPC_PTRACE_GETREGS
mdefine_line|#define PPC_PTRACE_GETREGS&t;      0x99  /* Get GPRs 0 - 31 */
DECL|macro|PPC_PTRACE_SETREGS
mdefine_line|#define PPC_PTRACE_SETREGS&t;      0x98  /* Set GPRs 0 - 31 */
DECL|macro|PPC_PTRACE_GETFPREGS
mdefine_line|#define PPC_PTRACE_GETFPREGS&t;    0x97  /* Get FPRs 0 - 31 */
DECL|macro|PPC_PTRACE_SETFPREGS
mdefine_line|#define PPC_PTRACE_SETFPREGS&t;    0x96  /* Set FPRs 0 - 31 */
DECL|macro|PPC_PTRACE_PEEKTEXT_3264
mdefine_line|#define PPC_PTRACE_PEEKTEXT_3264  0x95  /* Read word at location ADDR on a 64-bit process from a 32-bit process. */
DECL|macro|PPC_PTRACE_PEEKDATA_3264
mdefine_line|#define PPC_PTRACE_PEEKDATA_3264  0x94  /* Read word at location ADDR on a 64-bit process from a 32-bit process. */
DECL|macro|PPC_PTRACE_POKETEXT_3264
mdefine_line|#define PPC_PTRACE_POKETEXT_3264  0x93  /* Write word at location ADDR on a 64-bit process from a 32-bit process. */
DECL|macro|PPC_PTRACE_POKEDATA_3264
mdefine_line|#define PPC_PTRACE_POKEDATA_3264  0x92  /* Write word at location ADDR on a 64-bit process from a 32-bit process. */
DECL|macro|PPC_PTRACE_PEEKUSR_3264
mdefine_line|#define PPC_PTRACE_PEEKUSR_3264   0x91  /* Read a register (specified by ADDR) out of the &quot;user area&quot; on a 64-bit process from a 32-bit process. */
DECL|macro|PPC_PTRACE_POKEUSR_3264
mdefine_line|#define PPC_PTRACE_POKEUSR_3264   0x90  /* Write DATA into location ADDR within the &quot;user area&quot; on a 64-bit process from a 32-bit process. */
macro_line|#endif /* _PPC64_PTRACE_H */
eof
