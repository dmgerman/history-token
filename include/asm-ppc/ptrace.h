multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#ifndef _PPC_PTRACE_H
DECL|macro|_PPC_PTRACE_H
mdefine_line|#define _PPC_PTRACE_H
multiline_comment|/*&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; *&n; * this should only contain volatile regs&n; * since we can keep non-volatile in the thread_struct&n; * should set this up when only volatiles are saved&n; * by intr code.&n; *&n; * Since this is going on the stack, *CARE MUST BE TAKEN* to insure&n; * that the overall structure is a multiple of 16 bytes in length.&n; *&n; * Note that the offsets of the fields in this struct correspond with&n; * the PT_* values below.  This simplifies arch/ppc/kernel/ptrace.c.&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|gpr
r_int
r_int
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|nip
r_int
r_int
id|nip
suffix:semicolon
DECL|member|msr
r_int
r_int
id|msr
suffix:semicolon
DECL|member|orig_gpr3
r_int
r_int
id|orig_gpr3
suffix:semicolon
multiline_comment|/* Used for restarting system calls */
DECL|member|ctr
r_int
r_int
id|ctr
suffix:semicolon
DECL|member|link
r_int
r_int
id|link
suffix:semicolon
DECL|member|xer
r_int
r_int
id|xer
suffix:semicolon
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
DECL|member|mq
r_int
r_int
id|mq
suffix:semicolon
multiline_comment|/* 601 only (not used at present) */
multiline_comment|/* Used on APUS to hold IPL value. */
DECL|member|trap
r_int
r_int
id|trap
suffix:semicolon
multiline_comment|/* Reason for being here */
DECL|member|dar
r_int
r_int
id|dar
suffix:semicolon
multiline_comment|/* Fault registers */
DECL|member|dsisr
r_int
r_int
id|dsisr
suffix:semicolon
DECL|member|result
r_int
r_int
id|result
suffix:semicolon
multiline_comment|/* Result of a system call */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* iSeries uses mq field for soft enable flag */
DECL|macro|softEnable
mdefine_line|#define softEnable mq
macro_line|#ifdef __KERNEL__
DECL|macro|STACK_FRAME_OVERHEAD
mdefine_line|#define STACK_FRAME_OVERHEAD&t;16&t;/* size of minimum stack frame */
multiline_comment|/* Size of stack frame allocated when calling signal handler. */
DECL|macro|__SIGNAL_FRAMESIZE
mdefine_line|#define __SIGNAL_FRAMESIZE&t;64
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;nip)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;msr &amp; MSR_PR) != 0)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Offsets used by &squot;ptrace&squot; system call interface.&n; * These can&squot;t be changed without breaking binary compatibility&n; * with MkLinux, etc.&n; */
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
DECL|macro|PT_MQ
mdefine_line|#define PT_MQ&t;39
DECL|macro|PT_FPR0
mdefine_line|#define PT_FPR0&t;48&t;/* each FP reg occupies 2 slots in this space */
DECL|macro|PT_FPR31
mdefine_line|#define PT_FPR31 (PT_FPR0 + 2*31)
DECL|macro|PT_FPSCR
mdefine_line|#define PT_FPSCR (PT_FPR0 + 2*32 + 1)
multiline_comment|/* Get/set all the altivec registers vr0..vr31, vscr, vrsave, in one go */
DECL|macro|PTRACE_GETVRREGS
mdefine_line|#define PTRACE_GETVRREGS&t;18
DECL|macro|PTRACE_SETVRREGS
mdefine_line|#define PTRACE_SETVRREGS&t;19
macro_line|#endif
eof
