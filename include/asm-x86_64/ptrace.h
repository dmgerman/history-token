macro_line|#ifndef _X86_64_PTRACE_H
DECL|macro|_X86_64_PTRACE_H
mdefine_line|#define _X86_64_PTRACE_H
macro_line|#if defined(__ASSEMBLY__) || defined(__FRAME_OFFSETS) 
DECL|macro|R15
mdefine_line|#define R15 0
DECL|macro|R14
mdefine_line|#define R14 8
DECL|macro|R13
mdefine_line|#define R13 16
DECL|macro|R12
mdefine_line|#define R12 24
DECL|macro|RBP
mdefine_line|#define RBP 36
DECL|macro|RBX
mdefine_line|#define RBX 40
multiline_comment|/* arguments: interrupts/non tracing syscalls only save upto here*/
DECL|macro|R11
mdefine_line|#define R11 48
DECL|macro|R10
mdefine_line|#define R10 56&t;
DECL|macro|R9
mdefine_line|#define R9 64
DECL|macro|R8
mdefine_line|#define R8 72
DECL|macro|RAX
mdefine_line|#define RAX 80
DECL|macro|RCX
mdefine_line|#define RCX 88
DECL|macro|RDX
mdefine_line|#define RDX 96
DECL|macro|RSI
mdefine_line|#define RSI 104
DECL|macro|RDI
mdefine_line|#define RDI 112
DECL|macro|ORIG_RAX
mdefine_line|#define ORIG_RAX 120       /* = ERROR */ 
multiline_comment|/* end of arguments */
multiline_comment|/* cpu exception frame or undefined in case of fast syscall. */
DECL|macro|RIP
mdefine_line|#define RIP 128
DECL|macro|CS
mdefine_line|#define CS 136
DECL|macro|EFLAGS
mdefine_line|#define EFLAGS 144
DECL|macro|RSP
mdefine_line|#define RSP 152
DECL|macro|SS
mdefine_line|#define SS 160
DECL|macro|ARGOFFSET
mdefine_line|#define ARGOFFSET R11
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* top of stack page */
DECL|macro|FRAME_SIZE
mdefine_line|#define FRAME_SIZE 168
DECL|macro|PTRACE_SETOPTIONS
mdefine_line|#define PTRACE_SETOPTIONS         21
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD     0x00000001
multiline_comment|/* Dummy values for ptrace */
DECL|macro|FS
mdefine_line|#define FS 1000 
DECL|macro|GS
mdefine_line|#define GS 1008
macro_line|#ifndef __ASSEMBLY__ 
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|r15
r_int
r_int
id|r15
suffix:semicolon
DECL|member|r14
r_int
r_int
id|r14
suffix:semicolon
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
DECL|member|rbp
r_int
r_int
id|rbp
suffix:semicolon
DECL|member|rbx
r_int
r_int
id|rbx
suffix:semicolon
multiline_comment|/* arguments: non interrupts/non tracing syscalls only save upto here*/
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
DECL|member|rax
r_int
r_int
id|rax
suffix:semicolon
DECL|member|rcx
r_int
r_int
id|rcx
suffix:semicolon
DECL|member|rdx
r_int
r_int
id|rdx
suffix:semicolon
DECL|member|rsi
r_int
r_int
id|rsi
suffix:semicolon
DECL|member|rdi
r_int
r_int
id|rdi
suffix:semicolon
DECL|member|orig_rax
r_int
r_int
id|orig_rax
suffix:semicolon
multiline_comment|/* end of arguments */
multiline_comment|/* cpu exception frame or undefined */
DECL|member|rip
r_int
r_int
id|rip
suffix:semicolon
DECL|member|cs
r_int
r_int
id|cs
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|rsp
r_int
r_int
id|rsp
suffix:semicolon
DECL|member|ss
r_int
r_int
id|ss
suffix:semicolon
multiline_comment|/* top of stack page */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS            12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS            13
DECL|macro|PTRACE_GETFPREGS
mdefine_line|#define PTRACE_GETFPREGS          14
DECL|macro|PTRACE_SETFPREGS
mdefine_line|#define PTRACE_SETFPREGS          15
DECL|macro|PTRACE_GETFPXREGS
mdefine_line|#define PTRACE_GETFPXREGS         18
DECL|macro|PTRACE_SETFPXREGS
mdefine_line|#define PTRACE_SETFPXREGS         19
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__) 
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!!((regs)-&gt;cs &amp; 3))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;rip)
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
r_void
id|signal_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|frame
comma
r_char
op_star
id|where
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|EF_CF
id|EF_CF
op_assign
l_int|0x00000001
comma
DECL|enumerator|EF_PF
id|EF_PF
op_assign
l_int|0x00000004
comma
DECL|enumerator|EF_AF
id|EF_AF
op_assign
l_int|0x00000010
comma
DECL|enumerator|EF_ZF
id|EF_ZF
op_assign
l_int|0x00000040
comma
DECL|enumerator|EF_SF
id|EF_SF
op_assign
l_int|0x00000080
comma
DECL|enumerator|EF_TF
id|EF_TF
op_assign
l_int|0x00000100
comma
DECL|enumerator|EF_IE
id|EF_IE
op_assign
l_int|0x00000200
comma
DECL|enumerator|EF_DF
id|EF_DF
op_assign
l_int|0x00000400
comma
DECL|enumerator|EF_OF
id|EF_OF
op_assign
l_int|0x00000800
comma
DECL|enumerator|EF_IOPL
id|EF_IOPL
op_assign
l_int|0x00003000
comma
DECL|enumerator|EF_IOPL_RING0
id|EF_IOPL_RING0
op_assign
l_int|0x00000000
comma
DECL|enumerator|EF_IOPL_RING1
id|EF_IOPL_RING1
op_assign
l_int|0x00001000
comma
DECL|enumerator|EF_IOPL_RING2
id|EF_IOPL_RING2
op_assign
l_int|0x00002000
comma
DECL|enumerator|EF_NT
id|EF_NT
op_assign
l_int|0x00004000
comma
multiline_comment|/* nested task */
DECL|enumerator|EF_RF
id|EF_RF
op_assign
l_int|0x00010000
comma
multiline_comment|/* resume */
DECL|enumerator|EF_VM
id|EF_VM
op_assign
l_int|0x00020000
comma
multiline_comment|/* virtual mode */
DECL|enumerator|EF_AC
id|EF_AC
op_assign
l_int|0x00040000
comma
multiline_comment|/* alignment */
DECL|enumerator|EF_VIF
id|EF_VIF
op_assign
l_int|0x00080000
comma
multiline_comment|/* virtual interrupt */
DECL|enumerator|EF_VIP
id|EF_VIP
op_assign
l_int|0x00100000
comma
multiline_comment|/* virtual interrupt pending */
DECL|enumerator|EF_ID
id|EF_ID
op_assign
l_int|0x00200000
comma
multiline_comment|/* id */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
