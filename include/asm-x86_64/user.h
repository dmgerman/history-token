macro_line|#ifndef _X86_64_USER_H
DECL|macro|_X86_64_USER_H
mdefine_line|#define _X86_64_USER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
multiline_comment|/* Core file format: The core file is written in such a way that gdb&n;   can understand it and provide useful information to the user.&n;   There are quite a number of obstacles to being able to view the&n;   contents of the floating point registers, and until these are&n;   solved you will not be able to view the contents of them.&n;   Actually, you can read in the core file and look at the contents of&n;   the user struct to find out what the floating point registers&n;   contain.&n;&n;   The actual file contents are as follows:&n;   UPAGE: 1 page consisting of a user struct that tells gdb what is present&n;   in the file.  Directly after this is a copy of the task_struct, which&n;   is currently not used by gdb, but it may come in useful at some point.&n;   All of the registers are stored as part of the upage.  The upage should&n;   always be only one page.&n;   DATA: The data area is stored.  We use current-&gt;end_text to&n;   current-&gt;brk to pick up all of the user variables, plus any memory&n;   that may have been malloced.  No attempt is made to determine if a page&n;   is demand-zero or if a page is totally unused, we just cover the entire&n;   range.  All of the addresses are rounded in such a way that an integral&n;   number of pages is written.&n;   STACK: We need the stack information in order to get a meaningful&n;   backtrace.  We need to write the data from (esp) to&n;   current-&gt;start_stack, so we round each of these off in order to be able&n;   to write an integer number of pages.&n;   The minimum core file size is 3 pages, or 12288 bytes.  */
multiline_comment|/*&n; * Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; *&n; * Provide support for the GDB 5.0+ PTRACE_{GET|SET}FPXREGS requests for&n; * interacting with the FXSR-format floating point environment.  Floating&n; * point data can be accessed in the regular format in the usual manner,&n; * and both the standard and SIMD floating point data can be accessed via&n; * the new ptrace requests.  In either case, changes to the FPU environment&n; * will be reflected in the task&squot;s state as expected.&n; * &n; * x86-64 support by Andi Kleen.&n; */
multiline_comment|/* This matches the 64bit FXSAVE format as defined by AMD. It is the same&n;   as the 32bit format defined by Intel, except that the selector:offset pairs for&n;   data and eip are replaced with flat 64bit pointers. */
DECL|struct|user_i387_struct
r_struct
id|user_i387_struct
(brace
DECL|member|cwd
r_int
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
r_int
id|twd
suffix:semicolon
multiline_comment|/* Note this is not the same as the 32bit/x87/FSAVE twd */
DECL|member|fop
r_int
r_int
id|fop
suffix:semicolon
DECL|member|rip
id|u64
id|rip
suffix:semicolon
DECL|member|rdp
id|u64
id|rdp
suffix:semicolon
DECL|member|mxcsr
id|u32
id|mxcsr
suffix:semicolon
DECL|member|mxcsr_mask
id|u32
id|mxcsr_mask
suffix:semicolon
DECL|member|st_space
id|u32
id|st_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each FP-reg = 128 bytes */
DECL|member|xmm_space
id|u32
id|xmm_space
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 16*16 bytes for each XMM-reg = 256 bytes */
DECL|member|padding
id|u32
id|padding
(braket
l_int|24
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Segment register layout in coredumps.&n; */
DECL|struct|user_regs_struct
r_struct
id|user_regs_struct
(brace
DECL|member|r15
DECL|member|r14
DECL|member|r13
DECL|member|r12
DECL|member|rbp
DECL|member|rbx
DECL|member|r11
DECL|member|r10
r_int
r_int
id|r15
comma
id|r14
comma
id|r13
comma
id|r12
comma
id|rbp
comma
id|rbx
comma
id|r11
comma
id|r10
suffix:semicolon
DECL|member|r9
DECL|member|r8
DECL|member|rax
DECL|member|rcx
DECL|member|rdx
DECL|member|rsi
DECL|member|rdi
DECL|member|orig_rax
r_int
r_int
id|r9
comma
id|r8
comma
id|rax
comma
id|rcx
comma
id|rdx
comma
id|rsi
comma
id|rdi
comma
id|orig_rax
suffix:semicolon
DECL|member|rip
DECL|member|cs
DECL|member|eflags
r_int
r_int
id|rip
comma
id|cs
comma
id|eflags
suffix:semicolon
DECL|member|rsp
DECL|member|ss
r_int
r_int
id|rsp
comma
id|ss
suffix:semicolon
DECL|member|fs_base
DECL|member|gs_base
r_int
r_int
id|fs_base
comma
id|gs_base
suffix:semicolon
DECL|member|ds
DECL|member|es
DECL|member|fs
DECL|member|gs
r_int
r_int
id|ds
comma
id|es
comma
id|fs
comma
id|gs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* When the kernel dumps core, it starts by dumping the user struct -&n;   this will be used by gdb to figure out where the data and stack segments&n;   are within the file, and what virtual addresses to use. */
DECL|struct|user
r_struct
id|user
(brace
multiline_comment|/* We start with the registers, to mimic the way that &quot;memory&quot; is returned&n;   from the ptrace(3,...) function.  */
DECL|member|regs
r_struct
id|user_regs_struct
id|regs
suffix:semicolon
multiline_comment|/* Where the registers are actually stored */
multiline_comment|/* ptrace does not yet supply these.  Someday.... */
DECL|member|u_fpvalid
r_int
id|u_fpvalid
suffix:semicolon
multiline_comment|/* True if math co-processor being used. */
multiline_comment|/* for this mess. Not yet used. */
DECL|member|i387
r_struct
id|user_i387_struct
id|i387
suffix:semicolon
multiline_comment|/* Math Co-processor registers. */
multiline_comment|/* The rest of this junk is to help gdb figure out what goes where */
DECL|member|u_tsize
r_int
r_int
r_int
id|u_tsize
suffix:semicolon
multiline_comment|/* Text segment size (pages). */
DECL|member|u_dsize
r_int
r_int
r_int
id|u_dsize
suffix:semicolon
multiline_comment|/* Data segment size (pages). */
DECL|member|u_ssize
r_int
r_int
r_int
id|u_ssize
suffix:semicolon
multiline_comment|/* Stack segment size (pages). */
DECL|member|start_code
r_int
r_int
id|start_code
suffix:semicolon
multiline_comment|/* Starting virtual address of text. */
DECL|member|start_stack
r_int
r_int
id|start_stack
suffix:semicolon
multiline_comment|/* Starting virtual address of stack area.&n;&t;&t;&t;&t;   This is actually the bottom of the stack,&n;&t;&t;&t;&t;   the top of the stack is always found in the&n;&t;&t;&t;&t;   esp register.  */
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
multiline_comment|/* Signal that caused the core dump. */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* No longer used */
DECL|member|u_ar0
r_struct
id|user_pt_regs
op_star
id|u_ar0
suffix:semicolon
multiline_comment|/* Used by gdb to help find the values for */
multiline_comment|/* the registers. */
DECL|member|u_fpstate
r_struct
id|user_i387_struct
op_star
id|u_fpstate
suffix:semicolon
multiline_comment|/* Math Co-processor pointer. */
DECL|member|magic
r_int
r_int
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
r_int
id|u_debugreg
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NBPG
mdefine_line|#define NBPG PAGE_SIZE
DECL|macro|UPAGES
mdefine_line|#define UPAGES 1
DECL|macro|HOST_TEXT_START_ADDR
mdefine_line|#define HOST_TEXT_START_ADDR (u.start_code)
DECL|macro|HOST_STACK_END_ADDR
mdefine_line|#define HOST_STACK_END_ADDR (u.start_stack + u.u_ssize * NBPG)
macro_line|#endif /* _X86_64_USER_H */
eof
