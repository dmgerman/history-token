macro_line|#ifndef USER32_H
DECL|macro|USER32_H
mdefine_line|#define USER32_H 1
multiline_comment|/* IA32 compatible user structures for ptrace. These should be used for 32bit coredumps too. */
DECL|struct|user_i387_ia32_struct
r_struct
id|user_i387_ia32_struct
(brace
DECL|member|cwd
id|u32
id|cwd
suffix:semicolon
DECL|member|swd
id|u32
id|swd
suffix:semicolon
DECL|member|twd
id|u32
id|twd
suffix:semicolon
DECL|member|fip
id|u32
id|fip
suffix:semicolon
DECL|member|fcs
id|u32
id|fcs
suffix:semicolon
DECL|member|foo
id|u32
id|foo
suffix:semicolon
DECL|member|fos
id|u32
id|fos
suffix:semicolon
DECL|member|st_space
id|u32
id|st_space
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the old layout of &quot;struct pt_regs&quot;, and&n; * is still the layout used by user mode (the new&n; * pt_regs doesn&squot;t have all registers as the kernel&n; * doesn&squot;t use the extra segment registers)&n; */
DECL|struct|user_regs_struct32
r_struct
id|user_regs_struct32
(brace
DECL|member|ebx
DECL|member|ecx
DECL|member|edx
DECL|member|esi
DECL|member|edi
DECL|member|ebp
DECL|member|eax
id|__u32
id|ebx
comma
id|ecx
comma
id|edx
comma
id|esi
comma
id|edi
comma
id|ebp
comma
id|eax
suffix:semicolon
DECL|member|ds
DECL|member|__ds
DECL|member|es
DECL|member|__es
r_int
r_int
id|ds
comma
id|__ds
comma
id|es
comma
id|__es
suffix:semicolon
DECL|member|fs
DECL|member|__fs
DECL|member|gs
DECL|member|__gs
r_int
r_int
id|fs
comma
id|__fs
comma
id|gs
comma
id|__gs
suffix:semicolon
DECL|member|orig_eax
DECL|member|eip
id|__u32
id|orig_eax
comma
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__cs
r_int
r_int
id|cs
comma
id|__cs
suffix:semicolon
DECL|member|eflags
DECL|member|esp
id|__u32
id|eflags
comma
id|esp
suffix:semicolon
DECL|member|ss
DECL|member|__ss
r_int
r_int
id|ss
comma
id|__ss
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|user32
r_struct
id|user32
(brace
DECL|member|regs
r_struct
id|user_regs_struct32
id|regs
suffix:semicolon
multiline_comment|/* Where the registers are actually stored */
DECL|member|u_fpvalid
r_int
id|u_fpvalid
suffix:semicolon
multiline_comment|/* True if math co-processor being used. */
multiline_comment|/* for this mess. Not yet used. */
DECL|member|i387
r_struct
id|user_i387_ia32_struct
id|i387
suffix:semicolon
multiline_comment|/* Math Co-processor registers. */
multiline_comment|/* The rest of this junk is to help gdb figure out what goes where */
DECL|member|u_tsize
id|__u32
id|u_tsize
suffix:semicolon
multiline_comment|/* Text segment size (pages). */
DECL|member|u_dsize
id|__u32
id|u_dsize
suffix:semicolon
multiline_comment|/* Data segment size (pages). */
DECL|member|u_ssize
id|__u32
id|u_ssize
suffix:semicolon
multiline_comment|/* Stack segment size (pages). */
DECL|member|start_code
id|__u32
id|start_code
suffix:semicolon
multiline_comment|/* Starting virtual address of text. */
DECL|member|start_stack
id|__u32
id|start_stack
suffix:semicolon
multiline_comment|/* Starting virtual address of stack area.&n;&t;&t;&t;&t;   This is actually the bottom of the stack,&n;&t;&t;&t;&t;   the top of the stack is always found in the&n;&t;&t;&t;&t;   esp register.  */
DECL|member|signal
id|__u32
id|signal
suffix:semicolon
multiline_comment|/* Signal that caused the core dump. */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* No __u32er used */
DECL|member|u_ar0
id|__u32
id|u_ar0
suffix:semicolon
multiline_comment|/* Used by gdb to help find the values for */
multiline_comment|/* the registers. */
DECL|member|u_fpstate
id|__u32
id|u_fpstate
suffix:semicolon
multiline_comment|/* Math Co-processor pointer. */
DECL|member|magic
id|__u32
id|magic
suffix:semicolon
multiline_comment|/* To uniquely identify a core file */
DECL|member|u_comm
r_char
id|u_comm
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* User command that was responsible */
DECL|member|u_debugreg
r_int
id|u_debugreg
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
