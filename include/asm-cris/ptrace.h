macro_line|#ifndef _CRIS_PTRACE_H
DECL|macro|_CRIS_PTRACE_H
mdefine_line|#define _CRIS_PTRACE_H
multiline_comment|/* Register numbers in the ptrace system call interface */
DECL|macro|PT_FRAMETYPE
mdefine_line|#define PT_FRAMETYPE 0
DECL|macro|PT_ORIG_R10
mdefine_line|#define PT_ORIG_R10  1
DECL|macro|PT_R13
mdefine_line|#define PT_R13       2
DECL|macro|PT_R12
mdefine_line|#define PT_R12       3
DECL|macro|PT_R11
mdefine_line|#define PT_R11       4
DECL|macro|PT_R10
mdefine_line|#define PT_R10       5
DECL|macro|PT_R9
mdefine_line|#define PT_R9        6
DECL|macro|PT_R8
mdefine_line|#define PT_R8        7
DECL|macro|PT_R7
mdefine_line|#define PT_R7        8
DECL|macro|PT_R6
mdefine_line|#define PT_R6        9
DECL|macro|PT_R5
mdefine_line|#define PT_R5        10
DECL|macro|PT_R4
mdefine_line|#define PT_R4        11
DECL|macro|PT_R3
mdefine_line|#define PT_R3        12
DECL|macro|PT_R2
mdefine_line|#define PT_R2        13
DECL|macro|PT_R1
mdefine_line|#define PT_R1        14
DECL|macro|PT_R0
mdefine_line|#define PT_R0        15
DECL|macro|PT_MOF
mdefine_line|#define PT_MOF       16
DECL|macro|PT_DCCR
mdefine_line|#define PT_DCCR      17
DECL|macro|PT_SRP
mdefine_line|#define PT_SRP       18
DECL|macro|PT_IRP
mdefine_line|#define PT_IRP       19    /* This is actually the debugged process&squot; PC */
DECL|macro|PT_CSRINSTR
mdefine_line|#define PT_CSRINSTR  20    /* CPU Status record remnants -&n;&t;&t;&t;      valid if frametype == busfault */
DECL|macro|PT_CSRADDR
mdefine_line|#define PT_CSRADDR   21
DECL|macro|PT_CSRDATA
mdefine_line|#define PT_CSRDATA   22
DECL|macro|PT_USP
mdefine_line|#define PT_USP       23    /* special case - USP is not in the pt_regs */
DECL|macro|PT_MAX
mdefine_line|#define PT_MAX       23
multiline_comment|/* Frame types */
DECL|macro|CRIS_FRAME_NORMAL
mdefine_line|#define CRIS_FRAME_NORMAL   0 /* normal frame without SBFS stacking */
DECL|macro|CRIS_FRAME_BUSFAULT
mdefine_line|#define CRIS_FRAME_BUSFAULT 1 /* frame stacked using SBFS, need RBF return&n;&t;&t;&t;&t; path */
multiline_comment|/* pt_regs not only specifices the format in the user-struct during&n; * ptrace but is also the frame format used in the kernel prologue/epilogues &n; * themselves&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|frametype
r_int
r_int
id|frametype
suffix:semicolon
multiline_comment|/* type of stackframe */
DECL|member|orig_r10
r_int
r_int
id|orig_r10
suffix:semicolon
multiline_comment|/* pushed by movem r13, [sp] in SAVE_ALL, movem pushes backwards */
DECL|member|r13
r_int
r_int
id|r13
suffix:semicolon
DECL|member|r12
r_int
r_int
id|r12
suffix:semicolon
DECL|member|r11
r_int
r_int
id|r11
suffix:semicolon
DECL|member|r10
r_int
r_int
id|r10
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r3
r_int
r_int
id|r3
suffix:semicolon
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
DECL|member|r1
r_int
r_int
id|r1
suffix:semicolon
DECL|member|r0
r_int
r_int
id|r0
suffix:semicolon
DECL|member|mof
r_int
r_int
id|mof
suffix:semicolon
DECL|member|dccr
r_int
r_int
id|dccr
suffix:semicolon
DECL|member|srp
r_int
r_int
id|srp
suffix:semicolon
DECL|member|irp
r_int
r_int
id|irp
suffix:semicolon
multiline_comment|/* This is actually the debugged process&squot; PC */
DECL|member|csrinstr
r_int
r_int
id|csrinstr
suffix:semicolon
DECL|member|csraddr
r_int
r_int
id|csraddr
suffix:semicolon
DECL|member|csrdata
r_int
r_int
id|csrdata
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* switch_stack is the extra stuff pushed onto the stack in _resume (entry.S)&n; * when doing a context-switch. it is used (apart from in resume) when a new&n; * thread is made and we need to make _resume (which is starting it for the&n; * first time) realise what is going on.&n; *&n; * Actually, the use is very close to the thread struct (TSS) in that both the&n; * switch_stack and the TSS are used to keep thread stuff when switching in&n; * _resume.&n; */
DECL|struct|switch_stack
r_struct
id|switch_stack
(brace
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r3
r_int
r_int
id|r3
suffix:semicolon
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
DECL|member|r1
r_int
r_int
id|r1
suffix:semicolon
DECL|member|r0
r_int
r_int
id|r0
suffix:semicolon
DECL|member|return_ip
r_int
r_int
id|return_ip
suffix:semicolon
multiline_comment|/* ip that _resume will return to */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS            12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS            13
multiline_comment|/* bit 8 is user-mode flag */
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((regs)-&gt;dccr &amp; 0x100)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;irp)
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _CRIS_PTRACE_H */
eof
