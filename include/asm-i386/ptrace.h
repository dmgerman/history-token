macro_line|#ifndef _I386_PTRACE_H
DECL|macro|_I386_PTRACE_H
mdefine_line|#define _I386_PTRACE_H
DECL|macro|EBX
mdefine_line|#define EBX 0
DECL|macro|ECX
mdefine_line|#define ECX 1
DECL|macro|EDX
mdefine_line|#define EDX 2
DECL|macro|ESI
mdefine_line|#define ESI 3
DECL|macro|EDI
mdefine_line|#define EDI 4
DECL|macro|EBP
mdefine_line|#define EBP 5
DECL|macro|EAX
mdefine_line|#define EAX 6
DECL|macro|DS
mdefine_line|#define DS 7
DECL|macro|ES
mdefine_line|#define ES 8
DECL|macro|FS
mdefine_line|#define FS 9
DECL|macro|GS
mdefine_line|#define GS 10
DECL|macro|ORIG_EAX
mdefine_line|#define ORIG_EAX 11
DECL|macro|EIP
mdefine_line|#define EIP 12
DECL|macro|CS
mdefine_line|#define CS  13
DECL|macro|EFL
mdefine_line|#define EFL 14
DECL|macro|UESP
mdefine_line|#define UESP 15
DECL|macro|SS
mdefine_line|#define SS   16
DECL|macro|FRAME_SIZE
mdefine_line|#define FRAME_SIZE 17
multiline_comment|/* this struct defines the way the registers are stored on the &n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|ebx
r_int
id|ebx
suffix:semicolon
DECL|member|ecx
r_int
id|ecx
suffix:semicolon
DECL|member|edx
r_int
id|edx
suffix:semicolon
DECL|member|esi
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
id|edi
suffix:semicolon
DECL|member|ebp
r_int
id|ebp
suffix:semicolon
DECL|member|eax
r_int
id|eax
suffix:semicolon
DECL|member|xds
r_int
id|xds
suffix:semicolon
DECL|member|xes
r_int
id|xes
suffix:semicolon
DECL|member|orig_eax
r_int
id|orig_eax
suffix:semicolon
DECL|member|eip
r_int
id|eip
suffix:semicolon
DECL|member|xcs
r_int
id|xcs
suffix:semicolon
DECL|member|eflags
r_int
id|eflags
suffix:semicolon
DECL|member|esp
r_int
id|esp
suffix:semicolon
DECL|member|xss
r_int
id|xss
suffix:semicolon
)brace
suffix:semicolon
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
DECL|macro|PTRACE_OLDSETOPTIONS
mdefine_line|#define PTRACE_OLDSETOPTIONS         21
DECL|macro|PTRACE_GET_THREAD_AREA
mdefine_line|#define PTRACE_GET_THREAD_AREA    25
DECL|macro|PTRACE_SET_THREAD_AREA
mdefine_line|#define PTRACE_SET_THREAD_AREA    26
macro_line|#ifdef __KERNEL__
r_struct
id|task_struct
suffix:semicolon
r_extern
r_void
id|send_sigtrap
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
suffix:semicolon
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((VM_MASK &amp; (regs)-&gt;eflags) || (3 &amp; (regs)-&gt;xcs))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;eip)
macro_line|#if defined(CONFIG_SMP) &amp;&amp; defined(CONFIG_FRAME_POINTER)
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
macro_line|#endif
macro_line|#endif
eof
